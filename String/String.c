/**
 @file String.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Character Strings (non-unicode)"

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

 Function definitions for the opaque string_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include "String.h"

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
   to_lowercase

   return lowercase of character if its a letter, otherwise returns the character.

   @param c the character to convert
   @return lowercase version of character
*/
static
char_t
to_lowercase
(
   char_t c
)
{
   char_t result = c;

   if ( ( result >= 'A' ) && ( result <= 'Z' ) )
   {
      result = result - 'A' + 'a';
   }

   return result;
}

/**
   to_uppercase

   return uppercase of character if its a letter, otherwise returns the character.

   @param c the character to convert
   @return uppercase version of character
*/
static
char_t
to_uppercase
(
   char_t c
)
{
   char_t result = c;

   if ( ( result >= 'a' ) && ( result <= 'z' ) )
   {
      result = result - 'a' + 'A';
   }

   return result;
}


/**
   is_whitespace

   return 1 if character is whitespace - space, tab, form feed, carriage return,
   line feed, vertical tab. 0 otherwise.

   @param c the character to test
   @return 1 if whitespace, 0 otherwise
*/
static
int32_t
is_whitespace( char_t c )
{
   int32_t result = 0;

   if ( c == ' ' )
   {
      result = 1;
   }
   else if ( c == '\t' )
   {
      result = 1;
   }
   else if ( c == '\r' )
   {
      result = 1;
   }
   else if ( c == '\n' )
   {
      result = 1;
   }
   else if ( c == '\v' )
   {
      result = 1;
   }
   else if ( c == '\f' )
   {
      result = 1;
   }

   return result;
}

/**
   string structure
*/

struct string_struct
{
   int32_t _type;

