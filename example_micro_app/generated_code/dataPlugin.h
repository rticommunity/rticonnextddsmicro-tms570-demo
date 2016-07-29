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

#ifndef dataPlugin_1787923088_h
#define dataPlugin_1787923088_h

#include "data.h"

#ifdef NDDS_USER_DLL_EXPORT
#if (defined(RTI_WIN32) || defined(RTI_WINCE))
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif
#else
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

NDDSUSERDllExport extern struct NDDS_Type_Plugin*
HelloWorldTypePlugin_get(void);
NDDSUSERDllExport extern const char*
HelloWorldTypePlugin_get_default_type_name(void);
NDDSUSERDllExport extern NDDS_TypePluginKeyKind 
HelloWorld_get_key_kind(
    struct NDDS_Type_Plugin *plugin,
    void *param);
/* --------------------------------------------------------------------------
Untyped interfaces to the typed sample management functions
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL
HelloWorldPlugin_create_sample(
    struct NDDS_Type_Plugin *plugin, void **sample,void *param);

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL 
HelloWorldPlugin_delete_sample(
    struct NDDS_Type_Plugin *plugin, void *sample,void *param);
#endif

NDDSUSERDllExport extern RTI_BOOL 
HelloWorldPlugin_copy_sample(
    struct NDDS_Type_Plugin *plugin, void *dst, const void *src, void *param);

/* --------------------------------------------------------------------------
(De)Serialize functions:
* -------------------------------------------------------------------------- */
NDDSUSERDllExport extern RTI_BOOL 
HelloWorld_cdr_serialize(
    struct CDR_Stream_t *stream, const void *void_sample, void *param);

NDDSUSERDllExport extern RTI_BOOL 
HelloWorld_cdr_deserialize(
    struct CDR_Stream_t *stream, void *void_sample, void *param);

NDDSUSERDllExport extern RTI_UINT32
HelloWorld_get_serialized_sample_max_size(
    struct NDDS_Type_Plugin *plugin,
    RTI_UINT32 current_alignment,
    void *param);
/* Unkeyed type key serialization equivalent to sample serialization */
#define HelloWorld_cdr_serialize_key HelloWorld_cdr_serialize
#define HelloWorld_cdr_deserialize_key HelloWorld_cdr_deserialize
#define HelloWorld_get_serialized_key_max_size HelloWorld_get_serialized_sample_max_size

#ifdef NDDS_USER_DLL_EXPORT
#if (defined(RTI_WIN32) || defined(RTI_WINCE))
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
#endif

#endif /* dataPlugin_1787923088_h */

