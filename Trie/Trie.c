/**
 @file Trie.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Trie"

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

 Function definitions for the opaque Trie_t type.

*/

#include "Trie.h"

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
   Key_Element key_element;
   Type value;
   int32_t has_value;
   struct node *parent;
   struct node *child;
   struct node *next;
};

typedef struct node node_t;

/**
   Hash table structure definition.
*/

struct Trie_struct( Prefix )
{

   int32_t _type;
   int32_t _key_type;
   int32_t _key_element_type;
   int32_t _item_type;

   node_t *root;
   int32_t count;

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
   CHECK( "node allocated correctly", node != NULL );

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
   PRECONDITION( "node not null", *node != NULL );

   free(*node);
   *node = NULL;

   return;
}

/**
   local function prototypes
*/

static
int32_t
has( Trie_type( Prefix ) *trie, Key key, int32_t key_length );

static
node_t *
get_node_for_key( Trie_type( Prefix ) *trie, Key key, int32_t key_length );

static
node_t *
insert_nodes_for_key( Trie_type( Prefix ) *trie, Key key, int32_t key_length );

static
void
put( Trie_type( Prefix ) *trie, Type value, Key key, int32_t key_length );

static
void
put_and_dispose( Trie_type( Prefix ) *trie, Type value, Key key, int32_t key_length );

/**
   has

   Return 1 if trie has an item for key, 0 if not

   @param current Trie_t instance
   @param key the key to query for
   @param key_length the number of key elements in key
   @return 1 if key found, 0 otherwise
*/

static
int32_t
has( Trie_type( Prefix ) *current, Key key, int32_t key_length )
{
   int32_t result = 0;
   int32_t i = 0;
   int32_t flag = 0;
   Key_Element ke;
   node_t *node = NULL;

   // get current root
   node = (*current).root;

   for( i = 0; i < key_length; i++ )
   {
      // get key element, set flag to 0
      ke = KEY_ELEMENT_ACCESS_FUNCTION( key, i );
      flag = 0;

      // look through this node and its siblings at this level to see if we can
      // find the key element at index i
      while ( ( node != NULL ) && ( flag == 0 ) )
      {
         if ( KEY_ELEMENT_EQUALITY_FUNCTION( ke, (*node).key_element ) == 1 )
         {
            // we found the key element, continue, exit while loop with current node
            flag = 1;
            break;
         }
         else
         {
            // not found, next sibling
            node = (*node).next;
         }
      }

      // see if we found the key element at index i
      if ( flag == 0 )
      {
         // key element not found, key not present, exit for loop with fail
         result = 0;
         break;
      }

      // key element found - see if we're at the end of the key
      if ( i == ( key_length - 1 ) )
      {
         // we are - does this node have a value?
         if ( (*node).has_value == 1 )
         {
            // has value, we found node with the value for the key, exit for loop
            result = 1;
            break;
         }
      }

      // not at the end of the key, do next iteration of for loop with child of node
      node = (*node).child;

   }

   // return found flag
   return result;
}

/**
   get_node_for_key

   Return node if trie has an item for key, NULL if not

   @param current Trie_t instance
   @param key the key to query for
   @param key_length the number of key elements in key
   @return the found node, NULL otherwise
*/

static
node_t *
get_node_for_key( Trie_type( Prefix ) *current, Key key, int32_t key_length )
{
   node_t *result = NULL;
   int32_t i = 0;
   int32_t flag = 0;
   Key_Element ke;
   node_t *node = NULL;

   // get current root
   node = (*current).root;

   for( i = 0; i < key_length; i++ )
   {
      // get key element, set flag to 0
      ke = KEY_ELEMENT_ACCESS_FUNCTION( key, i );
      flag = 0;

      // look through this node and its siblings at this level to see if we can
      // find the key element at index i
      while ( ( node != NULL ) && ( flag == 0 ) )
      {
         if ( KEY_ELEMENT_EQUALITY_FUNCTION( ke, (*node).key_element ) == 1 )
         {
            // we found the key element, continue, exit while loop with current node
            flag = 1;
            break;
         }
         else
         {
            // not found, next sibling
            node = (*node).next;
         }
      }

      // see if we found the key element at index i
      if ( flag == 0 )
      {
         // key element not found, key not present, exit for loop with fail
         result = NULL;
         break;
      }

      // key element found - see if we're at the end of the key
      if ( i == ( key_length - 1 ) )
      {
         // we are - we found the node with the key, exit for loop
         result = node;
         break;
      }

      // not at the end of the key, do next iteration of for loop with child of node
      node = (*node).child;

   }

   // return found flag
   return result;
}

