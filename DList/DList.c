/**
 @file DList.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Doubly linked lists (next and previous)"

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

 Function definitions for the opaque DList_t type.

*/

#include "DList.h"

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_Indexable.ph"
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
   Node structure. Holds a value
*/

struct node
{
   struct node *next;
   struct node *prev;
   Type value;
};

typedef struct node node_t;

/**
   Linked list structure
*/

struct DList_struct( Prefix )
{

   PROTOCOLS_DEFINITION;

   int32_t _type;
   int32_t _item_type;

   node_t *first;
   node_t *last;
   int32_t count;
   DList_cursor_type( Prefix ) *first_cursor;
   DList_cursor_type( Prefix ) *last_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure. Accesses list and holds a location.
*/

struct DList_cursor_struct( Prefix )
{
   DList_type( Prefix ) *list;
   node_t *item;
   DList_cursor_type( Prefix ) *next_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};


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
   free(*node);
   *node = NULL;
   return;
}

/**
   move_all_cursors_at_node_forth

   After a node has been removed, move all cursors pointing to that node
   forth.

   @param current DList_t instance
   @param node the just removed node
*/
static
void
move_all_cursors_at_node_forth
(
   DList_type( Prefix ) *current,
   node_t *node
)
{
   DList_cursor_type( Prefix ) *cursor = NULL;

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
   DList_type( Prefix ) *current
)
{
   DList_cursor_type( Prefix ) *cursor = NULL;

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

   compare all items in the list to items in an array

   @param current the list
   @param array the array
   @param count the number of items in the array
   @return 1 if the items are equal, 0 otherwise
*/

static
int32_t
compare_list_items_to_array_items
(
   DList_type( Prefix ) *current,
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
   compare list items to list items

   compare items in one list to items in another list

   @param current the list to compare
   @param other the other list to compare with
   @return 1 if items are equal, 0 otherwise
*/

static
int32_t
compare_list_items_to_list_items
(
   DList_type( Prefix ) *current,
   DList_type( Prefix ) *other
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

   compare items in two lists for deep equality

   @param current the list to compare to
   @param other the list to compare
   @return 1 if deep equal, 0 otherwise
*/

static
int32_t
compare_list_items_to_list_items_deep_equal
(
   DList_type( Prefix ) *current,
   DList_type( Prefix ) *other
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

   compare part of a list to part of another list, starting at a particular node

   @param current the list to compare to
   @param other the list to compare
   @param node the node to start comparing values (to end of the lists)
   @return 1 if values equal, 0 otherwise
*/

static
int32_t
compare_list_in_list
(
   DList_type( Prefix ) *current,
   DList_type( Prefix ) *other,
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

   Returns 1 if DList contains item using "==" as comparison test

   @param current the DList
   @param item the item to look for
   @return 1 if found, 0 otherwise
*/
static
int32_t
has
(
   DList_type( Prefix ) *current,
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

   Returns 1 if DList contains item using equality_test_func as comparison test

   @param current the DList
   @param item the item to look for
   @param equality_test_func the function to compare values with
   @return 1 if found, 0 otherwise
*/
static
int32_t
has_eq_fn
(
   DList_type( Prefix ) *current,
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

   count how many times a node in a list contains a value equal to a specified value

   @param current the list
   @param value the value to look for
   @return the count of node that have a value equal to value
*/

static
int32_t
occurrences( DList_type( Prefix ) *current, Type value )
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

   count how many times a node in a list contains a value equal to a specified
   value, using a specified equality function

   @param current the list
   @param value the value to look for
   @param equality_test_function tests two values for equality
   @return the count of node that have a value equal to value
*/

static
int32_t
occurrences_eq_fn
(
   DList_type( Prefix ) *current,
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
   dlist_item

   get the value for the node at index

   @param current the list
   @param index the index
   @return the value in the list at index, or 0/NULL if not found
*/

static
Type
dlist_item( DList_type( Prefix ) *current, int32_t index )
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
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
is_empty_implies_first_last_null( DList_type( Prefix ) *current )
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
nonnegative_count( DList_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).count >= 0 );

   return result;
}

static
int32_t
valid_count( DList_type( Prefix ) *current )
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
first_cursor_not_null( DList_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).first_cursor != NULL );

   return result;
}

static
int32_t
last_cursor_next_null( DList_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).last_cursor != NULL )
   {
      result = ( ( *(*current).last_cursor ).next_cursor == NULL );
   }

   return result;
}

static
void invariant( DList_type( Prefix ) *current )
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
   DList_dispose( Prefix ),
   DList_deep_dispose( Prefix ),
   DList_is_equal( Prefix ),
   DList_is_deep_equal( Prefix ),
   DList_copy( Prefix ),
   DList_deep_copy( Prefix ),
   DList_clone( Prefix ),
   DList_deep_clone( Prefix )
};

static
void *
p_indexable_table[P_INDEXABLE_FUNCTION_COUNT]
=
{
   DList_count( Prefix ),
   DList_item( Prefix ),
   DList_replace( Prefix ),
   DList_replace_and_dispose( Prefix )
};

static
void *
p_iterable_table[P_ITERABLE_FUNCTION_COUNT]
=
{
   DList_count( Prefix ),
   DList_item_at( Prefix ),
   DList_off( Prefix ),
   DList_is_empty( Prefix ),
   DList_start( Prefix ),
   DList_forth( Prefix )
};

static
void *
p_diterable_table[P_DITERABLE_FUNCTION_COUNT]
=
{
   DList_count( Prefix ),
   DList_item_at( Prefix ),
   DList_off( Prefix ),
   DList_is_empty( Prefix ),
   DList_start( Prefix ),
   DList_forth( Prefix ),
   DList_finish( Prefix ),
   DList_back( Prefix )
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
   put_last
*/

static
void
put_last( DList_type( Prefix ) *current, Type value )
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

      ( *new_node ).prev = node;
      ( *new_node ).next = NULL;
      (*node).next = new_node;

      (*current).last = new_node;

      (*current).count = (*current).count + 1;
   }

   return;
}


