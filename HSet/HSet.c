/**
 @file HSet.c
 @author Greg Lee
 @version 1.0.0
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

#ifdef PROTOCOLS_ENABLED   
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Clonable.ph"
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

#define HSET_TYPE 0xA5000300

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

   int32_t type;
   int32_t item_type;
   
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
   
   Return 1 if hset has an item thac compares equal to item, 0 if not
   
   @param hset HSet_t instance
   @param item the item to query for
*/

static
int32_t
has( HSet_type( Prefix ) *hset, Item item )
{
   int32_t hash_code = HASH_FUNCTION( item );   
   int32_t i = hash_code % (*hset).bucket_count;
   int32_t result = 0;
   
   // get first of bucket's nodes
   node_t *node = (*hset).bucket[i];
   
   // look through nodes in bucket for match to item
   while ( ( node != NULL ) && ( result == 0 ) ) 
   {
      if ( EQUALITY_FUNCTION( (*node).item, item ) == 1 )
      {
         result = 1;
      }
      node = (*node).next;
   }
   
   return result;
}

/**
   put
*/

static
void
put( HSet_type( Prefix ) *hset, Item item )
{
   int32_t hash_code = HASH_FUNCTION( item );   
   int32_t i = hash_code % (*hset).bucket_count;
   
   // get node for new value
   node_t *new_node = NULL;
   
   // get first of bucket's nodes
   node_t *node = (*hset).bucket[i];
   
   // see if node with this item already exists
   int32_t flag = 0;
   
   // look through nodes in bucket for match to item
   while ( ( node != NULL ) && ( flag == 0 ) ) 
   {
      if ( EQUALITY_FUNCTION( (*node).item, item ) == 1 )
      {
         flag = 1;
         new_node = node;
      }
      node = (*node).next;
   }
   
   // if node exists in hset, replace value with new value
   if ( new_node != NULL )
   {
      (*new_node).item = item;
   }
   else
   {
      // else get new node and put new value at head of bucket
      new_node = node_make();
      (*new_node).item = item;
      (*new_node).next = (*hset).bucket[i];
      (*hset).bucket[i] = new_node;
     
      // place new node in node sequence
      if ( (*hset).last_in_sequence == NULL )
      {
         (*hset).first_in_sequence = new_node;
         (*hset).last_in_sequence = new_node; 
      }
      else
      {
         (*(*hset).last_in_sequence).next_in_sequence = new_node;
         (*hset).last_in_sequence = new_node;
      }
      
      (*hset).count = (*hset).count + 1;
   }
   
   return;
}

