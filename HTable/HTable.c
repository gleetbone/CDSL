/**
 @file HTable.c
 @author Greg Lee
 @version 1.0.0
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

#ifdef PROTOCOLS_ENABLED   
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Clonable.ph"
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

#define HTABLE_TYPE 0xA5000301

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

   int32_t type;
   int32_t key_type;
   int32_t item_type;
   
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
   has

   Return 1 if htable has an item for key, 0 if not

   @param htable HTable_t instance
   @param key the key to query for
*/

static
int32_t
has( HTable_type( Prefix ) *htable, Key key )
{
   int32_t hash_code = HASH_FUNCTION( key );
   int32_t i = hash_code % (*htable).bucket_count;

   // get first of bucket's nodes
   node_t *node = (*htable).bucket[i];

   // look through nodes in bucket for match to key
   while ( node != NULL )
   {
      if ( EQUALITY_FUNCTION( (*node).key, key ) == 1 )
      {
         return 1;
      }
      node = (*node).next;
   }

   return 0;
}

/**
   HTable_put
*/

static
void
put( HTable_type( Prefix ) *htable, Type value, Key key )
{
   int32_t hash_code = HASH_FUNCTION( key );
   int32_t i = hash_code % (*htable).bucket_count;

   // get node for new value
   node_t *new_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*htable).bucket[i];

   // see if node with this key already exists
   int32_t flag = 0;

   // look through nodes in bucket for match to key
   while ( ( node != NULL ) && ( flag == 0 ) )
   {
      if ( EQUALITY_FUNCTION( (*node).key, key ) == 1 )
      {
         flag = 1;
         new_node = node;
      }
      node = (*node).next;
   }

   // if node exists in htable, replace value with new value
   if ( new_node != NULL )
   {
      (*new_node).value = value;
      (*new_node).key = key;
   }
   else
   {
      // else get new node and put new value at head of bucket
      new_node = node_make();
      (*new_node).value = value;
      (*new_node).key = key;
      (*new_node).next = (*htable).bucket[i];
      (*htable).bucket[i] = new_node;

      // place new node in node sequence
      if ( (*htable).last_in_sequence == NULL )
      {
         (*htable).first_in_sequence = new_node;
         (*htable).last_in_sequence = new_node;
      }
      else
      {
         (*(*htable).last_in_sequence).next_in_sequence = new_node;
         (*htable).last_in_sequence = new_node;
      }

      (*htable).count = (*htable).count + 1;
   }

   return;
}

/**
   keys_as_array

*/

static
Key *
keys_as_array( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );

   Key *result = NULL;

   result = ( Key * ) calloc( (*htable).count+ 1, sizeof( Key ) );

   int32_t i = 0;
   node_t *node = (*htable).first_in_sequence;

   for( i=0; i<(*htable).count; i++ )
   {
      result[i] = (*node).key;
      node = (*node).next_in_sequence;
   }

   return result;
}

/**
   items_as_array

*/

static
Type *
items_as_array( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );

   Type *result = NULL;
   result = ( Type * ) calloc( (*htable).count + 1, sizeof( Type ) );

   int32_t i = 0;
   node_t *node = (*htable).first_in_sequence;

   for( i=0; i<(*htable).count; i++ )
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

   @param htable HTable_t instance
   @param node the just removed node
