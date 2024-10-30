/**
 @file SList.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Singly Linked Lists"

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

 Function definitions for the opaque SList_t type.

*/

#include "SList.h"

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_Indexable.ph"
#include "P_Iterable.ph"
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

struct node;

/**
   Node structure. Holds a value
*/

struct node
{
   struct node *next;
   Type value;
};

typedef struct node node_t;

/**
   Linked list structure
*/

struct SList_struct( Prefix )
{

   PROTOCOLS_DEFINITION;

   int32_t _type;
   int32_t _item_type;

   node_t *first;
   node_t *last;
   int32_t count;
   SList_cursor_type( Prefix ) *first_cursor;
   SList_cursor_type( Prefix ) *last_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure. Accesses list and holds a location.
*/

struct SList_cursor_struct( Prefix )
{
   SList_type( Prefix ) *list;
   node_t *item;
   SList_cursor_type( Prefix ) *next_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};


/**
   node_make

   create a new node

   @return new node
*/

static
node_t *
node_make( void )
{
   node_t *node = ( node_t * ) calloc( 1, sizeof( node_t ) );
   CHECK( "node not null", node != NULL );
   
   return node;
}

/**
   node_dispose

   dispose of a node

   @param node the node
*/

static
void
node_dispose( node_t **node )
{
   PRECONDITION( "node not null", node != NULL );
   PRECONDITION( "*node not null", *node != NULL );
   free(*node);
   node = NULL;
   return;
}

/**
   move_all_cursors_at_node_forth

   After a node has been removed, move all cursors pointing to that node
   forth.

   @param current SList_t instance
   @param node the just removed node
*/
static
void
move_all_cursors_at_node_forth
(
   SList_type( Prefix ) *current,
   node_t *node
)
{
   SList_cursor_type( Prefix ) *cursor = NULL;

   for (  cursor = (*current).first_cursor;
          cursor != NULL;
          cursor = (*cursor).next_cursor
       )
   {
      if ( (*cursor).item != NULL )
      {
         if ( (*cursor).item == node )
         {
            (*cursor).item = ( *(*cursor).item ).next;
         }
      }
   }

   return;
}

/**
   move_all_cursors_off

   Move all cursors pointing off.

   @param current the list
*/
static
void
move_all_cursors_off
(
   SList_type( Prefix ) *current
)
{
   SList_cursor_type( Prefix ) *cursor = NULL;

   for (  cursor = (*current).first_cursor;
          cursor != NULL;
          cursor = (*cursor).next_cursor
       )
   {
      (*cursor).item = NULL;
   }

   return;
}

/**
   compare list items to array items

   compare items in a list to items in an array

   @param current the list
   @param array the array
   @param count the number of items in the array
   @return 1 if items equal, 0 otherwise
*/

static
int32_t
compare_list_items_to_array_items
(
   SList_type( Prefix ) *current,
   Type *array,
   int32_t count
)
{
   int32_t result = 0;
   int32_t flag = 0;
   int32_t i = 0;
   node_t *node = NULL;

   node = (*current).first;

   for( i = 0; ( ( i < count ) && ( i < (*current).count ) ); i++ )
   {
      if ( (*node).value == array[i] )
      {
         flag = flag + 1;
      }
      node = (*node).next;
   }

   if ( ( flag == (*current).count ) && ( flag == count ) )
   {
      result = 1;
   }

   return result;
}

/**
   compare list items to another list items

   compare items in a list to items in another list

   @param current the list
   @param other the other list
   @return 1 if items equal, 0 otherwise
*/

static
int32_t
compare_list_items_to_list_items
(
   SList_type( Prefix ) *current,
   SList_type( Prefix ) *other
)
{
   int32_t result = 1;
   int32_t flag = 0;
   node_t *node_1 = NULL;
   node_t *node_2 = NULL;

   node_1 = (*current).first;
   node_2 = (*other).first;

   while( ( node_1 != NULL ) && ( node_2 != NULL ) )
   {
      if ( ( *node_1 ).value == ( *node_2 ).value )
      {
         flag = flag + 1;
      }
      node_1 = ( *node_1 ).next;
      node_2 = ( *node_2 ).next;
   }

   if ( ( flag == (*current).count ) && ( flag == (*other).count ) )
   {
      result = 1;
   }

   return result;
}

/**
   compare list items to list items deep equal

   compare items in a list to items in another list, deep equal

   @param current the list
   @param other the other list
   @return 1 if items deep equal, 0 otherwise
*/

static
int32_t
compare_list_items_to_list_items_deep_equal
(
   SList_type( Prefix ) *current,
   SList_type( Prefix ) *other
)
{
   int32_t result = 1;
   int32_t flag = 0;
   node_t *node_1 = NULL;
   node_t *node_2 = NULL;

   node_1 = (*current).first;
   node_2 = (*other).first;

   while( ( node_1 != NULL ) && ( node_2 != NULL ) )
   {
      if ( VALUE_DEEP_EQUAL_FUNCTION( ( *node_1 ).value, ( *node_2 ).value ) == 1 )
      {
         flag = flag + 1;
      }
      node_1 = ( *node_1 ).next;
      node_2 = ( *node_2 ).next;
   }

   if ( ( flag == (*current).count ) && ( flag == (*other).count ) )
   {
      result = 1;
   }

   return result;
}

/**
   compare list in list

   compare items in a list to another list, starting at node

   @param current the list
   @param other the other list
   @param node the node in current to start with
   @return 1 if items equal, 0 otherwise
*/

static
int32_t
compare_list_in_list
(
   SList_type( Prefix ) *current,
   SList_type( Prefix ) *other,
   node_t *node
)
{
   int32_t result = 1;
   int32_t flag = 0;
   node_t *node_1 = NULL;
   node_t *node_2 = NULL;

   node_1 = node;

   node_2 = (*other).first;

   while( ( node_1 != NULL ) && ( node_2 != NULL ) )
   {
      if ( ( *node_1 ).value == ( *node_2 ).value )
      {
         flag = flag + 1;
      }
      node_1 = ( *node_1 ).next;
      node_2 = ( *node_2 ).next;
   }

   if ( flag == (*other).count )
   {
      result = 1;
   }

   return result;
}

/**
   has

   Returns 1 if SList contains item using "==" as comparison test

   @param current the SList
   @param item the item to look for
   @return 1 if found, 0 otherwise
*/
static
int32_t
has
(
   SList_type( Prefix ) *current,
   Type value
)
{
   int32_t result = 0;
   node_t *node = NULL;

   node = (*current).first;

   while( node != NULL )
   {
      if ( (*node).value == value )
      {
         result = 1;
         break;
      }
      node = (*node).next;
   }

   return result;
}

/**
   has_eq_fn

   Returns 1 if SList contains item using equality_test_func as comparison test

   @param current the SList
   @param item the item to look for
   @param equality_test_func the function to compare values with
   @return 1 if equal, 0 otherwise
*/
static
int32_t
has_eq_fn
(
   SList_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   int32_t result = 0;
   node_t *node = NULL;

   node = (*current).first;

   while( node != NULL )
   {
      if ( equality_test_func( (*node).value, value ) == 1 )
      {
         result = 1;
         break;
      }
      node = (*node).next;
   }

   return result;
}

/**
   occurrences

   count how many nodes contain value

   @param current the list
   @param value the value to test for
   @return how many times a node contains value
*/

static
int32_t
occurrences( SList_type( Prefix ) *current, Type value )
{
   int32_t result = 0;
   node_t *node = NULL;

   node = (*current).first;

   while( node != NULL )
   {
      if ( (*node).value == value )
      {
         result = result + 1;
      }
      node = (*node).next;
   }

   return result;
}

/**
   occurrences_eq_fn

   count how many nodes contain value using specified equality function

   @param current the list
   @param value the value to test for
   @param equality_test_function the function to test for value equality
   @return how many times a node contains value
*/

static
int32_t
occurrences_eq_fn
(
   SList_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   int32_t result = 0;
   node_t *node = NULL;

   node = (*current).first;

   while( node != NULL )
   {
      if ( equality_test_func( (*node).value, value ) == 1 )
      {
         result = result + 1;
      }
      node = (*node).next;
   }

   return result;
}


/**
   slist_item

   get the item at indes

   @param current the list
   @param index the desired index
   @return the value in list at index
*/

static
Type
slist_item( SList_type( Prefix ) *current, int32_t index )
{
   node_t *node = (*current).first;

   int32_t i = 0;
   for ( i = 1; i <= index; i++ )
   {
      node = (*node).next;
   }

   Type value = (*node).value;

   return value;
}

/**
   node_at_index

   get the list node at index

   @param current the list
   @param index the index to find
   @return the node at index
*/
static
node_t *
node_at_index( SList_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "index OK", ( ( index >= 0 ) && ( index < (*current).count ) ) );

