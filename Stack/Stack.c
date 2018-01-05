/**
 @file Stack.c
 @author Greg Lee
 @version 1.0.0
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

#define STACK_TYPE 0xA5000804


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
   int32_t type;
   int32_t item_type;
   
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
   assert(((void) "empty implies first null", is_empty_implies_first_null( p ) ));
   assert(((void) "nonnegative count", nonnegative_count( p ) ));
   assert(((void) "valid count", valid_count( p ) ));
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
   Stack_type( Prefix ) * stack 
      = ( Stack_type( Prefix ) * ) calloc( 1, sizeof( Stack_type( Prefix ) ) );
      
   // set type
   (*stack).type = STACK_TYPE;
   (*stack).item_type = Type_Code;

   MULTITHREAD_MUTEX_INIT( (*stack).mutex );

   INVARIANT( stack );
   
   return stack;
}

/** 
   Stack_dispose
*/

void
Stack_dispose( Prefix )( Stack_type( Prefix ) *stack )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   INVARIANT( stack );
   
   // delete stack items
   node_t *item = (*stack).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      node_dispose( item );
      item = next;
   }

   MULTITHREAD_MUTEX_DESTROY( (*stack).mutex );

   // delete stack struct
   free( stack );

   return;
}

/** 
   Stack_dispose_with_contents
*/

void
Stack_dispose_with_contents( Prefix )( Stack_type( Prefix ) *stack )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   INVARIANT( stack );
   
   // delete stack items
   node_t *item = (*stack).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      VALUE_DISPOSE_FUNCTION( (*item).value );
      node_dispose( item );
      item = next;
   }

   MULTITHREAD_MUTEX_DESTROY( (*stack).mutex );

   // delete stack struct
   free( stack );

   return;
}

/**
   Stack_item
*/

Type 
Stack_item( Prefix )( Stack_type( Prefix ) *stack )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   PRECONDITION( "stack not empty", (*stack).count > 0 );
   INVARIANT( stack );
   
   Type value = (*(*stack).first).value;
   
   INVARIANT( stack );
   UNLOCK( (*stack).mutex );
   
   return value;
}

/**
   Stack_count
*/

int32_t
Stack_count( Prefix )( Stack_type( Prefix ) *stack )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   INVARIANT( stack );
   
   int32_t result = (*stack).count;
   
   INVARIANT( stack );
   UNLOCK( (*stack).mutex );
   
   return result;
}

/**
   Stack_is_empty
*/

int32_t
Stack_is_empty( Prefix )( Stack_type( Prefix ) *stack )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   INVARIANT( stack );
   
   int32_t result = ( (*stack).count == 0 );
   
   INVARIANT( stack );
   UNLOCK( (*stack).mutex );
   
   return result;
}

/**
   Stack_put
*/

void
Stack_put( Prefix )( Stack_type( Prefix ) *stack, Type value )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   INVARIANT( stack );
   
   node_t *node = (*stack).first;

       
   if ( node == NULL )
   {
      // stack is empty, make this the first item
      node_t *new_node = node_make();
      (*new_node).value = value;
      (*stack).first = new_node;
      (*stack).count = 1;
   }
   else
   {
      node_t *new_node = node_make();
      (*new_node).value = value;
     
      (*new_node).next = node;
      (*stack).first = new_node;
         
      (*stack).count = (*stack).count + 1;
      
   }
   
   INVARIANT( stack );
   POSTCONDITION( "first is put item", (*(*stack).first).value == value );
   POSTCONDITION( "stack not empty", (*stack).count > 0 );
   UNLOCK( (*stack).mutex );
   
   return;
}

/**
   Stack_replace
*/

void
Stack_replace( Prefix )( Stack_type( Prefix ) *stack, Type value )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   PRECONDITION( "stack not empty", (*stack).count > 0 );
   INVARIANT( stack );
   
   node_t *node = (*stack).first;
   
   if ( node != NULL )
   {
      (*node).value = value;
   }
   
   INVARIANT( stack );
   POSTCONDITION( "first is replace item", (*(*stack).first).value == value );
   POSTCONDITION( "stack not empty", (*stack).count > 0 );
   UNLOCK( (*stack).mutex );
   
   return;
}

/**
   Stack_replace_and_dispose
*/

void
Stack_replace_and_dispose( Prefix )( Stack_type( Prefix ) *stack, Type value )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   PRECONDITION( "stack not empty", (*stack).count > 0 );
   INVARIANT( stack );
   
   node_t *node = (*stack).first;
   
   if ( node != NULL )
   {
      VALUE_DISPOSE_FUNCTION( (*node).value );
      (*node).value = value;
   }
   
   INVARIANT( stack );
   POSTCONDITION( "first is replace item", (*(*stack).first).value == value );
   POSTCONDITION( "stack not empty", (*stack).count > 0 );
   UNLOCK( (*stack).mutex );
   
   return;
}

/**
   Stack_remove
*/

