/**
 @file MSorter.c
 @author Greg Lee
 @version 1.0.0
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
#include <math.h>

#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Indexable.h"
#include "P_Indexable.ph"
#include "P_Clonable.h"
#include "P_Clonable.ph"
#include "P_Sorter.ph"
   
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

#define MSORTER_TYPE 0xA5000903

/**
   MSorter structure
*/

struct MSorter_struct( Prefix )
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
struct_ok( MSorter_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).func != NULL );

   return result;
}

static
void invariant( MSorter_type( Prefix ) *p )
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
   MSorter_dispose( Prefix ),
   MSorter_sort_predefined_comparison_function( Prefix )
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
   
   for( k=i_start; k<i_end; k++ )
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
   item = P_Indexable_item_f( Prefix )( p_indexable );
   put = P_Indexable_put_f( Prefix )( p_indexable );

   // get size of indexable
   n = P_Indexable_count( Prefix )( p_indexable );

   // make second indexable for temp buffer
   protocol_base_t *p_indexable1 = P_Clonable_clone( Prefix )( p_indexable );
      
   // sort the indexable
   split_merge( p_indexable1, p_indexable, func, item, put, 0, n );
 
   // dispose of temp buffer
   P_Indexable_dispose( Prefix )( p_indexable1 );
   
   return;
}

/**
   MSorter_make
*/

MSorter_type( Prefix ) *
MSorter_make( Prefix )( void )
{
   // allocate msorter struct
   MSorter_type( Prefix ) * msorter
      = ( MSorter_type( Prefix ) * ) calloc( 1, sizeof( MSorter_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( msorter );

   // set type code
   (*msorter).type = MSORTER_TYPE;
   
   (*msorter).func = SORT_FUNCTION_NAME;
   
   MULTITHREAD_MUTEX_INIT( (*msorter).mutex );

   INVARIANT( msorter );

   return msorter;
}

/**
   MSorter_dispose
*/

void
MSorter_dispose( Prefix )( MSorter_type( Prefix ) *msorter )
{
   PRECONDITION( "msorter not null", msorter != NULL );
   PRECONDITION( "msorter type OK", (*msorter).type == MSORTER_TYPE );
   LOCK( (*msorter).mutex );
   INVARIANT( msorter );

   MULTITHREAD_MUTEX_DESTROY( (*msorter).mutex );

   // delete msorter struct
   free( msorter );

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
   PRECONDITION( "msorter type OK", (*msorter).type == MSORTER_TYPE );
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE ) == 1 );
   PRECONDITION( "p_indexable supports clonable protocol", protocol_base_supports_protocol( p_indexable, P_CLONABLE ) == 1 );
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
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE ) == 1 );
   PRECONDITION( "p_indexable supports clonable protocol", protocol_base_supports_protocol( p_indexable, P_CLONABLE ) == 1 );

   sort( p_indexable, func );

   return;
}

/* End of file */




