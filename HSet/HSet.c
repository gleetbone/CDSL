/**
 @file HSet.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Hash Sets"

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

 Function definitions for the opaque HSet_t type.

*/

#include "HSet.h"

#include "protocol.h"

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
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

#define DEFAULT_BUCKET_SIZE 13

/**
   Node structure declaration
*/

struct node;

/**
   Node structure definition. Holds an item.
*/

struct node
{
   Item item;
   struct node *next;
   struct node *next_in_sequence;
};

typedef struct node node_t;

/**
   Hash set structure definition.
*/

struct HSet_struct( Prefix )
{

   PROTOCOLS_DEFINITION;

   int32_t _type;
   int32_t _item_type;

   node_t *first_in_sequence;
   node_t *last_in_sequence;
   int32_t count;
   node_t **bucket; ///< array of pointers to node_t
   int32_t bucket_count;
   HSet_cursor_type( Prefix ) *first_cursor;
   HSet_cursor_type( Prefix ) *last_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure definition. Holds reference to hset, holds a sequence
   location, and holds a pointer to the next cursor.
*/

struct HSet_cursor_struct( Prefix )
{
   HSet_type( Prefix ) *hset;
   node_t *item;
   HSet_cursor_type( Prefix ) *next_cursor;

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

   Return 1 if hset has an item for key, 0 if not

   @param current HSet_t instance
   @param key the key to query for
   @return 1 if true, 0 otherwise
*/

static
int32_t
has( HSet_type( Prefix ) *current, Item item )
{
   int32_t hash_code = HASH_FUNCTION( item );
   int32_t i = hash_code % (*current).bucket_count;
   int32_t result = 0;

   node_t *node = (*current).bucket[i];

   // look through nodes in bucket for match to item
   while ( ( node != NULL ) && ( result == 0 ) )
   {
      if ( DEEP_EQUAL_FUNCTION( (*node).item, item ) == 1 )
      {
         result = 1;
      }
      node = (*node).next;
   }

   return result;
}

/**
   compare_hsets_shallow_equal

   see if two hsets are equal

   @param hset_1 the first hset
   @param hset_2 the other hset
   @return 1 if equal, 0 otherwise
*/
static
int32_t
compare_hsets_shallow_equal
(
   HSet_type( Prefix ) *hset_1,
   HSet_type( Prefix ) *hset_2
)
{
   int32_t result = 0;
   int32_t flag = 0;
   node_t *node_1 = NULL;
   node_t *node_2 = NULL;

   node_1 = ( *hset_1 ).first_in_sequence;

   while( node_1 != NULL )
   {
      node_2 = ( *hset_2 ).first_in_sequence;
      while( node_2 != NULL )
      {
         if ( ( *node_1 ).item == ( *node_2 ).item )
         {
            flag = flag + 1;
            break;
         }
         node_2 = ( *node_2 ).next_in_sequence;
      }
      node_1 = ( *node_1 ).next_in_sequence;
   }

   if ( ( flag == ( *hset_1 ).count ) && ( flag == ( *hset_2 ).count ) )
   {
      result = 1;
   }

   return result;
}

/**
   compare_hsets_deep_equal

   see if two hsets are deep equal

   @param hset_1 the first hset
   @param hset_2 the other hset
   @return 1 if equal, 0 otherwise
*/
static
int32_t
compare_hsets_deep_equal
(
   HSet_type( Prefix ) *hset_1,
   HSet_type( Prefix ) *hset_2
)
{
   int32_t result = 0;
   int32_t flag = 0;
   node_t *node_1 = NULL;
   node_t *node_2 = NULL;

   node_1 = ( *hset_1 ).first_in_sequence;

   while( node_1 != NULL )
   {
      node_2 = ( *hset_2 ).first_in_sequence;
      while( node_2 != NULL )
      {
         if ( DEEP_EQUAL_FUNCTION( ( *node_1 ).item, ( *node_2 ).item ) == 1 )
         {
            flag = flag + 1;
            break;
         }
         node_2 = ( *node_2 ).next_in_sequence;
      }
      node_1 = ( *node_1 ).next_in_sequence;
   }

   if ( ( flag == ( *hset_1 ).count ) && ( flag == ( *hset_2 ).count ) )
   {
      result = 1;
   }

   return result;
}

/**
   compare_hset_items_to_array_items

   compare values in hset to array of values

   @param current the hset
   @param array the array of values
   @param count the number of values in the array
   @return 1 if equal, 0 otherwise
*/
static
int32_t
compare_hset_items_to_array_items
(
   HSet_type( Prefix ) *current,
   Item *array,
   int32_t count
)
{
   int32_t result = 0;
   int32_t i = 0;
   int32_t flag = 0;
   node_t *node = NULL;

   for ( i = 0; i < count; i++ )
   {
      node = (*current).first_in_sequence;
      while( node != NULL )
      {
         if ( (*node).item == array[i] )
         {
            flag = flag + 1;
            break;
         }
         node = (*node).next_in_sequence;
      }
   }

   if ( ( flag == (*current).count ) && ( flag == count ) )
   {
      result = 1;
   }

   return result;
}


/**
   put

   insert a value in the htable for the given key if key not present,
   replace the value if key present. do not dispose the existing value

   @param current the hset
   @param value the value to put in the hset
*/

static
void
put( HSet_type( Prefix ) *current, Item value )
{
   int32_t hash_code = HASH_FUNCTION( value );
   int32_t i = hash_code % (*current).bucket_count;

   // get node for new value
   node_t *new_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*current).bucket[i];

   // see if node with this item already exists
   int32_t flag = 0;

   // look through nodes in bucket for match to item
   while ( ( node != NULL ) && ( flag == 0 ) )
   {
      if ( DEEP_EQUAL_FUNCTION( (*node).item, value ) == 1 )
      {
         flag = 1;
         new_node = node;
      }
      node = (*node).next;
   }

