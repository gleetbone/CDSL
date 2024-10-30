/**
 @file BTree_kv.c
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

 Function definitions for the opaque BTree_kv_t type.

*/

#include "BTree_kv.h"

#include "protocol.h"

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

#define BTREE_KV_TYPE 0xA5000210
#define BTREE_CURSOR_MIN_INDICES 4

/**
   Node structure declaration
*/

struct node;

/**
   Node structure definition. Holds a key and a value array.
*/

struct node
{
   int32_t n;  // number of keys, always less than (*current).max_n_keys + 1
   Key *keys;  // (*current).max_n_keys plus extra array
   // location used for temporary storage
   // during split
   Type *values;  // (*current).max_n_keys plus extra array
   // location used for temporary storage
   // during split
   struct node **children; // (*current).max_n_keys + 1 plus extra array location
   // used for temporary storage during split
   struct node *parent;
};

typedef struct node node_t;

struct BTree_kv_cursor_struct( Prefix );

/**
   Binary search tree structure definition.
*/

struct BTree_kv_struct( Prefix )
{

   PROTOCOLS_DEFINITION;

   int32_t _type;
   int32_t _key_type;
   int32_t _item_type;

   int32_t max_n_keys;
   int32_t min_n_keys;
   node_t *root;
   int32_t count;
   BTree_kv_cursor_type( Prefix ) *first_cursor;
   BTree_kv_cursor_type( Prefix ) *last_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure definition. Holds reference to btree, current node, node
   stack, and a pointer to the next cursor.
*/

struct BTree_kv_cursor_struct( Prefix )
{
   BTree_kv_type( Prefix ) *btree;
   node_t *item;
   int32_t *indices;
   int32_t n_indices;
   int32_t i_indices;
   BTree_kv_cursor_type( Prefix ) *next_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Function prototypes
*/

static
BTree_kv_cursor_type( Prefix ) *
cursor_make( BTree_kv_type( Prefix ) *btree );

static
void
cursor_dispose( BTree_kv_cursor_type( Prefix ) **cursor );

static
void
cursor_ensure_indices_ok( BTree_kv_cursor_type( Prefix ) *cursor );

static
int32_t
cursor_down_to_leftmost_child( BTree_kv_cursor_type( Prefix ) *cursor );

static
void
cursor_up_to_next_parent( BTree_kv_cursor_type( Prefix ) *cursor );

static
int32_t
cursor_down_to_rightmost_child( BTree_kv_cursor_type( Prefix ) *cursor );

static
void
cursor_up_to_prev_parent( BTree_kv_cursor_type( Prefix ) *cursor );

static
void
cursor_start( BTree_kv_cursor_type( Prefix ) *cursor );

static
void
cursor_finish( BTree_kv_cursor_type( Prefix ) *cursor );

static
void
cursor_forth( BTree_kv_cursor_type( Prefix ) *cursor );

static
void
cursor_back( BTree_kv_cursor_type( Prefix ) *cursor );

static
int32_t
cursor_off(  BTree_kv_cursor_type( Prefix ) *cursor );

static
Key
cursor_key( BTree_kv_cursor_type( Prefix ) *cursor );

static
Type
cursor_item( BTree_kv_cursor_type( Prefix ) *cursor );

static
void
rebalance( BTree_kv_type( Prefix ) *btree, node_t *node, Key key );

/**
   node_make

   create a node with space for up to max_n_keys nodes

   @param max_n_keys the maximum number of keys the node can hold
   @return the new node
*/

static
node_t *
node_make( int32_t max_n_keys )
{
   node_t *node = ( node_t * ) calloc( 1, sizeof( node_t ) );
   CHECK( "node allocated correctly", node != NULL );

   (*node).keys = ( Key * ) calloc( max_n_keys + 1, sizeof( Key ) );
   CHECK( "(*node).keys allocated correctly", (*node).keys != NULL );

   (*node).values = ( Type * ) calloc( max_n_keys + 1, sizeof( Type ) );
   CHECK( "(*node).values allocated correctly", (*node).values != NULL );

   (*node).children = ( struct node ** ) calloc( max_n_keys + 2, sizeof( struct node * ) );
   CHECK( "(*node).children allocated correctly", (*node).children != NULL );

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

   (**node).n = 0;

   free( (**node).keys );
   (**node).keys = NULL;

   free( (**node).values );
   (**node).values = NULL;

   free( (**node).children );
   (**node).children = NULL;

   (**node).parent = NULL;

   free(*node);
   *node = NULL;

   return;
}

/**
   node_in_node

   (recursively) find the node with the specified key

   @param node the current node
   @param key the desired key
   @param next the next node to search for key if not found
   @param index returns the index of the found node
   @return 1 if key and node found, 0 if not found but key is less than node's key
           > 1 if key is greater than node's key
*/
static
int32_t
node_in_node( node_t *node, Key key, node_t **next, int32_t *index )
{
   int32_t result = 0;
   int32_t lo = 0;
   int32_t hi = 0;
   int32_t m = 0;
   int32_t n = 0;
   Key k;
   Key k_lo;
   Key k_hi;
   Key *keys;

   // set returned index to invalid number
   *index = -1;

   // get node key count and shortcut to keys[]
   n = (*node).n;
   keys = (*node).keys;

   // check for key above keys[n-1] and below keys[0]
   if ( KEY_ORDER_FUNCTION( keys[n - 1], key ) == 1 )
   {
      *next = (*node).children[ n ];
      *index = n; // invalid key index but valid child index indicating key is greater than keys[n-1]
   }
   else if ( KEY_ORDER_FUNCTION( key, keys[0] ) == 1 )
   {
      *next = (*node).children[0];
      *index = 0;
   }
   else if ( KEY_EQUAL_FUNCTION( key, keys[0] ) == 1 )
   {
      result = 1;
      *next = (*node).children[0];
      *index = 0;
   }
   else
   {
      // otherwise search in keys
      lo = 0;
      hi = n - 1;

      // find lo and hi bracketing the key value, or find a key match
      while ( hi > lo )
      {
         k_lo = keys[lo];
         k_hi = keys[hi];

         // if difference between lo and hi is 1, either lo and hi bracket the key
         // or hi or lo is equal to the key
         if ( ( hi - lo ) == 1 )
         {
            // if lo and hi bracket the key, exit while loop now
            if (
               ( KEY_ORDER_FUNCTION( k_lo, key ) == 1 )
               &&
               ( KEY_ORDER_FUNCTION( key, k_hi ) == 1 )
            )
            {
               break;
            }
            // otherwise hi is the key, exit the loop
            else //  if ( KEY_EQUAL_FUNCTION( k_hi, key ) == 1 )
            {
               result = 1;
               *next = (*node).children[hi];
               *index = hi;
               break;
            }
         }

         // get the midpoint index
         m = lo + ( ( hi - lo ) >> 1 );

         // get the midpoint value
         k = keys[m];

         // compare key at midpoint to searched for key
         if ( KEY_EQUAL_FUNCTION( k, key ) == 1 )
         {
            result = 1;
            *next = (*node).children[m];
            *index = m;
            break;
         }

         // move lo up to m or hi down to m
         if ( KEY_ORDER_FUNCTION( k, key ) == 1 )
         {
            lo = m;
         }
         else
         {
            hi = m;
         }

      }

      // if we exited the while loop without finding the key, return child for key between lo and hi
      if ( result == 0 )
      {
         *next = (*node).children[hi];
         *index = hi;
      }

   }

   return result;
}

/**
   node_rightmost_child

   get the rightmost child of node

   @param node the current node
   @return the rightmost child node of node
*/
static
node_t *
node_rightmost_child( node_t *node )
{
   node_t *result = NULL;
   node_t *next = NULL;

   result = node;
   next = (*result).children[ (*result).n ];

   while( next != NULL )
   {
      result = next;
      next = (*result).children[ (*result).n ];
   }

   return result;
}

/**
   node_index_of_child

   get the index of the child of the node

   @param node the current node
   @param child the child of the node
   @return the child's index
*/
static
int32_t
node_index_of_child( node_t *node, node_t *child )
{
   int32_t result = -1;
   int32_t i = 0;

   for ( i = 0; i <= (*node).n; i++ )
   {
      if ( (*node).children[i] == child )
      {
         result = i;
         break;
      }
   }

   return result;
}

/**
   has

   Return 1 if btree has an item for key, 0 if not

   @param current tree instance
   @param key the key to query for
   @return 1 if key found, 0 otherwise
*/

static
int32_t
has( BTree_kv_type( Prefix ) *current, Key key )
{
   int32_t result = 0;
   int32_t index = 0;
   node_t *node = NULL;
   node_t *next = NULL;

   // get root node
   node = (*current).root;

   // travel through b tree to see if key is present
   while ( ( node != NULL ) && ( result == 0 ) )
   {
      result = node_in_node( node, key, &next, &index );
      node = next;
   }

   return result;
}

/**
   item

   Return value if tree has an item for key, 0 if not

   @param current tree instance
   @param key the key to query for
   @return value if key found, VALUE_DEFAULT_VALUE otherwise
*/

static
Type
item( BTree_kv_type( Prefix ) *current, Key key )
{
   Type result = VALUE_DEFAULT_VALUE;
   int32_t flag = 0;
   int32_t index = 0;
   node_t *node = NULL;
   node_t *n = NULL;
   node_t *next = NULL;

   // get root node
   node = (*current).root;

   // travel through b tree to see if key is present
   while ( ( node != NULL ) && ( flag == 0 ) )
   {
      flag = node_in_node( node, key, &next, &index );
      n = node;
      node = next;
   }

   if ( flag == 1 )
   {
      result = (*n).values[ index ];
   }

   return result;
}

/**
   insert_value

   insert a new key-value pair into the tree

   @param current tree instance
   @param node the current node
   @param index the current index
   @param child what will be the child of the newly inserted key-value pair
   @param value the value to insert
   @param key the key to insert
*/
static
void
insert_value
(
   BTree_kv_type( Prefix ) *current,
   node_t *node,
   int32_t index,
   node_t *child,
   Type value,
   Key key
)
{
   PRECONDITION( "index not negative", index >= 0 );

   node_t *new_node = NULL;
   node_t *n = NULL;
   node_t *new_root = NULL;
   node_t *parent = NULL;
   int32_t split_index = 0;
   Key split_key = KEY_DEFAULT_VALUE;
   Type split_value = VALUE_DEFAULT_VALUE;
   int32_t flag = 0;
   int32_t i = 0;
   int32_t n1 = 0;
   int32_t n2 = 0;

   // case of empty tree
   if ( (*current).root == NULL )
   {
      new_node = node_make( (*current).max_n_keys );
      ( *new_node ).keys[0] = key;
      ( *new_node ).values[0] = value;
      ( *new_node ).n = 1;
      (*current).root = new_node;
   }
   // case where node is not full
   else if ( (*node).n < (*current).max_n_keys )
   {
      if ( index < (*node).n )
      {
         // shift keys, values, children to right
         memmove( &( (*node).keys[index + 1] ), &( (*node).keys[index] ), ( (*node).n - index )*sizeof( Key ) );
         memmove( &( (*node).values[index + 1] ), &( (*node).values[index] ), ( (*node).n - index )*sizeof( Type ) );
         memmove( &( (*node).children[index + 1] ), &( (*node).children[index] ), ( (*node).n + 1 - index )*sizeof( node_t * ) );
      }

      // put in new key, value, child pointer
      (*node).keys[index] = key;
      (*node).values[index] = value;
      (*node).children[index + 1] = child;

      // increment key count in node
      (*node).n = (*node).n + 1;
   }

   // case where node is full, have to split
   else
   {
      // insert new value into node, exceeding its max count until we split it in the next section
      if ( index < (*node).n )
      {
         // shift keys, values, children to right
         memmove( &( (*node).keys[index + 1] ), &( (*node).keys[index] ), ( (*node).n - index )*sizeof( Key ) );
         memmove( &( (*node).values[index + 1] ), &( (*node).values[index] ), ( (*node).n - index )*sizeof( Type ) );
         memmove( &( (*node).children[index + 1] ), &( (*node).children[index] ), ( (*node).n + 1 - index )*sizeof( node_t * ) );
      }

      // put in new key, value, child pointer
      (*node).keys[index] = key;
      (*node).values[index] = value;
      (*node).children[index + 1] = child;
      (*node).n = (*node).n + 1;

      // split node

      // get new node
      new_node = node_make( (*current).max_n_keys );

      // get count of to-be-split node and new node
      n1 = (*node).n / 2;
      n2 = (*node).n - n1 - 1;

      // get index of splitting key
      split_index =  n1;
      split_key = (*node).keys[split_index];
      split_value = (*node).values[split_index];

      // put keys, values, and children pointers into new node
      for( i = split_index + 1; i < (*node).n; i++ )
      {
         ( *new_node ).keys[i - split_index - 1] = (*node).keys[i];
         ( *new_node ).values[i - split_index - 1] = (*node).values[i];
         ( *new_node ).children[i - split_index - 1] = (*node).children[i];

         (*node).keys[i - 1] = KEY_DEFAULT_VALUE;
         (*node).values[i - 1] = VALUE_DEFAULT_VALUE;
         (*node).children[i] = NULL;
      }
      ( *new_node ).children[i - split_index - 1] = (*node).children[i];
      (*node).keys[i - 1] = KEY_DEFAULT_VALUE;
      (*node).values[i - 1] = VALUE_DEFAULT_VALUE;
      (*node).children[i] = NULL;

      // set new key counts in nodes
      (*node).n = n1;
      ( *new_node ).n = n2;

      // set parent pointers in children of new_node
      for ( i = 0; i <= ( *new_node ).n; i++ )
      {
         if ( ( *new_node ).children[i] != NULL )
         {
            ( *( *new_node ).children[i] ).parent = new_node;
         }
      }

      ( *new_node ).parent = (*node).parent;

      // get index in parent of node and insert key at split into parent
      parent = (*node).parent;
      if ( parent != NULL )
      {
         flag = node_in_node( parent, split_key, &n, &i );
         insert_value( current, parent, i, new_node, split_value, split_key );

         // correct item count in current
         (*current).count = (*current).count - 1;

      }
      // parent doesn't exist, need new root node
      else
      {
         // get new root node
         new_root = node_make( (*current).max_n_keys );

         // put split key, value, and children into new root
         ( *new_root ).keys[0] = split_key;
         ( *new_root ).values[0] = split_value;
         ( *new_root ).children[0] = node;
         ( *new_root ).children[1] = new_node;
         ( *new_root ).n = 1;
         (*current).root = new_root;

         (*node).parent = new_root;
         ( *new_node ).parent = new_root;

      }

   }

   // increment count of keys in current
   (*current).count = (*current).count + 1;

   return;
}

/**
   put

   replace value for key in the tree, or if not present, insert key-value pair

   @param current tree instance
   @param key the key to
   @param value the value to insert
*/
static
void
put( BTree_kv_type( Prefix ) *current, Type value, Key key )
{
   node_t *node = NULL;
   node_t *next = NULL;
   node_t *last = NULL;
   int32_t flag = 0;
   int32_t index = 0;

   // get root node
   node = (*current).root;

   // look through node for key
   while ( node != NULL )
   {
      flag = node_in_node( node, key, &next, &index );
      if ( flag == 1 )
      {
         break;
      }
      last = node;
      node = next;
   }

   // found existing entry with this key, replace the value
   if ( flag == 1 )
   {
      (*node).values[index] = value;
   }

   // otherwise let's insert the new value
   else
   {
      insert_value( current, last, index, NULL, value, key );
   }

   return;
}

/**
   put_and_dispose

   replace value for key in the tree, or if not present, insert key-value pair
   and dispose of the previous key and value

   @param current tree instance
   @param key the key to
   @param value the value to insert
*/
static
void
put_and_dispose( BTree_kv_type( Prefix ) *current, Type value, Key key )
{
   node_t *node = NULL;
   node_t *next = NULL;
   node_t *last = NULL;
   int32_t flag = 0;
   int32_t index = 0;

   // get root node
   node = (*current).root;

   // look through node for key
   while ( node != NULL )
   {
      flag = node_in_node( node, key, &next, &index );
      if ( flag == 1 )
      {
         break;
      }
      last = node;
      node = next;
   }

   // found existing entry with this key, replace the value
   if ( flag == 1 )
   {
      // dispose of previous key and value
      KEY_DISPOSE_FUNCTION( (*node).keys[index] );
      VALUE_DISPOSE_FUNCTION( (*node).values[index] );

      (*node).keys[index] = key;
      (*node).values[index] = value;
   }

   // otherwise let's insert the new value
   else
   {
      insert_value( current, last, index, NULL, value, key );
   }

   return;
}

/**
   keys_as_array

   put the keys into an array in order

   @param current the tree
   @return array of keys, last element of array is 0 or NULL
*/
static
Key *
keys_as_array( BTree_kv_type( Prefix ) *current )
{
   Key *result = NULL;
   int32_t i_result = 0;
   BTree_kv_cursor_type( Prefix ) *cursor = NULL;

   result = ( Key * ) calloc( (*current).count + 1, sizeof( Key ) );
   CHECK( "result allocated correctly", result != NULL );

   cursor = cursor_make( current );

   cursor_start( cursor );

   while( cursor_off( cursor ) == 0 )
   {
      result[i_result] = ( *(*cursor).item ).keys[ (*cursor).indices[ (*cursor).i_indices ] ];
      i_result = i_result + 1;
      cursor_forth( cursor );
   }

   cursor_dispose( &cursor );

   return result;
}

/**
   values_as_array

   put the values into an array in order

   @param current the tree
   @return array of values, last element of array is 0 or NULL
*/
static
Type *
values_as_array( BTree_kv_type( Prefix ) *current )
{
   Type *result = NULL;
   int32_t i_result = 0;
   BTree_kv_cursor_type( Prefix ) *cursor = NULL;

   result = ( Key * ) calloc( (*current).count + 1, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   cursor = cursor_make( current );

   cursor_start( cursor );

   while( cursor_off( cursor ) == 0 )
   {
      result[i_result] = ( *(*cursor).item ).values[ (*cursor).indices[ (*cursor).i_indices ] ];
      i_result = i_result + 1;
      cursor_forth( cursor );
   }

   cursor_dispose( &cursor );

   return result;
}

/**
   nodes_as_array

   put the nodes into an array in order

   @param current the tree
   @return array of nodes, last element of array is 0 or NULL
*/

static
node_t **
nodes_as_array( BTree_kv_type( Prefix ) *current )
{
   node_t **result = NULL;
   int32_t i_result = 0;
   int32_t n_result = 0;
   BTree_kv_cursor_type( Prefix ) *cursor = NULL;

   if ( (*current).count == 0 )
   {
      result = ( node_t ** ) calloc( 1, sizeof( node_t * ) );
      CHECK( "result allocated correctly", result != NULL );

      n_result = 1;
   }
   else
   {
      result = ( node_t ** ) calloc( (*current).min_n_keys, sizeof( node_t * ) );
      CHECK( "result allocated correctly", result != NULL );

      n_result = (*current).min_n_keys;
   }

   if ( (*current).root != NULL )
   {
      cursor = cursor_make( current );

      cursor_start( cursor );

      while( cursor_off( cursor ) == 0 )
      {
         // increase space for result if necessary, leave space for
         // final NULL pointer in result
         if ( i_result >= n_result - 2 )
         {
            result = ( node_t ** ) realloc( result, 2 * n_result * sizeof( node_t * ) );
            CHECK( "result allocated correctly", result != NULL );

            n_result = 2 * n_result;
         }

         // if current index in cursor is zero, put node into result array
         if ( (*cursor).indices[ (*cursor).i_indices ] == 0 )
         {
            result[i_result] = (*cursor).item;
            i_result = i_result + 1;
         }

         cursor_forth( cursor );
      }

      cursor_dispose( &cursor );
   }

   // last entry in result is NULL
   result[i_result] = NULL;

   return result;
}

/**
   rotate_left

   tree balancing operation: rotate left

   @param current the tree
   @param parent the parent node for the rotation
   @param index the index of the parent item
   @param left the left node for the rotation
   @param right the right node for the rotation
*/
static
void
rotate_left
(
   BTree_kv_type( Prefix ) *current,
   node_t *parent,
   int32_t index,
   node_t *left,
   node_t *right
)
{
   PRECONDITION( "index not negative", index >= 0 );

   int32_t n_left = 0;
   int32_t n_right = 0;
   Key key = KEY_DEFAULT_VALUE;

   // parent key/value becomes rightmost key/value of left child
   n_left = (*left).n;
   (*left).keys[n_left] = (*parent).keys[index];
   (*left).values[n_left] = (*parent).values[index];

   // new child on left node from right node
   (*left).children[n_left + 1] = (*right).children[0];
   if ( (*left).children[n_left + 1] != NULL )
   {
      ( *(*left).children[n_left + 1] ).parent = left;
   }

   // increment count of left node
   (*left).n = (*left).n + 1;

   // take leftmost key of right child, overwrite parent, parent key count doesn't change
   (*parent).keys[index] = (*right).keys[0];
   (*parent).values[index] = (*right).values[0];

   // shift keys, values, children to left in right child
   n_right = (*right).n;
   key = (*right).keys[0];
   memmove( &( (*right).keys[0] ), &( (*right).keys[1] ), ( n_right )*sizeof( Key ) );
   memmove( &( (*right).values[0] ), &( (*right).values[1] ), ( n_right )*sizeof( Type ) );
   memmove( &( (*right).children[0] ), &( (*right).children[1] ), ( n_right + 1 )*sizeof( node_t * ) );
   (*right).n = (*right).n - 1;

   return;
}

/**
   rotate_right

   tree balancing operation: rotate right

   @param current the tree
   @param parent the parent node for the rotation
   @param index the index of the parent item
   @param left the left node for the rotation
   @param right the right node for the rotation
*/
static
void
rotate_right
(
   BTree_kv_type( Prefix ) *current,
   node_t *parent,
   int32_t index,
   node_t *left,
   node_t *right
)
{
   PRECONDITION( "index not negative", index >= 0 );

   int32_t n_left = 0;
   int32_t n_right = 0;
   Key key = KEY_DEFAULT_VALUE;

   // move right child keys/values/child pointers to right, increment count
   n_right = (*right).n;
   memmove( &( (*right).keys[1] ), &( (*right).keys[0] ), ( n_right )*sizeof( Key ) );
   memmove( &( (*right).values[1] ), &( (*right).values[0] ), ( n_right )*sizeof( Type ) );
   memmove( &( (*right).children[1] ), &( (*right).children[0] ), ( n_right + 1 )*sizeof( node_t * ) );

   // parent key/value becomes leftmost key/value of right child
   (*right).keys[0] = (*parent).keys[index - 1];
   (*right).values[0] = (*parent).values[index - 1];

   // new child on right node from left node
   (*right).children[0] = (*left).children[ (*left).n ];
   if ( (*right).children[0] != NULL )
   {
      ( *(*right).children[0] ).parent = right;
   }

   // increment count of right node
   (*right).n = (*right).n + 1;

   // take rightmost key of left child, overwrite parent, parent key count doesn't change
   n_left = (*left).n - 1;
   (*parent).keys[index - 1 ] = (*left).keys[n_left];
   (*parent).values[index - 1 ] = (*left).values[n_left];
   key = (*left).keys[n_left];
   (*left).keys[n_left] = KEY_DEFAULT_VALUE;
   (*left).values[n_left] = VALUE_DEFAULT_VALUE;
   (*left).children[n_left + 1] = NULL;

   // decrement count of keys in left child
   (*left).n = (*left).n - 1;

   return;
}

/**
   merge

   tree balancing operation: merge nodes

   @param current the tree
   @param parent the parent node for the rotation
   @param index the index of the parent item
   @param left the left node for the rotation
   @param right the right node for the rotation
*/
static
void
merge
(
   BTree_kv_type( Prefix ) *current,
   node_t *parent,
   int32_t index,
   node_t *left,
   node_t *right
)
{
   PRECONDITION( "index not negative", index >= 0 );

   int32_t n_left = 0;
   int32_t n_right = 0;
   int32_t n = 0;
   node_t *next = NULL;
   int32_t i = 0;
   int32_t flag = 0;
   Key k = KEY_DEFAULT_VALUE;
   Type v = VALUE_DEFAULT_VALUE;

   // special "merge" for case when right is empty
   if ( (*right).n == 0 )
   {
      k = (*parent).keys[index];
      v = (*parent).values[index];

      // eliminate parent key/value/child pointer entry
      n = (*parent).n - index;
      memmove( &( (*parent).keys[index] ), &( (*parent).keys[index + 1] ), ( n )*sizeof( Key ) );
      memmove( &( (*parent).values[index] ), &( (*parent).values[index + 1] ), ( n )*sizeof( Type ) );
      memmove( &( (*parent).children[index + 1] ), &( (*parent).children[index + 2] ), ( n )*sizeof( node_t * ) );
      (*parent).n = (*parent).n - 1;

      // delete empty right child
      node_dispose( &right );

      // if parent is now empty, make left node the new parent
      if ( (*parent).n == 0 )
      {
         (*left).parent = (*parent).parent;

         // if the new parent is the root, set it in current
         if ( (*left).parent == NULL )
         {
            (*current).root = left;
         }
         else
         {
            // find index in node's parent of rightmost key
            flag = node_in_node( (*left).parent, (*left).keys[ (*left).n - 1 ], &next, &i );

            // set child pointer to left in new parent
            ( *(*left).parent ).children[ i ] = left;
         }

         // dispose of now-empty old parent
         node_dispose( &parent );
      }

      // adjust size of btree
      (*current).count = (*current).count - 1;

      // insert the key-value from parent
      put( current, v, k );

   }
   else if ( (*left).n == 0 )
   {
      k = (*parent).keys[index];
      v = (*parent).values[index];

      // eliminate parent key/value/child pointer entry
      n = (*parent).n - index;
      memmove( &( (*parent).keys[index] ), &( (*parent).keys[index + 1] ), ( n )*sizeof( Key ) );
      memmove( &( (*parent).values[index] ), &( (*parent).values[index + 1] ), ( n )*sizeof( Type ) );
      memmove( &( (*parent).children[index] ), &( (*parent).children[index + 1] ), ( n + 1 )*sizeof( node_t * ) );
      (*parent).n = (*parent).n - 1;

      // delete empty left child
      node_dispose( &left );

      // if parent is now empty, make right node the new parent
      if ( (*parent).n == 0 )
      {
         (*right).parent = (*parent).parent;

         // if the new parent is the root, set it in current
         if ( (*right).parent == NULL )
         {
            (*current).root = right;
         }
         else
         {
            // find index in node's parent of rightmost key
            flag = node_in_node( (*right).parent, (*right).keys[ (*right).n - 1 ], &next, &i );

            // set child pointer to left in new parent
            ( *(*right).parent ).children[ i ] = right;
         }

         // dispose of now-empty old parent
         node_dispose( &parent );
      }

      // adjust size of btree
      (*current).count = (*current).count - 1;

      // insert the key-value from parent
      put( current, v, k );

   }
   else
   {

      // put parent key/value as new rightmost of left child
      n_left = (*left).n;
      (*left).keys[n_left] = (*parent).keys[index];
      (*left).values[n_left] = (*parent).values[index];

      if ( (*left).children[n_left] != NULL )
      {
         ( *(*left).children[n_left] ).parent = left;
      }

      (*left).n = (*left).n + 1;
      n_left = n_left + 1;

      // move right child keys/values/child pointers to left child, adjust count
      n_right = (*right).n;
      memmove( &( (*left).keys[n_left] ), &( (*right).keys[0] ), ( n_right )*sizeof( Key ) );
      memmove( &( (*left).values[n_left] ), &( (*right).values[0] ), ( n_right )*sizeof( Type ) );
      memmove( &( (*left).children[n_left] ), &( (*right).children[0] ), ( n_right + 1 )*sizeof( node_t * ) );

      (*left).n = (*left).n + (*right).n;
      (*right).n = 0;

      for ( i = n_left; i <= (*left).n; i++ )
      {
         if ( (*left).children[i] != NULL )
         {
            ( *(*left).children[i] ).parent = left;
         }
      }

      // eliminate parent key/value/child pointer entry
      n = (*parent).n - index;
      memmove( &( (*parent).keys[index] ), &( (*parent).keys[index + 1] ), ( n )*sizeof( Key ) );
      memmove( &( (*parent).values[index] ), &( (*parent).values[index + 1] ), ( n )*sizeof( Type ) );
      memmove( &( (*parent).children[index + 1] ), &( (*parent).children[index + 2] ), ( n )*sizeof( node_t * ) );
      (*parent).n = (*parent).n - 1;

      // delete empty right child
      node_dispose( &right );

      // if parent is now empty, make just-merged node the new parent
      if ( (*parent).n == 0 )
      {
         (*left).parent = (*parent).parent;

         // if the new parent is the root, set it in current
         if ( (*left).parent == NULL )
         {
            (*current).root = left;
         }

         // dispose of now-empty old parent
         node_dispose( &parent );
      }
      // otherwise if parent is now deficient, rebalance it
      else if ( (*parent).n < (*current).min_n_keys )
      {
         rebalance( current, parent, KEY_DEFAULT_VALUE );
      }

   }

   return;
}

/**
   rebalance

   tree rebalance operation

   @param current the tree
   @param node the current node
   @param last_key the last key in the rebalance operation
*/
static
void
rebalance( BTree_kv_type( Prefix ) *current, node_t *node, Key last_key )
{
   node_t *parent = NULL;
   node_t *right = NULL;
   node_t *left = NULL;
   node_t *next = NULL;
   int32_t index = 0;
   int32_t flag = 0;
   Key key = KEY_DEFAULT_VALUE;

   parent = (*node).parent;

   // do not rebalance root node
   if ( parent != NULL )
   {
      // get rightmost key in node
      if ( (*node).n > 0 )
      {
         key = (*node).keys[ (*node).n - 1 ];
      }
      else
      {
         key = last_key;
      }

      // find index in node's parent of key
      flag = node_in_node( parent, key, &next, &index );

      if ( index == 0 )
      {
         // get right sibling of node
         right = (*parent).children[ index + 1];

         // get left sibling of node
         left = NULL;
      }
      else if ( index < (*parent).n )
      {
         // get right sibling of node
         right = (*parent).children[ index + 1];

         // get left sibling of node
         left = (*parent).children[ index ];
      }
      else // if ( index == (*parent).n )
      {
         // get right sibling of node
         right = NULL;

         // get left sibling of node
         left = (*parent).children[ index - 1 ];
      }

      flag = 0;

      // if right sibling has items to spare, put one in node
      if ( ( flag == 0 ) && ( right != NULL ) && ( (*node).n > 0 ) )
      {
         if ( (*right).n > (*current).min_n_keys )
         {
            rotate_left( current, parent, index, node, right );
            flag = 1;
         }
      }

      // if left sibling has items to spare, put one in node
      if ( ( flag == 0 ) && ( left != NULL ) && ( (*node).n > 0 ) )
      {
         if ( (*left).n > (*current). min_n_keys )
         {
            rotate_right( current, parent, index, left, node );
            flag = 1;
         }
      }

      // otherwise merge the node and the right sibling node into the node
      if ( flag == 0 )
      {
         if ( ( left == NULL ) && ( right != NULL ) )
         {
            if ( right != node )
            {
               merge( current, parent, index, node, right );
            }
         }
         else if ( ( left != NULL ) && ( right == NULL ) )
         {
            if ( left != node )
            {
               merge( current, parent, index - 1, left, node );
            }
         }
         else if ( ( left != NULL ) && ( right != NULL ) )
         {
            merge( current, parent, index, left, right );
         }
      }
   }

   return;
}

/**
   removE

   spelled with an ending capital E to avoid name clash with remove() from <stdio.h>

   remove a key-value pair from the tree

   @param current the tree
   @param key the key to remove
*/
static
void
removE( BTree_kv_type( Prefix ) *current, Key key )
{
   node_t *node = NULL;
   node_t *next = NULL;
   node_t *left = NULL;
   node_t *right = NULL;
   node_t *child = NULL;
   int32_t flag = 0;
   int32_t index = 0;
   int32_t n_child = 0;
   int32_t n = 0;
   int32_t i = 0;
   Key key1 = KEY_DEFAULT_VALUE;

   // get root node
   node = (*current).root;

   // look through node for key
   while ( node != NULL )
   {
      flag = node_in_node( node, key, &next, &index );
      if ( flag == 1 )
      {
         break;
      }
      node = next;
   }

   // found entry with this key, remove the key/value
   if ( flag == 1 )
   {
      // get left and right children
      left = (*node).children[index];
      right = (*node).children[index + 1];

      // if no children, just overwrite the key/value found
      if ( ( left == NULL ) && ( right == NULL ) )
      {
         n = (*node).n - index;
         memmove( &( (*node).keys[index] ), &( (*node).keys[index + 1] ), ( n )*sizeof( Key ) );
         memmove( &( (*node).values[index] ), &( (*node).values[index + 1] ), ( n )*sizeof( Type ) );
         memmove( &( (*node).children[index] ), &( (*node).children[index + 1] ), ( n + 1 )*sizeof( node_t * ) );
         (*node).n = (*node).n - 1;

         // if node is now deficient, rebalance it
         if ( (*node).n < (*current).min_n_keys )
         {
            rebalance( current, node, key );
         }
      }
      // case where both children exist
      else if ( ( left != NULL ) && ( right != NULL ) )
      {
         // put rightmost item from left child to overwrite parent
         child = node_rightmost_child( left );
         n_child = (*child).n;

         key1 = (*child).keys[n_child - 1];

         (*node).keys[index] = (*child).keys[n_child - 1];
         (*node).values[index] = (*child).values[n_child - 1];
         (*child).n = (*child).n - 1;
         (*child).keys[n_child - 1] = KEY_DEFAULT_VALUE;
         (*child).values[n_child - 1] = VALUE_DEFAULT_VALUE;
         (*child).children[n_child] = NULL;

         // merge child if now empty
         if ( (*child).n == 0 )
         {
            i = node_index_of_child( (*child).parent, child );
            if ( i < ( *(*child).parent ).n )
            {
               merge
               (
                  current,
                  (*child).parent,
                  i,
                  child,
                  ( *(*child).parent ).children[ ( *(*child).parent ).n ]
               );
            }
            else
            {
               merge
               (
                  current,
                  (*child).parent,
                  i - 1,
                  ( *(*child).parent ).children[ ( *(*child).parent ).n - 1],
                  child
               );
            }
         }

         // rebalance child if now deficient
         else if ( (*child).n < (*current).min_n_keys )
         {
            rebalance( current, child, key1 );
         }

      }

      // decrease tree count
      (*current).count = (*current).count - 1;
   }

   // if current is empty, remove the root node if it exists
   if ( (*current).count == 0 )
   {
      if ( (*current).root != NULL )
      {
         node_dispose( &(*current).root );
         (*current).root = NULL;
      }
   }

   return;
}

/**
   remove_and_dispose

   remove a key-value pair from the tree and dispose of them

   @param current the tree
   @param key the key to remove
*/
static
void
remove_and_dispose( BTree_kv_type( Prefix ) *current, Key key )
{
   node_t *node = NULL;
   node_t *next = NULL;
   node_t *left = NULL;
   node_t *right = NULL;
   node_t *child = NULL;
   int32_t flag = 0;
   int32_t index = 0;
   int32_t n_child = 0;
   int32_t n = 0;
   int32_t i = 0;
   Key k = KEY_DEFAULT_VALUE;
   Type v = VALUE_DEFAULT_VALUE;

   // get root node
   node = (*current).root;

   // look through node for key
   while ( node != NULL )
   {
      flag = node_in_node( node, key, &next, &index );
      if ( flag == 1 )
      {
         break;
      }
      node = next;
   }

   // found entry with this key, remove the key/value
   if ( flag == 1 )
   {
      // get left and right children
      left = (*node).children[index];
      right = (*node).children[index + 1];

      // if no children, just overwrite the key/value found
      if ( ( left == NULL ) && ( right == NULL ) )
      {
         k = (*node).keys[index];
         v = (*node).values[index];

         n = (*node).n - index;
         memmove( &( (*node).keys[index] ), &( (*node).keys[index + 1] ), ( n )*sizeof( Key ) );
         memmove( &( (*node).values[index] ), &( (*node).values[index + 1] ), ( n )*sizeof( Type ) );
         memmove( &( (*node).children[index] ), &( (*node).children[index + 1] ), ( n + 1 )*sizeof( node_t * ) );
         (*node).n = (*node).n - 1;

         // if node is now deficient, rebalance it
         if ( (*node).n < (*current).min_n_keys )
         {
            rebalance( current, node, k );
         }

         KEY_DISPOSE_FUNCTION( k );
         VALUE_DISPOSE_FUNCTION( v );
      }
      // case where both children exist
      else if ( ( left != NULL ) && ( right != NULL ) )
      {
         // put rightmost item from left child to overwrite parent
         child = node_rightmost_child( left );
         n_child = (*child).n;

         k = (*node).keys[index];
         v = (*node).values[index];

         (*node).keys[index] = (*child).keys[n_child - 1];
         (*node).values[index] = (*child).values[n_child - 1];
         (*child).n = (*child).n - 1;
         (*child).keys[n_child - 1] = KEY_DEFAULT_VALUE;
         (*child).values[n_child - 1] = VALUE_DEFAULT_VALUE;
         (*child).children[n_child] = NULL;

         // merge child if now empty
         if ( (*child).n == 0 )
         {
            i = node_index_of_child( (*child).parent, child );
            if ( i < ( *(*child).parent ).n )
            {
               merge
               (
                  current,
                  (*child).parent,
                  i,
                  child,
                  ( *(*child).parent ).children[ ( *(*child).parent ).n ]
               );
            }
            else
            {
               merge
               (
                  current,
                  (*child).parent,
                  i - 1,
                  ( *(*child).parent ).children[ ( *(*child).parent ).n - 1],
                  child
               );
            }
         }

         // rebalance child if now deficient
         else if ( (*child).n < (*current).min_n_keys )
         {
            rebalance( current, child, k );
         }

         KEY_DISPOSE_FUNCTION( k );
         VALUE_DISPOSE_FUNCTION( v );
      }

      // decrease tree count
      (*current).count = (*current).count - 1;
   }

   // if current is empty, remove the root node if it exists
   if ( (*current).count == 0 )
   {
      if ( (*current).root != NULL )
      {
         node_dispose( &(*current).root );
         (*current).root = NULL;
      }
   }
   return;
}

/**
   height

   get the height of the tree

   @param current the tree
   @return the height of the tree
*/
static
int
height( BTree_kv_type( Prefix ) *current )
{
   int32_t result = 0;
   BTree_kv_cursor_type( Prefix ) *cursor = NULL;

   cursor = cursor_make( current );

   cursor_start( cursor );

   while( cursor_off( cursor ) == 0 )
   {
      if ( result < (*cursor).i_indices )
      {
         result = (*cursor).i_indices;
      }
      cursor_forth( cursor );
   }

   if ( (*current).root != NULL )
   {
      result = result + 1;
   }

   cursor_dispose( &cursor );

   return result;
}

/**
   count

   get the number of items in the tree

   @param current the tree
   @return the number of items in the tree
*/
static
int
count( BTree_kv_type( Prefix ) *current )
{
   int32_t result = 0;
   BTree_kv_cursor_type( Prefix ) *cursor = NULL;

   cursor = cursor_make( current );

   cursor_start( cursor );

   while( cursor_off( cursor ) == 0 )
   {
      result = result + 1;
      cursor_forth( cursor );
   }

   cursor_dispose( &cursor );

   return result;
}

/**
   btree cursor functions - start, item, forth, off

   The following routines depend on the fact that the btree
   is (already) in order and that the recursion keeps track
   of each node's parent (in the btree structure).
*/

/**
   cursor_make
*/
static
BTree_kv_cursor_type( Prefix ) *
cursor_make( BTree_kv_type( Prefix ) *current )
{
   // allocate cursor struct
   BTree_kv_cursor_type( Prefix ) *cursor
      =  ( BTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BTree_kv_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set current
   (*cursor).btree = current;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // allocate indices, set to 0
   (*cursor).indices = ( int32_t * ) calloc( BTREE_CURSOR_MIN_INDICES, sizeof( int32_t ) );
   CHECK( "(*cursnr).indices allocated correctly", (*cursor).indices != NULL );

   (*cursor).n_indices = BTREE_CURSOR_MIN_INDICES;
   (*cursor).i_indices = 0;

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

   MULTITHREAD_MUTEX_INIT( (*cursor).mutex );

   return cursor;
}

/**
   cursor_dispose
*/
static
void
cursor_dispose( BTree_kv_cursor_type( Prefix ) **cursor )
{
   BTree_kv_type( Prefix ) *btree = (**cursor).btree;

   BTree_kv_cursor_type( Prefix ) *c1 = NULL;
   BTree_kv_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from btree structure
   c1 = ( *(**cursor).btree ).first_cursor;
   c2 = (*c1).next_cursor;

   // search through the cursors
   while ( ( c2 != NULL ) && ( flag == 0 ) )
   {
      if ( c2 == *cursor )
      {
         // if we have a match, remove "c2" from the cursor btree, set flag
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

   // set btree's last cursor
   c1 = (*btree).first_cursor;
   while ( c1 != NULL )
   {
      c2 = c1;
      c1 = (*c1).next_cursor;
   }
   (*btree).last_cursor = c2;

   // only one cursor, last_cursor is NULL
   if ( c2 == (*btree).first_cursor )
   {
      (*btree).last_cursor = NULL;
   }

   // delete cursor struct
   free( (**cursor).indices );
   free(*cursor);
   *cursor = NULL;

   return;
}

/**
   cursor_finish
*/
static
void
cursor_finish( BTree_kv_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;

   // set node from the btree root
   node = ( *(*cursor).btree ).root;
   (*cursor).i_indices = 0;
   (*cursor).indices[ (*cursor).i_indices ] = (*node).n - 1;
   (*cursor).item = node;

   cursor_down_to_rightmost_child( cursor );

   return;
}

/**
   cursor_start
*/
static
void
cursor_start( BTree_kv_cursor_type( Prefix ) *cursor )
{
   int32_t flag = 0;

   (*cursor).item = ( *(*cursor).btree ).root;
   (*cursor).indices[0] = 0;
   (*cursor).i_indices = 0;
   flag = cursor_down_to_leftmost_child( cursor );

   return;
}

/**
   cursor_key
*/
static
Key
cursor_key( BTree_kv_cursor_type( Prefix ) *cursor )
{
   // return the key for the current cursor item
   return ( *(*cursor).item ).keys[ (*cursor).indices[ (*cursor).i_indices ] ];
}

/**
   cursor_item
*/
static
Type
cursor_item( BTree_kv_cursor_type( Prefix ) *cursor )
{
   // return the value for the current cursor item
   return ( *(*cursor).item ).values[ (*cursor).indices[ (*cursor).i_indices ] ];
}


/**
   cursor_back
*/
static
void
cursor_back( BTree_kv_cursor_type( Prefix ) *cursor )
{
   int32_t flag = 0;

   // go to next item in node's array of keys/values
   (*cursor).indices[ (*cursor).i_indices ] = (*cursor).indices[ (*cursor).i_indices ] - 1;

   // go to rightmost child
   flag = cursor_down_to_rightmost_child( cursor );

   if ( flag == 0 )
   {
      // we didn't go down to a new child, see if we're past the keys/values array
      if ( (*cursor).indices[ (*cursor).i_indices ] < 0 )
      {
         cursor_up_to_prev_parent( cursor );
      }
   }

   return;
}

/**
   cursor_ensure_indices_ok
*/
void
cursor_ensure_indices_ok( BTree_kv_cursor_type( Prefix ) *cursor )
{
   // increase size of indices when next increment would fill indices
   if ( (*cursor).i_indices >= (*cursor).n_indices - 1 )
   {
      (*cursor).indices = realloc( (*cursor).indices, 2 * (*cursor).n_indices * sizeof( int32_t ) );
      CHECK( "(*cursor).indices allocated correctly", (*cursor).indices != NULL );

      (*cursor).n_indices = 2 * (*cursor).n_indices;
   }

   return;
}

/**
   cursor_down_to_leftmost_child
*/
static
int32_t
cursor_down_to_leftmost_child( BTree_kv_cursor_type( Prefix ) *cursor )
{
   int32_t result = 0;
   int32_t flag = 0;

   // cursor is at a valid item or NULL, adjust cursor if not NULL
   if ( (*cursor).item != NULL )
   {
      while( flag == 0 )
      {
         // see if child pointer is not NULL, move cursor if not NULL
         if ( ( *(*cursor).item ).children[ (*cursor).indices[ (*cursor).i_indices ] ] != NULL )
         {
            // set result to 1 indicating that we actually found a child
            result = 1;

            // ensure enough room in (*cursor).indices
            cursor_ensure_indices_ok( cursor );

            // valid item, valid child pointer, set cursor to child

            // get the next node from the children pointer
            (*cursor).item = ( *(*cursor).item ).children[ (*cursor).indices[ (*cursor).i_indices ] ];

            // increase depth of cursor indices
            (*cursor).i_indices = (*cursor).i_indices + 1;

            // first index is zero
            (*cursor).indices[ (*cursor).i_indices ] = 0;

         }
         else
         {
            // cursor child pointer is NULL, we're done
            flag = 1;
         }
      }
   }

   return result;
}

/**
   cursor_up_to_next_parent
*/
static
void
cursor_up_to_next_parent( BTree_kv_cursor_type( Prefix ) *cursor )
{
   int32_t flag = 0;

   // cursor is at a valid item or NULL, adjust cursor if not NULL
   if ( (*cursor).item != NULL )
   {
      while( flag == 0 )
      {
         // see if child pointer is not NULL, move cursor if not NULL
         if ( ( *(*cursor).item ).parent != NULL )
         {
            // valid item, valid parent pointer, set cursor to parent

            // get the parent node from the parent pointer
            (*cursor).item = ( *(*cursor).item ).parent;

            // decrease depth of cursor indices
            (*cursor).i_indices = (*cursor).i_indices - 1;

            // if the parent's (cursor item's) index is "n", go down the rightmost child pointer if non NULL
            if ( (*cursor).indices[ (*cursor).i_indices ] != ( *(*cursor).item ).n )
            {
               // valid parent found
               flag = 1;
            }
         }
         else
         {
            (*cursor).item = NULL;
            (*cursor).i_indices = (*cursor).i_indices - 1;

            // cursor child pointer is NULL, we're done
            flag = 1;
         }
      }
   }

   return;
}

/**
   cursor_down_to_rightmost_child
*/
static
int32_t
cursor_down_to_rightmost_child( BTree_kv_cursor_type( Prefix ) *cursor )
{
   int32_t result = 0;
   int32_t flag = 0;

   // cursor is at a valid item or NULL, adjust cursor if not NULL
   if ( (*cursor).item != NULL )
   {
      while( flag == 0 )
      {
         // see if child pointer is not NULL, move cursor if not NULL
         if ( ( *(*cursor).item ).children[ (*cursor).indices[ (*cursor).i_indices ] + 1 ] != NULL )
         {
            // set result to 1 indicating that we actually found a child
            result = 1;

            // ensure enough room in (*cursor).indices
            cursor_ensure_indices_ok( cursor );

            // valid item, valid child pointer, set cursor to child

            // get the next node from the children pointer
            (*cursor).item = ( *(*cursor).item ).children[ (*cursor).indices[ (*cursor).i_indices ] + 1];

            // increase depth of cursor indices
            (*cursor).i_indices = (*cursor).i_indices + 1;

            // new cursor index is last index in key/value arrau
            (*cursor).indices[ (*cursor).i_indices ] = ( *(*cursor).item ).n - 1;

         }
         else
         {
            // cursor child pointer is NULL, we're done
            flag = 1;
         }
      }
   }

   return result;
}

/**
   cursor_up_to_prev_parent
*/
static
void
cursor_up_to_prev_parent( BTree_kv_cursor_type( Prefix ) *cursor )
{
   int32_t flag = 0;

   // cursor is at a valid item or NULL, adjust cursor if not NULL
   if ( (*cursor).item != NULL )
   {
      while( flag == 0 )
      {
         // see if child pointer is not NULL, move cursor if not NULL
         if ( ( *(*cursor).item ).parent != NULL )
         {
            // valid item, valid parent pointer, set cursor to parent

            // get the parent node from the parent pointer
            (*cursor).item = ( *(*cursor).item ).parent;

            // decrease depth of cursor indices
            (*cursor).i_indices = (*cursor).i_indices - 1;

            // if the parent's (cursor item's) index is "-1", go down the leftmost child pointer if non NULL
            if ( (*cursor).indices[ (*cursor).i_indices ] != -1 )
            {
               // valid parent found
               flag = 1;
            }
         }
         else
         {
            (*cursor).item = NULL;
            (*cursor).i_indices = (*cursor).i_indices - 1;

            // cursor child pointer is NULL, we're done
            flag = 1;
         }
      }
   }

   return;
}

/**
   cursor_forth
*/
static
void
cursor_forth( BTree_kv_cursor_type( Prefix ) *cursor )
{
   int32_t flag = 0;

   // go to next item in node's array of keys/values
   (*cursor).indices[ (*cursor).i_indices ] = (*cursor).indices[ (*cursor).i_indices ] + 1;

   // go to leftmost child
   flag = cursor_down_to_leftmost_child( cursor );

   if ( flag == 0 )
   {
      // we didn't go down to a new child, see if we're past the keys/values array
      if ( (*cursor).indices[ (*cursor).i_indices ] == ( *(*cursor).item ).n )
      {
         cursor_up_to_next_parent( cursor );
      }
   }

   return;
}

/**
   cursor_off
*/
static
int32_t
cursor_off(  BTree_kv_cursor_type( Prefix ) *cursor )
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
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
is_empty_implies_root_null( BTree_kv_type( Prefix ) *current )
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
nonnegative_count( BTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).count >= 0 );

   return result;
}

static
int32_t
valid_count( BTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( count( current ) == (*current).count );

   return result;
}

static
int32_t
valid_nodes( BTree_kv_type( Prefix ) *current )
{
   int32_t result = 0;
   int32_t i = 0;
   BTree_kv_cursor_type( Prefix ) *cursor = NULL;
   node_t *node = NULL;
   int32_t flag1 = 0;
   int32_t flag2 = 0;
   int32_t flag3 = 0;
   int32_t flag4 = 0;
   int32_t f = 0;
   int32_t count = 0;
   int32_t count1 = 0;
   int32_t count2 = 0;

   result = 1;

   if ( (*current).count == 0 )
   {
      result = 1;
   }
   else
   {
      cursor = cursor_make( current );

      cursor_start( cursor );

      while( ( cursor_off( cursor ) == 0 ) && ( result == 1 ) )
      {
         node = (*cursor).item;

         flag1 = 0;

         if ( (*node).parent == NULL )
         {
            flag1 = 1;
         }
         else if ( (*node).n >= (*current).min_n_keys )
         {
            flag1 = 1;
         }

         flag2 = 0;
         if ( (*node).n <= (*current).max_n_keys )
         {
            flag2 = 1;
         }

         flag3 = 0;
         flag4 = 0;
         if ( (*node).children[0] == NULL )
         {
            count = 0;
            for ( i = 0; i < (*current).max_n_keys + 1; i++ )
            {
               if ( (*node).children[i] == NULL )
               {
                  count = count + 1;
               }
            }
            if ( count == (*current).max_n_keys + 1 )
            {
               flag3 = 1;
            }
         }
         else  //if ( (*node).children[0] != NULL )
         {
            count = 0;
            count1 = 0;
            count2 = 0;
            for ( i = 0; i < (*current).max_n_keys + 1; i++ )
            {
               if ( i <= (*node).n )
               {
                  f = ( (*node).children[i] != NULL );
                  if ( f != 0 )
                  {
                     count = count + 1;
                  }

                  f = ( *(*node).children[i] ).parent == node;
                  if ( f != 0 )
                  {
                     count1 = count1 + 1;
                  }
               }
               else // if ( i > (*node).n )
               {
                  f = ( (*node).children[i] == NULL );
                  if ( f != 0 )
                  {
                     count2 = count2 + 1;
                  }
               }
            }

            if ( ( count == ( (*node).n + 1 ) ) && ( count1 == ( (*node).n + 1 ) ) && ( count2 == (*current).max_n_keys - (*node).n ) )
            {
               flag4 = 1;
            }
         }

         result = 0;
         if ( ( flag1 == 1 ) && ( flag2 == 1 ) && ( ( flag3 == 1 ) || ( flag4 == 1 ) ) )
         {
            result = 1;
         }

         cursor_forth( cursor );
      }

      cursor_dispose( &cursor );

   }

   return result;
}

static
int32_t
first_cursor_not_null( BTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).first_cursor != NULL );

   return result;
}

static
int32_t
cursors_btree_kv_ok( BTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;

   BTree_kv_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   while( ( cursor != NULL ) && ( result == 1 ) )
   {
      result = ( (*cursor).btree == current );
      cursor = (*cursor).next_cursor;
   }

   return result;
}

static
int32_t
last_cursor_next_null( BTree_kv_type( Prefix ) *current )
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
last_cursor_null_if_one_cursor( BTree_kv_type( Prefix ) *current )
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
in_order( BTree_kv_type( Prefix ) *current )
{
   int32_t result = 1;
   node_t *n1 = NULL;
   node_t *n2 = NULL;
   int32_t i1 = 0;
   int32_t i2 = 0;
   BTree_kv_cursor_type( Prefix ) *cursor = NULL;

   if ( (*current).count > 1 )
   {
      cursor = cursor_make( current );
      cursor_start( cursor );
      n1 = (*cursor).item;
      i1 = (*cursor).indices[ (*cursor).i_indices ];
      cursor_forth( cursor );
      n2 = (*cursor).item;

      while( ( n2 != NULL ) && ( result == 1 ) )
      {
         i2 = (*cursor).indices[ (*cursor).i_indices ];

         result = KEY_ORDER_FUNCTION( (*n1).keys[i1], (*n2).keys[i2] );
         n1 = n2;
         i1 = i2;

         cursor_forth( cursor );

         n2 = (*cursor).item;
      }

      cursor_dispose( &cursor );
   }

   return result;
}


static
void invariant( BTree_kv_type( Prefix ) *current )
{
   assert( ( ( void ) "empty implies root null", is_empty_implies_root_null( current ) ) );
   assert( ( ( void ) "nonnegative count", nonnegative_count( current ) ) );
   assert( ( ( void ) "valid count", valid_count( current ) ) );
   assert( ( ( void ) "valid_nodes", valid_nodes( current ) ) );
   assert( ( ( void ) "first cursor not null", first_cursor_not_null( current ) ) );
   assert( ( ( void ) "last cursor next null", last_cursor_next_null( current ) ) );
   assert( ( ( void ) "last cursor null if one cursor", last_cursor_null_if_one_cursor( current ) ) );
   assert( ( ( void ) "cursors btree OK", cursors_btree_kv_ok( current ) ) );
   assert( ( ( void ) "btree in order", in_order( current ) ) );
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
   BTree_kv_dispose( Prefix ),
   BTree_kv_deep_dispose( Prefix ),
   BTree_kv_is_equal( Prefix ),
   BTree_kv_is_deep_equal( Prefix ),
   BTree_kv_copy( Prefix ),
   BTree_kv_deep_copy( Prefix ),
   BTree_kv_clone( Prefix ),
   BTree_kv_deep_clone( Prefix )
};

static
void *
p_iterable_kv_table[P_ITERABLE_KV_FUNCTION_COUNT]
=
{
   BTree_kv_count( Prefix ),
   BTree_kv_key_at( Prefix ),
   BTree_kv_item_at( Prefix ),
   BTree_kv_off( Prefix ),
   BTree_kv_is_empty( Prefix ),
   BTree_kv_start( Prefix ),
   BTree_kv_forth( Prefix )
};

static
void *
p_diterable_kv_table[P_DITERABLE_KV_FUNCTION_COUNT]
=
{
   BTree_kv_count( Prefix ),
   BTree_kv_key_at( Prefix ),
   BTree_kv_item_at( Prefix ),
   BTree_kv_off( Prefix ),
   BTree_kv_is_empty( Prefix ),
   BTree_kv_start( Prefix ),
   BTree_kv_forth( Prefix ),
   BTree_kv_finish( Prefix ),
   BTree_kv_back( Prefix )
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
   BTree_kv_make
*/

BTree_kv_type( Prefix ) *
BTree_kv_make( Prefix )( int32_t max_n_keys )
{
   PRECONDITION( "max_n_keys positive", max_n_keys > 0 );

   // allocate current struct
   BTree_kv_type( Prefix ) * current
      = ( BTree_kv_type( Prefix ) * ) calloc( 1, sizeof( BTree_kv_type( Prefix ) ) );
   CHECK( "current allocated correctly", current != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = BTREE_KV_TYPE;
   (*current)._key_type = Key_Code;
   (*current)._item_type = Type_Code;

   // set min and nad number of keys in node
   (*current).max_n_keys = max_n_keys;
   (*current).min_n_keys = (*current).max_n_keys / 2;

   // root is null
   (*current).root = NULL;

   // count is zero
   (*current).count = 0;

   // set built-in cursor
   // allocate cursor struct
   BTree_kv_cursor_type( Prefix ) *cursor
      =  ( BTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BTree_kv_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set current
   (*cursor).btree = current;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set indices
   (*cursor).indices = ( int32_t * ) calloc( BTREE_CURSOR_MIN_INDICES, sizeof( int32_t ) );
   CHECK( "(*cursor).indices allocated correctly", (*cursor).indices != NULL );

   (*cursor).n_indices = BTREE_CURSOR_MIN_INDICES;
   (*cursor).i_indices = 0;

   // set current built-in cursor
   (*current).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );

   return current;
}

/**
   BTree_kv_make_from_array
*/

BTree_kv_type( Prefix ) *
BTree_kv_make_from_array( Prefix )( Key *key_array, Type *value_array, int32_t count, int32_t max_n_keys )
{
   PRECONDITION( "key_array not null", key_array != NULL );
   PRECONDITION( "value_array not null", value_array != NULL );
   PRECONDITION( "max_n_keys positive", max_n_keys > 0 );
   PRECONDITION( "count  ok", count >= 0 );

   // make btree struct
   BTree_kv_type( Prefix ) *result = BTree_kv_make( Prefix )( max_n_keys );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = BTREE_KV_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   int32_t i = 0;

   for ( i = 0; i < count; i++ )
   {
      put( result, value_array[i], key_array[i] );
   }

   INVARIANT( result );

   return result;
}

/**
   BTree_kv_clone
*/

BTree_kv_type( Prefix ) *
BTree_kv_clone( Prefix )( BTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == BTREE_KV_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*other)._item_type = Type_Code ) );

