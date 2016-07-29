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

#ifndef dataSupport_1787923088_h
#define dataSupport_1787923088_h

#include <stdlib.h>

/* Uses */
#include "data.h"
/* Requires */
#include "dataPlugin.h"

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

/* ========================================================================== */
/**
Uses:     T
Defines:  TTypeSupport, TDataWriter, TDataReader*/

NDDSUSERDllExport extern DDS_ReturnCode_t
HelloWorldTypeSupport_register_type(
    DDS_DomainParticipant* participant,
    const char* type_name);

#ifndef RTI_CERT
NDDSUSERDllExport extern DDS_ReturnCode_t
HelloWorldTypeSupport_unregister_type(
    DDS_DomainParticipant* participant,
    const char* type_name);
#endif

NDDSUSERDllExport extern const char*
HelloWorldTypeSupport_get_type_name();

NDDSUSERDllExport extern HelloWorld *
HelloWorldTypeSupport_create_data();

NDDSUSERDllExport extern void
HelloWorldTypeSupport_delete_data(
    HelloWorld *data);

DDS_DATAWRITER_C(HelloWorldDataWriter, HelloWorld);

DDS_DATAREADER_C(HelloWorldDataReader, HelloWorldSeq, HelloWorld);

#ifdef NDDS_USER_DLL_EXPORT
#if (defined(RTI_WIN32) || defined(RTI_WINCE))
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
#endif

#endif  /* dataSupport_1787923088_h */

