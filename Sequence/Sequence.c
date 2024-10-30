/**
 @file Sequence.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Sequences (resizable arrays)"

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

 Function definitions for the opaque Sequence_t type.

*/

#include "protocol.h"

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_Indexable.ph"
#endif // PROTOCOLS_ENABLED   

#include "Sequence.h"

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
   Sequence structure
   contiguous array of Type
*/

struct Sequence_struct( Prefix )
{

   PROTOCOLS_DEFINITION;

   int32_t _type;
   int32_t _item_type;

   int32_t count;
   int32_t capacity;
   Type *buffer;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};


/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
nonnegative_count( Sequence_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).count >= 0 );

   return result;
}

static
int32_t
valid_count_capacity( Sequence_type( Prefix ) *current )
{
   int32_t result = 1;

   result = ( (*current).capacity >= (*current).count );

   return result;
}

static
void invariant( Sequence_type( Prefix ) *current )
{
   assert( ( ( void ) "nonnegative count", nonnegative_count( current ) ) );
   assert( ( ( void ) "valid count and capacity", valid_count_capacity( current ) ) );
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
   Sequence_dispose( Prefix ),
   Sequence_deep_dispose( Prefix ),
   Sequence_is_equal( Prefix ),
   Sequence_is_deep_equal( Prefix ),
   Sequence_copy( Prefix ),
   Sequence_deep_copy( Prefix ),
   Sequence_clone( Prefix ),
   Sequence_deep_clone( Prefix )
};

static
void *
p_indexable_table[P_INDEXABLE_FUNCTION_COUNT]
=
{
   Sequence_count( Prefix ),
   Sequence_item( Prefix ),
   Sequence_replace( Prefix ),
   Sequence_replace_and_dispose( Prefix )
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

   }

   return result;
}

#endif // PROTOCOLS_ENABLED


/**
   Sequence_make
*/