   // make struct
   BTree_kv_type( Prefix ) *current = BTree_kv_make( Prefix )( (*other).max_n_keys );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = BTREE_KV_TYPE;
   (*current)._key_type = Key_Code;
   (*current)._item_type = Type_Code;

   // copy from other
   BTree_kv_cursor_type( Prefix ) *cursor = cursor_make( other );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( current, cursor_item( cursor ), cursor_key( cursor ) );
      cursor_forth( cursor );
   }

   INVARIANT( current );

   return current;
}

/**
   BTree_kv_deep_clone
*/

BTree_kv_type( Prefix ) *
BTree_kv_deep_clone( Prefix )( BTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == BTREE_KV_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*other)._item_type = Type_Code ) );

   // make other struct
   BTree_kv_type( Prefix ) *current = BTree_kv_make( Prefix )( (*other).max_n_keys );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = BTREE_KV_TYPE;
   (*current)._key_type = Key_Code;
   (*current)._item_type = Type_Code;

   // copy from other
   BTree_kv_cursor_type( Prefix ) *cursor = cursor_make( other );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( current, KEY_DUPLICATE_FUNCTION( cursor_item( cursor ) ), VALUE_DUPLICATE_FUNCTION( cursor_key( cursor ) ) );
      cursor_forth( cursor );
   }

   INVARIANT( current );

   return current;
}

