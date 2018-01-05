/**
 @file DList.c
 @author Greg Lee
 @version 1.0.0
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
#include "P_Clonable.ph"
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

#define DLIST_TYPE 0xA5000102

struct node;

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

   int32_t type;
   int32_t item_type;
   
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

   @param list DList_t instance
   @param node the just removed node
*/
static
void
move_all_cursors_at_node_forth
(
   DList_type( Prefix ) *list,
   node_t *node
)
{
   DList_cursor_type( Prefix ) *cursor = NULL;

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
   DList_type( Prefix ) *list
)
{
   DList_cursor_type( Prefix ) *cursor = NULL;

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
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
is_empty_implies_first_last_null( DList_type( Prefix ) *p )
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
nonnegative_count( DList_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
valid_count( DList_type( Prefix ) *p )
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
first_cursor_not_null( DList_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).first_cursor != NULL );

   return result;
}

static
int32_t
last_cursor_next_null( DList_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*p).last_cursor != NULL )
   {
      result = ( (*(*p).last_cursor).next_cursor == NULL );
   }

   return result;
}

static
void invariant( DList_type( Prefix ) *p )
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
   DList_dispose( Prefix ),
   DList_dispose_with_contents( Prefix ),
   DList_make_from( Prefix ),
   DList_make_duplicate_from( Prefix )
};