*/
static
void
move_all_cursors_forth_after_node_removal
(
   HTable_type( Prefix ) *htable,
   node_t *node
)
{
   HTable_cursor_type( Prefix ) *cursor = NULL;

   for (  cursor = (*htable).first_cursor;
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

   @param htable HTable_t instance
   @param node the to be removed node
*/
static
void
remove_node_from_sequence
(
   HTable_type( Prefix ) *htable,
   node_t *node
)
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "node not null", node != NULL );

   node_t *node1 = (*htable).first_in_sequence;
   node_t *prev = (*(*htable).first_in_sequence).next_in_sequence;

   if ( node1 == node )
   {
      (*htable).first_in_sequence = (*node).next_in_sequence;
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
            if ( node1 == (*htable).last_in_sequence )
            {
               (*htable).last_in_sequence = prev;
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
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
is_empty_implies_first_last_null( HTable_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).count == 0 )
   {
      result
         = (
               ( (*p).first_in_sequence == NULL )
               &&
               ( (*p).last_in_sequence  == NULL )
           );
   }

   return result;
}

static
int32_t
nonnegative_count( HTable_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
last_in_sequence_ok( HTable_type( Prefix ) *p )
{
   int32_t result = 0;

   node_t *node = (*p).first_in_sequence;
   node_t *node1 = NULL;

   while( node != NULL )
   {
      node1 = node;
      node = (*node).next_in_sequence;
   }

   result = ( node1 == (*p).last_in_sequence );

   return result;
}

static
int32_t
valid_sequence_count( HTable_type( Prefix ) *p )
{
   int32_t result = 1;
   int32_t n = 0;

   node_t *node = (*p).first_in_sequence;

   while( node != NULL )
   {
      n = n + 1;
      node = (*node).next_in_sequence;
   }

   result = ( n == (*p).count );

   return result;
}

static
int32_t
valid_bucket_count( HTable_type( Prefix ) *p )
{
   int32_t i = 0;
   int32_t result = 1;
   node_t *node = NULL;
   int32_t n = 0;

   for ( i=0; i < (*p).bucket_count; i ++ )
   {
      node = (*p).bucket[i];

      while( node != NULL )
      {
         n = n + 1;
         node = (*node).next;
      }
   }

   result = ( n == (*p).count );

   return result;
}

static
int32_t
first_cursor_not_null( HTable_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).first_cursor != NULL );

   return result;
}

static
int32_t
cursors_htable_ok( HTable_type( Prefix ) *p )
{
   int32_t result = 1;

   HTable_cursor_type( Prefix ) *cursor = (*p).first_cursor;

   while ( ( cursor != NULL ) && ( result == 1 ) )
   {
      result = ( (*cursor).htable == p );
      cursor = (*cursor).next_cursor;
   }

   return result;
}

static
int32_t
last_cursor_next_null( HTable_type( Prefix ) *p )
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
last_cursor_null_if_one_cursor( HTable_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*(*p).first_cursor).next_cursor == NULL )
   {
      result = ( (*p).last_cursor == NULL );
   }

   return result;
}

static
void invariant( HTable_type( Prefix ) *p )
{
   assert(((void) "empty implies first and last null", is_empty_implies_first_last_null( p ) ));
   assert(((void) "nonnegative count", nonnegative_count( p ) ));
   assert(((void) "last in sequence OK", last_in_sequence_ok( p ) ));
   assert(((void) "valid sequence count", valid_sequence_count( p ) ));
   assert(((void) "valid bucket count", valid_bucket_count( p ) ));
   assert(((void) "first cursor not null", first_cursor_not_null( p ) ));
   assert(((void) "last cursor next null", last_cursor_next_null( p ) ));
   assert(((void) "last cursor null if one cursor", last_cursor_null_if_one_cursor( p ) ) );
   assert(((void) "cursors htable OK", cursors_htable_ok( p ) ));
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
   HTable_dispose( Prefix ),
   HTable_dispose_with_contents( Prefix ),
   HTable_make_from( Prefix ),
   HTable_make_duplicate_from( Prefix )
};

static
void *
p_iterable_kv_table[P_ITERABLE_KV_FUNCTION_COUNT]
=
{
   HTable_dispose( Prefix ),
   HTable_dispose_with_contents( Prefix ),
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
   HTable_type( Prefix ) * htable
      = ( HTable_type( Prefix ) * ) calloc( 1, sizeof( HTable_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( htable );

   // set type codes
   (*htable).type = HTABLE_TYPE;
   (*htable).key_type = Key_Code;
   (*htable).item_type = Type_Code;
   
   (*htable).count = 0;

   // allocate bucket array, default size
   (*htable).bucket = ( node_t ** ) calloc( DEFAULT_BUCKET_SIZE, sizeof( node_t * ) );

   (*htable).bucket_count = DEFAULT_BUCKET_SIZE;

   // set built-in cursor
   // allocate cursor struct
   HTable_cursor_type( Prefix ) *cursor
      =  ( HTable_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HTable_cursor_type( Prefix ) ) );

   // set htable
   (*cursor).htable = htable;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set htable built-in cursor
   (*htable).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*htable).mutex );

   INVARIANT( htable );

   return htable;
}

/**
   HTable_make_n
*/

