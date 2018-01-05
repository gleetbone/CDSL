/**
 @file RBTree_kv.c
 @author Greg Lee
 @version 1.0.0
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
#include "P_Clonable.ph"
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

#define RBTREE_KV_TYPE 0xA5000203

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

   int32_t type;
   int32_t key_type;
   int32_t item_type;
   
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
   function prototype of height
*/

static
int
height( RBTree_kv_type( Prefix ) *rbtree );

/**
   height_of_node
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
   void (func)( char_t *, Key key, Type value ) 
)
{
   int32_t node_height = 0;
   int32_t i = 0;
   char_t *cp = NULL;
   
   node_height = height_of_node( node );
   i = ( int32_t ) floor( pow( 2.0, tree_height - node_height ) );
   i = width*i + 2*width*i*index;
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
*/

void
RBTree_kv_as_string( Prefix )
( 
   RBTree_kv_type( Prefix ) *rbtree, 
   char_t **astr,
   int32_t width,
   void (func)( char_t *, Key key, Type value )
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
*/

static
node_t *
node_make( void )
{
   node_t *node = ( node_t * ) calloc( 1, sizeof( node_t ) );

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
*/

static
void
node_dispose( node_t *node )
{
   PRECONDITION( "node not null", node != NULL );
   
   (*node).parent = NULL;
   (*node).left = NULL;
   (*node).right = NULL;
   (*node).color = 0;
   
   free( node );
   
   return;
}

/**
   has_recurse
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
      result = KEY_EQUALITY_FUNCTION( (*node).key, key );
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
   item_recurse
*/
static
node_t *
item_recurse( node_t *node, Key key )
{
   node_t *result = &null_node;

   if ( KEY_EQUALITY_FUNCTION( key, (*node).key ) == 1 )
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

   Return node in rbtree that has key, NULL if none

   @param rbtree RBTree_kv_t instance
   @param key the key to query for
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
   rotate_left
   perform left rotation starting at node
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
           (*(*child).left).parent = node;
       }
   
       (*child).parent = (*node).parent;
   
       if ( node == (*(*node).parent).left )
       {
          (*(*node).parent).left = child;
       }
       else
       {
          (*(*node).parent).right = child;
       }
   
       (*child).left = node;
       (*node).parent = child;
    }

    return;
}

/**
   rotate_right
   perform right rotation starting at node
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
           (*(*child).right).parent = node;
       }
   
       (*child).parent = (*node).parent;
   
       if ( node == (*(*node).parent).left )
       {
          (*(*node).parent).left = child;
       }
       else
       {
          (*(*node).parent).right = child;
       }
   
       (*child).right = node;
       (*node).parent = child;
    }

   return;
}

/**
   sibling_of
   find sibling of node, if it exists
*/
static 
node_t *
sibling_of( node_t *node )
{
   node_t *result = NULL;
   
   if ( (*node).parent != &null_node )
   {
      if ( node == (*(*node).parent).left )
      {
         result = (*(*node).parent).right;
      }
      else
      {
         result = (*(*node).parent).left;
      }
   }
   
   return result;
}