void
Stack_remove( Prefix )( Stack_type( Prefix ) *stack )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   PRECONDITION( "stack not empty", (*stack).count > 0 );
   INVARIANT( stack );
   
   node_t *node = (*stack).first;
   
   // remove the node
   if ( node != NULL )
   {
      (*stack).first = (*node).next;
      (*stack).count = (*stack).count - 1;
      node_dispose( node );
   }
   
   INVARIANT( stack );
   UNLOCK( (*stack).mutex );
   
   return;
}

/**
   Stack_remove_and_dispose
*/

void
Stack_remove_and_dispose( Prefix )( Stack_type( Prefix ) *stack )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   PRECONDITION( "stack not empty", (*stack).count > 0 );
   INVARIANT( stack );
   
   node_t *node = (*stack).first;
   
   // remove the node
   if ( node != NULL )
   {
      (*stack).first = (*node).next;
      (*stack).count = (*stack).count - 1;
      VALUE_DISPOSE_FUNCTION( (*node).value );
      node_dispose( node );
   }
   
   INVARIANT( stack );
   UNLOCK( (*stack).mutex );
   
   return;
}

/**
   Stack_prune
*/

void
Stack_prune( Prefix )( Stack_type( Prefix ) *stack, int32_t count )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   PRECONDITION( "stack has enough items", (*stack).count >= count );
   INVARIANT( stack );
   
   int32_t i = 0;
   node_t *node = NULL;
   
   // remove the node
   for( i=0; i < count; i++ )
   {
      node = (*stack).first;
      
      if ( node != NULL )
      {
         (*stack).first = (*node).next;
         (*stack).count = (*stack).count - 1;
         node_dispose( node );
      }
   }

   INVARIANT( stack );
   UNLOCK( (*stack).mutex );
   
   return;
}

/**
   Stack_prune_and_dispose
*/

void
Stack_prune_and_dispose( Prefix )( Stack_type( Prefix ) *stack, int32_t count )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   PRECONDITION( "stack has enough items", (*stack).count >= count );
   INVARIANT( stack );
   
   int32_t i = 0;
   node_t *node = NULL;
   
   // remove the node
   for( i=0; i < count; i++ )
   {
      node = (*stack).first;
      
      if ( node != NULL )
      {
         (*stack).first = (*node).next;
         (*stack).count = (*stack).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
   }

   INVARIANT( stack );
   UNLOCK( (*stack).mutex );
   
   return;
}

/**
   Stack_keep
*/

void
Stack_keep( Prefix )( Stack_type( Prefix ) *stack, int32_t count )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   PRECONDITION( "stack has enough items", (*stack).count >= count );
   INVARIANT( stack );
   
   int32_t i = 0;
   int32_t n = (*stack).count - count;
   
   node_t *node = NULL;
   
   // remove n nodes
   for( i=0; i < n; i++ )
   {
      node = (*stack).first;
      
      if ( node != NULL )
      {
         (*stack).first = (*node).next;
         (*stack).count = (*stack).count - 1;
         node_dispose( node );
      }
   }

   INVARIANT( stack );
   UNLOCK( (*stack).mutex );
   
   return;
}

/**
   Stack_keep_and_dispose
*/

void
Stack_keep_and_dispose( Prefix )( Stack_type( Prefix ) *stack, int32_t count )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   PRECONDITION( "stack has enough items", (*stack).count >= count );
   INVARIANT( stack );
   
   int32_t i = 0;
   int32_t n = (*stack).count - count;
   
   node_t *node = NULL;
   
   // remove n nodes
   for( i=0; i<n; i++ )
   {
      node = (*stack).first;
      
      if ( node != NULL )
      {
         (*stack).first = (*node).next;
         (*stack).count = (*stack).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
   }

   INVARIANT( stack );
   UNLOCK( (*stack).mutex );
   
   return;
}

/**
   Stack_wipe_out
*/

void
Stack_wipe_out( Prefix )( Stack_type( Prefix ) *stack )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   INVARIANT( stack );
   
   node_t *node = (*stack).first;
   node_t *next = NULL;
  
   // remove all nodes   
   while ( node != NULL )
   {
      next = (*node).next;
      node_dispose( node );
      node = next;
   }
   
   (*stack).count = 0;
   (*stack).first = NULL;
   
   INVARIANT( stack );
   POSTCONDITION( "stack is empty", (*stack).count == 0 );
   UNLOCK( (*stack).mutex );
   
   return;
}

/**
   Stack_wipe_out_and_dispose
*/

void
Stack_wipe_out_and_dispose( Prefix )( Stack_type( Prefix ) *stack )
{
   PRECONDITION( "stack not null", stack != NULL );
   PRECONDITION( "stack type OK", ( (*stack).type == STACK_TYPE ) && ( (*stack).item_type == Type_Code ) );
   LOCK( (*stack).mutex );
   INVARIANT( stack );
   
   node_t *node = (*stack).first;
   node_t *next = NULL;
  
   // remove all nodes   
   while ( node != NULL )
   {
      next = (*node).next;
      VALUE_DISPOSE_FUNCTION( (*node).value );
      node_dispose( node );
      node = next;
   }
   
   (*stack).count = 0;
   (*stack).first = NULL;
   
   INVARIANT( stack );
   POSTCONDITION( "stack is empty", (*stack).count == 0 );
   UNLOCK( (*stack).mutex );
   
   return;
}


/* End of file */

