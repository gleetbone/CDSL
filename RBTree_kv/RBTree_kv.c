/**
 @file RBTree_kv.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Red Black Binary Search Trees of keys with values"

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

 Function definitions for the opaque RBTree_kv_t type.

*/

#include "RBTree_kv.h"

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
#include <math.h>

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

/**
   Enumeration for red-black
*/

enum rbcolor
{
   red,
   black
};

typedef enum rbcolor rbcolor_t;

/**
   Node structure declaration
*/

struct node;

/**
   Node structure definition. Holds a value. a color, and node pointers.
*/

struct node
{
   Key key;
   Type value;
   rbcolor_t color;
   struct node *parent;
   struct node *left;
   struct node *right;
};

typedef struct node node_t;

/**
   null_node

   special node to act as sentinel for all instances of RBTree
   singleton null node - helps avoid complexity in code
*/
static int32_t null_node_initialized = 0;
static node_t null_node;

struct RBTree_kv_cursor_struct( Prefix );

/**
   Binary search tree structure definition.
*/

struct RBTree_kv_struct( Prefix )
{

   PROTOCOLS_DEFINITION;

   int32_t _type;
   int32_t _key_type;
   int32_t _item_type;

   node_t root;   // pseudo root, helps avoid complexity in code
   int32_t count;
   RBTree_kv_cursor_type( Prefix ) *first_cursor;
   RBTree_kv_cursor_type( Prefix ) *last_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure definition. Holds reference to rbtree, current node, node
   stack, and a pointer to the next cursor.
*/

struct RBTree_kv_cursor_struct( Prefix )
{
   RBTree_kv_type( Prefix ) *rbtree;
   node_t *item;
   RBTree_kv_cursor_type( Prefix ) *next_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   function prototypes
*/

static
int
height( RBTree_kv_type( Prefix ) *rbtree );

static
void
cursor_start( RBTree_kv_cursor_type( Prefix ) *cursor );

static
void
cursor_forth( RBTree_kv_cursor_type( Prefix ) *cursor );

static
int32_t
cursor_off(  RBTree_kv_cursor_type( Prefix ) *cursor );

static
Key
cursor_key( RBTree_kv_cursor_type( Prefix ) *cursor );

static
Type
cursor_item( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   black_path_count

   count black parents of node to root

   @param node the node to process
   @return the number of black nodes
*/

static
int
black_path_count( node_t *node )
{
   int32_t result = 0;
   node_t *n = NULL;

   n = node;

   while( n != &null_node )
   {
      if ( (*n).color == black )
      {
         result = result + 1;
      }
      n = (*n).parent;
   }

   return ( result - 1 );
}

/**
   height_of_node

   count number of parents of node to root

   @param node the node to process
   @return the number of ancestor nodes
*/

static
int
height_of_node( node_t *node )
{
   int32_t result = 0;
   node_t *n = NULL;

   n = node;

   while( n != &null_node )
   {
      result = result + 1;
      n = (*n).parent;
   }

   return ( result - 1 );
}

/**
   as_string_recurse

   create a string representation of the tree, recursive

   @param node the node to process
   @param astr array of strings, one string for each level of the tree
   @param tree_height the max number of nodes from root to any descendant node
   @param width the length of the string space for a node
   @param index which level is being processed
   @param func a function to convert a node's value to a string
*/

static
void
as_string_recurse
(
   node_t *node,
   char_t **astr,
   int32_t tree_height,
   int32_t width,
   int32_t index,
   void ( func )( char_t *, Key key, Type value )
)
{
   int32_t node_height = 0;
   int32_t i = 0;
   char_t *cp = NULL;

   node_height = height_of_node( node );
   i = ( int32_t ) floor( pow( 2.0, tree_height - node_height ) );
   i = width * i + 2 * width * i * index;
   cp = &( astr[ node_height - 1 ][ i ] );
   func( cp, (*node).key, (*node).value );

   if ( (*node).left != &null_node )
   {
      i = index << 1;
      as_string_recurse( (*node).left, astr, tree_height, width, i, func );
   }

   if ( (*node).right != &null_node )
   {
      i = index << 1;
      i = i | 1;
      as_string_recurse( (*node).right, astr, tree_height, width, i, func );
   }

   return;
}

/**
   RBTree_kv_as_string

   create a string representation of the tree

   @param current the tree
   @param astr array of strings, one string for each level of the tree
   @param width the length of the string space for a node
   @param func a function to convert a node's value to a string
*/

void
RBTree_kv_as_string( Prefix )
(
   RBTree_kv_type( Prefix ) *rbtree,
   char_t **astr,
   int32_t width,
   void ( func )( char_t *, Key key, Type value )
)
{
   node_t *node = NULL;
   int32_t tree_height = 0;
   int32_t index = 0;

   node = (*rbtree).root.left;
   tree_height = height( rbtree );

   as_string_recurse( node, astr, tree_height, width, index, func );

   return;
}

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
   CHECK( "node allocated_correctly", node != NULL );

   (*node).parent = &null_node;
   (*node).left = &null_node;
   (*node).right = &null_node;
   (*node).color = black;

   POSTCONDITION( "node not null", node != NULL );
   POSTCONDITION( "node parent null", (*node).parent == &null_node );
   POSTCONDITION( "node left null", (*node).left == &null_node );
   POSTCONDITION( "node right null", (*node).right == &null_node );
   POSTCONDITION( "node color black", (*node).color == black );

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
   PRECONDITION( "*node not null", *node != NULL );

   (**node).parent = NULL;
   (**node).left = NULL;
   (**node).right = NULL;
   (**node).color = 0;

   free(*node);
   *node = NULL;

   return;
}

/**
   has_recurse

   search for a node with the desired value, return 1 if found, 0 otherwise,
   recursive

   @param node the node to start from
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
   if ( (*node).left != &null_node )
   {
      result = has_recurse( (*node).left, key );
   }

   if ( result == 0 )
   {
      result = KEY_DEEP_EQUAL_FUNCTION( (*node).key, key );
   }

   if ( result == 0 )
   {
      if ( (*node).right != &null_node )
      {
         result = has_recurse( (*node).right, key );
      }
   }
   return result;
}

/**
   has

   Return 1 if rbtree has an item for key, 0 if not

   @param rbtree RBTree_kv_t instance
   @param key the key to query for
*/

static
int32_t
has( RBTree_kv_type( Prefix ) *rbtree, Key key )
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*rbtree).root.left;

   // recurse to see if can find value in tree
   if ( node != &null_node )
   {
      result = has_recurse( node, key );
   }

   return result;
}

/**
   has_eq_fn_recurse

   search for a node with the desired value using a provided equality function,
   return 1 if found, 0 otherwise, recursive

   @param node the node to start from
   @param key the key to search for
   @param equality_test_func the function to check equality of values
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
   if ( (*node).left != &null_node )
   {
      result = has_eq_fn_recurse( (*node).left, key, equality_test_func );
   }

   if ( result == 0 )
   {
      result = equality_test_func( (*node).key, key );
   }

   if ( result == 0 )
   {
      if ( (*node).right != &null_node )
      {
         result = has_eq_fn_recurse( (*node).right, key, equality_test_func );
      }
   }
   return result;
}

/**
   has_eq_fn

   search for a node with the desired value using a provided equality function,
   return 1 if found, 0 otherwise, recursive

   @param current the tree
   @param key the key to search for
   @param equality_test_func the function to check equality of values
   @return 1 if value found, 0 otherwise
*/

static
int32_t
has_eq_fn
(
   RBTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root.left;

   // recurse to see if can find value in tree
   if ( node != &null_node )
   {
      result = has_eq_fn_recurse( node, key, equality_test_func );
   }

   return result;
}

/**
   has_value_recurse

   search for a node with the desired value, return 1 if found, 0 otherwise,
   recursive

   @param node the node to start from
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
   if ( (*node).left != &null_node )
   {
      result = has_value_recurse( (*node).left, value );
   }

   if ( result == 0 )
   {
      result = VALUE_DEEP_EQUAL_FUNCTION( (*node).value, value );
   }

   if ( result == 0 )
   {
      if ( (*node).right != &null_node )
      {
         result = has_value_recurse( (*node).right, value );
      }
   }
   return result;
}

/**
   has_value

   Return 1 if rbtree has an item for value, 0 if not

   @param rbtree RBTree_kv_t instance
   @param key the value to query for
*/

static
int32_t
has_value( RBTree_kv_type( Prefix ) *rbtree, Type value )
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*rbtree).root.left;

   // recurse to see if can find value in tree
   if ( node != &null_node )
   {
      result = has_value_recurse( node, value );
   }

   return result;
}

/**
   has_value_eq_fn_recurse

   search for a node with the desired value using a provided equality function,
   return 1 if found, 0 otherwise, recursive

   @param node the node to start from
   @param value the value to search for
   @param equality_test_func the function to check equality of values
   @return 1 if value found, 0 otherwise
*/
static
int32_t
has_value_eq_fn_recurse
(
   node_t *node,
   Type value,
   int32_t ( *equality_test_func )( Type k1, Type k2 )
)
{
   int32_t result = 0;

   // in order recursion - left, self, right
   // if tested value is found, exit
   if ( (*node).left != &null_node )
   {
      result = has_value_eq_fn_recurse( (*node).left, value, equality_test_func );
   }

   if ( result == 0 )
   {
      result = equality_test_func( (*node).value, value );
   }

   if ( result == 0 )
   {
      if ( (*node).right != &null_node )
      {
         result = has_value_eq_fn_recurse( (*node).right, value, equality_test_func );
      }
   }
   return result;
}

/**
   has_value_eq_fn

   search for a node with the desired value using a provided equality function,
   return 1 if found, 0 otherwise, recursive

   @param current the tree
   @param value the value to search for
   @param equality_test_func the function to check equality of values
   @return 1 if value found, 0 otherwise
*/

