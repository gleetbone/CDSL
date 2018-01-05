/**
 @file PQueue.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Priority Queues"
 
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

 Function definitions for the opaque PQueue_t type.

*/

#include "PQueue.h"
 
#ifdef __cplusplus
extern "C" {
#endif
 
#include <string.h>
#include <stdlib.h>   
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

#define PQUEUE_TYPE 0xA5000802


struct node;

/** 
   Node structure. Holds a value
*/

struct node
{
   struct node *next;
   Type value;
};

typedef struct node node_t;

/**
   PQueue structure
*/

struct PQueue_struct( Prefix )
{
   int32_t type;
   int32_t item_type;
   
   node_t *first;
   node_t *last;
   int32_t count;
   
   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/** 
   node_make
*/

static
node_t *
node_make( void )
{
   node_t *node = ( node_t * ) calloc( 1, sizeof( node_t ) );
   POSTCONDITION( "node not null", node != NULL );
   return node;
}

/** 
   node_dispose
*/

static
void
node_dispose( node_t *node )
{
   PRECONDITION( "node not null", node != NULL );
   free( node );
   return;
}

/**
   Invariant
*/   

#if INVARIANT_CONDITIONAL != 0

static
int32_t 
is_empty_implies_first_and_last_null( PQueue_type( Prefix ) *p )
{
   int32_t result = 1;
   
   if ( (*p).count == 0 )
   {
      result = ( ( (*p).first == NULL ) && ( (*p).last == NULL ) );
   }
   
   return result;
}

static
int32_t 
last_next_is_null( PQueue_type( Prefix ) *p )
{
   int32_t result = 1;
   
   if ( (*p).last != NULL )
   {
      result = ( (*(*p).last).next == NULL ) ;
   }
   
   return result;
}

static
int32_t 
nonnegative_count( PQueue_type( Prefix ) *p )
{
   int32_t result = 1;
   
   result = ( (*p).count >= 0 );
   
   return result;
}

static
int32_t 
valid_count( PQueue_type( Prefix ) *p )
{
   int32_t result = 1;
   int32_t n = 0;
   
   node_t *node = (*p).first;
   
   while( node != NULL )
   {
      n = n + 1;
      node = (*node).next;
   }
   
   result = ( n == (*p).count );
   
   return result;
}

static
int32_t 
is_in_order( PQueue_type( Prefix ) *p )
{
   int32_t result = 1;
   node_t *n1 = (*p).first;
   node_t *n2 = NULL;
   
   if ( n1 != NULL )
   {
      n2 = (*n1).next;
   }
   
   while( ( n2 != NULL ) && ( result == 1 ) )
   {
      result = VALUE_ORDER_FUNCTION( (*n1).value, (*n2).value );
      
      n1 = n2;
      n2 = (*n2).next;
   }
   
   return result;
}

static
void invariant( PQueue_type( Prefix ) *p )
{
   assert(((void) "empty implies first and last null", is_empty_implies_first_and_last_null( p ) ));
   assert(((void) "last next is null", last_next_is_null( p ) ));
   assert(((void) "nonnegative count", nonnegative_count( p ) ));
   assert(((void) "valid count", valid_count( p ) ));
   assert(((void) "elements in order", is_in_order( p ) ));
   return;
}

#endif

/** 
   PQueue_make
*/

PQueue_type( Prefix ) *
PQueue_make( Prefix )( void )
{
   // allocate PQueue struct
   PQueue_type( Prefix ) *pqueue 
      = ( PQueue_type( Prefix ) * ) calloc( 1, sizeof( PQueue_type( Prefix ) ) );
      
   // set type
   (*pqueue).type = PQUEUE_TYPE;
   (*pqueue).item_type = Type_Code;

   MULTITHREAD_MUTEX_INIT( (*pqueue).mutex );

   INVARIANT( pqueue );
   
   return pqueue;
}

/** 
   PQueue_dispose
*/

void
PQueue_dispose( Prefix )( PQueue_type( Prefix ) *pqueue )
{
   PRECONDITION( "pqueue not null", pqueue != NULL );
   PRECONDITION( "pqueue type OK", ( (*pqueue).type == PQUEUE_TYPE ) && ( (*pqueue).item_type == Type_Code ) );
   LOCK( (*pqueue).mutex );
   INVARIANT( pqueue );
   
   // delete PQueue items
   node_t *item = (*pqueue).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      node_dispose( item );
      item = next;
   }

   MULTITHREAD_MUTEX_DESTROY( (*pqueue).mutex );

   // delete PQueue struct
   free( pqueue );

   return;
}

/** 
   PQueue_dispose_with_contents
*/

void
PQueue_dispose_with_contents( Prefix )( PQueue_type( Prefix ) *pqueue )
{
   PRECONDITION( "pqueue not null", pqueue != NULL );
   PRECONDITION( "pqueue type OK", ( (*pqueue).type == PQUEUE_TYPE ) && ( (*pqueue).item_type == Type_Code ) );
   LOCK( (*pqueue).mutex );
   INVARIANT( pqueue );
   
   // delete PQueue items
   node_t *item = (*pqueue).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      VALUE_DISPOSE_FUNCTION( (*item).value );
      node_dispose( item );
      item = next;
   }

   MULTITHREAD_MUTEX_DESTROY( (*pqueue).mutex );

   // delete PQueue struct
   free( pqueue );

   return;
}

