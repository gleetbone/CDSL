/**
 @file Cable_utf8.c
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

 Function definitions for the opaque cable_utf8_t type.

 @section Design notes
 
   The basic structure is a red-black balanced binary search tree of
   nodes, where each node contains an array of UTF8 characters. Each node is 
   sorted by the index of the first UTF8 character in its array. The nodes
   are also linked one to the next in order like a linked list. The character
   arrays in the nodes (other than the first one) do not necessarily begin with 
   the start of a UTF8 character or end with the final byte in a UTF8 
   multibyte character. The start of UTF8 characters in a node may or may not
   be at the start of the character array, and may end before the end of the
   character array. All bytes in each character array not specifically occupied
   with a UTF8 byte are zero. All nodes in a cable contain character strings
   of identical length. Most of the low level heavy lifting is done with 
   the local functions that remove character(s) by index, insert new 
   character(s) by index, and replace character(s) by index.
   
   There are a few API functions not exported to the Cable_utf8.h file that are
   used for testing. They allow the character array in each node to be created with a 
   specified length different from the default length. This allows testing 
   functions to easily set up scenarios where nodes are filled, emptied, and 
   otherwise run through the wringer of messy manipulation with shorter
   test character strings. To use these functions, cable_utf8_make_capacity and
   cable_utf8_make_capacity_from_cstring, simply include their prototype in the
   C code that uses them. 
*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Cable_utf8.h"
#include "utf8rewind.h"

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
   cable_utf8_make_capacity

   Create and initialize a cable_utf8_t instance.
   Content will be the empty cable_utf8 and the capacity of each node will be "capacity".

   @return pointer to the new data structure
*/
cable_utf8_t *
cable_utf8_make_capacity( int32_t capacity );

/**
   cable_utf8_make_capacity_from_cstring

   Create and initialize a cable_utf8_t instance.
   Content will be from other and the capacity of each node will be "capacity".

   @param str the cstring to copy from
   @param capacity the new cable_utf8's node capacity
   @return pointer to the new data structure
*/
cable_utf8_t *
cable_utf8_make_capacity_from_cstring( char_t *str, int32_t capacity );

/**
   cable_utf8_capacity

   Returns the number of available characters in cable_utf8 nodes.

   @param current the cable_utf8_t instance
   @return number of characters available for storage in cable_utf8
*/
int32_t
cable_utf8_capacity( cable_utf8_t *current );


#define DEFAULT_STRING_LENGTH 128
#define MINIMUM_STRING_LENGTH 4
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
   int32_t count;
   int32_t byte_index;
   int32_t byte_start;
   int32_t byte_count;
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

   special node to act as sentinel for all instances of Cable_utf8
   singleton null node - helps avoid complexity in code
*/
static int32_t null_node_initialized = 0;
static node_t null_node;

struct cable_utf8_cursor_struct;
typedef struct cable_utf8_cursor_struct cable_utf8_cursor_t;

/**
   Binary search tree structure definition.
   
   Nodes hold contiguous substrings of the cable. String data in a node is not 
   required to start or end with a valid UTF8 multibyte character. So, a 
   multibyte UTF8 character may be split between successive nodes. The byte
   stream is contiguous between nodes, no spaces or null characters.
*/

struct cable_utf8_struct
{
   int32_t _type;

   node_t root;   // pseudo root, helps avoid complexity in code
   int32_t count;
   int32_t str_count;
   int32_t str_count_valid;
   int32_t str_byte_count;
   int32_t str_length;
   node_t *first;
   cable_utf8_cursor_t *cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure definition. Holds reference to cable_utf8 and current node.
*/

struct cable_utf8_cursor_struct
{
   cable_utf8_t *cable_utf8;
   node_t *item;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   local function redo_indices
*/

static
void
redo_indices( cable_utf8_t *current );

static
void
redo_byte_indices( cable_utf8_t *current );

static
node_t *
node_for_index( cable_utf8_t *current, int32_t index );

static
char_t *
node_as_cstring( node_t *node );

static
char_t *
item( cable_utf8_t *current, int32_t index );

/**
   local utf8 functions
*/

#define CABLE_UTF8_FILL_CHARACTER 0x7FU

#define CABLE_UTF8_CHAR_MAX_SIZE 8

#define UTF8_1_MASK     0x80U
#define UTF8_1_VALID    0x00U

#define UTF8_N_MASK     0xC0U
#define UTF8_N_VALID    0xC0U

#define UTF8_21_MASK    0xE0U
#define UTF8_21_VALID   0xC0U
#define UTF8_22_MASK    0xC0U
#define UTF8_22_VALID   0x80U

#define UTF8_31_MASK    0xF0U
#define UTF8_31_VALID   0xE0U
#define UTF8_32_MASK    0xC0U
#define UTF8_32_VALID   0x80U
#define UTF8_33_MASK    0xC0U
#define UTF8_33_VALID   0x80U

#define UTF8_41_MASK    0xF8U
#define UTF8_41_VALID   0xF0U
#define UTF8_42_MASK    0xC0U
#define UTF8_42_VALID   0x80U
#define UTF8_43_MASK    0xC0U
#define UTF8_43_VALID   0x80U
#define UTF8_44_MASK    0xC0U
#define UTF8_44_VALID   0x80U

#define UTF8_SIZE       1
#define UTF16_SIZE      2
#define UTF32_SIZE      4
#define WCHAR_SIZE      sizeof( wchar_t )

/**
   utf8_byte_count
   
   returns number or bytes for a utf8
   
   @param c the (first) character
   @return byte count of utf8 character
*/
static
int32_t
utf8_byte_count( char_t c )
{
   int32_t result = 0;

   if ( ( c & UTF8_1_MASK ) == UTF8_1_VALID )
   {
      result = 1;
   }
   else if ( ( c & UTF8_21_MASK ) == UTF8_21_VALID  )
   {
      result = 2;
   }
   else if ( ( c & UTF8_31_MASK ) == UTF8_31_VALID  )
   {
      result = 3;
   }
   else if ( ( c & UTF8_41_MASK ) == UTF8_41_VALID  )
   {
      result = 4;
   }

   return result;
}

/**
   is_index_valid
   
   returns 1 if index is valid for cable
   
   @param current the tree of nodnes
   @param the index of interest
   @return 1 if valid, 0 otherwise
*/
static
int32_t
is_index_valid( cable_utf8_t *current, int32_t index )
{
   int32_t result = 0;

   result = ( ( index >= 0 ) && ( index < (*current).str_count ) );

   return result;
}

/**
   is_count_valid
   
   returns 1 if count is valid for cable
   
   @param current the tree of nodnes
   @param the count of interest
   @return 1 if valid, 0 otherwise
*/
static
int32_t
is_count_valid( cable_utf8_t *current, int32_t count )
{
   int32_t result = 0;

   result = ( ( count >= 0 ) && ( count <= (*current).str_count ) );

   return result;
}

/**
   byte_index_for_index
   
   returns byte index for character index
   
   @param current the tree of nodnes
   @param the character index of interest
   @return the byte index for the character index
*/
static
int32_t
byte_index_for_index( cable_utf8_t *current, int32_t index )
{
   int32_t result = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   char_t *cp1 = NULL;

   // check for end of bytes
   if ( index == (*current).str_count )
   {
      result = (*current).str_byte_count;
   }
   else
   {
      // otherwise find the node for index and get byte index
      node = node_for_index( current, index );
      cp = node_as_cstring( node );
      cp1 = ( char_t * ) utf8seek( cp, (*node).count, cp, index - (*node).index, SEEK_SET );

      result = cp1 - cp + (*node).byte_index;
   }

   return result;
}

/**
   black_path_count
   
   returns count of black nodes in path to node
   
   @param the node
   @return count of black nodex on path from node to root  
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
   
   make a new node
   
   @param current the tree of nodes
   @return a new node
*/

static
node_t *
node_make( cable_utf8_t *current )
{
   // allocate node
   node_t *node = ( node_t * ) calloc( 1, sizeof( node_t ) );
   CHECK( "node allocated correctly", node != NULL );
   
   // set values
   (*node).index = 0;
   (*node).count = 0;
   (*node).byte_index = 0;
   (*node).byte_start = 0;
   (*node).byte_count = 0;
   (*node).prev = NULL;
   (*node).next = NULL;
   (*node).parent = &null_node;
   (*node).left = &null_node;
   (*node).right = &null_node;
   (*node).color = black;

   // allocate string storage
   (*node).str = ( char_t * ) calloc( (*current).str_length + 1, sizeof( char_t ) );
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
   node_make_filled
   
   make a new node where character storage bytes are set to CABLE_UTF8_FILL_CHARACTER
   
   @param current the tree of nodes
   @return a new node
*/

static
node_t *
node_make_filled( cable_utf8_t *current )
{
   // allocate node
   node_t *node = ( node_t * ) calloc( 1, sizeof( node_t ) );
   CHECK( "node allocated correctly", node != NULL );

   // set values
   (*node).index = 0;
   (*node).count = 0;
   (*node).byte_index = 0;
   (*node).byte_start = 0;
   (*node).byte_count = 0;
   (*node).prev = NULL;
   (*node).next = NULL;
   (*node).parent = &null_node;
   (*node).left = &null_node;
   (*node).right = &null_node;
   (*node).color = black;

   // allocate string storage
   (*node).str = ( char_t * ) calloc( (*current).str_length + 1, sizeof( char_t ) );
   CHECK( "(*node).str allocated correctly", (*node).str != NULL );
   
   memset( (*node).str, CABLE_UTF8_FILL_CHARACTER, (*current).str_length );

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
   
   @param current the tree of nodes
   @param n the node to make from
   @return the new node
*/

static
node_t *
node_make_from( cable_utf8_t *current, node_t *n )
{
   // allocate node
   node_t *node = ( node_t * ) calloc( 1, sizeof( node_t ) );
   CHECK( "node allocated correctly", node != NULL );

   // set values
   (*node).index = (*n).index;
   (*node).count = (*n).count;
   (*node).byte_index = (*n).byte_index;
   (*node).byte_start = (*n).byte_start;
   (*node).byte_count = (*n).byte_count;
   (*node).prev = (*n).prev;
   (*node).next = (*n).next;
   (*node).parent = &null_node;
   (*node).left = &null_node;
   (*node).right = &null_node;
   (*node).color = black;

   // allocate string storage
   (*node).str = ( char_t * ) calloc( (*current).str_length + 1, sizeof( char_t ) );
   CHECK( "(*node).str allocated correctly", (*node).str != NULL );

   // copy string contents
   memcpy( (*node).str, (*n).str, (*current).str_length );

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
   (*node).count = 0;
   (*node).byte_index = 0;
   (*node).byte_start = 0;
   (*node).byte_count = 0;
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
   node_has_byte_index
   
   return 1 if node contains a byte at the specified index
   
   @param n the node
   @param byte_index the specified index of the byte
   @return 1 if true, 0 otherwise
*/

static
int32_t
node_has_byte_index( node_t *n, int32_t byte_index )
{
   int32_t result = 0;

   if (
         ( byte_index >= (*n).byte_index )
         &&
         (
            ( byte_index < ( (*n).byte_index + (*n).byte_count ) )
            ||
            ( (*n).byte_count ) == 0 )
      )
   {
      result = 1;
   }

   return result;
}

/**
   node_for_byte_index_recurse
   
   find the node with the specified byte index, retursive
   
   @param node the node to look at
   @param byte_index the index to look for
   @return the node with the byte index or NULL if not found
   
*/

static
node_t *
node_for_byte_index_recurse( node_t *node, int32_t byte_index )
{
   node_t *result = &null_node;

   if ( node_has_byte_index( node, byte_index ) == 1 )
   {
      result = node;
   }

   if ( result == &null_node )
   {
      if ( ( byte_index < (*node).byte_index ) == 1 )
      {

         if ( (*node).left != &null_node )
         {
            result = node_for_byte_index_recurse( (*node).left, byte_index );
         }
      }
   }

   if ( result == &null_node )
   {
      if ( ( byte_index < (*node).byte_index ) == 0 )
      {

         if ( (*node).right != &null_node )
         {
            result = node_for_byte_index_recurse( (*node).right, byte_index );
         }
      }
   }

   return result;
}

/**
   node for byte_index

   Return node in cable_utf8 for which the index is valid, NULL if none

   @param current cable_utf8_t instance
   @param byte_index the index to query for
   @return the found node with the specified byte index
*/

static
node_t *
node_for_byte_index( cable_utf8_t *current, int32_t byte_index )
{
   node_t *result = NULL;
   node_t *node = NULL;

   // get root node
   result = &null_node;
   node = (*current).root.left;

   // recurse to see if can find value in tree
   if ( node != &null_node )
   {
      result = node_for_byte_index_recurse( node, byte_index );
   }

   return result;
}

/**
   node_has_index
   
   returns 1 if node contains the specified character index
   
   @param n the node
   @param index the specified index
   @return 1 if true, 0 otherwise
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
   
   returns node node for specified index, recursive
   
   @param n the node
   @param index the specified index
   @return node if found, NULL otherwise
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

   Return node in cable_utf8 for which the index is valid, NULL if none

   @param current cable_utf8_t instance
   @param index the index to query for
   @return the desired node if it exists, NULL otherwise
*/

static
node_t *
node_for_index( cable_utf8_t *current, int32_t index )
{
   node_t *result = NULL;
   node_t *node = NULL;

   // get root node
   result = &null_node;
   node = (*current).root.left;

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

   @param current cable_utf8_t instance
   @return the cstring
*/

static
char_t *
node_as_cstring( node_t *node )
{
   char_t *result = NULL;

   // set result
   result = &( (*node).str[ (*node).byte_start ] );

   return result;
}

static
void
tree_remove( cable_utf8_t *current, node_t *n );

/**
   tree_rotate_left
   
   perform left rotation starting at node
   
   @param current the tree of nodes
   @param node the node to rotate around 
*/
static
void
tree_rotate_left( cable_utf8_t *current, node_t *node )
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
   tree_rotate_right
   
   perform right rotation starting at node
   
   @param current the tree of nodes
   @param node the node to rotate around 
*/
static void
tree_rotate_right( cable_utf8_t *current, node_t *node )
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
   tree_has_recurse
   
   returns 1 if node is present in tree, recursive
   
   @param node the node to start looking at
   @param nx the node to look for
   @return 1 if node is present, 0 otherwise
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

   @param current cable_utf8_t instance
   @param nx the node to query for
   @return the node if found, NULL otherwise
*/

static
int32_t
tree_has( cable_utf8_t *current, node_t *nx )
{
   int32_t result = 0;
   node_t *node = NULL;

   // get root node
   node = (*current).root.left;

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
   
   @param node the node to look at
   @return the sibling node if present, NULL otherwise  
*/
static
node_t *
tree_sibling_of( node_t *node )
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
  tree_repair_put
  
  repair the tree after a node is inserted
  
  @param current the tree of nodes
  @param  node the node inserted
*/

static
void
tree_repair_put( cable_utf8_t *current, node_t *node )
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
         ( (*(*n).parent).color == red )
      )
   {

      // recolor up if more work needed
      if ( (* tree_sibling_of( (*n).parent ) ).color == red )
      {
         (*(*n).parent).color = black;
         (* tree_sibling_of( (*n).parent ) ).color = black;
         if ( (*(*n).parent).parent != &null_node )
         {
            (*(*(*n).parent).parent).color = red;
            tree_repair_put( current, (*(*n).parent).parent );
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
            tree_rotate_left( current, n );
         }
         (*(*n).parent).color = black ;
         if ( (*(*n).parent).parent != &null_node )
         {
            (*(*(*n).parent).parent).color = red;
            tree_rotate_right( current, (*(*n).parent).parent );
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
            tree_rotate_right( current, n );
         }
         (*(*n).parent).color = black;
         if ( (*(*n).parent).parent != &null_node )
         {
            (*(*(*n).parent).parent).color = red;
            tree_rotate_left( current, (*(*n).parent).parent );
         }
      }
   }

   // color the root black
   (*(*current).root.left).color = black;

   return;
}

/**
   tree_put
   
   put a node into the tree
   
   @param current the tree of nodes
   @param n the node to insert
*/

static
void
tree_put( cable_utf8_t *current, node_t *n )
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
      result = ( (*n).byte_index < (*node).byte_index );
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
         ( parent == &(*current).root )
         ||
         ( (*n).byte_index < (*parent).byte_index )
      )
   {
      (*parent).left = n;
      tree_repair_put( current, n );
   }
   else
   {
      (*parent).right = n;
      tree_repair_put( current, n );
   }

   // ensure tree root is black
   (*(*current).root.left).color = black;

   // increment node_count
   (*current).count = (*current).count + 1;

   // remove any empty nodes
//   remove_empty_nodes( current );
   
   return;
}

/**
   tree_repair_remove

   repair the tree after a node has been deleted by rotating and repainting
   colors to restore the red-black tree's properties
   
   @param current the tree of nodes
   @param node the node removed
 */
static
void
tree_repair_remove( cable_utf8_t *current, node_t *node )
{
   node_t *n = NULL;
   node_t *sibling = NULL;

   n = node;

   // while node is not tree root and is black
   while ( ( n != (*current).root.left ) && ( (*n).color == black ) )
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
            tree_rotate_left( current, (*n).parent );
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
               tree_rotate_right( current, sibling );
               sibling = (*(*n).parent).right;
            }

            (*sibling).color = (*(*n).parent).color;
            (*(*n).parent).color = black;
            (*(*sibling).right).color = black;
            tree_rotate_left( current, (*n).parent );
            n = (*current).root.left;
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
            tree_rotate_right( current, (*n).parent );
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
               tree_rotate_left( current, sibling );
               sibling = (*(*n).parent).left;
            }

