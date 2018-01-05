/**
 @file Raw_Buffer.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Raw Buffer (byte array addressable by word size and endianness)"
 
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

 Function definitions for the opaque raw_buffer_t type.

*/

#include "Raw_Buffer.h"
 
#ifdef __cplusplus
extern "C" {
#endif
 
#include <string.h>
#include <stdlib.h>
#include "String_utilities.h"
   
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "base.h"
#include "dbc.h"

/**
   defines
*/

#define RAW_BUFFER_TYPE 0xA5000704


/**
   raw_buffer structure
*/

struct raw_buffer_struct
{
   int32_t type;
   
   int32_t count;
   uint8_t *buffer;
   
   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Invariant
*/   

#if INVARIANT_CONDITIONAL != 0

static
int32_t 
nonnegative_count( raw_buffer_t *p )
{
   int32_t result = 1;
   
   result = ( (*p).count >= 0 );
   
   return result;
}

static
int32_t 
base_pointer_not_void( raw_buffer_t *p )
{
   int32_t result = 1;
   
   result = ( (*p).buffer != NULL );
   
   return result;
}

static
void invariant( raw_buffer_t *p )
{
   assert(((void) "nonnegative count", nonnegative_count( p ) ));
   assert(((void) "base pointer not void", base_pointer_not_void( p ) ));
   return;
}

#else

static
void invariant( p )
{
   return;
}

#endif

/** 
   raw_buffer_make
*/

raw_buffer_t *
raw_buffer_make( int32_t n )
{
   PRECONDITION( "n ok", n > 0 );
   
   // allocate raw_buffer struct
   raw_buffer_t * raw_buffer 
      = ( raw_buffer_t * ) calloc( 1, sizeof( raw_buffer_t ) );
      
   // set type
   (*raw_buffer).type = RAW_BUFFER_TYPE;
   
   // allocate buffer
   (*raw_buffer).buffer = ( uint8_t * ) calloc( n, sizeof( uint8_t ) );
    
   // set count
   (*raw_buffer).count = n;
   
   MULTITHREAD_MUTEX_INIT( (*raw_buffer).mutex );

   INVARIANT( raw_buffer );
   POSTCONDITION( "count set", (*raw_buffer).count == n );
   POSTCONDITION( "buffer set", (*raw_buffer).buffer != NULL );
   
   return raw_buffer;
}

/** 
   raw_buffer_make_copy_from
*/

raw_buffer_t *
raw_buffer_make_copy_from( raw_buffer_t *other )
{
   PRECONDITION( "other ok", other != NULL );
   
   // allocate raw_buffer struct
   raw_buffer_t *result 
      = ( raw_buffer_t * ) calloc( 1, sizeof( raw_buffer_t ) );
      
   // set type
   (*result).type = RAW_BUFFER_TYPE;
   
   // allocate buffer
   (*result).buffer = ( uint8_t * ) calloc( (*other).count, sizeof( uint8_t ) );
      
   // set count
   (*result).count = (*other).count;

   // copy contents
   memcpy( (*result).buffer, (*other).buffer, (*other).count );
   
   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "count set", (*result).count == (*other).count );
   POSTCONDITION( "buffer set", (*result).buffer != NULL );
   
   return result;
}

/** 
   raw_buffer_make_from_pointer
*/

raw_buffer_t *
raw_buffer_make_from_pointer( uint8_t *p, int32_t n )
{
   PRECONDITION( "pointer ok", p != NULL );
   PRECONDITION( "n ok", n > 0 );
   
   // allocate raw_buffer struct
   raw_buffer_t * raw_buffer 
      = ( raw_buffer_t * ) calloc( 1, sizeof( raw_buffer_t ) );
      
   // set type
   (*raw_buffer).type = RAW_BUFFER_TYPE;
   
   // set buffer
   (*raw_buffer).buffer = p;
      
   // set count
   (*raw_buffer).count = n;

   MULTITHREAD_MUTEX_INIT( (*raw_buffer).mutex );

   INVARIANT( raw_buffer );
   POSTCONDITION( "count set", (*raw_buffer).count == n );
   POSTCONDITION( "buffer set", (*raw_buffer).buffer == p );
   
   return raw_buffer;
}

/** 
   raw_buffer_dispose
*/

void
raw_buffer_dispose( raw_buffer_t *raw_buffer )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   MULTITHREAD_MUTEX_DESTROY( (*raw_buffer).mutex );

   // delete raw_buffer struct
   free( raw_buffer );

   return;
}