Sequence_type( Prefix ) *
Sequence_make( Prefix )( void )
{
   // allocate sequence struct
   Sequence_type( Prefix ) *result
      = ( Sequence_type( Prefix ) * ) calloc( 1, sizeof( Sequence_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // allocate buffer
   (*result).buffer = ( Type * ) calloc( 1, sizeof( Type ) );
   CHECK( "(*result).buffer allocated correctly", (*result).buffer != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = SEQUENCE_TYPE;
   (*result)._item_type = Type_Code;

   // set count and capacity
   (*result).count = 0;
   (*result).capacity = 1;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "count set", (*result).count == 0 );
   POSTCONDITION( "capacity set", (*result).capacity == 1 );
   POSTCONDITION( "buffer set", (*result).buffer != NULL );

   return result;
}

/**
   Sequence_clone
*/

Sequence_type( Prefix ) *
Sequence_clone( Prefix )( Sequence_type( Prefix ) *current )
{
   PRECONDITION( "result ok", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );

   int32_t i = 0;

   // allocate result struct
   Sequence_type( Prefix ) * result
      = ( Sequence_type( Prefix ) * ) calloc( 1, sizeof( Sequence_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // allocate buffer
   (*result).buffer = ( Type * ) calloc( (*current).capacity, sizeof( Type ) );
   CHECK( "(*result).buffer allocated correctly", (*result).buffer != NULL );

   // set buffer
   for( i = 0; i < (*current).count; i++ )
   {
      (*result).buffer[i] = (*current).buffer[i];
   }

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = SEQUENCE_TYPE;
   (*result)._item_type = Type_Code;

   // set count and capacity
   (*result).count = (*current).count;
   (*result).capacity = (*current).capacity;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "count set", (*result).count == (*current).count );
   POSTCONDITION( "capacity set", (*result).capacity == (*current).capacity );
   POSTCONDITION( "buffer set", (*result).buffer != NULL );

   return result;
}

/**
   Sequence_deep_clone
*/

Sequence_type( Prefix ) *
Sequence_deep_clone( Prefix )( Sequence_type( Prefix ) *current )
{
   PRECONDITION( "result ok", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );

   int32_t i = 0;

   // allocate result struct
   Sequence_type( Prefix ) *result
      = ( Sequence_type( Prefix ) * ) calloc( 1, sizeof( Sequence_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // allocate buffer
   (*result).buffer = ( Type * ) calloc( (*current).capacity, sizeof( Type ) );
   CHECK( "(*result).buffer allocated correctly", (*result).buffer != NULL );

   // set buffer
   for( i = 0; i < (*current).count; i++ )
   {
      (*result).buffer[i] = VALUE_DEEP_CLONE_FUNCTION( (*current).buffer[i] );
   }

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = SEQUENCE_TYPE;
   (*result)._item_type = Type_Code;

   // set count and capacity
   (*result).count = (*current).count;
   (*result).capacity = (*current).capacity;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "count set", (*result).count == (*current).count );
   POSTCONDITION( "capacity set", (*result).capacity == (*current).capacity );
   POSTCONDITION( "buffer set", (*result).buffer != NULL );

   return result;
}

/**
   Sequence_make_n
*/

Sequence_type( Prefix ) *
Sequence_make_n( Prefix )( int32_t n )
{
   PRECONDITION( "n ok", n > 0 );

   // allocate result struct
   Sequence_type( Prefix ) *result
      = ( Sequence_type( Prefix ) * ) calloc( 1, sizeof( Sequence_type( Prefix ) ) );
   CHECK( "result allocated correctly", result != NULL );

   // allocate buffer
   (*result).buffer = ( Type * ) calloc( n, sizeof( Type ) );
   CHECK( "(*result).buffer allocated correctly", (*result).buffer != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type codes
   (*result)._type = SEQUENCE_TYPE;
   (*result)._item_type = Type_Code;

   // set count and capacity
   (*result).count = 0;
   (*result).capacity = n;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "count set", (*result).count == 0 );
   POSTCONDITION( "capacity set", (*result).capacity == n );
   POSTCONDITION( "buffer set", (*result).buffer != NULL );

   return result;
}

/**
   Sequence_make_from_array
*/

Sequence_type( Prefix ) *
Sequence_make_from_array( Prefix )( Type *array, int32_t count, int32_t capacity )
{
   PRECONDITION( "array ok", array != NULL );
   PRECONDITION( "count ok", count > 0 );
   PRECONDITION( "capacity ok", capacity >= count );

   int32_t i = 0;

   // allocate result struct
   Sequence_type( Prefix ) *result
      = ( Sequence_type( Prefix ) * ) calloc( 1, sizeof( Sequence_type( Prefix ) ) );
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
   (*result)._type = SEQUENCE_TYPE;
   (*result)._item_type = Type_Code;

   // set count and capacity
   (*result).count = count;
   (*result).capacity = capacity;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "count set", (*result).count == count );
   POSTCONDITION( "capacity set", (*result).capacity == capacity );
   POSTCONDITION( "buffer set", (*result).buffer != NULL );

   return result;
}

/**
   Sequence_is_equal
*/

int32_t
Sequence_is_equal( Prefix )( Sequence_type( Prefix ) *current, Sequence_type( Prefix ) *other )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "sequence ok", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == SEQUENCE_TYPE ) && ( (*other)._item_type == Type_Code ) );

   INVARIANT( current );

   int32_t result = 1;
   int32_t i = 0;

   // check count
   if ( (*current).count != (*other).count )
   {
      result = 0;
   }

   LOCK( (*other).mutex );

   for ( i = 0; i < (*other).count; i++ )
   {
      if ( result == 1 )
      {
         if ( (*current).buffer[i] != (*other).buffer[i] )
         {
            result = 0;
         }
      }
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return result;
}

/**
   Sequence_is_deep_equal
*/

int32_t
Sequence_is_deep_equal( Prefix )( Sequence_type( Prefix ) *current, Sequence_type( Prefix ) *other )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   PRECONDITION( "sequence ok", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == SEQUENCE_TYPE ) && ( (*other)._item_type == Type_Code ) );

   int32_t result = 1;
   int32_t i = 0;

   INVARIANT( current );

   // check count
   if ( (*current).count != (*other).count )
   {
      result = 0;
   }

   LOCK( (*other).mutex );

   for ( i = 0; i < (*other).count; i++ )
   {
      if ( result == 1 )
      {
         if ( VALUE_DEEP_EQUAL_FUNCTION( (*current).buffer[i], (*other).buffer[i] ) == 0 )
         {
            result = 0;
         }
      }
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return result;
}

/**
   Sequence_copy
*/

void
Sequence_copy( Prefix )( Sequence_type( Prefix ) *current, Sequence_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == SEQUENCE_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t i = 0;

   // empty out current

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

   // lock other
   LOCK( (*other).mutex );

   for ( i = 0; i < (*other).count; i++ )
   {
      (*current).buffer[i] = (*other).buffer[i];
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return;
}

/**
   Sequence_deep_copy
*/

void
Sequence_deep_copy( Prefix )( Sequence_type( Prefix ) *current, Sequence_type( Prefix ) *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type = Type_Code ) );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type ok", ( (*other)._type == SEQUENCE_TYPE ) && ( (*other)._item_type = Type_Code ) );

   INVARIANT( current );

   int32_t i = 0;

   // empty out current

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


   // lock other
   LOCK( (*other).mutex );

   for ( i = 0; i < (*other).count; i++ )
   {
      (*current).buffer[i] = VALUE_DEEP_CLONE_FUNCTION( (*other).buffer[i] );
   }

   // unlock other
   UNLOCK( (*other).mutex );

   INVARIANT( current );

   return;
}

/**
   Sequence_dispose
*/

void
Sequence_dispose( Prefix )( Sequence_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "type ok", ( (**current)._type == SEQUENCE_TYPE ) && ( (**current)._item_type == Type_Code ) );
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
   Sequence_deep_dispose
*/

