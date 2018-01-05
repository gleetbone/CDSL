/**
 @file AList.c
 @author Greg Lee
 @version 1.0.0
 @brief: "arrayed lists"
 
 @date: "$Mon Jan 01 15:21:40 PST 2018 @15 /Internet Time/$"

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

 Function definitions for the opaque AList_t type.

*/

#include "AList.h"

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

#define ALIST_TYPE 0xA5000100

/**
   Linked list structure
*/

struct AList_struct( Prefix )
{
   
   PROTOCOLS_DEFINITION;

   int32_t type;
   int32_t item_type;
   
   Type *array;
   int32_t capacity;
   int32_t count;
   AList_cursor_type( Prefix ) *first_cursor;
   AList_cursor_type( Prefix ) *last_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Cursor structure. Accesses list and holds a location.
*/

struct AList_cursor_struct( Prefix )
{
   AList_type( Prefix ) *list;
   int32_t index;
   AList_cursor_type( Prefix ) *next_cursor;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};


/**
   move_all_cursors_off

   Move all cursors pointing off.

   @param node the just removed node
*/
static
void
move_all_cursors_off
(
   AList_type( Prefix ) *list
)
{
   AList_cursor_type( Prefix ) *cursor = NULL;

   for 
   ( 
      cursor = (*list).first_cursor;
      cursor != NULL;
      cursor = (*cursor).next_cursor
   )
   {
      (*cursor).index = -1;
   }

   return;
}

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
nonnegative_count( AList_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
capacity_ok( AList_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count <= (*p).capacity );

   return result;
}

static
int32_t
first_cursor_not_null( AList_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).first_cursor != NULL );

   return result;
}

static
int32_t
last_cursor_next_null( AList_type( Prefix ) *p )
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
last_cursor_null_if_one_cursor( AList_type( Prefix ) *p )
{
   int32_t result = 1;

   if ( (*(*p).first_cursor).next_cursor == NULL )
   {
      result = ( (*p).last_cursor == NULL );
   }

   return result;
}

static
void invariant( AList_type( Prefix ) *p )
{
   assert(((void) "nonnegative count", nonnegative_count( p ) ) );
   assert(((void) "capacity ok", capacity_ok( p ) ) );
   assert(((void) "first cursor not null", first_cursor_not_null( p ) ) );
   assert(((void) "last cursor next null", last_cursor_next_null( p ) ) );
   assert(((void) "last cursor null if one cursor", last_cursor_null_if_one_cursor( p ) ) );
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
   AList_dispose( Prefix ),
   AList_dispose_with_contents( Prefix ),
   AList_make_from( Prefix ),
   AList_make_duplicate_from( Prefix )
};

static
void *
p_indexable_table[P_INDEXABLE_FUNCTION_COUNT]
=
{
   AList_dispose( Prefix ),
   AList_dispose_with_contents( Prefix ),
   AList_count( Prefix ),
   AList_item( Prefix ),
   AList_replace( Prefix ),
   AList_replace_and_dispose( Prefix )
};

static
void *
p_iterable_table[P_ITERABLE_FUNCTION_COUNT]
=
{
   AList_dispose( Prefix ),
   AList_dispose_with_contents( Prefix ),
   AList_count( Prefix ),
   AList_item_at( Prefix ),
   AList_off( Prefix ),
   AList_is_empty( Prefix ),
   AList_start( Prefix ),
   AList_forth( Prefix )
};

static
void *
p_diterable_table[P_DITERABLE_FUNCTION_COUNT]
=
{
   AList_dispose( Prefix ),
   AList_dispose_with_contents( Prefix ),
   AList_count( Prefix ),
   AList_item_at( Prefix ),
   AList_off( Prefix ),
   AList_is_empty( Prefix ),
   AList_start( Prefix ),
   AList_forth( Prefix ),
   AList_finish( Prefix ),
   AList_back( Prefix )
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
put_last( AList_type( Prefix ) *list, Type value )
{
   // resize array if we need space
   if ( (*list).count + 1 > (*list).capacity )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( (*list).count + 1 )*sizeof( Type * ) );
      
      // set list capacity
      (*list).capacity = (*list).count + 1;
   
   }
   
   // set new last value
   (*list).array[ (*list).count ] = value;
   
   // increment list count
   (*list).count = (*list).count + 1;
   
   return;
}


/**
   AList_make
*/