/**
   BTree_kv_copy
*/

void
BTree_kv_copy( Prefix )( BTree_kv_type( Prefix ) *current, BTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == BTREE_KV_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*other)._item_type = Type_Code ) );

   int32_t i = 0;
   int32_t n = 0;
   node_t **node_array = NULL;
   Key *key_array = NULL;
   Type *value_array = NULL;

   // dispose of contents

   // get arrays
   key_array = keys_as_array( current );
   value_array = values_as_array( current );
   node_array = nodes_as_array( current );

   // dispose nodes and values
   n = (*current).count;
   for ( i = 0; i < n; i++ )
   {
      KEY_DISPOSE_FUNCTION( key_array[i] );
      VALUE_DISPOSE_FUNCTION( value_array[i] );
   }

   // dispose of nodes
   i = 0;
   while( node_array[i] != NULL )
   {
      node_dispose( &node_array[i] );
      i = i + 1;
   }

   // free arrays
   free( key_array );
   free( value_array );
   free( node_array );

   // set count to 0
   (*current).count = 0;
   (*current).root = NULL;

   // copy from other
   BTree_kv_cursor_type( Prefix ) *cursor = cursor_make( other );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( current, cursor_item( cursor ), cursor_key( cursor ) );
      cursor_forth( cursor );
   }

   cursor_dispose( &cursor );

   INVARIANT( current );

   return;
}

