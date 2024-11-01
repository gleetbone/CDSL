/**
 @file Deque.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Deques (stack that can be appended to or popped from either end)"

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

 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE AUTHORS BE LIABLE TO ANY PARTY FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES ARISING IN ANY WAY OUT OF THE USE OF THIS PACKAGE.

 @section Description

 Function definitions for the opaque Deque_t type.

*/

#include "Deque.h"

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
   struct node *prev;
   struct node *next;
   Type value;
};

typedef struct node node_t;

/**
   Deque structure
*/

struct Deque_struct( Prefix )
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
   CHECK( "node not null", node != NULL );
   
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
is_empty_implies_first_and_last_null( Deque_type( Prefix ) *p )
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
last_next_is_null( Deque_type( Prefix ) *p )
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
first_prev_is_null( Deque_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).first != NULL )
   {
      result = ( ( *(*p).first ).prev == NULL ) ;
   }

   return result;
}

static
int32_t
nonnegative_count( Deque_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
valid_count_forward( Deque_type( Prefix ) *p )
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
valid_count_backward( Deque_type( Prefix ) *p )
{
   int32_t result = 1;
   int32_t n = 0;

   node_t *node = (*p).last;

   while( node != NULL )
   {
      n = n + 1;
      node = (*node).prev;
   }

   result = ( n == (*p).count );

   return result;
}

static
void invariant( Deque_type( Prefix ) *p )
{
   assert( ( ( void ) "empty implies first and last null", is_empty_implies_first_and_last_null( p ) ) );
   assert( ( ( void ) "last next is null", last_next_is_null( p ) ) );
   assert( ( ( void ) "first prev is null", first_prev_is_null( p ) ) );
   assert( ( ( void ) "nonnegative count", nonnegative_count( p ) ) );
   assert( ( ( void ) "valid count forward", valid_count_forward( p ) ) );
   assert( ( ( void ) "valid count backward", valid_count_backward( p ) ) );
   return;
}

#endif

/**
   Deque_make
*/

Deque_type( Prefix ) *
Deque_make( Prefix )( void )
{
   // allocate deque struct
   Deque_type( Prefix ) * deque
      = ( Deque_type( Prefix ) * ) calloc( 1, sizeof( Deque_type( Prefix ) ) );
   CHECK( "deque allocated correctly", deque != NULL );
      
   // set type
   (*deque)._type = DEQUE_TYPE;
   (*deque)._item_type = Type_Code;

   MULTITHREAD_MUTEX_INIT( (*deque).mutex );

   INVARIANT( deque );

   return deque;
}

/**
   Deque_clone
*/

Deque_type( Prefix ) *
Deque_clone( Prefix )( Deque_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == DEQUE_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*other).mutex );
   INVARIANT( other );

   node_t *node = NULL;
   node_t *n1 = NULL;
   node_t *n2 = NULL;

   // allocate deque struct
   Deque_type( Prefix ) * result
      = ( Deque_type( Prefix ) * ) calloc( 1, sizeof( Deque_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DEQUE_TYPE;
   (*result)._item_type = Type_Code;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // set internal data
   (*result).count = (*other).count;

   node = (*other).first;

   while( node != NULL )
   {
      n1 = node_make();
      if ( (*result).first == NULL )
      {
         (*result).first = n1;
      }

      (*n1).prev = n2;
      if ( n2 != NULL )
      {
         ( *(*n1).prev ).next = n1;
      }
      (*n1).value = (*node).value;
      n2 = n1;
      node = (*node).next;

      if ( ( node == NULL ) && ( (*result).last == NULL ) )
      {
         (*result).last = n1;
      }
   }

   INVARIANT( result );
   INVARIANT( other );
   UNLOCK( (*other).mutex );


   return result;
}

/**
   Deque_deep_clone
*/

Deque_type( Prefix ) *
Deque_deep_clone( Prefix )( Deque_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == DEQUE_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*other).mutex );
   INVARIANT( other );

   node_t *node = NULL;
   node_t *n1 = NULL;
   node_t *n2 = NULL;

   // allocate deque struct
   Deque_type( Prefix ) * result
      = ( Deque_type( Prefix ) * ) calloc( 1, sizeof( Deque_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = DEQUE_TYPE;
   (*result)._item_type = Type_Code;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // set internal data
   (*result).count = (*other).count;

   node = (*other).first;

   while( node != NULL )
   {
      n1 = node_make();
      if ( (*result).first == NULL )
      {
         (*result).first = n1;
      }

      (*n1).prev = n2;
      if ( n2 != NULL )
      {
         ( *(*n1).prev ).next = n1;
      }
      (*n1).value = VALUE_DEEP_CLONE_FUNCTION( (*node).value );
      n2 = n1;
      node = (*node).next;

      if ( ( node == NULL ) && ( (*result).last == NULL ) )
      {
         (*result).last = n1;
      }
   }

   INVARIANT( result );
   INVARIANT( other );
   UNLOCK( (*other).mutex );


   return result;
}

/**
   Deque_copy
*/

void
Deque_copy( Prefix )( Deque_type( Prefix ) *current, Deque_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == DEQUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == DEQUE_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( other );

   node_t *node = NULL;
   node_t *n1 = NULL;
   node_t *n2 = NULL;

   // delete current deque items
   node_t *item = (*current).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      VALUE_DISPOSE_FUNCTION( (*item).value );
      node_dispose( item );
      item = next;
   }

   // copy internal data
   (*current).count = (*other).count;
   (*current).first = NULL;
   (*current).last = NULL;

   node = (*other).first;

   while( node != NULL )
   {
      n1 = node_make();
      if ( (*current).first == NULL )
      {
         (*current).first = n1;
      }

      (*n1).prev = n2;
      if ( n2 != NULL )
      {
         ( *(*n1).prev ).next = n1;
      }
      (*n1).value = (*node).value;
      n2 = n1;
      node = (*node).next;

      if ( ( node == NULL ) && ( (*current).last == NULL ) )
      {
         (*current).last = n1;
      }
   }

   INVARIANT( current );
   INVARIANT( other );
   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );


   return;
}