AList_type( Prefix ) *
AList_make( Prefix )( void )
{
   // allocate list struct
   AList_type( Prefix ) * list
      = ( AList_type( Prefix ) * ) calloc( 1, sizeof( AList_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( list );

   // set type codes
   (*list).type = ALIST_TYPE;
   (*list).item_type = Type_Code;
   
   // set array
   (*list).array = ( Type * ) realloc( (*list).array, sizeof( Type * ) );

   // set capacity
   (*list).capacity = 1;
   
   // set count
   (*list).count = 0;
   
   // allocate cursor struct
   AList_cursor_type( Prefix ) *cursor
      =  ( AList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AList_cursor_type( Prefix ) ) );

   // set list
   (*cursor).list = list;

   // set index to -1 - cursor is "off"
   (*cursor).index = -1;

   // set list built-in cursor
   (*list).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*list).mutex );

   INVARIANT( list );

   return list;
}

/**
   AList_make_from
*/

AList_type( Prefix ) *
AList_make_from( Prefix )( AList_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == ALIST_TYPE ) && ( (*other).item_type = Type_Code ) );
   
   // allocate list struct
   AList_type( Prefix ) * result
      = ( AList_type( Prefix ) * ) calloc( 1, sizeof( AList_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = ALIST_TYPE;
   (*result).item_type = Type_Code;
   
   // set array
   (*result).array = ( Type * ) realloc( (*result).array, (*other).capacity*sizeof( Type * ) );

   // set capacity
   (*result).capacity = (*other).capacity;
   
   // set count
   (*result).count = (*other).count;
   
   // allocate cursor struct
   AList_cursor_type( Prefix ) *cursor
      =  ( AList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AList_cursor_type( Prefix ) ) );

   // set list
   (*cursor).list = result;

   // set index to -1 - cursor is "off"
   (*cursor).index = -1;

   // set list built-in cursor
   (*result).first_cursor = cursor;

   // lock other
   LOCK( (*other).mutex );

   int32_t i = 0;

   for ( i = 0; i < (*other).count; i++ )
   {
      (*result).array[i] = (*other).array[i];
   }

   // unlock other
   UNLOCK( (*other).mutex );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   AList_make_duplicate_from
*/

AList_type( Prefix ) *
AList_make_duplicate_from( Prefix )( AList_type( Prefix ) *other )
{
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == ALIST_TYPE ) && ( (*other).item_type = Type_Code ) );
   
   // allocate list struct
   AList_type( Prefix ) * result
      = ( AList_type( Prefix ) * ) calloc( 1, sizeof( AList_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = ALIST_TYPE;
   (*result).item_type = Type_Code;
   
   // set array
   (*result).array = ( Type * ) realloc( (*result).array, (*other).capacity*sizeof( Type * ) );

   // set capacity
   (*result).capacity = (*other).capacity;
   
   // set count
   (*result).count = (*other).count;

   // allocate cursor struct
   AList_cursor_type( Prefix ) *cursor
      =  ( AList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AList_cursor_type( Prefix ) ) );

   // set list
   (*cursor).list = result;

   // set index to -1 - cursor is "off"
   (*cursor).index = -1;

   // set list built-in cursor
   (*result).first_cursor = cursor;

   // copy from "list"
   LOCK( (*other).mutex );


   int32_t i = 0;

   for ( i = 0; i < (*other).count; i++ )
   {
      (*result).array[i] = VALUE_DUPLICATE_FUNCTION( (*other).array[i] ); 
   }

   UNLOCK( (*other).mutex );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   AList_make_from_array
*/

AList_type( Prefix ) *
AList_make_from_array( Prefix )( Type *array, int32_t count )
{
   PRECONDITION( "array not null", array != NULL );
   PRECONDITION( "count ok", count >= 0 );
   
   // allocate list struct
   AList_type( Prefix ) * result
      = ( AList_type( Prefix ) * ) calloc( 1, sizeof( AList_type( Prefix ) ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result).type = ALIST_TYPE;
   (*result).item_type = Type_Code;
   
   // set array
   (*result).array = ( Type * ) realloc( (*result).array, ( count + 1 )*sizeof( Type * ) );

   // set capacity
   (*result).capacity = count + 1;
   
   // set count
   (*result).count = count;
   
   // allocate cursor struct
   AList_cursor_type( Prefix ) *cursor
      =  ( AList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AList_cursor_type( Prefix ) ) );

   // set list
   (*cursor).list = result;

   // set index to -1 - cursor is "off"
   (*cursor).index = -1;

   // set list built-in cursor
   (*result).first_cursor = cursor;

   int32_t i = 0;

   for ( i = 0; i < count; i++ )
   {
      (*result).array[i] = array[i];
   }

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   AList_cursor_make
*/

AList_cursor_type( Prefix ) *
AList_cursor_make( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // allocate cursor struct
   AList_cursor_type( Prefix ) *cursor
      =  ( AList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AList_cursor_type( Prefix ) ) );

   // set list
   (*cursor).list = list;

   // set index to -1 - cursor is "off"
   (*cursor).index = -1;

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

   INVARIANT( list );
   POSTCONDITION( "new cursor is last cursor", (*list).last_cursor == cursor );
   UNLOCK( (*list).mutex );

   return cursor;
}

/**
   AList_dispose
*/

void
AList_dispose( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // free array
   free( (*list).array );

   // delete cursors
   AList_cursor_type( Prefix ) *cursor = (*list).first_cursor;
   AList_cursor_type( Prefix ) *next_cursor = NULL;
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
   AList_dispose_with_contents
*/

void
AList_dispose_with_contents( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // delete list items
   int32_t i = 0;
   for( i=0; i<(*list).count; i++ )
   {
      VALUE_DISPOSE_FUNCTION( (*list).array[i] );
   }

   // free array
   free( (*list).array );
   
   // delete cursors
   AList_cursor_type( Prefix ) *cursor = (*list).first_cursor;
   AList_cursor_type( Prefix ) *next_cursor = NULL;
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
   AList_cursor_dispose
*/

void
AList_cursor_dispose( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   AList_cursor_type( Prefix ) *c1 = NULL;
   AList_cursor_type( Prefix ) *c2 = NULL;
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

   INVARIANT( (*c2).list );
   UNLOCK( (*(*c2).list).mutex );

   return;
}


/**
   AList_cursor_item_at
*/

Type
AList_cursor_item_at( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );

   Type value = (*(*cursor).list).array[ (*cursor).index ];

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}


/**
   AList_item_at
*/

Type
AList_item_at( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not off", (*(*list).first_cursor).index != -1 );

   AList_cursor_type( Prefix ) *cursor = (*list).first_cursor;

   Type value = (*(*cursor).list).array[ (*cursor).index ];

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   AList_cursor_item_next
*/

Type
AList_cursor_item_next( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "not off", (*cursor).index != -1 );
   PRECONDITION( "next not off", ( (*cursor).index + 1 ) < (*(*cursor).list).count );

   Type value = (*(*cursor).list).array[ (*cursor).index + 1 ];

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}

/**
   AList_item_next
*/

Type
AList_item_next( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not off", (*(*list).first_cursor).index != -1 );
   PRECONDITION( "next not off", ( (*(*list).first_cursor).index + 1 ) < (*list).count );

   Type value = (*list).array[ (*(*list).first_cursor).index + 1 ];

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   AList_cursor_item_prev
*/

Type
AList_cursor_item_prev( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "not off", (*cursor).index != -1 );
   PRECONDITION( "prev not off", ( (*cursor).index - 1 ) >= 0 );

   Type value = (*(*cursor).list).array[ (*cursor).index - 1 ];

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}

/**
   AList_item_prev
*/

Type
AList_item_prev( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not off", (*(*list).first_cursor).index != -1 );
   PRECONDITION( "prev not off", ( (*(*list).first_cursor).index - 1 ) >= 0 );

   Type value = (*list).array[ (*(*list).first_cursor).index - 1 ];

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   AList_item
*/

Type
AList_item( Prefix )( AList_type( Prefix ) *list, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   Type value = (*list).array[ index ];

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   AList_first
*/

Type
AList_first( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "first not null", (*list).count > 0 );

   Type value = (*list).array[0];

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   AList_last
*/

Type
AList_last( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "last not null", (*list).count > 0 );

   Type value = (*list).array[ (*list).count - 1 ];

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return value;
}

/**
   AList_as_array
*/

Type *
AList_as_array( Prefix )( AList_type( Prefix ) *list, int32_t *count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*list).mutex );
   INVARIANT( list );
   
   int32_t i = 0;
   
   Type *result = ( Type * ) calloc( (*list).count + 1, sizeof( Type ) );

   for ( i=0; i < (*list).count; i++ )
   {
      result[i] = (*list).array[i];
   }
   
   (*count) = (*list).count;
   
   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   AList_count
*/

int32_t
AList_count( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t count = (*list).count;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return count;
}

/**
   AList_off
*/

int32_t
AList_off( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t result = ( (*(*list).first_cursor).index == -1 );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   AList_cursor_off
*/

int32_t
AList_cursor_off( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = ( (*cursor).index == -1 );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AList_is_first
*/

int32_t
AList_is_first( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t result = ( (*(*list).first_cursor).index == 0 );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   AList_cursor_is_first
*/

int32_t
AList_cursor_is_first( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = ( (*cursor).index == 0 );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AList_is_last
*/

int32_t
AList_is_last( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t result = ( (*(*list).first_cursor).index == ( (*list).count - 1 ) );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   AList_cursor_is_last
*/

int32_t
AList_cursor_is_last( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = ( (*cursor).index == ( (*(*cursor).list).count - 1 ) );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AList_index
*/

int32_t
AList_index( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t result = (*(*list).first_cursor).index;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   AList_cursor_index
*/

int32_t
AList_cursor_index( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = (*cursor).index;

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AList_is_empty
*/

int32_t
AList_is_empty( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t result = ( (*list).count ==  0 );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return result;
}

/**
   AList_forth
*/

void
AList_forth( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).index != -1 );

   (*(*list).first_cursor).index = (*(*list).first_cursor).index + 1;

   // check for cursor now "off"
   if ( (*(*list).first_cursor).index >= (*list).count )
   {
      (*(*list).first_cursor).index = -1;
   }
   
   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_cursor_forth
*/

void
AList_cursor_forth( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );

   (*cursor).index = (*cursor).index + 1;

   // check for cursor now "off"
   if ( (*cursor).index >= (*(*cursor).list).count )
   {
      (*cursor).index = -1;
   }
   
   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_back
*/

void
AList_back( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).index != -1 );

   (*(*list).first_cursor).index = (*(*list).first_cursor).index - 1;

   // check for cursor now "off"
   if ( (*(*list).first_cursor).index < 0 )
   {
      (*(*list).first_cursor).index = -1;
   }
   
   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_cursor_back
*/

void
AList_cursor_back( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );

   (*cursor).index = (*cursor).index - 1;

   // check for cursor now "off"
   if ( (*cursor).index < 0 )
   {
      (*cursor).index = -1;
   }
   
   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_back
*/

void
AList_go( Prefix )( AList_type( Prefix ) *list, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   (*(*list).first_cursor).index = index;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_cursor_go
*/

void
AList_cursor_go( Prefix )( AList_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*(*cursor).list).count ) ) );

   (*cursor).index = index;

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_start
*/

void
AList_start( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   if ( (*list).count > 0 )
   {
      (*(*list).first_cursor).index = 0;
   }
   else
   {
      (*(*list).first_cursor).index = -1;
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_cursor_start
*/

void
AList_cursor_start( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   if ( (*(*cursor).list).count > 0 )
   {
      (*cursor).index = 0;
   }
   else
   {
      (*cursor).index = -1;
   }

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_finish
*/

void
AList_finish( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   if ( (*list).count > 0 )
   {
      (*(*list).first_cursor).index = (*list).count - 1;
   }
   else
   {
      (*(*list).first_cursor).index = -1;
   }

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_cursor_finish
*/

void
AList_cursor_finish( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   if ( (*(*cursor).list).count > 0 )
   {
      (*cursor).index = (*(*cursor).list).count - 1;
   }
   else
   {
      (*cursor).index = -1;
   }

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_put
*/

void
AList_put( Prefix )( AList_type( Prefix ) *list, Type value, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*list).count ) ) );

   // handle list growth if required
   if ( (*list).count + 1 > (*list).capacity )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( (*list).count + 1 )*sizeof( Type * ) );
      
      // set list capacity
      (*list).capacity = (*list).count + 1;
   
   }
   
   // see if we're adding to last of list
   if ( index == (*list).count )
   {
      (*list).array[index] = value;
      (*list).count = (*list).count + 1;
   }
   else
   {
      // otherwise, move array entries to right to make room for new value at index
      int32_t i = 0;
      Type *array = (*list).array;
      
      for( i=(*list).count; i>index; i-- )
      {
         array[i] = array[i-1];
      }
      
      array[index] = value;
      (*list).count = (*list).count + 1;
   }
   
   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_put_right
*/

void
AList_put_right( Prefix )( AList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).index != -1 );

   // handle list growth if required
   if ( (*list).count + 1 > (*list).capacity )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( (*list).count + 1 )*sizeof( Type * ) );
      
      // set list capacity
      (*list).capacity = (*list).count + 1;
   
   }
   
   int32_t index = (*(*list).first_cursor).index + 1;
   
   // see if we're adding to last of list
   if ( index == (*list).count )
   {
      (*list).array[index] = value;
      (*list).count = (*list).count + 1;
   }
   else
   {
      // otherwise, move array entries to right to make room for new value at index
      int32_t i = 0;
      Type *array = (*list).array;
      
      for( i=(*list).count; i>index; i-- )
      {
         array[i] = array[i-1];
      }
      
      // set new entry
      array[index] = value;
      
      // increment list count
      (*list).count = (*list).count + 1;
   }
   
   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_cursor_put_right
*/

void
AList_cursor_put_right( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );

   AList_type( Prefix ) *list = (*cursor).list;
   
   // handle list growth if required
   if ( (*list).count + 1 > (*(*cursor).list).capacity )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( (*list).count + 1 )*sizeof( Type * ) );
      
      // set list capacity
      (*list).capacity = (*list).count + 1;
   
   }
   
   int32_t index = (*cursor).index + 1;
   
   // see if we're adding to last of list
   if ( index == (*list).count )
   {
      (*list).array[index] = value;
      (*list).count = (*list).count + 1;
   }
   else
   {
      // otherwise, move array entries to right to make room for new value at index
      int32_t i = 0;
      Type *array = (*list).array;
      
      for( i=(*list).count; i>index; i-- )
      {
         array[i] = array[i-1];
      }
      
      // set new entry
      array[index] = value;
      
      // increment list count
      (*list).count = (*list).count + 1;
   }
   
   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_put_left
*/

void
AList_put_left( Prefix )( AList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).index != -1 );

   // handle list growth if required
   if ( (*list).count + 1 > (*list).capacity )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( (*list).count + 1 )*sizeof( Type * ) );
      
      // set list capacity
      (*list).capacity = (*list).count + 1;
   
   }
   
   int32_t index = (*(*list).first_cursor).index;
   
   // move array entries to right to make room for new value at index - 1
   int32_t i = 0;
   Type *array = (*list).array;
   
   for( i=(*list).count; i>index; i-- )
   {
      array[i] = array[i-1];
   }
   
   // set new entry
   array[index] = value;
   
   // increment list count
   (*list).count = (*list).count + 1;
  
   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_cursor_put_left
