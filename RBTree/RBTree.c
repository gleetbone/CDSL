/**
 @file RBTree.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Red Black Binary Search Trees"

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

 Function definitions for the opaque RBTree_t type.

*/

#include "RBTree.h"

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_Iterable.ph"
#include "P_DIterable.ph"
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

struct RBTree_cursor_struct( Prefix );

/**
   Binary search tree structure definition.
*/

struct RBTree_struct( Prefix )
{

   PROTOCOLS_DEFINITION;

   int32_t _type;
   int32_t _item_type;

   node_t root;   // pseudo root, helps avoid complexity in code
   int32_t count;
   RBTree_cursor_type( Prefix ) *first_cursor;
   RBTree_cursor_type( Prefix ) *last_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure definition. Holds reference to rbtree, current node, node
   stack, and a pointer to the next cursor.
*/

struct RBTree_cursor_struct( Prefix )
{
   RBTree_type( Prefix ) *rbtree;
   node_t *item;
   RBTree_cursor_type( Prefix ) *next_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   function prototypes
*/

static
int
height( RBTree_type( Prefix ) *current );

static
void
cursor_start( RBTree_cursor_type( Prefix ) *cursor );

static
void
cursor_forth( RBTree_cursor_type( Prefix ) *cursor );

static
int32_t
cursor_off(  RBTree_cursor_type( Prefix ) *cursor );

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
   void ( func )( char_t *, Type value )
)
{
   int32_t node_height = 0;
   int32_t i = 0;
   char_t *cp = NULL;

   node_height = height_of_node( node );
   i = ( int32_t ) floor( pow( 2.0, tree_height - node_height ) );
   i = width * i + 2 * width * i * index;
   cp = &( astr[ node_height - 1 ][ i ] );
   func( cp, (*node).value );

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
   RBTree_as_string

   create a string representation of the tree

   @param current the tree
   @param astr array of strings, one string for each level of the tree
   @param width the length of the string space for a node
   @param func a function to convert a node's value to a string
*/

void
RBTree_as_string( Prefix )
(
   RBTree_type( Prefix ) *current,
   char_t **astr,
   int32_t width,
   void ( func )( char_t *, Type value )
)
{
   node_t *node = NULL;
   int32_t tree_height = 0;
   int32_t index = 0;

   node = (*current).root.left;
   tree_height = height( current );

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
   CHECK( "node allocated correctly", node != NULL );

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
   @param value the value to search for
   @return 1 if value found, 0 otherwise
*/
static
int32_t
has_recurse( node_t *node, Type value )
{
   int32_t result = 0;

   // in order recursion - left, self, right
   // if tested value is found, exit
   if ( (*node).left != &null_node )
   {
      result = has_recurse( (*node).left, value );
   }

   if ( result == 0 )
   {
      result = VALUE_DEEP_EQUAL_FUNCTION( (*node).value, value );
   }

   if ( result == 0 )
   {
      if ( (*node).right != &null_node )
      {
         result = has_recurse( (*node).right, value );
      }
   }
   return result;
}

/**
   has

   Return 1 if rbtree has an item for value, 0 if not

   @param current RBTree_t instance
   @param value the value to search for
*/

static
int32_t
has( RBTree_type( Prefix ) *current, Type value )
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root.left;

   // recurse to see if can find value in tree
   if ( node != &null_node )
   {
      result = has_recurse( node, value );
   }

   return result;
}

/**
   has_eq_fn_recurse

   search for a node with the desired value using a provided equality function,
   return 1 if found, 0 otherwise, recursive

   @param node the node to start from
   @param value the value to search for
   @param equality_test_func the function to check equality of values
   @return 1 if value found, 0 otherwise
*/
static
int32_t
has_eq_fn_recurse
(
   node_t *node,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   int32_t result = 0;

   // in order recursion - left, self, right
   // if tested value is found, exit
   if ( (*node).left != &null_node )
   {
      result = has_eq_fn_recurse( (*node).left, value, equality_test_func );
   }

   if ( result == 0 )
   {
      result = equality_test_func( (*node).value, value );
   }

   if ( result == 0 )
   {
      if ( (*node).right != &null_node )
      {
         result = has_eq_fn_recurse( (*node).right, value, equality_test_func );
      }
   }
   return result;
}

/**
   has_eq_fn

   search for a node with the desired value using a provided equality function,
   return 1 if found, 0 otherwise, recursive

   @param current the tree
   @param value the value to search for
   @param equality_test_func the function to check equality of values
   @return 1 if value found, 0 otherwise
*/

static
int32_t
has_eq_fn
(
   RBTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   int32_t result = 0;
   node_t *node = &null_node;

   // get root node
   node = (*current).root.left;

   // recurse to see if can find value in tree
   if ( node != &null_node )
   {
      result = has_eq_fn_recurse( node, value, equality_test_func );
   }

   return result;
}

/**
   occurrences_recurse

   count number of nodes with a value equal to the desired value, recusive

   @param node the node to start from
   @param value the value to search for
   @param count accumulates the number of found nodes
*/
static
void
occurrences_recurse( node_t *node, Type value, int32_t *count )
{
   // in order recursion - left, self, right
   // if tested value is found, count it
   if ( (*node).left != &null_node )
   {
      occurrences_recurse( (*node).left, value, count );
   }

   if ( VALUE_DEEP_EQUAL_FUNCTION( (*node).value, value ) == 1 )
   {
      *count = *count + 1;
   }

   if ( (*node).right != &null_node )
   {
      occurrences_recurse( (*node).right, value, count );
   }

   return;
}

/**
   occurrences

   Return count of nodes in tree with a value equal to the desired value

   @param current RBTree_t instance
   @param value the value to query for
   @return the count of items count
*/

static
int32_t
occurrences( RBTree_type( Prefix ) *current, Type value )
{
   int32_t result = 0;
   node_t *node = &null_node;

   // get root node
   node = (*current).root.left;

   // recurse to see if can find value in tree
   if ( node != &null_node )
   {
      occurrences_recurse( node, value, &result );
   }

   return result;
}

/**
   occurrences_eq_fn_recurse

   count number of nodes with a value equal to the desired value using the
   supplied equality function, recusive

   @param node the node to start from
   @param value the value to search for
   @param count accumulates the number of found nodes
   @param equality_test_func function to compare values for equality
*/
static
void
occurrences_eq_fn_recurse
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
      occurrences_eq_fn_recurse( (*node).left, value, count, equality_test_func );
   }

