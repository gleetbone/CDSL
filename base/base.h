/**
 @file base.h
 @author Greg Lee
 @version 2.0.0
 @brief: "include file for basic primitive typedefs"

 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee

 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0):

 1. Permission is hereby granted to use, copy, modify and/or
    distribute this package, provided that:
       * copyright notices are retained unchanged,
       * any distribution of this package, whether modified or not,
         includes this license text.
 2. Permission is hereby also granted to distribute binary programs
    which depend on this package. If the binary program depends on a
    modified version of this package, you are encouraged to publicly
    release the modified version of this package.

 THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT WARRANTY. ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE AUTHORS BE LIABLE TO ANY PARTY FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES ARISING IN ANY WAY OUT OF THE USE OF THIS PACKAGE.

 @section Description

 Defines for basic types.

*/

#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/**
   Function prototypes
*/

void core_dump_enable();

// typedefs for basic types
#include <stdint.h>
#include <complex.h>

#include "cdsl_types.h"

typedef char char_t;

typedef float float32_t;
typedef double float64_t;

typedef complex float complex64_t;
typedef complex double complex128_t;

// type codes for basic types
#define  char_type_code       0x00000040
#define  int8_type_code       0x00000001
#define  int16_type_code      0x00000002
#define  int32_type_code      0x00000003
#define  int64_type_code      0x00000004
#define  uint8_type_code      0x00000011
#define  octet_type_code      0x00000019
#define  uint16_type_code     0x00000012
#define  uint32_type_code     0x00000013
#define  uint64_type_code     0x00000014
#define  float32_type_code    0x00000023
#define  float64_type_code    0x00000024
#define  complex64_type_code  0x00000034
#define  complex128_type_code 0x00000035

#define  void_ptr_type_code         0x00000080
#define  char_ptr_type_code         0x000000C0
#define  int8_ptr_type_code         0x00000081
#define  int16_ptr_type_code        0x00000082
#define  int32_ptr_type_code        0x00000083
#define  int64_ptr_type_code        0x00000084
#define  uint8_ptr_type_code        0x00000091
#define  octet_ptr_type_code        0x00000099
#define  uint16_ptr_type_code       0x00000092
#define  uint32_ptr_type_code       0x00000093
#define  uint64_ptr_type_code       0x00000094
#define  float32_ptr_type_code      0x000000A3
#define  float64_ptr_type_code      0x000000A4
#define  complex64_ptr_type_code    0x000000B4
#define  complex128_ptr_type_code   0x000000B5

#include "cdsl_types.h"

/**
   Design by contract defaults
   Override these by defining FILE versions for each file
*/

#define PRE_GLOBAL DBC_YES
#define POST_GLOBAL DBC_YES
#define INVARIANT_GLOBAL DBC_YES
#define CHECK_GLOBAL DBC_YES
#define LOOP_VARIANT_FILE DBC_YES

/**
   Multithreading macros
*/

// default value is for MULTITHREADING macro to be undefined
#define MULTITHREADED

// override by defining MULTITHREADED macro by file (#define MULTITHREADED)

// default (empty) multithreading macros
#define MULTITHREAD_INCLUDE <stdint.h>
#define MULTITHREAD_THREAD_DEFINITION( p )
#define MULTITHREAD_THREAD_CREATE( arg1, arg2, arg3, arg4 )
#define MULTITHREAD_THREAD_JOIN( arg )
#define MULTITHREAD_MUTEX_DEFINITION( p )
#define MULTITHREAD_MUTEX_INIT( p )
#define MULTITHREAD_MUTEX_DEFINITION_INIT( p )
#define MULTITHREAD_MUTEX_DESTROY( p )
#define MULTITHREAD_COND_TYPE
#define MULTITHREAD_COND_DEFINITION( p )
#define MULTITHREAD_COND_INIT( p )
#define MULTITHREAD_COND_DEFINITION_INIT( p )
#define MULTITHREAD_COND_DESTROY( p )
#define MULTITHREAD_COND_SIGNAL( p )
#define MULTITHREAD_COND_WAIT( p, q )
#define LOCK( p )
#define UNLOCK( p )

// define multithreading macros for linux
#ifdef __linux__

#ifdef MULTITHREADED

#undef MULTITHREAD_INCLUDE
#define MULTITHREAD_INCLUDE <pthread.h>

