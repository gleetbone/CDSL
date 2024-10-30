/**
 @file BSearcher.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Binary Searcher"

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

 Function definitions for the opaque BSearcher_t type.

*/

#include "BSearcher.h"

#include "protocol.h"

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_Indexable.h"
#include "P_Indexable.ph"
#include "P_Searcher.ph"
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

/**
   BSearcher structure
*/

struct BSearcher_struct( Prefix )
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
struct_ok( BSearcher_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).func != NULL );

   return result;
}

static
void invariant( BSearcher_type( Prefix ) *p )
{
   assert( ( ( void ) "struct ok count", struct_ok( p ) ) );
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
   BSearcher_dispose( Prefix ),
   BSearcher_deep_dispose( Prefix ),
   BSearcher_is_equal( Prefix ),
   BSearcher_is_deep_equal( Prefix ),
   BSearcher_copy( Prefix ),
   BSearcher_deep_copy( Prefix ),
   BSearcher_clone( Prefix ),
   BSearcher_deep_clone( Prefix )
};

/**
   searcher protocol function array
*/

static
void *
p_searcher_table[P_SEARCHER_FUNCTION_COUNT]
=
{
   BSearcher_search_predefined_comparison_function( Prefix )
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

      case P_SEARCHER_TYPE:
      {
         result = 1;
         break;
      }
   }

   return result;
}

#endif // PROTOCOLS_ENABLED


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
   Type value;
   int32_t lo = 0;
   int32_t hi = 0;
   int32_t m = 0;
   int32_t n = 0;

   // get direct pointer to item, put functions
   item = ( *p_indexable ).get_function( P_INDEXABLE_TYPE, P_INDEXABLE_ITEM );

   n = P_Indexable_count( Prefix )( p_indexable );

   // continue until p_indexable is searched
   lo = 0;
   hi = n - 1;
   while ( lo <= hi )
   {
      // get the midpoint index
      if ( ( ( lo & 1 ) == 1 ) && ( ( hi & 1 ) == 1 ) )
      {
         m = ( lo >> 1 ) + ( hi >> 1 ) + 1;
      }
      else
      {
         m = ( lo >> 1 ) + ( hi >> 1 );
      }

      // get the midpoint value
      value = item( p_indexable, m );

      // compare value at midpoint to target
      if ( func( value, target ) < 0 )
      {
         lo = m + 1;
      }
      else if ( func( value, target ) > 0 )
      {
         hi = m - 1;
      }
      else
      {
         result = m;
         break;
      }
   }

   return result;
}

/**
   BSearcher_make
*/

BSearcher_type( Prefix ) *
BSearcher_make( Prefix )( void )
{
   // allocate bsearcher struct
   BSearcher_type( Prefix ) * bsearcher
      = ( BSearcher_type( Prefix ) * ) calloc( 1, sizeof( BSearcher_type( Prefix ) ) );
   CHECK( "bsearcher allocated correctly", bsearcher != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( bsearcher );

   // set type codes
   (*bsearcher)._type = BSEARCHER_TYPE;

   (*bsearcher).func = SEARCH_FUNCTION_NAME;

   MULTITHREAD_MUTEX_INIT( (*bsearcher).mutex );

   INVARIANT( bsearcher );

   return bsearcher;
}

/**
   BSearcher_clone
*/

BSearcher_type( Prefix ) *
BSearcher_clone( Prefix )( BSearcher_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == BSEARCHER_TYPE );
   LOCK( (*other).mutex );
   INVARIANT( other );

   // allocate other struct
   BSearcher_type( Prefix ) * current
      = ( BSearcher_type( Prefix ) * ) calloc( 1, sizeof( BSearcher_type( Prefix ) ) );
   CHECK( "current allocated correctly", current != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = BSEARCHER_TYPE;

   (*current).func = (*other).func;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return current;
}

/**
   BSearcher_deep_clone
*/

BSearcher_type( Prefix ) *
BSearcher_deep_clone( Prefix )( BSearcher_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == BSEARCHER_TYPE );
   LOCK( (*other).mutex );
   INVARIANT( other );

   // allocate other struct
   BSearcher_type( Prefix ) * current
      = ( BSearcher_type( Prefix ) * ) calloc( 1, sizeof( BSearcher_type( Prefix ) ) );
   CHECK( "current allocated correctly", current != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = BSEARCHER_TYPE;

   (*current).func = (*other).func;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return current;
}

/**
   BSearcher_is_equal
*/

int32_t
BSearcher_is_equal( Prefix )( BSearcher_type( Prefix ) *current, BSearcher_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == BSEARCHER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == BSEARCHER_TYPE );
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
   BSearcher_is_deep_equal
*/

int32_t
BSearcher_is_deep_equal( Prefix )( BSearcher_type( Prefix ) *current, BSearcher_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == BSEARCHER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == BSEARCHER_TYPE );
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
   BSearcher_copy
*/

void
BSearcher_copy( Prefix )( BSearcher_type( Prefix ) *current, BSearcher_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == BSEARCHER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == BSEARCHER_TYPE );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   if ( current != other )
   {
      (*current).func = (*other).func;
      INVARIANT( current );
   }

   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return;
}

/**
   BSearcher_deep_copy
*/

void
BSearcher_deep_copy( Prefix )( BSearcher_type( Prefix ) *current, BSearcher_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == BSEARCHER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == BSEARCHER_TYPE );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   if ( current != other )
   {
      (*current).func = (*other).func;
      INVARIANT( current );
   }

   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return;
}

/**
   BSearcher_dispose
*/

void
BSearcher_dispose( Prefix )( BSearcher_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == BSEARCHER_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);
   *current = NULL;

   return;
}

/**
   BSearcher_deep_dispose
*/

void
BSearcher_deep_dispose( Prefix )( BSearcher_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == BSEARCHER_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);
   *current = NULL;

   return;
}

/**
   BSearcher_search_predefined_comparison_function
*/

int32_t
BSearcher_search_predefined_comparison_function( Prefix )
(
   BSearcher_type( Prefix ) *current,
   protocol_base_t *p_indexable,
   Type target
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == BSEARCHER_TYPE );
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
   BSearcher_search
*/

int32_t
BSearcher_search( Prefix )
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

#ifdef __cplusplus
}
#endif

/* End of file */




