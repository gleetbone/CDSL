/**
 @file Circular_Array.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Circular_Arrays (resizable arrays)"

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

 Function definitions for the opaque Circular_Array_t type.

*/

#include "protocol.h"

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_Indexable.ph"
#endif // PROTOCOLS_ENABLED   

#include "Circular_Array.h"

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
   Circular_Array structure
   circluar array of Type
*/

struct Circular_Array_struct( Prefix )
{

   PROTOCOLS_DEFINITION;

   int32_t _type;
   int32_t _item_type;

   int32_t count;
   int32_t capacity;
   int32_t start_index;
   Type *buffer;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};


/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
nonnegative_count( Circular_Array_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).count >= 0 );

   return result;
}

static
int32_t
valid_count_capacity( Circular_Array_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).capacity >= (*current).count );

   return result;
}

static
int32_t
start_index_ok( Circular_Array_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( ( (*current).start_index >= 0 ) && ( (*current).start_index < (*current).capacity ) );

   return result;
}

static
int32_t
buffer_ok( Circular_Array_type( Prefix ) *current )
{
   int32_t result = 1;

   result = (*current).buffer != NULL;

   return result;
}

static
void invariant( Circular_Array_type( Prefix ) *current )
{
   assert( ( ( void ) "nonnegative count", nonnegative_count( current ) ) );
   assert( ( ( void ) "valid count and capacity", valid_count_capacity( current ) ) );
   assert( ( ( void ) "start index ok", start_index_ok( current ) ) );
   assert( ( ( void ) "buffer ok", buffer_ok( current ) ) );
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
   Circular_Array_dispose( Prefix ),
   Circular_Array_deep_dispose( Prefix ),
   Circular_Array_is_equal( Prefix ),
   Circular_Array_is_deep_equal( Prefix ),
   Circular_Array_copy( Prefix ),
   Circular_Array_deep_copy( Prefix ),
   Circular_Array_clone( Prefix ),
   Circular_Array_deep_clone( Prefix )
};

static
void *
p_indexable_table[P_INDEXABLE_FUNCTION_COUNT]
=
{
   Circular_Array_count( Prefix ),
   Circular_Array_item( Prefix ),
   Circular_Array_replace( Prefix ),
   Circular_Array_replace_and_dispose( Prefix )
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

   }

   return result;
}

#endif // PROTOCOLS_ENABLED


/**
   Circular_Array_make
*/