/**
   Deque_deep_copy
*/

void
Deque_deep_copy( Prefix )( Deque_type( Prefix ) *current, Deque_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == DEQUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == DEQUE_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( other );

   node_t *node = NULL;
   node_t *n1 = NULL;
   node_t *n2 = NULL;

   // delete current deque items
   node_t *item = (*current).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      VALUE_DISPOSE_FUNCTION( (*item).value );
      node_dispose( item );
      item = next;
   }

   // copy internal data
   (*current).count = (*other).count;
   (*current).first = NULL;
   (*current).last = NULL;

   node = (*other).first;

   while( node != NULL )
   {
      n1 = node_make();
      if ( (*current).first == NULL )
      {
         (*current).first = n1;
      }

      (*n1).prev = n2;
      if ( n2 != NULL )
      {
         ( *(*n1).prev ).next = n1;
      }
      (*n1).value = VALUE_DEEP_CLONE_FUNCTION( (*node).value );
      n2 = n1;
      node = (*node).next;

      if ( ( node == NULL ) && ( (*current).last == NULL ) )
      {
         (*current).last = n1;
      }
   }

   INVARIANT( current );
   INVARIANT( other );
   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );


   return;
}

/**
   Deque_is_equal
*/

int32_t
Deque_is_equal( Prefix )( Deque_type( Prefix ) *current, Deque_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == DEQUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == DEQUE_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( other );

   int32_t result = 1;
   int32_t count = 0;
   node_t *n1 = NULL;
   node_t *n2 = NULL;

   // check count
   if ( (*current).count != (*other).count )
   {
      result = 0;
   }

   if ( result == 1 )
   {

      n1 = (*current).first;
      n2 = (*other).first;

      while( ( n1 != NULL ) && ( n2 != NULL ) )
      {
         if ( result == 1 )
         {
            if ( (*n1).value != (*n2).value )
            {
               result = 0;
               break;
            }
            else
            {
               count = count + 1;
            }
         }

         n1 = (*n1).next;
         n2 = (*n2).next;

      }

   }

   INVARIANT( current );
   INVARIANT( other );
   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return result;
}