/**
   PQueue_item
*/

Type 
PQueue_item( Prefix )( PQueue_type( Prefix ) *pqueue )
{
   PRECONDITION( "pqueue not null", pqueue != NULL );
   PRECONDITION( "pqueue type OK", ( (*pqueue).type == PQUEUE_TYPE ) && ( (*pqueue).item_type == Type_Code ) );
   LOCK( (*pqueue).mutex );
   INVARIANT( pqueue );
   PRECONDITION( "pqueue not empty", (*pqueue).count > 0 );
   
   Type value = (*(*pqueue).first).value;
   
   INVARIANT( pqueue );
   UNLOCK( (*pqueue).mutex );
   
   return value;
}

/**
   PQueue_count
*/

int32_t
PQueue_count( Prefix )( PQueue_type( Prefix ) *pqueue )
{
   PRECONDITION( "pqueue not null", pqueue != NULL );
   PRECONDITION( "pqueue type OK", ( (*pqueue).type == PQUEUE_TYPE ) && ( (*pqueue).item_type == Type_Code ) );
   LOCK( (*pqueue).mutex );
   INVARIANT( pqueue );
   
   int32_t result = (*pqueue).count;
   
   INVARIANT( pqueue );
   UNLOCK( (*pqueue).mutex );
   
   return result;
}

/**
   PQueue_is_empty
*/

int32_t
PQueue_is_empty( Prefix )( PQueue_type( Prefix ) *pqueue )
{
   PRECONDITION( "pqueue not null", pqueue != NULL );
   PRECONDITION( "pqueue type OK", ( (*pqueue).type == PQUEUE_TYPE ) && ( (*pqueue).item_type == Type_Code ) );
   LOCK( (*pqueue).mutex );
   INVARIANT( pqueue );
   
   int32_t result = ( (*pqueue).count == 0 );
   
   INVARIANT( pqueue );
   UNLOCK( (*pqueue).mutex );
   
   return result;
}

/**
   PQueue_put
*/

void
PQueue_put( Prefix )( PQueue_type( Prefix ) *pqueue, Type value )
{
   PRECONDITION( "pqueue not null", pqueue != NULL );
   PRECONDITION( "pqueue type OK", ( (*pqueue).type == PQUEUE_TYPE ) && ( (*pqueue).item_type == Type_Code ) );
   LOCK( (*pqueue).mutex );
   INVARIANT( pqueue );
   
   int flag = 0;
   int completed_flag = 0;
   node_t *n = NULL;
   node_t *n1 = NULL;
   node_t *new_node = node_make();
   (*new_node).value = value;

   if ( (*pqueue).count == 0 )
   {
      // PQueue is empty, make this the first item
      (*pqueue).first = new_node;
      (*pqueue).last = new_node;
      (*pqueue).count = 1;
   }
   else
   {
      // otherwise start with first node
      n = (*pqueue).first;
      flag = VALUE_ORDER_FUNCTION( (*n).value, (*new_node).value );
      
      // if new_node does not come before n, increment n
      if ( flag == 1 )
      {
         n1 = n;
         n = (*n).next;
      }
      // if new_node comes before n, it is now the first element
      else
      {
         (*new_node).next = n;
         (*pqueue).first = new_node;
         (*pqueue).count = (*pqueue).count + 1;
         completed_flag = 1;
      }
            
      // if not complete, loop through elements until we find where new_node
      // should be inserted
      if ( completed_flag == 0 )
      {
         while( n != NULL )
         {
            flag = VALUE_ORDER_FUNCTION( (*n).value, (*new_node).value );
            
            if ( flag == 1 )
            {
               // if new_node comes after n, increment n
               n1 = n;
               n = (*n).next;
            }
            else
            {
               // if new node comes before n, insert new_node before n
               (*n1).next = new_node;
               (*new_node).next = n;
               (*pqueue).count = (*pqueue).count + 1;
               completed_flag = 1;
               
               // exit loop
               break;               
            }
         }
         
         // last possiblity is that new_node is the new last element
         if ( completed_flag == 0 )
         {
            (*n1).next = new_node;
            (*pqueue).last = new_node;
            (*pqueue).count = (*pqueue).count + 1;
            completed_flag = 1;
         }
         
      }
   }
   
   // make sure last element's next is null
   (*(*pqueue).last).next = NULL;
   
   INVARIANT( pqueue );
   POSTCONDITION( "PQueue not empty", (*pqueue).count > 0 );
   UNLOCK( (*pqueue).mutex );
   
   return;
}

