/**
 @file BSTree.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Binary Search Trees"
 
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

 Function definitions for the opaque BSTree_t type.

*/

#include "BSTree.h"

#ifdef PROTOCOLS_ENABLED   
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Clonable.ph"
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

#define BSTREE_TYPE 0xA5000200

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
   struct node *parent;
   struct node *left;
   struct node *right;
};

typedef struct node node_t;

struct BSTree_cursor_struct( Prefix );

/**
   Binary search tree structure definition.
*/

struct BSTree_struct( Prefix )
{
   
   PROTOCOLS_DEFINITION;

   int32_t type;
   int32_t item_type;
   
   node_t *root;
   int32_t count;
   BSTree_cursor_type( Prefix ) *first_cursor;
   BSTree_cursor_type( Prefix ) *last_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure definition. Holds reference to bstree, current node, node
   stack, and a pointer to the next cursor.
*/

struct BSTree_cursor_struct( Prefix )
{
   BSTree_type( Prefix ) *bstree;
   node_t *item;
   BSTree_cursor_type( Prefix ) *next_cursor;

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
   has_recurse
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
      result = EQUALITY_FUNCTION( (*node).value, value );
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

   Return 1 if bstree has an item for value, 0 if not

   @param bstree BSTree_t instance
   @param key the key to query for
*/

static
int32_t
has( BSTree_type( Prefix ) *bstree, Type value )
{
   int32_t result = 0;
   node_t *node = NULL;
   
   // get root node
   node = (*bstree).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      result = has_recurse( node, value );
   }
   
