/**
 @file MSorter.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Merge Sorter"

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

 Function definitions for the opaque MSorter_t type.

*/

#include "MSorter.h"

/**
   Includes
*/

#include <stddef.h>
#include <stdlib.h>

#include <math.h>

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Indexable.ph"
#include "P_Basic.ph"
#include "P_Sorter.ph"
#endif // PROTOCOLS_ENABLED   

#include "P_Basic.h"
#include "P_Indexable.h"

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

/**
   MSorter structure
*/

struct MSorter_struct( Prefix )
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
struct_ok( MSorter_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).func != NULL );

   return result;
}

static
void invariant( MSorter_type( Prefix ) *p )
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

#ifdef PROTOCOLS_ENABLED

/**
   basic protocol function array
*/

static
void *
p_basic_table[P_BASIC_FUNCTION_COUNT]
=
{
   MSorter_dispose( Prefix ),
   MSorter_deep_dispose( Prefix ),
   MSorter_is_equal( Prefix ),
   MSorter_is_deep_equal( Prefix ),
   MSorter_copy( Prefix ),
   MSorter_deep_copy( Prefix ),
   MSorter_clone( Prefix ),
   MSorter_deep_clone( Prefix )
};

/**
   sorter protocol function array
*/

static
void *
p_sorter_table[P_SORTER_FUNCTION_COUNT]
=
{
   MSorter_sort_predefined_comparison_function( Prefix ),
   MSorter_is_sorted_predefined_comparison_function( Prefix )

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
      }

   }

   return result;
}

#endif // PROTOCOLS_ENABLED   


/**
   merge

   merge two sorted arrays of data into a single sorted array

   @param p_indexable holds two input sorted data arrays in sequence
   @param p_indexable1 the result sorted data array
   @param func the comparison function
   @param item the function to get an item from a p_indexable
   @param put the function to put an item into a p_indexable
   @param i_start the index of the first input data array
   @param i_middle the index of the start of the second input array
   @param i_end the last item in the second input array
*/
static
void
merge
(
   protocol_base_t *p_indexable,
   protocol_base_t *p_indexable1,
   int32_t (*func)( Type a, Type b ),
   Type (*item)( protocol_base_t *p_indexable, int32_t index ),
   void (*put)( protocol_base_t *p_indexable, Type value, int32_t index ),
   int32_t i_start,
   int32_t i_middle,
   int32_t i_end
)
{
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;

   i = i_start;
   j = i_middle;

   for( k = i_start; k < i_end; k++ )
   {

      if ( ( i < i_middle ) && ( ( j >= i_end ) || ( func( item( p_indexable, i ), item( p_indexable, j ) ) <= 0 ) ) )
      {
         put( p_indexable1, item( p_indexable, i ), k );
         i = i + 1;
      }
      else
      {
         put( p_indexable1, item( p_indexable, j ), k );
         j = j + 1;
      }
   }

   return;
}

/**
   split_merge

   recursively split the input data array into smaller and smaller data arrays
   and the merge them back together into a softed array

   @param p_indexable1 working data array, holds split array, starts as clone of p_indexable
   @param p_indexable input data array
   @param func the comparison function
   @param item the function to get an item from a p_indexable
   @param put the function to put an item into a p_indexable
   @param i_start the index of the data array
   @param i_end the last item of the data array
*/
static
void
split_merge
(
   protocol_base_t *p_indexable1,
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b ),
   Type (*item)( protocol_base_t *p_indexable, int32_t index ),
   void (*put)( protocol_base_t *p_indexable, Type value, int32_t index ),
   int32_t i_start,
   int32_t i_end
)
{
   int32_t i_middle = 0;

   // only sort if working with more than 1 item
   if ( ( i_end - i_start ) >= 2 )
   {
      // get index for split
      i_middle = ( int32_t ) ( ( i_end + i_start ) / 2 );

      // recursively sort both split halves into p_indexable1
      split_merge( p_indexable, p_indexable1, func, item, put, i_start, i_middle );
      split_merge( p_indexable, p_indexable1, func, item, put, i_middle, i_end );

      // merge the splits in p_indexable1 back into p_indexable
      merge( p_indexable1, p_indexable, func, item, put, i_start, i_middle, i_end );
   }

   return;
}

#define Base_Prefix p

