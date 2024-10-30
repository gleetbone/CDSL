/**
 @file P_Iterable_kv.c
 @author Greg Lee
 @version 2.0.0
 @brief: "P_Iterable_kv protocol"

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

 Function definitions for the P_Iterable_kv protocol.

*/

#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Iterable_kv.h"
#include "P_Iterable_kv.ph"

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   Includes
*/

#include <stddef.h>

/**
   p_iterable_kv_count
*/
int32_t
P_Iterable_kv_count( Prefix )
(
   protocol_base_t *p_iterable_kv
)
{
   PRECONDITION( "p_iterable_kv not null", p_iterable_kv != NULL );
   PRECONDITION( "p_iterable_kv is object", protocol_base_is_valid_object( p_iterable_kv ) == 1 );
   PRECONDITION( "p_iterable_kv supports protocol", protocol_base_supports_protocol( p_iterable_kv, P_ITERABLE_KV_TYPE ) == 1 );

   int32_t (*count)( protocol_base_t * )
      = ( *p_iterable_kv ).get_function( P_ITERABLE_KV_TYPE, P_ITERABLE_KV_COUNT );

   CHECK( "P_ITERABLE_KV_COUNT function not null", count != NULL );

   int32_t result = count( p_iterable_kv );

   return result;
}

/**
   p_iterable_kv_key
*/
Key
P_Iterable_kv_key( Prefix )
(
   protocol_base_t *p_iterable_kv
)
{
   PRECONDITION( "p_iterable_kv not null", p_iterable_kv != NULL );
   PRECONDITION( "p_iterable_kv is object", protocol_base_is_valid_object( p_iterable_kv ) == 1 );
   PRECONDITION( "p_iterable_kv supports protocol", protocol_base_supports_protocol( p_iterable_kv, P_ITERABLE_KV_TYPE ) == 1 );

   Key (*key)( protocol_base_t * )
      = ( *p_iterable_kv ).get_function( P_ITERABLE_KV_TYPE, P_ITERABLE_KV_KEY );

   CHECK( "P_ITERABLE_KV_KEY function not null", key != NULL );

   Key result = key( p_iterable_kv );

   return result;
}

/**
   p_iterable_kv_value
*/
Type
P_Iterable_kv_value( Prefix )
(
   protocol_base_t *p_iterable_kv
)
{
   PRECONDITION( "p_iterable_kv not null", p_iterable_kv != NULL );
   PRECONDITION( "p_iterable_kv is object", protocol_base_is_valid_object( p_iterable_kv ) == 1 );
   PRECONDITION( "p_iterable_kv supports protocol", protocol_base_supports_protocol( p_iterable_kv, P_ITERABLE_KV_TYPE ) == 1 );

   Type (*value)( protocol_base_t * )
      = ( *p_iterable_kv ).get_function( P_ITERABLE_KV_TYPE, P_ITERABLE_KV_VALUE );

   CHECK( "P_ITERABLE_KV_VALUE function not null", value != NULL );

   Type result = value( p_iterable_kv );

   return result;
}

/**
   p_iterable_kv_off
*/
int32_t
P_Iterable_kv_off( Prefix )
(
   protocol_base_t *p_iterable_kv
)
{
   PRECONDITION( "p_iterable_kv not null", p_iterable_kv != NULL );
   PRECONDITION( "p_iterable_kv is object", protocol_base_is_valid_object( p_iterable_kv ) == 1 );
   PRECONDITION( "p_iterable_kv supports protocol", protocol_base_supports_protocol( p_iterable_kv, P_ITERABLE_KV_TYPE ) == 1 );

   int32_t (*off)( protocol_base_t * )
      = ( *p_iterable_kv ).get_function( P_ITERABLE_KV_TYPE, P_ITERABLE_KV_OFF );

   CHECK( "P_ITERABLE_KV_OFF function not null", off != NULL );

   int32_t result = off( p_iterable_kv );

   return result;
}

/**
   p_iterable_kv_is_empty
*/
int32_t
P_Iterable_kv_is_empty( Prefix )
(
   protocol_base_t *p_iterable_kv
)
{
   PRECONDITION( "p_iterable_kv not null", p_iterable_kv != NULL );
   PRECONDITION( "p_iterable_kv is object", protocol_base_is_valid_object( p_iterable_kv ) == 1 );
   PRECONDITION( "p_iterable_kv supports protocol", protocol_base_supports_protocol( p_iterable_kv, P_ITERABLE_KV_TYPE ) == 1 );

   int32_t ( *is_empty )( protocol_base_t * )
      = ( *p_iterable_kv ).get_function( P_ITERABLE_KV_TYPE, P_ITERABLE_KV_IS_EMPTY );

   CHECK( "P_ITERABLE_KV_IS_EMPTY function not null", is_empty != NULL );

   int32_t result = is_empty( p_iterable_kv );

   return result;
}

/**
   p_iterable_kv_start
*/
void
P_Iterable_kv_start( Prefix )
(
   protocol_base_t *p_iterable_kv
)
{
   PRECONDITION( "p_iterable_kv not null", p_iterable_kv != NULL );
   PRECONDITION( "p_iterable_kv is object", protocol_base_is_valid_object( p_iterable_kv ) == 1 );
   PRECONDITION( "p_iterable_kv supports protocol", protocol_base_supports_protocol( p_iterable_kv, P_ITERABLE_KV_TYPE ) == 1 );

   void (*start)( protocol_base_t * )
      = ( *p_iterable_kv ).get_function( P_ITERABLE_KV_TYPE, P_ITERABLE_KV_START );

   CHECK( "P_ITERABLE_KV_START function not null", start != NULL );

   start( p_iterable_kv );

   return;
}

/**
   p_iterable_kv_forth
*/
void
P_Iterable_kv_forth( Prefix )
(
   protocol_base_t *p_iterable_kv
)
{
   PRECONDITION( "p_iterable_kv not null", p_iterable_kv != NULL );
   PRECONDITION( "p_iterable_kv is object", protocol_base_is_valid_object( p_iterable_kv ) == 1 );
   PRECONDITION( "p_iterable_kv supports protocol", protocol_base_supports_protocol( p_iterable_kv, P_ITERABLE_KV_TYPE ) == 1 );

   void (*forth)( protocol_base_t * )
      = ( *p_iterable_kv ).get_function( P_ITERABLE_KV_TYPE, P_ITERABLE_KV_FORTH );

   CHECK( "P_ITERABLE_KV_FORTH function not null", forth != NULL );

   forth( p_iterable_kv );

   return;
}

/* End of file */




