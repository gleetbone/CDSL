/**
 @file HTable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Hash Tables"

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

 Function definitions for the opaque HTable_t type.

*/

#include "HTable.h"

#include "protocol.h"

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_Iterable_kv.ph"
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

#define DEFAULT_BUCKET_SIZE 13

/**
   Node structure declaration
*/

struct node;

/**
   Node structure definition. Holds a key and a value.
*/

struct node
{
   Key key;
   Type value;
   struct node *next;
   struct node *next_in_sequence;
};

typedef struct node node_t;

/**
   Hash table structure definition.
*/

struct HTable_struct( Prefix )
{

   PROTOCOLS_DEFINITION;

   int32_t _type;
   int32_t _key_type;
   int32_t _item_type;

   node_t *first_in_sequence;
   node_t *last_in_sequence;
   int32_t count;
   node_t **bucket; ///< array of pointers to node_t
   int32_t bucket_count;
   HTable_cursor_type( Prefix ) *first_cursor;
   HTable_cursor_type( Prefix ) *last_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure definition. Holds reference to htable, holds a sequence
   location, and holds a pointer to the next curso15r.
*/

struct HTable_cursor_struct( Prefix )
{
   HTable_type( Prefix ) *htable;
   node_t *item;
   HTable_cursor_type( Prefix ) *next_cursor;

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

   @param the node to be disposed
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
   has

   Return 1 if htable has an item for key, 0 if not

   @param current HTable_t instance
   @param key the key to query for
   @return 1 if true, 0 otherwise
*/

static
int32_t
has( HTable_type( Prefix ) *current, Key key )
{
   int32_t hash_code = KEY_HASH_FUNCTION( key );
   int32_t i = hash_code % (*current).bucket_count;

   // get first of bucket's nodes
   node_t *node = (*current).bucket[i];

   // look through nodes in bucket for match to key
   while ( node != NULL )
   {
      if ( KEY_DEEP_EQUAL_FUNCTION( (*node).key, key ) == 1 )
      {
         return 1;
      }
      node = (*node).next;
   }

   return 0;
}

/**
   item

   Return value in htable for key

   @param current HTable_t instance
   @param key the key to query for
   @return the value
*/

static
Type
item( HTable_type( Prefix ) *current, Key key )
{
   int32_t hash_code = KEY_HASH_FUNCTION( key );
   int32_t i = hash_code % (*current).bucket_count;

   // get first of bucket's nodes
   node_t *node = (*current).bucket[i];

   Type value = ( *(*current).first_in_sequence ).value;

   // look through nodes in bucket for match to key
   while ( node != NULL )
   {
      if ( KEY_DEEP_EQUAL_FUNCTION( (*node).key, key ) == 1 )
      {
         value = (*node).value;
         break;
      }
      node = (*node).next;
   }

   return value;
}

/**
   put

   insert a value in the htable for the given key if key not present,
   replace the value if key present. do not dispose the existing value

   @param current the htable
   @param value the value to put in the htable
   @param key the key for the value
*/

static
void
put( HTable_type( Prefix ) *current, Type value, Key key )
{
   int32_t hash_code = KEY_HASH_FUNCTION( key );
   int32_t i = hash_code % (*current).bucket_count;

   // get node for new value
   node_t *new_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*current).bucket[i];

   // see if node with this key already exists
   int32_t flag = 0;

   // look through nodes in bucket for match to key
   while ( ( node != NULL ) && ( flag == 0 ) )
   {
      if ( KEY_DEEP_EQUAL_FUNCTION( (*node).key, key ) == 1 )
      {
         flag = 1;
         new_node = node;
      }
      node = (*node).next;
   }

   // if node exists in htable, replace value with new value
   if ( new_node != NULL )
   {
      ( *new_node ).value = value;
      ( *new_node ).key = key;
   }
   else
   {
      // else get new node and put new value at head of bucket
      new_node = node_make();
      ( *new_node ).value = value;
      ( *new_node ).key = key;
      ( *new_node ).next = (*current).bucket[i];
      (*current).bucket[i] = new_node;

      // place new node in node sequence
      if ( (*current).last_in_sequence == NULL )
      {
         (*current).first_in_sequence = new_node;
         (*current).last_in_sequence = new_node;
      }
      else
      {
         ( *(*current).last_in_sequence ).next_in_sequence = new_node;
         (*current).last_in_sequence = new_node;
      }

      (*current).count = (*current).count + 1;
   }

   return;
}

/**
   keys_as_array

   create an array of keys for all nodes in the htable

   @param current the htable
   @return the array of keys

*/

static
Key *
keys_as_array( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );

   Key *result = NULL;

   result = ( Key * ) calloc( (*current).count + 1, sizeof( Key ) );
   CHECK( "result allocated correctly", result != NULL );

   int32_t i = 0;
   node_t *node = (*current).first_in_sequence;

   for( i = 0; i < (*current).count; i++ )
   {
      result[i] = (*node).key;
      node = (*node).next_in_sequence;
   }

   return result;
}

/**
   values_as_array

   create an array of values for all nodes in the htable

   @param current the htable
   @return the array of balues

*/

static
Type *
values_as_array( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );

   Type *result = NULL;
   result = ( Type * ) calloc( (*current).count + 1, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   int32_t i = 0;
   node_t *node = (*current).first_in_sequence;

   for( i = 0; i < (*current).count; i++ )
   {
      result[i] = (*node).value;
      node = (*node).next_in_sequence;
   }

   return result;
}

/**
   move_all_cursors_forth_after_node_removal

   After a node hs been removed, move all cursors pointing to that node
   forth.

   @param current HTable_t instance
   @param node the just removed node
*/
static
void
move_all_cursors_forth_after_node_removal
(
   HTable_type( Prefix ) *current,
   node_t *node
)
{
   HTable_cursor_type( Prefix ) *cursor = NULL;

   for (  cursor = (*current).first_cursor;
          cursor != NULL;
          cursor = (*cursor).next_cursor
       )
   {
      if ( (*cursor).item != NULL )
      {
         if ( (*cursor).item == node )
         {
            HTable_cursor_forth( Prefix )( cursor );
         }
      }
   }

   return;
}

