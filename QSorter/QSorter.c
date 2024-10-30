/**
 @file QSorter.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Quick Sorter"

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

 Function definitions for the opaque QSorter_t type.

*/

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_Indexable.ph"
#include "P_Sorter.ph"
#endif // PROTOCOLS_ENABLED   

#include "P_Indexable.h"

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

/**
   Includes
*/

#include <stddef.h>
#include <stdlib.h>

/**
   QSorter structure
*/

struct QSorter_struct( Prefix )
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
struct_ok( QSorter_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).func != NULL );

   return result;
}

static
void invariant( QSorter_type( Prefix ) *p )
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
   QSorter_dispose( &Prefix ),
   QSorter_deep_dispose( &Prefix ),
   QSorter_is_equal( Prefix ),
   QSorter_is_deep_equal( Prefix ),
   QSorter_copy( Prefix ),
   QSorter_deep_copy( Prefix ),
   QSorter_clone( Prefix ),
   QSorter_deep_clone( Prefix )
};

/**
   sorter protocol function array
*/

static
void *
p_sorter_table[P_SORTER_FUNCTION_COUNT]
=
{
   QSorter_sort_predefined_comparison_function( Prefix ),
   QSorter_is_sorted_predefined_comparison_function( Prefix )
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
         if ( ( function_id >= 0 ) & ( function_id <= P_BASIC_FUNCTION_MAX ) )
         {
            result = p_basic_table[ function_id ];
         }
         break;
      }

      case P_SORTER_TYPE:
      {
         if ( ( function_id >= 0 ) & ( function_id <= P_SORTER_FUNCTION_MAX ) )
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
   sort

   performs a quicksort on the data in p_indexable using the func comparison function.

   @param p_indexable the input data to sort
   @param func the comparison function
   @param start the index of the start of the data in p_indexable
   @param stop the index of the end of the data in p_indexable
*/
static
void
sort
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b ),
   int32_t start,
   int32_t stop
)
{
   Type pivot;
   Type temp;
   Type (*item)( protocol_base_t *p_indexable, int32_t index ) = NULL;
   void (*put)( protocol_base_t *p_indexable, Type value, int32_t index ) = NULL;

   int32_t left = 0;
   int32_t right = 0;
   int32_t p = 0;

   // get direct pointer to item, put functions
   item = ( *p_indexable ).get_function( P_INDEXABLE_TYPE, P_INDEXABLE_ITEM );
   put = ( *p_indexable ).get_function( P_INDEXABLE_TYPE, P_INDEXABLE_PUT );

   while ( start < stop )
   {
      left = start;
      p = start + ( stop - start ) / 2;
      right = stop;

      pivot = item( p_indexable, p );

      while ( 1 )
      {
         while (
            ( left <= right )
            &&
            ( func( item( p_indexable, left ), pivot ) <= 0 )
         )
         {
            left++;
         }

         while (
            ( left <= right )
            &&
            ( func( item( p_indexable, right ), pivot )  > 0 )
         )
         {
            right--;
         }

         if ( left > right )
         {
            break;
         }

         temp = item( p_indexable, left );
         put( p_indexable, item( p_indexable, right ), left );
         put( p_indexable, temp, right );

         if ( p == right )
         {
            p = left;
         }

         left++;
         right--;
      }

      put( p_indexable, item( p_indexable, right ), p );
      put( p_indexable, pivot, right );
      right--;

      // Recursion on the shorter side & loop (with new indexes) on the longer
      if ( ( right - start ) < ( stop - left ) )
      {
         sort( p_indexable, func, start, right );
         start = left;
      }
      else
      {
         sort( p_indexable, func, left, stop );
         stop = right;
      }
   }

   return;
}

/**
   is_sorted

   returns 1 if the data is sorted according to comparison function
   @param p_indexable the data
   @param func the comparison function
   @param start the index of the start of the data in p_indexable
   @param stop the index of the end of the data in p_indexable
   @return 1 if data is sorted, 0 otherwise
*/

static
int32_t
is_sorted
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b ),
   int32_t start,
   int32_t stop
)
{
   int32_t result = 1;
   int32_t i = 0;
   Type x;
   Type y;
   Type (*item)( protocol_base_t *p_indexable, int32_t index ) = NULL;

   // get direct pointer to item function
   item = ( *p_indexable ).get_function( P_INDEXABLE_TYPE, P_INDEXABLE_ITEM );

   x = item( p_indexable, start );

   for ( i = start; i < stop; i++ )
   {
      y = item( p_indexable, i + 1 );
      if ( func( x, y ) > 0 )
      {
         result = 0;
         break;
      }
      x = y;
   }

   return result;
}