/**
   Deque_is_deep_equal
*/

int32_t
Deque_is_deep_equal( Prefix )( Deque_type( Prefix ) *current, Deque_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", ( (*current)._type == DEQUE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", ( (*other)._type == DEQUE_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( other );

   int32_t result = 1;
   int32_t count = 0;
   node_t *n1 = NULL;
   node_t *n2 = NULL;

   // check count
   if ( (*current).count != (*other).count )
   {
      result = 0;
   }

   if ( result == 1 )
   {

      n1 = (*current).first;
      n2 = (*other).first;

      while( ( n1 != NULL ) && ( n2 != NULL ) )
      {
         if ( result == 1 )
         {
            if ( VALUE_DEEP_EQUAL_FUNCTION( (*n1).value, (*n2).value ) == 0 )
            {
               result = 0;
               break;
            }
            else
            {
               count = count + 1;
            }
         }

         n1 = (*n1).next;
         n2 = (*n2).next;

      }

   }

   INVARIANT( current );
   INVARIANT( other );
   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return result;
}

/**
   Deque_dispose
*/

void
Deque_dispose( Prefix )( Deque_type( Prefix ) **deque )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque not null", *deque != NULL );
   PRECONDITION( "deque type OK", ( (**deque)._type == DEQUE_TYPE ) && ( (**deque)._item_type == Type_Code ) );
   LOCK( (**deque).mutex );
   INVARIANT(*deque);

   // delete deque items
   node_t *item = (**deque).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      node_dispose( item );
      item = next;
   }

   MULTITHREAD_MUTEX_DESTROY( (**deque).mutex );

   // delete deque struct
   free(*deque);

   // set deque to NULL
   deque = NULL;

   return;
}

/**
   Deque_deep_dispose
*/

void
Deque_deep_dispose( Prefix )( Deque_type( Prefix ) **deque )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque not null", *deque != NULL );
   PRECONDITION( "deque type OK", ( (**deque)._type == DEQUE_TYPE ) && ( (**deque)._item_type == Type_Code ) );
   LOCK( (**deque).mutex );
   INVARIANT(*deque);

   // delete deque items
   node_t *item = (**deque).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      VALUE_DISPOSE_FUNCTION( (*item).value );
      node_dispose( item );
      item = next;
   }

   MULTITHREAD_MUTEX_DESTROY( (**deque).mutex );

   // delete deque struct
   free(*deque);

   // set deque to NULL
   deque = NULL;

   return;
}

/**
   Deque_first
*/

Type
Deque_first( Prefix )( Deque_type( Prefix ) *deque )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );
   PRECONDITION( "deque not empty", (*deque).count > 0 );

   Type value = ( *(*deque).first ).value;

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return value;
}

/**
   Deque_last
*/

Type
Deque_last( Prefix )( Deque_type( Prefix ) *deque )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );
   PRECONDITION( "deque not empty", (*deque).count > 0 );

   Type value = ( *(*deque).last ).value;

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return value;
}

/**
   Deque_count
*/

int32_t
Deque_count( Prefix )( Deque_type( Prefix ) *deque )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );

   int32_t result = (*deque).count;

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return result;
}

/**
   Deque_is_empty
*/

int32_t
Deque_is_empty( Prefix )( Deque_type( Prefix ) *deque )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );

   int32_t result = ( (*deque).count == 0 );

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return result;
}

/**
   Deque_put_first
*/