   if ( equality_test_func( (*node).value, value ) == 1 )
   {
      *count = *count + 1;
   }

   if ( (*node).right != &null_node )
   {
      occurrences_eq_fn_recurse( (*node).right, value, count, equality_test_func );
   }

   return;
}

/**
   occurrences_eq_fn

   Return count of nodes in rbtree containing a value equal to the desired
   value according to equality_test_func

   @param rbtree RBTree_t instance
   @param value the value to query for
   @param equality_test_func the test function for value equality
   @return the count of nodes found
*/

static
int32_t
occurrences_eq_fn
(
   RBTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   int32_t result = 0;
   node_t *node = &null_node;

   // get root node
   node = (*current).root.left;

   // recurse to see if can find value in tree
   if ( node != &null_node )
   {
      occurrences_eq_fn_recurse( node, value, &result, equality_test_func );
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
node_for_index( RBTree_type( Prefix ) *current, int32_t index )
{
   int32_t i = 0;
   node_t *result = &null_node;

   // get cursor
   RBTree_cursor_type( Prefix ) *c
      =  ( RBTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );

   // set rbtree in cursor
   (*c).rbtree = current;

   if ( ( index < 0 ) || ( index >= (*current).count ) )
   {
      result = &null_node;
   }
   else
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
index_for_node( RBTree_type( Prefix ) *current, node_t *node )
{
   int32_t result = 0;
   int32_t flag = 0;

   // get cursor
   RBTree_cursor_type( Prefix ) *c
      =  ( RBTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_cursor_type( Prefix ) ) );
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
item_recurse( node_t *node, Type value )
{
   node_t *result = &null_node;

   if ( VALUE_DEEP_EQUAL_FUNCTION( value, (*node).value ) == 1 )
   {
      result = node;
   }

   if ( result == &null_node )
   {
      if ( ORDER_FUNCTION( value, (*node).value ) == 1 )
      {

         if ( (*node).left != &null_node )
         {
            result = item_recurse( (*node).left, value );
         }
      }
   }

   if ( result == &null_node )
   {
      if ( ORDER_FUNCTION( value, (*node).value ) == 0 )
      {

         if ( (*node).right != &null_node )
         {
            result = item_recurse( (*node).right, value );
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
item( RBTree_type( Prefix ) *current, Type value )
{
   node_t *result = &null_node;
   node_t *node = &null_node;

   // get root node
   result = &null_node;
   node = (*current).root.left;

   // recurse to see if can find value in tree
   if ( node != &null_node )
   {
      result = item_recurse( node, value );
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
rotate_left( RBTree_type( Prefix ) *current, node_t *node )
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
rotate_right( RBTree_type( Prefix ) *current, node_t *node )
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
repair_put( RBTree_type( Prefix ) *current, node_t *node )
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
      ( n != (*current).root.left )
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
            repair_put( current, ( *(*n).parent ).parent );
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
            rotate_left( current, n );
         }
         ( *(*n).parent ).color = black ;
         if ( ( *(*n).parent ).parent != &null_node )
         {
            ( *( *(*n).parent ).parent ).color = red;
            rotate_right( current, ( *(*n).parent ).parent );
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
            rotate_right( current, n );
         }
         ( *(*n).parent ).color = black;
         if ( ( *(*n).parent ).parent != &null_node )
         {
            ( *( *(*n).parent ).parent ).color = red;
            rotate_left( current, ( *(*n).parent ).parent );
         }
      }
   }

   // color the root black
   ( *(*current).root.left ).color = black;

   return;
}

/**
   node_for_value_recurse

   search for a node with the desired value, recursive

   @param node the node to start with
   @param value the desired value
   @return the found node, or NULL if not found
*/
static
node_t *
node_for_value_recurse( node_t *node, Type value )
{
   node_t *result = &null_node;
   node_t *temp = &null_node;
   node_t *n = &null_node;

   if ( VALUE_DEEP_EQUAL_FUNCTION( value, (*node).value ) == 1 )
   {
      result = node;
   }

   if ( result == &null_node )
   {
      if ( ORDER_FUNCTION( value, (*node).value ) == 1 )
      {

         if ( (*node).left != &null_node )
         {
            result = node_for_value_recurse( (*node).left, value );
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
      if ( ORDER_FUNCTION( value, (*node).value ) == 0 )
      {

         if ( (*node).right != &null_node )
         {
            result = node_for_value_recurse( (*node).right, value );
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
   put

   put a new node into the tree with the specified value

   @param current the tree
   @param value the value to put in the tree
*/

static
void
put( RBTree_type( Prefix ) *current, Type value )
{
   node_t *node = NULL;
   node_t *parent = NULL;
   int32_t result = 0;

   // start at root of tree
   node = (*current).root.left;
   parent = &(*current).root;

   // find insertion point
   while( node != &null_node )
   {
      parent = node;
      result = ORDER_FUNCTION( value, (*node).value );
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
   (*node).value = value;
   (*node).left = &null_node;
   (*node).right = &null_node;
   (*node).parent = parent;
   (*node).color = red;

   // adjust its parent node
   if (
      ( parent == &(*current).root )
      ||
      ( ORDER_FUNCTION( (*node).value, (*parent).value ) == 1 )
   )
   {
      (*parent).left = node;
      repair_put( current, node );
   }
   else
   {
      (*parent).right = node;
      repair_put( current, node );
   }

   // ensure tree root is black
   ( *(*current).root.left ).color = black;

   // increment count
   (*current).count = (*current).count + 1;

   return;
}

/**
   values_as_array_recurse

   construct an in-order array of values from the tree, recursive

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

   construct an in-order array of values from the tree

   @param current the tree
   @return the array of values
*/

static
Type *
values_as_array( RBTree_type( Prefix ) *current )
{
   Type *result = NULL;
   int32_t index = 0;

   result = ( Type * ) calloc( (*current).count + 1, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   if ( (*current).root.left != &null_node )
   {
      values_as_array_recurse( (*current).root.left, result, &index );
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
nodes_as_array( RBTree_type( Prefix ) *current )
{
   node_t **result = NULL;
   int32_t index = 0;

   result = ( node_t ** ) calloc( (*current).count + 1, sizeof( node_t ) );
   CHECK( "result allocated correctly", result != NULL );

   if ( (*current).root.left != &null_node )
   {
      nodes_as_array_recurse( (*current).root.left, result, &index );
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
repair_remove( RBTree_type( Prefix ) *current, node_t *node )
{
   node_t *n = NULL;
   node_t *sibling = NULL;

   n = node;

   // while node is not tree root and is black
   while ( ( n != (*current).root.left ) && ( (*n).color == black ) )
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
            rotate_left( current, (*n).parent );
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
               rotate_right( current, sibling );
               sibling = ( *(*n).parent ).right;
            }

            (*sibling).color = ( *(*n).parent ).color;
            ( *(*n).parent ).color = black;
            ( *(*sibling).right ).color = black;
            rotate_left( current, (*n).parent );
            n = (*current).root.left;
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
            rotate_right( current, (*n).parent );
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
               rotate_left( current, sibling );
               sibling = ( *(*n).parent ).left;
            }

            (*sibling).color = ( *(*n).parent ).color;
            ( *(*n).parent ).color = black;
            ( *(*sibling).left ).color = black;
            rotate_right( current, (*n).parent );
            n = (*current).root.left;
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
predecessor( RBTree_type( Prefix ) *current, node_t *node )
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

/**
   remove

   remove a node from the tree

   @param current the tree
   @param node the node to remove
   @return the removed node to be disposed of in the calling routine
*/
static
node_t *
remove( RBTree_type( Prefix ) *current, node_t *node )
{
   node_t *pre = NULL;
   node_t *pull_up = NULL;
   Type v;
   RBTree_cursor_type( Prefix ) *cursor = NULL;

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
         (*node).value = (*pre).value;
         (*pre).value = v;
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
int32_t
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
height( RBTree_type( Prefix ) *current )
{
   int32_t result = 0;

   result = height_recurse( (*current).root.left );

   return result;
}

/**
   count_recurse

   count the number of nodes in the tree, recursive

   @param node the node being analyzed
   @return the height so far
*/
static
int32_t
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
count( RBTree_type( Prefix ) *current )
{
   int32_t result = 0;

   result = count_recurse( (*current).root.left );

   return result;
}

/**
   recursion for rbtree cursor functions - start, item, forth, off

   The following routines depend on the fact that the rbtree
   is (already) in order and that the forth recursion keeps track
   of the last seen ( the previous ) node (in the cursor structure).
*/

/**
   cursor_finish
*/
static
void
cursor_finish( RBTree_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;

   // set node from the rbtree root
   node = ( *(*cursor).rbtree ).root.left;

   // walk to the rightmost node from the tree root
   while ( (*node).right != &null_node )
   {
      node = (*node).right;
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
cursor_start( RBTree_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;

   // set node from the rbtree root
   node = ( *(*cursor).rbtree ).root.left;

   // walk to the leftmost node from the tree root
   while ( (*node).left != &null_node )
   {
      node = (*node).left;
   }

   // set data items in the cursor
   (*cursor).item = node;

   return;
}

/**
   cursor_item_at
*/
static
Type
cursor_item_at( RBTree_cursor_type( Prefix ) *cursor )
{
   // return the value for the current cursor item
   return ( *(*cursor).item ).value;
}


/**
   cursor_back
*/
static
void
cursor_back( RBTree_cursor_type( Prefix ) *cursor )
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
cursor_forth( RBTree_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;
   node_t *temp = NULL;

   // go to next item in sequence ( or off )
   if ( cursor_off( cursor ) == 0 )
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
cursor_off(  RBTree_cursor_type( Prefix ) *cursor )
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
move_all_cursors_off( RBTree_type( Prefix ) *current )
{
   RBTree_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   while( cursor != NULL )
   {
      // set cursor item to null == off
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
   @param array the array of values
   @param array_count the number of values in the array
   @return 1 if values are equal, 0 otherwise
*/

static
int32_t
compare_tree_items_to_array_items( RBTree_type( Prefix ) *current, Type *array, int32_t array_count )
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t count = 0;
   int32_t i = 0;

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
         if ( has( current, array[i] ) == 1 )
         {
            count = count + 1;
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
   RBTree_type( Prefix ) *current, 
   RBTree_type( Prefix ) *other 
)
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t count = 0;
   RBTree_cursor_type( Prefix ) *c1
      =  ( RBTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_cursor_type( Prefix ) ) );
   CHECK( "c1 allocated correctly", c1 != NULL );

   RBTree_cursor_type( Prefix ) *c2
      =  ( RBTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_cursor_type( Prefix ) ) );
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
         if ( cursor_item_at( c1 ) == cursor_item_at( c2 ) )
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
   RBTree_type( Prefix ) *current, 
   RBTree_type( Prefix ) *other 
)
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t count = 0;
   RBTree_cursor_type( Prefix ) *c1
      =  ( RBTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_cursor_type( Prefix ) ) );
   CHECK( "c1 allocated correctly", c1 != NULL );

   RBTree_cursor_type( Prefix ) *c2
      =  ( RBTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_cursor_type( Prefix ) ) );
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
         if ( VALUE_DEEP_EQUAL_FUNCTION( cursor_item_at( c1 ), cursor_item_at( c2 ) ) == 1 )
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
is_empty_implies_root_null( RBTree_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).count == 0 )
   {
      result = ( (*current).root.left == &null_node );
   }

   return result;
}

static
int32_t
nonnegative_count( RBTree_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).count >= 0 );

   return result;
}

static
int32_t
valid_count( RBTree_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( count( current ) == (*current).count );

   return result;
}

static
int32_t
first_cursor_not_null( RBTree_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).first_cursor != NULL );

   return result;
}

static
int32_t
cursors_rbtree_ok( RBTree_type( Prefix ) *current )
{
   int32_t result = 1;

   RBTree_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   while( ( cursor != NULL ) && ( result == 1 ) )
   {
      result = ( (*cursor).rbtree == current );
      cursor = (*cursor).next_cursor;
   }

   return result;
}

static
int32_t
last_cursor_null_if_one_cursor( RBTree_type( Prefix ) *current )
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
last_cursor_next_null( RBTree_type( Prefix ) *current )
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
in_order_recurse( node_t *node )
{
   int32_t result = 1;

   if ( (*node).left != &null_node )
   {
      result = ORDER_FUNCTION( ( *(*node).left ).value, (*node).value );
   }

   if ( result == 1 )
   {
      if ( (*node).right != &null_node )
      {
         result = ORDER_FUNCTION( (*node).value, ( *(*node).right ).value );
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
in_order( RBTree_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).count > 1 )
   {
      result = in_order_recurse( (*current).root.left );
   }

   return result;
}

static
int32_t
root_is_black( RBTree_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).root.left != &null_node )
   {
      result = ( ( *(*current).root.left ).color == black );
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
node_colors_ok( RBTree_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).root.left != &null_node )
   {
      result = node_colors_ok_recurse( (*current).root.left );
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
path_black_count_ok( RBTree_type( Prefix ) *current )
{
   int32_t result = 1;
   int32_t count = 0;

   if ( (*current).root.left != &null_node )
   {
      result = path_black_count_ok_recurse( (*current).root.left, &count );
   }

   return result;
}

static
int32_t
null_node_ok( RBTree_type( Prefix ) *current )
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
cursors_off_or_valid( RBTree_type( Prefix ) *current )
{
   int32_t result = 1;
   RBTree_cursor_type( Prefix ) *cursor = NULL;

   // get cursor
   RBTree_cursor_type( Prefix ) *c
      =  ( RBTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_cursor_type( Prefix ) ) );
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
node_pointers_consistent( RBTree_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).count > 1 )
   {
      result = node_pointers_consistent_recurse( (*current).root.left );
   }

   return result;
}

static
void invariant( RBTree_type( Prefix ) *current )
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
   RBTree_dispose( Prefix ),
   RBTree_deep_dispose( Prefix ),
   RBTree_is_equal( Prefix ),
   RBTree_is_deep_equal( Prefix ),
   RBTree_copy( Prefix ),
   RBTree_deep_copy( Prefix ),
   RBTree_clone( Prefix ),
   RBTree_deep_clone( Prefix )
};

static
void *
p_iterable_table[P_ITERABLE_FUNCTION_COUNT]
=
{
   RBTree_count( Prefix ),
   RBTree_item_at( Prefix ),
   RBTree_off( Prefix ),
   RBTree_is_empty( Prefix ),
   RBTree_start( Prefix ),
   RBTree_forth( Prefix )
};

static
void *
p_diterable_table[P_DITERABLE_FUNCTION_COUNT]
=
{
   RBTree_count( Prefix ),
   RBTree_item_at( Prefix ),
   RBTree_off( Prefix ),
   RBTree_is_empty( Prefix ),
   RBTree_start( Prefix ),
   RBTree_forth( Prefix ),
   RBTree_finish( Prefix ),
   RBTree_back( Prefix )
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

      case P_ITERABLE_TYPE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_ITERABLE_FUNCTION_MAX ) )
         {
            result = p_iterable_table[ function_id ];
         }
         break;
      }

      case P_DITERABLE_TYPE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_DITERABLE_FUNCTION_MAX ) )
         {
            result = p_diterable_table[ function_id ];
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

      case P_ITERABLE_TYPE:
      {
         result = 1;
         break;
      }

      case P_DITERABLE_TYPE:
      {
         result = 1;
         break;
      }

   }

   return result;
}

#endif // PROTOCOLS_ENABLED


/**
   RBTree_make
*/

RBTree_type( Prefix ) *
RBTree_make( Prefix )( void )
{
   // allocate result struct
   RBTree_type( Prefix ) * result
      = ( RBTree_type( Prefix ) * ) calloc( 1, sizeof( RBTree_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = RBTREE_TYPE;
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
   RBTree_cursor_type( Prefix ) *cursor
      =  ( RBTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set result
   (*cursor).rbtree = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = &null_node;

   // set result built-in cursor
   (*result).first_cursor = cursor;

   // init mutex
   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new result is empty", (*result).count == 0 );
   POSTCONDITION( "new result cursor is off", ( *(*result).first_cursor ).item == &null_node );

   INVARIANT( result );

   return result;
}

/**
   RBTree_make_from_array
*/

RBTree_type( Prefix ) *
RBTree_make_from_array( Prefix )( Type *array, int32_t count )
{
   PRECONDITION( "array not null", array != NULL );
   PRECONDITION( "count ok", count >= 0 );

   // make rbtree struct
   RBTree_type( Prefix ) *result = RBTree_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = RBTREE_TYPE;
   (*result)._item_type = Type_Code;

   int32_t i = 0;

   for ( i = 0; i < count; i++ )
   {
      put( result, array[i] );
   }

   POSTCONDITION( "new result cursor is off", ( *(*result).first_cursor ).item == &null_node );
   POSTCONDITION( "new result contains elements of array", compare_tree_items_to_array_items( result, array, count ) );

   INVARIANT( result );

   return result;
}

/**
   RBTree_clone
*/

RBTree_type( Prefix ) *
RBTree_clone( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );

   // make current struct
   RBTree_type( Prefix ) *result = RBTree_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = RBTREE_TYPE;
   (*result)._item_type = Type_Code;

   // copy from current
   RBTree_cursor_type( Prefix ) *cursor = RBTree_cursor_make( Prefix )( current );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, cursor_item_at( cursor ) );
      cursor_forth( cursor );
   }

   POSTCONDITION( "new tree cursor is off", ( *(*result).first_cursor ).item == &null_node );
   POSTCONDITION( "new tree contains elements of current", compare_tree_items_to_tree_items( result, current ) );

   INVARIANT( result );

   return result;
}

/**
   RBTree_deep_clone
*/

RBTree_type( Prefix ) *
RBTree_deep_clone( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );

   // make current struct
   RBTree_type( Prefix ) *result = RBTree_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = RBTREE_TYPE;
   (*result)._item_type = Type_Code;

   // copy from current
   RBTree_cursor_type( Prefix ) *cursor = RBTree_cursor_make( Prefix )( current );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, VALUE_DEEP_CLONE_FUNCTION( cursor_item_at( cursor ) ) );
      cursor_forth( cursor );
   }

   POSTCONDITION( "new tree cursor is off", ( *(*result).first_cursor ).item == &null_node );
   POSTCONDITION( "new tree contains elements of current", compare_tree_items_to_tree_items_deep_equal( result, current ) );

   INVARIANT( result );

   return result;
}

/**
   RBTree_is_equal
*/

int32_t
RBTree_is_equal( Prefix )( RBTree_type( Prefix ) *current, RBTree_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == RBTREE_TYPE ) && ( (*other)._item_type = Type_Code ) );

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
   RBTree_is_deep_equal