/**
   QSorter_make
*/

QSorter_type( Prefix ) *
QSorter_make( Prefix )( void )
{
   // allocate result struct
   QSorter_type( Prefix ) * result
      = ( QSorter_type( Prefix ) * ) calloc( 1, sizeof( QSorter_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type code
   (*result)._type = QSORTER_TYPE;

   (*result).func = SORT_FUNCTION_NAME;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   QSorter_clone
*/

QSorter_type( Prefix ) *
QSorter_clone( Prefix )( QSorter_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == QSORTER_TYPE );
   LOCK( (*other).mutex );
   INVARIANT( other );

   // allocate other struct
   QSorter_type( Prefix ) * current
      = ( QSorter_type( Prefix ) * ) calloc( 1, sizeof( QSorter_type( Prefix ) ) );
   CHECK( "current allocated correctly", current != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = QSORTER_TYPE;

   (*current).func = (*other).func;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return current;
}

/**
   QSorter_deep_clone
*/

QSorter_type( Prefix ) *
QSorter_deep_clone( Prefix )( QSorter_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == QSORTER_TYPE );
   LOCK( (*other).mutex );
   INVARIANT( other );

   // allocate other struct
   QSorter_type( Prefix ) * current
      = ( QSorter_type( Prefix ) * ) calloc( 1, sizeof( QSorter_type( Prefix ) ) );
   CHECK( "current allocated correctly", current != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = QSORTER_TYPE;

   (*current).func = (*other).func;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return current;
}

/**
   QSorter_is_equal
*/

int32_t
QSorter_is_equal( Prefix )( QSorter_type( Prefix ) *current, QSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == QSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == QSORTER_TYPE );
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
   QSorter_is_deep_equal
*/

int32_t
QSorter_is_deep_equal( Prefix )( QSorter_type( Prefix ) *current, QSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == QSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == QSORTER_TYPE );
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
   QSorter_copy
*/

void
QSorter_copy( Prefix )( QSorter_type( Prefix ) *current, QSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == QSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == QSORTER_TYPE );
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
   QSorter_deep_copy
*/

void
QSorter_deep_copy( Prefix )( QSorter_type( Prefix ) *current, QSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == QSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == QSORTER_TYPE );
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
   QSorter_dispose
*/

void
QSorter_dispose( Prefix )( QSorter_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == QSORTER_TYPE );
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
   QSorter_deep_dispose
*/

void
QSorter_deep_dispose( Prefix )( QSorter_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == QSORTER_TYPE );
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
   QSorter_sort_predefined_comparison_function
*/

void
QSorter_sort_predefined_comparison_function( Prefix )
(
   QSorter_type( Prefix ) *qsorter,
   protocol_base_t *p_indexable
)
{
   PRECONDITION( "qsorter not null", qsorter != NULL );
   PRECONDITION( "qsorter type OK", (*qsorter)._type == QSORTER_TYPE );
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );
   LOCK( (*qsorter).mutex );
   INVARIANT( qsorter );

   int32_t start = 0;
   int32_t stop = 0;

   start = 0;
   stop = P_Indexable_count( Prefix )( p_indexable ) - 1;

   sort( p_indexable, (*qsorter).func, start, stop );

   INVARIANT( qsorter );
   UNLOCK( (*qsorter).mutex );

   return;
}

/**
   QSorter_sort
*/

void
QSorter_sort( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
)
{
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );

   int32_t start = 0;
   int32_t stop = 0;

   start = 0;
   stop = P_Indexable_count( Prefix )( p_indexable ) - 1;

   sort( p_indexable, func, start, stop );

   return;
}

/**
   QSorter_is_sorted_predefined_comparison_function
*/

int32_t
QSorter_is_sorted_predefined_comparison_function( Prefix )
(
   QSorter_type( Prefix ) *current,
   protocol_base_t *p_indexable
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == QSORTER_TYPE );
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t start = 0;
   int32_t stop = 0;

   start = 0;
   stop = P_Indexable_count( Prefix )( p_indexable ) - 1;

   result = is_sorted( p_indexable, (*current).func, start, stop );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   QSorter_is_sorted
*/

int32_t
QSorter_is_sorted( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b )
)
{
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );

   int32_t result = 0;
   int32_t start = 0;
   int32_t stop = 0;

   start = 0;
   stop = P_Indexable_count( Prefix )( p_indexable ) - 1;

   result = is_sorted( p_indexable, func, start, stop );

   return result;
}

/* End of file */




