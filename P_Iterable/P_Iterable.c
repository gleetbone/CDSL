/**
 @file P_Iterable.c
 @author Greg Lee
 @version 1.0.0
 @brief: "P_Iterable protocol"
 
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

 Function definitions for the P_Iterable protocol.

*/

#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Iterable.h"
#include "P_Iterable.ph"
   
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   Includes
*/

#include <stddef.h>

/**
   p_iterable_dispose
*/
void
P_Iterable_dispose( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   void (*dispose)( protocol_base_t * ) = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_DISPOSE );

   CHECK( "P_ITERABLE_DISPOSE function not null", dispose != NULL );

   dispose( p_iterable );

   return;
}

/**
   p_iterable_dispose_f
*/
iterable_dispose_f
P_Iterable_dispose_f( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   void (*dispose)( protocol_base_t * ) = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_DISPOSE );

   CHECK( "P_ITERABLE_DISPOSE function not null", dispose != NULL );

   return dispose;
}

/**
   p_iterable_dispose_with_contents
*/
void
P_Iterable_dispose_with_contents( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   void (*dispose_with_contents)( protocol_base_t * ) 
      = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_DISPOSE_WITH_CONTENTS );

   CHECK( "P_ITERABLE_DISPOSE function not null", dispose_with_contents != NULL );

   dispose_with_contents( p_iterable );

   return;
}

/**
   p_iterable_dispose_with_contents_f
*/
iterable_dispose_with_contents_f
P_Iterable_dispose_with_contents_f( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   void (*dispose_with_contents)( protocol_base_t * ) 
      = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_DISPOSE_WITH_CONTENTS );

   CHECK( "P_ITERABLE_DISPOSE function not null", dispose_with_contents != NULL );
   
   return dispose_with_contents;
}

/**
   p_iterable_count
*/
int32_t
P_Iterable_count( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   int32_t (*count)( protocol_base_t * ) 
      = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_COUNT );

   CHECK( "P_ITERABLE_COUNT function not null", count != NULL );

   int32_t result = count( p_iterable );

   return result;
}

/**
   p_iterable_count_f
*/
iterable_count_f
P_Iterable_count_f( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   int32_t (*count)( protocol_base_t * ) 
      = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_COUNT );

   CHECK( "P_ITERABLE_COUNT function not null", count != NULL );

   return count;
}

/**
   p_iterable_item
*/
Type
P_Iterable_item( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   Type (*item)( protocol_base_t * ) 
      = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_ITEM );

   CHECK( "P_ITERABLE_ITEM function not null", item != NULL );

   Type result = item( p_iterable );

   return result;
}

/**
   p_iterable_item_f
*/
iterable_item_f
P_Iterable_item_f( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   Type (*item)( protocol_base_t * index ) 
      = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_ITEM );

   CHECK( "P_ITERABLE_ITEM function not null", item != NULL );

   return item;
}

/**
   p_iterable_off
*/
int32_t
P_Iterable_off( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   int32_t (*off)( protocol_base_t * ) 
      = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_OFF );

   CHECK( "P_ITERABLE_OFF function not null", off != NULL );

   int32_t result = off( p_iterable );

   return result;
}

/**
   p_iterable_off_f
*/
iterable_off_f
P_Iterable_off_f( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   int32_t (*off)( protocol_base_t * ) 
      = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_OFF );

   CHECK( "P_ITERABLE_OFF function not null", off != NULL );

   return off;
}

/**
   p_iterable_is_empty
*/
int32_t
P_Iterable_is_empty( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   int32_t (*is_empty)( protocol_base_t * ) 
      = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_IS_EMPTY );

   CHECK( "P_ITERABLE_IS_EMPTY function not null", is_empty != NULL );

   int32_t result = is_empty( p_iterable );

   return result;
}

/**
   p_iterable_is_empty_f
*/
iterable_is_empty_f
P_Iterable_is_empty_f( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   int32_t (*is_empty)( protocol_base_t * ) 
      = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_IS_EMPTY );

   CHECK( "P_ITERABLE_IS_EMPTY function not null", is_empty != NULL );

   return is_empty;
}

/**
   p_iterable_start
*/
void
P_Iterable_start( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   void (*start)( protocol_base_t * ) 
      = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_START );

   CHECK( "P_ITERABLE_START function not null", start != NULL );

   start( p_iterable );

   return;
}

/**
   p_iterable_start_f
*/
iterable_start_f
P_Iterable_start_f( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   void (*start)( protocol_base_t * ) 
      = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_START );

   CHECK( "P_ITERABLE_START function not null", start != NULL );

   return start;
}

/**
   p_iterable_forth
*/
void
P_Iterable_forth( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   void (*forth)( protocol_base_t * ) 
      = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_FORTH );

   CHECK( "P_ITERABLE_FORTH function not null", forth != NULL );

   forth( p_iterable );

   return;
}

/**
   p_iterable_forth_f
*/
iterable_forth_f
P_Iterable_forth_f( Prefix )
(
   protocol_base_t *p_iterable
)
{
   PRECONDITION( "p_iterable not null", p_iterable != NULL );
   PRECONDITION( "p_iterable is object", protocol_base_is_valid_object( p_iterable ) == 1 );
   PRECONDITION( "p_iterable supports protocol", protocol_base_supports_protocol( p_iterable, P_ITERABLE ) == 1 );

   void (*forth)( protocol_base_t * ) 
      = (*p_iterable).get_function( P_ITERABLE, P_ITERABLE_FORTH );

   CHECK( "P_ITERABLE_FORTH function not null", forth != NULL );

   return forth;
}

/* End of file */