   return result;
}

/**
   item_recurse
*/
static
node_t *
item_recurse( node_t *node, Type value )
{
   node_t *result = NULL;
   
   if ( EQUALITY_FUNCTION( value, (*node).value ) == 1 )
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

   Return node in bstree that has value, NULL if none

   @param bstree BSTree_t instance
   @param value the value to query for
*/

static
node_t *
item( BSTree_type( Prefix ) *bstree, Type value )
{
   node_t *result = NULL;
   node_t *node = NULL;
   
   // get root node
   node = (*bstree).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      result = item_recurse( node, value );
   }
   
   return result;
}

/**
   put_recurse
*/
static
int32_t
put_recurse( node_t *node, Type value )
{
   int32_t result = 0;
   node_t *new_node = NULL;
   
   // if value is inserted, exit 
      
   // in order recursion - left, self, right
   if ( ORDER_FUNCTION( value, (*node).value ) == 1 ) // value < (*node).value
   {
      
      if ( (*node).left != NULL )
      {
         // if left node exists, recurse
         result = put_recurse( (*node).left, value );
      }
      else
      {
         // if left node does not exist, put new node with value there
         new_node = node_make();
         (*node).left = new_node;
         (*new_node).value = value;
         (*new_node).parent = node;
         result = 1;
      }
      
   }
   else // ( value > (*node).value )
   {
      
      if ( (*node).right != NULL )
      {
         // if right node exists, recurse
         result = put_recurse( (*node).right, value );
      }
      else
      {
         // if right node does not exist, put new node with value there
         new_node = node_make();
         (*node).right = new_node;
         (*new_node).value = value;
         (*new_node).parent = node;
         result = 1;
      }
      
   }
   
   return result;
}

/**
   BSTree_put
*/

static
void
put( BSTree_type( Prefix ) *bstree, Type value )
{
   node_t *node = NULL;
   node_t *new_node = NULL;
   
   // get root node
   node = (*bstree).root;

   // recurse to put value in tree
   if ( node == NULL )
   {
      new_node = node_make();
      (*bstree).root = new_node;
      (*new_node).value = value;
   }
   else
   {   
      put_recurse( node, value );
   }
   
   // adjust count
   (*bstree).count = (*bstree).count + 1;
   
   return;
}

/**
   BSTree_get_min
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
   nodes_as_array_recurse
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
*/

static
node_t **
nodes_as_array( BSTree_type( Prefix ) *bstree )
{
   node_t **result = NULL;
   int32_t index = 0;
   
   if ( (*bstree).count == 0 )
   {
      result = ( node_t ** ) calloc( 1, sizeof( node_t ) );
   }
   else
   {
      result = ( node_t ** ) calloc( (*bstree).count, sizeof( node_t ) );
   }
   
   if ( (*bstree).root != NULL )
   {
      nodes_as_array_recurse( (*bstree).root, result, &index );
   }
   
   return result;
}


/**
   remove_recurse
*/
static
void
remove_recurse( node_t *node )
{
   node_t *n = NULL;
   
   if ( ( (*node).left == NULL ) && ( (*node).right == NULL ) )
   {
      // no children, remove this node
      if ( (*(*node).parent).left == node )
      {
         // node is its parent's left child
         (*(*node).parent).left = NULL;
      }
      else
      {
         // node is its parent's right child
         (*(*node).parent).right = NULL;
      }
      
      // and dispose of the node
      node_dispose( node );    
     
   }
   else if ( ( (*node).left != NULL ) && ( (*node).right == NULL ) )
   {
      // one child, the left one
      
      // replace node with its left child
      if ( (*(*node).parent).left == node )
      {
         // node is its parent's left child
         (*(*node).parent).left = (*node).left;
      }
      else
      {
         // node is its parent's right child
         (*(*node).parent).right = (*node).left;
      }
      
      // and dispose of the node
      node_dispose( node );
      
   }
   else if ( ( (*node).left == NULL ) && ( (*node).right != NULL ) )
   {
      // one child, the right one
      
      // replace node with its right child
      if ( (*(*node).parent).left == node )
      {
         // node is its parent's left child
         (*(*node).parent).left = (*node).right;
      }
      else
      {
         // node is its parent's right child
         (*(*node).parent).right = (*node).right;
      }
      
      // and dispose of the node
      node_dispose( node );
      
   }
   else // two children
   {
      // find min from this node's right child
      n = get_min( (*node).right );
   
      // replace node value with value of min
      (*node).value = (*n).value;
      
      // recursively remove "n"
      remove_recurse( n );
      
   }
   
   return;
}

static
void
cursor_forth( BSTree_cursor_type( Prefix ) *cursor );

/**
   remove
*/
static
void
remove( BSTree_type( Prefix ) *bstree, Type value )
{
   node_t *node = NULL;
   BSTree_cursor_type( Prefix ) *cursor = NULL;
   
   node = item( bstree, value );
   
   if ( node != NULL )
   {
      // move cursors pointing to this node forth
      cursor = (*bstree).first_cursor;
      while ( cursor != NULL )
      {
         if ( (*cursor).item == node )
         {
            cursor_forth( cursor );
         }
         
         cursor = (*cursor).next_cursor;
      }

      // case of only one node (the root)
      if ( (*bstree).count == 1 )
      {
         node_dispose( node );
         (*bstree).root = NULL;
      }
      else if ( (*node).parent == NULL )
      {
         // special case of root node with one child
         if ( ( (*node).left != NULL ) && ( (*node).right == NULL ) )
         {
            (*bstree).root = (*node).left;
            node_dispose( node );
         }
         else if ( ( (*node).left == NULL ) && ( (*node).right != NULL ) )
         {
            (*bstree).root = (*node).right;
            node_dispose( node );
         }
         else
         {
            // delete the node
            remove_recurse( node );
         }
      }
      else
      {
         // delete the node
         remove_recurse( node );
      }
      
      // decrement count
      (*bstree).count = (*bstree).count - 1;
   }
   
   return;   
}

/**
   remove_and_dispose_recurse
*/
static
void
remove_and_dispose_recurse( node_t *node )
{
   node_t *n = NULL;
   
   if ( ( (*node).left == NULL ) && ( (*node).right == NULL ) )
   {
      // no children, remove this node
      if ( (*(*node).parent).left == node )
      {
         // node is its parent's left child
         (*(*node).parent).left = NULL;
      }
      else
      {
         // node is its parent's right child
         (*(*node).parent).right = NULL;
      }
      
      // dispose of the value
      DISPOSE_FUNCTION( (*node).value );
      
      // and dispose of the node
      node_dispose( node );    
     
   }
   else if ( ( (*node).left != NULL ) && ( (*node).right == NULL ) )
   {
      // one child, the left one
      
      // replace node with its left child
      if ( (*(*node).parent).left == node )
      {
         // node is its parent's left child
         (*(*node).parent).left = (*node).left;
      }
      else
      {
         // node is its parent's right child
         (*(*node).parent).right = (*node).left;
      }
      
      // dispose of the value
      DISPOSE_FUNCTION( (*node).value );
      
      // and dispose of the node
      node_dispose( node );
      
   }
   else if ( ( (*node).left == NULL ) && ( (*node).right != NULL ) )
   {
      // one child, the right one
      
      // replace node with its right child
      if ( (*(*node).parent).left == node )
      {
         // node is its parent's left child
         (*(*node).parent).left = (*node).right;
      }
      else
      {
         // node is its parent's right child
         (*(*node).parent).right = (*node).right;
      }
      
      // dispose of the value
      DISPOSE_FUNCTION( (*node).value );
      
      // and dispose of the node
      node_dispose( node );
      
   }
   else // two children
   {
      // find min from this node's right child
      n = get_min( (*node).right );
   
      // replace node value with value of min
      (*node).value = (*n).value;
      
      // recursively remove "n"
      remove_and_dispose_recurse( n );
      
   }
   
   return;
}

/**
   remove_and_dispose
*/
static
void
remove_and_dispose( BSTree_type( Prefix ) *bstree, Type value )
{
   node_t *node = NULL;
   BSTree_cursor_type( Prefix ) *cursor = NULL;
   
   node = item( bstree, value );
   
   if ( node != NULL )
   {
      // move cursors pointing to this node forth
      cursor = (*bstree).first_cursor;
      while ( cursor != NULL )
      {
         if ( (*cursor).item == node )
         {
            cursor_forth( cursor );
         }
         
         cursor = (*cursor).next_cursor;
      }

      // case of only one node
      if ( (*bstree).count == 1 )
      {
         DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
         (*bstree).root = NULL;
      }
      else if ( (*node).parent == NULL )
      {
         // special case of root node with one child
         if ( ( (*node).left != NULL ) && ( (*node).right == NULL ) )
         {
            (*bstree).root = (*node).left;
            DISPOSE_FUNCTION( (*node).value );
            node_dispose( node );
         }
         else if ( ( (*node).left == NULL ) && ( (*node).right != NULL ) )
         {
            (*bstree).root = (*node).right;
            DISPOSE_FUNCTION( (*node).value );
            node_dispose( node );
         }
         else
         {
            // delete the node
            remove_recurse( node );
         }
      }
      else
      {
         // delete the node
         remove_and_dispose_recurse( node );
      }
      
      // decrement count
      (*bstree).count = (*bstree).count - 1;
   }
   
   return;   
}

/**
   height_recurse
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
*/
static
int 
height( BSTree_type( Prefix ) *bstree )
{
   int32_t result = 0;
   
   result = height_recurse( (*bstree).root );
   
   return result;
}

/**
   count_recurse
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
*/
static
int 
count( BSTree_type( Prefix ) *bstree )
{
   int32_t result = 0;
   
   result = count_recurse( (*bstree).root );
   
   return result;
}

/**
   compression DSW algorithm
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
   
   return result/2;
}

/**
   tree_to_vine
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
*/
static
void 
vine_to_tree( node_t *root, int32_t size )
{  
   int32_t full_count = 0;
   
   // get size of full binary tree
   full_count = full_size( size );
   
   // first pass
   compression(root, size - full_count);
   
   // iteratively flatten tree
   for ( size = full_count; size > 1; size /= 2 )
   {
      compression( root, size / 2 );
   }
   
   return;
}

/**
   balance
*/
static
void
balance( BSTree_type( Prefix ) *bstree )
{
   if ( (*bstree).count > 1 )
   {
      node_t *node = NULL;
      
      // add pseudo-root
      node = node_make();
      (*node).right = (*bstree).root;
      (*bstree).root = node;
  
      // tree to vine
      tree_to_vine( (*bstree).root );
      
      // vine to tree
      vine_to_tree( (*bstree).root, (*bstree).count );
      
      // remove pseudo-root
      (*bstree).root = (*node).right;
      node_dispose( node );
      
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
cursor_finish( BSTree_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;
   
   // set node from the bstree root
   node = (*(*cursor).bstree).root;
   
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
cursor_start( BSTree_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;
   
   // set node from the bstree root
   node = (*(*cursor).bstree).root;
   
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
   cursor_item
*/
static
Type
cursor_item( BSTree_cursor_type( Prefix ) *cursor )
{
   // return the value for the current cursor item
   return (*(*cursor).item).value;
}


/**
   cursor_back
*/
static
void
cursor_back( BSTree_cursor_type( Prefix ) *cursor )
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
cursor_forth( BSTree_cursor_type( Prefix ) *cursor )
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
cursor_off(  BSTree_cursor_type( Prefix ) *cursor )
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
is_empty_implies_root_null( BSTree_type( Prefix ) *p )
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
nonnegative_count( BSTree_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
valid_count( BSTree_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( count( p ) == (*p).count );

   return result;
}

static
int32_t
first_cursor_not_null( BSTree_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).first_cursor != NULL );

   return result;
}

static
int32_t
cursors_bstree_ok( BSTree_type( Prefix ) *p )
{
   int32_t result = 1;

   BSTree_cursor_type( Prefix ) *cursor = (*p).first_cursor;

   while( ( cursor != NULL ) && ( result == 1 ) )
   {
      result = ( (*cursor).bstree == p );
      cursor = (*cursor).next_cursor;
   }

   return result;
}

static
int32_t
last_cursor_next_null( BSTree_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).last_cursor != NULL )
   {
      result = ( (*(*p).last_cursor).next_cursor == NULL );
   }

   return result;
}

static
int32_t
last_cursor_null_if_one_cursor( BSTree_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*(*p).first_cursor).next_cursor == NULL )
   {
      result = ( (*p).last_cursor == NULL );
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
      result = ORDER_FUNCTION( (*(*node).left).value, (*node).value );
   }
   
