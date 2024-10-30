/**
 @file P_Indexable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "P_Indexable protocol"

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

 Function definitions for the P_Indexable protocol.

*/

#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Indexable.h"
#include "P_Indexable.ph"

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   Includes
*/

#include <stddef.h>

/**
   p_indexable_count
*/
int32_t
P_Indexable_count( Prefix )
(
   protocol_base_t *p_indexable
)
{
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );

   int32_t (*count)( protocol_base_t * )
      = ( *p_indexable ).get_function( P_INDEXABLE_TYPE, P_INDEXABLE_COUNT );

   CHECK( "P_INDEXABLE_COUNT function not null", count != NULL );

   int32_t result = count( p_indexable );

   return result;
}

/**
   p_indexable_item
*/
Type
P_Indexable_item( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t index
)
{
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );

   Type (*item)( protocol_base_t *, int32_t index )
      = ( *p_indexable ).get_function( P_INDEXABLE_TYPE, P_INDEXABLE_ITEM );

   CHECK( "P_INDEXABLE_ITEM function not null", item != NULL );

   Type result = item( p_indexable, index );

   return result;
}

/**
   p_indexable_put
*/
void
P_Indexable_put( Prefix )
(
   protocol_base_t *p_indexable,
   Type value,
   int32_t index
)
{
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );

   void (*put)( protocol_base_t *, Type value, int32_t index )
      = ( *p_indexable ).get_function( P_INDEXABLE_TYPE, P_INDEXABLE_PUT );

   CHECK( "P_INDEXABLE_PUT function not null", put != NULL );

   put( p_indexable, value, index );

   return;
}

/**
   p_indexable_put_and_dispose
*/
void
P_Indexable_put_and_dispose( Prefix )
(
   protocol_base_t *p_indexable,
   Type value,
   int32_t index
)
{
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );

   void ( *put_and_dispose )( protocol_base_t *, Type value, int32_t index )
      = ( *p_indexable ).get_function( P_INDEXABLE_TYPE, P_INDEXABLE_PUT_AND_DISPOSE );

   CHECK( "P_INDEXABLE_PUT function not null", put_and_dispose != NULL );

   put_and_dispose( p_indexable, value, index );

   return;
}

/* End of file */




