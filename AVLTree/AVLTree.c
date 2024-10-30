/**
 @file AVLTree.c
 @author Greg Lee
 @version 2.0.0
 @brief: "AVL Binary Search Trees"

 @date: "$Mon Jan 01 15:25:21 PST 2018 @17 /Internet Time/$"

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

 Function definitions for the opaque AVLTree_t type.

*/

#include "AVLTree.h"

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
   Type value;
   int32_t balance;
   struct node *parent;
   struct node *left;
   struct node *right;
};

typedef struct node node_t;

struct AVLTree_cursor_struct( Prefix );

/**
   Binary search tree structure definition.
*/

struct AVLTree_struct( Prefix )
{

   PROTOCOLS_DEFINITION;

   int32_t _type;
   int32_t _item_type;

   node_t *root;
   int32_t count;
   AVLTree_cursor_type( Prefix ) *first_cursor;
   AVLTree_cursor_type( Prefix ) *last_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure definition. Holds reference to avltree, current node, node
   stack, and a pointer to the next cursor.
*/

struct AVLTree_cursor_struct( Prefix )
{
   AVLTree_type( Prefix ) *avltree;
   node_t *item;
   AVLTree_cursor_type( Prefix ) *next_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Local Function Prototypes
*/

static
void
cursor_start( AVLTree_cursor_type( Prefix ) *cursor );

static
void
cursor_forth( AVLTree_cursor_type( Prefix ) *cursor );

static
int32_t
cursor_off(  AVLTree_cursor_type( Prefix ) *cursor );

static
Type
cursor_item_at( AVLTree_cursor_type( Prefix ) *cursor );

static
node_t *
rotate_left( AVLTree_type( Prefix ) *avltree, node_t *node );

static
node_t *
rotate_right( AVLTree_type( Prefix ) *avltree, node_t *node );

static
node_t *
rotate_left_right( AVLTree_type( Prefix ) *avltree, node_t *node );

static
node_t *
rotate_right_left( AVLTree_type( Prefix ) *avltree, node_t *node );

/**
   node_make

   make a new node to hold a value

   @return the newly created node
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

   dispose of a node

   @param node reference to the node to dispose
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

   determine if the tree has a node with the specified value, recursive

   @param node the current node being searched
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
   if ( (*node).left != NULL )
   {
      result = has_recurse( (*node).left, value );
   }

   if ( result == 0 )
   {
      result = VALUE_DEEP_EQUAL_FUNCTION( (*node).value, value );
   }

   if ( result == 0 )
   {
      if ( (*node).right != NULL )
      {
         result = has_recurse( (*node).right, value );
      }
   }
   return result;
}

/**
   has

   Return 1 if avltree has an item for value, 0 if not

   @param current AVLTree_t instance
   @param key the key to query for
*/
static
int32_t
has( AVLTree_type( Prefix ) *current, Type value )
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      result = has_recurse( node, value );
   }

   return result;
}

/**
   has_eq_fn_recurse

   determine if the tree has a node with the specified value,
   uses the supplied equality function, recursive

   @param node the current node being searched
   @param value the value to search for
   @param equality_test_func the function to determine value equality
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
   if ( (*node).left != NULL )
   {
      result = has_eq_fn_recurse( (*node).left, value, equality_test_func );
   }

   if ( result == 0 )
   {
      result = equality_test_func( (*node).value, value );
   }

   if ( result == 0 )
   {
      if ( (*node).right != NULL )
      {
         result = has_eq_fn_recurse( (*node).right, value, equality_test_func );
      }
   }
   return result;
}

/**
   has_eq_fn

   determine if the tree has a node with the specified value,
   uses the supplied equality function

   @param current AVLTree_t instance
   @param value the value to query for
   @param equality_test_func the function to determine value equality
   @return 1 if value found, 0 otherwise
*/

static
int32_t
has_eq_fn
(
   AVLTree_type( Prefix ) *current,
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
      result = has_eq_fn_recurse( node, value, equality_test_func );
   }

   return result;
}

/**
   occurrences_recurse

   counts number of nodes with the specified value, recursive

   @param node the current node being searched
   @param value the value to search for
   @param count pointer to the count of occurrences found so far
*/
static
void
occurrences_recurse( node_t *node, Type value, int32_t *count )
{
   // in order recursion - left, self, right
   // if tested value is found, count it
   if ( (*node).left != NULL )
   {
      occurrences_recurse( (*node).left, value, count );
   }

   if ( VALUE_DEEP_EQUAL_FUNCTION( (*node).value, value ) == 1 )
   {
      *count = *count + 1;
   }

   if ( (*node).right != NULL )
   {
      occurrences_recurse( (*node).right, value, count );
   }

   return;
}

/**
   occurrences

   Return count of items in avltree equal to value

   @param current AVLTree_t instance
   @param key the key to query for
   @return the count of items count
*/

static
int32_t
occurrences( AVLTree_type( Prefix ) *current, Type value )
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      occurrences_recurse( node, value, &result );
   }

   return result;
}

