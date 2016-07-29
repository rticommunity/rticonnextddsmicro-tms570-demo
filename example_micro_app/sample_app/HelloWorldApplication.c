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
#include "disc_dpde/disc_dpde_discovery_plugin.h"
#include "HelloWorldApplication.h"
#include "dataPlugin.h"
#include "wh_sm/wh_sm_history.h"
#include "rh_sm/rh_sm_history.h"
#include "netio/netio_udp.h"

#include "HL_sci.h"

extern void sciDisplayText(sciBASE_t *sci, uint8_t *text, uint32_t length);
#define sciREGx    sciREG1

#define printf(s, ...) sciDisplayText(sciREG1, s, sizeof(s))

void
Application_help(char *appname)
{
    printf("%s [options]\n", appname);
    printf("options:\n");
    printf("-h                 - This text\n");
    printf("-domain <id>       - DomainId (default: 0)\n");
    printf("-udp_intf <intf>   - udp interface (no default)\n");
    printf("-peer <address>    - peer address (no default)\n");
    printf("-count <count>     - count (default -1)\n");
    printf("-sleep <ms>        - sleep between sends (default 1s)\n");
    printf("\n");
}

// TODO : We will need to of following variables, one for subscriber and another one for publisher.
static struct Application                  appStaticSubscriber;
//static struct UDP_InterfaceFactoryProperty intFactPropStaticSubscriber;

static struct Application                  appStaticPublisher;
//static struct UDP_InterfaceFactoryProperty intFactPropStaticPublisher;