   if ( result == 1 )
   {
      if ( (*node).right != NULL )
      {
         result = ORDER_FUNCTION( (*node).value, (*(*node).right).value );
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
in_order( BSTree_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).count > 1 )
   {
      result = in_order_recurse( (*p).root );
   }

   return result;
}

static
void invariant( BSTree_type( Prefix ) *p )
{
   assert(((void) "empty implies root null", is_empty_implies_root_null( p ) ));
   assert(((void) "nonnegative count", nonnegative_count( p ) ));
   assert(((void) "valid count", valid_count( p ) ));
   assert(((void) "first cursor not null", first_cursor_not_null( p ) ));
   assert(((void) "last cursor next null", last_cursor_next_null( p ) ));
   assert(((void) "last cursor null if one cursor", last_cursor_null_if_one_cursor( p ) ));
   assert(((void) "cursors bstree OK", cursors_bstree_ok( p ) ));
   assert(((void) "bstree in order", in_order( p ) ));
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
   clonable protocol function array
*/

static
void *
p_clonable_table[P_CLONABLE_FUNCTION_COUNT]
=
{
   BSTree_dispose( Prefix ),
   BSTree_dispose_with_contents( Prefix ),
   BSTree_make_from( Prefix ),
   BSTree_make_duplicate_from( Prefix )
};

static
void *
p_iterable_table[P_ITERABLE_FUNCTION_COUNT]
=
{
   BSTree_dispose( Prefix ),
   BSTree_dispose_with_contents( Prefix ),
   BSTree_count( Prefix ),
   BSTree_item_at( Prefix ),
   BSTree_off( Prefix ),
   BSTree_is_empty( Prefix ),
   BSTree_start( Prefix ),
   BSTree_forth( Prefix )
};

static
void *
p_diterable_table[P_DITERABLE_FUNCTION_COUNT]
=
{
   BSTree_dispose( Prefix ),
   BSTree_dispose_with_contents( Prefix ),
   BSTree_count( Prefix ),
   BSTree_item_at( Prefix ),
   BSTree_off( Prefix ),
   BSTree_is_empty( Prefix ),
   BSTree_start( Prefix ),
   BSTree_forth( Prefix ),
   BSTree_finish( Prefix ),
   BSTree_back( Prefix )
};

/**
   protocol get_function
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
      case P_CLONABLE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_CLONABLE_FUNCTION_MAX ) )
         {
            result = p_clonable_table[ function_id ];
         }
         break;
      }
   
      case P_ITERABLE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_ITERABLE_FUNCTION_MAX ) )
         {
            result = p_iterable_table[ function_id ];
         }
         break;
      }
      
      case P_DITERABLE:
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
      case P_CLONABLE:
      {
         result = 1;
         break;
      }
      
      case P_ITERABLE:
      {
         result = 1;
         break;
      }
   
      case P_DITERABLE:
      {
         result = 1;
         break;
      }
   
   }

   return result;
}

#endif // PROTOCOLS_ENABLED


/**
   BSTree_make
*/

BSTree_type( Prefix ) *
BSTree_make( Prefix )( void )
{
   // allocate bstree struct
   BSTree_type( Prefix ) * bstree
      = ( BSTree_type( Prefix ) * ) calloc( 1, sizeof( BSTree_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( bstree );

   // set type codes
   (*bstree).type = BSTREE_TYPE; 
   (*bstree).item_type = Type_Code;

   // root is null
   (*bstree).root = NULL;

   // count is zeor
   (*bstree).count = 0;

   // set built-in cursor
   // allocate cursor struct
   BSTree_cursor_type( Prefix ) *cursor
      =  ( BSTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BSTree_cursor_type( Prefix ) ) );

   // set bstree
   (*cursor).bstree = bstree;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set bstree built-in cursor
   (*bstree).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*bstree).mutex );

   INVARIANT( bstree );

   return bstree;
}

/**
   BSTree_make_from
*/

BSTree_type( Prefix ) *
BSTree_make_from( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );

   // make bstree struct
   BSTree_type( Prefix ) *result = BSTree_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = BSTREE_TYPE; 
   (*result).item_type = Type_Code;

   // copy from bstree
   BSTree_cursor_type( Prefix ) *cursor = BSTree_cursor_make( Prefix )( bstree );
   
   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, cursor_item( cursor ) );
      cursor_forth( cursor );
   }

   // balance this new tree
   balance( result );
   
   INVARIANT( result );

   return result;
}

/**
   BSTree_make_duplicate_from
*/

BSTree_type( Prefix ) *
BSTree_make_duplicate_from( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );

   // make bstree struct
   BSTree_type( Prefix ) *result = BSTree_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = BSTREE_TYPE; 
   (*result).item_type = Type_Code;

   // copy from bstree
   BSTree_cursor_type( Prefix ) *cursor = BSTree_cursor_make( Prefix )( bstree );
   
   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, DUPLICATE_FUNCTION( cursor_item( cursor ) ) );
      cursor_forth( cursor );
   }

   // balance this new tree
   balance( result );
   
   INVARIANT( result );

   return result;
}

/**
   BSTree_make_from_array
*/

BSTree_type( Prefix ) *
BSTree_make_from_array( Prefix )( Type *array, int32_t count )
{
   PRECONDITION( "array not null", array != NULL );
   PRECONDITION( "count ok", count >= 0 );

   // make bstree struct
   BSTree_type( Prefix ) *result = BSTree_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = BSTREE_TYPE; 
   (*result).item_type = Type_Code;

   // copy from array
   int32_t i = 0;
   
   for ( i=0; i<count; i++ )
   {
      put( result, array[i] );
   }

   // balance this new tree
   balance( result );
   
   INVARIANT( result );

   return result;
}