static
void *
p_indexable_table[P_INDEXABLE_FUNCTION_COUNT]
=
{
   DList_dispose( Prefix ),
   DList_dispose_with_contents( Prefix ),
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
   DList_dispose( Prefix ),
   DList_dispose_with_contents( Prefix ),
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
   DList_dispose( Prefix ),
   DList_dispose_with_contents( Prefix ),
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
      
      case P_DITERABLE:
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
   
      case P_DITERABLE:
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
put_last( DList_type( Prefix ) *list, Type value )
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

      (*new_node).prev = node;
      (*new_node).next = NULL;
      (*node).next = new_node;

      (*list).last = new_node;

      (*list).count = (*list).count + 1;
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
   DList_type( Prefix ) * list
      = ( DList_type( Prefix ) * ) calloc( 1, sizeof( DList_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( list );

   // set type codes
   (*list).type = DLIST_TYPE;
   (*list).item_type = Type_Code;
   
   // set built-in cursor

   // allocate cursor struct
   DList_cursor_type( Prefix ) *cursor
      =  ( DList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DList_cursor_type( Prefix ) ) );

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
   DList_make_from
*/

DList_type( Prefix ) *
DList_make_from( Prefix )( DList_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == DLIST_TYPE ) && ( (*other).item_type == Type_Code ) );  
   
   // allocate list struct
   DList_type( Prefix ) * result
      = ( DList_type( Prefix ) * ) calloc( 1, sizeof( DList_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = DLIST_TYPE;
   (*result).item_type = Type_Code;
   
   // set built-in cursor

   // allocate cursor struct
   DList_cursor_type( Prefix ) *cursor
      =  ( DList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DList_cursor_type( Prefix ) ) );

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
   DList_make_duplicate_from
*/

DList_type( Prefix ) *
DList_make_duplicate_from( Prefix )( DList_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == DLIST_TYPE ) && ( (*other).item_type == Type_Code ) );
   
   // allocate list struct
   DList_type( Prefix ) * result
      = ( DList_type( Prefix ) * ) calloc( 1, sizeof( DList_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = DLIST_TYPE;
   (*result).item_type = Type_Code;
   
   // set built-in cursor

   // allocate cursor struct
   DList_cursor_type( Prefix ) *cursor
      =  ( DList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DList_cursor_type( Prefix ) ) );

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
   DList_make_from_array
*/

DList_type( Prefix ) *
DList_make_from_array( Prefix )( Type *array, int32_t count )
{
   PRECONDITION( "array not null", array != NULL );
   PRECONDITION( "count ok", count >= 0 );
   
   // allocate list struct
   DList_type( Prefix ) * result
      = ( DList_type( Prefix ) * ) calloc( 1, sizeof( DList_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = DLIST_TYPE;
   (*result).item_type = Type_Code;
   
   // set built-in cursor

   // allocate cursor struct
   DList_cursor_type( Prefix ) *cursor
      =  ( DList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DList_cursor_type( Prefix ) ) );

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
   dlist_cursor_make
*/

DList_cursor_type( Prefix ) *
dlist_cursor_make( DList_type( Prefix ) *list )
{
   // allocate cursor struct
   DList_cursor_type( Prefix ) *cursor
      =  ( DList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( DList_cursor_type( Prefix ) ) );

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
   DList_cursor_make
*/

DList_cursor_type( Prefix ) *
DList_cursor_make( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );

   DList_cursor_type( Prefix ) *cursor = dlist_cursor_make( list );
   
   INVARIANT( list );
   POSTCONDITION( "new cursor is last cursor", (*list).last_cursor == cursor );
   UNLOCK( (*list).mutex );

   return cursor;
}

/**
   DList_dispose
*/

void
DList_dispose( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
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
   DList_cursor_type( Prefix ) *cursor = (*list).first_cursor;
   DList_cursor_type( Prefix ) *next_cursor = NULL;
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
   DList_dispose_with_contents
*/

void
DList_dispose_with_contents( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
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
   DList_cursor_type( Prefix ) *cursor = (*list).first_cursor;
   DList_cursor_type( Prefix ) *next_cursor = NULL;
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
   dlist_cursor_dispose
*/

void
dlist_cursor_dispose( DList_cursor_type( Prefix ) *cursor )
{
   DList_cursor_type( Prefix ) *c1 = NULL;
   DList_cursor_type( Prefix ) *c2 = NULL;
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
   DList_cursor_dispose
*/

void
DList_cursor_dispose( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   DList_type( Prefix ) *list = (*cursor).list;
   
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
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
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
   DList_item_at
*/

Type
DList_item_at( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not off", (*(*list).first_cursor).item != NULL );

   DList_cursor_type( Prefix ) *cursor = (*list).first_cursor;

   Type value = (*(*cursor).item).value;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   DList_cursor_item_next
*/

Type
DList_cursor_item_next( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "not off", (*cursor).item != NULL );
   PRECONDITION( "next not off", (*(*cursor).item).next != NULL );

   Type value = (*(*(*cursor).item).next).value;

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}

/**
   DList_item_next
*/

Type
DList_item_next( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not off", (*(*list).first_cursor).item != NULL );
   PRECONDITION( "next not off", (*(*(*list).first_cursor).item).next != NULL );

   Type value = (*(*(*(*list).first_cursor).item).next).value;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   DList_cursor_item_prev
*/

Type
DList_cursor_item_prev( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "not off", (*cursor).item != NULL );
   PRECONDITION( "prev not off", (*(*cursor).item).prev != NULL );

   Type value = (*(*(*cursor).item).prev).value;

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}

/**
   DList_item_prev
*/

Type
DList_item_prev( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not off", (*(*list).first_cursor).item != NULL );
   PRECONDITION( "next not off", (*(*(*list).first_cursor).item).prev != NULL );

   Type value = (*(*(*(*list).first_cursor).item).prev).value;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   DList_item
*/

Type
DList_item( Prefix )( DList_type( Prefix ) *list, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
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
   DList_first
*/

Type
DList_first( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "first not null", (*list).first != NULL );

   Type value = (*(*list).first).value;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   DList_last
*/

Type
DList_last( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "first not null", (*list).first != NULL );

   Type value = (*(*list).last).value;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   DList_as_array
*/

Type *
DList_as_array( Prefix )( DList_type( Prefix ) *list, int32_t *count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
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
   DList_count
*/

int32_t
DList_count( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t count = (*list).count;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return count;
}

/**
   DList_off
*/

int32_t
DList_off( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t result = ( (*(*list).first_cursor).item == NULL );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   DList_cursor_off
*/

int32_t
DList_cursor_off( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
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
   DList_is_first
*/

int32_t
DList_is_first( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t result = ( (*(*list).first_cursor).item == (*list).first );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   DList_cursor_is_first
*/

int32_t
DList_cursor_is_first( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
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
   DList_is_last
*/

int32_t
DList_is_last( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t result = ( (*(*list).first_cursor).item ==  (*list).last );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   DList_cursor_is_last
*/

int32_t
DList_cursor_is_last( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
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
   DList_index
*/

int32_t
DList_index( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
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
   DList_cursor_index
*/

int32_t
DList_cursor_index( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
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
   DList_is_empty
*/

int32_t
DList_is_empty( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t result = ( (*list).count ==  0 );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   DList_forth
*/

void
DList_forth( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).item != NULL );

   (*(*list).first_cursor).item = (*(*(*list).first_cursor).item).next;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_cursor_forth
*/

void
DList_cursor_forth( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
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
   DList_back
*/

void
DList_back( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).item != NULL );

   (*(*list).first_cursor).item = (*(*(*list).first_cursor).item).prev;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_cursor_back
*/

void
DList_cursor_back( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   (*cursor).item = (*(*cursor).item).prev;

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   DList_back
*/

void
DList_go( Prefix )( DList_type( Prefix ) *list, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
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
   DList_cursor_go
*/

void
DList_cursor_go( Prefix )( DList_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
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
   DList_start
*/

void
DList_start( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );

   (*(*list).first_cursor).item = (*list).first;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_cursor_start
*/

void
DList_cursor_start( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
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
   DList_finish
*/

void
DList_finish( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );

   (*(*list).first_cursor).item = (*list).last;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_cursor_finish
*/

void
DList_cursor_finish( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   (*cursor).item = (*(*cursor).list).last;

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   DList_put
*/

void
DList_put( Prefix )( DList_type( Prefix ) *list, Type value, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*list).count ) ) );

   int32_t i = 0;
   int32_t flag = 0;
   node_t *node = (*list).first;


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

         (*new_node).prev = (*node).prev;
         (*new_node).next = node;
         (*node).prev = new_node;
         (*(*new_node).prev).next = new_node;

         (*list).count = (*list).count + 1;
      }

      // special case for putting new item at end of list
      if ( ( flag == 0 ) && ( index = (*list).count ) )
      {
         node_t *new_node = node_make();
         (*new_node).value = value;
         (*(*list).last).next = new_node;
         (*new_node).prev = (*list).last;
         (*list).last = new_node;
         (*list).count = (*list).count + 1;
      }

   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_put_right
*/

void
DList_put_right( Prefix )( DList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).item != NULL );

   node_t *node = (*(*list).first_cursor).item;

   node_t *new_node = node_make();
   (*new_node).value = value;

   (*new_node).prev = node;
   (*new_node).next = (*node).next;
   if ( (*node).next != NULL )
   {
      (*(*node).next).prev = new_node;
   }
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
   DList_cursor_put_right
*/

void
DList_cursor_put_right( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   node_t *node = (*cursor).item;

   node_t *new_node = node_make();
   (*new_node).value = value;

   (*new_node).prev = node;
   (*new_node).next = (*node).next;
   if ( (*node).next != NULL )
   {
      (*(*node).next).prev = new_node;
   }
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
   DList_put_left
*/

void
DList_put_left( Prefix )( DList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).item != NULL );

   node_t *node = (*(*list).first_cursor).item;

   if ( node != NULL )
   {
      node_t *new_node = node_make();
      (*new_node).value = value;

      (*new_node).prev = (*node).prev;
      (*new_node).next = node;
      if ( (*node).prev != NULL )
      {
         (*(*node).prev).next = new_node;
      }
      (*node).prev = new_node;

      if ( (*list).first == node )
      {
         (*list).first = new_node;
      }

      (*list).count = (*list).count + 1;

   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_cursor_put_left
*/

void
DList_cursor_put_left( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );

   node_t *node = (*cursor).item;

   if ( node != NULL )
   {
      node_t *new_node = node_make();
      (*new_node).value = value;

      (*new_node).prev = (*node).prev;
      (*new_node).next = node;
      if ( (*node).prev != NULL )
      {
         (*(*node).prev).next = new_node;
      }
      (*node).prev = new_node;

      if ( (*(*cursor).list).first == node )
      {
         (*(*cursor).list).first = new_node;
      }

      (*(*cursor).list).count = (*(*cursor).list).count + 1;

   }

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   DList_put_first
*/

void
DList_put_first( Prefix )( DList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
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

      (*new_node).prev = NULL;
      (*new_node).next = node;
      (*node).prev = new_node;

      (*list).first = new_node;

      (*list).count = (*list).count + 1;
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_put_last
*/

void
DList_put_last( Prefix )( DList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
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

   @param list a DList_t instance
   @param other a DList_t instance to append/insert into list
   @param node1 the node after which to append/insert the list
                 if null, append other to start of list
*/

static
void
append( DList_type( Prefix ) *list, DList_type( Prefix ) *other, node_t *node )
{
   int32_t i = 0;

   if ( node == NULL )
   {
      // append other to start of list
      if ( (*other).count > 0 )
      {
         node_t *n1 = (*list).first;

         node_t *new_node = node_make();
         (*new_node).value = (*(*other).first).value;
         (*list).first = new_node;
         node_t *n = new_node;

         DList_cursor_type( Prefix ) *cursor = dlist_cursor_make( other );
         (*cursor).item = (*(*cursor).list).first;
         (*cursor).item = (*(*cursor).item).next;

         for( i = 1; i < (*other).count; i++ )
         {
            node_t *new_node = node_make();
            (*new_node).value = (*(*cursor).item).value;
            (*n).next = new_node;
            (*new_node).prev = n;
            n = new_node;
         }

         (*n).next = n1;
         if ( n1 == NULL )
         {
            (*list).last = n;
         }
         else
         {
            (*n1).prev = n;
         }

         (*list).count = (*list).count + (*other).count;
         dlist_cursor_dispose( cursor );

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
         (*n).prev = node;

         DList_cursor_type( Prefix ) *cursor = dlist_cursor_make( other );
         (*cursor).item = (*(*cursor).list).first;
         (*cursor).item = (*(*cursor).item).next;

         for ( i = 1; i < (*other).count; i++ )
         {
            node_t *new_node = node_make();
            (*new_node).value = (*(*cursor).item).value;

            (*new_node).prev = n;
            (*n).next = new_node;

            n = new_node;
         }

         (*n).next = n1;

         if ( n1 == NULL )
         {
            (*list).last = n;
         }
         else
         {
            (*n1).prev = n;
         }

         (*list).count = (*list).count + (*other).count;
         dlist_cursor_dispose( cursor );

      }


   }

   return;
}

/**
   DList_append
*/

void
DList_append( Prefix )( DList_type( Prefix ) *list, DList_type( Prefix ) *other, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == DLIST_TYPE ) && ( (*other).item_type == Type_Code ) );  
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
   DList_append_right
*/

void
DList_append_right( Prefix )( DList_type( Prefix ) *list, DList_type( Prefix ) *other )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == DLIST_TYPE ) && ( (*other).item_type == Type_Code ) );  
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
   DList_cursor_append_right
*/

void
DList_cursor_append_right( Prefix )( DList_cursor_type( Prefix ) *cursor, DList_type( Prefix ) *other )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == DLIST_TYPE ) && ( (*other).item_type == Type_Code ) );  
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
   DList_append_left
*/

void
DList_append_left( Prefix )( DList_type( Prefix ) *list, DList_type( Prefix ) *other )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == DLIST_TYPE ) && ( (*other).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   INVARIANT( list );

   // lock other
   LOCK( (*other).mutex );

   node_t *node = (*(*list).first_cursor).item;

   if ( node == NULL )
   {
      append( list, other, node );
   }
   else
   {
      node_t *n = (*node).prev;
      append( list, other, n );
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_cursor_append_left
*/

void
DList_cursor_append_left( Prefix )( DList_cursor_type( Prefix ) *cursor, DList_type( Prefix ) *other )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == DLIST_TYPE ) && ( (*other).item_type == Type_Code ) );  
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

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

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   DList_append_first
*/

void
DList_append_first( Prefix )( DList_type( Prefix ) *list, DList_type( Prefix ) *other )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == DLIST_TYPE ) && ( (*other).item_type == Type_Code ) );  
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
   DList_append_last
*/

void
DList_append_last( Prefix )( DList_type( Prefix ) *list, DList_type( Prefix ) *other )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == DLIST_TYPE ) && ( (*other).item_type == Type_Code ) );  
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
   DList_replace
*/

void
DList_replace( Prefix )( DList_type( Prefix ) *list, Type value, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );
   INVARIANT( list );

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
   DList_replace_and_dispose
*/

void
DList_replace_and_dispose( Prefix )( DList_type( Prefix ) *list, Type value, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );
   INVARIANT( list );

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
   DList_replace_at
*/

void
DList_replace_at( Prefix )( DList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "list not off", (*(*list).first_cursor).item != NULL );
   INVARIANT( list );

   if ( (*(*list).first_cursor).item != NULL )
   {
      (*(*(*list).first_cursor).item).value = value;
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_replace_at_and_dispose
*/

void
DList_replace_at_and_dispose( Prefix )( DList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "list not off", (*(*list).first_cursor).item != NULL );
   INVARIANT( list );

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
   DList_cursor_replace_at
*/

void
DList_cursor_replace_at( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   INVARIANT( (*cursor).list );

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
   DList_cursor_replace_at_and_dispose
*/

void
DList_cursor_replace_at_and_dispose( Prefix )( DList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   INVARIANT( (*cursor).list );

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

   @param list a DList_t instance
   @param node1 the node to remove
*/

static
void
remove( DList_type( Prefix ) *list, node_t *node )
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
         node_dispose( node );
      }
      // first item in list
      else if ( ( (*node).prev == NULL ) && ( (*node).next != NULL ) )
      {
         (*list).first = (*node).next;
         (*(*list).first).prev = NULL;
         (*list).count = (*list).count - 1;
         node_dispose( node );
      }
      // last item in list
      else if ( ( (*node).prev != NULL ) && ( (*node).next == NULL ) )
      {
         (*list).last = (*node).prev;
         (*(*list).last).next = NULL;
         (*list).count = (*list).count - 1;
         node_dispose( node );
      }
      // not first, not last item in list
      else if ( ( (*node).prev != NULL ) && ( (*node).next != NULL ) )
      {
         (*(*node).prev).next = (*node).next;
         (*(*node).next).prev = (*node).prev;
         (*list).count = (*list).count - 1;
         node_dispose( node );
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
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
      // first item in list
      else if ( ( (*node).prev == NULL ) && ( (*node).next != NULL ) )
      {
         (*list).first = (*node).next;
         (*(*list).first).prev = NULL;
         (*list).count = (*list).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
      // last item in list
      else if ( ( (*node).prev != NULL ) && ( (*node).next == NULL ) )
      {
         (*list).last = (*node).prev;
         (*(*list).last).next = NULL;
         (*list).count = (*list).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }
      // not first, not last item in list
      else if ( ( (*node).prev != NULL ) && ( (*node).next != NULL ) )
      {
         (*(*node).prev).next = (*node).next;
         (*(*node).next).prev = (*node).prev;
         (*list).count = (*list).count - 1;
         VALUE_DISPOSE_FUNCTION( (*node).value );
         node_dispose( node );
      }

   }

   return;
}

/**
   DList_remove
*/

void
DList_remove( Prefix )( DList_type( Prefix ) *list, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );
   INVARIANT( list );

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
   DList_remove_and_dispose
*/

void
DList_remove_and_dispose( Prefix )( DList_type( Prefix ) *list, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );
   INVARIANT( list );

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
   DList_remove_at
*/

void
DList_remove_at( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "list not off", (*(*list).first_cursor).item != NULL );
   INVARIANT( list );

   node_t *node = (*(*list).first_cursor).item;

   // remove the node
   remove( list, node );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_remove_at_and_dispose
*/

void
DList_remove_at_and_dispose( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "list not off", (*(*list).first_cursor).item != NULL );
   INVARIANT( list );

   node_t *node = (*(*list).first_cursor).item;

   // remove the node
   remove_and_dispose( list, node );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_cursor_remove_at
*/

void
DList_cursor_remove_at( Prefix )( DList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor type ok", ( (*(*cursor).list).type == DLIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );  
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   INVARIANT( (*cursor).list );

   node_t *node = (*cursor).item;
   DList_type( Prefix ) *list = (*cursor).list;

   // remove the node
   remove( list, node );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
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
   LOCK( (*(*cursor).list).mutex );
   PRECONDITION( "cursor not off", (*cursor).item != NULL );
   INVARIANT( (*cursor).list );

   node_t *node = (*cursor).item;
   DList_type( Prefix ) *list = (*cursor).list;

   // remove the node
   remove_and_dispose( list, node );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   DList_remove_first
*/

void
DList_remove_first( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "not empty", ( (*list).count > 0 ) );
   INVARIANT( list );

   node_t *node = (*list).first;

   // remove the node
   remove( list, node );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_remove_first_and_dispose
*/

void
DList_remove_first_and_dispose( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "not empty", ( (*list).count > 0 ) );
   INVARIANT( list );

   node_t *node = (*list).first;

   // remove the node
   remove_and_dispose( list, node );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_remove_last
*/

void
DList_remove_last( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "not empty", ( (*list).count > 0 ) );
   INVARIANT( list );

   node_t *node = (*list).last;

   // remove the node
   remove( list, node );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_remove_last_and_dispose
*/

void
DList_remove_last_and_dispose( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "not empty", ( (*list).count > 0 ) );
   INVARIANT( list );

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

   @param list a DList_t instance
   @param node_start the start node to remove
   @param count the number of entries to remove
*/

static
void
prune( DList_type( Prefix ) *list, node_t *node_start, int32_t count )
{
   int32_t i = 0;
   int32_t n = 0;
   node_t *node = node_start;
   node_t *prev = (*node_start).prev;
   node_t *n1 = NULL;
   node_t *ns = NULL;

   // move all cursors off - list will be mangled
   move_all_cursors_off( list );

   // node is first node
   if ( (*node).prev == NULL )
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

   // node1 is last node
   else if ( (*node).next == NULL )
   {
      // set previous node as last
      if ( (*node).prev != NULL )
      {
         (*(*node).prev).next = NULL;
      }
      (*list).last = (*node).prev;

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
      ns = (*node).prev;

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

      if ( node != NULL )
      {
         (*node).prev = prev;
      }

      // (*node).prev may be the last in the list
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

   @param list a DList_t instance
   @param node1 the start node to remove
   @param node2 the end node to remove
*/

static
void
prune_and_dispose( DList_type( Prefix ) *list, node_t *node_start, int32_t count )
{
   int32_t i = 0;
   int32_t n = 0;
   node_t *node = node_start;
   node_t *prev = (*node_start).prev;
   node_t *n1 = NULL;
   node_t *ns = NULL;

   // move all cursors off - list will be mangled
   move_all_cursors_off( list );

   // node is first node
   if ( (*node).prev == NULL )
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
   else if ( (*node).next == NULL )
   {
      // set previous node as last
      if ( (*node).prev != NULL )
      {
         (*(*node).prev).next = NULL;
      }
      (*list).last = (*node).prev;

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
      ns = (*node).prev;

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

      if ( node != NULL )
      {
         (*node).prev = prev;
      }

      // (*node).prev may be the last in the list
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
   DList_prune
*/

void
DList_prune( Prefix )( DList_type( Prefix ) *list, int32_t index, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );
   INVARIANT( list );

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
   DList_prune_and_dispose
*/

void
DList_prune_and_dispose( Prefix )( DList_type( Prefix ) *list, int32_t index, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );
   INVARIANT( list );

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
   DList_prune_first
*/

void
DList_prune_first( Prefix )( DList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "count ok", ( (*list).count >= count ) );
   INVARIANT( list );

   node_t *node = (*list).first;

   prune( list, node, count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_prune_first_and_dispose
*/

void
DList_prune_first_and_dispose( Prefix )( DList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "count ok", ( (*list).count >= count ) );
   INVARIANT( list );

   node_t *node = (*list).first;

   prune_and_dispose( list, node, count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_prune_last
*/

void
DList_prune_last( Prefix )( DList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "count ok", ( (*list).count >= count ) );
   INVARIANT( list );

   int32_t i = 0;

   node_t *node = (*list).last;

   for ( i = 1; ( i < count ) && ( node != NULL ); i++ )
   {
      node = (*node).prev;
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
   DList_prune_last_and_dispose
*/

void
DList_prune_last_and_dispose( Prefix )( DList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "count ok", ( (*list).count >= count ) );
   INVARIANT( list );

   int32_t i = 0;

   node_t *node = (*list).last;

   for ( i = 1; ( i < count ) && ( node != NULL ); i++ )
   {
      node = (*node).prev;
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
   DList_keep_first
*/

void
DList_keep_first( Prefix )( DList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "count ok", ( (*list).count >= count ) );
   INVARIANT( list );

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
   DList_keep_first_and_dispose
*/

void
DList_keep_first_and_dispose( Prefix )( DList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "count ok", ( (*list).count >= count ) );
   INVARIANT( list );

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
   DList_keep_last
*/

void
DList_keep_last( Prefix )( DList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "count ok", ( (*list).count >= count ) );
   INVARIANT( list );

   node_t *node = (*list).first;

   prune( list, node, (*list).count - count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_keep_last_and_dispose
*/

void
DList_keep_last_and_dispose( Prefix )( DList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
   LOCK( (*list).mutex );
   PRECONDITION( "count ok", ( (*list).count >= count ) );
   INVARIANT( list );

   node_t *node = (*list).first;

   prune_and_dispose( list, node, (*list).count - count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   DList_wipe_out
*/

void
DList_wipe_out( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
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
   DList_wipe_out_and_dispose
*/

void
DList_wipe_out_and_dispose( Prefix )( DList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
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
   DList_sort
*/

void
DList_sort( Prefix )( DList_type( Prefix ) *list, int32_t (*sort_func)( Type v1, Type v2 ) )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == DLIST_TYPE ) && ( (*list).item_type == Type_Code ) );  
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
      
      // set the sort func
      value_sort_func_name = sort_func;
      
      // sort the array
      qsort( array, (*list).count, sizeof( node_t * ), ( int (*)(const void*,const void*) ) node_sort_func );
      
      // put sorted items into list
      node = array[0];
      (*list).first = node;
      (*node).prev = NULL;
      (*node).next = array[1];
      
      node = (*node).next;
      
      for( i=1; i< (*list).count; i++ )
      {
         (*node).prev = array[i-1];
         
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