*/

void
AList_cursor_put_left( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );

   AList_type( Prefix ) *list = (*cursor).list;

   // handle list growth if required
   if ( (*list).count + 1 > (*list).capacity )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( (*list).count + 1 )*sizeof( Type * ) );
      
      // set list capacity
      (*list).capacity = (*list).count + 1;
   
   }
   
   int32_t index = (*cursor).index;
   
   // move array entries to right to make room for new value at index - 1
   int32_t i = 0;
   Type *array = (*list).array;
   
   for( i=(*list).count; i>index; i-- )
   {
      array[i] = array[i-1];
   }
   
   // set new entry
   array[index] = value;
   
   // increment list count
   (*list).count = (*list).count + 1;
   
   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_put_first
*/

void
AList_put_first( Prefix )( AList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // handle list growth if required
   if ( (*list).count + 1 > (*list).capacity )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( (*list).count + 1 )*sizeof( Type * ) );
      
      // set list capacity
      (*list).capacity = (*list).count + 1;
   
   }
   
   int32_t index = 0;
   
   // move array entries to right to make room for new value at index
   int32_t i = 0;
   Type *array = (*list).array;
   
   for( i=(*list).count; i>index; i-- )
   {
      array[i] = array[i-1];
   }
   
   // set new entry
   array[index] = value;
   
   // increment list count
   (*list).count = (*list).count + 1;
  
   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_put_last
