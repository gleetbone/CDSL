/**
 @file AVLTree.c
 @author Greg Lee
 @version 1.0.0
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

#ifdef __cplusplus
extern "C" {
#endif

#ifdef PROTOCOLS_ENABLED   
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Clonable.ph"
#include "P_Iterable.ph"
#include "P_DIterable.ph"
#endif // PROTOCOLS_ENABLED   

#include <string.h>
#include <stdlib.h>   
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

#define AVLTREE_TYPE 0xA5000204

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

   int32_t type;
   int32_t item_type;
   
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

   Return 1 if avltree has an item for value, 0 if not

   @param avltree AVLTree_t instance
   @param key the key to query for
*/
static
int32_t
has( AVLTree_type( Prefix ) *avltree, Type value )
{
   int32_t result = 0;
   node_t *node = NULL;
   
   // get root node
   node = (*avltree).root;

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

   Return node in avltree that has value, NULL if none

   @param avltree AVLTree_t instance
   @param value the value to query for
*/

static
node_t *
item( AVLTree_type( Prefix ) *avltree, Type value )
{
   node_t *result = NULL;
   node_t *node = NULL;
   
   // get root node
   node = (*avltree).root;

   // recurse to see if can find value in tree
   if ( node != NULL )
   {
      result = item_recurse( node, value );
   }
   
   return result;
}

/**
   forward declarations of internal functions
*/

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
   insert_balance
*/
static
void
insert_balance( AVLTree_type( Prefix ) *avltree, node_t *node, int32_t balance )
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
         if ( (*(*node).left).balance == -1 ) 
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
         if ( (*(*node).right).balance == 1 ) 
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
*/
static
void
delete_balance( AVLTree_type( Prefix ) *avltree, node_t *node, int32_t balance )
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
         if ( (*(*node).left).balance <= 0 ) 
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
          if ( (*(*node).right).balance >= 0 ) 
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
*/
static
void
replace_node( node_t *target, node_t *source ) 
{
   node_t *left = NULL;
   node_t *right = NULL;
 
   left = (*source).left;
   right = (*source).right;
 
   // put contents of source into target
   (*target).balance = (*source).balance;
   (*target).value = (*source).value;
   (*target).left = left;
   (*target).right = right;
 
   if ( left != NULL ) 
   {
      (*left).parent = target;
   }
 
   if ( right != NULL ) 
   {
      (*right).parent = target;
   }
    
   return;
}



/**
   rotate_left
*/
static
node_t *
rotate_left( AVLTree_type( Prefix ) *avltree, node_t *node )
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
      (*right_left).parent = node;
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
*/
static
node_t *
rotate_right( AVLTree_type( Prefix ) *avltree, node_t *node )
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
      (*left_right).parent = node;
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
*/
static
node_t *
rotate_left_right( AVLTree_type( Prefix ) *avltree, node_t *node )
{
   node_t *left = NULL;
   node_t *left_right = NULL;
   node_t *parent = NULL;
   node_t *left_right_right = NULL;
   node_t *left_right_left = NULL;
 
   left = (*node).left;
   left_right = (*left).right;
   parent = (*node).parent;
   left_right_right = (*left_right).right;
   left_right_left = (*left_right).left;
 
   (*left_right).parent = parent;
   (*node).left = left_right_right;
   (*left).right = left_right_left;
   (*left_right).left = left;
   (*left_right).right = node;
   (*left).parent = left_right;
   (*node).parent = left_right;
 
   if ( left_right_right != NULL ) 
   {
      (*left_right_right).parent = node;
   }
 
   if ( left_right_left != NULL ) 
   {
      (*left_right_left).parent = left;
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
 
   (*left_right).balance = 0;
 
   return left_right;
}

/**
   rotate_right_left
*/
static
node_t *
rotate_right_left( AVLTree_type( Prefix ) *avltree, node_t *node )
{
   node_t *right = NULL;
   node_t *right_left = NULL;
   node_t *parent = NULL;
   node_t *right_left_left = NULL;
   node_t *right_left_right = NULL;
 
   right = (*node).right;
   right_left = (*right).left;
   parent = (*node).parent;
   right_left_left = (*right_left).left;
   right_left_right = (*right_left).right;
 
   (*right_left).parent = parent;
   (*node).right = right_left_left;
   (*right).left = right_left_right;
   (*right_left).right = right;
   (*right_left).left = node;
   (*right).parent = right_left;
   (*node).parent = right_left;
 
   if ( right_left_left != NULL ) 
   {
      (*right_left_left).parent = node;
   }
 
   if ( right_left_right != NULL ) 
   {
      (*right_left_right).parent = right;
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
 
   if ( (*right_left).balance == -1 ) 
   {
      (*node).balance = 0;
      (*right).balance = 1;
   } 
   else if ( (*right_left).balance == 0 ) 
   {
      (*node).balance = 0;
      (*right).balance = 0;
   } 
   else 
   {
      (*node).balance = -1;
      (*right).balance = 0;
   }
 
   (*right_left).balance = 0;
 
   return right_left;
}

/**
   AVLTree_put
*/

static
void
put( AVLTree_type( Prefix ) *avltree, Type value )
{
   node_t *node = NULL;
   node_t *new_node = NULL;
   node_t *left = NULL;
   node_t *right = NULL;
   
   // get new node
   new_node = node_make();
   (*new_node).value = value;

   if ( (*avltree).root == NULL ) 
   {
       (*avltree).root = new_node;
   } 
   else 
   {
      node = (*avltree).root;
      while ( node != NULL ) 
      {
         if ( ORDER_FUNCTION( value, (*node).value) == 1 ) 
         {
            left = (*node).left;
            
            if (left == NULL) 
            {
               (*node).left = new_node;
               (*new_node).parent = node;
               insert_balance( avltree, node, -1 );
               break;
            } 
            else 
            {
               node = left;
            }
         } 
         else if ( ORDER_FUNCTION( value, (*node).value) == 0 ) 
         {
            right = (*node).right;
            
            if ( right == NULL ) 
            {
               (*node).right = new_node;
               (*new_node).parent = node;
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
   items_as_array_recurse
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
*/

static
Type *
items_as_array( AVLTree_type( Prefix ) *avltree )
{
   Type *result = NULL;
   int32_t index = 0;
   
   result = ( Type * ) calloc( (*avltree).count + 1, sizeof( Type ) );
   
   if ( (*avltree).root != NULL )
   {
      items_as_array_recurse( (*avltree).root, result, &index );
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
nodes_as_array( AVLTree_type( Prefix ) *avltree )
{
   node_t **result = NULL;
   int32_t index = 0;
   
   if ( (*avltree).count == 0 )
   {
      result = ( node_t ** ) calloc( 1, sizeof( node_t ) );
   }
   else
   {
      result = ( node_t ** ) calloc( (*avltree).count, sizeof( node_t ) );
   }
   
   if ( (*avltree).root != NULL )
   {
      nodes_as_array_recurse( (*avltree).root, result, &index );
   }
   
   return result;
}

static
void
cursor_forth( AVLTree_cursor_type( Prefix ) *cursor );

/**
   remove
*/
static
node_t *
remove( AVLTree_type( Prefix ) *avltree, Type value )
{
   node_t *node = NULL;
   node_t *left = NULL;
   node_t *right = NULL;
   node_t *node_to_delete = NULL;
   node_t *parent = NULL;
   node_t *successor = NULL;
   node_t *successor_parent = NULL;
   node_t *successor_right = NULL;
   AVLTree_cursor_type( Prefix ) *cursor = NULL;
   
   // get node to delete
   node = item( avltree, value );
   
   if ( node != NULL )
   {
      // move cursors pointing to this node forth
      cursor = (*avltree).first_cursor;
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
            if ( node == (*avltree).root ) 
            {
               (*avltree).root = NULL;
            } 
            // case where node has no children
            else 
            {
               parent = (*node).parent;
               
               // node is parent's left child
               if ( (*parent).left == node ) 
               {
                  (*parent).left = NULL;
                  delete_balance( avltree, parent, 1 );
               } 
               // node is parent's right child
               else 
               {
                  (*parent).right = NULL;
                  delete_balance( avltree, parent, -1 );
               }
            }
         }
         // left child is NULL, right child isn't
         else 
         {
            replace_node( node, right );
            delete_balance( avltree, node, 0 );
            node_to_delete = right;
         }
      }
      // left child is not NULL, right child is NULL
      else if ( right == NULL ) 
      {
         replace_node( node, left );
         delete_balance( avltree, node, 0 );
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
            if ( node == (*avltree).root ) 
            {
               (*avltree).root = successor;
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
            delete_balance( avltree, successor, -1 );
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
      
            if ( (*successor_parent).left == successor ) 
            {
               (*successor_parent).left = successor_right;
            } 
            else 
            {
               (*successor_parent).right = successor_right;
            }
      
            if ( successor_right != NULL ) 
            {
               (*successor_right).parent = successor_parent;
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
      
            if ( node == (*avltree).root ) 
            {
               (*avltree).root = successor;
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
            delete_balance( avltree, successor_parent, 1 );
         }
      }
 
      // decrement element count
      (*avltree).count = (*avltree).count - 1;
      
   }
   
   return node_to_delete;   
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
height( AVLTree_type( Prefix ) *avltree )
{
   int32_t result = 0;
   
   result = height_recurse( (*avltree).root );
   
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
count( AVLTree_type( Prefix ) *avltree )
{
   int32_t result = 0;
   
   result = count_recurse( (*avltree).root );
   
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
   node = (*(*cursor).avltree).root;
   
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
   node = (*(*cursor).avltree).root;
   
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
cursor_item( AVLTree_cursor_type( Prefix ) *cursor )
{
   // return the value for the current cursor item
   return (*(*cursor).item).value;
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

   if ( (*(*p).first_cursor).next_cursor == NULL )
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
      result = ( (*(*p).last_cursor).next_cursor == NULL );
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
   
   result = ( (*node).balance == -1 ) ||( (*node).balance == 0 ) ||( (*node).balance == 1 );
   
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

static
void invariant( AVLTree_type( Prefix ) *p )
{
   assert(((void) "empty implies root null", is_empty_implies_root_null( p ) ));
   assert(((void) "nonnegative count", nonnegative_count( p ) ));
   assert(((void) "valid count", valid_count( p ) ));
   assert(((void) "first cursor not null", first_cursor_not_null( p ) ));
   assert(((void) "last cursor next null", last_cursor_next_null( p ) ));
   assert(((void) "last cursor null if one cursor", last_cursor_null_if_one_cursor( p ) ));
   assert(((void) "cursors avltree OK", cursors_avltree_ok( p ) ));
   assert(((void) "avltree in order", in_order( p ) ));
   assert(((void) "avltree in balance", balance_ok( p ) ));
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
   AVLTree_dispose( Prefix ),
   AVLTree_dispose_with_contents( Prefix ),
   AVLTree_make_from( Prefix ),
   AVLTree_make_duplicate_from( Prefix )
};

static
void *
p_iterable_table[P_ITERABLE_FUNCTION_COUNT]
=
{
   AVLTree_dispose( Prefix ),
   AVLTree_dispose_with_contents( Prefix ),
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
   AVLTree_dispose( Prefix ),
   AVLTree_dispose_with_contents( Prefix ),
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
   AVLTree_make
*/

AVLTree_type( Prefix ) *
AVLTree_make( Prefix )( void )
{
   // allocate avltree struct
   AVLTree_type( Prefix ) * avltree
      = ( AVLTree_type( Prefix ) * ) calloc( 1, sizeof( AVLTree_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( avltree );

   // set type codes
   (*avltree).type = AVLTREE_TYPE; 
   (*avltree).item_type = Type_Code;

   // root is null
   (*avltree).root = NULL;

   // count is zero
   (*avltree).count = 0;

   // set built-in cursor
   // allocate cursor struct
   AVLTree_cursor_type( Prefix ) *cursor
      =  ( AVLTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_cursor_type( Prefix ) ) );

   // set avltree
   (*cursor).avltree = avltree;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set avltree built-in cursor
   (*avltree).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*avltree).mutex );

   INVARIANT( avltree );

   return avltree;
}

/**
   AVLTree_make_duplicate_from
*/

AVLTree_type( Prefix ) *
AVLTree_make_duplicate_from( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );

   // make avltree struct
   AVLTree_type( Prefix ) *result = AVLTree_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = AVLTREE_TYPE; 
   (*result).item_type = Type_Code;

   // copy from avltree
   AVLTree_cursor_type( Prefix ) *cursor = AVLTree_cursor_make( Prefix )( avltree );
   
   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, DUPLICATE_FUNCTION( cursor_item( cursor ) ) );
      cursor_forth( cursor );
   }

   INVARIANT( result );

   return result;
}

/**
   AVLTree_make_from
*/

AVLTree_type( Prefix ) *
AVLTree_make_from( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );

   // make avltree struct
   AVLTree_type( Prefix ) *result = AVLTree_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = AVLTREE_TYPE; 
   (*result).item_type = Type_Code;

   // copy from avltree
   AVLTree_cursor_type( Prefix ) *cursor = AVLTree_cursor_make( Prefix )( avltree );
   
   cursor_start( cursor );
   while( cursor_off( cursor ) == 0 )
   {
      put( result, cursor_item( cursor ) );
      cursor_forth( cursor );
   }

   INVARIANT( result );

   return result;
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
   (*result).type = AVLTREE_TYPE; 
   (*result).item_type = Type_Code;

   int32_t i = 0;
   
   for ( i=0; i< count; i++ )
   {
      put( result, array[i] );
   }

   INVARIANT( result );

   return result;
}

/**
   AVLTree_cursor_make
*/

AVLTree_cursor_type( Prefix ) *
AVLTree_cursor_make( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );

   // allocate cursor struct
   AVLTree_cursor_type( Prefix ) *cursor
      =  ( AVLTree_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AVLTree_cursor_type( Prefix ) ) );

   // set avltree
   (*cursor).avltree = avltree;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // place cursor reference into avltree structure
   if ( (*avltree).last_cursor == NULL )
   {
      // set second cursor for avltree
      (*(*avltree).first_cursor).next_cursor = cursor;
      (*avltree).last_cursor = cursor;
   }
   else
   {
      // set additional cursor for avltree
      // (*avltree).last_cursor holds last cursor allocated
      (*(*avltree).last_cursor).next_cursor = cursor;
      (*avltree).last_cursor = cursor;
   }

   MULTITHREAD_MUTEX_INIT( (*avltree).mutex );

   INVARIANT( avltree );
   POSTCONDITION( "new cursor is last cursor", (*avltree).last_cursor == cursor );
   UNLOCK( (*avltree).mutex );

   return cursor;
}

/**
   AVLTree_dispose
*/

void
AVLTree_dispose( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );

   int32_t i = 0;
   
   // get array of nodes
   node_t **array = nodes_as_array( avltree );
   
   // delete nodes
   for ( i=0; i< (*avltree).count; i++ )
   {
      node_dispose( array[i] );
   }
   
   // delete array
   free( array );

   // delete cursors
   AVLTree_cursor_type( Prefix ) *cursor = (*avltree).first_cursor;
   AVLTree_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   MULTITHREAD_MUTEX_DESTROY( (*avltree).mutex );

   // delete avltree struct
   free( avltree );

   return;
}

/**
   AVLTree_dispose_with_contents
*/

void
AVLTree_dispose_with_contents( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );

   int32_t i = 0;
   
   // get array of nodes
   node_t **array = nodes_as_array( avltree );
   
   // delete nodes and values
   for ( i=0; i< (*avltree).count; i++ )
   {
      DISPOSE_FUNCTION( (*array[i]).value );
      node_dispose( array[i] );
   }
   
   // delete array
   free( array );

   // delete cursors
   AVLTree_cursor_type( Prefix ) *cursor = (*avltree).first_cursor;
   AVLTree_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   MULTITHREAD_MUTEX_DESTROY( (*avltree).mutex );

   // delete avltree struct
   free( avltree );

   return;
}

/**
   AVLTree_cursor_dispose
*/

void
AVLTree_cursor_dispose( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).avltree).type == AVLTREE_TYPE ) && ( (*(*cursor).avltree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).avltree).mutex );                                                                                                  
   INVARIANT( (*cursor).avltree );

   AVLTree_type( Prefix ) *avltree = (*cursor).avltree;

   AVLTree_cursor_type( Prefix ) *c1 = NULL;
   AVLTree_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from avltree structure
   c1 = (*(*cursor).avltree).first_cursor;
   c2 = (*c1).next_cursor;

   // search through the cursors
   while ( ( c2 != NULL) && ( flag == 0 ) )
   {
      if ( c2 == cursor )
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
   c1 = (*(*cursor).avltree).first_cursor;
   while ( c1 != NULL )
   {
      c2 = c1;
      c1 = (*c1).next_cursor;
   }
   (*(*cursor).avltree).last_cursor = c2;

   // only one cursor, last_cursor is NULL
   if ( c2 == (*(*cursor).avltree).first_cursor )
   {
      (*(*cursor).avltree).last_cursor = NULL;
   }
   
   // delete cursor struct
   free( cursor );

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return;
}

/**
   AVLTree_as_array

*/

Type *
AVLTree_as_array( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );

   Type *result = items_as_array( avltree );

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return result;
}

/**
   AVLTree_cursor_item_at
*/

Type
AVLTree_cursor_item_at( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).avltree).type == AVLTREE_TYPE ) && ( (*(*cursor).avltree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).avltree).mutex );
   INVARIANT( (*cursor).avltree );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Type value = cursor_item( cursor );

   INVARIANT( (*cursor).avltree );
   UNLOCK( (*(*cursor).avltree).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}


