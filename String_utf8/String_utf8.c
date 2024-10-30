/**
 @file String_utf8.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Character String_utf8s (non-unicode)"

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

 Function definitions for the opaque string_utf8_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include "String_utf8.h"
#include "utf8rewind.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

#define STRING_MIN_SIZE 4
#define STRING_UTF8_CHAR_MAX_SIZE 8
#define STRING_UTF8_ASCII_MASK 0x80

#define UTF16_NUM_BYTES 2
#define UTF32_NUM_BYTES 4
#define WCHAR_NUM_BYTES sizeof( wchar_t )

#define HASH_PRIME_NUMBER 8388593U

/**
   get_hash

   get the hash code for a character string

   @param s the cstring to get the hash of
   @param count the length of the string
   @return the hash value
*/
static
int32_t
get_hash
(
   char_t *s,
   int32_t count
)
{
   PRECONDITION( "s not null", s != NULL );
   PRECONDITION( "count ok", count >= 0 );

   uint32_t result = 0;   // returned hash value
   int32_t i = 0;             // loop variable

   // loop to compute the hash
   for( i = 0; i < count; i++ )
   {
      result = ( ( result % HASH_PRIME_NUMBER ) << 8 ) + ( uint32_t ) s[i];
   }

   // return result
   return ( int32_t ) result;
}

/**
   string structure
*/

struct string_utf8_struct
{
   int32_t _type;

   char *area;
   int32_t count;
   int32_t count_valid;
   int32_t byte_count;
   int32_t capacity;
   int32_t hash_code;
   int32_t hash_code_valid;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   get_count

   get the number of utf8 characters in a character string

