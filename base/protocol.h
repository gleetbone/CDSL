/**
 @file protocol.h
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

#ifndef PROTOCOL_H
#define PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
   Protocol macros
*/

// default value is for PROTOCOLS_ENABLED macro to be undefined
// #define PROTOCOLS_ENABLED

#ifdef PROTOCOLS_ENABLED

#undef PROTOCOLS_DEFINITION
#define PROTOCOLS_DEFINITION \
   void * (*get_function)( int32_t protocol_id, int32_t function_id ); \
   int32_t (*supports_protocol)( int32_t protocol_id );

#undef PROTOCOLS_INIT
#define PROTOCOLS_INIT( x ) \
   (*x).get_function = get_function; \
   (*x).supports_protocol = supports_protocol;

#undef protocol_arg_ok
#define protocol_arg_ok( Type_Code, ARG ) \
( ( ( Type_Code & PROTOCOL_MASK ) == PROTOCOL_VALID_PROTOCOL ) ?\
protocol_supported_by_arg( Type_Code, ARG ) :\
1 )

#else // PROTOCOLS_ENABLED

#define PROTOCOLS_DEFINITION

#define PROTOCOLS_INIT( x )

#define protocol_arg_ok( Type_Code, ARG ) 1

#endif // PROTOCOLS_ENABLED

#ifdef __cplusplus
}
#endif

#endif /* PROTOCOL_H */

/* End of file */
