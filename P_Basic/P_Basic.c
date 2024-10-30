/**
 @file P_Basic.c
 @author Greg Lee
 @version 2.0.0
 @brief: "P_Basic protocol"

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

 Function definitions for the P_Basic protocol.

*/

#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.h"
#include "P_Basic.ph"

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   Includes
*/

#include <stddef.h>

/**
   p_basic_dispose
*/
void
P_Basic_dispose( Prefix )
(
   protocol_base_t **p_basic
)
{
   PRECONDITION( "p_basic not null", p_basic != NULL );
   PRECONDITION( "*p_basic not null", *p_basic != NULL );
   PRECONDITION( "p_basic is object", protocol_base_is_valid_object( *p_basic ) == 1 );
   PRECONDITION( "p_basic supports protocol", protocol_base_supports_protocol( *p_basic, P_BASIC_TYPE ) == 1 );

   void (*dispose)( protocol_base_t ** ) = ( **p_basic ).get_function( P_BASIC_TYPE, P_BASIC_DISPOSE );

   CHECK( "P_BASIC_DISPOSE function not null", dispose != NULL );

   dispose( p_basic );

   *p_basic = NULL;

   return;
}

/**
   p_basic_deep_dispose
*/
void
P_Basic_deep_dispose( Prefix )
(
   protocol_base_t **p_basic
)
{
   PRECONDITION( "p_basic not null", p_basic != NULL );
   PRECONDITION( "*p_basic not null", *p_basic != NULL );
   PRECONDITION( "p_basic is object", protocol_base_is_valid_object( *p_basic ) == 1 );
   PRECONDITION( "p_basic supports protocol", protocol_base_supports_protocol( *p_basic, P_BASIC_TYPE ) == 1 );

   void ( *deep_dispose )( protocol_base_t ** )
      = ( **p_basic ).get_function( P_BASIC_TYPE, P_BASIC_DEEP_DISPOSE );

   CHECK( "P_BASIC_DEEP_DISPOSE function not null", deep_dispose != NULL );

   deep_dispose( p_basic );

   *p_basic = NULL;

   return;
}

/**
   p_basic_is_equal
*/
int32_t
P_Basic_is_equal( Prefix )
(
   protocol_base_t *p_basic,
   protocol_base_t *other
)
{
   PRECONDITION( "p_basic not null", p_basic != NULL );
   PRECONDITION( "p_basic is object", protocol_base_is_valid_object( p_basic ) == 1 );
   PRECONDITION( "p_basic supports protocol", protocol_base_supports_protocol( p_basic, P_BASIC_TYPE ) == 1 );
   PRECONDITION( "other not null", p_basic != NULL );
   PRECONDITION( "other is object", protocol_base_is_valid_object( other ) == 1 );
   PRECONDITION( "other supports protocol", protocol_base_supports_protocol( other, P_BASIC_TYPE ) == 1 );

   int32_t ( *is_equal )( protocol_base_t *, protocol_base_t * )
      = ( *p_basic ).get_function( P_BASIC_TYPE, P_BASIC_IS_EQUAL );

   CHECK( "P_BASIC_IS_EQUAL function not null", is_equal != NULL );

   int32_t result = is_equal( p_basic, other );

   return result;
}

/**
   p_basic_is_deep_equal
*/
int32_t
P_Basic_is_deep_equal( Prefix )
(
   protocol_base_t *p_basic,
   protocol_base_t *other
)
{
   PRECONDITION( "p_basic not null", p_basic != NULL );
   PRECONDITION( "p_basic is object", protocol_base_is_valid_object( p_basic ) == 1 );
   PRECONDITION( "p_basic supports protocol", protocol_base_supports_protocol( p_basic, P_BASIC_TYPE ) == 1 );
   PRECONDITION( "other not null", p_basic != NULL );
   PRECONDITION( "other is object", protocol_base_is_valid_object( other ) == 1 );
   PRECONDITION( "other supports protocol", protocol_base_supports_protocol( other, P_BASIC_TYPE ) == 1 );

   int32_t ( *is_deep_equal )( protocol_base_t *, protocol_base_t * )
      = ( *p_basic ).get_function( P_BASIC_TYPE, P_BASIC_IS_DEEP_EQUAL );

   CHECK( "P_BASIC_IS_DEEP_EQUAL function not null", is_deep_equal != NULL );

   int32_t result = is_deep_equal( p_basic, other );

   return result;
}