*/

void
AList_put_last( Prefix )( AList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
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

   @param list a AList_t instance
   @param other a AList_t instance to append/insert into list
   @param index the index after which to append/insert the list
*/

static
void
append( AList_type( Prefix ) *list, AList_type( Prefix ) *other, int32_t index )
{
   // handle list growth if required
   if ( (*list).count + (*other).count > (*list).capacity )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( (*list).count + (*other).count )*sizeof( Type * ) );
      
      // set list capacity
      (*list).capacity = (*list).count + (*other).count;
   
   }
   
   int32_t i = 0;
   
   // see if we're appending to last of list
   if ( index == (*list).count )
   {
      for( i=0; i<(*other).count; i++ )
      {
         (*list).array[ (*list).count + i ] = (*other).array[i];
      }
      
      // update list count
      (*list).count = (*list).count + (*other).count;
   }
   else
   {
      // otherwise, move array entries to right to make room for new values at index
      int32_t i = 0;
      Type *array = (*list).array;
      
      for( i=(*list).count; i>index; i-- )
      {
         array[ (*other).count + i - 1 ] = array[i-1];
      }
      
      // and copy entries of other into the new space
      for( i=0; i<(*other).count; i++ )
      {
         array[ index + i ] = (*other).array[i];
      }
      
      // update list count
      (*list).count = (*list).count + (*other).count;
   }
   
   return;
}