/**
   AVLTree_item_at
*/

Type
AVLTree_item_at( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );
   PRECONDITION( "not off", (*(*avltree).first_cursor).item != NULL );

   AVLTree_cursor_type( Prefix ) *cursor = (*avltree).first_cursor;

   Type value = cursor_item( cursor );

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return value;
}

/**
   AVLTree_item_at_index
*/

Type
AVLTree_item_at_index( Prefix )( AVLTree_type( Prefix ) *avltree, int32_t index )
{
   PRECONDITION( "avltree not null", avltree != NULL );  
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*avltree).count ) );

   int32_t i = 0;
   Type value;
   
   cursor_start( (*avltree).first_cursor );
   value = cursor_item( (*avltree).first_cursor );
   
   for( i = 1; i <= index; i++ )
   {
      cursor_forth( (*avltree).first_cursor );
      value = cursor_item( (*avltree).first_cursor );
   }

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return value;
}

/**
   AVLTree_count
*/

int32_t
AVLTree_count( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );

   int32_t count = (*avltree).count;

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return count;
}

/**
   AVLTree_height
*/

int32_t
AVLTree_height( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );

   int32_t count = height( avltree );

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return count;
}

/**
   AVLTree_off
*/

int32_t
AVLTree_off( Prefix)( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );

   int32_t result = cursor_off( (*avltree).first_cursor );

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return result;
}