Circular_Array_type( Prefix ) *
Circular_Array_make( Prefix )( int32_t n )
{
   PRECONDITION( "n ok", n > 0 );

   // allocate result struct
   Circular_Array_type( Prefix ) *result
      = ( Circular_Array_type( Prefix ) * ) calloc( 1, sizeof( Circular_Array_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // allocate buffer
   (*result).buffer = ( Type * ) calloc( n, sizeof( Type ) );
   CHECK( "(*result).buffer allocated correctly", (*result).buffer != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = CIRCULAR_ARRAY_TYPE;
   (*result)._item_type = Type_Code;

   // set count and capacity
   (*result).count = 0;
   (*result).capacity = n;
   (*result).start_index = 0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "count set", (*result).count == 0 );
   POSTCONDITION( "capacity set", (*result).capacity == n );
   POSTCONDITION( "start_index set", (*result).start_index == 0 );
   POSTCONDITION( "buffer set", (*result).buffer != NULL );

   return result;
}

/**
   Circular_Array_make_from_array
*/

Circular_Array_type( Prefix ) *
Circular_Array_make_from_array( Prefix )( Type *array, int32_t count, int32_t capacity )
{
   PRECONDITION( "array ok", array != NULL );
   PRECONDITION( "count ok", count > 0 );
   PRECONDITION( "capacity ok", capacity >= count );

   int32_t i = 0;

   // allocate result struct
   Circular_Array_type( Prefix ) *result
      = ( Circular_Array_type( Prefix ) * ) calloc( 1, sizeof( Circular_Array_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // allocate buffer
   (*result).buffer = ( Type * ) calloc( capacity, sizeof( Type ) );
   CHECK( "(*result).buffer allocated correctly", (*result).buffer != NULL );

   // set buffer
   for( i = 0; i < count; i++ )
   {
      (*result).buffer[i] = array[i];
   }

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = CIRCULAR_ARRAY_TYPE;
   (*result)._item_type = Type_Code;

   // set count and capacity
   (*result).count = count;
   (*result).capacity = capacity;
   (*result).start_index = 0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "count set", (*result).count == count );
   POSTCONDITION( "capacity set", (*result).capacity == capacity );
   POSTCONDITION( "start_index set", (*result).start_index == 0 );
   POSTCONDITION( "buffer set", (*result).buffer != NULL );

   return result;
}

/**
   Circular_Array_clone
*/

Circular_Array_type( Prefix ) *
Circular_Array_clone( Prefix )( Circular_Array_type( Prefix ) *current )
{
   PRECONDITION( "result ok", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );

   int32_t i = 0;

   // allocate result struct
   Circular_Array_type( Prefix ) * result
      = ( Circular_Array_type( Prefix ) * ) calloc( 1, sizeof( Circular_Array_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // allocate buffer
   (*result).buffer = ( Type * ) calloc( (*current).capacity, sizeof( Type ) );
   CHECK( "(*result).buffer allocated correctly", (*result).buffer != NULL );

   // set buffer
   for( i = 0; i < (*current).capacity; i++ )
   {
      (*result).buffer[i] = (*current).buffer[i];
   }

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = CIRCULAR_ARRAY_TYPE;
   (*result)._item_type = Type_Code;

   // set count and capacity
   (*result).count = (*current).count;
   (*result).capacity = (*current).capacity;
   (*result).start_index = (*current).start_index;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "count set", (*result).count == (*current).count );
   POSTCONDITION( "capacity set", (*result).capacity == (*current).capacity );
   POSTCONDITION( "start_index set", (*result).start_index == (*current).start_index );
   POSTCONDITION( "buffer set", (*result).buffer != NULL );

   return result;
}

/**
   Circular_Array_deep_clone
*/

Circular_Array_type( Prefix ) *
Circular_Array_deep_clone( Prefix )( Circular_Array_type( Prefix ) *current )
{
   PRECONDITION( "result ok", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );

   int32_t i = 0;

   // allocate result struct
   Circular_Array_type( Prefix ) *result
      = ( Circular_Array_type( Prefix ) * ) calloc( 1, sizeof( Circular_Array_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // allocate buffer
   (*result).buffer = ( Type * ) calloc( (*current).capacity, sizeof( Type ) );
   CHECK( "(*result).buffer allocated correctly", (*result).buffer != NULL );

   // set buffer
   for( i = 0; i < (*current).capacity; i++ )
   {
      (*result).buffer[i] = VALUE_DEEP_CLONE_FUNCTION( (*current).buffer[i] );
   }

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = CIRCULAR_ARRAY_TYPE;
   (*result)._item_type = Type_Code;

   // set count and capacity
   (*result).count = (*current).count;
   (*result).capacity = (*current).capacity;
   (*result).start_index = (*current).start_index;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "count set", (*result).count == (*current).count );
   POSTCONDITION( "capacity set", (*result).capacity == (*current).capacity );
   POSTCONDITION( "start_index set", (*result).start_index == (*current).start_index );
   POSTCONDITION( "buffer set", (*result).buffer != NULL );

   return result;
}

/**
   Circular_Array_is_equal
*/

int32_t
Circular_Array_is_equal( Prefix )( Circular_Array_type( Prefix ) *current, Circular_Array_type( Prefix ) *other )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "circular_array ok", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == CIRCULAR_ARRAY_TYPE ) && ( (*other)._item_type == Type_Code ) );

   INVARIANT( current );

   int32_t result = 1;
   int32_t flag = 0;
   int32_t i = 0;

   // check identity
   if ( result == 1 )
   {
      flag = 0;
      if ( current == other )
      {
         flag = 1;
      }
   }

   if ( flag == 0 )
   {
      // check count
      if ( (*current).count != (*other).count )
      {
         result = 0;
      }

      LOCK( (*other).mutex );

      if ( result == 1 )
      {
         for ( i = 0; i < (*other).capacity; i++ )
         {
            if ( (*current).buffer[i] != (*other).buffer[i] )
            {
               result = 0;
               break;
            }
         }
      }

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );

   return result;
}

/**
   Circular_Array_is_deep_equal
*/

int32_t
Circular_Array_is_deep_equal( Prefix )( Circular_Array_type( Prefix ) *current, Circular_Array_type( Prefix ) *other )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "circular_array ok", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == CIRCULAR_ARRAY_TYPE ) && ( (*other)._item_type == Type_Code ) );

   int32_t result = 1;
   int32_t flag = 0;
   int32_t i = 0;

   INVARIANT( current );

   // check identity
   if ( result == 1 )
   {
      flag = 0;
      if ( current == other )
      {
         flag = 1;
      }
   }

   if ( flag == 0 )
   {
      // check count
      if ( (*current).count != (*other).count )
      {
         result = 0;
      }

      LOCK( (*other).mutex );

      if ( result == 1 )
      {
         for ( i = 0; i < (*other).capacity; i++ )
         {
            if ( VALUE_DEEP_EQUAL_FUNCTION( (*current).buffer[i], (*other).buffer[i] ) == 0 )
            {
               result = 0;
               break;
            }
         }
      }

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );

   return result;
}

