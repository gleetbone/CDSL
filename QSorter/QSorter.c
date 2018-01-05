/**
 @file QSorter.c
 @author Greg Lee
 @version 1.0.0
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

#define QSORTER_TYPE 0xA5000904

/**
   QSorter structure
*/

struct QSorter_struct( Prefix )
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
struct_ok( QSorter_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).func != NULL );

   return result;
}

static
void invariant( QSorter_type( Prefix ) *p )
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
   QSorter_dispose( Prefix ),
   QSorter_sort_predefined_comparison_function( Prefix )
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
   item = P_Indexable_item_f( Prefix )( p_indexable );
   put = P_Indexable_put_f( Prefix )( p_indexable );
   
   while ( start < stop )
   {
      left = start; 
      p = start + (stop-start)/2; 
      right = stop;

      pivot = item( p_indexable, p );

      while (1)
      {
         while ( 
                  (left <= right ) 
                  && 
                  ( func( item( p_indexable, left ), pivot ) <= 0 ) 
               ) 
         {
            left++;
         }
         
         while ( 
                  ( left <= right ) 
                  && 
                  ( func( item( p_indexable, right ), pivot)  > 0 ) 
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
   QSorter_make
*/

QSorter_type( Prefix ) *
QSorter_make( Prefix )( void )
{
   // allocate qsorter struct
   QSorter_type( Prefix ) * qsorter
      = ( QSorter_type( Prefix ) * ) calloc( 1, sizeof( QSorter_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( qsorter );

   // set type code
   (*qsorter).type = QSORTER_TYPE;
   
   (*qsorter).func = SORT_FUNCTION_NAME;
   
   MULTITHREAD_MUTEX_INIT( (*qsorter).mutex );

   INVARIANT( qsorter );

   return qsorter;
}

/**
   QSorter_dispose
*/

void
QSorter_dispose( Prefix )( QSorter_type( Prefix ) *qsorter )
{
   PRECONDITION( "qsorter not null", qsorter != NULL );
   PRECONDITION( "qsorter type OK", (*qsorter).type == QSORTER_TYPE );
   LOCK( (*qsorter).mutex );
   INVARIANT( qsorter );

   MULTITHREAD_MUTEX_DESTROY( (*qsorter).mutex );

   // delete qsorter struct
   free( qsorter );

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
   PRECONDITION( "qsorter type OK", (*qsorter).type == QSORTER_TYPE );
   PRECONDITION( "p_indexable not null", p_indexable != NULL );
   PRECONDITION( "p_indexable is object", protocol_base_is_valid_object( p_indexable ) == 1 );
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE ) == 1 );
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
   PRECONDITION( "p_indexable supports protocol", protocol_base_supports_protocol( p_indexable, P_INDEXABLE ) == 1 );

   int32_t start = 0;
   int32_t stop = 0;

   start = 0;
   stop = P_Indexable_count( Prefix )( p_indexable ) - 1;
   
   sort( p_indexable, func, start, stop );

   return;
}

/* End of file */