   @param s the string_utf8_t
   @return the count of characters
*/

static
int32_t
get_count( string_utf8_t *s )
{
   int32_t result = utf8len( (*s).area );
   return result;
}

/**
   set_count

   get the number of utf8 characters in a string_utf8_t and
   set the count and count_valid fields in the string_utf8_t structure

   @param s the string_utf8_t
*/

static
void
set_count( string_utf8_t *s )
{
   if ( (*s).count_valid == 0 )
   {
      (*s).count = utf8len( (*s).area );
      (*s).count_valid = 1;
   }

   return;
}

/**
   utf16_len

   get the number of utf16 characters in a utf16 character string

   @param s the cstring
   @return the count of characters
*/
static
int32_t
utf16_len( utf16_t *s )
{
   int32_t result = 0;

   while( s[result] != 0 )
   {
      result = result + 1;
   }

   return result;
}

/**
   utf32_len

   get the number of utf32 characters in a utf32 character string

   @param s the cstring
   @return the count of characters

*/
static
int32_t
utf32_len( utf32_t *s )
{
   int32_t result = 0;

   while( s[result] != 0 )
   {
      result = result + 1;
   }

   return result;
}

/**
   wchar_len

   get the number of wchar characters in a character string

   @param s the cstring
   @return the count of characters
*/
static
int32_t
wchar_len( wchar_t *s )
{
   int32_t result = 0;

   while( s[result] != 0 )
   {
      result = result + 1;
   }

   return result;
}

/**
   utf8_to_utf16

   convert a utf8 character (may be multiple bytes) to a utf16 character

   @param c the input character(s)
   @return the converted character
*/
static
utf16_t
utf8_to_utf16( char_t *c )
{
   int32_t n_c = 0;
   int32_t errors = 0;
   utf16_t s16[2] = {0};

   n_c = strlen( c );

   utf8toutf16( c, n_c, s16, 2 * UTF16_NUM_BYTES, &errors );
   CHECK( "utf conversion ok", errors == 0 );

   return s16[0];
}

/**
   utf8_to_utf32

   convert a utf8 character to a utf32 character

   @param c the input character
   @return the converted character
*/
static
utf32_t
utf8_to_utf32( char_t *c )
{
   int32_t n_c = 0;
   int32_t errors = 0;
   utf32_t s32[2] = {0};

   n_c = strlen( c );

   utf8toutf32( c, n_c, s32, 2 * UTF32_NUM_BYTES, &errors );
   CHECK( "utf conversion ok", errors == 0 );

   return s32[0];
}

/**
   utf8_to_wchar

   convert a utf8 character to a wchar character

   @param c the input character
   @return the converted character
*/
static
wchar_t
utf8_to_wchar( char_t *c )
{
   int32_t n_c = 0;
   int32_t errors = 0;
   wchar_t sw[2] = {0};

   n_c = strlen( c );

   utf8towide( c, n_c, sw, 2 * WCHAR_NUM_BYTES, &errors );
   CHECK( "utf conversion ok", errors == 0 );

   return sw[0];
}

/**
   utf16_to_utf8

   convert a utf16 character to a utf16 character

   @param c the input character
   @return the converted character
*/
static
char_t *
utf16_to_utf8( utf16_t c )
{
   char_t *result = NULL;
   int32_t errors = 0;
   utf16_t s16[2] = {0};

   s16[0] = c;

   result = ( char_t * ) calloc( STRING_UTF8_CHAR_MAX_SIZE, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   utf16toutf8( s16, 2 * UTF16_NUM_BYTES, result, STRING_UTF8_CHAR_MAX_SIZE, &errors );
   CHECK( "utf conversion ok", errors == 0 );

   return result;
}

/**
   utf32_to_utf8

   convert a utf32 character to a utf16 character

   @param c the input character
   @return the converted character
*/
static
char_t *
utf32_to_utf8( utf32_t c )
{
   char_t *result = NULL;
   int32_t errors = 0;
   utf32_t s32[2] = {0};

   s32[0] = c;

   result = ( char_t * ) calloc( STRING_UTF8_CHAR_MAX_SIZE, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   utf32toutf8( s32, 2 * UTF32_NUM_BYTES, result, STRING_UTF8_CHAR_MAX_SIZE, &errors );
   CHECK( "utf conversion ok", errors == 0 );

   return result;
}

/**
   wchar_to_utf8

   convert a wchar character to a utf16 character

   @param c the input character
   @return the converted character
*/
static
char_t *
wchar_to_utf8( wchar_t c )
{
   char_t *result = NULL;
   int32_t errors = 0;
   wchar_t sw[2] = {0};

   sw[0] = c;

   result = ( char_t * ) calloc( STRING_UTF8_CHAR_MAX_SIZE, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   widetoutf8( sw, 2 * WCHAR_NUM_BYTES, result, STRING_UTF8_CHAR_MAX_SIZE, &errors );
   CHECK( "utf conversion ok", errors == 0 );

   return result;
}

#if INVARIANT_CONDITIONAL != 0

static
int32_t
area_not_null( string_utf8_t *p )
{
   int32_t result = 1;

   result = ( (*p).area != NULL );

   return result;
}

static
int32_t
nonnegative_count( string_utf8_t *p )
{
   int32_t result = 1;

   if ( (*p).count_valid == 1 )
   {
      result = ( (*p).count >= 0 );
   }

   return result;
}

static
int32_t
valid_count( string_utf8_t *p )
{
   int32_t result = 1;

   if ( (*p).count_valid == 1 )
   {
      result = ( (*p).count <= strlen( (*p).area ) );
   }
   else
   {
      result = ( get_count( p ) <= strlen( (*p).area ) );
   }

   return result;
}

static
int32_t
valid_byte_count( string_utf8_t *p )
{
   int32_t result = 1;

   result = ( (*p).byte_count == strlen( (*p).area ) );

   return result;
}

static
int32_t
capacity_ok( string_utf8_t *p )
{
   int32_t result = 1;

   result = ( (*p).capacity > get_count( p ) ) && ( (*p).capacity > strlen( (*p).area ) );

   return result;
}

static
int32_t
hash_ok( string_utf8_t *p )
{
   int32_t result = 1;

   if ( (*p).hash_code_valid == 1 )
   {
      result = ( (*p).hash_code == get_hash( (*p).area, (*p).byte_count ) );
   }

   return result;
}

static
void invariant( string_utf8_t *p )
{
   assert( ( ( void ) "area not null", area_not_null( p ) ) );
   assert( ( ( void ) "nonnegative count", nonnegative_count( p ) ) );
   assert( ( ( void ) "valid count", valid_count( p ) ) );
   assert( ( ( void ) "valid byte count", valid_byte_count( p ) ) );
   assert( ( ( void ) "capacity ok", capacity_ok( p ) ) );
   assert( ( ( void ) "hash code ok", hash_ok( p ) ) );
   return;
}

#endif

/**
   s_copy

   make a copy of a string_utf8_t

   @param current the string_utf8_t to copy
   @return the copy
*/

static
string_utf8_t *
s_copy( string_utf8_t *current )
{
   string_utf8_t *result = string_utf8_make_n( (*current).byte_count + 1 );
   strcpy( (*result).area, (*current).area );
   (*result).count = (*current).count;
   (*result).count_valid = (*current).count_valid;
   (*result).byte_count = (*current).byte_count;
   (*result).capacity = (*current).byte_count + 1;
   (*result).hash_code_valid = (*current).hash_code_valid;
   (*result).hash_code = (*current).hash_code;

   return result;
}

/**
   string_utf8_make
*/

string_utf8_t *
string_utf8_make( void )
{
   // allocate string struct
   string_utf8_t *result = ( string_utf8_t * ) calloc( 1, sizeof( string_utf8_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = STRING_UTF8_TYPE;

   // allocate area
   (*result).area = ( char * ) calloc( STRING_MIN_SIZE, sizeof( char_t ) );
   CHECK( "(*result).area allocated correctly", (*result).area != NULL );

   // set count
   (*result).count = 0;

   // set count_valid
   (*result).count_valid = 0;

   // set byte count
   (*result).byte_count = 0;

   // set capacity
   (*result).capacity = STRING_MIN_SIZE;

   // set hash_code
   (*result).hash_code = 0;

   // set hash_code_valid
   (*result).hash_code_valid = 0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   string_utf8_make_n
*/

string_utf8_t *
string_utf8_make_n( int32_t capacity )
{
   PRECONDITION( "capacity ok", capacity > 0 );

   int32_t real_capacity = STRING_MIN_SIZE;

   // allocate string struct
   string_utf8_t *result = ( string_utf8_t * ) calloc( 1, sizeof( string_utf8_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = STRING_UTF8_TYPE;

   if ( capacity > STRING_MIN_SIZE )
   {
      real_capacity = capacity;
   }

   // allocate area
   (*result).area = ( char * ) calloc( real_capacity, sizeof( char_t ) );
   CHECK( "(*result).area allocated correctly", (*result).area != NULL );

   // set count
   (*result).count = 0;

   // set count valid
   (*result).count_valid = 0;

   // set byte count
   (*result).byte_count = 0;

   // set capacity
   (*result).capacity = real_capacity;

   // set hash_code
   (*result).hash_code = 0;

   // set hash_code_valid
   (*result).hash_code_valid = 0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "capacity set", (*result).capacity == real_capacity );

   return result;
}

/**
   string_utf8_make_from
*/

string_utf8_t *
string_utf8_make_from( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );

   // get copy of input
   LOCK( (*current).mutex );

   // allocate string struct
   string_utf8_t * result = ( string_utf8_t * ) calloc( 1, sizeof( string_utf8_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = STRING_UTF8_TYPE;

   // set area
   (*result).area = ( char * ) calloc( (*current).capacity, sizeof( char_t ) );
   CHECK( "(*result).area allocated correctly", (*result).area != NULL );

   strncpy( (*result).area, (*current).area, (*current).byte_count );

   // set count
   (*result).count = (*current).count;

   // set count valid
   (*result).count_valid = (*current).count_valid;

   // set byte count
   (*result).byte_count = (*current).byte_count;

   // set capacity
   (*result).capacity = (*current).capacity;

   // set hash_code
   (*result).hash_code = (*current).hash_code;

   // set hash_code_valid
   (*result).hash_code_valid = (*current).hash_code_valid;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // dispose of copy
   UNLOCK( (*current).mutex );

   INVARIANT( result );
   POSTCONDITION( "size set", (*result).byte_count == (*current).byte_count );
   POSTCONDITION( "area set", strcmp( (*result).area, (*current).area ) == 0 );

   return result;
}

/**
   string_utf8_make_from_cstring
*/

string_utf8_t *
string_utf8_make_from_cstring( char *str )
{
   PRECONDITION( "str not null", str != NULL );

   int32_t real_capacity = STRING_MIN_SIZE;

   // allocate string struct
   string_utf8_t *result = ( string_utf8_t * ) calloc( 1, sizeof( string_utf8_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = STRING_UTF8_TYPE;

   int32_t n = strlen( str );

   if ( n < STRING_MIN_SIZE )
   {
      real_capacity = STRING_MIN_SIZE;
   }
   else if ( n >= STRING_MIN_SIZE )
   {
      real_capacity = n + 1;
   }

   // allocate area
   (*result).area = ( char_t * ) calloc( real_capacity, sizeof( char_t ) );
   CHECK( "(*result).area allocated correctly", (*result).area != NULL );

   strcpy( (*result).area, str );

   // set count
   (*result).count = 0;

   // set count valid
   (*result).count_valid = 0;

   // set byte count
   (*result).byte_count = n;

   // set capacity
   (*result).capacity = real_capacity;

   // set hash_code
   (*result).hash_code = 0;

   // set hash_code_valid
   (*result).hash_code_valid = 0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "size set", (*result).byte_count == strlen( str ) );
   POSTCONDITION( "area set", strcmp( (*result).area, str ) == 0 );

   return result;
}

/**
   string_utf8_make_from_utf16
*/

string_utf8_t *
string_utf8_make_from_utf16( utf16_t *str )
{
   PRECONDITION( "str not null", str != NULL );

   int32_t capacity = 0;
   int32_t real_capacity = STRING_MIN_SIZE;
   int32_t count = 0;
   int32_t errors = 0;

   // get length of str
   count = utf16_len( str );

   // get size of converted UTF-8 string
   capacity = utf16toutf8( str, count, NULL, 0, &errors );

   if ( capacity >= real_capacity )
   {
      real_capacity = capacity + 1;
   }

   // allocate string struct
   string_utf8_t *result = ( string_utf8_t * ) calloc( 1, sizeof( string_utf8_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = STRING_UTF8_TYPE;

   // allocate area
   (*result).area = ( char * ) calloc( real_capacity, sizeof( char_t ) );
   CHECK( "(*result).area allocated correctly", (*result).area != NULL );

   // put converted UTF-8 string into area
   utf16toutf8( str, count, (*result).area, real_capacity, &errors );

   // set count
   (*result).count = 0;

   // set count valid
   (*result).count_valid = 0;

   // set byte count
   (*result).byte_count = strlen( (*result).area );

   // set capacity
   (*result).capacity = real_capacity;

   // set hash_code
   (*result).hash_code = 0;

   // set hash_code_valid
   (*result).hash_code_valid = 0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "size set", (*result).byte_count == strlen( (*result).area ) );
   POSTCONDITION( "area set", (*result).area != NULL );

   return result;
}

/**
   string_utf8_make_from_utf32
*/

string_utf8_t *
string_utf8_make_from_utf32( utf32_t *str )
{
   PRECONDITION( "str not null", str != NULL );

   int32_t capacity = 0;
   int32_t real_capacity = STRING_MIN_SIZE;
   int32_t count = 0;
   int32_t errors = 0;

   // get length of str
   count = utf32_len( str );

   // get size of converted UTF-8 string
   capacity = utf32toutf8( str, count, NULL, 0, &errors );

   if ( capacity >= real_capacity )
   {
      real_capacity = capacity + 1;
   }

   // allocate string struct
   string_utf8_t *result = ( string_utf8_t * ) calloc( 1, sizeof( string_utf8_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = STRING_UTF8_TYPE;

   // allocate area
   (*result).area = ( char * ) calloc( real_capacity, sizeof( char_t ) );
   CHECK( "(*result).area allocated correctly", (*result).area != NULL );

   // put converted UTF-8 string into area
   utf32toutf8( str, count, (*result).area, real_capacity, &errors );

   // set count
   (*result).count = 0;

   // set count valid
   (*result).count_valid = 0;

   // set byte count
   (*result).byte_count = strlen( (*result).area );

   // set capacity
   (*result).capacity = real_capacity;

   // set hash_code
   (*result).hash_code = 0;

   // set hash_code_valid
   (*result).hash_code_valid = 0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "size set", (*result).byte_count == strlen( (*result).area ) );
   POSTCONDITION( "area set", (*result).area != NULL );

   return result;
}

/**
   string_utf8_make_from_wchar
*/

string_utf8_t *
string_utf8_make_from_wchar( wchar_t *str )
{
   PRECONDITION( "str not null", str != NULL );

   int32_t capacity = 0;
   int32_t real_capacity = STRING_MIN_SIZE;
   int32_t count = 0;
   int32_t errors = 0;

   // get length of str
   count = wchar_len( str );

   // get size of converted UTF-8 string
   capacity = widetoutf8( str, count, NULL, 0, &errors );

   if ( capacity >= real_capacity )
   {
      real_capacity = capacity + 1;
   }

   // allocate string struct
   string_utf8_t *result = ( string_utf8_t * ) calloc( 1, sizeof( string_utf8_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = STRING_UTF8_TYPE;

   // allocate area
   (*result).area = ( char * ) calloc( real_capacity, sizeof( char_t ) );
   CHECK( "(*result).area allocated correctly", (*result).area != NULL );

   // put converted UTF-8 string into area
   widetoutf8( str, count, (*result).area, real_capacity, &errors );

   // set count
   (*result).count = 0;

   // set count valid
   (*result).count_valid = 0;

   // set byte count
   (*result).byte_count = strlen( (*result).area );

   // set capacity
   (*result).capacity = real_capacity;

   // set hash_code
   (*result).hash_code = 0;

   // set hash_code_valid
   (*result).hash_code_valid = 0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );
   POSTCONDITION( "size set", (*result).byte_count == strlen( (*result).area ) );
   POSTCONDITION( "area set", (*result).area != NULL );

   return result;
}


/**
   string_utf8_dispose
*/

void
string_utf8_dispose( string_utf8_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == STRING_UTF8_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete string struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}


/**
   string_utf8_deep_dispose
*/

void
string_utf8_deep_dispose( string_utf8_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == STRING_UTF8_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   // delete string items
   free( (**current).area );

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   // delete string struct
   free(*current);

   // set to NULL
   *current = NULL;

   return;
}

/**
   string_utf8_item
*/

char_t *
string_utf8_item( string_utf8_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < get_count( current ) ) ) );
   INVARIANT( current );

   char_t *result = calloc( 5, sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   const char_t *cp = NULL;
   const char_t *cp1 = NULL;

   cp = utf8seek( (*current).area, (*current).byte_count, (*current).area, index, SEEK_SET );
   cp1 = utf8seek( cp, (*current).byte_count, (*current).area, 1, SEEK_CUR );
   memcpy( result, cp, cp1 - cp );

   CHECK( "UTF conversion ok", ( strlen( result ) > 0 ) && ( strlen( result ) <= 4 ) );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_item_ascii
*/

char_t
string_utf8_item_ascii( string_utf8_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < get_count( current ) ) ) );
   INVARIANT( current );

   char_t result = 0;

   const char_t *cp = NULL;

   cp = utf8seek( (*current).area, (*current).byte_count, (*current).area, index, SEEK_SET );
   CHECK( "UTF conversion ok", cp != NULL );

   result = *cp;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   POSTCONDITION( "result is ascii", ( result & STRING_UTF8_ASCII_MASK ) == 0 );

   return result;
}

/**
   string_utf8_item_utf16
*/

utf16_t
string_utf8_item_utf16( string_utf8_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < get_count( current ) ) ) );
   INVARIANT( current );

   utf16_t result = 0;
   const char_t *cp = NULL;
   const char_t *cp1 = NULL;
   int32_t i = 0;
   char_t str[STRING_UTF8_CHAR_MAX_SIZE] = {0};

   cp = utf8seek( (*current).area, (*current).byte_count, (*current).area, index, SEEK_SET );
   cp1 = ( char_t * ) utf8seek( cp, (*current).byte_count, (*current).area, 1, SEEK_CUR );

   while ( cp != cp1 )
   {
      str[i] = *cp;
      cp++;
   }

   result = utf8_to_utf16( str );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_item_utf32
*/

utf32_t
string_utf8_item_utf32( string_utf8_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < get_count( current ) ) ) );
   INVARIANT( current );

   utf32_t result = 0;
   const char_t *cp = NULL;
   const char_t *cp1 = NULL;
   int32_t i = 0;
   char_t str[STRING_UTF8_CHAR_MAX_SIZE] = {0};

   cp = utf8seek( (*current).area, (*current).byte_count, (*current).area, index, SEEK_SET );
   cp1 = ( char_t * ) utf8seek( cp, (*current).byte_count, (*current).area, 1, SEEK_CUR );

   while ( cp != cp1 )
   {
      str[i] = *cp;
      cp++;
   }

   result = utf8_to_utf32( str );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_item_wchar
*/

wchar_t
string_utf8_item_wchar( string_utf8_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < get_count( current ) ) ) );
   INVARIANT( current );

   utf32_t result = 0;
   const char_t *cp = NULL;
   const char_t *cp1 = NULL;
   int32_t i = 0;
   char_t str[STRING_UTF8_CHAR_MAX_SIZE] = {0};

   cp = utf8seek( (*current).area, (*current).byte_count, (*current).area, index, SEEK_SET );
   cp1 = ( char_t * ) utf8seek( cp, (*current).byte_count, (*current).area, 1, SEEK_CUR );

   while ( cp != cp1 )
   {
      str[i] = *cp;
      cp++;
   }

   result = utf8_to_wchar( str );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_as_cstring
*/

char_t *
string_utf8_as_cstring( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *result = (*current).area;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_as_utf8
*/

char_t *
string_utf8_as_utf8( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *result = calloc( (*current).byte_count + sizeof( char_t ), sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   memcpy( result, (*current).area, (*current).byte_count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );
   POSTCONDITION( "result not null", result != NULL );

   return result;
}

/**
   string_utf8_as_utf16
*/

utf16_t *
string_utf8_as_utf16( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = 0;
   int32_t errors = 0;
   utf16_t *result = NULL;

   // get count in bytes of conversion length
   count = utf8toutf16( (*current).area, (*current).byte_count, NULL, 0, &errors );
   CHECK( "UTF conversion ok", errors == 0 );

   // allocate space for return value
   result = ( utf16_t * ) calloc( count + sizeof( utf16_t ), sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // put utf16 string into result
   count = utf8toutf16( (*current).area, (*current).byte_count, result, count, &errors );
   CHECK( "UTF conversion ok", errors == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );
   POSTCONDITION( "result not null", result != NULL );

   return result;
}

/**
   string_utf8_as_utf32
*/

utf32_t *
string_utf8_as_utf32( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = 0;
   int32_t errors = 0;
   utf32_t *result = NULL;

   // get count in bytes of conversion length
   count = utf8toutf32( (*current).area, (*current).byte_count, NULL, 0, &errors );
   CHECK( "UTF conversion ok", errors == 0 );

   // allocate space for return value
   result = ( utf32_t * ) calloc( count + sizeof( utf32_t ), sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // put utf32 string into result
   count = utf8toutf32( (*current).area, (*current).byte_count, result, count, &errors );
   CHECK( "UTF conversion ok", errors == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );
   POSTCONDITION( "result not null", result != NULL );

   return result;
}

/**
   string_utf8_as_wchar
*/

wchar_t *
string_utf8_as_wchar( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = 0;
   int32_t errors = 0;
   wchar_t *result = NULL;

   // get count in bytes of conversion length
   count = utf8towide( (*current).area, (*current).byte_count, NULL, 0, &errors );
   CHECK( "UTF conversion ok", errors == 0 );

   // allocate space for return value
   result = ( wchar_t * ) calloc( count + sizeof( wchar_t ), sizeof( char_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // put wchar_t string into result
   count = utf8towide( (*current).area, (*current).byte_count, result, count, &errors );
   CHECK( "UTF conversion ok", errors == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );
   POSTCONDITION( "result not null", result != NULL );

   return result;
}

/**
   string_utf8_count
*/

int32_t
string_utf8_count( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( (*current).count_valid == 1 )
   {
      result = (*current).count;
   }
   else
   {
      set_count( current );
      result = (*current).count;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_byte_count
*/

int32_t
string_utf8_byte_count( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result =  (*current).byte_count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_capacity
*/

int32_t
string_utf8_capacity( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result =  (*current).capacity;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_is_empty
*/

int32_t
string_utf8_is_empty( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).byte_count == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_valid_index
*/

int32_t
string_utf8_valid_index( string_utf8_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   set_count( current );
   int32_t result = ( index >= 0 ) && ( index < (*current).count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_has
*/

int32_t
string_utf8_has( string_utf8_t *current, char_t *c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "search character not null", c != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   char_t *cp = NULL;

   // search string for character c, return true if found
   cp = strstr( (*current).area, c );
   if ( cp != NULL )
   {
      result = 1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_has_ascii
*/

int32_t
string_utf8_has_ascii( string_utf8_t *current, char_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "c is ascii", ( c & STRING_UTF8_ASCII_MASK ) == 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   char_t *cp = NULL;
   char_t str[STRING_UTF8_CHAR_MAX_SIZE] = {0};
   str[0] = c;

   // search string for character c, return true if found
   cp = strstr( (*current).area, str );
   if ( cp != NULL )
   {
      result = 1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_has_utf16
*/

int32_t
string_utf8_has_utf16( string_utf8_t *current, utf16_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   char_t *cp = NULL;
   char_t utf8[STRING_UTF8_CHAR_MAX_SIZE] = {0};
   utf16_t s16[2] = {0};
   int32_t errors = 0;

   s16[0] = c;

   // convert utf16 to utf8
   utf16toutf8( s16, 2 * UTF16_NUM_BYTES, utf8, STRING_UTF8_CHAR_MAX_SIZE, &errors );

   CHECK( "utf conversion error", errors == 0 );

   // search string for UTF-8 version of character c, return true if found
   cp = strstr( (*current).area, utf8 );
   if ( cp != NULL )
   {
      result = 1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_has_utf32
*/

int32_t
string_utf8_has_utf32( string_utf8_t *current, utf32_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   char_t *cp = NULL;
   char_t utf8[STRING_UTF8_CHAR_MAX_SIZE] = {0};
   utf32_t s32[2] = {0};
   int32_t errors = 0;

   s32[0] = c;

   // convert utf132to utf8
   utf32toutf8( s32, 2 * UTF32_NUM_BYTES, utf8, STRING_UTF8_CHAR_MAX_SIZE, &errors );
   CHECK( "utf conversion error", errors == 0 );

   // search string for UTF-8 version of character c, return true if found
   cp = strstr( (*current).area, utf8 );
   if ( cp != NULL )
   {
      result = 1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_has_wchar
*/

int32_t
string_utf8_has_wchar( string_utf8_t *current, wchar_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   char_t *cp = NULL;
   char_t utf8[STRING_UTF8_CHAR_MAX_SIZE] = {0};
   wchar_t sw[2] = {0};
   int32_t errors = 0;

   sw[0] = c;

   // convert wchar to utf8
   widetoutf8( sw, 2 * WCHAR_NUM_BYTES, utf8, STRING_UTF8_CHAR_MAX_SIZE, &errors );

   CHECK( "utf conversion error", errors == 0 );

   // search string for UTF-8 version of character c, return true if found
   cp = strstr( (*current).area, utf8 );
   if ( cp != NULL )
   {
      result = 1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_is_int32
*/

int32_t
string_utf8_is_int32( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t args_parsed = 0;
   int32_t value = 0;
   args_parsed = sscanf( (*current).area, "%d", &value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return ( args_parsed == 1 );
}

/**
   string_utf8_is_float64
*/

int32_t
string_utf8_is_float64( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t args_parsed = 0;
   float64_t value = 0;
   args_parsed = sscanf( (*current).area, "%lf", &value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return ( args_parsed == 1 );
}

/**
   string_utf8_hash_code
*/

int32_t
string_utf8_hash_code( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   if ( (*current).hash_code_valid == 0 )
   {
      (*current).hash_code = get_hash( (*current).area, (*current).byte_count );
      (*current).hash_code_valid = 1;
   }

   int32_t result = (*current).hash_code;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_is_equal
*/

int32_t
string_utf8_is_equal( string_utf8_t *s1, string_utf8_t *s2 )
{
   PRECONDITION( "s1 not null", s1 != NULL );
   PRECONDITION( "s1 type OK", (*s1)._type == STRING_UTF8_TYPE );
   PRECONDITION( "s2 not null", s2 != NULL );
   PRECONDITION( "s2 type OK", (*s2)._type == STRING_UTF8_TYPE );
   LOCK( (*s1).mutex );
   INVARIANT( s1 );

   // lock s2
   LOCK( (*s2).mutex );

   int32_t result = 0;
   result = strcmp( (*s1).area, (*s2).area );

   // unlock s2
   UNLOCK( (*s2).mutex );

   INVARIANT( s1 );
   UNLOCK( (*s1).mutex );

   return ( result == 0 );
}

/**
   string_utf8_is_equal_cstring
*/

int32_t
string_utf8_is_equal_cstring( string_utf8_t *s1, char_t *s2 )
{
   PRECONDITION( "s1 not null", s1 != NULL );
   PRECONDITION( "s1 type OK", (*s1)._type == STRING_UTF8_TYPE );
   PRECONDITION( "s2 not null", s2 != NULL );
   LOCK( (*s1).mutex );
   INVARIANT( s1 );

   int32_t result = 0;
   result = strcmp( (*s1).area, s2 );

   INVARIANT( s1 );
   UNLOCK( (*s1).mutex );

   return ( result == 0 );
}


/**
   string_utf8_is_less_than
*/

int32_t
string_utf8_is_less_than( string_utf8_t *s1, string_utf8_t *s2 )
{
   PRECONDITION( "s1 not null", s1 != NULL );
   PRECONDITION( "s1 type OK", (*s1)._type == STRING_UTF8_TYPE );
   PRECONDITION( "s2 not null", s2 != NULL );
   PRECONDITION( "s2 type OK", (*s2)._type == STRING_UTF8_TYPE );
   LOCK( (*s1).mutex );
   INVARIANT( s1 );

   // lock s2
   LOCK( (*s2).mutex );

   int32_t result = 0;
   result = strcmp( (*s1).area, (*s2).area );

   // unlock s2
   UNLOCK( (*s2).mutex );

   INVARIANT( s1 );
   UNLOCK( (*s1).mutex );

   return ( result < 0 );
}

/**
   string_utf8_is_less_than_cstring
*/

int32_t
string_utf8_is_less_than_cstring( string_utf8_t *s1, char_t *s2 )
{
   PRECONDITION( "s1 not null", s1 != NULL );
   PRECONDITION( "s1 type OK", (*s1)._type == STRING_UTF8_TYPE );
   PRECONDITION( "s2 not null", s2 != NULL );
   LOCK( (*s1).mutex );
   INVARIANT( s1 );

   int32_t result = 0;
   result = strcmp( (*s1).area, s2 );

   INVARIANT( s1 );
   UNLOCK( (*s1).mutex );

   return ( result < 0 );
}


/**
   string_utf8_is_greater_than
*/

int32_t
string_utf8_is_greater_than( string_utf8_t *s1, string_utf8_t *s2 )
{
   PRECONDITION( "s1 not null", s1 != NULL );
   PRECONDITION( "s1 type OK", (*s1)._type == STRING_UTF8_TYPE );
   PRECONDITION( "s2 not null", s2 != NULL );
   PRECONDITION( "s2 type OK", (*s2)._type == STRING_UTF8_TYPE );
   LOCK( (*s1).mutex );
   INVARIANT( s1 );

   // lock s2
   LOCK( (*s2).mutex );

   int32_t result = 0;
   result = strcmp( (*s1).area, (*s2).area );

   // unlock s2
   UNLOCK( (*s2).mutex );

   INVARIANT( s1 );
   UNLOCK( (*s1).mutex );

   return ( result > 0 );
}

/**
   string_utf8_is_greater_than_cstring
*/

int32_t
string_utf8_is_greater_than_cstring( string_utf8_t *s1, char_t *s2 )
{
   PRECONDITION( "s1 not null", s1 != NULL );
   PRECONDITION( "s1 type OK", (*s1)._type == STRING_UTF8_TYPE );
   PRECONDITION( "s2 not null", s2 != NULL );
   LOCK( (*s1).mutex );
   INVARIANT( s1 );

   int32_t result = 0;
   result = strcmp( (*s1).area, s2 );

   INVARIANT( s1 );
   UNLOCK( (*s1).mutex );

   return ( result > 0 );
}


/**
   string_utf8_has_substring
*/

int32_t
string_utf8_has_substring( string_utf8_t *current, string_utf8_t *substring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // unlock substring
   LOCK( (*substring).mutex );

   char_t *cp = NULL;

   cp = strstr( (*current).area, (*substring).area );

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return ( cp != NULL );
}

/**
   string_utf8_has_substring_cstring
*/

int32_t
string_utf8_has_substring_cstring( string_utf8_t *current, char_t *substring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *cp = NULL;

   cp = strstr( (*current).area, substring );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return ( cp != NULL );
}

/**
   string_utf8_starts_with
*/

int32_t
string_utf8_starts_with( string_utf8_t *current, string_utf8_t *substring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // unlock substring
   LOCK( (*substring).mutex );

   char_t *cp = NULL;

   cp = strstr( (*current).area, (*substring).area );

   int32_t result = ( cp == (*current).area );

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_starts_with_cstring
*/

int32_t
string_utf8_starts_with_cstring( string_utf8_t *current, char_t *substring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *cp = NULL;

   cp = strstr( (*current).area, substring );

   int32_t result = ( cp == (*current).area );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_ends_with
*/

int32_t
string_utf8_ends_with( string_utf8_t *current, string_utf8_t *substring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // unlock substring
   LOCK( (*substring).mutex );

   int32_t result = 0;
   const char_t *cp = NULL;
   const char_t *cp1 = NULL;

   set_count( current );
   set_count( substring );

   if ( (*substring).count <= (*current).count )
   {
      cp = utf8seek( (*current).area, (*current).byte_count, (*current).area, ( (*current).count - (*substring).count ), SEEK_SET );
      cp1 = strstr( cp, (*substring).area );
      result = ( cp == cp1 );
   }

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

int32_t
string_utf8_ends_with_cstring( string_utf8_t *current, char_t *substring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   const char_t *cp = NULL;
   const char_t *cp1 = NULL;

   set_count( current );
   int32_t substring_length = utf8len( substring );

   cp = utf8seek( (*current).area, (*current).byte_count, (*current).area, ( (*current).count - substring_length ), SEEK_SET );


   if ( substring_length <= (*current).count )
   {
      cp = utf8seek( (*current).area, (*current).byte_count, (*current).area, ( (*current).count - substring_length ), SEEK_SET );
      cp1 = strstr( cp, substring );
      result = ( cp == cp1 );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_substring_index_in_bounds
*/

int32_t
string_utf8_substring_index_in_bounds
(
   string_utf8_t *current,
   string_utf8_t *substring,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_UTF8_TYPE );
   PRECONDITION( "start index ok", ( ( start_index >= 0 ) && ( start_index < get_count( current ) ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= start_index ) && ( end_index < get_count( current ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock substring
   LOCK( (*substring).mutex );

   const char_t *cp = NULL;
   char_t *cp1 = NULL;
   char_t c = 0;
   int32_t result = 0;

   set_count( current );
   set_count( substring );

   // get pointer to start_index
   cp = utf8seek( (*current).area, (*current).byte_count, (*current).area, start_index, SEEK_SET );

   // see if substring can be found at pointer or after pointer
   cp1 = strstr( cp, (*substring).area );

   // pointer found, get its utf8 index
   if ( cp1 != NULL )
   {
      // set character at pointer to zero, get utf8 length of string == index at pointer
      c = *cp1;
      *cp1 = 0;
      result = utf8len( (*current).area );
      *cp1 = c;
   }

   if ( ( cp1 == NULL ) || ( result < start_index ) || ( result > end_index ) )
   {
      result = -1;
   }

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_substring_index_in_bounds_cstring
*/

int32_t
string_utf8_substring_index_in_bounds_cstring
(
   string_utf8_t *current,
   char_t *substring,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "start index ok", ( ( start_index >= 0 ) && ( start_index < get_count( current ) ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < get_count( current ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   const char_t *cp = NULL;
   char_t *cp1 = NULL;
   char_t c = 0;
   int32_t result = 0;

   set_count( current );

   // get pointer to start_index
   cp = utf8seek( (*current).area, (*current).byte_count, (*current).area, start_index, SEEK_SET );

   // see if substring can be found at pointer or after pointer
   cp1 = strstr( cp, substring );

   // pointer found, get its utf8 index
   if ( cp1 != NULL )
   {
      // set character at pointer to zero, get utf8 length of string == index at pointer
      c = *cp1;
      *cp1 = 0;
      result = utf8len( (*current).area );
      *cp1 = c;
   }

   if ( ( cp1 == NULL ) || ( result < start_index ) || ( result > end_index ) )
   {
      result = -1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}


/**
   string_utf8_substring_index
*/

int32_t
string_utf8_substring_index
(
   string_utf8_t *current,
   string_utf8_t *substring
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock substring
   LOCK( (*substring).mutex );

   char_t *cp = NULL;
   char_t c = 0;
   int32_t result = 0;

   set_count( current );
   set_count( substring );

   cp = strstr( (*current).area, (*substring).area );

   if ( cp == NULL )
   {
      result = -1;
   }
   else
   {
      // set character at pointer to zero, get utf8 length of string == index at pointer
      c = *cp;
      *cp = 0;
      result = utf8len( (*current).area );
      *cp = c;
   }

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_substring_index_cstring
*/

int32_t
string_utf8_substring_index_cstring
(
   string_utf8_t *current,
   char_t *substring
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring not null", current != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *cp = NULL;
   char_t c = 0;
   int32_t result = 0;

   set_count( current );

   cp = strstr( (*current).area, substring );

   if ( cp == NULL )
   {
      result = -1;
   }
   else
   {
      // set character at pointer to zero, get utf8 length of string == index at pointer
      c = *cp;
      *cp = 0;
      result = utf8len( (*current).area );
      *cp = c;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

#define DEFAULT_SPLIT_RETURN_ARRAY_SIZE 8

/**
   find_next_separator
*/
static
char *
find_next_separator( char_t *str, char **separators, int32_t n_separators, int32_t *separator_count )
{
   PRECONDITION( "str not null", str != NULL );
   PRECONDITION( "separators not null", separators != NULL );
   PRECONDITION( "n_separators ok", n_separators > 0 );
   PRECONDITION( "separator count ok", separator_count != NULL );

   char_t *result = NULL;
   char_t *cp1 = NULL;
   int32_t i = 0;

   // find next separator
   result = strstr( str, separators[0] );

   for( i = 1; i < n_separators; i++ )
   {
      cp1 = strstr( str, separators[i] );

      if ( cp1 != NULL )
      {
         if ( result == NULL )
         {
            result = cp1;
         }
         else if ( cp1 < result )
         {
            result = cp1;
         }
      }
   }

   return result;
}

/**
   string_utf8_split
*/

string_utf8_t **
string_utf8_split
(
   string_utf8_t *current,
   string_utf8_t *separators,
   int32_t *count
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "separators not null", separators != NULL );
   PRECONDITION( "separators type OK", (*separators)._type == STRING_UTF8_TYPE );
   PRECONDITION( "separators not empty", (*separators).byte_count > 0 );
   PRECONDITION( "count ok", count != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock separators
   LOCK( (*separators).mutex );

   char_t *scopy = NULL;
   char_t *cp = NULL;
   const char_t *cp0 = NULL;
   const char_t *cp1 = NULL;
   char_t *cp2 = NULL;
   string_utf8_t **result = NULL;
   int32_t i_result = 0;
   string_utf8_t *s = NULL;
   int32_t size = DEFAULT_SPLIT_RETURN_ARRAY_SIZE;
   int32_t seps_size = DEFAULT_SPLIT_RETURN_ARRAY_SIZE;
   char_t **seps = NULL;
   int32_t n_seps = 0;
   int32_t i = 0;
   int32_t n = 0;
   int32_t flag = 0;

   // allocate array to return
   result = ( string_utf8_t ** ) calloc( size, sizeof( string_utf8_t * ) );
   CHECK( "result allocated correctly", result != NULL );

   // allocate and fill temp string
   scopy = ( char_t * ) calloc( (*current).byte_count + 1, sizeof( char_t ) );
   CHECK( "scopy allocated correctly", scopy != NULL );

   strcpy( scopy, (*current).area );

   // allocate separators array
   seps = ( char_t ** ) calloc( size, sizeof( char_t * ) );
   CHECK( "seps allocated correctly", seps != NULL );

   // allocate and fill separators array

   // get separators
   cp = (*separators).area;
   cp1 = utf8seek( cp, (*separators).byte_count, (*separators).area, 1, SEEK_CUR );
   n = cp1 - cp;
   seps[0] = ( char_t * ) calloc( n + 1, sizeof( char_t ) );
   CHECK( "seps[0] allocated correctly", seps[0] != NULL );

   memcpy( seps[0], cp, n );

   i = 1;
   n_seps = 1;
   while( flag == 0 )
   {
      cp0 = cp1;
      cp1 = utf8seek( cp0, (*separators).byte_count, (*separators).area, 1, SEEK_CUR );

      if ( cp1 > cp0 )
      {
         n = cp1 - cp0;
         if ( i < seps_size - 1 )
         {
            seps[i] = ( char_t * ) calloc( n + 1, sizeof( char_t ) );
            CHECK( "seps[i] allocated correctly", seps[i] != NULL );

            memcpy( seps[i], cp0, n );
            i = i + 1;
            n_seps = n_seps + 1;
         }
         else
         {
            seps = ( char_t ** ) realloc( seps, 2 * seps_size * sizeof( string_utf8_t * ) );
            CHECK( "seps allocated correctly", seps != NULL );

            memset( seps + size, 0, sizeof( string_utf8_t * )*seps_size );
            seps_size = 2 * seps_size;
            seps[i] = ( char_t * ) calloc( n + 1, sizeof( char_t ) );
            CHECK( "seps[i] allocated correctly", seps[i] != NULL );

            memcpy( seps[i], cp0, n );
            i = i + 1;
            n_seps = n_seps + 1;
         }
      }
      else
      {
         flag = 1;
      }
   }

   cp = scopy;
   // loop to find next separator, put found split string into return array,
   while( cp != NULL )
   {
      cp2 = find_next_separator( cp, seps, n_seps, &n );
      if ( cp2 != NULL )
      {
         // zero out separator in scopy
         for ( i = 0; i < n; i++ )
         {
            *cp2 = 0;
            cp2++;
         }
      }

      // first time cp2 is null is when we're at the end of scopy,
      // still need to consume string at cp

      // don't collect empty strings, same behavior as strtok()
      if ( strlen( cp ) > 0 )
      {
         // put found split into result
         s = string_utf8_make_from_cstring( cp );

         // put the string into the return array
         if ( i_result < ( size - 1 ) )
         {
            result[i_result] = s;
            i_result = i_result + 1;
         }
         // resize the array if necessary
         else
         {
            result = ( string_utf8_t ** ) realloc( result, 2 * size * sizeof( string_utf8_t * ) );
            CHECK( "result allocated correctly", result != NULL );

            memset( result + size, 0, sizeof( string_utf8_t * )*size );
            size = 2 * size;
            result[i_result] = s;
            i_result = i_result + 1;
         }
      }

      cp = cp2;
   }

   // deallocate separators array
   for ( i = 0; i < n_seps; i++ )
   {
      free( seps[i] );
   }

   free( seps );

   // deallocate temp string
   free( scopy );

   // unlock separators
   UNLOCK( (*separators).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   // set count
   *count = i_result;

   // return array of split strings
   return result;
}


/**
   string_utf8_split_cstring
*/

string_utf8_t **
string_utf8_split_cstring
(
   string_utf8_t *current,
   char_t *separators,
   int32_t *count
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "separators not null", separators != NULL );
   PRECONDITION( "separators not empty", strlen( separators ) > 0 );
   PRECONDITION( "count ok", count != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *scopy = NULL;
   char_t *cp = NULL;
   const char_t *cp0 = NULL;
   const char_t *cp1 = NULL;
   char_t *cp2 = NULL;
   string_utf8_t **result = NULL;
   int32_t i_result = 0;
   string_utf8_t *s = NULL;
   int32_t size = DEFAULT_SPLIT_RETURN_ARRAY_SIZE;
   int32_t seps_size = DEFAULT_SPLIT_RETURN_ARRAY_SIZE;
   char_t **seps = NULL;
   int32_t n_seps = 0;
   int32_t i = 0;
   int32_t n = 0;
   int32_t flag = 0;

   // allocate array to return
   result = ( string_utf8_t ** ) calloc( size, sizeof( string_utf8_t * ) );
   CHECK( "result allocated correctly", result != NULL );

   // allocate and fill temp string
   scopy = ( char_t * ) calloc( (*current).byte_count + 1, sizeof( char_t ) );
   CHECK( "scopy allocated correctly", scopy != NULL );

   strcpy( scopy, (*current).area );

   // allocate separators array
   seps = ( char_t ** ) calloc( size, sizeof( char_t * ) );
   CHECK( "seps allocated correctly", seps != NULL );

   // allocate and fill separators array

   // get separators
   cp0 = separators;
   cp1 = utf8seek( cp0, strlen( separators ), separators, 1, SEEK_CUR );
   n = cp1 - cp0;
   seps[0] = ( char_t * ) calloc( n + 1, sizeof( char_t ) );
   CHECK( "seps[0] allocated correctly", seps[0] != NULL );

   memcpy( seps[0], cp0, n );

   i = 1;
   n_seps = 1;
   while( flag == 0 )
   {
      cp0 = cp1;
      cp1 = utf8seek( cp0, strlen( separators ), separators, 1, SEEK_CUR );

      if ( cp1 > cp0 )
      {
         n = cp1 - cp0;
         if ( i < seps_size - 1 )
         {
            seps[i] = ( char_t * ) calloc( n + 1, sizeof( char_t ) );
            CHECK( "seps[i] allocated correctly", seps[i] != NULL );

            memcpy( seps[i], cp0, n );
            i = i + 1;
            n_seps = n_seps + 1;
         }
         else
         {

            seps = ( char_t ** ) realloc( seps, 2 * seps_size * sizeof( char_t * ) );
            CHECK( "seps allocated correctly", seps != NULL );

            memset( seps + size, 0, sizeof( char_t * )*seps_size );
            seps_size = 2 * seps_size;
            seps[i] = ( char_t * ) calloc( n + 1, sizeof( char_t ) );
            CHECK( "seps[i] allocated correctly", seps[i] != NULL );

            memcpy( seps[i], cp0, n );
            i = i + 1;
            n_seps = n_seps + 1;
         }
      }
      else
      {
         flag = 1;
      }
   }

   cp = scopy;

   // loop to find next separator, put found split string into return array,
   while( cp != NULL )
   {
      cp2 = find_next_separator( cp, seps, n_seps, &n );
      if ( cp2 != NULL )
      {
         // zero out separator in scopy
         for ( i = 0; i < n; i++ )
         {
            *cp2 = 0;
            cp2++;
         }
      }

      // first time cp1 is null is when we're at the end of scopy,
      // still need to consume string at cp

      // don't collect empty strings, same behavior as strtok()
      if ( strlen( cp ) > 0 )
      {

         // put found split into result
         s = string_utf8_make_from_cstring( cp );

         // put the string into the return array
         if ( i_result < ( size - 1 ) )
         {
            result[i_result] = s;
            i_result = i_result + 1;
         }
         // resize the array if necessary
         else
         {
            result = ( string_utf8_t ** ) realloc( result, 2 * size * sizeof( string_utf8_t * ) );
            CHECK( "result allocated correctly", result != NULL );

            memset( result + size, 0, sizeof( string_utf8_t * )*size );
            size = 2 * size;
            result[i_result] = s;
            i_result = i_result + 1;
         }
      }
      cp = cp2;
   }

   // deallocate separators array
   for ( i = 0; i < n_seps; i++ )
   {
      free( seps[i] );
   }

   free( seps );

   // deallocate temp string
   free( scopy );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   // set count
   *count = i_result;

   // return array of split strings
   return result;
}


/**
   string_utf8_as_lower
*/

string_utf8_t *
string_utf8_as_lower( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_utf8_t *result = s_copy( current );
   int32_t errors = 0;
   int32_t n = 0;

   n = utf8tolower( (*current).area, (*current).byte_count, NULL, 1, utf8envlocale(), &errors );
   CHECK( "utf8 conversion error", errors == 0 );

   // make result area large enough
   free( (*result).area );
   (*result).area = ( char_t * ) calloc( n + 1, sizeof( char_t ) );
   CHECK( "(*result).area allocated correctly", (*result).area != NULL );

   (*result).byte_count = n;
   (*result).capacity = n + 1;

   utf8tolower( (*current).area, (*current).byte_count, (*result).area, (*result).capacity, utf8envlocale(), &errors );
   CHECK( "utf8 conversion error", errors == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_as_upper
*/

string_utf8_t *
string_utf8_as_upper( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_utf8_t *result = s_copy( current );
   int32_t errors = 0;
   int32_t n = (*result).count;

   n = utf8toupper( (*current).area, (*current).byte_count, NULL, 1, utf8envlocale(), &errors );
   CHECK( "utf8 conversion error", errors == 0 );

   // make result area large enough
   free( (*result).area );
   (*result).area = ( char_t * ) calloc( n + 1, sizeof( char_t ) );
   CHECK( "(*result).area allocated correctly", (*result).area != NULL );

   (*result).byte_count = n;
   (*result).capacity = n + 1;

   utf8toupper( (*current).area, (*current).byte_count, (*result).area, (*result).capacity, utf8envlocale(), &errors );
   CHECK( "utf8 conversion error", errors == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_as_int32
*/

int32_t
string_utf8_as_int32( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t value = 0;
   sscanf( (*current).area, "%d", &value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   string_utf8_as_float64
*/

float64_t
string_utf8_as_float64( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   float64_t value = 0;
   sscanf( (*current).area, "%lf", &value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   utf8_put
*/
static
void
utf8_put( string_utf8_t *current, char_t *c, int32_t index )
{
   int32_t i = 0;
   int32_t n_char = 0;
   int32_t n_c = 0;
   char_t *cp = NULL;
   const char_t *cp1 = NULL;
   const char_t *cp2 = NULL;

   // size of utf8 character to put
   n_c = strlen( c );

   // pointer to string at index
   cp1 = utf8seek( (*current).area, (*current).byte_count, (*current).area, index, SEEK_SET );
   cp = ( char_t * ) cp1;

   // pointer to next utf8 character
   cp2 = utf8seek( cp1, (*current).byte_count, (*current).area, 1, SEEK_CUR );

   // string count of current utf8 character at index
   n_char = cp2 - cp1;

   // allow "put" into position following last character

   if ( n_char == 0 )
   {
      // we're at the end of the string, append new utf8 character to end

      // increase the string's capacity if needed
      if ( (*current).capacity <= (*current).byte_count + n_c )
      {
         (*current).area = ( char_t * ) realloc( (*current).area, (*current).capacity + n_c );
         CHECK( "(*current).area allocated correctly", (*current).area != NULL );

         memset( (*current).area + (*current).byte_count, 0, (*current).capacity + n_c - (*current).byte_count - 1 );
         (*current).capacity = (*current).capacity + n_c;
         (*current).area[ (*current).capacity - 1] = 0;
      }

      for ( i = 0; i < n_c; i++ )
      {
         (*current).area[ (*current).byte_count + i ] = c[i];
      }
      (*current).hash_code_valid = 0;
      (*current).byte_count = (*current).byte_count + n_c;
      (*current).count_valid = 0;
   }
   else
   {
      // we're at the beginning or in the middle of the string

      // increase the string's capacity if needed
      if ( (*current).capacity <= (*current).byte_count + ( n_c - n_char ) )
      {
         (*current).area = ( char_t * ) realloc( (*current).area, (*current).capacity + n_c - n_char );
         CHECK( "(*current).area allocated correctly", (*current).area != NULL );

         memset( (*current).area + (*current).byte_count, 0, (*current).capacity + ( n_c - n_char ) - (*current).byte_count - 1 );
         (*current).capacity = (*current).capacity + n_c - n_char;
         (*current).area[ (*current).capacity - 1] = 0;
      }

      // move the characters after the location to put, if needed
      if ( n_c != n_char )
      {
         cp1 = utf8seek( (*current).area, (*current).byte_count, (*current).area, index, SEEK_SET );
         cp = ( char_t * ) cp1;
         cp2 = utf8seek( cp1, (*current).byte_count, (*current).area, 1, SEEK_CUR );
         memmove( cp + n_c, cp2, (*current).byte_count - ( cp2 - (*current).area ) );
      }

      // put the utf8 character into the string at cp
      for ( i = 0; i < n_c; i++ )
      {
         *cp = c[i];
         cp++;
      }
      (*current).hash_code_valid = 0;
      (*current).byte_count = (*current).byte_count + n_c - n_char;
      (*current).count_valid = 0;
   }

   return;
}

/**
   string_utf8_put
*/

void
string_utf8_put( string_utf8_t *current, char_t *c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= get_count( current ) ) ) );
   INVARIANT( current );

   utf8_put( current, c, index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_put_ascii
*/

void
string_utf8_put_ascii( string_utf8_t *current, char_t c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "c is ascii", ( c & STRING_UTF8_ASCII_MASK ) == 0 );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= get_count( current ) ) ) );
   INVARIANT( current );

   char_t str[STRING_UTF8_CHAR_MAX_SIZE] = {0};
   str[0] = c;

   utf8_put( current, str, index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_put_utf16
*/

void
string_utf8_put_utf16( string_utf8_t *current, utf16_t c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= get_count( current ) ) ) );
   INVARIANT( current );

   char_t *s = NULL;

   s = utf16_to_utf8( c );

   utf8_put( current, s, index );

   free( s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_put_utf32
*/

void
string_utf8_put_utf32( string_utf8_t *current, utf32_t c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= get_count( current ) ) ) );
   INVARIANT( current );

   char_t *s = NULL;

   s = utf32_to_utf8( c );

   utf8_put( current, s, index );

   free( s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_put_wchar
*/

void
string_utf8_put_wchar( string_utf8_t *current, wchar_t c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= get_count( current ) ) ) );
   INVARIANT( current );

   char_t *s = NULL;

   s = wchar_to_utf8( c );

   utf8_put( current, s, index );

   free( s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   utf8_replace
*/
static
void
utf8_replace
(
   string_utf8_t *current,
   char_t *substring,
   int32_t n_substring,
   int32_t start_index,
   int32_t end_index
)
{
   int32_t n = 0;
   const char_t *cp_start = NULL;
   const char_t *cp_end = NULL;
   const char_t *cp = NULL;
   char_t *cp1 = NULL;

   // copy substring into string from start_index to end index

   // get pointer to start and end index
   cp_start = utf8seek( (*current).area, (*current).byte_count, (*current).area, start_index, SEEK_SET );
   cp_end = utf8seek( (*current).area, (*current).byte_count, (*current).area, end_index, SEEK_SET );
   cp = utf8seek( cp_end, (*current).byte_count, (*current).area, 1, SEEK_CUR );

   // get number of bytes between start and end
   n = cp_end - cp_start;

   // increase size of string if needed
   if ( (*current).capacity < (*current).byte_count + n_substring - n )
   {
      (*current).area = ( char_t * ) realloc( (*current).area, (*current).capacity + n_substring - n + 1 );
      CHECK( "(*current).area allocated correctly", (*current).area != NULL );

      memset( (*current).area + (*current).byte_count, 0, (*current).capacity + n_substring - n + 1 - (*current).byte_count );
      (*current).capacity = (*current).capacity + n_substring - n + 1;
      (*current).area[ (*current).capacity - 1] = 0;

      // redo index pointers
      cp_start = utf8seek( (*current).area, (*current).byte_count, (*current).area, start_index, SEEK_SET );
      cp_end = utf8seek( (*current).area, (*current).byte_count, (*current).area, end_index, SEEK_SET );
      cp = utf8seek( cp_end, (*current).byte_count, (*current).area, 1, SEEK_CUR );
   }

   // move characters after end including trailing zero to new location
   if ( n_substring != ( ( cp_end - cp_start ) + 1 ) )
   {
      cp1 = ( char_t * ) cp_end;
      memmove( cp1 + n_substring - ( cp_end - cp_start ), cp, (*current).byte_count - ( cp - (*current).area ) + 1 );
   }

   // copy substring into string
   cp1 = ( char_t * ) cp_start;
   memcpy( cp1, substring, n_substring );

   // after change, redo byte count - hash code and count are invalid
   (*current).byte_count = strlen( (*current).area );
   (*current).hash_code_valid = 0;
   (*current).count_valid = 0;

   return;
}

/**
   string_utf8_replace
*/

void
string_utf8_replace
(
   string_utf8_t *current,
   string_utf8_t *substring,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "start index ok", ( ( start_index >= 0 ) && ( start_index < get_count( current ) ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= start_index ) && ( end_index < get_count( current ) ) ) );
   INVARIANT( current );

   // unlock substring
   LOCK( (*substring).mutex );

   utf8_replace( current, (*substring).area, (*substring).byte_count, start_index, end_index );

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_replace_cstring
*/

void
string_utf8_replace_cstring
(
   string_utf8_t *current,
   char_t *substring,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   LOCK( (*current).mutex );
   PRECONDITION( "start index ok", ( ( start_index >= 0 ) && ( start_index < get_count( current ) ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < get_count( current ) ) ) );
   INVARIANT( current );

   utf8_replace( current, substring, strlen( substring ), start_index, end_index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   string_utf8_replace_all
*/

void
string_utf8_replace_all
(
   string_utf8_t *current,
   string_utf8_t *substring_original,
   string_utf8_t *substring_new
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring_original not null", substring_original != NULL );
   PRECONDITION( "substring_original type OK", ( *substring_original )._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring_new not null", substring_new != NULL );
   PRECONDITION( "substring_new type OK", ( *substring_new )._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock substring_original and substring_new
   LOCK( ( *substring_original ).mutex );
   LOCK( ( *substring_new ).mutex );

   int32_t n_new = 0;
   int32_t n_orig = 0;
   int32_t flag = 0;
   int32_t offset = 0;

   char_t *cp = NULL;
   char_t *cp_s = NULL;
   char_t *cp_s1 = NULL;
   char_t *cp_orig = NULL;
   char_t *cp_new = NULL;

   cp_s = (*current).area;
   cp_s1 = (*current).area;
   cp_orig = ( *substring_original ).area;
   cp_new = ( *substring_new ).area;

   n_orig = ( *substring_original ).byte_count;
   n_new = ( *substring_new ).byte_count;

   while( 1 )
   {
      cp = strstr( cp_s1, cp_orig );

      offset = cp - cp_s;

      if ( cp != NULL )
      {
         utf8_replace( current, cp_new, n_new, cp - cp_s, cp - cp_s + n_orig - 1 );

         // update cp_s1
         cp_s1 = (*current).area + offset + n_new;

         flag = 1;

      }
      else
      {
         break;
      }

   }

   if ( flag == 1 )
   {
      (*current).hash_code_valid = 0;
   }

   // unlock substring_original and substring_new
   UNLOCK( ( *substring_original ).mutex );
   UNLOCK( ( *substring_new ).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   string_utf8_replace_all_cstring
*/

void
string_utf8_replace_all_cstring
(
   string_utf8_t *current,
   string_utf8_t *substring_original,
   char_t *substring_new
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring_original not null", substring_original != NULL );
   PRECONDITION( "substring_original type OK", ( *substring_original )._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring_new not null", substring_new != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock substring_original
   LOCK( ( *substring_original ).mutex );

   int32_t n_orig = 0;
   int32_t n_new = 0;
   int32_t flag = 0;
   int32_t offset = 0;

   char_t *cp = NULL;
   char_t *cp_s = NULL;
   char_t *cp_s1 = NULL;
   char_t *cp_orig = NULL;
   char_t *cp_new = NULL;

   cp_s = (*current).area;
   cp_s1 = (*current).area;
   cp_orig = ( *substring_original ).area;
   cp_new = substring_new;

   n_orig = ( *substring_original ).byte_count;
   n_new = strlen( substring_new );

   while( 1 )
   {
      cp = strstr( cp_s1, cp_orig );

      offset = cp - cp_s;

      if ( cp != NULL )
      {
         utf8_replace( current, cp_new, n_new, cp - cp_s, cp - cp_s + n_orig - 1 );

         // update cp_s1
         cp_s1 = (*current).area + offset + n_new;


         flag = 1;
      }
      else
      {
         break;
      }

   }

   if ( flag == 1 )
   {
      (*current).hash_code_valid = 0;
   }

   // unlock substring_original
   UNLOCK( ( *substring_original ).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   string_utf8_replace_all_cstring2
*/

void
string_utf8_replace_all_cstring2
(
   string_utf8_t *current,
   char_t *substring_original,
   char_t *substring_new
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring_original not null", substring_original != NULL );
   PRECONDITION( "substring_new not null", substring_new != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t n_orig = 0;
   int32_t n_new = 0;
   int32_t flag = 0;
   int32_t offset = 0;

   char_t *cp = NULL;
   char_t *cp_s = NULL;
   char_t *cp_s1 = NULL;
   char_t *cp_orig = NULL;
   char_t *cp_new = NULL;

   cp_s = (*current).area;
   cp_s1 = (*current).area;
   cp_orig = substring_original;
   cp_new = substring_new;

   n_orig = strlen( substring_original );
   n_new = strlen( substring_new );

   while( 1 )
   {
      cp = strstr( cp_s1, cp_orig );

      offset = cp - cp_s;

      if ( cp != NULL )
      {
         utf8_replace( current, cp_new, n_new, cp - cp_s, cp - cp_s + n_orig - 1 );

         cp_s1 = (*current).area + offset + n_new;

         flag = 1;
      }
      else
      {
         break;
      }

   }

   if ( flag == 1 )
   {
      (*current).hash_code_valid = 0;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   string_utf8_append
*/

void
string_utf8_append( string_utf8_t *current, string_utf8_t *s )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "s not null", s != NULL );
   PRECONDITION( "s type OK", (*s)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock s
   LOCK( (*s).mutex );

   int32_t count = 0;

   // make sure there's enough space in string
   if ( (*current).capacity < (*current).byte_count + (*s).byte_count + 1 )
   {
      (*current).area = ( char_t * ) realloc( (*current).area, (*current).byte_count + (*s).byte_count + 1 );
      CHECK( "(*current).area allocated correctly", (*current).area != NULL );

      memset( &( (*current).area[ (*current).byte_count ] ), 0, (*s).byte_count + 1 );
      (*current).capacity = (*current).byte_count + (*s).byte_count + 1;
      count = (*current).byte_count + (*s).byte_count;
   }
   else
   {
      count = (*current).byte_count + (*s).byte_count;
   }

   // append s to string
   strcat( (*current).area, (*s).area );

   // set count
   (*current).byte_count = count;

   if ( (*s).byte_count > 0 )
   {
      (*current).hash_code_valid = 0;
   }

   // unlock s
   UNLOCK( (*s).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_append_cstring
*/

void
string_utf8_append_cstring( string_utf8_t *current, char_t *s )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "s not null", s != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = 0;

   // make sure there's enough space in string
   if ( (*current).capacity < (*current).byte_count + strlen( s ) + 1 )
   {
      (*current).area = ( char_t * ) realloc( (*current).area, (*current).byte_count + strlen( s ) + 1 );
      CHECK( "current).area allocated correctly", (*current).area != NULL );

      memset( &( (*current).area[ (*current).byte_count ] ), 0, strlen( s ) + 1 );
      (*current).capacity = (*current).byte_count + strlen( s ) + 1;
      count = (*current).byte_count + strlen( s );
   }
   else
   {
      count = (*current).byte_count + strlen( s );
   }

   // append s to string
   strcat( (*current).area, s );

   // set count
   (*current).byte_count = count;

   if ( strlen( s ) > 0 )
   {
      (*current).hash_code_valid = 0;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   string_utf8_prepend
*/

void
string_utf8_prepend( string_utf8_t *current, string_utf8_t *s )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "s not null", s != NULL );
   PRECONDITION( "s type OK", (*s)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock s
   LOCK( (*s).mutex );

   int32_t count = 0;
   int32_t capacity = 0;

   // get capacity, count of result string
   if ( (*current).capacity < (*current).byte_count + (*s).byte_count + 1 )
   {
      capacity = (*current).byte_count + (*s).byte_count + 1;
      count = (*current).byte_count + (*s).byte_count;
   }
   else
   {
      capacity = (*current).capacity;
      count = (*current).byte_count + (*s).byte_count;
   }

   // make new string, append strings to prepend s to string
   char_t *cp = calloc( capacity, sizeof( char_t ) );
   CHECK( "cp allocated correctly", cp != NULL );

   strcat( cp, (*s).area );
   strcat( cp, (*current).area );

   // free original (*current).area, replace with cp
   free( (*current).area );
   (*current).area = cp;

   // set string capacity and count
   (*current).capacity = capacity;
   (*current).byte_count = count;

   if ( (*s).byte_count > 0 )
   {
      (*current).hash_code_valid = 0;
   }

   // unlock s
   UNLOCK( (*s).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   string_utf8_prepend_cstring
*/

void
string_utf8_prepend_cstring( string_utf8_t *current, char_t *s )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "s not null", s != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = 0;
   int32_t capacity = 0;

   int32_t s_count = strlen( s );

   // get capacity, count of result string
   if ( (*current).capacity < (*current).byte_count + s_count + 1 )
   {
      capacity = (*current).byte_count + s_count + 1;
      count = (*current).byte_count + s_count;
   }
   else
   {
      capacity = (*current).capacity;
      count = (*current).byte_count + s_count;
   }

   // make new string, append strings to prepend s to string
   char_t *cp = calloc( capacity, sizeof( char_t ) );
   CHECK( "cp allocated correctly", cp != NULL );

   strcat( cp, s );
   strcat( cp, (*current).area );

   // free original (*current).area, replace with cp
   free( (*current).area );
   (*current).area = cp;

   // set string capacity and count
   (*current).capacity = capacity;
   (*current).byte_count = count;

   if ( s_count > 0 )
   {
      (*current).hash_code_valid = 0;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   utf8_insert
*/
static
void
utf8_insert
(
   string_utf8_t *current,
   char_t *substring,
   int32_t n_substring,
   int32_t index
)
{
   int32_t capacity = 0;
   char_t *cp = NULL;
   const char_t *cp1 = NULL;

   // increase string capacity if needed
   if ( (*current).capacity < (*current).byte_count + n_substring + 1 )
   {
      capacity = (*current).byte_count + n_substring + 1;
      (*current).area = ( char_t * ) realloc( (*current).area, capacity );
      CHECK( "(*current).area allocated correctly", (*current).area != NULL );

      memset( &( (*current).area[ (*current).byte_count ] ), 0, capacity - (*current).byte_count );
      (*current).capacity = capacity;
   }
   else
   {
      capacity = (*current).capacity;
   }

   // get pointer to index
   cp1 = utf8seek( (*current).area, (*current).byte_count, (*current).area, index, SEEK_SET );
   cp = ( char_t * ) cp1;

   // move string contents after index back the size of substring
   memmove( cp + n_substring, cp, (*current).byte_count - ( cp - (*current).area ) );

   // set substring in string
   memcpy( cp, substring, n_substring * sizeof( char_t ) );
   (*current).byte_count = (*current).byte_count + n_substring;

   if ( n_substring > 0 )
   {
      (*current).hash_code_valid = 0;
      (*current).count_valid = 0;
   }

   return;
}

/**
   string_utf8_insert
*/

void
string_utf8_insert( string_utf8_t *current, string_utf8_t *substring, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_UTF8_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= get_count( current ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock substring
   LOCK( (*substring).mutex );

   utf8_insert( current, (*substring).area, (*substring).byte_count, index );

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   string_utf8_insert_cstring
*/

void
string_utf8_insert_cstring( string_utf8_t *current, char_t *substring, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= get_count( current ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   utf8_insert( current, substring, strlen( substring ), index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   utf8_append_character
*/
static
void
utf8_append_character( string_utf8_t *current, char_t *c )
{
   int32_t i = 0;
   int32_t n_c = 0;
   char_t *cp = NULL;

   n_c = strlen( c );

   // increase string capacity if needed
   if ( (*current).capacity < (*current).byte_count + n_c + 1 )
   {
      (*current).area = ( char_t * ) realloc( (*current).area, (*current).capacity + n_c + 1 );
      CHECK( "(*current).area allocated correctly", (*current).area != NULL );

      memset( &( (*current).area[ (*current).capacity ] ), 0, n_c );
      (*current).capacity = (*current).capacity + n_c + 1;
   }

   // set character into string
   cp = &( (*current).area[ (*current).byte_count ] );

   for( i = 0; i < n_c; i++ )
   {
      cp[i] = c[i];
   }

   // zero termination
   cp[i] = 0;

   (*current).byte_count = (*current).byte_count + n_c;

   (*current).hash_code_valid = 0;
   (*current).count_valid = 0;

   return;
}

/**
   string_utf8_append_character
*/

void
string_utf8_append_character( string_utf8_t *current, char_t *c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "c not null", c != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   utf8_append_character( current, c );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_append_character_ascii
*/

void
string_utf8_append_character_ascii( string_utf8_t *current, char_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "c is ascii", ( c & STRING_UTF8_ASCII_MASK ) == 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t str[STRING_UTF8_CHAR_MAX_SIZE] = {0};
   str[0] = c;

   utf8_append_character( current, str );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_append_character_utf16
*/

void
string_utf8_append_character_utf16( string_utf8_t *current, utf16_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *s = NULL;

   s = utf16_to_utf8( c );

   utf8_append_character( current, s );

   free( s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_append_character_utf32
*/

void
string_utf8_append_character_utf32( string_utf8_t *current, utf32_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *s = NULL;

   s = utf32_to_utf8( c );

   utf8_append_character( current, s );

   free( s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_append_character_wchar
*/

void
string_utf8_append_character_wchar( string_utf8_t *current, wchar_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *s = NULL;

   s = wchar_to_utf8( c );

   utf8_append_character( current, s );

   free( s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_prepend_character
*/

void
string_utf8_prepend_character( string_utf8_t *current, char_t *c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "c not null", c != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   utf8_insert( current, c, strlen( c ), 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_prepend_character_ascii
*/

void
string_utf8_prepend_character_ascii( string_utf8_t *current, char_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "c is ascii", ( c & STRING_UTF8_ASCII_MASK ) == 0 );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t str[STRING_UTF8_CHAR_MAX_SIZE] = {0};
   str[0] = c;
   utf8_insert( current, str, strlen( str ), 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_prepend_character_utf16
*/

void
string_utf8_prepend_character_utf16( string_utf8_t *current, utf16_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *s = NULL;

   s = utf16_to_utf8( c );

   utf8_insert( current, s, strlen( s ), 0 );

   free( s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_prepend_character_utf32
*/

void
string_utf8_prepend_character_utf32( string_utf8_t *current, utf32_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *s = NULL;

   s = utf32_to_utf8( c );

   utf8_insert( current, s, strlen( s ), 0 );

   free( s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_prepend_character_wchar
*/

void
string_utf8_prepend_character_wchar( string_utf8_t *current, wchar_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *s = NULL;

   s = wchar_to_utf8( c );

   utf8_insert( current, s, strlen( s ), 0 );

   free( s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_insert_character
*/

void
string_utf8_insert_character( string_utf8_t *current, char_t *c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "c not null", c != NULL );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= get_count( current ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   utf8_insert( current, c, strlen( c ), index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_insert_character_ascii
*/

void
string_utf8_insert_character_ascii( string_utf8_t *current, char_t c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "c is ascii", ( c & STRING_UTF8_ASCII_MASK ) == 0 );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= get_count( current ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t str[STRING_UTF8_CHAR_MAX_SIZE] = {0};
   str[0] = c;

   utf8_insert( current, str, strlen( str ), index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_insert_character_utf16
*/

void
string_utf8_insert_character_utf16( string_utf8_t *current, utf16_t c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= get_count( current ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *s = NULL;

   s = utf16_to_utf8( c );

   utf8_insert( current, s, strlen( s ), index );

   free( s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_insert_character_utf32
*/

void
string_utf8_insert_character_utf32( string_utf8_t *current, utf32_t c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= get_count( current ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *s = NULL;

   s = utf32_to_utf8( c );

   utf8_insert( current, s, strlen( s ), index );

   free( s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_insert_character_wchar
*/

void
string_utf8_insert_character_wchar( string_utf8_t *current, wchar_t c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= get_count( current ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *s = NULL;

   s = wchar_to_utf8( c );

   utf8_insert( current, s, strlen( s ), index );

   free( s );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_insert_int32
*/

void
string_utf8_insert_int32( string_utf8_t *current, int32_t i, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= get_count( current ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *s_i = calloc( 120, sizeof( char_t ) );
   CHECK( "s_i allocated correctly", s_i != NULL );

   int32_t s_i_count = 0;

   // make stringified version of integer
   s_i_count = sprintf( s_i, "%d", i );

   utf8_insert( current, s_i, s_i_count, index );

   free( s_i );

   (*current).hash_code_valid = 0;
   (*current).count_valid = 0;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_insert_float64
*/

void
string_utf8_insert_float64( string_utf8_t *current, float64_t f, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= get_count( current ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *s_f = calloc( 120, sizeof( char_t ) );
   CHECK( "s_f allocated correctly", s_f != NULL );

   int32_t s_f_count = 0;

   // make stringified version of integer
   s_f_count = sprintf( s_f, "%lf", f );

   utf8_insert( current, s_f, s_f_count, index );

   // free temp string
   free( s_f );

   (*current).hash_code_valid = 0;
   (*current).count_valid = 0;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}



/**
   string_utf8_to_lower
*/

void
string_utf8_to_lower( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *cp = NULL;
   int32_t n = 0;
   int32_t errors = 0;

   // get size of lowercased string
   n = utf8tolower( (*current).area, (*current).byte_count, NULL, 1, utf8envlocale(), &errors );
   CHECK( "utf8 translation errors", errors == 0 );

   cp = ( char_t * ) calloc( n + 1, sizeof( char_t ) );
   CHECK( "cp allocated correctly", cp != NULL );

   utf8tolower( (*current).area, (*current).byte_count, cp, n, utf8envlocale(), &errors );
   CHECK( "utf8 translation errors", errors == 0 );

   free( (*current).area );
   (*current).area = cp;
   (*current).capacity = n + 1;

   (*current).hash_code_valid = 0;
   (*current).count_valid = 0;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_to_upper
*/

void
string_utf8_to_upper( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *cp = NULL;
   int32_t n = 0;
   int32_t errors = 0;

   // get size of uppercased string
   n = utf8toupper( (*current).area, (*current).byte_count, NULL, 1, utf8envlocale(), &errors );
   CHECK( "utf8 translation errors", errors == 0 );

   cp = ( char_t * ) calloc( n + 1, sizeof( char_t ) );
   CHECK( "cp allocated correctly", cp != NULL );

   utf8toupper( (*current).area, (*current).byte_count, cp, n, utf8envlocale(), &errors );
   CHECK( "utf8 translation errors", errors == 0 );

   free( (*current).area );
   (*current).area = cp;
   (*current).capacity = n + 1;

   (*current).hash_code_valid = 0;
   (*current).count_valid = 0;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_substring
*/

string_utf8_t *
string_utf8_substring( string_utf8_t *current, int32_t start_index, int32_t end_index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < get_count( current ) ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= start_index ) && ( end_index < get_count( current ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   const char_t *cp_start = NULL;
   const char_t *cp_end = NULL;
   int32_t n = 0;

   cp_start = utf8seek( (*current).area, (*current).byte_count, (*current).area, start_index, SEEK_SET );
   cp_end = utf8seek( (*current).area, (*current).byte_count, (*current).area, end_index, SEEK_SET );
   cp_end = utf8seek( cp_end, (*current).byte_count, (*current).area, 1, SEEK_CUR );

   n = cp_end - cp_start;

   string_utf8_t *result = string_utf8_make_n( n + 1 );
   memcpy( (*result).area, cp_start, n );
   (*result).byte_count = n;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_utf8_copy
*/

string_utf8_t *
string_utf8_copy( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_utf8_t *result = s_copy( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   utf8_remove
*/
static
void
utf8_remove( string_utf8_t *current, int32_t start_offset, int32_t end_offset )
{
   char_t *cp = NULL;

   // move string contents after offset forward
   cp = (*current).area;
   memmove( cp + start_offset, cp + end_offset + 1, (*current).byte_count - end_offset - 1 );

   // set byte_count
   (*current).byte_count = (*current).byte_count - end_offset + start_offset - 1;
   cp[ (*current).byte_count ] = 0;

   (*current).hash_code_valid = 0;
   (*current).count_valid = 0;

   return;
}

/**
   string_utf8_remove
*/

void
string_utf8_remove( string_utf8_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < get_count( current ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   const char_t *cp_index = NULL;
   const char_t *cp_next = NULL;

   cp_index = utf8seek( (*current).area, (*current).byte_count, (*current).area, index, SEEK_SET );
   cp_next = utf8seek( cp_index, (*current).byte_count, (*current).area, 1, SEEK_CUR );

   utf8_remove( current, cp_index - (*current).area, ( cp_next - (*current).area ) - 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_remove_substring
*/

void
string_utf8_remove_substring( string_utf8_t *current, int32_t start_index, int32_t end_index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < get_count( current ) ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= start_index ) && ( end_index < get_count( current ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   const char_t *cp_start = NULL;
   const char_t *cp_end = NULL;
   const char_t *cp_next = NULL;

   cp_start = utf8seek( (*current).area, (*current).byte_count, (*current).area, start_index, SEEK_SET );
   cp_end = utf8seek( (*current).area, (*current).byte_count, (*current).area, end_index, SEEK_SET );
   cp_next = utf8seek( cp_end, (*current).byte_count, (*current).area, 1, SEEK_CUR );

   utf8_remove( current, cp_start - (*current).area, ( cp_next - (*current).area ) - 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_keep_head
*/

void
string_utf8_keep_head( string_utf8_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", get_count( current ) >= count );

   char_t *cp = NULL;

   // get pointer to index at count
   cp = ( char_t * ) utf8seek( (*current).area, (*current).byte_count, (*current).area, count, SEEK_SET );

   // set new end
   *cp = 0;

   // update byte count
   (*current).byte_count = strlen( (*current).area );

   // hash code and count invalidated
   (*current).hash_code_valid = 0;
   (*current).count_valid = 0;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_remove_head
*/

void
string_utf8_remove_head( string_utf8_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", get_count( current ) >= count );
   INVARIANT( current );

   const char_t *cp = NULL;

   // get pointer to character past count
   cp = utf8seek( (*current).area, (*current).byte_count, (*current).area, count, SEEK_SET );

   // remove bytes
   utf8_remove( current, 0, ( cp - (*current).area ) - 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_keep_tail
*/

void
string_utf8_keep_tail( string_utf8_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", get_count( current ) >= count );
   INVARIANT( current );

   int32_t index = 0;
   const char_t *cp = NULL;

   // make sure string count is valid
   set_count( current );

   // get character index of one past character to keep
   index = (*current).count - count;

   // get pointer to index
   cp = utf8seek( (*current).area, (*current).byte_count, (*current).area, index, SEEK_SET );

   // remove bytes
   utf8_remove( current, 0, ( cp - (*current).area ) - 1 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_remove_tail
*/

void
string_utf8_remove_tail( string_utf8_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", get_count( current ) >= count );
   INVARIANT( current );

   int32_t index = 0;
   char_t *cp = NULL;

   // make sure string count is valid
   set_count( current );

   // get character index of one past character to keep
   index = (*current).count - count;

   // get pointer to index
   cp = ( char_t * ) utf8seek( (*current).area, (*current).byte_count, (*current).area, index, SEEK_SET );

   // set new end
   *cp = 0;

   // update byte count
   (*current).byte_count = strlen( (*current).area );

   // hash code and count invalidated
   (*current).hash_code_valid = 0;
   (*current).count_valid = 0;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_wipe_out
*/

void
string_utf8_wipe_out( string_utf8_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set to empty string
   (*current).area[0] = 0;
   (*current).byte_count = 0;

   (*current).hash_code_valid = 0;
   (*current).count_valid = 0;

   INVARIANT( current );
   POSTCONDITION( "string empty", (*current).count == 0 );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_utf8_resize
*/

void
string_utf8_resize( string_utf8_t *current, int32_t new_capacity )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_UTF8_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "capacity ok", new_capacity > (*current).byte_count );
   INVARIANT( current );

   // don't reduce capacity below what is required to store the content
   if ( new_capacity > (*current).byte_count )
   {
      // make new capacity at least 4 characters
      if ( new_capacity < STRING_MIN_SIZE )
      {
         new_capacity = STRING_MIN_SIZE;
      }

      // set new capacity
      (*current).area = ( char_t * ) realloc( (*current).area, new_capacity );
      CHECK( "(*current).area allocated correctly", (*current).area != NULL );

      if ( new_capacity > (*current).capacity )
      {
         memset( (*current).area + (*current).byte_count, 0, new_capacity - (*current).byte_count );
      }

      (*current).capacity = new_capacity;
   }

   INVARIANT( current );
   POSTCONDITION( "capacity set", (*current).capacity == new_capacity );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