/**
   AList_append
*/

void
AList_append( Prefix )( AList_type( Prefix ) *list, AList_type( Prefix ) *other, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == ALIST_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*list).count ) ) );

   // lock other
   LOCK( (*other).mutex );

   // append other to list
   append( list, other, index );
   
   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_append_right
*/

void
AList_append_right( Prefix )( AList_type( Prefix ) *list, AList_type( Prefix ) *other )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == ALIST_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // lock other
   LOCK( (*other).mutex );

   int32_t index = 0;
   
   if ( (*list).count == 0 )
   {
      index = 0;
   }
   else
   {
      index = (*(*list).first_cursor).index + 1;
   }
   
   // append other to list
   append( list, other, index );
   
   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_cursor_append_right
*/

void
AList_cursor_append_right( Prefix )( AList_cursor_type( Prefix ) *cursor, AList_type( Prefix ) *other )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   PRECONDITION( "list not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == ALIST_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   // lock other
   LOCK( (*other).mutex );

   int32_t index = 0;
   
   if ( (*(*cursor).list).count == 0 )
   {
      index = 0;
   }
   else
   {
      index = (*cursor).index + 1;
   }
   
   // append other to list
   append( (*cursor).list, other, index );
   
   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_append_left
*/

void
AList_append_left( Prefix )( AList_type( Prefix ) *list, AList_type( Prefix ) *other )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == ALIST_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // lock other
   LOCK( (*other).mutex );

   int32_t index = 0;
   
   if ( (*list).count == 0 )
   {
      index = 0;
   }
   else
   {
      index = (*(*list).first_cursor).index;
   }
   
   // append other to list
   append( list, other, index );
   
   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_cursor_append_left
*/

void
AList_cursor_append_left( Prefix )( AList_cursor_type( Prefix ) *cursor, AList_type( Prefix ) *other )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == ALIST_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );

   // lock other
   LOCK( (*other).mutex );

   int32_t index = 0;
   
   if ( (*(*cursor).list).count == 0 )
   {
      index = 0;
   }
   else
   {
      index = (*cursor).index;
   }
   
   // append other to list
   append( (*cursor).list, other, index );
   
   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_append_first
