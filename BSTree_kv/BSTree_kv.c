/**
 @file BSTree_kv.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Binary Search Trees of keys with values"

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

 Function definitions for the opaque BSTree_kv_t type.

*/

#include "BSTree_kv.h"

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_Iterable_kv.ph"
#include "P_DIterable_kv.ph"
#endif // PROTOCOLS_ENABLED   

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
   struct node *parent;
   struct node *left;
   struct node *right;
};

typedef struct node node_t;

struct BSTree_kv_cursor_struct( Prefix );

/**
   Binary search tree structure definition.
*/

struct BSTree_kv_struct( Prefix )
{

   PROTOCOLS_DEFINITION;

   int32_t _type;
   int32_t _key_type;
   int32_t _item_type;

   node_t *root;
   int32_t count;
   int32_t is_balanced;
   BSTree_kv_cursor_type( Prefix ) *first_cursor;
   BSTree_kv_cursor_type( Prefix ) *last_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure definition. Holds reference to bstree, current node, node
   stack, and a pointer to the next cursor.
*/

struct BSTree_kv_cursor_struct( Prefix )
{
   BSTree_kv_type( Prefix ) *bstree;
   node_t *item;
   BSTree_kv_cursor_type( Prefix ) *next_cursor;

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
   has_recurse

   determine if the tree has a node with the specified key, recursive

   @param node the current node being searched
   @param key the key to search for
   @return 1 if value found, 0 otherwise
*/
static
int32_t
has_recurse( node_t *node, Key key )
{
   int32_t result = 0;

   // in order recursion - left, self, right
   // if tested value is found, exit
   if ( (*node).left != NULL )
   {
      result = has_recurse( (*node).left, key );
   }

   if ( result == 0 )
   {
      result = KEY_DEEP_EQUAL_FUNCTION( (*node).key, key );
   }

   if ( result == 0 )
   {
      if ( (*node).right != NULL )
      {
         result = has_recurse( (*node).right, key );
      }
   }
   return result;
}

/**
   has

   Return 1 if bstree has an item for key, 0 if not

   @param bstree BSTree_t instance
   @param key the key to query for
   @return 1 if item found, 0 otherwise

   Return 1 if bstree has an item for key, 0 if not

   @param current BSTree_kv_t instance
   @param key the key to query for
*/

static
int32_t
has( BSTree_kv_type( Prefix ) *current, Key key )
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      result = has_recurse( node, key );
   }

   return result;
}

/**
   has_eq_fn_recurse

   determine if the tree has a node with the specified key,
   uses the supplied equality function, recursive

   @param node the current node being searched
   @param key the key to search for
   @param equality_test_func the function to determine value equality
   @return 1 if value found, 0 otherwise
*/
static
int32_t
has_eq_fn_recurse
(
   node_t *node,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   int32_t result = 0;

   // in order recursion - left, self, right
   // if tested value is found, exit
   if ( (*node).left != NULL )
   {
      result = has_eq_fn_recurse( (*node).left, key, equality_test_func );
   }

   if ( result == 0 )
   {
      result = equality_test_func( (*node).key, key );
   }

   if ( result == 0 )
   {
      if ( (*node).right != NULL )
      {
         result = has_eq_fn_recurse( (*node).right, key, equality_test_func );
      }
   }
   return result;
}

/**
   has_eq_fn

   determine if the tree has a node with the specified key,
   uses the supplied equality function

   @param current tree instance
   @param key the key to query for
   @param equality_test_func the function to determine key equality
   @return 1 if value found, 0 otherwise
*/

static
int32_t
has_eq_fn
(
   BSTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      result = has_eq_fn_recurse( node, key, equality_test_func );
   }

   return result;
}

/**
   has_value_recurse

   determine if the tree has a node with the specified value, recursive

   @param node the current node being searched
   @param value the value to search for
   @return 1 if value found, 0 otherwise
*/
static
int32_t
has_value_recurse( node_t *node, Type value )
{
   int32_t result = 0;

   // in order recursion - left, self, right
   // if tested value is found, exit
   if ( (*node).left != NULL )
   {
      result = has_value_recurse( (*node).left, value );
   }

   if ( result == 0 )
   {
      result = VALUE_DEEP_EQUAL_FUNCTION( (*node).value, value );
   }

   if ( result == 0 )
   {
      if ( (*node).right != NULL )
      {
         result = has_value_recurse( (*node).right, value );
      }
   }
   return result;
}

/**
   has_value

   Return 1 if bstree has an item for value, 0 if not

   @param bstree BSTree_kv_t instance
   @param value the value to query for
*/

static
int32_t
has_value( BSTree_kv_type( Prefix ) *current, Type value )
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      result = has_value_recurse( node, value );
   }

   return result;
}

/**
   has_value_eq_fn_recurse

   determine if the tree has a node with the specified value,
   uses the supplied equality function, recursive

   @param node the current node being searched
   @param value the value to search for
   @param equality_test_func the function to determine value equality
   @return 1 if value found, 0 otherwise
*/
static
int32_t
has_value_eq_fn_recurse
(
   node_t *node,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   int32_t result = 0;

   // in order recursion - left, self, right
   // if tested value is found, exit
   if ( (*node).left != NULL )
   {
      result = has_value_eq_fn_recurse( (*node).left, value, equality_test_func );
   }

   if ( result == 0 )
   {
      result = equality_test_func( (*node).value, value );
   }

   if ( result == 0 )
   {
      if ( (*node).right != NULL )
      {
         result = has_value_eq_fn_recurse( (*node).right, value, equality_test_func );
      }
   }
   return result;
}

/**
   has_value_eq_fn

   determine if the tree has a node with the specified value,
   uses the supplied equality function

   @param current AVLTree_t instance
   @param value the value to query for
   @param equality_test_func the function to determine value equality
   @return 1 if value found, 0 otherwise
*/

static
int32_t
has_value_eq_fn
(
   BSTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      result = has_value_eq_fn_recurse( node, value, equality_test_func );
   }

   return result;
}

/**
   occurrences_recurse

   counts number of nodes with the specified key, recursive

   @param node the current node being searched
   @param key the key to search for
   @param count pointer to the count of occurrences found so far
*/
static
void
occurrences_recurse( node_t *node, Key key, int32_t *count )
{
   // in order recursion - left, self, right
   // if tested value is found, count it
   if ( (*node).left != NULL )
   {
      occurrences_recurse( (*node).left, key, count );
   }

   if ( KEY_DEEP_EQUAL_FUNCTION( (*node).key, key ) == 1 )
   {
      *count = *count + 1;
   }

   if ( (*node).right != NULL )
   {
      occurrences_recurse( (*node).right, key, count );
   }

   return;
}

/**
   occurrences

   Return count of item keys in bstree equal to value

   @param current BSTree_kv_t instance
   @param key the key to query for
   @return the count of items count
*/

static
int32_t
occurrences( BSTree_kv_type( Prefix ) *current, Key key )
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      occurrences_recurse( node, key, &result );
   }

   return result;
}

/**
   occurrences_eq_fn_recurse

   counts number of nodes with the specified key, recursive

   @param node the current node being searched
   @param key the value to key for
   @param count pointer to the count of occurrences found so far
   @param equality_test_func the function to determine value equality
*/
static
void
occurrences_eq_fn_recurse
(
   node_t *node,
   Key key,
   int32_t *count,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   // in order recursion - left, self, right
   // if tested value is found, count it
   if ( (*node).left != NULL )
   {
      occurrences_eq_fn_recurse( (*node).left, key, count, equality_test_func );
   }

   if ( equality_test_func( (*node).key, key ) == 1 )
   {
      *count = *count + 1;
   }

   if ( (*node).right != NULL )
   {
      occurrences_eq_fn_recurse( (*node).right, key, count, equality_test_func );
   }

   return;
}

/**
   occurrences_eq_fn

   Return count of item keys in bstree equal to key according to equality_test_func

   @param current BSTree_kv_t instance
   @param key the key to query for
   @param equality_test_func the test function for value equality
   @return the count of items count
*/

static
int32_t
occurrences_eq_fn
(
   BSTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      occurrences_eq_fn_recurse( node, key, &result, equality_test_func );
   }

   return result;
}

/**
   occurrences_value_recurse

   counts number of nodes with the specified value, recursive

   @param node the current node being searched
   @param value the value to search for
   @param count pointer to the count of occurrences found so far
*/
static
void
occurrences_value_recurse( node_t *node, Type value, int32_t *count )
{
   // in order recursion - left, self, right
   // if tested value is found, count it
   if ( (*node).left != NULL )
   {
      occurrences_value_recurse( (*node).left, value, count );
   }

   if ( VALUE_DEEP_EQUAL_FUNCTION( (*node).value, value ) == 1 )
   {
      *count = *count + 1;
   }

   if ( (*node).right != NULL )
   {
      occurrences_value_recurse( (*node).right, value, count );
   }

   return;
}

/**
   occurrences_value

   Return count of items in bstree equal to value

   @param current BSTree_kv_t instance
   @param value the value to query for
   @return the count of items count
*/

static
int32_t
occurrences_value( BSTree_kv_type( Prefix ) *current, Type value )
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      occurrences_value_recurse( node, value, &result );
   }

   return result;
}

/**
   occurrences_value_eq_fn_recurse

   counts number of nodes with the specified value, recursive

   @param node the current node being searched
   @param value the value to search for
   @param count pointer to the count of occurrences found so far
   @param equality_test_func the function to determine value equality
*/
static
void
occurrences_value_eq_fn_recurse
(
   node_t *node,
   Type value,
   int32_t *count,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   // in order recursion - left, self, right
   // if tested value is found, count it
   if ( (*node).left != NULL )
   {
      occurrences_value_eq_fn_recurse( (*node).left, value, count, equality_test_func );
   }

   if ( equality_test_func( (*node).value, value ) == 1 )
   {
      *count = *count + 1;
   }

   if ( (*node).right != NULL )
   {
      occurrences_value_eq_fn_recurse( (*node).right, value, count, equality_test_func );
   }

   return;
}

/**
   occurrences_value_eq_fn

   Return count of items in bstree equal to value according to equality_test_func

   @param current BSTree_kv_t instance
   @param value the value to query for
   @param equality_test_func the test function for value equality
   @return the count of items count
*/

static
int32_t
occurrences_value_eq_fn
(
   BSTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      occurrences_value_eq_fn_recurse( node, value, &result, equality_test_func );
   }

   return result;
}

static
void
cursor_start( BSTree_kv_cursor_type( Prefix ) *cursor );

static
void
cursor_forth( BSTree_kv_cursor_type( Prefix ) *cursor );

static
int32_t
cursor_off(  BSTree_kv_cursor_type( Prefix ) *cursor );

static
BSTree_kv_cursor_type( Prefix ) *
cursor_make( BSTree_kv_type( Prefix ) *current );

static
void
cursor_dispose( BSTree_kv_cursor_type( Prefix ) **cursor );

/**
   node_for_index

   Return node at index

   @param current the tree
   @param index the index of the desired node
   @return the desired node
*/

static
node_t *
node_for_index( BSTree_kv_type( Prefix ) *current, int32_t index )
{
   int32_t i = 0;
   node_t *result = NULL;

   // get cursor
   BSTree_kv_cursor_type( Prefix ) *c
      =  ( BSTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BSTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );

   // set bstree in cursor
   (*c).bstree = current;

   if ( ( index >= 0 ) || ( index < (*current).count ) )
   {
      // iterate to index
      cursor_start( c );
      result = (*c).item;

      for( i = 1; i <= index; i++ )
      {
         cursor_forth( c );
         result = (*c).item;
      }
   }

   free( c );

   return result;
}

