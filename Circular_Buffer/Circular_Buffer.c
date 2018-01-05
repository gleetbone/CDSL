/**
 @file Circular_Buffer.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Circular buffer"
 
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

 Function definitions for the opaque Circular_Buffer_t type.

*/

#include "Circular_Buffer.h"

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

#define CIRCULAR_BUFFER_TYPE 0xA5000800

/**
   Circular buffer structure
*/

struct Circular_Buffer_struct( Prefix )
{
   int32_t type;
   int32_t item_type;
   
   Type *buffer;
   int32_t capacity;
   int32_t read_index;
   int32_t write_index;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   cbuffer_count
*/

static
int32_t
cbuffer_count( Circular_Buffer_type( Prefix ) *cbuffer )
{
   int32_t count = 0;
   int32_t result = 0;
   
   count = (*cbuffer).write_index - (*cbuffer).read_index;
   if ( count < 0 )
   {
      count = count + (*cbuffer).capacity;
   }
   
   result = count;
   
   return result;
}

/**
   Invariant
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
nonnegative_count( Circular_Buffer_type( Prefix ) *p )
{
   int32_t count = 0;
   int32_t result = 1;

   count = cbuffer_count( p );
   result = ( count >= 0 );

   return result;
}

static
int32_t
indices_ok( Circular_Buffer_type( Prefix ) *p )
{
   int32_t result = 1;

   result 
      =  ( (*p).read_index < (*p).capacity )
         &&
         ( (*p).read_index >= 0 )
         &&
         ( (*p).write_index < (*p).capacity )
         &&
         ( (*p).write_index >= 0 );

   return result;
}

static
int32_t
buffer_ok( Circular_Buffer_type( Prefix ) *p )
{
   int32_t result = 0;

   result = ( (*p).buffer != NULL );

   return result;
}

static
void invariant( Circular_Buffer_type( Prefix ) *p )
{
   assert(((void) "nonnegative count", nonnegative_count( p ) ));
   assert(((void) "indices ok", indices_ok( p ) ));
   assert(((void) "buffer ok", buffer_ok( p ) ));
   return;
}

#endif


/**
   Circular_Buffer_make
*/

Circular_Buffer_type( Prefix ) *
Circular_Buffer_make( Prefix )( int32_t capacity )
{
   // allocate cbuffer struct
   Circular_Buffer_type( Prefix ) * cbuffer
      = ( Circular_Buffer_type( Prefix ) * ) calloc( 1, sizeof( Circular_Buffer_type( Prefix ) ) );

   // set type
   (*cbuffer).type = CIRCULAR_BUFFER_TYPE;
   (*cbuffer).item_type = Type_Code;

   // set buffer
   (*cbuffer).buffer = ( Type * ) calloc( capacity + 1, sizeof( Type * ) );

   // set capacity
   (*cbuffer).capacity = capacity + 1;
   
   // set indices
   (*cbuffer).read_index = 0;
   (*cbuffer).write_index = 0;
   
   MULTITHREAD_MUTEX_INIT( (*cbuffer).mutex );

   INVARIANT( cbuffer );

   return cbuffer;
}

/**
   Circular_Buffer_dispose
*/

void
Circular_Buffer_dispose( Prefix )( Circular_Buffer_type( Prefix ) *cbuffer )
{
   PRECONDITION( "cbuffer not null", cbuffer != NULL );
   PRECONDITION( "cbuffer type OK", ( (*cbuffer).type == CIRCULAR_BUFFER_TYPE ) && ( (*cbuffer).item_type == Type_Code ) );
   LOCK( (*cbuffer).mutex );
   INVARIANT( cbuffer );

   // free buffer
   free( (*cbuffer).buffer );

   MULTITHREAD_MUTEX_DESTROY( (*cbuffer).mutex );

   // delete cbuffer struct
   free( cbuffer );

   return;
}


/**
   Circular_Buffer_item
*/

Type
Circular_Buffer_item( Prefix )( Circular_Buffer_type( Prefix ) *cbuffer )
{
   PRECONDITION( "cbuffer not null", cbuffer != NULL );
   PRECONDITION( "cbuffer type OK", ( (*cbuffer).type == CIRCULAR_BUFFER_TYPE ) && ( (*cbuffer).item_type == Type_Code ) );
   LOCK( (*cbuffer).mutex );
   INVARIANT( cbuffer );
   PRECONDITION( "read index ok", ( (*cbuffer).read_index >= 0 ) && ( (*cbuffer).read_index < (*cbuffer).capacity )  );

   Type value = (*cbuffer).buffer[ (*cbuffer).read_index ];

   INVARIANT( cbuffer );
   UNLOCK( (*cbuffer).mutex );

   return value;
}

/**
   Circular_Buffer_count
*/

int32_t
Circular_Buffer_count( Prefix )( Circular_Buffer_type( Prefix ) *cbuffer )
{
   PRECONDITION( "cbuffer not null", cbuffer != NULL );
   PRECONDITION( "cbuffer type OK", ( (*cbuffer).type == CIRCULAR_BUFFER_TYPE ) && ( (*cbuffer).item_type == Type_Code ) );
   LOCK( (*cbuffer).mutex );
   INVARIANT( cbuffer );

   int32_t count = cbuffer_count( cbuffer );

   INVARIANT( cbuffer );
   UNLOCK( (*cbuffer).mutex );

   return count;
}

/**
   Circular_Buffer_capacity
*/

int32_t
Circular_Buffer_capacity( Prefix )( Circular_Buffer_type( Prefix ) *cbuffer )
{
   PRECONDITION( "cbuffer not null", cbuffer != NULL );
   PRECONDITION( "cbuffer type OK", ( (*cbuffer).type == CIRCULAR_BUFFER_TYPE ) && ( (*cbuffer).item_type == Type_Code ) );
   LOCK( (*cbuffer).mutex );
   INVARIANT( cbuffer );

   int32_t capacity = (*cbuffer).capacity - 1;

   INVARIANT( cbuffer );
   UNLOCK( (*cbuffer).mutex );

   return capacity;
}

/**
   Circular_Buffer_is_empty
*/

int32_t
Circular_Buffer_is_empty( Prefix )( Circular_Buffer_type( Prefix ) *cbuffer )
{
   PRECONDITION( "cbuffer not null", cbuffer != NULL );
   PRECONDITION( "cbuffer type OK", ( (*cbuffer).type == CIRCULAR_BUFFER_TYPE ) && ( (*cbuffer).item_type == Type_Code ) );
   LOCK( (*cbuffer).mutex );
   INVARIANT( cbuffer );

   int32_t result = ( (*cbuffer).read_index ==  (*cbuffer).write_index );

   INVARIANT( cbuffer );
   UNLOCK( (*cbuffer).mutex );

   return result;
}

/**
   Circular_Buffer_is_full
*/

int32_t
Circular_Buffer_is_full( Prefix )( Circular_Buffer_type( Prefix ) *cbuffer )
{
   PRECONDITION( "cbuffer not null", cbuffer != NULL );
   PRECONDITION( "cbuffer type OK", ( (*cbuffer).type == CIRCULAR_BUFFER_TYPE ) && ( (*cbuffer).item_type == Type_Code ) );
   LOCK( (*cbuffer).mutex );
   INVARIANT( cbuffer );

   int32_t count = cbuffer_count( cbuffer );
   
   int32_t result = ( count >= (*cbuffer).capacity - 1 );

   INVARIANT( cbuffer );
   UNLOCK( (*cbuffer).mutex );

   return result;
}

/**
   Circular_Buffer_forth
*/

void
Circular_Buffer_forth( Prefix )( Circular_Buffer_type( Prefix ) *cbuffer )
{
   PRECONDITION( "cbuffer not null", cbuffer != NULL );
   PRECONDITION( "cbuffer type OK", ( (*cbuffer).type == CIRCULAR_BUFFER_TYPE ) && ( (*cbuffer).item_type == Type_Code ) );
   LOCK( (*cbuffer).mutex );
   INVARIANT( cbuffer );
   PRECONDITION( "cbuffer not empty", (*cbuffer).write_index != (*cbuffer).read_index );

   (*cbuffer).read_index = ( (*cbuffer).read_index + 1 ) % (*cbuffer).capacity; 

   INVARIANT( cbuffer );
   UNLOCK( (*cbuffer).mutex );

   return;
}

/**
   Circular_Buffer_put
*/

void
Circular_Buffer_put( Prefix )( Circular_Buffer_type( Prefix ) *cbuffer, Type value )
{
   PRECONDITION( "cbuffer not null", cbuffer != NULL );
   PRECONDITION( "cbuffer type OK", ( (*cbuffer).type == CIRCULAR_BUFFER_TYPE ) && ( (*cbuffer).item_type == Type_Code ) );
   LOCK( (*cbuffer).mutex );
   INVARIANT( cbuffer );
   PRECONDITION( "cbuffer not full", ( cbuffer_count( cbuffer ) != ( (*cbuffer).capacity - 1 ) ) );
   PRECONDITION( "write index ok", ( (*cbuffer).write_index >= 0 ) && ( (*cbuffer).write_index < (*cbuffer).capacity )  );

   (*cbuffer).buffer[ (*cbuffer).write_index ] = value;
   (*cbuffer).write_index = ( (*cbuffer).write_index + 1 ) % (*cbuffer).capacity;
   
   INVARIANT( cbuffer );
   UNLOCK( (*cbuffer).mutex );

   return;
}

/**
   Circular_Buffer_wipe_out
*/

void
Circular_Buffer_wipe_out( Prefix )( Circular_Buffer_type( Prefix ) *cbuffer )
{
   PRECONDITION( "cbuffer not null", cbuffer != NULL );
   PRECONDITION( "cbuffer type OK", ( (*cbuffer).type == CIRCULAR_BUFFER_TYPE ) && ( (*cbuffer).item_type == Type_Code ) );
   LOCK( (*cbuffer).mutex );
   INVARIANT( cbuffer );

   (*cbuffer).read_index = 0;
   (*cbuffer).write_index = 0;
   
   INVARIANT( cbuffer );
   POSTCONDITION( "cbuffer is empty", cbuffer_count( cbuffer ) == 0 );
   UNLOCK( (*cbuffer).mutex );

   return;
}


/* End of file */

