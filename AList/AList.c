/**
 @file AList.c
 @author Greg Lee
 @version 2.0.0
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

#include "protocol.h"

#ifdef PROTOCOLS_ENABLED

#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_Indexable.ph"
#include "P_Iterable.ph"
#include "P_DIterable.ph"

#endif // PROTOCOLS_ENABLED

// take care of undefined prototypes

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
   Linked list structure
*/

struct AList_struct( Prefix )
{

   PROTOCOLS_DEFINITION;

   int32_t _type;
   int32_t _item_type;

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
   compare list items4 to array items

   compare each item to corresponding item in an array

   @param list the list to compare to
   @param array the array to compare to the list
   @return 1 if equal, 0 otherwise
*/

static
int32_t
compare_list_items_to_array_items
(
   AList_type( Prefix ) *list,
   Type *array,
   int32_t count
)
{
   int32_t result = 0;
   int32_t flag = 0;
   int32_t i = 0;

   for( i = 0; ( ( i < count ) && ( i < (*list).count ) ); i++ )
   {
      if ( (*list).array[i] == array[i] )
      {
         flag = flag + 1;
      }
   }

   if ( ( flag == (*list).count ) && ( flag == count ) )
   {
      result = 1;
   }

   return result;
}

/**
   compare list items to list items

   compare each item to corresponding item in another list

   @param list the list to compare to
   @param list1 the array to compare to the list
   @return 1 if equal, 0 otherwise
*/

static
int32_t
compare_list_items_to_list_items
(
   AList_type( Prefix ) *list,
   AList_type( Prefix ) *list1
)
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t i = 0;

   for( i = 0; ( ( i < (*list).count ) && ( i < (*list1).count ) ); i++ )
   {
      if ( (*list).array[i] == (*list1).array[i] )
      {
         flag = flag + 1;
      }
   }

   if ( ( flag == (*list).count ) && ( flag == (*list1).count ) )
   {
      result = 1;
   }

   return result;
}

/**
   compare list items to list items deep equal

   compare each item to corresponding item in another list

   @param list the list to compare to
   @param list1 the array to compare to the list
   @return 1 if deep equal, 0 otherwise
*/

static
int32_t
compare_list_items_to_list_items_deep_equal
(
   AList_type( Prefix ) *list,
   AList_type( Prefix ) *list1
)
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t i = 0;

   for( i = 0; ( ( i < (*list).count ) && ( i < (*list1).count ) ); i++ )
   {
      if ( VALUE_DEEP_EQUAL_FUNCTION( (*list).array[i], (*list1).array[i] ) == 1 )
      {
         flag = flag + 1;
      }
   }

   if ( ( flag == (*list).count ) && ( flag == (*list1).count ) )
   {
      result = 1;
   }

   return result;
}

/**
   compare list in list

   compare each item to corresponding item in another list
   starting at a particular index

   @param list the list to compare to
   @param list1 the array to compare to the list
   @param index the starting index to compare
   @return 1 if equal, 0 otherwise
*/

static
int32_t
compare_list_in_list
(
   AList_type( Prefix ) *list,
   AList_type( Prefix ) *list1,
   int32_t index
)
{
   int32_t result = 1;
   int32_t flag = 0;
   int32_t i = 0;
   int32_t i_start = 0;

   if ( index >= 0 )
   {
      i_start = index;
   }
   else
   {
      i_start = 0;
   }

   for( i = i_start; ( ( i < (*list1).count + i_start ) && ( i < (*list).count ) ); i++ )
   {
      if ( (*list).array[i] == (*list1).array[i - i_start] )
      {
         flag = flag + 1;
      }
   }

   if ( flag == (*list1).count )
   {
      result = 1;
   }

   return result;
}

/**
   move_all_cursors_off

   Move all cursors to point off.

   @param current the AList
*/
static
void
move_all_cursors_off
(
   AList_type( Prefix ) *current
)
{
   AList_cursor_type( Prefix ) *cursor = NULL;

   for
   (
      cursor = (*current).first_cursor;
      cursor != NULL;
      cursor = (*cursor).next_cursor
   )
   {
      (*cursor).index = -1;
   }

   return;
}

/**
   has

   Returns 1 if AList contains item using "==" as comparison test

   @param current the AList
   @param item the item to look for
*/
static
int32_t
has
(
   AList_type( Prefix ) *current,
   Type value
)
{
   int32_t result = 0;
   int32_t index = 0;
   Type *array = NULL;
   int32_t count = 0;

   array = (*current).array;
   count = (*current).count;

   for( index = 0; index < count; index++ )
   {
      if ( array[index] == value )
      {
         result = 1;
         break;
      }
   }

   return result;
}

/**
   has_eq_fn

   Returns 1 if AList contains item using equality_test_func as comparison test

   @param current the AList
   @param value the value to look for
   @param equality_test_func the function to compare values with
   @return 1 if found, 0 otherwise
*/
static
int32_t
has_eq_fn
(
   AList_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   int32_t result = 0;
   int32_t index = 0;
   Type *array = NULL;
   int32_t count = 0;

   array = (*current).array;
   count = (*current).count;

   for( index = 0; index < count; index++ )
   {
      if ( equality_test_func( array[index], value ) == 1 )
      {
         result = 1;
         break;
      }
   }

   return result;
}

/**
   occurrences

   compare each item to value, count equal items

   @param current the list to compare to
   @param value what to look for
   @return count of equal items found, can be 0
*/

static
int32_t
occurrences( AList_type( Prefix ) *current, Type value )
{
   int32_t result = 0;
   int32_t index = 0;
   Type *array = NULL;
   int32_t count = 0;

   array = (*current).array;
   count = (*current).count;

   for( index = 0; index < count; index++ )
   {
      if ( array[index] == value )
      {
         result = result + 1;
      }
   }

   return result;
}

/**
   occurrences_eq_fn

   compare each item to value, count equal items
   comparison function is specified

   @param current the list to compare to
   @param value what to look for
   @param equality_test_func the function to check equality with value
   @return count of equal items found, can be 0
*/

static
int32_t
occurrences_eq_fn
(
   AList_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   int32_t result = 0;
   int32_t index = 0;
   Type *array = NULL;
   int32_t count = 0;

   array = (*current).array;
   count = (*current).count;

   for( index = 0; index < count; index++ )
   {
      if ( equality_test_func( array[index], value ) == 1 )
      {
         result = result + 1;
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
nonnegative_count( AList_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).count >= 0 );

   return result;
}

static
int32_t
capacity_ok( AList_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).count <= (*current).capacity );

   return result;
}

static
int32_t
first_cursor_not_null( AList_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).first_cursor != NULL );

   return result;
}

static
int32_t
last_cursor_next_null( AList_type( Prefix ) *current )
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
last_cursor_null_if_one_cursor( AList_type( Prefix ) *current )
{
   int32_t result = 1;

   if ( ( *(*current).first_cursor ).next_cursor == NULL )
   {
      result = ( (*current).last_cursor == NULL );
   }

   return result;
}

static
void invariant( AList_type( Prefix ) *current )
{
   assert( ( ( void ) "nonnegative count", nonnegative_count( current ) ) );
   assert( ( ( void ) "capacity ok", capacity_ok( current ) ) );
   assert( ( ( void ) "first cursor not null", first_cursor_not_null( current ) ) );
   assert( ( ( void ) "last cursor next null", last_cursor_next_null( current ) ) );
   assert( ( ( void ) "last cursor null if one cursor", last_cursor_null_if_one_cursor( current ) ) );
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
   AList_dispose( Prefix ),
   AList_deep_dispose( Prefix ),
   AList_is_equal( Prefix ),
   AList_is_deep_equal( Prefix ),
   AList_copy( Prefix ),
   AList_deep_copy( Prefix ),
   AList_clone( Prefix ),
   AList_deep_clone( Prefix )
};