/**
   Circular_Array_copy
*/

void
Circular_Array_copy( Prefix )( Circular_Array_type( Prefix ) *current, Circular_Array_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == CIRCULAR_ARRAY_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t i = 0;
   Type *buffer = NULL;
   Type *other_buffer = NULL;

   // empty out current
   buffer = (*current).buffer;

   // remove all nodes
   for ( i = 0; i < (*current).count; i++ )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( buffer[i] );
   }

   // set array
   (*current).buffer = ( Type * ) realloc( (*current).buffer, (*other).capacity * sizeof( Type ) );
   CHECK( "(*current).buffer allocated correctly", (*current).buffer != NULL );

   // set capacity
   (*current).capacity = (*other).capacity;

   // set count
   (*current).count = (*other).count;

   // set start_index
   (*current).start_index = (*other).start_index;

   // lock other
   LOCK( (*other).mutex );

   buffer = (*current).buffer;
   other_buffer = (*other).buffer;

   for ( i = 0; i < (*other).capacity; i++ )
   {
      buffer[i] = other_buffer[i];
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return;
}

/**
   Circular_Array_deep_copy
*/

void
Circular_Array_deep_copy( Prefix )( Circular_Array_type( Prefix ) *current, Circular_Array_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == CIRCULAR_ARRAY_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );
   Type *buffer = NULL;
   Type *other_buffer = NULL;

   int32_t i = 0;

   // empty out current
   buffer = (*current).buffer;

   // remove all nodes
   for ( i = 0; i < (*current).count; i++ )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( (*current).buffer[i] );
   }

   // set array
   (*current).buffer = ( Type * ) realloc( (*current).buffer, (*other).capacity * sizeof( Type ) );
   CHECK( "(*current).buffer allocated correctly", (*current).buffer != NULL );

   // set capacity
   (*current).capacity = (*other).capacity;

   // set count
   (*current).count = (*other).count;

   // set start_index
   (*current).start_index = (*other).start_index;

   // lock other
   LOCK( (*other).mutex );

   buffer = (*current).buffer;
   other_buffer = (*other).buffer;

   for ( i = 0; i < (*other).capacity; i++ )
   {
      buffer[i] = VALUE_DEEP_CLONE_FUNCTION( other_buffer[i] );
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return;
}

/**
   Circular_Array_dispose
*/