*/

void
AList_append_first( Prefix )( AList_type( Prefix ) *list, AList_type( Prefix ) *other )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == ALIST_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // lock other
   LOCK( (*other).mutex );

   // append other to list
   append( list, other, 0 );
   
   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_append_last
*/

void
AList_append_last( Prefix )( AList_type( Prefix ) *list, AList_type( Prefix ) *other )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == ALIST_TYPE ) && ( (*other).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // lock other
   LOCK( (*other).mutex );

   // append other to list
   append( list, other, (*list).count );
   
   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_replace
*/

void
AList_replace( Prefix )( AList_type( Prefix ) *list, Type value, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   LOCK( (*list).mutex );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   (*list).array[index] = value;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_replace_and_dispose
*/

void
AList_replace_and_dispose( Prefix )( AList_type( Prefix ) *list, Type value, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   VALUE_DISPOSE_FUNCTION( (*list).array[index] );
   (*list).array[index] = value;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_replace_at
*/

void
AList_replace_at( Prefix )( AList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).index != -1 );

   (*list).array[ (*(*list).first_cursor).index ] = value;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_replace_at_and_dispose
*/

void
AList_replace_at_and_dispose( Prefix )( AList_type( Prefix ) *list, Type value )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).index != -1 );

   VALUE_DISPOSE_FUNCTION( (*list).array[index] );
   (*list).array[ (*(*list).first_cursor).index ] = value;

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_cursor_replace_at
*/

void
AList_cursor_replace_at( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );

   (*(*cursor).list).array[ (*cursor).index ] = value;

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_cursor_replace_at_and_dispose
*/

void
AList_cursor_replace_at_and_dispose( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );

   VALUE_DISPOSE_FUNCTION( (*(*(*cursor).list).array[ (*cursor).index ] ) );
   (*(*cursor).list).array[ (*cursor).index ] = value;

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   remove

   Helper function to remove an item from a list

   @param list a AList_t instance
   @param index the index to remove
*/

static
void
remove( AList_type( Prefix ) *list, int32_t index )
{
   // see if we're removing from last of list
   if ( index == ( (*list).count - 1 ) )
   {
      (*list).count = (*list).count - 1;
   }
   else
   {
      // otherwise, move array entries to left to overwrite value at index
      int32_t i = 0;
      Type *array = (*list).array;
      
      for( i=index + 1; i<(*list).count; i++ )
      {
         array[i-1] = array[i];
      }
      
      (*list).count = (*list).count - 1;
   }
   
   // handle list reduction if required
   if ( (*list).count < (*list).capacity/2 )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( (*list).count )*sizeof( Type * ) );
      
      // set list capacity
      (*list).capacity = (*list).count;
   
   }
   
   return;
}

/**
   remove_and_dispose

   Helper function to remove an item from a list and dispose of its value

   @param list a AList_t instance
   @param index the index to remove
*/

