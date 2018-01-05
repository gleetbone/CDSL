/**
 @file HSorter.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Heap Sorter"
 
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

 Function definitions for the opaque HSorter_t type.

*/
#include <stdlib.h>
#include <math.h>

#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Indexable.h"
#include "P_Indexable.ph"
#include "P_Sorter.ph"
   
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

#define HSORTER_TYPE 0xA5000205

/**
   HSorter structure
*/

struct HSorter_struct( Prefix )
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
struct_ok( HSorter_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).func != NULL );

   return result;
}

static
void invariant( HSorter_type( Prefix ) *p )
{
   assert(( (void) "struct ok count", struct_ok( p ) ));
   return;
}

#else

static
void invariant( p )
{
   return;
}

#endif

/**
   sorter protocol function array
*/

static
void *
p_sorter_table[P_SORTER_FUNCTION_COUNT]
=
{
   HSorter_dispose( Prefix ),
   HSorter_sort_predefined_comparison_function( Prefix )
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


/**
   Includes
*/

#include <stddef.h>

static
int32_t
parent_index( int32_t index )
{
   return ( ( int32_t ) floor( (index-1)/2 ) );
}

static
int32_t
left_child_index( int32_t index )
{
   return ( 2*index + 1 );
}

static
void
sift_down
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b ),
   int32_t start,
   int32_t end,
   Type (*item)( protocol_base_t *p_indexable, int32_t index ),
   void (*put)( protocol_base_t *p_indexable, Type value, int32_t index )
)
{
   Type temp;
   
   int32_t root_index = 0;
   int32_t swap_index = 0;
   int32_t child_index = 0;
   
   root_index = start;
   
   // "repair" the heap at root_index
   
   // continue while heap at root_index has a child
   while( left_child_index(root_index) <= end )
   {
      child_index = left_child_index( root_index );
      swap_index = root_index;
      
      // update the swap_index if left child is out of order
      if ( func( item( p_indexable, swap_index ), item( p_indexable, child_index ) ) < 0 )
      {
         swap_index = child_index; 
      }
      
      // update swap index if right child exists and is out of order
      if ( ( child_index + 1 <= end ) && ( func( item( p_indexable, swap_index ), item( p_indexable, child_index + 1 ) ) < 0 ) )
      {
         swap_index = child_index + 1; 
      }
      
      // if both left and right children are in order
      if ( swap_index == root_index )
      {
         // we're done
         break;
      }
      else
      {
         // else, swap items at root_index and swap_index 
         temp = item( p_indexable, root_index ); 
         put( p_indexable, item( p_indexable, swap_index ), root_index ); 
         put( p_indexable, temp, swap_index );
         root_index = swap_index;
      }
      
   }
   
   return;
}

static
void
make_heap
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b ),
   Type (*item)( protocol_base_t *p_indexable, int32_t index ),
   void (*put)( protocol_base_t *p_indexable, Type value, int32_t index )
)
{
   int32_t start = 0;
   int32_t n = 0;
   
   // get count
   n = P_Indexable_count( Prefix )( p_indexable );
   
   // start at end of array/heap 
   start = parent_index( n-1 );
   
   // move each item to its proper location in the heap
   while( start >= 0 )
   {
      sift_down( p_indexable, func, start, n - 1, item, put );
      start = start - 1;
   }
   
   return;
}

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
 
   int32_t n = 0;
   int32_t end = 0;

   // get direct pointer to item, put functions
   item = P_Indexable_item_f( Prefix )( p_indexable );
   put = P_Indexable_put_f( Prefix )( p_indexable );
   
   // get size of indexable
   n = P_Indexable_count( Prefix )( p_indexable );

   // make the indexable into a heap
   make_heap( p_indexable, func, item, put );
      
   // construct the sorted indexable from the heap
   end = n - 1;
   while( end > 0 )
   {
      // put largest value at index 0
      temp = item( p_indexable, 0 ); 
      put( p_indexable, item( p_indexable, end ), 0 ); 
      put( p_indexable, temp, end );
      
      // update end
      end = end - 1;

      // restore heap 
      sift_down( p_indexable, func, 0, end, item, put );
   }
   
   return;
}

/**
   HSorter_make
*/

HSorter_type( Prefix ) *
HSorter_make( Prefix )( void )
{
   // allocate hsorter struct
   HSorter_type( Prefix ) * hsorter
      = ( HSorter_type( Prefix ) * ) calloc( 1, sizeof( HSorter_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( hsorter );

   // set type codes
   (*hsorter).type = HSORTER_TYPE;
   
   (*hsorter).func = SORT_FUNCTION_NAME;
   
   MULTITHREAD_MUTEX_INIT( (*hsorter).mutex );

   INVARIANT( hsorter );

   return hsorter;
}

/**
   HSorter_dispose
*/

void
HSorter_dispose( Prefix )( HSorter_type( Prefix ) *hsorter )
{
   PRECONDITION( "hsorter not null", hsorter != NULL );
   PRECONDITION( "hsorter type OK", (*hsorter).type == HSORTER_TYPE );
   LOCK( (*hsorter).mutex );
   INVARIANT( hsorter );

   MULTITHREAD_MUTEX_DESTROY( (*hsorter).mutex );

   // delete hsorter struct
   free( hsorter );

   return;
}

/**
   HSorter_sort_predefined_comparison_function
*/

void
HSorter_sort_predefined_comparison_function( Prefix )
(
   HSorter_type( Prefix ) *hsorter,
   protocol_base_t *p_indexable
)
{
   PRECONDITION( "hsorter not null", hsorter != NULL );
   PRECONDITION( "hsorter type OK", (*hsorter).type == HSORTER_TYPE );
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE ) == 1 );
   LOCK( (*hsorter).mutex );
   INVARIANT( hsorter );

   sort( p_indexable, (*hsorter).func );

   INVARIANT( hsorter );
   UNLOCK( (*hsorter).mutex );
   
   return;
}

/**
   HSorter_sort
*/

void
HSorter_sort( Prefix )
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

/* End of file */




