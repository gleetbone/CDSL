/**
 @file Sequence.c
 @author Greg Lee
 @version 1.0.0
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

#include "Sequence.h"

#ifdef PROTOCOLS_ENABLED   
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Clonable.ph"
#include "P_Indexable.ph"
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

#define SEQUENCE_TYPE 0xA5000400

/**
   Sequence structure
   contiguous array of Type
*/

struct Sequence_struct( Prefix )
{
   
   PROTOCOLS_DEFINITION;

   int32_t type;
   int32_t item_type;
   
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
nonnegative_count( Sequence_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t
valid_count_capacity( Sequence_type( Prefix ) *p )
{
   int32_t result = 1;

   result = ( (*p).capacity >= (*p).count );

   return result;
}

static
void invariant( Sequence_type( Prefix ) *p )
{
   assert(( (void) "nonnegative count", nonnegative_count( p ) ));
   assert(( (void) "valid count and capacity", valid_count_capacity( p ) ));
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
   Sequence_dispose( Prefix ),
   Sequence_dispose_with_contents( Prefix ),
   Sequence_clone( Prefix ),
   Sequence_deep_clone( Prefix )
};

static
void *
p_indexable_table[P_INDEXABLE_FUNCTION_COUNT]
=
{
   Sequence_dispose( Prefix ),
   Sequence_dispose_with_contents( Prefix ),
   Sequence_count( Prefix ),
   Sequence_item( Prefix ),
   Sequence_replace( Prefix ),
   Sequence_replace_and_dispose( Prefix )
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
   Sequence_type( Prefix ) * sequence
      = ( Sequence_type( Prefix ) * ) calloc( 1, sizeof( Sequence_type( Prefix ) ) );

   // allocate buffer
   (*sequence).buffer = ( Type * ) calloc( 1, sizeof( Type ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( sequence );

   // set type codes
   (*sequence).type = SEQUENCE_TYPE;
   (*sequence).item_type = Type_Code;
   
   // set count and capacity
   (*sequence).count = 0;
   (*sequence).capacity = 1;

   MULTITHREAD_MUTEX_INIT( (*sequence).mutex );

   INVARIANT( sequence );
   POSTCONDITION( "count set", (*sequence).count == 0 );
   POSTCONDITION( "capacity set", (*sequence).capacity == 1 );
   POSTCONDITION( "buffer set", (*sequence).buffer != NULL );

   return sequence;
}

/**
   Sequence_make_n
*/

Sequence_type( Prefix ) *
Sequence_make_n( Prefix )( int32_t n )
{
   PRECONDITION( "n ok", n > 0 );

   // allocate sequence struct
   Sequence_type( Prefix ) * sequence
      = ( Sequence_type( Prefix ) * ) calloc( 1, sizeof( Sequence_type( Prefix ) ) );

   // allocate buffer
   (*sequence).buffer = ( Type * ) calloc( n, sizeof( Type ) );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( sequence );

   // set type codes
   (*sequence).type = SEQUENCE_TYPE;
   (*sequence).item_type = Type_Code;
   
   // set count and capacity
   (*sequence).count = 0;
   (*sequence).capacity = n;

   MULTITHREAD_MUTEX_INIT( (*sequence).mutex );

   INVARIANT( sequence );
   POSTCONDITION( "count set", (*sequence).count == 0 );
   POSTCONDITION( "capacity set", (*sequence).capacity == n );
   POSTCONDITION( "buffer set", (*sequence).buffer != NULL );

   return sequence;
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

   // allocate sequence struct
   Sequence_type( Prefix ) * sequence
      = ( Sequence_type( Prefix ) * ) calloc( 1, sizeof( Sequence_type( Prefix ) ) );

   // allocate buffer
   (*sequence).buffer = ( Type * ) calloc( capacity, sizeof( Type ) );

   // set buffer
   for( i=0; i<count; i++ )
   {
      (*sequence).buffer[i] = array[i];
   }

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( sequence );

   // set type codes
   (*sequence).type = SEQUENCE_TYPE;
   (*sequence).item_type = Type_Code;
   
   // set count and capacity
   (*sequence).count = count;
   (*sequence).capacity = capacity;

   MULTITHREAD_MUTEX_INIT( (*sequence).mutex );

   INVARIANT( sequence );
   POSTCONDITION( "count set", (*sequence).count == count );
   POSTCONDITION( "capacity set", (*sequence).capacity == capacity );
   POSTCONDITION( "buffer set", (*sequence).buffer != NULL );

   return sequence;
}

/**
   Sequence_dispose
*/

void
Sequence_dispose( Prefix )( Sequence_type( Prefix ) *sequence )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );

   // delete buffer
   free( (*sequence).buffer );

   MULTITHREAD_MUTEX_DESTROY( (*sequence).mutex );

   // delete sequence struct
   free( sequence );

   return;
}

/**
   Sequence_dispose_with_contents
*/

void
Sequence_dispose_with_contents( Prefix )( Sequence_type( Prefix ) *sequence )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );

   // delete buffer items
   int32_t i = 0;
   for( i = 0; i < (*sequence).count; i++ )
   {
      DISPOSE_FUNCTION( (*sequence).buffer[i] );
   }

