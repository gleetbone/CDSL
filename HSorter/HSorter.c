/**
 @file HSorter.c
 @author Greg Lee
 @version 2.0.0
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

#include "HSorter.h"

#include "protocol.h"

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_Indexable.h"
#include "P_Indexable.ph"
#include "P_Sorter.ph"
#endif // PROTOCOLS_ENABLED   

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

/**
   HSorter structure
*/

struct HSorter_struct( Prefix )
{

   PROTOCOLS_DEFINITION;

   int32_t _type;

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
   assert( ( ( void ) "struct ok count", struct_ok( p ) ) );
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
   Protocol stuff
*/

#ifdef PROTOCOLS_ENABLED

/**
   basic protocol function array
*/

static
void *
p_basic_table[P_BASIC_FUNCTION_COUNT]
=
{
   HSorter_dispose( Prefix ),
   HSorter_deep_dispose( Prefix ),
   HSorter_is_equal( Prefix ),
   HSorter_is_deep_equal( Prefix ),
   HSorter_copy( Prefix ),
   HSorter_deep_copy( Prefix ),
   HSorter_clone( Prefix ),
   HSorter_deep_clone( Prefix )
};

/**
   sorter protocol function array
*/

static
void *
p_sorter_table[P_SORTER_FUNCTION_COUNT]
=
{
   HSorter_sort_predefined_comparison_function( Prefix ),
   HSorter_is_sorted_predefined_comparison_function( Prefix )
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

   switch ( protocol_id )
   {
      case P_BASIC_TYPE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_BASIC_FUNCTION_MAX ) )
         {
            result = p_basic_table[ function_id ];
         }
         break;
      }

      case P_SORTER_TYPE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_SORTER_FUNCTION_MAX ) )
         {
            result = p_sorter_table[ function_id ];
         }
         break;
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

   switch ( protocol_id )
   {
      case P_BASIC_TYPE:
      {
         result = 1;
         break;
      }

      case P_SORTER_TYPE:
      {
         result = 1;
         break;
      }
   }

   return result;
}

#endif // PROTOCOLS_ENABLED

/**
   Includes
*/

#include <stddef.h>

static
int32_t
parent_index( int32_t index )
{
   return ( ( int32_t ) floor( ( index - 1 ) / 2 ) );
}

static
int32_t
left_child_index( int32_t index )
{
   return ( 2 * index + 1 );
}

/**
   sift_down

   Repair/reset/sort the heap tree from start to end

   @param p_indexable the data to be sorter
   @param func the comparison function
   @param start the index to start
   @param end the index to stop
   @param item function to access the data by index
   @param put function to put item by index into the data
*/

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
   while( left_child_index( root_index ) <= end )
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

/**
   make heap

   build up the heap tree to sort the data

   @param p_indexable the data to sort
   @param func the comparison function
   @param item function to access an item in the data
   @param put function to place item into the data
*/

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
   start = parent_index( n - 1 );

   // move each item to its proper location in the heap
   while( start >= 0 )
   {
      sift_down( p_indexable, func, start, n - 1, item, put );
      start = start - 1;
   }

   return;
}

/**
   sort

   sort the input data

   @param p_indexable the data to sort
   @param func the comparison function
*/
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
   item = P_Indexable_item( Prefix );
   put = P_Indexable_put( Prefix );

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
   is_sorted

   returns 1 if the data is sorted according to comparison function
   @param p_indexable the data
   @param func the comparison function
   @return 1 if data is sorted, 0 otherwise
*/

static
int32_t
is_sorted
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
)
{
   Type (*item)( protocol_base_t *p_indexable, int32_t index ) = NULL;

   int32_t i = 0;
   int32_t n = 0;
   int32_t result  = 1;

   // get direct pointer to item function
   item = ( *p_indexable ).get_function( P_INDEXABLE_TYPE, P_INDEXABLE_ITEM );

   n = P_Indexable_count( Prefix )( p_indexable );

   for ( i = 1; i < n; i++ )
   {
      // compare sequential items - if out of order, stop and return 0
      if ( func( item( p_indexable, i - 1 ), item( p_indexable, i ) ) > 0 )
      {
         result = 0;
         break;
      }
   }

   return result;
}

