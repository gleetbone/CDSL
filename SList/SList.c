/**
 @file SList.c
 @author Greg Lee
 @version 1.0.0
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
#include "P_Clonable.ph"
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

#define SLIST_TYPE 0xA5000101

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

   int32_t type;
   int32_t item_type;
   
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
   move_all_cursors_at_node_forth

   After a node has been removed, move all cursors pointing to that node
   forth.

   @param list SList_t instance
   @param node the just removed node
*/
static
void
move_all_cursors_at_node_forth
(
   SList_type( Prefix ) *list,
   node_t *node
)
{
   SList_cursor_type( Prefix ) *cursor = NULL;

   for (  cursor = (*list).first_cursor;
          cursor != NULL;
          cursor = (*cursor).next_cursor
       )
   {
      if ( (*cursor).item != NULL )
      {
         if ( (*cursor).item == node )
         {
            (*cursor).item = (*(*cursor).item).next;
         }
      }
   }

   return;
}

/**
   move_all_cursors_off

   Move all cursors pointing off.

   @param node the just removed node
*/
static
void
move_all_cursors_off
(
   SList_type( Prefix ) *list
)
{
   SList_cursor_type( Prefix ) *cursor = NULL;

   for (  cursor = (*list).first_cursor;
          cursor != NULL;
          cursor = (*cursor).next_cursor
       )
   {
      (*cursor).item = NULL;
   }

   return;
}

/**
   node_at_index
   
   @param list the list
   @param index the index to find
   @return the node at index
*/
static
node_t *
node_at_index( SList_type( Prefix ) *list, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "index OK", ( ( index >= 0 ) && ( index < (*list).count ) ) );
   
   int32_t i = 0;
   node_t *result = (*list).first;
   
   if ( result != NULL )
   {
      for( i=1; ( i<=index ) && ( result != NULL ); i++ )
      {
         result = (*result).next;
      }
   }
   
   return result;
}

/**
   node_before
   
   @param list the list
   @param node the node after the desired node
   @return the node at index
*/
static
node_t *
node_before( SList_type( Prefix ) *list, node_t *node )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "node not null", node != NULL );
   
   node_t *result = NULL;
   node_t *n = (*list).first;
   
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
is_empty_implies_first_last_null( SList_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).count == 0 )
   {
      result
         = (
               ( (*p).first == NULL )
               &&
               ( (*p).last  == NULL )
           );
   }

   return result;
}

static
int32_t
nonnegative_count( SList_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
valid_count( SList_type( Prefix ) *p )
{
   int32_t result = 1;
   int32_t n = 0;

   node_t *node = (*p).first;

   while( node != NULL )
   {
      n = n + 1;
      node = (*node).next;
   }

   result = ( n == (*p).count );

   return result;
}

static
int32_t
first_cursor_not_null( SList_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).first_cursor != NULL );

   return result;
}

static
int32_t
last_cursor_next_null( SList_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).last_cursor != NULL )
   {
      result = ( (*(*p).last_cursor).next_cursor == NULL );
   }

   return result;
}

static
void invariant( SList_type( Prefix ) *p )
{
   assert(((void) "empty implies first and last null", is_empty_implies_first_last_null( p ) ));
   assert(((void) "nonnegative count", nonnegative_count( p ) ));
   assert(((void) "valid count", valid_count( p ) ));
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
   SList_dispose( Prefix ),
   SList_dispose_with_contents( Prefix ),
   SList_make_from( Prefix ),
   SList_make_duplicate_from( Prefix )
};

