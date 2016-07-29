/*******************************************************************************
 (c) 2005-2016 Copyright, Real-Time Innovations, Inc.  All rights reserved.
 RTI grants Licensee a license to use, modify, compile, and create derivative
 works of the Software.  Licensee has the right to distribute object form only
 for use with RTI products.  The Software is provided "as is", with no warranty
 of any type, including any warranty for fitness for any purpose. RTI is under
 no obligation to maintain or support the Software.  RTI shall not be liable for
 any incidental or consequential damages arising out of the use or inability to
 use the software.
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rti_me_c.h"
#include "wh_sm/wh_sm_history.h"
#include "rh_sm/rh_sm_history.h"

#include "data.h"
#include "dataSupport.h"
#include "dataPlugin.h"
#include "HelloWorldApplication.h"

#include "HL_sci.h"

extern void sciDisplayText(sciBASE_t *sci, uint8_t *text, uint32_t length);
#define sciREGx    sciREG1

char itoaBuffer[10];

#define printf(s, ...) sciDisplayText(sciREG1, s, sizeof(s) - 1)

void printSample(HelloWorld *s)
{
    int lenPrintSample;

    printf("Sample received : ");
    lenPrintSample = snprintf(itoaBuffer, sizeof(itoaBuffer), "%d", s->data1);
    if (lenPrintSample < sizeof(itoaBuffer))
    {
        itoaBuffer[lenPrintSample] = '\n';
        lenPrintSample++;
    }
    sciDisplayText(sciREG1, (uint8_t*)itoaBuffer, lenPrintSample);
}

#define CREATE_APPLICATION (0)

void
HelloWorldSubscriber_on_data_available(void *listener_data,
                                       DDS_DataReader * reader)
{
    HelloWorldDataReader *hw_reader = HelloWorldDataReader_narrow(reader);
    DDS_ReturnCode_t retcode;
    struct DDS_SampleInfo *sample_info = NULL;
    HelloWorld *sample = NULL;

    struct DDS_SampleInfoSeq info_seq = 
        DDS_SEQUENCE_INITIALIZER;
    struct HelloWorldSeq sample_seq = 
        DDS_SEQUENCE_INITIALIZER;

    const DDS_Long TAKE_MAX_SAMPLES = 32;
    DDS_Long i;

    retcode = HelloWorldDataReader_take(hw_reader, 
       &sample_seq, &info_seq, TAKE_MAX_SAMPLES, 
       DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);

    if (retcode != DDS_RETCODE_OK)
    {
        printf("failed to take data, retcode(%d)\n", retcode);
        goto done;
    }

    /* Print each valid sample taken */
    for (i = 0; i < HelloWorldSeq_get_length(&sample_seq); ++i)
    {
        sample_info = DDS_SampleInfoSeq_get_reference(&info_seq, i);

        if (sample_info->valid_data)
        {
            sample = HelloWorldSeq_get_reference(&sample_seq, i);
            //printf("\nSample received\n\tmsg: %d\n", sample->data1);
            printSample(sample);
        }
        else
        {
            printf("\nSample received\n\tINVALID DATA\n");
        }
    }

    HelloWorldDataReader_return_loan(hw_reader, &sample_seq, &info_seq);

done:
    HelloWorldSeq_finalize(&sample_seq);
    DDS_SampleInfoSeq_finalize(&info_seq);
}

void
HelloWorldSubscriber_on_subscription_matched(void *listener_data,
                                             DDS_DataReader * reader,
                                             const struct
                                             DDS_SubscriptionMatchedStatus
                                             *status)
{
    if (status->current_count_change > 0)
    {
        printf("Matched a publisher\n");
    }
    else if (status->current_count_change < 0)
    {
        printf("Unmatched a publisher\n");
    }
}


#ifdef HW_USE_SAMPLE_FILTER
void 
HelloWorldSubscriber_filter_sample(HelloWorld *sample,
                                   DDS_Boolean *drop_sample)
{
    /* Example filter: drop samples with even-numbered count in msg */

    int dec_radix = 1;
    int digit = 0;
    int count = 0;
    char *str_idx = strchr(sample->data1, ')');

    if (str_idx == NULL)
    {
        return;
    }

    --str_idx;
    do 
    {
        digit = *(str_idx) - '0';
        count += digit * dec_radix;
        dec_radix *= 10;
        --str_idx;
    } while (*str_idx != '(');

    *drop_sample = (count % 2 == 0) ? DDS_BOOLEAN_TRUE : DDS_BOOLEAN_FALSE;
}