/**
   insert_child_in_parent

   insert a node into the list of a parent's children in correct order

   @param parent the parent node
   @param node the node to insert

*/

static
void
insert_child_in_parent( node_t *parent, node_t *node )
{
   Key_Element ke = Key_Element_Default_Value;
   Key_Element ke_prev = Key_Element_Default_Value;
   Key_Element ke_next = Key_Element_Default_Value;
   node_t *prev = NULL;
   node_t *next = NULL;
   int32_t flag = 0;

   // get key element of node
   ke = (*node).key_element;

   // attach new node to parent
   if ( (*parent).child == NULL )
   {
      // parent has no children, assign new node to (*parent).child
      (*parent).child = node;
      (*node).parent = parent;
   }
   else
   {
      // parent has children, put new node in order within list of children
      prev = (*parent).child;
      ke_prev = (*prev).key_element;

      // see where node belongs in list of siblings
      if ( KEY_ELEMENT_COMPARISON_FUNCTION( ke, ke_prev ) < 0 )
      {
         // new node belongs at start of sibling list
         (*node).next = prev;
         (*parent).child = node;
         (*node).parent = parent;
      }
      else
      {
         // otherwise see where new node fits in list of siblings and put it there
         next = (*prev).next;
         flag = 0;
         while ( next != NULL )
         {
            // see if new node fits between prev and next
            ke_next = (*next).key_element;
            if (
               ( KEY_ELEMENT_COMPARISON_FUNCTION( ke_prev, ke ) < 0 )
               &&
               ( KEY_ELEMENT_COMPARISON_FUNCTION( ke, ke_next ) < 0 )
            )
            {
               // new node fits here, place it here
               (*prev).next = node;
               (*node).next = next;
               (*node).parent = parent;

               // exit while loop
               flag = 1;
               break;
            }

            // set up for next while loop iteration
            prev = next;
            ke_prev = ke_next;
            next = (*prev).next;
         }

         // next was NULL, new node not inserted yet, tag onto prev at end of list
         if ( flag == 0 )
         {
            (*prev).next = node;
            (*node).parent = parent;
         }
      }
   }

   return;
}

/**
   insert_nodes_for_key_from_last_parent

   Insert nodes into trie for key starting from last parent, return node for full key

   @param current Trie_t instance
   @param key the key to query for
   @param key_length the number of key elements in key
   @param last_parent the last parent of the node
   @param index the index in key to be inserted from
   @return the node for the full key
*/