/** 
   raw_buffer_dispose_with_contents
*/

void
raw_buffer_dispose_with_contents( raw_buffer_t *raw_buffer )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // delete buffer
   free( (*raw_buffer).buffer );

   MULTITHREAD_MUTEX_DESTROY( (*raw_buffer).mutex );

   // delete raw_buffer struct
   free( raw_buffer );

   return;
}

/**
   raw_buffer_is_same
*/

int32_t
raw_buffer_is_same( raw_buffer_t *raw_buffer, raw_buffer_t *other )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other).type == RAW_BUFFER_TYPE );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );

   int32_t result = 1;
   
   if ( 
         ( (*raw_buffer).count != (*other).count )
         ||
         ( (*raw_buffer).buffer != (*other).buffer )
      )
   {
      result = 0;
   }
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}


/**
   raw_buffer_copy_from
*/

void
raw_buffer_copy_from( raw_buffer_t *raw_buffer, raw_buffer_t *other )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other).type == RAW_BUFFER_TYPE );
   PRECONDITION( "same size", (*raw_buffer).count == (*other).count );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );

   memcpy( (*raw_buffer).buffer, (*other).buffer, (*raw_buffer).count );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}



/**
   raw_buffer_subcopy
*/

void
raw_buffer_subcopy
( 
   raw_buffer_t *raw_buffer, 
   raw_buffer_t *other, 
   int32_t destination_index,  
   int32_t source_index,  
   int32_t count  
)
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other).type == RAW_BUFFER_TYPE );
   PRECONDITION( "source index ok", ( source_index >= 0 ) && ( source_index <= (*other).count  - count ) );
   PRECONDITION( "destination index ok", ( destination_index >= 0 ) && ( destination_index < (*raw_buffer).count  - count ) );
   PRECONDITION( "count ok", ( count >= 0 ) && ( count <= (*raw_buffer).count ) && ( count <= (*other).count ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );

   // copy the bytes
   memcpy
   ( 
      (*raw_buffer).buffer + destination_index, 
      (*other).buffer + source_index, 
      count 
   );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}


/**
   raw_buffer_clear
*/

void
raw_buffer_clear( raw_buffer_t *raw_buffer )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   memset( (*raw_buffer).buffer, 0, (*raw_buffer).count );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}


/**
   raw_buffer_append
*/

void
raw_buffer_append( raw_buffer_t *raw_buffer, raw_buffer_t *other )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other).type == RAW_BUFFER_TYPE );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );

   // make buffer large enough
   (*raw_buffer).buffer 
      = ( uint8_t * ) realloc( (*raw_buffer).buffer, (*raw_buffer).count + (*other).count );
      
   // copy the bytes
   memcpy
   ( 
      (*raw_buffer).buffer + (*raw_buffer).count, 
      (*other).buffer, 
      (*other).count 
   );
   
   // update count
   (*raw_buffer).count = (*raw_buffer).count + (*other).count;
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_resize
*/

void
raw_buffer_resize( raw_buffer_t *raw_buffer, int32_t count )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "count ok", count >= 0 );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );

   // make buffer large enough
   (*raw_buffer).buffer 
      = ( uint8_t * ) realloc( (*raw_buffer).buffer, count );
      
   // zero new bytes if new size is larger
   if ( count > (*raw_buffer).count )
   {
      memset
      ( 
         (*raw_buffer).buffer + (*raw_buffer).count, 
         0, 
         count - (*raw_buffer).count 
      );
   }
   
   // set count
   (*raw_buffer).count = count;
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_base
*/