/**
   AVLTree_cursor_off
*/

int32_t
AVLTree_cursor_off( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).avltree).type == AVLTREE_TYPE ) && ( (*(*cursor).avltree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   int32_t result = cursor_off( cursor );

   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AVLTree_is_empty
*/

int32_t
AVLTree_is_empty( Prefix)( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );

   int32_t result = ( (*avltree).count ==  0 );

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return result;
}

/**
   AVLTree_has
*/

int32_t
AVLTree_has( Prefix )( AVLTree_type( Prefix ) *avltree, Type value )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );

   int32_t result = has( avltree, value );

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return result;
}

/**
   AVLTree_cursor_forth
*/
void
AVLTree_cursor_forth( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).avltree).type == AVLTREE_TYPE ) && ( (*(*cursor).avltree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   cursor_forth( cursor );
   
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_cursor_back
*/
void
AVLTree_cursor_back( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).avltree).type == AVLTREE_TYPE ) && ( (*(*cursor).avltree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );

   cursor_back( cursor );
   
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_cursor_go
*/
void
AVLTree_cursor_go( Prefix )( AVLTree_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).avltree).type == AVLTREE_TYPE ) && ( (*(*cursor).avltree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).avltree).mutex );
   INVARIANT( (*cursor).avltree );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*(*cursor).avltree).count ) ) );

   int32_t i = 0;
   cursor_start( cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( cursor );
   }

   INVARIANT( (*cursor).avltree );
   UNLOCK( (*(*cursor).avltree).mutex );
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
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).avltree).type == AVLTREE_TYPE ) && ( (*(*cursor).avltree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).avltree).mutex );
   INVARIANT( (*cursor).avltree );

   int32_t result = 0;
   int32_t flag = 0;
   node_t *target = (*cursor).item;

   if ( (*(*cursor).avltree).count > 0 )
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
   
   INVARIANT( (*cursor).avltree );
   UNLOCK( (*(*cursor).avltree).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AVLTree_cursor_start
*/

void
AVLTree_cursor_start( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).avltree).type == AVLTREE_TYPE ) && ( (*(*cursor).avltree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).avltree).mutex );
   INVARIANT( (*cursor).avltree );

   cursor_start( cursor );

   INVARIANT( (*cursor).avltree );
   UNLOCK( (*(*cursor).avltree).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_cursor_finish
*/

void
AVLTree_cursor_finish( Prefix )( AVLTree_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( (*(*cursor).avltree).type == AVLTREE_TYPE ) && ( (*(*cursor).avltree).item_type = Type_Code ) ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).avltree).mutex );
   INVARIANT( (*cursor).avltree );

   cursor_finish( cursor );

   INVARIANT( (*cursor).avltree );
   UNLOCK( (*(*cursor).avltree).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AVLTree_forth
*/
void
AVLTree_forth( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );
   PRECONDITION( "not off", (*(*avltree).first_cursor).item != NULL );

   cursor_forth( (*avltree).first_cursor );

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return;
}

