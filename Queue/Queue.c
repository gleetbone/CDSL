/**
 @file Queue.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Queues (queue that can be added to on one end and popped on the other)"

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
   int32_t _type;
   int32_t _item_type;

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
   CHECK( "node allocated correctly", node != NULL );

   return node;
}

/**
   node_dispose
*/

static
void
node_dispose( node_t **node )
{
   PRECONDITION( "node not null", node != NULL );
   PRECONDITION( "node not null", *node != NULL );

   free(*node);

   *node = NULL;

   return;
}

/**
   compare queue items to queue items

   compares items in current and other one by one, shallow equal

   @param current the queue to compare to
   @param other the queue to compare
   @return 1 if all itmes equal, 0 otherwise
*/

static
int32_t
compare_queue_items_to_queue_items
(
   Queue_type( Prefix ) *current,
   Queue_type( Prefix ) *other
)
{
   int32_t result = 1;
   int32_t flag = 0;
   node_t *node_1 = NULL;
   node_t *node_2 = NULL;

   node_1 = (*current).first;
   node_2 = (*other).first;

   while( ( node_1 != NULL ) && ( node_2 != NULL ) )
   {
      if ( ( *node_1 ).value == ( *node_2 ).value )
      {
         flag = flag + 1;
      }
      node_1 = ( *node_1 ).next;
      node_2 = ( *node_2 ).next;
   }

   if ( ( flag == (*current).count ) && ( flag == (*other).count ) )
   {
      result = 1;
   }

   return result;
}

/**
   compare queue items to queue items deep equal

   compares items in current and other one by one, deep equal

   @param current the queue to compare to
   @param other the queue to compare
   @return 1 if all itmes equal, 0 otherwise
*/

static
int32_t
compare_queue_items_to_queue_items_deep_equal
(
   Queue_type( Prefix ) *current,
   Queue_type( Prefix ) *other
)
{
   int32_t result = 1;
   int32_t flag = 0;
   node_t *node_1 = NULL;
   node_t *node_2 = NULL;

   node_1 = (*current).first;
   node_2 = (*other).first;

   while( ( node_1 != NULL ) && ( node_2 != NULL ) )
   {
      if ( VALUE_DEEP_EQUAL_FUNCTION( ( *node_1 ).value, ( *node_2 ).value ) == 1 )
      {
         flag = flag + 1;
      }
      node_1 = ( *node_1 ).next;
      node_2 = ( *node_2 ).next;
   }

   if ( ( flag == (*current).count ) && ( flag == (*other).count ) )
   {
      result = 1;
   }

   return result;
}

/**
   put

   put a new value into the queue at the end

   @param current the queue
   @param value the value to put into the queue
*/
static
void
put( Queue_type( Prefix ) *current, Type value )
{
   node_t *node = (*current).last;

   if ( node == NULL )
   {
      // current is empty, make this the first item
      node_t *new_node = node_make();
      ( *new_node ).value = value;
      (*current).first = new_node;
      (*current).last = new_node;
      (*current).count = 1;
   }
   else
   {
      node_t *new_node = node_make();
      ( *new_node ).value = value;

      ( *(*current).last ).next = new_node;
      ( *new_node ).next = NULL;
      (*current).last = new_node;

      (*current).count = (*current).count + 1;

   }

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
      result = ( ( *(*p).last ).next == NULL ) ;
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
   assert( ( ( void ) "empty implies first and last null", is_empty_implies_first_and_last_null( p ) ) );
   assert( ( ( void ) "last next is null", last_next_is_null( p ) ) );
   assert( ( ( void ) "nonnegative count", nonnegative_count( p ) ) );
   assert( ( ( void ) "valid count", valid_count( p ) ) );
   return;
}

#endif

/**
   Queue_make
*/

