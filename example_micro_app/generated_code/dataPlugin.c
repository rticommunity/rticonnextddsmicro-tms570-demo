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

#include "data.h"
#include "dataPlugin.h"

/*** SOURCE_BEGIN ***/
#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
RTI_BOOL 
HelloWorld_cdr_serialize(
    struct CDR_Stream_t *stream, const void *void_sample, void *param)
{
    HelloWorld *sample = (HelloWorld *)void_sample;

    if ((stream == NULL) || (void_sample == NULL))
    {
        return RTI_FALSE;
    }

    UNUSED_ARG(param);

    if (!CDR_Stream_serialize_long(
        stream, &sample->data1)) {
        return RTI_FALSE;
    }  

    return RTI_TRUE;
}

RTI_BOOL 
HelloWorld_cdr_deserialize(
    struct CDR_Stream_t *stream, void *void_sample, void *param)
{
    HelloWorld *sample = (HelloWorld *)void_sample;

    if ((stream == NULL) || (void_sample == NULL))
    {
        return RTI_FALSE;
    }

    UNUSED_ARG(param);

    if (!CDR_Stream_deserialize_long(
        stream, &sample->data1)) {
        return RTI_FALSE;
    }  

    return RTI_TRUE;

}

RTI_UINT32
HelloWorld_get_serialized_sample_max_size(
    struct NDDS_Type_Plugin *plugin,
    RTI_UINT32 current_alignment,
    void *param)
{
    RTI_UINT32 initial_alignment = current_alignment;

    UNUSED_ARG(plugin);
    UNUSED_ARG(param);
    current_alignment += CDR_get_max_size_serialized_long(
        current_alignment);

    return  current_alignment - initial_alignment;
}

/* --------------------------------------------------------------------------
*  Sample Support functions:
* -------------------------------------------------------------------------- */
RTI_BOOL
HelloWorldPlugin_create_sample(
    struct NDDS_Type_Plugin *plugin, void **sample, void *param)
{
    UNUSED_ARG(plugin);
    UNUSED_ARG(param);
    *sample = (void *) HelloWorld_create();
    return (sample != NULL);
}

#ifndef RTI_CERT
RTI_BOOL
HelloWorldPlugin_delete_sample(
    struct NDDS_Type_Plugin *plugin, void *sample, void *param)
{
    UNUSED_ARG(plugin);
    UNUSED_ARG(param);
    /* HelloWorld_delete() is a void function
    which expects (sample != NULL). Since HelloWorldPlugin_delete_sample
    is an internal function, sample is assumed to be a valid pointer */ 
    HelloWorld_delete((HelloWorld *) sample);
    return RTI_TRUE;
}
#endif

RTI_BOOL 
HelloWorldPlugin_copy_sample(
    struct NDDS_Type_Plugin *plugin, void *dst, const void *src, void *param)
{
    UNUSED_ARG(plugin);
    UNUSED_ARG(param);
    return HelloWorld_copy(
        (HelloWorld *)dst,
        (const HelloWorld *)src);
}
/* --------------------------------------------------------------------------
*  Type HelloWorld Plugin Instantiation
* -------------------------------------------------------------------------- */

NDDSCDREncapsulation HelloWorldEncapsulationKind[] =
{ {0,0} };

struct NDDS_Type_Plugin HelloWorldTypePlugin =
{
    {0, 0},                     /* NDDS_Type_PluginVersion */
    NULL,                       /* DDS_TypeCode_t* */
    HelloWorldEncapsulationKind,
    NDDS_TYPEPLUGIN_NO_KEY,     /* NDDS_TypePluginKeyKind */
    HelloWorld_cdr_serialize,
    HelloWorld_cdr_deserialize,
    HelloWorld_get_serialized_sample_max_size,
    NULL, NULL, NULL,           /* key support functions*/
    HelloWorldPlugin_create_sample,
    #ifndef RTI_CERT
    HelloWorldPlugin_delete_sample,
    #else
    NULL,
    #endif
    HelloWorldPlugin_copy_sample,
    PluginHelper_get_key_kind,
    PluginHelper_instance_to_keyhash,
    NULL, NULL, NULL, NULL  /* endpoint wrappers not used in C */
};

/* --------------------------------------------------------------------------
*  Type HelloWorld Plugin Methods
* -------------------------------------------------------------------------- */

struct NDDS_Type_Plugin *
HelloWorldTypePlugin_get(void) 
{ 
    return &HelloWorldTypePlugin;
} 

const char*
HelloWorldTypePlugin_get_default_type_name(void) 
{ 
    return HelloWorldTYPENAME;
} 

NDDS_TypePluginKeyKind 
HelloWorld_get_key_kind(
    struct NDDS_Type_Plugin *plugin,
    void *param)
{
    UNUSED_ARG(param);
    UNUSED_ARG(plugin);
    return NDDS_TYPEPLUGIN_NO_KEY;
}