/**
   index_for_node

   Return index of specified node

   @param current the tree
   @param node the specified node
   @return the index of the specified node
*/
static
int32_t
index_for_node( BSTree_kv_type( Prefix ) *current, node_t *node )
{
   int32_t result = 0;
   int32_t flag = 0;

   // get cursor
   BSTree_kv_cursor_type( Prefix ) *c
      =  ( BSTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BSTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );

   // set bstree in cursor
   (*c).bstree = current;

   if ( (*current).count > 0 )
   {
      cursor_start( c );

      while ( cursor_off( c ) == 0 )
      {
         if ( (*c).item == node )
         {
            flag = 1;
            break;
         }
         result = result + 1;
         cursor_forth( c );
      }
   }

   if ( flag == 0 )
   {
      result = -1;
   }

   // free c
   free( c );

   return result;
}

/**
   item_recurse

   Return node with specified key, recursive

   @param current the tree
   @param key the specified key
   @return the desired node
*/
static
node_t *
item_recurse( node_t *node, Key key )
{
   node_t *result = NULL;

   if ( KEY_DEEP_EQUAL_FUNCTION( key, (*node).key ) == 1 )
   {
      result = node;
   }

   if ( result == NULL )
   {
      if ( KEY_ORDER_FUNCTION( key, (*node).key ) == 1 )
      {

         if ( (*node).left != NULL )
         {
            result = item_recurse( (*node).left, key );
         }
      }
   }

   if ( result == NULL )
   {
      if ( KEY_ORDER_FUNCTION( key, (*node).key ) == 0 )
      {

         if ( (*node).right != NULL )
         {
            result = item_recurse( (*node).right, key );
         }
      }
   }

   return result;
}

/**
   item

   Return node in current that has key, NULL if none

   @param current BSTree_kv_t instance
   @param key the key to query for
*/

static
node_t *
item( BSTree_kv_type( Prefix ) *current, Key key )
{
   node_t *result = NULL;
   node_t *node = NULL;

   // get root node
   node = (*current).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      result = item_recurse( node, key );
   }

   return result;
}

/**
   node_for_key_recurse

   Find node with specified key, recursive

   @param node the current node
   @param key the specified key
   @return the desired node
*/
static
node_t *
node_for_key_recurse( node_t *node, Key key )
{
   node_t *result = NULL;
   node_t *temp = NULL;
   node_t *n = NULL;

   if ( KEY_DEEP_EQUAL_FUNCTION( key, (*node).key ) == 1 )
   {
      result = node;
   }

   if ( result == NULL )
   {
      if ( KEY_ORDER_FUNCTION( key, (*node).key ) == 1 )
      {

         if ( (*node).left != NULL )
         {
            result = node_for_key_recurse( (*node).left, key );
         }
         else
         {
            // get the previous node

            // get the node's parent
            temp = node;
            n = (*node).parent;

            // go up until we find a parent whose left child is not the previous node
            while ( ( n != NULL ) && ( (*n).left == temp ) )
            {
               temp = n;
               n = (*n).parent;
            }

            result = n;
         }
      }
   }

   if ( result == NULL )
   {
      if ( KEY_ORDER_FUNCTION( key, (*node).key ) == 0 )
      {

         if ( (*node).right != NULL )
         {
            result = node_for_key_recurse( (*node).right, key );
         }
         else
         {
            result = node;
         }
      }
   }

   return result;
}

/**
   node_for_value_recurse

   Find node with specified value, recursive

   @param node the current node
   @param value the specified value
   @return the desired node
*/
static
node_t *
node_for_value_recurse( node_t *node, Type value )
{
   node_t *result = NULL;

   // in order recursion - left, self, right
   // if tested value is found, exit
   if ( (*node).left != NULL )
   {
      result = node_for_value_recurse( (*node).left, value );
   }

   if ( result == NULL )
   {
      if ( VALUE_DEEP_EQUAL_FUNCTION( (*node).value, value ) == 1 )
      {
         result = node;
      }
   }

   if ( result == NULL )
   {
      if ( (*node).right != NULL )
      {
         result = node_for_value_recurse( (*node).right, value );
      }
   }
   return result;
}

/**
   put_recurse

   insert a node with a key-value into the tree, recursive

   @param node the current node
   @param value the value to insert
   @param key the key to insert
*/
static
int32_t
put_recurse( node_t *node, Type value, Key key )
{
   int32_t result = 0;
   node_t *new_node = NULL;

   // if value is inserted, exit

   // in order recursion - left, self, right
   if ( KEY_ORDER_FUNCTION( key, (*node).key ) == 1 ) // key < (*node).key
   {

      if ( (*node).left != NULL )
      {
         // if left node exists, recurse
         result = put_recurse( (*node).left, value, key );
      }
      else
      {
         // if left node does not exist, put new node with value there
         new_node = node_make();
         (*node).left = new_node;
         ( *new_node ).key = key;
         ( *new_node ).value = value;
         ( *new_node ).parent = node;
         result = 1;
      }

   }
   else // ( key > (*node).key )
   {

      if ( (*node).right != NULL )
      {
         // if right node exists, recurse
         result = put_recurse( (*node).right, value, key );
      }
      else
      {
         // if right node does not exist, put new node with value there
         new_node = node_make();
         (*node).right = new_node;
         ( *new_node ).key = key;
         ( *new_node ).value = value;
         ( *new_node ).parent = node;
         result = 1;
      }

   }

   return result;
}

/**
   put

   insert a value into the tree

   @param current the tree
   @param value the value to insert
*/

static
void
put( BSTree_kv_type( Prefix ) *current, Type value, Key key )
{
   node_t *node = NULL;
   node_t *new_node = NULL;

   // get root node
   node = (*current).root;

   // recurse to put value in tree
   if ( node == NULL )
   {
      new_node = node_make();
      (*current).root = new_node;
      ( *new_node ).key = key;
      ( *new_node ).value = value;
   }
   else
   {
      put_recurse( node, value, key );
   }

   // adjust count
   (*current).count = (*current).count + 1;

   return;
}

/**
   get_min

   find node with minimum value

   @param node the current node
   @return the found node
*/

static
node_t *
get_min( node_t *node )
{
   node_t *result = node;

   while ( (*result).left != NULL )
   {
      result = (*result).left;
   }

   return result;
}

/**
   keys_as_array_recurse

   fill an array with the keys in the tree in order, recursive

   @param node the current node being processed
   @param array the destination array for the values
   @param index pointer to the current index
*/
static
void
keys_as_array_recurse( node_t *node, Key *array, int32_t *index )
{
   // if has left child, recurse
   if ( (*node).left != NULL )
   {
      keys_as_array_recurse( (*node).left, array, index );
   }

   // handle this node
   array[ *index ] = (*node).key;
   *index = *index + 1;

   // if has right child, recurse
   if ( (*node).right != NULL )
   {
      keys_as_array_recurse( (*node).right, array, index );
   }

   return;
}

/**
   keys_as_array

   create and return an array with the keys in the tree in order

   @param current the tree
   @return the array, the last item in the array is 0 or NULL
*/

static
Key *
keys_as_array( BSTree_kv_type( Prefix ) *current )
{
   Type *result = NULL;
   int32_t index = 0;

   result = ( Key * ) calloc( (*current).count + 1, sizeof( Key ) );
   CHECK( "result allocated correctly", result != NULL );

   if ( (*current).root != NULL )
   {
      keys_as_array_recurse( (*current).root, result, &index );
   }

   return result;
}

/**
   values_as_array_recurse

   fill an array with the values in the tree in order, recursive

   @param node the current node being processed
   @param array the destination array for the values
   @param index pointer to the current index
*/
static
void
values_as_array_recurse( node_t *node, Type *array, int32_t *index )
{
   // if has left child, recurse
   if ( (*node).left != NULL )
   {
      values_as_array_recurse( (*node).left, array, index );
   }

   // handle this node
   array[ *index ] = (*node).value;
   *index = *index + 1;

   // if has right child, recurse
   if ( (*node).right != NULL )
   {
      values_as_array_recurse( (*node).right, array, index );
   }

   return;
}

/**
   values_as_array

   create and return an array with the values in the tree in order

   @param current the tree
   @return the array, the last item in the array is 0 or NULL
*/