/**
   HSorter_make
*/

HSorter_type( Prefix ) *
HSorter_make( Prefix )( void )
{
   // allocate result struct
   HSorter_type( Prefix ) * result
      = ( HSorter_type( Prefix ) * ) calloc( 1, sizeof( HSorter_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = HSORTER_TYPE;

   (*result).func = SORT_FUNCTION_NAME;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   HSorter_clone
*/

HSorter_type( Prefix ) *
HSorter_clone( Prefix )( HSorter_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == HSORTER_TYPE );
   LOCK( (*other).mutex );
   INVARIANT( other );

   // allocate other struct
   HSorter_type( Prefix ) * current
      = ( HSorter_type( Prefix ) * ) calloc( 1, sizeof( HSorter_type( Prefix ) ) );
   CHECK( "current allocated correctly", current != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = HSORTER_TYPE;

   (*current).func = (*other).func;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return current;
}

/**
   HSorter_deep_clone
*/

HSorter_type( Prefix ) *
HSorter_deep_clone( Prefix )( HSorter_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == HSORTER_TYPE );
   LOCK( (*other).mutex );
   INVARIANT( other );

   // allocate other struct
   HSorter_type( Prefix ) * current
      = ( HSorter_type( Prefix ) * ) calloc( 1, sizeof( HSorter_type( Prefix ) ) );
   CHECK( "current allocated correctly", current != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = HSORTER_TYPE;

   (*current).func = (*other).func;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return current;
}

/**
   HSorter_is_equal
*/

int32_t
HSorter_is_equal( Prefix )( HSorter_type( Prefix ) *current, HSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == HSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == HSORTER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else if ( (*current).func == (*other).func )
   {
      LOCK( (*other).mutex );
      result = 1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return result;
}

/**
   HSorter_is_deep_equal
*/

int32_t
HSorter_is_deep_equal( Prefix )( HSorter_type( Prefix ) *current, HSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == HSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == HSORTER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else if ( (*current).func == (*other).func )
   {
      LOCK( (*other).mutex );
      result = 1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return result;
}

/**
   HSorter_copy
*/

void
HSorter_copy( Prefix )( HSorter_type( Prefix ) *current, HSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == HSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == HSORTER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   if ( current != other )
   {
      LOCK( (*other).mutex );
      (*current).func = (*other).func;
      UNLOCK( (*other).mutex );
      INVARIANT( current );
   }

   UNLOCK( (*current).mutex );

   return;
}

/**
   HSorter_deep_copy
*/

void
HSorter_deep_copy( Prefix )( HSorter_type( Prefix ) *current, HSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == HSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == HSORTER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   if ( current != other )
   {
      LOCK( (*other).mutex );
      (*current).func = (*other).func;
      UNLOCK( (*other).mutex );
      INVARIANT( current );
   }

   UNLOCK( (*current).mutex );

   return;
}

/**
   HSorter_dispose
*/

void
HSorter_dispose( Prefix )( HSorter_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == HSORTER_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to null
   *current = NULL;

   return;
}

/**
   HSorter_deep_dispose
*/

void
HSorter_deep_dispose( Prefix )( HSorter_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == HSORTER_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to null
   *current = NULL;

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
   PRECONDITION( "hsorter type OK", (*hsorter)._type == HSORTER_TYPE );
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );
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
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );

   sort( p_indexable, func );

   return;
}

/**
   HSorter_is_sorted_predefined_comparison_function
*/

int32_t
HSorter_is_sorted_predefined_comparison_function( Prefix )
(
   HSorter_type( Prefix ) *hsorter,
   protocol_base_t *p_indexable
)
{
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );

   int32_t result = 0;

   result = is_sorted( p_indexable, (*hsorter).func );

   return result;
}

/**
   HSorter_is_sorted
*/

int32_t
HSorter_is_sorted( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
)
{
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );

   int32_t result = 0;

   result = is_sorted( p_indexable, func );

   return result;
}

/* End of file */