static
void
remove_and_dispose( AList_type( Prefix ) *list, int32_t index )
{
   // see if we're removing from last of list
   if ( index == ( (*list).count - 1 ) )
   {
      VALUE_DISPOSE_FUNCTION( (*list).array[index] );
      (*list).count = (*list).count - 1;
   }
   else
   {
      // otherwise, move array entries to left to overwrite value at index
      int32_t i = 0;
      Type *array = (*list).array;
      
      VALUE_DISPOSE_FUNCTION( (*list).array[index] );
      
      for( i=index + 1; i<(*list).count; i++ )
      {
         array[i-1] = array[i];
      }
      
      (*list).count = (*list).count - 1;
   }
   
   // handle list reduction if required
   if ( (*list).count < (*list).capacity/2 )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( (*list).count )*sizeof( Type * ) );
      
      // set list capacity
      (*list).capacity = (*list).count;
   
   }
   
   return;
}

/**
   AList_remove
*/

void
AList_remove( Prefix )( AList_type( Prefix ) *list, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   // remove 
   remove( list, index );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_remove_and_dispose
*/

void
AList_remove_and_dispose( Prefix )( AList_type( Prefix ) *list, int32_t index )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   // remove
   remove_and_dispose( list, index );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_remove_at
*/

void
AList_remove_at( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).index != -1 );
   
   // remove 
   remove( list, (*(*list).first_cursor).index );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_remove_at_and_dispose
*/

void
AList_remove_at_and_dispose( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "list not off", (*(*list).first_cursor).index != -1 );

   // remove 
   remove_and_dispose( list, (*(*list).first_cursor).index );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_cursor_remove_at
*/

void
AList_cursor_remove_at( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );

   // remove
   remove( (*cursor).list, (*cursor).index );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_cursor_remove_at_and_dispose
*/