/**
   BTree_kv_deep_copy
*/

void
BTree_kv_deep_copy( Prefix )( BTree_kv_type( Prefix ) *current, BTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == BTREE_KV_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*other)._item_type = Type_Code ) );

   int32_t i = 0;
   int32_t n = 0;
   node_t **node_array = NULL;
   Key *key_array = NULL;
   Type *value_array = NULL;

   // dispose of contents

   // get arrays
   key_array = keys_as_array( current );
   value_array = values_as_array( current );
   node_array = nodes_as_array( current );

   // dispose nodes and values
   n = (*current).count;
   for ( i = 0; i < n; i++ )
   {
      KEY_DISPOSE_FUNCTION( key_array[i] );
      VALUE_DISPOSE_FUNCTION( value_array[i] );
   }

   // dispose of nodes
   i = 0;
   while( node_array[i] != NULL )
   {
      node_dispose( &node_array[i] );
      i = i + 1;
   }

   // free arrays
   free( key_array );
   free( value_array );
   free( node_array );


   // set count to 0
   (*current).count = 0;
   (*current).root = NULL;

   // copy from other
   BTree_kv_cursor_type( Prefix ) *cursor = cursor_make( other );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( current, KEY_DUPLICATE_FUNCTION( cursor_item( cursor ) ), VALUE_DUPLICATE_FUNCTION( cursor_key( cursor ) ) );
      cursor_forth( cursor );
   }

   cursor_dispose( &cursor );

   INVARIANT( current );

   return;
}