/**
   AVLTree_back
*/
void
AVLTree_back( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );
   PRECONDITION( "not off", (*(*avltree).first_cursor).item != NULL );

   cursor_back( (*avltree).first_cursor );

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return;
}

/**
   AVLTree_go
*/
void
AVLTree_go( Prefix )( AVLTree_type( Prefix ) *avltree, int32_t index )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*avltree).count ) ) );

   int32_t i = 0;
   cursor_start( (*avltree).first_cursor );

   for( i = 1; i <= index; i++ )
   {
      cursor_forth( (*avltree).first_cursor );
   }

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return;
}

/**
   AVLTree_index
*/

int32_t
AVLTree_index( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );

   int32_t result = 0;
   int32_t flag = 0;
   AVLTree_cursor_type( Prefix ) *cursor = (*avltree).first_cursor;
   node_t *target = (*cursor).item;

   if ( (*avltree).count > 0 )
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
   
   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return result;
}

/**
   AVLTree_start
*/

void
AVLTree_start( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );

   cursor_start( (*avltree).first_cursor );

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return;
}

/**
   AVLTree_finish
*/

void
AVLTree_finish( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );

   cursor_finish( (*avltree).first_cursor );

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return;
}

/**
   AVLTree_put
*/

void
AVLTree_put( Prefix )( AVLTree_type( Prefix ) *avltree, Type value )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );

   put( avltree, value );

   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return;
}

