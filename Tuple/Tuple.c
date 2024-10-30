/**
   @file Tuple.c
   @author Greg Lee
   @version 0.0

   description: "Access to tick files"
   author: "Greg Lee"
   date: "$Date: 2014-06-26 10:34:55 -0800 (Thu, 26 Jun 2014) $"
   revision: "$Revision: 4433 $"

   @section DESCRIPTION

   Access to file that holds tick data in fixed length records.

 */

#include "Tuple.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Raw_Buffer.h"

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define CHECK_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#include "dbc.h"

/**
   Defines
*/

#define STRING_MASK 0x40
#define ARRAY_MASK  0x80

#define TYPE_OFFSET        0
#define BYTE_COUNT_OFFSET  4
#define START_OFFSET  8

/**
   tuple structure
*/

struct tuple_struct
{
   int32_t _type;

   char_t *name;

   int32_t field_count;

   int32_t *field_types;
   char_t **field_names;

   int32_t *field_array_counts;
   int32_t *field_string_lengths;

   int32_t *field_offsets;

   raw_buffer_t *buf;
};

#if INVARIANT_CONDITIONAL != 0

static
int32_t
name_ok( tuple_t *current )
{
   int32_t result = 0;

   result = (*current).name != NULL;

   return result;
}

static
int32_t
field_count_ok( tuple_t *current )
{
   int32_t result = 0;

   result = ( (*current).field_count >= 0 );

   return result;
}

static
int32_t
field_names_ok( tuple_t *current )
{
   int32_t result = 0;

   result = (*current).field_names != NULL;

   return result;
}

static
int32_t
field_types_ok( tuple_t *current )
{
   int32_t result = 0;

   result = (*current).field_types != NULL;

   return result;
}

static
int32_t
field_array_counts_ok( tuple_t *current )
{
   int32_t result = 0;

   result = (*current).field_array_counts != NULL;

   return result;
}

static
int32_t
field_string_lengths_ok( tuple_t *current )
{
   int32_t result = 0;

   result = (*current).field_string_lengths != NULL;

   return result;
}

static
int32_t
field_offsets_ok( tuple_t *current )
{
   int32_t result = 0;

   result = (*current).field_offsets != NULL;

   return result;
}


static
void invariant( tuple_t *current )
{
   assert( ( ( void ) "name_ok", name_ok( current ) ) );
   assert( ( ( void ) "field_count_ok", field_count_ok( current ) ) );
   assert( ( ( void ) "field_names_ok", field_names_ok( current ) ) );
   assert( ( ( void ) "field_types_ok", field_types_ok( current ) ) );
   assert( ( ( void ) "field_array_counts_ok", field_array_counts_ok( current ) ) );
   assert( ( ( void ) "field_string_lengths_ok", field_string_lengths_ok( current ) ) );
   assert( ( ( void ) "field_offsets_ok", field_offsets_ok( current ) ) );
   return;
}

#else

static
void invariant( tuple_t *current )
{
   return;
}

#endif


/**
   tuple_make
*/

