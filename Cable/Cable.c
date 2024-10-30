/**
 @file Cable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Character strings implemented as a binary search tree of substrings"

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

 Function definitions for the opaque cable_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Cable.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

/**
   Additional "hidden" API functions
   Include these function prototypes in your C file if you wish to use them.
   These functions are used for testing.
*/

/**
   cable_make_capacity

   Create and initialize a cable_t instance.
   Content will be the empty cable and the capacity of each node will be "capacity".

   @return pointer to the new data structure
*/
cable_t *
cable_make_capacity( int32_t capacity );

/**
   cable_make_capacity_from_cstring

   Create and initialize a cable_t instance.
   Content will be from other and the capacity of each node will be "capacity".

   @param str the cstring to copy from
   @param capacity the new cable's node capacity
   @return pointer to the new data structure
*/
cable_t *
cable_make_capacity_from_cstring( char_t *str, int32_t capacity );

/**
   cable_capacity

   Returns the number of available characters in cable nodes.

   @param cable the cable_t instance
   @return number of characters available for storage in cable
*/
int32_t
cable_capacity( cable_t *cable );


#define DEFAULT_STRING_LENGTH 128
#define HASH_PRIME_NUMBER 8388593U

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
   int32_t index;
   int32_t start;
   int32_t count;
   rbcolor_t color;
   struct node *prev;
   struct node *next;
   struct node *parent;
   struct node *left;
   struct node *right;
   char_t *str;
};

typedef struct node node_t;

/**
   null_node

   special node to act as sentinel for all instances of Cable
   singleton null node - helps avoid complexity in code
*/
static int32_t null_node_initialized = 0;
static node_t null_node;

struct cable_cursor_struct;
typedef struct cable_cursor_struct cable_cursor_t;

/**
   Binary search tree structure definition.
*/

struct cable_struct
{
   int32_t _type;

   node_t root;   // pseudo root, helps avoid complexity in code
   int32_t count;
   int32_t str_count;
   int32_t str_length;
   node_t *first;
   cable_cursor_t *cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure definition. Holds reference to cable and current node.
*/

struct cable_cursor_struct
{
   cable_t *cable;
   node_t *item;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   local functions
*/

/**
   redo_indices
*/

static
void
redo_indices( cable_t *cable );

/**
   black_path_count

   counts number of black nodes in path to root

   @param node the node to start from
   @return count of black nodes
*/

static
int32_t
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
   node_make

   create a new cable node

   @param cable the tree of nodes
   @return the new node
*/

static
node_t *
node_make( cable_t *cable )
{
   // allocate node
   node_t *node = ( node_t * ) calloc( 1, sizeof( node_t ) );
   CHECK( "node allocated correctly", node != NULL );

   // set values
   (*node).index = 0;
   (*node).start = 0;
   (*node).count = 0;
   (*node).prev = NULL;
   (*node).next = NULL;
   (*node).parent = &null_node;
   (*node).left = &null_node;
   (*node).right = &null_node;
   (*node).color = black;

   // allocate string storage
   (*node).str = ( char_t * ) calloc( (*cable).str_length + 1, sizeof( char_t ) );
   CHECK( "(*node).str allocated correctly", (*node).str != NULL );

   POSTCONDITION( "node not null", node != NULL );
   POSTCONDITION( "node str not null", (*node).str != NULL );
   POSTCONDITION( "node parent null", (*node).parent == &null_node );
   POSTCONDITION( "node left null", (*node).left == &null_node );
   POSTCONDITION( "node right null", (*node).right == &null_node );
   POSTCONDITION( "node color black", (*node).color == black );

   return node;
}

/**
   node_make_from

   make a new node from an existing one

   @param cable the tree of nodes
   @param n the node to make the new one from
   @return the new node
*/

static
node_t *
node_make_from( cable_t *cable, node_t *n )
{
   // allocate node
   node_t *node = ( node_t * ) calloc( 1, sizeof( node_t ) );
   CHECK( "node allocated correctly", node != NULL );

   // set values
   (*node).index = (*n).index;
   (*node).start = (*n).start;
   (*node).count = (*n).count;
   (*node).prev = (*n).prev;
   (*node).next = (*n).next;
   (*node).parent = &null_node;
   (*node).left = &null_node;
   (*node).right = &null_node;
   (*node).color = black;

   // allocate string storage
   (*node).str = ( char_t * ) calloc( (*cable).str_length + 1, sizeof( char_t ) );
   CHECK( "(*node).str allocated correctly", (*node).str != NULL );

   // copy string contents
   memcpy( (*node).str, (*n).str, (*cable).str_length );

   POSTCONDITION( "node not null", node != NULL );
   POSTCONDITION( "node str not null", (*node).str != NULL );
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
node_dispose( node_t *node )
{
   PRECONDITION( "node not null", node != NULL );

   // free string storage
   free( (*node).str );

   (*node).index = 0;
   (*node).start = 0;
   (*node).count = 0;
   (*node).color = 0;
   (*node).prev = NULL;
   (*node).next = NULL;
   (*node).parent = NULL;
   (*node).left = NULL;
   (*node).right = NULL;
   (*node).str = NULL;

   // free node
   free( node );

   return;
}


/**
   node_has_index

   does this node contain the desired index?

   @param node the node to look at
   @param index the desired indes
   @return 1 if index is in node, 0 otherwise
*/

static
int32_t
node_has_index( node_t *n, int32_t index )
{
   int32_t result = 0;

   if (
      ( index >= (*n).index )
      &&
      (
         ( index < ( (*n).index + (*n).count ) )
         ||
         ( (*n).count ) == 0 )
   )
   {
      result = 1;
   }

   return result;
}

/**
   node_for_index_recurse

   look for the node that contains index, recursive

   @param node the node to start looking at
   @param index the desired index
   @return the node with the desired index, NULL otherwise
*/

static
node_t *
node_for_index_recurse( node_t *node, int32_t index )
{
   node_t *result = &null_node;

   if ( node_has_index( node, index ) == 1 )
   {
      result = node;
   }

   if ( result == &null_node )
   {
      if ( ( index < (*node).index ) == 1 )
      {

         if ( (*node).left != &null_node )
         {
            result = node_for_index_recurse( (*node).left, index );
         }
      }
   }

   if ( result == &null_node )
   {
      if ( ( index < (*node).index ) == 0 )
      {

         if ( (*node).right != &null_node )
         {
            result = node_for_index_recurse( (*node).right, index );
         }
      }
   }

   return result;
}

/**
   node for index

   Return node in cable for which the index is valid, NULL if none

   @param cable cable_t instance
   @param index the index to query for
   @return the node with the index or NULL if none
*/

static
node_t *
node_for_index( cable_t *cable, int32_t index )
{
   node_t *result = NULL;
   node_t *node = NULL;

   // get root node
   result = &null_node;
   node = (*cable).root.left;

   // recurse to see if can find value in tree
   if ( node != &null_node )
   {
      result = node_for_index_recurse( node, index );
   }

   return result;
}

/**
   node_as_cstring

   Return contents in node as cstring, not a copy

   @param cable cable_t instance
   @return the entire string held in the cable as a C string
*/

static
char_t *
node_as_cstring( node_t *node )
{
   char_t *result = NULL;

   // set trailing zero
   (*node).str[ (*node).start + (*node).count ] = 0;

   // set result
   result = &( (*node).str[ (*node).start ] );

   return result;
}

/**
   tree_rotate_left

   perform left rotation starting at node

   @param cable the tree of nodes
   @param node the node to rotate around
*/
static
void
tree_rotate_left( cable_t *cable, node_t *node )
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
   tree_rotate_right

   perform right rotation starting at node

   @param cable the tree of nodes
   @param node the node to rotate around
*/
static void
tree_rotate_right( cable_t *cable, node_t *node )
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
   tree_has_recurse

   does the tree contain a node, recursive

   @param node the node to start looking at
   @param nx the node to look for
   @return 1 if found, 0 otherwise
*/
static
int32_t
tree_has_recurse( node_t *node, node_t *nx )
{
   int32_t result = 0;

   // in order recursion - left, self, right
   // if tested value is found, exit
   if ( (*node).left != &null_node )
   {
      result = tree_has_recurse( (*node).left, nx );
   }

   if ( result == 0 )
   {
      result = ( node == nx );
   }

   if ( result == 0 )
   {
      if ( (*node).right != &null_node )
      {
         result = tree_has_recurse( (*node).right, nx );
      }
   }
   return result;
}

/**
   tree_has

   Return 1 if rbtree has node, 0 if not

   @param cable cable_t instance
   @param nx the node to query for
   @return 1 if found, 0 otherwise
*/

static
int32_t
tree_has( cable_t *cable, node_t *nx )
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*cable).root.left;

   // recurse to see if can find value in tree
   if ( node != &null_node )
   {
      result = tree_has_recurse( node, nx );
   }

   return result;
}

/**
   tree_sibling_of

   find sibling of node, if it exists

   @param node the node to start with
   @return the sibling, or NULL if not found
*/
static
node_t *
tree_sibling_of( node_t *node )
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
  tree_repair_put

  fix up the red-black balanced binary search tree in cable after a put

  @param cable the tree of nodes
  @param node the node just added
*/

static
void
tree_repair_put( cable_t *cable, node_t *node )
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
      ( n != (*cable).root.left )
      &&
      ( ( *(*n).parent ).color == red )
   )
   {

      // recolor up if more work needed
      if ( ( * tree_sibling_of( (*n).parent ) ).color == red )
      {
         ( *(*n).parent ).color = black;
         ( * tree_sibling_of( (*n).parent ) ).color = black;
         if ( ( *(*n).parent ).parent != &null_node )
         {
            ( *( *(*n).parent ).parent ).color = red;
            tree_repair_put( cable, ( *(*n).parent ).parent );
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
            tree_rotate_left( cable, n );
         }
         ( *(*n).parent ).color = black ;
         if ( ( *(*n).parent ).parent != &null_node )
         {
            ( *( *(*n).parent ).parent ).color = red;
            tree_rotate_right( cable, ( *(*n).parent ).parent );
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
            tree_rotate_right( cable, n );
         }
         ( *(*n).parent ).color = black;
         if ( ( *(*n).parent ).parent != &null_node )
         {
            ( *( *(*n).parent ).parent ).color = red;
            tree_rotate_left( cable, ( *(*n).parent ).parent );
         }
      }
   }

   // color the root black
   ( *(*cable).root.left ).color = black;

   return;
}

/**
   tree_put

   put a node into the tree of nodes

   @param cable the tree of nodes
   @param n the node to add
*/

static
void
tree_put( cable_t *cable, node_t *n )
{
   node_t *node = NULL;
   node_t *parent = NULL;
   int32_t result = 0;

   // start at root of tree
   node = (*cable).root.left;
   parent = &(*cable).root;

   // find insertion point
   while( node != &null_node )
   {
      parent = node;
      result = ( (*n).index < (*node).index );
      if ( result == 1 )
      {
         node = (*node).left;
      }
      else
      {
         node = (*node).right;
      }
   }

   // set new node's members
   (*n).left = &null_node;
   (*n).right = &null_node;
   (*n).parent = parent;
   (*n).color = red;

   // adjust its parent node
   if (
      ( parent == &(*cable).root )
      ||
      ( (*n).index < (*parent).index )
   )
   {
      (*parent).left = n;
      tree_repair_put( cable, n );
   }
   else
   {
      (*parent).right = n;
      tree_repair_put( cable, n );
   }

   // ensure tree root is black
   ( *(*cable).root.left ).color = black;

   // increment count
   (*cable).count = (*cable).count + 1;

   return;
}

/**
   tree_repair_remove

   repair the tree after a node has been deleted by rotating and repainting
   colors to restore the red-black tree's properties

   @param cable the tree of nodes
   @param node the node where another node was just removed
*/
static
void
tree_repair_remove( cable_t *cable, node_t *node )
{
   node_t *n = NULL;
   node_t *sibling = NULL;

   n = node;

   // while node is not tree root and is black
   while ( ( n != (*cable).root.left ) && ( (*n).color == black ) )
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
            tree_rotate_left( cable, (*n).parent );
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
               tree_rotate_right( cable, sibling );
               sibling = ( *(*n).parent ).right;
            }

            (*sibling).color = ( *(*n).parent ).color;
            ( *(*n).parent ).color = black;
            ( *(*sibling).right ).color = black;
            tree_rotate_left( cable, (*n).parent );
            n = (*cable).root.left;
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
            tree_rotate_right( cable, (*n).parent );
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
               tree_rotate_left( cable, sibling );
               sibling = ( *(*n).parent ).left;
            }

            (*sibling).color = ( *(*n).parent ).color;
            ( *(*n).parent ).color = black;
            ( *(*sibling).left ).color = black;
            tree_rotate_right( cable, (*n).parent );
            n = (*cable).root.left;
         }
      }
   }

   (*n).color = black;

   return;
}