*/

int32_t
RBTree_is_deep_equal( Prefix )( RBTree_type( Prefix ) *current, RBTree_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == RBTREE_TYPE ) && ( (*other)._item_type = Type_Code ) );

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
   RBTree_copy
*/

void
RBTree_copy( Prefix )( RBTree_type( Prefix ) *current, RBTree_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == RBTREE_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t i = 0;
   RBTree_cursor_type( Prefix ) *c
      =  ( RBTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );

   (*c).rbtree = other;

   // empty out current
   node_t **array = nodes_as_array( current );

   // delete nodes and values
   for ( i = 0; i < (*current).count; i++ )
   {
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
      put( current, cursor_item_at( c ) );
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
   RBTree_deep_copy
*/

void
RBTree_deep_copy( Prefix )( RBTree_type( Prefix ) *current, RBTree_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == RBTREE_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t i = 0;
   Type v;
   RBTree_cursor_type( Prefix ) *c
      =  ( RBTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );

   (*c).rbtree = other;

   // empty out current
   node_t **array = nodes_as_array( current );

   // delete nodes and values
   for ( i = 0; i < (*current).count; i++ )
   {
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
      v = VALUE_DEEP_CLONE_FUNCTION( cursor_item_at( c ) );
      put( current, v );
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
   RBTree_cursor_make
*/

RBTree_cursor_type( Prefix ) *
RBTree_cursor_make( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // allocate cursor struct
   RBTree_cursor_type( Prefix ) *cursor
      =  ( RBTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set current
   (*cursor).rbtree = current;

   // set item to NULL - cursor is "off"
   (*cursor).item = &null_node;

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
   RBTree_dispose
*/

void
RBTree_dispose( Prefix )( RBTree_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == RBTREE_TYPE ) && ( (**current)._item_type = Type_Code ) );
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
   RBTree_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   RBTree_cursor_type( Prefix ) *next_cursor = NULL;
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
   RBTree_deep_dispose
*/

void
RBTree_deep_dispose( Prefix )( RBTree_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == RBTREE_TYPE ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   int32_t i = 0;

   // get array of nodes
   node_t **array = nodes_as_array(*current);

   // delete nodes and values
   for ( i = 0; i < (**current).count; i++ )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( ( *array[i] ).value );
      node_dispose( &array[i] );
   }

   // delete array
   free( array );

   // delete cursors
   RBTree_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   RBTree_cursor_type( Prefix ) *next_cursor = NULL;
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
   RBTree_cursor_dispose
*/

void
RBTree_cursor_dispose( Prefix )( RBTree_cursor_type( Prefix ) **cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "*cursor not null", *cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(**cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(**cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (**cursor).mutex );
   LOCK( ( *(**cursor).rbtree ).mutex );
   INVARIANT( (**cursor).rbtree );

   RBTree_type( Prefix ) *rbtree = (**cursor).rbtree;

   RBTree_cursor_type( Prefix ) *c1 = NULL;
   RBTree_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from rbtree structure
   c1 = ( *(**cursor).rbtree ).first_cursor;
   c2 = (*c1).next_cursor;

   // search through the cursors
   while ( ( c2 != NULL ) && ( flag == 0 ) )
   {
      if ( c2 == *cursor )
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
   c1 = ( *(**cursor).rbtree ).first_cursor;
   while ( c1 != NULL )
   {
      c2 = c1;
      c1 = (*c1).next_cursor;
   }
   ( *(**cursor).rbtree ).last_cursor = c2;

   // only one cursor, last_cursor is NULL
   if ( c2 == ( *(**cursor).rbtree ).first_cursor )
   {
      ( *(**cursor).rbtree ).last_cursor = NULL;
   }

   // delete cursor struct
   free(*cursor);

   // set to NULL
   *cursor = NULL;

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return;
}

/**
   RBTree_as_array

*/

Type *
RBTree_as_array( Prefix )( RBTree_type( Prefix ) *current, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type *result = values_as_array( current );

   (*count) = (*current).count;

   POSTCONDITION( "array contains items of current", compare_tree_items_to_array_items( current, result, *count ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_cursor_item_at
*/

Type
RBTree_cursor_item_at( Prefix )( RBTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );
   PRECONDITION( "cursor not off", cursor_off( cursor ) == 0 );

   Type value = cursor_item_at( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}


/**
   RBTree_item_at
*/

Type
RBTree_item_at( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", cursor_off( (*current).first_cursor ) == 0 );

   RBTree_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   Type value = cursor_item_at( cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   RBTree_item
*/

Type
RBTree_item( Prefix )( RBTree_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   node_t *node = node_for_index( current, index );
   Type result = (*node).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_first
*/

Type
RBTree_first( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "current not empty", (*current).count >= 0 );
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
   RBTree_last
*/

Type
RBTree_last( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "current not empty", (*current).count >= 0 );
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
   RBTree_count
*/

int32_t
RBTree_count( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_height
*/

int32_t
RBTree_height( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = height( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_off
*/

int32_t
RBTree_off( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = cursor_off( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_cursor_off
*/

int32_t
RBTree_cursor_off( Prefix )( RBTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).rbtree );

   int32_t result = cursor_off( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   RBTree_cursor_is_first
*/

int32_t
RBTree_cursor_is_first( Prefix )( RBTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
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
   RBTree_cursor_is_last
*/

int32_t
RBTree_cursor_is_last( Prefix )( RBTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
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
   RBTree_cursor_search_forth
*/

void
RBTree_cursor_search_forth( Prefix )( RBTree_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
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
   RBTree_cursor_search_forth_eq_fn
*/

void
RBTree_cursor_search_forth_eq_fn( Prefix )
(
   RBTree_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
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
   RBTree_cursor_search_back
*/

void
RBTree_cursor_search_back( Prefix )( RBTree_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
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
   RBTree_cursor_search_back_eq_fn
*/

void
RBTree_cursor_search_back_eq_fn( Prefix )
(
   RBTree_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
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
   RBTree_is_empty
*/

int32_t
RBTree_is_empty( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count ==  0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_is_first
*/

int32_t
RBTree_is_first( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   RBTree_is_last
*/

int32_t
RBTree_is_last( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   RBTree_has
*/

int32_t
RBTree_has( Prefix )( RBTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_has_eq_fn
*/

int32_t
RBTree_has_eq_fn( Prefix )
(
   RBTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has_eq_fn( current, value, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_occurrences
*/

int32_t
RBTree_occurrences( Prefix )( RBTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_occurrences_eq_fn
*/

int32_t
RBTree_occurrences_eq_fn( Prefix )
(
   RBTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences_eq_fn( current, value, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_search_forth
*/

void
RBTree_search_forth( Prefix )( RBTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   RBTree_search_forth_eq_fn
*/

void
RBTree_search_forth_eq_fn( Prefix )
(
   RBTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   RBTree_search_back
*/

void
RBTree_search_back( Prefix )( RBTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   RBTree_search_back_eq_fn
*/

void
RBTree_search_back_eq_fn( Prefix )
(
   RBTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
      cursor_back( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_cursor_forth
*/
void
RBTree_cursor_forth( Prefix )( RBTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).rbtree );

   cursor_forth( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_cursor_back
*/
void
RBTree_cursor_back( Prefix )( RBTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).rbtree );

   cursor_back( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_cursor_go
*/
void
RBTree_cursor_go( Prefix )( RBTree_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
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
   RBTree_cursor_go_to_value
*/
void
RBTree_cursor_go_to_value( Prefix )( RBTree_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );
   POSTCONDITION_VARIABLE_DEFINE( RBTree_cursor_type( Prefix ) c; c.rbtree = (*cursor).rbtree; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_empty = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_first = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_last = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_equal = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_lt = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_gt = 0; );

   node_t *node = NULL;

   if ( ( *(*cursor).rbtree ).root.left != &null_node )
   {
      node = node_for_value_recurse( ( *(*cursor).rbtree ).root.left, value );
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
   if ( VALUE_DEEP_EQUAL_FUNCTION( value, (*node).value ) == 1 )
      {
         is_equal = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( node != &null_node )
{
   if ( ORDER_FUNCTION( (*node).value, value ) == 1 )
      {
         is_lt = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( cursor_off( &c ) != 1 )
{
   if ( ORDER_FUNCTION( value, ( *c.item ).value ) == 1 )
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
   RBTree_cursor_index
*/

int32_t
RBTree_cursor_index( Prefix )( RBTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
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
   RBTree_cursor_start
*/

void
RBTree_cursor_start( Prefix )( RBTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
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
   RBTree_cursor_finish
*/

void
RBTree_cursor_finish( Prefix )( RBTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) ) );
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
   RBTree_forth
*/
void
RBTree_forth( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != &null_node );

   cursor_forth( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_cursor_remove_at
*/

void
RBTree_cursor_remove_at( Prefix )( RBTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "current type ok", ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );
   PRECONDITION( "cursor not off", cursor_off( cursor ) == 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *(*cursor).item ).value; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( (*cursor).rbtree, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).rbtree ).count; );

   node_t *node = NULL;
   node = (*cursor).item;
   cursor_forth( cursor );

   node = remove( (*cursor).rbtree, node );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( (*cursor).rbtree, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == ( *(*cursor).rbtree ).count + 1 );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_cursor_remove_at_and_dispose
*/

void
RBTree_cursor_remove_at_and_dispose( Prefix )( RBTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "current type ok", ( ( *(*cursor).rbtree )._type == RBTREE_TYPE ) && ( ( *(*cursor).rbtree )._item_type = Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).rbtree ).mutex );
   INVARIANT( (*cursor).rbtree );
   PRECONDITION( "cursor not off", cursor_off( cursor ) == 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = VALUE_DEEP_CLONE_FUNCTION( ( *(*cursor).item ).value ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( (*cursor).rbtree, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).rbtree ).count; );

   node_t *node = NULL;
   node = (*cursor).item;
   cursor_forth( cursor );

   node = remove( (*cursor).rbtree, node );

   // dispose of the value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( (*cursor).rbtree, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == ( *(*cursor).rbtree ).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( VALUE_DEEP_DISPOSE_FUNCTION( val_pc ); );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( ( *(*cursor).rbtree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_back
*/
void
RBTree_back( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != &null_node );

   cursor_back( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_go
*/
void
RBTree_go( Prefix )( RBTree_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   RBTree_go_to_value
*/
void
RBTree_go_to_value( Prefix )( RBTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( RBTree_cursor_type( Prefix ) c; c.rbtree = current; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_empty = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_first = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_last = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_equal = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_lt = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_gt = 0; );

   node_t *node = NULL;

   if ( (*current).root.left != &null_node )
   {
      node = node_for_value_recurse( (*current).root.left, value );
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
   if ( VALUE_DEEP_EQUAL_FUNCTION( value, (*node).value ) == 1 )
      {
         is_equal = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( node != &null_node )
{
   if ( ORDER_FUNCTION( (*node).value, value ) == 1 )
      {
         is_lt = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( cursor_off( &c ) != 1 )
{
   if ( ORDER_FUNCTION( value, ( *c.item ).value ) == 1 )
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
   RBTree_index
*/

int32_t
RBTree_index( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = index_for_node( current, ( *(*current).first_cursor ).item );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   RBTree_start
*/

void
RBTree_start( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cursor_start( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_finish
*/

void
RBTree_finish( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cursor_finish( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_put
*/

void
RBTree_put( Prefix )( RBTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   put( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_remove
*/

void
RBTree_remove( Prefix )( RBTree_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   node_t *node = NULL;

   // remove the node from the tree
   node = node_for_index( current, index );
   node = remove( current, node );

   // dispose of the node
   node_dispose( &node );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_remove_and_dispose
*/

void
RBTree_remove_and_dispose( Prefix )( RBTree_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   node_t *node = NULL;

   // remove the node from the tree
   node = node_for_index( current, index );
   node = remove( current, node );

   // dispose of the value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of the node
   node_dispose( &node );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_remove_value
*/

void
RBTree_remove_value( Prefix )( RBTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has( current, value ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, value ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = item( current, value );

   node = remove( current, node );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, value ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_remove_value_and_dispose
*/

void
RBTree_remove_value_and_dispose( Prefix )( RBTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has( current, value ) );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = VALUE_DEEP_CLONE_FUNCTION( value ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, value ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = item( current, value );

   node = remove( current, node );

   // dispose of the value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( VALUE_DEEP_DISPOSE_FUNCTION( val_pc ); );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_remove_at
*/

void
RBTree_remove_at( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "internal cursor not off", cursor_off( (*current).first_cursor ) == 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *( *(*current).first_cursor ).item ).value; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = ( *(*current).first_cursor ).item;

   node = remove( current, node );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_remove_at_and_dispose
*/

void
RBTree_remove_at_and_dispose( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "internal cursor not off", cursor_off( (*current).first_cursor ) == 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = VALUE_DEEP_CLONE_FUNCTION( ( *( *(*current).first_cursor ).item ).value ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = ( *(*current).first_cursor ).item;

   node = remove( current, node );

   // dispose of the value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( VALUE_DEEP_DISPOSE_FUNCTION( val_pc ); );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_remove_first
*/

void
RBTree_remove_first( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( * node_for_index( current, 0 ) ).value; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, 0 );

   node = remove( current, node );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_remove_first_and_dispose
*/

void
RBTree_remove_first_and_dispose( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = VALUE_DEEP_CLONE_FUNCTION( ( * node_for_index( current, 0 ) ).value ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, 0 );

   node = remove( current, node );

   // dispose of the value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( VALUE_DEEP_DISPOSE_FUNCTION( val_pc ); );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_remove_last
*/

void
RBTree_remove_last( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( * node_for_index( current, (*current).count - 1 ) ).value; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, (*current).count - 1 );

   node = remove( current, node );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_remove_last_and_dispose
*/

void
RBTree_remove_last_and_dispose( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not empty", (*current).count > 0 );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = VALUE_DEEP_CLONE_FUNCTION( ( * node_for_index( current, (*current).count - 1 ) ).value ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( current, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = NULL;
   node = node_for_index( current, (*current).count - 1 );

   node = remove( current, node );

   // dispose of the value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( VALUE_DEEP_DISPOSE_FUNCTION( val_pc ); );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   RBTree_wipe_out
*/

void
RBTree_wipe_out( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   RBTree_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   RBTree_cursor_type( Prefix ) *next_cursor = NULL;
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
   RBTree_wipe_out_and_dispose
*/

void
RBTree_wipe_out_and_dispose( Prefix )( RBTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == RBTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;

   // get array of nodes
   node_t **array = nodes_as_array( current );

   // delete nodes and values
   for ( i = 0; i < (*current).count; i++ )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( ( *array[i] ).value );
      node_dispose( &array[i] );
   }

   // delete array
   free( array );

   // delete cursors, all but first
   RBTree_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   RBTree_cursor_type( Prefix ) *next_cursor = NULL;
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