/**
   PQueue_remove
*/

void
PQueue_remove( Prefix )( PQueue_type( Prefix ) *pqueue )
{
   PRECONDITION( "pqueue not null", pqueue != NULL );
   PRECONDITION( "pqueue type OK", ( (*pqueue).type == PQUEUE_TYPE ) && ( (*pqueue).item_type == Type_Code ) );
   LOCK( (*pqueue).mutex );
   INVARIANT( pqueue );
   PRECONDITION( "pqueue not empty", (*pqueue).count > 0 );
   
   node_t *node = (*pqueue).first;
   
   // remove the node
   if ( node != NULL )
   {
      (*pqueue).first = (*node).next;
      (*pqueue).count = (*pqueue).count - 1;
      node_dispose( node );
      
      // if PQueue is now empty, set last to NULL
      if ( (*pqueue).count == 0 )
      {
         (*pqueue).last = NULL;
      }
   }
   
   INVARIANT( pqueue );
   UNLOCK( (*pqueue).mutex );
   
   return;
}

/**
   PQueue_remove_and_dispose
*/

void
PQueue_remove_and_dispose( Prefix )( PQueue_type( Prefix ) *pqueue )
{
   PRECONDITION( "pqueue not null", pqueue != NULL );
   PRECONDITION( "pqueue type OK", ( (*pqueue).type == PQUEUE_TYPE ) && ( (*pqueue).item_type == Type_Code ) );
   LOCK( (*pqueue).mutex );
   INVARIANT( pqueue );
   PRECONDITION( "pqueue not empty", (*pqueue).count > 0 );
   
   node_t *node = (*pqueue).first;
   
   // remove the node
   if ( node != NULL )
   {
      (*pqueue).first = (*node).next;
      (*pqueue).count = (*pqueue).count - 1;
      VALUE_DISPOSE_FUNCTION( (*node).value );
      node_dispose( node );
      
      // if PQueue is now empty, set last to NULL
      if ( (*pqueue).count == 0 )
      {
         (*pqueue).last = NULL;
      }
   }
   
   INVARIANT( pqueue );
   UNLOCK( (*pqueue).mutex );
   
   return;
}

/**
   PQueue_prune
*/

void
PQueue_prune( Prefix )( PQueue_type( Prefix ) *pqueue, int32_t count )
{
   PRECONDITION( "pqueue not null", pqueue != NULL );
   PRECONDITION( "pqueue type OK", ( (*pqueue).type == PQUEUE_TYPE ) && ( (*pqueue).item_type == Type_Code ) );
   LOCK( (*pqueue).mutex );
   INVARIANT( pqueue );
   PRECONDITION( "PQueue has enough items", (*pqueue).count >= count );
   
   int32_t i = 0;
   node_t *node = NULL;
   
   // remove the node
   for( i=0; i < count; i++ )
   {
      node = (*pqueue).first;
      
      if ( node != NULL )
      {
         (*pqueue).first = (*node).next;
         (*pqueue).count = (*pqueue).count - 1;
         node_dispose( node );
      }
   }

   // if PQueue is now empty, set last to NULL
   if ( (*pqueue).count == 0 )
   {
      (*pqueue).last = NULL;
   }
   
   INVARIANT( pqueue );
   UNLOCK( (*pqueue).mutex );
   
   return;
}

/**
   PQueue_prune_and_dispose
*/