/**
   move_all_cursors_forth_after_node_removal 
   
   After a node has been removed, move all cursors pointing to that node
   forth.
   
   @param hset HSet_t instance
   @param node the just removed node
*/
static
void
move_all_cursors_forth_after_node_removal
(
   HSet_type( Prefix ) *hset,
   node_t *node
)
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "node not null", node != NULL );
   
   HSet_cursor_type( Prefix ) *cursor = NULL;
   
   for (  cursor = (*hset).first_cursor;
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
   
   @param hset HSet_t instance
   @param node the to be removed node
*/
static
void
remove_node_from_sequence
(
   HSet_type( Prefix ) *hset,
   node_t *node
)
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "node not null", node != NULL );
   
   node_t *node1 = (*hset).first_in_sequence;
   node_t *prev = (*(*hset).first_in_sequence).next_in_sequence;

   if ( node1 == node )
   {
      (*hset).first_in_sequence = (*node).next_in_sequence;
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
            if ( node1 == (*hset).last_in_sequence )
            {
               (*hset).last_in_sequence = prev;
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
   
   @param hset HSet_t instance
*/
static
void
move_all_cursors_off
(
   HSet_type( Prefix ) *hset
)
{
   PRECONDITION( "hset not null", hset != NULL );
   
   HSet_cursor_type( Prefix ) *cursor = NULL;
   
   for (  cursor = (*hset).first_cursor;
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
is_empty_implies_first_last_null( HSet_type( Prefix ) *p )
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
nonnegative_count( HSet_type( Prefix ) *p )
{
   int32_t result = 1;
   
   result = ( (*p).count >= 0 );
   
   return result;
}

static
int32_t
last_in_sequence_ok( HSet_type( Prefix ) *p )
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
valid_sequence_count( HSet_type( Prefix ) *p )
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
valid_bucket_count( HSet_type( Prefix ) *p )
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
first_cursor_not_null( HSet_type( Prefix ) *p )
{
   int32_t result = 1;
   
   result = ( (*p).first_cursor != NULL );
   
   return result;
}

static
int32_t 
last_cursor_next_null( HSet_type( Prefix ) *p )
{
   int32_t result = 1;
   
   if ( (*p).last_cursor != NULL )
   {
      result = ( (*(*p).last_cursor).next_cursor == NULL );
   }
   
   return result;
}

static
void invariant( HSet_type( Prefix ) *p )
{
   assert(((void) "empty implies first and last null", is_empty_implies_first_last_null( p ) ));
   assert(((void) "nonnegative count", nonnegative_count( p ) ));
   assert(((void) "last in sequence OK", last_in_sequence_ok( p ) ));
   assert(((void) "valid sequence count", valid_sequence_count( p ) ));
   assert(((void) "valid bucket count", valid_bucket_count( p ) ));
   assert(((void) "first cursor not null", first_cursor_not_null( p ) ));
   assert(((void) "last cursor next null", last_cursor_next_null( p ) ));
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
   HSet_dispose( Prefix ),
   HSet_dispose_with_contents( Prefix ),
   HSet_make_from( Prefix ),
   HSet_make_duplicate_from( Prefix )
};

static
void *
p_iterable_table[P_ITERABLE_FUNCTION_COUNT]
=
{
   HSet_dispose( Prefix ),
   HSet_dispose_with_contents( Prefix ),
   HSet_count( Prefix ),
   HSet_item_at( Prefix ),
   HSet_off( Prefix ),
   HSet_is_empty( Prefix ),
   HSet_start( Prefix ),
   HSet_forth( Prefix )
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
   // allocate hset struct
   HSet_type( Prefix ) * hset 
      = ( HSet_type( Prefix ) * ) calloc( 1, sizeof( HSet_type( Prefix ) ) );
      
   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( hset );

   // set type codes
   (*hset).type = HSET_TYPE;
   (*hset).item_type = Type_Code;
   
   (*hset).count = 0;
   
   // allocate bucket array, default size
   (*hset).bucket = ( node_t ** ) calloc( DEFAULT_BUCKET_SIZE, sizeof( node_t * ) );     
      
   (*hset).bucket_count = DEFAULT_BUCKET_SIZE;
         
   // set built-in cursor
   // allocate cursor struct
   HSet_cursor_type( Prefix ) *cursor 
      =  ( HSet_cursor_type( Prefix ) * ) 
         calloc( 1, sizeof( HSet_cursor_type( Prefix ) ) );
         
   // set hset
   (*cursor).hset = hset;
   
   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;
   
   // set hset built-in cursor
   (*hset).first_cursor = cursor;
   
   MULTITHREAD_MUTEX_INIT( (*hset).mutex );

   INVARIANT( hset );
   
   return hset;
}

/**
   HSet_make_n
*/

HSet_type( Prefix ) *
HSet_make_n( Prefix )( int32_t bucket_count )
{
   PRECONDITION( "bucket count ok", bucket_count > 0 );
   
   // allocate hset struct
   HSet_type( Prefix ) * hset 
      = ( HSet_type( Prefix ) * ) calloc( 1, sizeof( HSet_type( Prefix ) ) );
      
   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( hset );

   // set type codes
   (*hset).type = HSET_TYPE;
   (*hset).item_type = Type_Code;
   
   (*hset).count = 0;
   
   // allocate bucket array
   (*hset).bucket = ( node_t ** ) calloc( bucket_count, sizeof( node_t * ) );     
      
   (*hset).bucket_count = bucket_count;
      
   // set built-in cursor
   // allocate cursor struct
   HSet_cursor_type( Prefix ) *cursor 
      =  ( HSet_cursor_type( Prefix ) * ) 
         calloc( 1, sizeof( HSet_cursor_type( Prefix ) ) );
         
   // set hset
   (*cursor).hset = hset;
   
   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;
   
   // set hset built-in cursor
   (*hset).first_cursor = cursor;
      
   MULTITHREAD_MUTEX_INIT( (*hset).mutex );

   INVARIANT( hset );
   POSTCONDITION( "bucket count set", (*hset).bucket_count == bucket_count );
   
   return hset;
}

/**
   HSet_make_from
*/

HSet_type( Prefix ) *
HSet_make_from( Prefix )( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );   
   
   // allocate hset struct
   HSet_type( Prefix ) * result 
      = ( HSet_type( Prefix ) * ) calloc( 1, sizeof( HSet_type( Prefix ) ) );
      
   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = HSET_TYPE;
   (*result).item_type = Type_Code;
   
   (*result).count = 0;
   
   // allocate bucket array
   (*result).bucket = ( node_t ** ) calloc( (*hset).bucket_count, sizeof( node_t * ) );     
      
   (*result).bucket_count = (*hset).bucket_count;
      
   // set built-in cursor
   // allocate cursor struct
   HSet_cursor_type( Prefix ) *cursor 
      =  ( HSet_cursor_type( Prefix ) * ) 
         calloc( 1, sizeof( HSet_cursor_type( Prefix ) ) );
         
   // set hset
   (*cursor).hset = result;
   
   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;
   
   // set hset built-in cursor
   (*result).first_cursor = cursor;
   
   int32_t i = 0;
   node_t *node = (*hset).first_in_sequence;
   
   // put items from hset into result
   for ( i = 0; i < (*hset).count; i++ ) 
   {
      put( result, (*node).item );
      node = (*node).next_in_sequence;
   }
   
   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   UNLOCK( (*hset).mutex );
   
   return result;
}

/**
   HSet_make_duplicate_from
*/

HSet_type( Prefix ) *
HSet_make_duplicate_from( Prefix )( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   
   INVARIANT( hset );
   
   // allocate hset struct
   HSet_type( Prefix ) * result 
      = ( HSet_type( Prefix ) * ) calloc( 1, sizeof( HSet_type( Prefix ) ) );
      
   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = HSET_TYPE;
   (*result).item_type = Type_Code;
   
   (*result).count = 0;
   
   // allocate bucket array
   (*result).bucket = ( node_t ** ) calloc( (*hset).bucket_count, sizeof( node_t * ) );     
      
   (*result).bucket_count = (*hset).bucket_count;
      
   // set built-in cursor
   // allocate cursor struct
   HSet_cursor_type( Prefix ) *cursor 
      =  ( HSet_cursor_type( Prefix ) * ) 
         calloc( 1, sizeof( HSet_cursor_type( Prefix ) ) );
         
   // set hset
   (*cursor).hset = result;
   
   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;
   
   // set hset built-in cursor
   (*result).first_cursor = cursor;
   
   int32_t i = 0;
   node_t *node = (*hset).first_in_sequence;
   
   Item item;
   // put items from hset into result
   for ( i = 0; i < (*hset).count; i++ ) 
   {
      item = DUPLICATE_FUNCTION( (*node).item );
      put( result, item );
      node = (*node).next_in_sequence;
   }
   
   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   UNLOCK( (*hset).mutex );
   
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
   HSet_type( Prefix ) * result = HSet_make( Prefix )();
      
   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = HSET_TYPE;
   (*result).item_type = Type_Code;
   
   int32_t i = 0;
   
   // put items from hset into result
   for ( i = 0; i < count; i++ ) 
   {
      put( result, array[i] );
   }
   
   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   
   return result;
}

/** 
   HSet_cursor_make
*/

HSet_cursor_type( Prefix ) * 
HSet_cursor_make( Prefix )( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   // allocate cursor struct
   HSet_cursor_type( Prefix ) *cursor 
      =  ( HSet_cursor_type( Prefix ) * ) 
         calloc( 1, sizeof( HSet_cursor_type( Prefix ) ) );
         
   // set hset
   (*cursor).hset = hset;
   
   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;
   
   // place cursor reference into hset structure
   if ( (*hset).last_cursor == NULL )
   {
      // set second cursor for hset
      (*(*hset).first_cursor).next_cursor = cursor;
      (*hset).last_cursor = cursor;
   }
   else
   {
      // set additional cursor for hset
      // (*hset).last_cursor holds last cursor allocated
      (*(*hset).last_cursor).next_cursor = cursor;
      (*hset).last_cursor = cursor;
   }
   
   MULTITHREAD_MUTEX_INIT( (*hset).mutex );

   INVARIANT( hset );
   POSTCONDITION( "new cursor is last cursor", (*hset).last_cursor == cursor );
   UNLOCK( (*hset).mutex );
   
   return cursor;
}

/** 
   HSet_dispose
*/

void
HSet_dispose( Prefix )( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   // delete hset sequence items
   node_t *item = (*hset).first_in_sequence;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next_in_sequence;
      node_dispose( item );
      item = next;
   }

   // delete cursors
   HSet_cursor_type( Prefix ) *cursor = (*hset).first_cursor;
   HSet_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // delete bucket array
   free( (*hset).bucket );
   
   MULTITHREAD_MUTEX_DESTROY( (*hset).mutex );

   // delete hset struct
   free( hset );

   return;
}

/** 
   HSet_dispose_with_contents
*/

void
HSet_dispose_with_contents( Prefix )( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   // delete hset sequence items
   node_t *item = (*hset).first_in_sequence;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next_in_sequence;
      DISPOSE_FUNCTION( (*item).item );
      node_dispose( item );
      item = next;
   }

   // delete cursors
   HSet_cursor_type( Prefix ) *cursor = (*hset).first_cursor;
   HSet_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // delete bucket array
   free( (*hset).bucket );
   
   MULTITHREAD_MUTEX_DESTROY( (*hset).mutex );

   // delete hset struct
   free( hset );

   return;
}

/** 
   HSet_cursor_dispose
*/

void
HSet_cursor_dispose( Prefix )( HSet_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).hset).type == HSET_TYPE ) && ( (*(*cursor).hset).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).hset).mutex );
   INVARIANT( (*cursor).hset );
   
   HSet_type( Prefix ) *hset = (*cursor).hset;

   HSet_cursor_type( Prefix ) *c1 = NULL;
   HSet_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;
   
   // find and remove this cursor from hset structure
   c1 = (*(*cursor).hset).first_cursor;
   c2 = (*c1).next_cursor;
   
   // search through the cursors
   while ( ( c2 != NULL) && ( flag == 0 ) )
   {
      if ( c2 == cursor )
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
   c1 = (*(*cursor).hset).first_cursor;
   while ( c1 != NULL )
   {
      c2 = c1;
      c1 = (*c1).next_cursor;
   }
   (*(*cursor).hset).last_cursor = c2;
   
   // only one cursor, last_cursor is NULL
   if ( c2 == (*(*cursor).hset).first_cursor )
   {
      (*(*cursor).hset).last_cursor = NULL;
   }
   
   // delete cursor struct
   free( cursor );
   
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
   PRECONDITION( "cursor list type ok", ( (*(*cursor).hset).type == HSET_TYPE ) && ( (*(*cursor).hset).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).hset).mutex );
   INVARIANT( (*cursor).hset );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   
   Item item = (*(*cursor).item).item;
   
   INVARIANT( (*cursor).hset );
   UNLOCK( (*(*cursor).hset).mutex );
   UNLOCK( (*cursor).mutex );
   
   return item;
}