/**
  repair_put
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
         ( (*(*n).parent).color == red ) 
      ) 
   {
   
      // recolor up if more work needed
      if ( (* sibling_of( (*n).parent ) ).color == red ) 
      {
         (*(*n).parent).color = black;
         (* sibling_of( (*n).parent ) ).color = black;
         if ( (*(*n).parent).parent != &null_node )
         {
            (*(*(*n).parent).parent).color = red;
            repair_put( rbtree, (*(*n).parent).parent );
         }
      }
   
      // restructure for a parent who is the left child of the
      // grandparent. requires a single right rotation if n is
      // also a left child, or a left-right rotation otherwise
      else if ( (*n).parent == (*(*(*n).parent).parent).left  ) 
      {
         if ( n == (*(*n).parent).right ) 
         {
            n = (*n).parent;
            rotate_left( rbtree, n );
         }
         (*(*n).parent).color = black ;
         if ( (*(*n).parent).parent != &null_node )
         {
            (*(*(*n).parent).parent).color = red;
            rotate_right( rbtree, (*(*n).parent).parent );
         }
      }
   
      // restructure for a parent who is the right child of the
      // grandparent. requires a single left rotation if n is
      // also a right child, or a right-left rotation otherwise
      else if ( (*n).parent == (*(*(*n).parent).parent).right ) 
      {
         if ( n == (*(*n).parent).left  ) 
         {
            n = (*n).parent;
            rotate_right( rbtree, n );
         }
         (*(*n).parent).color = black;
         if ( (*(*n).parent).parent != &null_node )
         {
            (*(*(*n).parent).parent).color = red;
            rotate_left( rbtree, (*(*n).parent).parent );
         }
      }
   }
   
   // color the root black
   (*(*rbtree).root.left).color = black;
   
   return;
}

/**
   put
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
   (*(*rbtree).root.left).color = black;

   // increment count
   (*rbtree).count = (*rbtree).count + 1;

   return;
}

/**
   keys_as_array_recurse
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
*/

static
Type *
keys_as_array( RBTree_kv_type( Prefix ) *rbtree )
{
   Key *result = NULL;
   int32_t index = 0;

   result = ( Key * ) calloc( (*rbtree).count + 1, sizeof( Key ) );

   if ( (*rbtree).root.left != &null_node )
   {
      keys_as_array_recurse( (*rbtree).root.left, result, &index );
   }

   return result;
}

/**
   items_as_array_recurse
*/
static
void
items_as_array_recurse( node_t *node, Type *array, int32_t *index )
{
   // if has left child, recurse
   if ( (*node).left != &null_node )
   {
      items_as_array_recurse( (*node).left, array, index );
   }

   // handle this node
   array[ *index ] = (*node).value;
   *index = *index + 1;

   // if has right child, recurse
   if ( (*node).right != &null_node )
   {
      items_as_array_recurse( (*node).right, array, index );
   }

   return;
}

/**
   items_as_array
*/

static
Type *
items_as_array( RBTree_kv_type( Prefix ) *rbtree )
{
   Type *result = NULL;
   int32_t index = 0;

   result = ( Type * ) calloc( (*rbtree).count + 1, sizeof( Type ) );

   if ( (*rbtree).root.left != &null_node )
   {
      items_as_array_recurse( (*rbtree).root.left, result, &index );
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
*/

static
node_t **
nodes_as_array( RBTree_kv_type( Prefix ) *rbtree )
{
   node_t **result = NULL;
   int32_t index = 0;

   result = ( node_t ** ) calloc( (*rbtree).count + 1, sizeof( node_t ) );

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
      if ( n == (*(*n).parent).left ) 
      {
         // Pulled up node is a left child
         sibling = (*(*n).parent).right;
         if ( (*sibling).color == red ) 
         {
            if ( sibling != &null_node )
            {
               (*sibling).color = black;
            }
            (*(*n).parent).color = red;
            rotate_left( rbtree, (*n).parent );
            sibling = (*(*n).parent).right;
         }
          
         if ( ( (*(*sibling).left).color == black ) && ( (*(*sibling).right).color == black ) ) 
         {
            if ( sibling != &null_node )
            {
               (*sibling).color = red;
            }
            n = (*n).parent;
         } 
         else 
         {
            if ( (*(*sibling).right).color == black ) 
            {
               (*(*sibling).left).color = black;
               (*sibling).color = red;
               rotate_right( rbtree, sibling );
               sibling = (*(*n).parent).right;
            }
              
            (*sibling).color = (*(*n).parent).color;
            (*(*n).parent).color = black;
            (*(*sibling).right).color = black;
            rotate_left( rbtree, (*n).parent );
            n = (*rbtree).root.left;
         }
      } 
      else 
      {
         // pulled up node is a right child
         sibling = (*(*n).parent).left;
         if ( (*sibling).color == red ) 
         {
            (*sibling).color = black ;
            (*(*n).parent).color = red;
            rotate_right( rbtree, (*n).parent );
            sibling = (*(*n).parent).left;
         }
          
         if ( ( (*(*sibling).left).color == black ) && ( (*(*sibling).right).color == black ) ) 
         {
            if ( sibling != &null_node )
            {
               (*sibling).color = red;
            }
            n = (*n).parent;
         } 
         else 
         {
            if ( (*(*sibling).left).color == black ) 
            {
               (*(*sibling).right).color = black;
               (*sibling).color = red;
               rotate_left( rbtree, sibling );
               sibling = (*(*n).parent).left;
            }
              
            (*sibling).color = (*(*n).parent).color;
            (*(*n).parent).color = black;
            (*(*sibling).left).color = black;
            rotate_right( rbtree, (*n).parent );
            n = (*rbtree).root.left;
         }
      }
   }
        
   (*n).color = black;
   
   return;
}

/**
   predecessor

   returns the node before node, or nil if none.
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
/*   
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
*/
   
   return( result );
}