static
int32_t
has_value_eq_fn
(
   RBTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type k1, Type k2 )
)
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root.left;

   // recurse to see if can find value in tree
   if ( node != &null_node )
   {
      result = has_value_eq_fn_recurse( node, value, equality_test_func );
   }

   return result;
}

/**
   occurrences_recurse

   count number of nodes with a value equal to the desired value, recusive

   @param node the node to start from
   @param key the key to search for
   @param count accumulates the number of found nodes
*/
static
void
occurrences_recurse( node_t *node, Key key, int32_t *count )
{
   // in order recursion - left, self, right
   // if tested value is found, count it
   if ( (*node).left != &null_node )
   {
      occurrences_recurse( (*node).left, key, count );
   }

   if ( KEY_DEEP_EQUAL_FUNCTION( (*node).key, key ) == 1 )
   {
      *count = *count + 1;
   }

   if ( (*node).right != &null_node )
   {
      occurrences_recurse( (*node).right, key, count );
   }

   return;
}

/**
   occurrences

   Return count of item keys in rbtree equal to value

   @param current RBTree_kv_t instance
   @param key the key to query for
   @return the count of items count
*/

static
int32_t
occurrences( RBTree_kv_type( Prefix ) *current, Key key )
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root.left;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      occurrences_recurse( node, key, &result );
   }

   return result;
}

/**
   occurrences_eq_fn_recurse

   count number of nodes with a value equal to the desired value using the
   supplied equality function, recusive

   @param node the node to start from
   @param key the key to search for
   @param count accumulates the number of found nodes
   @param equality_test_func function to compare values for equality
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
   if ( (*node).left != &null_node )
   {
      occurrences_eq_fn_recurse( (*node).left, key, count, equality_test_func );
   }

   if ( equality_test_func( (*node).key, key ) == 1 )
   {
      *count = *count + 1;
   }

   if ( (*node).right != &null_node )
   {
      occurrences_eq_fn_recurse( (*node).right, key, count, equality_test_func );
   }

   return;
}

/**
   occurrences_eq_fn

   Return count of item keys in rbtree equal to key according to equality_test_func

   @param current RBTree_kv_t instance
   @param key the key to query for
   @param equality_test_func the test function for value equality
   @return the count of items count
*/

static
int32_t
occurrences_eq_fn
(
   RBTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root.left;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      occurrences_eq_fn_recurse( node, key, &result, equality_test_func );
   }

   return result;
}

/**
   occurrences_value_recurse

   count number of nodes with a value equal to the desired value, recusive

   @param node the node to start from
   @param value the value to search for
   @param count accumulates the number of found nodes
*/
static
void
occurrences_value_recurse( node_t *node, Type value, int32_t *count )
{
   // in order recursion - left, self, right
   // if tested value is found, count it
   if ( (*node).left != &null_node )
   {
      occurrences_value_recurse( (*node).left, value, count );
   }

   if ( VALUE_DEEP_EQUAL_FUNCTION( (*node).value, value ) == 1 )
   {
      *count = *count + 1;
   }

   if ( (*node).right != &null_node )
   {
      occurrences_value_recurse( (*node).right, value, count );
   }

   return;
}

/**
   occurrences_value

   Return count of items in rbtree equal to value

   @param current RBTree_kv_t instance
   @param value the value to query for
   @return the count of items count
*/

static
int32_t
occurrences_value( RBTree_kv_type( Prefix ) *current, Type value )
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root.left;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      occurrences_value_recurse( node, value, &result );
   }

   return result;
}

/**
   occurrences_value_eq_fn_recurse

   count number of nodes with a value equal to the desired value using the
   supplied equality function, recusive

   @param node the node to start from
   @param value the value to search for
   @param count accumulates the number of found nodes
   @param equality_test_func function to compare values for equality
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
   if ( (*node).left != &null_node )
   {
      occurrences_value_eq_fn_recurse( (*node).left, value, count, equality_test_func );
   }

   if ( equality_test_func( (*node).value, value ) == 1 )
   {
      *count = *count + 1;
   }

   if ( (*node).right != &null_node )
   {
      occurrences_value_eq_fn_recurse( (*node).right, value, count, equality_test_func );
   }

   return;
}

/**
   occurrences_value_eq_fn

   Return count of items in rbtree equal to value according to equality_test_func

   @param current RBTree_kv_t instance
   @param value the value to query for
   @param equality_test_func the test function for value equality
   @return the count of items count
*/

static
int32_t
occurrences_value_eq_fn
(
   RBTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root.left;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      occurrences_value_eq_fn_recurse( node, value, &result, equality_test_func );
   }

   return result;
}

/**
   node_for_index

   return the node for the given index

   @param current the tree
   @param index the desired index
   @return the node at the desired index
*/

