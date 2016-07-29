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

#ifndef Application_h
#define Application_h

#include "rti_me_c.h"

struct Application {
    DDS_DomainParticipant *participant;
    char topic_name[255];
    char type_name[255];
    DDS_Long sleep_time;
    DDS_Long count;
    DDS_Topic *topic;
};

extern void 
Application_help(char *appname);

extern struct Application*
Application_create(const char *local_participant_name,
                  const char *remote_participant_name,
                  DDS_Boolean publisher,
                  DDS_Long domain_id, char *udp_intf, char *peer,
                  DDS_Long sleep_time, DDS_Long count);

extern DDS_ReturnCode_t
Application_enable(struct Application *application);

extern void
Application_delete(struct Application *application);

#endif