static
void *
p_indexable_table[P_INDEXABLE_FUNCTION_COUNT]
=
{
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

   static file level function without assertions - puts a value at the end of the list

   @param current the list
   @param value the value to add to the list
*/

static
void
put_last( AList_type( Prefix ) *current, Type value )
{
   // resize array if we need space
   if ( (*current).count + 1 > (*current).capacity )
   {
      (*current).array = ( Type * ) realloc( (*current).array, ( (*current).count + 1 ) * sizeof( Type ) );
      CHECK( "(*current).array reallocated correctly", (*current).array != NULL );

      // set current capacity
      (*current).capacity = (*current).count + 1;

   }

   // set new last value
   (*current).array[ (*current).count ] = value;

   // increment current count
   (*current).count = (*current).count + 1;

   return;
}


/**
   AList_make
*/

AList_type( Prefix ) *
AList_make( Prefix )( void )
{
   // allocate result struct
   AList_type( Prefix ) * result
      = ( AList_type( Prefix ) * ) calloc( 1, sizeof( AList_type( Prefix ) ) );
   CHECK( "result allocated_correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = ALIST_TYPE;
   (*result)._item_type = Type_Code;

   // set array
   (*result).array = ( Type * ) realloc( (*result).array, sizeof( Type ) );
   CHECK( "(*result).array reallocated correctly", (*result).array != NULL );

   // set capacity
   (*result).capacity = 1;

   // set count
   (*result).count = 0;

   // allocate cursor struct
   AList_cursor_type( Prefix ) *cursor
      =  ( AList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AList_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated_correctly", cursor != NULL );

   // set result
   (*cursor).list = result;

   // set index to -1 - cursor is "off"
   (*cursor).index = -1;

   // set result built-in cursor
   (*result).first_cursor = cursor;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new result is empty", (*result).count == 0 );
   POSTCONDITION( "new result cursor is off", ( *(*result).first_cursor ).index == -1 );

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

   // allocate result struct
   AList_type( Prefix ) * result
      = ( AList_type( Prefix ) * ) calloc( 1, sizeof( AList_type( Prefix ) ) );
   CHECK( "result allocated_correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = ALIST_TYPE;
   (*result)._item_type = Type_Code;

   // set array
   (*result).array = ( Type * ) realloc( (*result).array, ( count + 1 ) * sizeof( Type ) );
   CHECK( "(*result).array reallocated correctly", (*result).array != NULL );

   // set capacity
   (*result).capacity = count + 1;

   // set count
   (*result).count = count;

   // allocate cursor struct
   AList_cursor_type( Prefix ) *cursor
      =  ( AList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AList_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated_correctly", cursor != NULL );

   // set result
   (*cursor).list = result;

   // set index to -1 - cursor is "off"
   (*cursor).index = -1;

   // set result built-in cursor
   (*result).first_cursor = cursor;

   int32_t i = 0;

   for ( i = 0; i < count; i++ )
   {
      (*result).array[i] = array[i];
   }

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new result cursor is off", ( *(*result).first_cursor ).index == -1 );
   POSTCONDITION( "new result contains elements of array", compare_list_items_to_array_items( result, array, count ) );

   INVARIANT( result );

   return result;
}

/**
   AList_clone
*/

AList_type( Prefix ) *
AList_clone( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );

   // lock current
   LOCK( (*current).mutex );

   int32_t i = 0;

   // allocate list struct
   AList_type( Prefix ) * result
      = ( AList_type( Prefix ) * ) calloc( 1, sizeof( AList_type( Prefix ) ) );
   CHECK( "result allocated_correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = ALIST_TYPE;
   (*result)._item_type = Type_Code;

   // set array
   (*result).array = ( Type * ) realloc( (*result).array, (*current).capacity * sizeof( Type ) );
   CHECK( "(*result).array reallocated correctly", (*result).array != NULL );

   // set capacity
   (*result).capacity = (*current).capacity;

   // set count
   (*result).count = (*current).count;

   // allocate cursor struct
   AList_cursor_type( Prefix ) *cursor
      =  ( AList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AList_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated_correctly", cursor != NULL );

   // set list
   (*cursor).list = result;

   // set index to -1 - cursor is "off"
   (*cursor).index = -1;

   // set list built-in cursor
   (*result).first_cursor = cursor;

   for ( i = 0; i < (*current).count; i++ )
   {
      (*result).array[i] = (*current).array[i];
   }

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new list cursor is off", ( *(*result).first_cursor ).index == -1 );
   POSTCONDITION( "new list contains elements of current", compare_list_items_to_list_items( result, current ) );

   INVARIANT( result );
   INVARIANT( current );

   // unlock current
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AList_deep_clone
*/

AList_type( Prefix ) *
AList_deep_clone( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );

   // lock mutex
   LOCK( (*current).mutex );

   int32_t i = 0;

   // allocate list struct
   AList_type( Prefix ) * result
      = ( AList_type( Prefix ) * ) calloc( 1, sizeof( AList_type( Prefix ) ) );
   CHECK( "result allocated_correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = ALIST_TYPE;
   (*result)._item_type = Type_Code;

   // set array
   (*result).array = ( Type * ) realloc( (*result).array, (*current).capacity * sizeof( Type ) );
   CHECK( "(*result).array reallocated correctly", (*result).array != NULL );

   // set capacity
   (*result).capacity = (*current).capacity;

   // set count
   (*result).count = (*current).count;

   // allocate cursor struct
   AList_cursor_type( Prefix ) *cursor
      =  ( AList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AList_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated_correctly", cursor != NULL );

   // set list
   (*cursor).list = result;

   // set index to -1 - cursor is "off"
   (*cursor).index = -1;

   // set list built-in cursor
   (*result).first_cursor = cursor;

   for ( i = 0; i < (*current).count; i++ )
   {
      (*result).array[i] = VALUE_DEEP_CLONE_FUNCTION( (*current).array[i] );
   }

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "new list cursor is off", ( *(*result).first_cursor ).index == -1 );
   POSTCONDITION( "new list contains elements deep equal to current", compare_list_items_to_list_items_deep_equal( result, current ) );

   INVARIANT( result );
   INVARIANT( current );

   UNLOCK( (*current).mutex );

   return result;
}

/**
   AList_is_equal
*/

int32_t
AList_is_equal( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == ALIST_TYPE ) && ( (*other)._item_type = Type_Code ) );

   // lock mutex
   LOCK( (*current).mutex );

   INVARIANT( current );

   int32_t result = 1;
   int32_t i = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other mutex
      LOCK( (*other).mutex );

      // check count
      if ( (*current).count != (*other).count )
      {
         result = 0;
      }

      for ( i = 0; i < (*other).count; i++ )
      {
         if ( result == 1 )
         {
            if ( (*current).array[i] != (*other).array[i] )
            {
               result = 0;
               break;
            }
         }
         else
         {
            break;
         }
      }

      // unlock other mutex
      UNLOCK( (*other).mutex );

      INVARIANT( current );
   }

   UNLOCK( (*current).mutex );

   return result;
}

/**
   AList_is_deep_equal
*/

int32_t
AList_is_deep_equal( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == ALIST_TYPE ) && ( (*other)._item_type = Type_Code ) );

   // lock mutex
   LOCK( (*current).mutex );

   INVARIANT( current );

   int32_t result = 1;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other mutex
      LOCK( (*other).mutex );

      // check count
      if ( (*current).count != (*other).count )
      {
         result = 0;
      }

      int32_t i = 0;

      for ( i = 0; i < (*other).count; i++ )
      {
         if ( result == 1 )
         {
            if ( VALUE_DEEP_EQUAL_FUNCTION( (*current).array[i], (*other).array[i] ) == 0 )
            {
               result = 0;
               break;
            }
         }
         else
         {
            break;
         }
      }

      // unlock other mutex
      UNLOCK( (*other).mutex );

      INVARIANT( current );
   }

   // unlock mutex
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AList_copy
*/

void
AList_copy( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == ALIST_TYPE ) && ( (*other)._item_type = Type_Code ) );
   INVARIANT( current );

   // lock current
   LOCK( (*current).mutex );

   int32_t i = 0;

   if ( current != other )
   {
      // move all cursors off - list will be mangled
      move_all_cursors_off( current );

      // remove all nodes
      for ( i = 0; i < (*current).count; i++ )
      {
         VALUE_DEEP_DISPOSE_FUNCTION( (*current).array[i] );
      }

      // set array
      (*current).array = ( Type * ) realloc( (*current).array, (*other).capacity * sizeof( Type ) );
      CHECK( "(*current).array reallocated correctly", (*current).array != NULL );

      // set capacity
      (*current).capacity = (*other).capacity;

      // set count
      (*current).count = (*other).count;

      // lock other
      LOCK( (*other).mutex );

      for ( i = 0; i < (*other).count; i++ )
      {
         (*current).array[i] = (*other).array[i];
      }

      POSTCONDITION( "new list contains elements of other", compare_list_items_to_list_items( current, other ) );

      // unlock other mutex
      UNLOCK( (*other).mutex );

      INVARIANT( other );
      INVARIANT( current );
   }

   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_deep_copy
*/

void
AList_deep_copy( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == ALIST_TYPE ) && ( (*other)._item_type = Type_Code ) );
   INVARIANT( current );

   // lock current
   LOCK( (*current).mutex );

   int32_t i = 0;

   if ( current != other )
   {
      // move all cursors off - list will be mangled
      move_all_cursors_off( current );

      // remove all nodes
      for ( i = 0; i < (*current).count; i++ )
      {
         VALUE_DEEP_DISPOSE_FUNCTION( (*current).array[i] );
      }

      // set array
      (*current).array = ( Type * ) realloc( (*current).array, (*other).capacity * sizeof( Type ) );
      CHECK( "(*current).array reallocated correctly", (*current).array != NULL );

      // set capacity
      (*current).capacity = (*other).capacity;

      // set count
      (*current).count = (*other).count;


      // lock other
      LOCK( (*other).mutex );

      for ( i = 0; i < (*other).count; i++ )
      {
         (*current).array[i] = VALUE_DEEP_CLONE_FUNCTION( (*other).array[i] );
      }

      POSTCONDITION( "new list contains elements deep equal to other", compare_list_items_to_list_items_deep_equal( current, other ) );

      // unlock other mutex
      UNLOCK( (*other).mutex );

      INVARIANT( current );
   }

   UNLOCK( (*current).mutex );

   return;
}


