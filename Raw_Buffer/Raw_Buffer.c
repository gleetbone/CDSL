/**
 @file Raw_Buffer.c
 @author Greg Lee
 @version 2.0.0
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
#include <endian.h>
#include "String_utilities.h"

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "base.h"
#include "dbc.h"

/**
   defines
*/

union Int_16_union
{
   uint16_t    u;
   int16_t     i;
};

typedef union Int_16_union Int_16_t;

union Int_Float_32_union
{
   uint32_t    u;
   int32_t     i;
   float32_t   f;
};

typedef union Int_Float_32_union Int_Float_32_t;

union Int_Float_64_union
{
   uint64_t    u;
   int64_t     i;
   float64_t   f;
};

typedef union Int_Float_64_union Int_Float_64_t;

/**
   raw_buffer structure
*/

struct raw_buffer_struct
{
   int32_t _type;

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
   assert( ( ( void ) "nonnegative count", nonnegative_count( p ) ) );
   assert( ( ( void ) "base pointer not void", base_pointer_not_void( p ) ) );
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
   PRECONDITION( "n ok", n >= 0 );

   // allocate raw_buffer struct
   raw_buffer_t * result
      = ( raw_buffer_t * ) calloc( 1, sizeof( raw_buffer_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = RAW_BUFFER_TYPE;

   // allocate buffer
   (*result).buffer = ( uint8_t * ) calloc( n, sizeof( uint8_t ) );
   CHECK( "(*result).buffer allocated correctly", (*result).buffer != NULL );

   // set count
   (*result).count = n;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "count set", (*result).count == n );
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
   PRECONDITION( "n ok", n >= 0 );

   // allocate raw_buffer struct
   raw_buffer_t * result
      = ( raw_buffer_t * ) calloc( 1, sizeof( raw_buffer_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = RAW_BUFFER_TYPE;

   // set buffer
   (*result).buffer = p;

   // set count
   (*result).count = n;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "count set", (*result).count == n );
   POSTCONDITION( "buffer set", (*result).buffer == p );

   return result;
}

/**
   raw_buffer_clone
*/

raw_buffer_t *
raw_buffer_clone( raw_buffer_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );

   // allocate raw_buffer struct
   raw_buffer_t *result
      = ( raw_buffer_t * ) calloc( 1, sizeof( raw_buffer_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = RAW_BUFFER_TYPE;

   // allocate buffer
   (*result).buffer = ( uint8_t * ) calloc( (*current).count, sizeof( uint8_t ) );
   CHECK( "(*result).buffer allocated correctly", (*result).buffer != NULL );

   // set count
   (*result).count = (*current).count;

   // copy contents
   memcpy( (*result).buffer, (*current).buffer, (*current).count );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "count set", (*result).count == (*current).count );
   POSTCONDITION( "buffer set", (*result).buffer != NULL );

   return result;
}

/**
   raw_buffer_deep_clone
*/

raw_buffer_t *
raw_buffer_deep_clone( raw_buffer_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );

   // allocate raw_buffer struct
   raw_buffer_t *result
      = ( raw_buffer_t * ) calloc( 1, sizeof( raw_buffer_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = RAW_BUFFER_TYPE;

   // allocate buffer
   (*result).buffer = ( uint8_t * ) calloc( (*current).count, sizeof( uint8_t ) );
   CHECK( "(*result).buffer allocated correctly", (*result).buffer != NULL );

   // set count
   (*result).count = (*current).count;

   // copy contents
   memcpy( (*result).buffer, (*current).buffer, (*current).count );

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "count set", (*result).count == (*current).count );
   POSTCONDITION( "buffer set", (*result).buffer != NULL );

   return result;
}

/**
   raw_buffer_is_equal
*/

int32_t
raw_buffer_is_equal( raw_buffer_t *current, raw_buffer_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == RAW_BUFFER_TYPE );

   int32_t result = 1;
   int32_t flag = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // check count
      if ( (*current).count != (*other).count )
      {
         result = 0;
      }

      // check contents
      if ( result == 1 )
      {
         result = 0;
         flag = memcmp( (*current).buffer, (*other).buffer, (*other).count );
         if ( flag == 0 )
         {
            result = 1;
         }
      }
   }

   INVARIANT( current );

   return result;
}