/**
   HSet_item_at
*/

Item 
HSet_item_at( Prefix )( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   PRECONDITION( "not off", (*(*hset).first_cursor).item != NULL );
   
   HSet_cursor_type( Prefix ) *cursor = (*hset).first_cursor;

   Item item = (*(*cursor).item).item;
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return item;
}

/**
   HSet_item
*/

Item 
HSet_item( Prefix )( HSet_type( Prefix ) *hset, Item item )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   PRECONDITION( "has item", has( hset, item ) );
   
   int32_t hash_code = HASH_FUNCTION( item );   
   int32_t i = hash_code % (*hset).bucket_count;
   
   // get first of bucket's nodes
   node_t *node = (*hset).bucket[i];
   
   Item result = (*(*hset).first_in_sequence).item;
   
   // look through nodes in bucket for match to item
   while ( node != NULL ) 
   {
      if ( EQUALITY_FUNCTION( (*node).item, item ) == 1 )
      {
         result = (*node).item;
         break;
      }
      node = (*node).next;
   }
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return result;
}

/**
   HSet_item_at_index
*/

Item
HSet_item_at_index( Prefix )( HSet_type( Prefix ) *hset, int32_t index )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*hset).count ) );

   int32_t i = 0;
   node_t *node = (*hset).first_in_sequence;

   for( i = 1; i <= index; i ++ )
   {
      node = (*node).next_in_sequence;
   }

   Item item = (*node).item;

   INVARIANT( hset );
   UNLOCK( (*hset).mutex );

   return item;
}