static
void
cursor_forth( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   remove
*/
static
node_t *
remove( RBTree_kv_type( Prefix ) *rbtree, Type value )
{
   node_t *node = NULL;
   node_t *pre = NULL;
   node_t *pull_up = NULL;
   Key k;
   Type v;
   RBTree_kv_cursor_type( Prefix ) *cursor = NULL;

   // find the node to be removed
   node = item( rbtree, value );

   // if node is not null, continue
   if ( node != &null_node )
   {
      // move cursors pointing to this node forth
      cursor = (*rbtree).first_cursor;
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
         pre = predecessor( rbtree, node );
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
         
         if ( node == (*rbtree).root.left )
         {
            // eliminate tree root
            (*rbtree).root.left = pull_up;
            (*pull_up).parent = &( (*rbtree).root );
         }
         else if ( (*(*node).parent).left == node )
         {
            // eliminate node parent's left 
            (*(*node).parent).left = pull_up;
            (*pull_up).parent = (*node).parent;
         }
         else
         {
            // eliminate node parent's right
            (*(*node).parent).right = pull_up;
            (*pull_up).parent = (*node).parent;
         }
         
         if ( (*node).color == black )
         {
            repair_remove( rbtree, pull_up );
         }
      }
      else if ( node == (*rbtree).root.left )
      {
         // eliminate root, tree is not empty
         (*rbtree).root.left = &null_node;
      }
      else
      {
         // if node is black, repair tree
         if ( (*node).color == black )
         {
            repair_remove( rbtree, node );
         }
         
         // eliminate the node from the tree
         if ( (*node).parent != &null_node )
         {
            if ( (*(*node).parent).left == node )
            {
               (*(*node).parent).left = &null_node;
            }
            else if ( (*(*node).parent).right == node )
            {
               (*(*node).parent).right = &null_node;
            }
            (*node).parent = &null_node;
         }
      }
      
      // decrement count
      (*rbtree).count = (*rbtree).count - 1;
   }

   // node is disposed in calling routine
   return node;
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
cursor_finish( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   node_t *node = NULL;
   
   // set node from the rbtree root
   node = (*(*cursor).rbtree).root.left;
   
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
   node = (*(*cursor).rbtree).root.left;

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
   return (*(*cursor).item).key;
}

/**
   cursor_item
*/
static
Type
cursor_item( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   // return the value for the current cursor item
   return (*(*cursor).item).value;
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
         ( (*cursor).item == &(*(*cursor).rbtree).root )
         ||
         ( (*cursor).item == &null_node )
      )
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

   if ( (*(*p).first_cursor).next_cursor == NULL )
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
      result = ( (*(*p).last_cursor).next_cursor == NULL );
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
      result = KEY_ORDER_FUNCTION( (*(*node).left).key, (*node).key );
   }

   if ( result == 1 )
   {
      if ( (*node).right != &null_node )
      {
         result = KEY_ORDER_FUNCTION( (*node).key, (*(*node).right).key );
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
      result = ( (*(*p).root.left).color == black );
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
         result = ( (*(*node).left).color == black );
      }
      if ( result == 1 )
      {
         if ( (*node).right != &null_node )
         {
            result = ( (*(*node).right).color == black );
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

static
void invariant( RBTree_kv_type( Prefix ) *p )
{
   assert(((void) "empty implies root null", is_empty_implies_root_null( p ) ));
   assert(((void) "nonnegative count", nonnegative_count( p ) ));
   assert(((void) "valid count", valid_count( p ) ));
   assert(((void) "first cursor not null", first_cursor_not_null( p ) ));
   assert(((void) "last cursor next null", last_cursor_next_null( p ) ));
   assert(((void) "last cursor null if one cursor", last_cursor_null_if_one_cursor( p ) ));
   assert(((void) "cursors rbtree OK", cursors_rbtree_ok( p ) ));
   assert(((void) "rbtree in order", in_order( p ) ));
   assert(((void) "root is black", root_is_black( p ) ));
   assert(((void) "node colors ok", node_colors_ok( p ) ));
   assert(((void) "path black count ok", path_black_count_ok( p ) ));
   assert(((void) "null node ok", null_node_ok( p ) ));
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
   RBTree_kv_dispose( Prefix ),
   RBTree_kv_dispose_with_contents( Prefix ),
   RBTree_kv_make_from( Prefix ),
   RBTree_kv_make_duplicate_from( Prefix )
};

static
void *
p_iterable_kv_table[P_ITERABLE_KV_FUNCTION_COUNT]
=
{
   RBTree_kv_dispose( Prefix ),
   RBTree_kv_dispose_with_contents( Prefix ),
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
   RBTree_kv_dispose( Prefix ),
   RBTree_kv_dispose_with_contents( Prefix ),
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
   
      case P_ITERABLE_KV:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_ITERABLE_KV_FUNCTION_MAX ) )
         {
            result = p_iterable_kv_table[ function_id ];
         }
         break;
      }
      
      case P_DITERABLE_KV:
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
      
      case P_ITERABLE_KV:
      {
         result = 1;
         break;
      }
   
      case P_DITERABLE_KV:
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
   RBTree_kv_type( Prefix ) * rbtree
      = ( RBTree_kv_type( Prefix ) * ) calloc( 1, sizeof( RBTree_kv_type( Prefix ) ) );
                                    // initialize protocol functions if protocols enabled
                                    
   PROTOCOLS_INIT( rbtree );

   // set type codes
   (*rbtree).type = RBTREE_KV_TYPE; 
   (*rbtree).key_type = Key_Code;
   (*rbtree).item_type = Type_Code;

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
   (*rbtree).root.left = &null_node;
   (*rbtree).root.right = &null_node;
   (*rbtree).root.parent = &null_node;
   (*rbtree).root.color = black;

   // count is zero
   (*rbtree).count = 0;

   // set built-in cursor
   // allocate cursor struct
   RBTree_kv_cursor_type( Prefix ) *cursor
      =  ( RBTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_kv_cursor_type( Prefix ) ) );

   // set rbtree
   (*cursor).rbtree = rbtree;

   // set item to NULL - cursor is "off"
   (*cursor).item = &null_node;

   // set rbtree built-in cursor
   (*rbtree).first_cursor = cursor;

   // init mutex
   MULTITHREAD_MUTEX_INIT( (*rbtree).mutex );

   INVARIANT( rbtree );

   return rbtree;
}