/**
   raw_buffer_is_deep_equal
*/

int32_t
raw_buffer_is_deep_equal( raw_buffer_t *current, raw_buffer_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == RAW_BUFFER_TYPE );

   int32_t result = 1;
   int32_t flag = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // check count
      if ( (*current).count != (*other).count )
      {
         result = 0;
      }

      // check contents
      if ( result == 1 )
      {
         result = 0;
         flag = memcmp( (*current).buffer, (*other).buffer, (*other).count );
         if ( flag == 0 )
         {
            result = 1;
         }
      }
   }

   INVARIANT( current );

   return result;
}

/**
   raw_buffer_copy
*/

void
raw_buffer_copy( raw_buffer_t *current, raw_buffer_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == RAW_BUFFER_TYPE );

   // (re)allocate buffer
   (*current).buffer = ( uint8_t * ) realloc( (*current).buffer, (*other).count * sizeof( uint8_t ) );
   CHECK( "(*current).buffer allocated correctly", (*current).buffer != NULL );

   // set count
   (*current).count = (*other).count;

   // copy contents
   memcpy( (*current).buffer, (*other).buffer, (*other).count );

   INVARIANT( current );
   POSTCONDITION( "count set", (*current).count == (*other).count );

   return;
}

/**
   raw_buffer_deep_copy
*/

void
raw_buffer_deep_copy( raw_buffer_t *current, raw_buffer_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == RAW_BUFFER_TYPE );

   // (re)allocate buffer
   (*current).buffer = ( uint8_t * ) realloc( (*current).buffer, (*other).count * sizeof( uint8_t ) );
   CHECK( "(*current).buffer allocated correctly", (*current).buffer != NULL );

   // set count
   (*current).count = (*other).count;

   // copy contents
   memcpy( (*current).buffer, (*other).buffer, (*other).count );

   INVARIANT( current );
   POSTCONDITION( "count set", (*current).count == (*other).count );

   return;
}

/**
   raw_buffer_dispose
*/

void
raw_buffer_dispose( raw_buffer_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == RAW_BUFFER_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete raw_buffer struct
   free(*current);

   // set to null
   *current = NULL;

   return;
}

/**
   raw_buffer_deep_dispose
*/

void
raw_buffer_deep_dispose( raw_buffer_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == RAW_BUFFER_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete buffer
   free( (**current).buffer );

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete raw_buffer struct
   free(*current);

   // set to null
   *current = NULL;

   return;
}


/**
   raw_buffer_subcopy
*/