static
node_t *
insert_nodes_for_key_from_last_parent
(
   Trie_type( Prefix ) *current,
   Key key,
   int32_t key_length,
   node_t *last_parent,
   int32_t index
)
{
   node_t *result = NULL;
   int32_t i = 0;
   int32_t i1 = 0;
   int32_t flag = 0;
   Key_Element ke = Key_Element_Default_Value;
   Key_Element ke_prev = Key_Element_Default_Value;
   Key_Element ke_next = Key_Element_Default_Value;
   node_t *n = NULL;
   node_t *node = NULL;
   node_t *prev = NULL;
   node_t *next = NULL;

   // get current root
   node = (*current).root;

   if ( ( node == NULL ) && ( index == 0 ) && ( last_parent == NULL ) )
   {
      // we're starting with an empty current
      node = node_make();
      (*current).root = node;
      (*node).key_element = KEY_ELEMENT_ACCESS_FUNCTION( key, 0 );
      n = node;
      i1 = 1;

      // handle case where key is one key element long
      if ( key_length == 1 )
      {
         result = node;
      }
   }
   else if ( ( node != NULL ) && ( index == 0 ) && ( last_parent == NULL ) )
   {
      // don't have the start of the key - make a new node to start the key
      node = node_make();
      n = node;
      (*node).key_element = KEY_ELEMENT_ACCESS_FUNCTION( key, 0 );
      ke = (*node).key_element;

      // see if new node should be the root
      if ( KEY_ELEMENT_COMPARISON_FUNCTION( (*node).key_element, ( *(*current).root ).key_element ) < 0 )
      {
         // new node is the new root
         (*node).next = (*current).root;
         (*current).root = node;

         // set index
         i1 = 1;

         // handle case where key is one key element long
         if ( key_length == 1 )
         {
            result = node;
         }

      }
      else
      {
         // place the new node in the root's list of siblings
         n = (*current).root;
         prev = n;
         ke_prev = (*prev).key_element;
         next = (*prev).next;

         // set index
         i1 = 1;

         while ( next != NULL )
         {
            // see if new node fits between prev and next
            ke_next = (*next).key_element;
            if (
               ( KEY_ELEMENT_COMPARISON_FUNCTION( ke_prev, ke ) < 0 )
               &&
               ( KEY_ELEMENT_COMPARISON_FUNCTION( ke, ke_next ) < 0 )
            )
            {
               // new node fits here, place it here
               (*prev).next = node;
               (*node).next = next;
               (*node).parent = (*prev).parent;

               // exit while loop
               flag = 1;
               break;
            }

            // set up for next while loop iteration
            prev = next;
            ke_prev = ke_next;
            next = (*prev).next;
         }

         // next was NULL, new node not inserted yet, append onto prev at end of list
         if ( flag == 0 )
         {
            (*prev).next = node;
            (*node).parent = (*prev).parent;
            n = node;
         }

         // set index
         i1 = 1;

         // handle case where key is one key element long
         if ( key_length == 1 )
         {
            result = node;
         }
      }
   }
   else
   {
      n = last_parent;
      i1 = index;
   }

   for( i = i1; i < key_length; i++ )
   {
      // add children to n to put key into current
      node = node_make();
      ke = KEY_ELEMENT_ACCESS_FUNCTION( key, i );
      (*node).key_element = ke;

      // put child into current
      insert_child_in_parent( n, node );

      // if we've gone through all elements in key, we're done, return node
      if ( i == ( key_length - 1 ) )
      {
         result = node;
      }

      // prepare for next iteration
      n = node;
   }

   return result;

}

/**
   insert_nodes_for_key

   Insert nodes into trie for key, return node for full key

   @param current Trie_t instance
   @param key the key to query for
   @param key_length the number of key elements in key
   @return the node for the full key
*/

static
node_t *
insert_nodes_for_key( Trie_type( Prefix ) *current, Key key, int32_t key_length )
{
   node_t *result = NULL;
   int32_t i = 0;
   int32_t flag = 0;
   Key_Element ke;
   node_t *node = NULL;
   node_t *last_parent = NULL;

   // get current root
   node = (*current).root;
   last_parent = NULL;

   for( i = 0; i < key_length; i++ )
   {
      // get key element, set flag to 0
      ke = KEY_ELEMENT_ACCESS_FUNCTION( key, i );
      flag = 0;

      // look through this node and its siblings at this level to see if we can
      // find the key element at index i
      while ( ( node != NULL ) && ( flag == 0 ) )
      {
         if ( KEY_ELEMENT_EQUALITY_FUNCTION( ke, (*node).key_element ) == 1 )
         {
            // we found the key element, continue, exit while loop with current node
            flag = 1;
            break;
         }
         else
         {
            // not found, next sibling
            node = (*node).next;
         }
      }

      // see if we found the key element at index i
      if ( flag == 0 )
      {
         // key element not found, insert node for rest of key elements,
         // return node for full key
         result
            =  insert_nodes_for_key_from_last_parent
               (
                  current,
                  key,
                  key_length,
                  last_parent,
                  i
               );
         break;
      }

//      // key element found - see if we're at the end of the key
//      if ( i == ( key_length - 1 ) )
//      {
//         // we are - we found the node with the key, exit for loop
//         result = node;
//         break;
//      }

      // not at the end of the key, do next iteration of for loop with child of node
      last_parent = node;
      node = (*node).child;

   }

   // return found flag
   return result;
}