/**
   RBTree_kv_make_from
*/

RBTree_kv_type( Prefix ) *
RBTree_kv_make_from( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );

   // make rbtree struct
   RBTree_kv_type( Prefix ) *result = RBTree_kv_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = RBTREE_KV_TYPE;    
   (*result).key_type = Key_Code;
   (*result).item_type = Type_Code;

   // copy from rbtree
   RBTree_kv_cursor_type( Prefix ) *cursor = RBTree_kv_cursor_make( Prefix )( rbtree );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, cursor_item( cursor ), cursor_key( cursor ) );
      cursor_forth( cursor );
   }

   INVARIANT( result );

   return result;
}

/**
   RBTree_kv_make_duplicate_from
*/

RBTree_kv_type( Prefix ) *
RBTree_kv_make_duplicate_from( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );

   // make rbtree struct
   RBTree_kv_type( Prefix ) *result = RBTree_kv_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = RBTREE_KV_TYPE; 
   (*result).key_type = Key_Code;
   (*result).item_type = Type_Code;

   // copy from rbtree
   RBTree_kv_cursor_type( Prefix ) *cursor = RBTree_kv_cursor_make( Prefix )( rbtree );

   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, VALUE_DUPLICATE_FUNCTION( cursor_item( cursor ) ), KEY_DUPLICATE_FUNCTION( cursor_key( cursor ) ) );
      cursor_forth( cursor );
   }

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
   (*result).type = RBTREE_KV_TYPE; 
   (*result).key_type = Key_Code;
   (*result).item_type = Type_Code;

   int32_t i = 0;
   
   for ( i=0; i<count; i++ )
   {
      put( result, value_array[i], key_array[i] );
   }

   INVARIANT( result );

   return result;
}