   char *area;
   int32_t count;
   int32_t capacity;
   int32_t hash_code;
   int32_t hash_code_valid;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

#if INVARIANT_CONDITIONAL != 0

static
int32_t
area_not_null( string_t *current )
{
   int32_t result = 1;

   result = ( (*current).area != NULL );

   return result;
}

static
int32_t
nonnegative_count( string_t *current )
{
   int32_t result = 1;

   result = ( (*current).count >= 0 );

   return result;
}

static
int32_t
valid_count( string_t *current )
{
   int32_t result = 1;

   result = ( (*current).count == strlen( (*current).area ) );

   return result;
}

static
int32_t
capacity_ok( string_t *current )
{
   int32_t result = 1;

   result = ( (*current).capacity > (*current).count );

   return result;
}

static
int32_t
hash_ok( string_t *current )
{
   int32_t result = 1;

   if ( (*current).hash_code_valid == 1 )
   {
      result = ( (*current).hash_code == get_hash( (*current).area, (*current).count ) );
   }

   return result;
}

static
void invariant( string_t *current )
{
   assert( ( ( void ) "area not null", area_not_null( current ) ) );
   assert( ( ( void ) "nonnegative count", nonnegative_count( current ) ) );
   assert( ( ( void ) "valid count", valid_count( current ) ) );
   assert( ( ( void ) "capacity ok", capacity_ok( current ) ) );
   assert( ( ( void ) "hash code ok", hash_ok( current ) ) );
   return;
}

#endif

/**
   string_make
*/

string_t *
string_make( void )
{
   // allocate string struct
   string_t * result = ( string_t * ) calloc( 1, sizeof( string_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = STRING_TYPE;

   // allocate area
   (*result).area = ( char * ) calloc( STRING_MIN_SIZE, sizeof( char_t ) );
   CHECK( "(*result).area allocated correctly", (*result).area != NULL );

   // set count
   (*result).count = 0;

   // set capacity
   (*result).capacity = 1;

   // set hash_code
   (*result).hash_code = 0;

   // set hash_code_valid
   (*result).hash_code_valid = 0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   string_make_n
*/

string_t *
string_make_n( int32_t capacity )
{
   PRECONDITION( "capacity ok", capacity > 0 );

   int32_t real_capacity = STRING_MIN_SIZE;

   // allocate string struct
   string_t *result = ( string_t * ) calloc( 1, sizeof( string_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = STRING_TYPE;

   if ( capacity > STRING_MIN_SIZE )
   {
      real_capacity = capacity;
   }

   // allocate area
   (*result).area = ( char * ) calloc( real_capacity, sizeof( char_t ) );
   CHECK( "(*result).area allocated correctly", (*result).area != NULL );

   // set count
   (*result).count = 0;

   // set capacity
   (*result).capacity = real_capacity;

   // set hash_code
   (*result).hash_code = 0;

   // set hash_code_valid
   (*result).hash_code_valid = 0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "capacity set", (*result).capacity == real_capacity );
   INVARIANT( result );

   return result;
}

/**
   string_make_from_cstring
*/

string_t *
string_make_from_cstring( char *str )
{
   PRECONDITION( "str not null", str != NULL );

   int32_t real_capacity = STRING_MIN_SIZE;

   // allocate string struct
   string_t *result = ( string_t * ) calloc( 1, sizeof( string_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = STRING_TYPE;

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
   (*result).area = ( char * ) calloc( real_capacity, sizeof( char_t ) );
   CHECK( "(*result).area allocated correctly", (*result).area != NULL );

   strncpy( (*result).area, str, n );

   // set count
   (*result).count = n;

   // set capacity
   (*result).capacity = real_capacity;

   // set hash_code
   (*result).hash_code = 0;

   // set hash_code_valid
   (*result).hash_code_valid = 0;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "size set", (*result).count == strlen( str ) );
   POSTCONDITION( "area set", strcmp( (*result).area, str ) == 0 );
   INVARIANT( result );

   return result;
}


/**
   s_clone
*/

static
string_t *
s_clone( string_t *current )
{
   // allocate string struct
   string_t *result = ( string_t * ) calloc( 1, sizeof( string_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = STRING_TYPE;

   // set area
   (*result).area = ( char * ) calloc( (*current).capacity, sizeof( char_t ) );
   CHECK( "(*result).area allocated correctly", (*result).area != NULL );

   strncpy( (*result).area, (*current).area, (*current).count );

   // set count
   (*result).count = (*current).count;

   // set capacity
   (*result).capacity = (*current).capacity;

   // set hash_code
   (*result).hash_code = (*current).hash_code;

   // set hash_code_valid
   (*result).hash_code_valid = (*current).hash_code_valid;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   return result;
}

/**
   string_clone
*/

string_t *
string_clone( string_t *current )
{
   PRECONDITION( "string not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   INVARIANT( current );

   string_t *result = NULL;

   // lock mutex
   LOCK( (*current).mutex );

   result = s_clone( current );

   // unlock mutex
   UNLOCK( (*current).mutex );

   POSTCONDITION( "size set", (*result).count == (*current).count );
   POSTCONDITION( "area set", strcmp( (*result).area, (*current).area ) == 0 );
   INVARIANT( result );

   return result;
}

/**
   string_deep_clone
*/

string_t *
string_deep_clone( string_t *current )
{
   PRECONDITION( "string not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   INVARIANT( current );

   string_t *result = NULL;

   // lock mutex
   LOCK( (*current).mutex );

   result = s_clone( current );

   // unlock mutex
   UNLOCK( (*current).mutex );

   POSTCONDITION( "size set", (*result).count == (*current).count );
   POSTCONDITION( "area set", strcmp( (*result).area, (*current).area ) == 0 );
   INVARIANT( result );

   return result;
}

/**
   string_is_equal
*/

int32_t
string_is_equal( string_t *current, string_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = ( strcmp( (*current).area, (*other).area ) == 0 );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   UNLOCK( (*current).mutex );
   INVARIANT( current );

   return result;
}

/**
   string_is_deep_equal
*/

int32_t
string_is_deep_equal( string_t *current, string_t *other )
{
   // is_deep_equal is same as is_equal for this type
   return string_is_equal( current, other );
}

/**
   string_copy
*/

void
string_copy( string_t *current, string_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == STRING_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   // ensure current has enough capacity to hold other
   if ( (*current).capacity < (*other).count + 1 )
   {
      (*current).area = ( char_t * ) realloc( (*current).area, (*other).count + 1 );
      CHECK( "(*current).area reallocated correctly", (*current).area != NULL );
      memset( (*current).area, 0, (*other).count + 1 );
      (*current).capacity = (*other).count + 1;
   }

   // copy characters
   strcpy( (*current).area, (*other).area );

   // set count, hash_code
   (*current).count = (*other).count;
   (*current).hash_code = (*other).hash_code;
   (*current).hash_code_valid = (*other).hash_code_valid;

   POSTCONDITION( "size set", (*current).count == (*other).count );
   POSTCONDITION( "area set", strcmp( (*current).area, (*other).area ) == 0 );

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_deep_copy
*/

void
string_deep_copy( string_t *current, string_t *other )
{
   // deep copy is same as copy for this type
   string_copy( current, other );
   return;
}

/**
   string_copy_cstring
*/

void
string_copy_cstring( string_t *current, char_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "other not null", other != NULL );

   INVARIANT( current );

   // lock mutex
   LOCK( (*current).mutex );

   // ensure current has enough capacity to hold other
   if ( (*current).capacity < strlen( other ) + 1 )
   {
      (*current).area = ( char_t * ) realloc( (*current).area, strlen( other ) + 1 );
      CHECK( "(*current).area reallocated correctly", (*current).area != NULL );
      memset( (*current).area, 0, strlen( other ) + 1 );
      (*current).capacity = strlen( other ) + 1;
   }

   // copy characters
   strcpy( (*current).area, other );

   // set count, hash_code
   (*current).count = strlen( other );
   (*current).hash_code = 0;
   (*current).hash_code_valid = 0;

   POSTCONDITION( "size set", (*current).count == strlen( other ) );
   POSTCONDITION( "area set", strcmp( (*current).area, other ) == 0 );

   INVARIANT( current );

   // unlock mutex
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_dispose

*/

void
string_dispose( string_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == STRING_TYPE );
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
   string_deep_dispose
*/

void
string_deep_dispose( string_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == STRING_TYPE );
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
   string_dispose_wrapper

*/

void
string_dispose_wrapper( string_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == STRING_TYPE );
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
   string_item
*/

char_t
string_item( string_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   INVARIANT( current );

   char_t result = (*current).area[index];

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_as_cstring
*/

char_t *
string_as_cstring( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *result = (*current).area;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_count
*/

int32_t
string_count( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).count;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_capacity
*/

int32_t
string_capacity( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result =  (*current).capacity;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_char_count
*/

int32_t
string_char_count( string_t *current, char_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t result = 0;
   int32_t n = 0;
   char_t *area = NULL;

   n = (*current).count;
   area = (*current).area;

   for( i = 0; i < n; i++ )
   {
      if ( area[i] == c )
      {
         result = result + 1;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_is_empty
*/

int32_t
string_is_empty( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( (*current).count == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_valid_index
*/

int32_t
string_valid_index( string_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = ( index >= 0 ) && ( index < (*current).count );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_has
*/

int32_t
string_has( string_t *current, char_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   int32_t result = 0;

   // search string for character c, stop if found
   for( i = 0; i < (*current).count; i++ )
   {
      if ( (*current).area[i] == c )
      {
         result = 1;
         break;
      }
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_is_int32
*/

int32_t
string_is_int32( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
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
   string_is_float64
*/

int32_t
string_is_float64( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
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
   string_hash_code
*/

int32_t
string_hash_code( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   if ( (*current).hash_code_valid == 0 )
   {
      (*current).hash_code = get_hash( (*current).area, (*current).count );
      (*current).hash_code_valid = 1;
   }

   int32_t result = (*current).hash_code;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_is_equal_cstring
*/

int32_t
string_is_equal_cstring( string_t *current, char_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   result = strcmp( (*current).area, other );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return ( result == 0 );
}


/**
   string_is_less_than
*/

int32_t
string_is_less_than( string_t *current, string_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 0;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = ( strcmp( (*current).area, (*other).area ) < 0 );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_is_less_than_cstring
*/

int32_t
string_is_less_than_cstring( string_t *current, char_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   result = strcmp( (*current).area, other );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return ( result < 0 );
}


/**
   string_is_less_than_or_equal
*/

int32_t
string_is_less_than_or_equal( string_t *current, string_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = ( strcmp( (*current).area, (*other).area ) <= 0 );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_is_less_than_or_equal_cstring
*/

int32_t
string_is_less_than_or_equal_cstring( string_t *current, char_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   result = strcmp( (*current).area, other );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return ( result <= 0 );
}

/**
   string_is_greater_than
*/

int32_t
string_is_greater_than( string_t *current, string_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 0;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = ( strcmp( (*current).area, (*other).area ) > 0 );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_is_greater_than_cstring
*/

int32_t
string_is_greater_than_cstring( string_t *current, char_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   result = strcmp( (*current).area, other );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return ( result > 0 );
}

/**
   string_is_greater_than_or_equal
*/

int32_t
string_is_greater_than_or_equal( string_t *current, string_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 1;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = ( strcmp( (*current).area, (*other).area ) >= 0 );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_is_greater_than_or_equal_cstring
*/

int32_t
string_is_greater_than_or_equal_cstring( string_t *current, char_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   result = strcmp( (*current).area, other );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return ( result >= 0 );
}

/**
   string_compare
*/

int32_t
string_compare( string_t *current, string_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;

   if ( current == other )
   {
      result = 0;
   }
   else
   {
      // lock other
      LOCK( (*other).mutex );

      result = strcmp( (*current).area, (*other).area );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_compare_cstring
*/

int32_t
string_compare_cstring( string_t *current, char_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "other not null", other != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   result = strcmp( (*current).area, other );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_has_substring
*/

int32_t
string_has_substring( string_t *current, string_t *substring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_TYPE );
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
   string_substring_count
*/

int32_t
string_substring_count( string_t *current, string_t *substring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock substring
   LOCK( (*substring).mutex );

   int32_t result = 0;
   int32_t length = (*substring).count;

   char_t *cp = NULL;
   cp = strstr( (*current).area, (*substring).area );

   while( cp != NULL )
   {
      result = result + 1;
      cp = strstr( cp + length, (*substring).area );
   }

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return ( result );
}

/**
   string_substring_count_cstring
*/

int32_t
string_substring_count_cstring( string_t *current, char_t *substring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   int32_t length = strlen( substring );

   char_t *cp = NULL;
   cp = strstr( (*current).area, substring );

   while( cp != NULL )
   {
      result = result + 1;
      cp = strstr( cp + length, substring );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return ( result );
}

/**
   string_has_substring_cstring
*/

int32_t
string_has_substring_cstring( string_t *current, char_t *substring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
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
   string_starts_with
*/

int32_t
string_starts_with( string_t *current, string_t *substring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_TYPE );
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
   string_starts_with_cstring
*/

int32_t
string_starts_with_cstring( string_t *current, char_t *substring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
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
   string_ends_with
*/

int32_t
string_ends_with( string_t *current, string_t *substring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // unlock substring
   LOCK( (*substring).mutex );

   int32_t result = 0;
   char_t *cp = NULL;

   if ( (*substring).count <= (*current).count )
   {
      cp = strstr( (*current).area + ( (*current).count - (*substring).count ), (*substring).area );
      result = ( cp == (*current).area + ( (*current).count - (*substring).count ) );
   }

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

int32_t
string_ends_with_cstring( string_t *current, char_t *substring )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = 0;
   char_t *cp = NULL;

   int32_t substring_length = strlen( substring );

   if ( substring_length <= (*current).count )
   {
      cp = strstr( (*current).area + ( (*current).count - substring_length ), substring );
      result = ( cp == (*current).area + ( (*current).count - substring_length ) );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_substring_index_in_bounds
*/

int32_t
string_substring_index_in_bounds
(
   string_t *current,
   string_t *substring,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_TYPE );
   PRECONDITION( "start index ok", ( ( start_index >= 0 ) && ( start_index < (*current).count ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < (*current).count ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock substring
   LOCK( (*substring).mutex );

   char_t *cp = NULL;
   int32_t result = 0;

   cp = strstr( (*current).area + start_index, (*substring).area );
   if ( cp != NULL )
   {
      result = cp - (*current).area;
   }

   if ( ( cp == NULL ) || ( result < start_index ) || ( result > end_index ) )
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
   string_substring_index_in_bounds_cstring
*/

int32_t
string_substring_index_in_bounds_cstring
(
   string_t *current,
   char_t *substring,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "start index ok", ( ( start_index >= 0 ) && ( start_index < (*current).count ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < (*current).count ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *cp = NULL;
   int32_t result = 0;

   cp = strstr( (*current).area + start_index, substring );
   if ( cp != NULL )
   {
      result = cp - (*current).area;
   }

   if ( ( cp == NULL ) || ( result < start_index ) || ( result > end_index ) )
   {
      result = -1;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}


/**
   string_substring_index
*/

int32_t
string_substring_index
(
   string_t *current,
   string_t *substring
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock substring
   LOCK( (*substring).mutex );

   char_t *cp = NULL;
   int32_t result = 0;

   cp = strstr( (*current).area, (*substring).area );

   if ( cp == NULL )
   {
      result = -1;
   }
   else
   {
      result = cp - (*current).area;
   }

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_substring_index_cstring
*/

int32_t
string_substring_index_cstring
(
   string_t *current,
   char_t *substring
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *cp = NULL;
   int32_t result = 0;

   cp = strstr( (*current).area, substring );

   if ( cp == NULL )
   {
      result = -1;
   }
   else
   {
      result = cp - (*current).area;
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}


#define STRTOK_R_DEFINED
#ifndef STRTOK_R_DEFINED // use this code for strtok_r if it's not defined in <string.h>
/**
   strtok_r

   Parse s into tokens separated by characters in delim.
   If s is NULL, the saved pointer in save_ptr is used as
   the next starting point.  For example:

        char s[] = "-abc-=-def";
        char *sp;
        x = strtok_r( s, "-", &sp );      // x = "abc", sp = "=-def"
        x = strtok_r( NULL, "-=", &sp );  // x = "def", sp = NULL
        x = strtok_r( NULL, "=", &sp );   // x = NULL
                                          // s = "abc\0-def\0"
*/
static
char_t *
strtok_r( char_t *s, char_t *delim, char_t **save_ptr )
{
   char_t *result = NULL;
   char_t *end = NULL;

   if ( s == NULL )
   {
      s = *save_ptr;
   }

   if ( *s == '\0' )
   {
      *save_ptr = s;
      result = NULL;
   }
   else
   {
      // scan leading delimiters.
      s = s + strspn( s, delim );
      if ( *s == '\0' )
      {
         *save_ptr = s;
         result = NULL;
      }
      else
      {
         // find the end of the token.
         end = s + strcspn( s, delim );
         if ( *end == '\0' )
         {
            *save_ptr = end;
            result = s;
         }
         else
         {
            // terminate the token and make *save_ptr point past it.
            *end = '\0';
            *save_ptr = end + 1;
            result = s;
         }
      }
   }

   return result;
}
#endif // strtok_r

#define DEFAULT_SPLIT_RETURN_ARRAY_SIZE 8

/**
   string_split
*/

string_t **
string_split( string_t *current, string_t *separators, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "separators not null", separators != NULL );
   PRECONDITION( "separators type OK", (*separators)._type == STRING_TYPE );
   PRECONDITION( "count ok", count != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock separators
   LOCK( (*separators).mutex );

   char_t *scopy = NULL;
   char_t *cp = NULL;
   char_t *save_cp = NULL;
   string_t **result = NULL;
   int32_t i_result = 0;
   string_t *s = NULL;
   int32_t size = DEFAULT_SPLIT_RETURN_ARRAY_SIZE;

   // allocate array to return
   result = ( string_t ** ) calloc( size, sizeof( string_t * ) );
   CHECK( "result allocated correctly", result != NULL );

   // allocate and fill temp string
   scopy = ( char_t * ) calloc( (*current).count + 1, sizeof( char_t ) );
   CHECK( "scopy allocated correctly", scopy != NULL );

   strcpy( scopy, (*current).area );

   // split scopy into tokens, make into strings, put into return array
   cp = strtok_r( scopy, (*separators).area, &save_cp );

   while( cp != NULL )
   {
      s = string_make_from_cstring( cp );

      // put the string into the return array
      if ( i_result < ( size - 1 ) )
      {
         result[i_result] = s;
         i_result = i_result + 1;
      }
      // resize the array if necessary
      else
      {
         result = ( string_t ** ) realloc( result, 2 * size * sizeof( string_t * ) );
         CHECK( "result reallocated correctly", result != NULL );

         memset( result + size, 0, sizeof( string_t * )*size );
         size = 2 * size;
         result[i_result] = s;
         i_result = i_result + 1;
      }

      cp = strtok_r( NULL, (*separators).area, &save_cp );
   }

   // deallocate temp string
   free( scopy );

   // unlock separators
   UNLOCK( (*separators).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   // return list
   *count = i_result;

   return result;
}


/**
   string_split_cstring
*/

string_t **
string_split_cstring( string_t *current, char_t *separators, int32_t *count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "separators not null", separators != NULL );
   PRECONDITION( "count ok", count != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *scopy = NULL;
   char_t *cp = NULL;
   char_t *save_cp = NULL;
   string_t **result = NULL;
   int32_t i_result = 0;
   string_t *s = NULL;
   int32_t size = DEFAULT_SPLIT_RETURN_ARRAY_SIZE;

   // allocate array to return
   result = ( string_t ** ) calloc( size, sizeof( string_t * ) );
   CHECK( "result allocated correctly", result != NULL );

   // allocate and fill temp string
   scopy = ( char_t * ) calloc( (*current).count + 1, sizeof( char_t ) );
   CHECK( "scopy allocated correctly", scopy != NULL );

   strcpy( scopy, (*current).area );

   // split scopy into tokens, make into strings, put into return array
   cp = strtok_r( scopy, separators, &save_cp );

   while( cp != NULL )
   {
      s = string_make_from_cstring( cp );

      // put the string into the return array
      if ( i_result < ( size - 1 ) )
      {
         result[i_result] = s;
         i_result = i_result + 1;
      }
      // resize the array if necessary
      else
      {
         result = ( string_t ** ) realloc( result, 2 * size * sizeof( string_t * ) );
         CHECK( "result reallocated correctly", result != NULL );
         memset( result + size, 0, sizeof( string_t * )*size );
         size = 2 * size;
         result[i_result] = s;
         i_result = i_result + 1;
      }

      cp = strtok_r( NULL, separators, &save_cp );
   }

   // deallocate temp string
   free( scopy );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   // return list
   *count = i_result;

   return result;
}


/**
   string_as_lower
*/

string_t *
string_as_lower( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   string_t *result = s_clone( current );
   char_t *cp1 = (*result).area;
   char_t *cp = (*current).area;
   int32_t n = (*result).count;

   for( i = 0; i < n; i++ )
   {
      cp1[i] = to_lowercase( cp[i] );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_as_upper
*/

string_t *
string_as_upper( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   string_t *result = s_clone( current );
   char_t *cp1 = (*result).area;
   char_t *cp = (*current).area;
   int32_t n = (*result).count;

   for( i = 0; i < n; i++ )
   {
      cp1[i] = to_uppercase( cp[i] );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_as_int64
*/

int64_t
string_as_int64( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int64_t value = 0;
   sscanf( (*current).area, "%ld", &value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   string_as_int32
*/

int32_t
string_as_int32( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t value = 0;
   sscanf( (*current).area, "%d", &value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   string_as_float64
*/

float64_t
string_as_float64( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   float64_t value = 0;
   sscanf( (*current).area, "%lf", &value );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return value;
}

/**
   string_put
*/

void
string_put( string_t *current, char_t c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*current).count ) ) );
   INVARIANT( current );

   // allow "put" into position following last character
   // if capacity is too small, increase it and zero last character
   if ( index == (*current).count )
   {
      if ( (*current).capacity == (*current).count + 1 )
      {
         (*current).area = ( char_t * ) realloc( (*current).area, (*current).capacity + 1 );
         CHECK( "(*current).area reallocated correctly", (*current).area != NULL );

         (*current).capacity = (*current).capacity + 1;
         (*current).area[ (*current).capacity - 1] = 0;
      }

      (*current).area[index] = c;
      (*current).hash_code_valid = 0;
      (*current).count = (*current).count + 1;
   }
   else
   {
      (*current).area[index] = c;
      (*current).hash_code_valid = 0;
   }

   POSTCONDITION( "item set", (*current).area[index] == c );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_replace
*/

void
string_replace
(
   string_t *current,
   string_t *substring,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "start index ok", ( ( start_index >= 0 ) && ( start_index < (*current).count ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < (*current).count ) ) );
   INVARIANT( current );

   // unlock substring
   LOCK( (*substring).mutex );

   int32_t i = 0;
   int32_t j = 0;
   int32_t n_s = (*current).count;
   int32_t n_sub = (*substring).count;
   char_t *cp_s = (*current).area;
   char_t *cp_sub = (*substring).area;

   // copy substring into string from start_index to end index
   // do not go past end of either string
   for(  i = start_index, j = 0;
         ( i <= end_index ) && ( i < n_s ) && ( j < n_sub );
         i++, j++
      )
   {
      cp_s[i] = cp_sub[j];
   }

   (*current).hash_code_valid = 0;

   // unlock substring
   UNLOCK( (*substring).mutex );

   POSTCONDITION( "substring set", strncmp( &(*current).area[start_index], (*substring).area, end_index - start_index + 1 ) == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_replace_cstring
*/

void
string_replace_cstring
(
   string_t *current,
   char_t *substring,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   LOCK( (*current).mutex );
   PRECONDITION( "start index ok", ( ( start_index >= 0 ) && ( start_index < (*current).count ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < (*current).count ) ) );
   INVARIANT( current );

   int32_t i = 0;
   int32_t j = 0;
   int32_t n_s = (*current).count;
   int32_t n_sub = strlen( substring );
   char_t *cp_s = (*current).area;
   char_t *cp_sub = substring;

   // copy substring into string from start_index to end index
   // do not go past end of either string
   for(  i = start_index, j = 0;
         ( i <= end_index ) && ( i < n_s ) && ( j < n_sub );
         i++, j++
      )
   {
      cp_s[i] = cp_sub[j];
   }

   (*current).hash_code_valid = 0;

   POSTCONDITION( "substring set", strncmp( &(*current).area[start_index], substring, end_index - start_index + 1 ) == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   string_replace_all
*/

void
string_replace_all
(
   string_t *current,
   string_t *substring_original,
   string_t *substring_new
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring_original not null", substring_original != NULL );
   PRECONDITION( "substring_original type OK", ( *substring_original )._type == STRING_TYPE );
   PRECONDITION( "substring_new not null", substring_new != NULL );
   PRECONDITION( "substring_new type OK", ( *substring_new )._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock substring_original and substring_new
   LOCK( ( *substring_original ).mutex );
   LOCK( ( *substring_new ).mutex );

   int32_t n_s = 0;
   int32_t n_orig = 0;
   int32_t n_new = 0;
   int32_t flag = 0;
   int32_t cp_s1_offset = 0;
   int32_t cp_offset = 0;

   char_t *cp = NULL;
   char_t *cp_s = NULL;
   char_t *cp_s1 = NULL;
   char_t *cp_orig = NULL;
   char_t *cp_new = NULL;

   cp_s = (*current).area;
   cp_s1 = (*current).area;
   cp_orig = ( *substring_original ).area;
   cp_new = ( *substring_new ).area;

   n_s = (*current).count;
   n_orig = ( *substring_original ).count;
   n_new = ( *substring_new ).count;

   while( 1 )
   {
      cp = strstr( cp_s1, cp_orig );

      if ( cp != NULL )
      {
         // increase capacity if necessary, zero newly allocated space
         if ( n_new > n_orig )
         {
            if ( (*current).capacity < n_s + n_new - n_orig  + 1 )
            {
               cp_offset = cp - cp_s;
               cp_s1_offset = cp_s1 - cp_s;

               (*current).area = ( char_t * ) realloc( cp_s, n_s + n_new - n_orig + 1 );
               CHECK( "(*current).area reallocated correctly", (*current).area != NULL );
               cp_s = (*current).area;
               (*current).capacity = n_s + n_new - n_orig + 1;

               memset( cp_s + n_s, 0, (*current).capacity - n_s );

               // adjust pointers if realloc moved (*current).area
               cp = cp_s + cp_offset;
               cp_s1 = cp_s + cp_s1_offset;
            }
         }

         // move part of string after orig to new spot
         memmove( cp + n_new, cp + n_orig, n_s - ( cp - cp_s ) - n_orig );
         // put new substring in its place
         memmove( cp, cp_new, n_new );

         // update count
         (*current).count = (*current).count + n_new - n_orig;
         n_s = (*current).count;

         // zero out area after if string is now shorter
         if ( n_new < n_orig )
         {
            memset( cp_s + n_s, 0, (*current).capacity - n_s );
         }

         // ensure string area still terminates with null character
         if ( n_orig < n_new )
         {
            cp_s[n_s] = 0;
         }

         // update cp_s1
         cp_s1 = cp + n_new;

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
   string_replace_all_cstring
*/

void
string_replace_all_cstring
(
   string_t *current,
   string_t *substring_original,
   char_t *substring_new
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring_original not null", substring_original != NULL );
   PRECONDITION( "substring_original type OK", ( *substring_original )._type == STRING_TYPE );
   PRECONDITION( "substring_new not null", substring_new != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock substring_original
   LOCK( ( *substring_original ).mutex );

   int32_t n_s = 0;
   int32_t n_orig = 0;
   int32_t n_new = 0;
   int32_t flag = 0;
   int32_t cp_s1_offset = 0;
   int32_t cp_offset = 0;

   char_t *cp = NULL;
   char_t *cp_s = NULL;
   char_t *cp_s1 = NULL;
   char_t *cp_orig = NULL;
   char_t *cp_new = NULL;

   cp_s = (*current).area;
   cp_s1 = (*current).area;
   cp_orig = ( *substring_original ).area;
   cp_new = substring_new;

   n_s = (*current).count;
   n_orig = ( *substring_original ).count;
   n_new = strlen( substring_new );

   while( 1 )
   {
      cp = strstr( cp_s1, cp_orig );

      if ( cp != NULL )
      {
         // increase capacity if necessary, zero newly allocated space
         if ( n_new > n_orig )
         {
            if ( (*current).capacity < n_s + n_new - n_orig  + 1 )
            {
               cp_offset = cp - cp_s;
               cp_s1_offset = cp_s1 - cp_s;

               (*current).area = ( char_t * ) realloc( cp_s, n_s + n_new - n_orig + 1 );
               CHECK( "(*current).area reallocated correctly", (*current).area != NULL );
               cp_s = (*current).area;
               (*current).capacity = n_s + n_new - n_orig + 1;

               memset( cp_s + n_s, 0, (*current).capacity - n_s );

               // adjust pointers if realloc moved (*current).area
               cp = cp_s + cp_offset;
               cp_s1 = cp_s + cp_s1_offset;
            }
         }

         // move part of string after orig to new spot
         memmove( cp + n_new, cp + n_orig, n_s - ( cp - cp_s ) - n_orig );
         // put new substring in its place
         memmove( cp, cp_new, n_new );

         // update count
         (*current).count = (*current).count + n_new - n_orig;
         n_s = (*current).count;

         // zero out area after if string is now shorter
         if ( n_new < n_orig )
         {
            memset( cp_s + n_s, 0, (*current).capacity - n_s );
         }

         // ensure string area still terminates with null character
         if ( n_orig < n_new )
         {
            cp_s[n_s] = 0;
         }

         // update cp_s1
         cp_s1 = cp + n_new;

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
   string_replace_all_cstring2
*/

void
string_replace_all_cstring2
(
   string_t *current,
   char_t *substring_original,
   char_t *substring_new
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring_original not null", substring_original != NULL );
   PRECONDITION( "substring_new not null", substring_new != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t n_s = 0;
   int32_t n_orig = 0;
   int32_t n_new = 0;
   int32_t flag = 0;
   int32_t cp_s1_offset = 0;
   int32_t cp_offset = 0;

   char_t *cp = NULL;
   char_t *cp_s = NULL;
   char_t *cp_s1 = NULL;
   char_t *cp_orig = NULL;
   char_t *cp_new = NULL;

   cp_s = (*current).area;
   cp_s1 = (*current).area;
   cp_orig = substring_original;
   cp_new = substring_new;

   n_s = (*current).count;
   n_orig = strlen( substring_original );
   n_new = strlen( substring_new );

   while( 1 )
   {
      cp = strstr( cp_s1, cp_orig );

      if ( cp != NULL )
      {
         // increase capacity if necessary, zero newly allocated space
         if ( n_new > n_orig )
         {
            if ( (*current).capacity < n_s + n_new - n_orig  + 1 )
            {
               cp_offset = cp - cp_s;
               cp_s1_offset = cp_s1 - cp_s;

               (*current).area = ( char_t * ) realloc( cp_s, n_s + n_new - n_orig + 1 );
               CHECK( "(*current).area reallocated correctly", (*current).area != NULL );
               cp_s = (*current).area;
               (*current).capacity = n_s + n_new - n_orig + 1;

               memset( cp_s + n_s, 0, (*current).capacity - n_s );

               // adjust pointers if realloc moved (*current).area
               cp = cp_s + cp_offset;
               cp_s1 = cp_s + cp_s1_offset;
            }
         }

         // move part of string after orig to new spot
         memmove( cp + n_new, cp + n_orig, n_s - ( cp - cp_s ) - n_orig );
         // put new substring in its place
         memmove( cp, cp_new, n_new );

         // update count
         (*current).count = (*current).count + n_new - n_orig;
         n_s = (*current).count;

         // zero out area after if string is now shorter
         if ( n_new < n_orig )
         {
            memset( cp_s + n_s, 0, (*current).capacity - n_s );
         }

         // ensure string area still terminates with null character
         if ( n_orig < n_new )
         {
            cp_s[n_s] = 0;
         }

         // update cp_s1
         cp_s1 = cp + n_new;

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
   string_append
*/

void
string_append( string_t *current, string_t *s )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "s not null", s != NULL );
   PRECONDITION( "s type OK", (*s)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   // lock s
   LOCK( (*s).mutex );

   int32_t count = 0;

   // make sure there's enough space in string
   if ( (*current).capacity < (*current).count + (*s).count + 1 )
   {
      (*current).area = ( char_t * ) realloc( (*current).area, (*current).count + (*s).count + 1 );
      CHECK( "(*current).area reallocated correctly", (*current).area != NULL );
      memset( &( (*current).area[ (*current).count ] ), 0, (*s).count + 1 );
      (*current).capacity = (*current).count + (*s).count + 1;
      count = (*current).count + (*s).count;
   }
   else
   {
      count = (*current).count + (*s).count;
   }

   // append s to string
   strcat( (*current).area, (*s).area );

   // set count
   (*current).count = count;

   if ( (*s).count > 0 )
   {
      (*current).hash_code_valid = 0;
   }

   POSTCONDITION( "string appended", strcmp( &(*current).area[i_pc], (*s).area ) == 0 );

   // unlock s
   UNLOCK( (*s).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_append_cstring
*/

void
string_append_cstring( string_t *current, char_t *s )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "s not null", s != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t i_pc = (*current).count; );

   int32_t count = 0;

   // make sure there's enough space in string
   if ( (*current).capacity < (*current).count + strlen( s ) + 1 )
   {
      (*current).area = ( char_t * ) realloc( (*current).area, (*current).count + strlen( s ) + 1 );
      CHECK( "(*current).area reallocated correctly", (*current).area != NULL );
      memset( &( (*current).area[ (*current).count ] ), 0, strlen( s ) + 1 );
      (*current).capacity = (*current).count + strlen( s ) + 1;
      count = (*current).count + strlen( s );
   }
   else
   {
      count = (*current).count + strlen( s );
   }

   // append s to string
   strcat( (*current).area, s );

   // set count
   (*current).count = count;

   if ( strlen( s ) > 0 )
   {
      (*current).hash_code_valid = 0;
   }

   POSTCONDITION( "string appended", strcmp( &(*current).area[i_pc], s ) == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   string_prepend
*/

void
string_prepend( string_t *current, string_t *s )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "s not null", s != NULL );
   PRECONDITION( "s type OK", (*s)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock s
   LOCK( (*s).mutex );

   int32_t count = 0;
   int32_t capacity = 0;

   // get capacity, count of result string
   if ( (*current).capacity < (*current).count + (*s).count + 1 )
   {
      capacity = (*current).count + (*s).count + 1;
      count = (*current).count + (*s).count;
   }
   else
   {
      capacity = (*current).capacity;
      count = (*current).count + (*s).count;
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
   (*current).count = count;

   if ( (*s).count > 0 )
   {
      (*current).hash_code_valid = 0;
   }

   POSTCONDITION( "string prepended", strncmp( (*current).area, (*s).area, (*s).count ) == 0 );

   // unlock s
   UNLOCK( (*s).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   string_prepend_cstring
*/

void
string_prepend_cstring( string_t *current, char_t *s )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "s not null", s != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = 0;
   int32_t capacity = 0;

   int32_t s_count = strlen( s );

   // get capacity, count of result string
   if ( (*current).capacity < (*current).count + s_count + 1 )
   {
      capacity = (*current).count + s_count + 1;
      count = (*current).count + s_count;
   }
   else
   {
      capacity = (*current).capacity;
      count = (*current).count + s_count;
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
   (*current).count = count;

   if ( s_count > 0 )
   {
      (*current).hash_code_valid = 0;
   }

   POSTCONDITION( "string prepended", strncmp( (*current).area, s, s_count ) == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   string_insert
*/

void
string_insert( string_t *current, string_t *substring, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring)._type == STRING_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*current).count ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // lock substring
   LOCK( (*substring).mutex );

   int32_t capacity = 0;
   char_t *cp = NULL;

   // get capacity, count of result string
   if ( (*current).capacity < (*current).count + (*substring).count + 1 )
   {
      capacity = (*current).count + (*substring).count + 1;
      (*current).area = ( char_t * ) realloc( (*current).area, capacity );
      CHECK( "(*current).area reallocated correctly", (*current).area != NULL );

      memset( &( (*current).area[ (*current).count ] ), 0, capacity - (*current).count );
      (*current).capacity = capacity;
   }
   else
   {
      capacity = (*current).capacity;
   }

   // move string contents after index back the size of substring
   cp = (*current).area;
   memmove( cp + index + (*substring).count, cp + index, (*current).count - index );

   // set substring in string
   memcpy( cp + index, (*substring).area, (*substring).count * sizeof( char_t ) );
   (*current).count = (*current).count + (*substring).count;

   if ( (*substring).count > 0 )
   {
      (*current).hash_code_valid = 0;
   }

   POSTCONDITION( "string inserted", strncmp( &(*current).area[index], (*substring).area, (*substring).count ) == 0 );

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   string_insert_cstring
*/

void
string_insert_cstring( string_t *current, char_t *substring, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*current).count ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t capacity = 0;
   char_t *cp = NULL;

   int32_t substring_count = strlen( substring );

   // get capacity, count of result string
   if ( (*current).capacity < (*current).count + substring_count + 1 )
   {
      capacity = (*current).count + substring_count + 1;
      (*current).area = ( char_t * ) realloc( (*current).area, capacity );
      CHECK( "(*current).area reallocated correctly", (*current).area != NULL );

      memset( &( (*current).area[ (*current).count ] ), 0, capacity - (*current).count );
      (*current).capacity = capacity;
   }
   else
   {
      capacity = (*current).capacity;
   }

   // move string contents after index back the size of substring
   cp = (*current).area;
   memmove( cp + index + substring_count, cp + index, (*current).count - index );

   // set substring in string
   memcpy( cp + index, substring, substring_count * sizeof( char_t ) );
   (*current).count = (*current).count + substring_count;

   if ( substring_count > 0 )
   {
      (*current).hash_code_valid = 0;
   }

   POSTCONDITION( "string inserted", strncmp( &(*current).area[index], substring, substring_count ) == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}


/**
   string_append_character
*/

void
string_append_character( string_t *current, char_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = 0;
   int32_t capacity = 0;
   char_t *cp = NULL;

   // get capacity, count of result string
   if ( (*current).capacity < (*current).count + 2 )
   {
      capacity = (*current).count + 2;
      count = (*current).count + 1;
      (*current).area = ( char_t * ) realloc( (*current).area, capacity );
      CHECK( "(*current).area reallocated correctly", (*current).area != NULL );
      (*current).capacity = capacity;
   }
   else
   {
      capacity = (*current).capacity;
      count = (*current).count + 1;
   }

   // set character in string
   cp = (*current).area;
   cp[count - 1] = c;
   cp[count] = 0;
   (*current).count = (*current).count + 1;

   (*current).hash_code_valid = 0;

   POSTCONDITION( "character appended", (*current).area[(*current).count - 1] == c );
   POSTCONDITION( "null terminated", (*current).area[(*current).count] == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_prepend_character
*/

void
string_prepend_character( string_t *current, char_t c )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = 0;
   int32_t capacity = 0;
   char_t *cp = NULL;

   // get capacity, count of result string
   if ( (*current).capacity < (*current).count + 2 )
   {
      capacity = (*current).count + 2;
      count = (*current).count + 1;
      (*current).area = ( char_t * ) realloc( (*current).area, capacity );
      CHECK( "(*current).area reallocated correctly", (*current).area != NULL );

      (*current).capacity = capacity;
   }
   else
   {
      capacity = (*current).capacity;
      count = (*current).count + 1;
   }

   // move string contents back one
   cp = (*current).area;
   memmove( cp + 1, cp, count );

   // set character in string
   cp[0] = c;
   cp[count] = 0;
   (*current).count = (*current).count + 1;

   (*current).hash_code_valid = 0;

   POSTCONDITION( "character prepended", (*current).area[0] == c );
   POSTCONDITION( "null terminated", (*current).area[(*current).count] == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_insert_character
*/

void
string_insert_character( string_t *current, char_t c, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*current).count ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t count = 0;
   int32_t capacity = 0;
   char_t *cp = NULL;

   // get capacity, count of result string
   if ( (*current).capacity < (*current).count + 2 )
   {
      capacity = (*current).count + 2;
      count = (*current).count + 1;
      (*current).area = ( char_t * ) realloc( (*current).area, capacity );
      CHECK( "(*current).area reallocated correctly", (*current).area != NULL );

      (*current).capacity = capacity;
   }
   else
   {
      capacity = (*current).capacity;
      count = (*current).count + 1;
   }

   // move string contents after index back one
   cp = (*current).area;
   memmove( cp + index + 1, cp + index, count - index );

   // set character in string
   cp[index] = c;
   (*current).count = (*current).count + 1;

   (*current).hash_code_valid = 0;

   POSTCONDITION( "character inserted", (*current).area[index] == c );
   POSTCONDITION( "null terminated", (*current).area[(*current).count] == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_insert_int32
*/

void
string_insert_int32( string_t *current, int32_t i, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*current).count ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t capacity = 0;
   char_t *cp = NULL;
   int32_t s_i_count = 0;
   char_t *s_i = calloc( 120, sizeof( char_t ) );
   CHECK( "s_i allocated correctly", s_i != NULL );

   // make stringified version of integer
   s_i_count = sprintf( s_i, "%d", i );

   // get capacity, count of result string
   if ( (*current).capacity < (*current).count + s_i_count + 1 )
   {
      capacity = (*current).count + s_i_count + 1;
      (*current).area = ( char_t * ) realloc( (*current).area, capacity );
      CHECK( "(*current).are reallocated correctly", (*current).area != NULL );
      (*current).capacity = capacity;
   }
   else
   {
      capacity = (*current).capacity;
   }

   // move string contents after index back the size of integer string
   cp = (*current).area;
   memmove( cp + index + s_i_count, cp + index, (*current).count - index );

   // set substring in string
   memcpy( cp + index, s_i, s_i_count * sizeof( char_t ) );
   (*current).count = (*current).count + s_i_count;
   cp[ (*current).count ] = 0;

   // free temp string
   free( s_i );

   (*current).hash_code_valid = 0;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_insert_float64
*/

void
string_insert_float64( string_t *current, float64_t f, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*current).count ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t capacity = 0;
   char_t *cp = NULL;
   int32_t s_f_count = 0;
   char_t *s_f = calloc( 120, sizeof( char_t ) );
   CHECK( "s_f allocated correctly", s_f != NULL );

   // make stringified version of integer
   s_f_count = sprintf( s_f, "%lf", f );

   // get capacity, count of result string
   if ( (*current).capacity < (*current).count + s_f_count + 1 )
   {
      capacity = (*current).count + s_f_count + 1;
      (*current).area = ( char_t * ) realloc( (*current).area, capacity );
      CHECK( "(*current).are reallocated correctly", (*current).area != NULL );
      (*current).capacity = capacity;
   }
   else
   {
      capacity = (*current).capacity;
   }

   // move string contents after index back the size of integer string
   cp = (*current).area;
   memmove( cp + index + s_f_count, cp + index, (*current).count - index );

   // set substring in string
   memcpy( cp + index, s_f, s_f_count * sizeof( char_t ) );
   (*current).count = (*current).count + s_f_count;
   cp[ (*current).count ] = 0;

   // free temp string
   free( s_f );

   (*current).hash_code_valid = 0;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}



/**
   string_to_lower
*/

void
string_to_lower( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   char_t *cp = (*current).area;
   int32_t n = (*current).count;

   for( i = 0; i < n; i++ )
   {
      cp[i] = to_lowercase( cp[i] );
   }

   (*current).hash_code_valid = 0;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_to_lower_by_index
*/

void
string_to_lower_by_index( string_t *current, int32_t start_index, int32_t end_index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "start index ok", ( ( start_index >= 0 ) && ( start_index < (*current).count ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < (*current).count ) ) );
   PRECONDITION( "indices ok", start_index <= end_index  );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   char_t *cp = (*current).area;

   for( i = start_index; i <= end_index; i++ )
   {
      cp[i] = to_lowercase( cp[i] );
   }

   (*current).hash_code_valid = 0;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_to_upper
*/

void
string_to_upper( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   char_t *cp = (*current).area;
   int32_t n = (*current).count;

   for( i = 0; i < n; i++ )
   {
      cp[i] = to_uppercase( cp[i] );
   }

   (*current).hash_code_valid = 0;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_to_upper_by_index
*/

void
string_to_upper_by_index( string_t *current, int32_t start_index, int32_t end_index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "start index ok", ( ( start_index >= 0 ) && ( start_index < (*current).count ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < (*current).count ) ) );
   PRECONDITION( "indices ok", start_index <= end_index  );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t i = 0;
   char_t *cp = (*current).area;

   for( i = start_index; i <= end_index; i++ )
   {
      cp[i] = to_uppercase( cp[i] );
   }

   (*current).hash_code_valid = 0;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_substring
*/

string_t *
string_substring( string_t *current, int32_t start_index, int32_t end_index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*current).count ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < (*current).count ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_make_n( end_index - start_index + 2 );
   char_t *cp = (*current).area;
   memcpy( (*result).area, cp + start_index, end_index - start_index + 1 );
   (*result).count = end_index - start_index + 1;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   string_remove
*/

void
string_remove( string_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*current).count ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t n_pc = (*current).count; );

   char_t *cp = NULL;

   // move string contents after index forward one
   cp = (*current).area;
   memmove( cp + index, cp + index + 1, (*current).count - index );

   // set count
   (*current).count = (*current).count - 1;
   cp[ (*current).count ] = 0;

   (*current).hash_code_valid = 0;

   POSTCONDITION( "count decremented", (*current).count == n_pc - 1 );
   POSTCONDITION( "null terminated", (*current).area[(*current).count] == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_remove_substring
*/

void
string_remove_substring( string_t *current, int32_t start_index, int32_t end_index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*current).count ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < (*current).count ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t n_pc = (*current).count; );

   char_t *cp = NULL;

   // move string contents after index forward
   cp = (*current).area;
   memmove( cp + start_index, cp + end_index + 1, (*current).count - end_index - 1 );

   // set count
   (*current).count = (*current).count - end_index + start_index - 1;
   cp[ (*current).count ] = 0;

   (*current).hash_code_valid = 0;

   POSTCONDITION( "count decremented", (*current).count == n_pc - end_index + start_index - 1 );
   POSTCONDITION( "null terminated", (*current).area[(*current).count] == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_keep_head
*/

void
string_keep_head( string_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );
   PRECONDITION( "count ok", (*current).count >= count );

   // set new end
   (*current).area[count] = 0;
   (*current).count = count;

   (*current).hash_code_valid = 0;

   POSTCONDITION( "count set", (*current).count == count );
   POSTCONDITION( "null terminated", (*current).area[(*current).count] == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_remove_head
*/

void
string_remove_head( string_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", (*current).count >= count );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t n_pc = (*current).count; );

   char_t *cp = NULL;

   // move string contents after count forward
   cp = (*current).area;
   memmove( cp, cp + count, (*current).count - count );
   cp[(*current).count - count] = 0;
   (*current).count = (*current).count - count;

   (*current).hash_code_valid = 0;

   POSTCONDITION( "count set", (*current).count == n_pc - count );
   POSTCONDITION( "null terminated", (*current).area[(*current).count] == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_keep_tail
*/

void
string_keep_tail( string_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", (*current).count >= count );
   INVARIANT( current );

   char_t *cp = NULL;

   // move string contents after (*current).count - count forward
   cp = (*current).area;
   memmove( cp, cp + (*current).count - count, count );
   cp[count] = 0;
   (*current).count = count;

   (*current).hash_code_valid = 0;

   POSTCONDITION( "count set", (*current).count == count );
   POSTCONDITION( "null terminated", (*current).area[(*current).count] == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_remove_tail
*/

void
string_remove_tail( string_t *current, int32_t count )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "count ok", (*current).count >= count );
   INVARIANT( current );
   POSTCONDITION_VARIABLE_DEFINE( int32_t n_pc = (*current).count; );

   // set new end
   (*current).area[ (*current).count - count] = 0;
   (*current).count = (*current).count - count;

   (*current).hash_code_valid = 0;

   POSTCONDITION( "count set", (*current).count == n_pc - count );
   POSTCONDITION( "null terminated", (*current).area[(*current).count] == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_remove_leading_whitespace
*/

void
string_remove_leading_whitespace( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *cp = NULL;
   int32_t flag = 0;

   // move string contents after remove whitespace character forward
   cp = (*current).area;

   while( is_whitespace( cp[0] ) == 1 )
   {
      memmove( cp, cp + 1, (*current).count - 1 );
      cp[(*current).count - 1] = 0;
      (*current).count = (*current).count - 1;
      flag = 1;
   }

   if ( flag == 1 )
   {
      (*current).hash_code_valid = 0;
   }

   POSTCONDITION( "null terminated", (*current).area[(*current).count] == 0 );

   UNLOCK( (*current).mutex );

   return;
}

/**
   string_remove_trailing_whitespace
*/

void
string_remove_trailing_whitespace( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   char_t *cp = NULL;
   int32_t flag = 0;

   // move string contents after remove whitespace character forward
   cp = (*current).area;

   while( is_whitespace( cp[ (*current).count - 1 ] ) == 1 )
   {
      cp[(*current).count - 1] = 0;
      (*current).count = (*current).count - 1;
      flag = 1;
   }

   if ( flag == 1 )
   {
      (*current).hash_code_valid = 0;
   }

   POSTCONDITION( "null terminated", (*current).area[(*current).count] == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_wipe_out
*/

void
string_wipe_out( string_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   // set to empty string
   (*current).area[0] = 0;
   (*current).count = 0;

   (*current).hash_code_valid = 0;

   POSTCONDITION( "string empty", (*current).count == 0 );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   string_resize
*/

void
string_resize( string_t *current, int32_t new_capacity )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == STRING_TYPE );
   LOCK( (*current).mutex );
   PRECONDITION( "capacity ok", new_capacity > (*current).count );
   INVARIANT( current );

   // don't reduce capacity below what is required to store the content
   if ( new_capacity > (*current).count )
   {
      // make new capacity at least 4 characters
      if ( new_capacity < STRING_MIN_SIZE )
      {
         new_capacity = STRING_MIN_SIZE;
      }

      // set new capacity
      (*current).area = ( char_t * ) realloc( (*current).area, new_capacity );
      CHECK( "(*current).are reallocated correctly", (*current).area != NULL );
      (*current).capacity = new_capacity;
   }

   POSTCONDITION( "capacity set", (*current).capacity == new_capacity );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

