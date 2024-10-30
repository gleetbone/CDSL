/**
 @file SelSorter.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Selection Sorter"

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

 Function definitions for the opaque SelSorter_t type.

*/

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_Indexable.ph"
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
   SelSorter structure
*/

struct SelSorter_struct( Prefix )
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
struct_ok( SelSorter_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).func != NULL );

   return result;
}

static
void invariant( SelSorter_type( Prefix ) *p )
{
   assert( ( ( void ) "struct ok count", struct_ok( p ) ) );
   return;
}

#else // INVARIANT_CONDITIONAL

static
void invariant( p )
{
   return;
}

#endif // INVARIANT_CONDITIONAL

#ifdef PROTOCOLS_ENABLED

/**
   basic protocol function array
*/

static
void *
p_basic_table[P_BASIC_FUNCTION_COUNT]
=
{
   SelSorter_dispose( Prefix ),
   SelSorter_deep_dispose( Prefix ),
   SelSorter_is_equal( Prefix ),
   SelSorter_is_deep_equal( Prefix ),
   SelSorter_copy( Prefix ),
   SelSorter_deep_copy( Prefix ),
   SelSorter_clone( Prefix ),
   SelSorter_deep_clone( Prefix )
};


/**
   sorter protocol function array
*/

static
void *
p_sorter_table[P_SORTER_FUNCTION_COUNT]
=
{
   SelSorter_sort_predefined_comparison_function( Prefix ),
   SelSorter_is_sorted_predefined_comparison_function( Prefix )
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
   Includes
*/

#include <stddef.h>
#include <stdlib.h>

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
   Type temp;
   Type (*item)( protocol_base_t *p_indexable, int32_t index ) = NULL;
   void (*put)( protocol_base_t *p_indexable, Type value, int32_t index ) = NULL;

   int32_t i = 0;
   int32_t i_min = 0;
   int32_t j = 0;
   int32_t n = 0;

   // get direct pointer to item, put functions
   item = P_Indexable_item( Prefix );
   put = P_Indexable_put( Prefix );

   n = P_Indexable_count( Prefix )( p_indexable );
   i = 1;

   // walk through items
   for ( j = 0; j < n - 1; j++ )
   {
      i_min = j;

      // walk through unsorted items, find index of "smallest" item
      for( i = j + 1; i < n; i++ )
      {
         if ( func( item( p_indexable, i ), item( p_indexable, i_min ) ) < 0 )
         {
            i_min = i;
         }
      }

      // if "smallest" item is out of order, swap it to put it in order
      if ( i_min != j )
      {
         temp = item( p_indexable, j );
         put( p_indexable, item( p_indexable, i_min ), j );
         put( p_indexable, temp, i_min );
      }

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
   SelSorter_make
*/

SelSorter_type( Prefix ) *
SelSorter_make( Prefix )( void )
{
   // allocate result struct
   SelSorter_type( Prefix ) * result
      = ( SelSorter_type( Prefix ) * ) calloc( 1, sizeof( SelSorter_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type code
   (*result)._type = SELSORTER_TYPE;

   (*result).func = SORT_FUNCTION_NAME;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   SelSorter_clone
*/

SelSorter_type( Prefix ) *
SelSorter_clone( Prefix )( SelSorter_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == SELSORTER_TYPE );
   LOCK( (*other).mutex );
   INVARIANT( other );

   // allocate other struct
   SelSorter_type( Prefix ) * current
      = ( SelSorter_type( Prefix ) * ) calloc( 1, sizeof( SelSorter_type( Prefix ) ) );
   CHECK( "current allocated correctly", current != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = SELSORTER_TYPE;

   (*current).func = (*other).func;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return current;
}

/**
   SelSorter_deep_clone
*/

SelSorter_type( Prefix ) *
SelSorter_deep_clone( Prefix )( SelSorter_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == SELSORTER_TYPE );
   LOCK( (*other).mutex );
   INVARIANT( other );

   // allocate other struct
   SelSorter_type( Prefix ) * current
      = ( SelSorter_type( Prefix ) * ) calloc( 1, sizeof( SelSorter_type( Prefix ) ) );
   CHECK( "current allocated correctly", current != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = SELSORTER_TYPE;

   (*current).func = (*other).func;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return current;
}

/**
   SelSorter_is_equal
*/

int32_t
SelSorter_is_equal( Prefix )( SelSorter_type( Prefix ) *current, SelSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == SELSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == SELSORTER_TYPE );
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
   SelSorter_is_deep_equal
*/

int32_t
SelSorter_is_deep_equal( Prefix )( SelSorter_type( Prefix ) *current, SelSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == SELSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == SELSORTER_TYPE );
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
   SelSorter_copy
*/

void
SelSorter_copy( Prefix )( SelSorter_type( Prefix ) *current, SelSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == SELSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == SELSORTER_TYPE );
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
   SelSorter_deep_copy
*/

void
SelSorter_deep_copy( Prefix )( SelSorter_type( Prefix ) *current, SelSorter_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == SELSORTER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == SELSORTER_TYPE );
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
   SelSorter_dispose
*/

void
SelSorter_dispose( Prefix )( SelSorter_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == SELSORTER_TYPE );
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
   SelSorter_deep_dispose
*/

void
SelSorter_deep_dispose( Prefix )( SelSorter_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == SELSORTER_TYPE );
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
   SelSorter_sort_predefined_comparison_function
*/

void
SelSorter_sort_predefined_comparison_function( Prefix )
(
   SelSorter_type( Prefix ) *selsorter,
   protocol_base_t *p_indexable
)
{
   PRECONDITION( "selsorter not null", selsorter != NULL );
   PRECONDITION( "selsorter type OK", (*selsorter)._type == SELSORTER_TYPE );
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );
   LOCK( (*selsorter).mutex );
   INVARIANT( selsorter );

   sort( p_indexable, (*selsorter).func );

   INVARIANT( selsorter );
   UNLOCK( (*selsorter).mutex );

   return;
}

/**
   SelSorter_sort
*/

void
SelSorter_sort( Prefix )
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
   SelSorter_is_sorted_predefined_comparison_function
*/

int32_t
SelSorter_is_sorted_predefined_comparison_function( Prefix )
(
   SelSorter_type( Prefix ) *current,
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
   SelSorter_is_sorted
*/

int32_t
SelSorter_is_sorted( Prefix )
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