/**
   HSet_as_array
*/

Item *
HSet_as_array( Prefix )( HSet_type( Prefix ) *hset, int32_t *count )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   int32_t i = 0;
   
   Item *result = ( Item * ) calloc( (*hset).count + 1, sizeof( Item ) );
   node_t *node = (*hset).first_in_sequence;
   
   // put nodes into array
   while ( node != NULL ) 
   {
      result[i] = (*node).item;
      i = i + 1;
      node = (*node).next_in_sequence;
   }
   
   (*count) = (*hset).count;
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return result;
}

/**
   HSet_count
*/

int32_t
HSet_count( Prefix )( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   int32_t count = (*hset).count;
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return count;
}

/**
   HSet_bucket_count
*/

int32_t
HSet_bucket_count( Prefix )( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   int32_t count = (*hset).bucket_count;
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return count;
}

/**
   HSet_off
*/

int32_t
HSet_off( Prefix)( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   int32_t result = ( (*(*hset).first_cursor).item == NULL );
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return result;
}

/**
   HSet_cursor_off
*/

int32_t
HSet_cursor_off( Prefix )( HSet_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).hset).type == HSET_TYPE ) && ( (*(*cursor).hset).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   
   int32_t result = ( (*cursor).item == NULL );
   
   UNLOCK( (*cursor).mutex );
   
   return result;
}

/**
   HSet_is_empty
*/

int32_t
HSet_is_empty( Prefix)( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   int32_t result = ( (*hset).count ==  0 );
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return result;
}

/**
   HSet_has
*/

int32_t
HSet_has( Prefix )( HSet_type( Prefix ) *hset, Item item )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   int32_t result = has( hset, item );
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return result;
}

/**
   HSet_cursor_forth
*/ 
void
HSet_cursor_forth( Prefix )( HSet_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).hset).type == HSET_TYPE ) && ( (*(*cursor).hset).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   
   if ( (*cursor).item != NULL )
   {
      (*cursor).item = (*(*cursor).item).next_in_sequence;
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
   PRECONDITION( "cursor list type ok", ( (*(*cursor).hset).type == HSET_TYPE ) && ( (*(*cursor).hset).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).hset).mutex );
   INVARIANT( (*cursor).hset );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*(*cursor).hset).count ) ) );
   
   int32_t i = 0;
   (*cursor).item = (*(*cursor).hset).first_in_sequence;
   
   for( i = 1; ( i <= index ) && ( (*cursor).item != NULL ); i++ )
   {
      (*cursor).item = (*(*cursor).item).next_in_sequence;
   }
   
   INVARIANT( (*cursor).hset );
   UNLOCK( (*(*cursor).hset).mutex );
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
   PRECONDITION( "cursor list type ok", ( (*(*cursor).hset).type == HSET_TYPE ) && ( (*(*cursor).hset).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).hset).mutex );
   INVARIANT( (*cursor).hset );

   int32_t result = 0;
   int32_t flag = 0;
   node_t *node = (*(*cursor).hset).first_in_sequence;
   node_t *target = (*cursor).item;

   if ( (*(*cursor).hset).count > 0 )
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
   UNLOCK( (*(*cursor).hset).mutex );
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
   PRECONDITION( "cursor list type ok", ( (*(*cursor).hset).type == HSET_TYPE ) && ( (*(*cursor).hset).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).hset).mutex );
   INVARIANT( (*cursor).hset );
   
   (*cursor).item = (*(*cursor).hset).first_in_sequence;
   
   INVARIANT( (*cursor).hset );
   UNLOCK( (*(*cursor).hset).mutex );
   UNLOCK( (*cursor).mutex );
   
   return;
}

