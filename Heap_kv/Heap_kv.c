/**
 @file Heap.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Heaps of values"

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

 Function definitions for the opaque Heap_kv_t type.

*/

#include "Heap_kv.h"

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

#define HEAP_MIN_CAPACITY 15

/*
   Parent and child index relationships
**/

/**
   parent_index

   get the index of the parent of the input index

   @param index the index
   @return the parent index of index
*/
static
int32_t
parent_index( int32_t index )
{
   return ( index - 1 ) / 2;
}

/**
   left_child_index

   get the index of the left child of the input index

   @param index the index
   @return the left child index of index
*/
static
int32_t
left_child_index( int32_t index )
{
   return 2 * index + 1;
}

/**
   right_child_index

   get the index of the right child of the input index

   @param index the index
   @return the right child index of index
*/
static
int32_t
right_child_index( int32_t index )
{
   return 2 * index + 2;
}


/**
   Node structure declaration
*/

struct node;

/**
   Node structure definition. Holds a key and a value.
*/

struct node
{
   Key key;
   Type value;
};

typedef struct node node_t;

/**
   Binary search tree structure definition.
*/

struct Heap_kv_struct( Prefix )
{
   int32_t _type;
   int32_t _key_type;
   int32_t _item_type;

   node_t **array;
   int32_t count;
   int32_t capacity;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   node_make

   create a new node

   @return the new node
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

   dispose of a node

   @param node the node to dispose
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
   has

   Return 1 if heap has an item for value, 0 if not