HTable_type( Prefix ) *
HTable_make_n( Prefix )( int32_t bucket_count )
{
   PRECONDITION( "bucket count ok", bucket_count > 0 );

   // allocate htable struct
   HTable_type( Prefix ) * htable
      = ( HTable_type( Prefix ) * ) calloc( 1, sizeof( HTable_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( htable );

   // set type codes
   (*htable).type = HTABLE_TYPE;
   (*htable).key_type = Key_Code;
   (*htable).item_type = Type_Code;
   
   (*htable).count = 0;

   // allocate bucket array
   (*htable).bucket = ( node_t ** ) calloc( bucket_count, sizeof( node_t * ) );

   (*htable).bucket_count = bucket_count;

   // set built-in cursor
   // allocate cursor struct
   HTable_cursor_type( Prefix ) *cursor
      =  ( HTable_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HTable_cursor_type( Prefix ) ) );

   // set htable
   (*cursor).htable = htable;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set htable built-in cursor
   (*htable).first_cursor = cursor;


   MULTITHREAD_MUTEX_INIT( (*htable).mutex );

   INVARIANT( htable );
   POSTCONDITION( "bucket count set", (*htable).bucket_count == bucket_count );

   return htable;
}

/**
   HTable_make_from
*/

HTable_type( Prefix ) *
HTable_make_from( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );

   // get input
   LOCK( (*htable).mutex );
   Key *keys = keys_as_array( htable );
   Type *items = items_as_array( htable );
   int32_t count = (*htable).count;
   UNLOCK( (*htable).mutex );

   // allocate htable struct
   HTable_type( Prefix ) * result
      = ( HTable_type( Prefix ) * ) calloc( 1, sizeof( HTable_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = HTABLE_TYPE;
   (*result).key_type = Key_Code;
   (*result).item_type = Type_Code;
   
   (*result).count = 0;

   // allocate bucket array
   (*result).bucket = ( node_t ** ) calloc( (*htable).bucket_count, sizeof( node_t * ) );

   (*result).bucket_count = (*htable).bucket_count;

   // set built-in cursor
   // allocate cursor struct
   HTable_cursor_type( Prefix ) *cursor
      =  ( HTable_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HTable_cursor_type( Prefix ) ) );

   // set htable
   (*cursor).htable = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set htable built-in cursor
   (*result).first_cursor = cursor;

   // put key-values from htable into result
   int32_t i = 0;
   for ( i=0; i < count; i++ )
   {
      put( result, items[i], keys[i] );
   }

   MULTITHREAD_MUTEX_INIT( (*htable).mutex );

   free( keys );
   free( items );

   INVARIANT( result );

   return result;
}

/**
   HTable_make_duplicate_from
*/

HTable_type( Prefix ) *
HTable_make_duplicate_from( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );

   // get input
   LOCK( (*htable).mutex );
   Key *keys = keys_as_array( htable );
   Type *items = items_as_array( htable );
   int32_t count = (*htable).count;
   UNLOCK( (*htable).mutex );

   // allocate htable struct
   HTable_type( Prefix ) * result
      = ( HTable_type( Prefix ) * ) calloc( 1, sizeof( HTable_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = HTABLE_TYPE;
   (*result).key_type = Key_Code;
   (*result).item_type = Type_Code;
   
   (*result).count = 0;

   // allocate bucket array
   (*result).bucket = ( node_t ** ) calloc( (*htable).bucket_count, sizeof( node_t * ) );

   (*result).bucket_count = (*htable).bucket_count;

   // set built-in cursor
   // allocate cursor struct
   HTable_cursor_type( Prefix ) *cursor
      =  ( HTable_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HTable_cursor_type( Prefix ) ) );

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
      k = KEY_DUPLICATE_FUNCTION( keys[i] );
      v = VALUE_DUPLICATE_FUNCTION( items[i] );
      put( result, v, k );
   }

   MULTITHREAD_MUTEX_INIT( (*htable).mutex );

   free( keys );
   free( items );
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
   HTable_type( Prefix ) * result = HTable_make( Prefix )();

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = HTABLE_TYPE;
   (*result).key_type = Key_Code;
   (*result).item_type = Type_Code;
   
   // put key-values from htable into result
   int32_t i = 0;
   for ( i=0; i < count; i++ )
   {
      put( result, value_array[i], key_array[i] );
   }

   INVARIANT( result );

   return result;
}

/**
   HTable_cursor_make
*/