void
AList_cursor_remove_at_and_dispose( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( (*(*cursor).list).type == ALIST_TYPE ) && ( (*(*cursor).list).item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( (*(*cursor).list).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );

   // remove
   remove_and_dispose( (*cursor).list, (*cursor).index );

   INVARIANT( (*cursor).list );
   UNLOCK( (*(*cursor).list).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_remove_first
*/

void
AList_remove_first( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not empty", ( (*list).count > 0 ) );

   // remove
   remove( list, 0 );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_remove_first_and_dispose
*/

void
AList_remove_first_and_dispose( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not empty", ( (*list).count > 0 ) );

   // remove
   remove_and_dispose( list, 0 );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_remove_last
*/

void
AList_remove_last( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not empty", ( (*list).count > 0 ) );

   // remove
   remove( list, (*list).count - 1 );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_remove_last_and_dispose
*/

void
AList_remove_last_and_dispose( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "not empty", ( (*list).count > 0 ) );

   // remove
   remove_and_dispose( list, (*list).count - 1 );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   prune

   Helper function to remove a sublist out of a list

   @param list a AList_t instance
   @param index the start index to remove
   @param count the number of entries to remove
*/

static
void
prune( AList_type( Prefix ) *list, int32_t index, int32_t count )
{
   // move all cursors off - list will be mangled
   move_all_cursors_off( list );

   // see if we're removing from last of list
   if ( index + count == ( (*list).count ) )
   {
      (*list).count = (*list).count - count;
   }
   else
   {
      // otherwise, move array entries to left to overwrite values at index
      int32_t i = 0;
      Type *array = (*list).array;
      
      for( i=0; i<(*list).count - count; i++ )
      {
         array[index + i] = array[index + i + count];
      }
      
      (*list).count = (*list).count - count;
   }
   
   // handle list reduction if required
   if ( (*list).count < (*list).capacity/2 )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( (*list).count )*sizeof( Type * ) );
      
      // set list capacity
      (*list).capacity = (*list).count;
   
   }
   
   return;
}

/**
   prune_and_dispose

   Helper function to remove a sublist out of a list and dispose of its
   values.

   @param list a AList_t instance
   @param index the start index to remove
   @param count the number of entries to remove
*/

static
void
prune_and_dispose( AList_type( Prefix ) *list, int32_t index, int32_t count )
{
   // move all cursors off - list will be mangled
   move_all_cursors_off( list );

   // see if we're removing from last of list
   if ( index + count == ( (*list).count ) )
   {
      // if so, dispose of the entries and adjust the list count
      int32_t i = 0;
      for( i=index; i < index + count; i++ )
      {
         VALUE_DISPOSE_FUNCTION( (*list).array[i] );
      }
      (*list).count = (*list).count - count;
   }
   else
   {
      // otherwise, move array entries to left to overwrite values at index
      int32_t i = 0;
      Type *array = (*list).array;
      
      // dispose of entries
      for( i=index; i < index + count; i++ )
      {
         VALUE_DISPOSE_FUNCTION( array[i] );
      }
      
      // move entries
      for( i=0; i<(*list).count - count; i++ )
      {
         array[index + i] = array[index + i + count];
      }
      
      (*list).count = (*list).count - count;
   }
   
   // handle list reduction if required
   if ( (*list).count < (*list).capacity/2 )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( (*list).count )*sizeof( Type * ) );
      
      // set list capacity
      (*list).capacity = (*list).count;
   
   }
   
   return;
}


/**
   AList_prune
*/

void
AList_prune( Prefix )( AList_type( Prefix ) *list, int32_t index, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   prune( list, index, count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_prune_and_dispose
*/

void
AList_prune_and_dispose( Prefix )( AList_type( Prefix ) *list, int32_t index, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*list).count ) ) );

   prune_and_dispose( list, index, count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_prune_first
*/

void
AList_prune_first( Prefix )( AList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   prune( list, 0, count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_prune_first_and_dispose
*/

void
AList_prune_first_and_dispose( Prefix )( AList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   prune_and_dispose( list, 0, count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_prune_last
*/

void
AList_prune_last( Prefix )( AList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   prune( list, (*list).count - count , count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_prune_last_and_dispose
*/

void
AList_prune_last_and_dispose( Prefix )( AList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   prune_and_dispose( list, (*list).count - count, count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_keep_first
*/

void
AList_keep_first( Prefix )( AList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   prune( list, count, (*list).count - count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_keep_first_and_dispose
*/

void
AList_keep_first_and_dispose( Prefix )( AList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   prune_and_dispose( list, count, (*list).count - count );
 
   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_keep_last
*/

void
AList_keep_last( Prefix )( AList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   prune( list, 0, (*list).count - count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_keep_last_and_dispose
*/

void
AList_keep_last_and_dispose( Prefix )( AList_type( Prefix ) *list, int32_t count )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );
   PRECONDITION( "count ok", ( (*list).count >= count ) );

   prune_and_dispose( list, 0, (*list).count - count );

   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_wipe_out
*/

void
AList_wipe_out( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // move all cursors off - list will be mangled
   move_all_cursors_off( list );

   (*list).count = 0;

   // handle list reduction if required - at least capacity of 1
   if ( 1 < (*list).capacity/2 )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( 1 )*sizeof( Type * ) );
      
      // set list capacity
      (*list).capacity = 1;
   
   }
   
   INVARIANT( list );
   POSTCONDITION( "list is empty", (*list).count == 0 );
   UNLOCK( (*list).mutex );

   return;
}

/**
   AList_wipe_out_and_dispose
*/

void
AList_wipe_out_and_dispose( Prefix )( AList_type( Prefix ) *list )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   LOCK( (*list).mutex );
   INVARIANT( list );

   int32_t i = 0;
   
   // move all cursors off - list will be mangled
   move_all_cursors_off( list );

   // remove all nodes
   for ( i=0; i<(*list).count; i++ )
   {
      VALUE_DISPOSE_FUNCTION( (*list).array[i] );
   }
   
   (*list).count = 0;

   // handle list reduction if required - at least capacity of 1
   if ( 1 < (*list).capacity/2 )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( 1 )*sizeof( Type * ) );
      
      // set list capacity
      (*list).capacity = 1;
   
   }
   

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
   value_sort_func
   
   compare value according to value_sort_func
*/

static
int32_t
value_sort_func( Type *v1, Type *v2 )
{
   int32_t result = value_sort_func_name( (*v1), (*v2) );
   return result;
}

/**
   AList_sort
*/

void
AList_sort( Prefix )( AList_type( Prefix ) *list, int32_t (*sort_func)( Type v1, Type v2 ) )
{
   PRECONDITION( "list not null", list != NULL );
   PRECONDITION( "list type ok", ( (*list).type == ALIST_TYPE ) && ( (*list).item_type = Type_Code ) );
   PRECONDITION( "sort_func not null", sort_func != NULL );
   LOCK( (*list).mutex );
   INVARIANT( list );

   // array to use for sorting
   Type *array = NULL;
   
   // only sort if there's enough to sort
   if ( (*list).count > 1 )
   {
      array = (*list).array;
      
      // set the sort func
      value_sort_func_name = sort_func;
      
      // sort the array
      qsort( array, (*list).count, sizeof( Type ), ( int (*)(const void*,const void*) ) value_sort_func );
      
      // reset cursors
      move_all_cursors_off( list );
      
   }
   
   INVARIANT( list );
   UNLOCK( (*list).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