   // if node exists in current, replace value with new value
   if ( new_node != NULL )
   {
      ( *new_node ).item = value;
   }
   else
   {
      // else get new node and put new value at head of bucket
      new_node = node_make();
      ( *new_node ).item = value;
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
   move_all_cursors_forth_after_node_removal

   After a node has been removed, move all cursors pointing to that node
   forth.

   @param current HSet_t instance
   @param node the just removed node
*/
static
void
move_all_cursors_forth_after_node_removal
(
   HSet_type( Prefix ) *current,
   node_t *node
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "node not null", node != NULL );

   HSet_cursor_type( Prefix ) *cursor = NULL;

   for (  cursor = (*current).first_cursor;
          cursor != NULL;
          cursor = (*cursor).next_cursor
       )
   {
      if ( (*cursor).item != NULL )
      {
         if ( (*cursor).item == node )
         {
            HSet_cursor_forth( Prefix )( cursor );
         }
      }
   }

   return;
}

/**
   remove_node_from_sequence

   Remove node from sequence. Does not delete node, does not change count,
   does not change bucket contents.

   @param current HSet_t instance
   @param node the to be removed node
*/
static
void
remove_node_from_sequence
(
   HSet_type( Prefix ) *current,
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
   move_all_cursors_off

   Set all cursors off.

   @param current HSet_t instance
*/
static
void
move_all_cursors_off
(
   HSet_type( Prefix ) *current
)
{
   PRECONDITION( "current not null", current != NULL );

   HSet_cursor_type( Prefix ) *cursor = NULL;

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
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
is_empty_implies_first_last_null( HSet_type( Prefix ) *current )
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
nonnegative_count( HSet_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).count >= 0 );

   return result;
}

static
int32_t
last_in_sequence_ok( HSet_type( Prefix ) *current )
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
valid_sequence_count( HSet_type( Prefix ) *current )
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
valid_bucket_count( HSet_type( Prefix ) *current )
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
first_cursor_not_null( HSet_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).first_cursor != NULL );

   return result;
}

static
int32_t
last_cursor_next_null( HSet_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( (*current).last_cursor != NULL )
   {
      result = ( ( *(*current).last_cursor ).next_cursor == NULL );
   }

   return result;
}

static
void invariant( HSet_type( Prefix ) *current )
{
   assert( ( ( void ) "empty implies first and last null", is_empty_implies_first_last_null( current ) ) );
   assert( ( ( void ) "nonnegative count", nonnegative_count( current ) ) );
   assert( ( ( void ) "last in sequence OK", last_in_sequence_ok( current ) ) );
   assert( ( ( void ) "valid sequence count", valid_sequence_count( current ) ) );
   assert( ( ( void ) "valid bucket count", valid_bucket_count( current ) ) );
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
   HSet_dispose( Prefix ),
   HSet_deep_dispose( Prefix ),
   HSet_is_equal( Prefix ),
   HSet_is_deep_equal( Prefix ),
   HSet_copy( Prefix ),
   HSet_deep_copy( Prefix ),
   HSet_clone( Prefix ),
   HSet_deep_clone( Prefix )
};

static
void *
p_iterable_table[P_ITERABLE_FUNCTION_COUNT]
=
{
   HSet_count( Prefix ),
   HSet_item_at( Prefix ),
   HSet_off( Prefix ),
   HSet_is_empty( Prefix ),
   HSet_start( Prefix ),
   HSet_forth( Prefix )
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

   }

   return result;
}

#endif // PROTOCOLS_ENABLED

/**
   HSet_make
*/