   @param heap Heap_kv_t instance
   @param key the key to query for
   @return 1 if present, 0 if not
*/

static
int32_t
has( Heap_kv_type( Prefix ) *heap, Key key )
{
   int32_t result = 0;
   int32_t start = 0;
   int32_t end = 0;
   int32_t nodes = 0;
   int32_t count = 0;
   int32_t heap_count = 0;
   node_t **array = NULL;

   // shortcut to array and count
   array = (*heap).array;
   heap_count = (*heap).count;

   // initialize nodes
   nodes = 1;

   // loop to search through array for key
   while ( ( start < heap_count ) && ( result == 0 ) )
   {
      // set up for first loop
      start = nodes - 1;
      end = nodes + start;
      count = 0;

      // loop to search for key at this node level, exiting if we're sure it's not present
      while ( ( start < heap_count ) && ( start < end ) && ( result == 0 ) )
      {
         // see if we found it
         if ( key == ( *array[start] ).key )
         {
            // found it, set result flag to true
            result = 1;
         }

         // didn't find it, count item if key is bracketed by parent and this child
         else if  (
            ( KEY_ORDER_FUNCTION( key, ( *array[ parent_index( start ) ] ).key ) == 0 )
            &&
            ( KEY_ORDER_FUNCTION( key, ( *array[start] ).key ) == 1 )
         )
         {
            count = count + 1;
         }

         // set for next comparison
         start = start + 1;
      }

      // if we've exhausted the nodes at this level and along with parent all bracket the search key, we're done
      if ( count == nodes )
      {
         result = 0;
         break;
      }

      // otherwise look at next level of nodes
      nodes = 2 * nodes;
   }

   return result;

}

/**
   item

   Return value of node in heap that has key, NULL if none

   @param heap Heap_kv_t instance
   @param key the key to query for
   @return value for key or default value if not found
*/

static
Type
item( Heap_kv_type( Prefix ) *heap, Key key )
{
   Type result = VALUE_DEFAULT_VALUE;
   int32_t flag = 0;
   int32_t start = 0;
   int32_t end = 0;
   int32_t nodes = 0;
   int32_t count = 0;
   int32_t heap_count = 0;
   node_t **array = NULL;

   // shortcut to array and count
   array = (*heap).array;
   heap_count = (*heap).count;

   // initialize nodes
   nodes = 1;

   // loop to search through array for key
   while ( ( start < heap_count ) && ( flag == 0 ) )
   {
      // set up for first loop
      start = nodes - 1;
      end = nodes + start;
      count = 0;

      // loop to search for key at this node level, exiting if we're sure it's not present
      while ( ( start < heap_count ) && ( start < end ) && ( flag == 0 ) )
      {
         // see if we found it
         if ( key == ( *array[start] ).key )
         {
            // found it, set result and flag to true
            result = ( *array[start] ).value;
            flag = 1;
         }

         // didn't find it, count item if key is bracketed by parent and this child
         else if  (
            ( KEY_ORDER_FUNCTION( key, ( *array[ parent_index( start ) ] ).key ) == 0 )
            &&
            ( KEY_ORDER_FUNCTION( key, ( *array[start] ).key ) == 1 )
         )
         {
            count = count + 1;
         }

         // set for next comparison
         start = start + 1;
      }

      // if we've exhausted the nodes at this level and along with parent all bracket the search key, we're done
      if ( count == nodes )
      {
         flag = 0;
         break;
      }

      // otherwise look at next level of nodes
      nodes = 2 * nodes;
   }

   return result;

}

/**
   node_for_key

   Return node in heap that has key, NULL if none

   @param heap Heap_kv_t instance
   @param key the key to query for
   @return value for key or default value if not found
*/

static
node_t *
node_for_key( Heap_kv_type( Prefix ) *heap, Key key )
{
   node_t *result = NULL;
   int32_t flag = 0;
   int32_t start = 0;
   int32_t end = 0;
   int32_t nodes = 0;
   int32_t count = 0;
   int32_t heap_count = 0;
   node_t **array = NULL;

   // shortcut to array and count
   array = (*heap).array;
   heap_count = (*heap).count;

   // initialize nodes
   nodes = 1;

   if ( heap_count > 0 )
   {
      // loop to search through array for key
      while ( ( start < heap_count ) && ( flag == 0 ) )
      {
         // set up for first loop
         start = nodes - 1;
         end = nodes + start;
         count = 0;

         // loop to search for key at this node level, exiting if we're sure it's not present
         while ( ( start < heap_count ) && ( start < end ) && ( flag == 0 ) )
         {
            // see if we found it
            if ( key == ( *array[start] ).key )
            {
               // found it, set result and flag to true
               result = array[start];
               flag = 1;
            }

            // didn't find it, count item if key is bracketed by parent and this child
            else if  (
               (   KEY_ORDER_FUNCTION( key, ( *array[ parent_index( start ) ] ).key ) == 0 )
               &&
               ( KEY_ORDER_FUNCTION( key, ( *array[start] ).key ) == 1 )
            )
            {
               count = count + 1;
            }

            // set for next comparison
            start = start + 1;
         }

         // if we've exhausted the nodes at this level and along with parent all bracket the search key, we're done
         if ( count == nodes )
         {
            flag = 0;
            break;
         }

         // otherwise look at next level of nodes
         nodes = 2 * nodes;
      }
   }

   return result;

}

/**
   index_of_key

   Return index of node in heap that has key, -1 if none

   @param heap Heap_kv_t instance
   @param key the key to query for
   @return the index of key, or -1 if not found
*/

static
int32_t
index_of_key( Heap_kv_type( Prefix ) *heap, Key key )
{
   int32_t result = -1;
   int32_t flag = 0;
   int32_t start = 0;
   int32_t end = 0;
   int32_t nodes = 0;
   int32_t count = 0;
   int32_t heap_count = 0;
   node_t **array = NULL;

   // shortcut to array and count
   array = (*heap).array;
   heap_count = (*heap).count;

   // initialize nodes
   nodes = 1;

   // loop to search through array for key
   while ( ( start < heap_count ) && ( flag == 0 ) )
   {
      // set up for first loop
      start = nodes - 1;
      end = nodes + start;
      count = 0;

      // loop to search for key at this node level, exiting if we're sure it's not present
      while ( ( start < heap_count ) && ( start < end ) && ( flag == 0 ) )
      {
         // see if we found it
         if ( key == ( *array[start] ).key )
         {
            // found it, set result and flag to true
            result = start;
            flag = 1;
         }

         // didn't find it, count item if key is bracketed by parent and this child
         else if  (
            ( KEY_ORDER_FUNCTION( key, ( *array[ parent_index( start ) ] ).key ) == 0 )
            &&
            ( KEY_ORDER_FUNCTION( key, ( *array[start] ).key ) == 1 )
         )
         {
            count = count + 1;
         }

         // set for next comparison
         start = start + 1;
      }

      // the following if statement is never executed because preconditions ensure
      // that the key exists in the heap
      // if we've exhausted the nodes at this level and along with parent all bracket the search key, we're done
      //if ( count == nodes )
      //{
      //   flag = 0;
      //   break;
      //}

      // otherwise look at next level of nodes
      nodes = 2 * nodes;
   }

   return result;

}

/**
   reorder

   re-order the heap tree to accomoate an insert at the end of the array

   @param current the heap
*/

static
void
reorder_from_last( Heap_kv_type( Prefix ) *current )
{
   int32_t i = 0;
   int32_t parent_i = 0;
   node_t *node = NULL;
   node_t **array = NULL;

   // shortcut to array
   array = (*current).array;

   // initialize indices for loop
   i = (*current).count - 1;
   parent_i = parent_index( i );

   // loop to move node up in current to restore current order
   while ( ( i > 0 ) && ( KEY_ORDER_FUNCTION( ( *array[i] ).key, ( *array[parent_i] ).key ) == 1 ) )
   {
      // swap nodes at i and parent_i
      node = array[i];
      array[i] = array[parent_i];
      array[parent_i] = node;

      // indices for next iteration
      i = parent_i;
      parent_i = parent_index( i );
   }

   return;
}

/**
   put

   put a new value into the heap

   @param current the heap
   @param value the new value
   @param key the key for the new value
*/

static
void
put( Heap_kv_type( Prefix ) *current, Type value, Key key )
{
   node_t *node = NULL;

   // increase current capacity if necessary
   if ( (*current).count == (*current).capacity )
   {
      (*current).capacity = 2 * (*current).capacity;
      (*current).array = ( node_t ** ) realloc( (*current).array, (*current).capacity * sizeof( node_t * ) );
      CHECK( "(*current).array allocated correctly", (*current).array != NULL );
   }

   // see if we already have this key
   node = node_for_key( current, key );

   if ( node != NULL )
   {
      // we already have a node with this key, set its value
      (*node).key = key;
      (*node).value = value;
   }
   else
   {
      // didn't find the key, insert new node

      // make and populate new last node
      node = node_make();
      (*node).key = key;
      (*node).value = value;

      // put new node at end of array
      (*current).array[ (*current).count ] = node;

      // increment current count
      (*current).count = (*current).count + 1;

      // fix up the current order
      reorder_from_last( current );

   }
   return;
}

/**
   put_and_dispose

   put a new value into the heap, dispose of any previous item with the same key

   @param current the heap
   @param value the new value
   @param key the key for the new value
*/

static
void
put_and_dispose( Heap_kv_type( Prefix ) *heap, Type value, Key key )
{
   node_t *node = NULL;

   // increase heap capacity if necessary
   if ( (*heap).count == (*heap).capacity )
   {
      (*heap).capacity = 2 * (*heap).capacity;
      (*heap).array = ( node_t ** ) realloc( (*heap).array, (*heap).capacity * sizeof( node_t * ) );
      CHECK( "(*heap).array allocated correctly", (*heap).array != NULL );
   }

   // see if we already have this key
   node = node_for_key( heap, key );

   if ( node != NULL )
   {
      // we already have a node with this key, dispose of old value and set new value
      KEY_DISPOSE_FUNCTION( (*node).key );
      VALUE_DISPOSE_FUNCTION( (*node).value );
      (*node).key = key;
      (*node).value = value;
   }
   else
   {
      // didn't find the key, insert new node

      // make and populate new last node
      node = node_make();
      (*node).key = key;
      (*node).value = value;

      // put new node at end of array
      (*heap).array[ (*heap).count ] = node;

      // increment heap count
      (*heap).count = (*heap).count + 1;

      // fix up the heap order
      reorder_from_last( heap );

   }
   return;
}

/**
   remove

   remove an item with "key" from the heap

   @param current the heap
   @param key the key to look for
*/

static
void
remove( Heap_kv_type( Prefix ) *current, Key key )
{
   int32_t index = 0;
   int32_t left_i = 0;
   int32_t right_i = 0;
   node_t *node = NULL;
   node_t **array = NULL;
   int32_t current_count = 0;

   // find key in the current, get its index
   index = index_of_key( current, key );

   // only proceed if key was found
   if ( index >= 0 )
   {
      // decrement count
      (*current).count = (*current).count - 1;

      // get shortcut to current_count, array
      current_count = (*current).count;
      array = (*current).array;

      // delete the node
      node_dispose( &array[index] );

      // put node at end of current into deleted node's location
      array[index] = array[current_count];

      // get pointers to left and right children
      left_i = left_child_index( index );
      right_i = right_child_index( index );

      // loop to promote node within current to where it should go
      while (
         ( left_i < current_count )
         &&
         (
            ( KEY_ORDER_FUNCTION( ( *array[index] ).key, ( *array[left_i] ).key ) == 0 )
            ||
            ( KEY_ORDER_FUNCTION( ( *array[index] ).key, ( *array[right_i] ).key ) == 0  )
         )
      )
      {
         // promote key from subtree up
         if ( KEY_ORDER_FUNCTION( ( *array[left_i] ).key, ( *array[right_i] ).key ) == 1 )
         {
            node = array[left_i];
            array[left_i] = array[index];
            array[index] = node;
            index = left_i;
            left_i = left_child_index( index );
            right_i = right_child_index( index );
         }
         else
         {
            node = array[right_i];
            array[right_i] = array[index];
            array[index] = node;
            index = right_i;
            left_i = left_child_index( index );
            right_i = right_child_index( index );
         }
      }
   }
   return;
}

/**
   remove_and_dispose

   remove and dispose an item with "key" from the heap

   @param current the heap
   @param key the key to look for
*/

static
void
remove_and_dispose( Heap_kv_type( Prefix ) *current, Key key )
{
   int32_t index = 0;
   int32_t left_i = 0;
   int32_t right_i = 0;
   node_t *node = NULL;
   node_t **array = NULL;
   int32_t current_count = 0;

   // find key in the current, get its index
   index = index_of_key( current, key );

   // only proceed if key was found
   if ( index >= 0 )
   {
      // decrement count
      (*current).count = (*current).count - 1;

      // get shortcut to current_count, array
      current_count = (*current).count;
      array = (*current).array;

      // delete the node
      KEY_DISPOSE_FUNCTION( ( *array[index] ).key );
      VALUE_DISPOSE_FUNCTION( ( *array[index] ).value );
      node_dispose( &array[index] );

      // put node at end of current into deleted node's location
      array[index] = array[current_count];

      // get pointers to left and right children
      left_i = left_child_index( index );
      right_i = right_child_index( index );

      // loop to promote node within current to where it should go
      while (
         ( left_i < current_count )
         &&
         (
            ( KEY_ORDER_FUNCTION( ( *array[index] ).key, ( *array[left_i] ).key ) == 0 )
            ||
            ( KEY_ORDER_FUNCTION( ( *array[index] ).key, ( *array[right_i] ).key ) == 0  )
         )
      )
      {
         // promote key from subtree up
         if ( KEY_ORDER_FUNCTION( ( *array[left_i] ).key, ( *array[right_i] ).key ) == 1 )
         {
            node = array[left_i];
            array[left_i] = array[index];
            array[index] = node;
            index = left_i;
            left_i = left_child_index( index );
            right_i = right_child_index( index );
         }
         else
         {
            node = array[right_i];
            array[right_i] = array[index];
            array[index] = node;
            index = right_i;
            left_i = left_child_index( index );
            right_i = right_child_index( index );
         }
      }
   }
   return;
}

/**
   keys_as_array

   return an array of keys in the heap

   @param current the heap
   @return an array of keys
*/

static
Key *
keys_as_array( Heap_kv_type( Prefix ) *current )
{
   Key *result = NULL;
   node_t **array = NULL;
   int32_t i = 0;

   result = ( Key * ) calloc( (*current).count + 1, sizeof( Key ) );
   CHECK( "result allocated correctly", result != NULL );

   array = (*current).array;

   for ( i = 0; i < (*current).count; i++ )
   {
      result[i] = ( *array[i] ).key;
   }

   return result;
}

/**
   items_as_array

   return an array of items in the heap

   @param current the heap
   @return an array of items
*/

static
Type *
items_as_array( Heap_kv_type( Prefix ) *current )
{
   Type *result = NULL;
   node_t **array = NULL;
   int32_t i = 0;

   result = ( Type * ) calloc( (*current).count + 1, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   array = (*current).array;

   for ( i = 0; i < (*current).count; i++ )
   {
      result[i] = ( *array[i] ).value;
   }

   return result;
}

/**
   height

   return the height of the heap tree

   @param current the heap
*/
static
int32_t
height( Heap_kv_type( Prefix ) *current )
{
   int32_t result = 0;
   float64_t x = 0;

   if ( (*current).count == 0 )
   {
      result = 0;
   }
   else
   {
      x = log10( 1.0 * (*current).count ) / log10( 2.0 );
      result = ( int32_t ) x;
      result = result + 1;
   }

   return result;
}

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
nonnegative_count( Heap_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
in_order( Heap_kv_type( Prefix ) *p )
{
   int32_t result = 1;
   int32_t i = 0;
   int32_t heap_count = 0;
   node_t **array = NULL;

   if ( (*p).count > 1 )
   {
      array = (*p).array;
      heap_count = (*p).count;

      while ( ( left_child_index( i ) < heap_count ) && ( result == 1 ) )
      {
         result = ( KEY_ORDER_FUNCTION( ( *array[i] ).key, ( *array[ left_child_index( i ) ] ).key ) == 1 );

         if ( ( result == 1 ) && ( right_child_index( i ) < heap_count ) )
         {
            result = ( KEY_ORDER_FUNCTION( ( *array[i] ).key, ( *array[ right_child_index( i ) ] ).key ) == 1 );
         }
         i = i + 1;
      }
   }

   return result;
}

static
void invariant( Heap_kv_type( Prefix ) *p )
{
   assert( ( ( void ) "nonnegative count", nonnegative_count( p ) ) );
   assert( ( ( void ) "heap in order", in_order( p ) ) );
   return;
}

#endif // INVARIANT_CONDITIONAL

/**
   Heap_make
*/

Heap_kv_type( Prefix ) *
Heap_kv_make( Prefix )( void )
{
   // allocate heap struct
   Heap_kv_type( Prefix ) * heap
      = ( Heap_kv_type( Prefix ) * ) calloc( 1, sizeof( Heap_kv_type( Prefix ) ) );
   CHECK( "heap allocated correctly", heap != NULL );

   // set type codes
   (*heap)._type = HEAP_KV_TYPE;
   (*heap)._key_type = Key_Code;
   (*heap)._item_type = Type_Code;

   // allocate array
   (*heap).array = ( node_t ** ) calloc( HEAP_MIN_CAPACITY, sizeof( node_t * ) );
   CHECK( "(*heap).array allocated correctly", (*heap).array != NULL );

   // count is zero
   (*heap).count = 0;
   (*heap).capacity = HEAP_MIN_CAPACITY;

   MULTITHREAD_MUTEX_INIT( (*heap).mutex );

   INVARIANT( heap );

   return heap;
}

/**
   Heap_make_n
*/

Heap_kv_type( Prefix ) *
Heap_kv_make_n( Prefix )( int32_t requested_capacity )
{
   int32_t capacity = 0;

   if ( requested_capacity < HEAP_MIN_CAPACITY )
   {
      capacity = HEAP_MIN_CAPACITY;
   }
   else
   {
      capacity = requested_capacity;
   }

   // allocate heap struct
   Heap_kv_type( Prefix ) * heap
      = ( Heap_kv_type( Prefix ) * ) calloc( 1, sizeof( Heap_kv_type( Prefix ) ) );
   CHECK( "heap allocated correctly", heap != NULL );

   // set type codes
   (*heap)._type = HEAP_KV_TYPE;
   (*heap)._key_type = Key_Code;
   (*heap)._item_type = Type_Code;

   // allocate array
   (*heap).array = ( node_t ** ) calloc( capacity, sizeof( node_t * ) );
   CHECK( "(*heap).array allocated correctly", (*heap).array != NULL );

   // count is zero
   (*heap).count = 0;
   (*heap).capacity = capacity;

   MULTITHREAD_MUTEX_INIT( (*heap).mutex );

   INVARIANT( heap );

   return heap;
}

/**
   Heap_make_from_array
*/

Heap_kv_type( Prefix ) *
Heap_kv_make_from_array( Prefix )( Key *key_array, Type *value_array, int32_t count )
{
   PRECONDITION( "key_array not null", key_array != NULL );
   PRECONDITION( "value_array not null", value_array != NULL );
   PRECONDITION( "count  ok", count >= 0 );

   int32_t i = 0;

   // make heap struct
   Heap_kv_type( Prefix ) *result
      = ( Heap_kv_type( Prefix ) * ) calloc( 1, sizeof( Heap_kv_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type codes
   (*result)._type = HEAP_KV_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   // allocate array
   (*result).array = ( node_t ** ) calloc( count + 1, sizeof( node_t * ) );
   CHECK( "(*result).array allocated correctly", (*result).array != NULL );

   // count is zero
   (*result).count = 0;
   (*result).capacity = count + 1;

   for ( i = 0; i < count; i++ )
   {
      put( result, value_array[i], key_array[i] );
   }

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Heap_clone
*/

Heap_kv_type( Prefix ) *
Heap_kv_clone( Prefix )( Heap_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );

   int32_t i = 0;
   node_t *node = NULL;
   node_t **array = NULL;
   node_t **current_array = NULL;

   // make current struct
   Heap_kv_type( Prefix ) *result = Heap_kv_make_n( Prefix )( (*current).capacity );

   // copy from current
   current_array = (*current).array;
   array = (*result).array;
   for ( i = 0; i < (*current).count; i++ )
   {
      node = node_make();
      (*node).key = ( *current_array[i] ).key;
      (*node).value = ( *current_array[i] ).value;
      array[i] = node;
   }
   (*result).count = (*current).count;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( result );

   return result;
}

/**
   Heap_deep_clone
*/

Heap_kv_type( Prefix ) *
Heap_kv_deep_clone( Prefix )( Heap_kv_type( Prefix ) *heap )
{
   PRECONDITION( "heap not null", heap != NULL );
   PRECONDITION( "heap type ok", ( (*heap)._type == HEAP_KV_TYPE ) && ( (*heap)._key_type = Key_Code ) && ( (*heap)._item_type = Type_Code ) );

   int32_t i = 0;
   node_t *node = NULL;
   node_t **array = NULL;
   node_t **heap_array = NULL;

   // make heap struct
   Heap_kv_type( Prefix ) *result = Heap_kv_make_n( Prefix )( (*heap).capacity );

   // copy from heap
   heap_array = (*heap).array;
   array = (*result).array;
   for ( i = 0; i < (*heap).count; i++ )
   {
      node = node_make();
      (*node).key = KEY_DUPLICATE_FUNCTION( ( *heap_array[i] ).key );
      (*node).value = VALUE_DUPLICATE_FUNCTION( ( *heap_array[i] ).value );
      array[i] = node;
   }
   (*result).count = (*heap).count;

   MULTITHREAD_MUTEX_INIT( (*heap).mutex );

   INVARIANT( result );

   return result;
}

/**
   Heap_copy
*/

void
Heap_kv_copy( Prefix )( Heap_kv_type( Prefix ) *current, Heap_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HEAP_KV_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( other );

   int32_t i = 0;
   node_t *node = NULL;
   node_t **array = NULL;
   node_t **other_array = NULL;

   // get array of nodes
   array = (*current).array;

   // delete nodes and values
   for ( i = 0; i < (*current).count; i++ )
   {
      KEY_DISPOSE_FUNCTION( ( *array[i] ).key );
      VALUE_DISPOSE_FUNCTION( ( *array[i] ).value );
      node_dispose( &array[i] );
   }

   if ( (*current).capacity < (*other).capacity )
   {
      (*current).array = ( node_t ** ) realloc( (*current).array, (*other).capacity * sizeof( node_t * ) );
      CHECK( "(*current).array allocated correctly", (*current).array != NULL );
   }

   // copy from other
   other_array = (*other).array;
   array = (*current).array;
   for ( i = 0; i < (*other).count; i++ )
   {
      node = node_make();
      (*node).key = ( *other_array[i] ).key;
      (*node).value = ( *other_array[i] ).value;
      array[i] = node;
   }
   (*current).count = (*other).count;

   INVARIANT( current );
   INVARIANT( other );

   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return;
}

/**
   Heap_deep_copy
*/

void
Heap_kv_deep_copy( Prefix )( Heap_kv_type( Prefix ) *current, Heap_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HEAP_KV_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( other );

   int32_t i = 0;
   node_t *node = NULL;
   node_t **array = NULL;
   node_t **other_array = NULL;

   // get array of nodes
   array = (*current).array;

   // delete nodes and values
   for ( i = 0; i < (*current).count; i++ )
   {
      KEY_DISPOSE_FUNCTION( ( *array[i] ).key );
      VALUE_DISPOSE_FUNCTION( ( *array[i] ).value );
      node_dispose( &array[i] );
   }

   if ( (*current).capacity < (*other).capacity )
   {
      (*current).array = ( node_t ** ) realloc( (*current).array, (*other).capacity * sizeof( node_t * ) );
      CHECK( "(*current).array allocated correctly", (*current).array != NULL );
   }

   // copy from other
   other_array = (*other).array;
   array = (*current).array;
   for ( i = 0; i < (*other).count; i++ )
   {
      node = node_make();
      (*node).key = KEY_DUPLICATE_FUNCTION( ( *other_array[i] ).key );
      (*node).value = VALUE_DUPLICATE_FUNCTION( ( *other_array[i] ).value );
      array[i] = node;
   }
   (*current).count = (*other).count;

   INVARIANT( current );
   INVARIANT( other );

   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return;
}

/**
   Heap_kv_is_equal
*/

int32_t
Heap_kv_is_equal( Prefix )( Heap_kv_type( Prefix ) *current, Heap_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HEAP_KV_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*other).mutex );
   if ( current != other )
   {
      LOCK( (*current).mutex );
   }
   INVARIANT( current );
   INVARIANT( other );

   int32_t result = 0;
   int32_t i = 0;
   node_t **array = NULL;
   node_t **other_array = NULL;

   result = 1;

   if ( current != other )
   {

      if ( (*current).count != (*other).count )
      {
         result = 0;
      }
      else
      {
         // compare to other
         other_array = (*other).array;
         array = (*current).array;

         for ( i = 0; i < (*other).count; i++ )
         {
            if ( ( *array[i] ).key != ( *other_array[i] ).key )
            {
               result = 0;
               break;
            }

            if ( ( *array[i] ).value != ( *other_array[i] ).value )
            {
               result = 0;
               break;
            }
         }
      }
   }
   else
   {
      result = 1;
   }

   INVARIANT( current );
   INVARIANT( other );

   UNLOCK( (*other).mutex );
   if ( current != other )
   {
      UNLOCK( (*current).mutex );
   }

   return result;
}

/**
   Heap_kv_is_deep_equal
*/

int32_t
Heap_kv_is_deep_equal( Prefix )( Heap_kv_type( Prefix ) *current, Heap_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HEAP_KV_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*other).mutex );
   if ( current != other )
   {
      LOCK( (*current).mutex );
   }
   INVARIANT( current );
   INVARIANT( other );

   int32_t result = 0;
   int32_t i = 0;
   node_t **array = NULL;
   node_t **other_array = NULL;

   result = 1;

   if ( current != other )
   {

      if ( (*current).count != (*other).count )
      {
         result = 0;
      }
      else
      {
         // compare to other
         other_array = (*other).array;
         array = (*current).array;

         for ( i = 0; i < (*other).count; i++ )
         {
            if ( KEY_EQUALITY_FUNCTION( ( *array[i] ).key, ( *other_array[i] ).key ) != 1 )
            {
               result = 0;
               break;
            }

            if ( VALUE_EQUALITY_FUNCTION( ( *array[i] ).value, ( *other_array[i] ).value ) != 1 )
            {
               result = 0;
               break;
            }
         }
      }
   }
   else
   {
      result = 1;
   }

   INVARIANT( current );
   INVARIANT( other );

   UNLOCK( (*other).mutex );
   if ( current != other )
   {
      UNLOCK( (*current).mutex );
   }

   return result;
}

/**
   Heap_kv_dispose
*/

void
Heap_kv_dispose( Prefix )( Heap_kv_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == HEAP_KV_TYPE ) && ( (**current)._key_type = Key_Code ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   int32_t i = 0;

   // get array of nodes
   node_t **array = (**current).array;

   // delete nodes
   for ( i = 0; i < (**current).count; i++ )
   {
      node_dispose( &array[i] );
   }

   // delete array
   free( (**current).array );

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to null
   *current = NULL;

   return;
}

/**
   Heap_kv_deep_dispose
*/

void
Heap_kv_deep_dispose( Prefix )( Heap_kv_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == HEAP_KV_TYPE ) && ( (**current)._key_type = Key_Code ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   int32_t i = 0;

   // get array of nodes
   node_t **array = (**current).array;

   // delete nodes and values
   for ( i = 0; i < (**current).count; i++ )
   {
      KEY_DISPOSE_FUNCTION( ( *array[i] ).key );
      VALUE_DISPOSE_FUNCTION( ( *array[i] ).value );
      node_dispose( &array[i] );
   }

   // delete array
   free( (**current).array );

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to null
   *current = NULL;

   return;
}

/**
   Heap_kv_keys_as_array

*/

Type *
Heap_kv_keys_as_array( Prefix )( Heap_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );

   Key *result = keys_as_array( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Heap_kv_values_as_array

*/

Type *
Heap_kv_values_as_array( Prefix )( Heap_kv_type( Prefix ) *heap )
{
   PRECONDITION( "heap not null", heap != NULL );
   PRECONDITION( "heap type ok", ( (*heap)._type == HEAP_KV_TYPE ) && ( (*heap)._key_type = Key_Code ) && ( (*heap)._item_type = Type_Code ) );
   LOCK( (*heap).mutex );

   Type *result = items_as_array( heap );

   INVARIANT( heap );
   UNLOCK( (*heap).mutex );

   return result;
}

/**
   Heap_kv_key
*/

Type
Heap_kv_key( Prefix )( Heap_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Key key = KEY_DEFAULT_VALUE;

   key = ( *(*current).array[0] ).key;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return key;
}

/**
   Heap_kv_item
*/

Type
Heap_kv_item( Prefix )( Heap_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type value = VALUE_DEFAULT_VALUE;

   value = ( *(*current).array[0] ).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   Heap_kv_item_for_key
*/

Type
Heap_kv_item_for_key( Prefix )( Heap_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type value = VALUE_DEFAULT_VALUE;

   value = item( current, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   Heap_kv_count
*/

int32_t
Heap_kv_count( Prefix )( Heap_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   Heap_kv_capacity
*/

int32_t
Heap_kv_capacity( Prefix )( Heap_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t capacity = (*current).capacity;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return capacity;
}

/**
   Heap_kv_height
*/

int32_t
Heap_kv_height( Prefix )( Heap_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = height( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   Heap_kv_set_capacity
*/

void
Heap_kv_set_capacity( Prefix )( Heap_kv_type( Prefix ) *current, int32_t new_capacity )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   if ( new_capacity > (*current).capacity )
   {
      (*current).capacity = new_capacity;
      (*current).array = ( node_t ** ) realloc( (*current).array, (*current).capacity * sizeof( node_t * ) );
      CHECK( "(*current).array allocated correctly", (*current).array != NULL );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_kv_is_empty
*/

int32_t
Heap_kv_is_empty( Prefix )( Heap_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count ==  0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Heap_kv_has
*/

int32_t
Heap_kv_has( Prefix )( Heap_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has( current, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Heap_kv_put
*/

void
Heap_kv_put( Prefix )( Heap_kv_type( Prefix ) *current, Type value, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   put( current, value, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_kv_put_and_dispose
*/

void
Heap_kv_put_and_dispose( Prefix )( Heap_kv_type( Prefix ) *current, Type value, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   put_and_dispose( current, value, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_kv_append
*/

void
Heap_kv_append( Prefix )( Heap_kv_type( Prefix ) *current, Heap_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HEAP_KV_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   int32_t i = 0;
   node_t **other_array = NULL;

   // adjust capacity if needed
   if ( ( (*current).count + (*other).count ) < (*current).capacity )
   {
      (*current).capacity = (*current).count + (*other).count + 1;
      (*current).array = ( node_t ** ) realloc( (*current).array, (*current).capacity * sizeof( node_t * ) );
      CHECK( "(*current).array allocated correctly", (*current).array != NULL );
   }

   // copy from other
   other_array = (*other).array;
   for ( i = 0; i < (*other).count; i++ )
   {
      put( current, ( *other_array[i] ).value, ( *other_array[i] ).key );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return;
}

/**
   Heap_kv_append_and_dispose
*/

void
Heap_kv_append_and_dispose( Prefix )( Heap_kv_type( Prefix ) *current, Heap_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HEAP_KV_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   int32_t i = 0;
   node_t **other_array = NULL;

   // adjust capacity if needed
   if ( ( (*current).count + (*other).count ) < (*current).capacity )
   {
      (*current).capacity = (*current).count + (*other).count + 1;
      (*current).array = ( node_t ** ) realloc( (*current).array, (*current).capacity * sizeof( node_t * ) );
      CHECK( "(*current).array allocated correctly", (*current).array != NULL );
   }

   // copy from other
   other_array = (*other).array;
   for ( i = 0; i < (*other).count; i++ )
   {
      put_and_dispose( current, ( *other_array[i] ).value, ( *other_array[i] ).key );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return;
}

/**
   Heap_kv_remove
*/

void
Heap_kv_remove( Prefix )( Heap_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has( current, key ) );

   remove( current, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_kv_remove_and_dispose
*/

void
Heap_kv_remove_and_dispose( Prefix )( Heap_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has( current, key ) );

   remove_and_dispose( current, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_kv_prune
*/

void
Heap_kv_prune( Prefix )( Heap_kv_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( count >= 0 ) && ( count <= (*current).count ) );

   int32_t i = 0;
   int32_t current_count = 0;
   node_t **array = NULL;

   array = (*current).array;
   current_count = (*current).count;

   for( i = 0; i < count; i++ )
   {
      node_dispose( &array[ current_count - 1 - i ] );
   }

   (*current).count = (*current).count - count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_kv_prune_and_dispose
*/

void
Heap_kv_prune_and_dispose( Prefix )( Heap_kv_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( count >= 0 ) && ( count <= (*current).count ) );

   int32_t i = 0;
   int32_t current_count = 0;
   node_t **array = NULL;

   array = (*current).array;
   current_count = (*current).count;

   for( i = 0; i < count; i++ )
   {
      KEY_DISPOSE_FUNCTION( ( *array[ current_count - 1 - i ] ).key );
      VALUE_DISPOSE_FUNCTION( ( *array[ current_count - 1 - i ] ).value );
      node_dispose( &array[ current_count - 1 - i ] );
   }

   (*current).count = (*current).count - count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_kv_keep
*/

void
Heap_kv_keep( Prefix )( Heap_kv_type( Prefix ) *current, int32_t keep_count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( keep_count >= 0 ) && ( keep_count <= (*current).count ) );

   int32_t i = 0;
   int32_t count = 0;
   int32_t current_count = 0;
   node_t **array = NULL;

   array = (*current).array;
   current_count = (*current).count;
   count = current_count - keep_count;

   for( i = 0; i < count; i++ )
   {
      node_dispose( &array[ current_count - 1 - i ] );
   }

   (*current).count = keep_count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_kv_keep_and_dispose
*/

void
Heap_kv_keep_and_dispose( Prefix )( Heap_kv_type( Prefix ) *current, int32_t keep_count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( keep_count >= 0 ) && ( keep_count <= (*current).count ) );

   int32_t i = 0;
   int32_t count = 0;
   int32_t current_count = 0;
   node_t **array = NULL;

   array = (*current).array;
   current_count = (*current).count;
   count = current_count - keep_count;

   for( i = 0; i < count; i++ )
   {
      KEY_DISPOSE_FUNCTION( ( *array[ current_count - 1 - i ] ).key );
      VALUE_DISPOSE_FUNCTION( ( *array[ current_count - 1 - i ] ).value );
      node_dispose( &array[ current_count - 1 - i ] );
   }

   (*current).count = keep_count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_kv_wipe_out
*/

void
Heap_kv_wipe_out( Prefix )( Heap_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;

   // get array of nodes
   node_t **array = (*current).array;

   // delete nodes
   for ( i = 0; i < (*current).count; i++ )
   {
      node_dispose( &array[i] );
   }

   // set count to zero
   (*current).count = 0;

   POSTCONDITION( "is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_kv_wipe_out_and_dispose
*/

void
Heap_kv_wipe_out_and_dispose( Prefix )( Heap_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;

   // get array of nodes
   node_t **array = (*current).array;

   // delete nodes and values
   for ( i = 0; i < (*current).count; i++ )
   {
      KEY_DISPOSE_FUNCTION( ( *array[i] ).key );
      VALUE_DISPOSE_FUNCTION( ( *array[i] ).value );
      node_dispose( &array[i] );
   }

   // set count to zero
   (*current).count = 0;

   POSTCONDITION( "is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