            (*sibling).color = (*(*n).parent).color;
            (*(*n).parent).color = black;
            (*(*sibling).left).color = black;
            tree_rotate_right( current, (*n).parent );
            n = (*current).root.left;
         }
      }
   }

   (*n).color = black;

   return;
}

/**
   tree_predecessor

   returns the node before node, or nil if none.
   
   @param current the tree of nodes
   @param node the node to look at
   @return the predecessor node if exists, NULL otherwise
*/
static
node_t *
tree_predecessor( cable_utf8_t *current, node_t *node )
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
      if ( result == &(*current).root )
      {
         result = &null_node;
      }

   }
*/

   return( result );
}

static
void
cursor_forth( cable_utf8_cursor_t *cursor );

static
void
cursor_start( cable_utf8_cursor_t *cursor );

static
node_t *
cursor_item( cable_utf8_cursor_t *cursor );

/**
   tree_remove
   
   remove a node from the tree
   
   @param current the tree of nodes
   @param n the node to remove
*/
static
void
tree_remove( cable_utf8_t *current, node_t *n )
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
   rbcolor_t p_color = 0;
   node_t *p_left = NULL;
   node_t *p_right = NULL;

// the following local variable is never needed when the tree invariants are true
//   int32_t p_is_parents_left = 0;
   
   // get the node to be removed
   node = n;

   // if node is not null, continue
   if ( node != &null_node )
   {
      // move cursor forth if pointing to this node
      if ( (*(*current).cursor).item == node )
      {
         cursor_forth( (*current).cursor );
      }

      // if node has two children, find predecessor, swap pre's data into node
      // and set node to pre
      if ( ( (*node).left != &null_node ) && ( (*node).right != &null_node ) )
      {
         pre = tree_predecessor( current, node );

         // swap nodes pre and node in tree
         n_parent = (*node).parent;
         if ( (*(*node).parent).left == node )
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
         
// the following commented out bit of code is never needed when the tree invariants are true
//         if ( (*(*pre).parent).left == pre )
//         {
//            p_is_parents_left = 1;
//         }
//         else
//         {
//            p_is_parents_left = 0;
//         }

         p_color = (*pre).color;
         p_left = (*pre).left;
         p_right = (*pre).right;

         (*node).parent = p_parent;
         (*node).left = p_left;
         (*node).right = p_right;
         (*node).color = p_color;

         if ( n_is_parents_left == 1 )
         {
            (*n_parent).left = pre;
         }
         else
         {
            (*n_parent).right = pre;
         }

         (*n_left).parent = pre;
         (*n_right).parent = pre;

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
               (*p_left).parent = node;
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
               (*p_parent).right = node;
            }

            if ( p_left != &null_node )
            {
               (*p_left).parent = node;
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

         if ( node == (*current).root.left )
         {
            // eliminate tree root
            (*current).root.left = pull_up;
            (*pull_up).parent = &( (*current).root );
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
            tree_repair_remove( current, pull_up );
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
            tree_repair_remove( current, node );
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
      (*current).count = (*current).count - 1;
   }

   // dispose of node
   node_dispose( node );

   return;
}

/**
   tree_count_recurse
   
   find number of nodes, recursive
   
   @param node the current node to look at
   @return the count of nodes
*/
static
int
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
   
   find number of nodes, recursive
   
   @param current the tree of nodes
   @return the count of nodes
*/
static
int
tree_count( cable_utf8_t *current )
{
   int32_t result = 0;

   result = tree_count_recurse( (*current).root.left );

   return result;
}

/**
   recursion for cable_utf8 cursor functions - start, item, forth, off

   The following routines depend on the fact that the cable_utf8
   is (already) in order and that the forth recursion keeps track
   of the last seen ( the previous ) node (in the cursor structure).
*/

/**
   cursor_finish
   
   put the cursor at the last node
   
   @param cursor the cursor
*/
static
void
cursor_finish( cable_utf8_cursor_t *cursor )
{
   node_t *node = NULL;

   // set node from the cable_utf8 root
   node = (*(*cursor).cable_utf8).root.left;

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
   
   put the cursor at the first node
   
   @param cursor the cursor
*/
static
void
cursor_start( cable_utf8_cursor_t *cursor )
{
   node_t *node = NULL;

   // set node from the cable_utf8 root
   node = (*(*cursor).cable_utf8).root.left;

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
   
   return the current node for the cursor
   
   @param cursor the cursor
   @return the n
*/
static
node_t *
cursor_item( cable_utf8_cursor_t *cursor )
{
   // return the value for the current cursor item
   return (*cursor).item;
}


/**
   cursor_forth
   
   put the cursor at the next node
   
   @param cursor the cursor
*/
static
void
cursor_forth( cable_utf8_cursor_t *cursor )
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
   
   return 1 if the cursor is past the last item
   
   @param cursor the cursor
   @return 1 if the cursor is off, 0 otherwise
*/
static
int32_t
cursor_off(  cable_utf8_cursor_t *cursor )
{
   int32_t result = 0;

   // cursor item is null_node or root == off
   if (
         ( (*cursor).item == &(*(*cursor).cable_utf8).root )
         ||
         ( (*cursor).item == &null_node )
      )
   {
      result = 1;
   }

   return result;
}

/**
   subcable_utf8_from_bounds
   
   create another cable from the part of the original cable bewtween the start_index
   and the end_index
   
   @param current the tree of nodes
   @param start_index where to start the result cable
   @param end_index where to end the result cable
   @return a new cable made from part of the original cable
*/

static
cable_utf8_t *
subcable_utf8_from_bounds( cable_utf8_t *current, int32_t start_index, int32_t end_index )
{
   cable_utf8_t *result = NULL;
   node_t *node = NULL;
   node_t *n = NULL;
   node_t *n1 = NULL;
   char_t *cp_node = NULL;
   char_t *cp_node_start = NULL;
   char_t *cpn = NULL;
   int32_t i = 0;
   int32_t i_b = 0;
   int32_t bcount = 0;
   char_t c = 0;
   int32_t i_n = 0;

   // make a new cable_utf8 to return
   result = cable_utf8_make_capacity( (*current).str_length );

   // if invalid indices, return empty cable_utf8
   if ( end_index >= start_index )
   {
      // remove the empty node in result
      tree_remove( result, (*result).root.left );

      // set to iterate through cable_utf8
      node = node_for_index( current, start_index );

      // get pointer to first UTF8 character in node
      cp_node_start = &( (*node).str[ (*node).byte_start ] );
      cp_node = ( char_t * ) utf8seek( cp_node_start, (*node).byte_count, cp_node_start, start_index - (*node).index, SEEK_SET );

      // set up new node
      i_n = 0;
      n = node_make( current );
      (*n).index = 0;
      (*n).count = 0;
      (*n).byte_start = 0;
      (*n).byte_index = 0;
      (*n).byte_count = 0;
      cpn = (*n).str;
      (*result).first = n;

      // tree_put new node into result tree
      tree_put( result, n );

      // copy UTF8 characters into new node
      i = start_index;
      while ( i <= end_index )
      {
         // get first byte of UTF8 character in node
         c = cp_node[0];

         // get number of bytes of UTF8 character string
         bcount = utf8_byte_count( c );

         // see if it will fit in the current new node
         if ( i_n + bcount < (*current).str_length )
         {
            // if so, put the bytes for the UTF8 character at i into the new node
            for( i_b = 0; i_b < bcount; i_b++ )
            {
               // put into new node
               cpn[i_n] = cp_node[i_b];

               // update n's index
               i_n++;

            }
            // update n info
            (*n).byte_count = (*n).byte_count + bcount;
            (*n).count = (*n).count + 1;

            // update the node byte pointer
            cp_node = cp_node + bcount;

            // update the UTF8 index
            i = i + 1;
         }

         // n is full
         else
         {
            // make new node
            n1 = node_make( current );
            (*n1).index = i;
            (*n1).count = 0;
            (*n1).byte_start = 0;
            (*n1).byte_index = 0;
            (*n1).byte_count = 0;

            (*n).next = n1;
            (*n1).prev = n;
            n = n1;
            cpn = (*n).str;
            i_n = 0;

            // put new node into tree
            redo_byte_indices( result );
            tree_put( result, n );

         }

         // set up for next "i"
         if ( ( i - (*node).index ) > ( (*node).count - 1 ) )
         {
            node = (*node).next;
            if ( node != NULL )
            {
               // get pointer to first UTF8 character in node
               cp_node = &( (*node).str[ (*node).byte_start ] );
            }
         }
      }
   }

   (*result).str_count_valid = 0;

   redo_byte_indices( result );
   redo_indices( result );

   return result;
}

/**
   redo_indices
   
   waok through the cable and assign correct indices to each node
   
   @param current the tree of nodes
*/

static
void
redo_indices( cable_utf8_t *current )
{
   node_t *node = NULL;
   int32_t i = 0;
   int32_t index = 0;
   int32_t count = 0;

   // start at first node, set index
   node = (*current).first;
   (*node).index = 0;
   index = (*node).index;

   while ( ( node != &null_node ) && ( node != NULL ) )
   {
      count = 0;
      // count the starting byte of single and multi-byte UTF8 characters
      for ( i = (*node).byte_start; i < (*node).byte_start + (*node).byte_count; i++ )
      {
         if ( ( (*node).str[i] & UTF8_1_MASK ) == UTF8_1_VALID )
         {
            index = index + 1;
            count = count + 1;
         }
         
         if ( ( (*node).str[i] & UTF8_N_MASK ) ==  UTF8_N_VALID )
         {
            index = index + 1;
            count = count + 1;
         }
      }
      
      (*node).count = count;
      
      // get the next node to process
      node = (*node).next;
      
      // if the next node is not the null_node, set its index 
      // (the index of the first complete utf8 character in the node)
      if ( ( node != &null_node ) && ( node != NULL ) )
      {
         (*node).index = index;
      }
      
   }
   
   // set string count
   (*current).str_count = index;
   (*current).str_count_valid = 1;

   return;
}

/**
   redo_byte_indices
   
   walk through the tree and redo the byte indices for each node
   
   @param cable_urf8 the tree of nodes
*/

static
void
redo_byte_indices( cable_utf8_t *current )
{
   node_t *node = NULL;
   int32_t byte_index = 0;
   int32_t byte_count = 0;

   // start at first node, set index
   node = (*current).first;
   (*node).byte_index = 0;
   byte_index = (*node).byte_index;
   byte_count = (*node).byte_count;
   node = (*node).next;
   byte_index = byte_count;

   // set indices through linked list
   while ( node != NULL )
   {
      (*node).byte_index = byte_index;
      byte_index = byte_index + (*node).byte_count;
      byte_count = byte_count + (*node).byte_count;
      node = (*node).next;
   }

   // set string count
   (*current).str_byte_count = byte_count;

   return;
}

/**
   remove_from_bounds
   
   remove part of a cable between a start_index and an end_index
   
   @param current the tree of nodes
   @param start_index where to start removing characters
   @param end_index where to end removing characters
*/

static
void
remove_from_bounds( cable_utf8_t *current, int32_t start_index, int32_t end_index )
{
   node_t *node = NULL;
   node_t *node1 = NULL;
   node_t *n1 = NULL;
   node_t *n2 = NULL;
   int32_t i = 0;
   int32_t byte_index_start = 0;
   int32_t byte_index_end = 0;
   int32_t si = 0;
   int32_t ei = 0;
   char_t *cp = NULL;
   char_t c = 0;

   // get start and end node for start and end indices
   n1 = node_for_index( current, start_index );
   byte_index_start = byte_index_for_index( current, start_index );
   
   n2 = node_for_index( current, end_index );
   byte_index_end = byte_index_for_index( current, end_index );
   c = (*n2).str[ (*n2).byte_start + ( byte_index_end - (*n2).byte_index ) ];
   byte_index_end = byte_index_end + utf8_byte_count( c ) - 1;
   
   // cases - same node, next to each other nodes, separated nodes

   // same node
   if ( n1 == n2 )
   {
      // get indices
      si = byte_index_start - (*n1).byte_index + (*n1).byte_start;
      ei = byte_index_end - (*n1).byte_index + (*n1).byte_start;
      
      // get pointer to utf8 characters
      cp = (*n1).str;
      
      for ( i = 0; i < (*n1).byte_count - ei; i++ )
      {
         if ( ( ei + i + 1 ) < (*current).str_length )
         {  
            cp[si + i] = cp[ei + i + 1];
         }
      }
      
      // adjust node count
      (*n1).byte_count = (*n1).byte_count - ( ei - si + 1 );
      
      // zero out unused bytes
      for ( i = (*n1).byte_start + (*n1).byte_count; i < (*current).str_length; i++ )
      {
         cp[i] = 0;
      }
      
      redo_byte_indices( current );

      // now see if n1 is now empty; if so, remove
      if ( ( (*current).count > 1 ) && ( (*n1).byte_count ==  0 ) )
      {
         if ( n1 == (*current).first )
         {
            (*current).first = (*n1).next;
            if ( (*n1).next != NULL )
            {
               (*(*n1).next).prev = NULL;
            }
         }
         else
         {
            (*(*n1).prev).next = (*n1).next;
            if ( (*n1).next != NULL )
            {
               (*(*n1).next).prev = (*n1).prev;
            }
         }
         tree_remove( current, n1 );
         redo_byte_indices( current );
      }
   }

   // neighbor nodes
   else if ( (*n1).next == n2 )
   {
      // new byte count
      (*n1).byte_count = byte_index_start - (*n1).byte_index;
      
      // zero out now-unused bytes in (*n1).str
      cp = (*n1).str;
      for ( i = (*n1).byte_start + (*n1).byte_count; i < (*current).str_length; i++ )
      {
         cp[i] = 0;
      }
        
      // new byte count and byte start in n2
      (*n2).byte_count = (*n2).byte_count - ( byte_index_end - (*n2).byte_index + 1 );
      (*n2).byte_start = byte_index_end - (*n2).byte_index + (*n2).byte_start + 1;
      
      // zero out now-unused bytes in (*n1).str
      cp = (*n2).str;
      for ( i=0; i<(*n2).byte_start; i++ )
      {
         cp[i] = 0;
      }
   
      redo_byte_indices( current );

      // now see if n1 and/or n2 is now empty; if so, remove
      if ( ( (*current).str_byte_count > 0 ) && ( (*n1).byte_count == 0 ) && ( (*n2).byte_count == 0 ) )
      {
         // both n1 and n2 are empty, remove both
         if ( n1 == (*current).first )
         {
            (*current).first = (*n2).next;
            if ( (*n2).next != NULL )
            {
               (*(*n2).next).prev = NULL;
            }
         }
         else
         {
            (*(*n1).prev).next = (*n2).next;
            if ( (*n2).next != NULL )
            {
               (*(*n2).next).prev = (*n1).prev;
            }
         }
         tree_remove( current, n1 );
         tree_remove( current, n2 );
         redo_byte_indices( current );
      }
      else if ( ( (*current).str_byte_count == 0 ) && ( (*n1).byte_count == 0 ) && ( (*n2).byte_count == 0 ) )
      {
         // cable_utf8 is empty, both n1 and n2 are empty, remove n2
         (*n1).prev = NULL;
         (*n1).next = NULL;
         tree_remove( current, n2 );
         redo_byte_indices( current );
      }
      else if ( ( (*current).str_byte_count > 0 ) && ( (*n1).byte_count ==  0 ) )
      {
         // n1 empty, n2 not empty
         if ( n1 == (*current).first )
         {
            (*current).first = n2;
            (*n2).prev = NULL;
         }
         else
         {
            (*(*n1).prev).next = (*n1).next;
            if ( (*n1).next != NULL )
            {
               (*(*n1).next).prev = (*n1).prev;
            }
         }
         tree_remove( current, n1 );
         redo_byte_indices( current );
      }
      else if ( ( (*current).str_byte_count > 0 ) && ( (*n2).byte_count ==  0 ) )
      {
         // n1 not empty, n2 empty
         (*n1).next = (*n2).next;
         if ( (*n2).next != NULL )
         {
            (*(*n2).next).prev = n1;
         }
         tree_remove( current, n2 );
         redo_byte_indices( current );
      }

   }

   // not neighbor nodes
   else
   {
      // new byte count
      (*n1).byte_count = byte_index_start - (*n1).byte_index;
      
      // zero out now-unused bytes in (*n1).str
      cp = (*n1).str;
      for ( i = (*n1).byte_start + (*n1).byte_count; i < (*current).str_length; i++ )
      {
         cp[i] = 0;
      }
   
      // new byte count and byte start in n2
      (*n2).byte_count = (*n2).byte_count - ( byte_index_end - (*n2).byte_index + 1 );
      (*n2).byte_start = byte_index_end - (*n2).byte_index + (*n2).byte_start + 1;
      
      // zero out now-unused bytes in (*n1).str
      cp = (*n2).str;
      for ( i=0; i<(*n2).byte_start; i++ )
      {
         cp[i] = 0;
      }

	  // delete nodes between n1 and n2
      node = (*n1).next;
      while( node != n2 )
      {
         node1 = (*node).next;
         tree_remove( current, node );
         node = node1;
      }

      // set pointers
      (*n1).next = n2;
      (*n2).prev = n1;

      redo_byte_indices( current );

      // now see if n1 and/or n2 is now empty; if so, remove
      if ( ( (*current).str_byte_count == 0 ) )
      {
         // n1 and n2 are empty, remove n2
         (*n1).next = NULL;
         tree_remove( current, n2 );
         redo_byte_indices( current );
      }
      else if ( ( (*current).str_byte_count > 0 ) && ( (*n1).byte_count ==  0 ) && ( (*n2).byte_count ==  0 ) )
      {
         if ( n1 == (*current).first )
         {
            (*current).first = (*n2).next;
            (*(*n2).next).prev = NULL;
         }
         
         // n1 and n2 are empty
         if ( (*n1).prev != NULL )
         {
            (*(*n1).prev).next = n2;
            (*(*n1).next).prev = (*n1).prev;
         }

         if ( (*n2).prev != NULL )
         {
            (*(*n2).prev).next = (*n2).next;
         }

         if ( (*n2).next != NULL )
         {
            (*(*n2).next).prev = (*n2).prev;
            if ( (*(*n2).next).prev == n1 )
            {
               (*(*n2).next).prev = NULL;
            }
         }

         tree_remove( current, n1 );
         tree_remove( current, n2 );
         redo_byte_indices( current );
      }
      else if ( ( (*current).str_byte_count > 0 ) && ( (*n1).byte_count ==  0 ) )
      {
         // n1 is empty
         if ( n1 == (*current).first )
         {
            (*current).first = n2;
            (*n2).prev = NULL;
         }
         else
         {
            (*(*n1).prev).next = (*n1).next;
            if ( (*n1).next != NULL )
            {
               (*(*n1).next).prev = (*n1).prev;
            }
         }
         
         tree_remove( current, n1 );
         redo_byte_indices( current );
      }
      else if ( ( (*current).str_byte_count > 0 ) && ( (*n2).byte_count ==  0 ) )
      {
         // n1 not empty, n2 is empty
         (*n1).next = (*n2).next;
         if ( (*n2).next != NULL )
         {
            (*(*n2).next).prev = n1;
         }

         tree_remove( current, n2 );
         redo_byte_indices( current );
      }

   }

   (*current).str_count_valid = 0;
   redo_indices( current );

   return;
}

/**
   insert_at_byte_index
   
   insert byte_count blank (zero) characters at a particular byte_index
   
   @param current the tree of nodes
   @param byte_index where to insert blank characters
   @param byte_count how many bytes of blank characters to insert
*/

static
void
insert_at_byte_index( cable_utf8_t *current, int32_t byte_index, int32_t byte_count )
{
   node_t *node = NULL;
   node_t *node1 = NULL;
   node_t *nodex = NULL;
   node_t *n1 = NULL;
   node_t *n2 = NULL;
   char_t *cp = NULL;
   char_t *cp1 = NULL;
   int32_t length = 0;
   int32_t i = 0;

   // see if we're adding at the end of the cable_utf8
   if ( byte_index == (*current).str_byte_count )
   {
      // add new nodes at end of cable_utf8 to hold count chars
      length = 0;

      if ( (*current).str_byte_count == 0 )
      {
         node1 = (*current).first;
         nodex = node1;
      }
      else
      {
         node1 = node_for_byte_index( current, (*current).str_byte_count - 1 );
         nodex = node1;
      }

      while ( length < byte_count )
      {
         node = node_make_filled( current );
         (*node).prev = node1;
         (*node1).next = node;
         (*node).byte_index = (*current).str_byte_count;
         if ( ( byte_count - length ) < (*current).str_length )
         {
            (*node).byte_count = byte_count - length;
            
            // zero unused bytes
            cp = (*node).str;
            for ( i = (*node).byte_count; i< (*current).str_length; i++ )
            {
               cp[i] = 0;
            }
            
            length = byte_count;
         }
         else
         {
            (*node).byte_count = (*current).str_length;
            length = length + (*current).str_length;
         }

         redo_byte_indices( current );
         tree_put( current, node );
         node1 = node;
      }

         // remove node with zero count, if any
         if ( (*nodex).byte_count == 0 )
         {
            (*current).first = (*nodex).next;
            (*(*current).first).prev = NULL;

            // remove from tree and dispose of node
            tree_remove( current, nodex );

         }
   }
   else
   {
      // get node for byte_index
      n1 = node_for_byte_index( current, byte_index );
      if ( n1 != NULL )
      {
         cp1 = (*n1).str;
         n2 = (*n1).next;
      }

      // see if count chars will fit in n1
      if ( ( (*n1).byte_count + byte_count ) <= (*current).str_length )
      {
         // if so, move chars to start of node
         if ( (*n1).byte_start != 0 )
         {
            memmove( (*n1).str, &(  (*n1).str[ (*n1).byte_start ] ), (*n1).byte_count );
            (*n1).byte_start = 0;
         }

         // and move chars after (*n1).count
         memmove
         (
            &( (*n1).str[ byte_index - (*n1).byte_index + byte_count ] ),
            &( (*n1).str[ byte_index - (*n1).byte_index ] ),
            (*n1).byte_count - ( byte_index - (*n1).byte_index )
         );

         // fill zero bytes possibly left in str array with default character
         for ( i= byte_index - (*n1).byte_index; i < byte_index - (*n1).byte_index + byte_count; i++ )
         {
            if ( (*n1).str[i] == 0 )
            {
               (*n1).str[i] = CABLE_UTF8_FILL_CHARACTER;
            }
         }

         // adjust node count
         (*n1).byte_count = (*n1).byte_count + byte_count;

         redo_byte_indices( current );
      }
      // add new node(s) to hold new chars
      else
      {
         // first, split n1 into two nodes at index
         node = node_make( current );
         cp = (*node).str;

         // adjust pointers
         (*node).next = (*n1).next;
         (*node).prev = n1;
         (*n1).next = node;

         if ( (*node).next != NULL )
         {
            (*(*node).next).prev = node;
         }

         // move chars after index to new node
         memmove
         (
            &( cp[ 0 ] ),
            &( cp1[ (*n1).byte_start + byte_index - (*n1).byte_index ] ),
            (*n1).byte_count - ( byte_index - (*n1).byte_index + (*n1).byte_start )
         );

         (*node).byte_count = (*n1).byte_count - ( byte_index - (*n1).byte_index + (*n1).byte_start );
         (*n1).byte_count = byte_index - (*n1).byte_index - (*n1).byte_start;
         
         // fill unused bytes with zeroes
         cp = (*n1).str;
         for ( i = (*n1).byte_start + (*n1).byte_count; i < (*current).str_length; i++ )
         {
            cp[i] = 0;
         }

         // haven't added any chars yet, now do so one node at a time
         length = 0;
         node1 = node;
         nodex = n1;

         while ( byte_count - length > 0 )
         {
            node = node_make_filled( current );
            if ( ( byte_count - length ) > (*current).str_length )
            {
               (*node).byte_count = (*current).str_length;
               length = length + (*node).byte_count;
               (*node1).prev = node;
               (*node).next = node1;
               (*node).prev = nodex;
               (*nodex).next = node;
            }
            else
            {
               (*node).byte_count = byte_count - length;
               
               // zero unused bytes
               cp = (*node).str;
               for ( i = (*node).byte_count; i< (*current).str_length; i++ )
               {
                  cp[i] = 0;
               }
               
               length = length + (*node).byte_count;
               
               (*node1).prev = node;
               (*node).next = node1;
               (*node).prev = nodex;
               (*nodex).next = node;
            }
            nodex = node;
         }

         redo_byte_indices( current );

         // remove nodes with zero count, if any
         node1 = (*current).first;
         nodex = (*node1).next;

         while ( (*node1).byte_count == 0 )
         {
            // update n1 if it has count of 0
            if ( node1 == n1 )
            {
               n1 = (*node1).next;
            }

            (*nodex).prev = NULL;
            (*current).first = nodex;

            // remove from tree and dispose of node
            tree_remove( current, node1 );

            node1 = (*current).first;
            nodex = (*node1).next;
         }

         while( nodex != n2 )
         {
            if ( (*nodex).byte_count == 0 )
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
                  (*(*nodex).next).prev = node1;
               }

               // remove from tree and dispose of node
               tree_remove( current, nodex );

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
         redo_byte_indices( current );

         // put new nodes into tree
         node = n1;

         while( node != n2 )
         {
            if ( tree_has( current, node ) == 0 )
            {
               tree_put( current, node );
            }
            node = (*node).next;
         }
      }
   }

   (*current).str_count_valid = 0;

   return;
}

/**
   insert_at_index
   
   insert byte_count blank (zero) characters at index
   
   @param current the tree of nodes
   @param index where to insert the characters
   @param byte_count how many characters to insert
*/

static
void
insert_at_index( cable_utf8_t *current, int32_t index, int32_t byte_count )
{
   int32_t byte_index = 0;

   byte_index = byte_index_for_index( current, index );

   insert_at_byte_index( current, byte_index, byte_count );
   
   redo_indices( current );

   return;
}

/**
   substring_index_in_bounds
   
   return 1 if other cable is within cable_utf8 between start_index and end_index
   
   @param current the tree of nodes
   @param other cable that may or may not be contained within cable_utf8
   @param start_index first index to see if other is within cable_utf8 
   @param end_index last index to see if other is within cable_utf8
   @return -1 if other is not within current, >=0 otherwise 
*/
static
int32_t
substring_index_in_bounds
(
   cable_utf8_t *current,
   cable_utf8_t *other,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "start_index ok", is_index_valid( current, start_index ) == 1 );
   PRECONDITION( "end_index ok", is_index_valid( current, end_index ) ==1 );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );

   int32_t result = -1;
   int32_t i = 0;
   int32_t i_b = 0;
   int32_t flag = 0;
   int32_t byte_length_other = 0;
   node_t *node = NULL;
   node_t *node_other = NULL;
   char_t *cp = NULL;
   char_t *cp_start = NULL;
   char_t *cp_other = NULL;
   int32_t offset = 0;
   int32_t offset_other = 0;
   char_t c = 0;
   char_t c_other = 0;

   // make sure indices are current
   redo_indices( current );
   redo_indices( other );

   // check length of other
   if ( (*other).str_count > ( end_index - start_index + 1 ) )
   {
      // no chance for finding other - it's longer than segment of cable_utf8
      result = -1;
   }
   else
   {
      // compare each character looking for substring
      node = node_for_index( current, start_index );

      // get start of bytes for UTF8 character at start_index
      cp = &( (*node).str[ (*node).byte_start ] );
      cp_start = ( char_t * ) utf8seek( cp, (*node).byte_count, cp, start_index - (*node).index, SEEK_SET );
      offset = cp_start - cp;

      // get number of bytes to comp
      byte_length_other = (*other).str_byte_count;

      result = -1;

      // see if this spot in cable_utf8 is equal to other
      i = start_index;
      while ( i <= end_index )
      {

         // go to start of other
         flag = 1;
         node_other = (*other).first;
         cp_other = node_as_cstring( node_other );
         offset_other = 0;

         // compare other to this spot in cable_utf8
         for ( i_b = 0; i_b < byte_length_other; i_b++ )
         {
            // get character in cable_utf8
            c = cp[ i_b + offset ];

            // get character in other
            c_other = cp_other[ i_b + offset_other ];

            // if not equal, we're done for this "i"
            if ( c != c_other  )
            {
               flag = 0;
               break;
            }

            // set up for next i_b
            if ( ( i_b + offset ) >= ( (*node).byte_count - 1 ) )
            {
               node = (*node).next;
               if ( node != NULL )
               {
                  cp = node_as_cstring( node );
                  offset = -i_b - 1;
               }
            }

            if ( ( i_b + offset_other ) >= ( (*node_other).byte_count - 1 ) )
            {
               node_other = (*node_other).next;
               if ( node_other != NULL )
               {
                  cp_other = node_as_cstring( node_other );
                  offset_other = -i_b - 1;
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
         i = i + 1;
         node = node_for_index( current, i );
         cp = &( (*node).str[ (*node).byte_start ] );
         cp_start = ( char_t * ) utf8seek( cp, (*node).byte_count, cp, i - (*node).index, SEEK_SET );
         offset = cp_start - cp;

      }
   }

   return result;
}

/**
   substring_at_index_cstring
   
   return 1 if other string is at index in cable_utf8
   
   @param current the tree of nodes
   @param other cstring that may or may not be contained within cable_utf8
   @param index index to see if other is within cable_utf8 
   @param end_index last index to see if other is within cable_utf8
   @return 0 if other is not at index, 1 if so 
*/
static
int32_t
substring_at_index_cstring
(
   cable_utf8_t *current,
   char_t *other,
   int32_t index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "index ok", is_index_valid( current, index ) == 1 );
   PRECONDITION( "end_index ok", is_index_valid( current, end_index ) == 1 );
   PRECONDITION( "index and end_index ok", ( index <= end_index ) );

   int32_t result = 0;
   int32_t i_character = 0;
   int32_t i = 0;
   int32_t i_other = 0;
   int32_t flag = 0;
   int32_t str_count_other = 0;
   int32_t byte_count_other = 0;
   char_t *cp = 0;
   
   // get count of other
   str_count_other = utf8len( other );
   byte_count_other = strlen( other );

   // check length of other
   if ( str_count_other > ( end_index - index + 1 ) )
   {
      // no chance for finding other - it's longer than segment of cable_utf8
      result = 0;
   }
   else
   {
      result = 1;
      i_other = 0;
      
      // check other one character at a time aganst current
      for ( i_character = index; i_character <= end_index; i_character++ )
      {
         cp = item( current, i_character );
         
         i = 0;
         flag = 0;
         while ( cp[i] != 0 )
         {
            if ( cp[i] == other[i_other] )
            {
               flag = 1;
            }
            
            i = i + 1;
            i_other = i_other + 1;
         }
         
         free( cp );
         
         if ( flag != 1 )
         {
            result = 0;
            break;
         }
         
         if ( i_other == byte_count_other )
         {
            break;
         }   
      }
   }
   
   if ( i_other != byte_count_other )
   {
      result = 0;
   }   
   
   return result;
}


/**
   substring_index_in_bounds_cstring
   
   return 1 if other cable is within cable_utf8 between start_index and end_index
   
   @param current the tree of nodes
   @param other cstring that may or may not be contained within cable_utf8
   @param start_index first index to see if other is within cable_utf8 
   @param end_index last index to see if other is within cable_utf8
   @return -1 if other is not within current, >= 0 if found 
*/
static
int32_t
substring_index_in_bounds_cstring
(
   cable_utf8_t *current,
   char_t *other,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "start_index ok", is_index_valid( current, start_index ) == 1 );
   PRECONDITION( "end_index ok", is_index_valid( current, end_index ) == 1 );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );

   int32_t result = -1;
   int32_t flag = 0;
   int32_t i = 0;

   for ( i = start_index; i <= end_index; i++ )
   {
      flag = substring_at_index_cstring( current, other, i, end_index );
      
      if ( flag == 1 )
      {
         result = i;
         break;
      }
   }

   return result;
}

/**
   replace_at_index
   
   replace contents of cable_utf8 with contents of other at start_index
   
   @param current the tree of nodes
   @param other cable to replace contents of cable_utf8
   @param start_index where to place contents of other into cable_utf8
*/
static
void
replace_at_index
(
   cable_utf8_t *current,
   cable_utf8_t *other,
   int32_t start_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "start_index ok", is_index_valid( current, start_index ) == 1 );

   int32_t i_b = 0;
   int32_t byte_length_other = 0;
   node_t *node = NULL;
   node_t *node_other = NULL;
   char_t *cp = NULL;
   char_t *cp_start = NULL;
   char_t *cp_other = NULL;
   int32_t offset = 0;
   int32_t offset_other = 0;

   // make sure indices are current
   redo_indices( current );
   redo_indices( other );

   // compare each character looking for substring
   node = node_for_index( current, start_index );

   // get start of bytes for UTF8 character at start_index
   cp = &( (*node).str[ (*node).byte_start ] );
   cp_start = ( char_t * ) utf8seek( cp, (*node).byte_count, cp, start_index - (*node).index, SEEK_SET );
   offset = cp_start - cp;

   // get number of bytes to copy
   byte_length_other = (*other).str_byte_count;

   // copy characters in other into cable_utf8

   // go to start of other
   node_other = (*other).first;
   cp_other = node_as_cstring( node_other );
   offset_other = 0;

   // copy character in other to this spot in cable_utf8
   for ( i_b = 0; i_b < byte_length_other; i_b++ )
   {
      // copy character in other into cable_utf8
      cp[ i_b + offset ] = cp_other[ i_b + offset_other ];

      // set up for next i_b
      if ( ( i_b + offset ) >= ( (*node).byte_count - 1 ) )
      {
         node = (*node).next;
         if ( node != NULL )
         {
            cp = node_as_cstring( node );
            offset = -i_b - 1;
         }
      }

      if ( ( i_b + offset_other ) >= ( (*node_other).byte_count - 1 ) )
      {
         node_other = (*node_other).next;
         if ( node_other != NULL )
         {
            cp_other = node_as_cstring( node_other );
            offset_other = -i_b - 1;
         }
      }
   }

   return;
}