/**
   HSet_forth
*/ 
void
HSet_forth( Prefix )( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   PRECONDITION( "not off", (*(*hset).first_cursor).item != NULL );
   
   if ( (*(*hset).first_cursor).item != NULL )
   {
      (*(*hset).first_cursor).item = (*(*(*hset).first_cursor).item).next_in_sequence;
   }
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex);
   
   return;
}

/**
   HSet_go
*/ 
void
HSet_go( Prefix )( HSet_type( Prefix ) *hset, int32_t index )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*hset).count ) ) );
   
   int32_t i = 0;
   (*(*hset).first_cursor).item = (*hset).first_in_sequence;
   
   for( i = 1; ( i <= index ) && ( (*(*hset).first_cursor).item != NULL ); i++ )
   {
      (*(*hset).first_cursor).item = (*(*(*hset).first_cursor).item).next_in_sequence;
   }
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return;
}

/**
   HSet_index
*/

int32_t
HSet_index( Prefix )( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );

   int32_t result = 0;
   int32_t flag = 0;
   node_t *node = (*hset).first_in_sequence;
   node_t *target = (*(*hset).first_cursor).item;

   if ( (*hset).count > 0 )
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
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );

   return result;
}

/**
   HSet_start
*/

void
HSet_start( Prefix )( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   (*(*hset).first_cursor).item = (*hset).first_in_sequence;
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return;
}

/**
   HSet_put
*/

void
HSet_put( Prefix )( HSet_type( Prefix ) *hset, Item item )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   put( hset, item );
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return;
}

/**
   HSet_replace
*/

void
HSet_replace( Prefix )( HSet_type( Prefix ) *hset, Item item )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   PRECONDITION( "has item", has( hset, item ) );
   
   int32_t hash_code = HASH_FUNCTION( item );   
   int32_t i = hash_code % (*hset).bucket_count;
   
   // get node for new value
   node_t *new_node = NULL;
   
   // get first of bucket's nodes
   node_t *node = (*hset).bucket[i];
   
   // see if node with this item already exists
   int32_t flag = 0;
   
   // look through nodes in bucket for match to item
   while ( ( node != NULL ) && ( flag == 0 ) ) 
   {
      if ( EQUALITY_FUNCTION( (*node).item, item ) == 1 )
      {
         flag = 1;
         new_node = node;
      }
      node = (*node).next;
   }
   
   // if node exists in hset, replace value with new value
   if ( new_node != NULL )
   {
      (*new_node).item = item;
   }
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return;
}

/**
   HSet_replace_and_dispose
*/

void
HSet_replace_and_dispose( Prefix )( HSet_type( Prefix ) *hset, Item item )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   PRECONDITION( "has item", has( hset, item ) );
   
   int32_t hash_code = HASH_FUNCTION( item );   
   int32_t i = hash_code % (*hset).bucket_count;
   
   // get node for new value
   node_t *new_node = NULL;
   
   // get first of bucket's nodes
   node_t *node = (*hset).bucket[i];
   
   // see if node with this item already exists
   int32_t flag = 0;
   
   // look through nodes in bucket for match to item
   while ( ( node != NULL ) && ( flag == 0 ) ) 
   {
      if ( EQUALITY_FUNCTION( (*node).item, item ) == 1 )
      {
         flag = 1;
         new_node = node;
      }
      node = (*node).next;
   }
   
   // if node exists in hset, replace value with new value
   if ( new_node != NULL )
   {
      DISPOSE_FUNCTION( (*new_node).item );
      (*new_node).item = item;
   }
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return;
}

/**
   remove
*/