HTable_cursor_type( Prefix ) *
HTable_cursor_make( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   // allocate cursor struct
   HTable_cursor_type( Prefix ) *cursor
      =  ( HTable_cursor_type( Prefix ) * )
         calloc( 1, sizeof( HTable_cursor_type( Prefix ) ) );

   // set htable
   (*cursor).htable = htable;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // place cursor reference into htable structure
   if ( (*htable).last_cursor == NULL )
   {
      // set second cursor for htable
      (*(*htable).first_cursor).next_cursor = cursor;
      (*htable).last_cursor = cursor;
   }
   else
   {
      // set additional cursor for htable
      // (*htable).last_cursor holds last cursor allocated
      (*(*htable).last_cursor).next_cursor = cursor;
      (*htable).last_cursor = cursor;
   }

   MULTITHREAD_MUTEX_INIT( (*htable).mutex );

   INVARIANT( htable );
   POSTCONDITION( "new cursor is last cursor", (*htable).last_cursor == cursor );
   UNLOCK( (*htable).mutex );

   return cursor;
}

/**
   HTable_dispose
*/

void
HTable_dispose( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   // delete htable sequence items
   node_t *item = (*htable).first_in_sequence;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next_in_sequence;
      node_dispose( item );
      item = next;
   }

   // delete cursors
   HTable_cursor_type( Prefix ) *cursor = (*htable).first_cursor;
   HTable_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // delete bucket array
   free( (*htable).bucket );

   MULTITHREAD_MUTEX_DESTROY( (*htable).mutex );

   // delete htable struct
   free( htable );

   return;
}

/**
   HTable_dispose_with_contents
*/

void
HTable_dispose_with_contents( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   // delete htable sequence items
   node_t *item = (*htable).first_in_sequence;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next_in_sequence;
      KEY_DISPOSE_FUNCTION( (*item).key );
      VALUE_DISPOSE_FUNCTION( (*item).value );
      node_dispose( item );
      item = next;
   }

   // delete cursors
   HTable_cursor_type( Prefix ) *cursor = (*htable).first_cursor;
   HTable_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // delete bucket array
   free( (*htable).bucket );

   MULTITHREAD_MUTEX_DESTROY( (*htable).mutex );

   // delete htable struct
   free( htable );

   return;
}

/**
   HTable_cursor_dispose
*/

void
HTable_cursor_dispose( Prefix )( HTable_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).htable).type == HTABLE_TYPE ) && ( (*(*cursor).htable).key_type == Key_Code ) && ( (*(*cursor).htable).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).htable).mutex );
   INVARIANT( (*cursor).htable );

   HTable_type( Prefix ) *htable = (*cursor).htable;

   HTable_cursor_type( Prefix ) *c1 = NULL;
   HTable_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from htable structure
   c1 = (*(*cursor).htable).first_cursor;
   c2 = (*c1).next_cursor;

   // search through the cursors
   while ( ( c2 != NULL) && ( flag == 0 ) )
   {
      if ( c2 == cursor )
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
   c1 = (*(*cursor).htable).first_cursor;
   while ( c1 != NULL )
   {
      c2 = c1;
      c1 = (*c1).next_cursor;
   }
   (*(*cursor).htable).last_cursor = c2;

   // only one cursor, last_cursor is NULL
   if ( c2 == (*(*cursor).htable).first_cursor )
   {
      (*(*cursor).htable).last_cursor = NULL;
   }
   
   // delete cursor struct
   free( cursor );

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return;
}

/**
   HTable_keys_as_array

*/

Key *
HTable_keys_as_array( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );

   Key *result = keys_as_array( htable );

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return result;
}

/**
   HTable_values_as_array

*/

Type *
HTable_values_as_array( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );

   Type *result = items_as_array( htable );

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return result;
}

/**
   HTable_cursor_item_at
*/

Type
HTable_cursor_item_at( Prefix )( HTable_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).htable).type == HTABLE_TYPE ) && ( (*(*cursor).htable).key_type == Key_Code ) && ( (*(*cursor).htable).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).htable).mutex );
   INVARIANT( (*cursor).htable );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Type value = (*(*cursor).item).value;

   INVARIANT( (*cursor).htable );
   UNLOCK( (*(*cursor).htable).mutex );
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
   PRECONDITION( "cursor list type ok", ( (*(*cursor).htable).type == HTABLE_TYPE ) && ( (*(*cursor).htable).key_type == Key_Code ) && ( (*(*cursor).htable).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).htable).mutex );
   INVARIANT( (*cursor).htable );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Key key = (*(*cursor).item).key;

   INVARIANT( (*cursor).htable );
   UNLOCK( (*(*cursor).htable).mutex );
   UNLOCK( (*cursor).mutex );

   return key;
}


