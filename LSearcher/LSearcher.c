/**
 @file LSearcher.c
 @author Greg Lee
 @version 1.0.0
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

#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Indexable.h"
#include "P_Indexable.ph"
#include "P_Searcher.ph"
   
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

#define LSEARCHER_TYPE 0xA5000A01

/**
   LSearcher structure
*/

struct LSearcher_struct( Prefix )
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
struct_ok( LSearcher_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).func != NULL );

   return result;
}

static
void invariant( LSearcher_type( Prefix ) *p )
{
   assert(( (void) "struct ok count", struct_ok( p ) ));
   return;
}

#endif

/**
   searcher protocol function array
*/

static
void *
p_searcher_table[P_SEARCHER_FUNCTION_COUNT]
=
{
   LSearcher_dispose( Prefix ),
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

   if ( protocol_id == P_SEARCHER )
   {
      if ( ( function_id >= 0 ) && ( function_id <= P_SEARCHER_FUNCTION_MAX ) )
      {
         result = p_searcher_table[ function_id ];
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

   if ( protocol_id == P_SEARCHER )
   {
      result = 1;
   }

   return result;
}


/**
   Includes
*/

#include <stddef.h>
#include <stdlib.h>

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
   item = P_Indexable_item_f( Prefix )( p_indexable );
   
   n = P_Indexable_count( Prefix )( p_indexable );
   
   // continue until p_indexable is searched
   for ( i=0; i<n; i++ )
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
   LSearcher_type( Prefix ) * lsearcher
      = ( LSearcher_type( Prefix ) * ) calloc( 1, sizeof( LSearcher_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( lsearcher );

   // set type code
   (*lsearcher).type = LSEARCHER_TYPE;
   
   (*lsearcher).func = SEARCH_FUNCTION_NAME;
   
   MULTITHREAD_MUTEX_INIT( (*lsearcher).mutex );

   INVARIANT( lsearcher );

   return lsearcher;
}

/**
   LSearcher_dispose
*/

void
LSearcher_dispose( Prefix )( LSearcher_type( Prefix ) *lsearcher )
{
   PRECONDITION( "lsearcher not null", lsearcher != NULL );
   PRECONDITION( "lsearcher type OK", (*lsearcher).type == LSEARCHER_TYPE );
   LOCK( (*lsearcher).mutex );
   INVARIANT( lsearcher );

   MULTITHREAD_MUTEX_DESTROY( (*lsearcher).mutex );

   // delete lsearcher struct
   free( lsearcher );

   return;
}

/**
   LSearcher_search_predefined_comparison_function
*/

int32_t
LSearcher_search_predefined_comparison_function( Prefix )
(
   LSearcher_type( Prefix ) *lsearcher,
   protocol_base_t *p_indexable,
   Type target
)
{
   PRECONDITION( "lsearcher not null", lsearcher != NULL );
   PRECONDITION( "lsearcher type OK", (*lsearcher).type == LSEARCHER_TYPE );
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE ) == 1 );
   LOCK( (*lsearcher).mutex );
   INVARIANT( lsearcher );

   int32_t result = search( p_indexable, (*lsearcher).func, target );

   INVARIANT( lsearcher );
   UNLOCK( (*lsearcher).mutex );
   
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
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE ) == 1 );

   int32_t result = search( p_indexable, func, target );

   return result;
}

/* End of file */