/**
   replace_at_index_cstring
   
   replace contents of cable_utf8 with contents of other at start_index
   
   @param current the tree of nodes
   @param other cstring to replace contents of cable_utf8
   @param start_index where to place contents of other into cable_utf8
*/
static
void
replace_at_index_cstring
(
   cable_utf8_t *current,
   char_t *other,
   int32_t start_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "start_index ok", is_index_valid( current, start_index ) == 1 );

   int32_t i_b = 0;
   int32_t byte_length_other = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   char_t *cp_start = NULL;
   char_t *cp_other = NULL;
   int32_t offset = 0;
   node = node_for_index( current, start_index );

   // make sure indices are current
   redo_indices( current );

   // compare each character looking for substring
   node = node_for_index( current, start_index );

   // get start of bytes for UTF8 character at start_index
   cp = &( (*node).str[ (*node).byte_start ] );
   cp_start = ( char_t * ) utf8seek( cp, (*node).byte_count, cp, start_index - (*node).index, SEEK_SET );
   offset = cp_start - cp;

   // get number of bytes to comp
   byte_length_other = strlen( other );

   // copy characters in other into cable_utf8

   // go to start of other
   cp_other = other;

   // copy character in other to this spot in cable_utf8
   for ( i_b = 0; i_b < byte_length_other; i_b++ )
   {
      // copy character in other into cable_utf8
      cp[ i_b + offset ] = cp_other[ i_b ];

      // set up for next i_b
      if ( ( i_b + offset ) >= ( (*node).byte_count - 1 ) )
      {
         node = (*node).next;
         if ( node != NULL )
         {
            cp = node_as_cstring( node );
            offset = -i_b - 1;
         }
      }
   }

   redo_indices( current );
   
   return;
}

