/**
 @file Queue.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Queues (stack that can be added to on one end and popped on the other)"
 
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

 Function definitions for the opaque Queue_t type.

*/

#include "Queue.h"
 
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

#define QUEUE_TYPE 0xA5000803


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
   Queue structure
*/

struct Queue_struct( Prefix )
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
is_empty_implies_first_and_last_null( Queue_type( Prefix ) *p )
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
last_next_is_null( Queue_type( Prefix ) *p )
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
nonnegative_count( Queue_type( Prefix ) *p )
{
   int32_t result = 1;
   
   result = ( (*p).count >= 0 );
   
   return result;
}

static
int32_t 
valid_count( Queue_type( Prefix ) *p )
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
void invariant( Queue_type( Prefix ) *p )
{
   assert(((void) "empty implies first and last null", is_empty_implies_first_and_last_null( p ) ));
   assert(((void) "last next is null", last_next_is_null( p ) ));
   assert(((void) "nonnegative count", nonnegative_count( p ) ));
   assert(((void) "valid count", valid_count( p ) ));
   return;
}

#endif

/** 
   Queue_make
*/

Queue_type( Prefix ) *
Queue_make( Prefix )( void )
{
   // allocate queue struct
   Queue_type( Prefix ) * queue 
      = ( Queue_type( Prefix ) * ) calloc( 1, sizeof( Queue_type( Prefix ) ) );
      
   // set type
   (*queue).type = QUEUE_TYPE;
   (*queue).item_type = Type_Code;

   MULTITHREAD_MUTEX_INIT( (*queue).mutex );

   INVARIANT( queue );
   
   return queue;
}

/** 
   Queue_dispose
*/

void
Queue_dispose( Prefix )( Queue_type( Prefix ) *queue )
{
   PRECONDITION( "queue not null", queue != NULL );
   PRECONDITION( "queue type OK", ( (*queue).type == QUEUE_TYPE ) && ( (*queue).item_type == Type_Code ) );
   LOCK( (*queue).mutex );
   INVARIANT( queue );
   
   // delete queue items
   node_t *item = (*queue).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      node_dispose( item );
      item = next;
   }

   MULTITHREAD_MUTEX_DESTROY( (*queue).mutex );

   // delete queue struct
   free( queue );

   return;
}

/** 
   Queue_dispose_with_contents
*/

void
Queue_dispose_with_contents( Prefix )( Queue_type( Prefix ) *queue )
{
   PRECONDITION( "queue not null", queue != NULL );
   PRECONDITION( "queue type OK", ( (*queue).type == QUEUE_TYPE ) && ( (*queue).item_type == Type_Code ) );
   LOCK( (*queue).mutex );
   INVARIANT( queue );
   
   // delete queue items
   node_t *item = (*queue).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      VALUE_DISPOSE_FUNCTION( (*item).value );
      node_dispose( item );
      item = next;
   }

   MULTITHREAD_MUTEX_DESTROY( (*queue).mutex );

   // delete queue struct
   free( queue );

   return;
}

/**
   Queue_item
*/

Type 
Queue_item( Prefix )( Queue_type( Prefix ) *queue )
{
   PRECONDITION( "queue not null", queue != NULL );
   PRECONDITION( "queue type OK", ( (*queue).type == QUEUE_TYPE ) && ( (*queue).item_type == Type_Code ) );
   LOCK( (*queue).mutex );
   INVARIANT( queue );
   PRECONDITION( "queue not empty", (*queue).count > 0 );
   
   Type value = (*(*queue).first).value;
   
   INVARIANT( queue );
   UNLOCK( (*queue).mutex );
   
   return value;
}

/**
   Queue_count
*/

int32_t
Queue_count( Prefix )( Queue_type( Prefix ) *queue )
{
   PRECONDITION( "queue not null", queue != NULL );
   PRECONDITION( "queue type OK", ( (*queue).type == QUEUE_TYPE ) && ( (*queue).item_type == Type_Code ) );
   LOCK( (*queue).mutex );
   INVARIANT( queue );
   
   int32_t result = (*queue).count;
   
   INVARIANT( queue );
   UNLOCK( (*queue).mutex );
   
   return result;
}

/**
   Queue_is_empty
*/

int32_t
Queue_is_empty( Prefix )( Queue_type( Prefix ) *queue )
{
   PRECONDITION( "queue not null", queue != NULL );
   PRECONDITION( "queue type OK", ( (*queue).type == QUEUE_TYPE ) && ( (*queue).item_type == Type_Code ) );
   LOCK( (*queue).mutex );
   INVARIANT( queue );
   
   int32_t result = ( (*queue).count == 0 );
   
   INVARIANT( queue );
   UNLOCK( (*queue).mutex );
   
   return result;
}