static
Type *
values_as_array( BSTree_kv_type( Prefix ) *current )
{
   Type *result = NULL;
   int32_t index = 0;

   result = ( Type * ) calloc( (*current).count + 1, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   if ( (*current).root != NULL )
   {
      values_as_array_recurse( (*current).root, result, &index );
   }

   return result;
}

/**
   nodes_as_array_recurse

   fill an array with the nodes in the tree in order, recursive

   @param node the current node being processed
   @param array the destination array for the nodes
   @param index pointer to the current index
*/
static
void
nodes_as_array_recurse( node_t *node, node_t **array, int32_t *index )
{
   // if has left child, recurse
   if ( (*node).left != NULL )
   {
      nodes_as_array_recurse( (*node).left, array, index );
   }

   // handle this node
   array[ *index ] = node;
   *index = *index + 1;

   // if has right child, recurse
   if ( (*node).right != NULL )
   {
      nodes_as_array_recurse( (*node).right, array, index );
   }

   return;
}

/**
   nodes_as_array

   create and return an array with the nodes in the tree in order

   @param current the tree
   @return the array, the last item in the array is NULL
*/

static
node_t **
nodes_as_array( BSTree_kv_type( Prefix ) *current )
{
   node_t **result = NULL;
   int32_t index = 0;

   if ( (*current).count == 0 )
   {
      result = ( node_t ** ) calloc( 1, sizeof( node_t ) );
      CHECK( "result allocated correctly", result != NULL );
   }
   else
   {
      result = ( node_t ** ) calloc( (*current).count, sizeof( node_t ) );
      CHECK( "result allocated correctly", result != NULL );
   }

   if ( (*current).root != NULL )
   {
      nodes_as_array_recurse( (*current).root, result, &index );
   }

   return result;
}


#undef SWAP_GENERAL_CASE

/**
   swap_nodes

   In this BSTree_kv file, the only way that n1 and n2 can be connected is for
   n2 to be the right child of n1, and n2 cannot have a left child. When the
   macro SWAP_GENERAL_CASE is defined, code to handle the general case of n1
   and n2 being connected is included. If the macro is undefined, the general
   case code is not included and only code to handle this specific case is
   present.

   swap two nodes

   @param current the tree
   @param n1 the first node
   @param n2 the second node
*/
static
void
swap_nodes( BSTree_kv_type( Prefix ) *current, node_t *n1, node_t *n2 )
{
   node_t *parent = NULL;
   int32_t n1_parent_is_left = 0;
   int32_t n2_parent_is_left = 0;
   node_t *left = NULL;
   node_t *right = NULL;
   int32_t parent_of_n2_is_n1 = 0;
#ifdef SWAP_GENERAL_CASE
   int32_t parent_of_n1_is_n2 = 0;
   int32_t parent_has_left_child = 0;
#endif // SWAP_GENERAL_CASE

   // see if n1 and n2 are directly connected
#ifdef SWAP_GENERAL_CASE
   if ( (*n1).parent == n2 )
   {
      parent_of_n1_is_n2 = 1;
      if ( (*n2).left == n1 )
      {
         parent_has_left_child = 1;
      }
      else
      {
         parent_has_left_child = 0;
      }
   }
#endif // SWAP_GENERAL_CASE

   if ( (*n2).parent == n1 )
   {
      parent_of_n2_is_n1 = 1;
#ifdef SWAP_GENERAL_CASE
      if ( (*n1).left == n2 )
      {
         parent_has_left_child = 1;
      }
      else
      {
         parent_has_left_child = 0;
      }
#endif // SWAP_GENERAL_CASE

   }

   // get whether n1 and n2 parents have n1 and n2 as left or right children
   if ( (*n1).parent != NULL )
   {
      if ( ( *(*n1).parent ).left == n1 )
      {
         n1_parent_is_left = 1;
      }
      else
      {
         n1_parent_is_left = 0;
      }
   }

   if ( (*n2).parent != NULL )
   {
      if ( ( *(*n2).parent ).left == n2 )
      {
         n2_parent_is_left = 1;
      }
      else
      {
         n2_parent_is_left = 0;
      }
   }

   // save info for n1
   parent = (*n1).parent;
   left = (*n1).left;
   right = (*n1).right;

   (*n1).parent = (*n2).parent;
   (*n1).left = (*n2).left;
   (*n1).right = (*n2).right;

   // overwrite n1 info with n2 info
   if ( parent != NULL )
   {
      if ( n1_parent_is_left == 1 )
      {
         (*parent).left = n2;
      }
      else
      {
         (*parent).right = n2;
      }
   }

   if ( left != NULL )
   {
      (*left).parent = n2;
   }

   if ( right != NULL )
   {
      (*right).parent = n2;
   }

   // overwrite n2 info with n1 info
   if ( (*n2).parent != NULL )
   {
      if ( n2_parent_is_left == 1 )
      {
         ( *(*n2).parent ).left = n1;
      }
      else
      {
         ( *(*n2).parent ).right = n1;
      }
   }

   (*n2).parent = parent;

#ifdef SWAP_GENERAL_CASE
   if ( (*n2).left != NULL )
   {
      ( *(*n2).left ).parent = n1;
   }
#endif // SWAP_GENERAL_CASE   
   (*n2).left = left;


   if ( (*n2).right != NULL )
   {
      ( *(*n2).right ).parent = n1;
   }
   (*n2).right = right;

   // fix up parent-child pointers if n1 and n2 connected
#ifdef SWAP_GENERAL_CASE
   if ( parent_of_n1_is_n2 == 1 )
   {
      (*n2).parent = n1;
      if ( parent_has_left_child == 1 )
      {
         (*n1).left = n2;
      }
      else
      {
         (*n1).right = n2;
      }
   }
#endif // SWAP_GENERAL_CASE

   if ( parent_of_n2_is_n1 == 1 )
   {
      (*n1).parent = n2;
#ifdef SWAP_GENERAL_CASE
      if ( parent_has_left_child == 1 )
      {
         (*n2).left = n1;
      }
      else
      {
         (*n2).right = n1;
      }
#else
      (*n2).right = n1;
#endif
   }

   // correct root node if necessary
#ifdef SWAP_GENERAL_CASE
   if ( (*n1).parent == NULL )
   {
      (*current).root = n1;
   }
#endif // SWAP_GENERAL_CASE

   if ( (*n2).parent == NULL )
   {
      (*current).root = n2;
   }

   return;
}

/**
   remove_recurse

   remove a node from the tree. recursive

   @param current the tree
   @param node the node with the value to delete
*/
static
void
remove_recurse( BSTree_kv_type( Prefix ) *current, node_t *node )
{
   node_t *n = NULL;

   if ( ( (*node).left == NULL ) && ( (*node).right == NULL ) )
   {
      // no children, remove this node
      if ( ( *(*node).parent ).left == node )
      {
         // node is its parent's left child
         ( *(*node).parent ).left = NULL;
      }
      else
      {
         // node is its parent's right child
         ( *(*node).parent ).right = NULL;
      }

      // and dispose of the node
      node_dispose( &node );

   }
   else if ( ( (*node).left != NULL ) && ( (*node).right == NULL ) )
   {
      // one child, the left one

      // replace node with its left child
      if ( ( *(*node).parent ).left == node )
      {
         // node is its parent's left child
         ( *(*node).parent ).left = (*node).left;
         ( *(*node).left ).parent = (*node).parent;
      }
      else
      {
         // node is its parent's right child
         ( *(*node).parent ).right = (*node).left;
         ( *(*node).left ).parent = (*node).parent;
      }

      // and dispose of the node
      node_dispose( &node );

   }
   else if ( ( (*node).left == NULL ) && ( (*node).right != NULL ) )
   {
      // one child, the right one

      // replace node with its right child
      if ( ( *(*node).parent ).left == node )
      {
         // node is its parent's left child
         ( *(*node).parent ).left = (*node).right;
         ( *(*node).right ).parent = (*node).parent;
      }
      else
      {
         // node is its parent's right child
         ( *(*node).parent ).right = (*node).right;
         ( *(*node).right ).parent = (*node).parent;
      }

      // and dispose of the node
      node_dispose( &node );

   }
   else // two children
   {
      // find min from this node's right chile
      n = get_min( (*node).right );

      swap_nodes( current, node, n );

      // recursively remove "node"
      remove_recurse( current, node );

   }

   return;
}

/**
   removE

   spelled with an ending capital E to avoid name clash with remove() from <stdio.h>

   remove a node from the tree

   @param current the tree
   @param node the node to remove
*/

static
void
removE( BSTree_kv_type( Prefix ) *current, node_t *node )
{
   BSTree_kv_cursor_type( Prefix ) *cursor = NULL;

   if ( node != NULL )
   {
      // move cursors pointing to this node forth
      cursor = (*current).first_cursor;
      while ( cursor != NULL )
      {
         if ( (*cursor).item == node )
         {
            cursor_forth( cursor );
         }

         cursor = (*cursor).next_cursor;
      }

      // case of only one node (the root)
      if ( (*current).count == 1 )
      {
         node_dispose( &node );
         (*current).root = NULL;
      }
      else if ( (*node).parent == NULL )
      {
         // special case of root node with one child
         if ( ( (*node).left != NULL ) && ( (*node).right == NULL ) )
         {
            (*current).root = (*node).left;
            ( *(*current).root ).parent = NULL;
            node_dispose( &node );
         }
         else if ( ( (*node).left == NULL ) && ( (*node).right != NULL ) )
         {
            (*current).root = (*node).right;
            ( *(*current).root ).parent = NULL;
            node_dispose( &node );
         }
         else
         {
            // delete the node
            remove_recurse( current, node );
         }
      }
      else
      {
         // delete the node
         remove_recurse( current, node );
      }

      // decrement count
      (*current).count = (*current).count - 1;
   }

   return;
}

/**
   remove_and_dispose_recurse

   remove a node from the tree and delete its value, recursive

   @param current the tree
   @param node the node to remove
*/
static
void
remove_and_dispose_recurse( BSTree_kv_type( Prefix ) *current, node_t *node )
{
   node_t *n = NULL;

   if ( ( (*node).left == NULL ) && ( (*node).right == NULL ) )
   {
      // no children, remove this node
      if ( ( *(*node).parent ).left == node )
      {
         // node is its parent's left child
         ( *(*node).parent ).left = NULL;
      }
      else
      {
         // node is its parent's right child
         ( *(*node).parent ).right = NULL;
      }

      // dispose of the key
      KEY_DEEP_DISPOSE_FUNCTION( (*node).key );

      // dispose of the value
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

      // and dispose of the node
      node_dispose( &node );

   }
   else if ( ( (*node).left != NULL ) && ( (*node).right == NULL ) )
   {
      // one child, the left one

      // replace node with its left child
      if ( ( *(*node).parent ).left == node )
      {
         // node is its parent's left child
         ( *(*node).parent ).left = (*node).left;
         ( *(*node).left ).parent = (*node).parent;
      }
      else
      {
         // node is its parent's right child
         ( *(*node).parent ).right = (*node).left;
         ( *(*node).left ).parent = (*node).parent;
      }

      // dispose of the key
      KEY_DEEP_DISPOSE_FUNCTION( (*node).key );

      // dispose of the value
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

      // and dispose of the node
      node_dispose( &node );

   }
   else if ( ( (*node).left == NULL ) && ( (*node).right != NULL ) )
   {
      // one child, the right one

      // replace node with its right child
      if ( ( *(*node).parent ).left == node )
      {
         // node is its parent's left child
         ( *(*node).parent ).left = (*node).right;
         ( *(*node).right ).parent = (*node).parent;
      }
      else
      {
         // node is its parent's right child
         ( *(*node).parent ).right = (*node).right;
         ( *(*node).right ).parent = (*node).parent;
      }

      // dispose of the key
      KEY_DEEP_DISPOSE_FUNCTION( (*node).key );

      // dispose of the value
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

      // and dispose of the node
      node_dispose( &node );

   }
   else // two children
   {
      // find min from this node's right child
      n = get_min( (*node).right );

      swap_nodes( current, node, n );

      // recursively remove "node"
      remove_and_dispose_recurse( current, node );

   }

   return;
}

/**
   remove_and_dispose

   remove a node from the tree and delete its value

   @param current the tree
   @param node the node to remove
*/
static
void
remove_and_dispose( BSTree_kv_type( Prefix ) *current, node_t *node )
{
   BSTree_kv_cursor_type( Prefix ) *cursor = NULL;

   if ( node != NULL )
   {
      // move cursors pointing to this node forth
      cursor = (*current).first_cursor;
      while ( cursor != NULL )
      {
         if ( (*cursor).item == node )
         {
            cursor_forth( cursor );
         }

         cursor = (*cursor).next_cursor;
      }

      // case of only one node
      if ( (*current).count == 1 )
      {
         KEY_DEEP_DISPOSE_FUNCTION( (*node).key );
         VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
         (*current).root = NULL;
      }
      else if ( (*node).parent == NULL )
      {
         // special case of root node with one child
         if ( ( (*node).left != NULL ) && ( (*node).right == NULL ) )
         {
            (*current).root = (*node).left;
            KEY_DEEP_DISPOSE_FUNCTION( (*node).key );
            VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
            ( *(*current).root ).parent = NULL;
            node_dispose( &node );
         }
         else if ( ( (*node).left == NULL ) && ( (*node).right != NULL ) )
         {
            (*current).root = (*node).right;
            KEY_DEEP_DISPOSE_FUNCTION( (*node).key );
            VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
            ( *(*current).root ).parent = NULL;
            node_dispose( &node );
         }
         else
         {
            // delete the node
            remove_and_dispose_recurse( current, node );
         }
      }
      else
      {
         // delete the node
         remove_and_dispose_recurse( current, node );
      }

      // decrement count
      (*current).count = (*current).count - 1;
   }

   return;
}

/**
   height_recurse

   find and return the height of the tree, recursive

   @param node the current node
   @return the height of node
*/
static
int
height_recurse( node_t *node )
{
   int32_t result = 0;
   int32_t left_height = 0;
   int32_t right_height = 0;

   if ( node == NULL )
   {
      result = 0;
   }
   else
   {
      left_height = height_recurse( (*node).left );
      right_height = height_recurse( (*node).right );

      if ( left_height > right_height )
      {
         result = left_height + 1;
      }
      else
      {
         result = right_height + 1;
      }
   }

   return result;

}

/**
   height

   find and return the height of the tree

   @param current the tree
   @return the height of the tree
*/
static
int
height( BSTree_kv_type( Prefix ) *current )
{
   int32_t result = 0;

   result = height_recurse( (*current).root );

   return result;
}

/**
   count_recurse

   find and return the number of nodes in the tree, recursive

   @param node the current node
   @return the count of children of node
*/
static
int
count_recurse( node_t *node )
{
   int32_t result = 0;
   int32_t left_count = 0;
   int32_t right_count = 0;

   if ( node == NULL )
   {
      result = 0;
   }
   else
   {
      left_count = count_recurse( (*node).left );
      right_count = count_recurse( (*node).right );

      result = left_count + right_count + 1;
   }

   return result;

}

/**
   count

   find and return the number of nodes in the tree

   @param current the tree
   @return the count of nodes in current
*/
static
int
count( BSTree_kv_type( Prefix ) *current )
{
   int32_t result = 0;

   result = count_recurse( (*current).root );

   return result;
}

/**
   compression DSW algorithm

   Day–Stout–Warren (DSW) algorithm to balance the tree

   @param node the node
   @param count how many nodes to process
*/
static
void
compression( node_t *node, int32_t count )
{
   int32_t i = 0;
   node_t *scanner = NULL;
   node_t *child = NULL;

   scanner = node;
   for ( i = 0; i < count; i++ )
   {
      // Leftward rotation
      child = (*scanner).right;
      (*scanner).right = (*child).right;
      scanner = (*scanner).right;
      (*child).right = (*scanner).left;
      (*scanner).left = child;
   }

   return;
}

/**
   full_size DSW algorithm
   Full portion of a complete tree

   part of Day–Stout–Warren (DSW) algorithm to balance the tree

   @param size height of the tree
   @return how many nodes
*/
static
int32_t
full_size( int32_t size )
{
   int32_t result = 1;

   // loop to one step PAST FULL
   while ( result <= size )
   {
      // get next pow(2,k)-1
      result = result + result + 1;
   }

   return result / 2;
}

/**
   tree_to_vine

   put tree into a right child only tree, similar to a linked list,
   as part of algotirhn to balancing the tree

   @param root the tree
*/
static
void
tree_to_vine( node_t *root )
{
   node_t *tail = NULL;
   node_t *remainder = NULL;
   node_t *temp = NULL;

   // initial conditions
   tail = root;
   remainder = (*tail).right;

   while ( remainder != NULL )
   {
      // if no leftward subtree, move rightward
      if ( (*remainder).left == NULL )
      {
         tail = remainder;
         remainder = (*remainder).right;
      }
      // else eliminate leftward subtree by rotations
      else
      {
         // rightward rotation
         temp = (*remainder).left;
         (*remainder).left = (*temp).right;
         (*temp).right = remainder;
         remainder = temp;
         (*tail).right = temp;
      }
   }

   return;
}
/**
   vine_to_tree

   reorganize the tree from a right child only tree to a balanced tree,
   part of algorithm to balance the tree

   @param root the tree
   @param size the special value computed by full_size()
*/
static
void
vine_to_tree( node_t *root, int32_t size )
{
   int32_t full_count = 0;

   // get size of full binary tree
   full_count = full_size( size );

   // first pass
   compression( root, size - full_count );

   // iteratively flatten tree
   for ( size = full_count; size > 1; size /= 2 )
   {
      compression( root, size / 2 );
   }

   return;
}

/**
   set_node_parent_pointers_recurse

   go through the tree and set parent node pointers, recursive

   @param tree the tree
*/
static
int32_t
set_node_parent_pointers_recurse( node_t *node )
{
   int32_t result = 1;

   if ( (*node).left != NULL )
   {
      ( *(*node).left ).parent = node;
   }

   if ( result == 1 )
   {
      if ( (*node).right != NULL )
      {
         ( *(*node).right ).parent = node;
      }
   }

   if ( result == 1 )
   {
      if ( (*node).left != NULL )
      {
         result = set_node_parent_pointers_recurse( (*node).left );
      }
   }

   if ( result == 1 )
   {
      if ( (*node).right != NULL )
      {
         result = set_node_parent_pointers_recurse( (*node).right );
      }
   }

   return result;
}

/**
   set_node_parent_pointers

   go through the tree and set parent node pointers

   @param tree the tree
*/
static
int32_t
set_node_parent_pointers( BSTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).count > 1 )
   {
      result = set_node_parent_pointers_recurse( (*current).root );
   }

   return result;
}