/**
   HTable_item_at
*/

Type
HTable_item_at( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );
   PRECONDITION( "not off", (*(*htable).first_cursor).item != NULL );

   HTable_cursor_type( Prefix ) *cursor = (*htable).first_cursor;

   Type value = (*(*cursor).item).value;

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return value;
}

/**
   HTable_key_at
*/

Key
HTable_key_at( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );
   PRECONDITION( "not off", (*(*htable).first_cursor).item != NULL );

   HTable_cursor_type( Prefix ) *cursor = (*htable).first_cursor;

   Key key = (*(*cursor).item).key;

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return key;
}


/**
   HTable_item_at_index
*/

Type
HTable_item_at_index( Prefix )( HTable_type( Prefix ) *htable, int32_t index )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*htable).count ) );

   int32_t i = 0;
   node_t *node = (*htable).first_in_sequence;

   for( i = 1; i <= index; i ++ )
   {
      node = (*node).next_in_sequence;
   }

   Type value = (*node).value;

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return value;
}

/**
   HTable_key_at_index
*/

Key
HTable_key_at_index( Prefix )( HTable_type( Prefix ) *htable, int32_t index )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*htable).count ) );

   int32_t i = 0;
   node_t *node = (*htable).first_in_sequence;

   for( i = 1; i <= index; i ++ )
   {
      node = (*node).next_in_sequence;
   }

   Key key = (*node).key;

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return key;
}


/**
   HTable_item
*/

Type
HTable_item( Prefix )( HTable_type( Prefix ) *htable, Key key )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );
   PRECONDITION( "has key", has( htable, key ) );

   int32_t hash_code = HASH_FUNCTION( key );
   int32_t i = hash_code % (*htable).bucket_count;

   // get first of bucket's nodes
   node_t *node = (*htable).bucket[i];

   Type value = (*(*htable).first_in_sequence).value;

   // look through nodes in bucket for match to key
   while ( node != NULL )
   {
      if ( EQUALITY_FUNCTION( (*node).key, key ) == 1 )
      {
         value = (*node).value;
         break;
      }
      node = (*node).next;
   }

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return value;
}

/**
   HTable_count
*/

int32_t
HTable_count( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   int32_t count = (*htable).count;

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return count;
}

/**
   HTable_bucket_count
*/

int32_t
HTable_bucket_count( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   int32_t count = (*htable).bucket_count;

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return count;
}

/**
   HTable_off
*/

int32_t
HTable_off( Prefix)( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   int32_t result = ( (*(*htable).first_cursor).item == NULL );

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return result;
}

/**
   HTable_cursor_off
*/

int32_t
HTable_cursor_off( Prefix )( HTable_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).htable).type == HTABLE_TYPE ) && ( (*(*cursor).htable).key_type == Key_Code ) && ( (*(*cursor).htable).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );

   int32_t result = ( (*cursor).item == NULL );

   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   HTable_is_empty
*/

int32_t
HTable_is_empty( Prefix)( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   int32_t result = ( (*htable).count ==  0 );

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return result;
}

/**
   HTable_has
*/

int32_t
HTable_has( Prefix )( HTable_type( Prefix ) *htable, Key key )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   int32_t result = has( htable, key );

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return result;
}