struct Application *
Application_create(const char *local_participant_name,
                   const char *remote_participant_name,
                   DDS_Boolean publisher,
                   DDS_Long domain_id, char *udp_intf, char *peer,
                   DDS_Long sleep_time, DDS_Long count)
{
    DDS_ReturnCode_t retcode;
    DDS_DomainParticipantFactory *factory = NULL;
    struct DDS_DomainParticipantFactoryQos dpf_qos =
        DDS_DomainParticipantFactoryQos_INITIALIZER;
    struct DDS_DomainParticipantQos dp_qos =
        DDS_DomainParticipantQos_INITIALIZER;
    DDS_Boolean success = DDS_BOOLEAN_FALSE;
    struct Application *application = NULL;
    RT_Registry_T *registry = NULL;
    struct UDP_InterfaceFactoryProperty *udp_property = NULL;

    struct DPDE_DiscoveryPluginProperty discovery_plugin_properties =
        DPDE_DiscoveryPluginProperty_INITIALIZER;


    /* Uncomment to increase verbosity level: 
       OSAPILog_set_verbosity(OSAPI_LOG_VERBOSITY_WARNING);
     */
    //application = (struct Application *)malloc(sizeof(struct Application));
    if (publisher == DDS_BOOLEAN_TRUE)
        application = &appStaticPublisher;
    else
        application = &appStaticSubscriber;

    if (application == NULL)
    {
        printf("failed to allocate application\n");
        goto done;
    }

    application->sleep_time = sleep_time;
    application->count = count;

    factory = DDS_DomainParticipantFactory_get_instance();

    registry =
        DDS_DomainParticipantFactory_get_registry
        (DDS_DomainParticipantFactory_get_instance());

    if (!RT_Registry_register(registry, DDSHST_WRITER_DEFAULT_HISTORY_NAME,
                              WHSM_HistoryFactory_get_interface(), NULL, NULL))
    {
        printf("failed to register wh\n");
        goto done;
    }

    if (!RT_Registry_register(registry, DDSHST_READER_DEFAULT_HISTORY_NAME,
                              RHSM_HistoryFactory_get_interface(), NULL, NULL))
    {
        printf("failed to register rh\n");
        goto done;
    }

    /* Configure UDP transport's allowed interfaces */
    /*
    if (!RT_Registry_unregister(registry, NETIO_DEFAULT_UDP_NAME, NULL, NULL))
    {
        printf("failed to unregister udp\n");
        goto done;
    }
    */

    /*udp_property = (struct UDP_InterfaceFactoryProperty *)
        malloc(sizeof(struct UDP_InterfaceFactoryProperty));*/
    /*
    if (publisher == DDS_BOOLEAN_TRUE)
        udp_property = &intFactPropStaticPublisher;
    else
        udp_property = &intFactPropStaticSubscriber;
    *udp_property = UDP_INTERFACE_FACTORY_PROPERTY_DEFAULT;
    */

    /* For additional allowed interface(s), increase maximum and length, and
       set interface below:
    */
    /*
    REDA_StringSeq_set_maximum(&udp_property->allow_interface,1);
    REDA_StringSeq_set_length(&udp_property->allow_interface,1);
    */
    /* loopback interface */
    /*
#if defined(RTI_DARWIN)
    *REDA_StringSeq_get_reference(&udp_property->allow_interface,0) = "lo0";
#elif defined (RTI_LINUX)
    *REDA_StringSeq_get_reference(&udp_property->allow_interface,0) = "lo";
#elif defined (RTI_VXWORKS)
    *REDA_StringSeq_get_reference(&udp_property->allow_interface,0) = "lo0";
#elif defined(RTI_WIN32)
    *REDA_StringSeq_get_reference(&udp_property->allow_interface,0) = "Loopback Pseudo-Interface 1";
#else
    *REDA_StringSeq_get_reference(&udp_property->allow_interface,0) = "lo";
#endif
    */
    /*
    if (udp_intf != NULL) { // use interface supplied on command line
        *REDA_StringSeq_get_reference(&udp_property->allow_interface,1) = 
            DDS_String_dup(udp_intf);
    } else {                // use hardcoded interface
#if defined(RTI_DARWIN)
        *REDA_StringSeq_get_reference(&udp_property->allow_interface,1) = "en1";
#elif defined (RTI_LINUX)
        *REDA_StringSeq_get_reference(&udp_property->allow_interface,1) = "eth0";
#elif defined (RTI_VXWORKS)
        *REDA_StringSeq_get_reference(&udp_property->allow_interface,1) = "geisc0";
#elif defined(RTI_WIN32)
        *REDA_StringSeq_get_reference(&udp_property->allow_interface,1) = "Local Area Connection";
#else
        //*REDA_StringSeq_get_reference(&udp_property->allow_interface,1) = "ce0";
#endif
    }
    */
    /*
    if (!RT_Registry_register(registry, NETIO_DEFAULT_UDP_NAME,
                         UDP_InterfaceFactory_get_interface(),
                        (struct RT_ComponentFactoryProperty*)udp_property, NULL))
    {
       printf("failed to register udp\n");
       goto done;
    }
    */

    DDS_DomainParticipantFactory_get_qos(factory, &dpf_qos);
    dpf_qos.entity_factory.autoenable_created_entities = DDS_BOOLEAN_FALSE;
    DDS_DomainParticipantFactory_set_qos(factory, &dpf_qos);

    if (peer == NULL)
    {
        peer = "127.0.0.1"; /* default to loopback */
    }

    if (!RT_Registry_register(registry,
                              "dpde",
                              DPDE_DiscoveryFactory_get_interface(),
                              &discovery_plugin_properties._parent, 
                              NULL))
    {
        printf("failed to register dpde\n");
        goto done;
    }

    if (!RT_ComponentFactoryId_set_name(&dp_qos.discovery.discovery.name,"dpde"))
    {
        printf("failed to set discovery plugin name\n");
        goto done;
    }

    //FMT : BEGIN : enable only intra transport!!!

    REDA_StringSeq_set_maximum(&dp_qos.transports.enabled_transports,1);
    REDA_StringSeq_set_length(&dp_qos.transports.enabled_transports,1);
    *REDA_StringSeq_get_reference(&dp_qos.transports.enabled_transports,0) =
            DDS_String_dup(NETIO_DEFAULT_INTRA_NAME);

    /* Discovery enabled_transports */
    DDS_StringSeq_set_maximum(&dp_qos.discovery.enabled_transports, 1);
    DDS_StringSeq_set_length(&dp_qos.discovery.enabled_transports, 1);
    *DDS_StringSeq_get_reference(&dp_qos.discovery.enabled_transports, 0) =
         DDS_String_dup(NETIO_DEFAULT_INTRA_NAME);

    /* User Traffic enabled_transports */
    DDS_StringSeq_set_maximum(&dp_qos.user_traffic.enabled_transports, 1);
    DDS_StringSeq_set_length(&dp_qos.user_traffic.enabled_transports, 1);
    *DDS_StringSeq_get_reference(&dp_qos.user_traffic.enabled_transports, 0) =
         DDS_String_dup(NETIO_DEFAULT_INTRA_NAME);
    //FMT : END : enable only intra transport!!!

    DDS_StringSeq_set_maximum(&dp_qos.discovery.initial_peers,1);
    DDS_StringSeq_set_length(&dp_qos.discovery.initial_peers,1);
    *DDS_StringSeq_get_reference(&dp_qos.discovery.initial_peers,0) = DDS_String_dup(peer);

    /* if there are more remote or local endpoints, you need to increase these limits */
    dp_qos.resource_limits.max_destination_ports = 32;
    dp_qos.resource_limits.max_receive_ports = 32;
    dp_qos.resource_limits.local_topic_allocation = 1;
    dp_qos.resource_limits.local_type_allocation = 1;
    dp_qos.resource_limits.local_reader_allocation = 1;
    dp_qos.resource_limits.local_writer_allocation = 1;
    dp_qos.resource_limits.remote_participant_allocation = 8;
    dp_qos.resource_limits.remote_reader_allocation = 8;
    dp_qos.resource_limits.remote_writer_allocation = 8;

    application->participant =
        DDS_DomainParticipantFactory_create_participant(factory, domain_id,
                                                        &dp_qos, NULL,
                                                        DDS_STATUS_MASK_NONE);

    if (application->participant == NULL)
    {
        printf("failed to create participant\n");
        goto done;
    }

    sprintf(application->type_name, "HelloWorld");
    retcode = DDS_DomainParticipant_register_type(application->participant,
                                             application->type_name,
                                             HelloWorldTypePlugin_get());
    if (retcode != DDS_RETCODE_OK)
    {
        printf("failed to register type: %s\n", "test_type");
        goto done;
    }

    sprintf(application->topic_name, "Example HelloWorld");
    application->topic =
        DDS_DomainParticipant_create_topic(application->participant,
                                           application->topic_name,
                                           application->type_name,
                                           &DDS_TOPIC_QOS_DEFAULT, NULL,
                                           DDS_STATUS_MASK_NONE);

    if (application->topic == NULL)
    {
        printf("topic == NULL\n");
        goto done;
    }

    success = DDS_BOOLEAN_TRUE;

  done:
    if (!success)
    {
        if (udp_property != NULL)
        {
            //free(udp_property);
        }
        //free(application);
        application = NULL;
    }

    return application;
}