/**
   BSTree_cursor_make
*/

BSTree_cursor_type( Prefix ) *
BSTree_cursor_make( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   // allocate cursor struct
   BSTree_cursor_type( Prefix ) *cursor
      =  ( BSTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( BSTree_cursor_type( Prefix ) ) );

   // set bstree
   (*cursor).bstree = bstree;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // place cursor reference into bstree structure
   if ( (*bstree).last_cursor == NULL )
   {
      // set second cursor for bstree
      (*(*bstree).first_cursor).next_cursor = cursor;
      (*bstree).last_cursor = cursor;
   }
   else
   {
      // set additional cursor for bstree
      // (*bstree).last_cursor holds last cursor allocated
      (*(*bstree).last_cursor).next_cursor = cursor;
      (*bstree).last_cursor = cursor;
   }

   MULTITHREAD_MUTEX_INIT( (*cursor).mutex );

   INVARIANT( bstree );
   POSTCONDITION( "new cursor is last cursor", (*bstree).last_cursor == cursor );
   UNLOCK( (*bstree).mutex );

   return cursor;
}

/**
   BSTree_dispose
*/

void
BSTree_dispose( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   int32_t i = 0;
   
   // get array of nodes
   node_t **array = nodes_as_array( bstree );
   
   // delete nodes
   for ( i=0; i< (*bstree).count; i++ )
   {
      node_dispose( array[i] );
   }
   
   // delete array
   free( array );

   // delete cursors
   BSTree_cursor_type( Prefix ) *cursor = (*bstree).first_cursor;
   BSTree_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   MULTITHREAD_MUTEX_DESTROY( (*bstree).mutex );

   // delete bstree struct
   free( bstree );

   return;
}

