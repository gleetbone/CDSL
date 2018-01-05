/**
 @file ISorter.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Insertion Sorter"
 
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

 Function definitions for the opaque ISorter_t type.

*/

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

#define ISORTER_TYPE 0xA5000902

/**
   ISorter structure
*/

struct ISorter_struct( Prefix )
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
struct_ok( ISorter_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).func != NULL );

   return result;
}

static
void invariant( ISorter_type( Prefix ) *p )
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
   ISorter_dispose( Prefix ),
   ISorter_sort_predefined_comparison_function( Prefix )
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
#include <stdlib.h>

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
   int32_t j = 0;
   int32_t n = 0;

   // get direct pointer to item, put functions
   item = P_Indexable_item_f( Prefix )( p_indexable );
   put = P_Indexable_put_f( Prefix )( p_indexable );
   
   n = P_Indexable_count( Prefix )( p_indexable );
   i = 1;
   
   // continue until p_indexable is sorted
   while ( i < n )
   {
      j = i - 1;
      temp = item( p_indexable, i ); 
      
      // walk through items, swapping out of order items
      while( ( j >= 0 ) && ( func( item( p_indexable, j ), temp ) > 0 ) )
      {
         // move out of order item
         put( p_indexable, item( p_indexable, j ), j+1 ); 
         
         // update j
         j = j - 1;
      }
      
      // move out of order item
      put( p_indexable, temp, j+1 );
      
      // update i
      i = i + 1;
   }   
   
   return;
}

/**
   ISorter_make
*/

ISorter_type( Prefix ) *
ISorter_make( Prefix )( void )
{
   // allocate isorter struct
   ISorter_type( Prefix ) * isorter
      = ( ISorter_type( Prefix ) * ) calloc( 1, sizeof( ISorter_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( isorter );

   // set type code
   (*isorter).type = ISORTER_TYPE;
   
   (*isorter).func = SORT_FUNCTION_NAME;
   
   MULTITHREAD_MUTEX_INIT( (*isorter).mutex );

   INVARIANT( isorter );

   return isorter;
}

/**
   ISorter_dispose
*/

void
ISorter_dispose( Prefix )( ISorter_type( Prefix ) *isorter )
{
   PRECONDITION( "isorter not null", isorter != NULL );
   PRECONDITION( "isorter type OK", (*isorter).type == ISORTER_TYPE );
   LOCK( (*isorter).mutex );
   INVARIANT( isorter );

   MULTITHREAD_MUTEX_DESTROY( (*isorter).mutex );

   // delete isorter struct
   free( isorter );

   return;
}

/**
   ISorter_sort_predefined_comparison_function
*/

void
ISorter_sort_predefined_comparison_function( Prefix )
(
   ISorter_type( Prefix ) *isorter,
   protocol_base_t *p_indexable
)
{
   PRECONDITION( "isorter not null", isorter != NULL );
   PRECONDITION( "isorter type OK", (*isorter).type == ISORTER_TYPE );
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE ) == 1 );
   LOCK( (*isorter).mutex );
   INVARIANT( isorter );

   sort( p_indexable, (*isorter).func );

   INVARIANT( isorter );
   UNLOCK( (*isorter).mutex );
   
   return;
}

/**
   ISorter_sort
*/

void
ISorter_sort( Prefix )
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