   // delete buffer
   free( (*sequence).buffer );

   MULTITHREAD_MUTEX_DESTROY( (*sequence).mutex );

   // delete sequence struct
   free( sequence );

   return;
}

/**
   Sequence_item
*/

Type
Sequence_item( Prefix )( Sequence_type( Prefix ) *sequence, int32_t index )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );
   PRECONDITION( "index ok", ( index >= 0) && ( index < (*sequence).count ) );

   Type value = (*sequence).buffer[index];

   INVARIANT( sequence );
   UNLOCK( (*sequence).mutex );

   return value;
}

/**
   Sequence_as_array
*/

Type *
Sequence_as_array( Prefix )( Sequence_type( Prefix ) *sequence, int32_t *count )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );

   Type *result = ( Type * ) calloc( (*sequence).count + 1, sizeof( Type ) ); 
   
   int32_t i = 0;
   
   for( i=0; i<(*sequence).count; i++ )
   {
      result[i] = (*sequence).buffer[i];
   }

   (*count) = (*sequence).count;
   
   INVARIANT( sequence );
   UNLOCK( (*sequence).mutex );

   return result;
}

/**
   Sequence_count
*/

int32_t
Sequence_count( Prefix )( Sequence_type( Prefix ) *sequence )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );

   int32_t result = (*sequence).count;

   INVARIANT( sequence );
   UNLOCK( (*sequence).mutex );

   return result;
}

/**
   Sequence_capacity
*/

int32_t
Sequence_capacity( Prefix )( Sequence_type( Prefix ) *sequence )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );

   int32_t result = (*sequence).capacity;

   INVARIANT( sequence );
   UNLOCK( (*sequence).mutex );

   return result;
}

/**
   Sequence_is_empty
*/

int32_t
Sequence_is_empty( Prefix )( Sequence_type( Prefix ) *sequence )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );

   int32_t result = ( (*sequence).count == 0 );

   INVARIANT( sequence );
   UNLOCK( (*sequence).mutex );

   return result;
}

/**
   Sequence_put
*/

void
Sequence_put( Prefix )( Sequence_type( Prefix ) *sequence, Type value, int32_t index )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );
   PRECONDITION( "index ok", ( index >= 0) && ( index < (*sequence).count ) );

   (*sequence).buffer[index] = value;

   INVARIANT( sequence );
   POSTCONDITION( "item set", (*sequence).buffer[index] == value );
   UNLOCK( (*sequence).mutex );

   return;
}

/**
   Sequence_replace
*/

void
Sequence_replace( Prefix )( Sequence_type( Prefix ) *sequence, Type value, int32_t index )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );
   PRECONDITION( "index ok", ( index >= 0) && ( index < (*sequence).count ) );

   (*sequence).buffer[index] = value;

   INVARIANT( sequence );
   POSTCONDITION( "item set", (*sequence).buffer[index] == value );
   UNLOCK( (*sequence).mutex );

   return;
}

/**
   Sequence_replace_and_dispose
*/

void
Sequence_replace_and_dispose( Prefix )( Sequence_type( Prefix ) *sequence, Type value, int32_t index )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );
   PRECONDITION( "index ok", ( index >= 0) && ( index < (*sequence).count ) );

   DISPOSE_FUNCTION( (*sequence).buffer[index] );
   (*sequence).buffer[index] = value;

   INVARIANT( sequence );
   POSTCONDITION( "item set", (*sequence).buffer[index] == value );
   UNLOCK( (*sequence).mutex );

   return;
}

/**
   Sequence_wipe_out
*/

void
Sequence_wipe_out( Prefix )( Sequence_type( Prefix ) *sequence )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );

   (*sequence).count = 0;

   INVARIANT( sequence );
   POSTCONDITION( "sequence is empty", (*sequence).count == 0 );
   UNLOCK( (*sequence).mutex );

   return;
}

/**
   Sequence_wipe_out_and_dispose
*/

void
Sequence_wipe_out_and_dispose( Prefix )( Sequence_type( Prefix ) *sequence )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );

   int32_t i = 0;
   for( i=0; i < (*sequence).count; i++ )
   {
      DISPOSE_FUNCTION( (*sequence).buffer[i] );
   }

   (*sequence).count = 0;

   INVARIANT( sequence );
   POSTCONDITION( "sequence is empty", (*sequence).count == 0 );
   UNLOCK( (*sequence).mutex );

   return;
}

/**
   Sequence_set_count
*/

void
Sequence_set_count( Prefix )( Sequence_type( Prefix ) *sequence, int32_t count )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );
   PRECONDITION( "count ok", ( count >= 0) && ( count <= (*sequence).capacity ) );

   (*sequence).count = count;

   INVARIANT( sequence );
   POSTCONDITION( "count set", (*sequence).count == count );
   UNLOCK( (*sequence).mutex );

   return;
}

/**
   Sequence_set_capacity
*/