static
void *
p_indexable_table[P_INDEXABLE_FUNCTION_COUNT]
=
{
   SList_dispose( Prefix ),
   SList_dispose_with_contents( Prefix ),
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
   SList_dispose( Prefix ),
   SList_dispose_with_contents( Prefix ),
   SList_count( Prefix ),
   SList_item_at( Prefix ),
   SList_off( Prefix ),
   SList_is_empty( Prefix ),
   SList_start( Prefix ),
   SList_forth( Prefix )
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
   
      case P_INDEXABLE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_INDEXABLE_FUNCTION_MAX ) )
         {
            result = p_indexable_table[ function_id ];
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
      
      case P_INDEXABLE:
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
   put_last
*/

static
void
put_last( SList_type( Prefix ) *list, Type value )
{
   node_t *node = (*list).last;

   if ( node == NULL )
   {
      node_t *new_node = node_make();
      (*new_node).value = value;

      (*list).first = new_node;
      (*list).last = new_node;

      (*list).count = 1;
   }
   else
   {
      node_t *new_node = node_make();
      (*new_node).value = value;

      (*new_node).next = NULL;
      (*node).next = new_node;

      (*list).last = new_node;

      (*list).count = (*list).count + 1;
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
   SList_type( Prefix ) * list
      = ( SList_type( Prefix ) * ) calloc( 1, sizeof( SList_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( list );

   // set type codes
   (*list).type = SLIST_TYPE;
   (*list).item_type = Type_Code;
   
   // set built-in cursor

   // allocate cursor struct
   SList_cursor_type( Prefix ) *cursor
      =  ( SList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( SList_cursor_type( Prefix ) ) );

   // set list
   (*cursor).list = list;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set list built-in cursor
   (*list).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*list).mutex );

   INVARIANT( list );

   return list;
}

/**
   SList_make_from
*/

SList_type( Prefix ) *
SList_make_from( Prefix )( SList_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == SLIST_TYPE ) && ( (*other).item_type == Type_Code ) );
   
   // allocate list struct
   SList_type( Prefix ) * result
      = ( SList_type( Prefix ) * ) calloc( 1, sizeof( SList_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = SLIST_TYPE;
   (*result).item_type = Type_Code;
   
   // set built-in cursor

   // allocate cursor struct
   SList_cursor_type( Prefix ) *cursor
      =  ( SList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( SList_cursor_type( Prefix ) ) );

   // set list
   (*cursor).list = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set list built-in cursor
   (*result).first_cursor = cursor;

   // copy from "list"
   LOCK( (*other).mutex );

   int32_t i = 0;
   node_t *node = (*other).first;

   for ( i = 0; i < (*other).count; i++ )
   {
      put_last( result, (*node).value );
      node = (*node).next;
   }

   UNLOCK( (*other).mutex );

   (*result).count = (*other).count;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   SList_make_duplicate_from
*/

SList_type( Prefix ) *
SList_make_duplicate_from( Prefix )( SList_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == SLIST_TYPE ) && ( (*other).item_type == Type_Code ) );
   
   // allocate list struct
   SList_type( Prefix ) * result
      = ( SList_type( Prefix ) * ) calloc( 1, sizeof( SList_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = SLIST_TYPE;
   (*result).item_type = Type_Code;
   
   // set built-in cursor

   // allocate cursor struct
   SList_cursor_type( Prefix ) *cursor
      =  ( SList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( SList_cursor_type( Prefix ) ) );

   // set list
   (*cursor).list = result;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // set list built-in cursor
   (*result).first_cursor = cursor;

   // copy from "list"
   LOCK( (*other).mutex );


   int32_t i = 0;
   node_t *node = (*other).first;
   Type v;

   for ( i = 0; i < (*other).count; i++ )
   {
      v = VALUE_DUPLICATE_FUNCTION( (*node).value ); 
      put_last( result, v );
      node = (*node).next;
   }

   UNLOCK( (*other).mutex );

   (*result).count = (*other).count;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

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
   SList_type( Prefix ) * result
      = ( SList_type( Prefix ) * ) calloc( 1, sizeof( SList_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = SLIST_TYPE;
   (*result).item_type = Type_Code;
   
   // set built-in cursor

   // allocate cursor struct
   SList_cursor_type( Prefix ) *cursor
      =  ( SList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( SList_cursor_type( Prefix ) ) );

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

   INVARIANT( result );

   return result;
}

/**
   slist_cursor_make
*/

SList_cursor_type( Prefix ) *
slist_cursor_make( SList_type( Prefix ) *list )
{
   // allocate cursor struct
   SList_cursor_type( Prefix ) *cursor
      =  ( SList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( SList_cursor_type( Prefix ) ) );

   // set list
   (*cursor).list = list;

   // set item to NULL - cursor is "off"
   (*cursor).item = NULL;

   // place cursor reference into list structure
   if ( (*list).last_cursor == NULL )
   {
      // set second cursor for list
      (*(*list).first_cursor).next_cursor = cursor;
      (*list).last_cursor = cursor;
   }
   else
   {
      // set additional cursor for list
      // (*list).last_cursor holds last cursor allocated
      (*(*list).last_cursor).next_cursor = cursor;
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
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // allocate cursor struct
   SList_cursor_type( Prefix ) *cursor = slist_cursor_make( list );
   
   INVARIANT( list );
   POSTCONDITION( "new cursor is last cursor", (*list).last_cursor == cursor );
   UNLOCK( (*list).mutex );

   return cursor;
}

/**
   SList_dispose
*/

void
SList_dispose( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // delete list items
   node_t *item = (*list).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      node_dispose( item );
      item = next;
   }

   // delete cursors
   SList_cursor_type( Prefix ) *cursor = (*list).first_cursor;
   SList_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   MULTITHREAD_MUTEX_DESTROY( (*list).mutex );

   // delete list struct
   free( list );

   return;
}

/**
   SList_dispose_with_contents
*/

void
SList_dispose_with_contents( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // delete list items
   node_t *item = (*list).first;
   node_t *next = NULL;
   while( item != NULL )
   {
      next = (*item).next;
      VALUE_DISPOSE_FUNCTION( (*item).value );
      node_dispose( item );
      item = next;
   }

   // delete cursors
   SList_cursor_type( Prefix ) *cursor = (*list).first_cursor;
   SList_cursor_type( Prefix ) *next_cursor = NULL;
   while( cursor != NULL )
   {
      next_cursor = (*cursor).next_cursor;
      free( cursor );
      cursor = next_cursor;
   }

   MULTITHREAD_MUTEX_DESTROY( (*list).mutex );

   // delete list struct
   free( list );

   return;
}

/**
   slist_cursor_dispose
*/

void
slist_cursor_dispose( SList_cursor_type( Prefix ) *cursor )
{
   SList_cursor_type( Prefix ) *c1 = NULL;
   SList_cursor_type( Prefix ) *c2 = NULL;
   int32_t flag = 0;

   // find and remove this cursor from list structure
   c1 = (*(*cursor).list).first_cursor;
   c2 = (*c1).next_cursor;

   // search through the rest of the cursors
   while ( ( c2 != NULL) && ( flag == 0 ) )
   {
      if ( c2 == cursor )
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
   c1 = (*(*cursor).list).first_cursor;
   while ( c1 != NULL )
   {
      c2 = c1;
      c1 = (*c1).next_cursor;
   }
   (*(*cursor).list).last_cursor = c2;

   // only one cursor, last_cursor is NULL
   if ( c2 == (*(*cursor).list).first_cursor )
   {
      (*(*cursor).list).last_cursor = NULL;
   }
   
   // delete cursor struct
   free( cursor );

   return;
};

/**
   SList_cursor_dispose
*/

void
SList_cursor_dispose( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   SList_type( Prefix ) *list = (*cursor).list;
   
   slist_cursor_dispose( cursor );
   
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
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   Type value = (*(*cursor).item).value;

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}


/**
   SList_item_at
*/

Type
SList_item_at( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not off", (*(*list).first_cursor).item != NULL );

   SList_cursor_type( Prefix ) *cursor = (*list).first_cursor;

   Type value = (*(*cursor).item).value;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   SList_item
*/

Type
SList_item( Prefix )( SList_type( Prefix ) *list, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   node_t *node = (*list).first;

   int32_t i = 0;
   for ( i = 1; i <= index; i++ )
   {
      node = (*node).next;
   }

   Type value = (*node).value;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   SList_first
*/

Type
SList_first( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "first not null", (*list).first != NULL );

   Type value = (*(*list).first).value;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   SList_last
*/

Type
SList_last( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "first not null", (*list).first != NULL );

   Type value = (*(*list).last).value;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   SList_as_array
*/

Type *
SList_as_array( Prefix )( SList_type( Prefix ) *list, int32_t *count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t i = 0;
   node_t *node = (*list).first;
   
   Type *result = ( Type * ) calloc( (*list).count + 1, sizeof( Type ) );

   for( i=0; i<(*list).count; i++ )
   {
      result[i] = (*node).value;
      node = (*node).next;
   }
   
   (*count) = (*list).count;
   
   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   SList_count
*/

int32_t
SList_count( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t count = (*list).count;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return count;
}

/**
   SList_off
*/

int32_t
SList_off( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t result = ( (*(*list).first_cursor).item == NULL );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   SList_cursor_off
*/

int32_t
SList_cursor_off( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = ( (*cursor).item == NULL );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   SList_is_first
*/

int32_t
SList_is_first( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t result = ( (*(*list).first_cursor).item == (*list).first );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   SList_cursor_is_first
*/

int32_t
SList_cursor_is_first( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = ( (*cursor).item == (*(*cursor).list).first );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   SList_is_last
*/

int32_t
SList_is_last( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t result = ( (*(*list).first_cursor).item ==  (*list).last );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   SList_cursor_is_last
*/

int32_t
SList_cursor_is_last( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = ( (*cursor).item == (*(*cursor).list).last );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   SList_index
*/

int32_t
SList_index( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t result = 0;
   int32_t n = (*list).count;
   node_t *node = (*list).first;
   node_t *target = (*(*list).first_cursor).item;
   
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
   
   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   SList_cursor_index
*/

int32_t
SList_cursor_index( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = 0;
   int32_t n = (*(*cursor).list).count;
   node_t *node = (*(*cursor).list).first;
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
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   SList_is_empty
*/

int32_t
SList_is_empty( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t result = ( (*list).count ==  0 );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   SList_forth
*/

void
SList_forth( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).item != NULL );

   (*(*list).first_cursor).item = (*(*(*list).first_cursor).item).next;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_cursor_forth
*/

void
SList_cursor_forth( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   (*cursor).item = (*(*cursor).item).next;

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_go
*/

void
SList_go( Prefix )( SList_type( Prefix ) *list, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   int32_t i = 0;
   (*(*list).first_cursor).item = (*list).first;

   for ( i = 1; ( i <= index ) && ( (*(*list).first_cursor).item != NULL ); i++ )
   {
      (*(*list).first_cursor).item = (*(*(*list).first_cursor).item).next;
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_cursor_go
*/

void
SList_cursor_go( Prefix )( SList_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*(*cursor).list).count ) ) );

   int32_t i = 0;
   (*cursor).item = (*(*cursor).list).first;

   for ( i = 1; ( i <= index ) && ( (*cursor).item != NULL ); i++ )
   {
      (*cursor).item = (*(*cursor).item).next;
   }

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_start
*/

void
SList_start( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   (*(*list).first_cursor).item = (*list).first;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_cursor_start
*/

void
SList_cursor_start( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   (*cursor).item = (*(*cursor).list).first;

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_put
*/

void
SList_put( Prefix )( SList_type( Prefix ) *list, Type value, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*list).count ) ) );

   int32_t i = 0;
   int32_t flag = 0;
   node_t *node = (*list).first;
   node_t *prev = NULL;


   if ( node == NULL )
   {
      // list is empty, make this the first item if index is 0
      if ( index == 0 )
      {
         node_t *new_node = node_make();
         (*new_node).value = value;
         (*list).first = new_node;
         (*list).last = new_node;
         (*list).count = 1;
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
            // if no such index, no change to list
            flag = 0;
            break;
         }
      }

      // change the list if index is valid
      if ( flag == 1 )
      {
         node_t *new_node = node_make();
         (*new_node).value = value;

         (*new_node).next = node;
         (*prev).next = new_node;

         (*list).count = (*list).count + 1;
      }

      // special case for putting new item at end of list
      if ( ( flag == 0 ) && ( index = (*list).count ) )
      {
         node_t *new_node = node_make();
         (*new_node).value = value;
         (*(*list).last).next = new_node;
         (*list).last = new_node;
         (*list).count = (*list).count + 1;
      }

   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_put_right
*/

void
SList_put_right( Prefix )( SList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).item != NULL );

   node_t *node = (*(*list).first_cursor).item;

   node_t *new_node = node_make();
   (*new_node).value = value;

   (*new_node).next = (*node).next;
   (*node).next = new_node;

   if ( (*list).last == node )
   {
      (*list).last = new_node;
   }

   (*list).count = (*list).count + 1;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_cursor_put_right
*/

void
SList_cursor_put_right( Prefix )( SList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   node_t *node = (*cursor).item;

   node_t *new_node = node_make();
   (*new_node).value = value;

   (*new_node).next = (*node).next;
   (*node).next = new_node;

   if ( (*(*cursor).list).last == node )
   {
      (*(*cursor).list).last = new_node;
   }

   (*(*cursor).list).count = (*(*cursor).list).count + 1;

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_put_first
*/

void
SList_put_first( Prefix )( SList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   node_t *node = (*list).first;

   if ( node == NULL )
   {
      node_t *new_node = node_make();
      (*new_node).value = value;

      (*list).first = new_node;
      (*list).last = new_node;

      (*list).count = 1;
   }
   else
   {
      node_t *new_node = node_make();
      (*new_node).value = value;

      (*new_node).next = node;

      (*list).first = new_node;

      (*list).count = (*list).count + 1;
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_put_last
*/

void
SList_put_last( Prefix )( SList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   put_last( list, value );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

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
append( SList_type( Prefix ) *list, SList_type( Prefix ) *other, node_t *node )
{
   int32_t i = 0;

   if ( node == NULL )
   {
      // prepend other to start of list
      if ( (*other).count > 0 )
      {
         node_t *n1 = (*list).first;

         node_t *new_node = node_make();
         (*new_node).value = (*(*other).first).value;
         (*list).first = new_node;
         node_t *n = new_node;

         SList_cursor_type( Prefix ) *cursor = slist_cursor_make( other );
         (*cursor).item = (*(*cursor).list).first;
         (*cursor).item = (*(*cursor).item).next;

         for( i = 1; i < (*other).count; i++ )
         {
            node_t *new_node = node_make();
            (*new_node).value = (*(*cursor).item).value;
            (*n).next = new_node;
            n = new_node;
         }

         (*n).next = n1;
         if ( n1 == NULL )
         {
            (*list).last = n;
         }

         (*list).count = (*list).count + (*other).count;
         slist_cursor_dispose( cursor );

      }
   }
   else
   {

      // append/insert other if it's not empty
      if ( (*other).count > 0 )
      {
         node_t *n1 = (*node).next;

         node_t *n = node_make();
         (*n).value = (*(*other).first).value;
         (*node).next = n;

         SList_cursor_type( Prefix ) *cursor = slist_cursor_make( other );
         (*cursor).item = (*(*cursor).list).first;
         (*cursor).item = (*(*cursor).item).next;

         for ( i = 1; i < (*other).count; i++ )
         {
            node_t *new_node = node_make();
            (*new_node).value = (*(*cursor).item).value;

            (*n).next = new_node;

            n = new_node;
         }

         (*n).next = n1;

         if ( n1 == NULL )
         {
            (*list).last = n;
         }

         (*list).count = (*list).count + (*other).count;
         slist_cursor_dispose( cursor );

      }


   }

   return;
}

/**
   SList_append
*/

void
SList_append( Prefix )( SList_type( Prefix ) *list, SList_type( Prefix ) *other, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == SLIST_TYPE ) && ( (*other).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*list).count ) ) );

   // lock other
   LOCK( (*other).mutex );

   int32_t i = 0;

   node_t *node = (*list).first;

   if ( ( index == 0 ) || ( node == NULL ) )
   {
      // append is at start of list (like a prepend)
      append( list, other, NULL );
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
         append( list, other, node );
      }

   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_append_right
*/

void
SList_append_right( Prefix )( SList_type( Prefix ) *list, SList_type( Prefix ) *other )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == SLIST_TYPE ) && ( (*other).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // lock other
   LOCK( (*other).mutex );

   node_t *node = (*(*list).first_cursor).item;

   append( list, other, node );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_cursor_append_right
*/

void
SList_cursor_append_right( Prefix )( SList_cursor_type( Prefix ) *cursor, SList_type( Prefix ) *other )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   PRECONDITION( "list not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == SLIST_TYPE ) && ( (*other).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   // lock other
   LOCK( (*other).mutex );

   node_t *node = (*cursor).item;

   append( (*cursor).list, other, node );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_append_first
*/

void
SList_append_first( Prefix )( SList_type( Prefix ) *list, SList_type( Prefix ) *other )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == SLIST_TYPE ) && ( (*other).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // lock other
   LOCK( (*other).mutex );

   append( list, other, NULL );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_append_last
*/

void
SList_append_last( Prefix )( SList_type( Prefix ) *list, SList_type( Prefix ) *other )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == SLIST_TYPE ) && ( (*other).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // lock other
   LOCK( (*other).mutex );

   node_t *node = (*list).last;

   append( list, other, node );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_replace
*/

void
SList_replace( Prefix )( SList_type( Prefix ) *list, Type value, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   int32_t i = 0;
   node_t *node = (*list).first;

   for ( i = 1; ( i <= index ) && ( node != NULL ); i++ )
   {
      node = (*node).next;
   }

   if ( node != NULL )
   {
      (*node).value = value;
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_replace_and_dispose
*/

void
SList_replace_and_dispose( Prefix )( SList_type( Prefix ) *list, Type value, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   int32_t i = 0;
   node_t *node = (*list).first;

   for ( i = 1; ( i <= index ) && ( node != NULL ); i++ )
   {
      node = (*node).next;
   }

   if ( node != NULL )
   {
      VALUE_DISPOSE_FUNCTION( (*node).value );
      (*node).value = value;
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_replace_at
*/

void
SList_replace_at( Prefix )( SList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).item != NULL );

   if ( (*(*list).first_cursor).item != NULL )
   {
      (*(*(*list).first_cursor).item).value = value;
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_replace_at_and_dispose
*/

void
SList_replace_at_and_dispose( Prefix )( SList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).item != NULL );

   if ( (*(*list).first_cursor).item != NULL )
   {
      VALUE_DISPOSE_FUNCTION( (*(*(*list).first_cursor).item).value );
      (*(*(*list).first_cursor).item).value = value;
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_cursor_replace_at
*/

void
SList_cursor_replace_at( Prefix )( SList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   if ( (*cursor).item != NULL )
   {
      (*(*cursor).item).value = value;
   }

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
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
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   if ( (*cursor).item != NULL )
   {
      VALUE_DISPOSE_FUNCTION( (*(*(*(*cursor).list).first_cursor).item).value );
      (*(*cursor).item).value = value;
   }

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   remove

   Helper function to remove an item from a list

   @param list a SList_t instance
   @param node1 the node to remove
*/

static
void
remove( SList_type( Prefix ) *list, node_t *node )
{
   node_t *n = NULL;
   
   if ( node != NULL )
   {
      move_all_cursors_at_node_forth( list, node );

      // only item in list
      if ( (*list).count == 1 )
      {
         (*list).first = NULL;
         (*list).last = NULL;
         (*list).count = 0;
         node_dispose( node );
      }
      // first item in list
      else if ( (*list).first == node )
      {
         (*list).first = (*node).next;
         (*list).count = (*list).count - 1;
         node_dispose( node );
      }
      // last item in list
      else if ( (*list).last == node )
      {
         n = node_at_index( list, (*list).count - 2 );
         (*list).last = n;
         (*n).next = NULL;
         (*list).count = (*list).count - 1;
         node_dispose( node );
      }
      // not first, not last item in list
      else 
      {
         n = node_before( list, node );
         (*n).next = (*node).next;
         (*list).count = (*list).count - 1;
         node_dispose( node );
      }

   }

   return;
}

/**
   remove_and_dispose

   Helper function to remove an item from a list and dispose of its value

   @param list a SList_t instance
   @param node1 the node to remove
*/

static
void
remove_and_dispose( SList_type( Prefix ) *list, node_t *node )
{
   node_t *n = NULL;
   
   if ( node != NULL )
   {
      move_all_cursors_at_node_forth( list, node );

      // only item in list
      if ( (*list).count == 1 )
      {
         (*list).first = NULL;
         (*list).last = NULL;
         (*list).count = 0;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
      // first item in list
      else if ( (*list).first == node )
      {
         (*list).first = (*node).next;
         (*list).count = (*list).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
      // last item in list
      else if ( (*list).last == node )
      {
         n = node_at_index( list, (*list).count - 2 );
         (*list).last = n;
         (*n).next = NULL;
         (*list).count = (*list).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
      // not first, not last item in list
      else
      {
         n = node_before( list, node );
         (*n).next = (*node).next;
         (*list).count = (*list).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }

   }

   return;
}

/**
   SList_remove
*/

void
SList_remove( Prefix )( SList_type( Prefix ) *list, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   int32_t i = 0;
   node_t *node = (*list).first;

   for ( i = 1; ( i <= index ) && ( node != NULL ); i++ )
   {
      node = (*node).next;
   }

   // remove the node
   remove( list, node );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_remove_and_dispose
*/

void
SList_remove_and_dispose( Prefix )( SList_type( Prefix ) *list, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   int32_t i = 0;
   node_t *node = (*list).first;

   for ( i = 1; ( i <= index ) && ( node != NULL ); i++ )
   {
      node = (*node).next;
   }

   // remove the node
   remove_and_dispose( list, node );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_remove_at
*/

void
SList_remove_at( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).item != NULL );

   node_t *node = (*(*list).first_cursor).item;

   // remove the node
   remove( list, node );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_remove_at_and_dispose
*/

void
SList_remove_at_and_dispose( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).item != NULL );

   node_t *node = (*(*list).first_cursor).item;

   // remove the node
   remove_and_dispose( list, node );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_cursor_remove_at
*/

void
SList_cursor_remove_at( Prefix )( SList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   node_t *node = (*cursor).item;
   SList_type( Prefix ) *list = (*cursor).list;

   // remove the node
   remove( list, node );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
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
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == SLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   node_t *node = (*cursor).item;
   SList_type( Prefix ) *list = (*cursor).list;

   // remove the node
   remove_and_dispose( list, node );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   SList_remove_first
*/

void
SList_remove_first( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not empty", ( (*list).count > 0 ) );

   node_t *node = (*list).first;

   // remove the node
   remove( list, node );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_remove_first_and_dispose
*/

void
SList_remove_first_and_dispose( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not empty", ( (*list).count > 0 ) );

   node_t *node = (*list).first;

   // remove the node
   remove_and_dispose( list, node );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_remove_last
*/

void
SList_remove_last( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not empty", ( (*list).count > 0 ) );

   node_t *node = (*list).last;

   // remove the node
   remove( list, node );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_remove_last_and_dispose
*/

void
SList_remove_last_and_dispose( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not empty", ( (*list).count > 0 ) );

   node_t *node = (*list).last;

   // remove the node
   remove_and_dispose( list, node );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   prune

   Helper function to remove a sublist out of a list

   @param list a SList_t instance
   @param node1 the start node to remove
   @param node2 the end node to remove
*/

static
void
prune( SList_type( Prefix ) *list, node_t *node_start, int32_t count )
{
   int32_t i = 0;
   int32_t n = 0;
   node_t *node = node_start;
   node_t *n1 = NULL;
   node_t *ns = NULL;

   // move all cursors off - list will be mangled
   move_all_cursors_off( list );

   // node is first node
   if ( node == (*list).first )
   {
      // dispose of nodes
      for ( i = 0; i < count; i++ )
      {
         n1 = (*node).next;
         node_dispose( node );
         node = n1;
         if ( node == NULL )
         {
            break;
         }
      }

      // set new first item in list
      (*list).first = node;

      // decrement list count
      (*list).count = (*list).count - count;

      // if list now only has one item, set last
      if ( (*list).count == 1 )
      {
         (*list).last = node;
      }

      // if list is now empty, set first and last to null
      if ( (*list).count <= 0 )
      {
         (*list).first = NULL;
         (*list).last = NULL;
         (*list).count = 0;
      }

   }

   // node is last node
   else if ( node == (*list).last )
   {
      n1 = node_before( list, node );
      
      // set previous node as last
      (*n1).next = NULL;
      (*list).last = n1;

      // dispose of node
      node_dispose( node );

      // decrement list count
      (*list).count = (*list).count - 1;

      // if list now only has one item, set first
      if ( (*list).count == 1 )
      {
         (*list).first = (*list).last;
      }

   }
   // node is neither first nor last node
   else
   {
      ns = node_before( list, node );

      // dispose of nodes
      n = 0;
      for ( i = 0; i < count; i++ )
      {
         n1 = (*node).next;
         node_dispose( node );
         n++;
         node = n1;
         if ( node == NULL )
         {
            break;
         }
      }

      // set prev and next node pointers
      (*ns).next = node;

      // ns may be the last in the list
      if ( (*ns).next == NULL )
      {
         (*list).last = ns;
      }

      // node may be the last in the list
      if ( node != NULL )
      {
         if ( (*node).next == NULL )
         {
            (*list).last = node;
         }
      }

      // decrement list count
      (*list).count = (*list).count - n;

   }

   return;
}

/**
   prune_and_dispose

   Helper function to remove a sublist out of a list and dispose of its
   values.

   @param list a SList_t instance
   @param node1 the start node to remove
   @param node2 the end node to remove
*/

static
void
prune_and_dispose( SList_type( Prefix ) *list, node_t *node_start, int32_t count )
{
   int32_t i = 0;
   int32_t n = 0;
   node_t *node = node_start;
   node_t *n1 = NULL;
   node_t *ns = NULL;

   // move all cursors off - list will be mangled
   move_all_cursors_off( list );

   // node is first node
   if ( node == (*list).first )
   {
      // dispose of nodes
      for ( i = 0; i < count; i++ )
      {
         n1 = (*node).next;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
         node = n1;
         if ( node == NULL )
         {
            break;
         }
      }

      // set new first item in list
      (*list).first = node;

      // decrement list count
      (*list).count = (*list).count - count;

      // if list now only has one item, set last
      if ( (*list).count == 1 )
      {
         (*list).last = node;
      }

      // if list is now empty, set first and last to null
      if ( (*list).count <= 0 )
      {
         (*list).first = NULL;
         (*list).last = NULL;
         (*list).count = 0;
      }

   }

   // node1 is last node
   else if ( node == (*list).last )
   {
      n1 = node_before( list, node );
      
      // set previous node as last
      (*n1).next = NULL;
      (*list).last = n1;

      // dispose of node
      VALUE_DISPOSE_FUNCTION( (*node).value );
      node_dispose( node );

      // decrement list count
      (*list).count = (*list).count - 1;

      // if list now only has one item, set first
      if ( (*list).count == 1 )
      {
         (*list).first = (*list).last;
      }

   }
   // node is neither first nor last node
   else
   {
      ns = node_before( list, node );

      // dispose of nodes
      n = 0;
      for ( i = 0; i < count; i++ )
      {
         n1 = (*node).next;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
         n++;
         node = n1;
         if ( node == NULL )
         {
            break;
         }
      }

      // set prev and next node pointers
      (*ns).next = node;

      // ns may be the last in the list
      if ( (*ns).next == NULL )
      {
         (*list).last = ns;
      }

      // node may be the last in the list
      if ( node != NULL )
      {
         if ( (*node).next == NULL )
         {
            (*list).last = node;
         }
      }

      // decrement list count
      (*list).count = (*list).count - n;

   }

   return;
}


/**
   SList_prune
*/

void
SList_prune( Prefix )( SList_type( Prefix ) *list, int32_t index, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   int32_t i = 0;

   node_t *node = (*list).first;

   for ( i = 1; ( i <= index ) && ( node != NULL ); i++ )
   {
      node = (*node).next;
   }

   if ( node != NULL )
   {
      prune( list, node, count );
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_prune_and_dispose
*/

void
SList_prune_and_dispose( Prefix )( SList_type( Prefix ) *list, int32_t index, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   int32_t i = 0;

   node_t *node = (*list).first;

   for ( i = 1; ( i <= index ) && ( node != NULL ); i++ )
   {
      node = (*node).next;
   }

   if ( node != NULL )
   {
      prune_and_dispose( list, node, count );
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_prune_first
*/

void
SList_prune_first( Prefix )( SList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   node_t *node = (*list).first;

   prune( list, node, count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_prune_first_and_dispose
*/

void
SList_prune_first_and_dispose( Prefix )( SList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   node_t *node = (*list).first;

   prune_and_dispose( list, node, count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_prune_last
*/

void
SList_prune_last( Prefix )( SList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   node_t *node = (*list).last;

   node = node_at_index( list, (*list).count - count );
   
   if ( node != NULL )
   {
      prune( list, node, count );
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_prune_last_and_dispose
*/

void
SList_prune_last_and_dispose( Prefix )( SList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   node_t *node = (*list).last;

   node = node_at_index( list, (*list).count - count );

   if ( node != NULL )
   {
      prune_and_dispose( list, node, count );
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_keep_first
*/

void
SList_keep_first( Prefix )( SList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   int32_t i = 0;

   node_t *node = (*list).first;

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
      prune( list, node, (*list).count - count );
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_keep_first_and_dispose
*/

void
SList_keep_first_and_dispose( Prefix )( SList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   int32_t i = 0;

   node_t *node = (*list).first;

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
      prune_and_dispose( list, node, (*list).count - count );
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_keep_last
*/

void
SList_keep_last( Prefix )( SList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   node_t *node = (*list).first;

   prune( list, node, (*list).count - count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_keep_last_and_dispose
*/

void
SList_keep_last_and_dispose( Prefix )( SList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   node_t *node = (*list).first;

   prune_and_dispose( list, node, (*list).count - count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_wipe_out
*/

void
SList_wipe_out( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   node_t *node = (*list).first;
   node_t *next = NULL;

   // move all cursors off - list will be mangled
   move_all_cursors_off( list );

   // remove all nodes
   while ( node != NULL )
   {
      next = (*node).next;
      node_dispose( node );
      node = next;
   }

   (*list).count = 0;
   (*list).first = NULL;
   (*list).last = NULL;

   INVARIANT( list );
   POSTCONDITION( "list is empty", (*list).count == 0 );
   UNLOCK( (*list).mutex );

   return;
}

/**
   SList_wipe_out_and_dispose
*/

void
SList_wipe_out_and_dispose( Prefix )( SList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   node_t *node = (*list).first;
   node_t *next = NULL;

   // move all cursors off - list will be mangled
   move_all_cursors_off( list );

   // remove all nodes and values
   while ( node != NULL )
   {
      next = (*node).next;
      VALUE_DISPOSE_FUNCTION( (*node).value );
      node_dispose( node );
      node = next;
   }

   (*list).count = 0;
   (*list).first = NULL;
   (*list).last = NULL;

   INVARIANT( list );
   POSTCONDITION( "list is empty", (*list).count == 0 );
   UNLOCK( (*list).mutex );

   return;
}

/**
   Sorting stuff
*/

static MULTITHREAD_MUTEX_DEFINITION_INIT( sort_mutex );

static
int32_t (*value_sort_func_name)( Type v1, Type v2 ) = NULL;

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
SList_sort( Prefix )( SList_type( Prefix ) *list, int32_t (*sort_func)( Type v1, Type v2 ) )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == SLIST_TYPE ) && ( (*list).item_type == Type_Code ) );
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
      
      // fill the array
      node = (*list).first;
      
      for( i=0; i< (*list).count; i++ )
      {
         array[i] = node;
         node = (*node).next;
      }
      
      // get the sort mutex
      LOCK( sort_mutex );
      
      // set the sort func
      value_sort_func_name = sort_func;
      
      // sort the array
      qsort( array, (*list).count, sizeof( node_t * ), ( int (*)(const void*,const void*) ) node_sort_func );
      
      // release the sort mutex
      UNLOCK( sort_mutex );
      
      // put sorted items into list
      node = array[0];
      (*list).first = node;
      (*node).next = array[1];
      
      node = (*node).next;
      
      for( i=1; i< (*list).count; i++ )
      {
         if ( i == ( (*list).count - 1 ) )
         {
            (*node).next = NULL;
         }
         else
         {
            (*node).next = array[i+1];
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


/* End of file */