/**
   remove_node_from_sequence

   Remove node from sequence. Does not delete node, does not change count,
   does not change bucket contents.

   @param current HTable_t instance
   @param node the to be removed node
*/
static
void
remove_node_from_sequence
(
   HTable_type( Prefix ) *current,
   node_t *node
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "node not null", node != NULL );

   node_t *node1 = (*current).first_in_sequence;
   node_t *prev = ( *(*current).first_in_sequence ).next_in_sequence;

   if ( node1 == node )
   {
      (*current).first_in_sequence = (*node).next_in_sequence;
   }
   else
   {
      prev = node1;
      node1 = (*node1).next_in_sequence;

      while( node1 != NULL )
      {
         if ( node1 == node )
         {
            (*prev).next_in_sequence = (*node1).next_in_sequence;
            if ( node1 == (*current).last_in_sequence )
            {
               (*current).last_in_sequence = prev;
            }
            node1 = NULL;
         }
         else
         {
            prev = node1;
            node1 = (*node1).next_in_sequence;
         }
      }
   }
   return;
}

/**
   compare_htables_shallow_equal

   compare two htables for all nodes in each being equal

   @param current the first htable to compare
   @param other the other htable to compare
   @return 1 if htable node keys and values equal, 0 otherwise
*/
static
int32_t
compare_htables_shallow_equal
(
   HTable_type( Prefix ) *current,
   HTable_type( Prefix ) *other
)
{
   int32_t result = 0;
   int32_t flag = 0;
   node_t *node_1 = NULL;
   node_t *node_2 = NULL;

   node_1 = (*current).first_in_sequence;

   while( node_1 != NULL )
   {
      node_2 = (*other).first_in_sequence;
      while( node_2 != NULL )
      {
         if ( KEY_DEEP_EQUAL_FUNCTION( ( *node_1 ).key, ( *node_2 ).key ) == 1 )
         {
            if ( ( *node_1 ).value == ( *node_2 ).value )
            {
               flag = flag + 1;
               break;
            }
         }
         node_2 = ( *node_2 ).next_in_sequence;
      }
      node_1 = ( *node_1 ).next_in_sequence;
   }

   if ( ( flag == (*current).count ) && ( flag == (*other).count ) )
   {
      result = 1;
   }

   return result;
}

/**
   compare_htables_deep_equal

   compare two htables for all nodes in each being deep equal

   @param current the first htable to compare
   @param other the other htable to compare
   @return 1 if htable node keys and values equal, 0 otherwise
*/
static
int32_t
compare_htables_deep_equal
(
   HTable_type( Prefix ) *current,
   HTable_type( Prefix ) *other
)
{
   int32_t result = 0;
   int32_t flag = 0;
   node_t *node_1 = NULL;
   node_t *node_2 = NULL;

   node_1 = (*current).first_in_sequence;

   while( node_1 != NULL )
   {
      node_2 = (*other).first_in_sequence;
      while( node_2 != NULL )
      {
         if ( KEY_DEEP_EQUAL_FUNCTION( ( *node_1 ).key, ( *node_2 ).key ) == 1 )
         {
            if ( VALUE_DEEP_EQUAL_FUNCTION( ( *node_1 ).value, ( *node_2 ).value ) == 1 )
            {
               flag = flag + 1;
               break;
            }
         }
         node_2 = ( *node_2 ).next_in_sequence;
      }
      node_1 = ( *node_1 ).next_in_sequence;
   }

   if ( ( flag == (*current).count ) && ( flag == (*other).count ) )
   {
      result = 1;
   }

   return result;
}

/**
   compare_htable_items_to_array_items

   compare keys and values in htable nodes to arrays of keys and values

   @param current the htable
   @param key_array the array of keys
   @param value array the array of values
   @param count the length of the arrays
   @result 1 if htable keys and values are equal, 0 otherwise
*/
static
int32_t
compare_htable_items_to_array_items
(
   HTable_type( Prefix ) *current,
   Key *key_array,
   Type *value_array,
   int32_t count
)
{
   int32_t result = 0;
   int32_t i = 0;
   int32_t flag = 0;
   node_t *node = NULL;

   node = (*current).first_in_sequence;

   while( node != NULL )
   {
      for( i = 0; i < count; i++ )
      {
         if ( KEY_DEEP_EQUAL_FUNCTION( (*node).key, key_array[i] ) == 1 )
         {
            if ( (*node).value == value_array[i] )
            {
               flag = flag + 1;
               break;
            }
         }
      }
      node = (*node).next_in_sequence;
   }

   if ( ( flag == (*current).count ) && ( flag == count ) )
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
is_empty_implies_first_last_null( HTable_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).count == 0 )
   {
      result
         = (
              ( (*current).first_in_sequence == NULL )
              &&
              ( (*current).last_in_sequence  == NULL )
           );
   }

   return result;
}

static
int32_t
nonnegative_count( HTable_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).count >= 0 );

   return result;
}

static
int32_t
last_in_sequence_ok( HTable_type( Prefix ) *current )
{
   int32_t result = 0;

   node_t *node = (*current).first_in_sequence;
   node_t *node1 = NULL;

   while( node != NULL )
   {
      node1 = node;
      node = (*node).next_in_sequence;
   }

   result = ( node1 == (*current).last_in_sequence );

   return result;
}

static
int32_t
valid_sequence_count( HTable_type( Prefix ) *current )
{
   int32_t result = 1;
   int32_t n = 0;

   node_t *node = (*current).first_in_sequence;

   while( node != NULL )
   {
      n = n + 1;
      node = (*node).next_in_sequence;
   }

   result = ( n == (*current).count );

   return result;
}