/**
   balance

   full algorithm to balance the tree

   @param current the tree
*/
static
void
balance( BSTree_kv_type( Prefix ) *current )
{
   if ( (*current).count > 1 )
   {
      node_t *node = NULL;

      // add pseudo-root
      node = node_make();
      (*node).right = (*current).root;
      (*current).root = node;

      // tree to vine
      tree_to_vine( (*current).root );

      // vine to tree
      vine_to_tree( (*current).root, (*current).count );

      // remove pseudo-root
      (*current).root = (*node).right;
      node_dispose( &node );

      // set node parent pointers
      set_node_parent_pointers( current );
   }

   // set root parent to NULL
   if ( (*current).root != NULL )
   {
      ( *(*current).root ).parent = NULL;
   }

   return;
}

/**
   recursion for bstree cursor functions - start, item, forth, off

   The following routines depend on the fact that the bstree
   is (already) in order and that the forth recursion keeps track
   of the last seen ( the previous ) node (in the cursor structure).
*/

/**
   cursor_finish
*/
static
void
cursor_finish( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;

   // set node from the bstree root
   node = ( *(*cursor).bstree ).root;

   if ( node != NULL )
   {
      // walk to the rightmost node from the tree root
      while ( (*node).right != NULL )
      {
         node = (*node).right;
      }
   }

   // set data items in the cursor
   (*cursor).item = node;

   return;
}

/**
   cursor_start
*/
static
void
cursor_start( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;

   // set node from the bstree root
   node = ( *(*cursor).bstree ).root;

   if ( node != NULL )
   {
      // walk to the leftmost node from the tree root
      while ( (*node).left != NULL )
      {
         node = (*node).left;
      }
   }

   // set data items in the cursor
   (*cursor).item = node;

   return;
}

/**
   cursor_key_at
*/
static
Key
cursor_key_at( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   // return the key for the current cursor item
   return ( *(*cursor).item ).key;
}

/**
   cursor_item
*/
static
Type
cursor_item_at( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   // return the value for the current cursor item
   return ( *(*cursor).item ).value;
}


/**
   cursor_back
*/
static
void
cursor_back( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;
   node_t *temp = NULL;

   // go to next item in sequence ( or off )
   if ( (*cursor).item != NULL )
   {
      node = (*cursor).item;

      // if the node's left child is not null
      if ( (*node).left != NULL )
      {
         // find the rightmost child of the node's left child
         node = (*node).left;
         while ( (*node).right != NULL )
         {
            node = (*node).right;
         }
      }
      else // if the node's left child is null
      {
         // get the node's parent
         temp = node;
         node = (*node).parent;

         // go up until we find a parent whose left child is not the previous node
         while ( ( node != NULL ) && ( (*node).left == temp ) )
         {
            temp = node;
            node = (*node).parent;
         }
      }
   }

   (*cursor).item = node;

   return;
}

/**
   cursor_forth
*/
static
void
cursor_forth( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;
   node_t *temp = NULL;

   // go to next item in sequence ( or off )
   if ( (*cursor).item != NULL )
   {
      node = (*cursor).item;

      // if node's right child is not null
      if ( (*node).right != NULL )
      {
         // get leftmost child of node's right child
         node = (*node).right;
         while ( (*node).left != NULL )
         {
            node = (*node).left;
         }
      }
      else // if node's right child is null
      {
         // get parent
         temp = node;
         node = (*node).parent;

         // go up until we find a parent whose right child is not the previous node
         while ( ( node != NULL ) && ( (*node).right == temp ) )
         {
            temp = node;
            node = (*node).parent;
         }
      }
   }

   (*cursor).item = node;

   return;
}

/**
   cursor_off
*/
static
int32_t
cursor_off(  BSTree_kv_cursor_type( Prefix ) *cursor )
{
   int32_t result = 0;

   // cursor item is null == off
   if ( (*cursor).item == NULL )
   {
      result = 1;
   }

   return result;
}

/**
   cursor_make
*/

static
BSTree_kv_cursor_type( Prefix ) *
cursor_make( BSTree_kv_type( Prefix ) *current )
{
   // allocate cursor struct
   BSTree_kv_cursor_type( Prefix ) *cursor
      =  ( BSTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BSTree_kv_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set bstree
   (*cursor).bstree = current;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // place cursor reference into bstree structure
   if ( (*current).last_cursor == NULL )
   {
      // set second cursor for bstree
      ( *(*current).first_cursor ).next_cursor = cursor;
      (*current).last_cursor = cursor;
   }
   else
   {
      // set additional cursor for bstree
      // (*bstree).last_cursor holds last cursor allocated
      ( *(*current).last_cursor ).next_cursor = cursor;
      (*current).last_cursor = cursor;
   }

   MULTITHREAD_MUTEX_INIT( (*cursor).mutex );

   return cursor;
}

/**
   cursor_dispose
*/

static
void
cursor_dispose( BSTree_kv_cursor_type( Prefix ) **cursor )
{
   BSTree_kv_cursor_type( Prefix ) *c1 = NULL;
   BSTree_kv_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from bstree structure
   c1 = ( *(**cursor).bstree ).first_cursor;
   c2 = (*c1).next_cursor;

   // search through the cursors
   while ( ( c2 != NULL ) && ( flag == 0 ) )
   {
      if ( c2 == *cursor )
      {
         // if we have a match, remove "c2" from the cursor bstree, set flag
         (*c1).next_cursor = (*c2).next_cursor;
         flag = 1;

         c2 = NULL;
      }
      else
      {
         // advance c1 and c2
         c1 = c2;
         if ( c1 != NULL )
         {
            c2 = (*c1).next_cursor;
         }
      }
   }

   // set bstree's last cursor
   c1 = ( *(**cursor).bstree ).first_cursor;
   while ( c1 != NULL )
   {
      c2 = c1;
      c1 = (*c1).next_cursor;
   }
   ( *(**cursor).bstree ).last_cursor = c2;

   // only one cursor, last_cursor is NULL
   if ( c2 == ( *(**cursor).bstree ).first_cursor )
   {
      ( *(**cursor).bstree ).last_cursor = NULL;
   }

   // delete cursor struct
   free(*cursor);

   // set to NULL
   *cursor = NULL;

   return;
}

/**
   move_all_cursors_off
*/
static
void
move_all_cursors_off( BSTree_kv_type( Prefix ) *current )
{
   BSTree_kv_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   while( cursor != NULL )
   {
      // set cursor item to null == off
      (*cursor).item = NULL;

      cursor = (*cursor).next_cursor;
   }

   return;
}

/**
   compare tree items to array items

   compare values in tree to values in an array

   @param current the tree
   @param array the array
   @param array_count the number of items in array
   @return 1 if all values are equal, 0 otherwise
*/

static
int32_t
compare_tree_items_to_array_items( BSTree_kv_type( Prefix ) *current, Key *keys, Type *values, int32_t array_count )
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t count = 0;
   int32_t i = 0;
   node_t *n = NULL;

   // check count
   if ( (*current).count == array_count )
   {
      flag = 1;
   }

   result = flag;

   if ( result == 1 )
   {
      flag = 0;
      for( i = 0; i < array_count; i++ )
      {
         if ( has( current, keys[i] ) == 1 )
         {
            n = item( current, keys[i] );
            if ( (*n).value == values[i] )
            {
               count = count + 1;
            }
         }
      }
      if ( ( count = (*current).count ) && ( count = array_count ) )
      {
         flag = 1;
      }
   }

   result = flag;

   return result;
}