/**
   BSTree_dispose_with_contents
*/

void
BSTree_dispose_with_contents( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   int32_t i = 0;
   
   // get array of nodes
   node_t **array = nodes_as_array( bstree );
   
   // delete nodes and values
   for ( i=0; i< (*bstree).count; i++ )
   {
      DISPOSE_FUNCTION( (*array[i]).value );
      node_dispose( array[i] );
   }
   
   // delete array
   free( array );

   // delete cursors
   BSTree_cursor_type( Prefix ) *cursor = (*bstree).first_cursor;
   BSTree_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   MULTITHREAD_MUTEX_DESTROY( (*bstree).mutex );

   // delete bstree struct
   free( bstree );

   return;
}

/**
   BSTree_cursor_dispose
*/

void
BSTree_cursor_dispose( Prefix )( BSTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).bstree).type == BSTREE_TYPE ) && ( (*(*cursor).bstree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).bstree).mutex );
   INVARIANT( (*cursor).bstree );

   BSTree_type( Prefix ) *bstree = (*cursor).bstree;

   BSTree_cursor_type( Prefix ) *c1 = NULL;
   BSTree_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from bstree structure
   c1 = (*(*cursor).bstree).first_cursor;
   c2 = (*c1).next_cursor;

   // search through the cursors
   while ( ( c2 != NULL) && ( flag == 0 ) )
   {
      if ( c2 == cursor )
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
   c1 = (*(*cursor).bstree).first_cursor;
   while ( c1 != NULL )
   {
      c2 = c1;
      c1 = (*c1).next_cursor;
   }
   (*(*cursor).bstree).last_cursor = c2;

   // only one cursor, last_cursor is NULL
   if ( c2 == (*(*cursor).bstree).first_cursor )
   {
      (*(*cursor).bstree).last_cursor = NULL;
   }
   
   // delete cursor struct
   free( cursor );

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return;
}

/**
   BSTree_cursor_item_at
*/

Type
BSTree_cursor_item_at( Prefix )( BSTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).bstree).type == BSTREE_TYPE ) && ( (*(*cursor).bstree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).bstree).mutex );
   INVARIANT( (*cursor).bstree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Type value = cursor_item( cursor );

   INVARIANT( (*cursor).bstree );
   UNLOCK( (*(*cursor).bstree).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}


/**
   BSTree_item_at
*/

Type
BSTree_item_at( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );
   PRECONDITION( "not off", (*(*bstree).first_cursor).item != NULL );

   BSTree_cursor_type( Prefix ) *cursor = (*bstree).first_cursor;

   Type value = cursor_item( cursor );

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return value;
}

/**
   BSTree_item_at_index
*/

Type
BSTree_item_at_index( Prefix )( BSTree_type( Prefix ) *bstree, int32_t index )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*bstree).count ) );

   int32_t i = 0;
   Type value;
   
   cursor_start( (*bstree).first_cursor );
   value = cursor_item( (*bstree).first_cursor );
   
   for( i = 1; i <= index; i++ )
   {
      cursor_forth( (*bstree).first_cursor );
      value = cursor_item( (*bstree).first_cursor );
   }

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return value;
}

/**
   BSTree_as_array
*/