/**
   AVLTree_remove
*/

void
AVLTree_remove( Prefix )( AVLTree_type( Prefix ) *avltree, Type value )
{
   PRECONDITION( "avltree not null", avltree != NULL ); 
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );
   PRECONDITION( "has value", has( avltree, value ) );

   node_t *node = NULL;
   
   node = remove( avltree, value );

   // dispose of node
   node_dispose( node );
      
   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return;
}

/**
   AVLTree_remove_and_dispose
*/

void
AVLTree_remove_and_dispose( Prefix )( AVLTree_type( Prefix ) *avltree, Type value )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );
   PRECONDITION( "has value", has( avltree, value ) );

   node_t *node = NULL;
   
   node = remove( avltree, value );
   
   // dispose of value
   DISPOSE_FUNCTION( (*node).value );
   
   // dispose of node
   node_dispose( node );
      
   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return;
}

/**
   AVLTree_wipe_out
*/

void
AVLTree_wipe_out( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );

   int32_t i = 0;
   
   // get array of nodes
   node_t **array = nodes_as_array( avltree );
   
   // delete nodes
   for ( i=0; i< (*avltree).count; i++ )
   {
      node_dispose( array[i] );
   }
   
   // delete array
   free( array );

   // delete cursors, all but first
   AVLTree_cursor_type( Prefix ) *cursor = (*(*avltree).first_cursor).next_cursor;
   AVLTree_cursor_type( Prefix ) *next_cursor = NULL;
   (*(*avltree).first_cursor).next_cursor = NULL;
   (*avltree).last_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // set count to zero
   (*avltree).count = 0;
   
   // set root to NULL
   (*avltree).root = NULL;

   POSTCONDITION( "is empty", (*avltree).count == 0 );
   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return;
}