/**
   Queue_put
*/

void
Queue_put( Prefix )( Queue_type( Prefix ) *queue, Type value )
{
   PRECONDITION( "queue not null", queue != NULL );
   PRECONDITION( "queue type OK", ( (*queue).type == QUEUE_TYPE ) && ( (*queue).item_type == Type_Code ) );
   LOCK( (*queue).mutex );
   INVARIANT( queue );
   
   node_t *node = (*queue).last;

   if ( node == NULL )
   {
      // queue is empty, make this the first item
      node_t *new_node = node_make();
      (*new_node).value = value;
      (*queue).first = new_node;
      (*queue).last = new_node;
      (*queue).count = 1;
   }
   else
   {
      node_t *new_node = node_make();
      (*new_node).value = value;
     
      (*(*queue).last).next = new_node;
      (*new_node).next = NULL;
      (*queue).last = new_node;
         
      (*queue).count = (*queue).count + 1;
      
   }
   
   INVARIANT( queue );
   POSTCONDITION( "last is put item", (*(*queue).last).value = value );
   POSTCONDITION( "queue not empty", (*queue).count > 0 );
   UNLOCK( (*queue).mutex );
   
   return;
}

/**
   Queue_remove
*/

void
Queue_remove( Prefix )( Queue_type( Prefix ) *queue )
{
   PRECONDITION( "queue not null", queue != NULL );
   PRECONDITION( "queue type OK", ( (*queue).type == QUEUE_TYPE ) && ( (*queue).item_type == Type_Code ) );
   LOCK( (*queue).mutex );
   PRECONDITION( "queue not empty", (*queue).count > 0 );
   INVARIANT( queue );
   
   node_t *node = (*queue).first;
   
   // remove the node
   if ( node != NULL )
   {
      (*queue).first = (*node).next;
      (*queue).count = (*queue).count - 1;
      node_dispose( node );
      
      // if queue is now empty, set last to NULL
      if ( (*queue).count == 0 )
      {
         (*queue).last = NULL;
      }
   }
   
   INVARIANT( queue );
   UNLOCK( (*queue).mutex );
   
   return;
}

/**
   Queue_remove_and_dispose
*/

void
Queue_remove_and_dispose( Prefix )( Queue_type( Prefix ) *queue )
{
   PRECONDITION( "queue not null", queue != NULL );
   PRECONDITION( "queue type OK", ( (*queue).type == QUEUE_TYPE ) && ( (*queue).item_type == Type_Code ) );
   LOCK( (*queue).mutex );
   PRECONDITION( "queue not empty", (*queue).count > 0 );
   INVARIANT( queue );
   
   node_t *node = (*queue).first;
   
   // remove the node
   if ( node != NULL )
   {
      (*queue).first = (*node).next;
      (*queue).count = (*queue).count - 1;
      VALUE_DISPOSE_FUNCTION( (*node).value );
      node_dispose( node );
      
      // if queue is now empty, set last to NULL
      if ( (*queue).count == 0 )
      {
         (*queue).last = NULL;
      }
   }
   
   INVARIANT( queue );
   UNLOCK( (*queue).mutex );
   
   return;
}

/**
   Queue_prune
*/

void
Queue_prune( Prefix )( Queue_type( Prefix ) *queue, int32_t count )
{
   PRECONDITION( "queue not null", queue != NULL );
   PRECONDITION( "queue type OK", ( (*queue).type == QUEUE_TYPE ) && ( (*queue).item_type == Type_Code ) );
   LOCK( (*queue).mutex );
   PRECONDITION( "queue not empty", (*queue).count > 0 );
   PRECONDITION( "queue has enough items", (*queue).count >= count );
   INVARIANT( queue );
   
   int32_t i = 0;
   node_t *node = NULL;
   
   // remove the node
   for( i=0; i < count; i++ )
   {
      node = (*queue).first;
      
      if ( node != NULL )
      {
         (*queue).first = (*node).next;
         (*queue).count = (*queue).count - 1;
         node_dispose( node );
      }
   }

   // if queue is now empty, set last to NULL
   if ( (*queue).count == 0 )
   {
      (*queue).last = NULL;
   }
   
   INVARIANT( queue );
   UNLOCK( (*queue).mutex );
   
   return;
}

/**
   Queue_prune_and_dispose
*/