/**
   put

   Insert nodes into trie for key, do not dispose of existing value for key

   @param current Trie_t instance
   @param value the value to put in the current
   @param key the key to query for
   @param key_length the number of key elements in key
*/

static
void
put( Trie_type( Prefix ) *current, Type value, Key key, int32_t key_length )
{
   node_t *node = NULL;

   // see if key exists in current
   node = get_node_for_key( current, key, key_length );

   if ( node != NULL )
   {
      // node exists, replace its value
      (*node).value = value;
   }
   else
   {
      // node doesn't exist, insert nodes to put nodes for key into current
      node = insert_nodes_for_key( current, key, key_length );

      // set node for new value, done
      (*node).value = value;
      (*node).has_value = 1;
      (*current).count = (*current).count + 1;
   }

   return;
}

/**
   put_and_dispose

   Insert nodes into trie for key, dispose of existing value for key

   @param current Trie_t instance
   @param value the value to put in the current
   @param key the key to query for
   @param key_length the number of key elements in key
*/

static
void
put_and_dispose( Trie_type( Prefix ) *current, Type value, Key key, int32_t key_length )
{
   node_t *node = NULL;

   // see if key exists in current
   node = get_node_for_key( current, key, key_length );

   if ( node != NULL )
   {
      // node exists, replace its value after disposing of the original
      VALUE_DISPOSE_FUNCTION( (*node).value );
      (*node).value = value;
   }
   else
   {
      // node doesn't exist, insert nodes to put nodes for key into current
      node = insert_nodes_for_key( current, key, key_length );

      // set node for new value, done
      (*node).value = value;
      (*node).has_value = 1;
      (*current).count = (*current).count + 1;
   }

   return;
}

/**
   remove_nodes_from_node

   Remove all possible nodes from trie from node

   @param current Trie_t instance
   @param key the key to query for
   @param key_length the number of key elements in key
*/

static
void
remove_nodes_from_node( Trie_type( Prefix ) *current, node_t *from_node )
{
   node_t *node = NULL;
   node_t *n = NULL;
   node_t *prev = NULL;

   // get node to start at
   node = from_node;

   while ( node != NULL )
   {
      // can remove node if no children, no value
      if ( ( (*node).child == NULL ) && ( (*node).has_value == 0 ) )
      {
         // get start of parent's list of children
         if ( (*node).parent != NULL )
         {
            prev = ( *(*node).parent ).child;
         }
         else
         {
            prev = (*current).root;
         }

         if ( node == prev )
         {
            // first sibling, set parent's child to next sibling
            if ( (*node).parent != NULL )
            {
               ( *(*node).parent ).child = (*node).next;
            }
            else
            {
               (*current).root = (*node).next;
            }

            // next node to look at is node's parent
            n = node;
            node = (*node).parent;

            // dispose of the node
            node_dispose( &n );
         }
         else // find the node in the parent's list of children
         {
            n = (*prev).next;
            while ( n != NULL )
            {
               if ( n == node )
               {
                  // found node, not first in list of children, remove it
                  (*prev).next = (*node).next;

                  // next node to look at is node's parent
                  node = (*node).parent;

                  // dispose of the node
                  node_dispose( &n );

                  // exit while loop
                  n = NULL;
               }
               else
               {
                  // otherwise set for next while loop iteration
                  prev = n;
                  n = (*n).next;
               }
            }
         }
      }
      else
      {
         // finish while loop
         node = NULL;
      }
   }

   // return
   return;
}

/**
   remove_nodes_from_node_and_dispose

   Remove all possible nodes from trie from node, dispose of key elements and values

   @param current Trie_t instance
   @param key the key to query for
   @param key_length the number of key elements in key
*/