#undef MULTITHREAD_THREAD_DEFINITION
#define MULTITHREAD_THREAD_DEFINITION( p ) pthread_t p

#undef MULTITHREAD_THREAD_CREATE
#define MULTITHREAD_THREAD_CREATE( arg1, arg2, arg3, arg4 ) pthread_create( arg1, arg2, arg3, arg4 )

#undef MULTITHREAD_THREAD_JOIN
#define MULTITHREAD_THREAD_JOIN( arg1, arg2 ) pthread_join( arg1, arg2 )

#undef MULTITHREAD_MUTEX_DEFINITION
#define MULTITHREAD_MUTEX_DEFINITION( p ) pthread_mutex_t p

#undef MULTITHREAD_MUTEX_DEFINITION_INIT
#define MULTITHREAD_MUTEX_DEFINITION_INIT( p ) pthread_mutex_t p = PTHREAD_MUTEX_INITIALIZER

#undef MULTITHREAD_MUTEX_INIT
#define MULTITHREAD_MUTEX_INIT( p ) pthread_mutex_init( &(p), NULL )

#undef MULTITHREAD_MUTEX_DESTROY
#define MULTITHREAD_MUTEX_DESTROY( p ) pthread_mutex_destroy( &(p) )

#undef MULTITHREAD_COND_TYPE
#define MULTITHREAD_COND_TYPE pthread_cond_t

#undef MULTITHREAD_COND_DEFINITION
#define MULTITHREAD_COND_DEFINITION( p ) pthread_cond_t p

#undef MULTITHREAD_COND_DEFINITION_INIT
#define MULTITHREAD_COND_DEFINITION_INIT( p ) pthread_cond_t p = PTHREAD_COND_INITIALIZER

#undef MULTITHREAD_COND_INIT
#define MULTITHREAD_COND_INIT( p ) pthread_cond_init( &(p), NULL )

#undef MULTITHREAD_COND_DESTROY
#define MULTITHREAD_COND_DESTROY( p ) pthread_cond_destroy( &(p) )

#undef MULTITHREAD_COND_SIGNAL_FUNCTION
#define MULTITHREAD_COND_SIGNAL_FUNCTION pthread_cond_signal

#undef MULTITHREAD_COND_SIGNAL
#define MULTITHREAD_COND_SIGNAL( p ) pthread_cond_signal( &(p) )

#undef MULTITHREAD_COND_WAIT
#define MULTITHREAD_COND_WAIT( p, q ) pthread_cond_wait( &(p), &(q) )

#undef LOCK
#define LOCK( p ) pthread_mutex_lock( &(p) )

#undef UNLOCK
#define UNLOCK( p ) pthread_mutex_unlock( &(p) )

#endif // MULTITHREADED

#endif // __linux__


/**
   Garbage collection macros
*/

// comment out the following lines to disable garbage collection
#ifndef GC_ENABLED
#define GC_ENABLED 1
#endif

// comment out the following lines to disable garbage collection debug stuff
#ifndef GC_DEBUG
// #define GC_DEBUG 1
#endif

// define garbage collection related stuff
#ifndef GC_ENABLED
#ifdef GC_ENABLED
#endif

// define GC_THREADS
#ifndef GC_THREADS
# define GC_THREADS
#endif

// define GC_PTHREADS
#ifndef GC_PTHREADS
# define GC_PTHREADS
#endif

// include garbage collection related files
#include <gc.h>
#include <stdlib.h>
#include <pthread.h>

// rename basic memory allocation routines to call appropriate
// garbage collection routines
#ifdef GC_DEBUG

#define malloc(n) GC_MALLOC( (n) )
#define calloc(m,n) GC_MALLOC( (m)*(n) )
#define realloc(p,n) GC_REALLOC( (p), (n) )
#define free( p ) GC_FREE( (p) )

#else /* GC_DEBUG undefined */

#define malloc(n) GC_malloc( (n) )
#define calloc(m,n) GC_malloc( (m)*(n) )
#define realloc(p,n) GC_realloc( (p), (n) )
#define free( p ) GC_free( (p) )

#endif /* GC_DEBUG */

#else /* GC_ENABLED */

// define basic GC calls as empty strings
#define GC_INIT()
#define GC_set_find_leak( arg )

#endif /* GC_ENABLED */

#ifdef __cplusplus
}
#endif

#endif /* BASIC_TYPES_H */

/* End of file */