/**
   p_basic_copy
*/
void
P_Basic_copy( Prefix )
(
   protocol_base_t *p_basic,
   protocol_base_t *other
)
{
   PRECONDITION( "p_basic not null", p_basic != NULL );
   PRECONDITION( "p_basic is object", protocol_base_is_valid_object( p_basic ) == 1 );
   PRECONDITION( "p_basic supports protocol", protocol_base_supports_protocol( p_basic, P_BASIC_TYPE ) == 1 );
   PRECONDITION( "other not null", p_basic != NULL );
   PRECONDITION( "other is object", protocol_base_is_valid_object( other ) == 1 );
   PRECONDITION( "other supports protocol", protocol_base_supports_protocol( other, P_BASIC_TYPE ) == 1 );

   void (*copy)( protocol_base_t *, protocol_base_t * )
      = ( *p_basic ).get_function( P_BASIC_TYPE, P_BASIC_COPY );

   CHECK( "P_BASIC_COPY function not null", copy != NULL );

   copy( p_basic, other );

   return;
}

/**
   p_basic_deep_copy
*/
void
P_Basic_deep_copy( Prefix )
(
   protocol_base_t *p_basic,
   protocol_base_t *other
)
{
   PRECONDITION( "p_basic not null", p_basic != NULL );
   PRECONDITION( "p_basic is object", protocol_base_is_valid_object( p_basic ) == 1 );
   PRECONDITION( "p_basic supports protocol", protocol_base_supports_protocol( p_basic, P_BASIC_TYPE ) == 1 );
   PRECONDITION( "other not null", p_basic != NULL );
   PRECONDITION( "other is object", protocol_base_is_valid_object( other ) == 1 );
   PRECONDITION( "other supports protocol", protocol_base_supports_protocol( other, P_BASIC_TYPE ) == 1 );

   void ( *deep_copy )( protocol_base_t *, protocol_base_t * )
      = ( *p_basic ).get_function( P_BASIC_TYPE, P_BASIC_DEEP_COPY );

   CHECK( "P_BASIC_DEEP_COPY function not null", deep_copy != NULL );

   deep_copy( p_basic, other );

   return;
}

/**
   p_basic_clone
*/
protocol_base_t *
P_Basic_clone( Prefix )
(
   protocol_base_t *p_basic
)
{
   PRECONDITION( "p_basic not null", p_basic != NULL );
   PRECONDITION( "p_basic is object", protocol_base_is_valid_object( p_basic ) == 1 );
   PRECONDITION( "p_basic supports protocol", protocol_base_supports_protocol( p_basic, P_BASIC_TYPE ) == 1 );

   protocol_base_t * (*clone)( protocol_base_t * )
      = ( *p_basic ).get_function( P_BASIC_TYPE, P_BASIC_CLONE );

   CHECK( "P_BASIC_CLONE function not null", clone != NULL );

   protocol_base_t *result = clone( p_basic );

   return result;
}

/**
   p_basic_deep_clone
*/
protocol_base_t *
P_Basic_deep_clone( Prefix )
(
   protocol_base_t *p_basic
)
{
   PRECONDITION( "p_basic not null", p_basic != NULL );
   PRECONDITION( "p_basic is object", protocol_base_is_valid_object( p_basic ) == 1 );
   PRECONDITION( "p_basic supports protocol", protocol_base_supports_protocol( p_basic, P_BASIC_TYPE ) == 1 );

   protocol_base_t * ( *deep_clone )( protocol_base_t * )
      = ( *p_basic ).get_function( P_BASIC_TYPE, P_BASIC_DEEP_CLONE );

   CHECK( "P_BASIC_DEEP_CLONE function not null", deep_clone != NULL );

   protocol_base_t *result = deep_clone( p_basic );

   return result;
}

/* End of file */