static
void
remove_nodes_from_node_and_dispose( Trie_type( Prefix ) *current, node_t *from_node )
{
   node_t *node = NULL;
   node_t *n = NULL;
   node_t *prev = NULL;

   // get node to start at
   node = from_node;

   while ( node != NULL )
   {
      // can remove node if no children, no value
      if ( (*node).child == NULL )
      {
         // get start of parent's list of children
         if ( (*node).parent != NULL )
         {
            prev = ( *(*node).parent ).child;
         }
         else
         {
            prev = (*current).root;
         }

         if ( node == prev )
         {
            // first sibling, set parent's child to next sibling
            if ( (*node).parent != NULL )
            {
               ( *(*node).parent ).child = (*node).next;
            }
            else
            {
               (*current).root = (*node).next;
            }

            // next node to look at is node's parent
            n = node;
            node = (*node).parent;

            // dispose of the node
            if ( (*n).has_value == 1 )
            {
               VALUE_DISPOSE_FUNCTION( (*n).value );
            }
            node_dispose( &n );
         }
         else // find the node in the parent's list of children
         {
            n = (*prev).next;
            while ( n != NULL )
            {
               if ( n == node )
               {
                  // found node, not first in list of children, remove it
                  (*prev).next = (*node).next;

                  // next node to look at is node's parent
                  node = (*node).parent;

                  // dispose of the node
                  if ( (*n).has_value == 1 )
                  {
                     VALUE_DISPOSE_FUNCTION( (*n).value );
                  }
                  node_dispose( &n );

                  // exit while loop
                  n = NULL;
               }
               else
               {
                  // otherwise set for next while loop iteration
                  prev = n;
                  n = (*n).next;
               }
            }
         }
      }
      else
      {
         // finish while loop
         node = NULL;
      }
   }

   // return
   return;
}


/**
   get_first_terminal_node

   Find first rerminal node in trie.

   @param current Trie_t instance
   @return the first terminal node
*/
static
node_t *
get_first_terminal_node
(
   Trie_type( Prefix ) *current
)
{
   node_t *result = NULL;
   node_t *node = NULL;
   int32_t flag = 0;

   node = (*current).root;
   result = node;

   while ( ( node != NULL ) && ( flag == 0 ) )
   {
      if ( (*node).child != NULL )
      {
         // get the child
         node = (*node).child;
         result = node;
      }
      else if ( (*node).next != NULL )
      {
         // get the sibling
         node = (*node).next;
         result = node;
      }
      else
      {
         // no child, no sibling, leave found node in result
         node = NULL;
      }

   }

   return result;
}

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
is_empty_implies_root_null( Trie_type( Prefix ) *p )
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
not_empty_implies_root_not_null( Trie_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).count > 0 )
   {
      result = ( (*p).root != NULL );
   }

   return result;
}

static
int32_t
nonnegative_count( Trie_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
void
count_ok_recurse( int32_t *count, node_t *node )
{

   if ( node != NULL )
   {
      if ( (*node).has_value == 1 )
      {
         *count = *count + 1;
      }
   }

   if ( (*node).child != NULL )
   {
      count_ok_recurse( count, (*node).child );
   }

   if ( (*node).next != NULL )
   {
      count_ok_recurse( count, (*node).next );
   }

   return;
}

static
int32_t
count_ok( Trie_type( Prefix ) *p )
{
   int32_t result = 1;
   int32_t count = 0;

   if ( (*p).root != NULL )
   {
      count_ok_recurse( &count, (*p).root );
   }

   result = 0;
   if ( count == (*p).count )
   {
      result = 1;
   }

   return result;
}

static
int32_t
has_value_ok_recurse( node_t *node )
{
   int32_t result = 1;

   if ( ( node != NULL ) && ( (*node).child == NULL ) )
   {
      result = 0;
      if ( (*node).has_value == 1 )
      {
         result = 1;
      }
   }

   if ( result == 1 )
   {
      if ( (*node).child != NULL )
      {
         result = has_value_ok_recurse( (*node).child );
      }
   }

   if ( result == 1 )
   {
      if ( (*node).next != NULL )
      {
         result = has_value_ok_recurse( (*node).next );
      }
   }

   return result;
}

static
int32_t
has_value_ok( Trie_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).root != NULL )
   {
      result = has_value_ok_recurse( (*p).root );
   }

   return result;
}

