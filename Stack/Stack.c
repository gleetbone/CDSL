/**
 @file Stack.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Stacks"

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

 Function definitions for the opaque Stack_t type.

*/

#include "Stack.h"

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
   Stack structure
*/

struct Stack_struct( Prefix )
{
   int32_t _type;
   int32_t _item_type;

   node_t *first;
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
   PRECONDITION( "*node not null", *node != NULL );
   
   free(*node);
   *node = NULL;
   
   return;
}

/**
   compare stack items to stack items

   compares items in current and other one by one, shallow equal

   @param current the stack to compare to
   @param other the stack to compare
   @return 1 if all itmes equal, 0 otherwise
*/

static
int32_t
compare_stack_items_to_stack_items
(
   Stack_type( Prefix ) *current,
   Stack_type( Prefix ) *other
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
   compare stack items to stack items deep equal

   compares items in current and other one by one, deep equal

   @param current the stack to compare to
   @param other the stack to compare
   @return 1 if all itmes equal, 0 otherwise
*/

static
int32_t
compare_stack_items_to_stack_items_deep_equal
(
   Stack_type( Prefix ) *current,
   Stack_type( Prefix ) *other
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

   put a new value into the stack

   @param current the stack
   @param value the value to put into the stack
*/
static
void
put( Stack_type( Prefix ) *current, Type value )
{
   node_t *node = (*current).first;

   if ( node == NULL )
   {
      // current is empty, make this the first item
      node_t *new_node = node_make();
      ( *new_node ).value = value;
      (*current).first = new_node;
      (*current).count = 1;
   }
   else
   {
      node_t *new_node = node_make();
      ( *new_node ).value = value;

      ( *new_node ).next = node;
      (*current).first = new_node;

      (*current).count = (*current).count + 1;

   }

   return;
}

/**
   put_last

   put a new value into the stack at the end

   @param current the stack
   @param value the value to put into the stack
*/
static
void
put_last( Stack_type( Prefix ) *current, Type value )
{
   node_t *node = (*current).first;
   node_t *next_node = NULL;
   node_t *new_node = NULL;

   if ( node == NULL )
   {
      // current is empty, make this the first item
      node_t *new_node = node_make();
      ( *new_node ).value = value;
      (*current).first = new_node;
      (*current).count = 1;
   }
   else
   {
      // find end of list
      next_node = (*node).next;
      while( next_node != NULL )
      {
         node = next_node;
         next_node = ( *next_node ).next;
      }

      // make new node to hold value
      new_node = node_make();
      ( *new_node ).value = value;
      ( *new_node ).next = NULL;

      // put new node at end of list
      (*node).next = new_node;

      // increment current count
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
is_empty_implies_first_null( Stack_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).count == 0 )
   {
      result = ( (*p).first == NULL );
   }

   return result;
}

static
int32_t
nonnegative_count( Stack_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
valid_count( Stack_type( Prefix ) *p )
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
void invariant( Stack_type( Prefix ) *p )
{
   assert( ( ( void ) "empty implies first null", is_empty_implies_first_null( p ) ) );
   assert( ( ( void ) "nonnegative count", nonnegative_count( p ) ) );
   assert( ( ( void ) "valid count", valid_count( p ) ) );
   return;
}

#endif

/**
   Stack_make
*/

Stack_type( Prefix ) *
Stack_make( Prefix )( void )
{
   // allocate stack struct
   Stack_type( Prefix ) * result
      = ( Stack_type( Prefix ) * ) calloc( 1, sizeof( Stack_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );
      
   // set type
   (*result)._type = STACK_TYPE;
   (*result)._item_type = Type_Code;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Stack_clone
*/

Stack_type( Prefix ) *
Stack_clone( Prefix )( Stack_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );

   int32_t i = 0;
   node_t *node = NULL;

   // allocate stack struct
   Stack_type( Prefix ) * result
      = ( Stack_type( Prefix ) * ) calloc( 1, sizeof( Stack_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type codes
   (*result)._type = STACK_TYPE;
   (*result)._item_type = Type_Code;

   // copy from current
   LOCK( (*current).mutex );

   node = (*current).first;

   for ( i = 0; i < (*current).count; i++ )
   {
      put_last( result, (*node).value );
      node = (*node).next;
   }

   (*result).count = (*current).count;

   UNLOCK( (*current).mutex );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new stack contains elements of current", compare_stack_items_to_stack_items( result, current ) );

   INVARIANT( result );

   return result;
}

/**
   Stack_deep_clone
*/

Stack_type( Prefix ) *
Stack_deep_clone( Prefix )( Stack_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );

   int32_t i = 0;
   node_t *node = NULL;
   Type v;

   // allocate stack struct
   Stack_type( Prefix ) * result
      = ( Stack_type( Prefix ) * ) calloc( 1, sizeof( Stack_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type codes
   (*result)._type = STACK_TYPE;
   (*result)._item_type = Type_Code;

   // set built-in cursor

   // copy from "stack"
   LOCK( (*current).mutex );

   node = (*current).first;

   for ( i = 0; i < (*current).count; i++ )
   {
      v = VALUE_DEEP_CLONE_FUNCTION( (*node).value );
      put_last( result, v );
      node = (*node).next;
   }

   UNLOCK( (*current).mutex );

   (*result).count = (*current).count;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new stack contains elements deep equal to current", compare_stack_items_to_stack_items_deep_equal( result, current ) );

   INVARIANT( result );

   return result;
}

/**
   Stack_is_equal
*/

int32_t
Stack_is_equal( Prefix )( Stack_type( Prefix ) *current, Stack_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == STACK_TYPE ) && ( (*other)._item_type = Type_Code ) );

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
   Stack_is_deep_equal
*/

int32_t
Stack_is_deep_equal( Prefix )( Stack_type( Prefix ) *current, Stack_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == STACK_TYPE ) && ( (*other)._item_type = Type_Code ) );

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
   Stack_copy
*/

void
Stack_copy( Prefix )( Stack_type( Prefix ) *current, Stack_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == STACK_TYPE ) && ( (*other)._item_type = Type_Code ) );

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
      put_last( current, (*node).value );
      node = (*node).next;
   }

   if ( (*other).count == 0 )
   {
      (*current).first = NULL;
   }

   POSTCONDITION( "new stack contains elements of other", compare_stack_items_to_stack_items( current, other ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return;
}

/**
   Stack_deep_copy
*/

void
Stack_deep_copy( Prefix )( Stack_type( Prefix ) *current, Stack_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == STACK_TYPE ) && ( (*other)._item_type = Type_Code ) );

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
      put_last( current, v );
      node = (*node).next;
   }

   if ( (*other).count == 0 )
   {
      (*current).first = NULL;
   }

   POSTCONDITION( "new stack contains elements of other", compare_stack_items_to_stack_items_deep_equal( current, other ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return;
}

/**
   Stack_dispose
*/

void
Stack_dispose( Prefix )( Stack_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", ( (**current)._type == STACK_TYPE ) && ( (**current)._item_type == Type_Code ) );
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
   Stack_deep_dispose
*/

void
Stack_deep_dispose( Prefix )( Stack_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", ( (**current)._type == STACK_TYPE ) && ( (**current)._item_type == Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete current items
   node_t *item = (**current).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      VALUE_DEEP_DISPOSE_FUNCTION( (*item).value );
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
   Stack_item
*/

Type
Stack_item( Prefix )( Stack_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not empty", (*current).count > 0 );
   INVARIANT( current );

   Type value = ( *(*current).first ).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   Stack_count
*/

int32_t
Stack_count( Prefix )( Stack_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Stack_is_empty
*/

int32_t
Stack_is_empty( Prefix )( Stack_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Stack_put
*/

void
Stack_put( Prefix )( Stack_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   put( current, value );

   INVARIANT( current );
   POSTCONDITION( "first is put item", ( *(*current).first ).value == value );
   POSTCONDITION( "current not empty", (*current).count > 0 );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Stack_replace
*/

void
Stack_replace( Prefix )( Stack_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not empty", (*current).count > 0 );
   INVARIANT( current );

   node_t *node = (*current).first;

   if ( node != NULL )
   {
      (*node).value = value;
   }

   INVARIANT( current );
   POSTCONDITION( "first is replace item", ( *(*current).first ).value == value );
   POSTCONDITION( "current not empty", (*current).count > 0 );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Stack_replace_and_dispose
*/

void
Stack_replace_and_dispose( Prefix )( Stack_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not empty", (*current).count > 0 );
   INVARIANT( current );

   node_t *node = (*current).first;

   if ( node != NULL )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
      (*node).value = value;
   }

   INVARIANT( current );
   POSTCONDITION( "first is replace item", ( *(*current).first ).value == value );
   POSTCONDITION( "current not empty", (*current).count > 0 );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Stack_remove
*/

void
Stack_remove( Prefix )( Stack_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Stack_remove_and_dispose
*/

void
Stack_remove_and_dispose( Prefix )( Stack_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not empty", (*current).count > 0 );
   INVARIANT( current );

   node_t *node = (*current).first;

   // remove the node
   if ( node != NULL )
   {
      (*current).first = (*node).next;
      (*current).count = (*current).count - 1;
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
      node_dispose( &node );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Stack_prune
*/

void
Stack_prune( Prefix )( Stack_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
         node_dispose( &node );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Stack_prune_and_dispose
*/

void
Stack_prune_and_dispose( Prefix )( Stack_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
         VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Stack_keep
*/

void
Stack_keep( Prefix )( Stack_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );
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

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Stack_keep_and_dispose
*/

void
Stack_keep_and_dispose( Prefix )( Stack_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
         VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Stack_wipe_out
*/

void
Stack_wipe_out( Prefix )( Stack_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );
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

   INVARIANT( current );
   POSTCONDITION( "current is empty", (*current).count == 0 );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Stack_wipe_out_and_dispose
*/

void
Stack_wipe_out_and_dispose( Prefix )( Stack_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == STACK_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   node_t *node = (*current).first;
   node_t *next = NULL;

   // remove all nodes
   while ( node != NULL )
   {
      next = (*node).next;
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
      node_dispose( &node );
      node = next;
   }

   (*current).count = 0;
   (*current).first = NULL;

   INVARIANT( current );
   POSTCONDITION( "current is empty", (*current).count == 0 );
   UNLOCK( (*current).mutex );

   return;
}


/* End of file */