void
Queue_prune_and_dispose( Prefix )( Queue_type( Prefix ) *queue, int32_t count )
{
   PRECONDITION( "queue not null", queue != NULL );
   PRECONDITION( "queue type OK", ( (*queue).type == QUEUE_TYPE ) && ( (*queue).item_type == Type_Code ) );
   LOCK( (*queue).mutex );
   PRECONDITION( "queue has enough items", (*queue).count >= count );
   INVARIANT( queue );
   
   int32_t i = 0;
   node_t *node = NULL;
   
   // remove the node
   for( i=0; i < count; i++ )
   {
      node = (*queue).first;
      
      if ( node != NULL )
      {
         (*queue).first = (*node).next;
         (*queue).count = (*queue).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
   }

   // if queue is now empty, set last to NULL
   if ( (*queue).count == 0 )
   {
      (*queue).last = NULL;
   }
   
   INVARIANT( queue );
   UNLOCK( (*queue).mutex );
   
   return;
}

/**
   Queue_keep
*/

void
Queue_keep( Prefix )( Queue_type( Prefix ) *queue, int32_t count )
{
   PRECONDITION( "queue not null", queue != NULL );
   PRECONDITION( "queue type OK", ( (*queue).type == QUEUE_TYPE ) && ( (*queue).item_type == Type_Code ) );
   LOCK( (*queue).mutex );
   PRECONDITION( "queue has enough items", (*queue).count >= count );
   INVARIANT( queue );
   
   int32_t i = 0;
   int32_t n = (*queue).count - count;
   
   node_t *node = NULL;
   
   // remove n nodes
   for( i=0; i < n; i++ )
   {
      node = (*queue).first;
      
      if ( node != NULL )
      {
         (*queue).first = (*node).next;
         (*queue).count = (*queue).count - 1;
         node_dispose( node );
      }
   }

   // if queue is now empty, set last to NULL
   if ( (*queue).count == 0 )
   {
      (*queue).last = NULL;
   }
   
   INVARIANT( queue );
   UNLOCK( (*queue).mutex );
   
   return;
}

/**
   Queue_keep_and_dispose
*/

void
Queue_keep_and_dispose( Prefix )( Queue_type( Prefix ) *queue, int32_t count )
{
   PRECONDITION( "queue not null", queue != NULL );
   PRECONDITION( "queue type OK", ( (*queue).type == QUEUE_TYPE ) && ( (*queue).item_type == Type_Code ) );
   LOCK( (*queue).mutex );
   PRECONDITION( "queue has enough items", (*queue).count >= count );
   INVARIANT( queue );
   
   int32_t i = 0;
   int32_t n = (*queue).count - count;
   
   node_t *node = NULL;
   
   // remove n nodes
   for( i=0; i<n; i++ )
   {
      node = (*queue).first;
      
      if ( node != NULL )
      {
         (*queue).first = (*node).next;
         (*queue).count = (*queue).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
   }

   // if queue is now empty, set last to NULL
   if ( (*queue).count == 0 )
   {
      (*queue).last = NULL;
   }
   
   INVARIANT( queue );
   UNLOCK( (*queue).mutex );
   
   return;
}

/**
   Queue_wipe_out
*/

void
Queue_wipe_out( Prefix )( Queue_type( Prefix ) *queue )
{
   PRECONDITION( "queue not null", queue != NULL );
   PRECONDITION( "queue type OK", ( (*queue).type == QUEUE_TYPE ) && ( (*queue).item_type == Type_Code ) );
   LOCK( (*queue).mutex );
   INVARIANT( queue );
   
   node_t *node = (*queue).first;
   node_t *next = NULL;
  
   // remove all nodes   
   while ( node != NULL )
   {
      next = (*node).next;
      node_dispose( node );
      node = next;
   }
   
   (*queue).count = 0;
   (*queue).first = NULL;
   (*queue).last = NULL;
   
   INVARIANT( queue );
   POSTCONDITION( "queue is empty", (*queue).count == 0 );
   UNLOCK( (*queue).mutex );
   
   return;
}

/**
   Queue_wipe_out_and_dispose
*/

void
Queue_wipe_out_and_dispose( Prefix )( Queue_type( Prefix ) *queue )
{
   PRECONDITION( "queue not null", queue != NULL );
   PRECONDITION( "queue type OK", ( (*queue).type == QUEUE_TYPE ) && ( (*queue).item_type == Type_Code ) );
   LOCK( (*queue).mutex );
   INVARIANT( queue );
   
   node_t *node = (*queue).first;
   node_t *next = NULL;
  
   // remove all nodes   
   while ( node != NULL )
   {
      next = (*node).next;
      VALUE_DISPOSE_FUNCTION( (*node).value );
      node_dispose( node );
      node = next;
   }
   
   (*queue).count = 0;
   (*queue).first = NULL;
   (*queue).last = NULL;
   
   INVARIANT( queue );
   POSTCONDITION( "queue is empty", (*queue).count == 0 );
   UNLOCK( (*queue).mutex );
   
   return;
}


/* End of file */