/**
   HTable_cursor_forth
*/
void
HTable_cursor_forth( Prefix )( HTable_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).htable).type == HTABLE_TYPE ) && ( (*(*cursor).htable).key_type == Key_Code ) && ( (*(*cursor).htable).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );

   if ( (*cursor).item != NULL )
   {
      (*cursor).item = (*(*cursor).item).next_in_sequence;
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
   PRECONDITION( "cursor list type ok", ( (*(*cursor).htable).type == HTABLE_TYPE ) && ( (*(*cursor).htable).key_type == Key_Code ) && ( (*(*cursor).htable).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).htable).mutex );
   INVARIANT( (*cursor).htable );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*(*cursor).htable).count ) ) );

   int32_t i = 0;
   (*cursor).item = (*(*cursor).htable).first_in_sequence;

   for( i = 1; ( i <= index ) && ( (*cursor).item != NULL ); i++ )
   {
      if ( (*cursor).item != NULL )
      {
         (*cursor).item = (*(*cursor).item).next_in_sequence;
      }
   }

   INVARIANT( (*cursor).htable );
   UNLOCK( (*(*cursor).htable).mutex );
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
   PRECONDITION( "cursor list type ok", ( (*(*cursor).htable).type == HTABLE_TYPE ) && ( (*(*cursor).htable).key_type == Key_Code ) && ( (*(*cursor).htable).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).htable).mutex );
   INVARIANT( (*cursor).htable );

   int32_t result = 0;
   int32_t flag = 0;
   node_t *node = (*(*cursor).htable).first_in_sequence;
   node_t *target = (*cursor).item;

   if ( (*(*cursor).htable).count > 0 )
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
   UNLOCK( (*(*cursor).htable).mutex );
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
   PRECONDITION( "cursor list type ok", ( (*(*cursor).htable).type == HTABLE_TYPE ) && ( (*(*cursor).htable).key_type == Key_Code ) && ( (*(*cursor).htable).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).htable).mutex );
   INVARIANT( (*cursor).htable );

   (*cursor).item = (*(*cursor).htable).first_in_sequence;

   INVARIANT( (*cursor).htable );
   UNLOCK( (*(*cursor).htable).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   HTable_forth
*/
void
HTable_forth( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );
   PRECONDITION( "not off", (*(*htable).first_cursor).item != NULL );

   if ( (*(*htable).first_cursor).item != NULL )
   {
      (*(*htable).first_cursor).item = (*(*(*htable).first_cursor).item).next_in_sequence;
   }

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return;
}

/**
   HTable_go
*/
void
HTable_go( Prefix )( HTable_type( Prefix ) *htable, int32_t index )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*htable).count ) ) );

   int32_t i = 0;
   (*(*htable).first_cursor).item = (*htable).first_in_sequence;

   for( i = 1; ( i <= index ) && ( (*(*htable).first_cursor).item != NULL ); i++ )
   {
      if ( (*(*htable).first_cursor).item != NULL )
      {
         (*(*htable).first_cursor).item = (*(*(*htable).first_cursor).item).next;
      }
   }

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return;
}

/**
   HTable_index
*/

int32_t
HTable_index( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   int32_t result = 0;
   int32_t flag = 0;
   node_t *node = (*htable).first_in_sequence;
   node_t *target = (*(*htable).first_cursor).item;

   if ( (*htable).count > 0 )
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
   
   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return result;
}

/**
   HTable_start
*/

void
HTable_start( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   (*(*htable).first_cursor).item = (*htable).first_in_sequence;

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return;
}

/**
   HTable_put
*/

void
HTable_put( Prefix )( HTable_type( Prefix ) *htable, Type value, Key key )
{
   PRECONDITION( "htable not null", htable != NULL );   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );

   LOCK( (*htable).mutex );
   INVARIANT( htable );

   put( htable, value, key );

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return;
}

/**
   HTable_replace
*/

void
HTable_replace( Prefix )( HTable_type( Prefix ) *htable, Type value, Key key )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   int32_t hash_code = HASH_FUNCTION( key );
   int32_t i = hash_code % (*htable).bucket_count;

   // get node for new value
   node_t *new_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*htable).bucket[i];

   // see if node with this key already exists
   int32_t flag = 0;

   // look through nodes in bucket for match to key
   while ( ( node != NULL ) && ( flag == 0 ) )
   {
      if ( EQUALITY_FUNCTION( (*node).key, key ) == 1 )
      {
         flag = 1;
         new_node = node;
      }
      node = (*node).next;
   }

   // if node exists in htable, replace value with new value
   if ( new_node != NULL )
   {
      (*new_node).value = value;
      (*new_node).key = key;
   }
   else
   {
      // else get new node and put new value at head of bucket
      new_node = node_make();
      (*new_node).value = value;
      (*new_node).key = key;
      (*new_node).next = (*htable).bucket[i];
      (*new_node).next_in_sequence = NULL;
      
      // put in sequence
      if ( (*htable).last_in_sequence == NULL )
      {
         (*htable).first_in_sequence = new_node;
         (*htable).last_in_sequence = new_node;
      }
      else
      {
         (*(*htable).last_in_sequence).next_in_sequence = new_node;
         (*htable).last_in_sequence = new_node;
      }
      
      // put in bucket
      (*htable).bucket[i] = new_node;
      (*htable).count = (*htable).count + 1;
   }

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return;
}