/**
   tree_predecessor

   returns the node before node, or nil if none.

   @param cable the tree of nodes
   @param the node to start with
   @return the predecessor of the node if any, NULL otherwise
*/
static
node_t *
tree_predecessor( cable_t *cable, node_t *node )
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
         if ( result == &(*cable).root )
         {
            result = &null_node;
         }

      }
   */

   return( result );
}

static
void
cursor_forth( cable_cursor_t *cursor );

static
void
cursor_start( cable_cursor_t *cursor );

static
node_t *
cursor_item( cable_cursor_t *cursor );

/**
   tree_remove

   remove a node from the tree

   @param cable the tree of nodes
   @param n the node to remove
*/
static
void
tree_remove( cable_t *cable, node_t *n )
{
   node_t *node = NULL;
   node_t *pre = NULL;
   node_t *pull_up = NULL;
   node_t *n_parent = NULL;
   int32_t n_is_parents_left = 0;
   rbcolor_t n_color = 0;
   node_t *n_left = NULL;
   node_t *n_right = NULL;
   node_t *p_parent = NULL;
   int32_t p_is_parents_left = 0;
   rbcolor_t p_color = 0;
   node_t *p_left = NULL;
   node_t *p_right = NULL;

   // get the node to be removed
   node = n;

   // if node is not null, continue
   if ( node != &null_node )
   {
      // move cursor forth if pointing to this node
      if ( ( *(*cable).cursor ).item == node )
      {
         cursor_forth( (*cable).cursor );
      }

      // if node has two children, find predecessor, swap pre's data into node
      // and set node to pre
      if ( ( (*node).left != &null_node ) && ( (*node).right != &null_node ) )
      {
         pre = tree_predecessor( cable, node );

         // swap nodes pre and node in tree
         n_parent = (*node).parent;
         if ( ( *(*node).parent ).left == node )
         {
            n_is_parents_left = 1;
         }
         else
         {
            n_is_parents_left = 0;
         }

         n_color = (*node).color;
         n_left = (*node).left;
         n_right = (*node).right;

         p_parent = (*pre).parent;
         if ( ( *(*pre).parent ).left == pre )
         {
            p_is_parents_left = 1;
         }
         else
         {
            p_is_parents_left = 0;
         }

         p_color = (*pre).color;
         p_left = (*pre).left;
         p_right = (*pre).right;

         (*node).parent = p_parent;
         (*node).left = p_left;
         (*node).right = p_right;
         (*node).color = p_color;

         if ( n_is_parents_left == 1 )
         {
            ( *n_parent ).left = pre;
         }
         else
         {
            ( *n_parent ).right = pre;
         }

         ( *n_left ).parent = pre;
         ( *n_right ).parent = pre;

         (*pre).parent = n_parent;
         (*pre).left = n_left;
         (*pre).right = n_right;
         (*pre).color = n_color;

         if ( p_parent == node )
         {
            (*node).parent = pre;
            (*pre).left = node;

            if ( p_left != &null_node )
            {
               ( *p_left ).parent = node;
            }

// the following commented out bit of code is never called when the tree invariants are true
//            if ( p_right != &null_node )
//            {
//               (*p_right).parent = node;
//            }

         }
         else
         {
// the following commented out bit of code is never called when the tree invariants are true
//            if ( p_is_parents_left == 1 )
//            {
//               (*p_parent).left = node;
//            }
//            else
            {
               ( *p_parent ).right = node;
            }

            if ( p_left != &null_node )
            {
               ( *p_left ).parent = node;
            }

// the following commented out bit of code is never called when the tree invariants are true
//            if ( p_right != &null_node )
//            {
//               (*p_right).parent = node;
//            }

         }

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

         if ( node == (*cable).root.left )
         {
            // eliminate tree root
            (*cable).root.left = pull_up;
            ( *pull_up ).parent = &( (*cable).root );
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
            tree_repair_remove( cable, pull_up );
         }
      }
      else if ( node == (*cable).root.left )
      {
         // eliminate root, tree is not empty
         (*cable).root.left = &null_node;
      }
      else
      {
         // if node is black, repair tree
         if ( (*node).color == black )
         {
            tree_repair_remove( cable, node );
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
      (*cable).count = (*cable).count - 1;
   }

   // dispose of node
   node_dispose( node );

   return;
}

/**
   tree_count_recurse

   get the node count of the tree, recursive

   @param node the node to start with
   @return the count of nodes
*/
static
int32_t
tree_count_recurse( node_t *node )
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
      left_count = tree_count_recurse( (*node).left );
      right_count = tree_count_recurse( (*node).right );

      result = left_count + right_count + 1;
   }

   return result;

}

/**
   tree_count

   get the node count of the tree, recursive

   @param cable the tree of nodes
   @return the count of nodes
*/
static
int32_t
tree_count( cable_t *cable )
{
   int32_t result = 0;

   result = tree_count_recurse( (*cable).root.left );

   return result;
}

/**
   recursion for cable cursor functions - start, item, forth, off

   The following routines depend on the fact that the cable
   is (already) in order and that the forth recursion keeps track
   of the last seen ( the previous ) node (in the cursor structure).
*/