void
Sequence_set_capacity( Prefix )( Sequence_type( Prefix ) *sequence, int32_t capacity )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );
   PRECONDITION( "capacity ok", ( capacity >= 0) && ( capacity >= (*sequence).count ) );

   int32_t old_capacity = (*sequence).capacity;

   int32_t real_capacity = capacity;
   if ( real_capacity == 0 )
   {
      real_capacity = 1;
   }

   (*sequence).buffer
      = ( Type * ) realloc( (*sequence).buffer, real_capacity*sizeof( Type ) );
   (*sequence).capacity = real_capacity;

   // zero out buffer if capacity increased
   if ( real_capacity > old_capacity )
   {
      memset
      (
         &((*sequence).buffer[old_capacity]),
         0,
         ( real_capacity - old_capacity)*sizeof( Type )
      );
   }

   INVARIANT( sequence );
   POSTCONDITION( "buffer ok", (*sequence).buffer != NULL );
   POSTCONDITION( "capacity set", (*sequence).capacity == real_capacity );
   UNLOCK( (*sequence).mutex );

   return;
}

/**
   Sequence_ensure_count
*/

void
Sequence_ensure_count( Prefix )( Sequence_type( Prefix ) *sequence, int32_t count )
{
   PRECONDITION( "sequence not null", sequence != NULL );
   PRECONDITION( "type ok", ( (*sequence).type == SEQUENCE_TYPE ) && ( (*sequence).item_type == Type_Code ) );
   LOCK( (*sequence).mutex );
   INVARIANT( sequence );
   PRECONDITION( "count ok", count >= 0 );

   int32_t old_capacity = (*sequence).capacity;

   if ( (*sequence).count < count )
   {
      if ( (*sequence).capacity < count )
      {
         (*sequence).buffer
            = ( Type * ) realloc( (*sequence).buffer, count*sizeof( Type ) );
         (*sequence).capacity = count;

         // zero out buffer if capacity increased
         if ( count > old_capacity )
         {
            memset
            (
               &((*sequence).buffer[old_capacity]),
               0,
               ( count - old_capacity)*sizeof( Type )
            );
         }
      }
      (*sequence).count = count;
   }

   INVARIANT( sequence );
   POSTCONDITION( "count ok", (*sequence).count >= count );
   UNLOCK( (*sequence).mutex );

   return;
}


/**
   Sequence_clone
*/

Sequence_type( Prefix ) *
Sequence_clone( Prefix )( Sequence_type( Prefix ) *other )
{
   PRECONDITION( "sequence ok", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == SEQUENCE_TYPE ) && ( (*other).item_type == Type_Code ) );

   int32_t i = 0;

   // allocate sequence struct
   Sequence_type( Prefix ) * sequence
      = ( Sequence_type( Prefix ) * ) calloc( 1, sizeof( Sequence_type( Prefix ) ) );

   // allocate buffer
   (*sequence).buffer = ( Type * ) calloc( (*other).capacity, sizeof( Type ) );

   // set buffer
   for( i=0; i<(*other).count; i++ )
   {
      (*sequence).buffer[i] = (*other).buffer[i];
   }

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( sequence );

   // set type codes
   (*sequence).type = SEQUENCE_TYPE;
   (*sequence).item_type = Type_Code;
   
   // set count and capacity
   (*sequence).count = (*other).count;
   (*sequence).capacity = (*other).capacity;

   MULTITHREAD_MUTEX_INIT( (*sequence).mutex );

   INVARIANT( sequence );
   POSTCONDITION( "count set", (*sequence).count == (*other).count );
   POSTCONDITION( "capacity set", (*sequence).capacity == (*other).capacity );
   POSTCONDITION( "buffer set", (*sequence).buffer != NULL );

   return sequence;
}

/**
   Sequence_deep_clone
*/

Sequence_type( Prefix ) *
Sequence_deep_clone( Prefix )( Sequence_type( Prefix ) *other )
{
   PRECONDITION( "sequence ok", other != NULL );
   PRECONDITION( "other type ok", ( (*other).type == SEQUENCE_TYPE ) && ( (*other).item_type == Type_Code ) );

   int32_t i = 0;

   // allocate sequence struct
   Sequence_type( Prefix ) * sequence
      = ( Sequence_type( Prefix ) * ) calloc( 1, sizeof( Sequence_type( Prefix ) ) );

   // allocate buffer
   (*sequence).buffer = ( Type * ) calloc( (*other).capacity, sizeof( Type ) );

   // set buffer
   for( i=0; i<(*other).count; i++ )
   {
      (*sequence).buffer[i] = COPY_FUNCTION( (*other).buffer[i] );
   }

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( sequence );

   // set type codes
   (*sequence).type = SEQUENCE_TYPE;
   (*sequence).item_type = Type_Code;
   
   // set count and capacity
   (*sequence).count = (*other).count;
   (*sequence).capacity = (*other).capacity;

   MULTITHREAD_MUTEX_INIT( (*sequence).mutex );

   INVARIANT( sequence );
   POSTCONDITION( "count set", (*sequence).count == (*other).count );
   POSTCONDITION( "capacity set", (*sequence).capacity == (*other).capacity );
   POSTCONDITION( "buffer set", (*sequence).buffer != NULL );

   return sequence;
}

/* End of file */