/**
   AList_cursor_make
*/

AList_cursor_type( Prefix ) *
AList_cursor_make( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // allocate cursor struct
   AList_cursor_type( Prefix ) *cursor
      =  ( AList_cursor_type( Prefix ) * )
         calloc( 1, sizeof( AList_cursor_type( Prefix ) ) );
   CHECK( "cursor allocated_correctly", cursor != NULL );

   // set list
   (*cursor).list = current;

   // set index to -1 - cursor is "off"
   (*cursor).index = -1;

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

   POSTCONDITION( "new cursor is last cursor", (*current).last_cursor == cursor );

   INVARIANT( current );

   UNLOCK( (*current).mutex );

   return cursor;
}

/**
   AList_dispose
*/

void
AList_dispose( Prefix )( AList_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == ALIST_TYPE ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // free array
   free( (**current).array );

   // delete cursors
   AList_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   AList_cursor_type( Prefix ) *next_cursor = NULL;
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
   AList_deep_dispose
*/

void
AList_deep_dispose( Prefix )( AList_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type ok", ( (**current)._type == ALIST_TYPE ) && ( (**current)._item_type = Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete list items
   int32_t i = 0;
   for( i = 0; i < (**current).count; i++ )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( (**current).array[i] );
   }

   // free array
   free( (**current).array );

   // delete cursors
   AList_cursor_type( Prefix ) *cursor = (**current).first_cursor;
   AList_cursor_type( Prefix ) *next_cursor = NULL;
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
   AList_cursor_dispose
*/

void
AList_cursor_dispose( Prefix )( AList_cursor_type( Prefix ) **cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "*cursor not null", *cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(**cursor).list )._type == ALIST_TYPE ) && ( ( *(**cursor).list )._item_type == Type_Code ) );
   LOCK( (**cursor).mutex );
   LOCK( ( *(**cursor).list ).mutex );
   INVARIANT( (**cursor).list );

   AList_cursor_type( Prefix ) *c1 = NULL;
   AList_cursor_type( Prefix ) *c2 = NULL;
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

   INVARIANT( (*c2).list );
   UNLOCK( ( *(*c2).list ).mutex );

   return;
}


/**
   AList_cursor_item_at
*/

Type
AList_cursor_item_at( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );

   Type value = ( *(*cursor).list ).array[ (*cursor).index ];

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}


/**
   AList_item_at
*/

Type
AList_item_at( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).index != -1 );

   AList_cursor_type( Prefix ) *cursor = (*current).first_cursor;

   Type value = ( *(*cursor).list ).array[ (*cursor).index ];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   AList_cursor_item_next
*/

Type
AList_cursor_item_next( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "not off", (*cursor).index != -1 );
   PRECONDITION( "next not off", ( (*cursor).index + 1 ) < ( *(*cursor).list ).count );

   Type value = ( *(*cursor).list ).array[ (*cursor).index + 1 ];

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}

/**
   AList_item_next
*/

Type
AList_item_next( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).index != -1 );
   PRECONDITION( "next not off", ( ( *(*current).first_cursor ).index + 1 ) < (*current).count );

   Type value = (*current).array[ ( *(*current).first_cursor ).index + 1 ];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   AList_cursor_item_prev
*/

Type
AList_cursor_item_prev( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "not off", (*cursor).index != -1 );
   PRECONDITION( "prev not off", ( (*cursor).index - 1 ) >= 0 );

   Type value = ( *(*cursor).list ).array[ (*cursor).index - 1 ];

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return value;
}

/**
   AList_item_prev
*/