/**
   BTree_kv_is_equal
*/

int32_t
BTree_kv_is_equal( Prefix )( BTree_kv_type( Prefix ) *current, BTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == BTREE_KV_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*other)._item_type = Type_Code ) );

   int32_t result = 1;

   if ( (*current).count != (*other).count )
   {
      result = 0;
   }
   else
   {
      BTree_kv_cursor_type( Prefix ) *cursor = cursor_make( current );
      BTree_kv_cursor_type( Prefix ) *other_cursor = cursor_make( other );
      cursor_start( cursor );
      cursor_start( other_cursor );
      while( ( cursor_off( cursor ) == 0 ) && ( result == 1 ) )
      {
         if ( cursor_item( cursor ) != cursor_item( other_cursor ) )
         {
            result = 0;
         }

         if ( cursor_key( cursor ) != cursor_key( other_cursor ) )
         {
            result = 0;
         }

         cursor_forth( cursor );
         cursor_forth( other_cursor );
      }

      cursor_dispose( &cursor );
      cursor_dispose( &other_cursor );
   }

   INVARIANT( current );

   return result;
}

/**
   BTree_kv_is_deep_equal
*/

int32_t
BTree_kv_is_deep_equal( Prefix )( BTree_kv_type( Prefix ) *current, BTree_kv_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == BTREE_KV_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == BTREE_KV_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*other)._item_type = Type_Code ) );

   int32_t result = 1;

   if ( (*current).count != (*other).count )
   {
      result = 0;
   }
   else
   {
      BTree_kv_cursor_type( Prefix ) *cursor = cursor_make( current );
      BTree_kv_cursor_type( Prefix ) *other_cursor = cursor_make( other );
      cursor_start( cursor );
      cursor_start( other_cursor );
      while( ( cursor_off( cursor ) == 0 ) && ( result == 1 ) )
      {
         if ( VALUE_DEEP_EQUAL_FUNCTION( cursor_item( cursor ), cursor_item( other_cursor ) ) == 0 )
         {
            result = 0;
         }

         if ( KEY_DEEP_EQUAL_FUNCTION( cursor_key( cursor ), cursor_key( other_cursor ) ) == 0 )
         {
            result = 0;
         }

         cursor_forth( cursor );
         cursor_forth( other_cursor );
      }

      cursor_dispose( &cursor );
      cursor_dispose( &other_cursor );
   }

   INVARIANT( current );

   return result;
}