DDS_ReturnCode_t
Application_enable(struct Application * application)
{
    DDS_Entity *entity;
    DDS_ReturnCode_t retcode;

    entity = DDS_DomainParticipant_as_entity(application->participant);

    retcode = DDS_Entity_enable(entity);
    if (retcode != DDS_RETCODE_OK)
    {
        printf("failed to enable entity\n");
    }

    return retcode;
}

void
Application_delete(struct Application *application)
{
    DDS_ReturnCode_t retcode;
    RT_Registry_T *registry = NULL;

    retcode = DDS_DomainParticipant_delete_contained_entities(application->participant);
    if (retcode != DDS_RETCODE_OK)
    {
        printf("failed to delete conteined entities (retcode=%d)\n",retcode);
    }

    if (DDS_DomainParticipant_unregister_type(application->participant,
                                         application->type_name) !=
        HelloWorldTypePlugin_get())
    {
        printf("failed to unregister type: %s\n", application->type_name);
        return;
    }

    retcode =
        DDS_DomainParticipantFactory_delete_participant
        (DDS_DomainParticipantFactory_get_instance(), application->participant);
    if (retcode != DDS_RETCODE_OK)
    {
        printf("failed to delete participant: %d\n", retcode);
        return;
    }

    registry = DDS_DomainParticipantFactory_get_registry
        (DDS_DomainParticipantFactory_get_instance());

    if (!RT_Registry_unregister(registry, "dpde", NULL, NULL))
    {
        printf("failed to unregister dpde\n");
        return;
    }
    if (!RT_Registry_unregister(registry, DDSHST_READER_DEFAULT_HISTORY_NAME, NULL, NULL))
    {
        printf("failed to unregister rh\n");
        return;
    }
    if (!RT_Registry_unregister(registry, DDSHST_WRITER_DEFAULT_HISTORY_NAME, NULL, NULL))
    {
        printf("failed to unregister wh\n");
        return;
    }

    //free(application);

    DDS_DomainParticipantFactory_finalize_instance();
}