DDS_Boolean
HelloWorldSubscriber_on_before_sample_deserialize(
        void *listener_data,
        DDS_DataReader *reader,
        struct NDDS_Type_Plugin *plugin,
        struct CDR_Stream_t *stream,
        DDS_Boolean *dropped)
{
    DDS_Boolean result = DDS_BOOLEAN_FALSE;
    HelloWorld *sample = NULL;

    sample = HelloWorld_create();
    if (sample == NULL)
    {
        printf("failed HelloWorld create\n");
        return DDS_BOOLEAN_FALSE;
    }

    /* CDR encapsulation header */
    if (!CDR_Stream_deserialize_header(stream))
    {
        printf("failed deserialize header\n");
        goto done;
    }

    /* user data */
    if (!plugin->deserialize_data(stream, sample, NULL))
    {
        printf("failed deserialize data\n");
        goto done;
    }

    /* filter the sample */
    HelloWorldSubscriber_filter_sample(sample, dropped);

    if (*dropped)
    {
        printf("\nSample filtered, before deserialize\n\tDROPPED - msg: %d\n",
               sample->data1);
    }

    result = DDS_BOOLEAN_TRUE;
done:
    if (sample != NULL)
    {
        HelloWorld_delete(sample);
    }
    return result;
}


DDS_Boolean
HelloWorldSubscriber_on_before_sample_commit(
        void *listener_data,
        DDS_DataReader *reader,
        const void *const sample,
        const struct DDS_SampleInfo *const sample_info,
        DDS_Boolean *dropped)
{
    HelloWorld *hw_sample = (HelloWorld *)sample; 

    HelloWorldSubscriber_filter_sample(hw_sample, dropped);

    if (*dropped)
    {
        printf("\nSample filtered, before commit\n\tDROPPED - msg: %d\n",
               hw_sample->data1);
    }

    return DDS_BOOLEAN_TRUE;
}
#endif

#if CREATE_APPLICATION == 1
#else
extern struct Application *sharedApplication;
#endif

int
subscriber_main_w_args(DDS_Long domain_id, char *udp_intf, char *peer,
                       DDS_Long sleep_time, DDS_Long count)
{
    DDS_Subscriber *subscriber;
    DDS_DataReader *datareader;
    struct DDS_DataReaderQos dr_qos = DDS_DataReaderQos_INITIALIZER;
#if CREATE_APPLICATION == 1
    DDS_ReturnCode_t retcode;
#endif
    struct DDS_DataReaderListener dr_listener =
        DDS_DataReaderListener_INITIALIZER;
    struct Application *application;

#if CREATE_APPLICATION == 1
    application = Application_create("subscriber", "publisher", DDS_BOOLEAN_FALSE, domain_id,
                                     udp_intf, peer, sleep_time, count);

    if (application == NULL)
    {
        return 0;
    }
#else
    // wait for the publisher to create the application
    while (sharedApplication == NULL)
    {
        OSAPI_Thread_sleep(1000); /* sleep is in ms */
       }
    application = sharedApplication;
#endif

    subscriber =
        DDS_DomainParticipant_create_subscriber(application->participant,
                                                &DDS_SUBSCRIBER_QOS_DEFAULT,
                                                NULL, DDS_STATUS_MASK_NONE);
    if (subscriber == NULL)
    {
        printf("subscriber == NULL\n");
        goto done;
    }


/* Uncomment to filter samples with callbacks */
/* #define HW_USE_SAMPLE_FILTER */
#ifdef HW_USE_SAMPLE_FILTER
    /* choose one callback to enable */
#if 1
    dr_listener.on_before_sample_deserialize = 
        HelloWorldSubscriber_on_before_sample_deserialize;
#else
    dr_listener.on_before_sample_commit = 
        HelloWorldSubscriber_on_before_sample_commit;
#endif

#endif

    /* INTEROPERABILITY NOTE:
       Non-Connext Micro DDS writers and readers will have default LivelinessQoS
       kind set to DDS_AUTOMATIC_LIVELINESS_QOS.
     
       Because Connext Micro currently only supports
       DDS_MANUAL_BY_TOPIC_LIVELINESS_QOS for finite lease_duration,
       a non-Connext Micro writer must set its liveliness kind to
       DDS_MANUAL_BY_TOPIC_LIVELINESS_QOS as well in order for
       Requested-Offered (RxO) semantics to be compatible.
    */

    dr_listener.on_data_available = HelloWorldSubscriber_on_data_available;
    dr_listener.on_subscription_matched =
        HelloWorldSubscriber_on_subscription_matched;
    dr_qos.resource_limits.max_samples = 32;
    dr_qos.resource_limits.max_instances = 1;
    dr_qos.resource_limits.max_samples_per_instance = 32;
    /* if there are more remote writers, you need to increase these limits */
    dr_qos.reader_resource_limits.max_remote_writers = 10;
    dr_qos.reader_resource_limits.max_remote_writers_per_instance = 10;
    dr_qos.history.depth = 32;

    /* Reliability QoS */
#if 1
    dr_qos.reliability.kind = DDS_RELIABLE_RELIABILITY_QOS;
#else
    dr_qos.reliability.kind = DDS_BEST_EFFORT_RELIABILITY_QOS;
#endif

    datareader = DDS_Subscriber_create_datareader(subscriber,
                                                  DDS_Topic_as_topicdescription
                                                  (application->topic), &dr_qos,
                                                  &dr_listener,
                                                  DDS_DATA_AVAILABLE_STATUS |
                                                  DDS_SUBSCRIPTION_MATCHED_STATUS);

    if (datareader == NULL)
    {
        printf("datareader == NULL\n");
        goto done;
    }

#if CREATE_APPLICATION == 1
    retcode = Application_enable(application);
    if (retcode != DDS_RETCODE_OK)
    {
        printf("failed to enable application\n");
        goto done;
    }
#endif

    if (application->count != 0)
    {
        //printf("Running for %d seconds, press Ctrl-C to exit\n", application->count);
        OSAPI_Thread_sleep(application->count * 1000);
    }
    else
    {
        int sleep_loop_count =  (24 * 60 * 60);

        //printf("Running for 24 hours, press Ctrl-C to exit\n");

        while (sleep_loop_count)
        {
            OSAPI_Thread_sleep(1000); /* sleep is in ms */
            --sleep_loop_count;
        }
    }

    done:

#if CREATE_APPLICATION == 1
    Application_delete(application);
#endif

    DDS_DataReaderQos_finalize(&dr_qos);

    return 0;
}

