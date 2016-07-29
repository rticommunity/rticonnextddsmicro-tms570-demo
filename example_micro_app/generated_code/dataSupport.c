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

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from data.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "dataSupport.h"

/*** SOURCE_BEGIN ***/
/* =========================================================================== */

/* Requires */
#define TTYPENAME   HelloWorldTYPENAME

/* 
HelloWorldDataWriter (DDS_DataWriter)   
*/

/* Defines */
#define TDataWriter HelloWorldDataWriter
#define TData       HelloWorld

#include "dds_c/dds_c_tdatawriter_gen.h"

#undef TDataWriter
#undef TData

/* =========================================================================== */
/* 
HelloWorldDataReader (DDS_DataReader)   
*/

/* Defines */
#define TDataReader HelloWorldDataReader
#define TDataSeq    HelloWorldSeq
#define TData       HelloWorld
#include "dds_c/dds_c_tdatareader_gen.h"
#undef TDataReader
#undef TDataSeq
#undef TData

DDS_ReturnCode_t
HelloWorldTypeSupport_register_type(
    DDS_DomainParticipant* participant,
    const char* type_name)
{
    DDS_ReturnCode_t retcode = DDS_RETCODE_ERROR;

    if (participant == NULL) 
    {
        goto done;
    }

    if (type_name == NULL) 
    {
        type_name = HelloWorldTypePlugin_get_default_type_name();
        if (type_name == NULL)
        {
            goto done;
        }
    }

    retcode = DDS_DomainParticipant_register_type(
        participant,
        type_name,
        HelloWorldTypePlugin_get());

    if (retcode != DDS_RETCODE_OK)
    {
        goto done;
    }

    retcode = DDS_RETCODE_OK;

    done:

    return retcode;
}

#ifndef RTI_CERT
DDS_ReturnCode_t
HelloWorldTypeSupport_unregister_type(
    DDS_DomainParticipant* participant,
    const char* type_name)
{
    DDS_ReturnCode_t retcode = DDS_RETCODE_ERROR;

    if (participant == NULL) 
    {
        goto done;
    }

    if (type_name == NULL) 
    {
        type_name = HelloWorldTypePlugin_get_default_type_name();
        if (type_name == NULL)
        {
            goto done;
        }
    }

    if (HelloWorldTypePlugin_get() !=
    DDS_DomainParticipant_unregister_type(participant,type_name))
    {
        goto done;
    }

    retcode = DDS_RETCODE_OK;

    done:

    return retcode;
}
#endif
const char*
HelloWorldTypeSupport_get_type_name()
{
    return HelloWorldTYPENAME;
}
HelloWorld *
HelloWorldTypeSupport_create_data()
{
    HelloWorld *data = NULL;

    data = HelloWorld_create();

    return data;
}

void
HelloWorldTypeSupport_delete_data(
    HelloWorld *data)
{
    HelloWorld_delete(data);
}

#undef TTYPENAME