/**
   sort

   sort the input data array using the func comparison function

   @param p_indexable the input data array
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
   Type (*item)( protocol_base_t *p_indexable, int32_t index ) = NULL;
   void (*put)( protocol_base_t *p_indexable, Type value, int32_t index ) = NULL;

   int32_t n = 0;

   // get direct pointer to item, put functions
   item = P_Indexable_item( Prefix );
   put = P_Indexable_put( Prefix );

   // get size of indexable
   n = P_Indexable_count( Prefix )( p_indexable );

   // make second indexable for temp buffer
   protocol_base_t *p_indexable1 = ( P_Basic_clone( Prefix ) )( p_indexable );

   // sort the indexable
   split_merge( p_indexable1, p_indexable, func, item, put, 0, n );

   // dispose of temp buffer
   ( P_Basic_dispose( Prefix ) )( &p_indexable1 );

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
   MSorter_make
*/

MSorter_type( Prefix ) *
MSorter_make( Prefix )( void )
{
   // allocate result struct
   MSorter_type( Prefix ) * result
      = ( MSorter_type( Prefix ) * ) calloc( 1, sizeof( MSorter_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type code
   (*result)._type = MSORTER_TYPE;

   (*result).func = SORT_FUNCTION_NAME;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   MSorter_clone
*/

MSorter_type( Prefix ) *
MSorter_clone( Prefix )( MSorter_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == MSORTER_TYPE );
   LOCK( (*other).mutex );
   INVARIANT( other );

   // allocate other struct
   MSorter_type( Prefix ) * current
      = ( MSorter_type( Prefix ) * ) calloc( 1, sizeof( MSorter_type( Prefix ) ) );
   CHECK( "current allocated correctly", current != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = MSORTER_TYPE;

   (*current).func = (*other).func;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return current;
}

/**
   MSorter_deep_clone
*/

MSorter_type( Prefix ) *
MSorter_deep_clone( Prefix )( MSorter_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == MSORTER_TYPE );
   LOCK( (*other).mutex );
   INVARIANT( other );

   // allocate other struct
   MSorter_type( Prefix ) * current
      = ( MSorter_type( Prefix ) * ) calloc( 1, sizeof( MSorter_type( Prefix ) ) );
   CHECK( "current allocated correctly", current != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = MSORTER_TYPE;

   (*current).func = (*other).func;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return current;
}

/**
   MSorter_is_equal
*/

int32_t
MSorter_is_equal( Prefix )( MSorter_type( Prefix ) *current, MSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == MSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == MSORTER_TYPE );
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
   MSorter_is_deep_equal
*/

int32_t
MSorter_is_deep_equal( Prefix )( MSorter_type( Prefix ) *current, MSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == MSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == MSORTER_TYPE );
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
   MSorter_copy
*/

void
MSorter_copy( Prefix )( MSorter_type( Prefix ) *current, MSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == MSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == MSORTER_TYPE );
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
   MSorter_deep_copy
*/

void
MSorter_deep_copy( Prefix )( MSorter_type( Prefix ) *current, MSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == MSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == MSORTER_TYPE );
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
   MSorter_dispose
*/

void
MSorter_dispose( Prefix )( MSorter_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == MSORTER_TYPE );
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
   MSorter_deep_dispose
*/

void
MSorter_deep_dispose( Prefix )( MSorter_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == MSORTER_TYPE );
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
   MSorter_sort_predefined_comparison_function
*/

void
MSorter_sort_predefined_comparison_function( Prefix )
(
   MSorter_type( Prefix ) *msorter,
   protocol_base_t *p_indexable
)
{
   PRECONDITION( "msorter not null", msorter != NULL );
   PRECONDITION( "msorter type OK", (*msorter)._type == MSORTER_TYPE );
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );
   PRECONDITION( "p_indexable supports basic protocol", protocol_base_supports_protocol( p_indexable, P_BASIC_TYPE ) == 1 );
   LOCK( (*msorter).mutex );
   INVARIANT( msorter );

   sort( p_indexable, (*msorter).func );

   INVARIANT( msorter );
   UNLOCK( (*msorter).mutex );

   return;
}

/**
   MSorter_sort
*/

void
MSorter_sort( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
)
{
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );
   PRECONDITION( "p_indexable supports basic protocol", protocol_base_supports_protocol( p_indexable, P_BASIC_TYPE ) == 1 );

   sort( p_indexable, func );

   return;
}

/**
   MSorter_is_sorted_predefined_comparison_function
*/

int32_t
MSorter_is_sorted_predefined_comparison_function( Prefix )
(
   MSorter_type( Prefix ) *current,
   protocol_base_t *p_indexable
)
{
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );

   int32_t result = 0;

   result = is_sorted( p_indexable, (*current).func );

   return result;
}

/**
   MSorter_is_sorted
*/

int32_t
MSorter_is_sorted( Prefix )
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