/**
   RBTree_kv_cursor_make
*/

RBTree_kv_cursor_type( Prefix ) *
RBTree_kv_cursor_make( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );

   // allocate cursor struct
   RBTree_kv_cursor_type( Prefix ) *cursor
      =  ( RBTree_kv_cursor_type( Prefix ) * )
         calloc( 1, sizeof( RBTree_kv_cursor_type( Prefix ) ) );

   // set rbtree
   (*cursor).rbtree = rbtree;

   // set item to NULL - cursor is "off"
   (*cursor).item = &null_node;

   // place cursor reference into rbtree structure
   if ( (*rbtree).last_cursor == NULL )
   {
      // set second cursor for rbtree
      (*(*rbtree).first_cursor).next_cursor = cursor;
      (*rbtree).last_cursor = cursor;
   }
   else
   {
      // set additional cursor for rbtree
      // last_cursor holds last cursor allocated
      (*(*rbtree).last_cursor).next_cursor = cursor;
      (*rbtree).last_cursor = cursor;
   }

   // init mutex
   MULTITHREAD_MUTEX_INIT( (*rbtree).mutex );

   INVARIANT( rbtree );
   POSTCONDITION( "new cursor is last cursor", (*rbtree).last_cursor == cursor );
   UNLOCK( (*rbtree).mutex );

   return cursor;
}

/**
   RBTree_kv_dispose
*/

void
RBTree_kv_dispose( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );

   int32_t i = 0;

   // get array of nodes
   node_t **array = nodes_as_array( rbtree );

   // delete nodes
   for ( i=0; i< (*rbtree).count; i++ )
   {
      node_dispose( array[i] );
   }

   // delete array
   free( array );

   // delete cursors
   RBTree_kv_cursor_type( Prefix ) *cursor = (*rbtree).first_cursor;
   RBTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // dispose of mutex
   MULTITHREAD_MUTEX_DESTROY( (*rbtree).mutex );

   // delete rbtree struct
   free( rbtree );

   return;
}

/**
   RBTree_kv_dispose_with_contents
*/

void
RBTree_kv_dispose_with_contents( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );

   int32_t i = 0;

   // get array of nodes
   node_t **array = nodes_as_array( rbtree );

   // delete nodes and values
   for ( i=0; i< (*rbtree).count; i++ )
   {
      KEY_DISPOSE_FUNCTION( (*array[i]).key );
      VALUE_DISPOSE_FUNCTION( (*array[i]).value );
      node_dispose( array[i] );
   }

   // delete array
   free( array );

   // delete cursors
   RBTree_kv_cursor_type( Prefix ) *cursor = (*rbtree).first_cursor;
   RBTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // dispose of mutex
   MULTITHREAD_MUTEX_DESTROY( (*rbtree).mutex );

   // delete rbtree struct
   free( rbtree );

   return;
}

/**
   RBTree_kv_cursor_dispose
*/

