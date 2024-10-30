/**
 @file LSearcher.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Linear searcher"

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

 Function definitions for the opaque LSearcher_t type.

*/

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_Indexable.h"
#include "P_Indexable.ph"
#include "P_Searcher.ph"
#endif // PROTOCOLS_ENABLED   

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

/**
   LSearcher structure
*/

struct LSearcher_struct( Prefix )
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
struct_ok( LSearcher_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).func != NULL );

   return result;
}

static
void invariant( LSearcher_type( Prefix ) *p )
{
   assert( ( ( void ) "struct ok count", struct_ok( p ) ) );
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
   LSearcher_dispose( Prefix ),
   LSearcher_deep_dispose( Prefix ),
   LSearcher_is_equal( Prefix ),
   LSearcher_is_deep_equal( Prefix ),
   LSearcher_copy( Prefix ),
   LSearcher_deep_copy( Prefix ),
   LSearcher_clone( Prefix ),
   LSearcher_deep_clone( Prefix )
};

/**
   searcher protocol function array
*/

static
void *
p_searcher_table[P_SEARCHER_FUNCTION_COUNT]
=
{
   LSearcher_search_predefined_comparison_function( Prefix )
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

      case P_SEARCHER_TYPE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_SEARCHER_FUNCTION_MAX ) )
         {
            result = p_searcher_table[ function_id ];
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

      case P_SEARCHER_TYPE:
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
   search

   find the target in the p_indexable according to func

   @param p_indexable the array of values to search through
   @param func the comparison function
   @param target the value to search for
   @return 1 if found, - otherwise
*/
static
int32_t
search
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b ),
   Type target
)
{
   Type (*item)( protocol_base_t *p_indexable, int32_t index ) = NULL;

   int32_t result = -1;
   int32_t i = 0;
   int32_t n = 0;

   // get direct pointer to item, put functions
   item = P_Indexable_item( Prefix );

   n = P_Indexable_count( Prefix )( p_indexable );

   // continue until p_indexable is searched
   for ( i = 0; i < n; i++ )
   {
      // compare value to target
      if ( func( item( p_indexable, i ), target ) == 0 )
      {
         result = i;
         break;
      }
   }

   return result;
}

/**
   LSearcher_make
*/

LSearcher_type( Prefix ) *
LSearcher_make( Prefix )( void )
{
   // allocate lsearcher struct
   LSearcher_type( Prefix ) * result
      = ( LSearcher_type( Prefix ) * ) calloc( 1, sizeof( LSearcher_type( Prefix ) ) );
   CHECK( "result allocated_correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type code
   (*result)._type = LSEARCHER_TYPE;

   (*result).func = SEARCH_FUNCTION_NAME;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   LSearcher_clone
*/

LSearcher_type( Prefix ) *
LSearcher_clone( Prefix )( LSearcher_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == LSEARCHER_TYPE );
   LOCK( (*other).mutex );
   INVARIANT( other );

   // allocate other struct
   LSearcher_type( Prefix ) * current
      = ( LSearcher_type( Prefix ) * ) calloc( 1, sizeof( LSearcher_type( Prefix ) ) );
   CHECK( "current allocated correctly", current != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = LSEARCHER_TYPE;

   (*current).func = (*other).func;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return current;
}

/**
   LSearcher_deep_clone
*/

LSearcher_type( Prefix ) *
LSearcher_deep_clone( Prefix )( LSearcher_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == LSEARCHER_TYPE );
   LOCK( (*other).mutex );
   INVARIANT( other );

   // allocate other struct
   LSearcher_type( Prefix ) * current
      = ( LSearcher_type( Prefix ) * ) calloc( 1, sizeof( LSearcher_type( Prefix ) ) );
   CHECK( "current allocated correctly", current != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = LSEARCHER_TYPE;

   (*current).func = (*other).func;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return current;
}

/**
   LSearcher_is_equal
*/

int32_t
LSearcher_is_equal( Prefix )( LSearcher_type( Prefix ) *current, LSearcher_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == LSEARCHER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == LSEARCHER_TYPE );
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
   LSearcher_is_deep_equal
*/

int32_t
LSearcher_is_deep_equal( Prefix )( LSearcher_type( Prefix ) *current, LSearcher_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == LSEARCHER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == LSEARCHER_TYPE );
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
   LSearcher_copy
*/

void
LSearcher_copy( Prefix )( LSearcher_type( Prefix ) *current, LSearcher_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == LSEARCHER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == LSEARCHER_TYPE );
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
   LSearcher_deep_copy
*/

void
LSearcher_deep_copy( Prefix )( LSearcher_type( Prefix ) *current, LSearcher_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == LSEARCHER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == LSEARCHER_TYPE );
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
   LSearcher_dispose
*/

void
LSearcher_dispose( Prefix )( LSearcher_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == LSEARCHER_TYPE );
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
   LSearcher_deep_dispose
*/

void
LSearcher_deep_dispose( Prefix )( LSearcher_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == LSEARCHER_TYPE );
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
   LSearcher_search_predefined_comparison_function
*/

int32_t
LSearcher_search_predefined_comparison_function( Prefix )
(
   LSearcher_type( Prefix ) *current,
   protocol_base_t *p_indexable,
   Type target
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == LSEARCHER_TYPE );
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = search( p_indexable, (*current).func, target );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   LSearcher_search
*/

int32_t
LSearcher_search( Prefix )
(
   protocol_base_t *p_indexable,
   int32_t (*func)( Type a, Type b ),
   Type target
)
{
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE_TYPE ) == 1 );

   int32_t result = search( p_indexable, func, target );

   return result;
}

/* End of file */