Type
AList_item_prev( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not off", ( *(*current).first_cursor ).index != -1 );
   PRECONDITION( "prev not off", ( ( *(*current).first_cursor ).index - 1 ) >= 0 );

   Type value = (*current).array[ ( *(*current).first_cursor ).index - 1 ];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   AList_item
*/

Type
AList_item( Prefix )( AList_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );

   Type value = (*current).array[ index ];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   AList_first
*/

Type
AList_first( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "first not null", (*current).count > 0 );

   Type value = (*current).array[0];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   AList_last
*/

Type
AList_last( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "last not null", (*current).count > 0 );

   Type value = (*current).array[ (*current).count - 1 ];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   AList_as_array
*/

Type *
AList_as_array( Prefix )( AList_type( Prefix ) *current, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "count not null", count != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;

   Type *result = ( Type * ) calloc( (*current).count + 1, sizeof( Type ) );
   CHECK( "result allocated_correctly", result != NULL );

   for ( i = 0; i < (*current).count; i++ )
   {
      result[i] = (*current).array[i];
   }

   (*count) = (*current).count;

   POSTCONDITION( "array contains items of current", compare_list_items_to_array_items( current, result, *count ) );

   INVARIANT( current );

   UNLOCK( (*current).mutex );

   return result;
}

/**
   AList_count
*/

int32_t
AList_count( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return count;
}

/**
   AList_off
*/

int32_t
AList_off( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( ( *(*current).first_cursor ).index == -1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AList_cursor_off
*/

int32_t
AList_cursor_off( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = ( (*cursor).index == -1 );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AList_is_first
*/

int32_t
AList_is_first( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( ( *(*current).first_cursor ).index == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AList_cursor_is_first
*/

int32_t
AList_cursor_is_first( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = ( (*cursor).index == 0 );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AList_is_last
*/

int32_t
AList_is_last( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( ( *(*current).first_cursor ).index == ( (*current).count - 1 ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AList_cursor_is_last
*/

int32_t
AList_cursor_is_last( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = ( (*cursor).index == ( ( *(*cursor).list ).count - 1 ) );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AList_index
*/

int32_t
AList_index( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( *(*current).first_cursor ).index;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AList_cursor_index
*/

int32_t
AList_cursor_index( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );

   int32_t result = (*cursor).index;

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return result;
}

/**
   AList_is_empty
*/

int32_t
AList_is_empty( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count ==  0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AList_forth
*/

void
AList_forth( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).index != -1 );

   ( *(*current).first_cursor ).index = ( *(*current).first_cursor ).index + 1;

   // check for cursor now "off"
   if ( ( *(*current).first_cursor ).index >= (*current).count )
   {
      ( *(*current).first_cursor ).index = -1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_cursor_forth
*/

void
AList_cursor_forth( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );

   (*cursor).index = (*cursor).index + 1;

   // check for cursor now "off"
   if ( (*cursor).index >= ( *(*cursor).list ).count )
   {
      (*cursor).index = -1;
   }

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_back
*/

void
AList_back( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).index != -1 );

   ( *(*current).first_cursor ).index = ( *(*current).first_cursor ).index - 1;

   // check for cursor now "off"
   if ( ( *(*current).first_cursor ).index < 0 )
   {
      ( *(*current).first_cursor ).index = -1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_cursor_back
*/

void
AList_cursor_back( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );

   (*cursor).index = (*cursor).index - 1;

   // check for cursor now "off"
   if ( (*cursor).index < 0 )
   {
      (*cursor).index = -1;
   }

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_go
*/

void
AList_go( Prefix )( AList_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );

   ( *(*current).first_cursor ).index = index;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_cursor_go
*/

void
AList_cursor_go( Prefix )( AList_cursor_type( Prefix ) *cursor, int32_t index )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < ( *(*cursor).list ).count ) ) );

   (*cursor).index = index;

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_start
*/

void
AList_start( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   if ( (*current).count > 0 )
   {
      ( *(*current).first_cursor ).index = 0;
   }
   else
   {
      ( *(*current).first_cursor ).index = -1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_cursor_start
*/

void
AList_cursor_start( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );

   if ( ( *(*cursor).list ).count > 0 )
   {
      (*cursor).index = 0;
   }
   else
   {
      (*cursor).index = -1;
   }

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_finish
*/

void
AList_finish( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   if ( (*current).count > 0 )
   {
      ( *(*current).first_cursor ).index = (*current).count - 1;
   }
   else
   {
      ( *(*current).first_cursor ).index = -1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_cursor_finish
*/

void
AList_cursor_finish( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );

   if ( ( *(*cursor).list ).count > 0 )
   {
      (*cursor).index = ( *(*cursor).list ).count - 1;
   }
   else
   {
      (*cursor).index = -1;
   }

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_put
*/

void
AList_put( Prefix )( AList_type( Prefix ) *current, Type value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*current).count ) ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   // handle current growth if required
   if ( (*current).count + 1 > (*current).capacity )
   {
      (*current).array = ( Type * ) realloc( (*current).array, ( (*current).count + 1 ) * sizeof( Type ) );
      CHECK( "(*current).array reallocated correctly", (*current).array != NULL );

      // set current capacity
      (*current).capacity = (*current).count + 1;

   }

   // see if we're adding to last of current
   if ( index == (*current).count )
   {
      (*current).array[index] = value;
      (*current).count = (*current).count + 1;
   }
   else
   {
      // otherwise, move array entries to right to make room for new value at index
      int32_t i = 0;
      Type *array = (*current).array;

      for( i = (*current).count; i > index; i-- )
      {
         array[i] = array[i - 1];
      }

      array[index] = value;
      (*current).count = (*current).count + 1;
   }

   POSTCONDITION( "count incremented", (*current).count == ( i_pc + 1 ) );
   POSTCONDITION( "value set", (*current).array[index] == value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_put_right
*/

void
AList_put_right( Prefix )( AList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   // handle current growth if required
   if ( (*current).count + 1 > (*current).capacity )
   {
      (*current).array = ( Type * ) realloc( (*current).array, ( (*current).count + 1 ) * sizeof( Type ) );
      CHECK( "(*current).array reallocated correctly", (*current).array != NULL );

      // set current capacity
      (*current).capacity = (*current).count + 1;

   }

   int32_t index = ( *(*current).first_cursor ).index + 1;

   // see if we're adding to last of current
   if ( index == (*current).count )
   {
      (*current).array[index] = value;
      (*current).count = (*current).count + 1;
   }
   else
   {
      // otherwise, move array entries to right to make room for new value at index
      int32_t i = 0;
      Type *array = (*current).array;

      for( i = (*current).count; i > index; i-- )
      {
         array[i] = array[i - 1];
      }

      // set new entry
      array[index] = value;

      // increment current count
      (*current).count = (*current).count + 1;
   }

   POSTCONDITION( "count incremented", (*current).count == i_pc + 1 );
   POSTCONDITION( "value set", (*current).array[( *(*current).first_cursor ).index + 1] == value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_cursor_put_right
*/

void
AList_cursor_put_right( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = ( *(*cursor).list ).count; );

   AList_type( Prefix ) *list = (*cursor).list;

   // handle list growth if required
   if ( (*list).count + 1 > ( *(*cursor).list ).capacity )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( (*list).count + 1 ) * sizeof( Type ) );
      CHECK( "(*list).array reallocated correctly", (*list).array != NULL );

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

      for( i = (*list).count; i > index; i-- )
      {
         array[i] = array[i - 1];
      }

      // set new entry
      array[index] = value;

      // increment list count
      (*list).count = (*list).count + 1;
   }

   POSTCONDITION( "count incremented", (*list).count == i_pc + 1 );
   POSTCONDITION( "value set", (*list).array[(*cursor).index + 1] == value );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_put_left
*/

void
AList_put_left( Prefix )( AList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   // handle current growth if required
   if ( (*current).count + 1 > (*current).capacity )
   {
      (*current).array = ( Type * ) realloc( (*current).array, ( (*current).count + 1 ) * sizeof( Type ) );
      CHECK( "(*current).array reallocated correctly", (*current).array != NULL );

      // set current capacity
      (*current).capacity = (*current).count + 1;

   }

   int32_t index = ( *(*current).first_cursor ).index;

   // move array entries to right to make room for new value at index - 1
   int32_t i = 0;
   Type *array = (*current).array;

   for( i = (*current).count; i > index; i-- )
   {
      array[i] = array[i - 1];
   }

   // set new entry
   array[index] = value;

   // increment current count
   (*current).count = (*current).count + 1;

   POSTCONDITION( "count incremented", (*current).count == i_pc + 1 );
   POSTCONDITION( "value set", (*current).array[( *(*current).first_cursor ).index] == value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_cursor_put_left
*/

void
AList_cursor_put_left( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = ( *(*cursor).list ).count; );

   AList_type( Prefix ) *list = (*cursor).list;

   // handle list growth if required
   if ( (*list).count + 1 > (*list).capacity )
   {
      (*list).array = ( Type * ) realloc( (*list).array, ( (*list).count + 1 ) * sizeof( Type ) );
      CHECK( "(*list).array reallocated correctly", (*list).array != NULL );

      // set list capacity
      (*list).capacity = (*list).count + 1;

   }

   int32_t index = (*cursor).index;

   // move array entries to right to make room for new value at index - 1
   int32_t i = 0;
   Type *array = (*list).array;

   for( i = (*list).count; i > index; i-- )
   {
      array[i] = array[i - 1];
   }

   // set new entry
   array[index] = value;

   // increment list count
   (*list).count = (*list).count + 1;

   POSTCONDITION( "count incremented", (*list).count == i_pc + 1 );
   POSTCONDITION( "value set", (*list).array[(*cursor).index] == value );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_put_first
*/

void
AList_put_first( Prefix )( AList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   // handle current growth if required
   if ( (*current).count + 1 > (*current).capacity )
   {
      (*current).array = ( Type * ) realloc( (*current).array, ( (*current).count + 1 ) * sizeof( Type ) );
      CHECK( "(*current).array reallocated correctly", (*current).array != NULL );

      // set current capacity
      (*current).capacity = (*current).count + 1;

   }

   int32_t index = 0;

   // move array entries to right to make room for new value at index
   int32_t i = 0;
   Type *array = (*current).array;

   for( i = (*current).count; i > index; i-- )
   {
      array[i] = array[i - 1];
   }

   // set new entry
   array[index] = value;

   // increment current count
   (*current).count = (*current).count + 1;

   POSTCONDITION( "count incremented", (*current).count == i_pc + 1 );
   POSTCONDITION( "value set", (*current).array[0] == value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_put_last
*/

void
AList_put_last( Prefix )( AList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   put_last( current, value );

   POSTCONDITION( "value set", (*current).array[(*current).count - 1] == value );

   POSTCONDITION( "count incremented", (*current).count == i_pc + 1 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   append

   Helper function to append a list to a list

   @param current a AList_t instance
   @param other a AList_t instance to append/insert into list
   @param index the index after which to append/insert the list
*/

static
void
append( AList_type( Prefix ) *current, AList_type( Prefix ) *other, int32_t index )
{
   // handle current growth if required
   if ( (*current).count + (*other).count > (*current).capacity )
   {
      (*current).array = ( Type * ) realloc( (*current).array, ( (*current).count + (*other).count ) * sizeof( Type ) );
      CHECK( "(*current).array reallocated correctly", (*current).array != NULL );

      // set current capacity
      (*current).capacity = (*current).count + (*other).count;

   }

   int32_t i = 0;

   // see if we're appending to last of current
   if ( index == (*current).count )
   {
      for( i = 0; i < (*other).count; i++ )
      {
         (*current).array[ (*current).count + i ] = (*other).array[i];
      }

      // update current count
      (*current).count = (*current).count + (*other).count;
   }
   else
   {
      // otherwise, move array entries to right to make room for new values at index
      int32_t i = 0;
      Type *array = (*current).array;

      for( i = (*current).count; i > index; i-- )
      {
         array[ (*other).count + i - 1 ] = array[i - 1];
      }

      // and copy entries of other into the new space
      for( i = 0; i < (*other).count; i++ )
      {
         array[ index + i ] = (*other).array[i];
      }

      // update current count
      (*current).count = (*current).count + (*other).count;
   }

   return;
}

/**
   AList_append
*/

void
AList_append( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == ALIST_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*current).count ) ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   // lock other
   LOCK( (*other).mutex );

   // append other to current
   append( current, other, index );

   POSTCONDITION( "count correct", (*current).count == i_pc + (*other).count );
   POSTCONDITION( "other is in current", compare_list_in_list( current, other, index ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_append_right
*/

void
AList_append_right( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == ALIST_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   // lock other
   LOCK( (*other).mutex );

   int32_t index = 0;

   if ( (*current).count == 0 )
   {
      index = 0;
   }
   else
   {
      index = ( *(*current).first_cursor ).index + 1;
   }

   // append other to current
   append( current, other, index );

   POSTCONDITION( "count correct", (*current).count == i_pc + (*other).count );
   POSTCONDITION( "other is in current", compare_list_in_list( current, other, ( *(*current).first_cursor ).index + 1 ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_cursor_append_right
*/

void
AList_cursor_append_right( Prefix )( AList_cursor_type( Prefix ) *cursor, AList_type( Prefix ) *other )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "list not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == ALIST_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = ( *(*cursor).list ).count; );

   // lock other
   LOCK( (*other).mutex );

   int32_t index = 0;

   if ( ( *(*cursor).list ).count == 0 )
   {
      index = 0;
   }
   else
   {
      index = (*cursor).index + 1;
   }

   // append other to list
   append( (*cursor).list, other, index );

   POSTCONDITION( "count correct", ( *(*cursor).list ).count == i_pc + (*other).count );
   POSTCONDITION( "other is in list", compare_list_in_list( (*cursor).list, other, (*cursor).index + 1 ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_append_left
*/

void
AList_append_left( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == ALIST_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   // lock other
   LOCK( (*other).mutex );

   int32_t index = 0;

   if ( (*current).count == 0 )
   {
      index = 0;
   }
   else
   {
      index = ( *(*current).first_cursor ).index;
   }

   // append other to current
   append( current, other, index );

   POSTCONDITION( "count correct", (*current).count == i_pc + (*other).count );
   POSTCONDITION( "other is in current", compare_list_in_list( current, other, ( *(*current).first_cursor ).index ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_cursor_append_left
*/

void
AList_cursor_append_left( Prefix )( AList_cursor_type( Prefix ) *cursor, AList_type( Prefix ) *other )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == ALIST_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = ( *(*cursor).list ).count; );

   // lock other
   LOCK( (*other).mutex );

   int32_t index = 0;

   if ( ( *(*cursor).list ).count == 0 )
   {
      index = 0;
   }
   else
   {
      index = (*cursor).index;
   }

   // append other to list
   append( (*cursor).list, other, index );

   POSTCONDITION( "count correct", ( *(*cursor).list ).count == i_pc + (*other).count );
   POSTCONDITION( "other is in list", compare_list_in_list( (*cursor).list, other, (*cursor).index ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_append_first
*/

void
AList_append_first( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == ALIST_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   // lock other
   LOCK( (*other).mutex );

   // append other to current
   append( current, other, 0 );

   POSTCONDITION( "count correct", (*current).count == i_pc + (*other).count );
   POSTCONDITION( "other is in current", compare_list_in_list( current, other, 0 ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_append_last
*/

void
AList_append_last( Prefix )( AList_type( Prefix ) *current, AList_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == ALIST_TYPE ) && ( (*other)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   // lock other
   LOCK( (*other).mutex );

   // append other to current
   append( current, other, (*current).count );

   POSTCONDITION( "count correct", (*current).count == i_pc + (*other).count );
   POSTCONDITION( "other is in current", compare_list_in_list( current, other, (*current).count - (*other).count ) );

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_replace
*/

void
AList_replace( Prefix )( AList_type( Prefix ) *current, Type value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   INVARIANT( current );

   (*current).array[index] = value;

   POSTCONDITION( "value set", (*current).array[index] == value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_replace_and_dispose
*/

void
AList_replace_and_dispose( Prefix )( AList_type( Prefix ) *current, Type value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );

   VALUE_DEEP_DISPOSE_FUNCTION( (*current).array[index] );
   (*current).array[index] = value;

   POSTCONDITION( "value set", (*current).array[index] == value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_replace_at
*/

void
AList_replace_at( Prefix )( AList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).index != -1 );

   (*current).array[ ( *(*current).first_cursor ).index ] = value;

   POSTCONDITION( "value set", (*current).array[( *(*current).first_cursor ).index] == value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_replace_at_and_dispose
*/

void
AList_replace_at_and_dispose( Prefix )( AList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).index != -1 );

   if ( (*current).array[ ( *(*current).first_cursor ).index ] != VALUE_DEFAULT )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( (*current).array[ ( *(*current).first_cursor ).index ] );
   }

   (*current).array[ ( *(*current).first_cursor ).index ] = value;

   POSTCONDITION( "value set", (*current).array[( *(*current).first_cursor ).index] == value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_cursor_replace_at
*/

void
AList_cursor_replace_at( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );

   ( *(*cursor).list ).array[ (*cursor).index ] = value;

   POSTCONDITION( "value set", ( *(*cursor).list ).array[(*cursor).index] == value );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
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
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );

   if ( ( *(*cursor).list ).array[ (*cursor).index ] != VALUE_DEFAULT )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( ( *(*cursor).list ).array[ (*cursor).index ] );
   }

   ( *(*cursor).list ).array[ (*cursor).index ] = value;

   POSTCONDITION( "value set", ( *(*cursor).list ).array[(*cursor).index] == value );

   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   remove

   Helper function to remove an item from a list

   @param current a AList_t instance
   @param index the index to remove
*/

static
void
remove( AList_type( Prefix ) *current, int32_t index )
{
   AList_cursor_type( Prefix ) *cursor;

   // see if we're removing from last of current
   if ( index == ( (*current).count - 1 ) )
   {
      (*current).count = (*current).count - 1;
   }
   else
   {
      // otherwise, move array entries to left to overwrite value at index
      int32_t i = 0;
      Type *array = (*current).array;

      for( i = index + 1; i < (*current).count; i++ )
      {
         array[i - 1] = array[i];
      }

      (*current).count = (*current).count - 1;
   }

   // handle current reduction if required
   if ( (*current).count < (*current).capacity / 2 )
   {
      if ( (*current).count / 2 == 0 )
      {
         (*current).array = ( Type * ) realloc( (*current).array, sizeof( Type ) );
         CHECK( "(*current).array reallocated correctly", (*current).array != NULL );
      }

      // set current capacity
      (*current).capacity = (*current).count;

   }

   // update the cursors
   cursor = (*current).first_cursor;
   while ( cursor != NULL )
   {
      if ( (*cursor).index >= (*current).count )
      {
         (*cursor).index = -1;
      }
      else if ( (*current).count == 0 )
      {
         (*cursor).index = -1;
      }
      cursor = (*cursor).next_cursor;
   }

   return;
}

/**
   remove_and_dispose

   Helper function to remove an item from a list and dispose of its value

   @param current a AList_t instance
   @param index the index to remove
*/

static
void
remove_and_dispose( AList_type( Prefix ) *current, int32_t index )
{
   AList_cursor_type( Prefix ) *cursor;

   // see if we're removing from last of current
   if ( index == ( (*current).count - 1 ) )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( (*current).array[index] );
      (*current).count = (*current).count - 1;
   }
   else
   {
      // otherwise, move array entries to left to overwrite value at index
      int32_t i = 0;
      Type *array = (*current).array;

      VALUE_DEEP_DISPOSE_FUNCTION( (*current).array[index] );

      for( i = index + 1; i < (*current).count; i++ )
      {
         array[i - 1] = array[i];
      }

      (*current).count = (*current).count - 1;
   }

   // handle current reduction if required
   if ( (*current).count < (*current).capacity / 2 )
   {
      if ( (*current).count / 2 == 0 )
      {
         (*current).array = ( Type * ) realloc( (*current).array, sizeof( Type ) );
         CHECK( "(*current).array reallocated correctly", (*current).array != NULL );
      }

      // set current capacity
      (*current).capacity = (*current).count;

   }

   // update the cursors
   cursor = (*current).first_cursor;
   while ( cursor != NULL )
   {
      if ( (*cursor).index >= (*current).count )
      {
         (*cursor).index = -1;
      }
      else if ( (*current).count == 0 )
      {
         (*cursor).index = -1;
      }
      cursor = (*cursor).next_cursor;
   }

   return;
}

/**
   AList_remove
*/

void
AList_remove( Prefix )( AList_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = (*current).array[index]; int32_t i_pc = occurrences( current, (*current).array[index] ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   // remove
   remove( current, index );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_remove_and_dispose
*/

void
AList_remove_and_dispose( Prefix )( AList_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = (*current).array[index]; int32_t i_pc = occurrences( current, (*current).array[index] ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   // remove
   remove_and_dispose( current, index );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_remove_at
*/

void
AList_remove_at( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = (*current).array[ ( *(*current).first_cursor ).index ]; int32_t i_pc = occurrences( current, (*current).array[ ( *(*current).first_cursor ).index ] ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   // remove
   remove( current, ( *(*current).first_cursor ).index );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_remove_at_and_dispose
*/

void
AList_remove_at_and_dispose( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = (*current).array[ ( *(*current).first_cursor ).index ]; int32_t i_pc = occurrences( current, (*current).array[ ( *(*current).first_cursor ).index ] ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   // remove
   remove_and_dispose( current, ( *(*current).first_cursor ).index );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_cursor_remove_at
*/

void
AList_cursor_remove_at( Prefix )( AList_cursor_type( Prefix ) *cursor )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *(*cursor).list ).array[ (*cursor).index ]; int32_t i_pc = occurrences( (*cursor).list, ( *(*cursor).list ).array[ (*cursor).index ] ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).list ).count; );

   // remove
   remove( (*cursor).list, (*cursor).index );

   POSTCONDITION( "element removed", i_pc == occurrences( (*cursor).list, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == ( *(*cursor).list ).count + 1 );
   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
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
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = ( *(*cursor).list ).array[ (*cursor).index ]; int32_t i_pc = occurrences( (*cursor).list, ( *(*cursor).list ).array[ (*cursor).index ] ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = ( *(*cursor).list ).count; );

   // remove
   remove_and_dispose( (*cursor).list, (*cursor).index );

   POSTCONDITION( "element removed", i_pc == occurrences( (*cursor).list, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == ( *(*cursor).list ).count + 1 );
   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_remove_first
*/

void
AList_remove_first( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not empty", ( (*current).count > 0 ) );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = (*current).array[0]; int32_t i_pc = occurrences( current, (*current).array[0] ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   // remove
   remove( current, 0 );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_remove_first_and_dispose
*/

void
AList_remove_first_and_dispose( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not empty", ( (*current).count > 0 ) );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = (*current).array[0]; int32_t i_pc = occurrences( current, (*current).array[0] ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   // remove
   remove_and_dispose( current, 0 );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_remove_last
*/

void
AList_remove_last( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not empty", ( (*current).count > 0 ) );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = (*current).array[ (*current).count - 1]; int32_t i_pc = occurrences( current, (*current).array[ (*current).count - 1 ] ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   // remove
   remove( current, (*current).count - 1 );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_remove_last_and_dispose
*/

void
AList_remove_last_and_dispose( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "not empty", ( (*current).count > 0 ) );
   POSTCONDITION_VARIABLE_DEFINE( Type val_pc = (*current).array[ (*current).count - 1]; int32_t i_pc = occurrences( current, (*current).array[ (*current).count - 1 ] ); );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   // remove
   remove_and_dispose( current, (*current).count - 1 );

   POSTCONDITION( "element removed", i_pc == occurrences( current, val_pc ) + 1 );
   POSTCONDITION( "count decremented", i_pc_count == (*current).count + 1 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   prune

   Helper function to remove a sublist out of a list

   @param current a AList_t instance
   @param index the start index to remove
   @param count the number of entries to remove
*/

static
void
prune( AList_type( Prefix ) *current, int32_t index, int32_t count )
{
   // move all cursors off - current will be mangled
   move_all_cursors_off( current );

   // see if we're removing from last of current
   if ( index + count == ( (*current).count ) )
   {
      (*current).count = (*current).count - count;
   }
   else
   {
      // otherwise, move array entries to left to overwrite values at index
      int32_t i = 0;
      Type *array = (*current).array;

      for( i = 0; ( i < (*current).count - count ) && ( i < (*current).count - count - index ); i++ )
      {
         array[index + i] = array[index + i + count];
      }

      (*current).count = (*current).count - count;
   }

   // handle current reduction if required
   if ( (*current).count < (*current).capacity / 2 )
   {
      if ( (*current).count > 0 )
      {
         (*current).array = ( Type * ) realloc( (*current).array, ( (*current).count ) * sizeof( Type ) );
         CHECK( "(*current).array reallocated correctly", (*current).array != NULL );
      }
      else
      {
         (*current).array = ( Type * ) realloc( (*current).array, sizeof( Type ) );
         CHECK( "(*current).array reallocated correctly", (*current).array != NULL );
      }

      // set current capacity
      (*current).capacity = (*current).count;

   }

   return;
}

/**
   prune_and_dispose

   Helper function to remove a sublist out of a list and dispose of its
   values.

   @param current a AList_t instance
   @param index the start index to remove
   @param count the number of entries to remove
*/

static
void
prune_and_dispose( AList_type( Prefix ) *current, int32_t index, int32_t count )
{
   // move all cursors off - current will be mangled
   move_all_cursors_off( current );

   // see if we're removing from last of current
   if ( index + count == ( (*current).count ) )
   {
      // if so, dispose of the entries and adjust the current count
      int32_t i = 0;
      for( i = index; i < index + count; i++ )
      {
         VALUE_DEEP_DISPOSE_FUNCTION( (*current).array[i] );
      }
      (*current).count = (*current).count - count;
   }
   else
   {
      // otherwise, move array entries to left to overwrite values at index
      int32_t i = 0;
      Type *array = (*current).array;

      // dispose of entries
      for( i = index; i < index + count; i++ )
      {
         VALUE_DEEP_DISPOSE_FUNCTION( array[i] );
      }

      // move entries
      for( i = 0; ( i < (*current).count - count ) && ( i < (*current).count - count - index ); i++ )
      {
         array[index + i] = array[index + i + count];
      }

      (*current).count = (*current).count - count;
   }

   // handle current reduction if required
   if ( (*current).count < (*current).capacity / 2 )
   {
      if ( (*current).count > 0 )
      {
         (*current).array = ( Type * ) realloc( (*current).array, ( (*current).count ) * sizeof( Type ) );
         CHECK( "(*current).array reallocated correctly", (*current).array != NULL );
      }
      else
      {
         (*current).array = ( Type * ) realloc( (*current).array, sizeof( Type ) );
         CHECK( "(*current).array reallocated correctly", (*current).array != NULL );
      }

      // set current capacity
      (*current).capacity = (*current).count;

   }

   return;
}


/**
   AList_prune
*/

void
AList_prune( Prefix )( AList_type( Prefix ) *current, int32_t index, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   prune( current, index, count );

   POSTCONDITION( "count ok", i_pc_count == (*current).count + count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_prune_and_dispose
*/

void
AList_prune_and_dispose( Prefix )( AList_type( Prefix ) *current, int32_t index, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   prune_and_dispose( current, index, count );

   POSTCONDITION( "count ok", i_pc_count == (*current).count + count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_prune_first
*/

void
AList_prune_first( Prefix )( AList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( (*current).count >= count ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   prune( current, 0, count );

   POSTCONDITION( "count ok", i_pc_count == (*current).count + count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_prune_first_and_dispose
*/

void
AList_prune_first_and_dispose( Prefix )( AList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( (*current).count >= count ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   prune_and_dispose( current, 0, count );

   POSTCONDITION( "count ok", i_pc_count == (*current).count + count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_prune_last
*/

void
AList_prune_last( Prefix )( AList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( (*current).count >= count ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   prune( current, (*current).count - count, count );

   POSTCONDITION( "count ok", i_pc_count == (*current).count + count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_prune_last_and_dispose
*/

void
AList_prune_last_and_dispose( Prefix )( AList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( (*current).count >= count ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc_count = (*current).count; );

   prune_and_dispose( current, (*current).count - count, count );

   POSTCONDITION( "count ok", i_pc_count == (*current).count + count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_keep_first
*/

void
AList_keep_first( Prefix )( AList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( (*current).count >= count ) );

   prune( current, count, (*current).count - count );

   POSTCONDITION( "count ok", (*current).count == count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_keep_first_and_dispose
*/

void
AList_keep_first_and_dispose( Prefix )( AList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( (*current).count >= count ) );

   prune_and_dispose( current, count, (*current).count - count );

   POSTCONDITION( "count ok", (*current).count == count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_keep_last
*/

void
AList_keep_last( Prefix )( AList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( (*current).count >= count ) );

   prune( current, 0, (*current).count - count );

   POSTCONDITION( "count ok", (*current).count == count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_keep_last_and_dispose
*/

void
AList_keep_last_and_dispose( Prefix )( AList_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( (*current).count >= count ) );

   prune_and_dispose( current, 0, (*current).count - count );

   POSTCONDITION( "count ok", (*current).count == count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_wipe_out
*/

void
AList_wipe_out( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // move all cursors off - current will be mangled
   move_all_cursors_off( current );

   (*current).count = 0;

   // handle current reduction if required - at least capacity of 1
   if ( 1 < (*current).capacity / 2 )
   {
      (*current).array = ( Type * ) realloc( (*current).array, ( 1 ) * sizeof( Type ) );
      CHECK( "(*current).array reallocated correctly", (*current).array != NULL );

      // set current capacity
      (*current).capacity = 1;

   }

   POSTCONDITION( "current is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_wipe_out_and_dispose
*/

void
AList_wipe_out_and_dispose( Prefix )( AList_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;

   // move all cursors off - current will be mangled
   move_all_cursors_off( current );

   // remove all nodes
   for ( i = 0; i < (*current).count; i++ )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( (*current).array[i] );
   }

   (*current).count = 0;

   // handle current reduction if required - at least capacity of 1
   if ( 1 < (*current).capacity / 2 )
   {
      (*current).array = ( Type * ) realloc( (*current).array, ( 1 ) * sizeof( Type ) );
      CHECK( "(*current).array reallocated correctly", (*current).array != NULL );

      // set current capacity
      (*current).capacity = 1;

   }

   POSTCONDITION( "current is empty", (*current).count == 0 );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_has
*/
int32_t
AList_has( Prefix )( AList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t index_pc = ( *(*current).first_cursor ).index; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t result = 0;

   result = has( current, value );

   POSTCONDITION( "current first cursor unchanged", index_pc == ( *(*current).first_cursor ).index );
   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AList_has_eq_fn
*/
int32_t
AList_has_eq_fn( Prefix )
(
   AList_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t index_pc = ( *(*current).first_cursor ).index; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t result = 0;

   result = has_eq_fn( current, value, equality_test_func );

   POSTCONDITION( "current first cursor unchanged", index_pc == ( *(*current).first_cursor ).index );
   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AList_search_forth
*/
void
AList_search_forth( Prefix )( AList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t *index = NULL;
   Type *array = NULL;
   int32_t count = 0;

   index = &( ( *(*current).first_cursor ).index );
   array = (*current).array;
   count = (*current).count;

   while( (*index) != -1 )
   {
      // see if value is equal to current item
      if ( array[ (*index) ] == value )
      {
         // if so, exit with first_cursor at index
         break;
      }

      // increment first_cursor index
      (*index) = (*index) + 1;

      // check for first_cursor index now "off"
      if ( (*index) >= count )
      {
         (*index) = -1;
      }

   }

   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_search_forth_eq_fn
*/
void
AList_search_forth_eq_fn( Prefix )
(
   AList_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t *index = NULL;
   Type *array = NULL;
   int32_t count = 0;

   index = &( ( *(*current).first_cursor ).index );
   array = (*current).array;
   count = (*current).count;

   while( (*index) != -1 )
   {
      // see if value is equal to current item
      if ( equality_test_func( array[ (*index) ], value ) == 1 )
      {
         // if so, exit with first_cursor at index
         break;
      }

      // increment first_cursor index
      (*index) = (*index) + 1;

      // check for first_cursor index now "off"
      if ( (*index) >= count )
      {
         (*index) = -1;
      }

   }

   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_search_back
*/
void
AList_search_back( Prefix )( AList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t *index = NULL;
   Type *array = NULL;

   index = &( ( *(*current).first_cursor ).index );
   array = (*current).array;

   while( (*index) != -1 )
   {
      // see if value is equal to current item
      if ( array[ (*index) ] == value )
      {
         // if so, exit with first_cursor at index
         break;
      }

      // decrement first_cursor index
      (*index) = (*index) - 1;

   }

   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_search_back_eq_fn
*/
void
AList_search_back_eq_fn( Prefix )
(
   AList_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "current not off", ( *(*current).first_cursor ).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t *index = NULL;
   Type *array = NULL;

   index = &( ( *(*current).first_cursor ).index );
   array = (*current).array;

   while( (*index) != -1 )
   {
      // see if value is equal to current item
      if ( equality_test_func( array[ (*index) ], value ) == 1 )
      {
         // if so, exit with first_cursor at index
         break;
      }

      // decrement first_cursor index
      (*index) = (*index) - 1;

   }

   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   AList_cursor_search_forth
*/
void
AList_cursor_search_forth( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = ( *(*cursor).list ).count; );

   int32_t *index = NULL;
   Type *array = NULL;
   int32_t count = 0;

   index = &( (*cursor).index );
   array = ( *(*cursor).list ).array;
   count = ( *(*cursor).list ).count;

   while( (*index) != -1 )
   {
      // see if value is equal to current item
      if ( array[ (*index) ] == value )
      {
         // if so, exit with first_cursor at index
         break;
      }

      // increment first_cursor index
      (*index) = (*index) + 1;

      // check for first_cursor index now "off"
      if ( (*index) >= count )
      {
         (*index) = -1;
      }

   }

   POSTCONDITION( "current count unchanged", count_pc == ( *(*cursor).list ).count );
   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_cursor_search_forth_eq_fn
*/
void
AList_cursor_search_forth_eq_fn( Prefix )
(
   AList_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   PRECONDITION( "equality_test_func OK ", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = ( *(*cursor).list ).count; );

   int32_t *index = NULL;
   Type *array = NULL;
   int32_t count = 0;

   index = &( (*cursor).index );
   array = ( *(*cursor).list ).array;
   count = ( *(*cursor).list ).count;

   while( (*index) != -1 )
   {
      // see if value is equal to current item
      if ( equality_test_func( array[ (*index) ], value ) == 1 )
      {
         // if so, exit with first_cursor at index
         break;
      }

      // increment first_cursor index
      (*index) = (*index) + 1;

      // check for first_cursor index now "off"
      if ( (*index) >= count )
      {
         (*index) = -1;
      }

   }

   POSTCONDITION( "current count unchanged", count_pc == ( *(*cursor).list ).count );
   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_cursor_search_back
*/
void
AList_cursor_search_back( Prefix )( AList_cursor_type( Prefix ) *cursor, Type value )
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = ( *(*cursor).list ).count; );

   int32_t *index = NULL;
   Type *array = NULL;

   index = &( (*cursor).index );
   array = ( *(*cursor).list ).array;

   while( (*index) != -1 )
   {
      // see if value is equal to current item
      if ( array[ (*index) ] == value )
      {
         // if so, exit with first_cursor at index
         break;
      }

      // decrement first_cursor index
      (*index) = (*index) - 1;

   }

   POSTCONDITION( "current count unchanged", count_pc == ( *(*cursor).list ).count );
   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_cursor_search_back_eq_fn
*/
void
AList_cursor_search_back_eq_fn( Prefix )
(
   AList_cursor_type( Prefix ) *cursor,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "cursor not null", cursor != NULL );
   PRECONDITION( "cursor list type ok", ( ( *(*cursor).list )._type == ALIST_TYPE ) && ( ( *(*cursor).list )._item_type == Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   PRECONDITION( "equality_test_func OK ", equality_test_func != NULL );
   LOCK( (*cursor).mutex );
   LOCK( ( *(*cursor).list ).mutex );
   INVARIANT( (*cursor).list );
   PRECONDITION( "cursor not off", (*cursor).index != -1 );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = ( *(*cursor).list ).count; );

   int32_t *index = NULL;
   Type *array = NULL;

   index = &( (*cursor).index );
   array = ( *(*cursor).list ).array;

   while( (*index) != -1 )
   {
      // see if value is equal to current item
      if ( equality_test_func( array[ (*index) ], value ) == 1 )
      {
         // if so, exit with first_cursor at index
         break;
      }

      // decrement first_cursor index
      (*index) = (*index) - 1;

   }

   POSTCONDITION( "current count unchanged", count_pc == ( *(*cursor).list ).count );
   INVARIANT( (*cursor).list );
   UNLOCK( ( *(*cursor).list ).mutex );
   UNLOCK( (*cursor).mutex );

   return;
}

/**
   AList_occurrences
*/
int32_t
AList_occurrences( Prefix )( AList_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t index_pc = ( *(*current).first_cursor ).index; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t result = 0;

   result = occurrences( current, value );

   POSTCONDITION( "current first cursor unchanged", index_pc == ( *(*current).first_cursor ).index );
   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AList_occurrences_eq_fn
*/
int32_t
AList_occurrences_eq_fn( Prefix )
(
   AList_type( Prefix ) *current,
   Type value,
   int32_t ( *equality_test_func )( Type v1, Type v2 )
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "value type ok", protocol_arg_ok( Type_Code, value ) );
   PRECONDITION( "equality_test_func not null", equality_test_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t index_pc = ( *(*current).first_cursor ).index; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   int32_t result = 0;

   result = occurrences_eq_fn( current, value, equality_test_func );

   POSTCONDITION( "current first cursor unchanged", index_pc == ( *(*current).first_cursor ).index );
   POSTCONDITION( "current count unchanged", count_pc == (*current).count );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   AList_swap
*/
void
AList_swap( Prefix )( AList_type( Prefix ) *current, int32_t i, int32_t j )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "i ok", ( ( i >= 0 ) && ( i < (*current).count ) ) );
   PRECONDITION( "j ok", ( ( j >= 0 ) && ( j < (*current).count ) ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t index_pc = ( *(*current).first_cursor ).index; );
   POSTCONDITION_VARIABLE_DEFINE( int32_t count_pc = (*current).count; );

   Type *array = NULL;
   Type v;

   if ( i != j )
   {
      array = (*current).array;

      v = array[i];
      array[i] = array[j];
      array[j] = v;
   }

   POSTCONDITION( "current first cursor unchanged", index_pc == ( *(*current).first_cursor ).index );
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
AList_sort( Prefix )( AList_type( Prefix ) *current, int32_t ( *sort_func )( Type v1, Type v2 ) )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == ALIST_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "sort_func not null", sort_func != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // array to use for sorting
   Type *array = NULL;

   // only sort if there's enough to sort
   if ( (*current).count > 1 )
   {
      array = (*current).array;

      // set the sort func
      value_sort_func_name = sort_func;

      // sort the array
      qsort( array, (*current).count, sizeof( Type ), ( int (*)( const void*, const void* ) ) value_sort_func );

      // reset cursors
      move_all_cursors_off( current );

   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