   int32_t i = 0;
   node_t *result = (*current).first;

   if ( result != NULL )
   {
      for( i = 1; ( i <= index ) && ( result != NULL ); i++ )
      {
         result = (*result).next;
      }
   }

   return result;
}

/**
   node_before

   get the previous node in the list

   @param current the list
   @param node the node after the desired node
   @return the node at index
*/
static
node_t *
node_before( SList_type( Prefix ) *current, node_t *node )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "node not null", node != NULL );

   node_t *result = NULL;
   node_t *n = (*current).first;

   while( n != NULL )
   {
      result = n;
      n = (*n).next;
      if ( n == node )
      {
         break;
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
is_empty_implies_first_last_null( SList_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).count == 0 )
   {
      result
         = (
              ( (*current).first == NULL )
              &&
              ( (*current).last  == NULL )
           );
   }

   return result;
}

static
int32_t
nonnegative_count( SList_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).count >= 0 );

   return result;
}

static
int32_t
valid_count( SList_type( Prefix ) *current )
{
   int32_t result = 1;
   int32_t n = 0;

   node_t *node = (*current).first;

   while( node != NULL )
   {
      n = n + 1;
      node = (*node).next;
   }

   result = ( n == (*current).count );

   return result;
}

static
int32_t
first_cursor_not_null( SList_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).first_cursor != NULL );

   return result;
}

static
int32_t
last_cursor_next_null( SList_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).last_cursor != NULL )
   {
      result = ( ( *(*current).last_cursor ).next_cursor == NULL );
   }

   return result;
}

static
void invariant( SList_type( Prefix ) *current )
{
   assert( ( ( void ) "empty implies first and last null", is_empty_implies_first_last_null( current ) ) );
   assert( ( ( void ) "nonnegative count", nonnegative_count( current ) ) );
   assert( ( ( void ) "valid count", valid_count( current ) ) );
   assert( ( ( void ) "first cursor not null", first_cursor_not_null( current ) ) );
   assert( ( ( void ) "last cursor next null", last_cursor_next_null( current ) ) );
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
   SList_dispose( Prefix ),
   SList_deep_dispose( Prefix ),
   SList_is_equal( Prefix ),
   SList_is_deep_equal( Prefix ),
   SList_copy( Prefix ),
   SList_deep_copy( Prefix ),
   SList_clone( Prefix ),
   SList_deep_clone( Prefix )
};

static
void *
p_indexable_table[P_INDEXABLE_FUNCTION_COUNT]
=
{
   SList_count( Prefix ),
   SList_item( Prefix ),
   SList_replace( Prefix ),
   SList_replace_and_dispose( Prefix )
};

static
void *
p_iterable_table[P_ITERABLE_FUNCTION_COUNT]
=
{
   SList_count( Prefix ),
   SList_item_at( Prefix ),
   SList_off( Prefix ),
   SList_is_empty( Prefix ),
   SList_start( Prefix ),
   SList_forth( Prefix )
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

      case P_INDEXABLE_TYPE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_INDEXABLE_FUNCTION_MAX ) )
         {
            result = p_indexable_table[ function_id ];
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

      case P_INDEXABLE_TYPE:
      {
         result = 1;
         break;
      }

      case P_ITERABLE_TYPE:
      {
         result = 1;
         break;
      }

   }

   return result;
}

#endif // PROTOCOLS_ENABLED


/**
   put_last
*/

static
void
put_last( SList_type( Prefix ) *current, Type value )
{
   node_t *node = (*current).last;

   if ( node == NULL )
   {
      node_t *new_node = node_make();
      ( *new_node ).value = value;

      (*current).first = new_node;
      (*current).last = new_node;

      (*current).count = 1;
   }
   else
   {
      node_t *new_node = node_make();
      ( *new_node ).value = value;

      ( *new_node ).next = NULL;
      (*node).next = new_node;

      (*current).last = new_node;

      (*current).count = (*current).count + 1;
   }

   return;
}


/**
   SList_make
*/