void
RBTree_kv_cursor_dispose( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );         
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).rbtree).type == RBTREE_KV_TYPE ) && ( (*(*cursor).rbtree).key_type = Key_Code ) && ( (*(*cursor).rbtree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).rbtree).mutex );
   INVARIANT( (*cursor).rbtree );

   RBTree_kv_type( Prefix ) *rbtree = (*cursor).rbtree;

   RBTree_kv_cursor_type( Prefix ) *c1 = NULL;
   RBTree_kv_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from rbtree structure
   c1 = (*(*cursor).rbtree).first_cursor;
   c2 = (*c1).next_cursor;

   // search through the cursors
   while ( ( c2 != NULL) && ( flag == 0 ) )
   {
      if ( c2 == cursor )
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
   c1 = (*(*cursor).rbtree).first_cursor;
   while ( c1 != NULL )
   {
      c2 = c1;
      c1 = (*c1).next_cursor;
   }
   (*(*cursor).rbtree).last_cursor = c2;

   // only one cursor, last_cursor is NULL
   if ( c2 == (*(*cursor).rbtree).first_cursor )
   {
      (*(*cursor).rbtree).last_cursor = NULL;
   }
   
   // delete cursor struct
   free( cursor );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return;
}

/**
   RBTree_kv_keys_as_array

*/

Type *
RBTree_kv_keys_as_array( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );

   Key *result = keys_as_array( rbtree );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return result;
}

/**
   RBTree_kv_values_as_array

*/

Type *
RBTree_kv_values_as_array( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );

   Type *result = items_as_array( rbtree );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return result;
}

/**
   RBTree_kv_cursor_key_at
*/

Key
RBTree_kv_cursor_key_at( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).rbtree).type == RBTREE_KV_TYPE ) && ( (*(*cursor).rbtree).key_type = Key_Code ) && ( (*(*cursor).rbtree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).rbtree).mutex );
   INVARIANT( (*cursor).rbtree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Key key = cursor_key( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( (*(*cursor).rbtree).mutex );
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
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).rbtree).type == RBTREE_KV_TYPE ) && ( (*(*cursor).rbtree).key_type = Key_Code ) && ( (*(*cursor).rbtree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).rbtree).mutex );
   INVARIANT( (*cursor).rbtree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Type value = cursor_item( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( (*(*cursor).rbtree).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}


/**
   RBTree_kv_key_at
*/

Key
RBTree_kv_key_at( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );
   PRECONDITION( "not off", (*(*rbtree).first_cursor).item != NULL );

   RBTree_kv_cursor_type( Prefix ) *cursor = (*rbtree).first_cursor;

   Key key = cursor_key( cursor );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return key;
}

/**
   RBTree_kv_item_at
*/

Type
RBTree_kv_item_at( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );
   PRECONDITION( "not off", (*(*rbtree).first_cursor).item != NULL );

   RBTree_kv_cursor_type( Prefix ) *cursor = (*rbtree).first_cursor;

   Type value = cursor_item( cursor );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return value;
}

/**
   RBTree_kv_key_at_index
*/

Key
RBTree_kv_key_at_index( Prefix )( RBTree_kv_type( Prefix ) *rbtree, int32_t index )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*rbtree).count ) );

   int32_t i = 0;
   Key key;

   cursor_start( (*rbtree).first_cursor );
   key = cursor_key( (*rbtree).first_cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( (*rbtree).first_cursor );
      key = cursor_key( (*rbtree).first_cursor );
   }

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return key;
}

/**
   RBTree_kv_item_at_index
*/

Type
RBTree_kv_item_at_index( Prefix )( RBTree_kv_type( Prefix ) *rbtree, int32_t index )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*rbtree).count ) );

   int32_t i = 0;
   Type value;

   cursor_start( (*rbtree).first_cursor );
   value = cursor_item( (*rbtree).first_cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( (*rbtree).first_cursor );
      value = cursor_item( (*rbtree).first_cursor );
   }

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return value;
}

/**
   RBTree_kv_count
*/

int32_t
RBTree_kv_count( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );

   int32_t result = (*rbtree).count;

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return result;
}

/**
   RBTree_kv_height
*/

int32_t
RBTree_kv_height( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );

   int32_t result = height( rbtree );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return result;
}

/**
   RBTree_kv_off
*/