void
Sequence_deep_dispose( Prefix )( Sequence_type( Prefix ) **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "type ok", ( (**current)._type == SEQUENCE_TYPE ) && ( (**current)._item_type == Type_Code ) );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete buffer items
   int32_t i = 0;
   for( i = 0; i < (**current).count; i++ )
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
   Sequence_item
*/

Type
Sequence_item( Prefix )( Sequence_type( Prefix ) *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   Type value = (*current).buffer[index];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   Sequence_as_array
*/

Type *
Sequence_as_array( Prefix )( Sequence_type( Prefix ) *current, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Type *result = ( Type * ) calloc( (*current).count + 1, sizeof( Type ) );
   CHECK( "result allocated correctly", result != NULL );

   int32_t i = 0;

   for( i = 0; i < (*current).count; i++ )
   {
      result[i] = (*current).buffer[i];
   }

   (*count) = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Sequence_count
*/

int32_t
Sequence_count( Prefix )( Sequence_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Sequence_capacity
*/

int32_t
Sequence_capacity( Prefix )( Sequence_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).capacity;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Sequence_is_empty
*/

int32_t
Sequence_is_empty( Prefix )( Sequence_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   Sequence_put
*/

void
Sequence_put( Prefix )( Sequence_type( Prefix ) *current, Type value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   (*current).buffer[index] = value;

   INVARIANT( current );
   POSTCONDITION( "item set", (*current).buffer[index] == value );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Sequence_replace
*/

void
Sequence_replace( Prefix )( Sequence_type( Prefix ) *current, Type value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   (*current).buffer[index] = value;

   INVARIANT( current );
   POSTCONDITION( "item set", (*current).buffer[index] == value );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Sequence_replace_and_dispose
*/

void
Sequence_replace_and_dispose( Prefix )( Sequence_type( Prefix ) *current, Type value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );

   VALUE_DEEP_DISPOSE_FUNCTION( (*current).buffer[index] );
   (*current).buffer[index] = value;

   INVARIANT( current );
   POSTCONDITION( "item set", (*current).buffer[index] == value );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Sequence_wipe_out
*/

void
Sequence_wipe_out( Prefix )( Sequence_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   (*current).count = 0;

   INVARIANT( current );
   POSTCONDITION( "current is empty", (*current).count == 0 );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Sequence_wipe_out_and_dispose
*/

void
Sequence_wipe_out_and_dispose( Prefix )( Sequence_type( Prefix ) *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   for( i = 0; i < (*current).count; i++ )
   {
      VALUE_DEEP_DISPOSE_FUNCTION( (*current).buffer[i] );
   }

   (*current).count = 0;

   INVARIANT( current );
   POSTCONDITION( "current is empty", (*current).count == 0 );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Sequence_set_count
*/

void
Sequence_set_count( Prefix )( Sequence_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
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
   Sequence_set_capacity
*/

void
Sequence_set_capacity( Prefix )( Sequence_type( Prefix ) *current, int32_t capacity )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "capacity ok", ( capacity >= 0 ) && ( capacity >= (*current).count ) );

   int32_t old_capacity = (*current).capacity;

   int32_t real_capacity = capacity;
   if ( real_capacity == 0 )
   {
      real_capacity = 1;
   }

   (*current).buffer
      = ( Type * ) realloc( (*current).buffer, real_capacity * sizeof( Type ) );
   CHECK( "(*current).buffer allocated correctly", (*current).buffer != NULL );

   (*current).capacity = real_capacity;

   // zero out buffer if capacity increased
   if ( real_capacity > old_capacity )
   {
      memset
      (
         &( (*current).buffer[old_capacity] ),
         0,
         ( real_capacity - old_capacity )*sizeof( Type )
      );
   }

   INVARIANT( current );
   POSTCONDITION( "buffer ok", (*current).buffer != NULL );
   POSTCONDITION( "capacity set", (*current).capacity == real_capacity );
   UNLOCK( (*current).mutex );

   return;
}

/**
   Sequence_ensure_count
*/

void
Sequence_ensure_count( Prefix )( Sequence_type( Prefix ) *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "type ok", ( (*current)._type == SEQUENCE_TYPE ) && ( (*current)._item_type == Type_Code ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", count >= 0 );

   int32_t old_capacity = (*current).capacity;

   if ( (*current).count < count )
   {
      if ( (*current).capacity < count )
      {
         (*current).buffer
            = ( Type * ) realloc( (*current).buffer, count * sizeof( Type ) );
         CHECK( "(*current).buffer allocated correctly", (*current).buffer != NULL );

         (*current).capacity = count;

         // zero out buffer if capacity increased
         if ( count > old_capacity )
         {
            memset
            (
               &( (*current).buffer[old_capacity] ),
               0,
               ( count - old_capacity )*sizeof( Type )
            );
         }
      }
      (*current).count = count;
   }

   INVARIANT( current );
   POSTCONDITION( "count ok", (*current).count >= count );
   UNLOCK( (*current).mutex );

   return;
}


/* End of file */

