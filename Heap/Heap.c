/**
 @file Heap.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Binary Search Trees of values with values"

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

 Function definitions for the opaque Heap_t type.

*/

#include "Heap.h"

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

/**
   Parent and child index relationships
*/

/**
   parent_index

   @param index the index of an item
   @return the index of the parent

**/
static
int32_t
parent_index( int32_t index )
{
   return ( index - 1 ) / 2;
}

/**
   left_child_index

   @param index the index of an item
   @return the index of the item's left child

*/
static
int32_t
left_child_index( int32_t index )
{
   return 2 * index + 1;
}

/**
   right_child_index

   @param index the index of an item
   @return the index of the item's right child

*/
static
int32_t
right_child_index( int32_t index )
{
   return 2 * index + 2;
}

/**
   Heap structure definition.
*/

struct Heap_struct( Prefix )
{
   int32_t _type;
   int32_t _item_type;

   Type *array;
   int32_t count;
   int32_t capacity;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   has

   Return 1 if heap has an item for value, 0 if not

   @param current Heap_t instance
   @param value the value to query for
   @return 1 if present, 0 if not
*/

static
int32_t
has( Heap_type( Prefix ) *current, Type value )
{
   int32_t result = 0;
   int32_t start = 0;
   int32_t end = 0;
   int32_t nodes = 0;
   int32_t count = 0;
   int32_t current_count = 0;
   Type *array = NULL;

   // shortcut to array and count
   array = (*current).array;
   current_count = (*current).count;

   // initialize nodes
   nodes = 1;

   // loop to search through array for value
   while ( ( start < current_count ) && ( result == 0 ) )
   {
      // set up for first loop
      start = nodes - 1;
      end = nodes + start;
      count = 0;

      // loop to search for value at this node level, exiting if we're sure it's not present
      while ( ( start < current_count ) && ( start < end ) && ( result == 0 ) )
      {
         // see if we found it
         if ( value == array[start] )
         {
            // found it, set result flag to true
            result = 1;
         }

         // didn't find it, count item if value is bracketed by parent and this child
         else if  (
            ( ORDER_FUNCTION( value, array[ parent_index( start ) ] ) == 0 )
            &&
            ( ORDER_FUNCTION( value, array[start] ) == 1 )
         )
         {
            count = count + 1;
         }

         // set for next comparison
         start = start + 1;
      }

      // if we've exhausted the nodes at this level and along with parent all bracket the search value, we're done
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
   index_of_value

   Return index of node in heap that has value, -1 if none

   @param current Heap_t instance
   @param value the value to query for
   @return the index of value, or -1 if not found
*/

static
int32_t
index_of_value( Heap_type( Prefix ) *current, Type value )
{
   int32_t result = -1;
   int32_t flag = 0;
   int32_t start = 0;
   int32_t end = 0;
   int32_t nodes = 0;
   int32_t count = 0;
   int32_t current_count = 0;
   Type *array = NULL;

   // shortcut to array and count
   array = (*current).array;
   current_count = (*current).count;

   // initialize nodes
   nodes = 1;

   // loop to search through array for value
   while ( ( start < current_count ) && ( flag == 0 ) )
   {
      // set up for first loop
      start = nodes - 1;
      end = nodes + start;
      count = 0;

      // loop to search for value at this node level, exiting if we're sure it's not present
      while ( ( start < current_count ) && ( start < end ) && ( flag == 0 ) )
      {
         // see if we found it
         if ( value == array[start] )
         {
            // found it, set result and flag to true
            result = start;
            flag = 1;
         }

         // didn't find it, count item if value is bracketed by parent and this child
         else if  (
            ( ORDER_FUNCTION( value, array[ parent_index( start ) ] ) == 0 )
            &&
            ( ORDER_FUNCTION( value, array[start] ) == 1 )
         )
         {
            count = count + 1;
         }

         // set for next comparison
         start = start + 1;
      }

      // if we've exhausted the nodes at this level and along with parent all bracket the search value, we're done
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
   reorder

   re-order the items to accomodate an insert at the end of the array

   @param current the heap
*/

static
void
reorder_from_last( Heap_type( Prefix ) *current )
{
   int32_t i = 0;
   int32_t parent_i = 0;
   Type value = DEFAULT_VALUE;
   Type *array = NULL;

   // shortcut to array
   array = (*current).array;

   // initialize indices for loop
   i = (*current).count - 1;
   parent_i = parent_index( i );

   // loop to move node up in current to restore current order
   while ( ( i > 0 ) && ( ORDER_FUNCTION( array[i], array[parent_i] ) == 1 ) )
   {
      // swap nodes at i and parent_i
      value = array[i];
      array[i] = array[parent_i];
      array[parent_i] = value;

      // indices for next iteration
      i = parent_i;
      parent_i = parent_index( i );
   }

   return;
}

/**
   put

   place an item into the heap

   @param current the heap
   @param value the item to add
*/

static
void
put( Heap_type( Prefix ) *current, Type value )
{
   int32_t index = 0;

   // increase current capacity if necessary
   if ( (*current).count == (*current).capacity )
   {
      (*current).capacity = 2 * (*current).capacity;
      (*current).array = ( Type * ) realloc( (*current).array, (*current).capacity * sizeof( Type ) );
      CHECK( "(*current).array allocated correctly", (*current).array != NULL );
   }

   // see if we already have this value
   index = index_of_value( current, value );

   if ( index >= 0 )
   {
      // we already have a node with this value, set its value
      (*current).array[index] = value;
   }
   else
   {
      // didn't find the value, insert new node

      // make and populate new last value

      // put new node at end of array
      (*current).array[ (*current).count ] = value;

      // increment current count
      (*current).count = (*current).count + 1;

      // fix up the current order
      reorder_from_last( current );

   }
   return;
}

/**
   put_and_dispose

   place an item into the heap, dispose of any existing item with the same value

   @param current the heap
   @param value the item to add
*/

static
void
put_and_dispose( Heap_type( Prefix ) *current, Type value )
{
   int32_t index = 0;

   // increase current capacity if necessary
   if ( (*current).count == (*current).capacity )
   {
      (*current).capacity = 2 * (*current).capacity;
      (*current).array = ( Type * ) realloc( (*current).array, (*current).capacity * sizeof( Type ) );
      CHECK( "(*current).array allocated correctly", (*current).array != NULL );
   }

   // see if we already have this value
   index = index_of_value( current, value );

   if ( index >= 0 )
   {
      // we already have a node with this value, dispose of old value and set new value
      DISPOSE_FUNCTION( (*current).array[index] );
      (*current).array[index] = value;
   }
   else
   {
      // didn't find the value, insert new node

      // make and populate new last value
      // put new node at end of array
      (*current).array[ (*current).count ] = value;

      // increment current count
      (*current).count = (*current).count + 1;

      // fix up the current order
      reorder_from_last( current );

   }
   return;
}

/**
   remove

   remove a value from the heap

   @param current the heap
   @param value the value to remove
*/

static
void
remove( Heap_type( Prefix ) *current, Type value )
{
   int32_t index = 0;
   int32_t left_i = 0;
   int32_t right_i = 0;
   Type v = DEFAULT_VALUE;
   Type *array = NULL;
   int32_t current_count = 0;

   // find value in the current, get its index
   index = index_of_value( current, value );

   // only proceed if value was found
   if ( index >= 0 )
   {
      // decrement count
      (*current).count = (*current).count - 1;

      // get shortcut to current_count, array
      current_count = (*current).count;
      array = (*current).array;

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
            ( ORDER_FUNCTION( array[index], array[left_i] ) == 0 )
            ||
            ( ORDER_FUNCTION( array[index], array[right_i] ) == 0  )
         )
      )
      {
         // promote value from subtree up
         if ( ORDER_FUNCTION( array[left_i], array[right_i] ) == 1 )
         {
            v = array[left_i];
            array[left_i] = array[index];
            array[index] = v;
            index = left_i;
            left_i = left_child_index( index );
            right_i = right_child_index( index );
         }
         else
         {
            v = array[right_i];
            array[right_i] = array[index];
            array[index] = v;
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

   remove a value from the heap and dispose of it

   @param current the heap
   @param value the value to remove
*/

static
void
remove_and_dispose( Heap_type( Prefix ) *current, Type value )
{
   int32_t index = 0;
   int32_t left_i = 0;
   int32_t right_i = 0;
   Type v = DEFAULT_VALUE;
   Type *array = NULL;
   int32_t current_count = 0;

   // find value in the current, get its index
   index = index_of_value( current, value );

   // only proceed if value was found
   if ( index >= 0 )
   {
      // decrement count
      (*current).count = (*current).count - 1;

      // get shortcut to current_count, array
      current_count = (*current).count;
      array = (*current).array;

      // delete the node
      DISPOSE_FUNCTION( array[index] );

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
            ( ORDER_FUNCTION( array[index], array[left_i] ) == 0 )
            ||
            ( ORDER_FUNCTION( array[index], array[right_i] ) == 0  )
         )
      )
      {
         // promote value from subtree up
         if ( ORDER_FUNCTION( array[left_i], array[right_i] ) == 1 )
         {
            v = array[left_i];
            array[left_i] = array[index];
            array[index] = v;
            index = left_i;
            left_i = left_child_index( index );
            right_i = right_child_index( index );
         }
         else
         {
            v = array[right_i];
            array[right_i] = array[index];
            array[index] = v;
            index = right_i;
            left_i = left_child_index( index );
            right_i = right_child_index( index );
         }
      }
   }
   return;
}

/**
   as_array

   put the heap contents into an array

   @param current the heap
   @return the array of values
*/

static
Type *
as_array( Heap_type( Prefix ) *current )
{
   Type *result = NULL;
   Type *array = NULL;
   int32_t i = 0;

   result = ( Type * ) calloc( (*current).count + 1, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   array = (*current).array;

   for ( i = 0; i < (*current).count; i++ )
   {
      result[i] = array[i];
   }

   return result;
}

/**
   height

   the height of the heap tree

   @param current the heap
   @return the height of the heap tree
*/
static
int32_t
height( Heap_type( Prefix ) *current )
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
nonnegative_count( Heap_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
in_order( Heap_type( Prefix ) *p )
{
   int32_t result = 1;
   int32_t i = 0;
   int32_t heap_count = 0;
   Type *array = NULL;

   if ( (*p).count > 1 )
   {
      array = (*p).array;
      heap_count = (*p).count;

      while ( ( left_child_index( i ) < heap_count ) && ( result == 1 ) )
      {
         result = ( ORDER_FUNCTION( array[i], array[ left_child_index( i ) ] ) == 1 );

         if ( ( result == 1 ) && ( right_child_index( i ) < heap_count ) )
         {
            result = ( ORDER_FUNCTION( array[i], array[ right_child_index( i ) ] ) == 1 );
         }
         i = i + 1;
      }
   }

   return result;
}

static
void invariant( Heap_type( Prefix ) *p )
{
   assert( ( ( void ) "nonnegative count", nonnegative_count( p ) ) );
   assert( ( ( void ) "heap in order", in_order( p ) ) );
   return;
}

#endif // INVARIANT_CONDITIONAL

/**
   Heap_make
*/

Heap_type( Prefix ) *
Heap_make( Prefix )( void )
{
   // allocate result struct
   Heap_type( Prefix ) * result
      = ( Heap_type( Prefix ) * ) calloc( 1, sizeof( Heap_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type codes
   (*result)._type = HEAP_TYPE;
   (*result)._item_type = Type_Code;

   // allocate array
   (*result).array = ( Type * ) calloc( HEAP_MIN_CAPACITY, sizeof( Type ) );
   CHECK( "(*result).array allocated correctly", (*result).array != NULL );

   // count is zero
   (*result).count = 0;
   (*result).capacity = HEAP_MIN_CAPACITY;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Heap_make_n
*/

Heap_type( Prefix ) *
Heap_make_n( Prefix )( int32_t requested_capacity )
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

   // allocate result struct
   Heap_type( Prefix ) * result
      = ( Heap_type( Prefix ) * ) calloc( 1, sizeof( Heap_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type codes
   (*result)._type = HEAP_TYPE;
   (*result)._item_type = Type_Code;

   // allocate array
   (*result).array = ( Type * ) calloc( capacity, sizeof( Type ) );
   CHECK( "(*result).array allocated correctly", (*result).array != NULL );

   // count is zero
   (*result).count = 0;
   (*result).capacity = capacity;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Heap_make_from_array
*/

Heap_type( Prefix ) *
Heap_make_from_array( Prefix )( Type *value_array, int32_t count )
{
   PRECONDITION( "value_array not null", value_array != NULL );
   PRECONDITION( "count  ok", count >= 0 );

   int32_t i = 0;

   // make heap struct
   Heap_type( Prefix ) *result
      = ( Heap_type( Prefix ) * ) calloc( 1, sizeof( Heap_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type codes
   (*result)._type = HEAP_TYPE;
   (*result)._item_type = Type_Code;

   // allocate array
   (*result).array = ( Type * ) calloc( count + 1, sizeof( Type ) );
   CHECK( "(*result).array allocated correctly", (*result).array != NULL );

   // count is zero
   (*result).count = 0;
   (*result).capacity = count + 1;

   for ( i = 0; i < count; i++ )
   {
      put( result, value_array[i] );
   }

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Heap_clone
*/

Heap_type( Prefix ) *
Heap_clone( Prefix )( Heap_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HEAP_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*other).mutex );
   INVARIANT( other );

   int32_t i = 0;
   Type *array = NULL;
   Type *other_array = NULL;

   // make other struct
   Heap_type( Prefix ) *result = Heap_make_n( Prefix )( (*other).capacity );

   // copy from other
   other_array = (*other).array;
   array = (*result).array;
   for ( i = 0; i < (*other).count; i++ )
   {
      array[i] = other_array[i];
   }
   (*result).count = (*other).count;

   MULTITHREAD_MUTEX_INIT( (*other).mutex );

   INVARIANT( result );

   UNLOCK( (*other).mutex );

   return result;
}

/**
   Heap_deep_clone
*/

Heap_type( Prefix ) *
Heap_deep_clone( Prefix )( Heap_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HEAP_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*other).mutex );
   INVARIANT( other );

   int32_t i = 0;
   Type *array = NULL;
   Type *other_array = NULL;

   // make other struct
   Heap_type( Prefix ) *result = Heap_make_n( Prefix )( (*other).capacity );

   // copy from other
   other_array = (*other).array;
   array = (*result).array;
   for ( i = 0; i < (*other).count; i++ )
   {
      array[i] = DUPLICATE_FUNCTION( other_array[i] );
   }
   (*result).count = (*other).count;

   MULTITHREAD_MUTEX_INIT( (*other).mutex );

   INVARIANT( result );

   UNLOCK( (*other).mutex );

   return result;
}

/**
   Heap_copy
*/

void
Heap_copy( Prefix )( Heap_type( Prefix ) *current, Heap_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HEAP_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*other).mutex );
   LOCK( (*current).mutex );
   INVARIANT( other );

   int32_t i = 0;
   Type *array = NULL;
   Type *other_array = NULL;

   // get array of values
   array = (*current).array;

   // delete values
   for ( i = 0; i < (*current).count; i++ )
   {
      DISPOSE_FUNCTION( array[i] );
   }

   if ( (*other).capacity > (*current).capacity )
   {
      (*current).capacity = (*other).capacity;
      (*current).array = ( Type * ) realloc( (*current).array, (*other).capacity * sizeof( Type ) );
      CHECK( "(*current).array allocated correctly", (*current).array != NULL );

      (*current).capacity = (*other).capacity;
   }

   // copy from other
   other_array = (*other).array;
   array = (*current).array;
   for ( i = 0; i < (*other).count; i++ )
   {
      array[i] = other_array[i];
   }
   (*current).count = (*other).count;

   INVARIANT( current );
   INVARIANT( other );

   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_deep_copy
*/

void
Heap_deep_copy( Prefix )( Heap_type( Prefix ) *current, Heap_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HEAP_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*other).mutex );
   LOCK( (*current).mutex );
   INVARIANT( other );

   int32_t i = 0;
   Type *array = NULL;
   Type *other_array = NULL;

   // get array of values
   array = (*current).array;

   // delete values
   for ( i = 0; i < (*current).count; i++ )
   {
      DISPOSE_FUNCTION( array[i] );
   }

   if ( (*other).capacity > (*current).capacity )
   {
      (*current).capacity = (*other).capacity;
      (*current).array = ( Type * ) realloc( (*current).array, (*other).capacity * sizeof( Type ) );
      CHECK( "(*current).array allocated correctly", (*current).array != NULL );

      (*current).capacity = (*other).capacity;
   }

   // copy from other
   other_array = (*other).array;
   array = (*current).array;
   for ( i = 0; i < (*other).count; i++ )
   {
      array[i] = DUPLICATE_FUNCTION( other_array[i] );
   }
   (*current).count = (*other).count;

   INVARIANT( current );
   INVARIANT( other );

   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_is_equal
*/

int32_t
Heap_is_equal( Prefix )( Heap_type( Prefix ) *current, Heap_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HEAP_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*other).mutex );
   if ( current != other )
   {
      LOCK( (*current).mutex );
   }
   INVARIANT( current );
   INVARIANT( other );

   int32_t result = 0;
   int32_t i = 0;
   Type *array = NULL;
   Type *other_array = NULL;

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
            if ( array[i] != other_array[i] )
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
   Heap_is_deep_equal
*/

int32_t
Heap_is_deep_equal( Prefix )( Heap_type( Prefix ) *current, Heap_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HEAP_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*other).mutex );
   if ( current != other )
   {
      LOCK( (*current).mutex );
   }
   INVARIANT( current );
   INVARIANT( other );

   int32_t result = 0;
   int32_t i = 0;
   Type *array = NULL;
   Type *other_array = NULL;

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
            if ( EQUALITY_FUNCTION( array[i],  other_array[i] ) != 1 )
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
   Heap_dispose
*/

void
Heap_dispose( Prefix )( Heap_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == HEAP_TYPE ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete array
   free( (**current).array );

   // delete current struct
   free(*current);

   // set to null
   *current = NULL;

   return;
}

/**
   Heap_deep_dispose
*/

void
Heap_deep_dispose( Prefix )( Heap_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == HEAP_TYPE ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   int32_t i = 0;

   // get array of values
   Type *array = (**current).array;

   // delete values
   for ( i = 0; i < (**current).count; i++ )
   {
      DISPOSE_FUNCTION( array[i] );
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
   Heap_as_array

*/

Type *
Heap_as_array( Prefix )( Heap_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );

   Type *result = as_array( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Heap_item
*/

Type
Heap_item( Prefix )( Heap_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type value = DEFAULT_VALUE;

   value = (*current).array[0];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   Heap_count
*/

int32_t
Heap_count( Prefix )( Heap_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   Heap_capacity
*/

int32_t
Heap_capacity( Prefix )( Heap_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t capacity = (*current).capacity;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return capacity;
}

/**
   Heap_height
*/

int32_t
Heap_height( Prefix )( Heap_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = height( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   Heap_set_capacity
*/

void
Heap_set_capacity( Prefix )( Heap_type( Prefix ) *current, int32_t new_capacity )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   if ( new_capacity > (*current).capacity )
   {
      (*current).capacity = new_capacity;
      (*current).array = ( Type * ) realloc( (*current).array, (*current).capacity * sizeof( Type ) );
      CHECK( "(*current).array allocated correctly", (*current).array != NULL );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_is_empty
*/

int32_t
Heap_is_empty( Prefix )( Heap_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count ==  0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Heap_has
*/

int32_t
Heap_has( Prefix )( Heap_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Heap_put
*/

void
Heap_put( Prefix )( Heap_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   put( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_put_and_dispose
*/

void
Heap_put_and_dispose( Prefix )( Heap_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   put_and_dispose( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_append
*/

void
Heap_append( Prefix )( Heap_type( Prefix ) *current, Heap_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HEAP_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   int32_t i = 0;
   Type *other_array = NULL;

   // adjust capacity if needed
   if ( ( (*current).count + (*other).count ) < (*current).capacity )
   {
      (*current).capacity = (*current).count + (*other).count + 1;
      (*current).array = ( Type * ) realloc( (*current).array, (*current).capacity * sizeof( Type ) );
      CHECK( "(*current).array allocated correctly", (*current).array != NULL );
   }

   // copy from other
   other_array = (*other).array;
   for ( i = 0; i < (*other).count; i++ )
   {
      put( current, other_array[i] );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return;
}

/**
   Heap_append_and_dispose
*/

void
Heap_append_and_dispose( Prefix )( Heap_type( Prefix ) *current, Heap_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HEAP_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   int32_t i = 0;
   Type *other_array = NULL;

   // adjust capacity if needed
   if ( ( (*current).count + (*other).count ) < (*current).capacity )
   {
      (*current).capacity = (*current).count + (*other).count + 1;
      (*current).array = ( Type * ) realloc( (*current).array, (*current).capacity * sizeof( Type ) );
      CHECK( "(*current).array allocated correctly", (*current).array != NULL );
   }

   // copy from other
   other_array = (*other).array;
   for ( i = 0; i < (*other).count; i++ )
   {
      put_and_dispose( current, other_array[i] );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );
   UNLOCK( (*other).mutex );

   return;
}

/**
   Heap_remove
*/

void
Heap_remove( Prefix )( Heap_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has( current, value ) );

   remove( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_remove_and_dispose
*/

void
Heap_remove_and_dispose( Prefix )( Heap_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has( current, value ) );

   remove_and_dispose( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_prune
*/

void
Heap_prune( Prefix )( Heap_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( count >= 0 ) && ( count <= (*current).count ) );

   (*current).count = (*current).count - count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_prune_and_dispose
*/

void
Heap_prune_and_dispose( Prefix )( Heap_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( count >= 0 ) && ( count <= (*current).count ) );

   int32_t i = 0;
   int32_t current_count = 0;
   Type *array = NULL;

   array = (*current).array;
   current_count = (*current).count;

   for( i = 0; i < count; i++ )
   {
      DISPOSE_FUNCTION( array[ current_count - 1 - i ] );
   }

   (*current).count = (*current).count - count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_keep
*/

void
Heap_keep( Prefix )( Heap_type( Prefix ) *current, int32_t keep_count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( keep_count >= 0 ) && ( keep_count <= (*current).count ) );

   (*current).count = keep_count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_keep_and_dispose
*/

void
Heap_keep_and_dispose( Prefix )( Heap_type( Prefix ) *current, int32_t keep_count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( keep_count >= 0 ) && ( keep_count <= (*current).count ) );

   int32_t i = 0;
   int32_t count = 0;
   int32_t current_count = 0;
   Type *array = NULL;

   array = (*current).array;
   current_count = (*current).count;
   count = current_count - keep_count;

   for( i = 0; i < count; i++ )
   {
      DISPOSE_FUNCTION( array[ current_count - 1 - i ] );
   }

   (*current).count = keep_count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_wipe_out
*/

void
Heap_wipe_out( Prefix )( Heap_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set count to zero
   (*current).count = 0;

   POSTCONDITION( "is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Heap_wipe_out_and_dispose
*/

void
Heap_wipe_out_and_dispose( Prefix )( Heap_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HEAP_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;

   // get array of values
   Type *array = (*current).array;

   // delete values
   for ( i = 0; i < (*current).count; i++ )
   {
      DISPOSE_FUNCTION( array[i] );
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