int32_t
RBTree_kv_off( Prefix)( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );

   int32_t result = cursor_off( (*rbtree).first_cursor );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return result;
}

/**
   RBTree_kv_cursor_off
*/

int32_t
RBTree_kv_cursor_off( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).rbtree).type == RBTREE_KV_TYPE ) && ( (*(*cursor).rbtree).key_type = Key_Code ) && ( (*(*cursor).rbtree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   INVARIANT( (*cursor).rbtree );

   int32_t result = cursor_off( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   RBTree_kv_is_empty
*/

int32_t
RBTree_kv_is_empty( Prefix)( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );

   int32_t result = ( (*rbtree).count ==  0 );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return result;
}

/**
   RBTree_kv_has
*/

int32_t
RBTree_kv_has( Prefix )( RBTree_kv_type( Prefix ) *rbtree, Key key )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );

   int32_t result = has( rbtree, key );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return result;
}

/**
   RBTree_kv_cursor_forth
*/
void
RBTree_kv_cursor_forth( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).rbtree).type == RBTREE_KV_TYPE ) && ( (*(*cursor).rbtree).key_type = Key_Code ) && ( (*(*cursor).rbtree).item_type = Type_Code ) ) );
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
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).rbtree).type == RBTREE_KV_TYPE ) && ( (*(*cursor).rbtree).key_type = Key_Code ) && ( (*(*cursor).rbtree).item_type = Type_Code ) ) );
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
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).rbtree).type == RBTREE_KV_TYPE ) && ( (*(*cursor).rbtree).key_type = Key_Code ) && ( (*(*cursor).rbtree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).rbtree).mutex );
   INVARIANT( (*cursor).rbtree );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*(*cursor).rbtree).count ) ) );

   int32_t i = 0;
   cursor_start( cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).rbtree );
   UNLOCK( (*(*cursor).rbtree).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_cursor_index
*/

int32_t
RBTree_kv_cursor_index( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).rbtree).type == RBTREE_KV_TYPE ) && ( (*(*cursor).rbtree).key_type = Key_Code ) && ( (*(*cursor).rbtree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).rbtree).mutex );
   INVARIANT( (*cursor).rbtree );

   int32_t result = 0;
   int32_t flag = 0;
   node_t *target = (*cursor).item;

   if ( (*(*cursor).rbtree).count > 0 )
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
   
   INVARIANT( (*cursor).rbtree );
   UNLOCK( (*(*cursor).rbtree).mutex );
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
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).rbtree).type == RBTREE_KV_TYPE ) && ( (*(*cursor).rbtree).key_type = Key_Code ) && ( (*(*cursor).rbtree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).rbtree).mutex );
   INVARIANT( (*cursor).rbtree );

   cursor_start( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( (*(*cursor).rbtree).mutex );
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
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).rbtree).type == RBTREE_KV_TYPE ) && ( (*(*cursor).rbtree).key_type = Key_Code ) && ( (*(*cursor).rbtree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).rbtree).mutex );
   INVARIANT( (*cursor).rbtree );

   cursor_finish( cursor );

   INVARIANT( (*cursor).rbtree );
   UNLOCK( (*(*cursor).rbtree).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   RBTree_kv_forth
*/
void
RBTree_kv_forth( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );
   PRECONDITION( "not off", (*(*rbtree).first_cursor).item != &null_node );

   cursor_forth( (*rbtree).first_cursor );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return;
}

/**
   RBTree_kv_back
*/
void
RBTree_kv_back( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );
   PRECONDITION( "not off", (*(*rbtree).first_cursor).item != &null_node );

   cursor_back( (*rbtree).first_cursor );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return;
}

/**
   RBTree_kv_go
*/
void
RBTree_kv_go( Prefix )( RBTree_kv_type( Prefix ) *rbtree, int32_t index )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*rbtree).count ) ) );

   int32_t i = 0;
   cursor_start( (*rbtree).first_cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( (*rbtree).first_cursor );
   }

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return;
}

/**
   RBTree_kv_index
*/