/**
   BTree_kv_cursor_make
*/

BTree_kv_cursor_type( Prefix ) *
BTree_kv_cursor_make( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );

   // allocate cursor struct
   BTree_kv_cursor_type( Prefix ) *cursor = cursor_make( btree );
   CHECK( "cursor allocated correctly", cursor != NULL );

   INVARIANT( btree );
   POSTCONDITION( "new cursor is last cursor", (*btree).last_cursor == cursor );
   UNLOCK( (*btree).mutex );

   return cursor;
}

/**
   BTree_kv_dispose
*/

void
BTree_kv_dispose( Prefix )( BTree_kv_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == BTREE_KV_TYPE ) && ( (**current)._key_type = Key_Code ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   int32_t i = 0;

   // get array of nodes
   node_t **array = nodes_as_array(*current);

   // delete nodes
   i = 0;
   while ( array[i] != NULL )
   {
      node_dispose( &array[i] );
      i = i + 1;
   }

   // delete array
   free( array );

   // delete cursors
   BTree_kv_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   BTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;

      // free cursor indices
      free( (*cursor).indices );

      // free cursor
      free( cursor );

      cursor = next_cursor;
   }

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   *current = NULL;

   return;
}

/**
   BTree_kv_deep_dispose
*/

void
BTree_kv_deep_dispose( Prefix )( BTree_kv_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == BTREE_KV_TYPE ) && ( (**current)._key_type = Key_Code ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   int32_t i = 0;
   int32_t n = 0;
   node_t **node_array = NULL;
   Key *key_array = NULL;
   Type *value_array = NULL;

   // get arrays
   key_array = keys_as_array(*current);
   value_array = values_as_array(*current);
   node_array = nodes_as_array(*current);

   // dispose nodes and values
   n = (**current).count;
   for ( i = 0; i < n; i++ )
   {
      KEY_DEEP_DISPOSE_FUNCTION( key_array[i] );
      VALUE_DEEP_DISPOSE_FUNCTION( value_array[i] );
   }

   // dispose of nodes
   i = 0;
   while( node_array[i] != NULL )
   {
      node_dispose( &node_array[i] );
      i = i + 1;
   }

   // free arrays
   free( key_array );
   free( value_array );
   free( node_array );

   // delete cursors
   BTree_kv_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   BTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( (*cursor).indices );
      free( cursor );
      cursor = next_cursor;
   }

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   *current = NULL;

   return;
}