void
Deque_put_first( Prefix )( Deque_type( Prefix ) *deque, Type value )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );

   node_t *node = (*deque).first;

   if ( node == NULL )
   {
      // deque is empty, make this the first item
      node_t *new_node = node_make();
      ( *new_node ).value = value;
      (*deque).first = new_node;
      (*deque).last = new_node;
      (*deque).count = 1;
   }
   else
   {
      node_t *new_node = node_make();
      ( *new_node ).value = value;

      ( *(*deque).first ).prev = new_node;
      ( *new_node ).next = (*deque).first;
      (*deque).first = new_node;

      (*deque).count = (*deque).count + 1;

   }

   INVARIANT( deque );
   POSTCONDITION( "first is put item", ( *(*deque).first ).value == value );
   POSTCONDITION( "deque not empty", (*deque).count > 0 );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_put_last
*/

void
Deque_put_last( Prefix )( Deque_type( Prefix ) *deque, Type value )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );

   node_t *node = (*deque).last;

   if ( node == NULL )
   {
      // deque is empty, make this the last item
      node_t *new_node = node_make();
      ( *new_node ).value = value;
      (*deque).first = new_node;
      (*deque).last = new_node;
      (*deque).count = 1;
   }
   else
   {
      node_t *new_node = node_make();
      ( *new_node ).value = value;

      ( *(*deque).last ).next = new_node;
      ( *new_node ).prev = (*deque).last;
      (*deque).last = new_node;

      (*deque).count = (*deque).count + 1;

   }

   INVARIANT( deque );
   POSTCONDITION( "last is put item", ( *(*deque).last ).value == value );
   POSTCONDITION( "deque not empty", (*deque).count > 0 );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_remove_first
*/

void
Deque_remove_first( Prefix )( Deque_type( Prefix ) *deque )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );
   PRECONDITION( "deque not empty", (*deque).count > 0 );

   node_t *node = (*deque).first;

   // remove the node
   if ( node != NULL )
   {
      (*deque).first = (*node).next;
      (*deque).count = (*deque).count - 1;
      if ( (*deque).first != NULL )
      {
         ( *(*deque).first ).prev = NULL;
      }
      node_dispose( node );

      // if deque is now empty, set last to NULL
      if ( (*deque).count == 0 )
      {
         (*deque).last = NULL;
      }
   }

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_remove_first_and_dispose
*/

void
Deque_remove_first_and_dispose( Prefix )( Deque_type( Prefix ) *deque )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );
   PRECONDITION( "deque not empty", (*deque).count > 0 );

   node_t *node = (*deque).first;

   // remove the node
   if ( node != NULL )
   {
      (*deque).first = (*node).next;
      (*deque).count = (*deque).count - 1;
      VALUE_DISPOSE_FUNCTION( (*node).value );
      if ( (*deque).first != NULL )
      {
         ( *(*deque).first ).prev = NULL;
      }
      node_dispose( node );

      // if deque is now empty, set last to NULL
      if ( (*deque).count == 0 )
      {
         (*deque).last = NULL;
      }
   }

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_remove_last
*/

void
Deque_remove_last( Prefix )( Deque_type( Prefix ) *deque )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );
   PRECONDITION( "deque not empty", (*deque).count > 0 );

   node_t *node = (*deque).last;

   // remove the node
   if ( node != NULL )
   {
      (*deque).last = (*node).prev;
      (*deque).count = (*deque).count - 1;
      if ( (*deque).last != NULL )
      {
         ( *(*deque).last ).next = NULL;
      }
      node_dispose( node );

      // if deque is now empty, set last to NULL
      if ( (*deque).count == 0 )
      {
         (*deque).first = NULL;
      }
   }

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_remove_last_and_dispose
*/

void
Deque_remove_last_and_dispose( Prefix )( Deque_type( Prefix ) *deque )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );
   PRECONDITION( "deque not empty", (*deque).count > 0 );

   node_t *node = (*deque).last;

   // remove the node
   if ( node != NULL )
   {
      (*deque).last = (*node).prev;
      (*deque).count = (*deque).count - 1;
      VALUE_DISPOSE_FUNCTION( (*node).value );
      if ( (*deque).last != NULL )
      {
         ( *(*deque).last ).next = NULL;
      }
      node_dispose( node );

      // if deque is now empty, set last to NULL
      if ( (*deque).count == 0 )
      {
         (*deque).first = NULL;
      }
   }

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_prune_first
*/

