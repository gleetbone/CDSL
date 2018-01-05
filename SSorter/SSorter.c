/**
 @file SSorter.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Shell Sorter"
 
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

 Function definitions for the opaque SSorter_t type.

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

#define SSORTER_TYPE 0xA5000906

/**
   SSorter structure
*/

struct SSorter_struct( Prefix )
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
struct_ok( SSorter_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).func != NULL );

   return result;
}

static
void invariant( SSorter_type( Prefix ) *p )
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
   SSorter_dispose( Prefix ),
   SSorter_sort_predefined_comparison_function( Prefix )
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
 
   int32_t gaps[] = { 701, 301, 132, 57, 23, 10, 4, 1 };
   int32_t n_gaps = 8;
   int32_t i_gap = 0;
   int32_t gap = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t n = 0;

   // get direct pointer to item, put functions
   item = P_Indexable_item_f( Prefix )( p_indexable );
   put = P_Indexable_put_f( Prefix )( p_indexable );
   
   n = P_Indexable_count( Prefix )( p_indexable );
   i = 1;
   
   // multiple passes with different gaps
   for( i_gap = 0; i_gap < n_gaps; i_gap++ )
   {
      // skip gaps that are too large
      if ( gaps[i_gap] > n )
      {
         continue;
      }
      
      // get the gap
      gap = gaps[i_gap];
      
      // walk through items with spacing of "gap", put those in order sequentially
      for ( i=gap; i<n; i++ )
      {
         // save item to make room
         temp = item( p_indexable, i ); 
         
         // shift down sorted items until we find the correct position for temp
         for( j=i; (j>=gap) && ( func( item( p_indexable, j - gap ), temp ) > 0 ); j=j-gap )
         {
            put( p_indexable, item( p_indexable, j - gap ), j ); 
         }
         
         // save temp in correct position
         put( p_indexable, temp, j );
         
      }   
   }
   
   return;
}

/**
   SSorter_make
*/

SSorter_type( Prefix ) *
SSorter_make( Prefix )( void )
{
   // allocate ssorter struct
   SSorter_type( Prefix ) * ssorter
      = ( SSorter_type( Prefix ) * ) calloc( 1, sizeof( SSorter_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( ssorter );

   // set type code
   (*ssorter).type = SSORTER_TYPE;
   
   (*ssorter).func = SORT_FUNCTION_NAME;
   
   MULTITHREAD_MUTEX_INIT( (*ssorter).mutex );

   INVARIANT( ssorter );

   return ssorter;
}

/**
   SSorter_dispose
*/

void
SSorter_dispose( Prefix )( SSorter_type( Prefix ) *ssorter )
{
   PRECONDITION( "ssorter not null", ssorter != NULL );
   PRECONDITION( "ssorter type OK", (*ssorter).type == SSORTER_TYPE );
   LOCK( (*ssorter).mutex );
   INVARIANT( ssorter );

   MULTITHREAD_MUTEX_DESTROY( (*ssorter).mutex );

   // delete ssorter struct
   free( ssorter );

   return;
}

/**
   SSorter_sort_predefined_comparison_function
*/

void
SSorter_sort_predefined_comparison_function( Prefix )
(
   SSorter_type( Prefix ) *ssorter,
   protocol_base_t *p_indexable
)
{
   PRECONDITION( "ssorter not null", ssorter != NULL );
   PRECONDITION( "ssorter type OK", (*ssorter).type == SSORTER_TYPE );
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE ) == 1 );
   LOCK( (*ssorter).mutex );
   INVARIANT( ssorter );

   sort( p_indexable, (*ssorter).func );

   INVARIANT( ssorter );
   UNLOCK( (*ssorter).mutex );
   
   return;
}

/**
   SSorter_sort
*/

void
SSorter_sort( Prefix )
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




