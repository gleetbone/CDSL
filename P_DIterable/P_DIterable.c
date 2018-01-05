/**
 @file P_DIterable.c
 @author Greg Lee
 @version 1.0.0
 @brief: "P_DIterable protocol"
 
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

 Function definitions for the P_DIterable protocol.

*/

#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_DIterable.h"
#include "P_DIterable.ph"
   
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   Includes
*/

#include <stddef.h>

/**
   p_diterable_dispose
*/
void
P_DIterable_dispose( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   void (*dispose)( protocol_base_t * ) = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_DISPOSE );

   CHECK( "P_DITERABLE_DISPOSE function not null", dispose != NULL );

   dispose( p_diterable );

   return;
}

/**
   p_diterable_dispose_f
*/
diterable_dispose_f
P_DIterable_dispose_f( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   void (*dispose)( protocol_base_t * ) = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_DISPOSE );

   CHECK( "P_DITERABLE_DISPOSE function not null", dispose != NULL );

   return dispose;
}

/**
   p_diterable_dispose_with_contents
*/
void
P_DIterable_dispose_with_contents( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   void (*dispose_with_contents)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_DISPOSE_WITH_CONTENTS );

   CHECK( "P_DITERABLE_DISPOSE function not null", dispose_with_contents != NULL );

   dispose_with_contents( p_diterable );

   return;
}

/**
   p_diterable_dispose_with_contents_f
*/
diterable_dispose_with_contents_f
P_DIterable_dispose_with_contents_f( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   void (*dispose_with_contents)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_DISPOSE_WITH_CONTENTS );

   CHECK( "P_DITERABLE_DISPOSE function not null", dispose_with_contents != NULL );
   
   return dispose_with_contents;
}

/**
   p_diterable_count
*/
int32_t
P_DIterable_count( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   int32_t (*count)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_COUNT );

   CHECK( "P_DITERABLE_COUNT function not null", count != NULL );

   int32_t result = count( p_diterable );

   return result;
}

/**
   p_diterable_count_f
*/
diterable_count_f
P_DIterable_count_f( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   int32_t (*count)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_COUNT );

   CHECK( "P_DITERABLE_COUNT function not null", count != NULL );

   return count;
}

/**
   p_diterable_item
*/
Type
P_DIterable_item( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   Type (*item)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_ITEM );

   CHECK( "P_DITERABLE_ITEM function not null", item != NULL );

   Type result = item( p_diterable );

   return result;
}

/**
   p_diterable_item_f
*/
diterable_item_f
P_DIterable_item_f( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   Type (*item)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_ITEM );

   CHECK( "P_DITERABLE_ITEM function not null", item != NULL );

   return item;
}

/**
   p_diterable_off
*/
int32_t
P_DIterable_off( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   int32_t (*off)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_OFF );

   CHECK( "P_DITERABLE_OFF function not null", off != NULL );

   int32_t result = off( p_diterable );

   return result;
}

/**
   p_diterable_off_f
*/
diterable_off_f
P_DIterable_off_f( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   int32_t (*off)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_OFF );

   CHECK( "P_DITERABLE_OFF function not null", off != NULL );

   return off;
}

/**
   p_diterable_is_empty
*/
int32_t
P_DIterable_is_empty( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   int32_t (*is_empty)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_IS_EMPTY );

   CHECK( "P_DITERABLE_IS_EMPTY function not null", is_empty != NULL );

   int32_t result = is_empty( p_diterable );

   return result;
}

/**
   p_diterable_is_empty_f
*/
diterable_is_empty_f
P_DIterable_is_empty_f( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   int32_t (*is_empty)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_IS_EMPTY );

   CHECK( "P_DITERABLE_IS_EMPTY function not null", is_empty != NULL );

   return is_empty;
}

/**
   p_diterable_start
*/
void
P_DIterable_start( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   void (*start)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_START );

   CHECK( "P_DITERABLE_START function not null", start != NULL );

   start( p_diterable );

   return;
}

/**
   p_diterable_start_f
*/
diterable_start_f
P_DIterable_start_f( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   void (*start)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_START );

   CHECK( "P_DITERABLE_START function not null", start != NULL );

   return start;
}

/**
   p_diterable_forth
*/
void
P_DIterable_forth( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   void (*forth)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_FORTH );

   CHECK( "P_DITERABLE_FORTH function not null", forth != NULL );

   forth( p_diterable );

   return;
}

/**
   p_diterable_forth_f
*/
diterable_forth_f
P_DIterable_forth_f( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   void (*forth)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_FORTH );

   CHECK( "P_DITERABLE_FORTH function not null", forth != NULL );

   return forth;
}

/**
   p_diterable_finish
*/
void
P_DIterable_finish( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   void (*finish)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_FINISH );

   CHECK( "P_DITERABLE_FINISH function not null", finish != NULL );

   finish( p_diterable );

   return;
}

/**
   p_diterable_finish_f
*/
diterable_finish_f
P_DIterable_finish_f( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   void (*finish)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_FINISH );

   CHECK( "P_DITERABLE_FINISH function not null", finish != NULL );

   return finish;
}

/**
   p_diterable_back
*/
void
P_DIterable_back( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   void (*back)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_BACK );

   CHECK( "P_DITERABLE_BACK function not null", back != NULL );

   back( p_diterable );

   return;
}

/**
   p_diterable_back_f
*/
diterable_back_f
P_DIterable_back_f( Prefix )
(
   protocol_base_t *p_diterable
)
{
   PRECONDITION( "p_diterable not null", p_diterable != NULL );
   PRECONDITION( "p_diterable is object", protocol_base_is_valid_object( p_diterable ) == 1 );
   PRECONDITION( "p_diterable supports protocol", protocol_base_supports_protocol( p_diterable, P_DITERABLE ) == 1 );

   void (*back)( protocol_base_t * ) 
      = (*p_diterable).get_function( P_DITERABLE, P_DITERABLE_BACK );

   CHECK( "P_DITERABLE_BACK function not null", back != NULL );

   return back;
}

/* End of file */