/**
   compare tree items to tree items

   compare values in one tree to values in another tree

   @param current the tree
   @param other the other tree
   @return 1 if all values are equal, 0 otherwise
*/

static
int32_t
compare_tree_items_to_tree_items( BSTree_kv_type( Prefix ) *current, BSTree_kv_type( Prefix ) *other )
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t count = 0;
   BSTree_kv_cursor_type( Prefix ) *c1
      =  ( BSTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BSTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c1 allocated correctly", c1 != NULL );

   BSTree_kv_cursor_type( Prefix ) *c2
      =  ( BSTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BSTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c2 allocated correctly", c2 != NULL );

   // set bstree in cursors
   (*c1).bstree = current;
   (*c2).bstree = other;

   cursor_start( c1 );
   cursor_start( c2 );

   // check count
   flag = 0;
   if ( (*current).count == (*other).count )
   {
      flag = 1;
   }

   result = flag;

   flag = 0;
   if ( result == 1 )
   {
      while( ( cursor_off( c1 ) == 0 ) && ( cursor_off( c2 ) == 0 ) )
      {
         if (
            ( cursor_key_at( c1 ) == cursor_key_at( c2 ) )
            &&
            ( cursor_item_at( c1 ) == cursor_item_at( c2 ) )
         )
         {
            count = count + 1;
         }

         cursor_forth( c1 );
         cursor_forth( c2 );
      }

      if ( count == (*current).count )
      {
         flag = 1;
      }
   }

   result = flag;

   // deallocate cursors
   free( c1 );
   free( c2 );

   return result;
}

/**
   compare tree items to tree items deep equal

   compare values in one tree to values in another tree, deep_equal

   @param current the tree
   @param other the other tree
   @return 1 if all values are equal, 0 otherwise
*/

static
int32_t
compare_tree_items_to_tree_items_deep_equal( BSTree_kv_type( Prefix ) *current, BSTree_kv_type( Prefix ) *other )
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t count = 0;
   BSTree_kv_cursor_type( Prefix ) *c1
      =  ( BSTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BSTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c1 allocated correctly", c1 != NULL );

   BSTree_kv_cursor_type( Prefix ) *c2
      =  ( BSTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BSTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c2 allocated correctly", c2 != NULL );

   // set bstree in cursors
   (*c1).bstree = current;
   (*c2).bstree = other;

   cursor_start( c1 );
   cursor_start( c2 );

   // check count
   flag = 0;
   if ( (*current).count == (*other).count )
   {
      flag = 1;
   }

   result = flag;

   flag = 0;
   if ( result == 1 )
   {
      while( ( cursor_off( c1 ) == 0 ) && ( cursor_off( c2 ) == 0 ) )
      {
         if (
            ( KEY_DEEP_EQUAL_FUNCTION( cursor_key_at( c1 ), cursor_key_at( c2 ) ) == 1 )
            &&
            ( VALUE_DEEP_EQUAL_FUNCTION( cursor_item_at( c1 ), cursor_item_at( c2 ) ) == 1 )
         )
         {
            count = count + 1;
         }

         cursor_forth( c1 );
         cursor_forth( c2 );
      }

      if ( count == (*current).count )
      {
         flag = 1;
      }
   }

   result = flag;

   // deallocate cursors
   free( c1 );
   free( c2 );

   return result;
}


/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
is_empty_implies_root_null( BSTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).count == 0 )
   {
      result = ( (*current).root == NULL );
   }

   return result;
}

static
int32_t
nonnegative_count( BSTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).count >= 0 );

   return result;
}

static
int32_t
valid_count( BSTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( count( current ) == (*current).count );

   return result;
}

static
int32_t
first_cursor_not_null( BSTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).first_cursor != NULL );

   return result;
}

static
int32_t
cursors_bstree_kv_ok( BSTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   BSTree_kv_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   while( ( cursor != NULL ) && ( result == 1 ) )
   {
      result = ( (*cursor).bstree == current );
      cursor = (*cursor).next_cursor;
   }

   return result;
}

static
int32_t
last_cursor_next_null( BSTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).last_cursor != NULL )
   {
      result = ( ( *(*current).last_cursor ).next_cursor == NULL );
   }

   return result;
}

static
int32_t
last_cursor_null_if_one_cursor( BSTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( ( *(*current).first_cursor ).next_cursor == NULL )
   {
      result = ( (*current).last_cursor == NULL );
   }

   return result;
}

static
int32_t
in_order_recurse( node_t *node )
{
   int32_t result = 1;

   if ( (*node).left != NULL )
   {
      result = KEY_ORDER_FUNCTION( ( *(*node).left ).key, (*node).key );
   }

   if ( result == 1 )
   {
      if ( (*node).right != NULL )
      {
         result = KEY_ORDER_FUNCTION( (*node).key, ( *(*node).right ).key );
      }
   }

   if ( result == 1 )
   {
      if ( (*node).left != NULL )
      {
         result = in_order_recurse( (*node).left );
      }
   }

   if ( result == 1 )
   {
      if ( (*node).right != NULL )
      {
         result = in_order_recurse( (*node).right );
      }
   }

   return result;
}

static
int32_t
in_order( BSTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).count > 1 )
   {
      result = in_order_recurse( (*current).root );
   }

   return result;
}

static
int32_t
count_by_cursor_ok( BSTree_kv_type( Prefix ) *current )
{
   BSTree_kv_cursor_type( Prefix ) *cursor = NULL;
   int32_t count = 0;
   int32_t max = 0;
   int32_t result = 0;

   cursor = cursor_make( current );
   max = 2 * (*current).count;

   cursor_start( cursor );
   while( ( cursor_off( cursor ) == 0 ) && ( max > 0 ) )
   {
      count = count + 1;
      max = max - 1;
      cursor_forth( cursor );
   }

   cursor_dispose( &cursor );

   if ( count == (*current).count )
   {
      result = 1;
   }

   return result;
}

/**
   cursors_null_or_valid
*/

static
int32_t
cursors_null_or_valid( BSTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;
   BSTree_kv_cursor_type( Prefix ) *cursor = NULL;

   // get cursor
   BSTree_kv_cursor_type( Prefix ) *c
      =  ( BSTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BSTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );

   // set bstree in cursor
   (*c).bstree = current;

   // loop through cursors
   cursor = (*current).first_cursor;

   // loop: if a cursor is not off and its item is not in tree, return 0
   while( ( cursor != NULL ) && ( result == 1 ) )
   {
      if ( (*cursor).item == NULL )
      {
         cursor = (*cursor).next_cursor;
         continue;
      }

      // iterate c to find item
      cursor_start( c );
      result = 0;

      while( (*c).item != NULL )
      {
         if ( (*cursor).item == (*c).item )
         {
            result = 1;
            break;
         }
         cursor_forth( c );
      }

      cursor = (*cursor).next_cursor;
   }

   free( c );

   return result;
}

static
int32_t
node_pointers_consistent_recurse( node_t *node )
{
   int32_t result = 1;

   if ( (*node).left != NULL )
   {
      result = ( ( *(*node).left ).parent == node );
   }

   if ( result == 1 )
   {
      if ( (*node).right != NULL )
      {
         result = ( ( *(*node).right ).parent == node );
      }
   }

   if ( result == 1 )
   {
      if ( (*node).left != NULL )
      {
         result = node_pointers_consistent_recurse( (*node).left );
      }
   }

   if ( result == 1 )
   {
      if ( (*node).right != NULL )
      {
         result = node_pointers_consistent_recurse( (*node).right );
      }
   }

   return result;
}

static
int32_t
node_pointers_consistent( BSTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).count > 1 )
   {
      result = node_pointers_consistent_recurse( (*current).root );
   }

   if ( result == 1 )
   {
      if ( (*current).count >= 1 )
      {
         result = ( *(*current).root ).parent == NULL;
      }
   }

   return result;
}

static
void invariant( BSTree_kv_type( Prefix ) *current )
{
   assert( ( ( void ) "empty implies root null", is_empty_implies_root_null( current ) ) );
   assert( ( ( void ) "nonnegative count", nonnegative_count( current ) ) );
   assert( ( ( void ) "valid count", valid_count( current ) ) );
   assert( ( ( void ) "count by cursor", count_by_cursor_ok( current ) ) );
   assert( ( ( void ) "first cursor not null", first_cursor_not_null( current ) ) );
   assert( ( ( void ) "last cursor next null", last_cursor_next_null( current ) ) );
   assert( ( ( void ) "last cursor null if one cursor", last_cursor_null_if_one_cursor( current ) ) );
   assert( ( ( void ) "cursors bstree OK", cursors_bstree_kv_ok( current ) ) );
   assert( ( ( void ) "bstree in order", in_order( current ) ) );
   assert( ( ( void ) "node pointers consistent", node_pointers_consistent( current ) ) );
   assert( ( ( void ) "cursors null or valid", cursors_null_or_valid( current ) ) );
   return;
}

#endif


/**
   Protocol stuff
*/

#ifdef PROTOCOLS_ENABLED

/**
   Protocol Function Arrays
*/

static
void *
p_basic_table[P_BASIC_FUNCTION_COUNT]
=
{
   BSTree_kv_dispose( Prefix ),
   BSTree_kv_deep_dispose( Prefix ),
   BSTree_kv_is_equal( Prefix ),
   BSTree_kv_is_deep_equal( Prefix ),
   BSTree_kv_copy( Prefix ),
   BSTree_kv_deep_copy( Prefix ),
   BSTree_kv_clone( Prefix ),
   BSTree_kv_deep_clone( Prefix )
};

static
void *
p_iterable_kv_table[P_ITERABLE_KV_FUNCTION_COUNT]
=
{
   BSTree_kv_count( Prefix ),
   BSTree_kv_key_at( Prefix ),
   BSTree_kv_item_at( Prefix ),
   BSTree_kv_off( Prefix ),
   BSTree_kv_is_empty( Prefix ),
   BSTree_kv_start( Prefix ),
   BSTree_kv_forth( Prefix )
};

static
void *
p_diterable_kv_table[P_DITERABLE_KV_FUNCTION_COUNT]
=
{
   BSTree_kv_count( Prefix ),
   BSTree_kv_key_at( Prefix ),
   BSTree_kv_item_at( Prefix ),
   BSTree_kv_off( Prefix ),
   BSTree_kv_is_empty( Prefix ),
   BSTree_kv_start( Prefix ),
   BSTree_kv_forth( Prefix ),
   BSTree_kv_finish( Prefix ),
   BSTree_kv_back( Prefix )
};