static
int32_t
valid_bucket_count( HTable_type( Prefix ) *current )
{
   int32_t i = 0;
   int32_t result = 1;
   node_t *node = NULL;
   int32_t n = 0;

   for ( i = 0; i < (*current).bucket_count; i ++ )
   {
      node = (*current).bucket[i];

      while( node != NULL )
      {
         n = n + 1;
         node = (*node).next;
      }
   }

   result = ( n == (*current).count );

   return result;
}

static
int32_t
first_cursor_not_null( HTable_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).first_cursor != NULL );

   return result;
}

static
int32_t
cursors_htable_ok( HTable_type( Prefix ) *current )
{
   int32_t result = 1;

   HTable_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   while ( ( cursor != NULL ) && ( result == 1 ) )
   {
      result = ( (*cursor).htable == current );
      cursor = (*cursor).next_cursor;
   }

   return result;
}

static
int32_t
last_cursor_next_null( HTable_type( Prefix ) *current )
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
last_cursor_null_if_one_cursor( HTable_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( ( *(*current).first_cursor ).next_cursor == NULL )
   {
      result = ( (*current).last_cursor == NULL );
   }

   return result;
}

static
void invariant( HTable_type( Prefix ) *current )
{
   assert( ( ( void ) "empty implies first and last null", is_empty_implies_first_last_null( current ) ) );
   assert( ( ( void ) "nonnegative count", nonnegative_count( current ) ) );
   assert( ( ( void ) "last in sequence OK", last_in_sequence_ok( current ) ) );
   assert( ( ( void ) "valid sequence count", valid_sequence_count( current ) ) );
   assert( ( ( void ) "valid bucket count", valid_bucket_count( current ) ) );
   assert( ( ( void ) "first cursor not null", first_cursor_not_null( current ) ) );
   assert( ( ( void ) "last cursor next null", last_cursor_next_null( current ) ) );
   assert( ( ( void ) "last cursor null if one cursor", last_cursor_null_if_one_cursor( current ) ) );
   assert( ( ( void ) "cursors htable OK", cursors_htable_ok( current ) ) );
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
   HTable_dispose( Prefix ),
   HTable_deep_dispose( Prefix ),
   HTable_is_equal( Prefix ),
   HTable_is_deep_equal( Prefix ),
   HTable_copy( Prefix ),
   HTable_deep_copy( Prefix ),
   HTable_clone( Prefix ),
   HTable_deep_clone( Prefix )
};

static
void *
p_iterable_kv_table[P_ITERABLE_KV_FUNCTION_COUNT]
=
{
   HTable_count( Prefix ),
   HTable_key_at( Prefix ),
   HTable_item_at( Prefix ),
   HTable_off( Prefix ),
   HTable_is_empty( Prefix ),
   HTable_start( Prefix ),
   HTable_forth( Prefix )
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

      case P_ITERABLE_KV_TYPE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_ITERABLE_KV_FUNCTION_MAX ) )
         {
            result = p_iterable_kv_table[ function_id ];
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

      case P_ITERABLE_KV_TYPE:
      {
         result = 1;
         break;
      }

   }

   return result;
}

#endif // PROTOCOLS_ENABLED


/**
   HTable_make
*/