/**
   cursor_finish

   put the cursor at the end of the cable

   @param cursor the cursor
*/
static
void
cursor_finish( cable_cursor_t *cursor )
{
   node_t *node = NULL;

   // set node from the cable root
   node = ( *(*cursor).cable ).root.left;

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

   put the cursor at the start of the cable

   @param cursor the cursor
*/
static
void
cursor_start( cable_cursor_t *cursor )
{
   node_t *node = NULL;

   // set node from the cable root
   node = ( *(*cursor).cable ).root.left;

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
   cursor_item

   return the current node

   @param cursor the cursor
   @return the cursor's current node
*/
static
node_t *
cursor_item( cable_cursor_t *cursor )
{
   // return the value for the current cursor item
   return (*cursor).item;
}


/**
   cursor_forth

   put the cursor at the next node in the tree

   @param cursor the cursor
*/
static
void
cursor_forth( cable_cursor_t *cursor )
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

   test to see if the cursor is at the end of the tree

   @param cursor the cursor
   @return 1 if at end, 0 otherwise
*/
static
int32_t
cursor_off(  cable_cursor_t *cursor )
{
   int32_t result = 0;

   // cursor item is null_node or root == off
   if (
      ( (*cursor).item == &( *(*cursor).cable ).root )
      ||
      ( (*cursor).item == &null_node )
   )
   {
      result = 1;
   }

   return result;
}

/**
   subcable_from_bounds

   return a new cable made from an existing cable between a start and end index

   @param cable the tree of nodes
   @param start_index index of desired start of new cable
   @param end_index index of desired end of new cable
   @return a new cable starting at start_index and ending at end_index
*/

static
cable_t *
subcable_from_bounds( cable_t *cable, int32_t start_index, int32_t end_index )
{
   cable_t *result = NULL;
   node_t *node = NULL;
   node_t *n = NULL;
   node_t *n1 = NULL;
   char_t *cp = NULL;
   char_t *cpn = NULL;
   int32_t i = 0;
   int32_t length = 0;
   int32_t length1 = 0;
   int32_t index = 0;
   int32_t count = 0;
   char_t c = 0;
   int32_t i_node = 0;

   // make a new cable to return
   result = cable_make();

   // if invalid indices, return empty cable
   if ( end_index >= start_index )
   {
      // remove the empty node in result
      tree_remove( result, (*result).root.left );

      length = end_index - start_index + 1;
      length1 = length;
      if ( (*cable).str_length < length1 )
      {
         length1 = (*cable).str_length;
      }

      // set to iterate through cable
      node = node_for_index( cable, start_index );
      cp = node_as_cstring( node );
      index = (*node).index;
      count = (*node).count;

      // set up new node
      i_node = 0;
      n = node_make( cable );
      (*n).index = 0;
      (*n).start = 0;
      (*n).count = length1;
      cpn = (*n).str;
      (*result).first = n;

      // tree_put new node into result tree
      redo_indices( result );
      tree_put( result, n );

      // copy characters into new nodes
      for ( i = start_index; i <= end_index; i++ )
      {

         // get character in cable
         c = cp[ i - index ];

         // put into new node
         cpn[i_node] = c;

         // update node index
         i_node++;

         // see if node is full
         if ( i_node >= (*cable).str_length )
         {
            // is full, make new node
            n1 = node_make( cable );
            (*n1).index = i;
            (*n1).start = 0;

            length1 = end_index - i;
            if ( (*cable).str_length < length1 )
            {
               length1 = (*cable).str_length;
            }

            (*n1).count = length1;

            (*n).next = n1;
            (*n1).prev = n;
            n = n1;
            cpn = (*n).str;
            i_node = 0;

            // put new node into tree
            redo_indices( result );
            tree_put( result, n );

         }

         // set up for next "i"
         if ( ( i - index ) >= ( count - 1 ) )
         {
            node = (*node).next;
            if ( node != NULL )
            {
               cp = node_as_cstring( node );
               index = (*node).index;
               count = (*node).count;
            }
         }
      }
   }

   return result;
}

/**
   redo_indices

   recalculate the start indices for each node in the cable

   @param cable the cable
*/

static
void
redo_indices( cable_t *cable )
{
   node_t *node = NULL;
   int32_t index = 0;
   int32_t count = 0;

   // start at first node, set index
   node = (*cable).first;
   (*node).index = 0;
   index = (*node).index;
   count = (*node).count;
   node = (*node).next;
   index = count;

   // set indices through linked list
   while ( node != NULL )
   {
      (*node).index = index;
      index = index + (*node).count;
      count = count + (*node).count;
      node = (*node).next;
   }

   // set string count
   (*cable).str_count = count;

   return;
}
/**
   remove_from_bounds

   remove part of a cable between start_index and end_index

   @param cable the tree of nodes
   @param start_index index where to start removing characters
   @param end_index index where to end removing characters
*/

static
void
remove_from_bounds( cable_t *cable, int32_t start_index, int32_t end_index )
{
   node_t *node = NULL;
   node_t *node1 = NULL;
   node_t *n1 = NULL;
   node_t *n2 = NULL;
   node_t *nx = NULL;
   char_t *cp = NULL;
   int32_t i = 0;
   int32_t length = 0;
   int32_t old_n1_count = 0;
   int32_t length1 = 0;
   int32_t count = 0;
   int32_t n_to_move = 0;

   // get start and end node for start and end indices
   n1 = node_for_index( cable, start_index );
   n2 = node_for_index( cable, end_index );
   length = end_index - start_index + 1;

   // cases - same node, next to each other nodes, separated nodes

   // same node
   if ( n1 == n2 )
   {
      n_to_move = (*n1).count - length - ( start_index - (*n1).index );
      count = (*n1).count - length;
      cp = (*n1).str;

      // move the chars after end_index up to start_index
      for ( i = 0; i < n_to_move; i++ )
      {
         cp[i + start_index - (*n1).index ] = cp[ i + end_index - (*n1).index + 1 ];
      }

      // adjust node count
      (*n1).count = count;
      redo_indices( cable );

      // now see if n1 is now empty; if so, remove
      if ( ( (*cable).count > 1 ) && ( (*n1).count ==  0 ) )
      {
         if ( n1 == (*cable).first )
         {
            (*cable).first = (*n1).next;
            if ( (*n1).next != NULL )
            {
               ( *(*n1).next ).prev = NULL;
            }
         }
         else
         {
            ( *(*n1).prev ).next = (*n1).next;
            if ( (*n1).next != NULL )
            {
               ( *(*n1).next ).prev = (*n1).prev;
            }
         }
         tree_remove( cable, n1 );
         redo_indices( cable );
      }
   }

   // neighbor nodes
   else if ( (*n1).next == n2 )
   {
      // change count in n1 and n2, start in n2
      old_n1_count = (*n1).count;
      (*n1).count = start_index - (*n1).index;

      length1 = length - ( old_n1_count - (*n1).count );
      (*n2).start = (*n2).start + length1;
      (*n2).count = (*n2).count - length1;

      redo_indices( cable );

      // now see if n1 and/or n2 is now empty; if so, remove
      if ( ( (*cable).str_count > 0 ) && ( (*n1).count == 0 ) && ( (*n2).count == 0 ) )
      {
         // both n1 and n2 are empty, remove both
         if ( n1 == (*cable).first )
         {
            (*cable).first = (*n2).next;
            if ( (*n2).next != NULL )
            {
               ( *(*n2).next ).prev = NULL;
            }
         }
         else
         {
            ( *(*n1).prev ).next = (*n2).next;
            if ( (*n2).next != NULL )
            {
               ( *(*n2).next ).prev = (*n1).prev;
            }
         }
         tree_remove( cable, n1 );
         tree_remove( cable, n2 );
         redo_indices( cable );
      }
      else if ( ( (*cable).str_count == 0 ) && ( (*n1).count == 0 ) && ( (*n2).count == 0 ) )
      {
         // cable is empty, both n1 and n2 are empty, remove n2
         (*n1).prev = NULL;
         (*n1).next = NULL;
         tree_remove( cable, n2 );
         redo_indices( cable );
      }
      else if ( ( (*cable).str_count > 0 ) && ( (*n1).count ==  0 ) )
      {
         if ( n1 == (*cable).first )
         {
            (*cable).first = n2;
            (*n2).prev = NULL;
         }
         else
         {
            ( *(*n1).prev ).next = (*n1).next;
            if ( (*n1).next != NULL )
            {
               ( *(*n1).next ).prev = (*n1).prev;
            }
         }
         tree_remove( cable, n1 );
         redo_indices( cable );
      }
      else if ( ( (*cable).str_count > 0 ) && ( (*n2).count ==  0 ) )
      {
         (*n1).next = (*n2).next;
         if ( (*n2).next != NULL )
         {
            ( *(*n2).next ).prev = n1;
         }
         tree_remove( cable, n2 );
         redo_indices( cable );
      }

   }

   // not neighbor nodes
   else
   {
      // delete nodes between n1 and n2
      node = (*n1).next;
      while( node != n2 )
      {
         node1 = (*node).next;
         tree_remove( cable, node );
         node = node1;
      }

      // adjust n1 count
      (*n1).count = start_index - (*n1).index;

      // adjust n2 start, count
      length1 = (*n2).count - ( end_index - (*n2).index + 1 );
      (*n2).start = end_index - (*n2).index + 1;
      (*n2).count = length1;

      // set pointers
      (*n1).next = n2;
      (*n2).prev = n1;

      redo_indices( cable );

      // now see if n1 and/or n2 is now empty; if so, remove
      if ( ( (*cable).count > 1 ) && ( (*n1).count ==  0 ) )
      {
         if ( n1 == (*cable).first )
         {
            (*cable).first = n2;
            (*n2).prev = NULL;
            nx = n2;
         }
         else
         {
            ( *(*n1).prev ).next = (*n1).next;
            if ( (*n1).next != NULL )
            {
               ( *(*n1).next ).prev = (*n1).prev;
            }
            nx = (*n1).prev;
         }
         tree_remove( cable, n1 );
         redo_indices( cable );
         n1 = nx;
      }

      if ( ( (*cable).count > 1 ) && ( (*n2).count ==  0 ) )
      {
         if ( n2 == (*cable).first )
         {
            (*cable).first = (*n2).next;
            if ( (*n2).next != NULL )
            {
               ( *(*n2).next ).prev = NULL;
            }
         }
         else
         {
            (*n1).next = (*n2).next;
            if ( (*n2).next != NULL )
            {
               ( *(*n2).next ).prev = n1;
            }
         }
         tree_remove( cable, n2 );
         redo_indices( cable );
      }

   }

   return;
}

/**
   insert_at_index

   insert count characters at index in a cable

   @param cable the tree of nodes
   @param index where to insert new characters
   @param how many (zero-valued) characters to insert at index
*/

static
void
insert_at_index( cable_t *cable, int32_t index, int32_t count )
{
   node_t *node = NULL;
   node_t *node1 = NULL;
   node_t *nodex = NULL;
   node_t *n1 = NULL;
   node_t *n2 = NULL;
   char_t *cp = NULL;
   char_t *cp1 = NULL;
   int32_t length = 0;

   // see if we're adding at the end of the cable
   if ( index == (*cable).str_count )
   {
      // add new nodes at end of cable to hold count chars
      length = 0;

      if ( (*cable).str_count == 0 )
      {
         node1 = (*cable).first;
         nodex = node1;
      }
      else
      {
         node1 = node_for_index( cable, (*cable).str_count - 1 );
         nodex = node1;
      }

      while ( length < count )
      {
         node = node_make( cable );
         (*node).prev = node1;
         (*node1).next = node;
         (*node).index = (*cable).str_count;
         if ( ( count - length ) < (*cable).str_length )
         {
            (*node).count = count - length;
            length = count;
         }
         else
         {
            (*node).count = (*cable).str_length;
            length = length + (*cable).str_length;
         }

         redo_indices( cable );
         tree_put( cable, node );
         node1 = node;
      }

      // remove node with zero count, if any
      if ( (*nodex).count == 0 )
      {
         (*cable).first = (*nodex).next;
         ( *(*cable).first ).prev = NULL;

         // remove from tree and dispose of node
         tree_remove( cable, nodex );

      }
   }
   else
   {
      // get node for index
      n1 = node_for_index( cable, index );
      if ( n1 != NULL )
      {
         cp1 = (*n1).str;
         n2 = (*n1).next;
      }

      // see if count chars will fit in n1
      if ( ( (*n1).count + count ) <= (*cable).str_length )
      {
         // if so, move chars to start of node
         if ( (*n1).start != 0 )
         {
            memmove( (*n1).str, &(  (*n1).str[ (*n1).start ] ), (*n1).count );
            (*n1).start = 0;
         }

         // and move chars after (*n1).count
         memmove
         (
            &( (*n1).str[ index - (*n1).index + count ] ),
            &( (*n1).str[ index - (*n1).index ] ),
            (*n1).count - ( index - (*n1).index )
         );

         // adjust node count
         (*n1).count = (*n1).count + count;

         redo_indices( cable );
      }
      // add new node(s) to hold new chars
      else
      {
         // first, split n1 into two nodes at index
         node = node_make( cable );
         cp = (*node).str;

         // adjust pointers
         (*node).next = (*n1).next;
         (*node).prev = n1;
         (*n1).next = node;

         if ( (*node).next != NULL )
         {
            ( *(*node).next ).prev = node;
         }

         // move chars after index to new node
         memmove
         (
            &( cp[ 0 ] ),
            &( cp1[ (*n1).start + index - (*n1).index ] ),
            (*n1).count - ( index - (*n1).index + (*n1).start )
         );

         (*node).count = (*n1).count - ( index - (*n1).index + (*n1).start );
         (*n1).count = index - (*n1).index - (*n1).start;

         // haven't added any chars yet, now do so one node at a time
         length = 0;
         node1 = node;
         nodex = n1;

         while ( count - length > 0 )
         {
            node = node_make( cable );
            if ( ( count - length ) > (*cable).str_length )
            {
               (*node).count = (*cable).str_length;
               length = length + (*node).count;
               (*node1).prev = node;
               (*node).next = node1;
               (*node).prev = nodex;
               (*nodex).next = node;
            }
            else
            {
               (*node).count = count - length;
               length = length + (*node).count;
               (*node1).prev = node;
               (*node).next = node1;
               (*node).prev = nodex;
               (*nodex).next = node;
            }
            nodex = node;
         }

         redo_indices( cable );

         // remove nodes with zero count, if any
         node1 = (*cable).first;
         nodex = (*node1).next;

         while ( (*node1).count == 0 )
         {
            // update n1 if it has count of 0
            if ( node1 == n1 )
            {
               n1 = (*node1).next;
            }

            (*nodex).prev = NULL;
            (*cable).first = nodex;

            // remove from tree and dispose of node
            tree_remove( cable, node1 );

            node1 = (*cable).first;
            nodex = (*node1).next;
         }

         while( nodex != n2 )
         {
            if ( (*nodex).count == 0 )
            {
               // update n1 if it has count of 0
               if ( nodex == n1 )
               {
                  n1 = (*nodex).next;
               }

               // take nodex out of linked list
               (*node1).next = (*nodex).next;
               if ( (*nodex).next != NULL )
               {
                  ( *(*nodex).next ).prev = node1;
               }

               // remove from tree and dispose of node
               tree_remove( cable, nodex );

               // prepare for next iteration
               nodex = (*node1).next;
            }
            else
            {
               // prepare for next iteration
               node1 = nodex;
               nodex = (*nodex).next;
            }
         }

         // redo indices
         redo_indices( cable );

         // put new nodes into tree
         node = n1;

         while( node != n2 )
         {
            if ( tree_has( cable, node ) == 0 )
            {
               tree_put( cable, node );
            }
            node = (*node).next;
         }
      }
   }

   return;
}

/**
   substring_index_in_bounds

   checks to see if characters in other are the same as the characters in cable
   from start_index to end_index

   @param cable the cable to compare to
   @param other the cable to compare
   @param start_index where to start comparing
   @param end_index where to end comparint
   @return -1 if match not found, >= 0 otherwise
*/
static
int32_t
substring_index_in_bounds
(
   cable_t *cable,
   cable_t *other,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*cable).str_count ) ) );
   PRECONDITION( "end_index ok", ( ( end_index >= 0 ) && ( end_index < (*cable).str_count ) ) );

   int32_t result = -1;
   int32_t i = 0;
   int32_t j = 0;
   int32_t flag = 0;
   int32_t length1 = 0;
   node_t *node = NULL;
   node_t *nodex = NULL;
   node_t *node1 = NULL;
   char_t *cpx = NULL;
   char_t *cp1 = NULL;
   int32_t index = 0;
   int32_t indexx = 0;
   int32_t index1 = 0;
   int32_t count = 0;
   int32_t countx = 0;
   int32_t count1 = 0;
   char_t c = 0;
   char_t c1 = 0;

   // get lengths, min length
   length1 = (*other).str_count;

   if ( length1 > ( end_index - start_index + 1 ) )
   {
      // no chance for finding other - it's longer than segment of cable
      result = -1;
   }
   else
   {
      // compare each character looking for substring
      node = node_for_index( cable, start_index );
      index = (*node).index;
      count = (*node).count;

      result = -1;

      // see if this spot in cable is equal to other
      for ( i = start_index; i <= end_index; i++ )
      {
         // cable access starting at index i
         nodex = node;
         cpx = node_as_cstring( nodex );
         indexx = (*nodex).index;
         countx = (*nodex).count;

         // go to start of other
         flag = 1;
         node1 = (*other).first;
         cp1 = node_as_cstring( node1 );
         index1 = (*node1).index;
         count1 = (*node1).count;

         // compare other to this spot in cable
         for ( j = 0; j < length1; j++ )
         {
            // get character in cable
            c = cpx[ i - indexx + j ];

            // get character in other
            c1 = cp1[ j - index1 ];

            // if not equal, we're done for this "i"
            if ( c != c1  )
            {
               flag = 0;
               break;
            }

            // set up for next j
            if ( ( i - indexx + j ) >= ( countx - 1 ) )
            {
               nodex = (*nodex).next;
               if ( nodex != NULL )
               {
                  cpx = node_as_cstring( nodex );
                  indexx = (*nodex).index;
                  countx = (*nodex).count;
               }
            }

            if ( ( j - index1 ) >= ( count1 - 1 ) )
            {
               node1 = (*node1).next;
               if ( node1 != NULL )
               {
                  cp1 = node_as_cstring( node1 );
                  index1 = (*node1).index;
                  count1 = (*node1).count;
               }
            }

         }

         if ( flag == 1 )
         {
            // all characters matched, we're done
            result = i;
            break;
         }

         // no match, set up for comparison at next "i"
         if ( ( i - index ) >= ( count - 1 ) )
         {
            node = (*node).next;
            if ( node != NULL )
            {
               index = (*node).index;
               count = (*node).count;
            }
         }

      }
   }

   return result;
}

/**
   substring_index_in_bounds_cstring

   checks to see if characters in other are the same as the characters in cable
   from start_index to end_index

   @param cable the cable to compare to
   @param other the cstring to compare
   @param start_index where to start comparing
   @param end_index where to end comparint
   @return -1 if match not found, >= 0 otherwise
*/
static
int32_t
substring_index_in_bounds_cstring
(
   cable_t *cable,
   char_t *other,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*cable).str_count ) ) );
   PRECONDITION( "end_index ok", ( ( end_index >= 0 ) && ( end_index < (*cable).str_count ) ) );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );

   int32_t result = -1;
   int32_t i = 0;
   int32_t j = 0;
   int32_t flag = 0;
   int32_t length1 = 0;
   node_t *node = NULL;
   node_t *nodex = NULL;
   char_t *cpx = NULL;
   int32_t index = 0;
   int32_t indexx = 0;
   int32_t count = 0;
   int32_t countx = 0;
   char_t c = 0;
   char_t c1 = 0;

   // get lengths, min length
   length1 = strlen( other );

   if ( length1 > ( end_index - start_index + 1 ) )
   {
      // no chance for finding other - it's longer than segment of cable
      result = -1;
   }
   else
   {
      // compare each character looking for substring
      node = node_for_index( cable, start_index );
      index = (*node).index;
      count = (*node).count;

      result = -1;

      // see if this spot in cable is equal to other
      for ( i = start_index; i <= end_index; i++ )
      {
         // cable access starting at index i
         nodex = node;
         cpx = node_as_cstring( nodex );
         indexx = (*nodex).index;
         countx = (*nodex).count;
         flag = 1;

         // compare other to this spot in cable
         for ( j = 0; j < length1; j++ )
         {
            // get character in cable
            c = cpx[ i - indexx + j ];

            // get character in other
            c1 = other[ j ];

            // if not equal, we're done for this "i"
            if ( c != c1  )
            {
               flag = 0;
               break;
            }

            // set up for next j
            if ( ( i - indexx + j ) >= ( countx - 1 ) )
            {
               nodex = (*nodex).next;
               if ( nodex != NULL )
               {
                  cpx = node_as_cstring( nodex );
                  indexx = (*nodex).index;
                  countx = (*nodex).count;
               }

            }

         }

         if ( flag == 1 )
         {
            // all characters matched, we're done
            result = i;
            break;
         }

         // no match, set up for comparison at next "i"
         if ( ( i - index ) >= ( count - 1 ) )
         {
            node = (*node).next;
            if ( node != NULL )
            {
               index = (*node).index;
               count = (*node).count;
            }
         }

      }
   }

   return result;
}