/**
   to_upper
   
   convert contents of cable_utf8 to upper case (if upper case exists)
   
   @param current the tree of nodes
*/
static
void
to_upper
(
   cable_utf8_t *current
)
{
   PRECONDITION( "current not null", current != NULL );

   node_t *node = NULL;
   char_t *cp = NULL;
   char_t *str = NULL;
   int32_t length = 0;
   int32_t errors = 0;

   // compare each character looking for substring
   node = (*current).first;

   // get temporary buffer
   str = ( char_t * ) calloc( 2*(*current).str_length, sizeof( char_t ) );
   CHECK( "str allocated correctly", str != NULL );

   // loop through nodes, putting each one in upper case
   while( node != NULL )
   {
      // get start of bytes for UTF8 character at start_index
      cp = &( (*node).str[ (*node).byte_start ] );

      // get byte count of converted buffer
      length = utf8toupper( cp, (*node).byte_count, str, 2*(*current).str_length, UTF8_LOCALE_DEFAULT, &errors );
      CHECK( "utf8 to upper ok", errors == 0 );

      // result will fit into the current node ( MINIMUM_STRING_LENGTH or larger )
      memcpy( (*node).str, str, length );
      (*node).byte_start = 0;
      (*node).byte_count = length;

      // redo byte indices
      redo_byte_indices( current );

      // set up for next iteration
      node = (*node).next;

   }

   // free temporary buffer
   free( str );

   (*current).str_count_valid = 0;
   redo_indices( current );

   return;
}

/**
   to_lower
   
   convert contents of cable_utf8 to lower case (if lower case exists)
   
   @param current the tree of nodes
*/
static
void
to_lower
(
   cable_utf8_t *current
)
{
   PRECONDITION( "current not null", current != NULL );

   node_t *node = NULL;
   char_t *cp = NULL;
   char_t *str = NULL;
   int32_t length = 0;
   int32_t errors = 0;

   // compare each character looking for substring
   node = (*current).first;

   // get temporary buffer
   str = ( char_t * ) calloc( 2*(*current).str_length, sizeof( char_t ) );
   CHECK( "str allocated correctly", str != NULL );

   // loop through nodes, putting each one in upper case
   while( node != NULL )
   {
      // get start of bytes for UTF8 character at start_index
      cp = &( (*node).str[ (*node).byte_start ] );

      // get byte count of converted buffer
      length = utf8tolower( cp, (*node).byte_count, str, 2*(*current).str_length, UTF8_LOCALE_DEFAULT, &errors );
      CHECK( "utf8 to upper ok", errors == 0 );

      // result will fit into the current node ( MINIMUM_STRING_LENGTH or larger )
      memcpy( (*node).str, str, length );
      (*node).byte_start = 0;
      (*node).byte_count = length;

      // redo byte indices
      redo_byte_indices( current );

      // set up for next iteration
      node = (*node).next;


   }

   // free temporary buffer
   free( str );

   (*current).str_count_valid = 0;
   redo_indices( current );

   return;
}