static
void
remove( HSet_type( Prefix ) *hset, Item item )
{
   int32_t hash_code = HASH_FUNCTION( item );   
   int32_t i = hash_code % (*hset).bucket_count;
   int32_t flag = 0;
   
   // get node for search
   node_t *last_node = NULL;
   
   // get first of bucket's nodes
   node_t *node = (*hset).bucket[i];
   
   // see if first node in bucket matches
   if ( EQUALITY_FUNCTION( (*node).item, item ) == 1 )
   {
         // remove first node
         (*hset).bucket[i] = (*node).next;
         move_all_cursors_forth_after_node_removal( hset, node );
         remove_node_from_sequence( hset, node );
         node_dispose( node );
         (*hset).count = (*hset).count - 1;
   }
   else
   { 
      last_node = node;
      node = (*node).next;
      
      // if not, look through rest of nodes in bucket for match to item
      while ( ( node != NULL ) && ( flag == 0 ) ) 
      {
         if ( EQUALITY_FUNCTION( (*node).item, item ) == 1 )
         {
            flag = 1;
            (*last_node).next = (*node).next;
            move_all_cursors_forth_after_node_removal( hset, node );
            remove_node_from_sequence( hset, node );
            node_dispose( node );
            (*hset).count = (*hset).count - 1;
         }
         
         if ( flag == 0 )
         {
            last_node = node;
            node = (*node).next;
         }
      }
   }
   
   if ( (*hset).count == 0 )
   {
      (*hset).first_in_sequence = NULL;
      (*hset).last_in_sequence = NULL;
   }
   
   return;
}

/**
   HSet_remove
*/

void
HSet_remove( Prefix )( HSet_type( Prefix ) *hset, Item item )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   PRECONDITION( "has item", has( hset, item ) );

   remove( hset, item );
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return;
}

/**
   HSet_remove_and_dispose
*/

void
HSet_remove_and_dispose( Prefix )( HSet_type( Prefix ) *hset, Item item )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   PRECONDITION( "has item", has( hset, item ) );
   
   int32_t hash_code = HASH_FUNCTION( item );   
   int32_t i = hash_code % (*hset).bucket_count;
   int32_t flag = 0;
   
   // get node for search
   node_t *last_node = NULL;
   
   // get first of bucket's nodes
   node_t *node = (*hset).bucket[i];
   
   // see if first node in bucket matches
   if ( EQUALITY_FUNCTION( (*node).item, item ) == 1 )
   {
         // remove first node
         (*hset).bucket[i] = (*node).next;
         DISPOSE_FUNCTION( (*node).item );
         move_all_cursors_forth_after_node_removal( hset, node );
         remove_node_from_sequence( hset, node );
         node_dispose( node );
         (*hset).count = (*hset).count - 1;
   }
   else
   { 
      last_node = node;
      node = (*node).next;
      
      // if not, look through rest of nodes in bucket for match to item
      while ( ( node != NULL ) && ( flag == 0 ) ) 
      {
         if ( EQUALITY_FUNCTION( (*node).item, item ) == 1 )
         {
            flag = 1;
            (*last_node).next = (*node).next;
            DISPOSE_FUNCTION( (*node).item );
            move_all_cursors_forth_after_node_removal( hset, node );
            remove_node_from_sequence( hset, node );
            node_dispose( node );
            (*hset).count = (*hset).count - 1;
         }

         if ( flag == 0 )
         {
            last_node = node;
            node = (*node).next;
         }
      }
   }
   
   if ( (*hset).count == 0 )
   {
      (*hset).first_in_sequence = NULL;
      (*hset).last_in_sequence = NULL;
   }
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return;
}

/**
   HSet_wipe_out
*/

void
HSet_wipe_out( Prefix )( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   // delete hset sequence items
   node_t *item = (*hset).first_in_sequence;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next_in_sequence;
      node_dispose( item );
      item = next;
   }

   // delete cursors
   HSet_cursor_type( Prefix ) *cursor = (*(*hset).first_cursor).next_cursor;
   HSet_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }
   
   // set first cursor's next cursor to NULL
   (*(*hset).first_cursor).next_cursor = NULL;
   
   // and set last cursor to first cursor
   (*hset).last_cursor = (*hset).first_cursor;
   
   // clear out buckets
   memset( (*hset).bucket, 0, (*hset).bucket_count*sizeof( node_t * ) );

   // set all cursors off   
   move_all_cursors_off( hset );
        
   // set count to zero
   (*hset).count = 0;

   // set sequence pointers
   (*hset).first_in_sequence = NULL;
   (*hset).last_in_sequence = NULL;
      
   POSTCONDITION( "is empty", (*hset).count == 0 );
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return;
}

/**
   HSet_wipe_out_and_dispose
*/

void
HSet_wipe_out_and_dispose( Prefix )( HSet_type( Prefix ) *hset )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   // delete hset sequence items
   node_t *item = (*hset).first_in_sequence;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next_in_sequence;
      DISPOSE_FUNCTION( (*item).item );
      node_dispose( item );
      item = next;
   }

   // delete cursors
   HSet_cursor_type( Prefix ) *cursor = (*(*hset).first_cursor).next_cursor;
   HSet_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   // set first cursor's next cursor to NULL
   (*(*hset).first_cursor).next_cursor = NULL;
   
   // and set last cursor to first cursor
   (*hset).last_cursor = (*hset).first_cursor;
   
   // clear out buckets
   memset( (*hset).bucket, 0, (*hset).bucket_count*sizeof( node_t * ) );
   
   // set all cursors off   
   move_all_cursors_off( hset );
   
   // set count to zero
   (*hset).count = 0;
      
   // set sequence pointers
   (*hset).first_in_sequence = NULL;
   (*hset).last_in_sequence = NULL;
      
   POSTCONDITION( "is empty", (*hset).count == 0 );
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return;
}