void
Deque_prune_first( Prefix )( Deque_type( Prefix ) *deque, int32_t count )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );
   PRECONDITION( "deque has enough items", (*deque).count >= count );

   int32_t i = 0;
   node_t *node = NULL;

   // remove the node
   for( i = 0; i < count; i++ )
   {
      node = (*deque).first;

      if ( node != NULL )
      {
         (*deque).first = (*node).next;
         if ( (*deque).first != NULL )
         {
            ( *(*deque).first ).prev = NULL;
         }
         (*deque).count = (*deque).count - 1;
         node_dispose( node );
      }
   }

   // if deque is now empty, set last to NULL
   if ( (*deque).count == 0 )
   {
      (*deque).last = NULL;
   }

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_prune_first_and_dispose
*/

void
Deque_prune_first_and_dispose( Prefix )( Deque_type( Prefix ) *deque, int32_t count )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );
   PRECONDITION( "deque has enough items", (*deque).count >= count );

   int32_t i = 0;
   node_t *node = NULL;

   // remove the node
   for( i = 0; i < count; i++ )
   {
      node = (*deque).first;

      if ( node != NULL )
      {
         (*deque).first = (*node).next;
         if ( (*deque).first != NULL )
         {
            ( *(*deque).first ).prev = NULL;
         }
         (*deque).count = (*deque).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
   }

   // if deque is now empty, set last to NULL
   if ( (*deque).count == 0 )
   {
      (*deque).last = NULL;
   }

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_prune_last
*/

void
Deque_prune_last( Prefix )( Deque_type( Prefix ) *deque, int32_t count )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );
   PRECONDITION( "deque has enough items", (*deque).count >= count );

   int32_t i = 0;
   node_t *node = NULL;

   // remove the node
   for( i = 0; i < count; i++ )
   {
      node = (*deque).last;

      if ( node != NULL )
      {
         (*deque).last = (*node).prev;
         if ( (*deque).last != NULL )
         {
            ( *(*deque).last ).next = NULL;
         }
         (*deque).count = (*deque).count - 1;
         node_dispose( node );
      }
   }

   // if deque is now empty, set last to NULL
   if ( (*deque).count == 0 )
   {
      (*deque).first = NULL;
   }

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_prune_last_and_dispose
*/

void
Deque_prune_last_and_dispose( Prefix )( Deque_type( Prefix ) *deque, int32_t count )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );
   PRECONDITION( "deque has enough items", (*deque).count >= count );

   int32_t i = 0;
   node_t *node = NULL;

   // remove the node
   for( i = 0; i < count; i++ )
   {
      node = (*deque).last;

      if ( node != NULL )
      {
         (*deque).last = (*node).prev;
         if ( (*deque).last != NULL )
         {
            ( *(*deque).last ).next = NULL;
         }
         (*deque).count = (*deque).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
   }

   // if deque is now empty, set last to NULL
   if ( (*deque).count == 0 )
   {
      (*deque).first = NULL;
   }

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_keep_first
*/

void
Deque_keep_first( Prefix )( Deque_type( Prefix ) *deque, int32_t count )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );
   PRECONDITION( "deque has enough items", (*deque).count >= count );

   int32_t i = 0;
   int32_t n = (*deque).count - count;

   node_t *node = NULL;

   // remove n nodes
   for( i = 0; i < n; i++ )
   {
      node = (*deque).last;

      if ( node != NULL )
      {
         (*deque).last = (*node).prev;
         if ( (*deque).last != NULL )
         {
            ( *(*deque).last ).next = NULL;
         }
         (*deque).count = (*deque).count - 1;
         node_dispose( node );
      }
   }

   // if deque is now empty, set last to NULL
   if ( (*deque).count == 0 )
   {
      (*deque).first = NULL;
   }

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_keep_first_and_dispose
*/