Queue_type( Prefix ) *
Queue_make( Prefix )( void )
{
   // allocate result struct
   Queue_type( Prefix ) * result
      = ( Queue_type( Prefix ) * ) calloc( 1, sizeof( Queue_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = QUEUE_TYPE;
   (*result)._item_type = Type_Code;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Queue_clone
*/

Queue_type( Prefix ) *
Queue_clone( Prefix )( Queue_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type == Type_Code ) );

   int32_t i = 0;
   node_t *node = NULL;

   // allocate queue struct
   Queue_type( Prefix ) * result
      = ( Queue_type( Prefix ) * ) calloc( 1, sizeof( Queue_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type codes
   (*result)._type = QUEUE_TYPE;
   (*result)._item_type = Type_Code;

   // copy from current
   LOCK( (*current).mutex );

   node = (*current).first;

   for ( i = 0; i < (*current).count; i++ )
   {
      put( result, (*node).value );
      node = (*node).next;
   }

   (*result).last = node;

   (*result).count = (*current).count;

   UNLOCK( (*current).mutex );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new queue contains elements of current", compare_queue_items_to_queue_items( result, current ) );

   INVARIANT( result );

   return result;
}

/**
   Queue_deep_clone
*/

Queue_type( Prefix ) *
Queue_deep_clone( Prefix )( Queue_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type == Type_Code ) );

   int32_t i = 0;
   node_t *node = NULL;
   Type v;

   // allocate queue struct
   Queue_type( Prefix ) * result
      = ( Queue_type( Prefix ) * ) calloc( 1, sizeof( Queue_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type codes
   (*result)._type = QUEUE_TYPE;
   (*result)._item_type = Type_Code;

   // set built-in cursor

   // copy from "queue"
   LOCK( (*current).mutex );

   node = (*current).first;

   for ( i = 0; i < (*current).count; i++ )
   {
      v = VALUE_DEEP_CLONE_FUNCTION( (*node).value );
      put( result, v );
      node = (*node).next;
   }

   (*result).last = node;

   (*result).count = (*current).count;

   UNLOCK( (*current).mutex );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new queue contains elements deep equal to current", compare_queue_items_to_queue_items_deep_equal( result, current ) );

   INVARIANT( result );

   return result;
}

/**
   Queue_is_equal
*/

int32_t
Queue_is_equal( Prefix )( Queue_type( Prefix ) *current, Queue_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == QUEUE_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t result = 1;
   int32_t count = 0;
   node_t *node_1 = NULL;
   node_t *node_2 = NULL;

   // check count
   if ( (*current).count != (*other).count )
   {
      result = 0;
   }

   // lock other
   LOCK( (*other).mutex );

   node_1 = (*current).first;
   node_2 = (*other).first;

   while( ( node_1 != NULL ) && ( node_2 != NULL ) )
   {
      if ( result == 1 )
      {
         if ( ( *node_1 ).value != ( *node_2 ).value )
         {
            result = 0;
            break;
         }
         else
         {
            count = count + 1;
         }
      }

      node_1 = ( *node_1 ).next;
      node_2 = ( *node_2 ).next;

   }

   if ( count != (*current).count )
   {
      result = 0;
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return result;
}

/**
   Queue_is_deep_equal
*/

int32_t
Queue_is_deep_equal( Prefix )( Queue_type( Prefix ) *current, Queue_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == QUEUE_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t result = 1;
   int32_t count = 0;
   node_t *node_1 = NULL;
   node_t *node_2 = NULL;

   // check count
   if ( (*current).count != (*other).count )
   {
      result = 0;
   }

   // lock other
   LOCK( (*other).mutex );

   node_1 = (*current).first;
   node_2 = (*other).first;

   while( ( node_1 != NULL ) && ( node_2 != NULL ) )
   {
      if ( result == 1 )
      {
         if ( VALUE_DEEP_EQUAL_FUNCTION( ( *node_1 ).value, ( *node_2 ).value ) == 0 )
         {
            result = 0;
            break;
         }
         else
         {
            count = count + 1;
         }
      }

      node_1 = ( *node_1 ).next;
      node_2 = ( *node_2 ).next;

   }

   if ( count != (*current).count )
   {
      result = 0;
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return result;
}

/**
   Queue_copy
*/

void
Queue_copy( Prefix )( Queue_type( Prefix ) *current, Queue_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == QUEUE_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t i = 0;
   node_t *node = NULL;
   node_t *next = NULL;

   // empty out current

   // remove all nodes
   node = (*current).first;
   while( node != NULL )
   {
      next = (*node).next;
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
      node_dispose( &node );
      node = next;
   }

   // lock other
   LOCK( (*other).mutex );

   // reset count
   (*current).count = 0;

   node = (*other).first;

   for ( i = 0; i < (*other).count; i++ )
   {
      put( current, (*node).value );
      node = (*node).next;
   }

   (*current).last = node;

   if ( (*other).count == 0 )
   {
      (*current).first = NULL;
   }

   POSTCONDITION( "new queue contains elements of other", compare_queue_items_to_queue_items( current, other ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return;
}

/**
   Queue_deep_copy
*/

void
Queue_deep_copy( Prefix )( Queue_type( Prefix ) *current, Queue_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == QUEUE_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t i = 0;
   node_t *node = NULL;
   node_t *next = NULL;
   Type v;

   // empty out current

   // remove all nodes
   node = (*current).first;
   while( node != NULL )
   {
      next = (*node).next;
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
      node_dispose( &node );
      node = next;
   }

   // lock other
   LOCK( (*other).mutex );

   // reset count
   (*current).count = 0;

   node = (*other).first;

   for ( i = 0; i < (*other).count; i++ )
   {
      v = VALUE_DEEP_CLONE_FUNCTION( (*node).value );
      put( current, v );
      node = (*node).next;
   }

   (*current).last = node;

   if ( (*other).count == 0 )
   {
      (*current).first = NULL;
   }

   POSTCONDITION( "new queue contains elements of other", compare_queue_items_to_queue_items_deep_equal( current, other ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return;
}

/**
   Queue_dispose
*/

void
Queue_dispose( Prefix )( Queue_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", ( (**current)._type == QUEUE_TYPE ) && ( (**current)._item_type == Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete current items
   node_t *item = (**current).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      node_dispose( &item );
      item = next;
   }

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   Queue_deep_dispose
*/

void
Queue_deep_dispose( Prefix )( Queue_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", ( (**current)._type == QUEUE_TYPE ) && ( (**current)._item_type == Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete current items
   node_t *item = (**current).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      VALUE_DISPOSE_FUNCTION( (*item).value );
      node_dispose( &item );
      item = next;
   }

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   Queue_item
*/

Type
Queue_item( Prefix )( Queue_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );

   Type value = ( *(*current).first ).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   Queue_count
*/

int32_t
Queue_count( Prefix )( Queue_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Queue_is_empty
*/

int32_t
Queue_is_empty( Prefix )( Queue_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Queue_put
*/

void
Queue_put( Prefix )( Queue_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   put( current, value );
   /*
      node_t *node = (*current).last;

      if ( node == NULL )
      {
         // current is empty, make this the first item
         node_t *new_node = node_make();
         ( *new_node ).value = value;
         (*current).first = new_node;
         (*current).last = new_node;
         (*current).count = 1;
      }
      else
      {
         node_t *new_node = node_make();
         ( *new_node ).value = value;

         ( *(*current).last ).next = new_node;
         ( *new_node ).next = NULL;
         (*current).last = new_node;

         (*current).count = (*current).count + 1;

      }
   */
   INVARIANT( current );
   POSTCONDITION( "last is put item", ( *(*current).last ).value = value );
   POSTCONDITION( "current not empty", (*current).count > 0 );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Queue_remove
*/

void
Queue_remove( Prefix )( Queue_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not empty", (*current).count > 0 );
   INVARIANT( current );

   node_t *node = (*current).first;

   // remove the node
   if ( node != NULL )
   {
      (*current).first = (*node).next;
      (*current).count = (*current).count - 1;
      node_dispose( &node );

      // if current is now empty, set last to NULL
      if ( (*current).count == 0 )
      {
         (*current).last = NULL;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Queue_remove_and_dispose
*/

void
Queue_remove_and_dispose( Prefix )( Queue_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not empty", (*current).count > 0 );
   INVARIANT( current );

   node_t *node = (*current).first;

   // remove the node
   if ( node != NULL )
   {
      (*current).first = (*node).next;
      (*current).count = (*current).count - 1;
      VALUE_DISPOSE_FUNCTION( (*node).value );
      node_dispose( &node );

      // if current is now empty, set last to NULL
      if ( (*current).count == 0 )
      {
         (*current).last = NULL;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Queue_prune
*/

void
Queue_prune( Prefix )( Queue_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not empty", (*current).count > 0 );
   PRECONDITION( "current has enough items", (*current).count >= count );
   INVARIANT( current );

   int32_t i = 0;
   node_t *node = NULL;

   // remove the node
   for( i = 0; i < count; i++ )
   {
      node = (*current).first;

      if ( node != NULL )
      {
         (*current).first = (*node).next;
         (*current).count = (*current).count - 1;
         node_dispose( &node );
      }
   }

   // if current is now empty, set last to NULL
   if ( (*current).count == 0 )
   {
      (*current).last = NULL;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Queue_prune_and_dispose
*/

void
Queue_prune_and_dispose( Prefix )( Queue_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current has enough items", (*current).count >= count );
   INVARIANT( current );

   int32_t i = 0;
   node_t *node = NULL;

   // remove the node
   for( i = 0; i < count; i++ )
   {
      node = (*current).first;

      if ( node != NULL )
      {
         (*current).first = (*node).next;
         (*current).count = (*current).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
      }
   }

   // if current is now empty, set last to NULL
   if ( (*current).count == 0 )
   {
      (*current).last = NULL;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Queue_keep
*/

void
Queue_keep( Prefix )( Queue_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current has enough items", (*current).count >= count );
   INVARIANT( current );

   int32_t i = 0;
   int32_t n = (*current).count - count;

   node_t *node = NULL;

   // remove n nodes
   for( i = 0; i < n; i++ )
   {
      node = (*current).first;

      if ( node != NULL )
      {
         (*current).first = (*node).next;
         (*current).count = (*current).count - 1;
         node_dispose( &node );
      }
   }

   // if current is now empty, set last to NULL
   if ( (*current).count == 0 )
   {
      (*current).last = NULL;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Queue_keep_and_dispose
*/

void
Queue_keep_and_dispose( Prefix )( Queue_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current has enough items", (*current).count >= count );
   INVARIANT( current );

   int32_t i = 0;
   int32_t n = (*current).count - count;

   node_t *node = NULL;

   // remove n nodes
   for( i = 0; i < n; i++ )
   {
      node = (*current).first;

      if ( node != NULL )
      {
         (*current).first = (*node).next;
         (*current).count = (*current).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
      }
   }

   // if current is now empty, set last to NULL
   if ( (*current).count == 0 )
   {
      (*current).last = NULL;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Queue_wipe_out
*/

void
Queue_wipe_out( Prefix )( Queue_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   node_t *node = (*current).first;
   node_t *next = NULL;

   // remove all nodes
   while ( node != NULL )
   {
      next = (*node).next;
      node_dispose( &node );
      node = next;
   }

   (*current).count = 0;
   (*current).first = NULL;
   (*current).last = NULL;

   INVARIANT( current );
   POSTCONDITION( "current is empty", (*current).count == 0 );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Queue_wipe_out_and_dispose
*/

void
Queue_wipe_out_and_dispose( Prefix )( Queue_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == QUEUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   node_t *node = (*current).first;
   node_t *next = NULL;

   // remove all nodes
   while ( node != NULL )
   {
      next = (*node).next;
      VALUE_DISPOSE_FUNCTION( (*node).value );
      node_dispose( &node );
      node = next;
   }

   (*current).count = 0;
   (*current).first = NULL;
   (*current).last = NULL;

   INVARIANT( current );
   POSTCONDITION( "current is empty", (*current).count == 0 );
   UNLOCK( (*current).mutex );

   return;
}


/* End of file */