/**
   occurrences_eq_fn_recurse

   counts number of nodes with the specified value, recursive

   @param node the current node being searched
   @param value the value to search for
   @param count pointer to the count of occurrences found so far
   @param equality_test_func the function to determine value equality
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
   if ( (*node).left != NULL )
   {
      occurrences_eq_fn_recurse( (*node).left, value, count, equality_test_func );
   }

   if ( equality_test_func( (*node).value, value ) == 1 )
   {
      *count = *count + 1;
   }

   if ( (*node).right != NULL )
   {
      occurrences_eq_fn_recurse( (*node).right, value, count, equality_test_func );
   }

   return;
}

/**
   occurrences_eq_fn

   Return count of items in avltree equal to value according to equality_test_func

   @param current AVLTree_t instance
   @param key the key to query for
   @param equality_test_func the test function for value equality
   @return the count of items count
*/

static
int32_t
occurrences_eq_fn
(
   AVLTree_type( Prefix ) *current,
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
      occurrences_eq_fn_recurse( node, value, &result, equality_test_func );
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
node_for_index( AVLTree_type( Prefix ) *current, int32_t index )
{
   int32_t i = 0;
   node_t *result = NULL;

   // get cursor
   AVLTree_cursor_type( Prefix ) *c
      =  ( AVLTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );

   // set avltree in cursor
   (*c).avltree = current;

   if ( ( index < 0 ) || ( index >= (*current).count ) )
   {
      result = NULL;
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

   Return index of specified node

   @param current the tree
   @param node the specified node
   @return the index of the specified node
*/
static
int32_t
index_for_node( AVLTree_type( Prefix ) *current, node_t *node )
{
   int32_t result = 0;
   int32_t flag = 0;

   // get cursor
   AVLTree_cursor_type( Prefix ) *c
      =  ( AVLTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_cursor_type( Prefix ) ) );
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

   Return node with specified value, recursive

   @param current the tree
   @param value the specified value
   @return the desired node
*/
static
node_t *
item_recurse( node_t *node, Type value )
{
   node_t *result = NULL;

   if ( VALUE_DEEP_EQUAL_FUNCTION( value, (*node).value ) == 1 )
   {
      result = node;
   }

   if ( result == NULL )
   {
      if ( ORDER_FUNCTION( value, (*node).value ) == 1 )
      {

         if ( (*node).left != NULL )
         {
            result = item_recurse( (*node).left, value );
         }
      }
   }

   if ( result == NULL )
   {
      if ( ORDER_FUNCTION( value, (*node).value ) == 0 )
      {

         if ( (*node).right != NULL )
         {
            result = item_recurse( (*node).right, value );
         }
      }
   }

   return result;
}

/**
   item

   Return node in avltree that has value, NULL if none

   @param current AVLTree_t instance
   @param value the value to look for
   @return the desired node
*/

static
node_t *
item( AVLTree_type( Prefix ) *current, Type value )
{
   node_t *result = NULL;
   node_t *node = NULL;

   // get root node
   node = (*current).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      result = item_recurse( node, value );
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
   node_t *temp = NULL;
   node_t *n = NULL;

   if ( VALUE_DEEP_EQUAL_FUNCTION( value, (*node).value ) == 1 )
   {
      result = node;
   }

   if ( result == NULL )
   {
      if ( ORDER_FUNCTION( value, (*node).value ) == 1 )
      {

         if ( (*node).left != NULL )
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
      if ( ORDER_FUNCTION( value, (*node).value ) == 0 )
      {

         if ( (*node).right != NULL )
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
   insert_balance

   rebalance the tree after an insert

   @param current the tree
   @param node the newly inserted node
   @param balance a flag value indicating how the tree is balanced around node
*/
static
void
insert_balance( AVLTree_type( Prefix ) *current, node_t *node, int32_t balance )
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
            rotate_right( current, node );
         }
         else
         {
            rotate_left_right( current, node );
         }
         break;
      }
      else if ( new_balance == 2 )
      {
         // rotate based on balance of right child
         if ( ( *(*node).right ).balance == 1 )
         {
            rotate_left( current, node );
         }
         else
         {
            rotate_right_left( current, node );
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
delete_balance( AVLTree_type( Prefix ) *current, node_t *node, int32_t balance )
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
            node = rotate_right( current, node );
            if ( (*node).balance == 1 )
            {
               break;
            }
         }
         else
         {
            node = rotate_left_right( current, node );
         }
      }
      else if ( new_balance == 2 )
      {
         // rotate based on balance of right child
         if ( ( *(*node).right ).balance >= 0 )
         {
            node = rotate_left( current, node );
            if ( (*node).balance == -1 )
            {
               break;
            }
         }
         else
         {
            node = rotate_right_left( current, node );
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
   Type val;

   left = (*source).left;
   right = (*source).right;

   // save target value
   val = (*target).value;

   // put contents of source into target
   (*target).balance = (*source).balance;
   (*target).value = (*source).value;
   (*target).left = left;
   (*target).right = right;

   // exchange source and target value
   (*source).value = val;

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
rotate_left( AVLTree_type( Prefix ) *current, node_t *node )
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

   if ( node == (*current).root )
   {
      (*current).root = right;
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
rotate_right( AVLTree_type( Prefix ) *current, node_t *node )
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

   if ( node == (*current).root )
   {
      (*current).root = left;
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
rotate_left_right( AVLTree_type( Prefix ) *current, node_t *node )
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

   if ( node == (*current).root )
   {
      (*current).root = left_right;
   }
   else if ( (*parent).left == node )
   {
      (*parent).left = left_right;
   }
   else
   {
      (*parent).right = left_right;
   }

   if ( ( *left_right ).balance == 1 )
   {
      (*node).balance = 0;
      (*left).balance = -1;
   }
   else if ( ( *left_right ).balance == 0 )
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
rotate_right_left( AVLTree_type( Prefix ) *current, node_t *node )
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

   if ( node == (*current).root )
   {
      (*current).root = right_left;
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

   insert a value into the tree

   @param current the tree
   @param value the value to insert
*/

static
void
put( AVLTree_type( Prefix ) *current, Type value )
{
   node_t *node = NULL;
   node_t *new_node = NULL;
   node_t *left = NULL;
   node_t *right = NULL;

   // get new node
   new_node = node_make();
   ( *new_node ).value = value;

   if ( (*current).root == NULL )
   {
      (*current).root = new_node;
   }
   else
   {
      node = (*current).root;
      while ( node != NULL )
      {
         if ( ORDER_FUNCTION( value, (*node).value ) == 1 )
         {
            left = (*node).left;

            if ( left == NULL )
            {
               (*node).left = new_node;
               ( *new_node ).parent = node;
               insert_balance( current, node, -1 );
               break;
            }
            else
            {
               node = left;
            }
         }
         else if ( ORDER_FUNCTION( value, (*node).value ) == 0 )
         {
            right = (*node).right;

            if ( right == NULL )
            {
               (*node).right = new_node;
               ( *new_node ).parent = node;
               insert_balance( current, node, 1 );
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
   (*current).count = (*current).count + 1;

   return;
}

/**
   items_as_array_recurse

   fill an array with the values in the tree in order, recursive

   @param node the current node being processed
   @param array the destination array for the values
   @param index pointer to the current index
*/
static
void
items_as_array_recurse( node_t *node, Type *array, int32_t *index )
{
   // if has left child, recurse
   if ( (*node).left != NULL )
   {
      items_as_array_recurse( (*node).left, array, index );
   }

   // handle this node
   array[ *index ] = (*node).value;
   *index = *index + 1;

   // if has right child, recurse
   if ( (*node).right != NULL )
   {
      items_as_array_recurse( (*node).right, array, index );
   }

   return;
}

/**
   items_as_array

   create and return an array with the values in the tree in order

   @param current the tree
   @return the array, the last item in the array is 0 or NULL
*/

static
Type *
items_as_array( AVLTree_type( Prefix ) *current )
{
   Type *result = NULL;
   int32_t index = 0;

   result = ( Type * ) calloc( (*current).count + 1, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   if ( (*current).root != NULL )
   {
      items_as_array_recurse( (*current).root, result, &index );
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
nodes_as_array( AVLTree_type( Prefix ) *current )
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

/**
   remove

   remove a node from the tree

   @param current the tree
   @param node the node with the value to delete
   @return the node that was deleted
*/
static
node_t *
remove( AVLTree_type( Prefix ) *current, node_t *node )
{
   node_t *left = NULL;
   node_t *right = NULL;
   node_t *node_to_delete = NULL;
   node_t *parent = NULL;
   node_t *successor = NULL;
   node_t *successor_parent = NULL;
   node_t *successor_right = NULL;
   AVLTree_cursor_type( Prefix ) *cursor = NULL;

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
height( AVLTree_type( Prefix ) *current )
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
count( AVLTree_type( Prefix ) *current )
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
cursor_finish( AVLTree_cursor_type( Prefix ) *cursor )
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
cursor_start( AVLTree_cursor_type( Prefix ) *cursor )
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
   cursor_item_at
*/
static
Type
cursor_item_at( AVLTree_cursor_type( Prefix ) *cursor )
{
   // return the value for the current cursor item
   return ( *(*cursor).item ).value;
}

/**
   cursor_back
*/
static
void
cursor_back( AVLTree_cursor_type( Prefix ) *cursor )
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
cursor_forth( AVLTree_cursor_type( Prefix ) *cursor )
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
cursor_off(  AVLTree_cursor_type( Prefix ) *cursor )
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
move_all_cursors_off( AVLTree_type( Prefix ) *current )
{
   AVLTree_cursor_type( Prefix ) *cursor = (*current).first_cursor;

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
compare_tree_items_to_array_items( AVLTree_type( Prefix ) *current, Type *array, int32_t array_count )
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

   compare values in one tree to values in another tree

   @param current the tree
   @param other the other tree
   @return 1 if all values are equal, 0 otherwise
*/

static
int32_t
compare_tree_items_to_tree_items( AVLTree_type( Prefix ) *current, AVLTree_type( Prefix ) *other )
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t count = 0;
   AVLTree_cursor_type( Prefix ) *c1
      =  ( AVLTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_cursor_type( Prefix ) ) );
   CHECK( "c1 allocated correctly", c1 != NULL );


   AVLTree_cursor_type( Prefix ) *c2
      =  ( AVLTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_cursor_type( Prefix ) ) );
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

   compare values in one tree to values in another tree, deep_equal

   @param current the tree
   @param other the other tree
   @return 1 if all values are equal, 0 otherwise
*/
static
int32_t
compare_tree_items_to_tree_items_deep_equal( AVLTree_type( Prefix ) *current, AVLTree_type( Prefix ) *other )
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t count = 0;
   AVLTree_cursor_type( Prefix ) *c1
      =  ( AVLTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_cursor_type( Prefix ) ) );
   CHECK( "c1 allocated correctly", c1 != NULL );


   AVLTree_cursor_type( Prefix ) *c2
      =  ( AVLTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_cursor_type( Prefix ) ) );
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
is_empty_implies_root_null( AVLTree_type( Prefix ) *p )
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
nonnegative_count( AVLTree_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
valid_count( AVLTree_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( count( p ) == (*p).count );

   return result;
}

static
int32_t
first_cursor_not_null( AVLTree_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).first_cursor != NULL );

   return result;
}

static
int32_t
last_cursor_null_if_one_cursor( AVLTree_type( Prefix ) *p )
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
cursors_avltree_ok( AVLTree_type( Prefix ) *p )
{
   int32_t result = 1;

   AVLTree_cursor_type( Prefix ) *cursor = (*p).first_cursor;

   while( ( cursor != NULL ) && ( result == 1 ) )
   {
      result = ( (*cursor).avltree == p );
      cursor = (*cursor).next_cursor;
   }

   return result;
}

static
int32_t
last_cursor_next_null( AVLTree_type( Prefix ) *p )
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
      result = ORDER_FUNCTION( ( *(*node).left ).value, (*node).value );
   }

   if ( result == 1 )
   {
      if ( (*node).right != NULL )
      {
         result = ORDER_FUNCTION( (*node).value, ( *(*node).right ).value );
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
in_order( AVLTree_type( Prefix ) *p )
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
balance_ok( AVLTree_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).count > 1 )
   {
      result = balance_recurse( (*p).root );
   }

   return result;
}

/**
   cursors_off_or_valid
*/

static
int32_t
cursors_off_or_valid( AVLTree_type( Prefix ) *current )
{
   int32_t result = 1;
   AVLTree_cursor_type( Prefix ) *cursor = NULL;

   // get cursor
   AVLTree_cursor_type( Prefix ) *c
      =  ( AVLTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_cursor_type( Prefix ) ) );
   CHECK( "c allocated correctly", c != NULL );

   // set avltree in cursor
   (*c).avltree = current;

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
node_pointers_consistent( AVLTree_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).count > 1 )
   {
      result = node_pointers_consistent_recurse( (*current).root );
   }

   return result;
}

static
void invariant( AVLTree_type( Prefix ) *current )
{
   assert( ( ( void ) "empty implies root null", is_empty_implies_root_null( current ) ) );
   assert( ( ( void ) "nonnegative count", nonnegative_count( current ) ) );
   assert( ( ( void ) "valid count", valid_count( current ) ) );
   assert( ( ( void ) "first cursor not null", first_cursor_not_null( current ) ) );
   assert( ( ( void ) "last cursor next null", last_cursor_next_null( current ) ) );
   assert( ( ( void ) "last cursor null if one cursor", last_cursor_null_if_one_cursor( current ) ) );
   assert( ( ( void ) "cursors avltree OK", cursors_avltree_ok( current ) ) );
   assert( ( ( void ) "avltree in order", in_order( current ) ) );
   assert( ( ( void ) "avltree in balance", balance_ok( current ) ) );
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
   protocol function arrays
*/

static
void *
p_basic_table[P_BASIC_FUNCTION_COUNT]
=
{
   AVLTree_dispose( Prefix ),
   AVLTree_deep_dispose( Prefix ),
   AVLTree_is_equal( Prefix ),
   AVLTree_is_deep_equal( Prefix ),
   AVLTree_copy( Prefix ),
   AVLTree_deep_copy( Prefix ),
   AVLTree_clone( Prefix ),
   AVLTree_deep_clone( Prefix )
};

static
void *
p_iterable_table[P_ITERABLE_FUNCTION_COUNT]
=
{
   AVLTree_count( Prefix ),
   AVLTree_item_at( Prefix ),
   AVLTree_off( Prefix ),
   AVLTree_is_empty( Prefix ),
   AVLTree_start( Prefix ),
   AVLTree_forth( Prefix )
};

static
void *
p_diterable_table[P_DITERABLE_FUNCTION_COUNT]
=
{
   AVLTree_count( Prefix ),
   AVLTree_item_at( Prefix ),
   AVLTree_off( Prefix ),
   AVLTree_is_empty( Prefix ),
   AVLTree_start( Prefix ),
   AVLTree_forth( Prefix ),
   AVLTree_finish( Prefix ),
   AVLTree_back( Prefix )
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
   AVLTree_make
*/

AVLTree_type( Prefix ) *
AVLTree_make( Prefix )( void )
{
   // allocate current struct
   AVLTree_type( Prefix ) *current
      = ( AVLTree_type( Prefix ) * ) calloc( 1, sizeof( AVLTree_type( Prefix ) ) );
   CHECK( "current allocated correctly", current != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( current );

   // set type codes
   (*current)._type = AVLTREE_TYPE;
   (*current)._item_type = Type_Code;

   // root is null
   (*current).root = NULL;

   // count is zero
   (*current).count = 0;

   // set built-in cursor
   // allocate cursor struct
   AVLTree_cursor_type( Prefix ) *cursor
      =  ( AVLTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set current
   (*cursor).avltree = current;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set current built-in cursor
   (*current).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   INVARIANT( current );

   return current;
}

/**
   AVLTree_make_from_array
*/

AVLTree_type( Prefix ) *
AVLTree_make_from_array( Prefix )( Type *array, int32_t count )
{
   PRECONDITION( "array not null", array != NULL );
   PRECONDITION( "count ok", count >= 0 );

   // make avltree struct
   AVLTree_type( Prefix ) *result = AVLTree_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = AVLTREE_TYPE;
   (*result)._item_type = Type_Code;

   int32_t i = 0;

   for ( i = 0; i < count; i++ )
   {
      put( result, array[i] );
   }

   POSTCONDITION( "new result cursor is off", ( *(*result).first_cursor ).item == NULL );
   POSTCONDITION( "new result contains elements of array", compare_tree_items_to_array_items( result, array, count ) );

   INVARIANT( result );

   return result;
}

/**
   AVLTree_clone
*/

AVLTree_type( Prefix ) *
AVLTree_clone( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );

   // make current struct
   AVLTree_type( Prefix ) *result = AVLTree_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = AVLTREE_TYPE;
   (*result)._item_type = Type_Code;

   // copy from current
   AVLTree_cursor_type( Prefix ) *cursor = AVLTree_cursor_make( Prefix )( current );

   // lock mutex
   LOCK( (*current).mutex );

   INVARIANT( current );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, cursor_item_at( cursor ) );
      cursor_forth( cursor );
   }

   INVARIANT( result );

   // unlock mutex
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_deep_clone
*/

AVLTree_type( Prefix ) *
AVLTree_deep_clone( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );

   INVARIANT( current );

   // make current struct
   AVLTree_type( Prefix ) *result = AVLTree_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = AVLTREE_TYPE;
   (*result)._item_type = Type_Code;

   // copy from current
   AVLTree_cursor_type( Prefix ) *cursor = AVLTree_cursor_make( Prefix )( current );

   // lock mutex
   LOCK( (*current).mutex );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, VALUE_DEEP_CLONE_FUNCTION( cursor_item_at( cursor ) ) );
      cursor_forth( cursor );
   }

   // unlock mutex
   UNLOCK( (*current).mutex );

   INVARIANT( result );

   return result;
}

/**
   AVLTree_is_equal
*/

int32_t
AVLTree_is_equal( Prefix )( AVLTree_type( Prefix ) *current, AVLTree_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == AVLTREE_TYPE ) && ( (*other)._item_type = Type_Code ) );

   // lock mutex
   LOCK( (*current).mutex );

   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {

      // lock other mutex
      LOCK( (*other).mutex );

      result = compare_tree_items_to_tree_items( current, other );

      // unlock other mutex
      UNLOCK( (*other).mutex );

      INVARIANT( current );

   }

   // unlock mutex
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_is_deep_equal
*/

int32_t
AVLTree_is_deep_equal( Prefix )( AVLTree_type( Prefix ) *current, AVLTree_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == AVLTREE_TYPE ) && ( (*other)._item_type = Type_Code ) );

   // lock mutex
   LOCK( (*current).mutex );

   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other mutex
      LOCK( (*other).mutex );

      result = compare_tree_items_to_tree_items_deep_equal( current, other );

      // unlock mutexes
      UNLOCK( (*other).mutex );

      INVARIANT( current );
   }

   // unlock mutex
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_copy
*/

void
AVLTree_copy( Prefix )( AVLTree_type( Prefix ) *current, AVLTree_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == AVLTREE_TYPE ) && ( (*other)._item_type = Type_Code ) );

   // lock current
   LOCK( (*current).mutex );

   INVARIANT( current );

   int32_t i = 0;

   if ( current != other )
   {
      AVLTree_cursor_type( Prefix ) *c
         =  ( AVLTree_cursor_type( Prefix ) * )
            calloc( 1, sizeof( AVLTree_cursor_type( Prefix ) ) );
      CHECK( "c allocated correctly", c != NULL );

      (*c).avltree = other;

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
      (*current).root = NULL;

      cursor_start( c );

      while ( cursor_off( c ) == 0 )
      {
         put( current, cursor_item_at( c ) );
         cursor_forth( c );
      }

      // free c
      free( c );

      POSTCONDITION( "new avltree contains elements of other", compare_tree_items_to_tree_items( current, other ) );

      // unlock mutexes
      UNLOCK( (*other).mutex );

      INVARIANT( current );
   }

   // unlock mutex
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_deep_copy
*/

void
AVLTree_deep_copy( Prefix )( AVLTree_type( Prefix ) *current, AVLTree_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == AVLTREE_TYPE ) && ( (*other)._item_type = Type_Code ) );

   // lock current
   LOCK( (*current).mutex );

   INVARIANT( current );

   int32_t i = 0;

   if ( current != other )
   {

      Type v;
      AVLTree_cursor_type( Prefix ) *c
         =  ( AVLTree_cursor_type( Prefix ) * )
            calloc( 1, sizeof( AVLTree_cursor_type( Prefix ) ) );
      CHECK( "c allocated correctly", c != NULL );

      (*c).avltree = other;

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
      (*current).root = NULL;

      cursor_start( c );

      while ( cursor_off( c ) == 0 )
      {
         v = VALUE_DEEP_CLONE_FUNCTION( cursor_item_at( c ) );
         put( current, v );
         cursor_forth( c );
      }

      // free cursor
      free( c );

      POSTCONDITION( "new avltree contains elements of other", compare_tree_items_to_tree_items_deep_equal( current, other ) );

      // unlock mutexes
      UNLOCK( (*other).mutex );

      INVARIANT( current );
   }

   // unlock mutex
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_cursor_make
*/

AVLTree_cursor_type( Prefix ) *
AVLTree_cursor_make( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // allocate cursor struct
   AVLTree_cursor_type( Prefix ) *cursor
      =  ( AVLTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set avltree
   (*cursor).avltree = current;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // place cursor reference into avltree structure
   if ( (*current).last_cursor == NULL )
   {
      // set second cursor for avltree
      ( *(*current).first_cursor ).next_cursor = cursor;
      (*current).last_cursor = cursor;
   }
   else
   {
      // set additional cursor for avltree
      // (*avltree).last_cursor holds last cursor allocated
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
   AVLTree_dispose
*/

void
AVLTree_dispose( Prefix )( AVLTree_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == AVLTREE_TYPE ) && ( (**current)._item_type = Type_Code ) );
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
   AVLTree_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   AVLTree_cursor_type( Prefix ) *next_cursor = NULL;
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
   AVLTree_deep_dispose
*/

void
AVLTree_deep_dispose( Prefix )( AVLTree_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == AVLTREE_TYPE ) && ( (**current)._item_type = Type_Code ) );
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
   AVLTree_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   AVLTree_cursor_type( Prefix ) *next_cursor = NULL;
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
   AVLTree_cursor_dispose
*/

void
AVLTree_cursor_dispose( Prefix )( AVLTree_cursor_type( Prefix ) **cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "*cursor not null", *cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(**cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(**cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (**cursor).mutex );
   LOCK( ( *(**cursor).avltree ).mutex );
   INVARIANT( (**cursor).avltree );

   AVLTree_type( Prefix ) *current = (**cursor).avltree;

   AVLTree_cursor_type( Prefix ) *c1 = NULL;
   AVLTree_cursor_type( Prefix ) *c2 = NULL;
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

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_as_array

*/

Type *
AVLTree_as_array( Prefix )( AVLTree_type( Prefix ) *current, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type *result = items_as_array( current );

   *count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_cursor_item_at
*/

Type
AVLTree_cursor_item_at( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
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
   AVLTree_item_at
*/

Type
AVLTree_item_at( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   AVLTree_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   Type value = cursor_item_at( cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   AVLTree_item
*/

Type
AVLTree_item( Prefix )( AVLTree_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_first
*/

Type
AVLTree_first( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_last
*/

Type
AVLTree_last( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_count
*/

int32_t
AVLTree_count( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   AVLTree_height
*/

int32_t
AVLTree_height( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = height( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   AVLTree_off
*/

int32_t
AVLTree_off( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = cursor_off( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_cursor_off
*/

int32_t
AVLTree_cursor_off( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   int32_t result = cursor_off( cursor );

   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AVLTree_cursor_is_first
*/

int32_t
AVLTree_cursor_is_first( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
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
   AVLTree_cursor_is_last
*/

int32_t
AVLTree_cursor_is_last( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
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
   AVLTree_cursor_search_forth
*/

void
AVLTree_cursor_search_forth( Prefix )( AVLTree_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
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
   AVLTree_cursor_search_forth_eq_fn
*/

void
AVLTree_cursor_search_forth_eq_fn( Prefix )
(
   AVLTree_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
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
   AVLTree_cursor_search_back
*/

void
AVLTree_cursor_search_back( Prefix )( AVLTree_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
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
   AVLTree_cursor_search_back_eq_fn
*/

void
AVLTree_cursor_search_back_eq_fn( Prefix )
(
   AVLTree_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
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
   AVLTree_is_empty
*/

int32_t
AVLTree_is_empty( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count ==  0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_is_first
*/

int32_t
AVLTree_is_first( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_is_last
*/

int32_t
AVLTree_is_last( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_has
*/

int32_t
AVLTree_has( Prefix )( AVLTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_has_eq_fn
*/

int32_t
AVLTree_has_eq_fn( Prefix )
(
   AVLTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = has_eq_fn( current, value, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_occurrences
*/

int32_t
AVLTree_occurrences( Prefix )( AVLTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_occurrences_eq_fn
*/

int32_t
AVLTree_occurrences_eq_fn( Prefix )
(
   AVLTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = occurrences_eq_fn( current, value, equality_test_func );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_search_forth
*/

void
AVLTree_search_forth( Prefix )( AVLTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_search_forth_eq_fn
*/

void
AVLTree_search_forth_eq_fn( Prefix )
(
   AVLTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_search_back
*/

void
AVLTree_search_back( Prefix )( AVLTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_search_back_eq_fn
*/

void
AVLTree_search_back_eq_fn( Prefix )
(
   AVLTree_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
      cursor_back( (*current).first_cursor );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_cursor_forth
*/
void
AVLTree_cursor_forth( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( ( *(*cursor).avltree ).mutex );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).avltree );

   cursor_forth( cursor );

   INVARIANT( (*cursor).avltree );
   UNLOCK( (*cursor).mutex );
   UNLOCK( ( *(*cursor).avltree ).mutex );

   return;
}

/**
   AVLTree_cursor_back
*/
void
AVLTree_cursor_back( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( ( *(*cursor).avltree ).mutex );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).avltree );

   cursor_back( cursor );

   INVARIANT( (*cursor).avltree );
   UNLOCK( (*cursor).mutex );
   UNLOCK( ( *(*cursor).avltree ).mutex );

   return;
}

/**
   AVLTree_cursor_go
*/
void
AVLTree_cursor_go( Prefix )( AVLTree_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( ( *(*cursor).avltree ).mutex );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).avltree );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < ( *(*cursor).avltree ).count ) ) );

   int32_t i = 0;
   cursor_start( cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).avltree );
   UNLOCK( (*cursor).mutex );
   UNLOCK( ( *(*cursor).avltree ).mutex );

   return;
}

/**
   AVLTree_cursor_go_to_value
*/
void
AVLTree_cursor_go_to_value( Prefix )( AVLTree_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) );
   LOCK( ( *(*cursor).avltree ).mutex );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).avltree );
   POSTCONDITION_VARIABLE_DEFINE( AVLTree_cursor_type( Prefix ) c; c.avltree = (*cursor).avltree; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_empty = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_first = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_last = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_equal = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_lt = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_gt = 0; );

   node_t *node = NULL;

   if ( ( *(*cursor).avltree ).root != NULL )
   {
      node = node_for_value_recurse( ( *(*cursor).avltree ).root, value );
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
   if ( VALUE_DEEP_EQUAL_FUNCTION( value, (*node).value ) == 1 )
      {
         is_equal = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( node != NULL )
{
   if ( ORDER_FUNCTION( (*node).value, value ) == 1 )
      {
         is_lt = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( c.item != NULL )
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

   INVARIANT( (*cursor).avltree );
   UNLOCK( ( *(*cursor).avltree ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_cursor_index
*/

int32_t
AVLTree_cursor_index( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( ( *(*cursor).avltree ).mutex );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).avltree );

   int32_t result = 0;

   result = index_for_node( (*cursor).avltree, (*cursor).item );

   INVARIANT( (*cursor).avltree );
   UNLOCK( (*cursor).mutex );
   UNLOCK( ( *(*cursor).avltree ).mutex );

   return result;
}

/**
   AVLTree_cursor_start
*/

void
AVLTree_cursor_start( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( ( *(*cursor).avltree ).mutex );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).avltree );

   cursor_start( cursor );

   INVARIANT( (*cursor).avltree );
   UNLOCK( (*cursor).mutex );
   UNLOCK( ( *(*cursor).avltree ).mutex );

   return;
}

/**
   AVLTree_cursor_finish
*/

void
AVLTree_cursor_finish( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) ) );
   LOCK( ( *(*cursor).avltree ).mutex );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).avltree );

   cursor_finish( cursor );

   INVARIANT( (*cursor).avltree );
   UNLOCK( (*cursor).mutex );
   UNLOCK( ( *(*cursor).avltree ).mutex );

   return;
}

/**
   AVLTree_cursor_remove_at
*/

void
AVLTree_cursor_remove_at( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "current type ok", ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) );
   LOCK( ( *(*cursor).avltree ).mutex );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).avltree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *(*cursor).item ).value; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( (*cursor).avltree, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).avltree ).count; );

   node_t *node = NULL;
   node = (*cursor).item;

   node = remove( (*cursor).avltree, node );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( (*cursor).avltree, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == ( *(*cursor).avltree ).count + 1 );

   INVARIANT( (*cursor).avltree );
   UNLOCK( (*cursor).mutex );
   UNLOCK( ( *(*cursor).avltree ).mutex );

   return;
}

/**
   AVLTree_cursor_remove_at_and_dispose
*/

void
AVLTree_cursor_remove_at_and_dispose( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "current type ok", ( ( *(*cursor).avltree )._type == AVLTREE_TYPE ) && ( ( *(*cursor).avltree )._item_type = Type_Code ) );
   LOCK( ( *(*cursor).avltree ).mutex );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).avltree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = VALUE_DEEP_CLONE_FUNCTION( ( *(*cursor).item ).value ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = occurrences( (*cursor).avltree, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).avltree ).count; );

   node_t *node = NULL;
   node = (*cursor).item;
   cursor_forth( cursor );

   node = remove( (*cursor).avltree, node );

   // dispose of the value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of the node
   node_dispose( &node );

   POSTCONDITION( "element removed", i_pc == occurrences( (*cursor).avltree, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == ( *(*cursor).avltree ).count + 1 );
   POSTCONDITION_VARIABLE_DISPOSE( VALUE_DEEP_DISPOSE_FUNCTION( val_pc ); );

   INVARIANT( (*cursor).avltree );
   UNLOCK( (*cursor).mutex );
   UNLOCK( ( *(*cursor).avltree ).mutex );

   return;
}

/**
   AVLTree_forth
*/
void
AVLTree_forth( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   cursor_forth( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_back
*/
void
AVLTree_back( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   cursor_back( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_go
*/
void
AVLTree_go( Prefix )( AVLTree_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_go_to_value
*/
void
AVLTree_go_to_value( Prefix )( AVLTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( AVLTree_cursor_type( Prefix ) c; c.avltree = current; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_empty = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_first = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_last = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_equal = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_lt = 0; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t is_gt = 0; );

   node_t *node = NULL;

   if ( (*current).root != NULL )
   {
      node = node_for_value_recurse( (*current).root, value );
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
   if ( VALUE_DEEP_EQUAL_FUNCTION( value, (*node).value ) == 1 )
      {
         is_equal = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( node != NULL )
{
   if ( ORDER_FUNCTION( (*node).value, value ) == 1 )
      {
         is_lt = 1;
      }
   } );
   POSTCONDITION_VARIABLE_DEFINE( if ( c.item != NULL )
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
   AVLTree_index
*/

int32_t
AVLTree_index( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = index_for_node( current, ( *(*current).first_cursor ).item );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AVLTree_start
*/

void
AVLTree_start( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cursor_start( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_finish
*/

void
AVLTree_finish( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cursor_finish( (*current).first_cursor );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_put
*/

void
AVLTree_put( Prefix )( AVLTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   put( current, value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_remove
*/

void
AVLTree_remove( Prefix )( AVLTree_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_remove_and_dispose
*/

void
AVLTree_remove_and_dispose( Prefix )( AVLTree_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_remove_value
*/

void
AVLTree_remove_value( Prefix )( AVLTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has( current, value ) );

   node_t *node = NULL;

   node = item( current, value );

   node = remove( current, node );

   // dispose of node
   node_dispose( &node );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_remove_value_and_dispose
*/

void
AVLTree_remove_value_and_dispose( Prefix )( AVLTree_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has value", has( current, value ) );

   node_t *node = NULL;

   node = item( current, value );

   node = remove( current, node );

   // dispose of value
   VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );

   // dispose of node
   node_dispose( &node );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AVLTree_remove_at
*/

void
AVLTree_remove_at( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_remove_at_and_dispose
*/

void
AVLTree_remove_at_and_dispose( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_remove_first
*/

void
AVLTree_remove_first( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_remove_first_and_dispose
*/

void
AVLTree_remove_first_and_dispose( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_remove_last
*/

void
AVLTree_remove_last( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_remove_last_and_dispose
*/

void
AVLTree_remove_last_and_dispose( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_wipe_out
*/

void
AVLTree_wipe_out( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   AVLTree_cursor_type( Prefix ) *next_cursor = NULL;
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
   AVLTree_wipe_out_and_dispose
*/

void
AVLTree_wipe_out_and_dispose( Prefix )( AVLTree_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == AVLTREE_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   AVLTree_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   AVLTree_cursor_type( Prefix ) *next_cursor = NULL;
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