/**
   HSet_set_bucket_count
*/

void
HSet_set_bucket_count( Prefix )( HSet_type( Prefix ) *hset, int32_t new_bucket_count )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   PRECONDITION( "bucket count ok", new_bucket_count > 0 );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   // change size of bucket array
   (*hset).bucket 
      = ( node_t ** ) realloc( (*hset).bucket, new_bucket_count*sizeof( node_t * ) );
   (*hset).bucket_count = new_bucket_count;
   
   
   // zero out bucket array
   memset( (*hset).bucket, 0, (*hset).bucket_count*sizeof( node_t * ) );

   // fill the buckets
   node_t *node = NULL;
   
   int32_t hash_code = 0;
   int32_t i = 0;
   
   for (   node = (*hset).first_in_sequence; 
           node != NULL; 
           node = (*node).next_in_sequence 
       )
   {
      hash_code = HASH_FUNCTION( (*node).item );   
      i = hash_code % (*hset).bucket_count;
      (*node).next = (*hset).bucket[i];
      (*hset).bucket[i] = node;
   }
   
   POSTCONDITION( "bucket count set", (*hset).bucket_count == new_bucket_count );
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return;
}

/**
   HSet_intersect
*/

void 
HSet_intersect( Prefix )( HSet_type( Prefix ) *hset, HSet_type( Prefix ) *other )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == HSET_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   // lock other
   LOCK( (*other).mutex );

   node_t *node = (*hset).first_in_sequence;
   node_t *next = NULL;

   // walk through nodes of hset, removing items not also in other    
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( other, (*node).item ) == 0 )
      {
         remove( hset, (*node).item );
      }
      node = next;
   }
   
   // unlock other
   UNLOCK( (*other).mutex );
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return;   
}

/**
   HSet_intersection
*/

HSet_type( Prefix ) * 
HSet_intersection( Prefix )( HSet_type( Prefix ) *hset, HSet_type( Prefix ) *other )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == HSET_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*other).mutex );
   INVARIANT( hset );
   
   HSet_type( Prefix ) *result = HSet_make_from( Prefix )( hset );
   
   node_t *node = (*result).first_in_sequence;
   node_t *next = NULL;

   // walk through nodes of hset, removing items not also in other    
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( other, (*node).item ) == 0 )
      {
         remove( result, (*node).item );
      }
      node = next;
   }
   
   INVARIANT( hset );
   UNLOCK( (*other).mutex );
   
   return result;   
}

/**
   HSet_subtract
*/

void 
HSet_subtract( Prefix )( HSet_type( Prefix ) *hset, HSet_type( Prefix ) *other )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == HSET_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   // lock other
   LOCK( (*other).mutex );

   node_t *node = (*hset).first_in_sequence;
   node_t *next = NULL;

   // walk through nodes of hset, removing items also in other    
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( other, (*node).item ) == 1 )
      {
         remove( hset, (*node).item );
      }
      node = next;
   }
   
   // unlock other
   UNLOCK( (*other).mutex );
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return;   
}

/**
   HSet_subtraction
*/

HSet_type( Prefix ) * 
HSet_subtraction( Prefix )( HSet_type( Prefix ) *hset, HSet_type( Prefix ) *other )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == HSET_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*other).mutex );
   INVARIANT( hset );
   
   HSet_type( Prefix ) *result = HSet_make_from( Prefix )( hset );
   
   node_t *node = (*result).first_in_sequence;
   node_t *next = NULL;

   // walk through nodes of hset, removing items also in other    
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( other, (*node).item ) == 1 )
      {
         remove( result, (*node).item );
      }
      node = next;
   }
   
   INVARIANT( hset );
   UNLOCK( (*other).mutex );
   
   return result;   
}

/**
   HSet_symdif
*/

void 
HSet_symdif( Prefix )( HSet_type( Prefix ) *hset, HSet_type( Prefix ) *other )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == HSET_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   // lock other
   LOCK( (*other).mutex );

   node_t *node = NULL;
   node_t *next = NULL;
   node_t *to_be_added = NULL;
   node_t *node1 = NULL;

   node = (*other).first_in_sequence;
   next = NULL;

   // walk through nodes of other, making list of items to add to hset    
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( hset, (*node).item ) == 0 )
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
   
   node = (*hset).first_in_sequence;
   
   // walk through nodes of hset, removing items also in other    
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( other, (*node).item ) == 1 )
      {
         remove( hset, (*node).item );
      }
      node = next;
   }
   
   
   // add items to hset, disposing of temporary nodes
   while( to_be_added != NULL )
   {
      put( hset, (*to_be_added).item );
      next = to_be_added;
      to_be_added = (*to_be_added).next;
      node_dispose( next );
   }
   
   // unlock other
   UNLOCK( (*other).mutex );
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return;   
}

/**
   HSet_symdifference
*/