HTable_type( Prefix ) *
HTable_make( Prefix )( void )
{
   // allocate htable struct
   HTable_type( Prefix ) *result
      = ( HTable_type( Prefix ) * ) calloc( 1, sizeof( HTable_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = HTABLE_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   (*result).count = 0;

   // allocate bucket array, default size
   (*result).bucket = ( node_t ** ) calloc( DEFAULT_BUCKET_SIZE, sizeof( node_t * ) );
   CHECK( "(*result).bucket allocated correctly", (*result).bucket != NULL );

   (*result).bucket_count = DEFAULT_BUCKET_SIZE;

   // set built-in cursor
   // allocate cursor struct
   HTable_cursor_type( Prefix ) *cursor
      =  ( HTable_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HTable_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set htable
   (*cursor).htable = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set htable built-in cursor
   (*result).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new htable is empty", (*result).count == 0 );
   POSTCONDITION( "new htable cursor is off", ( *(*result).first_cursor ).item == NULL );

   INVARIANT( result );

   return result;
}

/**
   HTable_make_n
*/

HTable_type( Prefix ) *
HTable_make_n( Prefix )( int32_t bucket_count )
{
   PRECONDITION( "bucket count ok", bucket_count > 0 );

   // allocate htable struct
   HTable_type( Prefix ) *result
      = ( HTable_type( Prefix ) * ) calloc( 1, sizeof( HTable_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = HTABLE_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   (*result).count = 0;

   // allocate bucket array
   (*result).bucket = ( node_t ** ) calloc( bucket_count, sizeof( node_t * ) );
   CHECK( "(*result).bucket allocated correctly", (*result).bucket != NULL );

   (*result).bucket_count = bucket_count;

   // set built-in cursor
   // allocate cursor struct
   HTable_cursor_type( Prefix ) *cursor
      =  ( HTable_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HTable_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set htable
   (*cursor).htable = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set htable built-in cursor
   (*result).first_cursor = cursor;


   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new htable is empty", (*result).count == 0 );
   POSTCONDITION( "new htable cursor is off", ( *(*result).first_cursor ).item == NULL );
   POSTCONDITION( "bucket count set", (*result).bucket_count == bucket_count );

   INVARIANT( result );

   return result;
}

/**
   HTable_make_from_array
*/

HTable_type( Prefix ) *
HTable_make_from_array( Prefix )( Key *key_array, Type *value_array, int32_t count )
{
   PRECONDITION( "key_array not null", key_array != NULL );
   PRECONDITION( "value_array not null", value_array != NULL );
   PRECONDITION( "count ok", count >= 0 );

   // allocate htable struct
   HTable_type( Prefix ) *result = HTable_make( Prefix )();
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = HTABLE_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   // put key-values from htable into result
   int32_t i = 0;
   for ( i = 0; i < count; i++ )
   {
      put( result, value_array[i], key_array[i] );
   }

   POSTCONDITION( "new htable has count items", (*result).count == count );
   POSTCONDITION( "new htable cursor is off", ( *(*result).first_cursor ).item == NULL );
   POSTCONDITION( "htable has array items", compare_htable_items_to_array_items( result, key_array, value_array, count ) == 1 );

   INVARIANT( result );

   return result;
}

/**
   HTable_cursor_make
*/

HTable_cursor_type( Prefix ) *
HTable_cursor_make( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "htable not null", current != NULL );
   PRECONDITION( "htable type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // allocate cursor struct
   HTable_cursor_type( Prefix ) *cursor
      =  ( HTable_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HTable_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set htable
   (*cursor).htable = current;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // place cursor reference into htable structure
   if ( (*current).last_cursor == NULL )
   {
      // set second cursor for htable
      ( *(*current).first_cursor ).next_cursor = cursor;
      (*current).last_cursor = cursor;
   }
   else
   {
      // set additional cursor for htable
      // (*current).last_cursor holds last cursor allocated
      ( *(*current).last_cursor ).next_cursor = cursor;
      (*current).last_cursor = cursor;
   }

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   POSTCONDITION( "new cursor is last cursor", (*current).last_cursor == cursor );

   INVARIANT( current );

   UNLOCK( (*current).mutex );

   return cursor;
}

/**
   HTable_clone
*/

HTable_type( Prefix ) *
HTable_clone( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "htable not null", current != NULL );
   PRECONDITION( "htable type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );

   // get input
   LOCK( (*current).mutex );
   Key *keys = keys_as_array( current );
   Type *items = values_as_array( current );
   int32_t count = (*current).count;
   UNLOCK( (*current).mutex );

   // allocate htable struct
   HTable_type( Prefix ) *result
      = ( HTable_type( Prefix ) * ) calloc( 1, sizeof( HTable_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = HTABLE_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   (*result).count = 0;

   // allocate bucket array
   (*result).bucket = ( node_t ** ) calloc( (*current).bucket_count, sizeof( node_t * ) );
   CHECK( "(*result).bucket allocated correctly", (*result).bucket != NULL );

   (*result).bucket_count = (*current).bucket_count;

   // set built-in cursor
   // allocate cursor struct
   HTable_cursor_type( Prefix ) *cursor
      =  ( HTable_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HTable_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set htable
   (*cursor).htable = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set htable built-in cursor
   (*result).first_cursor = cursor;

   // put key-values from htable into result
   int32_t i = 0;
   for ( i = 0; i < count; i++ )
   {
      put( result, items[i], keys[i] );
   }

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   free( keys );
   free( items );

   POSTCONDITION( "new htable has count items", (*result).count == (*current).count );
   POSTCONDITION( "new htable cursor is off", ( ( *(*result).first_cursor ).item == NULL ) );
   POSTCONDITION( "new htable clone is equal to original", compare_htables_shallow_equal( result, current ) == 1 );

   INVARIANT( result );

   return result;
}

/**
   HTable_deep_clone
*/

HTable_type( Prefix ) *
HTable_deep_clone( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "htable not null", current != NULL );
   PRECONDITION( "htable type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );

   // get input
   LOCK( (*current).mutex );
   Key *keys = keys_as_array( current );
   Type *items = values_as_array( current );
   int32_t count = (*current).count;
   UNLOCK( (*current).mutex );

   // allocate htable struct
   HTable_type( Prefix ) *result
      = ( HTable_type( Prefix ) * ) calloc( 1, sizeof( HTable_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = HTABLE_TYPE;
   (*result)._key_type = Key_Code;
   (*result)._item_type = Type_Code;

   (*result).count = 0;

   // allocate bucket array
   (*result).bucket = ( node_t ** ) calloc( (*current).bucket_count, sizeof( node_t * ) );
   CHECK( "(*result).bucket allocated correctly", (*result).bucket != NULL );

   (*result).bucket_count = (*current).bucket_count;

   // set built-in cursor
   // allocate cursor struct
   HTable_cursor_type( Prefix ) *cursor
      =  ( HTable_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HTable_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set htable
   (*cursor).htable = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set htable built-in cursor
   (*result).first_cursor = cursor;

   Key k;
   Type v;

   // put key-values from htable into result
   int32_t i = 0;
   for ( i = 0; i < count; i++ )
   {
      k = KEY_DEEP_CLONE_FUNCTION( keys[i] );
      v = VALUE_DEEP_CLONE_FUNCTION( items[i] );
      put( result, v, k );
   }

   MULTITHREAD_MUTEX_INIT( (*current).mutex );

   free( keys );
   free( items );

   POSTCONDITION( "new htable has count items", (*result).count == (*current).count );
   POSTCONDITION( "new htable cursor is off", ( ( *(*result).first_cursor ).item == NULL ) );
   POSTCONDITION( "new htable clone is equal to original", compare_htables_deep_equal( result, current ) == 1 );

   INVARIANT( result );

   return result;
}

/**
   HTable_is_equal
*/

int32_t
HTable_is_equal( Prefix )( HTable_type( Prefix ) *current, HTable_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HTABLE_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t result = 1;
   int32_t i = 0;
   Type value;

   // get input
   LOCK( (*other).mutex );
   Key *keys = keys_as_array( other );
   Type *items = values_as_array( other );
   int32_t count = (*other).count;
   UNLOCK( (*other).mutex );

   // check count
   if ( (*current).count != (*other).count )
   {
      result = 0;
   }

   // check equal key-value from other in result
   for ( i = 0; i < count; i++ )
   {
      if ( result == 1 )
      {
         if ( has( current, keys[i] ) == 0 )
         {
            result = 0;
            break;
         }
         else
         {
            value = item( current, keys[i] );
            if ( value != items[i] )
            {
               result = 0;
               break;
            }
         }
      }
      else
      {
         break;
      }
   }

   free( keys );
   free( items );

   INVARIANT( current );

   return result;
}

/**
   HTable_is_deep_equal
*/

int32_t
HTable_is_deep_equal( Prefix )( HTable_type( Prefix ) *current, HTable_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HTABLE_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t result = 1;
   int32_t i = 0;
   Type value;

   // get input
   LOCK( (*other).mutex );
   Key *keys = keys_as_array( other );
   Type *items = values_as_array( other );
   int32_t count = (*other).count;
   UNLOCK( (*other).mutex );

   // check count
   if ( (*current).count != (*other).count )
   {
      result = 0;
   }

   // check equal key-value from other in result
   for ( i = 0; i < count; i++ )
   {
      if ( result == 1 )
      {
         if ( has( current, keys[i] ) == 0 )
         {
            result = 0;
            break;
         }
         else
         {
            value = item( current, keys[i] );
            if ( VALUE_DEEP_EQUAL_FUNCTION( value, items[i] ) == 0 )
            {
               result = 0;
               break;
            }
         }
      }
      else
      {
         break;
      }
   }

   free( keys );
   free( items );

   INVARIANT( current );

   return result;
}

/**
   HTable_copy
*/

void
HTable_copy( Prefix )( HTable_type( Prefix ) *current, HTable_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HTABLE_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );

   int32_t i = 0;

   // get input
   LOCK( (*other).mutex );
   Key *keys = keys_as_array( other );
   Type *items = values_as_array( other );
   int32_t count = (*other).count;
   UNLOCK( (*other).mutex );

   // empty current
   HTable_wipe_out_and_dispose( Prefix )( current );

   // put key-values from htable into result
   for ( i = 0; i < count; i++ )
   {
      put( current, items[i], keys[i] );
   }

   free( keys );
   free( items );

   POSTCONDITION( "new htable clone is equal to original", compare_htables_shallow_equal( current, other ) == 1 );

   INVARIANT( current );

   return;
}

/**
   HTable_deep_copy
*/

void
HTable_deep_copy( Prefix )( HTable_type( Prefix ) *current, HTable_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HTABLE_TYPE ) && ( (*other)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );

   int32_t i = 0;
   Key k;
   Type v;

   // get input
   LOCK( (*other).mutex );
   Key *keys = keys_as_array( other );
   Type *items = values_as_array( other );
   int32_t count = (*other).count;
   UNLOCK( (*other).mutex );

   // empty current
   HTable_wipe_out_and_dispose( Prefix )( current );

   // put key-values from htable into result
   for ( i = 0; i < count; i++ )
   {
      k = KEY_DEEP_CLONE_FUNCTION( keys[i] );
      v = VALUE_DEEP_CLONE_FUNCTION( items[i] );
      put( current, v, k );
   }

   free( keys );
   free( items );

   POSTCONDITION( "new htable clone is equal to original", compare_htables_deep_equal( current, other ) == 1 );

   INVARIANT( current );

   return;
}

/**
   HTable_dispose
*/

void
HTable_dispose( Prefix )( HTable_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == HTABLE_TYPE ) && ( (**current)._key_type = Key_Code ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete htable sequence nodes
   node_t *node = (**current).first_in_sequence;
   node_t *next = NULL;
   while( node != NULL )
   {
      next = (*node).next_in_sequence;
      node_dispose( &node );
      node = next;
   }

   // delete cursors
   HTable_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   HTable_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // delete bucket array
   free( (**current).bucket );

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete htable struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   HTable_deep_dispose
*/

void
HTable_deep_dispose( Prefix )( HTable_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == HTABLE_TYPE ) && ( (**current)._key_type = Key_Code ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete htable sequence nodes
   node_t *node = (**current).first_in_sequence;
   node_t *next = NULL;
   while( node != NULL )
   {
      next = (*node).next_in_sequence;
      KEY_DEEP_DISPOSE_FUNCTION( (*node).key );
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
      node_dispose( &node );
      node = next;
   }

   // delete cursors
   HTable_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   HTable_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // delete bucket array
   free( (**current).bucket );

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete htable struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   HTable_cursor_dispose
*/

void
HTable_cursor_dispose( Prefix )( HTable_cursor_type( Prefix ) **cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "*cursor not null", *cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(**cursor).htable )._type == HTABLE_TYPE ) && ( ( *(**cursor).htable )._key_type == Key_Code ) && ( ( *(**cursor).htable )._item_type == Type_Code ) );
   LOCK( (**cursor).mutex );
   LOCK( ( *(**cursor).htable ).mutex );
   INVARIANT( (**cursor).htable );

   HTable_type( Prefix ) *htable = (**cursor).htable;

   HTable_cursor_type( Prefix ) *c1 = NULL;
   HTable_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from htable structure
   c1 = ( *(**cursor).htable ).first_cursor;
   c2 = (*c1).next_cursor;

   // search through the cursors
   while ( ( c2 != NULL ) && ( flag == 0 ) )
   {
      if ( c2 == *cursor )
      {
         // if we have a match, remove "c2" from the cursor htable, set flag
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

   // set htable's last cursor
   c1 = ( *(**cursor).htable ).first_cursor;
   while ( c1 != NULL )
   {
      c2 = c1;
      c1 = (*c1).next_cursor;
   }
   ( *(**cursor).htable ).last_cursor = c2;

   // only one cursor, last_cursor is NULL
   if ( c2 == ( *(**cursor).htable ).first_cursor )
   {
      ( *(**cursor).htable ).last_cursor = NULL;
   }

   // delete cursor struct
   free(*cursor);

   // set to NULL
   *cursor = NULL;

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return;
}

/**
   HTable_keys_as_array

*/

Key *
HTable_keys_as_array( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );

   Key *result = keys_as_array( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   HTable_values_as_array

*/

Type *
HTable_values_as_array( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );

   Type *result = values_as_array( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   HTable_cursor_item_at
*/

Type
HTable_cursor_item_at( Prefix )( HTable_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).htable )._type == HTABLE_TYPE ) && ( ( *(*cursor).htable )._key_type == Key_Code ) && ( ( *(*cursor).htable )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).htable ).mutex );
   INVARIANT( (*cursor).htable );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Type value = ( *(*cursor).item ).value;

   INVARIANT( (*cursor).htable );
   UNLOCK( ( *(*cursor).htable ).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}

/**
   HTable_cursor_key_at
*/

Key
HTable_cursor_key_at( Prefix )( HTable_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).htable )._type == HTABLE_TYPE ) && ( ( *(*cursor).htable )._key_type == Key_Code ) && ( ( *(*cursor).htable )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).htable ).mutex );
   INVARIANT( (*cursor).htable );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Key key = ( *(*cursor).item ).key;

   INVARIANT( (*cursor).htable );
   UNLOCK( ( *(*cursor).htable ).mutex );
   UNLOCK( (*cursor).mutex );

   return key;
}


/**
   HTable_item_at
*/

Type
HTable_item_at( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   HTable_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   Type value = ( *(*cursor).item ).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   HTable_key_at
*/

Key
HTable_key_at( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   HTable_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   Key key = ( *(*cursor).item ).key;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return key;
}


/**
   HTable_item_at_index
*/

Type
HTable_item_at_index( Prefix )( HTable_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   int32_t i = 0;
   node_t *node = (*current).first_in_sequence;

   for( i = 1; i <= index; i ++ )
   {
      node = (*node).next_in_sequence;
   }

   Type value = (*node).value;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   HTable_key_at_index
*/

Key
HTable_key_at_index( Prefix )( HTable_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   int32_t i = 0;
   node_t *node = (*current).first_in_sequence;

   for( i = 1; i <= index; i ++ )
   {
      node = (*node).next_in_sequence;
   }

   Key key = (*node).key;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return key;
}


/**
   HTable_item
*/

Type
HTable_item( Prefix )( HTable_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has key", has( current, key ) );

   Type value = item( current, key );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   HTable_count
*/

int32_t
HTable_count( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   HTable_bucket_count
*/

int32_t
HTable_bucket_count( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = (*current).bucket_count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   HTable_off
*/

int32_t
HTable_off( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( ( *(*current).first_cursor ).item == NULL );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   HTable_cursor_off
*/

int32_t
HTable_cursor_off( Prefix )( HTable_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).htable )._type == HTABLE_TYPE ) && ( ( *(*cursor).htable )._key_type == Key_Code ) && ( ( *(*cursor).htable )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );

   int32_t result = ( (*cursor).item == NULL );

   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   HTable_is_empty
*/

int32_t
HTable_is_empty( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count ==  0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   HTable_has
*/

int32_t
HTable_has( Prefix )( HTable_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( node_t *node_pc = ( *(*current).first_cursor ).item; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t result = has( current, key );

   POSTCONDITION( "current first cursor unchanged", node_pc == ( *(*current).first_cursor ).item );
   POSTCONDITION( "current count unchanged", count_pc == (*current).count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   HTable_cursor_forth
*/
void
HTable_cursor_forth( Prefix )( HTable_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).htable )._type == HTABLE_TYPE ) && ( ( *(*cursor).htable )._key_type == Key_Code ) && ( ( *(*cursor).htable )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );

   if ( (*cursor).item != NULL )
   {
      (*cursor).item = ( *(*cursor).item ).next_in_sequence;
   }

   UNLOCK( (*cursor).mutex );

   return;
}

/**
   HTable_cursor_go
*/
void
HTable_cursor_go( Prefix )( HTable_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).htable )._type == HTABLE_TYPE ) && ( ( *(*cursor).htable )._key_type == Key_Code ) && ( ( *(*cursor).htable )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).htable ).mutex );
   INVARIANT( (*cursor).htable );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < ( *(*cursor).htable ).count ) ) );

   int32_t i = 0;
   (*cursor).item = ( *(*cursor).htable ).first_in_sequence;

   for( i = 1; ( i <= index ) && ( (*cursor).item != NULL ); i++ )
   {
      if ( (*cursor).item != NULL )
      {
         (*cursor).item = ( *(*cursor).item ).next_in_sequence;
      }
   }

   INVARIANT( (*cursor).htable );
   UNLOCK( ( *(*cursor).htable ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   HTable_cursor_index
*/

int32_t
HTable_cursor_index( Prefix )( HTable_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).htable )._type == HTABLE_TYPE ) && ( ( *(*cursor).htable )._key_type == Key_Code ) && ( ( *(*cursor).htable )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).htable ).mutex );
   INVARIANT( (*cursor).htable );

   int32_t result = 0;
   int32_t flag = 0;
   node_t *node = ( *(*cursor).htable ).first_in_sequence;
   node_t *target = (*cursor).item;

   if ( ( *(*cursor).htable ).count > 0 )
   {
      while ( node != NULL )
      {
         if ( node == target )
         {
            flag = 1;
            break;
         }
         result = result + 1;
         node = (*node).next_in_sequence;
      }
   }

   if ( flag == 0 )
   {
      result = -1;
   }

   INVARIANT( (*cursor).htable );
   UNLOCK( ( *(*cursor).htable ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   HTable_cursor_start
*/

void
HTable_cursor_start( Prefix )( HTable_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).htable )._type == HTABLE_TYPE ) && ( ( *(*cursor).htable )._key_type == Key_Code ) && ( ( *(*cursor).htable )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).htable ).mutex );
   INVARIANT( (*cursor).htable );

   (*cursor).item = ( *(*cursor).htable ).first_in_sequence;

   INVARIANT( (*cursor).htable );
   UNLOCK( ( *(*cursor).htable ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   HTable_forth
*/
void
HTable_forth( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   if ( ( *(*current).first_cursor ).item != NULL )
   {
      ( *(*current).first_cursor ).item = ( *( *(*current).first_cursor ).item ).next_in_sequence;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HTable_go
*/
void
HTable_go( Prefix )( HTable_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );

   int32_t i = 0;
   ( *(*current).first_cursor ).item = (*current).first_in_sequence;

   for( i = 1; ( i <= index ) && ( ( *(*current).first_cursor ).item != NULL ); i++ )
   {
      if ( ( *(*current).first_cursor ).item != NULL )
      {
         ( *(*current).first_cursor ).item = ( *( *(*current).first_cursor ).item ).next;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HTable_index
*/

int32_t
HTable_index( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t flag = 0;
   node_t *node = (*current).first_in_sequence;
   node_t *target = ( *(*current).first_cursor ).item;

   if ( (*current).count > 0 )
   {
      while ( node != NULL )
      {
         if ( node == target )
         {
            flag = 1;
            break;
         }
         result = result + 1;
         node = (*node).next_in_sequence;
      }
   }

   if ( flag == 0 )
   {
      result = -1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   HTable_start
*/

void
HTable_start( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   ( *(*current).first_cursor ).item = (*current).first_in_sequence;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HTable_put
*/

void
HTable_put( Prefix )( HTable_type( Prefix ) *current, Type value, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );

   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = has( current, key ) == 1 ? (*current).count : (*current).count + 1; );

   put( current, value, key );

   POSTCONDITION( "count incremented", (*current).count == count_pc );
   POSTCONDITION( "item added", has( current, key ) == 1 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HTable_replace
*/

void
HTable_replace( Prefix )( HTable_type( Prefix ) *current, Type value, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   // design-wise, this precondition should hold true
   // in practice, someone will want replace to be a "put" when the key is not present
   // PRECONDITION( "has item", has( current, key ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = has( current, key ) == 1 ? (*current).count : (*current).count + 1; );

   int32_t hash_code = KEY_HASH_FUNCTION( key );
   int32_t i = hash_code % (*current).bucket_count;

   // get node for new value
   node_t *new_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*current).bucket[i];

   // see if node with this key already exists
   int32_t flag = 0;

   // look through nodes in bucket for match to key
   while ( ( node != NULL ) && ( flag == 0 ) )
   {
      if ( KEY_DEEP_EQUAL_FUNCTION( (*node).key, key ) == 1 )
      {
         flag = 1;
         new_node = node;
      }
      node = (*node).next;
   }

   // if node exists in htable, replace value with new value
   if ( new_node != NULL )
   {
      ( *new_node ).value = value;
      ( *new_node ).key = key;
   }
   else
   {
      // else get new node and put new value at head of bucket
      new_node = node_make();
      ( *new_node ).value = value;
      ( *new_node ).key = key;
      ( *new_node ).next = (*current).bucket[i];
      ( *new_node ).next_in_sequence = NULL;

      // put in sequence
      if ( (*current).last_in_sequence == NULL )
      {
         (*current).first_in_sequence = new_node;
         (*current).last_in_sequence = new_node;
      }
      else
      {
         ( *(*current).last_in_sequence ).next_in_sequence = new_node;
         (*current).last_in_sequence = new_node;
      }

      // put in bucket
      (*current).bucket[i] = new_node;
      (*current).count = (*current).count + 1;
   }

   POSTCONDITION( "count unchanged", (*current).count == count_pc );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HTable_replace_and_dispose
*/

void
HTable_replace_and_dispose( Prefix )( HTable_type( Prefix ) *current, Type value, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   // design-wise, this precondition should hold true
   // in practice, someone will want replace to be a "put" when the key is not present
   // PRECONDITION( "has item", has( current, key ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = has( current, key ) == 1 ? (*current).count : (*current).count + 1; );

   int32_t hash_code = KEY_HASH_FUNCTION( key );
   int32_t i = hash_code % (*current).bucket_count;

   // get node for new value
   node_t *new_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*current).bucket[i];

   // see if node with this key already exists
   int32_t flag = 0;

   // look through nodes in bucket for match to key
   while ( ( node != NULL ) && ( flag == 0 ) )
   {
      if ( KEY_DEEP_EQUAL_FUNCTION( (*node).key, key ) == 1 )
      {
         flag = 1;
         new_node = node;
      }
      node = (*node).next;
   }

   // if node exists in htable, replace value with new value
   // delete previous key unless it is the same as the new key
   // delete previous value unless it is the same as the new value
   if ( new_node != NULL )
   {
      if ( ( *new_node ).key != key )
      {
         KEY_DEEP_DISPOSE_FUNCTION( ( *new_node ).key );
      }
      if ( ( *new_node ).value != value )
      {
         VALUE_DEEP_DISPOSE_FUNCTION( ( *new_node ).value );
      }
      ( *new_node ).key = key;
      ( *new_node ).value = value;
   }
   else
   {
      // else get new node and put new value at head of bucket
      new_node = node_make();
      ( *new_node ).value = value;
      ( *new_node ).key = key;
      ( *new_node ).next = (*current).bucket[i];
      ( *new_node ).next_in_sequence = NULL;

      // put in sequence
      if ( (*current).last_in_sequence == NULL )
      {
         (*current).first_in_sequence = new_node;
         (*current).last_in_sequence = new_node;
      }
      else
      {
         ( *(*current).last_in_sequence ).next_in_sequence = new_node;
         (*current).last_in_sequence = new_node;
      }

      // put in bucket
      (*current).bucket[i] = new_node;
      (*current).count = (*current).count + 1;
   }

   POSTCONDITION( "count unchanged", (*current).count == count_pc );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HTable_remove
*/

void
HTable_remove( Prefix )( HTable_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has key", has( current, key ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = has( current, key ) ? (*current).count - 1 : (*current).count; );

   int32_t hash_code = KEY_HASH_FUNCTION( key );
   int32_t i = hash_code % (*current).bucket_count;

   // get node for search
   node_t *last_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*current).bucket[i];

   // see if first node in bucket matches
   if ( KEY_DEEP_EQUAL_FUNCTION( (*node).key, key ) == 1 )
   {
      // remove first node
      (*current).bucket[i] = (*node).next;
      move_all_cursors_forth_after_node_removal( current, node );
      remove_node_from_sequence( current, node );
      node_dispose( &node );
      (*current).count = (*current).count - 1;
   }
   else
   {
      last_node = node;
      node = (*node).next;

      // if not, look through rest of nodes in bucket for match to key
      while ( node != NULL )
      {
         if ( KEY_DEEP_EQUAL_FUNCTION( (*node).key, key ) == 1 )
         {
            ( *last_node ).next = (*node).next;
            move_all_cursors_forth_after_node_removal( current, node );
            remove_node_from_sequence( current, node );
            node_dispose( &node );
            (*current).count = (*current).count - 1;
            break;
         }

         last_node = node;
         node = (*node).next;
      }
   }

   // if count now zero, set first and last in sequence to  NULL
   if ( (*current).count == 0 )
   {
      (*current).first_in_sequence = NULL;
      (*current).last_in_sequence = NULL;
   }

   POSTCONDITION( "count decremented", (*current).count == count_pc );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HTable_remove_and_dispose
*/

void
HTable_remove_and_dispose( Prefix )( HTable_type( Prefix ) *current, Key key )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has key", has( current, key ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = has( current, key ) ? (*current).count - 1 : (*current).count; );

   int32_t hash_code = KEY_HASH_FUNCTION( key );
   int32_t i = hash_code % (*current).bucket_count;

   // get node for search
   node_t *last_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*current).bucket[i];

   // see if first node in bucket matches
   if ( KEY_DEEP_EQUAL_FUNCTION( (*node).key, key ) == 1 )
   {
      // remove first node
      (*current).bucket[i] = (*node).next;
      KEY_DEEP_DISPOSE_FUNCTION( (*node).key );
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
      move_all_cursors_forth_after_node_removal( current, node );
      remove_node_from_sequence( current, node );
      node_dispose( &node );
      (*current).count = (*current).count - 1;
   }
   else
   {
      last_node = node;
      node = (*node).next;

      // if not, look through rest of nodes in bucket for match to key
      while ( node != NULL )
      {
         if ( KEY_DEEP_EQUAL_FUNCTION( (*node).key, key ) == 1 )
         {
            ( *last_node ).next = (*node).next;
            KEY_DEEP_DISPOSE_FUNCTION( (*node).key );
            VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
            move_all_cursors_forth_after_node_removal( current, node );
            remove_node_from_sequence( current, node );
            node_dispose( &node );
            (*current).count = (*current).count - 1;
            break;
         }

         last_node = node;
         node = (*node).next;
      }
   }

   // if count now zero, set first and last in sequence to  NULL
   if ( (*current).count == 0 )
   {
      (*current).first_in_sequence = NULL;
      (*current).last_in_sequence = NULL;
   }

   if ( (*current).count == 1 )
   {
      (*current).last_in_sequence = (*current).first_in_sequence;
   }

   POSTCONDITION( "count decremented", (*current).count == count_pc );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HTable_wipe_out
*/

void
HTable_wipe_out( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // delete htable sequence nodes
   node_t *node = (*current).first_in_sequence;
   node_t *next = NULL;
   while( node != NULL )
   {
      next = (*node).next_in_sequence;
      node_dispose( &node );
      node = next;
   }

   // delete cursors, all but first
   HTable_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   HTable_cursor_type( Prefix ) *next_cursor = NULL;
   ( *(*current).first_cursor ).next_cursor = NULL;
   (*current).last_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // clear out buckets
   memset( (*current).bucket, 0, (*current).bucket_count * sizeof( node_t * ) );

   // set count to zero
   (*current).count = 0;
   (*current).first_in_sequence = NULL;
   (*current).last_in_sequence = NULL;

   POSTCONDITION( "is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HTable_wipe_out_and_dispose
*/

void
HTable_wipe_out_and_dispose( Prefix )( HTable_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // delete htable sequence nodes
   node_t *node = (*current).first_in_sequence;
   node_t *next = NULL;
   while( node != NULL )
   {
      next = (*node).next_in_sequence;
      KEY_DEEP_DISPOSE_FUNCTION( (*node).key );
      VALUE_DEEP_DISPOSE_FUNCTION( (*node).value );
      node_dispose( &node );
      node = next;
   }

   // delete cursors, all but first
   HTable_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   HTable_cursor_type( Prefix ) *next_cursor = NULL;
   ( *(*current).first_cursor ).next_cursor = NULL;
   (*current).last_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // clear out buckets
   memset( (*current).bucket, 0, (*current).bucket_count * sizeof( node_t * ) );

   // set count to zero
   (*current).count = 0;
   (*current).first_in_sequence = NULL;
   (*current).last_in_sequence = NULL;

   POSTCONDITION( "is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HTable_set_bucket_count
*/

void
HTable_set_bucket_count( Prefix )( HTable_type( Prefix ) *current, int32_t new_bucket_count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HTABLE_TYPE ) && ( (*current)._key_type = Key_Code ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "bucket count ok", new_bucket_count > 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // change size of bucket array
   (*current).bucket
      = ( node_t ** ) realloc( (*current).bucket, new_bucket_count * sizeof( node_t * ) );
   CHECK( "(*current).bucket allocated correctly", (*current).bucket != NULL );

   (*current).bucket_count = new_bucket_count;


   // zero out bucket array
   memset( (*current).bucket, 0, (*current).bucket_count * sizeof( node_t * ) );

   // fill the buckets
   node_t *node = NULL;

   int32_t hash_code = 0;
   int32_t i = 0;

   for (   node = (*current).first_in_sequence;
           node != NULL;
           node = (*node).next_in_sequence
       )
   {
      hash_code = KEY_HASH_FUNCTION( (*node).key );
      i = hash_code % (*current).bucket_count;
      (*node).next = (*current).bucket[i];
      (*current).bucket[i] = node;
   }

   POSTCONDITION( "bucket count set", (*current).bucket_count == new_bucket_count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


#ifdef __cplusplus
}
#endif

/* End of file */