static
void invariant( Trie_type( Prefix ) *p )
{
   assert( ( ( void ) "empty implies root null", is_empty_implies_root_null( p ) ) );
   assert( ( ( void ) "not empty implies root not null", not_empty_implies_root_not_null( p ) ) );
   assert( ( ( void ) "nonnegative count", nonnegative_count( p ) ) );
   assert( ( ( void ) "count OK", count_ok( p ) ) );
   assert( ( ( void ) "has_value OK", has_value_ok( p ) ) );
   return;
}

#endif

/**
   Trie_make
*/

Trie_type( Prefix ) *
Trie_make( Prefix )( void )
{
   // allocate trie struct
   Trie_type( Prefix ) * result
      = ( Trie_type( Prefix ) * ) calloc( 1, sizeof( Trie_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type codes
   (*result)._type = TRIE_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._key_element_type = Key_Element_Code;
   (*result)._item_type = Type_Code;

   (*result).count = 0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   Trie_dispose
*/

void
Trie_dispose( Prefix )( Trie_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == TRIE_TYPE ) && ( (**current)._key_type = Key_Code ) && ( (**current)._key_element_type = Key_Element_Code ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   int32_t flag = 0;
   node_t *node = NULL;

   // don't delete NULL root
   if ( (**current).root == NULL )
   {
      flag = 1;
   }

   // loop to delete all nodes - eventually
   while ( flag == 0 )
   {
      node = get_first_terminal_node(*current);

      if ( node != NULL )
      {
         (*node).has_value = 0;
      }

      remove_nodes_from_node( *current, node );

      if ( (**current).root == NULL )
      {
         flag = 1;
      }
   }

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   Trie_deep_dispose
*/

void
Trie_deep_dispose( Prefix )( Trie_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == TRIE_TYPE ) && ( (**current)._key_type = Key_Code ) && ( (**current)._key_element_type = Key_Element_Code ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   int32_t flag = 0;
   node_t *node = NULL;

   // don't delete NULL root
   if ( (**current).root == NULL )
   {
      flag = 1;
   }

   // loop to delete all nodes - eventually
   while ( flag == 0 )
   {
      node = get_first_terminal_node(*current);

      if ( node != NULL )
      {
         (*node).has_value = 0;
      }

      remove_nodes_from_node_and_dispose( *current, node );

      if ( (**current).root == NULL )
      {
         flag = 1;
      }
   }

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}


/**
   Trie_item
*/

Type
Trie_item( Prefix )( Trie_type( Prefix ) *current, Key key, int32_t key_length )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == TRIE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._key_element_type = Key_Element_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has key", has( current, key, key_length ) );

   node_t *node = NULL;
   Type result = Type_Default_Value;

   // get node at key
   node = get_node_for_key( current, key, key_length );

   if ( ( node != NULL ) && ( (*node).has_value == 1 ) )
   {
      result = (*node).value;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Trie_count
*/

int32_t
Trie_count( Prefix )( Trie_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == TRIE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._key_element_type = Key_Element_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   Trie_is_empty
*/

int32_t
Trie_is_empty( Prefix )( Trie_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == TRIE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._key_element_type = Key_Element_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count ==  0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Trie_has_key
*/

int32_t
Trie_has_key( Prefix )( Trie_type( Prefix ) *current, Key key, int32_t key_length )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == TRIE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._key_element_type = Key_Element_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( get_node_for_key( current, key, key_length ) != NULL );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Trie_has
*/

int32_t
Trie_has( Prefix )( Trie_type( Prefix ) *current, Key key, int32_t key_length )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == TRIE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._key_element_type = Key_Element_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = has( current, key, key_length );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Trie_put
*/

void
Trie_put( Prefix )( Trie_type( Prefix ) *current, Type value, Key key, int32_t key_length )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == TRIE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._key_element_type = Key_Element_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "key_length ok", key_length > 0 );

   LOCK( (*current).mutex );
   INVARIANT( current );

   put( current, value, key, key_length );

   POSTCONDITION( "item present", has( current, key, key_length ) == 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Trie_put_and_dispose
*/

void
Trie_put_and_dispose( Prefix )( Trie_type( Prefix ) *current, Type value, Key key, int32_t key_length )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == TRIE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._key_element_type = Key_Element_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "key_length ok", key_length > 0 );

   LOCK( (*current).mutex );
   INVARIANT( current );

   put_and_dispose( current, value, key, key_length );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Trie_replace
*/

void
Trie_replace( Prefix )( Trie_type( Prefix ) *current, Type value, Key key, int32_t key_length )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == TRIE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._key_element_type = Key_Element_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "key_length ok", key_length > 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   node_t *node = NULL;

   // get node at key
   node = get_node_for_key( current, key, key_length );

   if ( node != NULL )
   {
      (*node).value = value;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Trie_replace_and_dispose
*/

void
Trie_replace_and_dispose( Prefix )( Trie_type( Prefix ) *current, Type value, Key key, int32_t key_length )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == TRIE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._key_element_type = Key_Element_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "key_length ok", key_length > 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   node_t *node = NULL;

   // get node at key
   node = get_node_for_key( current, key, key_length );

   if ( node != NULL )
   {
      VALUE_DISPOSE_FUNCTION( (*node).value );
      (*node).value = value;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Trie_remove
*/

void
Trie_remove( Prefix )( Trie_type( Prefix ) *current, Key key, int32_t key_length )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == TRIE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._key_element_type = Key_Element_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "key_length ok", key_length > 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has key", has( current, key, key_length ) );

   node_t *node = NULL;

   // get the node at the key
   node = get_node_for_key( current, key, key_length );
   if ( node != NULL )
   {
      if ( (*node).has_value == 1 )
      {
         // dispose the value
         VALUE_DISPOSE_FUNCTION( (*node).value );
         (*node).has_value = 0;

         // decrement current count
         (*current).count = (*current).count - 1;
      }

      // remove all possible nodes from found node
      remove_nodes_from_node( current, node );

   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Trie_remove_and_dispose
*/

void
Trie_remove_and_dispose( Prefix )( Trie_type( Prefix ) *current, Key key, int32_t key_length )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == TRIE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._key_element_type = Key_Element_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "key_length ok", key_length > 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has key", has( current, key, key_length ) );

   node_t *node = NULL;

   // get the node at the key
   node = get_node_for_key( current, key, key_length );
   if ( node != NULL )
   {
      if ( (*node).has_value == 1 )
      {
         // overwrite the value
         (*node).value = Type_Default_Value;
         (*node).has_value = 0;

         // decrement current count
         (*current).count = (*current).count - 1;
      }

      // remove all possible nodes from found node
      remove_nodes_from_node( current, node );

   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Trie_wipe_out
*/

void
Trie_wipe_out( Prefix )( Trie_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == TRIE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._key_element_type = Key_Element_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t flag = 0;
   node_t *node = NULL;

   // don't delete NULL root
   if ( (*current).root == NULL )
   {
      flag = 1;
   }

   // loop to delete all nodes - eventually
   while ( flag == 0 )
   {
      node = get_first_terminal_node( current );

      if ( node != NULL )
      {
         (*node).has_value = 0;
      }

      remove_nodes_from_node( current, node );

      if ( (*current).root == NULL )
      {
         flag = 1;
      }

   }

   // set count to zero
   (*current).count = 0;

   POSTCONDITION( "is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Trie_wipe_out_and_dispose
*/

void
Trie_wipe_out_and_dispose( Prefix )( Trie_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == TRIE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._key_element_type = Key_Element_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t flag = 0;
   node_t *node = NULL;

   // don't delete NULL root
   if ( (*current).root == NULL )
   {
      flag = 1;
   }

   // loop to delete all nodes - eventually
   while ( flag == 0 )
   {
      node = get_first_terminal_node( current );
      remove_nodes_from_node_and_dispose( current, node );

      if ( (*current).root == NULL )
      {
         flag = 1;
      }
   }

   // set count to zero
   (*current).count = 0;

   POSTCONDITION( "is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