/**
   replace_at_index

   replace contents of cable with contents of other at start_index

   @param cable the tree of nodes
   @param other the other cable
   @param start_index where to replace contents of cable with other
*/
static
void
replace_at_index
(
   cable_t *cable,
   cable_t *other,
   int32_t start_index
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*cable).str_count ) ) );
   PRECONDITION( "other count ok", ( ( start_index + (*other).str_count ) <= (*cable).str_count ) );

   int32_t i = 0;
   int32_t j = 0;
   int32_t length1 = 0;
   node_t *node = NULL;
   node_t *node1 = NULL;
   char_t *cp = NULL;
   char_t *cp1 = NULL;
   int32_t index = 0;
   int32_t index1 = 0;
   int32_t count = 0;
   int32_t count1 = 0;
   char_t c = 0;

   // get lengths, min length
   length1 = (*other).str_count;

   node = node_for_index( cable, start_index );
   cp = node_as_cstring( node );
   index = (*node).index;
   count = (*node).count;

   node1 = (*other).first;
   cp1 = node_as_cstring( node1 );
   index1 = (*node1).index;
   count1 = (*node1).count;

   // write over cable with other's contents
   for ( i = start_index, j = 0; i <= start_index + length1 - 1; i++, j++ )
   {
      // get character in other
      c = cp1[ j - index1 ];

      // put character in cable
      cp[ i - index ] = c;

      // set up for next "i"
      if ( ( i - index ) >= ( count - 1 ) )
      {
         node = (*node).next;
         if ( node != NULL )
         {
            cp = node_as_cstring( node );
            index = (*node).index;
            count = (*node).count;
         }
      }

      // set up for next "j"
      if ( ( j - index1 ) >= ( count1 - 1 ) )
      {
         node1 = (*node1).next;
         if ( node1 != NULL )
         {
            cp1 = node_as_cstring( node1 );
            index1 = (*node1).index;
            count1 = (*node1).count;
         }
      }

   }

   return;
}