HSet_type( Prefix ) * 
HSet_symdifference( Prefix )( HSet_type( Prefix ) *hset, HSet_type( Prefix ) *other )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == HSET_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*other).mutex );
   INVARIANT( hset );
   
   HSet_type( Prefix ) *result = HSet_make_from( Prefix )( hset );
   
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
      put( result, (*to_be_added).item );
      next = to_be_added;
      to_be_added = (*to_be_added).next;
      node_dispose( next );
   }
      
   INVARIANT( hset );
   UNLOCK( (*other).mutex );
   
   return result;   
}

/**
   HSet_merge
*/

void 
HSet_merge( Prefix )( HSet_type( Prefix ) *hset, HSet_type( Prefix ) *other )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == HSET_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   // lock other
   LOCK( (*other).mutex );

   node_t *node = (*other).first_in_sequence;
   node_t *next = NULL;
   node_t *to_be_added = NULL;
   node_t *node1 = NULL;

   // walk through nodes of other, making list of items to add to hset    
   while ( node != NULL )
   {
      next = (*node).next_in_sequence;
      if ( has( hset, (*node).item ) == 0 )
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
   
   // add items to hset, disposing of temporary nodes
   while( to_be_added != NULL )
   {
      put( hset, (*to_be_added).item );
      next = to_be_added;
      to_be_added = (*to_be_added).next;
      node_dispose( next );
   }
   
   // unlock other
   UNLOCK( (*other).mutex );
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return;   
}

/**
   HSet_union
*/

HSet_type( Prefix ) * 
HSet_union( Prefix )( HSet_type( Prefix ) *hset, HSet_type( Prefix ) *other )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == HSET_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*other).mutex );
   INVARIANT( hset );
   
   HSet_type( Prefix ) *result = HSet_make_from( Prefix )( hset );
   
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
      put( result, (*to_be_added).item );
      next = to_be_added;
      to_be_added = (*to_be_added).next;
      node_dispose( next );
   }
      
   INVARIANT( hset );
   UNLOCK( (*other).mutex );
   
   return result;   
}

/**
   HSet_is_disjoint
*/

int32_t 
HSet_is_disjoint( Prefix )( HSet_type( Prefix ) *hset, HSet_type( Prefix ) *other )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == HSET_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   // lock other
   LOCK( (*other).mutex );

   int32_t result = 1;
   node_t *node = (*hset).first_in_sequence;
   node_t *next = NULL;

   // walk through nodes of hset. if an item is also in other, result is 0   
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
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return result;   
}

/**
   HSet_is_subset
*/

int32_t 
HSet_is_subset( Prefix )( HSet_type( Prefix ) *hset, HSet_type( Prefix ) *other )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == HSET_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   // lock other
   LOCK( (*other).mutex );

   int32_t result = 1;
   node_t *node = (*hset).first_in_sequence;
   node_t *next = NULL;

   // walk through nodes of hset. if an item is not in other, result is 0   
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
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return result;   
}

/**
   HSet_is_superset
*/

int32_t 
HSet_is_superset( Prefix )( HSet_type( Prefix ) *hset, HSet_type( Prefix ) *other )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == HSET_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   // lock other
   LOCK( (*other).mutex );

   int32_t result = 1;
   node_t *node = (*other).first_in_sequence;
   node_t *next = NULL;

   // walk through nodes of other. if an item is not in hset, result is 0   
   while ( ( node != NULL ) && ( result == 1 ) )
   {
      next = (*node).next_in_sequence;
      if ( has( hset, (*node).item ) == 0 )
      {
         result = 0;
      }
      node = next;
   }
   
   // unlock other
   UNLOCK( (*other).mutex );
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return result;   
}

/**
   HSet_is_equal
*/

int32_t 
HSet_is_equal( Prefix )( HSet_type( Prefix ) *hset, HSet_type( Prefix ) *other )
{
   PRECONDITION( "hset not null", hset != NULL );
   PRECONDITION( "hset type ok", ( (*hset).type == HSET_TYPE ) && ( (*hset).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == HSET_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*hset).mutex );
   INVARIANT( hset );
   
   // lock other
   LOCK( (*other).mutex );

   int32_t result = 1;
   node_t *node = (*hset).first_in_sequence;
   node_t *next = NULL;

   // if count of hset and other are not equal, 
   // hset and other are not equal
   
   if ( (*hset).count != (*other).count )
   {
      result = 0;
   }
   
   // walk through nodes of hset. if an item is not in other, result is 0   
   while ( ( node != NULL ) && ( result == 1 ) )
   {
      next = (*node).next_in_sequence;
      if ( has( other, (*node).item ) == 0 )
      {
         result = 0;
      }
      node = next;
   }
   
   // if result == 1 (and count of hset and other are equal), then
   // hset and other are equal
   
   // unlock other
   UNLOCK( (*other).mutex );
   
   INVARIANT( hset );
   UNLOCK( (*hset).mutex );
   
   return result;   
}

/**
   HSet_equal_items
*/

int32_t 
HSet_equal_items( Prefix )( Item item, Item other )
{
   return EQUALITY_FUNCTION( item, other );
}


#ifdef __cplusplus
}
#endif

/* End of file */

