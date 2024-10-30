/**
 @file AVLTree_kv.c
 @author Greg Lee
 @version 2.0.0
 @brief: "AVL Binary Search Trees of keys with values"

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

 Function definitions for the opaque AVLTree_kv_t type.

*/

#include "AVLTree_kv.h"

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
   int32_t balance;
   struct node *parent;
   struct node *left;
   struct node *right;
};

typedef struct node node_t;

struct AVLTree_kv_cursor_struct( Prefix );

/**
   Binary search tree structure definition.
*/

struct AVLTree_kv_struct( Prefix )
{

   PROTOCOLS_DEFINITION;

   int32_t _type;
   int32_t _key_type;
   int32_t _item_type;

   node_t *root;
   int32_t count;
   AVLTree_kv_cursor_type( Prefix ) *first_cursor;
   AVLTree_kv_cursor_type( Prefix ) *last_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure definition. Holds reference to avltree, current node, node
   stack, and a pointer to the next cursor.
*/

struct AVLTree_kv_cursor_struct( Prefix )
{
   AVLTree_kv_type( Prefix ) *avltree;
   node_t *item;
   AVLTree_kv_cursor_type( Prefix ) *next_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Local Function Prototypes
*/

static
void
cursor_start( AVLTree_kv_cursor_type( Prefix ) *cursor );

static
void
cursor_forth( AVLTree_kv_cursor_type( Prefix ) *cursor );

static
int32_t
cursor_off(  AVLTree_kv_cursor_type( Prefix ) *cursor );

/**
   node_make
*/

static
node_t *
node_make( void )
{
   node_t *node = ( node_t * ) calloc( 1, sizeof( node_t ) );
   CHECK( "node allocated correctly", node != NULL );

   POSTCONDITION( "node not null", node != NULL );
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
   @return 1 if key found, 0 otherwise
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

   Return 1 if avltree has an item for value, 0 if not

   @param current AVLTree_kv_t instance
   @param key the key to query for
*/

static
int32_t
has( AVLTree_kv_type( Prefix ) *current, Key key )
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
   @param equality_test_func the function to determine key equality
   @return 1 if key found, 0 otherwise
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

   @param current AVLTree_t instance
   @param key the key to query for
   @param equality_test_func the function to determine key equality
   @return 1 if value found, 0 otherwise
*/

static
int32_t
has_eq_fn
(
   AVLTree_kv_type( Prefix ) *current,
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

   Return 1 if avltree has an item for value, 0 if not

   @param avltree AVLTree_kv_t instance
   @param value the value to query for
*/

static
int32_t
has_value( AVLTree_kv_type( Prefix ) *current, Type value )
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
   AVLTree_kv_type( Prefix ) *current,
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

   Return count of item keys in avltree equal to value

   @param current AVLTree_kv_t instance
   @param key the key to query for
   @return the count of items count
*/

static
int32_t
occurrences( AVLTree_kv_type( Prefix ) *current, Key key )
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

   Return count of item keys in avltree equal to key according to equality_test_func

   @param current AVLTree_kv_t instance
   @param key the key to query for
   @param equality_test_func the test function for value equality
   @return the count of items count
*/

static
int32_t
occurrences_eq_fn
(
   AVLTree_kv_type( Prefix ) *current,
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

   Return count of items in avltree equal to value

   @param current AVLTree_kv_t instance
   @param value the value to query for
   @return the count of items count
*/

static
int32_t
occurrences_value( AVLTree_kv_type( Prefix ) *current, Type value )
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

   Return count of items in avltree equal to value according to equality_test_func

   @param current AVLTree_kv_t instance
   @param value the value to query for
   @param equality_test_func the test function for value equality
   @return the count of items count
*/

static
int32_t
occurrences_value_eq_fn
(
   AVLTree_kv_type( Prefix ) *current,
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

/**
   node_for_index

   Return node at index

   @param current the tree
   @param index the index of the desired node
   @return the desired node
*/

static
node_t *
node_for_index( AVLTree_kv_type( Prefix ) *current, int32_t index )
{
   int32_t i = 0;
   node_t *result = NULL;

   // get cursor
   AVLTree_kv_cursor_type( Prefix ) *c
      =  ( AVLTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );

   // set avltree in cursor
   (*c).avltree = current;

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
index_for_node( AVLTree_kv_type( Prefix ) *current, node_t *node )
{
   int32_t result = 0;
   int32_t flag = 0;

   // get cursor
   AVLTree_kv_cursor_type( Prefix ) *c
      =  ( AVLTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );

   // set avltree in cursor
   (*c).avltree = current;

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

   Return node in avltree that has key, NULL if none

   @param avltree AVLTree_kv_t instance
   @param key the key to query for
*/

static
node_t *
item( AVLTree_kv_type( Prefix ) *avltree, Key key )
{
   node_t *result = NULL;
   node_t *node = NULL;

   // get root node
   node = (*avltree).root;

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
   forward declarations of internal functions
*/

static
node_t *
rotate_left( AVLTree_kv_type( Prefix ) *avltree, node_t *node );

static
node_t *
rotate_right( AVLTree_kv_type( Prefix ) *avltree, node_t *node );

static
node_t *
rotate_left_right( AVLTree_kv_type( Prefix ) *avltree, node_t *node );

static
node_t *
rotate_right_left( AVLTree_kv_type( Prefix ) *avltree, node_t *node );

/**
   insert_balance

   rebalance the tree after an insert

   @param current the tree
   @param node the newly inserted node
   @param balance a flag value indicating how the tree is balanced around node
*/
static
void
insert_balance( AVLTree_kv_type( Prefix ) *avltree, node_t *node, int32_t balance )
{
   node_t *parent = NULL;
   int32_t new_balance = 0;

   new_balance = balance;

   while ( node != NULL )
   {
      // adjust balance for insert
      (*node).balance = (*node).balance + new_balance;
      new_balance = (*node).balance;

      // if balance is 0, we're done
      if ( new_balance == 0 )
      {
         break;
      }

      // cases where balance is off
      else if ( new_balance == -2 )
      {
         // rotate based on balance of left child
         if ( ( *(*node).left ).balance == -1 )
         {
            rotate_right( avltree, node );
         }
         else
         {
            rotate_left_right( avltree, node );
         }
         break;
      }
      else if ( new_balance == 2 )
      {
         // rotate based on balance of right child
         if ( ( *(*node).right ).balance == 1 )
         {
            rotate_left( avltree, node );
         }
         else
         {
            rotate_right_left( avltree, node );
         }
         break;
      }

      // set up for next interation
      parent = (*node).parent;

      if ( parent != NULL )
      {
         if ( (*parent).left == node )
         {
            new_balance = -1;
         }
         else
         {
            new_balance = 1;
         }
      }
      node = parent;
   }

   return;
}

/**
   delete_balance

   rebalance the tree after an delete

   @param current the tree
   @param node the newly inserted node
   @param balance a flag value indicating how the tree is balanced around node
*/
static
void
delete_balance( AVLTree_kv_type( Prefix ) *avltree, node_t *node, int32_t balance )
{
   node_t *parent = NULL;
   int32_t new_balance = 0;

   new_balance = balance;

   while ( node != NULL )
   {
      // adjust balance for delete
      (*node).balance = (*node).balance + new_balance;
      new_balance = (*node).balance;

      if ( new_balance == -2 )
      {
         // rotate based on balance of left child
         if ( ( *(*node).left ).balance <= 0 )
         {
            node = rotate_right( avltree, node );
            if ( (*node).balance == 1 )
            {
               break;
            }
         }
         else
         {
            node = rotate_left_right( avltree, node );
         }
      }
      else if ( new_balance == 2 )
      {
         // rotate based on balance of right child
         if ( ( *(*node).right ).balance >= 0 )
         {
            node = rotate_left( avltree, node );
            if ( (*node).balance == -1 )
            {
               break;
            }
         }
         else
         {
            node = rotate_right_left( avltree, node );
         }
      }
      else if ( new_balance != 0 )
      {
         break;
      }

      // set up for next interation
      parent = (*node).parent;

      if ( parent != NULL )
      {
         if ( (*parent).left == node )
         {
            new_balance = 1;
         }
         else
         {
            new_balance = -1;
         }
      }

      node = parent;
   }
}

/**
   replace_node

   replace one node with another and rebalance the tree

   @param target the node to be replaced
   @param source the node to be inserted into target
*/
static
void
replace_node( node_t *target, node_t *source )
{
   node_t *left = NULL;
   node_t *right = NULL;
   Key key;
   Type value;

   left = (*source).left;
   right = (*source).right;
   key = (*target).key;
   value = (*target).value;

   // put contents of source into target
   (*target).balance = (*source).balance;
   (*target).key = (*source).key;
   (*target).value = (*source).value;
   (*target).left = left;
   (*target).right = right;

   // exchange source and target key and value
   (*source).key = key;
   (*source).value = value;

   if ( left != NULL )
   {
      // the following line of code is correct, but is never called for an AVL tree
      //(*left).parent = target;
   }

   if ( right != NULL )
   {
      // the following line of code is correct, but is never called for an AVL tree
      //(*right).parent = target;
   }

   return;
}



/**
   rotate_left

   rebalance the tree with a rotate left operation

   @param current the tree
   @param node the node where the rotation will take place
*/
static
node_t *
rotate_left( AVLTree_kv_type( Prefix ) *avltree, node_t *node )
{
   node_t *right = NULL;
   node_t *right_left = NULL;
   node_t *parent = NULL;

   right = (*node).right;
   right_left = (*right).left;
   parent = (*node).parent;

   (*right).parent = parent;
   (*right).left = node;
   (*node).right = right_left;
   (*node).parent = right;

   if ( right_left != NULL )
   {
      ( *right_left ).parent = node;
   }

   if ( node == (*avltree).root )
   {
      (*avltree).root = right;
   }
   else if ( (*parent).right == node )
   {
      (*parent).right = right;
   }
   else
   {
      (*parent).left = right;
   }

   (*right).balance = (*right).balance - 1;
   (*node).balance = - (*right).balance;

   return right;
}

/**
   rotate_right

   rebalance the tree with a rotate right operation

   @param current the tree
   @param node the node where the rotation will take place
*/
static
node_t *
rotate_right( AVLTree_kv_type( Prefix ) *avltree, node_t *node )
{
   node_t *left = NULL;
   node_t *left_right = NULL;
   node_t *parent = NULL;

   left = (*node).left;
   left_right = (*left).right;
   parent = (*node).parent;

   (*left).parent = parent;
   (*left).right = node;
   (*node).left = left_right;
   (*node).parent = left;

   if ( left_right != NULL )
   {
      ( *left_right ).parent = node;
   }

   if ( node == (*avltree).root )
   {
      (*avltree).root = left;
   }
   else if ( (*parent).left == node )
   {
      (*parent).left = left;
   }
   else
   {
      (*parent).right = left;
   }

   (*left).balance = (*left).balance + 1;
   (*node).balance = - (*left).balance;

   return left;
}


/**
   rotate_left_right

   rebalance the tree with a rotate left-right operation

   @param current the tree
   @param node the node where the rotation will take place
*/
static
node_t *
rotate_left_right( AVLTree_kv_type( Prefix ) *avltree, node_t *node )
{
   node_t *left = NULL;
   node_t *left_right = NULL;
   node_t *parent = NULL;
   node_t *left_right_right = NULL;
   node_t *left_right_left = NULL;

   left = (*node).left;
   left_right = (*left).right;
   parent = (*node).parent;
   left_right_right = ( *left_right ).right;
   left_right_left = ( *left_right ).left;

   ( *left_right ).parent = parent;
   (*node).left = left_right_right;
   (*left).right = left_right_left;
   ( *left_right ).left = left;
   ( *left_right ).right = node;
   (*left).parent = left_right;
   (*node).parent = left_right;

   if ( left_right_right != NULL )
   {
      ( *left_right_right ).parent = node;
   }

   if ( left_right_left != NULL )
   {
      ( *left_right_left ).parent = left;
   }

   if ( node == (*avltree).root )
   {
      (*avltree).root = left_right;
   }
   else if ( parent->left == node )
   {
      (*parent).left = left_right;
   }
   else
   {
      (*parent).right = left_right;
   }

   if ( left_right->balance == 1 )
   {
      (*node).balance = 0;
      (*left).balance = -1;
   }
   else if ( left_right->balance == 0 )
   {
      (*node).balance = 0;
      (*left).balance = 0;
   }
   else
   {
      (*node).balance = 1;
      (*left).balance = 0;
   }

   ( *left_right ).balance = 0;

   return left_right;
}

/**
   rotate_right_left

   rebalance the tree with a rotate right-left operation

   @param current the tree
   @param node the node where the rotation will take place
*/
static
node_t *
rotate_right_left( AVLTree_kv_type( Prefix ) *avltree, node_t *node )
{
   node_t *right = NULL;
   node_t *right_left = NULL;
   node_t *parent = NULL;
   node_t *right_left_left = NULL;
   node_t *right_left_right = NULL;

   right = (*node).right;
   right_left = (*right).left;
   parent = (*node).parent;
   right_left_left = ( *right_left ).left;
   right_left_right = ( *right_left ).right;

   ( *right_left ).parent = parent;
   (*node).right = right_left_left;
   (*right).left = right_left_right;
   ( *right_left ).right = right;
   ( *right_left ).left = node;
   (*right).parent = right_left;
   (*node).parent = right_left;

   if ( right_left_left != NULL )
   {
      ( *right_left_left ).parent = node;
   }

   if ( right_left_right != NULL )
   {
      ( *right_left_right ).parent = right;
   }

   if ( node == (*avltree).root )
   {
      (*avltree).root = right_left;
   }
   else if ( (*parent).right == node )
   {
      (*parent).right = right_left;
   }
   else
   {
      (*parent).left = right_left;
   }

   if ( ( *right_left ).balance == -1 )
   {
      (*node).balance = 0;
      (*right).balance = 1;
   }
   else if ( ( *right_left ).balance == 0 )
   {
      (*node).balance = 0;
      (*right).balance = 0;
   }
   else
   {
      (*node).balance = -1;
      (*right).balance = 0;
   }

   ( *right_left ).balance = 0;

   return right_left;
}

/**
   put

   insert a key-value pair into the tree

   @param current the tree
   @param value the value to insert
   @param key the value to key
*/

static
void
put( AVLTree_kv_type( Prefix ) *avltree, Type value, Key key )
{
   node_t *node = NULL;
   node_t *new_node = NULL;
   node_t *left = NULL;
   node_t *right = NULL;

   // get new node
   new_node = node_make();
   ( *new_node ).key = key;
   ( *new_node ).value = value;

   if ( (*avltree).root == NULL )
   {
      (*avltree).root = new_node;
   }
   else
   {
      node = (*avltree).root;
      while ( node != NULL )
      {
         if ( KEY_ORDER_FUNCTION( key, (*node).key ) == 1 )
         {
            left = (*node).left;

            if ( left == NULL )
            {
               (*node).left = new_node;
               ( *new_node ).parent = node;
               insert_balance( avltree, node, -1 );
               break;
            }
            else
            {
               node = left;
            }
         }
         else if ( KEY_ORDER_FUNCTION( key, (*node).key ) == 0 )
         {
            right = (*node).right;

            if ( right == NULL )
            {
               (*node).right = new_node;
               ( *new_node ).parent = node;
               insert_balance( avltree, node, 1 );
               break;
            }
            else
            {
               node = right;
            }
         }
      }
   }

   // increment element count
   (*avltree).count = (*avltree).count + 1;

   return;
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
keys_as_array( AVLTree_kv_type( Prefix ) *current )
{
   Key *result = NULL;
   int32_t index = 0;

   result = ( Type * ) calloc( (*current).count + 1, sizeof( Key ) );
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
values_as_array( AVLTree_kv_type( Prefix ) *avltree )
{
   Type *result = NULL;
   int32_t index = 0;

   result = ( Type * ) calloc( (*avltree).count + 1, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   if ( (*avltree).root != NULL )
   {
      values_as_array_recurse( (*avltree).root, result, &index );
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
nodes_as_array( AVLTree_kv_type( Prefix ) *avltree )
{
   node_t **result = NULL;
   int32_t index = 0;

   if ( (*avltree).count == 0 )
   {
      result = ( node_t ** ) calloc( 1, sizeof( node_t ) );
      CHECK( "result allocated correctly", result != NULL );
   }
   else
   {
      result = ( node_t ** ) calloc( (*avltree).count, sizeof( node_t ) );
      CHECK( "result allocated correctly", result != NULL );
   }

   if ( (*avltree).root != NULL )
   {
      nodes_as_array_recurse( (*avltree).root, result, &index );
   }

   return result;
}

static
void
cursor_forth( AVLTree_kv_cursor_type( Prefix ) *cursor );

/**
   remove

   remove a node from the tree

   @param current the tree
   @param node the node with the value to delete
   @return the node that was deleted
*/
static
node_t *
remove( AVLTree_kv_type( Prefix ) *current, node_t *node )
{
   node_t *left = NULL;
   node_t *right = NULL;
   node_t *node_to_delete = NULL;
   node_t *parent = NULL;
   node_t *successor = NULL;
   node_t *successor_parent = NULL;
   node_t *successor_right = NULL;
   AVLTree_kv_cursor_type( Prefix ) *cursor = NULL;

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

      left = (*node).left;
      right = (*node).right;
      node_to_delete = node;

      if ( left == NULL )
      {
         if ( right == NULL )
         {
            // case where node is root of tree
            if ( node == (*current).root )
            {
               (*current).root = NULL;
            }
            // case where node has no children
            else
            {
               parent = (*node).parent;

               // node is parent's left child
               if ( (*parent).left == node )
               {
                  (*parent).left = NULL;
                  delete_balance( current, parent, 1 );
               }
               // node is parent's right child
               else
               {
                  (*parent).right = NULL;
                  delete_balance( current, parent, -1 );
               }
            }
         }
         // left child is NULL, right child isn't
         else
         {
            replace_node( node, right );
            delete_balance( current, node, 0 );
            node_to_delete = right;
         }
      }
      // left child is not NULL, right child is NULL
      else if ( right == NULL )
      {
         replace_node( node, left );
         delete_balance( current, node, 0 );
         node_to_delete = left;
      }
      // both children not NULL
      else
      {
         successor = right;
         if ( (*successor).left == NULL )
         {
            parent = (*node).parent;
            (*successor).parent = parent;
            (*successor).left = left;
            (*successor).balance = (*node).balance;

            if ( left != NULL )
            {
               (*left).parent = successor;
            }
            if ( node == (*current).root )
            {
               (*current).root = successor;
            }
            else
            {
               if ( (*parent).left == node )
               {
                  (*parent).left = successor;
               }
               else
               {
                  (*parent).right = successor;
               }
            }
            delete_balance( current, successor, -1 );
         }
         else
         {
            while ( (*successor).left != NULL )
            {
               successor = (*successor).left;
            }
            parent = (*node).parent;
            successor_parent = (*successor).parent;
            successor_right = (*successor).right;

            if ( ( *successor_parent ).left == successor )
            {
               ( *successor_parent ).left = successor_right;
            }
            else
            {
               // the following line of code is correct, but is never called for an AVL tree
               //(*successor_parent).right = successor_right;
            }

            if ( successor_right != NULL )
            {
               ( *successor_right ).parent = successor_parent;
            }

            (*successor).parent = parent;
            (*successor).left = left;
            (*successor).balance = (*node).balance;
            (*successor).right = right;
            (*right).parent = successor;

            if ( left != NULL )
            {
               (*left).parent = successor;
            }

            if ( node == (*current).root )
            {
               (*current).root = successor;
            }
            else
            {
               if ( (*parent).left == node )
               {
                  (*parent).left = successor;
               }
               else
               {
                  (*parent).right = successor;
               }
            }
            delete_balance( current, successor_parent, 1 );
         }
      }

      // decrement element count
      (*current).count = (*current).count - 1;

   }

   return node_to_delete;
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
height( AVLTree_kv_type( Prefix ) *current )
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
count( AVLTree_kv_type( Prefix ) *current )
{
   int32_t result = 0;

   result = count_recurse( (*current).root );

   return result;
}


/**
   recursion for avltree cursor functions - start, item, forth, off

   The following routines depend on the fact that the avltree
   is (already) in order and that the forth recursion keeps track
   of the last seen ( the previous ) node (in the cursor structure).
*/

/**
   cursor_finish
*/
static
void
cursor_finish( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;

   // set node from the avltree root
   node = ( *(*cursor).avltree ).root;

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
cursor_start( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;

   // set node from the avltree root
   node = ( *(*cursor).avltree ).root;

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
cursor_key_at( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   // return the value for the current cursor item
   return ( *(*cursor).item ).key;
}

/**
   cursor_item_at
*/
static
Type
cursor_item_at( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   // return the value for the current cursor item
   return ( *(*cursor).item ).value;
}


/**
   cursor_back
*/
static
void
cursor_back( AVLTree_kv_cursor_type( Prefix ) *cursor )
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
cursor_forth( AVLTree_kv_cursor_type( Prefix ) *cursor )
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
cursor_off(  AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   int32_t result = 0;

   // look for ways avltree cursor can be "off", return 1 if so

   // cursor item is null = off
   if ( (*cursor).item == NULL )
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
move_all_cursors_off( AVLTree_kv_type( Prefix ) *current )
{
   AVLTree_kv_cursor_type( Prefix ) *cursor = (*current).first_cursor;

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
   @param keys the array of keys
   @param values the array of values
   @param array_count the number of items in array
   @return 1 if all values are equal, 0 otherwise
*/

static
int32_t
compare_tree_items_to_array_items( AVLTree_kv_type( Prefix ) *current, Key *keys, Type *values, int32_t array_count )
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

   compare keys and values in one tree to values in another tree

   @param current the tree
   @param other the other tree
   @return 1 if all values are equal, 0 otherwise
*/

static
int32_t
compare_tree_items_to_tree_items( AVLTree_kv_type( Prefix ) *current, AVLTree_kv_type( Prefix ) *other )
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t count = 0;
   AVLTree_kv_cursor_type( Prefix ) *c1
      =  ( AVLTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c1 allocated correctly", c1 != NULL );

   AVLTree_kv_cursor_type( Prefix ) *c2
      =  ( AVLTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c2 allocated correctly", c2 != NULL );

   // set avltree in cursors
   (*c1).avltree = current;
   (*c2).avltree = other;

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

   compare keys and values in one tree to values in another tree, deep_equal

   @param current the tree
   @param other the other tree
   @return 1 if all values are equal, 0 otherwise
*/

static
int32_t
compare_tree_items_to_tree_items_deep_equal( AVLTree_kv_type( Prefix ) *current, AVLTree_kv_type( Prefix ) *other )
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t count = 0;
   AVLTree_kv_cursor_type( Prefix ) *c1
      =  ( AVLTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c1 allocated correctly", c1 != NULL );

   AVLTree_kv_cursor_type( Prefix ) *c2
      =  ( AVLTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_kv_cursor_type( Prefix ) ) );
   CHECK( "c2 allocated correctly", c2 != NULL );

   // set avltree in cursors
   (*c1).avltree = current;
   (*c2).avltree = other;

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
is_empty_implies_root_null( AVLTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).count == 0 )
   {
      result = ( (*p).root == NULL );
   }

   return result;
}

static
int32_t
nonnegative_count( AVLTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
valid_count( AVLTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( count( p ) == (*p).count );

   return result;
}

static
int32_t
first_cursor_not_null( AVLTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).first_cursor != NULL );

   return result;
}

static
int32_t
last_cursor_null_if_one_cursor( AVLTree_kv_type( Prefix ) *p )
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
cursors_avltree_ok( AVLTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   AVLTree_kv_cursor_type( Prefix ) *cursor = (*p).first_cursor;

   while( ( cursor != NULL ) && ( result == 1 ) )
   {
      result = ( (*cursor).avltree == p );
      cursor = (*cursor).next_cursor;
   }

   return result;
}

static
int32_t
last_cursor_next_null( AVLTree_kv_type( Prefix ) *p )
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
in_order( AVLTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).count > 1 )
   {
      result = in_order_recurse( (*p).root );
   }

   return result;
}

static
int32_t
balance_recurse( node_t *node )
{
   int32_t result = 1;

   result = ( (*node).balance == -1 ) || ( (*node).balance == 0 ) || ( (*node).balance == 1 );

   if ( result == 1 )
   {
      if ( (*node).left != NULL )
      {
         result = balance_recurse( (*node).left );
      }
   }

   if ( result == 1 )
   {
      if ( (*node).right != NULL )
      {
         result = balance_recurse( (*node).right );
      }
   }

   return result;
}

static
int32_t
balance_ok( AVLTree_kv_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).count > 1 )
   {
      result = balance_recurse( (*p).root );
   }

   return result;
}

static
void invariant( AVLTree_kv_type( Prefix ) *p )
{
   assert( ( ( void ) "empty implies root null", is_empty_implies_root_null( p ) ) );
   assert( ( ( void ) "nonnegative count", nonnegative_count( p ) ) );
   assert( ( ( void ) "valid count", valid_count( p ) ) );
   assert( ( ( void ) "first cursor not null", first_cursor_not_null( p ) ) );
   assert( ( ( void ) "last cursor next null", last_cursor_next_null( p ) ) );
   assert( ( ( void ) "last cursor null if one cursor", last_cursor_null_if_one_cursor( p ) ) );
   assert( ( ( void ) "cursors avltree OK", cursors_avltree_ok( p ) ) );
   assert( ( ( void ) "avltree in order", in_order( p ) ) );
   assert( ( ( void ) "avltree in balance", balance_ok( p ) ) );
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
   AVLTree_kv_dispose( Prefix ),
   AVLTree_kv_deep_dispose( Prefix ),
   AVLTree_kv_is_equal( Prefix ),
   AVLTree_kv_is_deep_equal( Prefix ),
   AVLTree_kv_copy( Prefix ),
   AVLTree_kv_deep_copy( Prefix ),
   AVLTree_kv_clone( Prefix ),
   AVLTree_kv_deep_clone( Prefix )
};

static
void *
p_iterable_kv_table[P_ITERABLE_KV_FUNCTION_COUNT]
=
{
   AVLTree_kv_count( Prefix ),
   AVLTree_kv_key_at( Prefix ),
   AVLTree_kv_item_at( Prefix ),
   AVLTree_kv_off( Prefix ),
   AVLTree_kv_is_empty( Prefix ),
   AVLTree_kv_start( Prefix ),
   AVLTree_kv_forth( Prefix )
};

static
void *
p_diterable_kv_table[P_DITERABLE_KV_FUNCTION_COUNT]
=
{
   AVLTree_kv_count( Prefix ),
   AVLTree_kv_key_at( Prefix ),
   AVLTree_kv_item_at( Prefix ),
   AVLTree_kv_off( Prefix ),
   AVLTree_kv_is_empty( Prefix ),
   AVLTree_kv_start( Prefix ),
   AVLTree_kv_forth( Prefix ),
   AVLTree_kv_finish( Prefix ),
   AVLTree_kv_back( Prefix )
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
   AVLTree_kv_make
*/

AVLTree_kv_type( Prefix ) *
AVLTree_kv_make( Prefix )( void )
{
   // allocate avltree struct
   AVLTree_kv_type( Prefix ) *result
      = ( AVLTree_kv_type( Prefix ) * ) calloc( 1, sizeof( AVLTree_kv_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = AVLTREE_KV_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   // root is null
   (*result).root = NULL;

   // count is zeor
   (*result).count = 0;

   // set built-in cursor
   // allocate cursor struct
   AVLTree_kv_cursor_type( Prefix ) *cursor
      =  ( AVLTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_kv_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set result
   (*cursor).avltree = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set result built-in cursor
   (*result).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new result is empty", (*result).count == 0 );
   POSTCONDITION( "new result cursor is off", ( *(*result).first_cursor ).item == NULL );

   INVARIANT( result );

   return result;
}

/**
   AVLTree_kv_make_from_array
*/

AVLTree_kv_type( Prefix ) *
AVLTree_kv_make_from_array( Prefix )( Key *key_array, Type *value_array, int32_t count )
{
   PRECONDITION( "key_array not null", key_array != NULL );
   PRECONDITION( "value_array not null", value_array != NULL );
   PRECONDITION( "count ok", count >= 0 );

   // make avltree struct
   AVLTree_kv_type( Prefix ) *result = AVLTree_kv_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = AVLTREE_KV_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   int32_t i = 0;

   for ( i = 0; i < count; i++ )
   {
      put( result, value_array[i], key_array[i] );
   }

   POSTCONDITION( "new result cursor is off", ( *(*result).first_cursor ).item == NULL );
   POSTCONDITION( "new result contains elements of array", compare_tree_items_to_array_items( result, key_array, value_array, count ) );

   INVARIANT( result );

   return result;
}

/**
   AVLTree_kv_clone
*/

AVLTree_kv_type( Prefix ) *
AVLTree_kv_clone( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );

   // make current struct
   AVLTree_kv_type( Prefix ) *result = AVLTree_kv_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = AVLTREE_KV_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   // copy from current
   AVLTree_kv_cursor_type( Prefix ) *cursor = AVLTree_kv_cursor_make( Prefix )( current );

   // lock current
   LOCK( (*current).mutex );

   INVARIANT( current );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, cursor_item_at( cursor ), cursor_key_at( cursor ) );
      cursor_forth( cursor );
   }

   POSTCONDITION( "new tree cursor is off", ( *(*result).first_cursor ).item == NULL );
   POSTCONDITION( "new tree contains elements of current", compare_tree_items_to_tree_items( result, current ) );

   INVARIANT( result );

   // unlock current
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_deep_clone
*/

AVLTree_kv_type( Prefix ) *
AVLTree_kv_deep_clone( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );

   // make current struct
   AVLTree_kv_type( Prefix ) *result = AVLTree_kv_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = AVLTREE_KV_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   // copy from current
   AVLTree_kv_cursor_type( Prefix ) *cursor = AVLTree_kv_cursor_make( Prefix )( current );

   // lock current
   LOCK( (*current).mutex );

   INVARIANT( current );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, VALUE_DEEP_CLONE_FUNCTION( cursor_item_at( cursor ) ), KEY_DEEP_CLONE_FUNCTION( cursor_key_at( cursor ) ) );
      cursor_forth( cursor );
   }

   POSTCONDITION( "new tree cursor is off", ( *(*result).first_cursor ).item == NULL );
   POSTCONDITION( "new tree contains elements of current", compare_tree_items_to_tree_items_deep_equal( result, current ) );

   INVARIANT( result );

   // unlock current
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_is_equal
*/

int32_t
AVLTree_kv_is_equal( Prefix )( AVLTree_kv_type( Prefix ) *current, AVLTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == AVLTREE_KV_TYPE ) && ( (*other)._item_type = Type_Code ) );

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
   AVLTree_kv_is_deep_equal
*/

int32_t
AVLTree_kv_is_deep_equal( Prefix )( AVLTree_kv_type( Prefix ) *current, AVLTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == AVLTREE_KV_TYPE ) && ( (*other)._item_type = Type_Code ) );

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
   AVLTree_kv_copy
*/

void
AVLTree_kv_copy( Prefix )( AVLTree_kv_type( Prefix ) *current, AVLTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == AVLTREE_KV_TYPE ) && ( (*other)._item_type = Type_Code ) );

   // lock current
   LOCK( (*current).mutex );

   INVARIANT( current );

   if ( current != other )
   {
      int32_t i = 0;
      AVLTree_kv_cursor_type( Prefix ) *c
         =  ( AVLTree_kv_cursor_type( Prefix ) * )
            calloc( 1, sizeof( AVLTree_kv_cursor_type( Prefix ) ) );
      CHECK( "c allocated correctly", c != NULL );

      (*c).avltree = other;

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
      (*current).root = NULL;

      cursor_start( c );

      while ( cursor_off( c ) == 0 )
      {
         put( current, cursor_item_at( c ), cursor_key_at( c ) );
         cursor_forth( c );
      }

      // free c
      free( c );

      POSTCONDITION( "new avltree contains elements of other", compare_tree_items_to_tree_items( current, other ) );

      // unlock other
      UNLOCK( (*other).mutex );

      INVARIANT( current );
   }

   // unlock current
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_deep_copy
*/

void
AVLTree_kv_deep_copy( Prefix )( AVLTree_kv_type( Prefix ) *current, AVLTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == AVLTREE_KV_TYPE ) && ( (*other)._item_type = Type_Code ) );

   // lock current
   LOCK( (*current).mutex );

   INVARIANT( current );

   if ( current != other )
   {
      int32_t i = 0;
      Key k;
      Type v;
      AVLTree_kv_cursor_type( Prefix ) *c
         =  ( AVLTree_kv_cursor_type( Prefix ) * )
            calloc( 1, sizeof( AVLTree_kv_cursor_type( Prefix ) ) );
      CHECK( "c allocated correctly", c != NULL );

      (*c).avltree = other;

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

      POSTCONDITION( "new avltree contains elements of other", compare_tree_items_to_tree_items_deep_equal( current, other ) );

      // unlock other
      UNLOCK( (*other).mutex );

      INVARIANT( current );
   }

   // unlock current
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_cursor_make
*/

AVLTree_kv_cursor_type( Prefix ) *
AVLTree_kv_cursor_make( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // allocate cursor struct
   AVLTree_kv_cursor_type( Prefix ) *cursor
      =  ( AVLTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_kv_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set current
   (*cursor).avltree = current;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // place cursor reference into current structure
   if ( (*current).last_cursor == NULL )
   {
      // set second cursor for current
      ( *(*current).first_cursor ).next_cursor = cursor;
      (*current).last_cursor = cursor;
   }
   else
   {
      // set additional cursor for current
      // (*current).last_cursor holds last cursor allocated
      ( *(*current).last_cursor ).next_cursor = cursor;
      (*current).last_cursor = cursor;
   }

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );
   POSTCONDITION( "new cursor is last cursor", (*current).last_cursor == cursor );
   UNLOCK( (*current).mutex );

   return cursor;
}

/**
   AVLTree_kv_dispose
*/

void
AVLTree_kv_dispose( Prefix )( AVLTree_kv_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == AVLTREE_KV_TYPE ) && ( (**current)._key_type = Key_Code ) && ( (**current)._item_type = Type_Code ) );
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
   AVLTree_kv_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   AVLTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
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
   AVLTree_kv_deep_dispose
*/

void
AVLTree_kv_deep_dispose( Prefix )( AVLTree_kv_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == AVLTREE_KV_TYPE ) && ( (**current)._key_type = Key_Code ) && ( (**current)._item_type = Type_Code ) );
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
   AVLTree_kv_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   AVLTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
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
   AVLTree_kv_cursor_dispose
*/

void
AVLTree_kv_cursor_dispose( Prefix )( AVLTree_kv_cursor_type( Prefix ) **cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "*cursor not null", *cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(**cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(**cursor).avltree )._key_type = Key_Code ) && ( ( *(**cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (**cursor).mutex );
   LOCK( ( *(**cursor).avltree ).mutex );
   INVARIANT( (**cursor).avltree );

   AVLTree_kv_type( Prefix ) *avltree = (**cursor).avltree;

   AVLTree_kv_cursor_type( Prefix ) *c1 = NULL;
   AVLTree_kv_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from avltree structure
   c1 = ( *(**cursor).avltree ).first_cursor;
   c2 = (*c1).next_cursor;

   // search through the cursors
   while ( ( c2 != NULL ) && ( flag == 0 ) )
   {
      if ( c2 == *cursor )
      {
         // if we have a match, remove "c2" from the cursor avltree, set flag
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

   // set avltree's last cursor
   c1 = ( *(**cursor).avltree ).first_cursor;
   while ( c1 != NULL )
   {
      c2 = c1;
      c1 = (*c1).next_cursor;
   }
   ( *(**cursor).avltree ).last_cursor = c2;

   // only one cursor, last_cursor is NULL
   if ( c2 == ( *(**cursor).avltree ).first_cursor )
   {
      ( *(**cursor).avltree ).last_cursor = NULL;
   }

   // delete cursor struct
   free(*cursor);

   // set to NULL
   *cursor = NULL;

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return;
}

/**
   AVLTree_kv_values_as_array

*/

Type *
AVLTree_kv_values_as_array( Prefix )( AVLTree_kv_type( Prefix ) *current, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type *result = values_as_array( current );

   *count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_keys_as_array

*/

Key *
AVLTree_kv_keys_as_array( Prefix )( AVLTree_kv_type( Prefix ) *current, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Key *result = keys_as_array( current );

   *count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_cursor_key_at
*/

Key
AVLTree_kv_cursor_key_at( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._key_type = Key_Code ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Key key = cursor_key_at( cursor );

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return key;
}

/**
   AVLTree_kv_cursor_item_at
*/

Type
AVLTree_kv_cursor_item_at( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._key_type = Key_Code ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Type value = cursor_item_at( cursor );

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}


/**
   AVLTree_kv_key_at
*/

Key
AVLTree_kv_key_at( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   AVLTree_kv_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   Key key = cursor_key_at( cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return key;
}

/**
   AVLTree_kv_item_at
*/

Type
AVLTree_kv_item_at( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   AVLTree_kv_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   Type value = cursor_item_at( cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   AVLTree_kv_key
*/

Key
AVLTree_kv_key( Prefix )( AVLTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   int32_t i = 0;
   Key key;

   cursor_start( (*current).first_cursor );
   key = cursor_key_at( (*current).first_cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( (*current).first_cursor );
      key = cursor_key_at( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return key;
}

/**
   AVLTree_kv_item
*/

Type
AVLTree_kv_item( Prefix )( AVLTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   int32_t i = 0;
   Type value;

   cursor_start( (*current).first_cursor );
   value = cursor_item_at( (*current).first_cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( (*current).first_cursor );
      value = cursor_item_at( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   AVLTree_kv_first
*/

Type
AVLTree_kv_first( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not empty", (*current).root != NULL );
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
   AVLTree_kv_last
*/

Type
AVLTree_kv_last( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not empty", (*current).root != NULL );
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
   AVLTree_kv_key_first
*/

Key
AVLTree_kv_key_first( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not empty", (*current).root != NULL );
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
   AVLTree_kv_key_last
*/

Key
AVLTree_kv_key_last( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not empty", (*current).root != NULL );
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
   AVLTree_kv_count
*/

int32_t
AVLTree_kv_count( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   AVLTree_kv_height
*/

int32_t
AVLTree_kv_height( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = height( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   AVLTree_kv_off
*/

int32_t
AVLTree_kv_off( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = cursor_off( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_cursor_off
*/

int32_t
AVLTree_kv_cursor_off( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._key_type = Key_Code ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   int32_t result = cursor_off( cursor );

   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AVLTree_kv_cursor_is_first
*/

int32_t
AVLTree_kv_cursor_is_first( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );

   node_t *node = node_for_index( (*cursor).avltree, 0 );
   int32_t result = ( node == (*cursor).item );

   if ( ( *(*cursor).avltree ).count == 0 )
   {
      result = 0;
   }

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AVLTree_kv_cursor_is_last
*/

int32_t
AVLTree_kv_cursor_is_last( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );

   node_t *node = node_for_index( (*cursor).avltree, ( *(*cursor).avltree ).count - 1 );
   int32_t result = ( node == (*cursor).item );

   if ( ( *(*cursor).avltree ).count == 0 )
   {
      result = 0;
   }

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AVLTree_kv_cursor_key_search_forth
*/

void
AVLTree_kv_cursor_key_search_forth( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor, Key key )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( KEY_DEEP_EQUAL_FUNCTION( ( *(*cursor).item ).key, key ) == 0 )
   )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_cursor_key_search_forth_eq_fn
*/

void
AVLTree_kv_cursor_key_search_forth_eq_fn( Prefix )
(
   AVLTree_kv_cursor_type( Prefix ) *cursor,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( equality_test_func( ( *(*cursor).item ).key, key ) == 0 )
   )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_cursor_search_forth
*/

void
AVLTree_kv_cursor_search_forth( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( VALUE_DEEP_EQUAL_FUNCTION( ( *(*cursor).item ).value, value ) == 0 )
   )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_cursor_search_forth_eq_fn
*/

void
AVLTree_kv_cursor_search_forth_eq_fn( Prefix )
(
   AVLTree_kv_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( equality_test_func( ( *(*cursor).item ).value, value ) == 0 )
   )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_cursor_key_search_back
*/

void
AVLTree_kv_cursor_key_search_back( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor, Key key )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( KEY_DEEP_EQUAL_FUNCTION( ( *(*cursor).item ).key, key ) == 0 )
   )
   {
      cursor_back( cursor );
   }

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_cursor_key_search_back_eq_fn
*/

void
AVLTree_kv_cursor_key_search_back_eq_fn( Prefix )
(
   AVLTree_kv_cursor_type( Prefix ) *cursor,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( equality_test_func( ( *(*cursor).item ).key, key ) == 0 )
   )
   {
      cursor_back( cursor );
   }

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_cursor_search_back
*/

void
AVLTree_kv_cursor_search_back( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( VALUE_DEEP_EQUAL_FUNCTION( ( *(*cursor).item ).value, value ) == 0 )
   )
   {
      cursor_back( cursor );
   }

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_cursor_search_back_eq_fn
*/

void
AVLTree_kv_cursor_search_back_eq_fn( Prefix )
(
   AVLTree_kv_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );

   while
   (
      ( (*cursor).item != NULL )
      &&
      ( equality_test_func( ( *(*cursor).item ).value, value ) == 0 )
   )
   {
      cursor_back( cursor );
   }

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_is_empty
*/

int32_t
AVLTree_kv_is_empty( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count ==  0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_is_first
*/

int32_t
AVLTree_kv_is_first( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_kv_is_last
*/

int32_t
AVLTree_kv_is_last( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_kv_has
*/

int32_t
AVLTree_kv_has( Prefix )( AVLTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has( current, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_has_eq_fn
*/

int32_t
AVLTree_kv_has_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has_eq_fn( current, key, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_has_value
*/

int32_t
AVLTree_kv_has_value( Prefix )( AVLTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has_value( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_has_value_eq_fn
*/

int32_t
AVLTree_kv_has_value_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has_value_eq_fn( current, value, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_occurrences
*/

int32_t
AVLTree_kv_occurrences( Prefix )( AVLTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences( current, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_occurrences_eq_fn
*/

int32_t
AVLTree_kv_occurrences_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences_eq_fn( current, key, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_occurrences_value
*/

int32_t
AVLTree_kv_occurrences_value( Prefix )( AVLTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences_value( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_occurrences_value_eq_fn
*/

int32_t
AVLTree_kv_occurrences_value_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences_value_eq_fn( current, value, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_key_search_forth
*/

void
AVLTree_kv_key_search_forth( Prefix )( AVLTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_kv_key_search_forth_eq_fn
*/

void
AVLTree_kv_key_search_forth_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_kv_search_forth
*/

void
AVLTree_kv_search_forth( Prefix )( AVLTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_kv_search_forth_eq_fn
*/

void
AVLTree_kv_search_forth_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_kv_key_search_back
*/

void
AVLTree_kv_key_search_back( Prefix )( AVLTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_kv_key_search_back_eq_fn
*/

void
AVLTree_kv_key_search_back_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *current,
   Key key,
   int32_t ( *equality_test_func )( Key k1, Key k2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_kv_search_back
*/

void
AVLTree_kv_search_back( Prefix )( AVLTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_kv_search_back_eq_fn
*/

void
AVLTree_kv_search_back_eq_fn( Prefix )
(
   AVLTree_kv_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_kv_cursor_forth
*/
void
AVLTree_kv_cursor_forth( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._key_type = Key_Code ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   cursor_forth( cursor );

   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_cursor_back
*/
void
AVLTree_kv_cursor_back( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._key_type = Key_Code ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   cursor_back( cursor );

   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_cursor_go
*/
void
AVLTree_kv_cursor_go( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._key_type = Key_Code ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < ( *(*cursor).avltree ).count ) ) );

   int32_t i = 0;
   cursor_start( cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_cursor_go_to_key
*/
void
AVLTree_kv_cursor_go_to_key( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor, Key key )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );
   POSTCONDITION_VARIABLE_DEFINE( AVLTree_kv_cursor_type( Prefix ) c; c.avltree = (*cursor).avltree; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_empty = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_first = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_last = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_equal = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_lt = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_gt = 0; );

   node_t *node = NULL;

   if ( ( *(*cursor).avltree ).root != NULL )
   {
      node = node_for_key_recurse( ( *(*cursor).avltree ).root, key );
   }

   (*cursor).item = node;

   POSTCONDITION_VARIABLE_DEFINE( c.item = node; if ( ( *(*cursor).avltree ).count > 0 )
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
   POSTCONDITION_VARIABLE_DEFINE( if ( ( *(*cursor).avltree ).count == 0 )
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

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );

   return;
}

/**
   AVLTree_kv_cursor_index
*/

int32_t
AVLTree_kv_cursor_index( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._key_type = Key_Code ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );

   int32_t result = 0;

   result = index_for_node( (*cursor).avltree, (*cursor).item );

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AVLTree_kv_cursor_remove_at
*/

void
AVLTree_kv_cursor_remove_at( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "current type ok", ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc =  ( *(*cursor).item ).key; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( (*cursor).avltree, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).avltree ).count; );

   node_t *node = NULL;
   node = (*cursor).item;

   node = remove( (*cursor).avltree, node );

   // dispose of node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( (*cursor).avltree, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == ( *(*cursor).avltree ).count + 1 );

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_cursor_remove_at_and_dispose
*/

void
AVLTree_kv_cursor_remove_at_and_dispose( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "current type ok", ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = KEY_DEEP_CLONE_FUNCTION( ( *(*cursor).item ).key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( (*cursor).avltree, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).avltree ).count; );

   node_t *node = NULL;
   node = (*cursor).item;

   node = remove( (*cursor).avltree, node );

   // dispose of key
   KEY_DEEP_DISPOSE_FUNCTION( (*node).key );

   // dispose of value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( (*cursor).avltree, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == ( *(*cursor).avltree ).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( KEY_DEEP_DISPOSE_FUNCTION( key_pc ); );

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_cursor_start
*/

void
AVLTree_kv_cursor_start( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._key_type = Key_Code ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );

   cursor_start( cursor );

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_cursor_finish
*/

void
AVLTree_kv_cursor_finish( Prefix )( AVLTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_KV_TYPE ) && ( ( *(*cursor).avltree )._key_type = Key_Code ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).avltree ).mutex );
   INVARIANT( (*cursor).avltree );

   cursor_finish( cursor );

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_kv_forth
*/
void
AVLTree_kv_forth( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   cursor_forth( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_back
*/
void
AVLTree_kv_back( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   cursor_back( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_go
*/
void
AVLTree_kv_go( Prefix )( AVLTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_kv_go_to_key
*/
void
AVLTree_kv_go_to_key( Prefix )( AVLTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( AVLTree_kv_cursor_type( Prefix ) c; c.avltree = current; );
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
   AVLTree_kv_index
*/

int32_t
AVLTree_kv_index( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = index_for_node( current, ( *(*current).first_cursor ).item );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_kv_start
*/

void
AVLTree_kv_start( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cursor_start( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_finish
*/

void
AVLTree_kv_finish( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cursor_finish( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_put
*/

void
AVLTree_kv_put( Prefix )( AVLTree_kv_type( Prefix ) *current, Type value, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   put( current, value, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_remove
*/

void
AVLTree_kv_remove( Prefix )( AVLTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has( current, key ) );

   node_t *node = NULL;
   node = item( current, key );

   node = remove( current, node );

   // dispose of node
   node_dispose( &node );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_remove_and_dispose
*/

void
AVLTree_kv_remove_and_dispose( Prefix )( AVLTree_kv_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has( current, key ) );

   node_t *node = NULL;
   node = item( current, key );

   node = remove( current, node );

   // dispose of key
   KEY_DEEP_DISPOSE_FUNCTION( (*node).key );

   // dispose of value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of node
   node_dispose( &node );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_remove_by_index
*/

void
AVLTree_kv_remove_by_index( Prefix )( AVLTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, index );

   node = remove( current, node );

   // dispose of node
   node_dispose( &node );

   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_remove_by_index_and_dispose
*/

void
AVLTree_kv_remove_by_index_and_dispose( Prefix )( AVLTree_kv_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, index );

   node = remove( current, node );

   // dispose of key
   KEY_DEEP_DISPOSE_FUNCTION( (*node).key );

   // dispose of value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of node
   node_dispose( &node );

   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_remove_value
*/

void
AVLTree_kv_remove_value( Prefix )( AVLTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
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

   node = remove( current, node );

   // dispose of node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences_value( current, value ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_remove_value_and_dispose
*/

void
AVLTree_kv_remove_value_and_dispose( Prefix )( AVLTree_kv_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
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

   node = remove( current, node );

   // dispose of key
   KEY_DEEP_DISPOSE_FUNCTION( (*node).key );

   // dispose of value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences_value( current, value_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( VALUE_DEEP_DISPOSE_FUNCTION( value_pc ); );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_remove_at
*/

void
AVLTree_kv_remove_at( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = ( *(*current).first_cursor ).item;

   node = remove( current, node );

   // dispose of node
   node_dispose( &node );

   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_remove_at_and_dispose
*/

void
AVLTree_kv_remove_at_and_dispose( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = ( *(*current).first_cursor ).item;

   node = remove( current, node );

   // dispose of key
   KEY_DEEP_DISPOSE_FUNCTION( (*node).key );

   // dispose of value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of node
   node_dispose( &node );

   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_remove_first
*/

void
AVLTree_kv_remove_first( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = ( * node_for_index( current, 0 ) ).key; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, 0 );

   node = remove( current, node );

   // dispose of node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_remove_first_and_dispose
*/

void
AVLTree_kv_remove_first_and_dispose( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = KEY_DEEP_CLONE_FUNCTION( ( * node_for_index( current, 0 ) ).key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, 0 );

   node = remove( current, node );

   // dispose of key
   KEY_DEEP_DISPOSE_FUNCTION( (*node).key );

   // dispose of value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( KEY_DEEP_DISPOSE_FUNCTION( key_pc ); );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_remove_last
*/

void
AVLTree_kv_remove_last( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = ( * node_for_index( current, (*current).count - 1 ) ).key; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, (*current).count - 1 );

   node = remove( current, node );

   // dispose of node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_remove_last_and_dispose
*/

void
AVLTree_kv_remove_last_and_dispose( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type key_pc = KEY_DEEP_CLONE_FUNCTION( ( * node_for_index( current, (*current).count - 1 ) ).key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, key_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, (*current).count - 1 );

   node = remove( current, node );

   // dispose of key
   KEY_DEEP_DISPOSE_FUNCTION( (*node).key );

   // dispose of value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, key_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( KEY_DEEP_DISPOSE_FUNCTION( key_pc ); );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_wipe_out
*/

void
AVLTree_kv_wipe_out( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_kv_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   AVLTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
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

   POSTCONDITION( "is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_kv_wipe_out_and_dispose
*/

void
AVLTree_kv_wipe_out_and_dispose( Prefix )( AVLTree_kv_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_kv_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   AVLTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
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

   POSTCONDITION( "is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