tuple_t *
tuple_make( char_t *name, int32_t field_count, ... )
{
   PRECONDITION( "name ok", name != NULL );
   PRECONDITION( "field_count ok", field_count >= 0 );

   int32_t i = 0;
   int32_t offset = 0;
   int32_t type = 0;
   char_t *str = NULL;
   int32_t count = 0;
   int32_t length = 0;

   va_list ap;

   // allocate tuple struct
   tuple_t * result = ( tuple_t * ) calloc( 1, sizeof( tuple_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = TUPLE_TYPE;

   // set elements
   (*result).name = ( char_t * ) calloc( sizeof( name ) + 1, sizeof( char_t ) );
   CHECK( "(*result).name allocated correctly", (*result).name != NULL );
   strcpy( (*result).name, name );

   (*result).field_count = field_count;

   // make struct fields
   (*result).field_types = ( int32_t * ) calloc( field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_types allocated correctly", (*result).field_types != NULL );

   (*result).field_names = ( char_t ** ) calloc( field_count, sizeof( char_t * ) );
   CHECK( "(*result).field_names allocated correctly", (*result).field_names != NULL );

   (*result).field_array_counts = ( int32_t * ) calloc( field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_array_counts allocated correctly", (*result).field_array_counts != NULL );

   (*result).field_string_lengths = ( int32_t * ) calloc( field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_string_lengths allocated correctly", (*result).field_string_lengths != NULL );

   (*result).field_offsets = ( int32_t * ) calloc( field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_offsets allocated correctly", (*result).field_offsets != NULL );

   va_start( ap, field_count );

   // handle variadic arguments
   for ( i = 0; i < field_count; i++ )
   {
      type = va_arg( ap, int32_t );

      switch( type )
      {

         // 8 bit values
         case TUPLE_INT8_TYPE:
         case TUPLE_UINT8_TYPE:

            name = va_arg( ap, char_t * );

            (*result).field_types[i] = type;
            str = ( char_t * ) calloc( strlen( name ) + 1, sizeof( char_t ) );
            CHECK( "str allocated correctly", str != NULL );

            strcpy( str, name );
            (*result).field_names[i] = str;
            (*result).field_array_counts[i] = 1;
            (*result).field_string_lengths[i] = 0;
            (*result).field_offsets[i] = offset;

            offset = offset + sizeof( int8_t );

            break;

         // 16 bit values
         case TUPLE_INT16_TYPE:
         case TUPLE_UINT16_TYPE:

            name = va_arg( ap, char_t * );

            (*result).field_types[i] = type;
            str = ( char_t * ) calloc( strlen( name ) + 1, sizeof( char_t ) );
            CHECK( "str allocated correctly", str != NULL );

            strcpy( str, name );
            (*result).field_names[i] = str;
            (*result).field_array_counts[i] = 1;
            (*result).field_string_lengths[i] = 0;
            (*result).field_offsets[i] = offset;

            offset = offset + sizeof( int16_t );

            break; /* optional */

         // 32 bit values
         case TUPLE_INT32_TYPE:
         case TUPLE_UINT32_TYPE:
         case TUPLE_FLOAT32_TYPE:

            name = va_arg( ap, char_t * );

            (*result).field_types[i] = type;
            str = ( char_t * ) calloc( strlen( name ) + 1, sizeof( char_t ) );
            CHECK( "str allocated correctly", str != NULL );

            strcpy( str, name );
            (*result).field_names[i] = str;
            (*result).field_array_counts[i] = 1;
            (*result).field_string_lengths[i] = 0;
            (*result).field_offsets[i] = offset;

            offset = offset + sizeof( int32_t );
            break;

         // 64 bit values
         case TUPLE_INT64_TYPE:
         case TUPLE_UINT64_TYPE:
         case TUPLE_FLOAT64_TYPE:

            name = va_arg( ap, char_t * );

            (*result).field_types[i] = type;
            str = ( char_t * ) calloc( strlen( name ) + 1, sizeof( char_t ) );
            CHECK( "str allocated correctly", str != NULL );

            strcpy( str, name );
            (*result).field_names[i] = str;
            (*result).field_array_counts[i] = 1;
            (*result).field_string_lengths[i] = 0;
            (*result).field_offsets[i] = offset;

            offset = offset + sizeof( int64_t );

            break; /* optional */

         // pointer values
         case TUPLE_POINTER_TYPE:

            name = va_arg( ap, char_t * );

            (*result).field_types[i] = type;
            str = ( char_t * ) calloc( strlen( name ) + 1, sizeof( char_t ) );
            CHECK( "str allocated correctly", str != NULL );

            strcpy( str, name );
            (*result).field_names[i] = str;
            (*result).field_array_counts[i] = 1;
            (*result).field_string_lengths[i] = 0;
            (*result).field_offsets[i] = offset;

            offset = offset + sizeof( void * );

            break; /* optional */

         // 8 bit array values
         case TUPLE_ARRAY_INT8_TYPE:
         case TUPLE_ARRAY_UINT8_TYPE:

            name = va_arg( ap, char_t * );
            count = va_arg( ap, int32_t );

            (*result).field_types[i] = type;
            str = ( char_t * ) calloc( strlen( name ) + 1, sizeof( char_t ) );
            CHECK( "str allocated correctly", str != NULL );

            strcpy( str, name );
            (*result).field_names[i] = str;
            (*result).field_array_counts[i] = count;
            (*result).field_string_lengths[i] = 0;
            (*result).field_offsets[i] = offset;

            offset = offset + count * sizeof( int8_t );

            break;

         // 16 bit array values
         case TUPLE_ARRAY_INT16_TYPE:
         case TUPLE_ARRAY_UINT16_TYPE:

            name = va_arg( ap, char_t * );
            count = va_arg( ap, int32_t );

            (*result).field_types[i] = type;
            str = ( char_t * ) calloc( strlen( name ) + 1, sizeof( char_t ) );
            CHECK( "str allocated correctly", str != NULL );

            strcpy( str, name );
            (*result).field_names[i] = str;
            (*result).field_array_counts[i] = count;
            (*result).field_string_lengths[i] = 0;
            (*result).field_offsets[i] = offset;

            offset = offset + count * sizeof( int16_t );

            break;

         // 32 bit array values
         case TUPLE_ARRAY_INT32_TYPE:
         case TUPLE_ARRAY_UINT32_TYPE:
         case TUPLE_ARRAY_FLOAT32_TYPE:

            name = va_arg( ap, char_t * );
            count = va_arg( ap, int32_t );

            (*result).field_types[i] = type;
            str = ( char_t * ) calloc( strlen( name ) + 1, sizeof( char_t ) );
            CHECK( "str allocated correctly", str != NULL );

            strcpy( str, name );
            (*result).field_names[i] = str;
            (*result).field_array_counts[i] = count;
            (*result).field_string_lengths[i] = 0;
            (*result).field_offsets[i] = offset;

            offset = offset + count * sizeof( int32_t );

            break;

         // 64 bit array values
         case TUPLE_ARRAY_INT64_TYPE:
         case TUPLE_ARRAY_UINT64_TYPE:
         case TUPLE_ARRAY_FLOAT64_TYPE:

            name = va_arg( ap, char_t * );
            count = va_arg( ap, int32_t );

            (*result).field_types[i] = type;
            str = ( char_t * ) calloc( strlen( name ) + 1, sizeof( char_t ) );
            CHECK( "str allocated correctly", str != NULL );

            strcpy( str, name );
            (*result).field_names[i] = str;
            (*result).field_array_counts[i] = count;
            (*result).field_string_lengths[i] = 0;
            (*result).field_offsets[i] = offset;

            offset = offset + count * sizeof( int64_t );

            break;

         // pointer array values
         case TUPLE_ARRAY_POINTER_TYPE:

            name = va_arg( ap, char_t * );
            count = va_arg( ap, int32_t );

            (*result).field_types[i] = type;
            str = ( char_t * ) calloc( strlen( name ) + 1, sizeof( char_t ) );
            CHECK( "str allocated correctly", str != NULL );

            strcpy( str, name );
            (*result).field_names[i] = str;
            (*result).field_array_counts[i] = count;
            (*result).field_string_lengths[i] = 0;
            (*result).field_offsets[i] = offset;

            offset = offset + count * sizeof( int64_t );

            break;

         // string value
         case TUPLE_STRING_TYPE:

            name = va_arg( ap, char_t * );
            length = va_arg( ap, int32_t );

            (*result).field_types[i] = type;
            str = ( char_t * ) calloc( strlen( name ) + 1, sizeof( char_t ) );
            CHECK( "str allocated correctly", str != NULL );

            strcpy( str, name );
            (*result).field_names[i] = str;
            (*result).field_array_counts[i] = 1;
            (*result).field_string_lengths[i] = length;
            (*result).field_offsets[i] = offset;

            offset = offset + length * sizeof( char_t );

            break;

         // array of string value
         case TUPLE_ARRAY_STRING_TYPE:

            name = va_arg( ap, char_t * );
            length = va_arg( ap, int32_t );
            count = va_arg( ap, int32_t );

            (*result).field_types[i] = type;
            str = ( char_t * ) calloc( strlen( name ) + 1, sizeof( char_t ) );
            CHECK( "str allocated correctly", str != NULL );

            strcpy( str, name );
            (*result).field_names[i] = str;
            (*result).field_array_counts[i] = count;
            (*result).field_string_lengths[i] = length;
            (*result).field_offsets[i] = offset;

            offset = offset + count * length * sizeof( char_t );

            break;
      }

   }

   va_end ( ap );

   (*result).buf = raw_buffer_make( offset );

   INVARIANT( result );

   return result;
}

/**
   buffer_size_from_header_info

   get the buffer size

   @param current the tuple_t instance
   @return the size of the buffer
*/
static
int32_t
buffer_size_from_header_info( tuple_t *current )
{
   int32_t result = 0;
   int32_t i = 0;
   int32_t type = 0;

   for ( i = 0; i < (*current).field_count; i++ )
   {
      type = (*current).field_types[i];

      switch( type )
      {
         case TUPLE_INT8_TYPE:
         case TUPLE_UINT8_TYPE:
            result = result + sizeof( int8_t );
            break;

         case TUPLE_INT16_TYPE:
         case TUPLE_UINT16_TYPE:
            result = result + sizeof( int16_t );
            break;

         case TUPLE_INT32_TYPE:
         case TUPLE_UINT32_TYPE:
         case TUPLE_FLOAT32_TYPE:
            result = result + sizeof( int32_t );
            break;

         case TUPLE_INT64_TYPE:
         case TUPLE_UINT64_TYPE:
         case TUPLE_FLOAT64_TYPE:
            result = result + sizeof( int64_t );
            break;

         case TUPLE_POINTER_TYPE:
            result = result + sizeof( void * );
            break;

         case TUPLE_ARRAY_INT8_TYPE:
         case TUPLE_ARRAY_UINT8_TYPE:
            result = result + sizeof( int8_t ) * (*current).field_array_counts[i];
            break;

         case TUPLE_ARRAY_INT16_TYPE:
         case TUPLE_ARRAY_UINT16_TYPE:
            result = result + sizeof( int16_t ) * (*current).field_array_counts[i];
            break;

         case TUPLE_ARRAY_INT32_TYPE:
         case TUPLE_ARRAY_UINT32_TYPE:
         case TUPLE_ARRAY_FLOAT32_TYPE:
            result = result + sizeof( int32_t ) * (*current).field_array_counts[i];
            break;

         case TUPLE_ARRAY_INT64_TYPE:
         case TUPLE_ARRAY_UINT64_TYPE:
         case TUPLE_ARRAY_FLOAT64_TYPE:
            result = result + sizeof( int64_t ) * (*current).field_array_counts[i];
            break;

         case TUPLE_ARRAY_POINTER_TYPE:
            result = result + sizeof( void * ) * (*current).field_array_counts[i];
            break;

         case TUPLE_STRING_TYPE:
            result = result + sizeof( char_t ) * (*current).field_string_lengths[i];
            break;

         case TUPLE_ARRAY_STRING_TYPE:
            result = result + sizeof( char_t ) * (*current).field_array_counts[i] * (*current).field_string_lengths[i];
            break;

      }
   }

   return result;
}

/**
   tuple_make_from_header_byte_array
*/
tuple_t *
tuple_make_from_header_byte_array( uint8_t *byte_array, int32_t byte_array_count )
{
   tuple_t *result = NULL;
   raw_buffer_t *buf = NULL;
   int32_t offset = 0;
   int32_t length = 0;
   int32_t i = 0;

   // allocate tuple struct
   result = ( tuple_t * ) calloc( 1, sizeof( tuple_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = TUPLE_TYPE;

   // make byte array into a raw_buffer
   buf = raw_buffer_make_from_pointer( byte_array, byte_array_count );

   // tuple type
   CHECK( "type OK", raw_buffer_read_int32_be( buf, TYPE_OFFSET ) == TUPLE_TYPE );

   // byte array count
   CHECK( "count ok", raw_buffer_read_int32_be( buf, BYTE_COUNT_OFFSET ) == byte_array_count );

   offset = START_OFFSET;

   // name byte count
   length = raw_buffer_read_int32_be( buf, offset );
   offset = offset + sizeof( int32_t );

   // name
   (*result).name = raw_buffer_read_cstring( buf, offset, length );
   offset = offset + length;

   // field_count
   (*result).field_count = raw_buffer_read_int32_be( buf, offset );
   offset = offset + sizeof( int32_t );

   // make arrays
   (*result).field_types = ( int32_t * ) calloc( (*result).field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_types allocated correctly", (*result).field_types != NULL );

   (*result).field_names = ( char_t ** ) calloc( (*result).field_count, sizeof( char_t * ) );
   CHECK( "(*result).field_names allocated correctly", (*result).field_names != NULL );

   (*result).field_array_counts = ( int32_t * ) calloc( (*result).field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_array_counts allocated correctly", (*result).field_array_counts != NULL );

   (*result).field_string_lengths = ( int32_t * ) calloc( (*result).field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_string_lengths allocated correctly", (*result).field_string_lengths != NULL );

   (*result).field_offsets = ( int32_t * ) calloc( (*result).field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_offsets allocated correctly", (*result).field_offsets != NULL );

   // field_types
   for ( i = 0; i < (*result).field_count; i++ )
   {
      (*result).field_types[i] = raw_buffer_read_int32_be( buf, offset );
      offset = offset + sizeof( int32_t );
   }

   // field names
   for ( i = 0; i < (*result).field_count; i++ )
   {
      // field name length
      length = raw_buffer_read_int32_be( buf, offset );
      offset = offset + sizeof( int32_t );

      // field name
      (*result).field_names[i] = raw_buffer_read_cstring( buf, offset, length );
      offset = offset + length;
   }

   // field array counts
   for ( i = 0; i < (*result).field_count; i++ )
   {
      (*result).field_array_counts[i] = raw_buffer_read_int32_be( buf, offset );
      offset = offset + sizeof( int32_t );
   }

   // field string_lengths
   for ( i = 0; i < (*result).field_count; i++ )
   {
      (*result).field_string_lengths[i] = raw_buffer_read_int32_be( buf, offset );
      offset = offset + sizeof( int32_t );
   }

   // field offsets
   for ( i = 0; i < (*result).field_count; i++ )
   {
      (*result).field_offsets[i] = raw_buffer_read_int32_be( buf, offset );
      offset = offset + sizeof( int32_t );
   }

   // make raw buffer
   (*result).buf = raw_buffer_make( buffer_size_from_header_info( result ) );

   // dispose of garbage
   raw_buffer_dispose( &buf );

   INVARIANT( result );

   return result;
}

/**
   tuple_clone
*/

tuple_t *
tuple_clone
(
   tuple_t *current
)
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   INVARIANT( current );

   int32_t i = 0;

   // allocate tuple struct
   tuple_t * result = ( tuple_t * ) calloc( 1, sizeof( tuple_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = TUPLE_TYPE;

   // set name
   (*result).name = ( char_t * ) calloc( strlen( (*current).name ) + 1, sizeof( char_t ) );
   CHECK( "(*result).name allocated correctly", (*result).name != NULL );

   strcpy( (*result).name, (*current).name );

   // set field_count
   (*result).field_count = (*current).field_count;

   // set field_types
   (*result).field_types = ( int32_t * ) calloc( (*current).field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_types allocated correctly", (*result).field_types != NULL );

   for ( i = 0; i < (*current).field_count; i++ )
   {
      (*result).field_types[i] = (*current).field_types[i];
   }

   // set field_names
   (*result).field_names = ( char_t ** ) calloc( (*current).field_count, sizeof( char_t * ) );
   CHECK( "(*result).name allocated correctly", (*result).field_names != NULL );

   for ( i = 0; i < (*current).field_count; i++ )
   {
      (*result).field_names[i] = ( char_t * ) calloc( strlen( (*current).field_names[i] ) + 1, sizeof( char_t ) );
      CHECK( "(*result).field_names[i] allocated correctly", (*result).field_names[i] != NULL );

      strcpy( (*result).field_names[i], (*current).field_names[i] );
   }

   // set field_array_counts
   (*result).field_array_counts = ( int32_t * ) calloc( (*current).field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_array_counts allocated correctly", (*result).field_array_counts != NULL );

   for ( i = 0; i < (*current).field_count; i++ )
   {
      (*result).field_array_counts[i] = (*current).field_array_counts[i];
   }

   // set field_string_lengths
   (*result).field_string_lengths = ( int32_t * ) calloc( (*current).field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_string_lengths allocated correctly", (*result).field_string_lengths != NULL );

   for ( i = 0; i < (*current).field_count; i++ )
   {
      (*result).field_string_lengths[i] = (*current).field_string_lengths[i];
   }

   // set field_offsets
   (*result).field_offsets = ( int32_t * ) calloc( (*current).field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_offsets allocated correctly", (*result).field_offsets != NULL );

   for ( i = 0; i < (*current).field_count; i++ )
   {
      (*result).field_offsets[i] = (*current).field_offsets[i];
   }

   (*result).buf = raw_buffer_deep_clone( (*current).buf );

   INVARIANT( result );

   return result;
}

/**
   tuple_deep_clone
*/

tuple_t *
tuple_deep_clone
(
   tuple_t *current
)
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   INVARIANT( current );

   int32_t i = 0;

   // allocate tuple struct
   tuple_t * result = ( tuple_t * ) calloc( 1, sizeof( tuple_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = TUPLE_TYPE;

   // set name
   (*result).name = ( char_t * ) calloc( strlen( (*current).name ) + 1, sizeof( char_t ) );
   CHECK( "(*result).name allocated correctly", (*result).name != NULL );

   strcpy( (*result).name, (*current).name );

   // set field_count
   (*result).field_count = (*current).field_count;

   // set field_types
   (*result).field_types = ( int32_t * ) calloc( (*current).field_count, sizeof( int32_t ) );
   CHECK( "(*result).name allocated correctly", (*result).name != NULL );

   for ( i = 0; i < (*current).field_count; i++ )
   {
      (*result).field_types[i] = (*current).field_types[i];
   }

   // set field_names
   (*result).field_names = ( char_t ** ) calloc( (*current).field_count, sizeof( char_t * ) );
   CHECK( "(*result).field_names allocated correctly", (*result).field_names != NULL );

   for ( i = 0; i < (*current).field_count; i++ )
   {
      (*result).field_names[i] = ( char_t * ) calloc( strlen( (*current).field_names[i] ) + 1, sizeof( char_t ) );
      CHECK( "(*result).field_names[i] allocated correctly", (*result).field_names[i] != NULL );

      strcpy( (*result).field_names[i], (*current).field_names[i] );
   }

   // set field_array_counts
   (*result).field_array_counts = ( int32_t * ) calloc( (*current).field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_array_counts allocated correctly", (*result).field_array_counts != NULL );

   for ( i = 0; i < (*current).field_count; i++ )
   {
      (*result).field_array_counts[i] = (*current).field_array_counts[i];
   }

   // set field_string_lengths
   (*result).field_string_lengths = ( int32_t * ) calloc( (*current).field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_string_lengths allocated correctly", (*result).field_string_lengths != NULL );

   for ( i = 0; i < (*current).field_count; i++ )
   {
      (*result).field_string_lengths[i] = (*current).field_string_lengths[i];
   }

   // set field_offsets
   (*result).field_offsets = ( int32_t * ) calloc( (*current).field_count, sizeof( int32_t ) );
   CHECK( "(*result).field_offsets allocated correctly", (*result).field_offsets != NULL );

   for ( i = 0; i < (*current).field_count; i++ )
   {
      (*result).field_offsets[i] = (*current).field_offsets[i];
   }

   (*result).buf = raw_buffer_deep_clone( (*current).buf );

   INVARIANT( result );

   return result;
}

/**
   tuple_copy
*/

void
tuple_copy
(
   tuple_t *current,
   tuple_t *other
)
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "other ok", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == TUPLE_TYPE );
   INVARIANT( current );

   int32_t i = 0;

   // set name
   free( (*current).name );
   (*current).name = ( char_t * ) calloc( strlen( (*other).name ) + 1, sizeof( char_t ) );
   CHECK( "(*current).name allocated correctly", (*current).name != NULL );

   strcpy( (*current).name, (*other).name );

   // set field_count
   (*current).field_count = (*other).field_count;

   // set field_types
   free( (*current).field_types );
   (*current).field_types = ( int32_t * ) calloc( (*other).field_count, sizeof( int32_t ) );
   CHECK( "(*current).field_types allocated correctly", (*current).field_types != NULL );

   for ( i = 0; i < (*other).field_count; i++ )
   {
      (*current).field_types[i] = (*other).field_types[i];
   }

   // set field_names
   for ( i = 0; i < (*current).field_count; i++ )
   {
      free( (*current).field_names[i] );
   }
   free( (*current).field_names );

   (*current).field_names = ( char_t ** ) calloc( (*other).field_count, sizeof( char_t * ) );
   CHECK( "(*current).field_names allocated correctly", (*current).field_names != NULL );

   for ( i = 0; i < (*other).field_count; i++ )
   {
      (*current).field_names[i] = ( char_t * ) calloc( strlen( (*other).field_names[i] ) + 1, sizeof( char_t ) );
      CHECK( "(*current).field_names[i] allocated correctly", (*current).field_names[i] != NULL );

      strcpy( (*current).field_names[i], (*other).field_names[i] );
   }

   // set field_array_counts
   free( (*current).field_array_counts );
   (*current).field_array_counts = ( int32_t * ) calloc( (*other).field_count, sizeof( int32_t ) );
   CHECK( "(*current).field_array_counts allocated correctly", (*current).field_array_counts != NULL );

   for ( i = 0; i < (*other).field_count; i++ )
   {
      (*current).field_array_counts[i] = (*other).field_array_counts[i];
   }

   // set field_string_lengths
   free( (*current).field_string_lengths );
   (*current).field_string_lengths = ( int32_t * ) calloc( (*other).field_count, sizeof( int32_t ) );
   CHECK( "(*current).field_string_lengths allocated correctly", (*current).field_string_lengths != NULL );

   for ( i = 0; i < (*other).field_count; i++ )
   {
      (*current).field_string_lengths[i] = (*other).field_string_lengths[i];
   }

   // set field_offsets
   free( (*current).field_offsets );
   (*current).field_offsets = ( int32_t * ) calloc( (*other).field_count, sizeof( int32_t ) );
   CHECK( "(*current).field_offsets allocated correctly", (*current).field_offsets != NULL );

   for ( i = 0; i < (*other).field_count; i++ )
   {
      (*current).field_offsets[i] = (*other).field_offsets[i];
   }

   raw_buffer_deep_dispose( &(*current).buf );
   (*current).buf = raw_buffer_deep_clone( (*other).buf );

   INVARIANT( current );

   return;
}

/**
   tuple_deep_copy
*/

void
tuple_deep_copy
(
   tuple_t *current,
   tuple_t *other
)
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "other ok", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == TUPLE_TYPE );
   INVARIANT( current );

   int32_t i = 0;

   // set name
   free( (*current).name );
   (*current).name = ( char_t * ) calloc( strlen( (*other).name ) + 1, sizeof( char_t ) );
   CHECK( "(*current).name allocated correctly", (*current).name != NULL );

   strcpy( (*current).name, (*other).name );

   // set field_count
   (*current).field_count = (*other).field_count;

   // set field_types
   free( (*current).field_types );
   (*current).field_types = ( int32_t * ) calloc( (*other).field_count, sizeof( int32_t ) );
   CHECK( "(*current).field_types allocated correctly", (*current).field_types != NULL );

   for ( i = 0; i < (*other).field_count; i++ )
   {
      (*current).field_types[i] = (*other).field_types[i];
   }

   // set field_names
   for ( i = 0; i < (*current).field_count; i++ )
   {
      free( (*current).field_names[i] );
   }
   free( (*current).field_names );

   (*current).field_names = ( char_t ** ) calloc( (*other).field_count, sizeof( char_t * ) );
   CHECK( "(*current).field_names allocated correctly", (*current).field_names != NULL );

   for ( i = 0; i < (*other).field_count; i++ )
   {
      (*current).field_names[i] = ( char_t * ) calloc( strlen( (*other).field_names[i] ) + 1, sizeof( char_t ) );
      CHECK( "(*current).field_names[i] allocated correctly", (*current).field_names[i] != NULL );

      strcpy( (*current).field_names[i], (*other).field_names[i] );
   }

   // set field_array_counts
   free( (*current).field_array_counts );
   (*current).field_array_counts = ( int32_t * ) calloc( (*other).field_count, sizeof( int32_t ) );
   CHECK( "(*current).field_array_counts allocated correctly", (*current).field_array_counts != NULL );

   for ( i = 0; i < (*other).field_count; i++ )
   {
      (*current).field_array_counts[i] = (*other).field_array_counts[i];
   }

   // set field_string_lengths
   free( (*current).field_string_lengths );
   (*current).field_string_lengths = ( int32_t * ) calloc( (*other).field_count, sizeof( int32_t ) );
   CHECK( "(*current).field_string_lengths allocated correctly", (*current).field_string_lengths != NULL );

   for ( i = 0; i < (*other).field_count; i++ )
   {
      (*current).field_string_lengths[i] = (*other).field_string_lengths[i];
   }

   // set field_offsets
   free( (*current).field_offsets );
   (*current).field_offsets = ( int32_t * ) calloc( (*other).field_count, sizeof( int32_t ) );
   CHECK( "(*current).field_offsets allocated correctly", (*current).field_offsets != NULL );

   for ( i = 0; i < (*other).field_count; i++ )
   {
      (*current).field_offsets[i] = (*other).field_offsets[i];
   }

   raw_buffer_deep_dispose( &(*current).buf );
   (*current).buf = raw_buffer_deep_clone( (*other).buf );

   INVARIANT( current );

   return;
}

/**
   int32_array_is_equal

   see if two arrays of int32_t are equal

   @param a1 the first array
   @param a2 the second array
   @param count the length of the arrays
   @return 1 if equal, 0 otherwise
*/
static
int32_t
int32_array_is_equal( int32_t *a1, int32_t *a2, int32_t count )
{
   int32_t result = 1;
   int32_t i = 0;
   int32_t count1 = 0;

   for ( i = 0; i < count; i++ )
   {
      if ( a1[i] == a2[i] )
      {
         count1 = count1 + 1;
      }
   }

   if ( count1 == count )
   {
      result = 1;
   }

   return result;
}

/**
   string_array_is_equal

   see if two arrays of character strings are equal

   @param a1 the first array
   @param a2 the second array
   @param count the length of the arrays
   @return 1 if equal, 0 otherwise
*/
static
int32_t
string_array_is_equal( char_t **a1, char_t **a2, int32_t count )
{
   int32_t result = 1;
   int32_t i = 0;
   int32_t count1 = 0;

   for ( i = 0; i < count; i++ )
   {
      if ( strcmp( a1[i], a2[i] ) == 0 )
      {
         count1 = count1 + 1;
      }
   }

   if ( count1 == count )
   {
      result = 1;
   }

   return result;
}


/**
   tuple_is_equal

   see if two tuples are equal - shallow equal

   @param current the first tuple
   @param other the second tuple
   @return 1 if equal, 0 otherwise
*/

int32_t
tuple_is_equal
(
   tuple_t *current,
   tuple_t *other
)
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "other ok", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == TUPLE_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // check elements
   if (
      ( strcmp( (*current).name, (*other).name ) == 0 )
      &&
      ( (*current).field_count == (*other).field_count )
      &&
      ( int32_array_is_equal( (*current).field_types, (*other).field_types, (*other).field_count ) == 1 )
      &&
      ( string_array_is_equal( (*current).field_names, (*other).field_names, (*other).field_count ) == 1 )
      &&
      ( int32_array_is_equal( (*current).field_array_counts, (*other).field_array_counts, (*other).field_count ) == 1 )
      &&
      ( int32_array_is_equal( (*current).field_string_lengths, (*other).field_string_lengths, (*other).field_count ) == 1 )
      &&
      ( int32_array_is_equal( (*current).field_offsets, (*other).field_offsets, (*other).field_count ) == 1 )
      &&
      ( raw_buffer_is_equal( (*current).buf, (*other).buf ) == 1 )
   )
   {
      result = 1;
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_is_deep_equal

   see if two tuples are equal - deep equal

   @param current the first tuple
   @param other the second tuple
   @return 1 if equal, 0 otherwise
*/

int32_t
tuple_is_deep_equal
(
   tuple_t *current,
   tuple_t *other
)
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "other ok", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == TUPLE_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   // check elements
   if (
      ( strcmp( (*current).name, (*other).name ) == 0 )
      &&
      ( (*current).field_count == (*other).field_count )
      &&
      ( int32_array_is_equal( (*current).field_types, (*other).field_types, (*other).field_count ) == 1 )
      &&
      ( string_array_is_equal( (*current).field_names, (*other).field_names, (*other).field_count ) == 1 )
      &&
      ( int32_array_is_equal( (*current).field_array_counts, (*other).field_array_counts, (*other).field_count ) == 1 )
      &&
      ( int32_array_is_equal( (*current).field_string_lengths, (*other).field_string_lengths, (*other).field_count ) == 1 )
      &&
      ( int32_array_is_equal( (*current).field_offsets, (*other).field_offsets, (*other).field_count ) == 1 )
      &&
      ( raw_buffer_is_equal( (*current).buf, (*other).buf ) == 1 )
   )
   {
      result = 1;
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_dispose

   dispose of a tuple, shallow dispose

   @param current the first tuple
*/
void
tuple_dispose( tuple_t **current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "*current ok", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == TUPLE_TYPE );
   INVARIANT(*current);

   int32_t i = 0;

   free( (**current).name );

   free( (**current).field_types );

   for ( i = 0; i < (**current).field_count; i++ )
   {
      free( (**current).field_names[i] );
   }
   free( (**current).field_names );

   free( (**current).field_array_counts );
   free( (**current).field_string_lengths );
   free( (**current).field_offsets );

   raw_buffer_deep_dispose( &(**current).buf );

   // dispose of allocated memory
   free(*current);

   // set pointer to null
   *current = NULL;

   return;
}

/**
   tuple_deep_dispose

   dispose of a tuple, deep dispose

   @param current the first tuple
*/
void
tuple_deep_dispose( tuple_t **current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "*current ok", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == TUPLE_TYPE );
   INVARIANT(*current);

   int32_t i = 0;

   free( (**current).name );

   free( (**current).field_types );

   for ( i = 0; i < (**current).field_count; i++ )
   {
      free( (**current).field_names[i] );
   }
   free( (**current).field_names );

   free( (**current).field_array_counts );
   free( (**current).field_string_lengths );
   free( (**current).field_offsets );

   raw_buffer_deep_dispose( &(**current).buf );

   // dispose of allocated memory
   free(*current);

   // set pointer to null
   *current = NULL;

   return;
}


/**
   tuple_name

   get the tuple's name

   @param current the first tuple
   @return the name
*/
char_t *
tuple_name( tuple_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   INVARIANT( current );

   char_t *result = NULL;

   // get name
   result = ( char_t * ) calloc( sizeof( (*current).name ) + 1, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   strcpy( result, (*current).name );

   INVARIANT( current );

   return result;
}

/**
   tuple_field_count

   get the tuple's field count

   @param current the first tuple
   @return the field count
*/
int32_t
tuple_field_count( tuple_t *current )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   INVARIANT( current );

   int32_t result = 0;

   result = (*current).field_count;

   INVARIANT( current );

   return result;
}

/**
   tuple_field_type

   get the tuple field's type

   @param current the first tuple
   @param index which field in the tuple
   @return the type
*/
int32_t
tuple_field_type( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   INVARIANT( current );

   int32_t result = 0;

   result = (*current).field_types[index];

   INVARIANT( current );

   return result;
}

/**
   tuple_field_name

   get the tuple field's name

   @param current the first tuple
   @param index which field in the tuple
   @return the name
*/
char_t *
tuple_field_name( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   INVARIANT( current );

   char_t *result = NULL;

   result = ( char_t * ) calloc( sizeof( (*current).name ) + 1, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   strcpy( result, (*current).field_names[index] );

   INVARIANT( current );

   return result;
}

/**
   tuple_field_array_count
*/
int32_t
tuple_field_array_count( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   INVARIANT( current );

   int32_t result = 1;
   int32_t type = 0;

   type = (*current).field_types[index];

   if ( ( type & ARRAY_MASK ) != 0 )
   {
      result = (*current).field_array_counts[index];
   }
   else if ( ( type & STRING_MASK ) != 0 )
   {
      result = (*current).field_string_lengths[index];
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_field_string_length
*/
int32_t
tuple_field_string_length( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   INVARIANT( current );

   int32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[index];

   if ( ( type & STRING_MASK ) != 0 )
   {
      result = (*current).field_string_lengths[index];
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_field_is_array
*/
int32_t
tuple_field_is_array( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   INVARIANT( current );

   int32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[index];

   if ( ( type & ARRAY_MASK ) != 0 )
   {
      result = 1;
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_field_is_string
*/
int32_t
tuple_field_is_string( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   INVARIANT( current );

   int32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[index];

   if ( ( type & STRING_MASK ) != 0 )
   {
      result = 1;
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_item_int8
*/
int8_t
tuple_item_int8( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_INT8_TYPE );
   INVARIANT( current );

   int32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_INT8_TYPE )
   {
      result = raw_buffer_read_int8( (*current).buf, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_int8
*/
void
tuple_put_int8( tuple_t *current, int32_t index, int8_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_INT8_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_INT8_TYPE )
   {
      raw_buffer_put_int8( (*current).buf, value, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_int16
*/
int16_t
tuple_item_int16( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_INT16_TYPE );
   INVARIANT( current );

   int32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_INT16_TYPE )
   {
      result = raw_buffer_read_int16( (*current).buf, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_int16
*/
void
tuple_put_int16( tuple_t *current, int32_t index, int16_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_INT16_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_INT16_TYPE )
   {
      raw_buffer_put_int16( (*current).buf, value, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_int32
*/
int32_t
tuple_item_int32( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_INT32_TYPE );
   INVARIANT( current );

   int32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_INT32_TYPE )
   {
      result = raw_buffer_read_int32( (*current).buf, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_int32
*/
void
tuple_put_int32( tuple_t *current, int32_t index, int32_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_INT32_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_INT32_TYPE )
   {
      raw_buffer_put_int32( (*current).buf, value, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_int64
*/
int64_t
tuple_item_int64( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_INT64_TYPE );
   INVARIANT( current );

   int32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_INT64_TYPE )
   {
      result = raw_buffer_read_int64( (*current).buf, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_int64
*/
void
tuple_put_int64( tuple_t *current, int32_t index, int64_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_INT64_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_INT64_TYPE )
   {
      raw_buffer_put_int64( (*current).buf, value, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_uint8
*/
uint8_t
tuple_item_uint8( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_UINT8_TYPE );
   INVARIANT( current );

   uint32_t result = 0;
   uint32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_UINT8_TYPE )
   {
      result = raw_buffer_read_uint8( (*current).buf, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_uint8
*/
void
tuple_put_uint8( tuple_t *current, int32_t index, uint8_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_UINT8_TYPE );
   INVARIANT( current );

   uint32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_UINT8_TYPE )
   {
      raw_buffer_put_uint8( (*current).buf, value, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_uint16
*/
uint16_t
tuple_item_uint16( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_UINT16_TYPE );
   INVARIANT( current );

   uint32_t result = 0;
   uint32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_UINT16_TYPE )
   {
      result = raw_buffer_read_uint16( (*current).buf, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_uint16
*/
void
tuple_put_uint16( tuple_t *current, int32_t index, uint16_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_UINT16_TYPE );
   INVARIANT( current );

   uint32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_UINT16_TYPE )
   {
      raw_buffer_put_uint16( (*current).buf, value, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_uint32
*/
uint32_t
tuple_item_uint32( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_UINT32_TYPE );
   INVARIANT( current );

   uint32_t result = 0;
   uint32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_UINT32_TYPE )
   {
      result = raw_buffer_read_uint32( (*current).buf, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_uint32
*/
void
tuple_put_uint32( tuple_t *current, int32_t index, uint32_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_UINT32_TYPE );
   INVARIANT( current );

   uint32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_UINT32_TYPE )
   {
      raw_buffer_put_uint32( (*current).buf, value, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_uint64
*/
uint64_t
tuple_item_uint64( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_UINT64_TYPE );
   INVARIANT( current );

   uint32_t result = 0;
   uint32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_UINT64_TYPE )
   {
      result = raw_buffer_read_uint64( (*current).buf, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_uint64
*/
void
tuple_put_uint64( tuple_t *current, int32_t index, uint64_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_UINT64_TYPE );
   INVARIANT( current );

   uint32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_UINT64_TYPE )
   {
      raw_buffer_put_uint64( (*current).buf, value, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_float32
*/
float32_t
tuple_item_float32( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_FLOAT32_TYPE );
   INVARIANT( current );

   float32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_FLOAT32_TYPE )
   {
      result = raw_buffer_read_float32( (*current).buf, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_float32
*/
void
tuple_put_float32( tuple_t *current, int32_t index, float32_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_FLOAT32_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_FLOAT32_TYPE )
   {
      raw_buffer_put_float32( (*current).buf, value, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_float64
*/
float64_t
tuple_item_float64( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_FLOAT64_TYPE );
   INVARIANT( current );

   float32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_FLOAT64_TYPE )
   {
      result = raw_buffer_read_float64( (*current).buf, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_float64
*/
void
tuple_put_float64( tuple_t *current, int32_t index, float64_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_FLOAT64_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_FLOAT64_TYPE )
   {
      raw_buffer_put_float64( (*current).buf, value, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_pointer
*/
void *
tuple_item_pointer( tuple_t *current, int32_t index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_POINTER_TYPE );
   INVARIANT( current );

   void *result = NULL;
   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_POINTER_TYPE )
   {
      result = raw_buffer_read_pointer( (*current).buf, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_pointer
*/
void
tuple_put_pointer( tuple_t *current, int32_t index, void *value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_POINTER_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_POINTER_TYPE )
   {
      raw_buffer_put_pointer( (*current).buf, value, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_string
*/
char_t *
tuple_item_string( tuple_t *current, int32_t index, int32_t *count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "count ok", count != NULL );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_STRING_TYPE );
   INVARIANT( current );

   char_t *result = NULL;
   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_STRING_TYPE )
   {
      result
         =  raw_buffer_read_cstring
            (
               (*current).buf,
               (*current).field_offsets[index],
               (*current).field_string_lengths[index]
            );
      result[ (*current).field_string_lengths[index] - 1 ] = 0;
   }

   *count = strlen( result );

   INVARIANT( current );

   return result;
}

/**
   tuple_put_string
*/
void
tuple_put_string( tuple_t *current, int32_t index, char_t *value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_STRING_TYPE );
   PRECONDITION( "value length OK", strlen( value ) < (*current).field_string_lengths[index] );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_STRING_TYPE )
   {
      raw_buffer_put_cstring( (*current).buf, value, (*current).field_offsets[index] );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_aint8
*/
int8_t *
tuple_item_aint8( tuple_t *current, int32_t index, int32_t *count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_INT8_TYPE );
   INVARIANT( current );

   int8_t *result = NULL;
   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_INT8_TYPE )
   {
      size = sizeof( int8_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make( size );
      raw_buffer_subcopy( buf, (*current).buf, 0, (*current).field_offsets[index], size );
      result = ( int8_t * ) raw_buffer_base( buf );
      raw_buffer_dispose( &buf );
   }

   *count = (*current).field_array_counts[index];

   INVARIANT( current );

   return result;
}

/**
   tuple_put_aint8
*/
void
tuple_put_aint8( tuple_t *current, int32_t index, int8_t *value, int32_t count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_INT8_TYPE );
   PRECONDITION( "field count OK", count == (*current).field_array_counts[index] );
   INVARIANT( current );

   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_INT8_TYPE )
   {
      size = sizeof( int8_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make_from_pointer( ( uint8_t * ) value, size );
      raw_buffer_subcopy( (*current).buf, buf, (*current).field_offsets[index], 0, size );
      raw_buffer_dispose( &buf );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_element_aint8
*/
int8_t
tuple_item_element_aint8( tuple_t *current, int32_t field_index, int32_t array_index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_INT8_TYPE );
   INVARIANT( current );

   int32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_INT8_TYPE )
   {
      result = raw_buffer_read_int8( (*current).buf, (*current).field_offsets[field_index] + sizeof( int8_t ) * array_index );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_element_aint8
*/
void
tuple_put_element_aint8( tuple_t *current, int32_t field_index, int32_t array_index, int8_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_INT8_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_INT8_TYPE )
   {
      raw_buffer_put_int8( (*current).buf, value, (*current).field_offsets[field_index] + sizeof( int8_t )*array_index );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_aint16
*/
int16_t *
tuple_item_aint16( tuple_t *current, int32_t index, int32_t *count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_INT16_TYPE );
   INVARIANT( current );

   int16_t *result = NULL;
   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_INT16_TYPE )
   {
      size = sizeof( int16_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make( size );
      raw_buffer_subcopy( buf, (*current).buf, 0, (*current).field_offsets[index], size );
      result = ( int16_t * ) raw_buffer_base( buf );
      raw_buffer_dispose( &buf );
   }

   *count = (*current).field_array_counts[index];

   INVARIANT( current );

   return result;
}

/**
   tuple_put_aint16
*/
void
tuple_put_aint16( tuple_t *current, int32_t index, int16_t *value, int32_t count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_INT16_TYPE );
   PRECONDITION( "field count OK", count == (*current).field_array_counts[index] );
   INVARIANT( current );

   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_INT16_TYPE )
   {
      size = sizeof( int16_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make_from_pointer( ( uint8_t * ) value, size );
      raw_buffer_subcopy( (*current).buf, buf, (*current).field_offsets[index], 0, size );
      raw_buffer_dispose( &buf );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_element_aint16
*/
int16_t
tuple_item_element_aint16( tuple_t *current, int32_t field_index, int32_t array_index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_INT16_TYPE );
   INVARIANT( current );

   int32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_INT16_TYPE )
   {
      result = raw_buffer_read_int16( (*current).buf, (*current).field_offsets[field_index] + sizeof( int16_t ) * array_index );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_element_aint16
*/
void
tuple_put_element_aint16( tuple_t *current, int32_t field_index, int32_t array_index, int16_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_INT16_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_INT16_TYPE )
   {
      raw_buffer_put_int16( (*current).buf, value, (*current).field_offsets[field_index] + sizeof( int16_t )*array_index );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_aint32
*/
int32_t *
tuple_item_aint32( tuple_t *current, int32_t index, int32_t *count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_INT32_TYPE );
   INVARIANT( current );

   int32_t *result = NULL;
   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_INT32_TYPE )
   {
      size = sizeof( int32_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make( size );
      raw_buffer_subcopy( buf, (*current).buf, 0, (*current).field_offsets[index], size );
      result = ( int32_t * ) raw_buffer_base( buf );
      raw_buffer_dispose( &buf );
   }

   *count = (*current).field_array_counts[index];

   INVARIANT( current );

   return result;
}

/**
   tuple_put_aint32
*/
void
tuple_put_aint32( tuple_t *current, int32_t index, int32_t *value, int32_t count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_INT32_TYPE );
   PRECONDITION( "field count OK", count == (*current).field_array_counts[index] );
   INVARIANT( current );

   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_INT32_TYPE )
   {
      size = sizeof( int32_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make_from_pointer( ( uint8_t * ) value, size );
      raw_buffer_subcopy( (*current).buf, buf, (*current).field_offsets[index], 0, size );
      raw_buffer_dispose( &buf );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_element_aint32
*/
int32_t
tuple_item_element_aint32( tuple_t *current, int32_t field_index, int32_t array_index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_INT32_TYPE );
   INVARIANT( current );

   int32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_INT32_TYPE )
   {
      result = raw_buffer_read_int32( (*current).buf, (*current).field_offsets[field_index] + sizeof( int32_t ) * array_index );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_element_aint32
*/
void
tuple_put_element_aint32( tuple_t *current, int32_t field_index, int32_t array_index, int32_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_INT32_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_INT32_TYPE )
   {
      raw_buffer_put_int32( (*current).buf, value, (*current).field_offsets[field_index] + sizeof( int32_t )*array_index );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_aint64
*/
int64_t *
tuple_item_aint64( tuple_t *current, int32_t index, int32_t *count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_INT64_TYPE );
   INVARIANT( current );

   int64_t *result = NULL;
   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_INT64_TYPE )
   {
      size = sizeof( int64_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make( size );
      raw_buffer_subcopy( buf, (*current).buf, 0, (*current).field_offsets[index], size );
      result = ( int64_t * ) raw_buffer_base( buf );
      raw_buffer_dispose( &buf );
   }

   *count = (*current).field_array_counts[index];

   INVARIANT( current );

   return result;
}

/**
   tuple_put_aint64
*/
void
tuple_put_aint64( tuple_t *current, int32_t index, int64_t *value, int32_t count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_INT64_TYPE );
   PRECONDITION( "field count OK", count == (*current).field_array_counts[index] );
   INVARIANT( current );

   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_INT64_TYPE )
   {
      size = sizeof( int64_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make_from_pointer( ( uint8_t * ) value, size );
      raw_buffer_subcopy( (*current).buf, buf, (*current).field_offsets[index], 0, size );
      raw_buffer_dispose( &buf );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_element_aint64
*/
int64_t
tuple_item_element_aint64( tuple_t *current, int32_t field_index, int32_t array_index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_INT64_TYPE );
   INVARIANT( current );

   int32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_INT64_TYPE )
   {
      result = raw_buffer_read_int64( (*current).buf, (*current).field_offsets[field_index] + sizeof( int64_t ) * array_index );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_element_aint64
*/
void
tuple_put_element_aint64( tuple_t *current, int32_t field_index, int32_t array_index, int64_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_INT64_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_INT64_TYPE )
   {
      raw_buffer_put_int64( (*current).buf, value, (*current).field_offsets[field_index] + sizeof( int64_t )*array_index );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_auint8
*/
uint8_t *
tuple_item_auint8( tuple_t *current, int32_t index, int32_t *count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_UINT8_TYPE );
   INVARIANT( current );

   uint8_t *result = NULL;
   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_UINT8_TYPE )
   {
      size = sizeof( int8_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make( size );
      raw_buffer_subcopy( buf, (*current).buf, 0, (*current).field_offsets[index], size );
      result = ( uint8_t * ) raw_buffer_base( buf );
      raw_buffer_dispose( &buf );
   }

   *count = (*current).field_array_counts[index];

   INVARIANT( current );

   return result;
}

/**
   tuple_put_auint8
*/
void
tuple_put_auint8( tuple_t *current, int32_t index, uint8_t *value, int32_t count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_UINT8_TYPE );
   PRECONDITION( "field count OK", count == (*current).field_array_counts[index] );
   INVARIANT( current );

   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_UINT8_TYPE )
   {
      size = sizeof( int8_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make_from_pointer( ( uint8_t * ) value, size );
      raw_buffer_subcopy( (*current).buf, buf, (*current).field_offsets[index], 0, size );
      raw_buffer_dispose( &buf );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_element_auint8
*/
uint8_t
tuple_item_element_auint8( tuple_t *current, int32_t field_index, int32_t array_index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_UINT8_TYPE );
   INVARIANT( current );

   uint32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_UINT8_TYPE )
   {
      result = raw_buffer_read_uint8( (*current).buf, (*current).field_offsets[field_index] + sizeof( uint8_t ) * array_index );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_element_auint8
*/
void
tuple_put_element_auint8( tuple_t *current, int32_t field_index, int32_t array_index, uint8_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_UINT8_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_UINT8_TYPE )
   {
      raw_buffer_put_uint8( (*current).buf, value, (*current).field_offsets[field_index] + sizeof( uint8_t )*array_index );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_auint16
*/
uint16_t *
tuple_item_auint16( tuple_t *current, int32_t index, int32_t *count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_UINT16_TYPE );
   INVARIANT( current );

   uint16_t *result = NULL;
   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_UINT16_TYPE )
   {
      size = sizeof( int16_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make( size );
      raw_buffer_subcopy( buf, (*current).buf, 0, (*current).field_offsets[index], size );
      result = ( uint16_t * )raw_buffer_base( buf );
      raw_buffer_dispose( &buf );
   }

   *count = (*current).field_array_counts[index];

   INVARIANT( current );

   return result;
}

/**
   tuple_put_auint16
*/
void
tuple_put_auint16( tuple_t *current, int32_t index, uint16_t *value, int32_t count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_UINT16_TYPE );
   PRECONDITION( "field count OK", count == (*current).field_array_counts[index] );
   INVARIANT( current );

   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_UINT16_TYPE )
   {
      size = sizeof( int16_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make_from_pointer( ( uint8_t * ) value, size );
      raw_buffer_subcopy( (*current).buf, buf, (*current).field_offsets[index], 0, size );
      raw_buffer_dispose( &buf );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_element_auint16
*/
uint16_t
tuple_item_element_auint16( tuple_t *current, int32_t field_index, int32_t array_index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_UINT16_TYPE );
   INVARIANT( current );

   uint32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_UINT16_TYPE )
   {
      result = raw_buffer_read_uint16( (*current).buf, (*current).field_offsets[field_index] + sizeof( uint16_t ) * array_index );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_element_auint16
*/
void
tuple_put_element_auint16( tuple_t *current, int32_t field_index, int32_t array_index, uint16_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_UINT16_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_UINT16_TYPE )
   {
      raw_buffer_put_uint16( (*current).buf, value, (*current).field_offsets[field_index] + sizeof( uint16_t )*array_index );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_auint32
*/
uint32_t *
tuple_item_auint32( tuple_t *current, int32_t index, int32_t *count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_UINT32_TYPE );
   INVARIANT( current );

   uint32_t *result = NULL;
   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_UINT32_TYPE )
   {
      size = sizeof( int32_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make( size );
      raw_buffer_subcopy( buf, (*current).buf, 0, (*current).field_offsets[index], size );
      result = ( uint32_t * )raw_buffer_base( buf );
      raw_buffer_dispose( &buf );
   }

   *count = (*current).field_array_counts[index];

   INVARIANT( current );

   return result;
}

/**
   tuple_put_auint32
*/
void
tuple_put_auint32( tuple_t *current, int32_t index, uint32_t *value, int32_t count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_UINT32_TYPE );
   PRECONDITION( "field count OK", count == (*current).field_array_counts[index] );
   INVARIANT( current );

   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_UINT32_TYPE )
   {
      size = sizeof( int32_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make_from_pointer( ( uint8_t * ) value, size );
      raw_buffer_subcopy( (*current).buf, buf, (*current).field_offsets[index], 0, size );
      raw_buffer_dispose( &buf );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_element_auint32
*/
uint32_t
tuple_item_element_auint32( tuple_t *current, int32_t field_index, int32_t array_index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_UINT32_TYPE );
   INVARIANT( current );

   uint32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_UINT32_TYPE )
   {
      result = raw_buffer_read_uint32( (*current).buf, (*current).field_offsets[field_index] + sizeof( uint32_t ) * array_index );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_element_auint32
*/
void
tuple_put_element_auint32( tuple_t *current, int32_t field_index, int32_t array_index, uint32_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_UINT32_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_UINT32_TYPE )
   {
      raw_buffer_put_uint32( (*current).buf, value, (*current).field_offsets[field_index] + sizeof( uint32_t )*array_index );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_auint64
*/
uint64_t *
tuple_item_auint64( tuple_t *current, int32_t index, int32_t *count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_UINT64_TYPE );
   INVARIANT( current );

   uint64_t *result = NULL;
   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_UINT64_TYPE )
   {
      size = sizeof( int64_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make( size );
      raw_buffer_subcopy( buf, (*current).buf, 0, (*current).field_offsets[index], size );
      result = ( uint64_t * )raw_buffer_base( buf );
      raw_buffer_dispose( &buf );
   }

   *count = (*current).field_array_counts[index];

   INVARIANT( current );

   return result;
}

/**
   tuple_put_auint64
*/
void
tuple_put_auint64( tuple_t *current, int32_t index, uint64_t *value, int32_t count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_UINT64_TYPE );
   PRECONDITION( "field count OK", count == (*current).field_array_counts[index] );
   INVARIANT( current );

   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_UINT64_TYPE )
   {
      size = sizeof( int64_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make_from_pointer( ( uint8_t * ) value, size );
      raw_buffer_subcopy( (*current).buf, buf, (*current).field_offsets[index], 0, size );
      raw_buffer_dispose( &buf );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_element_auint64
*/
uint64_t
tuple_item_element_auint64( tuple_t *current, int32_t field_index, int32_t array_index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_UINT64_TYPE );
   INVARIANT( current );

   uint32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_UINT64_TYPE )
   {
      result = raw_buffer_read_uint64( (*current).buf, (*current).field_offsets[field_index] + sizeof( uint64_t ) * array_index );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_element_auint64
*/
void
tuple_put_element_auint64( tuple_t *current, int32_t field_index, int32_t array_index, uint64_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_UINT64_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_UINT64_TYPE )
   {
      raw_buffer_put_uint64( (*current).buf, value, (*current).field_offsets[field_index] + sizeof( uint64_t )*array_index );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_afloat32
*/
float32_t *
tuple_item_afloat32( tuple_t *current, int32_t index, int32_t *count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_FLOAT32_TYPE );
   INVARIANT( current );

   float32_t *result = NULL;
   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_FLOAT32_TYPE )
   {
      size = sizeof( float32_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make( size );
      raw_buffer_subcopy( buf, (*current).buf, 0, (*current).field_offsets[index], size );
      result = ( float32_t * ) raw_buffer_base( buf );
      raw_buffer_dispose( &buf );
   }

   *count = (*current).field_array_counts[index];

   INVARIANT( current );

   return result;
}

/**
   tuple_put_afloat32
*/
void
tuple_put_afloat32( tuple_t *current, int32_t index, float32_t *value, int32_t count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_FLOAT32_TYPE );
   PRECONDITION( "field count OK", count == (*current).field_array_counts[index] );
   INVARIANT( current );

   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_FLOAT32_TYPE )
   {
      size = sizeof( float32_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make_from_pointer( ( uint8_t * ) value, size );
      raw_buffer_subcopy( (*current).buf, buf, (*current).field_offsets[index], 0, size );
      raw_buffer_dispose( &buf );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_element_afloat32
*/
float32_t
tuple_item_element_afloat32( tuple_t *current, int32_t field_index, int32_t array_index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_FLOAT32_TYPE );
   INVARIANT( current );

   float32_t result = 0;
   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_FLOAT32_TYPE )
   {
      result = raw_buffer_read_float32( (*current).buf, (*current).field_offsets[field_index] + sizeof( float32_t ) * array_index );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_element_afloat32
*/
void
tuple_put_element_afloat32( tuple_t *current, int32_t field_index, int32_t array_index, float32_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_FLOAT32_TYPE );
   INVARIANT( current );

   int32_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_FLOAT32_TYPE )
   {
      raw_buffer_put_float32( (*current).buf, value, (*current).field_offsets[field_index] + sizeof( float32_t )*array_index );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_afloat64
*/
float64_t *
tuple_item_afloat64( tuple_t *current, int32_t index, int32_t *count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_FLOAT64_TYPE );
   INVARIANT( current );

   float64_t *result = NULL;
   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_FLOAT64_TYPE )
   {
      size = sizeof( float64_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make( size );
      raw_buffer_subcopy( buf, (*current).buf, 0, (*current).field_offsets[index], size );
      result = ( float64_t * ) raw_buffer_base( buf );
      raw_buffer_dispose( &buf );
   }

   *count = (*current).field_array_counts[index];

   INVARIANT( current );

   return result;
}

/**
   tuple_put_afloat64
*/
void
tuple_put_afloat64( tuple_t *current, int32_t index, float64_t *value, int32_t count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_FLOAT64_TYPE );
   PRECONDITION( "field count OK", count == (*current).field_array_counts[index] );
   INVARIANT( current );

   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_FLOAT64_TYPE )
   {
      size = sizeof( float64_t ) * (*current).field_array_counts[index];
      buf = raw_buffer_make_from_pointer( ( uint8_t * ) value, size );
      raw_buffer_subcopy( (*current).buf, buf, (*current).field_offsets[index], 0, size );
      raw_buffer_dispose( &buf );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_element_afloat64
*/
float64_t
tuple_item_element_afloat64( tuple_t *current, int32_t field_index, int32_t array_index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_FLOAT64_TYPE );
   INVARIANT( current );

   float64_t result = 0;
   int64_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_FLOAT64_TYPE )
   {
      result = raw_buffer_read_float64( (*current).buf, (*current).field_offsets[field_index] + sizeof( float64_t ) * array_index );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_element_afloat64
*/
void
tuple_put_element_afloat64( tuple_t *current, int32_t field_index, int32_t array_index, float64_t value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_FLOAT64_TYPE );
   INVARIANT( current );

   int64_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_FLOAT64_TYPE )
   {
      raw_buffer_put_float64( (*current).buf, value, (*current).field_offsets[field_index] + sizeof( float64_t )*array_index );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_apointer
*/
void **
tuple_item_apointer( tuple_t *current, int32_t index, int32_t *count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_POINTER_TYPE );
   INVARIANT( current );

   void **result = NULL;
   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_POINTER_TYPE )
   {
      size = sizeof( void * ) * (*current).field_array_counts[index];
      buf = raw_buffer_make( size );
      raw_buffer_subcopy( buf, (*current).buf, 0, (*current).field_offsets[index], size );
      result = ( void ** ) raw_buffer_base( buf );
      raw_buffer_dispose( &buf );
   }

   *count = (*current).field_array_counts[index];

   INVARIANT( current );

   return result;
}

/**
   tuple_put_apointer
*/
void
tuple_put_apointer( tuple_t *current, int32_t index, void **value, int32_t count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_POINTER_TYPE );
   PRECONDITION( "field count OK", count == (*current).field_array_counts[index] );
   INVARIANT( current );

   int32_t type = 0;
   raw_buffer_t *buf = NULL;
   int32_t size = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_POINTER_TYPE )
   {
      size = sizeof( void * ) * (*current).field_array_counts[index];
      buf = raw_buffer_make_from_pointer( ( uint8_t * ) value, size );
      raw_buffer_subcopy( (*current).buf, buf, (*current).field_offsets[index], 0, size );
      raw_buffer_dispose( &buf );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_element_apointer
*/
void *
tuple_item_element_apointer( tuple_t *current, int32_t field_index, int32_t array_index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_POINTER_TYPE );
   INVARIANT( current );

   void **result = NULL;
   int64_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_POINTER_TYPE )
   {
      result = raw_buffer_read_pointer( (*current).buf, (*current).field_offsets[field_index] + sizeof( void * )*array_index );
   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_element_apointer
*/
void
tuple_put_element_apointer( tuple_t *current, int32_t field_index, int32_t array_index, void *value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_POINTER_TYPE );
   INVARIANT( current );

   int64_t type = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_POINTER_TYPE )
   {
      raw_buffer_put_pointer( (*current).buf, value, (*current).field_offsets[field_index] + sizeof( void * )*array_index );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_astring
*/
char_t **
tuple_item_astring( tuple_t *current, int32_t index, int32_t *count, int32_t *length )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_STRING_TYPE );
   INVARIANT( current );

   char_t **result = NULL;
   int32_t type = 0;
   int32_t size = 0;
   int32_t offset = 0;
   int32_t i = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_STRING_TYPE )
   {
      result = ( char_t ** ) calloc( (*current).field_array_counts[index], sizeof( char_t * ) );
      CHECK( "result allocated correctly", result != NULL );


      size = sizeof( char_t ) * (*current).field_string_lengths[index];

      for ( i = 0; i < (*current).field_array_counts[index]; i++ )
      {
         result[i]
            =  raw_buffer_read_cstring
               (
                  (*current).buf,
                  (*current).field_offsets[index] + offset,
                  (*current).field_string_lengths[index]
               );
         result[i][ (*current).field_string_lengths[index] - 1 ] = 0;

         offset = offset + size;
      }
   }

   *count = (*current).field_array_counts[index];
   *length = (*current).field_string_lengths[index];

   INVARIANT( current );

   return result;
}

/**
   tuple_put_astring
*/
void
tuple_put_astring( tuple_t *current, int32_t index, char_t **value, int32_t array_count, int32_t string_length )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "index ok", ( index >= 0 ) && ( index <= (*current).field_count ) );
   PRECONDITION( "field type OK", (*current).field_types[index] == TUPLE_ARRAY_STRING_TYPE );
   PRECONDITION( "array count OK", array_count == (*current).field_array_counts[index] );
   PRECONDITION( "string length OK", string_length == (*current).field_string_lengths[index] );
   INVARIANT( current );

   int32_t type = 0;
   int32_t size = 0;
   int32_t offset = 0;
   int32_t i = 0;

   type = (*current).field_types[index];

   if ( type == TUPLE_ARRAY_STRING_TYPE )
   {
      size = sizeof( char_t ) * (*current).field_string_lengths[index];

      for ( i = 0; i < (*current).field_array_counts[index]; i++ )
      {
         raw_buffer_put_cstring( (*current).buf, value[i], (*current).field_offsets[index] + offset );

         offset = offset + size;
      }
   }

   INVARIANT( current );

   return;
}

/**
   tuple_item_element_astring
*/
char_t *
tuple_item_element_astring( tuple_t *current, int32_t field_index, int32_t array_index )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_STRING_TYPE );
   INVARIANT( current );

   char_t *result = NULL;
   int32_t type = 0;
   int32_t size = 0;
   int32_t offset = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_STRING_TYPE )
   {
      size = sizeof( char_t ) * (*current).field_string_lengths[field_index];
      offset = array_index * size;

      result
         =  raw_buffer_read_cstring
            (
               (*current).buf,
               (*current).field_offsets[field_index] + offset,
               (*current).field_string_lengths[field_index]
            );
      result[ (*current).field_string_lengths[field_index] - 1 ] = 0;

   }

   INVARIANT( current );

   return result;
}

/**
   tuple_put_element_astring
*/
void
tuple_put_element_astring( tuple_t *current, int32_t field_index, int32_t array_index, char_t *value )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "field_index ok", ( field_index >= 0 ) && ( field_index <= (*current).field_count ) );
   PRECONDITION( "array_index ok", ( array_index >= 0 ) && ( array_index <= (*current).field_array_counts[field_index] ) );
   PRECONDITION( "field type OK", (*current).field_types[field_index] == TUPLE_ARRAY_STRING_TYPE );
   PRECONDITION( "value length OK", strlen( value ) < (*current).field_string_lengths[field_index] );
   INVARIANT( current );

   int32_t type = 0;
   int32_t size = 0;
   int32_t offset = 0;

   type = (*current).field_types[field_index];

   if ( type == TUPLE_ARRAY_STRING_TYPE )
   {
      size = sizeof( char_t ) * (*current).field_string_lengths[field_index];
      offset = array_index * size;

      raw_buffer_put_cstring( (*current).buf, value, (*current).field_offsets[field_index] + offset );
   }

   INVARIANT( current );

   return;
}

/**
   tuple_header_as_byte_array
*/
uint8_t *
tuple_header_as_byte_array( tuple_t *current, int32_t *count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   INVARIANT( current );

   uint8_t *result = NULL;
   raw_buffer_t *buf = NULL;
   raw_buffer_t *b = NULL;
   int32_t i = 0;

   // construct output byte array
   buf = raw_buffer_make( 2 * sizeof( int32_t ) );

   // tuple type
   raw_buffer_put_int32_be( buf, TUPLE_TYPE, 0 );

   // leave space for byte array length (including type and this length)

   // name byte count
   b = raw_buffer_make( sizeof( int32_t ) );
   raw_buffer_put_int32_be( b, strlen( (*current).name ) + 1, 0 );
   raw_buffer_append( buf, b );
   raw_buffer_deep_dispose( &b );

   // name
   b = raw_buffer_make( strlen( (*current).name ) + 1 );
   raw_buffer_put_cstring( b, (*current).name, 0 );
   raw_buffer_append( buf, b );
   raw_buffer_deep_dispose( &b );

   // field_count
   b = raw_buffer_make( sizeof( int32_t ) );
   raw_buffer_put_int32_be( b, (*current).field_count, 0 );
   raw_buffer_append( buf, b );
   raw_buffer_deep_dispose( &b );

   // field_types
   b = raw_buffer_make( (*current).field_count * sizeof( int32_t ) );
   for ( i = 0; i < (*current).field_count; i++ )
   {
      raw_buffer_put_int32_be( b, (*current).field_types[i], i * sizeof( int32_t ) );
   }
   raw_buffer_append( buf, b );
   raw_buffer_deep_dispose( &b );

   // field names
   for ( i = 0; i < (*current).field_count; i++ )
   {
      // field name length
      b = raw_buffer_make( sizeof( int32_t ) );
      raw_buffer_put_int32_be( b, strlen( (*current).field_names[i] ) + 1, 0 );
      raw_buffer_append( buf, b );
      raw_buffer_deep_dispose( &b );

      // field name
      b = raw_buffer_make( strlen( (*current).field_names[i] ) + 1 );
      raw_buffer_put_cstring( b, (*current).field_names[i], 0 );
      raw_buffer_append( buf, b );
      raw_buffer_deep_dispose( &b );
   }

   // field array counts
   b = raw_buffer_make( (*current).field_count * sizeof( int32_t ) );
   for ( i = 0; i < (*current).field_count; i++ )
   {
      raw_buffer_put_int32_be( b, (*current).field_array_counts[i], i * sizeof( int32_t ) );
   }
   raw_buffer_append( buf, b );
   raw_buffer_deep_dispose( &b );

   // field string lengths
   b = raw_buffer_make( (*current).field_count * sizeof( int32_t ) );
   for ( i = 0; i < (*current).field_count; i++ )
   {
      raw_buffer_put_int32_be( b, (*current).field_string_lengths[i], i * sizeof( int32_t ) );
   }
   raw_buffer_append( buf, b );
   raw_buffer_deep_dispose( &b );

   // field offsets
   b = raw_buffer_make( (*current).field_count * sizeof( int32_t ) );
   for ( i = 0; i < (*current).field_count; i++ )
   {
      raw_buffer_put_int32_be( b, (*current).field_offsets[i], i * sizeof( int32_t ) );
   }
   raw_buffer_append( buf, b );
   raw_buffer_deep_dispose( &b );

   // put byte array length
   raw_buffer_put_int32_be( buf, raw_buffer_count( buf ), 4 );

   // get result byte pointer
   *count = raw_buffer_count( buf );
   result = raw_buffer_base( buf );
   raw_buffer_dispose( &buf );

   INVARIANT( current );

   return result;
}

/**
   tuple_as_byte_array
*/
uint8_t *
tuple_as_byte_array( tuple_t *current, int32_t *byte_array_count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   INVARIANT( current );

   uint8_t *result = NULL;
   raw_buffer_t *buf = NULL;
   int32_t i = 0;
   int32_t i_array = 0;
   int32_t type = 0;
   int32_t offset = 0;
   int32_t count = 0;
   int32_t length = 0;
   char_t *s = NULL;

   // construct output byte array
   buf = raw_buffer_make( raw_buffer_count( (*current).buf ) );

   // by field
   for ( i = 0; i < (*current).field_count; i++ )
   {

      // type
      type = (*current).field_types[i];

      // offset
      offset = (*current).field_offsets[i];

      // count
      count = (*current).field_array_counts[i];

      // length
      length = (*current).field_string_lengths[i];

      switch( type )
      {

         case TUPLE_INT8_TYPE:
            raw_buffer_put_int8_be( buf, raw_buffer_read_int8( (*current).buf, offset ), offset );
            break;

         case TUPLE_INT16_TYPE:
            raw_buffer_put_int16_be( buf, raw_buffer_read_int16( (*current).buf, offset ), offset );
            break;

         case TUPLE_INT32_TYPE:
            raw_buffer_put_int32_be( buf, raw_buffer_read_int32( (*current).buf, offset ), offset );
            break;

         case TUPLE_INT64_TYPE:
            raw_buffer_put_int64_be( buf, raw_buffer_read_int64( (*current).buf, offset ), offset );
            break;

         case TUPLE_UINT8_TYPE:
            raw_buffer_put_uint8_be( buf, raw_buffer_read_uint8( (*current).buf, offset ), offset );
            break;

         case TUPLE_UINT16_TYPE:
            raw_buffer_put_uint16_be( buf, raw_buffer_read_uint16( (*current).buf, offset ), offset );
            break;

         case TUPLE_UINT32_TYPE:
            raw_buffer_put_uint32_be( buf, raw_buffer_read_uint32( (*current).buf, offset ), offset );
            break;

         case TUPLE_UINT64_TYPE:
            raw_buffer_put_uint64_be( buf, raw_buffer_read_uint64( (*current).buf, offset ), offset );
            break;

         case TUPLE_FLOAT32_TYPE:
            raw_buffer_put_float32_be( buf, raw_buffer_read_float32( (*current).buf, offset ), offset );
            break;

         case TUPLE_FLOAT64_TYPE:
            raw_buffer_put_float64_be( buf, raw_buffer_read_float64( (*current).buf, offset ), offset );
            break;

         case TUPLE_STRING_TYPE:
            s = raw_buffer_read_cstring( (*current).buf, offset, length );
            raw_buffer_put_cstring( buf, s, offset );
            free( s );
            break;

         case TUPLE_ARRAY_INT8_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_int8_be
               (
                  buf,
                  raw_buffer_read_int8( (*current).buf, offset + i_array * sizeof( int8_t ) ),
                  offset + i_array * sizeof( int8_t )
               );
            }
            break;

         case TUPLE_ARRAY_INT16_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_int16_be
               (
                  buf,
                  raw_buffer_read_int16( (*current).buf, offset + i_array * sizeof( int16_t ) ),
                  offset + i_array * sizeof( int16_t )
               );
            }
            break;

         case TUPLE_ARRAY_INT32_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_int32_be
               (
                  buf,
                  raw_buffer_read_int32( (*current).buf, offset + i_array * sizeof( int32_t ) ),
                  offset + i_array * sizeof( int32_t )
               );
            }
            break;

         case TUPLE_ARRAY_INT64_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_int64_be
               (
                  buf,
                  raw_buffer_read_int64( (*current).buf, offset + i_array * sizeof( int64_t ) ),
                  offset + i_array * sizeof( int64_t )
               );
            }
            break;

         case TUPLE_ARRAY_UINT8_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_uint8_be
               (
                  buf,
                  raw_buffer_read_uint8( (*current).buf, offset + i_array * sizeof( uint8_t ) ),
                  offset + i_array * sizeof( uint8_t )
               );
            }
            break;

         case TUPLE_ARRAY_UINT16_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_uint16_be
               (
                  buf,
                  raw_buffer_read_uint16( (*current).buf, offset + i_array * sizeof( uint16_t ) ),
                  offset + i_array * sizeof( uint16_t )
               );
            }
            break;

         case TUPLE_ARRAY_UINT32_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_uint32_be
               (
                  buf,
                  raw_buffer_read_uint32( (*current).buf, offset + i_array * sizeof( uint32_t ) ),
                  offset + i_array * sizeof( uint32_t )
               );
            }
            break;

         case TUPLE_ARRAY_UINT64_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_uint64_be
               (
                  buf,
                  raw_buffer_read_uint64( (*current).buf, offset + i_array * sizeof( uint64_t ) ),
                  offset + i_array * sizeof( uint64_t )
               );
            }
            break;

         case TUPLE_ARRAY_FLOAT32_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_float32_be
               (
                  buf,
                  raw_buffer_read_float32( (*current).buf, offset + i_array * sizeof( float32_t ) ),
                  offset + i_array * sizeof( float32_t )
               );
            }
            break;

         case TUPLE_ARRAY_FLOAT64_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_float64_be
               (
                  buf,
                  raw_buffer_read_float64( (*current).buf, offset + i_array * sizeof( float64_t ) ),
                  offset + i_array * sizeof( float64_t )
               );
            }
            break;

         case TUPLE_ARRAY_STRING_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               s = raw_buffer_read_cstring( (*current).buf, offset + i_array * length, length );
               raw_buffer_put_cstring
               (
                  buf,
                  s,
                  offset + i_array * length
               );
               free( s );
            }

            break;

      }
   }

   // get result
   *byte_array_count = raw_buffer_count( buf );
   result = raw_buffer_base( buf );
   raw_buffer_dispose( &buf );

   INVARIANT( current );

   return result;
}

/**
   tuple_from_byte_array
*/
void
tuple_from_byte_array( tuple_t *current, uint8_t *byte_array, int32_t byte_array_count )
{
   PRECONDITION( "current ok", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == TUPLE_TYPE );
   PRECONDITION( "byte_array ok", byte_array != NULL );
   PRECONDITION( "byte_array_count ok", byte_array_count == raw_buffer_count( (*current).buf ) );
   INVARIANT( current );

   raw_buffer_t *buf = NULL;
   int32_t i = 0;
   int32_t i_array = 0;
   int32_t type = 0;
   int32_t offset = 0;
   int32_t count = 0;
   int32_t length = 0;
   char_t *s = NULL;

   // construct raw buffer
   buf = raw_buffer_make_from_pointer( byte_array, raw_buffer_count( (*current).buf ) );

   // by field
   for ( i = 0; i < (*current).field_count; i++ )
   {

      // type
      type = (*current).field_types[i];

      // offset
      offset = (*current).field_offsets[i];

      // count
      count = (*current).field_array_counts[i];

      // length
      length = (*current).field_string_lengths[i];

      switch( type )
      {

         case TUPLE_INT8_TYPE:
            raw_buffer_put_int8( (*current).buf, raw_buffer_read_int8_be( buf, offset ), offset );
            break;

         case TUPLE_INT16_TYPE:
            raw_buffer_put_int16( (*current).buf, raw_buffer_read_int16_be( buf, offset ), offset );
            break;

         case TUPLE_INT32_TYPE:
            raw_buffer_put_int32( (*current).buf, raw_buffer_read_int32_be( buf, offset ), offset );
            break;

         case TUPLE_INT64_TYPE:
            raw_buffer_put_int64( (*current).buf, raw_buffer_read_int64_be( buf, offset ), offset );
            break;

         case TUPLE_UINT8_TYPE:
            raw_buffer_put_uint8( (*current).buf, raw_buffer_read_uint8_be( buf, offset ), offset );
            break;

         case TUPLE_UINT16_TYPE:
            raw_buffer_put_uint16( (*current).buf, raw_buffer_read_uint16_be( buf, offset ), offset );
            break;

         case TUPLE_UINT32_TYPE:
            raw_buffer_put_uint32( (*current).buf, raw_buffer_read_uint32_be( buf, offset ), offset );
            break;

         case TUPLE_UINT64_TYPE:
            raw_buffer_put_uint64( (*current).buf, raw_buffer_read_uint64_be( buf, offset ), offset );
            break;

         case TUPLE_FLOAT32_TYPE:
            raw_buffer_put_float32( (*current).buf, raw_buffer_read_float32_be( buf, offset ), offset );
            break;

         case TUPLE_FLOAT64_TYPE:
            raw_buffer_put_float64( (*current).buf, raw_buffer_read_float64_be( buf, offset ), offset );
            break;

         case TUPLE_STRING_TYPE:
            s = raw_buffer_read_cstring( buf, offset, length );
            raw_buffer_put_cstring( (*current).buf, s, offset );
            free( s );
            break;

         case TUPLE_ARRAY_INT8_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_int8
               (
                  (*current).buf,
                  raw_buffer_read_int8_be( buf, offset + i_array * sizeof( int8_t ) ),
                  offset + i_array * sizeof( int8_t )
               );
            }
            break;

         case TUPLE_ARRAY_INT16_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_int16
               (
                  (*current).buf,
                  raw_buffer_read_int16_be( buf, offset + i_array * sizeof( int16_t ) ),
                  offset + i_array * sizeof( int16_t )
               );
            }
            break;

         case TUPLE_ARRAY_INT32_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_int32
               (
                  (*current).buf,
                  raw_buffer_read_int32_be( buf, offset + i_array * sizeof( int32_t ) ),
                  offset + i_array * sizeof( int32_t )
               );
            }
            break;

         case TUPLE_ARRAY_INT64_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_int64
               (
                  (*current).buf,
                  raw_buffer_read_int64_be( buf, offset + i_array * sizeof( int64_t ) ),
                  offset + i_array * sizeof( int64_t )
               );
            }
            break;

         case TUPLE_ARRAY_UINT8_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_uint8
               (
                  (*current).buf,
                  raw_buffer_read_uint8_be( buf, offset + i_array * sizeof( uint8_t ) ),
                  offset + i_array * sizeof( uint8_t )
               );
            }
            break;

         case TUPLE_ARRAY_UINT16_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_uint16
               (
                  (*current).buf,
                  raw_buffer_read_uint16_be( buf, offset + i_array * sizeof( uint16_t ) ),
                  offset + i_array * sizeof( uint16_t )
               );
            }
            break;

         case TUPLE_ARRAY_UINT32_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_uint32
               (
                  (*current).buf,
                  raw_buffer_read_uint32_be( buf, offset + i_array * sizeof( uint32_t ) ),
                  offset + i_array * sizeof( uint32_t )
               );
            }
            break;

         case TUPLE_ARRAY_UINT64_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_uint64
               (
                  (*current).buf,
                  raw_buffer_read_uint64_be( buf, offset + i_array * sizeof( uint64_t ) ),
                  offset + i_array * sizeof( uint64_t )
               );
            }
            break;

         case TUPLE_ARRAY_FLOAT32_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_float32
               (
                  (*current).buf,
                  raw_buffer_read_float32_be( buf, offset + i_array * sizeof( float32_t ) ),
                  offset + i_array * sizeof( float32_t )
               );
            }
            break;

         case TUPLE_ARRAY_FLOAT64_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               raw_buffer_put_float64
               (
                  (*current).buf,
                  raw_buffer_read_float64_be( buf, offset + i_array * sizeof( float64_t ) ),
                  offset + i_array * sizeof( float64_t )
               );
            }
            break;

         case TUPLE_ARRAY_STRING_TYPE:
            for ( i_array = 0; i_array < count; i_array++ )
            {
               s = raw_buffer_read_cstring( buf, offset + i_array * length, length );
               raw_buffer_put_cstring
               (
                  (*current).buf,
                  s,
                  offset + i_array * length
               );
               free( s );
            }

            break;

      }
   }

   raw_buffer_dispose( &buf );

   INVARIANT( current );

   return;
}

/* End of file */