/**
   protocol get_function

   returns function pointer for requested protocol function

   @param protocol_id which protocol
   @param function_id which function
   @return function pointer if found, NULL otherwise
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

   switch ( protocol_id )
   {
      case P_BASIC_TYPE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_BASIC_FUNCTION_MAX ) )
         {
            result = p_basic_table[ function_id ];
         }
         break;
      }

      case P_ITERABLE_KV_TYPE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_ITERABLE_KV_FUNCTION_MAX ) )
         {
            result = p_iterable_kv_table[ function_id ];
         }
         break;
      }

      case P_DITERABLE_KV_TYPE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_DITERABLE_KV_FUNCTION_MAX ) )
         {
            result = p_diterable_kv_table[ function_id ];
         }
         break;
      }

   }

   return result;
}

/**
   protocol supports_protocol

   returns 1 if this class supports the specified protocol

   @param protocol_id which protocol
   @return 1 if protocol supported, 0 otherwise
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

   switch ( protocol_id )
   {
      case P_BASIC_TYPE:
      {
         result = 1;
         break;
      }

      case P_ITERABLE_KV_TYPE:
      {
         result = 1;
         break;
      }

      case P_DITERABLE_KV_TYPE:
      {
         result = 1;
         break;
      }

   }

   return result;
}

#endif // PROTOCOLS_ENABLED


/**
   BSTree_kv_make
*/

BSTree_kv_type( Prefix ) *
BSTree_kv_make( Prefix )( void )
{
   // allocate bstree struct
   BSTree_kv_type( Prefix ) *result
      = ( BSTree_kv_type( Prefix ) * ) calloc( 1, sizeof( BSTree_kv_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = BSTREE_KV_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   // root is null
   (*result).root = NULL;

   // count is zero
   (*result).count = 0;

   // empty trees are balanced
   (*result).is_balanced = 1;

   // set built-in cursor
   // allocate cursor struct
   BSTree_kv_cursor_type( Prefix ) *cursor
      =  ( BSTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BSTree_kv_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set bstree
   (*cursor).bstree = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set bstree built-in cursor
   (*result).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new result is empty", (*result).count == 0 );
   POSTCONDITION( "new result cursor is off", ( *(*result).first_cursor ).item == NULL );

   INVARIANT( result );

   return result;
}

/**
   BSTree_kv_make_from_array
*/

BSTree_kv_type( Prefix ) *
BSTree_kv_make_from_array( Prefix )( Key *key_array, Type *value_array, int32_t count )
{
   PRECONDITION( "key_array not null", key_array != NULL );
   PRECONDITION( "value_array not null", value_array != NULL );
   PRECONDITION( "count  ok", count >= 0 );

   // make bstree struct
   BSTree_kv_type( Prefix ) *result = BSTree_kv_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = BSTREE_KV_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   int32_t i = 0;

   for ( i = 0; i < count; i++ )
   {
      put( result, value_array[i], key_array[i] );
   }

   // balance this new tree
   balance( result );

   POSTCONDITION( "new result cursor is off", ( *(*result).first_cursor ).item == NULL );
   POSTCONDITION( "new result contains elements of array", compare_tree_items_to_array_items( result, key_array, value_array, count ) );

   INVARIANT( result );

   return result;
}

/**
   BSTree_kv_clone
*/

BSTree_kv_type( Prefix ) *
BSTree_kv_clone( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );

   // make bstree struct
   BSTree_kv_type( Prefix ) *result = BSTree_kv_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = BSTREE_KV_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   // copy from current
   BSTree_kv_cursor_type( Prefix ) *cursor = BSTree_kv_cursor_make( Prefix )( current );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, cursor_item_at( cursor ), cursor_key_at( cursor ) );
      cursor_forth( cursor );
   }

   // balance this new tree
   balance( result );

   // set is_balanced
   (*result).is_balanced = 1;

   POSTCONDITION( "new tree cursor is off", ( *(*result).first_cursor ).item == NULL );
   POSTCONDITION( "new tree contains elements of current", compare_tree_items_to_tree_items( result, current ) );

   INVARIANT( result );

   return result;
}

/**
   BSTree_kv_deep_clone
*/

BSTree_kv_type( Prefix ) *
BSTree_kv_deep_clone( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );

   // make bstree struct
   BSTree_kv_type( Prefix ) *result = BSTree_kv_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = BSTREE_KV_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   // copy from bstree
   BSTree_kv_cursor_type( Prefix ) *cursor = BSTree_kv_cursor_make( Prefix )( current );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, KEY_DEEP_CLONE_FUNCTION( cursor_item_at( cursor ) ), VALUE_DEEP_CLONE_FUNCTION( cursor_key_at( cursor ) ) );
      cursor_forth( cursor );
   }

   // balance this new tree
   balance( result );

   // set is_balanced
   (*result).is_balanced = 1;

   POSTCONDITION( "new tree cursor is off", ( *(*result).first_cursor ).item == NULL );
   POSTCONDITION( "new tree contains elements of current", compare_tree_items_to_tree_items_deep_equal( result, current ) );

   INVARIANT( result );

   return result;
}

/**
   BSTree_kv_is_equal
*/

int32_t
BSTree_kv_is_equal( Prefix )( BSTree_kv_type( Prefix ) *current, BSTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == BSTREE_KV_TYPE ) && ( (*other)._item_type = Type_Code ) );

   // lock current
   LOCK( (*current).mutex );

   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = compare_tree_items_to_tree_items( current, other );

      // unlock other
      UNLOCK( (*other).mutex );

      INVARIANT( current );
   }

   // unlock current
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_is_deep_equal
*/

int32_t
BSTree_kv_is_deep_equal( Prefix )( BSTree_kv_type( Prefix ) *current, BSTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == BSTREE_KV_TYPE ) && ( (*other)._item_type = Type_Code ) );

   // lock current
   LOCK( (*current).mutex );

   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = compare_tree_items_to_tree_items_deep_equal( current, other );

      // unlock other
      UNLOCK( (*other).mutex );

      INVARIANT( current );
   }

   // unlock current
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_copy
*/

