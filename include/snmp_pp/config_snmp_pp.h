/*_############################################################################
  _## 
  _##  config_snmp_pp.h.in  
  _##
  _##  SNMP++ v3.3
  _##  -----------------------------------------------
  _##  Copyright (c) 2001-2013 Jochen Katz, Frank Fock
  _##
  _##  This software is based on SNMP++2.6 from Hewlett Packard:
  _##  
  _##    Copyright (c) 1996
  _##    Hewlett-Packard Company
  _##  
  _##  ATTENTION: USE OF THIS SOFTWARE IS SUBJECT TO THE FOLLOWING TERMS.
  _##  Permission to use, copy, modify, distribute and/or sell this software 
  _##  and/or its documentation is hereby granted without fee. User agrees 
  _##  to display the above copyright notice and this license notice in all 
  _##  copies of the software and any documentation of the software. User 
  _##  agrees to assume all liability for the use of the software; 
  _##  Hewlett-Packard and Jochen Katz make no representations about the 
  _##  suitability of this software for any purpose. It is provided 
  _##  "AS-IS" without warranty of any kind, either express or implied. User 
  _##  hereby grants a royalty-free license to any and all derivatives based
  _##  upon this software code base. 
  _##  
  _##########################################################################*/

#ifndef _CONFIG_SNMP_PP_H_
#define _CONFIG_SNMP_PP_H_

//! The maximum size of a message that can be sent or received.
#define MAX_SNMP_PACKET 4096

// define _NO_LOGGING if you do not want any logging output 
// (increases performance drastically and minimizes memory consumption)
#if 0
#undef _NO_LOGGING
#else
#define _NO_LOGGING
#endif

#if 0
#ifndef WITHOUT_LOG_PROFILES
#define WITH_LOG_PROFILES 1
#endif
#else
#undef WITH_LOG_PROFILES
#endif

// define this if you want to send out broadcasts
#define SNMP_BROADCAST

// Some socket types
typedef socklen_t SocketLengthType;

typedef struct sockaddr_storage SocketAddrType;

// Define a unsigned 64 bit integer:
typedef unsigned long long pp_uint64;
typedef long long pp_int64;

// Define a type used for sockets
typedef int SnmpSocket;

#define SNMP_PP_DEFAULT_SNMP_PORT      161 // standard port # for SNMP
#define SNMP_PP_DEFAULT_SNMP_TRAP_PORT 162 // standard port # for SNMP traps

///////////////////////////////////////////////////////////////////////
// Changes below this line should not be necessary
///////////////////////////////////////////////////////////////////////

#define SAFE_INT_CAST(expr)  ((int)(expr))
#define SAFE_UINT_CAST(expr) ((unsigned int)(expr))

// Safe until 32 bit second counter wraps to zero (time functions)
#define SAFE_LONG_CAST(expr)  ((long)(expr))
#define SAFE_ULONG_CAST(expr) ((unsigned long)(expr))

#include <pthread.h>


#endif // _CONFIG_SNMP_PP_H_