/**
   AVLTree_wipe_out_and_dispose
*/

void
AVLTree_wipe_out_and_dispose( Prefix )( AVLTree_type( Prefix ) *avltree )
{
   PRECONDITION( "avltree not null", avltree != NULL );  
   PRECONDITION( "avltree type ok", ( (*avltree).type == AVLTREE_TYPE ) && ( (*avltree).item_type = Type_Code ) );
   LOCK( (*avltree).mutex );
   INVARIANT( avltree );

   int32_t i = 0;
   
   // get array of nodes
   node_t **array = nodes_as_array( avltree );
   
   // delete nodes and values
   for ( i=0; i< (*avltree).count; i++ )
   {
      DISPOSE_FUNCTION( (*array[i]).value );
      node_dispose( array[i] );
   }
   
   // delete array
   free( array );

   // delete cursors, all but first
   AVLTree_cursor_type( Prefix ) *cursor = (*(*avltree).first_cursor).next_cursor;
   AVLTree_cursor_type( Prefix ) *next_cursor = NULL;
   (*(*avltree).first_cursor).next_cursor = NULL;
   (*avltree).last_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // set count to zero
   (*avltree).count = 0;

   // set root to NULL
   (*avltree).root = NULL;

   POSTCONDITION( "is empty", (*avltree).count == 0 );
   INVARIANT( avltree );
   UNLOCK( (*avltree).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

