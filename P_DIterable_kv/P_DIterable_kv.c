/**
 @file P_DIterable_kv.c
 @author Greg Lee
 @version 1.0.0
 @brief: "P_DIterable_kv protocol"
 
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

 Function definitions for the P_DIterable_kv protocol.

*/

#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_DIterable_kv.h"
#include "P_DIterable_kv.ph"
   
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   Includes
*/

#include <stddef.h>

/**
   p_diterable_kv_dispose
*/
void
P_DIterable_kv_dispose( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   void (*dispose)( protocol_base_t * ) = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_DISPOSE );

   CHECK( "P_DITERABLE_KV_DISPOSE function not null", dispose != NULL );

   dispose( p_diterable_kv );

   return;
}

/**
   p_diterable_kv_dispose_f
*/
diterable_kv_dispose_f
P_DIterable_kv_dispose_f( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   void (*dispose)( protocol_base_t * ) = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_DISPOSE );

   CHECK( "P_DITERABLE_KV_DISPOSE function not null", dispose != NULL );

   return dispose;
}

/**
   p_diterable_kv_dispose_with_contents
*/
void
P_DIterable_kv_dispose_with_contents( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   void (*dispose_with_contents)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_DISPOSE_WITH_CONTENTS );

   CHECK( "P_DITERABLE_KV_DISPOSE function not null", dispose_with_contents != NULL );

   dispose_with_contents( p_diterable_kv );

   return;
}

/**
   p_diterable_kv_dispose_with_contents_f
*/
diterable_kv_dispose_with_contents_f
P_DIterable_kv_dispose_with_contents_f( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   void (*dispose_with_contents)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_DISPOSE_WITH_CONTENTS );

   CHECK( "P_DITERABLE_KV_DISPOSE function not null", dispose_with_contents != NULL );
   
   return dispose_with_contents;
}

/**
   p_diterable_kv_count
*/
int32_t
P_DIterable_kv_count( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   int32_t (*count)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_COUNT );

   CHECK( "P_DITERABLE_KV_COUNT function not null", count != NULL );

   int32_t result = count( p_diterable_kv );

   return result;
}

/**
   p_diterable_kv_count_f
*/
diterable_kv_count_f
P_DIterable_kv_count_f( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   int32_t (*count)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_COUNT );

   CHECK( "P_DITERABLE_KV_COUNT function not null", count != NULL );

   return count;
}

/**
   p_diterable_kv_key
*/
Key
P_DIterable_kv_key( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   Key (*key)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_KEY );

   CHECK( "P_DITERABLE_KV_KEY function not null", key != NULL );

   Key result = key( p_diterable_kv );

   return result;
}

/**
   p_diterable_kv_key_f
*/
diterable_kv_key_f
P_DIterable_kv_key_f( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   Key (*key)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_KEY );

   CHECK( "P_DITERABLE_KV_KEY function not null", key != NULL );

   return key;
}

/**
   p_diterable_kv_value
*/
Type
P_DIterable_kv_value( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   Type (*value)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_VALUE );

   CHECK( "P_DITERABLE_KV_VALUE function not null", value != NULL );

   Type result = value( p_diterable_kv );

   return result;
}

/**
   p_diterable_kv_value_f
*/
diterable_kv_value_f
P_DIterable_kv_value_f( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   Type (*value)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_VALUE );

   CHECK( "P_DITERABLE_KV_VALUE function not null", value != NULL );

   return value;
}

/**
   p_diterable_kv_off
*/
int32_t
P_DIterable_kv_off( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   int32_t (*off)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_OFF );

   CHECK( "P_DITERABLE_KV_OFF function not null", off != NULL );

   int32_t result = off( p_diterable_kv );

   return result;
}

/**
   p_diterable_kv_off_f
*/
diterable_kv_off_f
P_DIterable_kv_off_f( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   int32_t (*off)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_OFF );

   CHECK( "P_DITERABLE_KV_OFF function not null", off != NULL );

   return off;
}

/**
   p_diterable_kv_is_empty
*/
int32_t
P_DIterable_kv_is_empty( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   int32_t (*is_empty)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_IS_EMPTY );

   CHECK( "P_DITERABLE_KV_IS_EMPTY function not null", is_empty != NULL );

   int32_t result = is_empty( p_diterable_kv );

   return result;
}

/**
   p_diterable_kv_is_empty_f
*/
diterable_kv_is_empty_f
P_DIterable_kv_is_empty_f( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   int32_t (*is_empty)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_IS_EMPTY );

   CHECK( "P_DITERABLE_KV_IS_EMPTY function not null", is_empty != NULL );

   return is_empty;
}

/**
   p_diterable_kv_start
*/
void
P_DIterable_kv_start( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   void (*start)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_START );

   CHECK( "P_DITERABLE_KV_START function not null", start != NULL );

   start( p_diterable_kv );

   return;
}

/**
   p_diterable_kv_start_f
*/
diterable_kv_start_f
P_DIterable_kv_start_f( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   void (*start)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_START );

   CHECK( "P_DITERABLE_KV_START function not null", start != NULL );

   return start;
}

/**
   p_diterable_kv_forth
*/
void
P_DIterable_kv_forth( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   void (*forth)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_FORTH );

   CHECK( "P_DITERABLE_KV_FORTH function not null", forth != NULL );

   forth( p_diterable_kv );

   return;
}

/**
   p_diterable_kv_forth_f
*/
diterable_kv_forth_f
P_DIterable_kv_forth_f( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   void (*forth)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_FORTH );

   CHECK( "P_DITERABLE_KV_FORTH function not null", forth != NULL );

   return forth;
}

/**
   p_diterable_kv_finish
*/
void
P_DIterable_kv_finish( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   void (*finish)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_FINISH );

   CHECK( "P_DITERABLE_KV_FINISH function not null", finish != NULL );

   finish( p_diterable_kv );

   return;
}

/**
   p_diterable_kv_finish_f
*/
diterable_kv_finish_f
P_DIterable_kv_finish_f( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   void (*finish)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_FINISH );

   CHECK( "P_DITERABLE_KV_FINISH function not null", finish != NULL );

   return finish;
}

/**
   p_diterable_kv_back
*/
void
P_DIterable_kv_back( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   void (*back)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_BACK );

   CHECK( "P_DITERABLE_KV_BACK function not null", back != NULL );

   back( p_diterable_kv );

   return;
}

/**
   p_diterable_kv_back_f
*/
diterable_kv_back_f
P_DIterable_kv_back_f( Prefix )
(
   protocol_base_t *p_diterable_kv
)
{
   PRECONDITION( "p_diterable_kv not null", p_diterable_kv != NULL );
   PRECONDITION( "p_diterable_kv is object", protocol_base_is_valid_object( p_diterable_kv ) == 1 );
   PRECONDITION( "p_diterable_kv supports protocol", protocol_base_supports_protocol( p_diterable_kv, P_DITERABLE_KV ) == 1 );

   void (*back)( protocol_base_t * ) 
      = (*p_diterable_kv).get_function( P_DITERABLE_KV, P_DITERABLE_KV_BACK );

   CHECK( "P_DITERABLE_KV_BACK function not null", back != NULL );

   return back;
}

/* End of file */