void
Deque_keep_first_and_dispose( Prefix )( Deque_type( Prefix ) *deque, int32_t count )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );
   PRECONDITION( "deque has enough items", (*deque).count >= count );

   int32_t i = 0;
   int32_t n = (*deque).count - count;

   node_t *node = NULL;

   // remove n nodes
   for( i = 0; i < n; i++ )
   {
      node = (*deque).last;

      if ( node != NULL )
      {
         (*deque).last = (*node).prev;
         if ( (*deque).last != NULL )
         {
            ( *(*deque).last ).next = NULL;
         }
         (*deque).count = (*deque).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
   }

   // if deque is now empty, set last to NULL
   if ( (*deque).count == 0 )
   {
      (*deque).first = NULL;
   }

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_keep_last
*/

void
Deque_keep_last( Prefix )( Deque_type( Prefix ) *deque, int32_t count )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );
   PRECONDITION( "deque has enough items", (*deque).count >= count );

   int32_t i = 0;
   int32_t n = (*deque).count - count;

   node_t *node = NULL;

   // remove n nodes
   for( i = 0; i < n; i++ )
   {
      node = (*deque).first;

      if ( node != NULL )
      {
         (*deque).first = (*node).next;
         if ( (*deque).first != NULL )
         {
            ( *(*deque).first ).prev = NULL;
         }
         (*deque).count = (*deque).count - 1;
         node_dispose( node );
      }
   }

   // if deque is now empty, set last to NULL
   if ( (*deque).count == 0 )
   {
      (*deque).last = NULL;
   }

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_keep_last_and_dispose
*/

void
Deque_keep_last_and_dispose( Prefix )( Deque_type( Prefix ) *deque, int32_t count )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );
   PRECONDITION( "deque has enough items", (*deque).count >= count );

   int32_t i = 0;
   int32_t n = (*deque).count - count;

   node_t *node = NULL;

   // remove n nodes
   for( i = 0; i < n; i++ )
   {
      node = (*deque).first;

      if ( node != NULL )
      {
         (*deque).first = (*node).next;
         if ( (*deque).first != NULL )
         {
            ( *(*deque).first ).prev = NULL;
         }
         (*deque).count = (*deque).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
   }

   // if deque is now empty, set last to NULL
   if ( (*deque).count == 0 )
   {
      (*deque).last = NULL;
   }

   INVARIANT( deque );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_wipe_out
*/

void
Deque_wipe_out( Prefix )( Deque_type( Prefix ) *deque )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );

   node_t *node = (*deque).first;
   node_t *next = NULL;

   // remove all nodes
   while ( node != NULL )
   {
      next = (*node).next;
      node_dispose( node );
      node = next;
   }

   (*deque).count = 0;
   (*deque).first = NULL;
   (*deque).last = NULL;

   INVARIANT( deque );
   POSTCONDITION( "deque is empty", (*deque).count == 0 );
   UNLOCK( (*deque).mutex );

   return;
}

/**
   Deque_wipe_out_and_dispose
*/

void
Deque_wipe_out_and_dispose( Prefix )( Deque_type( Prefix ) *deque )
{
   PRECONDITION( "deque not null", deque != NULL );
   PRECONDITION( "deque type OK", ( (*deque)._type == DEQUE_TYPE ) && ( (*deque)._item_type == Type_Code ) );
   LOCK( (*deque).mutex );
   INVARIANT( deque );

   node_t *node = (*deque).first;
   node_t *next = NULL;

   // remove all nodes
   while ( node != NULL )
   {
      next = (*node).next;
      VALUE_DISPOSE_FUNCTION( (*node).value );
      node_dispose( node );
      node = next;
   }

   (*deque).count = 0;
   (*deque).first = NULL;
   (*deque).last = NULL;

   INVARIANT( deque );
   POSTCONDITION( "deque is empty", (*deque).count == 0 );
   UNLOCK( (*deque).mutex );

   return;
}


/* End of file */