/**
   replace_at_index_cstring

   replace contents of cable with contents of other at start_index

   @param cable the tree of nodes
   @param other the other cstring
   @param start_index where to replace contents of cable with other
*/
static
void
replace_at_index_cstring
(
   cable_t *cable,
   char_t *other,
   int32_t start_index
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index <= (*cable).str_count ) ) );
   PRECONDITION( "other count ok", ( ( start_index + strlen( other ) ) <= (*cable).str_count ) );

   int32_t i = 0;
   int32_t j = 0;
   int32_t length1 = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   int32_t index = 0;
   int32_t count = 0;
   char_t c = 0;

   // get lengths, min length
   length1 = strlen( other );

   node = node_for_index( cable, start_index );
   cp = node_as_cstring( node );
   index = (*node).index;
   count = (*node).count;

   // write over cable with other's contents
   for ( i = start_index, j = 0; i <= start_index + length1 - 1; i++, j++ )
   {
      // get character in other
      c = other[ j ];

      // put character in cable
      cp[ i - index ] = c;

      // set up for next "i"
      if ( ( i - index ) >= ( count - 1 ) )
      {
         node = (*node).next;
         if ( node != NULL )
         {
            cp = node_as_cstring( node );
            index = (*node).index;
            count = (*node).count;
         }
      }

   }

   return;
}

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
nonnegative_count( cable_t *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
valid_count( cable_t *p )
{
   int32_t result = 1;
   int32_t count = 0;
   node_t *node = NULL;

   result = ( tree_count( p ) == (*p).count );

   if ( result == 1 )
   {
      node = (*p).first;
      count = 1;
      node = (*node).next;

      while( node != NULL )
      {
         count = count + 1;
         node = (*node).next;
      }

      result = ( count == (*p).count );
   }


   return result;
}

static
int32_t
cursor_not_null( cable_t *p )
{
   int32_t result = 1;

   result = ( (*p).cursor != NULL );

   return result;
}

static
int32_t
in_order_recurse( node_t *node )
{
   int32_t result = 1;

   if ( (*node).left != &null_node )
   {
      result = ( ( *(*node).left ).index < (*node).index );
   }

   if ( result == 1 )
   {
      if ( (*node).right != &null_node )
      {
         result = ( (*node).index < ( *(*node).right ).index );
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
in_order( cable_t *p )
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
root_is_black( cable_t *p )
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
null_node_ok( cable_t *p )
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
int32_t
nonnegative_str_count( cable_t *p )
{
   int32_t result = 1;

   result = ( (*p).str_count >= 0 );

   return result;
}

static
int32_t
valid_str_count( cable_t *p )
{
   int32_t result = 0;
   int32_t count = 0;
   node_t *node = NULL;
   cable_cursor_t *cursor = NULL;

   node = (*p).first;

   count = 0;
   while( node != NULL )
   {
      count = count + (*node).count;
      node = (*node).next;
   }

   result = ( (*p).str_count == count );

   if ( result == 1 )
   {
      cursor = (*p).cursor;
      cursor_start( cursor );

      count = 0;
      while( cursor_off( cursor ) == 0 )
      {
         node = cursor_item( cursor );
         count = count + (*node).count;
         cursor_forth( cursor );
      }

      result = ( (*p).str_count == count );
   }

   return result;
}

static
int32_t
indices_ok( cable_t *p )
{
   int32_t result = 0;
   int32_t index = 0;
   node_t *node = NULL;
   cable_cursor_t *cursor = NULL;

   node = (*p).first;

   result = ( (*node).index == 0 );

   if ( result == 1 )
   {
      index = index + (*node).count;
      node = (*node).next;

      while( ( node != NULL ) && ( result == 1 ) )
      {
         result = ( (*node).index == index );
         index = index + (*node).count;
         node = (*node).next;
      }
   }

   if ( result == 1 )
   {
      cursor = (*p).cursor;
      cursor_start( cursor );

      index = 0;
      while( ( cursor_off( cursor ) == 0 ) && ( result == 1 ) )
      {
         node = cursor_item( cursor );
         result = ( (*node).index == index );
         index = index + (*node).count;
         cursor_forth( cursor );
      }

      result = ( (*p).str_count == index );
   }

   return result;
}

static
int32_t
sequence_ok( cable_t *p )
{
   int32_t result = 0;
   int32_t i = 0;
   node_t *node1 = NULL;
   node_t *node2 = NULL;
   cable_cursor_t *cursor = NULL;

   // get first node in linked list
   node1 = (*p).first;

   // get first node in tree
   cursor = (*p).cursor;
   cursor_start( cursor );
   node2 = cursor_item( cursor );

   // verify they're the same
   result = ( node1 == node2 );

   // loop to compare each node in both iterations
   for ( i = 1; ( i < (*p).count ) && ( result == 1 ); i++ )
   {
      node1 = (*node1).next;
      cursor_forth( cursor );
      node2 = cursor_item( cursor );

      result = ( node1 == node2 );
   }

   return result;
}

static
int32_t
links_ok( cable_t *p )
{
   int32_t result = 0;
   node_t *node = NULL;
   node_t *node1 = NULL;

   // get first node in linked list
   node = (*p).first;

   // see if prev is null
   result = ( (*node).prev == NULL );

   if ( result == 1 )
   {
      node1 = node;
      node = (*node).next;

      // loop to compare next and prev of nodes
      while( ( node != NULL ) && ( result == 1 ) )
      {
         result = ( (*node).prev == node1 );

         if ( result == 1 )
         {
            result = ( (*node1).next == node );
         }

         node1 = node;
         node = (*node).next;
      }
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
node_colors_ok( cable_t *p )
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
path_black_count_ok( cable_t *p )
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
void invariant( cable_t *p )
{
   assert( ( ( void ) "nonnegative count", nonnegative_count( p ) ) );
   assert( ( ( void ) "valid count", valid_count( p ) ) );
   assert( ( ( void ) "cursor not null", cursor_not_null( p ) ) );
   assert( ( ( void ) "cable in order", in_order( p ) ) );
   assert( ( ( void ) "root is black", root_is_black( p ) ) );
   assert( ( ( void ) "null node ok", null_node_ok( p ) ) );
   assert( ( ( void ) "nonnegative string count", nonnegative_str_count( p ) ) );
   assert( ( ( void ) "valid string count", valid_str_count( p ) ) );
   assert( ( ( void ) "indices ok", indices_ok( p ) ) );
   assert( ( ( void ) "sequence ok", sequence_ok( p ) ) );
   assert( ( ( void ) "links ok", links_ok( p ) ) );
   assert( ( ( void ) "node colors ok", node_colors_ok( p ) ) );
   assert( ( ( void ) "path black count ok", path_black_count_ok( p ) ) );
   return;
}

#endif

/**
   init_null_node
*/

static
void
init_null_node( void )
{

   // set null node - self referencing
   if ( null_node_initialized == 0 )
   {
      null_node.left = &null_node;
      null_node.right = &null_node;
      null_node.parent = &null_node;
      null_node.color = black;
      null_node_initialized = 1;
   }

   return;
}

/**
   cable_make
*/

cable_t *
cable_make( void )
{
   // allocate cable struct
   cable_t * result = ( cable_t * ) calloc( 1, sizeof( cable_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set null node - self referencing
   init_null_node();

   // set type
   (*result)._type = CABLE_TYPE;

   // set string length
   (*result).str_length = DEFAULT_STRING_LENGTH;

   // set pseudo root node
   (*result).root.left = &null_node;
   (*result).root.right = &null_node;
   (*result).root.parent = &null_node;
   (*result).root.color = black;

   // count is zero
   (*result).count = 0;
   (*result).str_count = 0;

   // set built-in cursor
   // allocate cursor struct
   cable_cursor_t *cursor
      =  ( cable_cursor_t * )
         calloc( 1, sizeof( cable_cursor_t ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set cable
   (*cursor).cable = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = &null_node;

   // set cable built-in cursor
   (*result).cursor = cursor;

   // make first node, empty
   node_t *node = node_make( result );
   tree_put( result, node );
   (*result).first = node;

   // init mutex
   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   cable_make_capacity
*/

cable_t *
cable_make_capacity( int32_t capacity )
{
   // allocate cable struct
   cable_t * result = ( cable_t * ) calloc( 1, sizeof( cable_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set null node - self referencing
   init_null_node();

   // set type
   (*result)._type = CABLE_TYPE;

   // set string length
   (*result).str_length = capacity;

   // set pseudo root node
   (*result).root.left = &null_node;
   (*result).root.right = &null_node;
   (*result).root.parent = &null_node;
   (*result).root.color = black;

   // count is zero
   (*result).count = 0;
   (*result).str_count = 0;

   // set built-in cursor
   // allocate cursor struct
   cable_cursor_t *cursor
      =  ( cable_cursor_t * )
         calloc( 1, sizeof( cable_cursor_t ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set cable
   (*cursor).cable = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = &null_node;

   // set cable built-in cursor
   (*result).cursor = cursor;

   // make first node, empty
   node_t *node = node_make( result );
   tree_put( result, node );
   (*result).first = node;

   // init mutex
   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   cable_make_from
*/

cable_t *
cable_make_from( cable_t *cable )
{
   PRECONDITION( "cable not null", cable != NULL );

   node_t *node = NULL;
   node_t *n = NULL;
   node_t *n1 = NULL;
   int32_t flag = 0;

   // make cable struct
   cable_t *result = cable_make_capacity( (*cable).str_length );

   // remove the empty node in result
   tree_remove( result, (*result).root.left );

   // walk through nodes in cable, duplicate them, copy string, insert
   node = (*cable).first;
   flag = 1;
   n1 = NULL;

   while( node != NULL )
   {
      n = node_make_from( result, node );
      (*n).prev = n1;
      (*n).next = NULL;
      if ( n1 != NULL )
      {
         (*n1).next = n;
      }

      // take care of first node
      if ( flag == 1 )
      {
         (*result).first = n;
         flag = 0;
      }

      // adjust indices and counts
      redo_indices( result );
      tree_put( result, n );

      // prepare for next iteration
      n1 = n;
      node = (*node).next;
   }

   INVARIANT( result );

   return result;
}

/**
   cable_make_from_cstring
*/

cable_t *
cable_make_from_cstring( char_t *str )
{
   PRECONDITION( "str not null", str != NULL );

   int32_t i = 0;
   int32_t j = 0;
   int32_t n = 0;
   int32_t count = 0;
   node_t *node = NULL;
   node_t *n1 = NULL;
   char_t *s = NULL;

   // make cable struct
   cable_t *result = cable_make();

   // set type
   (*result)._type = CABLE_TYPE;

   // copy string into result
   n = strlen( str );

   for( i = 0; i < n; i = i + (*result).str_length )
   {
      if ( i == 0 )
      {
         node = (*result).first;
         s = (*node).str;
         for( j = 0; ( ( j < n ) && ( j < (*result).str_length ) ); j++ )
         {
            s[j] = str[j];
         }
         (*node).start = 0;
         (*node).count = j;
         n1 = node;

         // adjust indices
         redo_indices( result );
      }
      else
      {
         node = node_make( result );
         s = (*node).str;
         for( j = 0; ( ( j < ( n - i ) ) && ( j < (*result).str_length ) ); j++ )
         {
            s[j] = str[i + j];
         }
         (*node).index = i;
         (*node).start = 0;
         (*node).count = j;

         // adjust pointers
         (*n1).next = node;
         (*node).prev = n1;

         // prepare for next iteration
         n1 = node;

         // adjust indices and put node into tree
         redo_indices( result );
         tree_put( result, node );
      }
      count = count + j;
   }

   INVARIANT( result );

   return result;
}

/**
   cable_make_capacity_from_cstring
*/

cable_t *
cable_make_capacity_from_cstring( char_t *str, int32_t capacity )
{
   PRECONDITION( "str not null", str != NULL );

   int32_t i = 0;
   int32_t j = 0;
   int32_t n = 0;
   int32_t count = 0;
   node_t *node = NULL;
   node_t *n1 = NULL;
   char_t *s = NULL;

   // make cable struct
   cable_t *result = cable_make_capacity( capacity );

   // set type
   (*result)._type = CABLE_TYPE;

   // copy string into result
   n = strlen( str );

   for( i = 0; i < n; i = i + (*result).str_length )
   {
      if ( i == 0 )
      {
         node = (*result).first;
         s = (*node).str;
         for( j = 0; ( ( j < n ) && ( j < (*result).str_length ) ); j++ )
         {
            s[j] = str[j];
         }
         (*node).start = 0;
         (*node).count = j;
         n1 = node;

         // adjust indices
         redo_indices( result );
      }
      else
      {
         node = node_make( result );
         s = (*node).str;
         for( j = 0; ( ( j < ( n - i ) ) && ( j < (*result).str_length ) ); j++ )
         {
            s[j] = str[i + j];
         }
         (*node).index = i;
         (*node).start = 0;
         (*node).count = j;

         // adjust pointers
         (*n1).next = node;
         (*node).prev = n1;

         // prepare for next iteration
         n1 = node;

         // adjust indices and put node into tree
         redo_indices( result );
         tree_put( result, node );
      }
      count = count + j;
   }

   INVARIANT( result );

   return result;
}

/**
   cable_dispose
*/

void
cable_dispose( cable_t **cable )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable not null", *cable != NULL );
   PRECONDITION( "cable type OK", (**cable)._type == CABLE_TYPE );
   LOCK( (**cable).mutex );
   INVARIANT(*cable);

   node_t *node = NULL;
   node_t *n = NULL;

   // delete nodes
   node = (**cable).first;
   while ( node != NULL )
   {
      n = (*node).next;
      tree_remove( *cable, node );
      node = n;
   }

   // delete cursor
   free( (**cable).cursor );

   // dispose of mutex
   MULTITHREAD_MUTEX_DESTROY( (**cable).mutex );

   // delete cable struct
   free(*cable);

   // set to NULL
   *cable = NULL;

   return;
}

/**
   cable_item
*/

char_t
cable_item( cable_t *cable, int32_t index )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*cable).str_count ) ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   node_t *node = node_for_index( cable, index );

   char_t result = (*node).str[ index - (*node).index + (*node).start ];

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_as_cstring
*/

char_t *
cable_as_cstring( cable_t *cable )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   char_t *result = NULL;
   char_t *cp = NULL;
   node_t *node;

   // allocate result
   result = ( char_t * ) calloc( (*cable).str_count + 1, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // walk through nodes, appending contents onto result
   node = (*cable).first;

   while( node != NULL )
   {
      cp = node_as_cstring( node );
      strcat( result, cp );
      node = (*node).next;
   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_count
*/

int32_t
cable_count( cable_t *cable )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t result = (*cable).str_count;

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_capacity
*/

int32_t
cable_capacity( cable_t *cable )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t result = (*cable).str_length;

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_is_empty
*/

int32_t
cable_is_empty( cable_t *cable )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t result = ( (*cable).str_count ==  0 );

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_valid_index
*/

int32_t
cable_valid_index( cable_t *cable, int32_t index )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t result = ( index >= 0 ) && ( index < (*cable).str_count );

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_has
*/
int32_t
cable_has( cable_t *cable, char_t c )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t result = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   char_t *cp1 = NULL;

   // walk through nodes, looking for 'c'
   node = (*cable).first;

   while( node != NULL )
   {
      // get string in node
      cp = node_as_cstring( node );

      // check for character present
      cp1 = strchr( cp, c );

      // get next node
      node = (*node).next;

      // check for presence of character; if so, exit
      if ( cp1 != NULL )
      {
         result = 1;
         break;
      }

   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_hash_code
*/
int32_t
cable_hash_code( cable_t *cable )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   uint32_t result = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   int32_t i = 0;

   // walk through nodes, compute hash code
   node = (*cable).first;

   while( node != NULL )
   {
      // get string in node
      cp = node_as_cstring( node );

      // compute hash
      for ( i = 0; i < (*node).count; i++ )
      {
         result = ( ( result % HASH_PRIME_NUMBER ) << 8 ) + ( uint32_t ) cp[i];
      }

      // get next node
      node = (*node).next;

   }


   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return ( int32_t ) result;
}

/**
   cable_is_equal
*/
int32_t
cable_is_equal( cable_t *cable, cable_t *other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   LOCK( (*other).mutex );
   INVARIANT( cable );

   int32_t result = 0;
   int32_t i = 0;
   int32_t length = 0;
   node_t *node = NULL;
   node_t *node1 = NULL;
   char_t *cp = NULL;
   char_t *cp1 = NULL;
   int32_t index = 0;
   int32_t index1 = 0;
   int32_t count = 0;
   int32_t count1 = 0;
   char_t c = 0;
   char_t c1 = 0;

   // walk through nodes, comparing characters
   if ( (*cable).str_count != (*other).str_count )
   {
      // if have different lengths, are not equal
      result = 0;
   }
   else
   {
      length = (*cable).str_count;

      // cables are same length, compare each character
      node = (*cable).first;
      cp = node_as_cstring( node );
      index = (*node).index;
      count = (*node).count;

      node1 = (*other).first;
      cp1 = node_as_cstring( node1 );
      index1 = (*node1).index;
      count1 = (*node1).count;

      result = 1;

      for ( i = 0; i < length; i++ )
      {
         // get character in cable
         c = cp[ i - index ];

         // get character in other
         c1 = cp1[ i - index1 ];

         // if not equal, we're done
         if ( c != c1  )
         {
            result = 0;
            break;
         }

         // set up for next comparison
         if ( ( i - index ) >= ( count - 1 ) )
         {
            node = (*node).next;
            if ( node != NULL )
            {
               cp = node_as_cstring( node );
               index = (*node).index;
               count = (*node).count;
            }
         }

         if ( ( i - index1 ) >= ( count1 - 1 ) )
         {
            node1 = (*node1).next;
            if ( node1 != NULL )
            {
               cp1 = node_as_cstring( node1 );
               index1 = (*node1).index;
               count1 = (*node1).count;
            }
         }

      }
   }

   INVARIANT( cable );
   UNLOCK( (*other).mutex );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_is_equal_cstring
*/
int32_t
cable_is_equal_cstring( cable_t *cable, char_t *other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t result = 0;
   int32_t i = 0;
   int32_t length = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   int32_t index = 0;
   int32_t count = 0;
   char_t c = 0;
   char_t c1 = 0;

   length = strlen( other );

   // walk through nodes, comparing characters
   if ( (*cable).str_count != length )
   {
      // if have different lengths, are not equal
      result = 0;
   }
   else
   {
      // cables are same length, compare each character
      node = (*cable).first;
      cp = node_as_cstring( node );
      index = (*node).index;
      count = (*node).count;

      result = 1;

      for ( i = 0; i < length; i++ )
      {
         // get character in cable
         c = cp[ i - index ];

         // get character in other
         c1 = other[ i ];

         // if not equal, we're done
         if ( c != c1  )
         {
            result = 0;
            break;
         }

         // set up for next comparison
         if ( ( i - index ) >= ( count - 1 ) )
         {
            node = (*node).next;
            if ( node != NULL )
            {
               cp = node_as_cstring( node );
               index = (*node).index;
               count = (*node).count;
            }
         }
      }
   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_is_less_than
*/
int32_t
cable_is_less_than( cable_t *cable, cable_t *other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   LOCK( (*other).mutex );
   INVARIANT( cable );

   int32_t result = 0;
   int32_t i = 0;
   int32_t n = 0;
   int32_t length = 0;
   int32_t length1 = 0;
   node_t *node = NULL;
   node_t *node1 = NULL;
   char_t *cp = NULL;
   char_t *cp1 = NULL;
   int32_t index = 0;
   int32_t index1 = 0;
   int32_t count = 0;
   int32_t count1 = 0;
   char_t c = 0;
   char_t c1 = 0;

   // get lengths, min length
   length = (*cable).str_count;
   length1 = (*other).str_count;
   n = length;
   if ( length1 < n )
   {
      n = length1;
   }

   // cables are same length, compare each character
   node = (*cable).first;
   cp = node_as_cstring( node );
   index = (*node).index;
   count = (*node).count;

   node1 = (*other).first;
   cp1 = node_as_cstring( node1 );
   index1 = (*node1).index;
   count1 = (*node1).count;

   result = 0;

   for ( i = 0; i < n; i++ )
   {
      // get character in cable
      c = cp[ i - index ];

      // get character in other
      c1 = cp1[ i - index1 ];

      // if greater than, we're done
      if ( c > c1  )
      {
         result = 0;
         break;
      }

      // if less than, we're done
      if ( c < c1  )
      {
         result = 1;
         break;
      }

      // otherwise they're equal, set up for next comparison
      if ( ( i - index ) >= ( count - 1 ) )
      {
         node = (*node).next;
         if ( node != NULL )
         {
            cp = node_as_cstring( node );
            index = (*node).index;
            count = (*node).count;
         }
      }

      if ( ( i - index1 ) >= ( count1 - 1 ) )
      {
         node1 = (*node1).next;
         if ( node1 != NULL )
         {
            cp1 = node_as_cstring( node1 );
            index1 = (*node1).index;
            count1 = (*node1).count;
         }
      }

   }

   // if we get to here, then all compared characters are equal, see if cable is
   // shorter than other
   if ( length < length1 )
   {
      result = 1;
   }

   // otherwise result is false (0), equal or greater than

   INVARIANT( cable );
   UNLOCK( (*other).mutex );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_is_less_than_cstring
*/
int32_t
cable_is_less_than_cstring( cable_t *cable, char_t *other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t result = 0;
   int32_t i = 0;
   int32_t n = 0;
   int32_t length = 0;
   int32_t length1 = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   int32_t index = 0;
   int32_t count = 0;
   char_t c = 0;
   char_t c1 = 0;

   // get lengths, min length
   length = (*cable).str_count;
   length1 = strlen( other );
   n = length;
   if ( length1 < n )
   {
      n = length1;
   }

   // cables are same length, compare each character
   node = (*cable).first;
   cp = node_as_cstring( node );
   index = (*node).index;
   count = (*node).count;

   result = 0;

   for ( i = 0; i < n; i++ )
   {
      // get character in cable
      c = cp[ i - index ];

      // get character in other
      c1 = other[ i ];

      // if greater than, we're done
      if ( c > c1  )
      {
         result = 0;
         break;
      }

      // if less than, we're done
      if ( c < c1  )
      {
         result = 1;
         break;
      }

      // otherwise they're equal, set up for next comparison
      if ( ( i - index ) >= ( count - 1 ) )
      {
         node = (*node).next;
         if ( node != NULL )
         {
            cp = node_as_cstring( node );
            index = (*node).index;
            count = (*node).count;
         }
      }

   }

   // if we get to here, then all compared characters are equal, see if cable is
   // shorter than other
   if ( length < length1 )
   {
      result = 1;
   }

   // otherwise result is false (0), equal or greater than

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_is_greater_than
*/
int32_t
cable_is_greater_than( cable_t *cable, cable_t *other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   LOCK( (*other).mutex );
   INVARIANT( cable );

   int32_t result = 0;
   int32_t i = 0;
   int32_t n = 0;
   int32_t length = 0;
   int32_t length1 = 0;
   node_t *node = NULL;
   node_t *node1 = NULL;
   char_t *cp = NULL;
   char_t *cp1 = NULL;
   int32_t index = 0;
   int32_t index1 = 0;
   int32_t count = 0;
   int32_t count1 = 0;
   char_t c = 0;
   char_t c1 = 0;

   // get lengths, min length
   length = (*cable).str_count;
   length1 = (*other).str_count;
   n = length;
   if ( length1 < n )
   {
      n = length1;
   }

   // cables are same length, compare each character
   node = (*cable).first;
   cp = node_as_cstring( node );
   index = (*node).index;
   count = (*node).count;

   node1 = (*other).first;
   cp1 = node_as_cstring( node1 );
   index1 = (*node1).index;
   count1 = (*node1).count;

   result = 0;

   for ( i = 0; i < n; i++ )
   {
      // get character in cable
      c = cp[ i - index ];

      // get character in other
      c1 = cp1[ i - index1 ];

      // if less than, we're done
      if ( c < c1  )
      {
         result = 0;
         break;
      }

      // if greater than, we're done
      if ( c > c1  )
      {
         result = 1;
         break;
      }

      // otherwise they're equal, set up for next comparison
      if ( ( i - index ) >= ( count - 1 ) )
      {
         node = (*node).next;
         if ( node != NULL )
         {
            cp = node_as_cstring( node );
            index = (*node).index;
            count = (*node).count;
         }
      }

      if ( ( i - index1 ) >= ( count1 - 1 ) )
      {
         node1 = (*node1).next;
         if ( node1 != NULL )
         {
            cp1 = node_as_cstring( node1 );
            index1 = (*node1).index;
            count1 = (*node1).count;
         }
      }

   }

   // if we get to here, then all compared characters are equal, see if other is
   // longer than cable
   if ( length > length1 )
   {
      result = 1;
   }

   // otherwise result is false (0), equal or less than

   INVARIANT( cable );
   UNLOCK( (*other).mutex );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_is_greater_than_cstring
*/
int32_t
cable_is_greater_than_cstring( cable_t *cable, char_t *other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t result = 0;
   int32_t i = 0;
   int32_t n = 0;
   int32_t length = 0;
   int32_t length1 = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   int32_t index = 0;
   int32_t count = 0;
   char_t c = 0;
   char_t c1 = 0;

   // get lengths, min length
   length = (*cable).str_count;
   length1 = strlen( other );
   n = length;
   if ( length1 < n )
   {
      n = length1;
   }

   // cables are same length, compare each character
   node = (*cable).first;
   cp = node_as_cstring( node );
   index = (*node).index;
   count = (*node).count;

   result = 0;

   for ( i = 0; i < n; i++ )
   {
      // get character in cable
      c = cp[ i - index ];

      // get character in other
      c1 = other[ i ];

      // if less than, we're done
      if ( c < c1  )
      {
         result = 0;
         break;
      }

      // if greater than, we're done
      if ( c > c1  )
      {
         result = 1;
         break;
      }

      // otherwise they're equal, set up for next comparison
      if ( ( i - index ) >= ( count - 1 ) )
      {
         node = (*node).next;
         if ( node != NULL )
         {
            cp = node_as_cstring( node );
            index = (*node).index;
            count = (*node).count;
         }
      }

   }

   // if we get to here, then all compared characters are equal, see if other is
   // longer than cable
   if ( length > length1 )
   {
      result = 1;
   }

   // otherwise result is false (0), equal or less than

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_has_substring
*/
int32_t
cable_has_substring( cable_t *cable, cable_t *other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   LOCK( (*other).mutex );
   INVARIANT( cable );

   int32_t result = 0;

   result = substring_index_in_bounds( cable, other, 0, (*cable).str_count - 1 );

   if ( result >= 0 )
   {
      result = 1;
   }
   else
   {
      result = 0;
   }

   INVARIANT( cable );
   UNLOCK( (*other).mutex );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_has_substring_cstring
*/
int32_t
cable_has_substring_cstring( cable_t *cable, char_t *other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t result = 0;

   result = substring_index_in_bounds_cstring( cable, other, 0, (*cable).str_count - 1 );

   if ( result >= 0 )
   {
      result = 1;
   }
   else
   {
      result = 0;
   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_starts_with
*/
int32_t
cable_starts_with( cable_t *cable, cable_t *other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   LOCK( (*other).mutex );
   INVARIANT( cable );

   int32_t result = 0;

   result = substring_index_in_bounds( cable, other, 0, (*other).str_count - 1 );

   if ( result >= 0 )
   {
      result = 1;
   }
   else
   {
      result = 0;
   }

   INVARIANT( cable );
   UNLOCK( (*other).mutex );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_starts_with_cstring
*/
int32_t
cable_starts_with_cstring( cable_t *cable, char_t *other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t result = 0;

   result = substring_index_in_bounds_cstring( cable, other, 0, strlen( other ) - 1 );

   if ( result >= 0 )
   {
      result = 1;
   }
   else
   {
      result = 0;
   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_ends_with
*/
int32_t
cable_ends_with( cable_t *cable, cable_t *other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   LOCK( (*other).mutex );
   INVARIANT( cable );

   int32_t result = 0;

   result = substring_index_in_bounds( cable, other, (*cable).str_count - (*other).str_count, (*cable).str_count - 1 );

   if ( result >= 0 )
   {
      result = 1;
   }
   else
   {
      result = 0;
   }

   INVARIANT( cable );
   UNLOCK( (*other).mutex );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_ends_with_cstring
*/
int32_t
cable_ends_with_cstring( cable_t *cable, char_t *other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t result = 0;

   result
      =  substring_index_in_bounds_cstring
         (
            cable,
            other,
            (*cable).str_count - strlen( other ),
            (*cable).str_count - 1
         );

   if ( result >= 0 )
   {
      result = 1;
   }
   else
   {
      result = 0;
   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_substring_index
*/
int32_t
cable_substring_index
(
   cable_t *cable,
   cable_t *other
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   LOCK( (*other).mutex );
   INVARIANT( cable );

   int32_t result = 0;

   result = substring_index_in_bounds( cable, other, 0, (*cable).str_count - 1 );

   INVARIANT( cable );
   UNLOCK( (*other).mutex );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_substring_index_cstring
*/
int32_t
cable_substring_index_cstring
(
   cable_t *cable,
   char_t *other
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t result = 0;

   result = substring_index_in_bounds_cstring( cable, other, 0, (*cable).str_count - 1 );

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_substring_index_in_bounds
*/
int32_t
cable_substring_index_in_bounds
(
   cable_t *cable,
   cable_t *other,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*cable).str_count ) ) );
   PRECONDITION( "end_index ok", ( ( end_index >= 0 ) && ( end_index < (*cable).str_count ) ) );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*cable).mutex );
   LOCK( (*other).mutex );
   INVARIANT( cable );

   int32_t result = 0;

   result = substring_index_in_bounds( cable, other, start_index, end_index );

   INVARIANT( cable );
   UNLOCK( (*other).mutex );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_substring_index_in_bounds_cstring
*/
int32_t
cable_substring_index_in_bounds_cstring
(
   cable_t *cable,
   char_t *other,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*cable).str_count ) ) );
   PRECONDITION( "end_index ok", ( ( end_index >= 0 ) && ( end_index < (*cable).str_count ) ) );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t result = 0;

   result = substring_index_in_bounds_cstring( cable, other, start_index, end_index );

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

#define DEFAULT_SPLIT_RETURN_ARRAY_SIZE 8

/**
   cable_split
*/
cable_t **
cable_split( cable_t *cable, char_t *separators, int32_t *result_count )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "separators not null", separators != NULL );
   PRECONDITION( "result_count not null", result_count != NULL );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   cable_t **result = NULL;
   cable_t *x = NULL;
   int32_t i = 0;
   int32_t j = 0;
   int32_t length = 0;
   int32_t length1 = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   int32_t index = 0;
   int32_t count = 0;
   char_t c = 0;
   int32_t start_index = 0;
   int32_t end_index = 0;
   int32_t flag = 0;
   int32_t size = DEFAULT_SPLIT_RETURN_ARRAY_SIZE;
   int32_t i_result = 0;

   // prepare result array
   result = ( cable_t ** ) calloc( size, sizeof( cable_t * ) );
   CHECK( "result allocated correctly", result != NULL );

   ( *result_count ) = 0;

   length = (*cable).str_count;
   length1 = strlen( separators );

   node = (*cable).first;
   cp = node_as_cstring( node );
   index = (*node).index;
   count = (*node).count;
   start_index = 0;

   // walk through cable to find separator characters
   for ( i = 0; i < length; i++ )
   {
      // get character in cable
      c = cp[ i - index ];

      // check for separator character
      flag = 0;
      for ( j = 0; j < length1; j++ )
      {
         if ( c == separators[j]  )
         {
            end_index = i - 1;
            flag = 1;
            break;
         }
      }

      // found a separator - make a new cable and put into result array
      if ( flag == 1 )
      {
         // get new cable from bounds
         x = subcable_from_bounds( cable, start_index, end_index );

         // put the new cable into the return array
         if ( i_result < ( size - 1 ) )
         {
            result[i_result] = x;
            i_result = i_result + 1;
         }
         // resize the result array if necessary
         else
         {
            result = ( cable_t ** ) realloc( result, 2 * size * sizeof( cable_t * ) );
            CHECK( "result allocated correctly", result != NULL );

            memset( &result[size], 0, size * sizeof( char_t * ) );
            size = 2 * size;
            result[i_result] = x;
            i_result = i_result + 1;
         }

         // update index
         start_index = end_index + 2;
      }

      // set up for next comparison
      if ( ( i - index ) >= ( count - 1 ) )
      {
         node = (*node).next;
         if ( node != NULL )
         {
            cp = node_as_cstring( node );
            index = (*node).index;
            count = (*node).count;
         }
      }

   }

   // make subcable from last separator to end of cable
   if ( i != ( end_index + 1 ) )
   {
      x = subcable_from_bounds( cable, start_index, length - 1 );
      // put the cable into the return array
      if ( i_result < ( size - 1 ) )
      {
         result[i_result] = x;
         i_result = i_result + 1;
      }
      // resize the result array if necessary
      else
      {
         result = ( cable_t ** ) realloc( result, 2 * size * sizeof( cable_t * ) );
         CHECK( "result allocated correctly", result != NULL );

         memset( &result[size], 0, size * sizeof( char_t * ) );
         size = 2 * size;
         result[i_result] = x;
         i_result = i_result + 1;
      }
   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   // set count of result array and return array
   ( *result_count ) = i_result;

   return result;
}

/**
   cable_as_lower
*/
cable_t *
cable_as_lower
(
   cable_t *cable,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*cable).str_count ) ) );
   PRECONDITION( "end_index ok", ( ( end_index >= 0 ) && ( end_index < (*cable).str_count ) ) );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   cable_t *result = NULL;
   int32_t i = 0;
   int32_t length = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   int32_t index = 0;
   int32_t count = 0;
   char_t c = 0;

   result = subcable_from_bounds( cable, start_index, end_index );

   // get lengths, min length
   length = (*result).str_count;

   // get lower case for each character, replace it
   node = node_for_index( result, 0 );
   cp = node_as_cstring( node );
   index = (*node).index;
   count = (*node).count;

   // see if this spot in cable is equal to other
   for ( i = 0; i <= length; i++ )
   {
      // get character in cable
      c = cp[ i - index ];
      c = ( char_t ) tolower( c );
      cp[ i - index ] = c;

      // set up for next "i"
      if ( ( i - index ) >= count - 1 )
      {
         if ( node != NULL )
         {
            node = (*node).next;
            if ( node != NULL )
            {
               cp = node_as_cstring( node );
               index = (*node).index;
               count = (*node).count;
            }
         }
      }

   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_as_upper
*/
cable_t *
cable_as_upper
(
   cable_t *cable,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*cable).str_count ) ) );
   PRECONDITION( "end_index ok", ( ( end_index >= 0 ) && ( end_index < (*cable).str_count ) ) );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   cable_t *result = NULL;
   int32_t i = 0;
   int32_t length = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   int32_t index = 0;
   int32_t count = 0;
   char_t c = 0;

   result = subcable_from_bounds( cable, start_index, end_index );

   // get lengths, min length
   length = (*result).str_count;

   // get upper case for each character, replace it
   node = node_for_index( result, 0 );
   cp = node_as_cstring( node );
   index = (*node).index;
   count = (*node).count;

   // see if this spot in cable is equal to other
   for ( i = 0; i <= length; i++ )
   {
      // get character in cable
      c = cp[ i - index ];
      c = ( char_t ) toupper( c );
      cp[ i - index ] = c;

      // set up for next "i"
      if ( ( i - index ) >= count )
      {
         node = (*node).next;
         if ( node != NULL )
         {
            cp = node_as_cstring( node );
            index = (*node).index;
            count = (*node).count;
         }
      }

   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_put
*/

void
cable_put( cable_t *cable, char_t c, int32_t index )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*cable).str_count ) ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   node_t *node = node_for_index( cable, index );

   (*node).str[ index - (*node).index + (*node).start ] = c;

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_replace
*/

void
cable_replace
(
   cable_t *cable,
   cable_t *other,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other type OK", (*other)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*cable).str_count ) ) );
   PRECONDITION( "end_index ok", ( ( end_index >= 0 ) && ( end_index < (*cable).str_count ) ) );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*cable).mutex );
   LOCK( (*other).mutex );
   INVARIANT( cable );

   int32_t length = 0;
   int32_t delta = 0;

   // get length of area to replace
   length = end_index - start_index + 1;

   // get difference between length and size of other
   delta = length - (*other).str_count;

   if ( delta == 0 )
   {
      // cables are same length
      // copy over existing chars in cable with chars from other
      replace_at_index( cable, other, start_index );
   }
   else if ( delta < 0 )
   {
      // other is longer than end_index - start_index
      // insert space in cable
      insert_at_index( cable, start_index, -delta );

      // copy over existing chars in cable with chars from other
      replace_at_index( cable, other, start_index );
   }
   else // delta > 0
   {
      // other is shorter than end_index - start_index
      // remove space in cable
      remove_from_bounds( cable, start_index, start_index + delta - 1 );

      // copy over existing chars in cable with chars from other
      replace_at_index( cable, other, start_index );
   }

   INVARIANT( cable );
   UNLOCK( (*other).mutex );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_replace_cstring
*/

void
cable_replace_cstring
(
   cable_t *cable,
   char_t *other,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*cable).str_count ) ) );
   PRECONDITION( "end_index ok", ( ( end_index >= 0 ) && ( end_index < (*cable).str_count ) ) );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t length = 0;
   int32_t delta = 0;

   // get length of area to replace
   length = end_index - start_index + 1;

   // get difference between length and size of other
   delta = length - strlen( other );

   if ( delta == 0 )
   {
      // cables are same length
      // copy over existing chars in cable with chars from other
      replace_at_index_cstring( cable, other, start_index );
   }
   else if ( delta < 0 )
   {
      // other is longer than end_index - start_index
      // insert space in cable
      insert_at_index( cable, start_index, -delta );

      // copy over existing chars in cable with chars from other
      replace_at_index_cstring( cable, other, start_index );
   }
   else // delta > 0
   {
      // other is shorter than end_index - start_index
      // remove space in cable
      remove_from_bounds( cable, start_index, start_index + delta - 1 );

      // copy over existing chars in cable with chars from other
      replace_at_index_cstring( cable, other, start_index );
   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_replace_all
*/

void
cable_replace_all
(
   cable_t *cable,
   cable_t *substring_original,
   cable_t *substring_new
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "substring_original not null", substring_original != NULL );
   PRECONDITION( "substring_original type OK", ( *substring_original )._type == CABLE_TYPE );
   PRECONDITION( "substring_new not null", substring_new != NULL );
   PRECONDITION( "substring_new type OK", ( *substring_new )._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   LOCK( ( *substring_original ).mutex );
   LOCK( ( *substring_new ).mutex );
   INVARIANT( cable );

   int32_t i = 0;
   int32_t start_index = 0;
   int32_t end_index = 0;
   int32_t length = 0;
   int32_t delta = 0;

   // work our way through cable finding instances of substring_original and
   // replacing them with substring_new

   while ( ( i >= 0 ) && ( i < (*cable).str_count ) )
   {
      i = substring_index_in_bounds( cable, substring_original, i, (*cable).str_count - 1 );

      // see if we found substring_original
      if ( i >= 0 )
      {
         // we found it, replace it with substring_new
         start_index = i;
         end_index = i + ( *substring_original ).str_count - 1;

         // get length of area to replace
         length = end_index - start_index + 1;

         // get difference between length and size of substring_new
         delta = length - ( *substring_new ).str_count;

         if ( delta == 0 )
         {
            // cables are same length
            // copy over existing chars in cable with chars from substring_new
            replace_at_index( cable, substring_new, start_index );
         }
         else if ( delta < 0 )
         {
            // substring_new is longer than end_index - start_index
            // insert space in cable
            insert_at_index( cable, start_index, -delta );

            // copy over existing chars in cable with chars from other
            replace_at_index( cable, substring_new, start_index );
         }
         else // delta > 0
         {
            // other is shorter than end_index - start_index
            // remove space in cable
            remove_from_bounds( cable, start_index, start_index + delta - 1 );

            // copy over existing chars in cable with chars from other
            replace_at_index( cable, substring_new, start_index );
         }

         // update i
         i = start_index + ( *substring_new ).str_count;
      }

   }

   INVARIANT( cable );
   UNLOCK( ( *substring_new ).mutex );
   UNLOCK( ( *substring_original ).mutex );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_replace_all
*/

void
cable_replace_all_cstring
(
   cable_t *cable,
   char_t *substring_original,
   char_t *substring_new
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "substring_original not null", substring_original != NULL );
   PRECONDITION( "substring_new not null", substring_new != NULL );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t i = 0;
   int32_t start_index = 0;
   int32_t end_index = 0;
   int32_t length = 0;
   int32_t delta = 0;

   // work our way through cable finding instances of substring_original and
   // replacing them with substring_new

   while ( ( i >= 0 ) && ( i < (*cable).str_count ) )
   {
      i = substring_index_in_bounds_cstring( cable, substring_original, i, (*cable).str_count - 1 );

      // see if we found substring_original
      if ( i >= 0 )
      {
         // we found it, replace it with substring_new
         start_index = i;
         end_index = i + strlen( substring_original ) - 1;

         // get length of area to replace
         length = end_index - start_index + 1;

         // get difference between length and size of substring_new
         delta = length - strlen( substring_new );

         if ( delta == 0 )
         {
            // cables are same length
            // copy over existing chars in cable with chars from substring_new
            replace_at_index_cstring( cable, substring_new, start_index );
         }
         else if ( delta < 0 )
         {
            // substring_new is longer than end_index - start_index
            // insert space in cable
            insert_at_index( cable, start_index, -delta );

            // copy over existing chars in cable with chars from other
            replace_at_index_cstring( cable, substring_new, start_index );
         }
         else // delta > 0
         {
            // other is shorter than end_index - start_index
            // remove space in cable
            remove_from_bounds( cable, start_index, start_index + delta - 1 );

            // copy over existing chars in cable with chars from other
            replace_at_index_cstring( cable, substring_new, start_index );
         }

         // update i
         i = start_index + strlen( substring_new );
      }

   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_append
*/

void
cable_append( cable_t *cable, cable_t *other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_TYPE );
   PRECONDITION( "cable and other same node string length", (*cable).str_length == (*other).str_length );
   LOCK( (*cable).mutex );
   LOCK( (*other).mutex );
   INVARIANT( cable );

   node_t *node = NULL;
   node_t *n = NULL;
   cable_cursor_t *cursor = NULL;
   node_t *last = NULL;

   // make copy of nodes in other, append to cable
   cursor = (*cable).cursor;
   n = (*other).first;

   while( n != NULL )
   {
      // make new node
      node = node_make_from( cable, n );

      // get next node in other
      n = (*n).next;

      // set index, next, prev
      (*node).index = (*cable).str_count;
      cursor_finish( cursor );
      last = cursor_item( cursor );
      (*last).next = node;
      (*node).prev = last;

      redo_indices( cable );

      // put new node into cable
      tree_put( cable, node );

   }

   INVARIANT( cable );
   UNLOCK( (*other).mutex );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_append_destructive
*/

void
cable_append_destructive( cable_t *cable, cable_t **other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (**other)._type == CABLE_TYPE );
   PRECONDITION( "cable and other same node string length", (*cable).str_length == (**other).str_length );
   LOCK( (*cable).mutex );
   LOCK( (**other).mutex );
   INVARIANT( cable );

   node_t *n = NULL;
   cable_cursor_t *cursor = NULL;
   node_t *last = NULL;

   // append other's nodes to cable
   cursor = (*cable).cursor;
   n = (**other).first;

   while( n != NULL )
   {
      // set index, next, prev
      (*n).index = (*cable).str_count;
      cursor_finish( cursor );
      last = cursor_item( cursor );
      (*last).next = n;
      (*n).prev = last;

      redo_indices( cable );

      // put new node into cable
      tree_put( cable, n );

      // get next node in other
      n = (*n).next;

   }

   // destroy other
   free( (**other).cursor );
   free( (*other) );
   (*other) = NULL;

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_append_cstring
*/

void
cable_append_cstring( cable_t *cable, char_t *other_cstring )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other_cstring not null", other_cstring != NULL );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   cable_t *other = NULL;
   node_t *node = NULL;
   node_t *n = NULL;
   cable_cursor_t *cursor = NULL;
   node_t *last = NULL;

   // turn other_cstring into cable
   other = cable_make_capacity_from_cstring( other_cstring, (*cable).str_length );

   // get first node in other
   n = (*other).first;

   // dispose of other except for its nodes
   free( (*other).cursor );
   free( other );

   // get cursor for cable
   cursor = (*cable).cursor;

   while( n != NULL )
   {
      // get node from other
      node = n;

      // get next node in other
      n = (*n).next;

      // set index, next, prev
      (*node).index = (*cable).str_count;
      cursor_finish( cursor );
      last = cursor_item( cursor );
      (*last).next = node;
      (*node).prev = last;
      (*node).next = NULL;

      redo_indices( cable );

      // put new node into cable
      tree_put( cable, node );

   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_prepend
*/

void
cable_prepend( cable_t *cable, cable_t *other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_TYPE );
   PRECONDITION( "cable and other same node string length", (*cable).str_length == (*other).str_length );
   LOCK( (*cable).mutex );
   LOCK( (*other).mutex );
   INVARIANT( cable );

   node_t *node = NULL;
   node_t *n = NULL;
   node_t *first = NULL;
   cable_cursor_t *cursor = NULL;

   // make copy of nodes in other, append to cable
   cursor = (*other).cursor;
   cursor_finish( cursor );

   // get last node in other
   n = cursor_item( cursor );

   while( n != NULL )
   {
      // make new node
      node = node_make_from( cable, n );

      // get prev node in other
      n = (*n).prev;

      // get first node in cable
      first = (*cable).first;

      // set index, next, prev
      (*node).index = 0;
      (*node).next = first;
      (*node).prev = NULL;
      (*first).prev = node;

      // put new node into cable
      (*cable).first = node;

      redo_indices( cable );

      tree_put( cable, node );

   }

   INVARIANT( cable );
   UNLOCK( (*other).mutex );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_prepend_destructive
*/

void
cable_prepend_destructive( cable_t *cable, cable_t **other )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (**other)._type == CABLE_TYPE );
   PRECONDITION( "cable and other same node string length", (*cable).str_length == (**other).str_length );
   LOCK( (*cable).mutex );
   LOCK( (**other).mutex );
   INVARIANT( cable );

   node_t *n = NULL;
   node_t *first = NULL;
   cable_cursor_t *cursor = NULL;

   // make copy of nodes in other, append to cable
   cursor = (**other).cursor;
   cursor_finish( cursor );

   // get last node in other
   n = cursor_item( cursor );

   while( n != NULL )
   {
      // get first node in cable
      first = (*cable).first;

      // set index, next, prev
      (*n).index = 0;
      (*n).next = first;
      (*n).prev = NULL;
      (*first).prev = n;

      // put new node into cable
      (*cable).first = n;

      redo_indices( cable );

      tree_put( cable, n );

      // get prev node in other
      n = (*n).prev;

   }

   // destroy other
   free( (**other).cursor );
   free( (*other) );
   (*other) = NULL;

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_prepend_cstring
*/

void
cable_prepend_cstring( cable_t *cable, char_t *other_cstring )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other_cstring not null", other_cstring != NULL );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   cable_t *other = NULL;
   node_t *node = NULL;
   node_t *n = NULL;
   cable_cursor_t *cursor = NULL;
   node_t *first = NULL;

   // turn other_cstring into cable
   other = cable_make_capacity_from_cstring( other_cstring, (*cable).str_length );

   // get last node in other
   cursor = (*other).cursor;
   cursor_finish( cursor );
   n = cursor_item( cursor );
   cursor = NULL;

   // dispose of other except for its nodes
   free( (*other).cursor );
   free( other );

   // get cursor for cable
   cursor = (*cable).cursor;

   while( n != NULL )
   {
      // get node from other
      node = n;

      // get next node in other
      n = (*n).prev;

      // get first node in cable
      first = (*cable).first;

      // set index, next, prev
      (*node).index = 0;
      (*node).next = first;
      (*node).prev = NULL;
      (*first).prev = node;

      // put new node into cable
      (*cable).first = node;

      redo_indices( cable );

      tree_put( cable, node );

   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_insert
*/

void
cable_insert( cable_t *cable, cable_t *other, int32_t start_index )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*cable).str_count ) ) );
   PRECONDITION( "cable and other same node string length", (*cable).str_length == (*other).str_length );
   LOCK( (*cable).mutex );
   LOCK( (*other).mutex );
   INVARIANT( cable );

   // insert space for other in cable
   insert_at_index( cable, start_index, (*other).str_count );

   // put other into cable
   replace_at_index( cable, other, start_index );

   INVARIANT( cable );
   UNLOCK( (*other).mutex );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_insert
*/

void
cable_insert_destructive( cable_t *cable, cable_t **other, int32_t start_index )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (**other)._type == CABLE_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index <= (*cable).str_count ) ) );
   PRECONDITION( "cable and other same node string length", (*cable).str_length == (**other).str_length );
   LOCK( (*cable).mutex );
   LOCK( (**other).mutex );
   INVARIANT( cable );

   node_t *n = NULL;
   node_t *n1 = NULL;
   node_t *n2 = NULL;
   node_t *nx = NULL;
   node_t *first = NULL;
   node_t *last = NULL;
   cable_cursor_t *cursor = NULL;

   if ( start_index == 0 )
   {
      // like a prepend
      n1 = NULL;
      n2 = (**other).first;

      cursor = (**other).cursor;
      cursor_finish( cursor );

      // get last node in other
      n = cursor_item( cursor );

      while( n != NULL )
      {
         // get first node in cable
         first = (*cable).first;

         // set index, next, prev
         (*n).index = 0;
         (*n).next = first;
         (*n).prev = NULL;
         (*first).prev = n;

         // put new node into cable
         (*cable).first = n;

         redo_indices( cable );

         tree_put( cable, n );

         // get prev node in other
         n = (*n).prev;

      }

   }
   else if ( start_index == (*cable).str_count )
   {
      // like an append
      // append other's nodes to cable
      cursor = (*cable).cursor;
      n = (**other).first;

      while( n != NULL )
      {
         // get next node in other
         n1 = (*n).next;

         // set next, prev
         cursor_finish( cursor );
         last = cursor_item( cursor );
         (*last).next = n;
         (*n).prev = last;
         (*n).next = NULL;

         redo_indices( cable );

         // put new node into cable
         tree_put( cable, n );

         // get next node in other
         n = n1;

      }
   }
   else
   {
      // somewhere in between
      n1 = node_for_index( cable, start_index );
      if ( (*n1).index == start_index )
      {
         // don't need to split node
         n2 = n1;
         n1 = (*n2).prev;
      }
      else
      {
         // need to split node at start_index
         n2 = node_make( cable );
         (*n2).next = (*n1).next;
         (*n2).prev = n1;
         (*n1).next = n2;
         if ( (*n2).next != NULL )
         {
            ( *(*n2).next ).prev = n2;
         }

         // copy string contents from start_index to n2
         memcpy
         (
            (*n2).str,
            &( (*n1).str[start_index - (*n1).index] ),
            (*n1).count - ( start_index - (*n1).index )
         );

         // adjust counts
         (*n2).count = (*n1).count - ( start_index - (*n1).index );
         (*n1).count = start_index - (*n1).index;

         // put new node into cable
         redo_indices( cable );
         tree_put( cable, n2 );

      }

      // insert other's nodes to cable between n1 and n2
      cursor = (**other).cursor;
      n = (**other).first;

      while( n != NULL )
      {
         // get next node in other
         nx = (*n).next;

         // set next, prev
         (*n).next = n2;
         (*n).prev = n1;
         (*n1).next = n;
         (*n2).prev = n;

         redo_indices( cable );

         // put new node into cable
         tree_put( cable, n );

         // get next node in other
         n = nx;

         // update n1
         n1 = (*n1).next;

      }
   }

   // destroy other
   free( (**other).cursor );
   free( (*other) );
   (*other) = NULL;

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_insert_cstring
*/

void
cable_insert_cstring( cable_t *cable, char_t *other_cstring, int32_t start_index )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "other_cstring not null", other_cstring != NULL );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index <= (*cable).str_count ) ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   // insert space for other in cable
   insert_at_index( cable, start_index, strlen( other_cstring ) );

   // put other into cable
   replace_at_index_cstring( cable, other_cstring, start_index );

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_append_character
*/

void
cable_append_character( cable_t *cable, char_t c )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   node_t *node = NULL;
   int32_t index = 0;

   // add a space for the character
   index = (*cable).str_count;
   insert_at_index( cable, index - 1, 1 );

   // put the character in the new space
   node = node_for_index( cable, index );
   (*node).str[ index - (*node).index + (*node).start ] = c;

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_prepend_character
*/

void
cable_prepend_character( cable_t *cable, char_t c )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   node_t *node = NULL;
   int32_t index = 0;

   // add a space for the character
   index = 0;
   insert_at_index( cable, index, 1 );

   // put the character in the new space
   node = node_for_index( cable, index );
   (*node).str[ index - (*node).index + (*node).start ] = c;

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_insert_character
*/

void
cable_insert_character( cable_t *cable, char_t c, int32_t index )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   node_t *node = NULL;

   // add a space for the character
   insert_at_index( cable, index, 1 );

   // put the character in the new space
   node = node_for_index( cable, index );
   (*node).str[ index - (*node).index + (*node).start ] = c;

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_to_lower
*/
void
cable_to_lower
(
   cable_t *cable,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*cable).str_count ) ) );
   PRECONDITION( "end_index ok", ( ( end_index >= 0 ) && ( end_index < (*cable).str_count ) ) );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t i = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   int32_t index = 0;
   int32_t count = 0;
   char_t c = 0;

   // get lower case for each character, replace it
   node = node_for_index( cable, start_index );
   cp = node_as_cstring( node );
   index = (*node).index;
   count = (*node).count;

   // see if this spot in cable is equal to other
   for ( i = start_index; i <= end_index; i++ )
   {
      // get character in cable
      c = cp[ i - index ];
      c = ( char_t ) tolower( c );
      cp[ i - index ] = c;

      // set up for next "i"
      if ( ( i - index ) >= ( count - 1 ) )
      {
         node = (*node).next;
         if ( node != NULL )
         {
            cp = node_as_cstring( node );
            index = (*node).index;
            count = (*node).count;
         }
      }

   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_to_upper
*/
void
cable_to_upper
(
   cable_t *cable,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*cable).str_count ) ) );
   PRECONDITION( "end_index ok", ( ( end_index >= 0 ) && ( end_index < (*cable).str_count ) ) );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t i = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   int32_t index = 0;
   int32_t count = 0;
   char_t c = 0;

   // get upper case for each character, replace it
   node = node_for_index( cable, start_index );
   cp = node_as_cstring( node );
   index = (*node).index;
   count = (*node).count;

   // see if this spot in cable is equal to other
   for ( i = start_index; i <= end_index; i++ )
   {
      // get character in cable
      c = cp[ i - index ];
      c = ( char_t ) toupper( c );
      cp[ i - index ] = c;

      // set up for next "i"
      if ( ( i - index ) >= ( count - 1 ) )
      {
         node = (*node).next;
         if ( node != NULL )
         {
            cp = node_as_cstring( node );
            index = (*node).index;
            count = (*node).count;
         }
      }

   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_substring
*/

cable_t *
cable_substring( cable_t *cable, int32_t start_index, int32_t end_index )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*cable).str_count ) ) );
   PRECONDITION( "end_index ok", ( ( end_index >= 0 ) && ( end_index < (*cable).str_count ) ) );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   cable_t *result = NULL;

   result = subcable_from_bounds( cable, start_index, end_index );

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_copy
*/

cable_t *
cable_copy( cable_t *cable )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   cable_t *result = NULL;

   result = subcable_from_bounds( cable, 0, (*cable).str_count - 1 );

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return result;
}