static
node_t *
node_for_index( RBTree_kv_type( Prefix ) *current, int32_t index )
{
   int32_t i = 0; 
   node_t *result = NULL;

   // get cursor
   RBTree_kv_cursor_type( Prefix ) *c
      =  ( RBTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );
      
   // set rbtree in cursor
   (*c).rbtree = current;

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

   return the index of the desired node

   @param current the tree
   @param node the desired node
   @return the index of the desired node
*/
static
int32_t
index_for_node( RBTree_kv_type( Prefix ) *current, node_t *node )
{
   int32_t result = 0;
   int32_t flag = 0;

   // get cursor
   RBTree_kv_cursor_type( Prefix ) *c
      =  ( RBTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );

   // set rbtree in cursor
   (*c).rbtree = current;

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

   return the node with the desired value, recursive

   @param node the starting node
   @param value the desired value
   @return the found node with the desired value
*/
static
node_t *
item_recurse( node_t *node, Key key )
{
   node_t *result = &null_node;

   if ( KEY_DEEP_EQUAL_FUNCTION( key, (*node).key ) == 1 )
   {
      result = node;
   }

   if ( result == &null_node )
   {
      if ( KEY_ORDER_FUNCTION( key, (*node).key ) == 1 )
      {

         if ( (*node).left != &null_node )
         {
            result = item_recurse( (*node).left, key );
         }
      }
   }

   if ( result == &null_node )
   {
      if ( KEY_ORDER_FUNCTION( key, (*node).key ) == 0 )
      {

         if ( (*node).right != &null_node )
         {
            result = item_recurse( (*node).right, key );
         }
      }
   }

   return result;
}

/**
   item

   Return node in rbtree that has value, NULL if none

   @param current RBTree_t instance
   @param value the desired value
   @return the found node with the desired value, NULL if not found
*/

static
node_t *
item( RBTree_kv_type( Prefix ) *rbtree, Key key )
{
   node_t *result = NULL;
   node_t *node = NULL;

   // get root node
   result = &null_node;
   node = (*rbtree).root.left;

   // recurse to see if can find value in tree
   if ( node != &null_node )
   {
      result = item_recurse( node, key );
   }

   return result;
}

/**
   node_for_key_recurse

   find the node that has the specified key, recursive

   @param node the node to start with
   @param key the desired key to search for
   @return the found node
*/
static
node_t *
node_for_key_recurse( node_t *node, Key key )
{
   node_t *result = &null_node;
   node_t *temp = &null_node;
   node_t *n = &null_node;

   if ( KEY_DEEP_EQUAL_FUNCTION( key, (*node).key ) == 1 )
   {
      result = node;
   }

   if ( result == &null_node )
   {
      if ( KEY_ORDER_FUNCTION( key, (*node).key ) == 1 )
      {

         if ( (*node).left != &null_node )
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
            while ( ( n != &null_node ) && ( (*n).left == temp ) )
            {
               temp = n;
               n = (*n).parent;
            }

            result = n;
         }
      }
   }

   if ( result == &null_node )
   {
      if ( KEY_ORDER_FUNCTION( key, (*node).key ) == 0 )
      {

         if ( (*node).right != &null_node )
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

   find the node that has the specified value, recursive

   @param node the node to start with
   @param value the desired value to search for
   @return the found node
*/
static
node_t *
node_for_value_recurse( node_t *node, Type value )
{
   node_t *result = NULL;

   // in order recursion - left, self, right
   // if tested value is found, exit
   if ( (*node).left != &null_node )
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
      if ( (*node).right != &null_node )
      {
         result = node_for_value_recurse( (*node).right, value );
      }
   }
   return result;
}

/**
   rotate_left

   perform left rotation balancing operation starting at node

   @param current the tree
   @param node the node to start with
*/
static
void
rotate_left( RBTree_kv_type( Prefix ) *rbtree, node_t *node )
{
   node_t *child = NULL;

   // adjust tree so that node and child exchange levels and side
   // node goes to left

   if ( (*node).right != &null_node )
   {
      child = (*node).right;
      (*node).right = (*child).left;

      if ( (*child).left != &null_node )
      {
         ( *(*child).left ).parent = node;
      }

      (*child).parent = (*node).parent;

      if ( node == ( *(*node).parent ).left )
      {
         ( *(*node).parent ).left = child;
      }
      else
      {
         ( *(*node).parent ).right = child;
      }

      (*child).left = node;
      (*node).parent = child;
   }

   return;
}

/**
   rotate_right

   perform right rotation balancing operation starting at node

   @param current the tree
   @param node the node to start with
*/
static void
rotate_right( RBTree_kv_type( Prefix ) *rbtree, node_t *node )
{
   node_t *child = NULL;

   // adjust tree so that node and child exchange levels and side
   // node goes to right

   if ( (*node).left != &null_node )
   {
      child = (*node).left;
      (*node).left = (*child).right;

      if ( (*child).right != &null_node )
      {
         ( *(*child).right ).parent = node;
      }

      (*child).parent = (*node).parent;

      if ( node == ( *(*node).parent ).left )
      {
         ( *(*node).parent ).left = child;
      }
      else
      {
         ( *(*node).parent ).right = child;
      }

      (*child).right = node;
      (*node).parent = child;
   }

   return;
}

/**
   sibling_of

   find sibling of node, if it exists

   @param node the node to analyze
   @return the found sibling node
*/
static
node_t *
sibling_of( node_t *node )
{
   node_t *result = NULL;

   if ( (*node).parent != &null_node )
   {
      if ( node == ( *(*node).parent ).left )
      {
         result = ( *(*node).parent ).right;
      }
      else
      {
         result = ( *(*node).parent ).left;
      }
   }

   return result;
}

/**
  repair_put

  reblance the tree after a put operation

  @param current the tree
  @param node the node that was altered
*/

static
void
repair_put( RBTree_kv_type( Prefix ) *rbtree, node_t *node )
{
   node_t *n = NULL;

   n = node;

   // color the node red
   if ( n != &null_node )
   {
      (*n).color = red;
   }

   // correct double red issues, if they exist
   if (
      ( n != &null_node )
      &&
      ( n != (*rbtree).root.left )
      &&
      ( ( *(*n).parent ).color == red )
   )
   {

      // recolor up if more work needed
      if ( ( * sibling_of( (*n).parent ) ).color == red )
      {
         ( *(*n).parent ).color = black;
         ( * sibling_of( (*n).parent ) ).color = black;
         if ( ( *(*n).parent ).parent != &null_node )
         {
            ( *( *(*n).parent ).parent ).color = red;
            repair_put( rbtree, ( *(*n).parent ).parent );
         }
      }

      // restructure for a parent who is the left child of the
      // grandparent. requires a single right rotation if n is
      // also a left child, or a left-right rotation otherwise
      else if ( (*n).parent == ( *( *(*n).parent ).parent ).left  )
      {
         if ( n == ( *(*n).parent ).right )
         {
            n = (*n).parent;
            rotate_left( rbtree, n );
         }
         ( *(*n).parent ).color = black ;
         if ( ( *(*n).parent ).parent != &null_node )
         {
            ( *( *(*n).parent ).parent ).color = red;
            rotate_right( rbtree, ( *(*n).parent ).parent );
         }
      }

      // restructure for a parent who is the right child of the
      // grandparent. requires a single left rotation if n is
      // also a right child, or a right-left rotation otherwise
      else if ( (*n).parent == ( *( *(*n).parent ).parent ).right )
      {
         if ( n == ( *(*n).parent ).left  )
         {
            n = (*n).parent;
            rotate_right( rbtree, n );
         }
         ( *(*n).parent ).color = black;
         if ( ( *(*n).parent ).parent != &null_node )
         {
            ( *( *(*n).parent ).parent ).color = red;
            rotate_left( rbtree, ( *(*n).parent ).parent );
         }
      }
   }

   // color the root black
   ( *(*rbtree).root.left ).color = black;

   return;
}

/**
   put

   put a new node into the tree with the specified value

   @param current the tree
   @param value the value to put in the tree
*/

static
void
put( RBTree_kv_type( Prefix ) *rbtree, Type value, Key key )
{
   node_t *node = NULL;
   node_t *parent = NULL;
   int32_t result = 0;

   // start at root of tree
   node = (*rbtree).root.left;
   parent = &(*rbtree).root;

   // find insertion point
   while( node != &null_node )
   {
      parent = node;
      result = KEY_ORDER_FUNCTION( key, (*node).key );
      if ( result == 1 )
      {
         node = (*node).left;
      }
      else
      {
         node = (*node).right;
      }
   }

   // make node to be inserted
   node = node_make();

   // set its members
   (*node).key = key;
   (*node).value = value;
   (*node).left = &null_node;
   (*node).right = &null_node;
   (*node).parent = parent;
   (*node).color = red;

   // adjust its parent node
   if (
      ( parent == &(*rbtree).root )
      ||
      ( KEY_ORDER_FUNCTION( (*node).key, (*parent).key ) == 1 )
   )
   {
      (*parent).left = node;
      repair_put( rbtree, node );
   }
   else
   {
      (*parent).right = node;
      repair_put( rbtree, node );
   }

   // ensure tree root is black
   ( *(*rbtree).root.left ).color = black;

   // increment count
   (*rbtree).count = (*rbtree).count + 1;

   return;
}

/**
   keys_as_array_recurse

   construct an in-order array of keys from the tree, recursive

   @param node the node to start with
   @param array the array of values to fill
   @param index the index of the array to for the node
*/
static
void
keys_as_array_recurse( node_t *node, Key *array, int32_t *index )
{
   // if has left child, recurse
   if ( (*node).left != &null_node )
   {
      keys_as_array_recurse( (*node).left, array, index );
   }

   // handle this node
   array[ *index ] = (*node).key;
   *index = *index + 1;

   // if has right child, recurse
   if ( (*node).right != &null_node )
   {
      keys_as_array_recurse( (*node).right, array, index );
   }

   return;
}

/**
   keys_as_array

   construct an in-order array of keys from the tree

   @param current the tree
   @return the array of keys
*/

static
Type *
keys_as_array( RBTree_kv_type( Prefix ) *rbtree )
{
   Key *result = NULL;
   int32_t index = 0;

   result = ( Key * ) calloc( (*rbtree).count + 1, sizeof( Key ) );
   CHECK( "result allocated correctly", result != NULL );

   if ( (*rbtree).root.left != &null_node )
   {
      keys_as_array_recurse( (*rbtree).root.left, result, &index );
   }

   return result;
}

/**
   values_as_array_recurse

   construct an in-order array of keys from the tree, recursive

   @param node the node to start with
   @param array the array of values to fill
   @param index the index of the array to for the node
*/
static
void
values_as_array_recurse( node_t *node, Type *array, int32_t *index )
{
   // if has left child, recurse
   if ( (*node).left != &null_node )
   {
      values_as_array_recurse( (*node).left, array, index );
   }

   // handle this node
   array[ *index ] = (*node).value;
   *index = *index + 1;

   // if has right child, recurse
   if ( (*node).right != &null_node )
   {
      values_as_array_recurse( (*node).right, array, index );
   }

   return;
}

/**
   values_as_array

   construct an in-order array of keys from the tree

   @param current the tree
   @return the array of keys
*/

static
Type *
values_as_array( RBTree_kv_type( Prefix ) *rbtree )
{
   Type *result = NULL;
   int32_t index = 0;

   result = ( Type * ) calloc( (*rbtree).count + 1, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   if ( (*rbtree).root.left != &null_node )
   {
      values_as_array_recurse( (*rbtree).root.left, result, &index );
   }

   return result;
}

/**
   nodes_as_array_recurse

   construct an in-order array of nodes from the tree, recursive

   @param node the node to start with
   @param array the array of nodes to fill
   @param index the index of the array to for the node
*/
static
void
nodes_as_array_recurse( node_t *node, node_t **array, int32_t *index )
{
   // if has left child, recurse
   if ( (*node).left != &null_node )
   {
      nodes_as_array_recurse( (*node).left, array, index );
   }

   // handle this node
   array[ *index ] = node;
   *index = *index + 1;

   // if has right child, recurse
   if ( (*node).right != &null_node )
   {
      nodes_as_array_recurse( (*node).right, array, index );
   }

   return;
}

/**
   nodes_as_array

   construct an in-order array of nodes from the tree

   @param current the tree
   @return array of nodes in order
*/

static
node_t **
nodes_as_array( RBTree_kv_type( Prefix ) *rbtree )
{
   node_t **result = NULL;
   int32_t index = 0;

   result = ( node_t ** ) calloc( (*rbtree).count + 1, sizeof( node_t ) );
   CHECK( "result allocated correctly", result != NULL );

   if ( (*rbtree).root.left != &null_node )
   {
      nodes_as_array_recurse( (*rbtree).root.left, result, &index );
   }

   return result;
}

/**
   repair_remove

   repair the tree after a node has been deleted by rotating and repainting
   colors to restore the red-black tree's properties

   @param current the tree
   @param node the node that was affected by the (previous) removal
 */
static
void
repair_remove( RBTree_kv_type( Prefix ) *rbtree, node_t *node )
{
   node_t *n = NULL;
   node_t *sibling = NULL;

   n = node;

   // while node is not tree root and is black
   while ( ( n != (*rbtree).root.left ) && ( (*n).color == black ) )
   {
      if ( n == ( *(*n).parent ).left )
      {
         // Pulled up node is a left child
         sibling = ( *(*n).parent ).right;
         if ( (*sibling).color == red )
         {
            if ( sibling != &null_node )
            {
               (*sibling).color = black;
            }
            ( *(*n).parent ).color = red;
            rotate_left( rbtree, (*n).parent );
            sibling = ( *(*n).parent ).right;
         }

         if ( ( ( *(*sibling).left ).color == black ) && ( ( *(*sibling).right ).color == black ) )
         {
            if ( sibling != &null_node )
            {
               (*sibling).color = red;
            }
            n = (*n).parent;
         }
         else
         {
            if ( ( *(*sibling).right ).color == black )
            {
               ( *(*sibling).left ).color = black;
               (*sibling).color = red;
               rotate_right( rbtree, sibling );
               sibling = ( *(*n).parent ).right;
            }

            (*sibling).color = ( *(*n).parent ).color;
            ( *(*n).parent ).color = black;
            ( *(*sibling).right ).color = black;
            rotate_left( rbtree, (*n).parent );
            n = (*rbtree).root.left;
         }
      }
      else
      {
         // pulled up node is a right child
         sibling = ( *(*n).parent ).left;
         if ( (*sibling).color == red )
         {
            (*sibling).color = black ;
            ( *(*n).parent ).color = red;
            rotate_right( rbtree, (*n).parent );
            sibling = ( *(*n).parent ).left;
         }

         if ( ( ( *(*sibling).left ).color == black ) && ( ( *(*sibling).right ).color == black ) )
         {
            if ( sibling != &null_node )
            {
               (*sibling).color = red;
            }
            n = (*n).parent;
         }
         else
         {
            if ( ( *(*sibling).left ).color == black )
            {
               ( *(*sibling).right ).color = black;
               (*sibling).color = red;
               rotate_left( rbtree, sibling );
               sibling = ( *(*n).parent ).left;
            }

            (*sibling).color = ( *(*n).parent ).color;
            ( *(*n).parent ).color = black;
            ( *(*sibling).left ).color = black;
            rotate_right( rbtree, (*n).parent );
            n = (*rbtree).root.left;
         }
      }
   }

   (*n).color = black;

   return;
}

#undef PREDECESSOR_GENERAL_CASE

/**
   predecessor

   returns the node before node, or nil if none.

   @param current the tree
   @param node the node to start with
   @return the predecessor node, or null_node if none
*/
static
node_t *
predecessor( RBTree_kv_type( Prefix ) *rbtree, node_t *node )
{
   node_t *result = NULL;

   result = (*node).left;

   // get leftmost node from starting node's right child
   if ( result != &null_node )
   {
      while ( (*result).right != &null_node )
      {
         result = (*result).right;
      }
   }


   // in this file, the only time predecessor() is called occurs when "node"
   // is guaranteed to have a left child, so the following code would never
   // be executed. that's why it's commented out.
#ifdef PREDECESSOR_GENERAL_CASE

   else // node has no left child, move up until we find it or hit the root
   {

      node_t *n = NULL;

      result = (*node).parent;

      n = node;

      // walk up the tree looking for right child
      while( n == (*result).left )
      {
         n = result;
         result = (*result).parent;
      }

      // if we stopped at the pseudo root, return null
      if ( result == &(*rbtree).root )
      {
         result = &null_node;
      }

   }
#endif // PREDECESSOR_GENERAL_CASE


   return( result );
}


static
void
cursor_forth( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   remove

   remove a node from the tree

   @param current the tree
   @param node the node to remove
   @return the removed node to be disposed of in the calling routine
*/
static
node_t *
remove( RBTree_kv_type( Prefix ) *current, node_t *node )
{
   node_t *pre = NULL;
   node_t *pull_up = NULL;
   Key k;
   Type v;
   RBTree_kv_cursor_type( Prefix ) *cursor = NULL;

   // if node is not null, continue
   if ( node != &null_node )
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

      // if node has two children, find predecessor, swap pre's data into node
      // and set node to pre
      if ( ( (*node).left != &null_node ) && ( (*node).right != &null_node ) )
      {
         pre = predecessor( current, node );
         v = (*node).value;
         k = (*node).key;
         (*node).value = (*pre).value;
         (*node).key = (*pre).key;
         (*pre).value = v;
         (*pre).key = k;
         node = pre;
      }

      // get the pull_up node
      if ( (*node).left != &null_node )
      {
         pull_up = (*node).left;
      }
      else
      {
         pull_up = (*node).right;
      }


      // node has zero or one child
      if ( pull_up != &null_node )
      {
         // eliminate node from tree, adjust if pull_up is double black

         if ( node == (*current).root.left )
         {
            // eliminate tree root
            (*current).root.left = pull_up;
            ( *pull_up ).parent = &( (*current).root );
         }
         else if ( ( *(*node).parent ).left == node )
         {
            // eliminate node parent's left
            ( *(*node).parent ).left = pull_up;
            ( *pull_up ).parent = (*node).parent;
         }
         else
         {
            // eliminate node parent's right
            ( *(*node).parent ).right = pull_up;
            ( *pull_up ).parent = (*node).parent;
         }

         if ( (*node).color == black )
         {
            repair_remove( current, pull_up );
         }
      }
      else if ( node == (*current).root.left )
      {
         // eliminate root, tree is not empty
         (*current).root.left = &null_node;
      }
      else
      {
         // if node is black, repair tree
         if ( (*node).color == black )
         {
            repair_remove( current, node );
         }

         // eliminate the node from the tree
         if ( (*node).parent != &null_node )
         {
            if ( ( *(*node).parent ).left == node )
            {
               ( *(*node).parent ).left = &null_node;
            }
            else if ( ( *(*node).parent ).right == node )
            {
               ( *(*node).parent ).right = &null_node;
            }
            (*node).parent = &null_node;
         }
      }

      // decrement count
      (*current).count = (*current).count - 1;
   }

   // node is disposed in calling routine
   return node;
}

/**
   height_recurse

   determine the height of the tree, recursive

   @param node the current node being analyzed
   @return the count so far
*/
static
int
height_recurse( node_t *node )
{
   int32_t result = 0;
   int32_t left_height = 0;
   int32_t right_height = 0;

   if ( node == &null_node )
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

   determine the height of the tree

   @param current the tree
   @return the height
*/
static
int
height( RBTree_kv_type( Prefix ) *rbtree )
{
   int32_t result = 0;

   result = height_recurse( (*rbtree).root.left );

   return result;
}

/**
   count_recurse

   count the number of nodes in the tree, recursive

   @param node the node being analyzed
   @return the height so far
*/
static
int
count_recurse( node_t *node )
{
   int32_t result = 0;
   int32_t left_count = 0;
   int32_t right_count = 0;

   if ( node == &null_node )
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

   count the number of nodes in the tree

   @param current the tree
   @return the height
*/
static
int
count( RBTree_kv_type( Prefix ) *rbtree )
{
   int32_t result = 0;

   result = count_recurse( (*rbtree).root.left );

   return result;
}

/**
   recursion for rbtree_kv cursor functions - start, item, forth, off

   The following routines depend on the fact that the rbtree_kv
   is (already) in order and that the forth recursion keeps track
   of the last seen ( the previous ) node (in the cursor structure).
*/

/**
   cursor_finish
*/
static
void
cursor_finish( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;

   // set node from the rbtree root
   node = ( *(*cursor).rbtree ).root.left;

   if ( node != NULL )
   {
      // walk to the rightmost node from the tree root
      while ( (*node).right != &null_node )
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
cursor_start( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;

   // set node from the rbtree root
   node = ( *(*cursor).rbtree ).root.left;

   if ( node != NULL )
   {
      // walk to the leftmost node from the tree root
      while ( (*node).left != &null_node )
      {
         node = (*node).left;
      }
   }

   // set data items in the cursor
   (*cursor).item = node;

   return;
}

/**
   cursor_key
*/
static
Key
cursor_key( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   // return the key for the current cursor item
   return ( *(*cursor).item ).key;
}

/**
   cursor_item
*/
static
Type
cursor_item( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   // return the value for the current cursor item
   return ( *(*cursor).item ).value;
}


/**
   cursor_back
*/
static
void
cursor_back( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;
   node_t *temp = NULL;

   // go to next item in sequence ( or off )
   if ( (*cursor).item != &null_node )
   {
      node = (*cursor).item;

      // if the node's left child is not null
      if ( (*node).left != &null_node )
      {
         // find the rightmost child of the node's left child
         node = (*node).left;
         while ( (*node).right != &null_node )
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
         while ( ( node != &null_node ) && ( (*node).left == temp ) )
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
cursor_forth( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;
   node_t *temp = NULL;

   // go to next item in sequence ( or off )
   if ( (*cursor).item != &null_node )
   {
      node = (*cursor).item;

      // if node's right child is not null
      if ( (*node).right != &null_node )
      {
         // get leftmost child of node's right child
         node = (*node).right;
         while ( (*node).left != &null_node )
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
         while ( ( node != &null_node ) && ( (*node).right == temp ) )
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
cursor_off(  RBTree_kv_cursor_type( Prefix ) *cursor )
{
   int32_t result = 0;

   // off is cursor item is null_node or root
   if (
      ( (*cursor).item == &( *(*cursor).rbtree ).root )
      ||
      ( (*cursor).item == &null_node )
   )
   {
      result = 1;
   }

   return result;
}

/**
   move_all_cursors_off
*/
static
void
move_all_cursors_off( RBTree_kv_type( Prefix ) *current )
{
   RBTree_kv_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   while( cursor != NULL )
   {
      // set cursor item to &null_node == off
      (*cursor).item = &null_node;

      cursor = (*cursor).next_cursor;
   }

   return;
}

/**
   compare tree items to array items

   see if the values in the nodes of the tree are equal to the values in an
   array of values

   @param current the tree
   @param keys the array of keys
   @param values the array of values
   @param array_count the number of values in the array
   @return 1 if values are equal, 0 otherwise
*/

static
int32_t
compare_tree_items_to_array_items( RBTree_kv_type
                                   (
                                      Prefix ) *current,
                                   Key *keys,
                                   Type *values,
                                   int32_t array_count
                                 )
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

   see if the values in one tree are equal to the values in an other tree

   @param current the tree
   @param other the other tree
   @return 1 if values are equal, 0 otherwise
*/

static
int32_t
compare_tree_items_to_tree_items
(
   RBTree_kv_type( Prefix ) *current,
   RBTree_kv_type( Prefix ) *other
)
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t count = 0;
   RBTree_kv_cursor_type( Prefix ) *c1
      =  ( RBTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c1 allocated correctly", c1 != NULL );
         
   RBTree_kv_cursor_type( Prefix ) *c2
      =  ( RBTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c2 allocated correctly", c2 != NULL );

   // set rbtree in cursors
   (*c1).rbtree = current;
   (*c2).rbtree = other;

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
            ( cursor_key( c1 ) == cursor_key( c2 ) )
            &&
            ( cursor_item( c1 ) == cursor_item( c2 ) )
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

   see if the values in one tree are equal to the values in an other tree using
   a deep equal comparison

   @param current the tree
   @param other the other tree
   @return 1 if values are equal, 0 otherwise
*/

static
int32_t
compare_tree_items_to_tree_items_deep_equal
(
   RBTree_kv_type( Prefix ) *current,
   RBTree_kv_type( Prefix ) *other
)
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t count = 0;
   RBTree_kv_cursor_type( Prefix ) *c1
      =  ( RBTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c1 allocated correctly", c1 != NULL );
         
   RBTree_kv_cursor_type( Prefix ) *c2
      =  ( RBTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c2 allocated correctly", c2 != NULL );
        
   // set rbtree in cursors
   (*c1).rbtree = current;
   (*c2).rbtree = other;

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
            ( KEY_DEEP_EQUAL_FUNCTION( cursor_key( c1 ), cursor_key( c2 ) ) == 1 )
            &&
            ( VALUE_DEEP_EQUAL_FUNCTION( cursor_item( c1 ), cursor_item( c2 ) ) == 1 )
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
is_empty_implies_root_null( RBTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).count == 0 )
   {
      result = ( (*p).root.left == &null_node );
   }

   return result;
}

static
int32_t
nonnegative_count( RBTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
valid_count( RBTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( count( p ) == (*p).count );

   return result;
}

static
int32_t
first_cursor_not_null( RBTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).first_cursor != NULL );

   return result;
}

static
int32_t
cursors_rbtree_ok( RBTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   RBTree_kv_cursor_type( Prefix ) *cursor = (*p).first_cursor;

   while( ( cursor != NULL ) && ( result == 1 ) )
   {
      result = ( (*cursor).rbtree == p );
      cursor = (*cursor).next_cursor;
   }

   return result;
}

static
int32_t
last_cursor_null_if_one_cursor( RBTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( ( *(*p).first_cursor ).next_cursor == NULL )
   {
      result = ( (*p).last_cursor == NULL );
   }

   return result;
}

static
int32_t
last_cursor_next_null( RBTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).last_cursor != NULL )
   {
      result = ( ( *(*p).last_cursor ).next_cursor == NULL );
   }

   return result;
}

static
int32_t
in_order_recurse( node_t *node )
{
   int32_t result = 1;

   if ( (*node).left != &null_node )
   {
      result = KEY_ORDER_FUNCTION( ( *(*node).left ).key, (*node).key );
   }

   if ( result == 1 )
   {
      if ( (*node).right != &null_node )
      {
         result = KEY_ORDER_FUNCTION( (*node).key, ( *(*node).right ).key );
      }
   }

   if ( result == 1 )
   {
      if ( (*node).left != &null_node )
      {
         result = in_order_recurse( (*node).left );
      }
   }

   if ( result == 1 )
   {
      if ( (*node).right != &null_node )
      {
         result = in_order_recurse( (*node).right );
      }
   }

   return result;
}

static
int32_t
in_order( RBTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).count > 1 )
   {
      result = in_order_recurse( (*p).root.left );
   }

   return result;
}

static
int32_t
root_is_black( RBTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).root.left != &null_node )
   {
      result = ( ( *(*p).root.left ).color == black );
   }

   return result;
}

static
int32_t
node_colors_ok_recurse( node_t *node )
{
   int32_t result = 1;

   if ( (*node).color == red )
   {
      if ( (*node).left != &null_node )
      {
         result = ( ( *(*node).left ).color == black );
      }
      if ( result == 1 )
      {
         if ( (*node).right != &null_node )
         {
            result = ( ( *(*node).right ).color == black );
         }
      }
   }

   if ( ( result == 1 ) && ( (*node).left != &null_node ) )
   {
      result = node_colors_ok_recurse( (*node).left );
   }

   if ( ( result == 1 ) && ( (*node).right != &null_node ) )
   {
      result = node_colors_ok_recurse( (*node).right );
   }

   return result;
}

static
int32_t
node_colors_ok( RBTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).root.left != &null_node )
   {
      result = node_colors_ok_recurse( (*p).root.left );
   }

   return result;
}

static
int32_t
path_black_count_ok_recurse( node_t *node, int32_t *the_count )
{
   int32_t result = 1;
   int32_t count = 0;

   if ( (*node).left == &null_node )
   {
      count = black_path_count( node );
      if ( *the_count == 0 )
      {
         *the_count = count;
      }
      result = ( count == *the_count );
   }
   else if ( (*node).right == &null_node )
   {
      count = black_path_count( node );
      if ( *the_count == 0 )
      {
         *the_count = count;
      }
      result = ( count == *the_count );
   }

   if ( ( result == 1 ) && ( (*node).left != &null_node ) )
   {
      result = path_black_count_ok_recurse( (*node).left, the_count );
   }

   if ( ( result == 1 ) && ( (*node).right != &null_node ) )
   {
      result = path_black_count_ok_recurse( (*node).right, the_count );
   }

   return result;
}

static
int32_t
path_black_count_ok( RBTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;
   int32_t count = 0;

   if ( (*p).root.left != &null_node )
   {
      result = path_black_count_ok_recurse( (*p).root.left, &count );
   }

   return result;
}

static
int32_t
null_node_ok( RBTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( null_node.left == &null_node );

   if ( result == 1 )
   {
      result = ( null_node.right == &null_node );
   }

   if ( result == 1 )
   {
      result = ( null_node.parent == &null_node );
   }

   if ( result == 1 )
   {
      result = ( null_node.color == black );
   }

   return result;
}

/**
   cursors_off_or_valid
*/

static
int32_t
cursors_off_or_valid( RBTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;
   RBTree_kv_cursor_type( Prefix ) *cursor = NULL;

   // get cursor
   RBTree_kv_cursor_type( Prefix ) *c
      =  ( RBTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );

   // set rbtree in cursor
   (*c).rbtree = current;

   // loop through cursors
   cursor = (*current).first_cursor;

   // loop: if a cursor is not off and its item is not in tree, return 0
   while( ( cursor != NULL ) && ( result == 1 ) )
   {
      if ( cursor_off( cursor ) == 1 )
      {
         cursor = (*cursor).next_cursor;
         continue;
      }

      // iterate c to find item
      cursor_start( c );
      result = 0;

      while( cursor_off( c ) == 0 )
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

   if ( (*node).left != &null_node )
   {
      result = ( ( *(*node).left ).parent == node );
   }

   if ( result == 1 )
   {
      if ( (*node).right != &null_node )
      {
         result = ( ( *(*node).right ).parent == node );
      }
   }

   if ( result == 1 )
   {
      if ( (*node).left != &null_node )
      {
         result = node_pointers_consistent_recurse( (*node).left );
      }
   }

   if ( result == 1 )
   {
      if ( (*node).right != &null_node )
      {
         result = node_pointers_consistent_recurse( (*node).right );
      }
   }

   return result;
}

static
int32_t
node_pointers_consistent( RBTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).count > 1 )
   {
      result = node_pointers_consistent_recurse( (*current).root.left );
   }

   return result;
}

static
void invariant( RBTree_kv_type( Prefix ) *current )
{
   assert( ( ( void ) "empty implies root null", is_empty_implies_root_null( current ) ) );
   assert( ( ( void ) "nonnegative count", nonnegative_count( current ) ) );
   assert( ( ( void ) "valid count", valid_count( current ) ) );
   assert( ( ( void ) "first cursor not null", first_cursor_not_null( current ) ) );
   assert( ( ( void ) "last cursor next null", last_cursor_next_null( current ) ) );
   assert( ( ( void ) "last cursor null if one cursor", last_cursor_null_if_one_cursor( current ) ) );
   assert( ( ( void ) "cursors rbtree OK", cursors_rbtree_ok( current ) ) );
   assert( ( ( void ) "rbtree in order", in_order( current ) ) );
   assert( ( ( void ) "root is black", root_is_black( current ) ) );
   assert( ( ( void ) "node colors ok", node_colors_ok( current ) ) );
   assert( ( ( void ) "path black count ok", path_black_count_ok( current ) ) );
   assert( ( ( void ) "null node ok", null_node_ok( current ) ) );
   assert( ( ( void ) "cursors off or valid", cursors_off_or_valid( current ) ) );
   assert( ( ( void ) "node pointers consistent", node_pointers_consistent( current ) ) );
   return;
}

#endif


/**
   Protocol stuff
*/

#ifdef PROTOCOLS_ENABLED

/**
   indexable protocol function array
*/

/**
   basic protocol function array
*/

static
void *
p_basic_table[P_BASIC_FUNCTION_COUNT]
=
{
   RBTree_kv_dispose( Prefix ),
   RBTree_kv_deep_dispose( Prefix ),
   RBTree_kv_is_equal( Prefix ),
   RBTree_kv_is_deep_equal( Prefix ),
   RBTree_kv_copy( Prefix ),
   RBTree_kv_deep_copy( Prefix ),
   RBTree_kv_clone( Prefix ),
   RBTree_kv_deep_clone( Prefix )
};

static
void *
p_iterable_kv_table[P_ITERABLE_KV_FUNCTION_COUNT]
=
{
   RBTree_kv_count( Prefix ),
   RBTree_kv_key_at( Prefix ),
   RBTree_kv_item_at( Prefix ),
   RBTree_kv_off( Prefix ),
   RBTree_kv_is_empty( Prefix ),
   RBTree_kv_start( Prefix ),
   RBTree_kv_forth( Prefix )
};

static
void *
p_diterable_kv_table[P_DITERABLE_KV_FUNCTION_COUNT]
=
{
   RBTree_kv_count( Prefix ),
   RBTree_kv_key_at( Prefix ),
   RBTree_kv_item_at( Prefix ),
   RBTree_kv_off( Prefix ),
   RBTree_kv_is_empty( Prefix ),
   RBTree_kv_start( Prefix ),
   RBTree_kv_forth( Prefix ),
   RBTree_kv_finish( Prefix ),
   RBTree_kv_back( Prefix )
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
   RBTree_kv_make
*/

RBTree_kv_type( Prefix ) *
RBTree_kv_make( Prefix )( void )
{
   // allocate rbtree struct
   RBTree_kv_type( Prefix ) * result
      = ( RBTree_kv_type( Prefix ) * ) calloc( 1, sizeof( RBTree_kv_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );
      
   // initialize protocol functions if protocols enabled

   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = RBTREE_KV_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   // set null node - self referencing
   if ( null_node_initialized == 0 )
   {
      null_node.left = &null_node;
      null_node.right = &null_node;
      null_node.parent = &null_node;
      null_node.color = black;
      null_node_initialized = 1;
   }

   // set pseudo root node
   (*result).root.left = &null_node;
   (*result).root.right = &null_node;
   (*result).root.parent = &null_node;
   (*result).root.color = black;

   // count is zero
   (*result).count = 0;

   // set built-in cursor
   // allocate cursor struct
   RBTree_kv_cursor_type( Prefix ) *cursor
      =  ( RBTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_kv_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set rbtree
   (*cursor).rbtree = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = &null_node;

   // set rbtree built-in cursor
   (*result).first_cursor = cursor;

   // init mutex
   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new result is empty", (*result).count == 0 );
   POSTCONDITION( "new result cursor is off", ( *(*result).first_cursor ).item == &null_node );

   INVARIANT( result );

   return result;
}

/**
   RBTree_kv_make_from_array
*/

RBTree_kv_type( Prefix ) *
RBTree_kv_make_from_array( Prefix )( Key *key_array, Type *value_array, int32_t count )
{
   PRECONDITION( "key_array not null", key_array != NULL );
   PRECONDITION( "value_array not null", value_array != NULL );
   PRECONDITION( "count ok", count >= 0 );

   // make rbtree struct
   RBTree_kv_type( Prefix ) *result = RBTree_kv_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = RBTREE_KV_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   int32_t i = 0;

   for ( i = 0; i < count; i++ )
   {
      put( result, value_array[i], key_array[i] );
   }

   POSTCONDITION( "new result cursor is off", ( *(*result).first_cursor ).item == &null_node );
   POSTCONDITION( "new result contains elements of array", compare_tree_items_to_array_items( result, key_array, value_array, count ) );

   INVARIANT( result );

   return result;
}

/**
   RBTree_kv_clone
*/

RBTree_kv_type( Prefix ) *
RBTree_kv_clone( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );

   // make current struct
   RBTree_kv_type( Prefix ) *result = RBTree_kv_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = RBTREE_KV_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   // copy from current
   RBTree_kv_cursor_type( Prefix ) *cursor = RBTree_kv_cursor_make( Prefix )( current );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, cursor_item( cursor ), cursor_key( cursor ) );
      cursor_forth( cursor );
   }

   POSTCONDITION( "new tree cursor is off", ( *(*result).first_cursor ).item == &null_node );
   POSTCONDITION( "new tree contains elements of current", compare_tree_items_to_tree_items( result, current ) );

   INVARIANT( result );

   return result;
}

/**
   RBTree_kv_deep_clone
*/

RBTree_kv_type( Prefix ) *
RBTree_kv_deep_clone( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );

   // make current struct
   RBTree_kv_type( Prefix ) *result = RBTree_kv_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = RBTREE_KV_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   // copy from current
   RBTree_kv_cursor_type( Prefix ) *cursor = RBTree_kv_cursor_make( Prefix )( current );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, VALUE_DEEP_CLONE_FUNCTION( cursor_item( cursor ) ), KEY_DEEP_CLONE_FUNCTION( cursor_key( cursor ) ) );
      cursor_forth( cursor );
   }

   POSTCONDITION( "new tree cursor is off", ( *(*result).first_cursor ).item == &null_node );
   POSTCONDITION( "new tree contains elements of current", compare_tree_items_to_tree_items_deep_equal( result, current ) );

   INVARIANT( result );

   return result;
}

/**
   RBTree_kv_is_equal
*/

int32_t
RBTree_kv_is_equal( Prefix )( RBTree_kv_type( Prefix ) *current, RBTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == RBTREE_KV_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t result = 0;

   // lock other
   LOCK( (*other).mutex );

   result = compare_tree_items_to_tree_items( current, other );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return result;
}

/**
   RBTree_kv_is_deep_equal
*/

int32_t
RBTree_kv_is_deep_equal( Prefix )( RBTree_kv_type( Prefix ) *current, RBTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == RBTREE_KV_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t result = 0;

   // lock other
   LOCK( (*other).mutex );

   result = compare_tree_items_to_tree_items_deep_equal( current, other );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return result;
}

/**
   RBTree_kv_copy
*/

void
RBTree_kv_copy( Prefix )( RBTree_kv_type( Prefix ) *current, RBTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == RBTREE_KV_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t i = 0;
   RBTree_kv_cursor_type( Prefix ) *c
      =  ( RBTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );
         
   (*c).rbtree = other;

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

   // set root to NULL
   (*current).root.left = &null_node;

   cursor_start( c );

   while ( cursor_off( c ) == 0 )
   {
      put( current, cursor_item( c ), cursor_key( c ) );
      cursor_forth( c );
   }

   // free c
   free( c );

   POSTCONDITION( "new rbtree contains elements of other", compare_tree_items_to_tree_items( current, other ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return;
}

/**
   RBTree_kv_deep_copy
*/

void
RBTree_kv_deep_copy( Prefix )( RBTree_kv_type( Prefix ) *current, RBTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == RBTREE_KV_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t i = 0;
   Key k;
   Type v;
   RBTree_kv_cursor_type( Prefix ) *c
      =  ( RBTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );
         
   (*c).rbtree = other;

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

   // set root to NULL
   (*current).root.left = &null_node;

   cursor_start( c );

   while ( cursor_off( c ) == 0 )
   {
      k = KEY_DEEP_CLONE_FUNCTION( cursor_key( c ) );
      v = VALUE_DEEP_CLONE_FUNCTION( cursor_item( c ) );
      put( current, v, k );
      cursor_forth( c );
   }

   // free cursor
   free( c );

   POSTCONDITION( "new rbtree contains elements of other", compare_tree_items_to_tree_items_deep_equal( current, other ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return;
}

/**
   RBTree_kv_cursor_make
*/

RBTree_kv_cursor_type( Prefix ) *
RBTree_kv_cursor_make( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // allocate cursor struct
   RBTree_kv_cursor_type( Prefix ) *cursor
      =  ( RBTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_kv_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set rbtree
   (*cursor).rbtree = current;

   // set item to NULL - cursor is "off"
   (*cursor).item = &null_node;

   // place cursor reference into rbtree structure
   if ( (*current).last_cursor == NULL )
   {
      // set second cursor for rbtree
      ( *(*current).first_cursor ).next_cursor = cursor;
      (*current).last_cursor = cursor;
   }
   else
   {
      // set additional cursor for rbtree
      // last_cursor holds last cursor allocated
      ( *(*current).last_cursor ).next_cursor = cursor;
      (*current).last_cursor = cursor;
   }

   // init mutex
   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );
   POSTCONDITION( "new cursor is last cursor", (*current).last_cursor == cursor );
   UNLOCK( (*current).mutex );

   return cursor;
}

/**
   RBTree_kv_dispose
*/

void
RBTree_kv_dispose( Prefix )( RBTree_kv_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == RBTREE_KV_TYPE ) && ( (**current)._key_type = Key_Code ) && ( (**current)._item_type = Type_Code ) );
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
   RBTree_kv_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   RBTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // dispose of mutex
   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   RBTree_kv_deep_dispose
*/

void
RBTree_kv_deep_dispose( Prefix )( RBTree_kv_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == RBTREE_KV_TYPE ) && ( (**current)._key_type = Key_Code ) && ( (**current)._item_type = Type_Code ) );
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
   RBTree_kv_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   RBTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // dispose of mutex
   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   RBTree_kv_cursor_dispose
*/

void
RBTree_kv_cursor_dispose( Prefix )( RBTree_kv_cursor_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( ( ( *(**current).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(**current).rbtree )._key_type = Key_Code ) && ( ( *(**current).rbtree )._item_type = Type_Code ) ) );
   LOCK( (**current).mutex );
   LOCK( ( *(**current).rbtree ).mutex );
   INVARIANT( (**current).rbtree );

   RBTree_kv_type( Prefix ) *rbtree = (**current).rbtree;

   RBTree_kv_cursor_type( Prefix ) *c1 = NULL;
   RBTree_kv_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from rbtree structure
   c1 = ( *(**current).rbtree ).first_cursor;
   c2 = (*c1).next_cursor;

   // search through the cursors
   while ( ( c2 != NULL ) && ( flag == 0 ) )
   {
      if ( c2 == *current )
      {
         // if we have a match, remove "c2" from the cursor rbtree, set flag
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

   // set rbtree's last cursor
   c1 = ( *(**current).rbtree ).first_cursor;
   while ( c1 != NULL )
   {
      c2 = c1;
      c1 = (*c1).next_cursor;
   }
   ( *(**current).rbtree ).last_cursor = c2;

   // only one cursor, last_cursor is NULL
   if ( c2 == ( *(**current).rbtree ).first_cursor )
   {
      ( *(**current).rbtree ).last_cursor = NULL;
   }

   // delete cursor struct
   free(*current);

   // set to NULL
   *current = NULL;

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return;
}

/**
   RBTree_kv_keys_as_array

*/

Type *
RBTree_kv_keys_as_array( Prefix )( RBTree_kv_type( Prefix ) *current, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*current).mutex );

   Key *result = keys_as_array( current );

   *count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_values_as_array

*/

Type *
RBTree_kv_values_as_array( Prefix )( RBTree_kv_type( Prefix ) *current, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*current).mutex );

   Type *result = values_as_array( current );

   *count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_cursor_key_at
*/

Key
RBTree_kv_cursor_key_at( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._key_type = Key_Code ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );
   PRECONDITION( "cursor not off", cursor_off( cursor ) == 0 );

   Key key = cursor_key( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return key;
}

/**
   RBTree_kv_cursor_item_at
*/

Type
RBTree_kv_cursor_item_at( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._key_type = Key_Code ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );
   PRECONDITION( "cursor not off", cursor_off( cursor ) == 0 );

   Type value = cursor_item( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}


/**
   RBTree_kv_key_at
*/

Key
RBTree_kv_key_at( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", cursor_off( (*current).first_cursor ) == 0 );

   RBTree_kv_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   Key key = cursor_key( cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return key;
}

/**
   RBTree_kv_item_at
*/

Type
RBTree_kv_item_at( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", cursor_off( (*current).first_cursor ) == 0 );

   RBTree_kv_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   Type value = cursor_item( cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   RBTree_kv_key
*/

Key
RBTree_kv_key( Prefix )( RBTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   int32_t i = 0;
   Key key;

   cursor_start( (*current).first_cursor );
   key = cursor_key( (*current).first_cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( (*current).first_cursor );
      key = cursor_key( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return key;
}

/**
   RBTree_kv_item
*/

Type
RBTree_kv_item( Prefix )( RBTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   int32_t i = 0;
   Type value;

   cursor_start( (*current).first_cursor );
   value = cursor_item( (*current).first_cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( (*current).first_cursor );
      value = cursor_item( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   RBTree_kv_first
*/

Type
RBTree_kv_first( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "current not empty", (*current).count != 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = VALUE_DEFAULT;
   node_t *node = node_for_index( current, 0 );

   if ( ( node != &(*current).root ) && ( node != &null_node ) )
   {
      result = (*node).value;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_last
*/

Type
RBTree_kv_last( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "current not empty", (*current).count != 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type result = VALUE_DEFAULT;
   node_t *node = node_for_index( current, (*current).count - 1 );

   if ( ( node != &(*current).root ) && ( node != &null_node ) )
   {
      result = (*node).value;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_key_first
*/

Key
RBTree_kv_key_first( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "current not empty", (*current).count != 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Key result = KEY_DEFAULT;
   node_t *node = node_for_index( current, 0 );

   if ( ( node != &(*current).root ) && ( node != &null_node ) )
   {
      result = (*node).key;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_key_last
*/

Key
RBTree_kv_key_last( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "current not empty", (*current).count != 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Key result = KEY_DEFAULT;
   node_t *node = node_for_index( current, (*current).count - 1 );

   if ( ( node != &(*current).root ) && ( node != &null_node ) )
   {
      result = (*node).key;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_count
*/

int32_t
RBTree_kv_count( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_height
*/

int32_t
RBTree_kv_height( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = height( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_off
*/

int32_t
RBTree_kv_off( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = cursor_off( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_cursor_off
*/

int32_t
RBTree_kv_cursor_off( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._key_type = Key_Code ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).rbtree );

   int32_t result = cursor_off( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   RBTree_kv_cursor_is_first
*/

int32_t
RBTree_kv_cursor_is_first( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );

   node_t *node = node_for_index( (*cursor).rbtree, 0 );
   int32_t result = ( node == (*cursor).item );

   if ( ( *(*cursor).rbtree ).count == 0 )
   {
      result = 0;
   }

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   RBTree_kv_cursor_is_last
*/

int32_t
RBTree_kv_cursor_is_last( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );

   node_t *node = node_for_index( (*cursor).rbtree, ( *(*cursor).rbtree ).count - 1 );
   int32_t result = ( node == (*cursor).item );

   if ( ( *(*cursor).rbtree ).count == 0 )
   {
      result = 0;
   }

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   RBTree_kv_cursor_key_search_forth
*/

void
RBTree_kv_cursor_key_search_forth( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor, Key key )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );

   while
   (
      ( cursor_off( cursor ) == 0 )
      &&
      ( KEY_DEEP_EQUAL_FUNCTION( ( *(*cursor).item ).key, key ) == 0 )
   )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_cursor_key_search_forth_eq_fn
*/

void
RBTree_kv_cursor_key_search_forth_eq_fn( Prefix )
(
   RBTree_kv_cursor_type( Prefix ) *cursor,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );

   while
   (
      ( cursor_off( cursor ) == 0 )
      &&
      ( equality_test_func( ( *(*cursor).item ).key, key ) == 0 )
   )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_cursor_search_forth
*/

void
RBTree_kv_cursor_search_forth( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );

   while
   (
      ( cursor_off( cursor ) == 0 )
      &&
      ( VALUE_DEEP_EQUAL_FUNCTION( ( *(*cursor).item ).value, value ) == 0 )
   )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_cursor_search_forth_eq_fn
*/

void
RBTree_kv_cursor_search_forth_eq_fn( Prefix )
(
   RBTree_kv_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );

   while
   (
      ( cursor_off( cursor ) == 0 )
      &&
      ( equality_test_func( ( *(*cursor).item ).value, value ) == 0 )
   )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_cursor_key_search_back
*/

void
RBTree_kv_cursor_key_search_back( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor, Key key )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );

   while
   (
      ( cursor_off( cursor ) == 0 )
      &&
      ( KEY_DEEP_EQUAL_FUNCTION( ( *(*cursor).item ).key, key ) == 0 )
   )
   {
      cursor_back( cursor );
   }

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_cursor_key_search_back_eq_fn
*/

void
RBTree_kv_cursor_key_search_back_eq_fn( Prefix )
(
   RBTree_kv_cursor_type( Prefix ) *cursor,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );

   while
   (
      ( cursor_off( cursor ) == 0 )
      &&
      ( equality_test_func( ( *(*cursor).item ).key, key ) == 0 )
   )
   {
      cursor_back( cursor );
   }

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_cursor_search_back
*/

void
RBTree_kv_cursor_search_back( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );

   while
   (
      ( cursor_off( cursor ) == 0 )
      &&
      ( VALUE_DEEP_EQUAL_FUNCTION( ( *(*cursor).item ).value, value ) == 0 )
   )
   {
      cursor_back( cursor );
   }

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_cursor_search_back_eq_fn
*/

void
RBTree_kv_cursor_search_back_eq_fn( Prefix )
(
   RBTree_kv_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );

   while
   (
      ( cursor_off( cursor ) == 0 )
      &&
      ( equality_test_func( ( *(*cursor).item ).value, value ) == 0 )
   )
   {
      cursor_back( cursor );
   }

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_is_empty
*/

int32_t
RBTree_kv_is_empty( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count ==  0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_is_first
*/

int32_t
RBTree_kv_is_first( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   RBTree_kv_is_last
*/

int32_t
RBTree_kv_is_last( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   RBTree_kv_has
*/

int32_t
RBTree_kv_has( Prefix )( RBTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has( current, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_has_eq_fn
*/

int32_t
RBTree_kv_has_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has_eq_fn( current, key, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_has_value
*/

int32_t
RBTree_kv_has_value( Prefix )( RBTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has_value( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_has_value_eq_fn
*/

int32_t
RBTree_kv_has_value_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has_value_eq_fn( current, value, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_occurrences
*/

int32_t
RBTree_kv_occurrences( Prefix )( RBTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences( current, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_occurrences_eq_fn
*/

int32_t
RBTree_kv_occurrences_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences_eq_fn( current, key, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_occurrences_value
*/

int32_t
RBTree_kv_occurrences_value( Prefix )( RBTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences_value( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_occurrences_value_eq_fn
*/

int32_t
RBTree_kv_occurrences_value_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences_value_eq_fn( current, value, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_key_search_forth
*/

void
RBTree_kv_key_search_forth( Prefix )( RBTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   while
   (
      ( cursor_off( (*current).first_cursor ) == 0 )
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
   RBTree_kv_key_search_forth_eq_fn
*/

void
RBTree_kv_key_search_forth_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   while
   (
      ( cursor_off( (*current).first_cursor ) == 0 )
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
   RBTree_kv_search_forth
*/

void
RBTree_kv_search_forth( Prefix )( RBTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   while
   (
      ( cursor_off( (*current).first_cursor ) == 0 )
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
   RBTree_kv_search_forth_eq_fn
*/

void
RBTree_kv_search_forth_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   while
   (
      ( cursor_off( (*current).first_cursor ) == 0 )
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
   RBTree_kv_key_search_back
*/

void
RBTree_kv_key_search_back( Prefix )( RBTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   while
   (
      ( cursor_off( (*current).first_cursor ) == 0 )
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
   RBTree_kv_key_search_back_eq_fn
*/

void
RBTree_kv_key_search_back_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   while
   (
      ( cursor_off( (*current).first_cursor ) == 0 )
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
   RBTree_kv_search_back
*/

void
RBTree_kv_search_back( Prefix )( RBTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   while
   (
      ( cursor_off( (*current).first_cursor ) == 0 )
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
   RBTree_kv_search_back_eq_fn
*/

void
RBTree_kv_search_back_eq_fn( Prefix )
(
   RBTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   INVARIANT( current );

   while
   (
      ( cursor_off( (*current).first_cursor ) == 0 )
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
   RBTree_kv_cursor_forth
*/
void
RBTree_kv_cursor_forth( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._key_type = Key_Code ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).rbtree );

   cursor_forth( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_cursor_back
*/
void
RBTree_kv_cursor_back( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._key_type = Key_Code ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).rbtree );

   cursor_back( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_cursor_go
*/
void
RBTree_kv_cursor_go( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._key_type = Key_Code ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < ( *(*cursor).rbtree ).count ) ) );

   int32_t i = 0;
   cursor_start( cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_cursor_go_to_key
*/
void
RBTree_kv_cursor_go_to_key( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor, Key key )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );
   POSTCONDITION_VARIABLE_DEFINE( RBTree_kv_cursor_type( Prefix ) c; c.rbtree = (*cursor).rbtree; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_empty = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_first = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_last = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_equal = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_lt = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_gt = 0; );

   node_t *node = NULL;

   if ( ( *(*cursor).rbtree ).root.left != &null_node )
   {
      node = node_for_key_recurse( ( *(*cursor).rbtree ).root.left, key );
   }

   if ( node == NULL )
   {
      (*cursor).item = &null_node;
      node = &null_node;
   }
   else
   {
      (*cursor).item = node;
   }

   POSTCONDITION_VARIABLE_DEFINE( c.item = node; if ( ( *(*cursor).rbtree ).count > 0 )
{
   if ( node == &null_node )
      {
         cursor_start( &c );
      }
      else
      {
         cursor_forth( &c );
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( ( *(*cursor).rbtree ).count == 0 )
{
   is_empty = 1;
} );
   POSTCONDITION_VARIABLE_DEFINE( if ( ( node == &null_node ) && ( c.item != &null_node ) )
{
   is_first = 1;
} );
   POSTCONDITION_VARIABLE_DEFINE( if ( ( node != &null_node ) && ( cursor_off( &c ) == 1 ) )
{
   is_last = 1;
} );
   POSTCONDITION_VARIABLE_DEFINE( if ( node != &null_node )
{
   if ( KEY_DEEP_EQUAL_FUNCTION( key, (*node).key ) == 1 )
      {
         is_equal = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( node != &null_node )
{
   if ( KEY_ORDER_FUNCTION( (*node).key, key ) == 1 )
      {
         is_lt = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( cursor_off( &c ) != 1 )
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

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );

   return;
}

/**
   RBTree_kv_cursor_index
*/

int32_t
RBTree_kv_cursor_index( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._key_type = Key_Code ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );

   int32_t result = 0;

   result = index_for_node( (*cursor).rbtree, (*cursor).item );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   RBTree_kv_cursor_start
*/

void
RBTree_kv_cursor_start( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._key_type = Key_Code ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );

   cursor_start( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_cursor_finish
*/

void
RBTree_kv_cursor_finish( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._key_type = Key_Code ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );

   cursor_finish( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_cursor_remove_at
*/

void
RBTree_kv_cursor_remove_at( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "current type ok", ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );
   PRECONDITION( "cursor not off", cursor_off( cursor ) == 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc =  ( *(*cursor).item ).key; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( (*cursor).rbtree, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).rbtree ).count; );

   node_t *node = NULL;
   node = (*cursor).item;
   cursor_forth( cursor );

   node = remove( (*cursor).rbtree, node );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( (*cursor).rbtree, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == ( *(*cursor).rbtree ).count + 1 );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_cursor_remove_at_and_dispose
*/

void
RBTree_kv_cursor_remove_at_and_dispose( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "current type ok", ( ( *(*cursor).rbtree )._type == RBTREE_KV_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );
   PRECONDITION( "cursor not off", cursor_off( cursor ) == 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = KEY_DEEP_CLONE_FUNCTION( ( *(*cursor).item ).key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( (*cursor).rbtree, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).rbtree ).count; );

   node_t *node = NULL;
   node = (*cursor).item;
   cursor_forth( cursor );

   node = remove( (*cursor).rbtree, node );

   // dispose of the value
   KEY_DEEP_DISPOSE_FUNCTION( (*node).key );
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( (*cursor).rbtree, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == ( *(*cursor).rbtree ).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( KEY_DEEP_DISPOSE_FUNCTION( key_pc ); );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_forth
*/
void
RBTree_kv_forth( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != &null_node );

   cursor_forth( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_back
*/
void
RBTree_kv_back( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != &null_node );

   cursor_back( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_go
*/
void
RBTree_kv_go( Prefix )( RBTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );

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
   RBTree_kv_go_to_key
*/
void
RBTree_kv_go_to_key( Prefix )( RBTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( RBTree_kv_cursor_type( Prefix ) c; c.rbtree = current; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_empty = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_first = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_last = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_equal = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_lt = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_gt = 0; );

   node_t *node = NULL;

   if ( (*current).root.left != &null_node )
   {
      node = node_for_key_recurse( (*current).root.left, key );
   }

   if ( node == NULL )
   {
      ( *(*current).first_cursor ).item = &null_node;
      node = &null_node;
   }
   else
   {
      ( *(*current).first_cursor ).item = node;
   }


   POSTCONDITION_VARIABLE_DEFINE( c.item = node; if ( (*current).count > 0 )
{
   if ( node == &null_node )
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
   POSTCONDITION_VARIABLE_DEFINE( if ( ( node == &null_node ) && ( c.item != &null_node ) )
{
   is_first = 1;
} );
   POSTCONDITION_VARIABLE_DEFINE( if ( ( node != &null_node ) && ( cursor_off( &c ) == 1 ) )
{
   is_last = 1;
} );
   POSTCONDITION_VARIABLE_DEFINE( if ( node != &null_node )
{
   if ( KEY_DEEP_EQUAL_FUNCTION( key, (*node).key ) == 1 )
      {
         is_equal = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( node != &null_node )
{
   if ( KEY_ORDER_FUNCTION( (*node).key, key ) == 1 )
      {
         is_lt = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( cursor_off( &c ) != 1 )
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
   RBTree_kv_index
*/

int32_t
RBTree_kv_index( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = index_for_node( current, ( *(*current).first_cursor ).item );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_kv_start
*/

void
RBTree_kv_start( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cursor_start( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_finish
*/

void
RBTree_kv_finish( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cursor_finish( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_put
*/

void
RBTree_kv_put( Prefix )( RBTree_kv_type( Prefix ) *current, Type value, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   put( current, value, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_remove
*/

void
RBTree_kv_remove( Prefix )( RBTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has( current, key ) );

   node_t *node = NULL;

   // find the node to be removed
   node = item( current, key );

   // remove the node from the tree
   node = remove( current, node );

   // dispose of the node
   node_dispose( &node );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_remove_and_dispose
*/

void
RBTree_kv_remove_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has( current, key ) );

   node_t *node = NULL;

   // find the node to be removed
   node = item( current, key );

   // remove the node from the tree
   node = remove( current, node );

   // dispose of the value
   KEY_DEEP_DISPOSE_FUNCTION( (*node).key );
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of the node
   node_dispose( &node );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_remove_by_index
*/

void
RBTree_kv_remove_by_index( Prefix )( RBTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, index );

   node = remove( current, node );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_remove_by_index_and_dispose
*/

void
RBTree_kv_remove_by_index_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, index );

   node = remove( current, node );

   // dispose of the value
   KEY_DEEP_DISPOSE_FUNCTION( (*node).key );
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_remove_value
*/

void
RBTree_kv_remove_value( Prefix )( RBTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has_value( current, value ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences_value( current, value ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   if ( (*current).count != 0 )
   {
      node = node_for_value_recurse( (*current).root.left, value );
   }

   node = remove( current, node );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences_value( current, value ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_remove_value_and_dispose
*/

void
RBTree_kv_remove_value_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has_value( current, value ) );
   POSTCONDITION_VARIABLE_DEFINE( Type value_pc = VALUE_DEEP_CLONE_FUNCTION( value ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences_value( current, value ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   if ( (*current).count != 0 )
   {
      node = node_for_value_recurse( (*current).root.left, value );
   }

   node = remove( current, node );

   KEY_DEEP_DISPOSE_FUNCTION( (*node).key );
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences_value( current, value_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( VALUE_DEEP_DISPOSE_FUNCTION( value_pc ); );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_remove_at
*/

void
RBTree_kv_remove_at( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = ( *(*current).first_cursor ).item;

   node = remove( current, node );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_remove_at_and_dispose
*/

void
RBTree_kv_remove_at_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = ( *(*current).first_cursor ).item;

   node = remove( current, node );

   KEY_DEEP_DISPOSE_FUNCTION( (*node).key );
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
   node_dispose( &node );

   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_remove_first
*/

void
RBTree_kv_remove_first( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = ( * node_for_index( current, 0 ) ).key; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, 0 );

   node = remove( current, node );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_remove_first_and_dispose
*/

void
RBTree_kv_remove_first_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = KEY_DEEP_CLONE_FUNCTION( ( * node_for_index( current, 0 ) ).key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, 0 );

   node = remove( current, node );

   KEY_DEEP_DISPOSE_FUNCTION( (*node).key );
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( KEY_DEEP_DISPOSE_FUNCTION( key_pc ); );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_remove_last
*/

void
RBTree_kv_remove_last( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = ( * node_for_index( current, (*current).count - 1 ) ).key; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, (*current).count - 1 );

   node = remove( current, node );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_remove_last_and_dispose
*/

void
RBTree_kv_remove_last_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = KEY_DEEP_CLONE_FUNCTION( ( * node_for_index( current, (*current).count - 1 ) ).key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, (*current).count - 1 );

   node = remove( current, node );

   KEY_DEEP_DISPOSE_FUNCTION( (*node).key );
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( KEY_DEEP_DISPOSE_FUNCTION( key_pc ); );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_wipe_out
*/

void
RBTree_kv_wipe_out( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
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
   RBTree_kv_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   RBTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
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
   (*current).root.left = &null_node;

   POSTCONDITION( "is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_kv_wipe_out_and_dispose
*/

void
RBTree_kv_wipe_out_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
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
   RBTree_kv_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   RBTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
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
   (*current).root.left = &null_node;

   POSTCONDITION( "is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