void
raw_buffer_subcopy
(
   raw_buffer_t *current,
   raw_buffer_t *other,
   int32_t destination_index,
   int32_t source_index,
   int32_t count
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "source index ok", ( source_index >= 0 ) && ( source_index <= (*other).count  - count ) );
   PRECONDITION( "destination index ok", ( destination_index >= 0 ) && ( destination_index <= (*current).count  - count ) );
   PRECONDITION( "count ok", ( count >= 0 ) && ( count <= (*current).count ) && ( count <= (*other).count ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy the bytes
   memcpy
   (
      (*current).buffer + destination_index,
      (*other).buffer + source_index,
      count
   );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   raw_buffer_clear
*/

void
raw_buffer_clear( raw_buffer_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   memset( (*current).buffer, 0, (*current).count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   raw_buffer_append
*/

void
raw_buffer_append( raw_buffer_t *current, raw_buffer_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == RAW_BUFFER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // make buffer large enough
   (*current).buffer
      = ( uint8_t * ) realloc( (*current).buffer, (*current).count + (*other).count );
   CHECK( "(*current).buffer allocated correctly", (*current).buffer != NULL );

   // copy the bytes
   memcpy
   (
      (*current).buffer + (*current).count,
      (*other).buffer,
      (*other).count
   );

   // update count
   (*current).count = (*current).count + (*other).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_resize
*/

void
raw_buffer_resize( raw_buffer_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "count ok", count >= 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // make buffer large enough
   (*current).buffer
      = ( uint8_t * ) realloc( (*current).buffer, count );
   CHECK( "(*current).buffer allocated correctly", (*current).buffer != NULL );

   // zero new bytes if new size is larger
   if ( count > (*current).count )
   {
      memset
      (
         (*current).buffer + (*current).count,
         0,
         count - (*current).count
      );
   }

   // set count
   (*current).count = count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_base
*/

uint8_t *
raw_buffer_base( raw_buffer_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint8_t *result = (*current).buffer;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_count
*/

int32_t
raw_buffer_count( raw_buffer_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_char
*/

char_t
raw_buffer_read_char( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( char_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   char_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( char_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_uint8
*/

uint8_t
raw_buffer_read_uint8( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint8_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   uint8_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( uint8_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_uint8_be
*/

uint8_t
raw_buffer_read_uint8_be( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint8_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   uint8_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( uint8_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_uint8_le
*/

uint8_t
raw_buffer_read_uint8_le( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint8_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   uint8_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( uint8_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_uint16
*/

uint16_t
raw_buffer_read_uint16( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint16_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   uint16_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( uint16_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_uint16_be
*/

uint16_t
raw_buffer_read_uint16_be( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint16_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_16_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( uint16_t ) );

   result.u = be16toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.u;
}

/**
   raw_buffer_read_uint16_le
*/

uint16_t
raw_buffer_read_uint16_le( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint16_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_16_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( uint16_t ) );

   result.u = le16toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.u;
}

/**
   raw_buffer_read_uint32
*/

uint32_t
raw_buffer_read_uint32( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   uint32_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( uint32_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_uint32_be
*/

uint32_t
raw_buffer_read_uint32_be( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_Float_32_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( uint32_t ) );

   result.u = be32toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.u;
}

/**
   raw_buffer_read_uint32_le
*/

uint32_t
raw_buffer_read_uint32_le( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_Float_32_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( uint32_t ) );

   result.u = le32toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.u;
}

/**
   raw_buffer_read_uint64
*/

uint64_t
raw_buffer_read_uint64( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   uint64_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( uint64_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_uint64_be
*/

uint64_t
raw_buffer_read_uint64_be( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_Float_64_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( uint64_t ) );

   result.u = be64toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.u;
}

/**
   raw_buffer_read_uint64_le
*/

uint64_t
raw_buffer_read_uint64_le( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_Float_64_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( uint64_t ) );

   result.u = le64toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.u;
}


/**
   raw_buffer_read_int8
*/

int8_t
raw_buffer_read_int8( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int8_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   int8_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( int8_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_int8_be
*/

int8_t
raw_buffer_read_int8_be( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int8_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   int8_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( int8_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_int8_le
*/

int8_t
raw_buffer_read_int8_le( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int8_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   int8_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( int8_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_int16
*/

int16_t
raw_buffer_read_int16( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int16_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   int16_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( int16_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_int16_be
*/

int16_t
raw_buffer_read_int16_be( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int16_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_16_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( int16_t ) );

   result.u = be16toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.i;
}

/**
   raw_buffer_read_int16_le
*/

int16_t
raw_buffer_read_int16_le( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int16_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_16_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( int16_t ) );

   result.u = le16toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.i;
}

/**
   raw_buffer_read_int32
*/

int32_t
raw_buffer_read_int32( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   int32_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( int32_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_int32_be
*/

int32_t
raw_buffer_read_int32_be( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_Float_32_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( int32_t ) );

   result.u = be32toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.i;
}

/**
   raw_buffer_read_int32_le
*/

int32_t
raw_buffer_read_int32_le( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_Float_32_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( int32_t ) );

   result.u = le32toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.i;
}

/**
   raw_buffer_read_int64
*/

int64_t
raw_buffer_read_int64( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   int64_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( int64_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_int64_be
*/

int64_t
raw_buffer_read_int64_be( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_Float_64_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( int64_t ) );

   result.u = be64toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.i;
}

/**
   raw_buffer_read_int64_le
*/

int64_t
raw_buffer_read_int64_le( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_Float_64_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( int64_t ) );

   result.u = le64toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.i;
}

/**
   raw_buffer_read_float32
*/

float32_t
raw_buffer_read_float32( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( float32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   float32_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( float32_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_float32_be
*/

float32_t
raw_buffer_read_float32_be( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( float32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_Float_32_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( float32_t ) );

   result.u = be32toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.f;
}

/**
   raw_buffer_read_float32_le
*/

float32_t
raw_buffer_read_float32_le( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( float32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_Float_32_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( float32_t ) );

   result.u = le32toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.f;
}

/**
   raw_buffer_read_float64
*/

float64_t
raw_buffer_read_float64( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( float64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   float64_t result = 0;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( float64_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_float64_be
*/

float64_t
raw_buffer_read_float64_be( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( float64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_Float_64_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( float64_t ) );

   result.u = be64toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.f;
}

/**
   raw_buffer_read_float64_le
*/

float64_t
raw_buffer_read_float64_le( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( float64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   Int_Float_64_t result = {0};

   // copy data into result
   memcpy( &result.u, &( (*current).buffer[index] ), sizeof( float64_t ) );

   result.u = le64toh( result.u );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result.f;
}

/**
   raw_buffer_read_pointer
*/

void *
raw_buffer_read_pointer( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( void * ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get result
   void *result = NULL;

   // copy data into result
   memcpy( &result, &( (*current).buffer[index] ), sizeof( void * ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}


/**
   raw_buffer_put_char
*/

void
raw_buffer_put_char( raw_buffer_t *current, char_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( char_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( char_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_uint8
*/

void
raw_buffer_put_uint8( raw_buffer_t *current, uint8_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint8_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( uint8_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_uint8_be
*/

void
raw_buffer_put_uint8_be( raw_buffer_t *current, uint8_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint8_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( uint8_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_uint8_le
*/

void
raw_buffer_put_uint8_le( raw_buffer_t *current, uint8_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint8_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( uint8_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_uint16
*/

void
raw_buffer_put_uint16( raw_buffer_t *current, uint16_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint16_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( uint16_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_uint16_be
*/

void
raw_buffer_put_uint16_be( raw_buffer_t *current, uint16_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint16_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint16_t i = 0;

   i = htobe16( value );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &i, sizeof( uint16_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_uint16_le
*/

void
raw_buffer_put_uint16_le( raw_buffer_t *current, uint16_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint16_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint16_t i = 0;

   i = htole16( value );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &i, sizeof( uint16_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_uint32
*/

void
raw_buffer_put_uint32( raw_buffer_t *current, uint32_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( uint32_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_uint32_be
*/

void
raw_buffer_put_uint32_be( raw_buffer_t *current, uint32_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint32_t i = 0;

   i = htobe32( value );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &i, sizeof( uint32_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_uint32_le
*/

void
raw_buffer_put_uint32_le( raw_buffer_t *current, uint32_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint32_t i = 0;

   i = htole32( value );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &i, sizeof( uint32_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_uint64
*/

void
raw_buffer_put_uint64( raw_buffer_t *current, uint64_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( uint64_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_uint64_be
*/

void
raw_buffer_put_uint64_be( raw_buffer_t *current, uint64_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint64_t i = 0;

   i = htobe64( value );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &i, sizeof( uint64_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_uint64_le
*/

void
raw_buffer_put_uint64_le( raw_buffer_t *current, uint64_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( uint64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   uint64_t i = 0;

   i = htole64( value );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &i, sizeof( uint64_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_int8
*/

void
raw_buffer_put_int8( raw_buffer_t *current, int8_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int8_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( int8_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_int8_be
*/

void
raw_buffer_put_int8_be( raw_buffer_t *current, int8_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int8_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( int8_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_int8_le
*/

void
raw_buffer_put_int8_le( raw_buffer_t *current, int8_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int8_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( int8_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_int16
*/

void
raw_buffer_put_int16( raw_buffer_t *current, int16_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int16_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( int16_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_int16_be
*/

void
raw_buffer_put_int16_be( raw_buffer_t *current, int16_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int16_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_16_t u = {0};
   u.i = value;
   u.u = htobe16( u.u );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &u.u, sizeof( int16_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_int16_le
*/

void
raw_buffer_put_int16_le( raw_buffer_t *current, int16_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int16_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_16_t u = {0};
   u.i = value;
   u.u = htole16( u.u );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &u.u, sizeof( int16_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_int32
*/

void
raw_buffer_put_int32( raw_buffer_t *current, int32_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( int32_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_int32_be
*/

void
raw_buffer_put_int32_be( raw_buffer_t *current, int32_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_32_t u = {0};
   u.i = value;
   u.u = htobe32( u.u );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &u.u, sizeof( int32_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_int32_le
*/

void
raw_buffer_put_int32_le( raw_buffer_t *current, int32_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_32_t u = {0};
   u.i = value;
   u.u = htole32( u.u );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &u.u, sizeof( int32_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_int64
*/

void
raw_buffer_put_int64( raw_buffer_t *current, int64_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( int64_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_int64_be
*/

void
raw_buffer_put_int64_be( raw_buffer_t *current, int64_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_64_t u = {0};
   u.i = value;
   u.u = htobe64( u.u );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &u.u, sizeof( int64_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_int64_le
*/

void
raw_buffer_put_int64_le( raw_buffer_t *current, int64_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( int64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_64_t u = {0};
   u.i = value;
   u.u = htole64( u.u );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &u.u, sizeof( int64_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_float32
*/

void
raw_buffer_put_float32( raw_buffer_t *current, float32_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( float32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( float32_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_float32_be
*/

void
raw_buffer_put_float32_be( raw_buffer_t *current, float32_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( float32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_32_t u = {0};
   u.f = value;
   u.u = htobe32( u.u );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &u.u, sizeof( float32_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_float32_le
*/

void
raw_buffer_put_float32_le( raw_buffer_t *current, float32_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( float32_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_32_t u = {0};
   u.f = value;
   u.u = htole32( u.u );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &u.u, sizeof( float32_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_float64
*/

void
raw_buffer_put_float64( raw_buffer_t *current, float64_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( float64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( float64_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_float64_be
*/

void
raw_buffer_put_float64_be( raw_buffer_t *current, float64_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( float64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_64_t u = {0};
   u.f = value;
   u.u = htobe64( u.u );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &u.u, sizeof( float64_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_float64_le
*/

void
raw_buffer_put_float64_le( raw_buffer_t *current, float64_t value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( float64_t ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   Int_Float_64_t u = {0};
   u.f = value;
   u.u = htole64( u.u );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &u.u, sizeof( float64_t ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_pointer
*/

void
raw_buffer_put_pointer( raw_buffer_t *current, void *value, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).count - sizeof( void * ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // copy data into buffer
   memcpy( &( (*current).buffer[index] ), &value, sizeof( void * ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   raw_buffer_read_string_zero_terminated
*/

string_t *
raw_buffer_read_string_zero_terminated( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // make result
   string_t *result
      = string_make_from_cstring( ( char_t * ) & ( (*current).buffer[index] ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_cstring_zero_terminated
*/

char_t *
raw_buffer_read_cstring_zero_terminated( raw_buffer_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // make result
   char_t *result = ( char_t * ) calloc( (*current).count, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   strcpy( result, ( char_t * ) & ( (*current).buffer[index] ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_string
*/

string_t *
raw_buffer_read_string( raw_buffer_t *current, int32_t index, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );
   PRECONDITION( "count ok", ( count >= 0 ) && ( count < (*current).count - index ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get string (with terminating zero)
   char_t *p = ( char_t * ) calloc( count + 1, sizeof( char_t ) );
   CHECK( "p allocated correctly", p != NULL );

   memcpy( p, &( (*current).buffer[index] ), count );

   // make result
   string_t *result = string_make_from_cstring( p );

   // free temporary string
   free( p );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_read_cstring
*/

char_t *
raw_buffer_read_cstring( raw_buffer_t *current, int32_t index, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count ) );
   PRECONDITION( "count ok", ( count >= 0 ) && ( count <= (*current).count - index ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // get string (with terminating zero)
   char_t *result = ( char_t * ) calloc( count + 1, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   memcpy( result, &( (*current).buffer[index] ), count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_put_string
*/

void
raw_buffer_put_string( raw_buffer_t *current, string_t *string, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "string ok", string != NULL );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count - string_count( string ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // put string (with terminating zero)
   memcpy( &( (*current).buffer[index] ), string_as_cstring( string ), string_count( string ) + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_put_cstring
*/

void
raw_buffer_put_cstring( raw_buffer_t *current, char_t *string, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "string ok", string != NULL );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index < (*current).count - strlen( string ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // put string (with terminating zero)
   memcpy( &( (*current).buffer[index] ), string, strlen( string ) + 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   raw_buffer_to_hex_string
*/

string_t *
raw_buffer_to_hex_string( raw_buffer_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // make result
   string_t *result = string_make_n( 2 * (*current).count + ( (*current).count / 40 ) + 2 );

   // loop to put each byte in hex
   int32_t i = 0;
   string_t *s = NULL;
   for( i = 0; i < (*current).count; i++ )
   {
      s = string_hex_from_uint8( (*current).buffer[i] );
      string_append( result, s );
      string_deep_dispose( &s );

      // new line every 64 hex characters
      if ( ( i > 0 ) && ( ( i % 32 ) == 31 ) )
      {
         string_append_newline( result );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   raw_buffer_to_hex_cstring
*/

char_t *
raw_buffer_to_hex_cstring( raw_buffer_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // make result
   char_t *result = ( char_t * ) calloc( 2 * (*current).count + ( (*current).count / 40 ) + 2, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // loop to put each byte in hex
   int32_t i = 0;
   char_t *p = NULL;
   for( i = 0; i < (*current).count; i++ )
   {
      p = cstring_hex_from_uint8( (*current).buffer[i] );
      strcat( result, p );
      free( p );

      // new line every 64 hex characters
      if ( ( i % 32 ) == 31 )
      {
         strcat( result, "\n" );
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

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
   string_t *s = string_clone( string );
   string_t *s1 = NULL;

   // remove newlines
   string_replace_all_cstring2( s, "\n", "" );

   // make result
   raw_buffer_t *result = raw_buffer_make( string_count( s ) / 2 );

   // loop to put each byte in buffer
   int32_t i = 0;
   uint8_t u8 = 0;
   for( i = 0; i <= string_count( s ) - 2; i = i + 2 )
   {
      s1 = string_substring( s, i, i + 1 );
      u8 = string_hex_to_uint8( s1 );
      (*result).buffer[i / 2] = u8;
      string_deep_dispose( &s1 );
   }

   // dispose of string copy
   string_deep_dispose( &s );

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
   for( i = 0; i <= string_count( s ) - 2; i = i + 2 )
   {
      s1 = string_substring( s, i, i + 1 );
      u8 = string_hex_to_uint8( s1 );
      (*result).buffer[i / 2] = u8;
      string_deep_dispose( &s1 );
   }

   // dispose of string copy
   string_deep_dispose( &s );

   INVARIANT( result );

   return result;
}

/**
   raw_buffer_to_display_string
*/

string_t *
raw_buffer_to_display_string( raw_buffer_t *current, int32_t start_index, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == RAW_BUFFER_TYPE );
   PRECONDITION( "start_index ok", ( start_index >= 0 ) && ( start_index < (*current).count ) );
   PRECONDITION( "count ok", ( count > 0 ) && ( count <= (*current).count - start_index ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // make result
   string_t *result = string_make_n( 3 * (*current).count );

   // loop to put each byte in display format
   int32_t i = 0;
   int32_t j = 0;
   string_t *s = NULL;
   string_t *offset = NULL;

   for( i = start_index; i < start_index + count; i = i + 16 )
   {

      // offset to left side
      offset = string_hex_from_int32( i );
      s = string_substring( offset, 5, 7 );
      string_append( result, s );
      string_deep_dispose( &s );
      string_deep_dispose( &offset );
      string_append_cstring( result, ": " );

      // u8 as hex digits
      for( j = i; j < i + 16; j++ )
      {
         if ( j < count )
         {
            s = string_hex_from_uint8( (*current).buffer[j] );
            string_append( result, s );
            string_deep_dispose( &s );
            string_append_cstring( result, " " );
         }
         else
         {
            string_append_cstring( result, "   " );
         }

         if ( ( j - i ) == 3 )
         {
            string_append_cstring( result, " " );
         }
         else if ( ( j - i ) == 7 )
         {
            string_append_cstring( result, "  " );
         }
         if ( ( j - i ) == 11 )
         {
            string_append_cstring( result, " " );
         }
      }

      string_append_cstring( result, " " );

      // u8 as printable characters
      for( j = i; j < i + 16; j++ )
      {
         if ( ( j < count ) && ( (*current).buffer[j] >= 0x20 ) && ( (*current).buffer[j] != 0x7f ) )
         {
            string_append_character( result, (*current).buffer[j] );
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

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/* End of file */