SList_type( Prefix ) *
SList_make( Prefix )( void )
{
   // allocate list struct
   SList_type( Prefix ) *result
      = ( SList_type( Prefix ) * ) calloc( 1, sizeof( SList_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = SLIST_TYPE;
   (*result)._item_type = Type_Code;

   // set built-in cursor

   // allocate cursor struct
   SList_cursor_type( Prefix ) *cursor
      =  ( SList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( SList_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set list
   (*cursor).list = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set list built-in cursor
   (*result).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new result is empty", (*result).count == 0 );
   POSTCONDITION( "new result cursor is off", ( *(*result).first_cursor ).item == NULL );

   INVARIANT( result );

   return result;
}

/**
   SList_make_from_array
*/

SList_type( Prefix ) *
SList_make_from_array( Prefix )( Type *array, int32_t count )
{
   PRECONDITION( "array not null", array != NULL );
   PRECONDITION( "count ok", count >= 0 );

   // allocate list struct
   SList_type( Prefix ) *result
      = ( SList_type( Prefix ) * ) calloc( 1, sizeof( SList_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = SLIST_TYPE;
   (*result)._item_type = Type_Code;

   // set built-in cursor

   // allocate cursor struct
   SList_cursor_type( Prefix ) *cursor
      =  ( SList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( SList_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set list
   (*cursor).list = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set list built-in cursor
   (*result).first_cursor = cursor;

   int32_t i = 0;

   for ( i = 0; i < count; i++ )
   {
      put_last( result, array[i] );
   }

   (*result).count = count;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new result cursor is off", ( *(*result).first_cursor ).item == NULL );
   POSTCONDITION( "new result contains elements of array", compare_list_items_to_array_items( result, array, count ) );

   INVARIANT( result );

   return result;
}

/**
   SList_clone
*/

SList_type( Prefix ) *
SList_clone( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );

   // allocate list struct
   SList_type( Prefix ) * result
      = ( SList_type( Prefix ) * ) calloc( 1, sizeof( SList_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = SLIST_TYPE;
   (*result)._item_type = Type_Code;

   // set built-in cursor

   // allocate cursor struct
   SList_cursor_type( Prefix ) *cursor
      =  ( SList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( SList_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set list
   (*cursor).list = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set list built-in cursor
   (*result).first_cursor = cursor;

   // copy from "list"
   LOCK( (*current).mutex );

   int32_t i = 0;
   node_t *node = (*current).first;

   for ( i = 0; i < (*current).count; i++ )
   {
      put_last( result, (*node).value );
      node = (*node).next;
   }

   UNLOCK( (*current).mutex );

   (*result).count = (*current).count;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new list cursor is off", ( *(*result).first_cursor ).item == NULL );
   POSTCONDITION( "new list contains elements of current", compare_list_items_to_list_items( result, current ) );

   INVARIANT( result );

   return result;
}

/**
   SList_deep_clone
*/

SList_type( Prefix ) *
SList_deep_clone( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );

   // allocate list struct
   SList_type( Prefix ) * result
      = ( SList_type( Prefix ) * ) calloc( 1, sizeof( SList_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = SLIST_TYPE;
   (*result)._item_type = Type_Code;

   // set built-in cursor

   // allocate cursor struct
   SList_cursor_type( Prefix ) *cursor
      =  ( SList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( SList_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set list
   (*cursor).list = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set list built-in cursor
   (*result).first_cursor = cursor;

   // copy from "list"
   LOCK( (*current).mutex );


   int32_t i = 0;
   node_t *node = (*current).first;
   Type v;

   for ( i = 0; i < (*current).count; i++ )
   {
      v = VALUE_DEEP_CLONE_FUNCTION( (*node).value );
      put_last( result, v );
      node = (*node).next;
   }

   UNLOCK( (*current).mutex );

   (*result).count = (*current).count;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new list cursor is off", ( *(*result).first_cursor ).item == NULL );
   POSTCONDITION( "new list contains elements deep equal to current", compare_list_items_to_list_items_deep_equal( result, current ) );

   INVARIANT( result );

   return result;
}

/**
   SList_is_equal
*/

int32_t
SList_is_equal( Prefix )( SList_type( Prefix ) *current, SList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == SLIST_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t result = 1;
   int32_t count = 0;
   node_t *node_1 = NULL;
   node_t *node_2 = NULL;

   // check count
   if ( (*current).count != (*other).count )
   {
      result = 0;
   }

   // lock other
   LOCK( (*other).mutex );

   node_1 = (*current).first;
   node_2 = (*other).first;

   while( ( node_1 != NULL ) && ( node_2 != NULL ) )
   {
      if ( result == 1 )
      {
         if ( ( *node_1 ).value != ( *node_2 ).value )
         {
            result = 0;
            break;
         }
         else
         {
            count = count + 1;
         }
      }

      node_1 = ( *node_1 ).next;
      node_2 = ( *node_2 ).next;

   }

   if ( count != (*current).count )
   {
      result = 0;
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return result;
}

/**
   SList_is_deep_equal
*/

int32_t
SList_is_deep_equal( Prefix )( SList_type( Prefix ) *current, SList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == SLIST_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t result = 1;
   int32_t count = 0;
   node_t *node_1 = NULL;
   node_t *node_2 = NULL;

   // check count
   if ( (*current).count != (*other).count )
   {
      result = 0;
   }

   // lock other
   LOCK( (*other).mutex );

   node_1 = (*current).first;
   node_2 = (*other).first;

   while( ( node_1 != NULL ) && ( node_2 != NULL ) )
   {
      if ( result == 1 )
      {
         if ( VALUE_DEEP_EQUAL_FUNCTION( ( *node_1 ).value, ( *node_2 ).value ) == 0 )
         {
            result = 0;
            break;
         }
         else
         {
            count = count + 1;
         }
      }

      node_1 = ( *node_1 ).next;
      node_2 = ( *node_2 ).next;

   }

   if ( count != (*current).count )
   {
      result = 0;
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return result;
}

/**
   SList_copy
*/

void
SList_copy( Prefix )( SList_type( Prefix ) *current, SList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == SLIST_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t i = 0;
   node_t *node = NULL;
   node_t *next = NULL;

   // empty out current

   // move all cursors off - list will be mangled
   move_all_cursors_off( current );

   // remove all nodes
   node = (*current).first;
   while( node != NULL )
   {
      next = (*node).next;
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
      node_dispose( &node );
      node = next;
   }

   // lock other
   LOCK( (*other).mutex );

   // reset count
   (*current).count = 0;
   (*current).first = NULL;
   (*current).last = NULL;

   node = (*other).first;

   for ( i = 0; i < (*other).count; i++ )
   {
      put_last( current, (*node).value );
      node = (*node).next;
   }

   if ( (*other).count == 0 )
   {
      (*current).first = NULL;
      (*current).last = NULL;
   }

   POSTCONDITION( "new list contains elements of other", compare_list_items_to_list_items( current, other ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return;
}

/**
   SList_deep_copy
*/

void
SList_deep_copy( Prefix )( SList_type( Prefix ) *current, SList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == SLIST_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t i = 0;
   node_t *node = NULL;
   node_t *next = NULL;
   Type v;

   // empty out current

   // move all cursors off - list will be mangled
   move_all_cursors_off( current );

   // remove all nodes
   node = (*current).first;
   while( node != NULL )
   {
      next = (*node).next;
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
      node_dispose( &node );
      node = next;
   }

   // lock other
   LOCK( (*other).mutex );

   // reset count
   (*current).count = 0;
   (*current).first = NULL;
   (*current).last = NULL;

   node = (*other).first;

   for ( i = 0; i < (*other).count; i++ )
   {
      v = VALUE_DEEP_CLONE_FUNCTION( (*node).value );
      put_last( current, v );
      node = (*node).next;
   }

   if ( (*other).count == 0 )
   {
      (*current).first = NULL;
      (*current).last = NULL;
   }

   POSTCONDITION( "new list contains elements of other", compare_list_items_to_list_items_deep_equal( current, other ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return;
}

/**
   slist_cursor_make
*/
static
SList_cursor_type( Prefix ) *
slist_cursor_make( SList_type( Prefix ) *list )
{
   // allocate cursor struct
   SList_cursor_type( Prefix ) *cursor
      =  ( SList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( SList_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set list
   (*cursor).list = list;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // place cursor reference into list structure
   if ( (*list).last_cursor == NULL )
   {
      // set second cursor for list
      ( *(*list).first_cursor ).next_cursor = cursor;
      (*list).last_cursor = cursor;
   }
   else
   {
      // set additional cursor for list
      // (*list).last_cursor holds last cursor allocated
      ( *(*list).last_cursor ).next_cursor = cursor;
      (*list).last_cursor = cursor;
   }

   MULTITHREAD_MUTEX_INIT( (*cursor).mutex );

   return cursor;
};

/**
   SList_cursor_make
*/

SList_cursor_type( Prefix ) *
SList_cursor_make( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list)._type == SLIST_TYPE ) && ( (*list)._item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // allocate cursor struct
   SList_cursor_type( Prefix ) *cursor = slist_cursor_make( list );
   CHECK( "cursor allocated correctly", cursor != NULL );

   INVARIANT( list );
   POSTCONDITION( "new cursor is last cursor", (*list).last_cursor == cursor );
   UNLOCK( (*list).mutex );

   return cursor;
}

/**
   SList_dispose
*/

void
SList_dispose( Prefix )( SList_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == SLIST_TYPE ) && ( (**current)._item_type == Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete list items
   node_t *node = (**current).first;
   node_t *next = NULL;
   while( node != NULL )
   {
      next = (*node).next;
      node_dispose( &node );
      node = next;
   }

   // delete cursors
   SList_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   SList_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete list struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   SList_deep_dispose
*/

void
SList_deep_dispose( Prefix )( SList_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "*current type ok", ( (**current)._type == SLIST_TYPE ) && ( (**current)._item_type == Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete *current items
   node_t *node = (**current).first;
   node_t *next = NULL;
   while( node != NULL )
   {
      next = (*node).next;
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
      node_dispose( &node );
      node = next;
   }

   // delete cursors
   SList_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   SList_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete *current struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   slist_cursor_dispose
*/
static
void
slist_cursor_dispose( SList_cursor_type( Prefix ) **cursor )
{
   SList_cursor_type( Prefix ) *c1 = NULL;
   SList_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from list structure
   c1 = ( *(**cursor).list ).first_cursor;
   c2 = (*c1).next_cursor;

   // search through the rest of the cursors
   while ( ( c2 != NULL ) && ( flag == 0 ) )
   {
      if ( c2 == *cursor )
      {
         // if we have a match, remove "c2" from the cursor list, set flag
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

   // set list's last cursor
   c1 = ( *(**cursor).list ).first_cursor;
   while ( c1 != NULL )
   {
      c2 = c1;
      c1 = (*c1).next_cursor;
   }
   ( *(**cursor).list ).last_cursor = c2;

   // only one cursor, last_cursor is NULL
   if ( c2 == ( *(**cursor).list ).first_cursor )
   {
      ( *(**cursor).list ).last_cursor = NULL;
   }

   // delete cursor struct
   free(*cursor);

   // set to NULL
   *cursor = NULL;

   return;
};

/**
   SList_cursor_dispose
*/

void
SList_cursor_dispose( Prefix )( SList_cursor_type( Prefix ) **cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "*cursor not null", *cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(**cursor).list )._type == SLIST_TYPE ) && ( ( *(**cursor).list )._item_type == Type_Code ) );
   LOCK( (**cursor).mutex );
   LOCK( ( *(**cursor).list ).mutex );
   INVARIANT( (**cursor).list );

   SList_type( Prefix ) *list = (**cursor).list;

   slist_cursor_dispose( cursor );

   *cursor = NULL;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}


/**
   SList_cursor_item_at
*/

Type
SList_cursor_item_at( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Type value = ( *(*cursor).item ).value;

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}


/**
   SList_item_at
*/

Type
SList_item_at( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   SList_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   Type value = ( *(*cursor).item ).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   SList_item
*/

Type
SList_item( Prefix )( SList_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );

   node_t *node = (*current).first;

   int32_t i = 0;
   for ( i = 1; i <= index; i++ )
   {
      node = (*node).next;
   }

   Type value = (*node).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   SList_first
*/

Type
SList_first( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "first not null", (*current).first != NULL );

   Type value = ( *(*current).first ).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   SList_last
*/

Type
SList_last( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "first not null", (*current).first != NULL );

   Type value = ( *(*current).last ).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   SList_as_array
*/

Type *
SList_as_array( Prefix )( SList_type( Prefix ) *current, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   node_t *node = (*current).first;

   Type *result = ( Type * ) calloc( (*current).count + 1, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   for( i = 0; i < (*current).count; i++ )
   {
      result[i] = (*node).value;
      node = (*node).next;
   }

   (*count) = (*current).count;

   POSTCONDITION( "array contains items of current", compare_list_items_to_array_items( current, result, *count ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   SList_count
*/

int32_t
SList_count( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   SList_off
*/

int32_t
SList_off( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( ( *(*current).first_cursor ).item == NULL );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   SList_cursor_off
*/

int32_t
SList_cursor_off( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = ( (*cursor).item == NULL );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   SList_is_first
*/

int32_t
SList_is_first( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( ( *(*current).first_cursor ).item == (*current).first );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   SList_cursor_is_first
*/

int32_t
SList_cursor_is_first( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = ( (*cursor).item == ( *(*cursor).list ).first );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   SList_is_last
*/

int32_t
SList_is_last( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( ( *(*current).first_cursor ).item ==  (*current).last );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   SList_cursor_is_last
*/

int32_t
SList_cursor_is_last( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = ( (*cursor).item == ( *(*cursor).list ).last );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   SList_index
*/

int32_t
SList_index( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t n = (*current).count;
   node_t *node = (*current).first;
   node_t *target = ( *(*current).first_cursor ).item;

   if ( target == NULL )
   {
      result = -1;
   }
   else
   {
      for ( result = 0; result <= n; result++ )
      {
         if ( node == target )
         {
            break;
         }
         node = (*node).next;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   SList_cursor_index
*/

int32_t
SList_cursor_index( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = 0;
   int32_t n = ( *(*cursor).list ).count;
   node_t *node = ( *(*cursor).list ).first;
   node_t *target = (*cursor).item;

   if ( target == NULL )
   {
      result = -1;
   }
   else
   {
      for ( result = 0; result <= n; result++ )
      {
         if ( node == target )
         {
            break;
         }
         node = (*node).next;
      }
   }

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   SList_is_empty
*/

int32_t
SList_is_empty( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count ==  0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   SList_forth
*/

void
SList_forth( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).item != NULL );

   ( *(*current).first_cursor ).item = ( *( *(*current).first_cursor ).item ).next;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_cursor_forth
*/

void
SList_cursor_forth( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   (*cursor).item = ( *(*cursor).item ).next;

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_go
*/

void
SList_go( Prefix )( SList_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );

   int32_t i = 0;
   ( *(*current).first_cursor ).item = (*current).first;

   for ( i = 1; ( i <= index ) && ( ( *(*current).first_cursor ).item != NULL ); i++ )
   {
      ( *(*current).first_cursor ).item = ( *( *(*current).first_cursor ).item ).next;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_cursor_go
*/

void
SList_cursor_go( Prefix )( SList_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < ( *(*cursor).list ).count ) ) );

   int32_t i = 0;
   (*cursor).item = ( *(*cursor).list ).first;

   for ( i = 1; ( i <= index ) && ( (*cursor).item != NULL ); i++ )
   {
      (*cursor).item = ( *(*cursor).item ).next;
   }

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_start
*/

void
SList_start( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   ( *(*current).first_cursor ).item = (*current).first;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_cursor_start
*/

void
SList_cursor_start( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );

   (*cursor).item = ( *(*cursor).list ).first;

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_put
*/

void
SList_put( Prefix )( SList_type( Prefix ) *current, Type value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*current).count ) ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   int32_t i = 0;
   int32_t flag = 0;
   node_t *node = (*current).first;
   node_t *prev = NULL;


   if ( node == NULL )
   {
      // current is empty, make this the first item if index is 0
      if ( index == 0 )
      {
         node_t *new_node = node_make();
         ( *new_node ).value = value;
         (*current).first = new_node;
         (*current).last = new_node;
         (*current).count = 1;
      }
   }
   else
   {
      // iterate until we get to item index
      flag = 1;
      for ( i = 1; i <= index; i++ )
      {
         prev = node;
         node = (*node).next;
         if ( node == NULL )
         {
            // if no such index, no change to current
            flag = 0;
            break;
         }
      }

      // change the current if index is valid
      if ( flag == 1 )
      {
         node_t *new_node = node_make();
         ( *new_node ).value = value;

         ( *new_node ).next = node;
         (*prev).next = new_node;

         (*current).count = (*current).count + 1;
      }

      // special case for putting new item at end of current
      if ( ( flag == 0 ) && ( index = (*current).count ) )
      {
         node_t *new_node = node_make();
         ( *new_node ).value = value;
         ( *(*current).last ).next = new_node;
         (*current).last = new_node;
         (*current).count = (*current).count + 1;
      }

   }

   POSTCONDITION( "count incremented", (*current).count == ( i_pc + 1 ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_put_right
*/

void
SList_put_right( Prefix )( SList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).item != NULL );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   node_t *node = ( *(*current).first_cursor ).item;

   node_t *new_node = node_make();
   ( *new_node ).value = value;

   ( *new_node ).next = (*node).next;
   (*node).next = new_node;

   if ( (*current).last == node )
   {
      (*current).last = new_node;
   }

   (*current).count = (*current).count + 1;

   POSTCONDITION( "count incremented", (*current).count == i_pc + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_cursor_put_right
*/

void
SList_cursor_put_right( Prefix )( SList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = ( *(*cursor).list ).count; );

   node_t *node = (*cursor).item;

   node_t *new_node = node_make();
   ( *new_node ).value = value;

   ( *new_node ).next = (*node).next;
   (*node).next = new_node;

   if ( ( *(*cursor).list ).last == node )
   {
      ( *(*cursor).list ).last = new_node;
   }

   ( *(*cursor).list ).count = ( *(*cursor).list ).count + 1;

   POSTCONDITION( "count incremented", ( *(*cursor).list ).count == i_pc + 1 );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_put_first
*/

void
SList_put_first( Prefix )( SList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   node_t *node = (*current).first;

   if ( node == NULL )
   {
      node_t *new_node = node_make();
      ( *new_node ).value = value;

      (*current).first = new_node;
      (*current).last = new_node;

      (*current).count = 1;
   }
   else
   {
      node_t *new_node = node_make();
      ( *new_node ).value = value;

      ( *new_node ).next = node;

      (*current).first = new_node;

      (*current).count = (*current).count + 1;
   }

   POSTCONDITION( "count incremented", (*current).count == i_pc + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_put_last
*/

void
SList_put_last( Prefix )( SList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   put_last( current, value );

   POSTCONDITION( "count incremented", (*current).count == i_pc + 1 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   append

   Helper function to append a list to a list

   @param list a SList_t instance
   @param other a SList_t instance to append/insert into list
   @param node1 the node after which to append/insert the list
                 if null, append other to start of list
*/

static
void
append( SList_type( Prefix ) *current, SList_type( Prefix ) *other, node_t *node )
{
   int32_t i = 0;

   if ( node == NULL )
   {
      // prepend other to start of list
      if ( (*other).count > 0 )
      {
         node_t *n1 = (*current).first;

         node_t *new_node = node_make();
         ( *new_node ).value = ( *(*other).first ).value;
         (*current).first = new_node;
         node_t *n = new_node;

         SList_cursor_type( Prefix ) *cursor = slist_cursor_make( other );
         (*cursor).item = ( *(*cursor).list ).first;
         (*cursor).item = ( *(*cursor).item ).next;

         for( i = 1; i < (*other).count; i++ )
         {
            node_t *new_node = node_make();
            ( *new_node ).value = ( *(*cursor).item ).value;
            (*n).next = new_node;
            n = new_node;
         }

         (*n).next = n1;
         if ( n1 == NULL )
         {
            (*current).last = n;
         }

         (*current).count = (*current).count + (*other).count;
         slist_cursor_dispose( &cursor );

      }
   }
   else
   {

      // append/insert other if it's not empty
      if ( (*other).count > 0 )
      {
         node_t *n1 = (*node).next;

         node_t *n = node_make();
         (*n).value = ( *(*other).first ).value;
         (*node).next = n;

         SList_cursor_type( Prefix ) *cursor = slist_cursor_make( other );
         (*cursor).item = ( *(*cursor).list ).first;
         (*cursor).item = ( *(*cursor).item ).next;

         for ( i = 1; i < (*other).count; i++ )
         {
            node_t *new_node = node_make();
            ( *new_node ).value = ( *(*cursor).item ).value;

            (*n).next = new_node;

            n = new_node;
         }

         (*n).next = n1;

         if ( n1 == NULL )
         {
            (*current).last = n;
         }

         (*current).count = (*current).count + (*other).count;
         slist_cursor_dispose( &cursor );

      }


   }

   return;
}

/**
   SList_append
*/

void
SList_append( Prefix )( SList_type( Prefix ) *current, SList_type( Prefix ) *other, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == SLIST_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*current).count ) ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   // lock other
   LOCK( (*other).mutex );

   int32_t i = 0;

   node_t *node = (*current).first;

   if ( ( index == 0 ) || ( node == NULL ) )
   {
      // append is at start of list (like a prepend)
      append( current, other, NULL );
   }
   else
   {
      // iterate until we get to item index
      for ( i = 1; ( i < index ) && ( (*node).next != NULL ); i++ )
      {
         node = (*node).next;
      }

      // append other into list
      if ( i == index )
      {
         append( current, other, node );
      }

   }

   POSTCONDITION( "count correct", (*current).count == i_pc + (*other).count );
   POSTCONDITION( "other is in current", compare_list_in_list( current, other, node ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_append_right
*/

void
SList_append_right( Prefix )( SList_type( Prefix ) *current, SList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == SLIST_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );
   POSTCONDITION_VARIABLE_DEFINE( node_t *node_pc = ( *(*current).first_cursor ).item != NULL ? ( *( *(*current).first_cursor ).item ).next : NULL; );

   // lock other
   LOCK( (*other).mutex );

   node_t *node = ( *(*current).first_cursor ).item;

   append( current, other, node );

   POSTCONDITION( "count correct", (*current).count == i_pc + (*other).count );
   POSTCONDITION( "other is in current", node_pc != NULL ? compare_list_in_list( current, other, node_pc ) : compare_list_in_list( current, other, (*current).first ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_cursor_append_right
*/

void
SList_cursor_append_right( Prefix )( SList_cursor_type( Prefix ) *cursor, SList_type( Prefix ) *other )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "list not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == SLIST_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = ( *(*cursor).list ).count; );
   POSTCONDITION_VARIABLE_DEFINE( node_t *node_pc = (*cursor).item != NULL ? ( *(*cursor).item ).next : NULL; );

   // lock other
   LOCK( (*other).mutex );

   node_t *node = (*cursor).item;

   append( (*cursor).list, other, node );

   POSTCONDITION( "count correct", ( *(*cursor).list ).count == i_pc + (*other).count );
   POSTCONDITION( "other is in current", node_pc != NULL ? compare_list_in_list( (*cursor).list, other, node_pc ) : compare_list_in_list( (*cursor).list, other, ( *(*cursor).list ).first ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_append_first
*/

void
SList_append_first( Prefix )( SList_type( Prefix ) *current, SList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == SLIST_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   // lock other
   LOCK( (*other).mutex );

   append( current, other, NULL );

   POSTCONDITION( "count correct", (*current).count == i_pc + (*other).count );
   POSTCONDITION( "other is in current", compare_list_in_list( current, other, (*current).first ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_append_last
*/

void
SList_append_last( Prefix )( SList_type( Prefix ) *current, SList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == SLIST_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );
   POSTCONDITION_VARIABLE_DEFINE( node_t *node_pc = (*current).last; );

   // lock other
   LOCK( (*other).mutex );

   node_t *node = (*current).last;

   append( current, other, node );

   POSTCONDITION( "count correct", (*current).count == i_pc + (*other).count );
   POSTCONDITION( "other is in current", compare_list_in_list( current, other, node_pc != NULL ? ( *node_pc ).next : (*current).first ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_replace
*/

void
SList_replace( Prefix )( SList_type( Prefix ) *current, Type value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );

   int32_t i = 0;
   node_t *node = (*current).first;

   for ( i = 1; ( i <= index ) && ( node != NULL ); i++ )
   {
      node = (*node).next;
   }

   if ( node != NULL )
   {
      (*node).value = value;
   }

   POSTCONDITION( "value set", slist_item( current, index ) == value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_replace_and_dispose
*/

void
SList_replace_and_dispose( Prefix )( SList_type( Prefix ) *current, Type value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );

   int32_t i = 0;
   node_t *node = (*current).first;

   for ( i = 1; ( i <= index ) && ( node != NULL ); i++ )
   {
      node = (*node).next;
   }

   if ( node != NULL )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
      (*node).value = value;
   }

   POSTCONDITION( "value set", slist_item( current, index ) == value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_replace_at
*/

void
SList_replace_at( Prefix )( SList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).item != NULL );

   if ( ( *(*current).first_cursor ).item != NULL )
   {
      ( *( *(*current).first_cursor ).item ).value = value;
   }

   POSTCONDITION( "value set", ( *( *(*current).first_cursor ).item ).value == value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_replace_at_and_dispose
*/

void
SList_replace_at_and_dispose( Prefix )( SList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).item != NULL );

   if ( ( *(*current).first_cursor ).item != NULL )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( ( *( *(*current).first_cursor ).item ).value );
   }

   ( *( *(*current).first_cursor ).item ).value = value;

   POSTCONDITION( "value set", ( *( *(*current).first_cursor ).item ).value == value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_cursor_replace_at
*/

void
SList_cursor_replace_at( Prefix )( SList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   if ( (*cursor).item != NULL )
   {
      ( *(*cursor).item ).value = value;
   }

   POSTCONDITION( "value set", ( *(*cursor).item ).value == value );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_cursor_replace_at_and_dispose
*/

void
SList_cursor_replace_at_and_dispose( Prefix )( SList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   if ( (*cursor).item != NULL )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( ( *(*cursor).item ).value );
   }

   ( *(*cursor).item ).value = value;

   POSTCONDITION( "value set", ( *(*cursor).item ).value == value );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   remove

   Helper function to remove an item from a current

   @param current a SList_t instance
   @param node1 the node to remove
*/

static
void
remove( SList_type( Prefix ) *current, node_t *node )
{
   node_t *n = NULL;

   if ( node != NULL )
   {
      move_all_cursors_at_node_forth( current, node );

      // only item in current
      if ( (*current).count == 1 )
      {
         (*current).first = NULL;
         (*current).last = NULL;
         (*current).count = 0;
         node_dispose( &node );
      }
      // first item in current
      else if ( (*current).first == node )
      {
         (*current).first = (*node).next;
         (*current).count = (*current).count - 1;
         node_dispose( &node );
      }
      // last item in current
      else if ( (*current).last == node )
      {
         n = node_at_index( current, (*current).count - 2 );
         (*current).last = n;
         (*n).next = NULL;
         (*current).count = (*current).count - 1;
         node_dispose( &node );
      }
      // not first, not last item in current
      else
      {
         n = node_before( current, node );
         (*n).next = (*node).next;
         (*current).count = (*current).count - 1;
         node_dispose( &node );
      }

   }

   return;
}

/**
   remove_and_dispose

   Helper function to remove an item from a current and dispose of its value

   @param current a SList_t instance
   @param node1 the node to remove
*/

static
void
remove_and_dispose( SList_type( Prefix ) *current, node_t *node )
{
   node_t *n = NULL;

   if ( node != NULL )
   {
      move_all_cursors_at_node_forth( current, node );

      // only item in current
      if ( (*current).count == 1 )
      {
         (*current).first = NULL;
         (*current).last = NULL;
         (*current).count = 0;
         VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
      }
      // first item in current
      else if ( (*current).first == node )
      {
         (*current).first = (*node).next;
         (*current).count = (*current).count - 1;
         VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
      }
      // last item in current
      else if ( (*current).last == node )
      {
         n = node_at_index( current, (*current).count - 2 );
         (*current).last = n;
         (*n).next = NULL;
         (*current).count = (*current).count - 1;
         VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
      }
      // not first, not last item in current
      else
      {
         n = node_before( current, node );
         (*n).next = (*node).next;
         (*current).count = (*current).count - 1;
         VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
      }

   }

   return;
}

/**
   SList_remove
*/

void
SList_remove( Prefix )( SList_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = slist_item( current, index ); int32_t i_pc = occurrences( current, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   int32_t i = 0;
   node_t *node = (*current).first;

   for ( i = 1; ( i <= index ) && ( node != NULL ); i++ )
   {
      node = (*node).next;
   }

   // remove the node
   remove( current, node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_remove_and_dispose
*/

void
SList_remove_and_dispose( Prefix )( SList_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = slist_item( current, index ); int32_t i_pc = occurrences( current, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   int32_t i = 0;
   node_t *node = (*current).first;

   for ( i = 1; ( i <= index ) && ( node != NULL ); i++ )
   {
      node = (*node).next;
   }

   // remove the node
   remove_and_dispose( current, node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_remove_at
*/

void
SList_remove_at( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).item != NULL );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *( *(*current).first_cursor ).item ).value; int32_t i_pc = occurrences( current, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = ( *(*current).first_cursor ).item;

   // remove the node
   remove( current, node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_remove_at_and_dispose
*/

void
SList_remove_at_and_dispose( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).item != NULL );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *( *(*current).first_cursor ).item ).value; int32_t i_pc = occurrences( current, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = ( *(*current).first_cursor ).item;

   // remove the node
   remove_and_dispose( current, node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_cursor_remove_at
*/

void
SList_cursor_remove_at( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   INVARIANT( (*cursor).list );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *(*cursor).item ).value; int32_t i_pc = occurrences( (*cursor).list, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).list ).count; );

   node_t *node = (*cursor).item;
   SList_type( Prefix ) *list = (*cursor).list;

   // remove the node
   remove( list, node );

   POSTCONDITION( "element removed", i_pc == occurrences( (*cursor).list, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == ( *(*cursor).list ).count + 1 );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_cursor_remove_at_and_dispose
*/

void
SList_cursor_remove_at_and_dispose( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   INVARIANT( (*cursor).list );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *(*cursor).item ).value; int32_t i_pc = occurrences( (*cursor).list, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).list ).count; );

   node_t *node = (*cursor).item;
   SList_type( Prefix ) *list = (*cursor).list;

   // remove the node
   remove_and_dispose( list, node );

   POSTCONDITION( "element removed", i_pc == occurrences( (*cursor).list, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == ( *(*cursor).list ).count + 1 );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_remove_first
*/

void
SList_remove_first( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "not empty", ( (*current).count > 0 ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *(*current).first ).value; int32_t i_pc = occurrences( current, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = (*current).first;

   // remove the node
   remove( current, node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_remove_first_and_dispose
*/

void
SList_remove_first_and_dispose( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "not empty", ( (*current).count > 0 ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *(*current).first ).value; int32_t i_pc = occurrences( current, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = (*current).first;

   // remove the node
   remove_and_dispose( current, node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_remove_last
*/

void
SList_remove_last( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "not empty", ( (*current).count > 0 ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *(*current).last ).value; int32_t i_pc = occurrences( current, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = (*current).last;

   // remove the node
   remove( current, node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_remove_last_and_dispose
*/

void
SList_remove_last_and_dispose( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "not empty", ( (*current).count > 0 ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *(*current).last ).value; int32_t i_pc = occurrences( current, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = (*current).last;

   // remove the node
   remove_and_dispose( current, node );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   prune

   Helper function to remove a subcurrent out of a current

   @param current a SList_t instance
   @param node1 the start node to remove
   @param node2 the end node to remove
*/

static
void
prune( SList_type( Prefix ) *current, node_t *node_start, int32_t count )
{
   int32_t i = 0;
   int32_t n = 0;
   node_t *node = node_start;
   node_t *n1 = NULL;
   node_t *ns = NULL;

   // move all cursors off - current will be mangled
   move_all_cursors_off( current );

   // node is first node
   if ( node == (*current).first )
   {
      // dispose of nodes
      for ( i = 0; i < count; i++ )
      {
         n1 = (*node).next;
         node_dispose( &node );
         node = n1;
         if ( node == NULL )
         {
            break;
         }
      }

      // set new first item in current
      (*current).first = node;

      // decrement current count
      (*current).count = (*current).count - count;

      // if current now only has one item, set last
      if ( (*current).count == 1 )
      {
         (*current).last = node;
      }

      // if current is now empty, set first and last to null
      if ( (*current).count <= 0 )
      {
         (*current).first = NULL;
         (*current).last = NULL;
         (*current).count = 0;
      }

   }

   // node is last node
   else if ( node == (*current).last )
   {
      n1 = node_before( current, node );

      // set previous node as last
      (*n1).next = NULL;
      (*current).last = n1;

      // dispose of node
      node_dispose( &node );

      // decrement current count
      (*current).count = (*current).count - 1;

      // if current now only has one item, set first
      if ( (*current).count == 1 )
      {
         (*current).first = (*current).last;
      }

   }
   // node is neither first nor last node
   else
   {
      ns = node_before( current, node );

      // dispose of nodes
      n = 0;
      for ( i = 0; i < count; i++ )
      {
         n1 = (*node).next;
         node_dispose( &node );
         n++;
         node = n1;
         if ( node == NULL )
         {
            break;
         }
      }

      // set prev and next node pointers
      (*ns).next = node;

      // ns may be the last in the current
      if ( (*ns).next == NULL )
      {
         (*current).last = ns;
      }

      // node may be the last in the current
      if ( node != NULL )
      {
         if ( (*node).next == NULL )
         {
            (*current).last = node;
         }
      }

      // decrement current count
      (*current).count = (*current).count - n;

   }

   return;
}

/**
   prune_and_dispose

   Helper function to remove a subcurrent out of a current and dispose of its
   values.

   @param current a SList_t instance
   @param node1 the start node to remove
   @param node2 the end node to remove
*/

static
void
prune_and_dispose( SList_type( Prefix ) *current, node_t *node_start, int32_t count )
{
   int32_t i = 0;
   int32_t n = 0;
   node_t *node = node_start;
   node_t *n1 = NULL;
   node_t *ns = NULL;

   // move all cursors off - current will be mangled
   move_all_cursors_off( current );

   // node is first node
   if ( node == (*current).first )
   {
      // dispose of nodes
      for ( i = 0; i < count; i++ )
      {
         n1 = (*node).next;
         VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
         node = n1;
         if ( node == NULL )
         {
            break;
         }
      }

      // set new first item in current
      (*current).first = node;

      // decrement current count
      (*current).count = (*current).count - count;

      // if current now only has one item, set last
      if ( (*current).count == 1 )
      {
         (*current).last = node;
      }

      // if current is now empty, set first and last to null
      if ( (*current).count <= 0 )
      {
         (*current).first = NULL;
         (*current).last = NULL;
         (*current).count = 0;
      }

   }

   // node1 is last node
   else if ( node == (*current).last )
   {
      n1 = node_before( current, node );

      // set previous node as last
      (*n1).next = NULL;
      (*current).last = n1;

      // dispose of node
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
      node_dispose( &node );

      // decrement current count
      (*current).count = (*current).count - 1;

      // if current now only has one item, set first
      if ( (*current).count == 1 )
      {
         (*current).first = (*current).last;
      }

   }
   // node is neither first nor last node
   else
   {
      ns = node_before( current, node );

      // dispose of nodes
      n = 0;
      for ( i = 0; i < count; i++ )
      {
         n1 = (*node).next;
         VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
         n++;
         node = n1;
         if ( node == NULL )
         {
            break;
         }
      }

      // set prev and next node pointers
      (*ns).next = node;

      // ns may be the last in the current
      if ( (*ns).next == NULL )
      {
         (*current).last = ns;
      }

      // node may be the last in the current
      if ( node != NULL )
      {
         if ( (*node).next == NULL )
         {
            (*current).last = node;
         }
      }

      // decrement current count
      (*current).count = (*current).count - n;

   }

   return;
}


/**
   SList_prune
*/

void
SList_prune( Prefix )( SList_type( Prefix ) *current, int32_t index, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   int32_t i = 0;

   node_t *node = (*current).first;

   for ( i = 1; ( i <= index ) && ( node != NULL ); i++ )
   {
      node = (*node).next;
   }

   if ( node != NULL )
   {
      prune( current, node, count );
   }

   POSTCONDITION( "count ok", i_pc_count == (*current).count + count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_prune_and_dispose
*/

void
SList_prune_and_dispose( Prefix )( SList_type( Prefix ) *current, int32_t index, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   int32_t i = 0;

   node_t *node = (*current).first;

   for ( i = 1; ( i <= index ) && ( node != NULL ); i++ )
   {
      node = (*node).next;
   }

   if ( node != NULL )
   {
      prune_and_dispose( current, node, count );
   }

   POSTCONDITION( "count ok", i_pc_count == (*current).count + count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_prune_first
*/

void
SList_prune_first( Prefix )( SList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", ( (*current).count >= count ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = (*current).first;

   prune( current, node, count );

   POSTCONDITION( "count ok", i_pc_count == (*current).count + count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_prune_first_and_dispose
*/

void
SList_prune_first_and_dispose( Prefix )( SList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", ( (*current).count >= count ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = (*current).first;

   prune_and_dispose( current, node, count );

   POSTCONDITION( "count ok", i_pc_count == (*current).count + count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_prune_last
*/

void
SList_prune_last( Prefix )( SList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", ( (*current).count >= count ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = (*current).last;

   node = node_at_index( current, (*current).count - count );

   if ( node != NULL )
   {
      prune( current, node, count );
   }

   POSTCONDITION( "count ok", i_pc_count == (*current).count + count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_prune_last_and_dispose
*/

void
SList_prune_last_and_dispose( Prefix )( SList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", ( (*current).count >= count ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   node_t *node = (*current).last;

   node = node_at_index( current, (*current).count - count );

   if ( node != NULL )
   {
      prune_and_dispose( current, node, count );
   }

   POSTCONDITION( "count ok", i_pc_count == (*current).count + count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_keep_first
*/

void
SList_keep_first( Prefix )( SList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", ( (*current).count >= count ) );
   INVARIANT( current );

   int32_t i = 0;

   node_t *node = (*current).first;

   // walk through the items to keep
   for ( i = 1; ( i < count ) && ( node != NULL ); i++ )
   {
      node = (*node).next;
   }

   // point to the first item to remove
   if ( count > 0 )
   {
      node = (*node).next;
   }

   if ( node != NULL )
   {
      prune( current, node, (*current).count - count );
   }

   POSTCONDITION( "count ok", (*current).count == count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_keep_first_and_dispose
*/

void
SList_keep_first_and_dispose( Prefix )( SList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", ( (*current).count >= count ) );
   INVARIANT( current );

   int32_t i = 0;

   node_t *node = (*current).first;

   // point to the first item to remove
   for ( i = 1; ( i < count ) && ( node != NULL ); i++ )
   {
      node = (*node).next;
   }

   // point to the first item to remove
   if ( count > 0 )
   {
      node = (*node).next;
   }

   if ( node != NULL )
   {
      prune_and_dispose( current, node, (*current).count - count );
   }

   POSTCONDITION( "count ok", (*current).count == count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_keep_last
*/

void
SList_keep_last( Prefix )( SList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", ( (*current).count >= count ) );
   INVARIANT( current );

   node_t *node = (*current).first;

   prune( current, node, (*current).count - count );

   POSTCONDITION( "count ok", (*current).count == count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_keep_last_and_dispose
*/

void
SList_keep_last_and_dispose( Prefix )( SList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", ( (*current).count >= count ) );
   INVARIANT( current );

   node_t *node = (*current).first;

   prune_and_dispose( current, node, (*current).count - count );

   POSTCONDITION( "count ok", (*current).count == count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_wipe_out
*/

void
SList_wipe_out( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   node_t *node = (*current).first;
   node_t *next = NULL;

   // move all cursors off - current will be mangled
   move_all_cursors_off( current );

   // remove all nodes
   while ( node != NULL )
   {
      next = (*node).next;
      node_dispose( &node );
      node = next;
   }

   (*current).count = 0;
   (*current).first = NULL;
   (*current).last = NULL;

   POSTCONDITION( "current is empty", (*current).count == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_wipe_out_and_dispose
*/

void
SList_wipe_out_and_dispose( Prefix )( SList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   node_t *node = (*current).first;
   node_t *next = NULL;

   // move all cursors off - current will be mangled
   move_all_cursors_off( current );

   // remove all nodes and values
   while ( node != NULL )
   {
      next = (*node).next;
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
      node_dispose( &node );
      node = next;
   }

   (*current).count = 0;
   (*current).first = NULL;
   (*current).last = NULL;

   POSTCONDITION( "current is empty", (*current).count == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_has
*/
int32_t
SList_has( Prefix )( SList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( node_t *node_pc = ( *(*current).first_cursor ).item; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t result = 0;

   result = has( current, value );

   POSTCONDITION( "current first cursor unchanged", node_pc == ( *(*current).first_cursor ).item );
   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   SList_has_eq_fn
*/
int32_t
SList_has_eq_fn( Prefix )
(
   SList_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( node_t *node_pc = ( *(*current).first_cursor ).item; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t result = 0;

   result = has_eq_fn( current, value, equality_test_func );

   POSTCONDITION( "current first cursor unchanged", node_pc == ( *(*current).first_cursor ).item );
   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   SList_search_forth
*/
void
SList_search_forth( Prefix )( SList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).item != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   node_t *node = NULL;

   node = ( *(*current).first_cursor ).item;

   while( node != NULL )
   {
      // see if value is equal to current item
      if ( node != NULL )
      {
         if ( (*node).value == value )
         {
            // if so, exit with first_cursor set to found value
            // update internal cursor
            ( *(*current).first_cursor ).item = node;

            break;
         }
      }

      // increment node pointer
      node = (*node).next;

      // update internal cursor
      ( *(*current).first_cursor ).item = node;

   }

   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_search_forth_eq_fn
*/
void
SList_search_forth_eq_fn( Prefix )
(
   SList_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).item != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   node_t *node = NULL;

   node = ( *(*current).first_cursor ).item;

   while( node != NULL )
   {
      // see if value is equal to current item
      if ( node != NULL )
      {
         if ( equality_test_func( (*node).value, value ) == 1 )
         {
            // if so, exit with first_cursor set to found value
            // update internal cursor
            ( *(*current).first_cursor ).item = node;

            break;
         }
      }

      // increment node pointer
      node = (*node).next;

      // update internal cursor
      ( *(*current).first_cursor ).item = node;

   }

   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   SList_cursor_search_forth
*/
void
SList_cursor_search_forth( Prefix )( SList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = ( *(*cursor).list ).count; );

   node_t *node = NULL;

   node = (*cursor).item;

   while( node != NULL )
   {
      // see if value is equal to current item
      if ( node != NULL )
      {
         if ( (*node).value == value )
         {
            // if so, exit with first_cursor set to found value
            // update internal cursor
            (*cursor).item = node;

            break;
         }
      }

      // increment node pointer
      node = (*node).next;

      // update internal cursor
      (*cursor).item = node;

   }

   POSTCONDITION( "current count unchanged", count_pc == ( *(*cursor).list ).count );
   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_cursor_search_forth_eq_fn
*/
void
SList_cursor_search_forth_eq_fn( Prefix )
(
   SList_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == SLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = ( *(*cursor).list ).count; );

   node_t *node = NULL;

   node = (*cursor).item;

   while( node != NULL )
   {
      // see if value is equal to current item
      if ( node != NULL )
      {
         if ( equality_test_func( (*node).value, value ) == 1 )
         {
            // if so, exit with first_cursor set to found value
            // update internal cursor
            (*cursor).item = node;

            break;
         }
      }

      // increment node pointer
      node = (*node).next;

      // update internal cursor
      (*cursor).item = node;

   }

   POSTCONDITION( "current count unchanged", count_pc == ( *(*cursor).list ).count );
   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_occurrences
*/
int32_t
SList_occurrences( Prefix )( SList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( node_t *node_pc = ( *(*current).first_cursor ).item; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t result = 0;

   result = occurrences( current, value );

   POSTCONDITION( "current first cursor unchanged", node_pc == ( *(*current).first_cursor ).item );
   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   SList_occurrences_eq_fn
*/
int32_t
SList_occurrences_eq_fn( Prefix )
(
   SList_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( node_t *node_pc = ( *(*current).first_cursor ).item; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t result = 0;

   result = occurrences_eq_fn( current, value, equality_test_func );

   POSTCONDITION( "current first cursor unchanged", node_pc == ( *(*current).first_cursor ).item );
   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   SList_swap
*/
void
SList_swap( Prefix )( SList_type( Prefix ) *current, int32_t i, int32_t j )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "i ok", ( ( i >= 0 ) && ( i < (*current).count ) ) );
   PRECONDITION( "j ok", ( ( j >= 0 ) && ( j < (*current).count ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( node_t *node_pc = ( *(*current).first_cursor ).item; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   node_t *node = NULL;
   node_t *node_1 = NULL;
   node_t *node_2 = NULL;
   int32_t index = 0;
   Type v;

   node = (*current).first;

   for ( index = 0; index < (*current).count; index++ )
   {
      if ( index == i )
      {
         node_1 = node;
      }

      if ( index == j )
      {
         node_2 = node;
      }

      if ( ( node_1 != NULL ) && ( node_2 != NULL ) )
      {
         break;
      }

      node = (*node).next;
   }

   if ( ( node_1 != NULL ) && ( node_2 != NULL ) )
   {
      v = ( *node_1 ).value;
      ( *node_1 ).value = ( *node_2 ).value;
      ( *node_2 ).value = v;
   }

   POSTCONDITION( "current first cursor unchanged", node_pc == ( *(*current).first_cursor ).item );
   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Sorting stuff
*/

static MULTITHREAD_MUTEX_DEFINITION_INIT( sort_mutex );

static
int32_t ( *value_sort_func_name )( Type v1, Type v2 ) = NULL;

/**
   node_sort_func

   compare nodes by their value accorting to value_sort_func
*/

static
int32_t
node_sort_func( node_t **n1, node_t **n2 )
{
   int32_t result = value_sort_func_name( (**n1).value, (**n2).value );
   return result;
}

/**
   SList_sort
*/

void
SList_sort( Prefix )( SList_type( Prefix ) *current, int32_t ( *sort_func )( Type v1, Type v2 ) )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "sort_func not null", sort_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // array to use for sorting
   node_t **array = NULL;
   node_t *node = NULL;
   node_t *last_node = NULL;
   int32_t i = 0;

   // only sort if there's enough to sort
   if ( (*current).count > 1 )
   {
      array = ( node_t ** ) calloc( (*current).count, sizeof( node_t * ) );
      CHECK( "array allocated correctly", array != NULL );

      // fill the array
      node = (*current).first;

      for( i = 0; i < (*current).count; i++ )
      {
         array[i] = node;
         node = (*node).next;
      }

      // get the sort mutex
      LOCK( sort_mutex );

      // set the sort func
      value_sort_func_name = sort_func;

      // sort the array
      qsort( array, (*current).count, sizeof( node_t * ), ( int (*)( const void*, const void* ) ) node_sort_func );

      // release the sort mutex
      UNLOCK( sort_mutex );

      // put sorted items into current
      node = array[0];
      (*current).first = node;
      (*node).next = array[1];

      node = (*node).next;

      for( i = 1; i < (*current).count; i++ )
      {
         if ( i == ( (*current).count - 1 ) )
         {
            (*node).next = NULL;
         }
         else
         {
            (*node).next = array[i + 1];
         }
         last_node = node;
         node = (*node).next;
      }

      (*current).last = last_node;

      // reset cursors
      move_all_cursors_off( current );

      free( array );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/* End of file */