void
PQueue_prune_and_dispose( Prefix )( PQueue_type( Prefix ) *pqueue, int32_t count )
{
   PRECONDITION( "pqueue not null", pqueue != NULL );
   PRECONDITION( "pqueue type OK", ( (*pqueue).type == PQUEUE_TYPE ) && ( (*pqueue).item_type == Type_Code ) );
   LOCK( (*pqueue).mutex );
   INVARIANT( pqueue );
   PRECONDITION( "PQueue has enough items", (*pqueue).count >= count );
   
   int32_t i = 0;
   node_t *node = NULL;
   
   // remove the node
   for( i=0; i < count; i++ )
   {
      node = (*pqueue).first;
      
      if ( node != NULL )
      {
         (*pqueue).first = (*node).next;
         (*pqueue).count = (*pqueue).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
   }

   // if PQueue is now empty, set last to NULL
   if ( (*pqueue).count == 0 )
   {
      (*pqueue).last = NULL;
   }
   
   INVARIANT( pqueue );
   UNLOCK( (*pqueue).mutex );
   
   return;
}

/**
   PQueue_keep
*/

void
PQueue_keep( Prefix )( PQueue_type( Prefix ) *pqueue, int32_t count )
{
   PRECONDITION( "pqueue not null", pqueue != NULL );
   PRECONDITION( "pqueue type OK", ( (*pqueue).type == PQUEUE_TYPE ) && ( (*pqueue).item_type == Type_Code ) );
   LOCK( (*pqueue).mutex );
   INVARIANT( pqueue );
   PRECONDITION( "PQueue has enough items", (*pqueue).count >= count );
   
   int32_t i = 0;
   int32_t n = (*pqueue).count - count;
   
   node_t *node = NULL;
   
   // remove n nodes
   for( i=0; i < n; i++ )
   {
      node = (*pqueue).first;
      
      if ( node != NULL )
      {
         (*pqueue).first = (*node).next;
         (*pqueue).count = (*pqueue).count - 1;
         node_dispose( node );
      }
   }

   // if PQueue is now empty, set last to NULL
   if ( (*pqueue).count == 0 )
   {
      (*pqueue).last = NULL;
   }
   
   INVARIANT( pqueue );
   UNLOCK( (*pqueue).mutex );
   
   return;
}

/**
   PQueue_keep_and_dispose
*/

void
PQueue_keep_and_dispose( Prefix )( PQueue_type( Prefix ) *pqueue, int32_t count )
{
   PRECONDITION( "pqueue not null", pqueue != NULL );
   PRECONDITION( "pqueue type OK", ( (*pqueue).type == PQUEUE_TYPE ) && ( (*pqueue).item_type == Type_Code ) );
   LOCK( (*pqueue).mutex );
   INVARIANT( pqueue );
   PRECONDITION( "PQueue has enough items", (*pqueue).count >= count );
   
   int32_t i = 0;
   int32_t n = (*pqueue).count - count;
   
   node_t *node = NULL;
   
   // remove n nodes
   for( i=0; i<n; i++ )
   {
      node = (*pqueue).first;
      
      if ( node != NULL )
      {
         (*pqueue).first = (*node).next;
         (*pqueue).count = (*pqueue).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
   }

   // if PQueue is now empty, set last to NULL
   if ( (*pqueue).count == 0 )
   {
      (*pqueue).last = NULL;
   }
   
   INVARIANT( pqueue );
   UNLOCK( (*pqueue).mutex );
   
   return;
}

/**
   PQueue_wipe_out
*/

void
PQueue_wipe_out( Prefix )( PQueue_type( Prefix ) *pqueue )
{
   PRECONDITION( "pqueue not null", pqueue != NULL );
   PRECONDITION( "pqueue type OK", ( (*pqueue).type == PQUEUE_TYPE ) && ( (*pqueue).item_type == Type_Code ) );
   LOCK( (*pqueue).mutex );
   INVARIANT( pqueue );
   
   node_t *node = (*pqueue).first;
   node_t *next = NULL;
  
   // remove all nodes   
   while ( node != NULL )
   {
      next = (*node).next;
      node_dispose( node );
      node = next;
   }
   
   (*pqueue).count = 0;
   (*pqueue).first = NULL;
   (*pqueue).last = NULL;
   
   INVARIANT( pqueue );
   POSTCONDITION( "PQueue is empty", (*pqueue).count == 0 );
   UNLOCK( (*pqueue).mutex );
   
   return;
}

/**
   PQueue_wipe_out_and_dispose
*/

void
PQueue_wipe_out_and_dispose( Prefix )( PQueue_type( Prefix ) *pqueue )
{
   PRECONDITION( "pqueue not null", pqueue != NULL );
   PRECONDITION( "pqueue type OK", ( (*pqueue).type == PQUEUE_TYPE ) && ( (*pqueue).item_type == Type_Code ) );
   LOCK( (*pqueue).mutex );
   INVARIANT( pqueue );
   
   node_t *node = (*pqueue).first;
   node_t *next = NULL;
  
   // remove all nodes   
   while ( node != NULL )
   {
      next = (*node).next;
      VALUE_DISPOSE_FUNCTION( (*node).value );
      node_dispose( node );
      node = next;
   }
   
   (*pqueue).count = 0;
   (*pqueue).first = NULL;
   (*pqueue).last = NULL;
   
   INVARIANT( pqueue );
   POSTCONDITION( "PQueue is empty", (*pqueue).count == 0 );
   UNLOCK( (*pqueue).mutex );
   
   return;
}


/* End of file */