void
BSTree_kv_copy( Prefix )( BSTree_kv_type( Prefix ) *current, BSTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == BSTREE_KV_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t i = 0;
   BSTree_kv_cursor_type( Prefix ) *c
      =  ( BSTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BSTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );

   (*c).bstree = other;

   // empty out current
   node_t **array = nodes_as_array( current );

   // delete nodes and values
   for ( i = 0; i < (*current).count; i++ )
   {
      KEY_DEEP_DISPOSE_FUNCTION( ( *array[i] ).key );
      VALUE_DEEP_DISPOSE_FUNCTION( ( *array[i] ).value );
      node_dispose( &array[i] );
   }

   // free array
   free( array );

   // move all cursors off - tree will be mangled
   move_all_cursors_off( current );

   // lock other
   LOCK( (*other).mutex );

   // reset count
   (*current).count = 0;

   // clear is_balanced
   (*current).is_balanced = 0;

   // set root to NULL
   (*current).root = NULL;

   cursor_start( c );

   while ( cursor_off( c ) == 0 )
   {
      put( current, cursor_item_at( c ), cursor_key_at( c ) );
      cursor_forth( c );
   }

   // free c
   free( c );

   POSTCONDITION( "new bstree contains elements of other", compare_tree_items_to_tree_items( current, other ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return;
}

/**
   BSTree_kv_deep_copy
*/

void
BSTree_kv_deep_copy( Prefix )( BSTree_kv_type( Prefix ) *current, BSTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == BSTREE_KV_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t i = 0;
   Key k;
   Type v;
   BSTree_kv_cursor_type( Prefix ) *c
      =  ( BSTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BSTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );

   (*c).bstree = other;

   // empty out current
   node_t **array = nodes_as_array( current );

   // delete nodes and values
   for ( i = 0; i < (*current).count; i++ )
   {
      KEY_DEEP_DISPOSE_FUNCTION( ( *array[i] ).key );
      VALUE_DEEP_DISPOSE_FUNCTION( ( *array[i] ).value );
      node_dispose( &array[i] );
   }

   // free array
   free( array );

   // move all cursors off - tree will be mangled
   move_all_cursors_off( current );

   // lock other
   LOCK( (*other).mutex );

   // reset count
   (*current).count = 0;

   // clear is_balanced
   (*current).is_balanced = 0;

   // set root to NULL
   (*current).root = NULL;

   cursor_start( c );

   while ( cursor_off( c ) == 0 )
   {
      k = KEY_DEEP_CLONE_FUNCTION( cursor_key_at( c ) );
      v = VALUE_DEEP_CLONE_FUNCTION( cursor_item_at( c ) );
      put( current, v, k );
      cursor_forth( c );
   }

   // free cursor
   free( c );

   POSTCONDITION( "new bstree contains elements of other", compare_tree_items_to_tree_items_deep_equal( current, other ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return;
}

/**
   BSTree_kv_cursor_make
*/

BSTree_kv_cursor_type( Prefix ) *
BSTree_kv_cursor_make( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   BSTree_kv_cursor_type( Prefix ) * cursor = NULL;

   cursor = cursor_make( current );

   INVARIANT( current );
   POSTCONDITION( "new cursor is last cursor", (*current).last_cursor == cursor );
   UNLOCK( (*current).mutex );

   return cursor;
}

/**
   BSTree_kv_dispose
*/

void
BSTree_kv_dispose( Prefix )( BSTree_kv_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == BSTREE_KV_TYPE ) && ( (**current)._key_type = Key_Code ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   int32_t i = 0;

   // get array of nodes
   node_t **array = nodes_as_array(*current);

   // delete nodes
   for ( i = 0; i < (**current).count; i++ )
   {
      node_dispose( &array[i] );
   }

   // delete array
   free( array );

   // delete cursors
   BSTree_kv_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   BSTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   BSTree_kv_deep_dispose
*/

void
BSTree_kv_deep_dispose( Prefix )( BSTree_kv_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == BSTREE_KV_TYPE ) && ( (**current)._key_type = Key_Code ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   int32_t i = 0;

   // get array of nodes
   node_t **array = nodes_as_array(*current);

   // delete nodes and values
   for ( i = 0; i < (**current).count; i++ )
   {
      KEY_DEEP_DISPOSE_FUNCTION( ( *array[i] ).key );
      VALUE_DEEP_DISPOSE_FUNCTION( ( *array[i] ).value );
      node_dispose( &array[i] );
   }

   // delete array
   free( array );

   // delete cursors
   BSTree_kv_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   BSTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   BSTree_kv_cursor_dispose
*/

void
BSTree_kv_cursor_dispose( Prefix )( BSTree_kv_cursor_type( Prefix ) **cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "*cursor not null", *cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(**cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(**cursor).bstree )._key_type = Key_Code ) && ( ( *(**cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (**cursor).mutex );
   LOCK( ( *(**cursor).bstree ).mutex );
   INVARIANT( (**cursor).bstree );

   BSTree_kv_type( Prefix ) *bstree = (**cursor).bstree;

   cursor_dispose( cursor );

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return;
}

/**
   BSTree_kv_keys_as_array

*/

Type *
BSTree_kv_keys_as_array( Prefix )( BSTree_kv_type( Prefix ) *current, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*current).mutex );

   Key *result = keys_as_array( current );

   *count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_values_as_array

*/

Type *
BSTree_kv_values_as_array( Prefix )( BSTree_kv_type( Prefix ) *current, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*current).mutex );

   Type *result = values_as_array( current );

   *count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_cursor_key_at
*/

Key
BSTree_kv_cursor_key_at( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._key_type = Key_Code ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Key key = cursor_key_at( cursor );

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return key;
}

/**
   BSTree_kv_cursor_item_at
*/

Type
BSTree_kv_cursor_item_at( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._key_type = Key_Code ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Type value = cursor_item_at( cursor );

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}


/**
   BSTree_kv_key_at
*/

Key
BSTree_kv_key_at( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   BSTree_kv_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   Key key = cursor_key_at( cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return key;
}

/**
   BSTree_kv_item_at
*/

Type
BSTree_kv_item_at( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   BSTree_kv_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   Type value = cursor_item_at( cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   BSTree_kv_key
*/

Key
BSTree_kv_key( Prefix )( BSTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   node_t *node = node_for_index( current, index );
   Key result = (*node).key;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_item
*/

Type
BSTree_kv_item( Prefix )( BSTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );
   INVARIANT( current );

   node_t *node = node_for_index( current, index );
   Type result = (*node).value;


   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_first
*/

Type
BSTree_kv_first( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "current not empty", (*current).root != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = VALUE_DEFAULT;
   node_t *node = (*current).root;

   while ( (*node).left != NULL )
   {
      node = (*node).left;
   }

   if ( node != NULL )
   {
      result = (*node).value;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_last
*/

Type
BSTree_kv_last( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "current not empty", (*current).root != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = VALUE_DEFAULT;
   node_t *node = (*current).root;

   while ( (*node).right != NULL )
   {
      node = (*node).right;
   }

   if ( node != NULL )
   {
      result = (*node).value;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_key_first
*/

Key
BSTree_kv_key_first( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "current not empty", (*current).root != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Key result = KEY_DEFAULT;
   node_t *node = (*current).root;

   while ( (*node).left != NULL )
   {
      node = (*node).left;
   }

   if ( node != NULL )
   {
      result = (*node).key;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_key_last
*/

Key
BSTree_kv_key_last( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "current not empty", (*current).root != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Key result = KEY_DEFAULT;
   node_t *node = (*current).root;

   while ( (*node).right != NULL )
   {
      node = (*node).right;
   }

   if ( node != NULL )
   {
      result = (*node).key;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_count
*/

int32_t
BSTree_kv_count( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   BSTree_kv_height
*/

int32_t
BSTree_kv_height( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = height( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   BSTree_kv_off
*/

int32_t
BSTree_kv_off( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = cursor_off( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_cursor_off
*/

int32_t
BSTree_kv_cursor_off( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._key_type = Key_Code ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   int32_t result = cursor_off( cursor );

   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   BSTree_kv_cursor_is_first
*/

int32_t
BSTree_kv_cursor_is_first( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );

   node_t *node = node_for_index( (*cursor).bstree, 0 );
   int32_t result = ( node == (*cursor).item );

   if ( ( *(*cursor).bstree ).count == 0 )
   {
      result = 0;
   }

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   BSTree_kv_cursor_is_last
*/

int32_t
BSTree_kv_cursor_is_last( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );

   node_t *node = node_for_index( (*cursor).bstree, ( *(*cursor).bstree ).count - 1 );
   int32_t result = ( node == (*cursor).item );

   if ( ( *(*cursor).bstree ).count == 0 )
   {
      result = 0;
   }

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   BSTree_kv_cursor_key_search_forth
*/

void
BSTree_kv_cursor_key_search_forth( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor, Key key )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( KEY_DEEP_EQUAL_FUNCTION( ( *(*cursor).item ).key, key ) == 0 )
   )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_cursor_key_search_forth_eq_fn
*/

void
BSTree_kv_cursor_key_search_forth_eq_fn( Prefix )
(
   BSTree_kv_cursor_type( Prefix ) *cursor,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( equality_test_func( ( *(*cursor).item ).key, key ) == 0 )
   )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_cursor_search_forth
*/

void
BSTree_kv_cursor_search_forth( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( VALUE_DEEP_EQUAL_FUNCTION( ( *(*cursor).item ).value, value ) == 0 )
   )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_cursor_search_forth_eq_fn
*/

void
BSTree_kv_cursor_search_forth_eq_fn( Prefix )
(
   BSTree_kv_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( equality_test_func( ( *(*cursor).item ).value, value ) == 0 )
   )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_cursor_key_search_back
*/

void
BSTree_kv_cursor_key_search_back( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor, Key key )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( KEY_DEEP_EQUAL_FUNCTION( ( *(*cursor).item ).key, key ) == 0 )
   )
   {
      cursor_back( cursor );
   }

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_cursor_key_search_back_eq_fn
*/

void
BSTree_kv_cursor_key_search_back_eq_fn( Prefix )
(
   BSTree_kv_cursor_type( Prefix ) *cursor,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( equality_test_func( ( *(*cursor).item ).key, key ) == 0 )
   )
   {
      cursor_back( cursor );
   }

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_cursor_search_back
*/

void
BSTree_kv_cursor_search_back( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( VALUE_DEEP_EQUAL_FUNCTION( ( *(*cursor).item ).value, value ) == 0 )
   )
   {
      cursor_back( cursor );
   }

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_cursor_search_back_eq_fn
*/

void
BSTree_kv_cursor_search_back_eq_fn( Prefix )
(
   BSTree_kv_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( equality_test_func( ( *(*cursor).item ).value, value ) == 0 )
   )
   {
      cursor_back( cursor );
   }

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_is_empty
*/

int32_t
BSTree_kv_is_empty( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count ==  0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_is_first
*/

int32_t
BSTree_kv_is_first( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   node_t *node = node_for_index( current, 0 );

   int32_t result = ( node == ( *(*current).first_cursor ).item );

   if ( (*current).count == 0 )
   {
      result = 0;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_is_last
*/

int32_t
BSTree_kv_is_last( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t index = (*current).count - 1;
   if ( index < 0 )
   {
      index = 0;
   }

   node_t *node = node_for_index( current, index );

   int32_t result = ( node == ( *(*current).first_cursor ).item );

   if ( (*current).count == 0 )
   {
      result = 0;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_has
*/

int32_t
BSTree_kv_has( Prefix )( BSTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has( current, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_has_eq_fn
*/

int32_t
BSTree_kv_has_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has_eq_fn( current, key, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_has_value
*/

int32_t
BSTree_kv_has_value( Prefix )( BSTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has_value( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_has_value_eq_fn
*/

int32_t
BSTree_kv_has_value_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has_value_eq_fn( current, value, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_occurrences
*/

int32_t
BSTree_kv_occurrences( Prefix )( BSTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences( current, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_occurrences_eq_fn
*/

int32_t
BSTree_kv_occurrences_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences_eq_fn( current, key, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_occurrences_value
*/

int32_t
BSTree_kv_occurrences_value( Prefix )( BSTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences_value( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_occurrences_value_eq_fn
*/

int32_t
BSTree_kv_occurrences_value_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences_value_eq_fn( current, value, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_key_search_forth
*/

void
BSTree_kv_key_search_forth( Prefix )( BSTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   while
   (
      ( ( *(*current).first_cursor ).item != NULL )
      &&
      ( KEY_DEEP_EQUAL_FUNCTION( ( *( *(*current).first_cursor ).item ).key, key ) == 0 )
   )
   {
      cursor_forth( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_key_search_forth_eq_fn
*/

void
BSTree_kv_key_search_forth_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   while
   (
      ( ( *(*current).first_cursor ).item != NULL )
      &&
      ( equality_test_func( ( *( *(*current).first_cursor ).item ).key, key ) == 0 )
   )
   {
      cursor_forth( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_search_forth
*/

void
BSTree_kv_search_forth( Prefix )( BSTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   while
   (
      ( ( *(*current).first_cursor ).item != NULL )
      &&
      ( VALUE_DEEP_EQUAL_FUNCTION( ( *( *(*current).first_cursor ).item ).value, value ) == 0 )
   )
   {
      cursor_forth( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_search_forth_eq_fn
*/

void
BSTree_kv_search_forth_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   while
   (
      ( ( *(*current).first_cursor ).item != NULL )
      &&
      ( equality_test_func( ( *( *(*current).first_cursor ).item ).value, value ) == 0 )
   )
   {
      cursor_forth( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_key_search_back
*/

void
BSTree_kv_key_search_back( Prefix )( BSTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   while
   (
      ( ( *(*current).first_cursor ).item != NULL )
      &&
      ( KEY_DEEP_EQUAL_FUNCTION( ( *( *(*current).first_cursor ).item ).key, key ) == 0 )
   )
   {
      cursor_back( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_key_search_back_eq_fn
*/

void
BSTree_kv_key_search_back_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   while
   (
      ( ( *(*current).first_cursor ).item != NULL )
      &&
      ( equality_test_func( ( *( *(*current).first_cursor ).item ).key, key ) == 0 )
   )
   {
      cursor_back( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_search_back
*/

void
BSTree_kv_search_back( Prefix )( BSTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   while
   (
      ( ( *(*current).first_cursor ).item != NULL )
      &&
      ( VALUE_DEEP_EQUAL_FUNCTION( ( *( *(*current).first_cursor ).item ).value, value ) == 0 )
   )
   {
      cursor_back( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_search_back_eq_fn
*/

void
BSTree_kv_search_back_eq_fn( Prefix )
(
   BSTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   INVARIANT( current );

   while
   (
      ( ( *(*current).first_cursor ).item != NULL )
      &&
      ( equality_test_func( ( *( *(*current).first_cursor ).item ).value, value ) == 0 )
   )
   {
      cursor_back( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_cursor_back
*/
void
BSTree_kv_cursor_back( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._key_type = Key_Code ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   cursor_back( cursor );

   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_cursor_forth
*/
void
BSTree_kv_cursor_forth( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._key_type = Key_Code ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   cursor_forth( cursor );

   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_cursor_go
*/
void
BSTree_kv_cursor_go( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._key_type = Key_Code ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < ( *(*cursor).bstree ).count ) ) );
   INVARIANT( (*cursor).bstree );

   int32_t i = 0;
   cursor_start( cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_cursor_go_to_key
*/
void
BSTree_kv_cursor_go_to_key( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor, Key key )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );
   POSTCONDITION_VARIABLE_DEFINE( BSTree_kv_cursor_type( Prefix ) c; c.bstree = (*cursor).bstree; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_empty = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_first = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_last = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_equal = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_lt = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_gt = 0; );

   node_t *node = NULL;

   if ( ( *(*cursor).bstree ).root != NULL )
   {
      node = node_for_key_recurse( ( *(*cursor).bstree ).root, key );
   }

   (*cursor).item = node;

   POSTCONDITION_VARIABLE_DEFINE( c.item = node; if ( ( *(*cursor).bstree ).count > 0 )
{
   if ( node == NULL )
      {
         cursor_start( &c );
      }
      else
      {
         cursor_forth( &c );
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( ( *(*cursor).bstree ).count == 0 )
{
   is_empty = 1;
} );
   POSTCONDITION_VARIABLE_DEFINE( if ( ( node == NULL ) && ( c.item != NULL ) )
{
   is_first = 1;
} );
   POSTCONDITION_VARIABLE_DEFINE( if ( ( node != NULL ) && ( c.item == NULL ) )
{
   is_last = 1;
} );
   POSTCONDITION_VARIABLE_DEFINE( if ( node != NULL )
{
   if ( KEY_DEEP_EQUAL_FUNCTION( key, (*node).key ) == 1 )
      {
         is_equal = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( node != NULL )
{
   if ( KEY_ORDER_FUNCTION( (*node).key, key ) == 1 )
      {
         is_lt = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( c.item != NULL )
{
   if ( KEY_ORDER_FUNCTION( key, ( *c.item ).key ) == 1 )
      {
         is_gt = 1;
      }
   } );

   POSTCONDITION
   (
      "node ok",
      ( is_empty == 1 ? 1 :
        ( is_first == 1 ? 1 :
          ( is_last == 1 ? 1 :
            ( is_equal == 1 ? 1 :
              ( ( is_lt == 1 ) && ( is_gt == 1 ) ? 1 : 0 )
            )
          )
        )
      )
   );

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );

   return;
}

/**
   BSTree_kv_cursor_index
*/

int32_t
BSTree_kv_cursor_index( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._key_type = Key_Code ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );

   int32_t result = 0;

   result = index_for_node( (*cursor).bstree, (*cursor).item );

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   BSTree_kv_cursor_finish
*/

void
BSTree_kv_cursor_finish( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._key_type = Key_Code ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );

   cursor_finish( cursor );

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_cursor_start
*/

void
BSTree_kv_cursor_start( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._key_type = Key_Code ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );

   cursor_start( cursor );

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_cursor_remove_at
*/

void
BSTree_kv_cursor_remove_at( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "current type ok", ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc =  ( *(*cursor).item ).key; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( (*cursor).bstree, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).bstree ).count; );

   node_t *node = NULL;
   node = (*cursor).item;

   removE( (*cursor).bstree, node );

   // clear is_balanced
   ( *(*cursor).bstree ).is_balanced = 0;

   POSTCONDITION( "element removed", i_pc == occurrences( (*cursor).bstree, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == ( *(*cursor).bstree ).count + 1 );

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_cursor_remove_at_and_dispose
*/

void
BSTree_kv_cursor_remove_at_and_dispose( Prefix )( BSTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "current type ok", ( ( *(*cursor).bstree )._type == BSTREE_KV_TYPE ) && ( ( *(*cursor).bstree )._item_type = Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).bstree ).mutex );
   INVARIANT( (*cursor).bstree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = KEY_DEEP_CLONE_FUNCTION( ( *(*cursor).item ).key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( (*cursor).bstree, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).bstree ).count; );

   node_t *node = NULL;
   node = (*cursor).item;

   remove_and_dispose( (*cursor).bstree, node );

   // clear is_balanced
   ( *(*cursor).bstree ).is_balanced = 0;

   POSTCONDITION( "element removed", i_pc == occurrences( (*cursor).bstree, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == ( *(*cursor).bstree ).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( KEY_DEEP_DISPOSE_FUNCTION( key_pc ); );

   INVARIANT( (*cursor).bstree );
   UNLOCK( ( *(*cursor).bstree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_kv_back
*/
void
BSTree_kv_back( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );
   INVARIANT( current );

   cursor_back( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_forth
*/
void
BSTree_kv_forth( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );
   INVARIANT( current );

   cursor_forth( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_go
*/
void
BSTree_kv_go( Prefix )( BSTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   INVARIANT( current );

   int32_t i = 0;
   cursor_start( (*current).first_cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_go_to_key
*/
void
BSTree_kv_go_to_key( Prefix )( BSTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( BSTree_kv_cursor_type( Prefix ) c; c.bstree = current; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_empty = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_first = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_last = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_equal = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_lt = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_gt = 0; );

   node_t *node = NULL;

   if ( (*current).root != NULL )
   {
      node = node_for_key_recurse( (*current).root, key );
   }

   ( *(*current).first_cursor ).item = node;

   POSTCONDITION_VARIABLE_DEFINE( c.item = node; if ( (*current).count > 0 )
{
   if ( node == NULL )
      {
         cursor_start( &c );
      }
      else
      {
         cursor_forth( &c );
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( (*current).count == 0 )
{
   is_empty = 1;
} );
   POSTCONDITION_VARIABLE_DEFINE( if ( ( node == NULL ) && ( c.item != NULL ) )
{
   is_first = 1;
} );
   POSTCONDITION_VARIABLE_DEFINE( if ( ( node != NULL ) && ( c.item == NULL ) )
{
   is_last = 1;
} );
   POSTCONDITION_VARIABLE_DEFINE( if ( node != NULL )
{
   if ( KEY_DEEP_EQUAL_FUNCTION( key, (*node).key ) == 1 )
      {
         is_equal = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( node != NULL )
{
   if ( KEY_ORDER_FUNCTION( (*node).key, key ) == 1 )
      {
         is_lt = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( c.item != NULL )
{
   if ( KEY_ORDER_FUNCTION( key, ( *c.item ).key ) == 1 )
      {
         is_gt = 1;
      }
   } );

   POSTCONDITION
   (
      "node ok",
      ( is_empty == 1 ? 1 :
        ( is_first == 1 ? 1 :
          ( is_last == 1 ? 1 :
            ( is_equal == 1 ? 1 :
              ( ( is_lt == 1 ) && ( is_gt == 1 ) ? 1 : 0 )
            )
          )
        )
      )
   );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_index
*/

int32_t
BSTree_kv_index( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = index_for_node( current, ( *(*current).first_cursor ).item );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   BSTree_kv_finish
*/

void
BSTree_kv_finish( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cursor_finish( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_start
*/

void
BSTree_kv_start( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cursor_start( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_put
*/

void
BSTree_kv_put( Prefix )( BSTree_kv_type( Prefix ) *current, Type value, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   put( current, value, key );

   // clear is_balanced
   (*current).is_balanced = 0;

   POSTCONDITION( "count incremented", (*current).count == ( i_pc + 1 ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_remove
*/

void
BSTree_kv_remove( Prefix )( BSTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has( current, key ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_key_recurse( (*current).root, key );

   removE( current, node );

   // clear is_balanced
   (*current).is_balanced = 0;

   POSTCONDITION( "element removed", i_pc == occurrences( current, key ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_remove_and_dispose
*/

void
BSTree_kv_remove_and_dispose( Prefix )( BSTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has( current, key ) );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = KEY_DEEP_CLONE_FUNCTION( key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_key_recurse( (*current).root, key );

   remove_and_dispose( current, node );

   // clear is_balanced
   (*current).is_balanced = 0;

   POSTCONDITION( "element removed", i_pc == occurrences( current, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( KEY_DEEP_DISPOSE_FUNCTION( key_pc ); );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_remove_by_index
*/

void
BSTree_kv_remove_by_index( Prefix )( BSTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, index );

   removE( current, node );

   // clear is_balanced
   (*current).is_balanced = 0;

   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_remove_by_index_and_dispose
*/

void
BSTree_kv_remove_by_index_and_dispose( Prefix )( BSTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, index );

   remove_and_dispose( current, node );

   // clear is_balanced
   (*current).is_balanced = 0;

   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_remove_value
*/

void
BSTree_kv_remove_value( Prefix )( BSTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has_value( current, value ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences_value( current, value ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   if ( (*current).root != NULL )
   {
      node = node_for_value_recurse( (*current).root, value );
   }

   removE( current, node );

   // clear is_balanced
   (*current).is_balanced = 0;

   POSTCONDITION( "element removed", i_pc == occurrences_value( current, value ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_remove_value_and_dispose
*/

void
BSTree_kv_remove_value_and_dispose( Prefix )( BSTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has_value( current, value ) );
   POSTCONDITION_VARIABLE_DEFINE( Type value_pc = VALUE_DEEP_CLONE_FUNCTION( value ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences_value( current, value ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   if ( (*current).root != NULL )
   {
      node = node_for_value_recurse( (*current).root, value );
   }

   remove_and_dispose( current, node );

   // clear is_balanced
   (*current).is_balanced = 0;

   POSTCONDITION( "element removed", i_pc == occurrences_value( current, value_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( VALUE_DEEP_DISPOSE_FUNCTION( value_pc ); );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_remove_at
*/

void
BSTree_kv_remove_at( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = ( *(*current).first_cursor ).item;

   removE( current, node );

   // clear is_balanced
   (*current).is_balanced = 0;

   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_remove_at_and_dispose
*/

void
BSTree_kv_remove_at_and_dispose( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = ( *(*current).first_cursor ).item;

   remove_and_dispose( current, node );

   // clear is_balanced
   (*current).is_balanced = 0;

   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_remove_first
*/

void
BSTree_kv_remove_first( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = ( * node_for_index( current, 0 ) ).key; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, 0 );

   removE( current, node );

   // clear is_balanced
   (*current).is_balanced = 0;

   POSTCONDITION( "element removed", i_pc == occurrences( current, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_remove_first_and_dispose
*/

void
BSTree_kv_remove_first_and_dispose( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = KEY_DEEP_CLONE_FUNCTION( ( * node_for_index( current, 0 ) ).key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, 0 );

   remove_and_dispose( current, node );

   // clear is_balanced
   (*current).is_balanced = 0;

   POSTCONDITION( "element removed", i_pc == occurrences( current, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( KEY_DEEP_DISPOSE_FUNCTION( key_pc ); );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_remove_last
*/

void
BSTree_kv_remove_last( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = ( * node_for_index( current, (*current).count - 1 ) ).key; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, (*current).count - 1 );

   removE( current, node );

   // clear is_balanced
   (*current).is_balanced = 0;

   POSTCONDITION( "element removed", i_pc == occurrences( current, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_remove_last_and_dispose
*/

void
BSTree_kv_remove_last_and_dispose( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = KEY_DEEP_CLONE_FUNCTION( ( * node_for_index( current, (*current).count - 1 ) ).key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, (*current).count - 1 );

   remove_and_dispose( current, node );

   // clear is_balanced
   (*current).is_balanced = 0;

   POSTCONDITION( "element removed", i_pc == occurrences( current, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( KEY_DEEP_DISPOSE_FUNCTION( key_pc ); );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_wipe_out
*/

void
BSTree_kv_wipe_out( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;

   // get array of nodes
   node_t **array = nodes_as_array( current );

   // delete nodes
   for ( i = 0; i < (*current).count; i++ )
   {
      node_dispose( &array[i] );
   }

   // delete array
   free( array );

   // delete cursors, all but first
   BSTree_kv_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   BSTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
   ( *(*current).first_cursor ).next_cursor = NULL;
   (*current).last_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // set count to zero
   (*current).count = 0;

   // set root to NULL
   (*current).root = NULL;

   // set is_balanced
   (*current).is_balanced = 1;

   POSTCONDITION( "is empty", (*current).count == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_wipe_out_and_dispose
*/

void
BSTree_kv_wipe_out_and_dispose( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;

   // get array of nodes
   node_t **array = nodes_as_array( current );

   // delete nodes and values
   for ( i = 0; i < (*current).count; i++ )
   {
      KEY_DEEP_DISPOSE_FUNCTION( ( *array[i] ).key );
      VALUE_DEEP_DISPOSE_FUNCTION( ( *array[i] ).value );
      node_dispose( &array[i] );
   }

   // delete array
   free( array );

   // delete cursors, all but first
   BSTree_kv_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   BSTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
   ( *(*current).first_cursor ).next_cursor = NULL;
   (*current).last_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // set count to zero
   (*current).count = 0;

   // set root to NULL
   (*current).root = NULL;

   // set is_balanced
   (*current).is_balanced = 1;

   POSTCONDITION( "is empty", (*current).count == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   BSTree_kv_balance
*/

void
BSTree_kv_balance( Prefix )( BSTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BSTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   balance( current );

   // set is_balanced
   (*current).is_balanced = 1;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


#ifdef __cplusplus
}
#endif

/* End of file */