HSet_type( Prefix ) *
HSet_make( Prefix )( void )
{
   // allocate result struct
   HSet_type( Prefix ) * result
      = ( HSet_type( Prefix ) * ) calloc( 1, sizeof( HSet_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = HSET_TYPE;
   (*result)._item_type = Type_Code;

   (*result).count = 0;

   // allocate bucket array, default size
   (*result).bucket = ( node_t ** ) calloc( DEFAULT_BUCKET_SIZE, sizeof( node_t * ) );
   CHECK( "(*result).bucket allocated correctly", (*result).bucket != NULL );

   (*result).bucket_count = DEFAULT_BUCKET_SIZE;

   // set built-in cursor
   // allocate cursor struct
   HSet_cursor_type( Prefix ) *cursor
      =  ( HSet_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HSet_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set result
   (*cursor).hset = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set result built-in cursor
   (*result).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new result is empty", (*result).count == 0 );
   POSTCONDITION( "new result cursor is off", ( ( *(*result).first_cursor ).item == NULL ) );

   INVARIANT( result );

   return result;
}

/**
   HSet_make_n
*/

HSet_type( Prefix ) *
HSet_make_n( Prefix )( int32_t bucket_count )
{
   PRECONDITION( "bucket count ok", bucket_count > 0 );

   // allocate result struct
   HSet_type( Prefix ) * result
      = ( HSet_type( Prefix ) * ) calloc( 1, sizeof( HSet_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = HSET_TYPE;
   (*result)._item_type = Type_Code;

   (*result).count = 0;

   // allocate bucket array
   (*result).bucket = ( node_t ** ) calloc( bucket_count, sizeof( node_t * ) );
   CHECK( "(*result).bucket allocated correctly", (*result).bucket != NULL );

   (*result).bucket_count = bucket_count;

   // set built-in cursor
   // allocate cursor struct
   HSet_cursor_type( Prefix ) *cursor
      =  ( HSet_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HSet_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set result
   (*cursor).hset = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set result built-in cursor
   (*result).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new result is empty", (*result).count == 0 );
   POSTCONDITION( "new result cursor is off", ( ( *(*result).first_cursor ).item == NULL ) );
   POSTCONDITION( "bucket count set", (*result).bucket_count == bucket_count );

   INVARIANT( result );

   return result;
}

/**
   HSet_make_from_array
*/

HSet_type( Prefix ) *
HSet_make_from_array( Prefix )( Item *array, int32_t count )
{
   PRECONDITION( "array not null", array != NULL );
   PRECONDITION( "count ok", count >= 0 );

   // allocate hset struct
   HSet_type( Prefix ) *result = HSet_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = HSET_TYPE;
   (*result)._item_type = Type_Code;

   int32_t i = 0;

   // put items from hset into result
   for ( i = 0; i < count; i++ )
   {
      put( result, array[i] );
   }

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new hset has count items", (*result).count == count );
   POSTCONDITION( "new hset cursor is off", ( ( *(*result).first_cursor ).item == NULL ) );
   POSTCONDITION( "hset has array items", compare_hset_items_to_array_items( result, array, count ) == 1 );

   INVARIANT( result );

   return result;
}

/**
   HSet_cursor_make
*/

HSet_cursor_type( Prefix ) *
HSet_cursor_make( Prefix )( HSet_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // allocate cursor struct
   HSet_cursor_type( Prefix ) *cursor
      =  ( HSet_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HSet_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set current
   (*cursor).hset = current;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // place cursor reference into current structure
   if ( (*current).last_cursor == NULL )
   {
      // set second cursor for current
      ( *(*current).first_cursor ).next_cursor = cursor;
      (*current).last_cursor = cursor;
   }
   else
   {
      // set additional cursor for current
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
   HSet_clone
*/

HSet_type( Prefix ) *
HSet_clone( Prefix )( HSet_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // allocate current struct
   HSet_type( Prefix ) * result
      = ( HSet_type( Prefix ) * ) calloc( 1, sizeof( HSet_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = HSET_TYPE;
   (*result)._item_type = Type_Code;

   (*result).count = 0;

   // allocate bucket array
   (*result).bucket = ( node_t ** ) calloc( (*current).bucket_count, sizeof( node_t * ) );
   CHECK( "(*result).bucket allocated correctly", (*result).bucket != NULL );

   (*result).bucket_count = (*current).bucket_count;

   // set built-in cursor
   // allocate cursor struct
   HSet_cursor_type( Prefix ) *cursor
      =  ( HSet_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HSet_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set current
   (*cursor).hset = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set current built-in cursor
   (*result).first_cursor = cursor;

   int32_t i = 0;
   node_t *node = (*current).first_in_sequence;

   // put items from current into result
   for ( i = 0; i < (*current).count; i++ )
   {
      put( result, (*node).item );
      node = (*node).next_in_sequence;
   }

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new current has count items", (*result).count == (*current).count );
   POSTCONDITION( "new current cursor is off", ( ( *(*result).first_cursor ).item == NULL ) );
   POSTCONDITION( "new current clone is equal to original", compare_hsets_shallow_equal( result, current ) == 1 );

   INVARIANT( result );

   UNLOCK( (*current).mutex );

   return result;
}

/**
   HSet_deep_clone
*/

HSet_type( Prefix ) *
HSet_deep_clone( Prefix )( HSet_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );

   INVARIANT( current );

   // allocate current struct
   HSet_type( Prefix ) * result
      = ( HSet_type( Prefix ) * ) calloc( 1, sizeof( HSet_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = HSET_TYPE;
   (*result)._item_type = Type_Code;

   (*result).count = 0;

   // allocate bucket array
   (*result).bucket = ( node_t ** ) calloc( (*current).bucket_count, sizeof( node_t * ) );
   CHECK( "(*result).bucket allocated correctly", (*result).bucket != NULL );

   (*result).bucket_count = (*current).bucket_count;

   // set built-in cursor
   // allocate cursor struct
   HSet_cursor_type( Prefix ) *cursor
      =  ( HSet_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HSet_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated correctly", cursor != NULL );

   // set current
   (*cursor).hset = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set current built-in cursor
   (*result).first_cursor = cursor;

   int32_t i = 0;
   node_t *node = (*current).first_in_sequence;

   Item item;
   // put items from current into result
   for ( i = 0; i < (*current).count; i++ )
   {
      item = DEEP_CLONE_FUNCTION( (*node).item );
      put( result, item );
      node = (*node).next_in_sequence;
   }

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new current has count items", (*result).count == (*current).count );
   POSTCONDITION( "new current cursor is off", ( ( *(*result).first_cursor ).item == NULL ) );
   POSTCONDITION( "new current clone is equal to original", compare_hsets_deep_equal( result, current ) == 1 );

   INVARIANT( result );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   HSet_is_equal
*/

int32_t
HSet_is_equal( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );
   INVARIANT( current );

   int32_t result = 1;
   int32_t i = 0;
   node_t *node = (*other).first_in_sequence;

   // check count
   if ( (*current).count != (*other).count )
   {
      result = 0;
   }

   // check items from other are in current
   for ( i = 0; i < (*other).count; i++ )
   {
      if ( result == 1 )
      {
         if ( has( current, (*node).item ) == 0 )
         {
            result = 0;
            break;
         }
         node = (*node).next_in_sequence;
      }
      else
      {
         break;
      }
   }

   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   INVARIANT( current );

   return result;
}

/**
   HSet_is_deep_equal
*/

int32_t
HSet_is_deep_equal( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 1;
   int32_t i = 0;
   node_t *node = (*other).first_in_sequence;

   LOCK( (*other).mutex );

   // check count
   if ( (*current).count != (*other).count )
   {
      result = 0;
   }

   // check items from other are in current
   for ( i = 0; i < (*other).count; i++ )
   {
      if ( result == 1 )
      {
         if ( has( current, (*node).item ) == 0 )
         {
            result = 0;
            break;
         }
         node = (*node).next_in_sequence;
      }
      else
      {
         break;
      }
   }

   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   INVARIANT( current );

   return result;
}

/**
   HSet_copy
*/

void
HSet_copy( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   node_t *node = (*other).first_in_sequence;

   // clean out current hset

   // delete hset sequence items
   node_t *node1 = (*current).first_in_sequence;
   node_t *next = NULL;

   while( node1 != NULL )
   {
      next = (*node1).next_in_sequence;
      DEEP_DISPOSE_FUNCTION( (*node1).item );
      node_dispose( &node1 );
      node1 = next;
   }

   // delete cursors
   HSet_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   HSet_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // set first cursor's next cursor to NULL
   ( *(*current).first_cursor ).next_cursor = NULL;

   // and set last cursor to first cursor
   (*current).last_cursor = (*current).first_cursor;

   // clear out buckets
   memset( (*current).bucket, 0, (*current).bucket_count * sizeof( node_t * ) );

   // set all cursors off
   move_all_cursors_off( current );

   // set count to zero
   (*current).count = 0;

   // set sequence pointers
   (*current).first_in_sequence = NULL;
   (*current).last_in_sequence = NULL;

   LOCK( (*other).mutex );

   // put items from other into current
   for ( i = 0; i < (*other).count; i++ )
   {
      put( current, (*node).item );
      node = (*node).next_in_sequence;
   }

   POSTCONDITION( "hset copy is equal to original", compare_hsets_shallow_equal( current, other ) == 1 );

   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   INVARIANT( current );

   return;
}

/**
   HSet_deep_copy
*/

void
HSet_deep_copy( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   node_t *node = (*other).first_in_sequence;
   Item item_clone;

   // clean out current hset

   // delete hset sequence items
   node_t *node1 = (*current).first_in_sequence;
   node_t *next = NULL;

   while( node1 != NULL )
   {
      next = (*node1).next_in_sequence;
      DEEP_DISPOSE_FUNCTION( (*node1).item );
      node_dispose( &node1 );
      node1 = next;
   }

   // delete cursors
   HSet_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   HSet_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // set first cursor's next cursor to NULL
   ( *(*current).first_cursor ).next_cursor = NULL;

   // and set last cursor to first cursor
   (*current).last_cursor = (*current).first_cursor;

   // clear out buckets
   memset( (*current).bucket, 0, (*current).bucket_count * sizeof( node_t * ) );

   // set all cursors off
   move_all_cursors_off( current );

   // set count to zero
   (*current).count = 0;

   // set sequence pointers
   (*current).first_in_sequence = NULL;
   (*current).last_in_sequence = NULL;


   LOCK( (*other).mutex );

   // put items from other into current
   for ( i = 0; i < (*other).count; i++ )
   {
      item_clone = DEEP_CLONE_FUNCTION( (*node).item );
      put( current, item_clone );
      node = (*node).next_in_sequence;
   }

   POSTCONDITION( "hset copy is equal to original", compare_hsets_deep_equal( current, other ) == 1 );

   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   INVARIANT( current );

   return;
}

/**
   HSet_dispose
*/

void
HSet_dispose( Prefix )( HSet_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == HSET_TYPE ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete current sequence items
   node_t *node1 = (**current).first_in_sequence;
   node_t *next = NULL;
   while( node1 != NULL )
   {
      next = (*node1).next_in_sequence;
      node_dispose( &node1 );
      node1 = next;
   }

   // delete cursors
   HSet_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   HSet_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // delete bucket array
   free( (**current).bucket );

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set current to NULL
   *current = NULL;

   return;
}

/**
   HSet_deep_dispose
*/

void
HSet_deep_dispose( Prefix )( HSet_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == HSET_TYPE ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete current sequence items
   node_t *node1 = (**current).first_in_sequence;
   node_t *next = NULL;
   while( node1 != NULL )
   {
      next = (*node1).next_in_sequence;
      DEEP_DISPOSE_FUNCTION( (*node1).item );
      node_dispose( &node1 );
      node1 = next;
   }

   // delete cursors
   HSet_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   HSet_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // delete bucket array
   free( (**current).bucket );

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set current to NULL
   *current = NULL;

   return;
}

/**
   HSet_cursor_dispose
*/

void
HSet_cursor_dispose( Prefix )( HSet_cursor_type( Prefix ) **cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "*cursor not null", *cursor != NULL );
   PRECONDITION( "cursor hset type ok", ( ( *(**cursor).hset )._type == HSET_TYPE ) && ( ( *(**cursor).hset )._item_type == Type_Code ) );
   LOCK( (**cursor).mutex );
   LOCK( ( *(**cursor).hset ).mutex );
   INVARIANT( (**cursor).hset );

   HSet_type( Prefix ) *hset = (**cursor).hset;

   HSet_cursor_type( Prefix ) *c1 = NULL;
   HSet_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from hset structure
   c1 = ( *(**cursor).hset ).first_cursor;
   c2 = (*c1).next_cursor;

   // search through the cursors
   while ( ( c2 != NULL ) && ( flag == 0 ) )
   {
      if ( c2 == *cursor )
      {
         // if we have a match, remove "c2" from the cursor hset, set flag
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

   // set hset's last cursor
   c1 = ( *(**cursor).hset ).first_cursor;
   while ( c1 != NULL )
   {
      c2 = c1;
      c1 = (*c1).next_cursor;
   }
   ( *(**cursor).hset ).last_cursor = c2;

   // only one cursor, last_cursor is NULL
   if ( c2 == ( *(**cursor).hset ).first_cursor )
   {
      ( *(**cursor).hset ).last_cursor = NULL;
   }

   // delete cursor struct
   free(*cursor);

   // set cursor to NULL
   *cursor = NULL;

   INVARIANT( hset );
   UNLOCK( (*hset).mutex );

   return;
}


/**
   HSet_cursor_item_at
*/

Item
HSet_cursor_item_at( Prefix )( HSet_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor hset type ok", ( ( *(*cursor).hset )._type == HSET_TYPE ) && ( ( *(*cursor).hset )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).hset ).mutex );
   INVARIANT( (*cursor).hset );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Item item = ( *(*cursor).item ).item;

   INVARIANT( (*cursor).hset );
   UNLOCK( ( *(*cursor).hset ).mutex );
   UNLOCK( (*cursor).mutex );

   return item;
}

/**
   HSet_item_at
*/

Item
HSet_item_at( Prefix )( HSet_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).item != NULL );

   HSet_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   Item item = ( *(*cursor).item ).item;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return item;
}

/**
   HSet_item
*/

Item
HSet_item( Prefix )( HSet_type( Prefix ) *current, Item item )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has item", has( current, item ) );

   int32_t hash_code = HASH_FUNCTION( item );
   int32_t i = hash_code % (*current).bucket_count;

   // get first of bucket's nodes
   node_t *node = (*current).bucket[i];

   Item result = ( *(*current).first_in_sequence ).item;

   // look through nodes in bucket for match to item
   while ( node != NULL )
   {
      if ( DEEP_EQUAL_FUNCTION( (*node).item, item ) == 1 )
      {
         result = (*node).item;
         break;
      }
      node = (*node).next;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   HSet_item_at_index
*/

Item
HSet_item_at_index( Prefix )( HSet_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   int32_t i = 0;
   node_t *node = (*current).first_in_sequence;

   for( i = 1; i <= index; i ++ )
   {
      node = (*node).next_in_sequence;
   }

   Item item = (*node).item;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return item;
}

/**
   HSet_as_array
*/

Item *
HSet_as_array( Prefix )( HSet_type( Prefix ) *current, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;

   Item *result = ( Item * ) calloc( (*current).count + 1, sizeof( Item ) );
   CHECK( "result allocated correctly", result != NULL );

   node_t *node = (*current).first_in_sequence;

   // put nodes into array
   while ( node != NULL )
   {
      result[i] = (*node).item;
      i = i + 1;
      node = (*node).next_in_sequence;
   }

   (*count) = (*current).count;

   POSTCONDITION( "result contains items of current", compare_hset_items_to_array_items( current, result, *count ) );

   INVARIANT( current );

   UNLOCK( (*current).mutex );

   return result;
}

/**
   HSet_count
*/

int32_t
HSet_count( Prefix )( HSet_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   HSet_bucket_count
*/

int32_t
HSet_bucket_count( Prefix )( HSet_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = (*current).bucket_count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   HSet_off
*/

int32_t
HSet_off( Prefix )( HSet_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( ( *(*current).first_cursor ).item == NULL );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   HSet_cursor_off
*/

int32_t
HSet_cursor_off( Prefix )( HSet_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor hset type ok", ( ( *(*cursor).hset )._type == HSET_TYPE ) && ( ( *(*cursor).hset )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );

   int32_t result = ( (*cursor).item == NULL );

   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   HSet_is_empty
*/

int32_t
HSet_is_empty( Prefix )( HSet_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count ==  0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   HSet_has
*/

int32_t
HSet_has( Prefix )( HSet_type( Prefix ) *current, Item item )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( node_t *node_pc = ( *(*current).first_cursor ).item; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t result = has( current, item );

   POSTCONDITION( "current first cursor unchanged", node_pc == ( *(*current).first_cursor ).item );
   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   HSet_cursor_forth
*/
void
HSet_cursor_forth( Prefix )( HSet_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor hset type ok", ( ( *(*cursor).hset )._type == HSET_TYPE ) && ( ( *(*cursor).hset )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );

   if ( (*cursor).item != NULL )
   {
      (*cursor).item = ( *(*cursor).item ).next_in_sequence;
   }

   UNLOCK( (*cursor).mutex );

   return;
}

/**
   HSet_cursor_go
*/
void
HSet_cursor_go( Prefix )( HSet_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor hset type ok", ( ( *(*cursor).hset )._type == HSET_TYPE ) && ( ( *(*cursor).hset )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).hset ).mutex );
   INVARIANT( (*cursor).hset );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < ( *(*cursor).hset ).count ) ) );

   int32_t i = 0;
   (*cursor).item = ( *(*cursor).hset ).first_in_sequence;

   for( i = 1; ( i <= index ) && ( (*cursor).item != NULL ); i++ )
   {
      (*cursor).item = ( *(*cursor).item ).next_in_sequence;
   }

   INVARIANT( (*cursor).hset );
   UNLOCK( ( *(*cursor).hset ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   HSet_cursor_index
*/

int32_t
HSet_cursor_index( Prefix )( HSet_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor hset type ok", ( ( *(*cursor).hset )._type == HSET_TYPE ) && ( ( *(*cursor).hset )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).hset ).mutex );
   INVARIANT( (*cursor).hset );

   int32_t result = 0;
   int32_t flag = 0;
   node_t *node = ( *(*cursor).hset ).first_in_sequence;
   node_t *target = (*cursor).item;

   if ( ( *(*cursor).hset ).count > 0 )
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

   INVARIANT( (*cursor).hset );
   UNLOCK( ( *(*cursor).hset ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   HSet_cursor_start
*/

void
HSet_cursor_start( Prefix )( HSet_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor hset type ok", ( ( *(*cursor).hset )._type == HSET_TYPE ) && ( ( *(*cursor).hset )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).hset ).mutex );
   INVARIANT( (*cursor).hset );

   (*cursor).item = ( *(*cursor).hset ).first_in_sequence;

   INVARIANT( (*cursor).hset );
   UNLOCK( ( *(*cursor).hset ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   HSet_forth
*/
void
HSet_forth( Prefix )( HSet_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   HSet_go
*/
void
HSet_go( Prefix )( HSet_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );

   int32_t i = 0;
   ( *(*current).first_cursor ).item = (*current).first_in_sequence;

   for( i = 1; ( i <= index ) && ( ( *(*current).first_cursor ).item != NULL ); i++ )
   {
      ( *(*current).first_cursor ).item = ( *( *(*current).first_cursor ).item ).next_in_sequence;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HSet_index
*/

int32_t
HSet_index( Prefix )( HSet_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
   HSet_start
*/

void
HSet_start( Prefix )( HSet_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   ( *(*current).first_cursor ).item = (*current).first_in_sequence;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HSet_put
*/

void
HSet_put( Prefix )( HSet_type( Prefix ) *current, Item item )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = has( current, item ) == 1 ? (*current).count : (*current).count + 1; );

   put( current, item );

   POSTCONDITION( "count incremented", (*current).count == count_pc );
   POSTCONDITION( "item added", has( current, item ) == 1 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HSet_replace
*/

void
HSet_replace( Prefix )( HSet_type( Prefix ) *current, Item item )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has item", has( current, item ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t hash_code = HASH_FUNCTION( item );
   int32_t i = hash_code % (*current).bucket_count;

   // get node for new value
   node_t *new_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*current).bucket[i];

   // see if node with this item already exists
   int32_t flag = 0;

   // look through nodes in bucket for match to item
   while ( ( node != NULL ) && ( flag == 0 ) )
   {
      if ( DEEP_EQUAL_FUNCTION( (*node).item, item ) == 1 )
      {
         flag = 1;
         new_node = node;
      }
      node = (*node).next;
   }

   // if node exists in current, replace value with new value
   if ( new_node != NULL )
   {
      ( *new_node ).item = item;
   }

   POSTCONDITION( "count unchanged", (*current).count == count_pc );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HSet_replace_and_dispose
*/

void
HSet_replace_and_dispose( Prefix )( HSet_type( Prefix ) *current, Item item )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has item", has( current, item ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t hash_code = HASH_FUNCTION( item );
   int32_t i = hash_code % (*current).bucket_count;

   // get node for new value
   node_t *new_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*current).bucket[i];

   // see if node with this item already exists
   int32_t flag = 0;

   // look through nodes in bucket for match to item
   while ( ( node != NULL ) && ( flag == 0 ) )
   {
      if ( DEEP_EQUAL_FUNCTION( (*node).item, item ) == 1 )
      {
         flag = 1;
         new_node = node;
      }
      node = (*node).next;
   }

   // if node exists in current, replace value with new value
   if ( new_node != NULL )
   {
      DEEP_DISPOSE_FUNCTION( ( *new_node ).item );
      ( *new_node ).item = item;
   }

   POSTCONDITION( "count unchanged", (*current).count == count_pc );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   remove
*/

static
void
remove( HSet_type( Prefix ) *current, Item item )
{
   int32_t hash_code = HASH_FUNCTION( item );
   int32_t i = hash_code % (*current).bucket_count;
   int32_t flag = 0;

   // get node for search
   node_t *last_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*current).bucket[i];

   // see if first node in bucket matches
   if ( DEEP_EQUAL_FUNCTION( (*node).item, item ) == 1 )
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

      // if not, look through rest of nodes in bucket for match to item
      while ( ( node != NULL ) && ( flag == 0 ) )
      {
         if ( DEEP_EQUAL_FUNCTION( (*node).item, item ) == 1 )
         {
            flag = 1;
            ( *last_node ).next = (*node).next;
            move_all_cursors_forth_after_node_removal( current, node );
            remove_node_from_sequence( current, node );
            node_dispose( &node );
            (*current).count = (*current).count - 1;
         }

         if ( flag == 0 )
         {
            last_node = node;
            node = (*node).next;
         }
      }
   }

   if ( (*current).count == 0 )
   {
      (*current).first_in_sequence = NULL;
      (*current).last_in_sequence = NULL;
   }

   return;
}

/**
   HSet_remove
*/

void
HSet_remove( Prefix )( HSet_type( Prefix ) *current, Item item )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has item", has( current, item ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = has( current, item ) ? (*current).count - 1 : (*current).count; );

   remove( current, item );

   POSTCONDITION( "count decremented", (*current).count == count_pc );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HSet_remove_and_dispose
*/

void
HSet_remove_and_dispose( Prefix )( HSet_type( Prefix ) *current, Item item )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "has item", has( current, item ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = has( current, item ) ? (*current).count - 1 : (*current).count; );

   int32_t hash_code = HASH_FUNCTION( item );
   int32_t i = hash_code % (*current).bucket_count;
   int32_t flag = 0;

   // get node for search
   node_t *last_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*current).bucket[i];

   // see if first node in bucket matches
   if ( DEEP_EQUAL_FUNCTION( (*node).item, item ) == 1 )
   {
      // remove first node
      (*current).bucket[i] = (*node).next;
      DEEP_DISPOSE_FUNCTION( (*node).item );
      move_all_cursors_forth_after_node_removal( current, node );
      remove_node_from_sequence( current, node );
      node_dispose( &node );
      (*current).count = (*current).count - 1;
   }
   else
   {
      last_node = node;
      node = (*node).next;

      // if not, look through rest of nodes in bucket for match to item
      while ( ( node != NULL ) && ( flag == 0 ) )
      {
         if ( DEEP_EQUAL_FUNCTION( (*node).item, item ) == 1 )
         {
            flag = 1;
            ( *last_node ).next = (*node).next;
            DEEP_DISPOSE_FUNCTION( (*node).item );
            move_all_cursors_forth_after_node_removal( current, node );
            remove_node_from_sequence( current, node );
            node_dispose( &node );
            (*current).count = (*current).count - 1;
         }

         if ( flag == 0 )
         {
            last_node = node;
            node = (*node).next;
         }
      }
   }

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
   HSet_wipe_out
*/

void
HSet_wipe_out( Prefix )( HSet_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // delete current sequence items
   node_t *node1 = (*current).first_in_sequence;
   node_t *next = NULL;
   while( node1 != NULL )
   {
      next = (*node1).next_in_sequence;
      node_dispose( &node1 );
      node1 = next;
   }

   // delete cursors
   HSet_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   HSet_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // set first cursor's next cursor to NULL
   ( *(*current).first_cursor ).next_cursor = NULL;

   // and set last cursor to first cursor
   (*current).last_cursor = (*current).first_cursor;

   // clear out buckets
   memset( (*current).bucket, 0, (*current).bucket_count * sizeof( node_t * ) );

   // set all cursors off
   move_all_cursors_off( current );

   // set count to zero
   (*current).count = 0;

   // set sequence pointers
   (*current).first_in_sequence = NULL;
   (*current).last_in_sequence = NULL;

   POSTCONDITION( "is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HSet_wipe_out_and_dispose
*/

void
HSet_wipe_out_and_dispose( Prefix )( HSet_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // delete current sequence items
   node_t *node1 = (*current).first_in_sequence;
   node_t *next = NULL;

   while( node1 != NULL )
   {
      next = (*node1).next_in_sequence;
      DEEP_DISPOSE_FUNCTION( (*node1).item );
      node_dispose( &node1 );
      node1 = next;
   }

   // delete cursors
   HSet_cursor_type( Prefix ) *cursor = ( *(*current).first_cursor ).next_cursor;
   HSet_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // set first cursor's next cursor to NULL
   ( *(*current).first_cursor ).next_cursor = NULL;

   // and set last cursor to first cursor
   (*current).last_cursor = (*current).first_cursor;

   // clear out buckets
   memset( (*current).bucket, 0, (*current).bucket_count * sizeof( node_t * ) );

   // set all cursors off
   move_all_cursors_off( current );

   // set count to zero
   (*current).count = 0;

   // set sequence pointers
   (*current).first_in_sequence = NULL;
   (*current).last_in_sequence = NULL;

   POSTCONDITION( "is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HSet_set_bucket_count
*/

void
HSet_set_bucket_count( Prefix )( HSet_type( Prefix ) *current, int32_t new_bucket_count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
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
      hash_code = HASH_FUNCTION( (*node).item );
      i = hash_code % (*current).bucket_count;
      (*node).next = (*current).bucket[i];
      (*current).bucket[i] = node;
   }

   POSTCONDITION( "bucket count set", (*current).bucket_count == new_bucket_count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HSet_intersect
*/

void
HSet_intersect( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock other
   LOCK( (*other).mutex );

   node_t *node = (*current).first_in_sequence;
   node_t *next = NULL;

   // walk through nodes of current, removing items not also in other
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( other, (*node).item ) == 0 )
      {
         remove( current, (*node).item );
      }
      node = next;
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HSet_intersection
*/

HSet_type( Prefix ) *
HSet_intersection( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*other).mutex );
   INVARIANT( current );

   HSet_type( Prefix ) *result = HSet_clone( Prefix )( current );

   node_t *node = (*result).first_in_sequence;
   node_t *next = NULL;

   // walk through nodes of current, removing items not also in other
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( other, (*node).item ) == 0 )
      {
         remove( result, (*node).item );
      }
      node = next;
   }

   POSTCONDITION( "current count ok", ( (*result).count <= (*current).count ) && ( (*result).count <= (*other).count ) );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return result;
}

/**
   HSet_subtract
*/

void
HSet_subtract( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   // lock other
   LOCK( (*other).mutex );

   node_t *node = (*current).first_in_sequence;
   node_t *next = NULL;

   // walk through nodes of current, removing items also in other
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( other, (*node).item ) == 1 )
      {
         remove( current, (*node).item );
      }
      node = next;
   }

   POSTCONDITION( "current count ok", ( ( (*current).count <= count_pc ) && ( (*current).count >= count_pc - (*other).count ) ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HSet_subtraction
*/

HSet_type( Prefix ) *
HSet_subtraction( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*other).mutex );
   INVARIANT( current );

   HSet_type( Prefix ) *result = HSet_clone( Prefix )( current );

   node_t *node = (*result).first_in_sequence;
   node_t *next = NULL;

   // walk through nodes of current, removing items also in other
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( other, (*node).item ) == 1 )
      {
         remove( result, (*node).item );
      }
      node = next;
   }

   POSTCONDITION( "result count ok", ( ( (*result).count <= (*current).count ) && ( (*result).count >= (*current).count - (*other).count ) ) );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return result;
}

/**
   HSet_symdif
*/

void
HSet_symdif( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   // lock other
   LOCK( (*other).mutex );

   node_t *node = NULL;
   node_t *next = NULL;
   node_t *to_be_added = NULL;
   node_t *node1 = NULL;

   node = (*other).first_in_sequence;
   next = NULL;

   // walk through nodes of other, making list of items to add to current
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( current, (*node).item ) == 0 )
      {
         // make a new node to hold item, save as stack in to_be_added
         if ( to_be_added == NULL )
         {
            node1 = node_make();
            (*node1).item = (*node).item;
            to_be_added = node1;
         }
         else
         {
            node1 = node_make();
            (*node1).item = (*node).item;
            (*node1).next = to_be_added;
            to_be_added = node1;
         }
      }
      node = next;
   }

   node = (*current).first_in_sequence;

   // walk through nodes of current, removing items also in other
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( other, (*node).item ) == 1 )
      {
         remove( current, (*node).item );
      }
      node = next;
   }


   // add items to current, disposing of temporary nodes
   while( to_be_added != NULL )
   {
      put( current, ( *to_be_added ).item );
      next = to_be_added;
      to_be_added = ( *to_be_added ).next;
      node_dispose( &next );
   }

   POSTCONDITION( "current count ok", ( ( (*current).count <= count_pc + (*other).count ) && ( (*current).count >= count_pc - (*other).count ) ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HSet_symdifference
*/

HSet_type( Prefix ) *
HSet_symdifference( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*other).mutex );
   INVARIANT( current );

   HSet_type( Prefix ) *result = HSet_clone( Prefix )( current );

   node_t *node = NULL;
   node_t *next = NULL;
   node_t *to_be_added = NULL;
   node_t *node1 = NULL;

   node = (*other).first_in_sequence;
   next = NULL;

   // walk through nodes of other, making list of items to add to result
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( result, (*node).item ) == 0 )
      {
         // make a new node to hold item, save as stack in to_be_added
         if ( to_be_added == NULL )
         {
            node1 = node_make();
            (*node1).item = (*node).item;
            to_be_added = node1;
         }
         else
         {
            node1 = node_make();
            (*node1).item = (*node).item;
            (*node1).next = to_be_added;
            to_be_added = node1;
         }
      }
      node = next;
   }

   node = (*result).first_in_sequence;

   // walk through nodes of result, removing items also in other
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( other, (*node).item ) == 1 )
      {
         remove( result, (*node).item );
      }
      node = next;
   }

   // add items to result, disposing of temporary nodes
   while( to_be_added != NULL )
   {
      put( result, ( *to_be_added ).item );
      next = to_be_added;
      to_be_added = ( *to_be_added ).next;
      node_dispose( &next );
   }

   POSTCONDITION( "result count ok", ( ( (*result).count <= (*current).count + (*other).count ) && ( (*result).count >= (*current).count - (*other).count ) ) );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return result;
}

/**
   HSet_merge
*/

void
HSet_merge( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   // lock other
   LOCK( (*other).mutex );

   node_t *node = (*other).first_in_sequence;
   node_t *next = NULL;
   node_t *to_be_added = NULL;
   node_t *node1 = NULL;

   // walk through nodes of other, making list of items to add to current
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( current, (*node).item ) == 0 )
      {
         // make a new node to hold item, save as stack in to_be_added
         if ( to_be_added == NULL )
         {
            node1 = node_make();
            (*node1).item = (*node).item;
            to_be_added = node1;
         }
         else
         {
            node1 = node_make();
            (*node1).item = (*node).item;
            (*node1).next = to_be_added;
            to_be_added = node1;
         }
      }
      node = next;
   }

   // add items to current, disposing of temporary nodes
   while( to_be_added != NULL )
   {
      put( current, ( *to_be_added ).item );
      next = to_be_added;
      to_be_added = ( *to_be_added ).next;
      node_dispose( &next );
   }

   POSTCONDITION( "current count ok", ( ( (*current).count <= count_pc + (*other).count ) && ( (*current).count >= count_pc ) ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   HSet_union
*/

HSet_type( Prefix ) *
HSet_union( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*other).mutex );
   INVARIANT( current );

   HSet_type( Prefix ) *result = HSet_clone( Prefix )( current );

   node_t *node = (*other).first_in_sequence;
   node_t *next = NULL;
   node_t *to_be_added = NULL;
   node_t *node1 = NULL;

   // walk through nodes of other, making list of items to add to result
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( result, (*node).item ) == 0 )
      {
         // make a new node to hold item, save as stack in to_be_added
         if ( to_be_added == NULL )
         {
            node1 = node_make();
            (*node1).item = (*node).item;
            to_be_added = node1;
         }
         else
         {
            node1 = node_make();
            (*node1).item = (*node).item;
            (*node1).next = to_be_added;
            to_be_added = node1;
         }
      }
      node = next;
   }

   // add items to result, disposing of temporary nodes
   while( to_be_added != NULL )
   {
      put( result, ( *to_be_added ).item );
      next = to_be_added;
      to_be_added = ( *to_be_added ).next;
      node_dispose( &next );
   }

   POSTCONDITION( "result count ok", ( ( (*result).count >= (*current).count ) && ( (*result).count >= (*other).count ) && ( (*result).count <= (*current).count + (*other).count ) ) );

   INVARIANT( current );
   UNLOCK( (*other).mutex );

   return result;
}

/**
   HSet_is_disjoint
*/

int32_t
HSet_is_disjoint( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock other
   LOCK( (*other).mutex );

   int32_t result = 1;
   node_t *node = (*current).first_in_sequence;
   node_t *next = NULL;

   // walk through nodes of current. if an item is also in other, result is 0
   while ( ( node != NULL ) && ( result == 1 ) )
   {
      next = (*node).next_in_sequence;
      if ( has( other, (*node).item ) == 1 )
      {
         result = 0;
      }
      node = next;
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   HSet_is_subset
*/

int32_t
HSet_is_subset( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock other
   LOCK( (*other).mutex );

   int32_t result = 1;
   node_t *node = (*current).first_in_sequence;
   node_t *next = NULL;

   // walk through nodes of current. if an item is not in other, result is 0
   while ( ( node != NULL ) && ( result == 1 ) )
   {
      next = (*node).next_in_sequence;
      if ( has( other, (*node).item ) == 0 )
      {
         result = 0;
      }
      node = next;
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   HSet_is_superset
*/

int32_t
HSet_is_superset( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == HSET_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == HSET_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock other
   LOCK( (*other).mutex );

   int32_t result = 1;
   node_t *node = (*other).first_in_sequence;
   node_t *next = NULL;

   // walk through nodes of other. if an item is not in current, result is 0
   while ( ( node != NULL ) && ( result == 1 ) )
   {
      next = (*node).next_in_sequence;
      if ( has( current, (*node).item ) == 0 )
      {
         result = 0;
      }
      node = next;
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   HSet_equal_items
*/

int32_t
HSet_equal_items( Prefix )( Item item, Item other )
{
   return DEEP_EQUAL_FUNCTION( item, other );
}


#ifdef __cplusplus
}
#endif

/* End of file */