/**
   BTree_kv_cursor_dispose
*/

void
BTree_kv_cursor_dispose( Prefix )( BTree_kv_cursor_type( Prefix ) **cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "*cursor not null", *cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(**cursor).btree )._type == BTREE_KV_TYPE ) && ( ( *(**cursor).btree )._key_type = Key_Code ) && ( ( *(**cursor).btree )._item_type = Type_Code ) ) );
   LOCK( (**cursor).mutex );
   LOCK( ( *(**cursor).btree ).mutex );
   INVARIANT( (**cursor).btree );

   BTree_kv_type( Prefix ) *btree = NULL;

   btree = (**cursor).btree;

   cursor_dispose( cursor );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return;
}

/**
   BTree_kv_keys_as_array

*/

Type *
BTree_kv_keys_as_array( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );

   Key *result = keys_as_array( btree );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return result;
}

/**
   BTree_kv_values_as_array

*/

Type *
BTree_kv_values_as_array( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );

   Type *result = values_as_array( btree );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return result;
}

/**
   BTree_kv_cursor_key_at
*/

Key
BTree_kv_cursor_key_at( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).btree )._type == BTREE_KV_TYPE ) && ( ( *(*cursor).btree )._key_type = Key_Code ) && ( ( *(*cursor).btree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).btree ).mutex );
   INVARIANT( (*cursor).btree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Key key = ( *(*cursor).item ).keys[ (*cursor).indices[ (*cursor).i_indices ] ];

   INVARIANT( (*cursor).btree );
   UNLOCK( ( *(*cursor).btree ).mutex );
   UNLOCK( (*cursor).mutex );

   return key;
}

/**
   BTree_kv_cursor_item_at
*/

Type
BTree_kv_cursor_item_at( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).btree )._type == BTREE_KV_TYPE ) && ( ( *(*cursor).btree )._key_type = Key_Code ) && ( ( *(*cursor).btree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).btree ).mutex );
   INVARIANT( (*cursor).btree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Type value = ( *(*cursor).item ).values[ (*cursor).indices[ (*cursor).i_indices ] ];

   INVARIANT( (*cursor).btree );
   UNLOCK( ( *(*cursor).btree ).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}


/**
   BTree_kv_item
*/

Type
BTree_kv_item( Prefix )( BTree_kv_type( Prefix ) *btree, Key key )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );

   Type value = item( btree, key );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return value;
}

/**
   BTree_kv_key_at
*/

Key
BTree_kv_key_at( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );
   PRECONDITION( "not off", ( *(*btree).first_cursor ).item != NULL );

   BTree_kv_cursor_type( Prefix ) *cursor = (*btree).first_cursor;

   Key key = ( *(*cursor).item ).keys[ (*cursor).indices[ (*cursor).i_indices ] ];

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return key;
}

/**
   BTree_kv_item_at
*/

Type
BTree_kv_item_at( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );
   PRECONDITION( "not off", ( *(*btree).first_cursor ).item != NULL );

   BTree_kv_cursor_type( Prefix ) *cursor = (*btree).first_cursor;

   Type value = ( *(*cursor).item ).values[ (*cursor).indices[ (*cursor).i_indices ] ];

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return value;
}

/**
   BTree_kv_key_at_index
*/

Type
BTree_kv_key_at_index( Prefix )( BTree_kv_type( Prefix ) *btree, int32_t index )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*btree).count ) );

   int32_t i = 0;
   Key key = KEY_DEFAULT_VALUE;
   BTree_kv_cursor_type( Prefix ) *cursor = NULL;

   cursor = (*btree).first_cursor;

   cursor_start( cursor );
   key = cursor_key( cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( cursor );
      key = ( *(*cursor).item ).keys[ (*cursor).indices[ (*cursor).i_indices ] ];
   }

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return key;
}

/**
   BTree_kv_item_at_index
*/

Type
BTree_kv_item_at_index( Prefix )( BTree_kv_type( Prefix ) *btree, int32_t index )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*btree).count ) );
   INVARIANT( btree );

   int32_t i = 0;
   Type value = VALUE_DEFAULT_VALUE;
   BTree_kv_cursor_type( Prefix ) *cursor = NULL;

   cursor = (*btree).first_cursor;

   cursor_start( cursor );
   value = cursor_item( cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( cursor );
      value = ( *(*cursor).item ).values[ (*cursor).indices[ (*cursor).i_indices ] ];
   }

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return value;
}

/**
   BTree_kv_count
*/

int32_t
BTree_kv_count( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );

   int32_t result = (*btree).count;

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return result;
}

/**
   BTree_kv_height
*/

int32_t
BTree_kv_height( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );

   int32_t result = height( btree );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return result;
}

/**
   BTree_kv_off
*/

int32_t
BTree_kv_off( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );

   int32_t result = cursor_off( (*btree).first_cursor );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return result;
}

/**
   BTree_kv_cursor_off
*/

int32_t
BTree_kv_cursor_off( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).btree )._type == BTREE_KV_TYPE ) && ( ( *(*cursor).btree )._key_type = Key_Code ) && ( ( *(*cursor).btree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   int32_t result = cursor_off( cursor );

   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   BTree_kv_is_empty
*/

int32_t
BTree_kv_is_empty( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );

   int32_t result = ( (*btree).count == 0 );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return result;
}

/**
   BTree_kv_has
*/

int32_t
BTree_kv_has( Prefix )( BTree_kv_type( Prefix ) *btree, Key key )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );

   int32_t result = has( btree, key );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return result;
}

