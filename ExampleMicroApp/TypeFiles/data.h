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

#ifndef data_1787923088_h
#define data_1787923088_h

#ifndef rti_me_c_h
#include "rti_me_c.h"
#endif

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

typedef struct HelloWorld

{

    CDR_Long data1;

} HelloWorld ;

extern const char *HelloWorldTYPENAME;

#define REDA_SEQUENCE_USER_API
#define T HelloWorld
#define TSeq HelloWorldSeq
#define REDA_SEQUENCE_EXCLUDE_C_METHODS
#include <reda/reda_sequence_decl.h>

#define REDA_SEQUENCE_USER_API
#define T HelloWorld
#define TSeq HelloWorldSeq
#define REDA_SEQUENCE_EXCLUDE_STRUCT
#include <reda/reda_sequence_decl.h>

NDDSUSERDllExport extern RTI_BOOL
HelloWorld_initialize(HelloWorld* sample);

NDDSUSERDllExport extern HelloWorld*
HelloWorld_create();

#ifndef RTI_CERT
NDDSUSERDllExport extern RTI_BOOL
HelloWorld_finalize(HelloWorld* sample);

NDDSUSERDllExport extern void
HelloWorld_delete(HelloWorld* sample);
#endif

NDDSUSERDllExport extern RTI_BOOL
HelloWorld_copy(HelloWorld* dst, const HelloWorld* src);

#ifdef NDDS_USER_DLL_EXPORT
#if (defined(RTI_WIN32) || defined(RTI_WINCE))
/* If the code is building on Windows, stop exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif
#endif

#endif /* data */

