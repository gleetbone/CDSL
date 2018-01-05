/**
 @file BSorter.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Implementation of Bubble Sorter"
 
 @version 1.0.0
 @brief: "Bubble Sorter"
 
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

 Function definitions for the opaque BSorter_t type.

*/

#ifdef PROTOCOLS_ENABLED   
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Indexable.h"
#include "P_Indexable.ph"
#include "P_Sorter.ph"
#endif // PROTOCOLS_ENABLED   
   
#ifdef __cplusplus
extern "C" {
#endif

/**
   Includes
*/

#include <stddef.h>
#include <stdlib.h>

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

#define BSORTER_TYPE 0xA5000900

/**
   BSorter structure
*/

struct BSorter_struct( Prefix )
{
   
   PROTOCOLS_DEFINITION;

   int32_t type;
   
   int32_t (*func)( Type a, Type b );

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
struct_ok( BSorter_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).func != NULL );

   return result;
}

static
void invariant( BSorter_type( Prefix ) *p )
{
   assert(( (void) "struct ok count", struct_ok( p ) ));
   return;
}

#endif

/**
   Protocol stuff
*/

#ifdef PROTOCOLS_ENABLED

/**
   sorter protocol function array
*/

static
void *
p_sorter_table[P_SORTER_FUNCTION_COUNT]
=
{
   BSorter_dispose( Prefix ),
   BSorter_sort_predefined_comparison_function( Prefix )
};

/**
   protocol get_function
*/

static
void *
get_function
(
   int32_t protocol_id,
   int32_t function_id
)
{
   PRECONDITION( "protocol id is ok", protocol_base_is_valid_protocol( protocol_id ) == 1 );

   void *result = NULL;

   if ( protocol_id == P_SORTER )
   {
      if ( ( function_id >= 0 ) && ( function_id <= P_SORTER_FUNCTION_MAX ) )
      {
         result = p_sorter_table[ function_id ];
      }
   }

   return result;
}

/**
   protocol supports_protocol
*/

static
int32_t
supports_protocol
(
   int32_t protocol_id
)
{
   PRECONDITION( "protocol id is ok", protocol_base_is_valid_protocol( protocol_id ) == 1 );

   int32_t result = 0;

   if ( protocol_id == P_SORTER )
   {
      result = 1;
   }

   return result;
}

#endif // PROTOCOLS_ENABLED


static
void 
sort
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
)
{
   Type temp;
   Type (*item)( protocol_base_t *p_indexable, int32_t index ) = NULL;
   void (*put)( protocol_base_t *p_indexable, Type value, int32_t index ) = NULL;
   
   int32_t i = 0;
   int32_t n = 0;
   int32_t new_n = 0;

   // get direct pointer to item, put functions
   item = P_Indexable_item_f( Prefix )( p_indexable );
   put = P_Indexable_put_f( Prefix )( p_indexable );
   
   n = P_Indexable_count( Prefix )( p_indexable );
   
   // continue until p_indexable is sorted
   while ( n != 0 )
   {
      new_n = 0;
      
      // walk through remaining unsorted items
      for( i=1; i<n; i++ )
      {
         // compare sequential items
         if ( func( item( p_indexable, i-1 ), item( p_indexable, i ) ) > 0 )
         {
            // if out of order, swap them
            temp = item( p_indexable, i-1 ); 
            put( p_indexable, item( p_indexable, i ), i-1 ); 
            put( p_indexable, temp, i );
            
            // set new_n as we had to swap at i
            new_n = i;
         }
      }
      
      // we can shorten the next walk because items past new_n are in order
      n = new_n;
   }   
   
   return;
}

/**
   BSorter_make
*/

BSorter_type( Prefix ) *
BSorter_make( Prefix )( void )
{
   // allocate bsorter struct
   BSorter_type( Prefix ) * bsorter
      = ( BSorter_type( Prefix ) * ) calloc( 1, sizeof( BSorter_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( bsorter );

   // set type code
   (*bsorter).type = BSORTER_TYPE;
   
   (*bsorter).func = SORT_FUNCTION_NAME;
   
   MULTITHREAD_MUTEX_INIT( (*bsorter).mutex );

   INVARIANT( bsorter );

   return bsorter;
}

/**
   BSorter_dispose
*/

void
BSorter_dispose( Prefix )( BSorter_type( Prefix ) *bsorter )
{
   PRECONDITION( "bsorter not null", bsorter != NULL ); 
   PRECONDITION( "bsorter type OK", (*bsorter).type == BSORTER_TYPE );
   LOCK( (*bsorter).mutex );
   INVARIANT( bsorter );

   MULTITHREAD_MUTEX_DESTROY( (*bsorter).mutex );

   // delete bsorter struct
   free( bsorter );

   return;
}

/**
   BSorter_sort_predefined_comparison_function
*/

void
BSorter_sort_predefined_comparison_function( Prefix )
(
   BSorter_type( Prefix ) *bsorter,
   protocol_base_t *p_indexable
)
{
   PRECONDITION( "bsorter not null", bsorter != NULL );
   PRECONDITION( "bsorter type OK", (*bsorter).type == BSORTER_TYPE );
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE ) == 1 );
   LOCK( (*bsorter).mutex );
   INVARIANT( bsorter );

   sort( p_indexable, (*bsorter).func );

   INVARIANT( bsorter );
   UNLOCK( (*bsorter).mutex );
   
   return;
}

/**
   BSorter_sort
*/

void
BSorter_sort( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
)
{
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE ) == 1 );

   sort( p_indexable, func );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */




