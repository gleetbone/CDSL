/**
 @file dbc.h
 @author Greg Lee
 @version 2.0.0
 @brief: "defines design by contract macros"

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

 Defines DbC macros.

*/

#ifndef DBC_H
#define DBC_H

#include <assert.h>
#include <execinfo.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
   Function Prototypes
*/

void dbc_print_stacktrace();

/**
   DbC Constants
*/
   
#define DBC_NEUTRAL 8
#define DBC_NO 0
#define DBC_YES 1
#define DBC_OVERRIDE_NO 2
#define DBC_OVERRIDE_YES 3

/**
   Loop Variant
*/

#ifndef LOOP_VARIANT_GLOBAL
   #define LOOP_VARIANT_GLOBAL DBC_NEUTRAL
#endif

#ifndef LOOP_VARIANT_FILE
   #define LOOP_VARIANT_FILE DBC_NEUTRAL
#endif

#ifndef LOOP_VARIANT_FUNCTION
   #define LOOP_VARIANT_FUNCTION DBC_NEUTRAL
#endif

#define LOOP_VARIANT( m, x ) \
if ( ( (LOOP_VARIANT_FUNCTION == DBC_OVERRIDE_YES) ) \
     || \
     ( (LOOP_VARIANT_GLOBAL == DBC_NEUTRAL)      && (LOOP_VARIANT_FILE == DBC_NEUTRAL)      && (LOOP_VARIANT_FUNCTION == DBC_YES) ) \
     || \
     ( (LOOP_VARIANT_GLOBAL == DBC_NEUTRAL)      && (LOOP_VARIANT_FILE == DBC_YES)          && (LOOP_VARIANT_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (LOOP_VARIANT_GLOBAL == DBC_NEUTRAL)      && (LOOP_VARIANT_FILE == DBC_OVERRIDE_YES) && (LOOP_VARIANT_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (LOOP_VARIANT_GLOBAL == DBC_NO)           && (LOOP_VARIANT_FILE == DBC_OVERRIDE_YES) && (LOOP_VARIANT_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (LOOP_VARIANT_GLOBAL == DBC_YES)          && (LOOP_VARIANT_FILE != DBC_OVERRIDE_NO)  && (LOOP_VARIANT_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (LOOP_VARIANT_GLOBAL == DBC_OVERRIDE_YES) && (LOOP_VARIANT_FILE != DBC_OVERRIDE_NO)  && (LOOP_VARIANT_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (LOOP_VARIANT_GLOBAL == DBC_OVERRIDE_NO)  && (LOOP_VARIANT_FILE == DBC_OVERRIDE_YES) && (LOOP_VARIANT_FUNCTION != DBC_OVERRIDE_NO) ) \
   ) \
{ \
   assert(( ( void ) m, ( --x >= 0 ) )); \
}

// LOOP_VARIANT_VARIABLE_DEFINE

#if ( ( (LOOP_VARIANT_FUNCTION == DBC_OVERRIDE_YES) ) \
     || \
     ( (LOOP_VARIANT_GLOBAL == DBC_NEUTRAL)      && (LOOP_VARIANT_FILE == DBC_NEUTRAL)      && (LOOP_VARIANT_FUNCTION == DBC_YES) ) \
     || \
     ( (LOOP_VARIANT_GLOBAL == DBC_NEUTRAL)      && (LOOP_VARIANT_FILE == DBC_YES)          && (LOOP_VARIANT_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (LOOP_VARIANT_GLOBAL == DBC_NEUTRAL)      && (LOOP_VARIANT_FILE == DBC_OVERRIDE_YES) && (LOOP_VARIANT_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (LOOP_VARIANT_GLOBAL == DBC_NO)           && (LOOP_VARIANT_FILE == DBC_OVERRIDE_YES) && (LOOP_VARIANT_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (LOOP_VARIANT_GLOBAL == DBC_YES)          && (LOOP_VARIANT_FILE != DBC_OVERRIDE_NO)  && (LOOP_VARIANT_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (LOOP_VARIANT_GLOBAL == DBC_OVERRIDE_YES) && (LOOP_VARIANT_FILE != DBC_OVERRIDE_NO)  && (LOOP_VARIANT_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (LOOP_VARIANT_GLOBAL == DBC_OVERRIDE_NO)  && (LOOP_VARIANT_FILE == DBC_OVERRIDE_YES) && (LOOP_VARIANT_FUNCTION != DBC_OVERRIDE_NO) ) \
   ) 
   #define LOOP_VARIANT_VARIABLE_DEFINE( x ) x
#else
   #define LOOP_VARIANT_VARIABLE_DEFINE( x )
#endif


/**
   Check
*/

#ifndef CHECK_GLOBAL
   #define CHECK_GLOBAL DBC_NEUTRAL
#endif

#ifndef CHECK_FILE
   #define CHECK_FILE DBC_NEUTRAL
#endif

#ifndef CHECK_FUNCTION
   #define CHECK_FUNCTION DBC_NEUTRAL
#endif

#define CHECK( m, x ) \
if ( ( (CHECK_FUNCTION == DBC_OVERRIDE_YES) ) \
     || \
     ( (CHECK_GLOBAL == DBC_NEUTRAL)      && (CHECK_FILE == DBC_NEUTRAL)      && (CHECK_FUNCTION == DBC_YES) ) \
     || \
     ( (CHECK_GLOBAL == DBC_NEUTRAL)      && (CHECK_FILE == DBC_YES)          && (CHECK_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (CHECK_GLOBAL == DBC_NEUTRAL)      && (CHECK_FILE == DBC_OVERRIDE_YES) && (CHECK_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (CHECK_GLOBAL == DBC_NO)           && (CHECK_FILE == DBC_OVERRIDE_YES) && (CHECK_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (CHECK_GLOBAL == DBC_YES)          && (CHECK_FILE != DBC_OVERRIDE_NO)  && (CHECK_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (CHECK_GLOBAL == DBC_OVERRIDE_YES) && (CHECK_FILE != DBC_OVERRIDE_NO)  && (CHECK_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (CHECK_GLOBAL == DBC_OVERRIDE_NO)  && (CHECK_FILE == DBC_OVERRIDE_YES) && (CHECK_FUNCTION != DBC_OVERRIDE_NO) ) \
   ) \
{ \
   assert(( ( void ) m, x )); \
}

/**
   Precondition
*/

#ifndef PRE_GLOBAL
   #define PRE_GLOBAL DBC_NEUTRAL
#endif

#ifndef PRE_FILE
   #define PRE_FILE DBC_NEUTRAL
#endif

#ifndef PRE_FUNCTION
   #define PRE_FUNCTION DBC_NEUTRAL
#endif

#define PRECONDITION( m, x ) \
if ( ( (PRE_FUNCTION == DBC_OVERRIDE_YES) ) \
     || \
     ( (PRE_GLOBAL == DBC_NEUTRAL)      && (PRE_FILE == DBC_NEUTRAL)      && (PRE_FUNCTION == DBC_YES) ) \
     || \
     ( (PRE_GLOBAL == DBC_NEUTRAL)      && (PRE_FILE == DBC_YES)          && (PRE_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (PRE_GLOBAL == DBC_NEUTRAL)      && (PRE_FILE == DBC_OVERRIDE_YES) && (PRE_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (PRE_GLOBAL == DBC_NO)           && (PRE_FILE == DBC_OVERRIDE_YES) && (PRE_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (PRE_GLOBAL == DBC_YES)          && (PRE_FILE != DBC_OVERRIDE_NO)  && (PRE_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (PRE_GLOBAL == DBC_OVERRIDE_YES) && (PRE_FILE != DBC_OVERRIDE_NO)  && (PRE_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (PRE_GLOBAL == DBC_OVERRIDE_NO)  && (PRE_FILE == DBC_OVERRIDE_YES) && (PRE_FUNCTION != DBC_OVERRIDE_NO) ) \
   ) \
{ \
   assert(( ( void ) m, x )); \
}

/**
   Postcondition
*/

#ifndef POST_GLOBAL
   #define POST_GLOBAL DBC_NEUTRAL
#endif

#ifndef POST_FILE
   #define POST_FILE DBC_NEUTRAL
#endif

#ifndef POST_FUNCTION
   #define POST_FUNCTION DBC_NEUTRAL
#endif

#define POSTCONDITION( m, x ) \
if ( ( (POST_FUNCTION == DBC_OVERRIDE_YES) ) \
     || \
     ( (POST_GLOBAL == DBC_NEUTRAL)      && (POST_FILE == DBC_NEUTRAL)      && (POST_FUNCTION == DBC_YES) ) \
     || \
     ( (POST_GLOBAL == DBC_NEUTRAL)      && (POST_FILE == DBC_YES)          && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_NEUTRAL)      && (POST_FILE == DBC_OVERRIDE_YES) && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_NO)           && (POST_FILE == DBC_OVERRIDE_YES) && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_YES)          && (POST_FILE != DBC_OVERRIDE_NO)  && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_OVERRIDE_YES) && (POST_FILE != DBC_OVERRIDE_NO)  && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_OVERRIDE_NO)  && (POST_FILE == DBC_OVERRIDE_YES) && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
   ) \
{ \
   assert(( ( void ) m, x )); \
}

// POSTCONDITION_VARIABLE_DEFINE

#if ( ( (POST_FUNCTION == DBC_OVERRIDE_YES) ) \
     || \
     ( (POST_GLOBAL == DBC_NEUTRAL)      && (POST_FILE == DBC_NEUTRAL)      && (POST_FUNCTION == DBC_YES) ) \
     || \
     ( (POST_GLOBAL == DBC_NEUTRAL)      && (POST_FILE == DBC_YES)          && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_NEUTRAL)      && (POST_FILE == DBC_OVERRIDE_YES) && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_NO)           && (POST_FILE == DBC_OVERRIDE_YES) && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_YES)          && (POST_FILE != DBC_OVERRIDE_NO)  && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_OVERRIDE_YES) && (POST_FILE != DBC_OVERRIDE_NO)  && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_OVERRIDE_NO)  && (POST_FILE == DBC_OVERRIDE_YES) && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
   ) 
   #define POSTCONDITION_VARIABLE_DEFINE( x ) x
#else
   #define POSTCONDITION_VARIABLE_DEFINE( x )
#endif

// POSTCONDITION_VARIABLE_DISPOSE

#if ( ( (POST_FUNCTION == DBC_OVERRIDE_YES) ) \
     || \
     ( (POST_GLOBAL == DBC_NEUTRAL)      && (POST_FILE == DBC_NEUTRAL)      && (POST_FUNCTION == DBC_YES) ) \
     || \
     ( (POST_GLOBAL == DBC_NEUTRAL)      && (POST_FILE == DBC_YES)          && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_NEUTRAL)      && (POST_FILE == DBC_OVERRIDE_YES) && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_NO)           && (POST_FILE == DBC_OVERRIDE_YES) && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_YES)          && (POST_FILE != DBC_OVERRIDE_NO)  && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_OVERRIDE_YES) && (POST_FILE != DBC_OVERRIDE_NO)  && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
     || \
     ( (POST_GLOBAL == DBC_OVERRIDE_NO)  && (POST_FILE == DBC_OVERRIDE_YES) && (POST_FUNCTION != DBC_OVERRIDE_NO) ) \
   ) 
   #define POSTCONDITION_VARIABLE_DISPOSE( x ) x
#else
   #define POSTCONDITION_VARIABLE_DISPOSE( x )
#endif

/**
   Invariant
*/

#ifndef INVARIANT_GLOBAL
   #define INVARIANT_GLOBAL DBC_NEUTRAL
#endif

#ifndef INVARIANT_FILE
   #define INVARIANT_FILE DBC_NEUTRAL
#endif

#define INVARIANT_CONDITIONAL \
   ( ( (INVARIANT_FILE == DBC_OVERRIDE_YES) ) \
     || \
     ( (INVARIANT_GLOBAL == DBC_NEUTRAL)      && (INVARIANT_FILE == DBC_YES) ) \
     || \
     ( (INVARIANT_GLOBAL == DBC_YES)          && (INVARIANT_FILE != DBC_OVERRIDE_NO) ) \
     || \
     ( (INVARIANT_GLOBAL == DBC_OVERRIDE_YES) && (INVARIANT_FILE != DBC_OVERRIDE_NO) ) \
   ) 

#if ( INVARIANT_CONDITIONAL == 1 )
   #define INVARIANT( p ) invariant( p );
#else
   #define INVARIANT( p )
#endif


#ifdef __cplusplus
}
#endif

#endif /* DBC_H */

/* End of file */