/**
   utf8_to_utf16
   
   convert utf8 character to utf16 character
   
   @param c the utf8 character
   @return the utf16 character
*/
static
utf16_t *
utf8_to_utf16( const char_t *c )
{
   utf16_t *result = NULL;
   int32_t n_c = 0;
   int32_t errors = 0;

   n_c = strlen( c );

   result = ( utf16_t * ) calloc( CABLE_UTF8_CHAR_MAX_SIZE, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   utf8toutf16( c, n_c, result, CABLE_UTF8_CHAR_MAX_SIZE, &errors );
   CHECK( "utf conversion ok", errors == 0 );

   return result;
}

/**
   utf8_to_utf32
   
   convert utf8 character to utf32 character
   
   @param c the utf8 character
   @return the utf32 character
*/
static
utf32_t
utf8_to_utf32( const char_t *c )
{
   utf32_t result = 0;
   int32_t n_c = 0;
   int32_t errors = 0;

   n_c = strlen( c );

   utf8toutf32( c, n_c, &result, sizeof( uint32_t ), &errors );
   CHECK( "utf conversion ok", errors == 0 );

   return result;
}

/**
   utf8_to_wchar
   
   convert utf8 character to wchar
   
   @param c the utf8 character
   @return the wchar
*/
static
wchar_t
utf8_to_wchar( const char_t *c )
{
   wchar_t result = 0;
   int32_t n_c = 0;
   int32_t errors = 0;

   n_c = strlen( c );

   utf8towide( c, n_c, &result, sizeof( wchar_t ), &errors );
   CHECK( "utf conversion ok", errors == 0 );

   return result;
}

/**
   utf16_to_utf8
   
   convert utf16 character to utf8 character
   
   @param c the utf8 character
   @return the utf8 character
*/
static
char_t *
utf16_to_utf8( utf16_t *cp )
{
   char_t *result = NULL;
   int32_t errors = 0;
   utf16_t str[4] = {0};
   int32_t str_len = 0;

   result = ( char_t * ) calloc( CABLE_UTF8_CHAR_MAX_SIZE, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   str_len = 2;
   if ( cp[1] != 0 )
   {
      str_len = 4;
   }
   
   str[0] = cp[0];
   str[1] = cp[1];
   utf16toutf8( str, str_len, result, CABLE_UTF8_CHAR_MAX_SIZE, &errors );
   CHECK( "utf conversion ok", errors == 0 );

   return result;
}

/**
   utf32_to_utf8
   
   convert utf32 character to utf8 character
   
   @param c the utf32 character
   @return the utf8 character
*/
static
char_t *
utf32_to_utf8( utf32_t c )
{
   char_t *result = NULL;
   int32_t errors = 0;
   utf32_t str[3] = {0};

   result = ( char_t * ) calloc( CABLE_UTF8_CHAR_MAX_SIZE, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   str[0] = c;
   utf32toutf8( str, UTF32_SIZE, result, CABLE_UTF8_CHAR_MAX_SIZE, &errors );
   CHECK( "utf conversion ok", errors == 0 );

   return result;
}

/**
   wchar_to_utf8
   
   convert wchar to utf8 character
   
   @param c the wchar
   @return the utf8 character
*/
static
char_t *
wchar_to_utf8( wchar_t c )
{
   char_t *result = NULL;
   int32_t errors = 0;
   wchar_t str[2] = {0};

   result = ( char_t * ) calloc( CABLE_UTF8_CHAR_MAX_SIZE, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   str[0] = c;
   widetoutf8( str, WCHAR_SIZE, result, CABLE_UTF8_CHAR_MAX_SIZE, &errors );
   CHECK( "utf conversion ok", errors == 0 );

   return result;
}

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
nonnegative_count( cable_utf8_t *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
valid_count( cable_utf8_t *p )
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
cursor_not_null( cable_utf8_t *p )
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
      result = ( (*(*node).left).byte_index <= (*node).byte_index );
   }

   if ( result == 1 )
   {
      if ( (*node).right != &null_node )
      {
         result = ( (*node).byte_index <= (*(*node).right).byte_index );
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
in_order( cable_utf8_t *p )
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
root_is_black( cable_utf8_t *p )
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
null_node_ok( cable_utf8_t *p )
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
nonnegative_byte_count( cable_utf8_t *p )
{
   int32_t result = 1;

   result = ( (*p).str_count >= 0 );

   return result;
}

static
int32_t
valid_byte_count( cable_utf8_t *p )
{
   int32_t result = 0;
   int32_t byte_count = 0;
   node_t *node = NULL;
   cable_utf8_cursor_t *cursor = NULL;

   node = (*p).first;

   byte_count = 0;
   while( node != NULL )
   {
      byte_count = byte_count + (*node).byte_count;
      node = (*node).next;
   }

   result = ( (*p).str_byte_count == byte_count );

   if ( result == 1 )
   {
      cursor = (*p).cursor;
      cursor_start( cursor );

      byte_count = 0;
      while( cursor_off( cursor ) == 0 )
      {
         node = cursor_item( cursor );
         byte_count = byte_count + (*node).byte_count;
         cursor_forth( cursor );
      }

      result = ( (*p).str_byte_count == byte_count );
   }

   return result;
}

static
int32_t
byte_indices_ok( cable_utf8_t *p )
{
   int32_t result = 0;
   int32_t byte_index = 0;
   node_t *node = NULL;
   cable_utf8_cursor_t *cursor = NULL;

   node = (*p).first;

   result = ( (*node).byte_index == 0 );

   if ( result == 1 )
   {
      byte_index = byte_index + (*node).byte_count;
      node = (*node).next;

      while( ( node != NULL ) && ( result == 1 ) )
      {
         result = ( (*node).byte_index == byte_index );
         byte_index = byte_index + (*node).byte_count;
         node = (*node).next;
      }
   }

   if ( result == 1 )
   {
      cursor = (*p).cursor;
      cursor_start( cursor );

      byte_index = 0;
      while( ( cursor_off( cursor ) == 0 ) && ( result == 1 ) )
      {
         node = cursor_item( cursor );
         result = ( (*node).byte_index == byte_index );
         byte_index = byte_index + (*node).byte_count;
         cursor_forth( cursor );
      }

      result = ( (*p).str_byte_count == byte_index );
   }

   return result;
}

static
int32_t
unused_bytes_zero_ok( cable_utf8_t *p )
{
   int32_t result = 0;
   int32_t i = 0;
   node_t *node = NULL;
   char_t *cp = NULL;

   node = (*p).first;
   cp = (*node).str;
   result = 1;

   if ( (*p).str_byte_count > 0 )
   {
   
      while( ( result == 1 ) && ( node != NULL ) )
      {
         cp = (*node).str;
         
         for ( i = 0; ( i < (*node).byte_start ) && ( result == 1 ); i++ )
         {
            result = 0;
            if ( cp[i] == 0 )
            {
               result = 1;
            }
         }
         
         for
         (
            i = (*node).byte_start + (*node).byte_count; 
            ( i < (*p).str_length ) && ( result == 1 ); 
            i++ 
         )
         {
            result = 0;
            if ( cp[i] == 0 )
            {
               result = 1;
            }
         }
      
         node = (*node).next;
      }
      
   }
   
   return result;
}

static
int32_t
sequence_ok( cable_utf8_t *p )
{
   int32_t result = 0;
   int32_t i = 0;
   node_t *node1 = NULL;
   node_t *node2 = NULL;
   cable_utf8_cursor_t *cursor = NULL;

   // get first node in linked list
   node1 = (*p).first;

   // get first node in tree
   cursor = (*p).cursor;
   cursor_start( cursor );
   node2 = cursor_item( cursor );

   // verify they're the same
   result = ( node1 == node2 );

   // loop to compare each node in both iterations
   for ( i=1; ( i<(*p).count ) && ( result == 1 ); i++ )
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
links_ok( cable_utf8_t *p )
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
node_colors_ok( cable_utf8_t *p )
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
path_black_count_ok( cable_utf8_t *p )
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
str_count_valid_ok( cable_utf8_t *p )
{
   int32_t result = 1;
   int32_t count = 0;
   int32_t i = 0;
   node_t *node = NULL;

   result = 0;
   
   if ( (*p).str_count_valid == 1 )
   {
      result = 1;
   }
   
   // count UTF8 characters, see if agrees with what's in p
   if ( result == 1 )
   {
      node = (*p).first;

      while ( ( node != NULL ) && ( node != &null_node ) )
      {
         for ( i = (*node).byte_start; i < (*node).byte_start + (*node).byte_count; i++ )
         {
            if ( ( (*node).str[i] & UTF8_1_MASK ) == UTF8_1_VALID )
            {
               count = count + 1;
            }
            
            if ( ( (*node).str[i] & UTF8_N_MASK ) == UTF8_N_VALID )
            {
               count = count + 1;
            }
         }
         
         node = (*node).next;
      }
      
      result = (*p).str_count == count;

   }

   return result;
}

static
void invariant( cable_utf8_t *p )
{
   assert(((void) "nonnegative count", nonnegative_count( p ) ));
   assert(((void) "nonnegative byte count", nonnegative_byte_count( p ) ));
   assert(((void) "valid byte count", valid_byte_count( p ) ));
   assert(((void) "valid count", valid_count( p ) ));
   assert(((void) "cursor not null", cursor_not_null( p ) ));
   assert(((void) "cable_utf8 in order", in_order( p ) ));
   assert(((void) "root is black", root_is_black( p ) ));
   assert(((void) "null node ok", null_node_ok( p ) ));
   assert(((void) "byte indices ok", byte_indices_ok( p ) )); 
   assert(((void) "byte unused_bytes_zero ok", unused_bytes_zero_ok( p ) )); 
   assert(((void) "sequence ok", sequence_ok( p ) ));
   assert(((void) "links ok", links_ok( p ) ));
   assert(((void) "node colors ok", node_colors_ok( p ) ));
   assert(((void) "path black count ok", path_black_count_ok( p ) ));
   assert(((void) "str count valid ok", str_count_valid_ok( p ) ));
   return;
}

#endif

/**
   init_null_node
   
   initialize the file-level null node structure
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
   cable_utf8_make
*/

cable_utf8_t *
cable_utf8_make( void )
{
   // allocate cable_utf8 struct
   cable_utf8_t * result
      = ( cable_utf8_t * ) calloc( 1, sizeof( cable_utf8_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set null node - self referencing
   init_null_node();

   // set type
   (*result)._type = CABLE_UTF8_TYPE;

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
   (*result).str_count_valid = 1;
   (*result).str_byte_count = 0;

   // set built-in cursor
   // allocate cursor struct
   cable_utf8_cursor_t *cursor
      =  ( cable_utf8_cursor_t * )
         calloc( 1, sizeof( cable_utf8_cursor_t ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set cable_utf8
   (*cursor).cable_utf8 = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = &null_node;

   // set cable_utf8 built-in cursor
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
   cable_utf8_make_capacity
*/

cable_utf8_t *
cable_utf8_make_capacity( int32_t capacity )
{
   PRECONDITION( "capacity ok", capacity >= MINIMUM_STRING_LENGTH );
   
   // allocate cable_utf8 struct
   cable_utf8_t * result
      = ( cable_utf8_t * ) calloc( 1, sizeof( cable_utf8_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set null node - self referencing
   init_null_node();

   // set type
   (*result)._type = CABLE_UTF8_TYPE;

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
   (*result).str_count_valid = 1;
   (*result).str_byte_count = 0;

   // set built-in cursor
   // allocate cursor struct
   cable_utf8_cursor_t *cursor
      =  ( cable_utf8_cursor_t * )
         calloc( 1, sizeof( cable_utf8_cursor_t ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set cable_utf8
   (*cursor).cable_utf8 = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = &null_node;

   // set cable_utf8 built-in cursor
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
   cable_utf8_make_from
*/

cable_utf8_t *
cable_utf8_make_from( cable_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );

   node_t *node = NULL;
   node_t *n = NULL;
   node_t *n1 = NULL;
   int32_t flag = 0;

   // make cable_utf8 struct
   cable_utf8_t *result = cable_utf8_make_capacity( (*current).str_length );

   // remove the empty node in result
   tree_remove( result, (*result).root.left );

   // walk through nodes in current, duplicate them, copy string, insert
   node = (*current).first;
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
      redo_byte_indices( result );
      tree_put( result, n );

      // prepare for next iteration
      n1 = n;
      node = (*node).next;
   }

   redo_indices( result );
   
   INVARIANT( result );

   return result;
}

/**
   cable_utf8_make_from_cstring
*/

cable_utf8_t *
cable_utf8_make_from_cstring( char_t *str )
{
   PRECONDITION( "str not null", str != NULL );

   int32_t i = 0;
   int32_t j = 0;
   int32_t n = 0;
   node_t *node = NULL;
   node_t *n1 = NULL;
   char_t *s = NULL;

   // make cable_utf8 struct
   cable_utf8_t *result = cable_utf8_make();

   // set type
   (*result)._type = CABLE_UTF8_TYPE;

   // copy string into result
   n = strlen( str );

   for( i=0; i<n; i=i+(*result).str_length )
   {
      if ( i == 0 )
      {
         node = (*result).first;
         s = (*node).str;
         for( j=0; ( (j<n) && (j<(*result).str_length) ); j++ )
         {
            s[j] = str[j];
         }
         (*node).byte_start = 0;
         (*node).byte_count = j;
         n1 = node;

         // adjust indices
         redo_byte_indices( result );
      }
      else
      {
         node = node_make( result );
         s = (*node).str;
         for( j=0; ( (j<(n-i)) && (j<(*result).str_length) ); j++ )
         {
            s[j] = str[i+j];
         }
         (*node).byte_index = i;
         (*node).byte_start = 0;
         (*node).byte_count = j;

         // adjust pointers
         (*n1).next = node;
         (*node).prev = n1;

         // prepare for next iteration
         n1 = node;

         // adjust indices and put node into tree
         redo_byte_indices( result );
         tree_put( result, node );
      }
   }

   redo_indices( result );

   INVARIANT( result );

   return result;
}

/**
   cable_utf8_make_capacity_from_cstring
*/

cable_utf8_t *
cable_utf8_make_capacity_from_cstring( char_t *str, int32_t capacity )
{
   PRECONDITION( "str not null", str != NULL );
   PRECONDITION( "capacity ok", capacity >= MINIMUM_STRING_LENGTH );

   int32_t i = 0;
   int32_t j = 0;
   int32_t n = 0;
   int32_t count = 0;
   node_t *node = NULL;
   node_t *n1 = NULL;
   char_t *s = NULL;

   // make cable_utf8 struct
   cable_utf8_t *result = cable_utf8_make_capacity( capacity );

   // set type
   (*result)._type = CABLE_UTF8_TYPE;

   // copy string into result
   n = strlen( str );

   for( i=0; i<n; i=i+(*result).str_length )
   {
      if ( i == 0 )
      {
         node = (*result).first;
         s = (*node).str;
         for( j=0; ( (j<n) && (j<(*result).str_length) ); j++ )
         {
            s[j] = str[j];
         }
         (*node).byte_start = 0;
         (*node).byte_count = j;
         n1 = node;

         // adjust indices
         redo_byte_indices( result );
      }
      else
      {
         node = node_make( result );
         s = (*node).str;
         for( j=0; ( (j<(n-i)) && (j<(*result).str_length) ); j++ )
         {
            s[j] = str[i+j];
         }
         (*node).byte_index = i;
         (*node).byte_start = 0;
         (*node).byte_count = j;

         // adjust pointers
         (*n1).next = node;
         (*node).prev = n1;

         // prepare for next iteration
         n1 = node;

         // adjust indices and put node into tree
         redo_byte_indices( result );
         tree_put( result, node );
      }
      count = count + j;
   }

   redo_indices( result );
   
   INVARIANT( result );

   return result;
}

/**
   cable_utf8_dispose
*/

void
cable_utf8_dispose( cable_utf8_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == CABLE_UTF8_TYPE );
   LOCK( (**current).mutex );
   INVARIANT( *current );

   node_t *node = NULL;
   node_t *n = NULL;

   // delete nodes
   node = (**current).first;
   while ( node != NULL )
   {
      n = (*node).next;
      tree_remove( *current, node );
      node = n;
   }

   // delete cursor
   free( (**current).cursor );

   // dispose of mutex
   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete cable_utf8 struct
   free( *current );

   // set to NULL
   *current= NULL;
   
   return;
}

/**
   item
*/

static
char_t *
item( cable_utf8_t *current, int32_t index )
{
   char_t *result = NULL;
   char_t *cp = NULL;
   char_t *cp0 = NULL;
   char_t *cp_next = NULL;
   int32_t n = 0;

   // get the node with the character
   node_t *node = node_for_index( current, index );

   // allocate space for result
   result = calloc( CABLE_UTF8_CHAR_MAX_SIZE + 1, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   cp = &( (*node).str[ (*node).byte_start ] );
   cp0 = cp;
   
   while( ( (  cp0[0] & UTF8_N_MASK ) != UTF8_N_VALID ) && ( ( cp0[0] & UTF8_1_MASK ) != UTF8_1_VALID ) )
   {
      cp0++;
   }
   
   cp0 = ( char_t * ) utf8seek( cp0, (*node).byte_count, cp0, index - (*node).index, SEEK_SET );
   
   n = utf8_byte_count( cp0[0] );

   if ( ( cp0 - cp ) + n <= (*node).byte_count )
   {
      memcpy( result, cp0, n );
   }
   else if ( ( cp0 - cp ) + n - 1 == (*node).byte_count )
   {
      memcpy( result, cp0, n - 1 );
      cp_next = (*(*node).next).str;
      result[ n - 1 ] = cp_next[0];
   }
   else if ( ( cp0 - cp ) + n - 2 == (*node).byte_count )
   {
      memcpy( result, cp0, n - 2 );
      cp_next = (*(*node).next).str;
      result[ n - 2 ] = cp_next[0];
      result[ n - 1 ] = cp_next[1];
   }
   else if ( ( cp0 - cp ) + n - 3 == (*node).byte_count )
   {
      memcpy( result, cp0, n - 3 );
      cp_next = (*(*node).next).str;
      result[ n - 3 ] = cp_next[0];
      result[ n - 2 ] = cp_next[1];
      result[ n - 1 ] = cp_next[2];
   }

   return result;
}

/**
   cable_utf8_item
*/

char_t *
cable_utf8_item( cable_utf8_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "index ok", is_index_valid( current, index ) == 1 );
   INVARIANT( current );

   char_t *result = item( current, index );
   
   INVARIANT( current );

   return result;
}

/**
   cable_utf8_item_ascii
*/

char_t
cable_utf8_item_ascii( cable_utf8_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "index ok", is_index_valid( current, index ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t result = 0;
   char_t *cp = NULL;
   char_t *cp0 = NULL;

   // get the node with the character
   node_t *node = node_for_index( current, index );

   cp = &( (*node).str[ (*node).byte_start ] );
   cp0 = ( char_t * ) utf8seek( cp, (*node).byte_count, cp, index - (*node).index, SEEK_SET );

   result = cp0[0];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   POSTCONDITION( "result is ascii", ( result & UTF8_1_MASK ) == UTF8_1_VALID );

   return result;
}

/**
   cable_utf8_item_utf16
*/

utf16_t *
cable_utf8_item_utf16( cable_utf8_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "index ok", is_index_valid( current, index ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   utf16_t *result = NULL;
   char_t *cp = NULL;

   cp = item( current, index );
   result = utf8_to_utf16( cp );
   
   free( cp );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_item_utf32
*/

utf32_t
cable_utf8_item_utf32( cable_utf8_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "index ok", is_index_valid( current, index ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   utf32_t result = 0;
   char_t *cp = NULL;

   cp = item( current, index );

   result = utf8_to_utf32( cp );

   free( cp );
   
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_item_wchar
*/

wchar_t
cable_utf8_item_wchar( cable_utf8_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "index ok", is_index_valid( current, index ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   wchar_t result = 0;
   char_t *cp = NULL;

   cp = item( current, index );

   result = utf8_to_wchar( cp );

   free( cp );
   
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_as_cstring
*/

char_t *
cable_utf8_as_cstring( cable_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *result = NULL;
   char_t *cp = NULL;
   node_t *node;

   // allocate result
   result = ( char_t * ) calloc( (*current).str_byte_count + 1, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // walk through nodes, appending contents onto result
   node = (*current).first;

   while( node != NULL )
   {
      cp = node_as_cstring( node );
      strcat( result, cp );
      node = (*node).next;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_byte_count
*/

int32_t
cable_utf8_byte_count( cable_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = (*current).str_byte_count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_count
*/

int32_t
cable_utf8_count( cable_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = (*current).str_count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_capacity
*/

int32_t
cable_utf8_capacity( cable_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).str_length;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_is_empty
*/

int32_t
cable_utf8_is_empty( cable_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).str_byte_count ==  0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_valid_index
*/

int32_t
cable_utf8_valid_index( cable_utf8_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = is_index_valid( current, index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_has
*/
int32_t
cable_utf8_has( cable_utf8_t *current, char_t *c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "c not null", c != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t flag = 0;

   flag = substring_index_in_bounds_cstring( current, c, 0, (*current).str_count - 1 );

   if ( flag >= 0 )
   {
      result = 1;
   }
   
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_has_ascii
*/
int32_t
cable_utf8_has_ascii( cable_utf8_t *current, char_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "c is ASCII", ( c & UTF8_1_MASK ) == UTF8_1_VALID );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t index = 0;
   char_t s[CABLE_UTF8_CHAR_MAX_SIZE] = {0};

   s[0] = c;
   index = substring_index_in_bounds_cstring( current, s, 0, (*current).str_count - 1 );

   result = ( index >= 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_has_utf16
*/
int32_t
cable_utf8_has_utf16( cable_utf8_t *current, utf16_t *cp )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t index = 0;
   char_t *s = NULL;

   s = utf16_to_utf8( cp );
   index = substring_index_in_bounds_cstring( current, s, 0, (*current).str_count - 1 );
   free( s );

   result = ( index >= 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_has_utf32
*/
int32_t
cable_utf8_has_utf32( cable_utf8_t *current, utf32_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t index = 0;
   char_t *s = NULL;

   s = utf32_to_utf8( c );
   index = substring_index_in_bounds_cstring( current, s, 0, (*current).str_count - 1 );
   free( s );

   result = ( index >= 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_has_wchar
*/
int32_t
cable_utf8_has_wchar( cable_utf8_t *current, wchar_t c )
{
   PRECONDITION( "cable_utf8 not null", current != NULL );
   PRECONDITION( "cable_utf8 type OK", (*current)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t index = 0;
   char_t *s = NULL;

   s = wchar_to_utf8( c );
   index = substring_index_in_bounds_cstring( current, s, 0, (*current).str_count - 1 );
   free( s );

   result = ( index >= 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_hash_code
*/
int32_t
cable_utf8_hash_code( cable_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint32_t result = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   int32_t i = 0;

   // walk through nodes, compute hash code
   node = (*current).first;

   while( node != NULL )
   {
      // get string in node
      cp = node_as_cstring( node );

      // compute hash
      for ( i=0; i<(*node).byte_count; i++ )
      {
         result = ( ( result % HASH_PRIME_NUMBER ) << 8 ) + ( uint32_t ) cp[i];
      }

      // get next node
      node = (*node).next;

   }


   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return ( int32_t ) result;
}

/**
   cable_utf8_is_equal
*/
int32_t
cable_utf8_is_equal( cable_utf8_t *current, cable_utf8_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t i = 0;
   int32_t length = 0;
   node_t *node = NULL;
   node_t *node_other = NULL;
   char_t *cp = NULL;
   char_t *cp_other = NULL;
   int32_t index = 0;
   int32_t index_other = 0;
   int32_t count = 0;
   int32_t count_other = 0;
   char_t c = 0;
   char_t c_other = 0;

   // walk through nodes, comparing characters
   if ( (*current).str_byte_count != (*other).str_byte_count )
   {
      // if have different lengths, are not equal
      result = 0;
   }
   else
   {
      length = (*current).str_byte_count;

      // cable_utf8s are same length, compare each character
      node = (*current).first;
      cp = node_as_cstring( node );
      index = (*node).byte_index;
      count = (*node).byte_count;

      node_other = (*other).first;
      cp_other = node_as_cstring( node_other );
      index_other = (*node_other).byte_index;
      count_other = (*node_other).byte_count;

      result = 1;

      for ( i=0; i<length; i++ )
      {
         // get character in cable_utf8
         c = cp[ i - index ];

         // get character in other
         c_other = cp_other[ i - index_other ];

         // if not equal, we're done
         if ( c != c_other  )
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
               index = (*node).byte_index;
               count = (*node).byte_count;
            }
         }

         if ( ( i - index_other ) >= ( count_other - 1 ) )
         {
            node_other = (*node_other).next;
            if ( node_other != NULL )
            {
               cp_other = node_as_cstring( node_other );
               index_other = (*node_other).byte_index;
               count_other = (*node_other).byte_count;
            }
         }

      }
   }

   INVARIANT( current );
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_is_equal_cstring
*/
int32_t
cable_utf8_is_equal_cstring( cable_utf8_t *current, char_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t i = 0;
   int32_t length = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   int32_t index = 0;
   int32_t count = 0;
   char_t c = 0;
   char_t c_other = 0;

   length = strlen( other );

   // walk through nodes, comparing characters
   if ( (*current).str_byte_count != length )
   {
      // if have different lengths, are not equal
      result = 0;
   }
   else
   {
      // cable_utf8s are same length, compare each character
      node = (*current).first;
      cp = node_as_cstring( node );
      index = (*node).byte_index;
      count = (*node).byte_count;

      result = 1;

      for ( i=0; i<length; i++ )
      {
         // get character in cable_utf8
         c = cp[ i - index ];

         // get character in other
         c_other = other[ i ];

         // if not equal, we're done
         if ( c != c_other  )
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
               index = (*node).byte_index;
               count = (*node).byte_count;
            }
         }
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_is_less_than
*/
int32_t
cable_utf8_is_less_than( cable_utf8_t *current, cable_utf8_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t i = 0;
   int32_t n = 0;
   int32_t length = 0;
   int32_t length_other = 0;
   node_t *node = NULL;
   node_t *node_other = NULL;
   char_t *cp = NULL;
   char_t *cp_other = NULL;
   int32_t index = 0;
   int32_t index_other = 0;
   int32_t count = 0;
   int32_t count_other = 0;
   char_t c = 0;
   char_t c_other = 0;

   // get lengths, min length
   length = (*current).str_byte_count;
   length_other = (*other).str_byte_count;
   n = length;
   if ( length_other < n )
   {
      n = length_other;
   }

   // cable_utf8s are same length, compare each character
   node = (*current).first;
   cp = node_as_cstring( node );
   index = (*node).byte_index;
   count = (*node).byte_count;

   node_other = (*other).first;
   cp_other = node_as_cstring( node_other );
   index_other = (*node_other).byte_index;
   count_other = (*node_other).byte_count;

   result = 0;

   for ( i=0; i<n; i++ )
   {
      // get character in cable_utf8
      c = cp[ i - index ];

      // get character in other
      c_other = cp_other[ i - index_other ];

      // if greater than, we're done
      if ( c > c_other  )
      {
         result = 0;
         break;
      }

      // if less than, we're done
      if ( c < c_other  )
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
            index = (*node).byte_index;
            count = (*node).byte_count;
         }
      }

      if ( ( i - index_other ) >= ( count_other - 1 ) )
      {
         node_other = (*node_other).next;
         if ( node_other != NULL )
         {
            cp_other = node_as_cstring( node_other );
            index_other = (*node_other).byte_index;
            count_other = (*node_other).byte_count;
         }
      }

   }

   // if we get to here, then all compared characters are equal, see if cable_utf8 is
   // shorter than other
   if ( length < length_other )
   {
      result = 1;
   }

   // otherwise result is false (0), equal or greater than

   INVARIANT( current );
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_is_less_than_cstring
*/
int32_t
cable_utf8_is_less_than_cstring( cable_utf8_t *current, char_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t i = 0;
   int32_t n = 0;
   int32_t length = 0;
   int32_t length_other = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   int32_t index = 0;
   int32_t count = 0;
   char_t c = 0;
   char_t c_other = 0;

   // get lengths, min length
   length = (*current).str_byte_count;
   length_other = strlen( other );
   n = length;
   if ( length_other < n )
   {
      n = length_other;
   }

   // cable_utf8s are same length, compare each character
   node = (*current).first;
   cp = node_as_cstring( node );
   index = (*node).byte_index;
   count = (*node).byte_count;

   result = 0;

   for ( i=0; i<n; i++ )
   {
      // get character in cable_utf8
      c = cp[ i - index ];

      // get character in other
      c_other = other[ i ];

      // if greater than, we're done
      if ( c > c_other  )
      {
         result = 0;
         break;
      }

      // if less than, we're done
      if ( c < c_other  )
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
            index = (*node).byte_index;
            count = (*node).byte_count;
         }
      }

   }

   // if we get to here, then all compared characters are equal, see if cable_utf8 is
   // shorter than other
   if ( length < length_other )
   {
      result = 1;
   }

   // otherwise result is false (0), equal or greater than

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_is_greater_than
*/
int32_t
cable_utf8_is_greater_than( cable_utf8_t *current, cable_utf8_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t i = 0;
   int32_t n = 0;
   int32_t length = 0;
   int32_t length_other = 0;
   node_t *node = NULL;
   node_t *node_other = NULL;
   char_t *cp = NULL;
   char_t *cp_other = NULL;
   int32_t index = 0;
   int32_t index_other = 0;
   int32_t count = 0;
   int32_t count_other = 0;
   char_t c = 0;
   char_t c_other = 0;

   // get lengths, min length
   length = (*current).str_byte_count;
   length_other = (*other).str_byte_count;
   n = length;
   if ( length_other < n )
   {
      n = length_other;
   }

   // cable_utf8s are same length, compare each character
   node = (*current).first;
   cp = node_as_cstring( node );
   index = (*node).byte_index;
   count = (*node).byte_count;

   node_other = (*other).first;
   cp_other = node_as_cstring( node_other );
   index_other = (*node_other).byte_index;
   count_other = (*node_other).byte_count;

   result = 0;

   for ( i=0; i<n; i++ )
   {
      // get character in cable_utf8
      c = cp[ i - index ];

      // get character in other
      c_other = cp_other[ i - index_other ];

      // if less than, we're done
      if ( c < c_other  )
      {
         result = 0;
         break;
      }

      // if greater than, we're done
      if ( c > c_other  )
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
            index = (*node).byte_index;
            count = (*node).byte_count;
         }
      }

      if ( ( i - index_other ) >= ( count_other - 1 ) )
      {
         node_other = (*node_other).next;
         if ( node_other != NULL )
         {
            cp_other = node_as_cstring( node_other );
            index_other = (*node_other).byte_index;
            count_other = (*node_other).byte_count;
         }
      }

   }

   // if we get to here, then all compared characters are equal, see if other is
   // longer than cable_utf8
   if ( length > length_other )
   {
      result = 1;
   }

   // otherwise result is false (0), equal or less than

   INVARIANT( current );
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_is_greater_than_cstring
*/
int32_t
cable_utf8_is_greater_than_cstring( cable_utf8_t *current, char_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t i = 0;
   int32_t n = 0;
   int32_t length = 0;
   int32_t length_other = 0;
   node_t *node = NULL;
   char_t *cp = NULL;
   int32_t index = 0;
   int32_t count = 0;
   char_t c = 0;
   char_t c_other = 0;

   // get lengths, min length
   length = (*current).str_byte_count;
   length_other = strlen( other );
   n = length;
   if ( length_other < n )
   {
      n = length_other;
   }

   // cable_utf8s are same length, compare each character
   node = (*current).first;
   cp = node_as_cstring( node );
   index = (*node).byte_index;
   count = (*node).byte_count;

   result = 0;

   for ( i=0; i<n; i++ )
   {
      // get character in cable_utf8
      c = cp[ i - index ];

      // get character in other
      c_other = other[ i ];

      // if less than, we're done
      if ( c < c_other  )
      {
         result = 0;
         break;
      }

      // if greater than, we're done
      if ( c > c_other  )
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
            index = (*node).byte_index;
            count = (*node).byte_count;
         }
      }

   }

   // if we get to here, then all compared characters are equal, see if other is
   // longer than cable_utf8
   if ( length > length_other )
   {
      result = 1;
   }

   // otherwise result is false (0), equal or less than

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_has_substring
*/
int32_t
cable_utf8_has_substring( cable_utf8_t *current, cable_utf8_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = substring_index_in_bounds( current, other, 0, (*current).str_count - 1 );

   if ( result >= 0 )
   {
      result = 1;
   }
   else
   {
      result = 0;
   }

   INVARIANT( current );
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_has_substring_cstring
*/
int32_t
cable_utf8_has_substring_cstring( cable_utf8_t *current, char_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = substring_index_in_bounds_cstring( current, other, 0, (*current).str_count - 1 );

   if ( result >= 0 )
   {
      result = 1;
   }
   else
   {
      result = 0;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_starts_with
*/
int32_t
cable_utf8_starts_with( cable_utf8_t *current, cable_utf8_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = substring_index_in_bounds( current, other, 0, (*other).str_count - 1 );

   if ( result == 0 )
   {
      result = 1;
   }
   else
   {
      result = 0;
   }

   INVARIANT( current );
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_starts_with_cstring
*/
int32_t
cable_utf8_starts_with_cstring( cable_utf8_t *current, char_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t other_count = 0;

   other_count = utf8len( other );
   result = substring_index_in_bounds_cstring( current, other, 0, other_count - 1 );

   if ( result == 0 )
   {
      result = 1;
   }
   else
   {
      result = 0;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_ends_with
*/
int32_t
cable_utf8_ends_with( cable_utf8_t *current, cable_utf8_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );
   INVARIANT( other );

   int32_t result = 0;

   result = substring_index_in_bounds( current, other, (*current).str_count - (*other).str_count, (*current).str_count - 1 );

   if ( result == (*current).str_count - (*other).str_count )
   {
      result = 1;
   }
   else
   {
      result = 0;
   }

   INVARIANT( current );
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_ends_with_cstring
*/
int32_t
cable_utf8_ends_with_cstring( cable_utf8_t *current, char_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t n = 0;

   n = utf8len( other );

   result
      =  substring_index_in_bounds_cstring
         (
            current,
            other,
            (*current).str_count - n,
            (*current).str_count - 1
         );

   if ( result == (*current).str_count - n )
   {
      result = 1;
   }
   else
   {
      result = 0;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_substring_index
*/
int32_t
cable_utf8_substring_index
(
   cable_utf8_t *current,
   cable_utf8_t *other
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = substring_index_in_bounds( current, other, 0, (*current).str_count - 1 );

   INVARIANT( current );
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_substring_index_cstring
*/
int32_t
cable_utf8_substring_index_cstring
(
   cable_utf8_t *current,
   char_t *other
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = substring_index_in_bounds_cstring( current, other, 0, (*current).str_count - 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_substring_index_in_bounds
*/
int32_t
cable_utf8_substring_index_in_bounds
(
   cable_utf8_t *current,
   cable_utf8_t *other,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "start_index ok", is_index_valid( current, start_index ) == 1 );
   PRECONDITION( "end_index ok", is_index_valid( current, end_index ) == 1 );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = substring_index_in_bounds( current, other, start_index, end_index );

   INVARIANT( current );
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_substring_index_in_bounds_cstring
*/
int32_t
cable_utf8_substring_index_in_bounds_cstring
(
   cable_utf8_t *current,
   char_t *other,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "start_index ok", is_index_valid( current, start_index ) == 1 );
   PRECONDITION( "end_index ok", is_index_valid( current, end_index ) == 1 );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = substring_index_in_bounds_cstring( current, other, start_index, end_index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

#define DEFAULT_SPLIT_RETURN_ARRAY_SIZE 8

/**
   cable_utf8_split
*/
cable_utf8_t **
cable_utf8_split( cable_utf8_t *current, char_t *separators, int32_t *result_count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "separators not null", separators != NULL );
   PRECONDITION( "result_count not null", result_count != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cable_utf8_t **result = NULL;
   cable_utf8_t *x = NULL;
   int32_t i = 0;
   int32_t n = 0;
   int32_t index = 0;
   int32_t start_index = 0;
   int32_t end_index = 0;
   int32_t flag = 0;
   int32_t size = DEFAULT_SPLIT_RETURN_ARRAY_SIZE;
   int32_t seps_size = DEFAULT_SPLIT_RETURN_ARRAY_SIZE;
   int32_t n_seps = 0;
   char_t **seps = NULL;
   int32_t i_result = 0;
   char_t *cp0 = NULL;
   char_t *cp1= NULL;

   // prepare result array
   result = ( cable_utf8_t ** ) calloc( size, sizeof( cable_utf8_t * ) );
   CHECK( "result allocated correctly", result != NULL );
   
   (*result_count) = 0;

   // allocate separators array
   seps = ( char_t ** ) calloc( seps_size, sizeof( char_t * ) );
   CHECK( "seps allocated correctly", seps != NULL );

   // allocate and fill separators array

   // get separators
   cp0 = separators;
   cp1 = ( char_t * ) utf8seek( cp0, strlen( separators ), separators, 1, SEEK_CUR);
   n = cp1 - cp0;
   seps[0] = ( char_t * ) calloc( n + 1, sizeof( char_t ) );
   CHECK( "seps[0] allocated correctly", seps[0] != NULL );
   
   memcpy( seps[0], cp0, n );

   i = 1;
   n_seps = 1;
   while( flag == 0 )
   {
      cp0 = cp1;
      cp1 = ( char_t * ) utf8seek( cp0, strlen( separators ), separators, 1, SEEK_CUR);

      if ( cp1 > cp0 )
      {
         n = cp1 - cp0;
         if ( i < seps_size - 1 )
         {
            seps[i] = ( char_t * ) calloc( n + 1, sizeof( char_t ) );
            CHECK( "seps[i] allocated correctly", seps[i] != NULL );
            
            memcpy( seps[i], cp0, n );
            i = i + 1;
            n_seps = n_seps + 1;
         }
         else
         {

            seps = ( char_t ** ) realloc( seps, 2*seps_size*sizeof( char_t * ) );
            CHECK( "seps allocated correctly", seps != NULL );
            
            memset( seps + size, 0, sizeof( char_t * )*seps_size );
            seps_size = 2*seps_size;
            seps[i] = ( char_t * ) calloc( n + 1, sizeof( char_t ) );
            CHECK( "seps[i] allocated correctly", seps[i] != NULL );
            
            memcpy( seps[i], cp0, n );
            i = i + 1;
            n_seps = n_seps + 1;
         }
      }
      else
      {
         flag = 1;
      }
   }

   // look for next separator
   start_index = 0;
   flag = 0;

   while ( flag == 0 )
   {
      // initialize end index for search
      end_index = (*current).str_count + 1;

      // loop for next separator
      for ( i=0; i<n_seps; i++ )
      {
         index = substring_index_in_bounds_cstring( current, seps[i], start_index, (*current).str_count - 1 );
         if ( index >= 0 )
         {
            // found the separator, is it the earliest one from start_index?
            if ( index < end_index )
            {
               // set end index
               end_index = index;
            }
         }
      }

      // see if we found a separator
      if ( end_index < (*current).str_count )
      {
         // adjust to not include separator
         end_index = end_index - 1;

         // we did, get subcable
         x = subcable_utf8_from_bounds( current, start_index, end_index );

         // put the new cable_utf8 into the return array
         if ( i_result < ( size - 1 ) )
         {
            result[i_result] = x;
            i_result = i_result + 1;
         }
          // resize the result array if necessary
         else
          {
            result = ( cable_utf8_t ** ) realloc( result, 2*size*sizeof( cable_utf8_t * ) );
            CHECK( "result allocated correctly", result != NULL );
            
            memset( &result[size], 0, size*sizeof( cable_utf8_t * ) );
            size = 2*size;
            result[i_result] = x;
            i_result = i_result + 1;
         }

         // prepare for next separator search
         start_index = end_index + 2;

         // if we're past the end of the string, set flag
         if ( start_index >= (*current).str_count )
         {
            flag = 1;
         }

         // special case where separator is last character in string,
         // put empty string as last entry in result
         if ( start_index == (*current).str_count )
         {
            x = cable_utf8_make_capacity( (*current).str_length );

            // put the new cable_utf8 into the return array
            if ( i_result < ( size - 1 ) )
            {
               result[i_result] = x;
               i_result = i_result + 1;
            }
            // resize the result array if necessary
            else
            {
               result = ( cable_utf8_t ** ) realloc( result, 2*size*sizeof( cable_utf8_t * ) );
               CHECK( "result allocated correctly", result != NULL );
               
               memset( &result[size], 0, size*sizeof( cable_utf8_t * ) );
               size = 2*size;
               result[i_result] = x;
               i_result = i_result + 1;
            }
         }

      }
      else
      {
         // no more separators
         flag = 1;

         // put last subcable into result
         if ( start_index < (*current).str_count )
         {
            // get (last) subcable
            x = subcable_utf8_from_bounds( current, start_index, (*current).str_count - 1 );

            // put the new cable_utf8 into the return array
            if ( i_result < ( size - 1 ) )
            {
               result[i_result] = x;
               i_result = i_result + 1;
            }
            // resize the result array if necessary
            else
            {
               result = ( cable_utf8_t ** ) realloc( result, 2*size*sizeof( cable_utf8_t * ) );
               CHECK( "result allocated correctly", result != NULL );
               
               memset( &result[size], 0, size*sizeof( cable_utf8_t * ) );
               size = 2*size;
               result[i_result] = x;
               i_result = i_result + 1;
            }

         }
      }
   }

   // free separator temps
   for ( i=0; i<n_seps; i++ )
   {
      free( seps[i] );
   }
   free( seps );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   // set count of result array and return array
   (*result_count) = i_result;

   return result;
}

/**
   cable_utf8_as_lower
*/
cable_utf8_t *
cable_utf8_as_lower
(
   cable_utf8_t *current,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "start_index ok", is_index_valid( current, start_index ) == 1 );
   PRECONDITION( "end_index ok", is_index_valid( current, end_index ) == 1 );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cable_utf8_t *result = NULL;

   result = subcable_utf8_from_bounds( current, start_index, end_index );

   to_lower( result );

   redo_indices( result );
   
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_as_upper
*/
cable_utf8_t *
cable_utf8_as_upper
(
   cable_utf8_t *current,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "start_index ok", is_index_valid( current, start_index ) == 1 );
   PRECONDITION( "end_index ok", is_index_valid( current, end_index ) == 1 );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cable_utf8_t *result = NULL;

   result = subcable_utf8_from_bounds( current, start_index, end_index );

   to_upper( result );

   redo_indices( result );
   
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_put
*/

void
cable_utf8_put( cable_utf8_t *current, char_t *c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "c not null", c != NULL );
   PRECONDITION( "index ok", is_index_valid( current, index ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *cp = NULL;
   int32_t cable_size = 0;
   int32_t c_size = 0;

   cp = item( current, index );
   cable_size = utf8_byte_count( cp[0] );
   c_size = utf8_byte_count( c[0] );

   if ( cable_size == c_size )
   {
      replace_at_index_cstring( current, c, index );
   }
   else
   {
      remove_from_bounds( current, index, index );
      insert_at_index( current, index, c_size );
      replace_at_index_cstring( current, c, index );
   }

   // delete temp buffer
   free( cp );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_put_ascii
*/

void
cable_utf8_put_ascii( cable_utf8_t *current, char_t c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "index ok", is_index_valid( current, index ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *cp = NULL;
   char_t c_cp[CABLE_UTF8_CHAR_MAX_SIZE + 1] = {0};
   int32_t cable_size = 0;
   int32_t c_size = 0;

   cp = item( current, index );
   cable_size = utf8_byte_count( cp[0] );
   c_cp[0] = c;
   c_size = 1;

   if ( cable_size == c_size )
   {
      replace_at_index_cstring( current, c_cp, index );
   }
   else
   {
      remove_from_bounds( current, index, index );
      insert_at_index( current, index, c_size );
      replace_at_index_cstring( current, c_cp, index );
   }

   // delete temp buffer
   free( cp );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_put_utf16
*/

void
cable_utf8_put_utf16( cable_utf8_t *current, utf16_t *cp, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "index ok", is_index_valid( current, index ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *cp_item = NULL;
   char_t *c_cp;
   int32_t cable_size = 0;
   int32_t c_size = 0;

   // get utf8 pointer to current index
   cp_item = item( current, index );
   cable_size = utf8_byte_count( cp_item[0] );
   
   // get input utf16 character as utf8 with count of bytes
   c_cp = utf16_to_utf8( cp );
   c_size = utf8_byte_count( c_cp[0] );

   if ( cable_size == c_size )
   {
      replace_at_index_cstring( current, c_cp, index );
   }
   else
   {
      remove_from_bounds( current, index, index );
      insert_at_index( current, index, c_size );
      replace_at_index_cstring( current, c_cp, index );
   }

   // delete temp buffers
   free( cp_item );
   free( c_cp );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_put_utf32
*/

void
cable_utf8_put_utf32( cable_utf8_t *current, utf32_t c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "index ok", is_index_valid( current, index ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *cp = NULL;
   char_t *c_cp;
   int32_t cable_size = 0;
   int32_t c_size = 0;

   // get utf8 pointer to current index
   cp = item( current, index );
   cable_size = utf8_byte_count( cp[0] );
   
   // get input utf32 character as utf8 with count of bytes
   c_cp = utf32_to_utf8( c );
   c_size = utf8_byte_count( c_cp[0] );

   if ( cable_size == c_size )
   {
      replace_at_index_cstring( current, c_cp, index );
   }
   else
   {
      remove_from_bounds( current, index, index );
      insert_at_index( current, index, c_size );
      replace_at_index_cstring( current, c_cp, index );
   }

   // delete temp buffers
   free( cp );
   free( c_cp );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_put_wchar
*/

void
cable_utf8_put_wchar( cable_utf8_t *current, wchar_t c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "index ok", is_index_valid( current, index ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *cp = NULL;
   char_t *c_cp;
   int32_t cable_size = 0;
   int32_t c_size = 0;

   // get utf8 pointer to current index
   cp = item( current, index );
   cable_size = utf8_byte_count( cp[0] );
   
   // get input wchar character as utf8 with count of bytes
   c_cp = wchar_to_utf8( c );
   c_size = utf8_byte_count( c_cp[0] );

   if ( cable_size == c_size )
   {
      replace_at_index_cstring( current, c_cp, index );
   }
   else
   {
      remove_from_bounds( current, index, index );
      insert_at_index( current, index, c_size );
      replace_at_index_cstring( current, c_cp, index );
   }

   // delete temp buffers
   free( cp );
   free( c_cp );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_replace
*/

void
cable_utf8_replace
(
   cable_utf8_t *current,
   cable_utf8_t *other,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other type OK", (*other)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "start_index ok", is_index_valid( current, start_index ) == 1 );
   PRECONDITION( "end_index ok", is_index_valid( current, end_index ) == 1 );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );
   INVARIANT( other );

   int32_t length = 0;
   int32_t delta = 0;

   // get length of area to replace
   length = byte_index_for_index( current, end_index ) - byte_index_for_index( current, start_index ) + 1;

   // get difference between length and size of other
   delta = length - (*other).str_byte_count;

   if ( delta == 0 )
   {
      // cable_utf8s are same length
      // copy over existing chars in cable_utf8 with chars from other
      replace_at_index( current, other, start_index );
   }
   else if ( delta < 0 )
   {
      // other is longer than end_index - start_index
      // insert space in cable_utf8
      insert_at_index( current, start_index, -delta );

      // copy over existing chars in cable_utf8 with chars from other
      replace_at_index( current, other, start_index );
   }
   else // delta > 0
   {
      // other is shorter than end_index - start_index
      // remove space in cable_utf8
      remove_from_bounds( current, start_index, end_index );

      // insert space in cable_utf8
      insert_at_index( current, start_index, (*other).str_byte_count );

      // copy over existing chars in cable_utf8 with chars from other
      replace_at_index( current, other, start_index );
   }

   (*current).str_count_valid = 0;
   redo_indices( current );

   INVARIANT( current );
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_replace_cstring
*/

void
cable_utf8_replace_cstring
(
   cable_utf8_t *current,
   char_t *other,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "start_index ok", is_index_valid( current, start_index ) == 1 );
   PRECONDITION( "end_index ok", is_index_valid( current, end_index ) == 1 );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t length = 0;
   int32_t delta = 0;

   // get length of area to replace
   length = byte_index_for_index( current, end_index ) - byte_index_for_index( current, start_index ) + 1;

   // get difference between length and size of other
   delta = length - strlen( other );

   if ( delta == 0 )
   {
      // cable_utf8s are same length
      // copy over existing chars in cable_utf8 with chars from other
      replace_at_index_cstring( current, other, start_index );
   }
   else if ( delta < 0 )
   {
      // other is longer than end_index - start_index
      // insert space in cable_utf8
      insert_at_index( current, start_index, -delta );

      // copy over existing chars in cable_utf8 with chars from other
      replace_at_index_cstring( current, other, start_index );
   }
   else // delta > 0
   {
      // other is shorter than end_index - start_index
      // remove space in cable_utf8
      remove_from_bounds( current, start_index, end_index );

      // insert space in cable_utf8
      insert_at_index( current, start_index, strlen( other ) );

      // copy over existing chars in cable_utf8 with chars from other
      replace_at_index_cstring( current, other, start_index );
   }

   (*current).str_count_valid = 0;
   redo_indices( current );
   
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_replace_all
*/

void
cable_utf8_replace_all
(
   cable_utf8_t *current,
   cable_utf8_t *substring_original,
   cable_utf8_t *substring_new
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "substring_original not null", substring_original != NULL );
   PRECONDITION( "substring_original type OK", (*substring_original)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "substring_new not null", substring_new != NULL );
   PRECONDITION( "substring_new type OK", (*substring_new)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   LOCK( (*substring_original).mutex );
   LOCK( (*substring_new).mutex );
   INVARIANT( current );
   INVARIANT( substring_original );
   INVARIANT( substring_new );

   int32_t i = 0;
   int32_t start_index = 0;
   int32_t end_index = 0;
   int32_t length = 0;
   int32_t delta = 0;

   // work our way through cable_utf8 finding instances of substring_original and
   // replacing them with substring_new

   while ( ( i >= 0 ) && ( i < (*current).str_count ) )
   {
      i = substring_index_in_bounds( current, substring_original, i, (*current).str_count - 1 );

      // see if we found substring_original
      if ( i >= 0 )
      {
         // we found it, replace it with substring_new
         start_index = i;
         end_index = i + (*substring_original).str_count - 1;

         // get length of area to replace
         length = byte_index_for_index( current, end_index ) - byte_index_for_index( current, start_index ) + 1;

         // get difference between length and size of substring_new
         delta = length - (*substring_new).str_byte_count;

         if ( delta == 0 )
         {
            // cable_utf8s are same length
            // copy over existing chars in cable_utf8 with chars from substring_new
            replace_at_index( current, substring_new, start_index );
         }
         else if ( delta < 0 )
         {
            // substring_new is longer than end_index - start_index
            // insert space in cable_utf8
            insert_at_index( current, start_index, -delta );

            // copy over existing chars in cable_utf8 with chars from other
            replace_at_index( current, substring_new, start_index );
         }
         else // delta > 0
         {
            // other is shorter than end_index - start_index
            // remove space in cable_utf8
            remove_from_bounds( current, start_index, end_index );

            // insert space in cable_utf8
            insert_at_index( current, start_index, (*substring_new).str_byte_count );

            // copy over existing chars in cable_utf8 with chars from other
            replace_at_index( current, substring_new, start_index );
         }

         // update indices
         redo_indices( current );

         // update i
         i = start_index + (*substring_new).str_count;
      }

   }

   INVARIANT( current );
   UNLOCK( (*substring_new).mutex );
   UNLOCK( (*substring_original).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_replace_all_cstring
*/

void
cable_utf8_replace_all_cstring
(
   cable_utf8_t *current,
   char_t *substring_original,
   char_t *substring_new
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "substring_original not null", substring_original != NULL );
   PRECONDITION( "substring_new not null", substring_new != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t start_index = 0;
   int32_t end_index = 0;
   int32_t length = 0;
   int32_t delta = 0;
   int32_t substring_original_count = 0;
   int32_t substring_new_count = 0;
   int32_t substring_new_length = 0;

   substring_original_count = utf8len( substring_original );

   substring_new_count = utf8len( substring_new );
   substring_new_length = strlen( substring_new );

   // work our way through cable_utf8 finding instances of substring_original and
   // replacing them with substring_new

   while ( ( i >= 0 ) && ( i < (*current).str_count ) )
   {
      i = substring_index_in_bounds_cstring( current, substring_original, i, (*current).str_count - 1 );

      // see if we found substring_original
      if ( i >= 0 )
      {
         // we found it, replace it with substring_new
         start_index = i;
         end_index = i + substring_original_count - 1;

         // get length of area to replace
         length = byte_index_for_index( current, end_index ) - byte_index_for_index( current, start_index ) + 1;

         // get difference between length and size of substring_new
         delta = length - substring_new_length;

         if ( delta == 0 )
         {
            // cable_utf8s are same length
            // copy over existing chars in cable_utf8 with chars from substring_new
            replace_at_index_cstring( current, substring_new, start_index );
         }
         else if ( delta < 0 )
         {
            // substring_new is longer than end_index - start_index
            // insert space in cable_utf8
            insert_at_index( current, start_index, -delta );

            // copy over existing chars in cable_utf8 with chars from other
            replace_at_index_cstring( current, substring_new, start_index );
         }
         else // delta > 0
         {
            // other is shorter than end_index - start_index
            // remove space in cable_utf8
            remove_from_bounds( current, start_index, end_index );

            // insert space in cable_utf8
            insert_at_index( current, start_index, substring_new_length );

            // copy over existing chars in cable_utf8 with chars from other
            replace_at_index_cstring( current, substring_new, start_index );
         }

         // update i
         i = start_index + substring_new_count;
      }

      redo_indices( current );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_append
*/

void
cable_utf8_append( cable_utf8_t *current, cable_utf8_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "cable_utf8 and other same node string length", (*current).str_length == (*other).str_length );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   node_t *node = NULL;
   node_t *n = NULL;
   cable_utf8_cursor_t *cursor = NULL;
   node_t *last = NULL;

   // make copy of nodes in other, append to cable_utf8
   cursor = (*current).cursor;
   n = (*other).first;

   while( n != NULL )
   {
      // make new node
      node = node_make_from( current, n );

      // get next node in other
      n = (*n).next;

      // set index, next, prev
      (*node).index = (*current).str_byte_count;
      cursor_finish( cursor );
      last = cursor_item( cursor );
      (*last).next = node;
      (*node).prev = last;

      redo_byte_indices( current );

      // put new node into cable_utf8
      tree_put( current, node );

   }

   (*current).str_count_valid = 0;
   redo_indices( current );
   
   INVARIANT( current );
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_append_destructive
*/

void
cable_utf8_append_destructive( cable_utf8_t *current, cable_utf8_t **other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (**other)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "cable_utf8 and other same node string length", (*current).str_length == (**other).str_length );
   LOCK( (*current).mutex );
   LOCK( (**other).mutex );
   INVARIANT( current );

   node_t *n = NULL;
   cable_utf8_cursor_t *cursor = NULL;
   node_t *last = NULL;

   // append other's nodes to cable_utf8
   cursor = (*current).cursor;
   n = (**other).first;

   while( n != NULL )
   {
      // set index, next, prev
      (*n).index = (*current).str_byte_count;
      cursor_finish( cursor );
      last = cursor_item( cursor );
      (*last).next = n;
      (*n).prev = last;

      redo_byte_indices( current );

      // put new node into cable_utf8
      tree_put( current, n );

      // get next node in other
      n = (*n).next;

   }

   // destroy other
   free( (**other).cursor );
   free( (*other) );
   (*other) = NULL;

   (*current).str_count_valid = 0;
   redo_indices( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_append_cstring
*/

void
cable_utf8_append_cstring( cable_utf8_t *current, char_t *other_cstring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other_cstring not null", other_cstring != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cable_utf8_t *other = NULL;
   node_t *node = NULL;
   node_t *n = NULL;
   cable_utf8_cursor_t *cursor = NULL;
   node_t *last = NULL;

   // turn other_cstring into cable_utf8
   other = cable_utf8_make_capacity_from_cstring( other_cstring, (*current).str_length );

   // get first node in other
   n = (*other).first;

   // dispose of other except for its nodes
   free( (*other).cursor );
   free( other );

   // get cursor for cable_utf8
   cursor = (*current).cursor;

   while( n != NULL )
   {
      // get node from other
      node = n;

      // get next node in other
      n = (*n).next;

      // set index, next, prev
      (*node).index = (*current).str_byte_count;
      cursor_finish( cursor );
      last = cursor_item( cursor );
      (*last).next = node;
      (*node).prev = last;
      (*node).next = NULL;

      redo_byte_indices( current );

      // put new node into cable_utf8
      tree_put( current, node );

   }

   (*current).str_count_valid = 0;
   redo_indices( current );
   
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_prepend
*/

void
cable_utf8_prepend( cable_utf8_t *current, cable_utf8_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "cable_utf8 and other same node string length", (*current).str_length == (*other).str_length );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   node_t *node = NULL;
   node_t *n = NULL;
   node_t *first = NULL;
   cable_utf8_cursor_t *cursor = NULL;

   // make copy of nodes in other, append to cable_utf8
   cursor = (*other).cursor;
   cursor_finish( cursor );

   // get last node in other
   n = cursor_item( cursor );

   while( n != NULL )
   {
      // make new node
      node = node_make_from( current, n );

      // get prev node in other
      n = (*n).prev;

      // get first node in cable_utf8
      first = (*current).first;

      // set index, next, prev
      (*node).byte_index = 0;
      (*node).next = first;
      (*node).prev = NULL;
      (*first).prev = node;

      // put new node into cable_utf8
      (*current).first = node;

      redo_byte_indices( current );

      tree_put( current, node );

   }

   (*current).str_count_valid = 0;
   redo_indices( current );
   
   INVARIANT( current );
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_prepend_destructive
*/

void
cable_utf8_prepend_destructive( cable_utf8_t *current, cable_utf8_t **other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (**other)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "cable_utf8 and other same node string length", (*current).str_length == (**other).str_length );
   LOCK( (*current).mutex );
   LOCK( (**other).mutex );
   INVARIANT( current );

   node_t *n = NULL;
   node_t *first = NULL;
   cable_utf8_cursor_t *cursor = NULL;

   // make copy of nodes in other, append to cable_utf8
   cursor = (**other).cursor;
   cursor_finish( cursor );

   // get last node in other
   n = cursor_item( cursor );

   while( n != NULL )
   {
      // get first node in cable_utf8
      first = (*current).first;

      // set index, next, prev
      (*n).byte_index = 0;
      (*n).next = first;
      (*n).prev = NULL;
      (*first).prev = n;

      // put new node into cable_utf8
      (*current).first = n;

      redo_byte_indices( current );

      tree_put( current, n );

      // get prev node in other
      n = (*n).prev;

   }

   // destroy other
   free( (**other).cursor );
   free( (*other) );
   (*other) = NULL;

   (*current).str_count_valid = 0;
   redo_indices( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_prepend_cstring
*/

void
cable_utf8_prepend_cstring( cable_utf8_t *current, char_t *other_cstring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other_cstring not null", other_cstring != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cable_utf8_t *other = NULL;
   node_t *node = NULL;
   node_t *n = NULL;
   cable_utf8_cursor_t *cursor = NULL;
   node_t *first = NULL;

   // turn other_cstring into cable_utf8
   other = cable_utf8_make_capacity_from_cstring( other_cstring, (*current).str_length );

   // get last node in other
   cursor = (*other).cursor;
   cursor_finish( cursor );
   n = cursor_item( cursor );
   cursor = NULL;

   // dispose of other except for its nodes
   free( (*other).cursor );
   free( other );

   // get cursor for cable_utf8
   cursor = (*current).cursor;

   while( n != NULL )
   {
      // get node from other
      node = n;

      // get next node in other
      n = (*n).prev;

      // get first node in cable_utf8
      first = (*current).first;

      // set index, next, prev
      (*node).byte_index = 0;
      (*node).next = first;
      (*node).prev = NULL;
      (*first).prev = node;

      // put new node into cable_utf8
      (*current).first = node;

      redo_byte_indices( current );

      tree_put( current, node );

   }

   (*current).str_count_valid = 0;
   redo_indices( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_insert
*/

void
cable_utf8_insert( cable_utf8_t *current, cable_utf8_t *other, int32_t start_index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "start_index ok", ( is_index_valid( current, start_index ) == 1 ) || ( start_index == (*current).str_count ) );
   PRECONDITION( "cable_utf8 and other same node string length", (*current).str_length == (*other).str_length );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );
   INVARIANT( other );

   // insert space for other in cable_utf8
   insert_at_index( current, start_index, (*other).str_byte_count );

   // put other into cable_utf8
   replace_at_index( current, other, start_index );

   INVARIANT( current );
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_insert_destructive
*/

void
cable_utf8_insert_destructive( cable_utf8_t *current, cable_utf8_t **other, int32_t start_index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (**other)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "start_index ok", ( is_index_valid( current, start_index ) == 1 ) || ( start_index == (*current).str_count ) );
   PRECONDITION( "cable_utf8 and other same node string length", (*current).str_length == (**other).str_length );
   LOCK( (*current).mutex );
   LOCK( (**other).mutex );
   INVARIANT( current );
   INVARIANT( *other );

   node_t *n = NULL;
   node_t *n1 = NULL;
   node_t *n2 = NULL;
   node_t *nx = NULL;
   node_t *first = NULL;
   node_t *last = NULL;
   cable_utf8_cursor_t *cursor = NULL;
   int32_t start_index_byte = 0;
   char_t *cp = NULL;
   int32_t i = 0;

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
         // get first node in cable_utf8
         first = (*current).first;

         // set index, next, prev
         (*n).index = 0;
         (*n).next = first;
         (*n).prev = NULL;
         (*first).prev = n;

         // put new node into cable_utf8
         (*current).first = n;

         redo_byte_indices( current );

         tree_put( current, n );

         // get prev node in other
         n = (*n).prev;

      }

   }
   else if ( start_index == (*current).str_count )
   {
      // like an append
      // append other's nodes to cable_utf8
      cursor = (*current).cursor;
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

         redo_byte_indices( current );

         // put new node into cable_utf8
         tree_put( current, n );

         // get next node in other
         n = n1;

      }
   }
   else
   {
      // somewhere in between
      n1 = node_for_index( current, start_index );
      if ( (*n1).index == start_index )
      {
         // don't need to split node
         n2 = n1;
         n1 = (*n2).prev;
      }
      else
      {
         // need to split node at start_index
         n2 = node_make( current );
         (*n2).next = (*n1).next;
         (*n2).prev = n1;
         (*n1).next = n2;
         if ( (*n2).next != NULL )
         {
            (*(*n2).next).prev = n2;
         }

         // copy string contents from start_index to n2
         start_index_byte = byte_index_for_index( current, start_index );
         memcpy
         (
            (*n2).str,
            &( (*n1).str[start_index_byte - (*n1).byte_index] ),
            (*n1).byte_count - ( start_index_byte - (*n1).byte_index )
         );

         // adjust counts
         (*n2).byte_count = (*n1).byte_count - ( start_index_byte - (*n1).byte_index );
         (*n1).byte_count = start_index_byte - (*n1).byte_index;

         // fill unused bytes with zeroes
         cp = (*n1).str;
         for ( i = (*n1).byte_start + (*n1).byte_count; i < (*current).str_length; i++ )
         {
            cp[i] = 0;
         }
         
         cp = (*n2).str;
         for ( i = (*n2).byte_start + (*n2).byte_count; i < (*current).str_length; i++ )
         {
            cp[i] = 0;
         }
         
         // put new node into cable_utf8
         redo_byte_indices( current );
         tree_put( current, n2 );

      }

      // insert other's nodes to cable_utf8 between n1 and n2
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

         redo_byte_indices( current );

         // put new node into cable_utf8
         tree_put( current, n );

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

   (*current).str_count_valid = 0;
   redo_indices( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_insert_cstring
*/

void
cable_utf8_insert_cstring( cable_utf8_t *current, char_t *other_cstring, int32_t start_index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "other_cstring not null", other_cstring != NULL );
   PRECONDITION( "start_index ok", ( is_index_valid( current, start_index ) == 1 ) || ( start_index == (*current).str_count ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // insert space for other in cable_utf8
   insert_at_index( current, start_index, strlen( other_cstring ) );

   // put other into cable_utf8
   replace_at_index_cstring( current, other_cstring, start_index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_append_character
*/

void
cable_utf8_append_character( cable_utf8_t *current, char_t *c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "c not null", c != NULL );

   cable_utf8_append_cstring( current, c );

   return;
}

/**
   cable_utf8_prepend_character
*/

void
cable_utf8_prepend_character( cable_utf8_t *current, char_t *c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "c not null", c != NULL );

   cable_utf8_prepend_cstring( current, c );

   return;
}

/**
   cable_utf8_insert_character
*/

void
cable_utf8_insert_character( cable_utf8_t *current, char_t *c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "c not null", c != NULL );
   PRECONDITION( "index OK", is_index_valid( current, index ) == 1 );

   cable_utf8_insert_cstring( current, c, index );

   return;
}

/**
   cable_utf8_to_lower
*/
void
cable_utf8_to_lower
(
   cable_utf8_t *current,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "start_index ok", is_index_valid( current, start_index ) == 1 );
   PRECONDITION( "end_index ok", is_index_valid( current, end_index ) == 1 );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cable_utf8_t *subcable = NULL;

   // get subcable to be changed
   subcable = subcable_utf8_from_bounds( current, start_index, end_index );

   // change it
   to_lower( subcable );

   // remove original from cable
   remove_from_bounds( current, start_index, end_index );

   // make space for changed subcable
   insert_at_index( current, start_index, (*subcable).str_byte_count );

   // put changed subcable into cable
   replace_at_index( current, subcable, start_index );

   // delete temo subcable
   cable_utf8_dispose( &subcable );

   (*current).str_count_valid = 0;
   redo_indices( current );
   
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_to_upper
*/
void
cable_utf8_to_upper
(
   cable_utf8_t *current,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "start_index ok", is_index_valid( current, start_index ) == 1 );
   PRECONDITION( "end_index ok", is_index_valid( current, end_index ) == 1 );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cable_utf8_t *subcable = NULL;

   // get subcable to be changed
   subcable = subcable_utf8_from_bounds( current, start_index, end_index );

   // change it
   to_upper( subcable );

   // remove original from cable
   remove_from_bounds( current, start_index, end_index );

   // make space for changed subcable
   insert_at_index( current, start_index, (*subcable).str_byte_count );

   // put changed subcable into cable
   replace_at_index( current, subcable, start_index );

   // delete temo subcable
   cable_utf8_dispose( &subcable );

   (*current).str_count_valid = 0;
   redo_indices( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_substring
*/

cable_utf8_t *
cable_utf8_substring( cable_utf8_t *current, int32_t start_index, int32_t end_index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "start_index ok", is_index_valid( current, start_index ) == 1 );
   PRECONDITION( "end_index ok", is_index_valid( current, end_index ) == 1 );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cable_utf8_t *result = NULL;

   result = subcable_utf8_from_bounds( current, start_index, end_index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_copy
*/

cable_utf8_t *
cable_utf8_copy( cable_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   cable_utf8_t *result = NULL;

   result = subcable_utf8_from_bounds( current, 0, (*current).str_count - 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   cable_utf8_remove
*/

void
cable_utf8_remove( cable_utf8_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "index ok", is_index_valid( current, index ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // remove the space for a character
   remove_from_bounds( current, index, index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_remove_substring
*/

void
cable_utf8_remove_substring( cable_utf8_t *current, int32_t start_index, int32_t end_index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "start_index ok", is_index_valid( current, start_index ) == 1 );
   PRECONDITION( "end_index ok", is_index_valid( current, end_index ) == 1 );
   PRECONDITION( "start_index and end_index ok", ( start_index <= end_index ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // remove the space
   remove_from_bounds( current, start_index, end_index );

   redo_indices( current );
   
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_keep_head
*/

void
cable_utf8_keep_head( cable_utf8_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "count ok", is_count_valid( current, count ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t start_index = 0;
   int32_t end_index = 0;

   start_index = count;
   end_index = (*current).str_count - 1;

   if ( start_index < (*current).str_count )
   {
      // remove the space
      remove_from_bounds( current, start_index, end_index );
   }

   redo_indices( current );
   
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_keep_tail
*/

void
cable_utf8_keep_tail( cable_utf8_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "count ok", is_count_valid( current, count ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t start_index = 0;
   int32_t end_index = 0;

   start_index = 0;
   end_index = (*current).str_count - count - 1;

   if ( end_index >= 0 )
   {
      // remove the space
      remove_from_bounds( current, start_index, end_index );
   }

   redo_indices( current );
   
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_remove_head
*/

void
cable_utf8_remove_head( cable_utf8_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "count ok", is_count_valid( current, count ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t start_index = 0;
   int32_t end_index = 0;

   start_index = 0;
   end_index = count - 1;

   if ( end_index >= 0 )
   {
      // remove the space
      remove_from_bounds( current, start_index, end_index );
   }

   redo_indices( current );
   
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_remove_tail
*/

void
cable_utf8_remove_tail( cable_utf8_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   PRECONDITION( "count ok", is_count_valid( current, count ) == 1 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t start_index = 0;
   int32_t end_index = 0;

   start_index = (*current).str_count - count;
   end_index = (*current).str_count - 1;

   if ( start_index >= 0 )
   {
      // remove the space
      remove_from_bounds( current, start_index, end_index );
   }

   redo_indices( current );
   
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_wipe_out
*/

void
cable_utf8_wipe_out( cable_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t start_index = 0;
   int32_t end_index = 0;

   start_index = 0;
   end_index = (*current).str_count - 1;

   if ( end_index < 0 )
   {
      end_index = 0;
   }

   if ( (*current).str_byte_count > 0 )
   {
      // remove the space
      remove_from_bounds( current, start_index, end_index );
   }

   redo_indices( current );
   
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   cable_utf8_reclaim
*/

void
cable_utf8_reclaim( cable_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == CABLE_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   node_t *node = NULL;
   node_t *n1 = NULL;
   node_t *n2 = NULL;
   int32_t i = 0;
   char_t *cp = NULL;

   // move chars in each node's str to start of str buffer
   node = (*current).first;

   while( node != NULL )
   {
      if ( (*node).byte_start != 0 )
      {
         memmove( (*node).str, &( (*node).str[(*node).byte_start] ), (*node).byte_count );
         (*node).byte_start = 0;
         
         cp = (*node).str;
         for ( i = (*node).byte_count; i < (*current).str_length; i++ )
         {
            cp[i] = 0;
         }
      }
      node = (*node).next;
   }

   // append node's chars to preceeding node's chars if there's space
   // if successful, remove the now empty node
   node = (*current).first;

   while( node != NULL )
   {
      n1 = (*node).next;

      if ( n1 != NULL )
      {
         if ( (*node).byte_count + (*n1).byte_count <= (*current).str_length )
         {
            // copy chars from n1 to node
            memmove
            (
               &( (*node).str[ (*node).byte_start + (*node).byte_count ] ),
               (*n1).str,
               (*n1).byte_count
            );

            // update counts
            (*node).byte_count = (*node).byte_count + (*n1).byte_count;
            (*n1).byte_count = 0;

            // adjust pointers to eliminate n1 from linked list
            n2 = (*n1).next;
            (*node).next = n2;

            if ( n2 != NULL )
            {
               (*n2).prev = node;
            }

            // remove n1
            redo_byte_indices( current );
            tree_remove( current, n1 );

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

   (*current).str_count_valid = 0;
   redo_indices( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


#ifdef __cplusplus
}
#endif

/* End of file */