int32_t
RBTree_kv_index( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );

   int32_t result = 0;
   int32_t flag = 0;
   RBTree_kv_cursor_type( Prefix ) *cursor = (*rbtree).first_cursor;
   node_t *target = (*cursor).item;

   if ( (*rbtree).count > 0 )
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
   
   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return result;
}

/**
   RBTree_kv_start
*/

void
RBTree_kv_start( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );

   cursor_start( (*rbtree).first_cursor );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return;
}

/**
   RBTree_kv_finish
*/

void
RBTree_kv_finish( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );

   cursor_finish( (*rbtree).first_cursor );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return;
}

/**
   RBTree_kv_put
*/

void
RBTree_kv_put( Prefix )( RBTree_kv_type( Prefix ) *rbtree, Type value, Key key )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );

   put( rbtree, value, key );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return;
}

/**
   RBTree_kv_remove
*/

void
RBTree_kv_remove( Prefix )( RBTree_kv_type( Prefix ) *rbtree, Key key )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );
   PRECONDITION( "has value", has( rbtree, key ) );

   node_t *node = NULL;
   
   // remove the node from the tree
   node = remove( rbtree, key );
   
   // dispose of the node
   node_dispose( node );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return;
}

/**
   RBTree_kv_remove_and_dispose
*/

void
RBTree_kv_remove_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *rbtree, Key key )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );
   PRECONDITION( "has value", has( rbtree, key ) );

   node_t *node = NULL;
   
   // remove the node from the tree
   node = remove( rbtree, key );
   
   // dispose of the value
   KEY_DISPOSE_FUNCTION( (*node).key );
   VALUE_DISPOSE_FUNCTION( (*node).value );
   
   // dispose of the node
   node_dispose( node );

   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return;
}

/**
   RBTree_kv_wipe_out
*/

void
RBTree_kv_wipe_out( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );

   int32_t i = 0;

   // get array of nodes
   node_t **array = nodes_as_array( rbtree );

   // delete nodes
   for ( i=0; i< (*rbtree).count; i++ )
   {
      node_dispose( array[i] );
   }

   // delete array
   free( array );

   // delete cursors, all but first
   RBTree_kv_cursor_type( Prefix ) *cursor = (*(*rbtree).first_cursor).next_cursor;
   RBTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
   (*(*rbtree).first_cursor).next_cursor = NULL;
   (*rbtree).last_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // set count to zero
   (*rbtree).count = 0;

   // set root to NULL
   (*rbtree).root.left = &null_node;

   POSTCONDITION( "is empty", (*rbtree).count == 0 );
   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return;
}

/**
   RBTree_kv_wipe_out_and_dispose
*/

void
RBTree_kv_wipe_out_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *rbtree )
{
   PRECONDITION( "rbtree not null", rbtree != NULL );
   PRECONDITION( "rbtree type ok", ( (*rbtree).type == RBTREE_KV_TYPE ) && ( (*rbtree).key_type = Key_Code ) && ( (*rbtree).item_type = Type_Code ) );
   LOCK( (*rbtree).mutex );
   INVARIANT( rbtree );

   int32_t i = 0;

   // get array of nodes
   node_t **array = nodes_as_array( rbtree );

   // delete nodes and values
   for ( i=0; i< (*rbtree).count; i++ )
   {
      KEY_DISPOSE_FUNCTION( (*array[i]).key );
      VALUE_DISPOSE_FUNCTION( (*array[i]).value );
      node_dispose( array[i] );
   }

   // delete array
   free( array );

   // delete cursors, all but first
   RBTree_kv_cursor_type( Prefix ) *cursor = (*(*rbtree).first_cursor).next_cursor;
   RBTree_kv_cursor_type( Prefix ) *next_cursor = NULL;
   (*(*rbtree).first_cursor).next_cursor = NULL;
   (*rbtree).last_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // set count to zero
   (*rbtree).count = 0;

   // set root to NULL
   (*rbtree).root.left = &null_node;

   POSTCONDITION( "is empty", (*rbtree).count == 0 );
   INVARIANT( rbtree );
   UNLOCK( (*rbtree).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