Type *
BSTree_as_array( Prefix )( BSTree_type( Prefix ) *bstree, int32_t *count )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   BSTree_cursor_type( Prefix ) *cursor = (*bstree).first_cursor;

   Type *result = ( Type * ) calloc( (*bstree).count + 1, sizeof( Type ) );

   cursor_start( cursor );
   int32_t i = 0;
   
   for( i=0; i<(*bstree).count; i++ )
   {
      result[i] = cursor_item( cursor );
      cursor_forth( cursor );
   }
   
   (*count) = (*bstree).count;

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return result;
}

/**
   BSTree_count
*/

int32_t
BSTree_count( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   int32_t count = (*bstree).count;

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return count;
}

/**
   BSTree_height
*/

int32_t
BSTree_height( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   int32_t count = height( bstree );

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return count;
}

/**
   BSTree_off
*/

int32_t
BSTree_off( Prefix)( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   int32_t result = cursor_off( (*bstree).first_cursor );

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return result;
}

/**
   BSTree_cursor_off
*/

int32_t
BSTree_cursor_off( Prefix )( BSTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).bstree).type == BSTREE_TYPE ) && ( (*(*cursor).bstree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   int32_t result = cursor_off( cursor );

   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   BSTree_is_empty
*/

int32_t
BSTree_is_empty( Prefix)( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   int32_t result = ( (*bstree).count ==  0 );

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return result;
}

/**
   BSTree_has
*/

int32_t
BSTree_has( Prefix )( BSTree_type( Prefix ) *bstree, Type value )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   int32_t result = has( bstree, value );

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return result;
}

/**
   BSTree_cursor_back
*/
void
BSTree_cursor_back( Prefix )( BSTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).bstree).type == BSTREE_TYPE ) && ( (*(*cursor).bstree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   cursor_back( cursor );
   
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_cursor_forth
*/
void
BSTree_cursor_forth( Prefix )( BSTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).bstree).type == BSTREE_TYPE ) && ( (*(*cursor).bstree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   cursor_forth( cursor );
   
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_cursor_go
*/
void
BSTree_cursor_go( Prefix )( BSTree_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).bstree).type == BSTREE_TYPE ) && ( (*(*cursor).bstree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).bstree).mutex );
   INVARIANT( (*cursor).bstree );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*(*cursor).bstree).count ) ) );

   int32_t i = 0;
   cursor_start( cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).bstree );
   UNLOCK( (*(*cursor).bstree).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_cursor_index
*/

int32_t
BSTree_cursor_index( Prefix )( BSTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).bstree).type == BSTREE_TYPE ) && ( (*(*cursor).bstree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).bstree).mutex );
   INVARIANT( (*cursor).bstree );

   int32_t result = 0;
   int32_t flag = 0;
   node_t *target = (*cursor).item;

   if ( (*(*cursor).bstree).count > 0 )
   {
      cursor_start( cursor );
      
      while ( cursor_off( cursor ) == 0 )
      {
         if ( (*cursor).item == target )
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
   
   INVARIANT( (*cursor).bstree );
   UNLOCK( (*(*cursor).bstree).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   BSTree_cursor_finish
*/

void
BSTree_cursor_finish( Prefix )( BSTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).bstree).type == BSTREE_TYPE ) && ( (*(*cursor).bstree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).bstree).mutex );
   INVARIANT( (*cursor).bstree );

   cursor_finish( cursor );

   INVARIANT( (*cursor).bstree );
   UNLOCK( (*(*cursor).bstree).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_cursor_start
*/

void
BSTree_cursor_start( Prefix )( BSTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).bstree).type == BSTREE_TYPE ) && ( (*(*cursor).bstree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).bstree).mutex );
   INVARIANT( (*cursor).bstree );

   cursor_start( cursor );

   INVARIANT( (*cursor).bstree );
   UNLOCK( (*(*cursor).bstree).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   BSTree_back
*/
void
BSTree_back( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );
   PRECONDITION( "not off", (*(*bstree).first_cursor).item != NULL );

   cursor_back( (*bstree).first_cursor );

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return;
}

/**
   BSTree_forth
*/
void
BSTree_forth( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );
   PRECONDITION( "not off", (*(*bstree).first_cursor).item != NULL );

   cursor_forth( (*bstree).first_cursor );

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return;
}