/**
   cable_remove
*/

void
cable_remove( cable_t *cable, int32_t index )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*cable).str_count ) ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   // remove the space for a character
   remove_from_bounds( cable, index, index );

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_remove_substring
*/

void
cable_remove_substring( cable_t *cable, int32_t start_index, int32_t end_index )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*cable).str_count ) ) );
   PRECONDITION( "end_index ok", ( ( end_index >= 0 ) && ( end_index < (*cable).str_count ) ) );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   // remove the space
   remove_from_bounds( cable, start_index, end_index );

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_keep_head
*/

void
cable_keep_head( cable_t *cable, int32_t count )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "count ok", ( count <= (*cable).str_count ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t start_index = count;
   int32_t end_index = (*cable).str_count - 1;

   if ( start_index < (*cable).str_count )
   {
      // remove the space
      remove_from_bounds( cable, start_index, end_index );
   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_keep_tail
*/

void
cable_keep_tail( cable_t *cable, int32_t count )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "count ok", ( count <= (*cable).str_count ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t start_index = 0;
   int32_t end_index = (*cable).str_count - count - 1;

   if ( end_index >= 0 )
   {
      // remove the space
      remove_from_bounds( cable, start_index, end_index );
   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_remove_head
*/

void
cable_remove_head( cable_t *cable, int32_t count )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "count ok", ( count <= (*cable).str_count ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t start_index = 0;
   int32_t end_index = count - 1;

   if ( end_index >= 0 )
   {
      // remove the space
      remove_from_bounds( cable, start_index, end_index );
   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_remove_tail
*/

void
cable_remove_tail( cable_t *cable, int32_t count )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   PRECONDITION( "count ok", ( count <= (*cable).str_count ) );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t start_index = (*cable).str_count - count;
   int32_t end_index = (*cable).str_count - 1;

   if ( start_index >= 0 )
   {
      // remove the space
      remove_from_bounds( cable, start_index, end_index );
   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_wipe_out
*/

void
cable_wipe_out( cable_t *cable )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   int32_t start_index = 0;
   int32_t end_index = (*cable).str_count - 1;
   if ( end_index < 0 )
   {
      end_index = 0;
   }

   if ( (*cable).str_count > 0 )
   {
      // remove the space
      remove_from_bounds( cable, start_index, end_index );
   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}

/**
   cable_reclaim
*/

void
cable_reclaim( cable_t *cable )
{
   PRECONDITION( "cable not null", cable != NULL );
   PRECONDITION( "cable type OK", (*cable)._type == CABLE_TYPE );
   LOCK( (*cable).mutex );
   INVARIANT( cable );

   node_t *node = NULL;
   node_t *n1 = NULL;
   node_t *n2 = NULL;

   // move chars in each node's str to start of str buffer
   node = (*cable).first;

   while( node != NULL )
   {
      if ( (*node).start != 0 )
      {
         memmove( (*node).str, &( (*node).str[(*node).start] ), (*node).count );
         (*node).start = 0;
      }
      node = (*node).next;
   }

   // append node's chars to preceeding node's chars if there's space
   // if successful, remove the now empty node
   node = (*cable).first;

   while( node != NULL )
   {
      n1 = (*node).next;

      if ( n1 != NULL )
      {
         if ( (*node).count + (*n1).count <= (*cable).str_length )
         {
            // copy chars from n1 to node
            memmove
            (
               &( (*node).str[ (*node).start + (*node).count ] ),
               (*n1).str,
               (*n1).count
            );

            // update counts
            (*node).count = (*node).count + (*n1).count;
            (*n1).count = 0;

            // adjust pointers to eliminate n1 from linked list
            n2 = (*n1).next;
            (*node).next = n2;

            if ( n2 != NULL )
            {
               (*n2).prev = node;
            }

            // remove n1
            redo_indices( cable );
            tree_remove( cable, n1 );

            // update for next iteration
            node = node;
         }
         else
         {
            // update for next iteration
            node = (*node).next;
         }
      }
      else
      {
         node = NULL;
      }
   }

   INVARIANT( cable );
   UNLOCK( (*cable).mutex );

   return;
}


#ifdef __cplusplus
}
#endif

/* End of file */