/**
   HTable_replace_and_dispose
*/

void
HTable_replace_and_dispose( Prefix )( HTable_type( Prefix ) *htable, Type value, Key key )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   int32_t hash_code = HASH_FUNCTION( key );
   int32_t i = hash_code % (*htable).bucket_count;

   // get node for new value
   node_t *new_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*htable).bucket[i];

   // see if node with this key already exists
   int32_t flag = 0;

   // look through nodes in bucket for match to key
   while ( ( node != NULL ) && ( flag == 0 ) )
   {
      if ( EQUALITY_FUNCTION( (*node).key, key ) == 1 )
      {
         flag = 1;
         new_node = node;
      }
      node = (*node).next;
   }

   // if node exists in htable, replace value with new value
   if ( new_node != NULL )
   {
      VALUE_DISPOSE_FUNCTION( (*new_node).value );
      (*new_node).value = value;
      (*new_node).key = key;
   }
   else
   {
      // else get new node and put new value at head of bucket
      new_node = node_make();
      (*new_node).value = value;
      (*new_node).key = key;
      (*new_node).next = (*htable).bucket[i];
      (*new_node).next_in_sequence = NULL;
      
      // put in sequence
      if ( (*htable).last_in_sequence == NULL )
      {
         (*htable).first_in_sequence = new_node;
         (*htable).last_in_sequence = new_node;
      }
      else
      {
         (*(*htable).last_in_sequence).next_in_sequence = new_node;
         (*htable).last_in_sequence = new_node;
      }
      
      // put in bucket
      (*htable).bucket[i] = new_node;
      (*htable).count = (*htable).count + 1;
   }

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return;
}

/**
   HTable_remove
*/

void
HTable_remove( Prefix )( HTable_type( Prefix ) *htable, Key key )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );
   PRECONDITION( "has key", has( htable, key ) );

   int32_t hash_code = HASH_FUNCTION( key );
   int32_t i = hash_code % (*htable).bucket_count;

   // get node for search
   node_t *last_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*htable).bucket[i];

   // see if first node in bucket matches
   if ( EQUALITY_FUNCTION( (*node).key, key ) == 1 )
   {
         // remove first node
         (*htable).bucket[i] = (*node).next;
         move_all_cursors_forth_after_node_removal( htable, node );
         remove_node_from_sequence( htable, node );
         node_dispose( node );
         (*htable).count = (*htable).count - 1;
   }
   else
   {
      last_node = node;
      node = (*node).next;

      // if not, look through rest of nodes in bucket for match to key
      while ( node != NULL )
      {
         if ( EQUALITY_FUNCTION( (*node).key, key ) == 1 )
         {
            (*last_node).next = (*node).next;
            move_all_cursors_forth_after_node_removal( htable, node );
            remove_node_from_sequence( htable, node );
            node_dispose( node );
            (*htable).count = (*htable).count - 1;
            break;
         }

         last_node = node;
         node = (*node).next;
      }
   }

   // if count now zero, set first and last in sequence to  NULL
   if ( (*htable).count == 0 )
   {
      (*htable).first_in_sequence = NULL;
      (*htable).last_in_sequence = NULL;
   }

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return;
}

/**
   HTable_remove_and_dispose
*/

void
HTable_remove_and_dispose( Prefix )( HTable_type( Prefix ) *htable, Key key )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );
   PRECONDITION( "has key", has( htable, key ) );

   int32_t hash_code = HASH_FUNCTION( key );
   int32_t i = hash_code % (*htable).bucket_count;

   // get node for search
   node_t *last_node = NULL;

   // get first of bucket's nodes
   node_t *node = (*htable).bucket[i];

   // see if first node in bucket matches
   if ( EQUALITY_FUNCTION( (*node).key, key ) == 1 )
   {
         // remove first node
         (*htable).bucket[i] = (*node).next;
         KEY_DISPOSE_FUNCTION( (*node).key );
         VALUE_DISPOSE_FUNCTION( (*node).value );
         move_all_cursors_forth_after_node_removal( htable, node );
         remove_node_from_sequence( htable, node );
         node_dispose( node );
         (*htable).count = (*htable).count - 1;
   }
   else
   {
      last_node = node;
      node = (*node).next;

      // if not, look through rest of nodes in bucket for match to key
      while ( node != NULL )
      {
         if ( EQUALITY_FUNCTION( (*node).key, key ) == 1 )
         {
            (*last_node).next = (*node).next;
            KEY_DISPOSE_FUNCTION( (*node).key );
            VALUE_DISPOSE_FUNCTION( (*node).value );
            move_all_cursors_forth_after_node_removal( htable, node );
            remove_node_from_sequence( htable, node );
            node_dispose( node );
            (*htable).count = (*htable).count - 1;
            break;
         }

         last_node = node;
         node = (*node).next;
      }
   }

   // if count now zero, set first and last in sequence to  NULL
   if ( (*htable).count == 0 )
   {
      (*htable).first_in_sequence = NULL;
      (*htable).last_in_sequence = NULL;
   }

   if ( (*htable).count == 1 )
   {
      (*htable).last_in_sequence = (*htable).first_in_sequence;
   }

   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return;
}