void
Circular_Array_dispose( Prefix )( Circular_Array_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "type ok", ( (**current)._type == CIRCULAR_ARRAY_TYPE ) && ( (**current)._item_type == Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete buffer
   free( (**current).buffer );

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   Circular_Array_deep_dispose
*/

void
Circular_Array_deep_dispose( Prefix )( Circular_Array_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "type ok", ( (**current)._type == CIRCULAR_ARRAY_TYPE ) && ( (**current)._item_type == Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete buffer items
   int32_t i = 0;
   for( i = 0; i < (**current).capacity; i++ )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( (**current).buffer[i] );
   }

   // delete buffer
   free( (**current).buffer );

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete current struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   Circular_Array_item
*/

Type
Circular_Array_item( Prefix )( Circular_Array_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   int32_t i = 0;
   int32_t capacity = 0;

   capacity = (*current).capacity;

   // get index into buffer
   i = index + (*current).start_index;
   if ( i >= capacity )
   {
      i = i - capacity;
   }

   Type value = (*current).buffer[i];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   Circular_Array_as_array
*/

Type *
Circular_Array_as_array( Prefix )( Circular_Array_type( Prefix ) *current, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type *result = ( Type * ) calloc( (*current).count + 1, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   int32_t i = 0;
   int32_t capacity = 0;
   int32_t i_buffer = 0;

   capacity = (*current).capacity;


   for( i = 0; i < (*current).count; i++ )
   {
      // get index into buffer
      i_buffer = i + (*current).start_index;
      if ( i_buffer >= capacity )
      {
         i_buffer = i_buffer - capacity;
      }

      result[i] = (*current).buffer[i_buffer];
   }

   (*count) = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Circular_Array_count
*/

int32_t
Circular_Array_count( Prefix )( Circular_Array_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Circular_Array_capacity
*/

int32_t
Circular_Array_capacity( Prefix )( Circular_Array_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).capacity;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Circular_Array_is_empty
*/

int32_t
Circular_Array_is_empty( Prefix )( Circular_Array_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Circular_Array_put_first
*/

void
Circular_Array_put_first( Prefix )( Circular_Array_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_c = (*current).count; );
   INVARIANT( current );

   int32_t i = 0;
   int32_t capacity = 0;

   capacity = (*current).capacity;

   i = (*current).start_index - 1;
   if ( i < 0 )
   {
      i = i + capacity;
   }

   (*current).buffer[i] = value;

   (*current).start_index = i;
   (*current).count = (*current).count + 1;

   INVARIANT( current );
   POSTCONDITION( "item set", (*current).buffer[(*current).start_index] == value );
   POSTCONDITION( "count incremented", (*current).count == ( i_c + 1 ) );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_remove_first
*/

void
Circular_Array_remove_first( Prefix )( Circular_Array_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_c = (*current).count; );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t capacity = 0;

   capacity = (*current).capacity;

   i = (*current).start_index;

   (*current).buffer[i] = VALUE_DEFAULT;

   i = i + 1;
   if ( i >= capacity )
   {
      i = i - capacity;
   }

   (*current).start_index = i;
   (*current).count = (*current).count - 1;

   POSTCONDITION( "count decremented", (*current).count == ( i_c - 1 ) );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_remove_first_and_dispose
*/

void
Circular_Array_remove_first_and_dispose( Prefix )( Circular_Array_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_c = (*current).count; );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t capacity = 0;

   capacity = (*current).capacity;

   i = (*current).start_index;

   VALUE_DEEP_DISPOSE_FUNCTION( (*current).buffer[i] );
   (*current).buffer[i] = VALUE_DEFAULT;

   i = i + 1;
   if ( i >= capacity )
   {
      i = i - capacity;
   }

   (*current).start_index = i;
   (*current).count = (*current).count - 1;

   POSTCONDITION( "count decremented", (*current).count == ( i_c - 1 ) );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_put_last
*/

void
Circular_Array_put_last( Prefix )( Circular_Array_type( Prefix ) *current, Type value )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_c = (*current).count; );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t capacity = 0;

   capacity = (*current).capacity;

   i = (*current).start_index + (*current).count;
   if ( i >= capacity )
   {
      i = i - capacity;
   }

   (*current).buffer[i] = value;

   (*current).count = (*current).count + 1;

   POSTCONDITION( "count incremented", (*current).count == ( i_c + 1 ) );
   POSTCONDITION( "item set", (*current).buffer[ ( (*current).start_index + (*current).count - 1 ) % (*current).capacity ] == value );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_remove_last
*/

void
Circular_Array_remove_last( Prefix )( Circular_Array_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_c = (*current).count; );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t capacity = 0;

   capacity = (*current).capacity;

   i = (*current).start_index + (*current).count - 1;
   if ( i >= capacity )
   {
      i = i - capacity;
   }

   (*current).buffer[i] = VALUE_DEFAULT;

   (*current).count = (*current).count - 1;

   POSTCONDITION( "count decremented", (*current).count == ( i_c - 1 ) );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_remove_last_and_dispose
*/

void
Circular_Array_remove_last_and_dispose( Prefix )( Circular_Array_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_c = (*current).count; );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t capacity = 0;

   capacity = (*current).capacity;

   i = (*current).start_index + (*current).count - 1;
   if ( i >= capacity )
   {
      i = i - capacity;
   }

   VALUE_DEEP_DISPOSE_FUNCTION( (*current).buffer[i] );
   (*current).buffer[i] = VALUE_DEFAULT;

   (*current).count = (*current).count - 1;

   POSTCONDITION( "count decremented", (*current).count == ( i_c - 1 ) );
   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_replace
*/

void
Circular_Array_replace( Prefix )( Circular_Array_type( Prefix ) *current, Type value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   int32_t i = 0;
   int32_t capacity = 0;

   capacity = (*current).capacity;

   i = (*current).start_index + index;
   if ( i >= capacity )
   {
      i = i - capacity;
   }

   (*current).buffer[i] = value;

   INVARIANT( current );
   POSTCONDITION( "item set", (*current).buffer[ ( (*current).start_index + index ) % (*current).capacity ] == value );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_replace_and_dispose
*/

void
Circular_Array_replace_and_dispose( Prefix )( Circular_Array_type( Prefix ) *current, Type value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   int32_t i = 0;
   int32_t capacity = 0;

   capacity = (*current).capacity;

   i = (*current).start_index + index;
   if ( i >= capacity )
   {
      i = i - capacity;
   }

   VALUE_DEEP_DISPOSE_FUNCTION( (*current).buffer[i] );
   (*current).buffer[i] = value;

   INVARIANT( current );
   POSTCONDITION( "item set", (*current).buffer[ ( (*current).start_index + index ) % (*current).capacity ] == value );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_wipe_out
*/

void
Circular_Array_wipe_out( Prefix )( Circular_Array_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t capacity = 0;
   Type *buffer = NULL;

   buffer = (*current).buffer;
   capacity = (*current).capacity;

   for ( i = 0; i < capacity; i++ )
   {
      buffer[i] = VALUE_DEFAULT;
   }

   (*current).start_index = 0;
   (*current).count = 0;

   INVARIANT( current );
   POSTCONDITION( "current is empty", (*current).count == 0 );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_wipe_out_and_dispose
*/

void
Circular_Array_wipe_out_and_dispose( Prefix )( Circular_Array_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t capacity = 0;
   Type *buffer = NULL;

   buffer = (*current).buffer;
   capacity = (*current).capacity;

   for( i = 0; i < capacity; i++ )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( buffer[i] );
      buffer[i] = VALUE_DEFAULT;
   }

   (*current).start_index = 0;
   (*current).count = 0;

   INVARIANT( current );
   POSTCONDITION( "current is empty", (*current).count == 0 );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_set_count
*/

void
Circular_Array_set_count( Prefix )( Circular_Array_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", ( count >= 0 ) && ( count <= (*current).capacity ) );

   (*current).count = count;

   INVARIANT( current );
   POSTCONDITION( "count set", (*current).count == count );
   UNLOCK( (*current).mutex );

   return;
}

/**
   resize
*/
static
void
resize( Circular_Array_type( Prefix ) *current, int32_t new_capacity )
{
   int32_t capacity = 0;
   int32_t count = 0;
   int32_t start_index = 0;
   int32_t i = 0;
   int32_t index = 0;
   Type *array = NULL;
   Type *buffer = NULL;
   int32_t real_capacity = 0;

   // get local copies of class values for faster access
   capacity = (*current).capacity;
   start_index = (*current).start_index;
   count = (*current).count;
   buffer = (*current).buffer;

   // save current contents in array
   array = ( Type * ) calloc( count, sizeof( Type ) );
   CHECK( "array allocated correctly", array != NULL );

   for ( i = 0; i < count; i++ )
   {
      index = i + start_index;
      if ( index >= capacity )
      {
         index = index - capacity;
      }
      array[i] = buffer[index];
   }

   // get new capacity
   real_capacity = new_capacity;
   if ( real_capacity <= 0 )
   {
      real_capacity = 1;
   }

   // dispose of old buffer
   free( (*current).buffer );

   // allocate new buffer
   (*current).buffer
      = ( Type * ) calloc( real_capacity, sizeof( Type ) );
   CHECK( "(*current).buffer allocated correctly", (*current).buffer != NULL );

   buffer = (*current).buffer;

   // fill buffer with saved contents in array
   for ( i = 0; i < capacity; i++ )
   {
      buffer[i] = VALUE_DEFAULT;
   }

   for ( i = 0; i < count; i++ )
   {
      buffer[i] = array[i];
   }

   // dispose of array
   free( array );

   // set new capacity
   (*current).capacity = real_capacity;

   return;
}

/**
   Circular_Array_set_capacity
*/

void
Circular_Array_set_capacity( Prefix )( Circular_Array_type( Prefix ) *current, int32_t capacity )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "capacity ok", ( capacity >= 0 ) && ( capacity >= (*current).count ) );

   resize( current, capacity );

   INVARIANT( current );
   POSTCONDITION( "buffer ok", (*current).buffer != NULL );
   POSTCONDITION( "capacity set", ( ( capacity == 0 ) ? ( (*current).capacity == 1 ) : ( (*current).capacity == capacity ) ) );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_ensure_count
*/

void
Circular_Array_ensure_count( Prefix )( Circular_Array_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", count >= 0 );

   if ( (*current).count < count )
   {
      if ( (*current).capacity < count )
      {
         resize( current, count );
      }
      (*current).count = count;
   }

   INVARIANT( current );
   POSTCONDITION( "count ok", (*current).count >= count );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_fill_default
*/

void
Circular_Array_fill_default( Prefix )( Circular_Array_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t capacity = 0;
   Type *buffer = NULL;

   buffer = (*current).buffer;
   capacity = (*current).capacity;

   for ( i = 0; i < capacity; i++ )
   {
      buffer[i] = VALUE_DEFAULT;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_fill_default_and_dispose
*/

void
Circular_Array_fill_default_and_dispose( Prefix )( Circular_Array_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t capacity = 0;
   Type *buffer = NULL;

   buffer = (*current).buffer;
   capacity = (*current).capacity;

   for ( i = 0; i < capacity; i++ )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( (*current).buffer[i] );
      buffer[i] = VALUE_DEFAULT;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_replace_from_array
*/

void
Circular_Array_replace_from_array( Prefix )
(
   Circular_Array_type( Prefix ) *current,
   Type *array,
   int32_t array_count,
   int32_t start_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "array_count ok", array_count <= (*current).count );
   PRECONDITION( "start_index ok", start_index + array_count <= (*current).count );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t i_start = 0;
   int32_t index = 0;
   int32_t capacity = 0;
   int32_t buffer_start_index = 0;
   Type *buffer = NULL;

   buffer = (*current).buffer;
   capacity = (*current).capacity;
   buffer_start_index = (*current).start_index;

   i_start = start_index + buffer_start_index;
   if ( i_start >= capacity )
   {
      i_start = i_start - capacity ;
   }

   for ( i = 0; i < array_count; i++ )
   {
      index = i_start + i;
      if ( index >= capacity )
      {
         index = index - capacity;
      }
      buffer[index] = array[i];
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Circular_Array_replace_from_array_and_dispose
*/

void
Circular_Array_replace_from_array_and_dispose( Prefix )
(
   Circular_Array_type( Prefix ) *current,
   Type *array,
   int32_t array_count,
   int32_t start_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == CIRCULAR_ARRAY_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "array_count ok", array_count <= (*current).count );
   PRECONDITION( "start_index ok", start_index + array_count < (*current).count );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t i_start = 0;
   int32_t index = 0;
   int32_t capacity = 0;
   int32_t buffer_start_index = 0;
   Type *buffer = NULL;

   buffer = (*current).buffer;
   capacity = (*current).capacity;
   buffer_start_index = (*current).start_index;

   i_start = start_index + buffer_start_index;
   if ( i_start >= capacity )
   {
      i_start = i_start - capacity ;
   }

   for ( i = 0; i < array_count; i++ )
   {
      index = i_start + i;
      if ( index >= capacity )
      {
         index = index - capacity;
      }
      VALUE_DEEP_DISPOSE_FUNCTION( buffer[index] );
      buffer[index] = array[i];
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