/**
   DList_make
*/

DList_type( Prefix ) *
DList_make( Prefix )( void )
{
   // allocate list struct
   DList_type( Prefix ) *result
      = ( DList_type( Prefix ) * ) calloc( 1, sizeof( DList_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = DLIST_TYPE;
   (*result)._item_type = Type_Code;

   // set built-in cursor

   // allocate cursor struct
   DList_cursor_type( Prefix ) *cursor
      =  ( DList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DList_cursor_type( Prefix ) ) );
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
   DList_make_from_array
*/

DList_type( Prefix ) *
DList_make_from_array( Prefix )( Type *array, int32_t count )
{
   PRECONDITION( "array not null", array != NULL );
   PRECONDITION( "count ok", count >= 0 );

   // allocate list struct
   DList_type( Prefix ) *result
      = ( DList_type( Prefix ) * ) calloc( 1, sizeof( DList_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = DLIST_TYPE;
   (*result)._item_type = Type_Code;

   // set built-in cursor

   // allocate cursor struct
   DList_cursor_type( Prefix ) *cursor
      =  ( DList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DList_cursor_type( Prefix ) ) );
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
   DList_clone
*/

DList_type( Prefix ) *
DList_clone( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );

   int32_t i = 0;
   node_t *node = NULL;

   // allocate list struct
   DList_type( Prefix ) * result
      = ( DList_type( Prefix ) * ) calloc( 1, sizeof( DList_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = DLIST_TYPE;
   (*result)._item_type = Type_Code;

   // set built-in cursor

   // allocate cursor struct
   DList_cursor_type( Prefix ) *cursor
      =  ( DList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DList_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set list
   (*cursor).list = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set list built-in cursor
   (*result).first_cursor = cursor;

   // copy from current
   LOCK( (*current).mutex );

   node = (*current).first;

   for ( i = 0; i < (*current).count; i++ )
   {
      put_last( result, (*node).value );
      node = (*node).next;
   }

   (*result).count = (*current).count;

   UNLOCK( (*current).mutex );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new list cursor is off", ( *(*result).first_cursor ).item == NULL );
   POSTCONDITION( "new list contains elements of current", compare_list_items_to_list_items( result, current ) );

   INVARIANT( result );

   return result;
}

/**
   DList_deep_clone
*/

DList_type( Prefix ) *
DList_deep_clone( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );

   int32_t i = 0;
   node_t *node = NULL;
   Type v;

   // allocate list struct
   DList_type( Prefix ) * result
      = ( DList_type( Prefix ) * ) calloc( 1, sizeof( DList_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = DLIST_TYPE;
   (*result)._item_type = Type_Code;

   // set built-in cursor

   // allocate cursor struct
   DList_cursor_type( Prefix ) *cursor
      =  ( DList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DList_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set list
   (*cursor).list = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set list built-in cursor
   (*result).first_cursor = cursor;

   // copy from "list"
   LOCK( (*current).mutex );

   node = (*current).first;

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
   DList_is_equal
*/

int32_t
DList_is_equal( Prefix )( DList_type( Prefix ) *current, DList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DLIST_TYPE ) && ( (*other)._item_type = Type_Code ) );

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
   DList_is_deep_equal
*/

int32_t
DList_is_deep_equal( Prefix )( DList_type( Prefix ) *current, DList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DLIST_TYPE ) && ( (*other)._item_type = Type_Code ) );

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
   DList_copy
*/

void
DList_copy( Prefix )( DList_type( Prefix ) *current, DList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DLIST_TYPE ) && ( (*other)._item_type = Type_Code ) );

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
   DList_deep_copy
*/

void
DList_deep_copy( Prefix )( DList_type( Prefix ) *current, DList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DLIST_TYPE ) && ( (*other)._item_type = Type_Code ) );

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
   dlist_cursor_make
*/
static
DList_cursor_type( Prefix ) *
dlist_cursor_make( DList_type( Prefix ) *current )
{
   // allocate cursor struct
   DList_cursor_type( Prefix ) *cursor
      =  ( DList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DList_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set list
   (*cursor).list = current;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // place cursor reference into list structure
   if ( (*current).last_cursor == NULL )
   {
      // set second cursor for list
      ( *(*current).first_cursor ).next_cursor = cursor;
      (*current).last_cursor = cursor;
   }
   else
   {
      // set additional cursor for list
      // (*current).last_cursor holds last cursor allocated
      ( *(*current).last_cursor ).next_cursor = cursor;
      (*current).last_cursor = cursor;
   }

   MULTITHREAD_MUTEX_INIT( (*cursor).mutex );

   return cursor;
};

/**
   DList_cursor_make
*/

DList_cursor_type( Prefix ) *
DList_cursor_make( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   DList_cursor_type( Prefix ) *cursor = dlist_cursor_make( current );

   INVARIANT( current );
   POSTCONDITION( "new cursor is last cursor", (*current).last_cursor == cursor );
   UNLOCK( (*current).mutex );

   return cursor;
}

/**
   DList_dispose
*/

void
DList_dispose( Prefix )( DList_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == DLIST_TYPE ) && ( (**current)._item_type == Type_Code ) );
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
   DList_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   DList_cursor_type( Prefix ) *next_cursor = NULL;
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
   DList_deep_dispose
*/

void
DList_deep_dispose( Prefix )( DList_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == DLIST_TYPE ) && ( (**current)._item_type == Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete list items
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
   DList_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   DList_cursor_type( Prefix ) *next_cursor = NULL;
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
   dlist_cursor_dispose
*/
static
void
dlist_cursor_dispose( DList_cursor_type( Prefix ) **cursor )
{
   DList_cursor_type( Prefix ) *c1 = NULL;
   DList_cursor_type( Prefix ) *c2 = NULL;
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
   DList_cursor_dispose
*/

void
DList_cursor_dispose( Prefix )( DList_cursor_type( Prefix ) **cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "*cursor not null", *cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(**cursor).list )._type == DLIST_TYPE ) && ( ( *(**cursor).list )._item_type == Type_Code ) );
   LOCK( (**cursor).mutex );
   LOCK( ( *(**cursor).list ).mutex );
   INVARIANT( (**cursor).list );

   DList_type( Prefix ) *list = (**cursor).list;

   dlist_cursor_dispose( cursor );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}


/**
   DList_cursor_item_at
*/

Type
DList_cursor_item_at( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
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
   DList_item_at
*/

Type
DList_item_at( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   DList_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   Type value = ( *(*cursor).item ).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   DList_cursor_item_next
*/

Type
DList_cursor_item_next( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "not off", (*cursor).item != NULL );
   PRECONDITION( "next not off", ( *(*cursor).item ).next != NULL );

   Type value = ( *( *(*cursor).item ).next ).value;

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}

/**
   DList_item_next
*/

Type
DList_item_next( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );
   PRECONDITION( "next not off", ( *( *(*current).first_cursor ).item ).next != NULL );

   Type value = ( *( *( *(*current).first_cursor ).item ).next ).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   DList_cursor_item_prev
*/

Type
DList_cursor_item_prev( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "not off", (*cursor).item != NULL );
   PRECONDITION( "prev not off", ( *(*cursor).item ).prev != NULL );

   Type value = ( *( *(*cursor).item ).prev ).value;

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}

/**
   DList_item_prev
*/

Type
DList_item_prev( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );
   PRECONDITION( "next not off", ( *( *(*current).first_cursor ).item ).prev != NULL );

   Type value = ( *( *( *(*current).first_cursor ).item ).prev ).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   DList_item
*/

Type
DList_item( Prefix )( DList_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_first
*/

Type
DList_first( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "first not null", (*current).first != NULL );

   Type value = ( *(*current).first ).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   DList_last
*/

Type
DList_last( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "first not null", (*current).first != NULL );

   Type value = ( *(*current).last ).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   DList_as_array
*/

Type *
DList_as_array( Prefix )( DList_type( Prefix ) *current, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_count
*/

int32_t
DList_count( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   DList_off
*/

int32_t
DList_off( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( ( *(*current).first_cursor ).item == NULL );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DList_cursor_off
*/

int32_t
DList_cursor_off( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
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
   DList_is_first
*/

int32_t
DList_is_first( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( ( *(*current).first_cursor ).item == (*current).first );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DList_cursor_is_first
*/

int32_t
DList_cursor_is_first( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
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
   DList_is_last
*/

int32_t
DList_is_last( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( ( *(*current).first_cursor ).item ==  (*current).last );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DList_cursor_is_last
*/

int32_t
DList_cursor_is_last( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
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
   DList_index
*/

int32_t
DList_index( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_cursor_index
*/

int32_t
DList_cursor_index( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
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
   DList_is_empty
*/

int32_t
DList_is_empty( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count ==  0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   DList_forth
*/

void
DList_forth( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).item != NULL );

   ( *(*current).first_cursor ).item = ( *( *(*current).first_cursor ).item ).next;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DList_cursor_forth
*/

void
DList_cursor_forth( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
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
   DList_back
*/

void
DList_back( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).item != NULL );

   ( *(*current).first_cursor ).item = ( *( *(*current).first_cursor ).item ).prev;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DList_cursor_back
*/

void
DList_cursor_back( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   (*cursor).item = ( *(*cursor).item ).prev;

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   DList_go
*/

void
DList_go( Prefix )( DList_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_cursor_go
*/

void
DList_cursor_go( Prefix )( DList_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
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
   DList_start
*/

void
DList_start( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   ( *(*current).first_cursor ).item = (*current).first;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DList_cursor_start
*/

void
DList_cursor_start( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
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
   DList_finish
*/

void
DList_finish( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   ( *(*current).first_cursor ).item = (*current).last;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DList_cursor_finish
*/

void
DList_cursor_finish( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );

   (*cursor).item = ( *(*cursor).list ).last;

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   DList_put
*/

void
DList_put( Prefix )( DList_type( Prefix ) *current, Type value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*current).count ) ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   int32_t i = 0;
   int32_t flag = 0;
   node_t *node = (*current).first;


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

         ( *new_node ).prev = (*node).prev;
         ( *new_node ).next = node;
         (*node).prev = new_node;
         ( *( *new_node ).prev ).next = new_node;

         (*current).count = (*current).count + 1;
      }

      // special case for putting new item at end of current
      if ( ( flag == 0 ) && ( index = (*current).count ) )
      {
         node_t *new_node = node_make();
         ( *new_node ).value = value;
         ( *(*current).last ).next = new_node;
         ( *new_node ).prev = (*current).last;
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
   DList_put_right
*/

void
DList_put_right( Prefix )( DList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).item != NULL );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   node_t *node = ( *(*current).first_cursor ).item;

   node_t *new_node = node_make();
   ( *new_node ).value = value;

   ( *new_node ).prev = node;
   ( *new_node ).next = (*node).next;
   if ( (*node).next != NULL )
   {
      ( *(*node).next ).prev = new_node;
   }
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
   DList_cursor_put_right
*/

void
DList_cursor_put_right( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = ( *(*cursor).list ).count; );

   node_t *node = (*cursor).item;

   node_t *new_node = node_make();
   ( *new_node ).value = value;

   ( *new_node ).prev = node;
   ( *new_node ).next = (*node).next;
   if ( (*node).next != NULL )
   {
      ( *(*node).next ).prev = new_node;
   }
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
   DList_put_left
*/

void
DList_put_left( Prefix )( DList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).item != NULL );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   node_t *node = ( *(*current).first_cursor ).item;

   if ( node != NULL )
   {
      node_t *new_node = node_make();
      ( *new_node ).value = value;

      ( *new_node ).prev = (*node).prev;
      ( *new_node ).next = node;
      if ( (*node).prev != NULL )
      {
         ( *(*node).prev ).next = new_node;
      }
      (*node).prev = new_node;

      if ( (*current).first == node )
      {
         (*current).first = new_node;
      }

      (*current).count = (*current).count + 1;

   }

   POSTCONDITION( "count incremented", (*current).count == i_pc + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DList_cursor_put_left
*/

void
DList_cursor_put_left( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   node_t *node = (*cursor).item;

   if ( node != NULL )
   {
      node_t *new_node = node_make();
      ( *new_node ).value = value;

      ( *new_node ).prev = (*node).prev;
      ( *new_node ).next = node;
      if ( (*node).prev != NULL )
      {
         ( *(*node).prev ).next = new_node;
      }
      (*node).prev = new_node;

      if ( ( *(*cursor).list ).first == node )
      {
         ( *(*cursor).list ).first = new_node;
      }

      ( *(*cursor).list ).count = ( *(*cursor).list ).count + 1;

   }

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   DList_put_first
*/

void
DList_put_first( Prefix )( DList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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

      ( *new_node ).prev = NULL;
      ( *new_node ).next = node;
      (*node).prev = new_node;

      (*current).first = new_node;

      (*current).count = (*current).count + 1;
   }

   POSTCONDITION( "count incremented", (*current).count == i_pc + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DList_put_last
*/

void
DList_put_last( Prefix )( DList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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

   @param current a DList_t instance
   @param other a DList_t instance to append/insert into current
   @param node1 the node after which to append/insert the list
                 if null, append other to start of current
*/

static
void
append( DList_type( Prefix ) *current, DList_type( Prefix ) *other, node_t *node )
{
   int32_t i = 0;

   if ( node == NULL )
   {
      // append other to start of list
      if ( (*other).count > 0 )
      {
         node_t *n1 = (*current).first;

         node_t *new_node = node_make();
         ( *new_node ).value = ( *(*other).first ).value;
         (*current).first = new_node;
         node_t *n = new_node;

         DList_cursor_type( Prefix ) *cursor = dlist_cursor_make( other );
         (*cursor).item = ( *(*cursor).list ).first;
         (*cursor).item = ( *(*cursor).item ).next;

         for( i = 1; i < (*other).count; i++ )
         {
            node_t *new_node = node_make();
            ( *new_node ).value = ( *(*cursor).item ).value;
            (*n).next = new_node;
            ( *new_node ).prev = n;
            n = new_node;
         }

         (*n).next = n1;
         if ( n1 == NULL )
         {
            (*current).last = n;
         }
         else
         {
            (*n1).prev = n;
         }

         (*current).count = (*current).count + (*other).count;
         dlist_cursor_dispose( &cursor );

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
         (*n).prev = node;

         DList_cursor_type( Prefix ) *cursor = dlist_cursor_make( other );
         (*cursor).item = ( *(*cursor).list ).first;
         (*cursor).item = ( *(*cursor).item ).next;

         for ( i = 1; i < (*other).count; i++ )
         {
            node_t *new_node = node_make();
            ( *new_node ).value = ( *(*cursor).item ).value;

            ( *new_node ).prev = n;
            (*n).next = new_node;

            n = new_node;
         }

         (*n).next = n1;

         if ( n1 == NULL )
         {
            (*current).last = n;
         }
         else
         {
            (*n1).prev = n;
         }

         (*current).count = (*current).count + (*other).count;
         dlist_cursor_dispose( &cursor );

      }


   }

   return;
}

/**
   DList_append
*/

void
DList_append( Prefix )( DList_type( Prefix ) *current, DList_type( Prefix ) *other, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DLIST_TYPE ) && ( (*other)._item_type == Type_Code ) );
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
      // append is at start of current (like a prepend)
      append( current, other, NULL );
   }
   else
   {
      // iterate until we get to item index
      for ( i = 1; ( i < index ) && ( (*node).next != NULL ); i++ )
      {
         node = (*node).next;
      }

      // append other into current
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
   DList_append_right
*/

void
DList_append_right( Prefix )( DList_type( Prefix ) *current, DList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DLIST_TYPE ) && ( (*other)._item_type == Type_Code ) );
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
   DList_cursor_append_right
*/

void
DList_cursor_append_right( Prefix )( DList_cursor_type( Prefix ) *cursor, DList_type( Prefix ) *other )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DLIST_TYPE ) && ( (*other)._item_type == Type_Code ) );
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
   DList_append_left
*/

void
DList_append_left( Prefix )( DList_type( Prefix ) *current, DList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DLIST_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );
   POSTCONDITION_VARIABLE_DEFINE( node_t *node_pc = ( *(*current).first_cursor ).item != NULL ? ( *( *(*current).first_cursor ).item ).prev : NULL; );

   // lock other
   LOCK( (*other).mutex );

   node_t *node = ( *(*current).first_cursor ).item;

   if ( node == NULL )
   {
      append( current, other, node );
   }
   else
   {
      node_t *n = (*node).prev;
      append( current, other, n );
   }

   POSTCONDITION( "count correct", (*current).count == i_pc + (*other).count );
   POSTCONDITION( "other is in current", node_pc != NULL ? compare_list_in_list( current, other, node_pc ) : compare_list_in_list( current, other, (*current).first ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DList_cursor_append_left
*/

void
DList_cursor_append_left( Prefix )( DList_cursor_type( Prefix ) *cursor, DList_type( Prefix ) *other )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DLIST_TYPE ) && ( (*other)._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = ( *(*cursor).list ).count; );
   POSTCONDITION_VARIABLE_DEFINE( node_t *node_pc = (*cursor).item != NULL ? ( *(*cursor).item ).prev : NULL; );

   // lock other
   LOCK( (*other).mutex );

   node_t *node = (*cursor).item;

   if ( node == NULL )
   {
      append( (*cursor).list, other, node );
   }
   else
   {
      node_t *n = (*node).prev;
      append( (*cursor).list, other, n );
   }

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
   DList_append_first
*/

void
DList_append_first( Prefix )( DList_type( Prefix ) *current, DList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DLIST_TYPE ) && ( (*other)._item_type == Type_Code ) );
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
   DList_append_last
*/

void
DList_append_last( Prefix )( DList_type( Prefix ) *current, DList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == DLIST_TYPE ) && ( (*other)._item_type == Type_Code ) );
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
   DList_replace
*/

void
DList_replace( Prefix )( DList_type( Prefix ) *current, Type value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   INVARIANT( current );

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

   POSTCONDITION( "value set", dlist_item( current, index ) == value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DList_replace_and_dispose
*/

void
DList_replace_and_dispose( Prefix )( DList_type( Prefix ) *current, Type value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   INVARIANT( current );

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

   POSTCONDITION( "value set", dlist_item( current, index ) == value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DList_replace_at
*/

void
DList_replace_at( Prefix )( DList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).item != NULL );
   INVARIANT( current );

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
   DList_replace_at_and_dispose
*/

void
DList_replace_at_and_dispose( Prefix )( DList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).item != NULL );
   INVARIANT( current );

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
   DList_cursor_replace_at
*/

void
DList_cursor_replace_at( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   INVARIANT( (*cursor).list );

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
   DList_cursor_replace_at_and_dispose
*/

void
DList_cursor_replace_at_and_dispose( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   INVARIANT( (*cursor).list );

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

   Helper function to remove an item from a list

   @param current a DList_t instance
   @param node1 the node to remove
*/

static
void
remove( DList_type( Prefix ) *current, node_t *node )
{
   if ( node != NULL )
   {
      move_all_cursors_at_node_forth( current, node );

      // only item in current
      if ( ( (*node).prev == NULL ) && ( (*node).next == NULL ) )
      {
         (*current).first = NULL;
         (*current).last = NULL;
         (*current).count = 0;
         node_dispose( &node );
      }
      // first item in current
      else if ( ( (*node).prev == NULL ) && ( (*node).next != NULL ) )
      {
         (*current).first = (*node).next;
         ( *(*current).first ).prev = NULL;
         (*current).count = (*current).count - 1;
         node_dispose( &node );
      }
      // last item in current
      else if ( ( (*node).prev != NULL ) && ( (*node).next == NULL ) )
      {
         (*current).last = (*node).prev;
         ( *(*current).last ).next = NULL;
         (*current).count = (*current).count - 1;
         node_dispose( &node );
      }
      // not first, not last item in current
      else if ( ( (*node).prev != NULL ) && ( (*node).next != NULL ) )
      {
         ( *(*node).prev ).next = (*node).next;
         ( *(*node).next ).prev = (*node).prev;
         (*current).count = (*current).count - 1;
         node_dispose( &node );
      }

   }

   return;
}

/**
   remove_and_dispose

   Helper function to remove an item from a list and dispose of its value

   @param list a DList_t instance
   @param node1 the node to remove
*/

static
void
remove_and_dispose( DList_type( Prefix ) *list, node_t *node )
{
   if ( node != NULL )
   {
      move_all_cursors_at_node_forth( list, node );

      // only item in list
      if ( ( (*node).prev == NULL ) && ( (*node).next == NULL ) )
      {
         (*list).first = NULL;
         (*list).last = NULL;
         (*list).count = 0;
         VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
      }
      // first item in list
      else if ( ( (*node).prev == NULL ) && ( (*node).next != NULL ) )
      {
         (*list).first = (*node).next;
         ( *(*list).first ).prev = NULL;
         (*list).count = (*list).count - 1;
         VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
      }
      // last item in list
      else if ( ( (*node).prev != NULL ) && ( (*node).next == NULL ) )
      {
         (*list).last = (*node).prev;
         ( *(*list).last ).next = NULL;
         (*list).count = (*list).count - 1;
         VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
      }
      // not first, not last item in list
      else if ( ( (*node).prev != NULL ) && ( (*node).next != NULL ) )
      {
         ( *(*node).prev ).next = (*node).next;
         ( *(*node).next ).prev = (*node).prev;
         (*list).count = (*list).count - 1;
         VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
         node_dispose( &node );
      }

   }

   return;
}

/**
   DList_remove
*/

void
DList_remove( Prefix )( DList_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = dlist_item( current, index ); int32_t i_pc = occurrences( current, val_pc ); );
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
   DList_remove_and_dispose
*/

void
DList_remove_and_dispose( Prefix )( DList_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = dlist_item( current, index ); int32_t i_pc = occurrences( current, val_pc ); );
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
   DList_remove_at
*/

void
DList_remove_at( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_remove_at_and_dispose
*/

void
DList_remove_at_and_dispose( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_cursor_remove_at
*/

void
DList_cursor_remove_at( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   INVARIANT( (*cursor).list );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *(*cursor).item ).value; int32_t i_pc = occurrences( (*cursor).list, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).list ).count; );

   node_t *node = (*cursor).item;
   DList_type( Prefix ) *list = (*cursor).list;

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
   DList_cursor_remove_at_and_dispose
*/

void
DList_cursor_remove_at_and_dispose( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   INVARIANT( (*cursor).list );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *(*cursor).item ).value; int32_t i_pc = occurrences( (*cursor).list, val_pc ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).list ).count; );

   node_t *node = (*cursor).item;
   DList_type( Prefix ) *list = (*cursor).list;

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
   DList_remove_first
*/

void
DList_remove_first( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_remove_first_and_dispose
*/

void
DList_remove_first_and_dispose( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_remove_last
*/

void
DList_remove_last( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_remove_last_and_dispose
*/

void
DList_remove_last_and_dispose( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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

   Helper function to remove a sublist out of a list

   @param current a DList_t instance
   @param node_start the start node to remove
   @param count the number of entries to remove
*/

static
void
prune( DList_type( Prefix ) *current, node_t *node_start, int32_t count )
{
   int32_t i = 0;
   int32_t n = 0;
   node_t *node = node_start;
   node_t *prev = ( *node_start ).prev;
   node_t *n1 = NULL;
   node_t *ns = NULL;

   // move all cursors off - current will be mangled
   move_all_cursors_off( current );

   // node is first node
   if ( (*node).prev == NULL )
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

   // node1 is last node
   else if ( (*node).next == NULL )
   {
      // set previous node as last
      if ( (*node).prev != NULL )
      {
         ( *(*node).prev ).next = NULL;
      }
      (*current).last = (*node).prev;

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
      ns = (*node).prev;

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

      if ( node != NULL )
      {
         (*node).prev = prev;
      }

      // (*node).prev may be the last in the current
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

   Helper function to remove a sublist out of a list and dispose of its
   values.

   @param current a DList_t instance
   @param node1 the start node to remove
   @param node2 the end node to remove
*/

static
void
prune_and_dispose( DList_type( Prefix ) *current, node_t *node_start, int32_t count )
{
   int32_t i = 0;
   int32_t n = 0;
   node_t *node = node_start;
   node_t *prev = ( *node_start ).prev;
   node_t *n1 = NULL;
   node_t *ns = NULL;

   // move all cursors off - current will be mangled
   move_all_cursors_off( current );

   // node is first node
   if ( (*node).prev == NULL )
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
   else if ( (*node).next == NULL )
   {
      // set previous node as last
      if ( (*node).prev != NULL )
      {
         ( *(*node).prev ).next = NULL;
      }
      (*current).last = (*node).prev;

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
      ns = (*node).prev;

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

      if ( node != NULL )
      {
         (*node).prev = prev;
      }

      // (*node).prev may be the last in the current
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
   DList_prune
*/

void
DList_prune( Prefix )( DList_type( Prefix ) *current, int32_t index, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_prune_and_dispose
*/

void
DList_prune_and_dispose( Prefix )( DList_type( Prefix ) *current, int32_t index, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_prune_first
*/

void
DList_prune_first( Prefix )( DList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_prune_first_and_dispose
*/

void
DList_prune_first_and_dispose( Prefix )( DList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_prune_last
*/

void
DList_prune_last( Prefix )( DList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", ( (*current).count >= count ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   int32_t i = 0;

   node_t *node = (*current).last;

   for ( i = 1; ( i < count ) && ( node != NULL ); i++ )
   {
      node = (*node).prev;
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
   DList_prune_last_and_dispose
*/

void
DList_prune_last_and_dispose( Prefix )( DList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", ( (*current).count >= count ) );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   int32_t i = 0;

   node_t *node = (*current).last;

   for ( i = 1; ( i < count ) && ( node != NULL ); i++ )
   {
      node = (*node).prev;
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
   DList_keep_first
*/

void
DList_keep_first( Prefix )( DList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_keep_first_and_dispose
*/

void
DList_keep_first_and_dispose( Prefix )( DList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_keep_last
*/

void
DList_keep_last( Prefix )( DList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_keep_last_and_dispose
*/

void
DList_keep_last_and_dispose( Prefix )( DList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_wipe_out
*/

void
DList_wipe_out( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_wipe_out_and_dispose
*/

void
DList_wipe_out_and_dispose( Prefix )( DList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == DLIST_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   DList_has
*/
int32_t
DList_has( Prefix )( DList_type( Prefix ) *current, Type value )
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
   DList_has_eq_fn
*/
int32_t
DList_has_eq_fn( Prefix )
(
   DList_type( Prefix ) *current,
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
   DList_search_forth
*/
void
DList_search_forth( Prefix )( DList_type( Prefix ) *current, Type value )
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
   DList_search_forth_eq_fn
*/
void
DList_search_forth_eq_fn( Prefix )
(
   DList_type( Prefix ) *current,
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
   DList_search_back
*/
void
DList_search_back( Prefix )( DList_type( Prefix ) *current, Type value )
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

      // decrement node pointer
      node = (*node).prev;

      // update internal cursor
      ( *(*current).first_cursor ).item = node;

   }

   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DList_search_back_eq_fn
*/
void
DList_search_back_eq_fn( Prefix )
(
   DList_type( Prefix ) *current,
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

      // decrement node pointer
      node = (*node).prev;

      // update internal cursor
      ( *(*current).first_cursor ).item = node;

   }

   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   DList_cursor_search_forth
*/
void
DList_cursor_search_forth( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
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
   DList_cursor_search_forth_eq_fn
*/
void
DList_cursor_search_forth_eq_fn( Prefix )
(
   DList_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
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
   DList_cursor_search_back
*/
void
DList_cursor_search_back( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
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

      // decrement node pointer
      node = (*node).prev;

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
   DList_cursor_search_back_eq_fn
*/
void
DList_cursor_search_back_eq_fn( Prefix )
(
   DList_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( ( *(*cursor).list )._type == DLIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
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

      // decrement node pointer
      node = (*node).prev;

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
   DList_occurrences
*/
int32_t
DList_occurrences( Prefix )( DList_type( Prefix ) *current, Type value )
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
   DList_occurrences_eq_fn
*/
int32_t
DList_occurrences_eq_fn( Prefix )
(
   DList_type( Prefix ) *current,
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
   DList_swap
*/
void
DList_swap( Prefix )( DList_type( Prefix ) *current, int32_t i, int32_t j )
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
   DList_sort
*/

void
DList_sort( Prefix )( DList_type( Prefix ) *list, int32_t ( *sort_func )( Type v1, Type v2 ) )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list)._type == DLIST_TYPE ) && ( (*list)._item_type == Type_Code ) );
   PRECONDITION( "sort_func not null", sort_func != NULL );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // array to use for sorting
   node_t **array = NULL;
   node_t *node = NULL;
   node_t *last_node = NULL;
   int32_t i = 0;

   // only sort if there's enough to sort
   if ( (*list).count > 1 )
   {
      array = ( node_t ** ) calloc( (*list).count, sizeof( node_t * ) );
      CHECK( "array allocated correctly", array != NULL );

      // fill the array
      node = (*list).first;

      for( i = 0; i < (*list).count; i++ )
      {
         array[i] = node;
         node = (*node).next;
      }

      // set the sort func
      value_sort_func_name = sort_func;

      // sort the array
      qsort( array, (*list).count, sizeof( node_t * ), ( int (*)( const void*, const void* ) ) node_sort_func );

      // put sorted items into list
      node = array[0];
      (*list).first = node;
      (*node).prev = NULL;
      (*node).next = array[1];

      node = (*node).next;

      for( i = 1; i < (*list).count; i++ )
      {
         (*node).prev = array[i - 1];

         if ( i == ( (*list).count - 1 ) )
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

      (*list).last = last_node;

      // reset cursors
      move_all_cursors_off( list );

      free( array );
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}


#ifdef __cplusplus
}
#endif

/* End of file */