/**
   BSTree_go
*/
void
BSTree_go( Prefix )( BSTree_type( Prefix ) *bstree, int32_t index )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*bstree).count ) ) );

   int32_t i = 0;
   cursor_start( (*bstree).first_cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( (*bstree).first_cursor );
   }

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return;
}

/**
   BSTree_index
*/

int32_t
BSTree_index( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   int32_t result = 0;
   int32_t flag = 0;
   BSTree_cursor_type( Prefix ) *cursor = (*bstree).first_cursor;
   node_t *target = (*cursor).item;

   if ( (*bstree).count > 0 )
   {
      cursor_start( cursor );
      
      while ( cursor_off( cursor ) == 0 )
      {
         if ( (*cursor).item == target )
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
   
   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return result;
}

/**
   BSTree_finish
*/

void
BSTree_finish( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   cursor_finish( (*bstree).first_cursor );

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return;
}

/**
   BSTree_start
*/

void
BSTree_start( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   cursor_start( (*bstree).first_cursor );

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return;
}

/**
   BSTree_put
*/

void
BSTree_put( Prefix )( BSTree_type( Prefix ) *bstree, Type value )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   put( bstree, value );

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return;
}

/**
   BSTree_remove
*/

void
BSTree_remove( Prefix )( BSTree_type( Prefix ) *bstree, Type value )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );
   PRECONDITION( "has value", has( bstree, value ) );

   remove( bstree, value );

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return;
}

/**
   BSTree_remove_and_dispose
*/

void
BSTree_remove_and_dispose( Prefix )( BSTree_type( Prefix ) *bstree, Type value )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );
   PRECONDITION( "has value", has( bstree, value ) );

   remove_and_dispose( bstree, value );
   
   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return;
}

/**
   BSTree_wipe_out
*/

void
BSTree_wipe_out( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   int32_t i = 0;
   
   // get array of nodes
   node_t **array = nodes_as_array( bstree );
   
   // delete nodes
   for ( i=0; i< (*bstree).count; i++ )
   {
      node_dispose( array[i] );
   }
   
   // delete array
   free( array );

   // delete cursors, all but first
   BSTree_cursor_type( Prefix ) *cursor = (*(*bstree).first_cursor).next_cursor;
   BSTree_cursor_type( Prefix ) *next_cursor = NULL;
   (*(*bstree).first_cursor).next_cursor = NULL;
   (*bstree).last_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // set count to zero
   (*bstree).count = 0;
   
   // set root to NULL
   (*bstree).root = NULL;

   POSTCONDITION( "is empty", (*bstree).count == 0 );
   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return;
}

/**
   BSTree_wipe_out_and_dispose
*/

void
BSTree_wipe_out_and_dispose( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   int32_t i = 0;
   
   // get array of nodes
   node_t **array = nodes_as_array( bstree );
   
   // delete nodes and values
   for ( i=0; i< (*bstree).count; i++ )
   {
      DISPOSE_FUNCTION( (*array[i]).value );
      node_dispose( array[i] );
   }
   
   // delete array
   free( array );

   // delete cursors, all but first
   BSTree_cursor_type( Prefix ) *cursor = (*(*bstree).first_cursor).next_cursor;
   BSTree_cursor_type( Prefix ) *next_cursor = NULL;
   (*(*bstree).first_cursor).next_cursor = NULL;
   (*bstree).last_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // set count to zero
   (*bstree).count = 0;

   // set root to NULL
   (*bstree).root = NULL;

   POSTCONDITION( "is empty", (*bstree).count == 0 );
   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return;
}

/**
   BSTree_balance
*/

void
BSTree_balance( Prefix )( BSTree_type( Prefix ) *bstree )
{
   PRECONDITION( "bstree not null", bstree != NULL );
   PRECONDITION( "bstree type ok", ( (*bstree).type == BSTREE_TYPE ) && ( (*bstree).item_type = Type_Code ) );
   LOCK( (*bstree).mutex );
   INVARIANT( bstree );

   balance( bstree );

   INVARIANT( bstree );
   UNLOCK( (*bstree).mutex );

   return;
}


#ifdef __cplusplus
}
#endif

/* End of file */