/**
   BTree_kv_cursor_back
*/
void
BTree_kv_cursor_back( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).btree )._type == BTREE_KV_TYPE ) && ( ( *(*cursor).btree )._key_type = Key_Code ) && ( ( *(*cursor).btree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   cursor_back( cursor );

   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BTree_kv_cursor_forth
*/
void
BTree_kv_cursor_forth( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).btree )._type == BTREE_KV_TYPE ) && ( ( *(*cursor).btree )._key_type = Key_Code ) && ( ( *(*cursor).btree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   cursor_forth( cursor );

   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BTree_kv_cursor_go
*/
void
BTree_kv_cursor_go( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).btree )._type == BTREE_KV_TYPE ) && ( ( *(*cursor).btree )._key_type = Key_Code ) && ( ( *(*cursor).btree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).btree ).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < ( *(*cursor).btree ).count ) ) );
   INVARIANT( (*cursor).btree );

   int32_t i = 0;
   cursor_start( cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).btree );
   UNLOCK( ( *(*cursor).btree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BTree_kv_cursor_index
*/

int32_t
BTree_kv_cursor_index( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).btree )._type == BTREE_KV_TYPE ) && ( ( *(*cursor).btree )._key_type = Key_Code ) && ( ( *(*cursor).btree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).btree ).mutex );
   INVARIANT( (*cursor).btree );

   int32_t result = 0;
   int32_t flag = 0;
   node_t *target_node = (*cursor).item;
   int32_t target_index = 0;

   if ( target_node != NULL )
   {
      target_index = (*cursor).indices[ (*cursor).i_indices ];
   }

   if ( ( *(*cursor).btree ).count > 0 )
   {
      cursor_start( cursor );

      while ( cursor_off( cursor ) == 0 )
      {
         if ( ( (*cursor).item == target_node ) && ( (*cursor).indices[ (*cursor).i_indices ] == target_index ) )
         {
            flag = 1;
            break;
         }
         result = result + 1;
         cursor_forth( cursor );
      }
   }

   if ( flag == 0 )
   {
      result = -1;
   }

   INVARIANT( (*cursor).btree );
   UNLOCK( ( *(*cursor).btree ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   BTree_kv_cursor_finish
*/

void
BTree_kv_cursor_finish( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).btree )._type == BTREE_KV_TYPE ) && ( ( *(*cursor).btree )._key_type = Key_Code ) && ( ( *(*cursor).btree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).btree ).mutex );
   INVARIANT( (*cursor).btree );

   cursor_finish( cursor );

   INVARIANT( (*cursor).btree );
   UNLOCK( ( *(*cursor).btree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BTree_kv_cursor_start
*/

void
BTree_kv_cursor_start( Prefix )( BTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).btree )._type == BTREE_KV_TYPE ) && ( ( *(*cursor).btree )._key_type = Key_Code ) && ( ( *(*cursor).btree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).btree ).mutex );
   INVARIANT( (*cursor).btree );

   cursor_start( cursor );

   INVARIANT( (*cursor).btree );
   UNLOCK( ( *(*cursor).btree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BTree_kv_back
*/
void
BTree_kv_back( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   PRECONDITION( "not off", ( *(*btree).first_cursor ).item != NULL );
   INVARIANT( btree );

   cursor_back( (*btree).first_cursor );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return;
}

/**
   BTree_kv_forth
*/
void
BTree_kv_forth( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   PRECONDITION( "not off", ( *(*btree).first_cursor ).item != NULL );
   INVARIANT( btree );

   cursor_forth( (*btree).first_cursor );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return;
}

/**
   BTree_kv_go
*/
void
BTree_kv_go( Prefix )( BTree_kv_type( Prefix ) *btree, int32_t index )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*btree).count ) ) );
   INVARIANT( btree );

   int32_t i = 0;
   cursor_start( (*btree).first_cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( (*btree).first_cursor );
   }

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return;
}

/**
   BTree_kv_index
*/

int32_t
BTree_kv_index( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );

   int32_t result = 0;
   int32_t flag = 0;
   BTree_kv_cursor_type( Prefix ) *cursor = (*btree).first_cursor;
   node_t *target_node = (*cursor).item;
   int32_t target_index = 0;

   if ( target_node != NULL )
   {
      target_index = (*cursor).indices[ (*cursor).i_indices ];
   }

   if ( (*btree).count > 0 )
   {
      cursor_start( cursor );

      while ( cursor_off( cursor ) == 0 )
      {
         if ( ( (*cursor).item == target_node ) && ( (*cursor).indices[ (*cursor).i_indices ] == target_index ) )
         {
            flag = 1;
            break;
         }
         result = result + 1;
         cursor_forth( cursor );
      }
   }

   if ( flag == 0 )
   {
      result = -1;
   }

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return result;
}

/**
   BTree_kv_finish
*/

void
BTree_kv_finish( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );

   cursor_finish( (*btree).first_cursor );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return;
}

/**
   BTree_kv_start
*/

void
BTree_kv_start( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );

   cursor_start( (*btree).first_cursor );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return;
}

/**
   BTree_kv_put
*/

void
BTree_kv_put( Prefix )( BTree_kv_type( Prefix ) *btree, Type value, Key key )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );
   POSTCONDITION_VARIABLE_DEFINE( int32_t has_key_pc = has( btree, key ); );
   POSTCONDITION_VARIABLE_DEFINE( Key key_pc = KEY_DUPLICATE_FUNCTION( key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*btree).count; );

   put( btree, value, key );

   POSTCONDITION( "count incremented", ( has_key_pc == 0 ) ? ( (*btree).count == ( count_pc + 1 ) ) : ( (*btree).count == count_pc ) );
   POSTCONDITION( "contains key", has( btree, key_pc ) == 1 );
   POSTCONDITION_VARIABLE_DISPOSE( KEY_DISPOSE_FUNCTION( key_pc ); );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return;
}

/**
   BTree_kv_put_and_dispose
*/

void
BTree_kv_put_and_dispose( Prefix )( BTree_kv_type( Prefix ) *btree, Type value, Key key )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );
   POSTCONDITION_VARIABLE_DEFINE( int32_t has_key_pc = has( btree, key ); );
   POSTCONDITION_VARIABLE_DEFINE( Key key_pc = KEY_DUPLICATE_FUNCTION( key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*btree).count; );

   put_and_dispose( btree, value, key );

   POSTCONDITION( "count incremented", ( has_key_pc == 0 ) ? ( (*btree).count == ( count_pc + 1 ) ) : ( (*btree).count == count_pc ) );
   POSTCONDITION( "contains key", has( btree, key_pc ) == 1 );
   POSTCONDITION_VARIABLE_DISPOSE( KEY_DISPOSE_FUNCTION( key_pc ); );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return;
}

/**
   BTree_kv_remove
*/

void
BTree_kv_remove( Prefix )( BTree_kv_type( Prefix ) *btree, Key key )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );
   PRECONDITION( "has value", has( btree, key ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t has_key_pc = has( btree, key ); );
   POSTCONDITION_VARIABLE_DEFINE( Key key_pc = KEY_DUPLICATE_FUNCTION( key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*btree).count; );

   removE( btree, key );

   POSTCONDITION( "count decremented", ( has_key_pc == 1 ) ? ( (*btree).count == ( count_pc - 1 ) ) : ( (*btree).count == count_pc ) );
   POSTCONDITION( "does not contain key", has( btree, key_pc ) == 0 );
   POSTCONDITION_VARIABLE_DISPOSE( KEY_DISPOSE_FUNCTION( key_pc ); );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return;
}

/**
   BTree_kv_remove_and_dispose
*/

void
BTree_kv_remove_and_dispose( Prefix )( BTree_kv_type( Prefix ) *btree, Key key )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );
   PRECONDITION( "has value", has( btree, key ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t has_key_pc = has( btree, key ); );
   POSTCONDITION_VARIABLE_DEFINE( Key key_pc = KEY_DUPLICATE_FUNCTION( key ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*btree).count; );

   remove_and_dispose( btree, key );

   POSTCONDITION( "count decremented", ( has_key_pc == 1 ) ? ( (*btree).count == ( count_pc - 1 ) ) : ( (*btree).count == count_pc ) );
   POSTCONDITION( "does not contain key", has( btree, key_pc ) == 0 );
   POSTCONDITION_VARIABLE_DISPOSE( KEY_DISPOSE_FUNCTION( key_pc ); );

   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return;
}

/**
   BTree_kv_wipe_out
*/

void
BTree_kv_wipe_out( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );

   int32_t i = 0;

   // get array of nodes
   node_t **array = nodes_as_array( btree );

   // delete nodes
   i = 0;
   while( array[i] != NULL )
   {
      node_dispose( &array[i] );
      i = i + 1;
   }

   // delete array
   free( array );

   // delete cursors, all but first
   BTree_kv_cursor_type( Prefix ) *cursor = ( *(*btree).first_cursor ).next_cursor;
   BTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
   ( *(*btree).first_cursor ).next_cursor = NULL;
   (*btree).last_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( (*cursor).indices );
      free( cursor );
      cursor = next_cursor;
   }

   // set count to zero
   (*btree).count = 0;

   // set root to NULL
   (*btree).root = NULL;

   POSTCONDITION( "is empty", (*btree).count == 0 );
   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return;
}

/**
   BTree_kv_wipe_out_and_dispose
*/

void
BTree_kv_wipe_out_and_dispose( Prefix )( BTree_kv_type( Prefix ) *btree )
{
   PRECONDITION( "btree not null", btree != NULL );
   PRECONDITION( "btree type ok", ( (*btree)._type == BTREE_KV_TYPE ) && ( (*btree)._key_type = Key_Code ) && ( (*btree)._item_type = Type_Code ) );
   LOCK( (*btree).mutex );
   INVARIANT( btree );

   int32_t i = 0;
   int32_t n = 0;
   node_t **node_array = NULL;
   Key *key_array = NULL;
   Type *value_array = NULL;

   // get arrays
   key_array = keys_as_array( btree );
   value_array = values_as_array( btree );
   node_array = nodes_as_array( btree );

   // dispose nodes and values
   n = (*btree).count;
   for ( i = 0; i < n; i++ )
   {
      KEY_DISPOSE_FUNCTION( key_array[i] );
      VALUE_DISPOSE_FUNCTION( value_array[i] );
   }

   // dispose of nodes
   i = 0;
   while( node_array[i] != NULL )
   {
      node_dispose( &node_array[i] );
      i = i + 1;
   }

   // free arrays
   free( key_array );
   free( value_array );
   free( node_array );

   // delete cursors, all but first
   BTree_kv_cursor_type( Prefix ) *cursor = ( *(*btree).first_cursor ).next_cursor;
   BTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
   ( *(*btree).first_cursor ).next_cursor = NULL;
   (*btree).last_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( (*cursor).indices );
      free( cursor );
      cursor = next_cursor;
   }

   // set count to zero
   (*btree).count = 0;

   // set root to NULL
   (*btree).root = NULL;

   POSTCONDITION( "is empty", (*btree).count == 0 );
   INVARIANT( btree );
   UNLOCK( (*btree).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