#if !(defined(RTI_VXWORKS) && !defined(__RTP__))
int
subscriber_main(int argc, char **argv)
{
    DDS_Long i = 0;
    DDS_Long domain_id = 0;
    char *peer = NULL;
    char *udp_intf = NULL;
    DDS_Long sleep_time = 1000;
    DDS_Long count = 0;

    for (i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "-domain"))
        {
            ++i;
            if (i == argc)
            {
                printf("-domain <domain_id>\n");
                return -1;
            }
            domain_id = strtol(argv[i], NULL, 0);
        }
        else if (!strcmp(argv[i], "-udp_intf"))
        {
            ++i;
            if (i == argc)
            {
                printf("-udp_intf <interface>\n");
                return -1;
            }
            udp_intf = argv[i];
        }
        else if (!strcmp(argv[i], "-peer"))
        {
            ++i;
            if (i == argc)
            {
                printf("-peer <address>\n");
                return -1;
            }
            peer = argv[i];
        }
        else if (!strcmp(argv[i], "-sleep"))
        {
            ++i;
            if (i == argc)
            {
                printf("-sleep_time <sleep_time>\n");
                return -1;
            }
            sleep_time = strtol(argv[i], NULL, 0);
        }
        else if (!strcmp(argv[i], "-count"))
        {
            ++i;
            if (i == argc)
            {
                printf("-count <count>\n");
                return -1;
            }
            count = strtol(argv[i], NULL, 0);
        }
        else if (!strcmp(argv[i], "-h"))
        {
            Application_help(argv[0]);
            return 0;
        }
        else
        {
            printf("unknown option: %s\n", argv[i]);
            return -1;
        }
    }

    return subscriber_main_w_args(domain_id, udp_intf, peer, sleep_time, count);
}

void subscriber_main_task(void *args)
{
    subscriber_main(0, NULL);
}

#elif defined(RTI_VXWORKS)
int
subscriber_main(void)
{
    /* Explicitly configure args below */
    DDS_Long domain_id = 44;
    char *peer = "10.10.65.103";
    char *udp_intf = NULL;
    DDS_Long sleep_time = 1000;
    DDS_Long count = 0;

    return subscriber_main_w_args(domain_id, udp_intf, peer, sleep_time, count);
}
#endif