/**
   HTable_wipe_out
*/

void
HTable_wipe_out( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   // delete htable sequence items
   node_t *item = (*htable).first_in_sequence;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next_in_sequence;
      node_dispose( item );
      item = next;
   }

   // delete cursors, all but first
   HTable_cursor_type( Prefix ) *cursor = (*(*htable).first_cursor).next_cursor;
   HTable_cursor_type( Prefix ) *next_cursor = NULL;
   (*(*htable).first_cursor).next_cursor = NULL;
   (*htable).last_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // clear out buckets
   memset( (*htable).bucket, 0, (*htable).bucket_count*sizeof( node_t * ) );

   // set count to zero
   (*htable).count = 0;
   (*htable).first_in_sequence = NULL;
   (*htable).last_in_sequence = NULL;

   POSTCONDITION( "is empty", (*htable).count == 0 );
   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return;
}

/**
   HTable_wipe_out_and_dispose
*/

void
HTable_wipe_out_and_dispose( Prefix )( HTable_type( Prefix ) *htable )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   // delete htable sequence items
   node_t *item = (*htable).first_in_sequence;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next_in_sequence;
      KEY_DISPOSE_FUNCTION( (*item).key );
      VALUE_DISPOSE_FUNCTION( (*item).value );
      node_dispose( item );
      item = next;
   }

   // delete cursors, all but first
   HTable_cursor_type( Prefix ) *cursor = (*(*htable).first_cursor).next_cursor;
   HTable_cursor_type( Prefix ) *next_cursor = NULL;
   (*(*htable).first_cursor).next_cursor = NULL;
   (*htable).last_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // clear out buckets
   memset( (*htable).bucket, 0, (*htable).bucket_count*sizeof( node_t * ) );

   // set count to zero
   (*htable).count = 0;
   (*htable).first_in_sequence = NULL;
   (*htable).last_in_sequence = NULL;

   POSTCONDITION( "is empty", (*htable).count == 0 );
   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return;
}

/**
   HTable_set_bucket_count
*/

void
HTable_set_bucket_count( Prefix )( HTable_type( Prefix ) *htable, int32_t new_bucket_count )
{
   PRECONDITION( "htable not null", htable != NULL );
   PRECONDITION( "htable type ok", ( (*htable).type == HTABLE_TYPE ) && ( (*htable).key_type = Key_Code ) && ( (*htable).item_type = Type_Code ) );
   PRECONDITION( "bucket count ok", new_bucket_count > 0 );
   LOCK( (*htable).mutex );
   INVARIANT( htable );

   // change size of bucket array
   (*htable).bucket
      = ( node_t ** ) realloc( (*htable).bucket, new_bucket_count*sizeof( node_t * ) );
   (*htable).bucket_count = new_bucket_count;


   // zero out bucket array
   memset( (*htable).bucket, 0, (*htable).bucket_count*sizeof( node_t * ) );

   // fill the buckets
   node_t *node = NULL;

   int32_t hash_code = 0;
   int32_t i = 0;

   for (   node = (*htable).first_in_sequence;
           node != NULL;
           node = (*node).next_in_sequence
       )
   {
      hash_code = HASH_FUNCTION( (*node).key );
      i = hash_code % (*htable).bucket_count;
      (*node).next = (*htable).bucket[i];
      (*htable).bucket[i] = node;
   }

   POSTCONDITION( "bucket count set", (*htable).bucket_count == new_bucket_count );
   INVARIANT( htable );
   UNLOCK( (*htable).mutex );

   return;
}


#ifdef __cplusplus
}
#endif

/* End of file */