uint8_t *
raw_buffer_base( raw_buffer_t *raw_buffer )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   uint8_t *result = (*raw_buffer).buffer;
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_count
*/

int32_t
raw_buffer_count( raw_buffer_t *raw_buffer )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   int32_t result = (*raw_buffer).count;
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_read_char
*/

char_t
raw_buffer_read_char( raw_buffer_t *raw_buffer, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( char_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // get result
   char_t result = 0;
   
   // copy data into result
   memcpy( &result, &( (*raw_buffer).buffer[index] ), sizeof( char_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_read_uint8
*/

uint8_t
raw_buffer_read_uint8( raw_buffer_t *raw_buffer, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( uint8_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // get result
   uint8_t result = 0;
   
   // copy data into result
   memcpy( &result, &( (*raw_buffer).buffer[index] ), sizeof( uint8_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_read_uint16
*/

uint16_t
raw_buffer_read_uint16( raw_buffer_t *raw_buffer, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( uint16_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // get result
   uint16_t result = 0;
   
   // copy data into result
   memcpy( &result, &( (*raw_buffer).buffer[index] ), sizeof( uint16_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_read_uint32
*/

uint32_t
raw_buffer_read_uint32( raw_buffer_t *raw_buffer, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( uint32_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // get result
   uint32_t result = 0;
   
   // copy data into result
   memcpy( &result, &( (*raw_buffer).buffer[index] ), sizeof( uint32_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_read_uint64
*/

uint64_t
raw_buffer_read_uint64( raw_buffer_t *raw_buffer, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( uint64_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // get result
   uint64_t result = 0;
   
   // copy data into result
   memcpy( &result, &( (*raw_buffer).buffer[index] ), sizeof( uint64_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}


/**
   raw_buffer_read_int8
*/

int8_t
raw_buffer_read_int8( raw_buffer_t *raw_buffer, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( int8_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // get result
   int8_t result = 0;
   
   // copy data into result
   memcpy( &result, &( (*raw_buffer).buffer[index] ), sizeof( int8_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_read_int16
*/

int16_t
raw_buffer_read_int16( raw_buffer_t *raw_buffer, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( int16_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // get result
   int16_t result = 0;
   
   // copy data into result
   memcpy( &result, &( (*raw_buffer).buffer[index] ), sizeof( int16_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_read_int32
*/

int32_t
raw_buffer_read_int32( raw_buffer_t *raw_buffer, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( int32_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // get result
   int32_t result = 0;
   
   // copy data into result
   memcpy( &result, &( (*raw_buffer).buffer[index] ), sizeof( int32_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_read_int64
*/

int64_t
raw_buffer_read_int64( raw_buffer_t *raw_buffer, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( int64_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // get result
   int64_t result = 0;
   
   // copy data into result
   memcpy( &result, &( (*raw_buffer).buffer[index] ), sizeof( int64_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_read_float32
*/

float32_t
raw_buffer_read_float32( raw_buffer_t *raw_buffer, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( float32_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // get result
   float32_t result = 0;
   
   // copy data into result
   memcpy( &result, &( (*raw_buffer).buffer[index] ), sizeof( float32_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_read_float64
*/

float64_t
raw_buffer_read_float64( raw_buffer_t *raw_buffer, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( float64_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // get result
   float64_t result = 0;
   
   // copy data into result
   memcpy( &result, &( (*raw_buffer).buffer[index] ), sizeof( float64_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_read_pointer
*/

void *
raw_buffer_read_pointer( raw_buffer_t *raw_buffer, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( void * ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // get result
   void *result = NULL;
   
   // copy data into result
   memcpy( &result, &( (*raw_buffer).buffer[index] ), sizeof( void * ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}


/**
   raw_buffer_put_char
*/

void
raw_buffer_put_char( raw_buffer_t *raw_buffer, char_t value, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( char_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // copy data into buffer
   memcpy( &( (*raw_buffer).buffer[index] ), &value, sizeof( char_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_put_uint8
*/

void
raw_buffer_put_uint8( raw_buffer_t *raw_buffer, uint8_t value, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( uint8_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // copy data into buffer
   memcpy( &( (*raw_buffer).buffer[index] ), &value, sizeof( uint8_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_put_uint16
*/

void
raw_buffer_put_uint16( raw_buffer_t *raw_buffer, uint16_t value, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( uint16_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // copy data into buffer
   memcpy( &( (*raw_buffer).buffer[index] ), &value, sizeof( uint16_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_put_uint32
*/

void
raw_buffer_put_uint32( raw_buffer_t *raw_buffer, uint32_t value, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( uint32_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // copy data into buffer
   memcpy( &( (*raw_buffer).buffer[index] ), &value, sizeof( uint32_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_put_uint64
*/

void
raw_buffer_put_uint64( raw_buffer_t *raw_buffer, uint64_t value, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( uint64_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // copy data into buffer
   memcpy( &( (*raw_buffer).buffer[index] ), &value, sizeof( uint64_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_put_int8
*/

void
raw_buffer_put_int8( raw_buffer_t *raw_buffer, int8_t value, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( int8_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // copy data into buffer
   memcpy( &( (*raw_buffer).buffer[index] ), &value, sizeof( int8_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_put_int16
*/

void
raw_buffer_put_int16( raw_buffer_t *raw_buffer, int16_t value, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( int16_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // copy data into buffer
   memcpy( &( (*raw_buffer).buffer[index] ), &value, sizeof( int16_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_put_int32
*/

void
raw_buffer_put_int32( raw_buffer_t *raw_buffer, int32_t value, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( int32_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // copy data into buffer
   memcpy( &( (*raw_buffer).buffer[index] ), &value, sizeof( int32_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_put_int64
*/

void
raw_buffer_put_int64( raw_buffer_t *raw_buffer, int64_t value, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( int64_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // copy data into buffer
   memcpy( &( (*raw_buffer).buffer[index] ), &value, sizeof( int64_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_put_float32
*/

void
raw_buffer_put_float32( raw_buffer_t *raw_buffer, float32_t value, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( float32_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // copy data into buffer
   memcpy( &( (*raw_buffer).buffer[index] ), &value, sizeof( float32_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_put_float64
*/

void
raw_buffer_put_float64( raw_buffer_t *raw_buffer, float64_t value, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( float64_t ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // copy data into buffer
   memcpy( &( (*raw_buffer).buffer[index] ), &value, sizeof( float64_t ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_put_pointer
*/

void
raw_buffer_put_pointer( raw_buffer_t *raw_buffer, void *value, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*raw_buffer).count - sizeof( void * ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // copy data into buffer
   memcpy( &( (*raw_buffer).buffer[index] ), &value, sizeof( void * ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}


/**
   raw_buffer_read_string_zero_terminated
*/

string_t *
raw_buffer_read_string_zero_terminated( raw_buffer_t *raw_buffer, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*raw_buffer).count ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // make result
   string_t *result 
      = string_make_from_cstring( ( char_t * ) &( (*raw_buffer).buffer[index] ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_read_cstring_zero_terminated
*/

char_t *
raw_buffer_read_cstring_zero_terminated( raw_buffer_t *raw_buffer, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*raw_buffer).count ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // make result
   char_t *result = ( char_t * ) calloc( (*raw_buffer).count, sizeof( char_t ) );
   strcpy( result, ( char_t * ) &( (*raw_buffer).buffer[index] ) );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_read_string
*/

string_t *
raw_buffer_read_string( raw_buffer_t *raw_buffer, int32_t index, int32_t count )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*raw_buffer).count ) );
   PRECONDITION( "count ok", ( count >= 0 ) && ( count < (*raw_buffer).count - index ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // get string (with terminating zero)
   char_t *p = ( char_t * ) calloc( count + 1, sizeof( char_t ) );
   memcpy( p, &( (*raw_buffer).buffer[index] ), count );
   
   // make result
   string_t *result = string_make_from_cstring( p );
   
   // free temporary string
   free( p );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_read_cstring
*/

char_t *
raw_buffer_read_cstring( raw_buffer_t *raw_buffer, int32_t index, int32_t count )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*raw_buffer).count ) );
   PRECONDITION( "count ok", ( count >= 0 ) && ( count < (*raw_buffer).count - index ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // get string (with terminating zero)
   char_t *result = ( char_t * ) calloc( count + 1, sizeof( char_t ) );
   memcpy( result, &( (*raw_buffer).buffer[index] ), count );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_put_string
*/

void
raw_buffer_put_string( raw_buffer_t *raw_buffer, string_t *string, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "string ok", string != NULL );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*raw_buffer).count - string_count( string ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // put string (with terminating zero)
   memcpy( &( (*raw_buffer).buffer[index] ), string_as_cstring( string ), string_count( string ) + 1 );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_put_cstring
*/

void
raw_buffer_put_cstring( raw_buffer_t *raw_buffer, char_t *string, int32_t index )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "string ok", string != NULL );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*raw_buffer).count - strlen( string ) ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // put string (with terminating zero)
   memcpy( &( (*raw_buffer).buffer[index] ), string, strlen( string ) + 1 );
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return;
}

/**
   raw_buffer_to_hex_string
*/

string_t *
raw_buffer_to_hex_string( raw_buffer_t *raw_buffer )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // make result
   string_t *result = string_make_n( 2*(*raw_buffer).count + ( (*raw_buffer).count / 40 ) + 2 );
   
   // loop to put each byte in hex
   int32_t i = 0;
   string_t *s = NULL;
   for( i=0; i<(*raw_buffer).count; i++ ) 
   {
      s = string_hex_from_uint8( (*raw_buffer).buffer[i] );
      string_append( result, s );
      string_dispose_with_contents( s );
      
      // new line every 64 hex characters
      if ( ( i > 0 ) && ( ( i % 32 ) == 31 ) )
      {
         string_append_newline( result );
      }
   }
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_to_hex_cstring
*/

char_t *
raw_buffer_to_hex_cstring( raw_buffer_t *raw_buffer )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // make result
   char_t *result = ( char_t * ) calloc( 2*(*raw_buffer).count + ( (*raw_buffer).count / 40 ) + 2, sizeof( char_t ) );
   
   // loop to put each byte in hex
   int32_t i = 0;
   char_t *p = NULL;
   for( i=0; i<(*raw_buffer).count; i++ ) 
   {
      p = cstring_hex_from_uint8( (*raw_buffer).buffer[i] );
      strcat( result, p );
      free( p );
      
      // new line every 64 hex characters
      if ( ( i % 32 ) == 31 )
      {
         strcat( result, "\n" );
      }
   }
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/**
   raw_buffer_from_hex_string
*/

raw_buffer_t *
raw_buffer_from_hex_string( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   
   // make copy of string
   string_t *s = string_make_from( string );
   string_t *s1 = NULL;
   
   // remove newlines
   string_replace_all_cstring2( s, "\n", "" );
   
   // make result
   raw_buffer_t *result = raw_buffer_make( string_count( s ) / 2 );
   
   // loop to put each byte in buffer
   int32_t i = 0;
   uint8_t u8 = 0;
   for( i=0; i<=string_count( s ) - 2; i=i+2 ) 
   {
      s1 = string_substring( s, i, i+1 );
      u8 = string_hex_to_uint8( s1 ); 
      (*result).buffer[i/2] = u8;
      string_dispose_with_contents( s1 );
   }
   
   // dispose of string copy
   string_dispose_with_contents( s );
   
   INVARIANT( result );
   
   return result;
}

/**
   raw_buffer_from_hex_cstring
*/

raw_buffer_t *
raw_buffer_from_hex_cstring( char_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   
   // make copy of string
   string_t *s = string_make_from_cstring( string );
   string_t *s1 = NULL;
   
   // remove newlines
   string_replace_all_cstring2( s, "\n", "" );
   
   // make result
   raw_buffer_t *result = raw_buffer_make( string_count( s ) / 2 );
   
   // loop to put each byte in buffer
   int32_t i = 0;
   uint8_t u8 = 0;
   for( i=0; i<=string_count( s ) - 2; i=i+2 ) 
   {
      s1 = string_substring( s, i, i+1 );
      u8 = string_hex_to_uint8( s1 ); 
      (*result).buffer[i/2] = u8;
      string_dispose_with_contents( s1 );
   }
   
   // dispose of string copy
   string_dispose_with_contents( s );
   
   INVARIANT( result );
   
   return result;
}

/**
   raw_buffer_to_display_string
*/

string_t *
raw_buffer_to_display_string( raw_buffer_t *raw_buffer, int32_t start_index, int32_t count )
{
   PRECONDITION( "raw_buffer not null", raw_buffer != NULL );
   PRECONDITION( "raw_buffer type OK", (*raw_buffer).type == RAW_BUFFER_TYPE );
   PRECONDITION( "start_index ok", ( start_index >= 0 ) && ( start_index < (*raw_buffer).count ) );
   PRECONDITION( "count ok", ( count > 0 ) && ( count <= (*raw_buffer).count - start_index ) );
   LOCK( (*raw_buffer).mutex );
   INVARIANT( raw_buffer );
   
   // make result
   string_t *result = string_make_n( 3*(*raw_buffer).count );
   
   // loop to put each byte in display format
   int32_t i = 0;
   int32_t j = 0;
   string_t *s = NULL;
   string_t *offset = NULL;
   
   for( i=start_index; i<start_index+count; i=i+16 ) 
   {
      
      // offset to left side
      offset = string_hex_from_int32( i );
      s = string_substring( offset, 5, 7 );
      string_append( result, s );
      string_dispose_with_contents( s );
      string_dispose_with_contents( offset );
      string_append_cstring( result, ": " );

      // u8 as hex digits
      for( j=i; j<i+16; j++ )
      {
         if ( j < count )
         {
            s = string_hex_from_uint8( (*raw_buffer).buffer[j] );
            string_append( result, s );
            string_dispose_with_contents( s );
            string_append_cstring( result, " " );
         }
         else
         {
            string_append_cstring( result, "   " );
         }
         
         if ( (j-i) == 3 )
         {
            string_append_cstring( result, " " );
         }
         else if ( (j-i) == 7 )
         {
            string_append_cstring( result, "  " );
         }
         if ( (j-i) == 11 )
         {
            string_append_cstring( result, " " );
         }
      }
      
      string_append_cstring( result, " " );
            
      // u8 as printable characters
      for( j=i; j<i+16; j++ )
      {
         if ( ( j < count ) && ( (*raw_buffer).buffer[j] >= 0x20 ) && ( (*raw_buffer).buffer[j] != 0x7f ) )
         {
            string_append_character( result, (*raw_buffer).buffer[j] );
         }
         else
         {
            string_append_cstring( result, " " );
         }
         
      }
      
      // end of line
      string_append_newline( result );
      
      // every 4 lines insert an extra newline
      if ( ( ( ( i - start_index ) / 16 ) % 4 ) == 3 )
      {
         string_append_newline( result );
      }
   }
   
   INVARIANT( raw_buffer );
   UNLOCK( (*raw_buffer).mutex );
   
   return result;
}

/* End of file */
