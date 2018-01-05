/**
 @file String.c
 @author Greg Lee
 @version 1.0.0
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

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

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

#define STRING_TYPE 0xA5000500
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
   string structure
*/

struct string_struct
{
   int32_t type;
   
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
area_not_null( string_t *p )
{
   int32_t result = 1;

   result = ( (*p).area != NULL );

   return result;
}

static
int32_t 
nonnegative_count( string_t *p )
{
   int32_t result = 1;

   result = ( (*p).count >= 0 );

   return result;
}

static
int32_t 
valid_count( string_t *p )
{
   int32_t result = 1;

   result = ( (*p).count == strlen( (*p).area ) );

   return result;
}

static
int32_t 
capacity_ok( string_t *p )
{
   int32_t result = 1;

   result = ( (*p).capacity > (*p).count );

   return result;
}

static
int32_t 
hash_ok( string_t *p )
{
   int32_t result = 1;

   if ( (*p).hash_code_valid == 1 )
   {
      result = ( (*p).hash_code == get_hash( (*p).area, (*p).count ) );
   }

   return result;
}

static
void invariant( string_t *p )
{
   assert(((void) "area not null", area_not_null( p ) ));
   assert(((void) "nonnegative count", nonnegative_count( p ) ));
   assert(((void) "valid count", valid_count( p ) ));
   assert(((void) "capacity ok", capacity_ok( p ) ));
   assert(((void) "hash code ok", hash_ok( p ) ));
   return;
}

#endif

/**
   s_copy
*/

static
string_t *
s_copy( string_t *string )
{
   string_t *result = string_make_n( (*string).count + 1 );
   strcpy( (*result).area, (*string).area );
   (*result).count = (*string).count;
   (*result).capacity = (*string).count + 1;
   (*result).hash_code_valid = (*string).hash_code_valid;
   (*result).hash_code = (*string).hash_code;

   return result;
}

/**
   string_make
*/

string_t *
string_make( void )
{
   // allocate string struct
   string_t * string = ( string_t * ) calloc( 1, sizeof( string_t ) );

   // set type
   (*string).type = STRING_TYPE;
   
   // allocate area
   (*string).area = ( char * ) calloc( STRING_MIN_SIZE, sizeof( char_t ) );

   // set count
   (*string).count = 0;

   // set capacity
   (*string).capacity = 1;

   // set hash_code
   (*string).hash_code = 0;

   // set hash_code_valid
   (*string).hash_code_valid = 0;

   MULTITHREAD_MUTEX_INIT( (*string).mutex );

   INVARIANT( string );

   return string;
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
   string_t * string = ( string_t * ) calloc( 1, sizeof( string_t ) );

   // set type
   (*string).type = STRING_TYPE;
   
   if ( capacity > STRING_MIN_SIZE )
   {
      real_capacity = capacity;
   }
   
   // allocate area
   (*string).area = ( char * ) calloc( real_capacity, sizeof( char_t ) );

   // set count
   (*string).count = 0;

   // set capacity
   (*string).capacity = real_capacity;

   // set hash_code
   (*string).hash_code = 0;

   // set hash_code_valid
   (*string).hash_code_valid = 0;

   MULTITHREAD_MUTEX_INIT( (*string).mutex );

   INVARIANT( string );
   POSTCONDITION( "capacity set", (*string).capacity == real_capacity );

   return string;
}

/**
   string_make_from
*/

string_t *
string_make_from( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );

   // get copy of input 
   LOCK( (*string).mutex );

   // allocate string struct
   string_t * result = ( string_t * ) calloc( 1, sizeof( string_t ) );

   // set type
   (*result).type = STRING_TYPE;
   
   // set area
   (*result).area = ( char * ) calloc( (*string).capacity, sizeof( char_t ) );
   strncpy( (*result).area, (*string).area, (*string).count );

   // set count
   (*result).count = (*string).count;

   // set capacity
   (*result).capacity = (*string).capacity;

   // set hash_code
   (*result).hash_code = (*string).hash_code;

   // set hash_code_valid
   (*result).hash_code_valid = (*string).hash_code_valid;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   // dispose of copy
   UNLOCK( (*string).mutex );

   INVARIANT( result );
   POSTCONDITION( "size set", (*result).count == (*string).count );
   POSTCONDITION( "area set", strcmp( (*result).area, (*string).area ) == 0 );

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
   string_t * string = ( string_t * ) calloc( 1, sizeof( string_t ) );

   // set type
   (*string).type = STRING_TYPE;
   
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
   (*string).area = ( char * ) calloc( real_capacity, sizeof( char_t ) );
   strncpy( (*string).area, str, n );

   // set count
   (*string).count = n;

   // set capacity
   (*string).capacity = real_capacity;

   // set hash_code
   (*string).hash_code = 0;

   // set hash_code_valid
   (*string).hash_code_valid = 0;

   MULTITHREAD_MUTEX_INIT( (*string).mutex );

   INVARIANT( string );
   POSTCONDITION( "size set", (*string).count == strlen( str ) );
   POSTCONDITION( "area set", strcmp( (*string).area, str ) == 0 );

   return string;
}

/**
   string_dispose
*/

void
string_dispose( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   MULTITHREAD_MUTEX_DESTROY( (*string).mutex );

   // delete string struct
   free( string );

   return;
}


/**
   string_dispose_with_contents
*/

void
string_dispose_with_contents( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   // delete string items
   free( (*string).area );

   MULTITHREAD_MUTEX_DESTROY( (*string).mutex );

   // delete string struct
   free( string );

   return;
}


/**
   string_item
*/

char_t
string_item( string_t *string, int32_t index )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*string).count ) ) );
   INVARIANT( string );

   char_t result = (*string).area[index];

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_as_cstring
*/

char_t *
string_as_cstring( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   char_t *result = (*string).area;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_count
*/

int32_t
string_count( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t result = (*string).count;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_capacity
*/

int32_t
string_capacity( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t result =  (*string).capacity;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_is_empty
*/

int32_t
string_is_empty( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t result = ( (*string).count == 0 );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_valid_index
*/

int32_t
string_valid_index( string_t *string, int32_t index )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t result = ( index >=0 ) && ( index < (*string).count );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_has
*/

int32_t
string_has( string_t *string, char_t c )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t i = 0;
   int32_t result = 0;

   // search string for character c, stop if found
   for( i = 0; i < (*string).count; i++ )
   {
      if ( (*string).area[i] == c )
      {
         result = 1;
         break;
      }
   }

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_is_int32
*/

int32_t
string_is_int32( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t args_parsed = 0;
   int32_t value = 0;
   args_parsed = sscanf( (*string).area, "%d", &value );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return ( args_parsed == 1 );
}

/**
   string_is_float64
*/

int32_t
string_is_float64( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t args_parsed = 0;
   float64_t value = 0;
   args_parsed = sscanf( (*string).area, "%lf", &value );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return ( args_parsed == 1 );
}

/**
   string_hash_code
*/

int32_t
string_hash_code( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   if ( (*string).hash_code_valid == 0 )
   {
      (*string).hash_code = get_hash( (*string).area, (*string).count );
      (*string).hash_code_valid = 1;
   }

   int32_t result = (*string).hash_code;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_is_equal
*/

int32_t
string_is_equal( string_t *s1, string_t *s2 )
{
   PRECONDITION( "s1 not null", s1 != NULL );
   PRECONDITION( "s1 type OK", (*s1).type == STRING_TYPE );
   PRECONDITION( "s2 not null", s2 != NULL );
   PRECONDITION( "s2 type OK", (*s2).type == STRING_TYPE );
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
   string_is_equal_cstring
*/

int32_t
string_is_equal_cstring( string_t *s1, char_t *s2 )
{
   PRECONDITION( "s1 not null", s1 != NULL );
   PRECONDITION( "s1 type OK", (*s1).type == STRING_TYPE );
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
   string_is_less_than
*/

int32_t
string_is_less_than( string_t *s1, string_t *s2 )
{
   PRECONDITION( "s1 not null", s1 != NULL );
   PRECONDITION( "s1 type OK", (*s1).type == STRING_TYPE );
   PRECONDITION( "s2 not null", s2 != NULL );
   PRECONDITION( "s2 type OK", (*s2).type == STRING_TYPE );
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
   string_is_less_than_cstring
*/

int32_t
string_is_less_than_cstring( string_t *s1, char_t *s2 )
{
   PRECONDITION( "s1 not null", s1 != NULL );
   PRECONDITION( "s1 type OK", (*s1).type == STRING_TYPE );
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
   string_is_greater_than
*/

int32_t
string_is_greater_than( string_t *s1, string_t *s2 )
{
   PRECONDITION( "s1 not null", s1 != NULL );
   PRECONDITION( "s1 type OK", (*s1).type == STRING_TYPE );
   PRECONDITION( "s2 not null", s2 != NULL );
   PRECONDITION( "s2 type OK", (*s2).type == STRING_TYPE );
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
   string_is_greater_than_cstring
*/

int32_t
string_is_greater_than_cstring( string_t *s1, char_t *s2 )
{
   PRECONDITION( "s1 not null", s1 != NULL );
   PRECONDITION( "s1 type OK", (*s1).type == STRING_TYPE );
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
   string_has_substring
*/

int32_t
string_has_substring( string_t *string, string_t *substring )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   // unlock substring
   LOCK( (*substring).mutex );

   char_t *cp = NULL;

   cp = strstr( (*string).area, (*substring).area );

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return ( cp != NULL );
}

/**
   string_has_substring_cstring
*/

int32_t
string_has_substring_cstring( string_t *string, char_t *substring )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   LOCK( (*string).mutex );
   INVARIANT( string );

   char_t *cp = NULL;

   cp = strstr( (*string).area, substring );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return ( cp != NULL );
}

/**
   string_starts_with
*/

int32_t
string_starts_with( string_t *string, string_t *substring )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   // unlock substring
   LOCK( (*substring).mutex );

   char_t *cp = NULL;

   cp = strstr( (*string).area, (*substring).area );

   int32_t result = ( cp == (*string).area );

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_starts_with_cstring
*/

int32_t
string_starts_with_cstring( string_t *string, char_t *substring )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   LOCK( (*string).mutex );
   INVARIANT( string );

   char_t *cp = NULL;

   cp = strstr( (*string).area, substring );

   int32_t result = ( cp == (*string).area );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_ends_with
*/

int32_t
string_ends_with( string_t *string, string_t *substring )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   // unlock substring
   LOCK( (*substring).mutex );

   int32_t result = 0;
   char_t *cp = NULL;

   if ( (*substring).count <= (*string).count )
   {
      cp = strstr( (*string).area + ( (*string).count - (*substring).count ), (*substring).area );
      result = ( cp == (*string).area + ( (*string).count - (*substring).count ) );
   }
   
   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

int32_t
string_ends_with_cstring( string_t *string, char_t *substring )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t result = 0;
   char_t *cp = NULL;

   int32_t substring_length = strlen( substring );

   if ( substring_length <= (*string).count )
   {
      cp = strstr( (*string).area + ( (*string).count - substring_length ), substring );
      result = ( cp == (*string).area + ( (*string).count - substring_length ) );
   }

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_substring_index_in_bounds
*/

int32_t
string_substring_index_in_bounds
(
   string_t *string,
   string_t *substring,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring).type == STRING_TYPE );
   PRECONDITION( "start index ok", ( ( start_index >= 0 ) && ( start_index < (*string).count ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < (*string).count ) ) );
   LOCK( (*string).mutex );
   INVARIANT( string );

   // lock substring
   LOCK( (*substring).mutex );

   char_t *cp = NULL;
   int32_t result = 0;

   cp = strstr( (*string).area + start_index, (*substring).area );
   if ( cp != NULL )
   {
      result = cp - (*string).area;
   }

   if ( ( cp == NULL ) || ( result < start_index ) || ( result > end_index ) )
   {
      result = -1;
   }

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_substring_index_in_bounds_cstring
*/

int32_t
string_substring_index_in_bounds_cstring
(
   string_t *string,
   char_t *substring,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "start index ok", ( ( start_index >= 0 ) && ( start_index < (*string).count ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < (*string).count ) ) );
   LOCK( (*string).mutex );
   INVARIANT( string );

   char_t *cp = NULL;
   int32_t result = 0;

   cp = strstr( (*string).area + start_index, substring );
   if ( cp != NULL )
   {
      result = cp - (*string).area;
   }

   if ( ( cp == NULL ) || ( result < start_index ) || ( result > end_index ) )
   {
      result = -1;
   }

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}


/**
   string_substring_index
*/

int32_t
string_substring_index
(
   string_t *string,
   string_t *substring
)
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   // lock substring
   LOCK( (*substring).mutex );

   char_t *cp = NULL;
   int32_t result = 0;

   cp = strstr( (*string).area, (*substring).area );

   if ( cp == NULL )
   {
      result = -1;
   }
   else
   {
      result = cp - (*string).area;
   }

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_substring_index_cstring
*/

int32_t
string_substring_index_cstring
(
   string_t *string,
   char_t *substring
)
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring not null", string != NULL );
   LOCK( (*string).mutex );
   INVARIANT( string );

   char_t *cp = NULL;
   int32_t result = 0;

   cp = strstr( (*string).area, substring );

   if ( cp == NULL )
   {
      result = -1;
   }
   else
   {
      result = cp - (*string).area;
   }

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

#define DEFAULT_SPLIT_RETURN_ARRAY_SIZE 8

/**
   string_split
*/

string_t **
string_split( string_t *string, string_t *separators, int32_t *count )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "separators not null", separators != NULL );
   PRECONDITION( "separators type OK", (*separators).type == STRING_TYPE );
   PRECONDITION( "count ok", count != NULL );
   LOCK( (*string).mutex );
   INVARIANT( string );

   // lock separators
   LOCK( (*separators).mutex );

   char_t *scopy = NULL;
   char_t *cp;
   string_t **result = NULL;
   int32_t i_result = 0;
   string_t *s = NULL;
   int32_t size = DEFAULT_SPLIT_RETURN_ARRAY_SIZE;

   // allocate array to return
   result = ( string_t ** ) calloc( size, sizeof( string_t * ) );

   // allocate and fill temp string
   scopy = ( char_t * ) calloc( (*string).count + 1, sizeof( char_t ) );
   strcpy( scopy, (*string).area );

   // split scopy into tokens, make into strings, put into return array
   cp = strtok( scopy, (*separators).area );

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
         result = ( string_t ** ) realloc( result, 2*size*sizeof( string_t * ) );
         memset( result + size, 0, sizeof( string_t * )*size );
         size = 2*size;
         result[i_result] = s;
         i_result = i_result + 1;
      }

      cp = strtok( NULL, (*separators).area );
   }

   // deallocate temp string
   free( scopy );

   // unlock separators
   UNLOCK( (*separators).mutex );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   // return list
   *count = i_result;

   return result;
}


/**
   string_split_cstring
*/

string_t **
string_split_cstring( string_t *string, char_t *separators, int32_t *count )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "separators not null", separators != NULL );
   PRECONDITION( "count ok", count != NULL );
   LOCK( (*string).mutex );
   INVARIANT( string );

   char_t *scopy = NULL;
   char_t *cp;
   string_t **result = NULL;
   int32_t i_result = 0;
   string_t *s = NULL;
   int32_t size = DEFAULT_SPLIT_RETURN_ARRAY_SIZE;

   // allocate array to return
   result = ( string_t ** ) calloc( size, sizeof( string_t * ) );

   // allocate and fill temp string
   scopy = ( char_t * ) calloc( (*string).count + 1, sizeof( char_t ) );
   strcpy( scopy, (*string).area );

   // split scopy into tokens, make into strings, put into return array
   cp = strtok( scopy, separators );

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
         result = ( string_t ** ) realloc( result, 2*size*sizeof( string_t * ) );
         memset( result + size, 0, sizeof( string_t * )*size );
         size = 2*size;
         result[i_result] = s;
         i_result = i_result + 1;
      }

      cp = strtok( NULL, separators );
   }

   // deallocate temp string
   free( scopy );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   // return list
   *count = i_result;

   return result;
}


/**
   string_as_lower
*/

string_t *
string_as_lower( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t i = 0;
   string_t *result = s_copy( string );
   char_t *cp1 = (*result).area;
   char_t *cp = (*string).area;
   int32_t n = (*result).count;

   for( i = 0; i < n; i++ )
   {
      cp1[i] = to_lowercase( cp[i] );
   }

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_as_upper
*/

string_t *
string_as_upper( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t i = 0;
   string_t *result = s_copy( string );
   char_t *cp1 = (*result).area;
   char_t *cp = (*string).area;
   int32_t n = (*result).count;

   for( i = 0; i < n; i++ )
   {
      cp1[i] = to_uppercase( cp[i] );
   }

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_as_int32
*/

int32_t
string_as_int32( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t value = 0;
   sscanf( (*string).area, "%d", &value );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return value;
}

/**
   string_as_float64
*/

float64_t
string_as_float64( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   float64_t value = 0;
   sscanf( (*string).area, "%lf", &value );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return value;
}

/**
   string_put
*/

void
string_put( string_t *string, char_t c, int32_t index )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*string).count ) ) );
   INVARIANT( string );

   // allow "put" into position following last character
   // if capacity is too small, increase it and zero last character
   if ( index == (*string).count )
   {
      if ( (*string).capacity == (*string).count + 1 )
      {
         (*string).area = ( char_t * ) realloc( (*string).area, (*string).capacity + 1 );
         (*string).capacity = (*string).capacity + 1;
         (*string).area[ (*string).capacity - 1] = 0;
      }
      
      (*string).area[index] = c;
      (*string).hash_code_valid = 0;
      (*string).count = (*string).count + 1;
   }
   else
   {
      (*string).area[index] = c;
      (*string).hash_code_valid = 0;
   }
   
   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_replace
*/

void
string_replace
(
   string_t *string,
   string_t *substring,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring).type == STRING_TYPE );
   LOCK( (*string).mutex );
   PRECONDITION( "start index ok", ( ( start_index >= 0 ) && ( start_index < (*string).count ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < (*string).count ) ) );
   INVARIANT( string );

   // unlock substring
   LOCK( (*substring).mutex );

   int32_t i = 0;
   int32_t j = 0;
   int32_t n_s = (*string).count;
   int32_t n_sub = (*substring).count;
   char_t *cp_s = (*string).area;
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

   (*string).hash_code_valid = 0;

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_replace_cstring
*/

void
string_replace_cstring
(
   string_t *string,
   char_t *substring,
   int32_t start_index,
   int32_t end_index
)
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   LOCK( (*string).mutex );
   PRECONDITION( "start index ok", ( ( start_index >= 0 ) && ( start_index < (*string).count ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < (*string).count ) ) );
   INVARIANT( string );

   int32_t i = 0;
   int32_t j = 0;
   int32_t n_s = (*string).count;
   int32_t n_sub = strlen( substring );
   char_t *cp_s = (*string).area;
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

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}


/**
   string_replace_all
*/

void
string_replace_all
(
   string_t *string,
   string_t *substring_original,
   string_t *substring_new
)
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring_original not null", substring_original != NULL );
   PRECONDITION( "substring_original type OK", (*substring_original).type == STRING_TYPE );
   PRECONDITION( "substring_new not null", substring_new != NULL );
   PRECONDITION( "substring_new type OK", (*substring_new).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   // lock substring_original and substring_new 
   LOCK( (*substring_original).mutex );
   LOCK( (*substring_new).mutex );

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

   cp_s = (*string).area;
   cp_s1 = (*string).area;
   cp_orig = (*substring_original).area;
   cp_new = (*substring_new).area;

   n_s = (*string).count;
   n_orig = (*substring_original).count;
   n_new = (*substring_new).count;

   while( 1 )
   {
      cp = strstr( cp_s1, cp_orig );

      if ( cp != NULL )
      {
         // increase capacity if necessary, zero newly allocated space
         if ( n_new > n_orig )
         {
            if ( (*string).capacity < n_s + n_new - n_orig  + 1)
            {
               cp_offset = cp - cp_s;
               cp_s1_offset = cp_s1 - cp_s;

               (*string).area = ( char_t * ) realloc( cp_s, n_s + n_new - n_orig + 1 );
               cp_s = (*string).area;
               (*string).capacity = n_s + n_new - n_orig + 1;

               memset( cp_s + n_s, 0, (*string).capacity - n_s );

               // adjust pointers if realloc moved (*string).area
               cp = cp_s + cp_offset;
               cp_s1 = cp_s + cp_s1_offset;
            }
         }

         // move part of string after orig to new spot
         memmove( cp + n_new, cp + n_orig, n_s - ( cp - cp_s) - n_orig );
         // put new substring in its place
         memmove( cp, cp_new, n_new );

         // update count
         (*string).count = (*string).count + n_new - n_orig;
         n_s = (*string).count;

         // zero out area after if string is now shorter
         if ( n_new < n_orig )
         {
            memset( cp_s + n_s, 0, (*string).capacity - n_s );
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
      (*string).hash_code_valid = 0;
   }

   // unlock substring_original and substring_new 
   UNLOCK( (*substring_original).mutex );
   UNLOCK( (*substring_new).mutex );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}


/**
   string_replace_all_cstring
*/

void
string_replace_all_cstring
(
   string_t *string,
   string_t *substring_original,
   char_t *substring_new
)
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring_original not null", substring_original != NULL );
   PRECONDITION( "substring_original type OK", (*substring_original).type == STRING_TYPE );
   PRECONDITION( "substring_new not null", substring_new != NULL );
   LOCK( (*string).mutex );
   INVARIANT( string );

   // lock substring_original
   LOCK( (*substring_original).mutex );

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

   cp_s = (*string).area;
   cp_s1 = (*string).area;
   cp_orig = (*substring_original).area;
   cp_new = substring_new;

   n_s = (*string).count;
   n_orig = (*substring_original).count;
   n_new = strlen( substring_new );

   while( 1 )
   {
      cp = strstr( cp_s1, cp_orig );

      if ( cp != NULL )
      {
         // increase capacity if necessary, zero newly allocated space
         if ( n_new > n_orig )
         {
            if ( (*string).capacity < n_s + n_new - n_orig  + 1)
            {
               cp_offset = cp - cp_s;
               cp_s1_offset = cp_s1 - cp_s;

               (*string).area = ( char_t * ) realloc( cp_s, n_s + n_new - n_orig + 1 );
               cp_s = (*string).area;
               (*string).capacity = n_s + n_new - n_orig + 1;

               memset( cp_s + n_s, 0, (*string).capacity - n_s );

               // adjust pointers if realloc moved (*string).area
               cp = cp_s + cp_offset;
               cp_s1 = cp_s + cp_s1_offset;
            }
         }

         // move part of string after orig to new spot
         memmove( cp + n_new, cp + n_orig, n_s - ( cp - cp_s) - n_orig );
         // put new substring in its place
         memmove( cp, cp_new, n_new );

         // update count
         (*string).count = (*string).count + n_new - n_orig;
         n_s = (*string).count;

         // zero out area after if string is now shorter
         if ( n_new < n_orig )
         {
            memset( cp_s + n_s, 0, (*string).capacity - n_s );
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
      (*string).hash_code_valid = 0;
   }

   // unlock substring_original
   UNLOCK( (*substring_original).mutex );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}


/**
   string_replace_all_cstring2
*/

void
string_replace_all_cstring2
(
   string_t *string,
   char_t *substring_original,
   char_t *substring_new
)
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring_original not null", substring_original != NULL );
   PRECONDITION( "substring_new not null", substring_new != NULL );
   LOCK( (*string).mutex );
   INVARIANT( string );

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

   cp_s = (*string).area;
   cp_s1 = (*string).area;
   cp_orig = substring_original;
   cp_new = substring_new;

   n_s = (*string).count;
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
            if ( (*string).capacity < n_s + n_new - n_orig  + 1)
            {
               cp_offset = cp - cp_s;
               cp_s1_offset = cp_s1 - cp_s;

               (*string).area = ( char_t * ) realloc( cp_s, n_s + n_new - n_orig + 1 );
               cp_s = (*string).area;
               (*string).capacity = n_s + n_new - n_orig + 1;

               memset( cp_s + n_s, 0, (*string).capacity - n_s );

               // adjust pointers if realloc moved (*string).area
               cp = cp_s + cp_offset;
               cp_s1 = cp_s + cp_s1_offset;
            }
         }

         // move part of string after orig to new spot
         memmove( cp + n_new, cp + n_orig, n_s - ( cp - cp_s) - n_orig );
         // put new substring in its place
         memmove( cp, cp_new, n_new );

         // update count
         (*string).count = (*string).count + n_new - n_orig;
         n_s = (*string).count;

         // zero out area after if string is now shorter
         if ( n_new < n_orig )
         {
            memset( cp_s + n_s, 0, (*string).capacity - n_s );
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
      (*string).hash_code_valid = 0;
   }

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}


/**
   string_append
*/

void
string_append( string_t *string, string_t *s )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "s not null", s != NULL );
   PRECONDITION( "s type OK", (*s).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   // lock s
   LOCK( (*s).mutex );

   int32_t count = 0;

   // make sure there's enough space in string
   if ( (*string).capacity < (*string).count + (*s).count + 1 )
   {
      (*string).area = ( char_t * ) realloc( (*string).area, (*string).count + (*s).count + 1 );
      memset( &((*string).area[ (*string).count ]), 0, (*s).count + 1 );
      (*string).capacity = (*string).count + (*s).count + 1;
      count = (*string).count + (*s).count;
   }
   else
   {
      count = (*string).count + (*s).count;
   }

   // append s to string
   strcat( (*string).area, (*s).area );

   // set count
   (*string).count = count;

   if ( (*s).count > 0 )
   {
      (*string).hash_code_valid = 0;
   }

   // unlock s
   UNLOCK( (*s).mutex );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_append_cstring
*/

void
string_append_cstring( string_t *string, char_t *s )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "s not null", s != NULL );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t count = 0;

   // make sure there's enough space in string
   if ( (*string).capacity < (*string).count + strlen( s ) + 1 )
   {
      (*string).area = ( char_t * ) realloc( (*string).area, (*string).count + strlen( s ) + 1 );
      memset( &((*string).area[ (*string).count ]), 0, strlen(s) + 1 );
      (*string).capacity = (*string).count + strlen( s ) + 1;
      count = (*string).count + strlen( s );
   }
   else
   {
      count = (*string).count + strlen( s );
   }

   // append s to string
   strcat( (*string).area, s );

   // set count
   (*string).count = count;

   if ( strlen( s ) > 0 )
   {
      (*string).hash_code_valid = 0;
   }

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}


/**
   string_prepend
*/

void
string_prepend( string_t *string, string_t *s )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "s not null", s != NULL );
   PRECONDITION( "s type OK", (*s).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   // lock s
   LOCK( (*s).mutex );

   int32_t count = 0;
   int32_t capacity = 0;

   // get capacity, count of result string
   if ( (*string).capacity < (*string).count + (*s).count + 1 )
   {
      capacity = (*string).count + (*s).count + 1;
      count = (*string).count + (*s).count;
   }
   else
   {
      capacity = (*string).capacity;
      count = (*string).count + (*s).count;
   }

   // make new string, append strings to prepend s to string
   char_t *cp = calloc( capacity, sizeof( char_t ) );
   strcat( cp, (*s).area );
   strcat( cp, (*string).area );

   // free original (*string).area, replace with cp
   free( (*string).area );
   (*string).area = cp;

   // set string capacity and count
   (*string).capacity = capacity;
   (*string).count = count;

   if ( (*s).count > 0 )
   {
      (*string).hash_code_valid = 0;
   }

   // unlock s
   UNLOCK( (*s).mutex );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}


/**
   string_prepend_cstring
*/

void
string_prepend_cstring( string_t *string, char_t *s )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "s not null", s != NULL );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t count = 0;
   int32_t capacity = 0;

   int32_t s_count = strlen( s );

   // get capacity, count of result string
   if ( (*string).capacity < (*string).count + s_count + 1 )
   {
      capacity = (*string).count + s_count + 1;
      count = (*string).count + s_count;
   }
   else
   {
      capacity = (*string).capacity;
      count = (*string).count + s_count;
   }

   // make new string, append strings to prepend s to string
   char_t *cp = calloc( capacity, sizeof( char_t ) );
   strcat( cp, s );
   strcat( cp, (*string).area );

   // free original (*string).area, replace with cp
   free( (*string).area );
   (*string).area = cp;

   // set string capacity and count
   (*string).capacity = capacity;
   (*string).count = count;

   if ( s_count > 0 )
   {
      (*string).hash_code_valid = 0;
   }

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}


/**
   string_insert
*/

void
string_insert( string_t *string, string_t *substring, int32_t index )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "substring type OK", (*substring).type == STRING_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*string).count ) ) );
   LOCK( (*string).mutex );
   INVARIANT( string );

   // lock substring
   LOCK( (*substring).mutex );

   int32_t capacity = 0;
   char_t *cp = NULL;

   // get capacity, count of result string
   if ( (*string).capacity < (*string).count + (*substring).count + 1 )
   {
      capacity = (*string).count + (*substring).count + 1;
      (*string).area = ( char_t * ) realloc( (*string).area, capacity );
      memset( &((*string).area[ (*string).count ]), 0, capacity - (*string).count );
      (*string).capacity = capacity;
   }
   else
   {
      capacity = (*string).capacity;
   }

   // move string contents after index back the size of substring
   cp = (*string).area;
   memmove( cp + index + (*substring).count, cp + index, (*string).count - index );

   // set substring in string
   memcpy( cp + index, (*substring).area, (*substring).count*sizeof( char_t ) );
   (*string).count = (*string).count + (*substring).count;

   if ( (*substring).count > 0 )
   {
      (*string).hash_code_valid = 0;
   }

   // unlock substring
   UNLOCK( (*substring).mutex );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}


/**
   string_insert_cstring
*/

void
string_insert_cstring( string_t *string, char_t *substring, int32_t index )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "substring not null", substring != NULL );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*string).count ) ) );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t capacity = 0;
   char_t *cp = NULL;

   int32_t substring_count = strlen( substring );

   // get capacity, count of result string
   if ( (*string).capacity < (*string).count + substring_count + 1 )
   {
      capacity = (*string).count + substring_count + 1;
      (*string).area = ( char_t * ) realloc( (*string).area, capacity );
      memset( &((*string).area[ (*string).count ]), 0, capacity - (*string).count );
      (*string).capacity = capacity;
   }
   else
   {
      capacity = (*string).capacity;
   }

   // move string contents after index back the size of substring
   cp = (*string).area;
   memmove( cp + index + substring_count, cp + index, (*string).count - index );

   // set substring in string
   memcpy( cp + index, substring, substring_count*sizeof( char_t ) );
   (*string).count = (*string).count + substring_count;

   if ( substring_count > 0 )
   {
      (*string).hash_code_valid = 0;
   }

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}


/**
   string_append_character
*/

void
string_append_character( string_t *string, char_t c )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t count = 0;
   int32_t capacity = 0;
   char_t *cp = NULL;

   // get capacity, count of result string
   if ( (*string).capacity < (*string).count + 2 )
   {
      capacity = (*string).count + 2;
      count = (*string).count + 1;
      (*string).area = ( char_t * ) realloc( (*string).area, capacity );
      (*string).capacity = capacity;
   }
   else
   {
      capacity = (*string).capacity;
      count = (*string).count + 1;
   }

   // set character in string
   cp = (*string).area;
   cp[count-1] = c;
   cp[count] = 0;
   (*string).count = (*string).count + 1;

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_prepend_character
*/

void
string_prepend_character( string_t *string, char_t c )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t count = 0;
   int32_t capacity = 0;
   char_t *cp = NULL;

   // get capacity, count of result string
   if ( (*string).capacity < (*string).count + 2 )
   {
      capacity = (*string).count + 2;
      count = (*string).count + 1;
      (*string).area = ( char_t * ) realloc( (*string).area, capacity );
      (*string).capacity = capacity;
   }
   else
   {
      capacity = (*string).capacity;
      count = (*string).count + 1;
   }

   // move string contents back one
   cp = (*string).area;
   memmove( cp + 1, cp, count );

   // set character in string
   cp[0] = c;
   cp[count] = 0;
   (*string).count = (*string).count + 1;

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_insert_character
*/

void
string_insert_character( string_t *string, char_t c, int32_t index )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*string).count ) ) );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t count = 0;
   int32_t capacity = 0;
   char_t *cp = NULL;

   // get capacity, count of result string
   if ( (*string).capacity < (*string).count + 2 )
   {
      capacity = (*string).count + 2;
      count = (*string).count + 1;
      (*string).area = ( char_t * ) realloc( (*string).area, capacity );
      (*string).capacity = capacity;
   }
   else
   {
      capacity = (*string).capacity;
      count = (*string).count + 1;
   }

   // move string contents after index back one
   cp = (*string).area;
   memmove( cp + index + 1, cp + index, count - index );

   // set character in string
   cp[index] = c;
   (*string).count = (*string).count + 1;

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_insert_int32
*/

void
string_insert_int32( string_t *string, int32_t i, int32_t index )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*string).count ) ) );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t capacity = 0;
   char_t *cp = NULL;
   char_t *s_i = calloc( 120, sizeof( char_t ) );
   int32_t s_i_count = 0;

   // make stringified version of integer
   s_i_count = sprintf( s_i, "%d", i );

   // get capacity, count of result string
   if ( (*string).capacity < (*string).count + s_i_count + 1 )
   {
      capacity = (*string).count + s_i_count + 1;
      (*string).area = ( char_t * ) realloc( (*string).area, capacity );
      (*string).capacity = capacity;
   }
   else
   {
      capacity = (*string).capacity;
   }

   // move string contents after index back the size of integer string
   cp = (*string).area;
   memmove( cp + index + s_i_count, cp + index, (*string).count - index );

   // set substring in string
   memcpy( cp + index, s_i, s_i_count*sizeof( char_t ) );
   (*string).count = (*string).count + s_i_count;
   cp[ (*string).count ] = 0;

   // free temp string
   free( s_i );

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_insert_float64
*/

void
string_insert_float64( string_t *string, float64_t f, int32_t index )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index <= (*string).count ) ) );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t capacity = 0;
   char_t *cp = NULL;
   char_t *s_f = calloc( 120, sizeof( char_t ) );
   int32_t s_f_count = 0;

   // make stringified version of integer
   s_f_count = sprintf( s_f, "%lf", f );

   // get capacity, count of result string
   if ( (*string).capacity < (*string).count + s_f_count + 1 )
   {
      capacity = (*string).count + s_f_count + 1;
      (*string).area = ( char_t * ) realloc( (*string).area, capacity );
      (*string).capacity = capacity;
   }
   else
   {
      capacity = (*string).capacity;
   }

   // move string contents after index back the size of integer string
   cp = (*string).area;
   memmove( cp + index + s_f_count, cp + index, (*string).count - index );

   // set substring in string
   memcpy( cp + index, s_f, s_f_count*sizeof( char_t ) );
   (*string).count = (*string).count + s_f_count;
   cp[ (*string).count ] = 0;

   // free temp string
   free( s_f );

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}



/**
   string_to_lower
*/

void
string_to_lower( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t i = 0;
   char_t *cp = (*string).area;
   int32_t n = (*string).count;

   for( i = 0; i < n; i++ )
   {
      cp[i] = to_lowercase( cp[i] );
   }

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_to_upper
*/

void
string_to_upper( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   int32_t i = 0;
   char_t *cp = (*string).area;
   int32_t n = (*string).count;

   for( i = 0; i < n; i++ )
   {
      cp[i] = to_uppercase( cp[i] );
   }

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_substring
*/

string_t *
string_substring( string_t *string, int32_t start_index, int32_t end_index )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*string).count ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < (*string).count ) ) );
   LOCK( (*string).mutex );
   INVARIANT( string );

   string_t *result = string_make_n( end_index - start_index + 2 );
   char_t *cp = (*string).area;
   memcpy( (*result).area, cp + start_index, end_index - start_index + 1 );
   (*result).count = end_index - start_index + 1;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_copy
*/

string_t *
string_copy( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   string_t *result = s_copy( string );

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return result;
}

/**
   string_remove
*/

void
string_remove( string_t *string, int32_t index )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < (*string).count ) ) );
   LOCK( (*string).mutex );
   INVARIANT( string );

   char_t *cp = NULL;

   // move string contents after index forward one
   cp = (*string).area;
   memmove( cp + index, cp + index + 1, (*string).count - index );

   // set count
   (*string).count = (*string).count - 1;
   cp[ (*string).count ] = 0;

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_remove_substring
*/

void
string_remove_substring( string_t *string, int32_t start_index, int32_t end_index )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   PRECONDITION( "start_index ok", ( ( start_index >= 0 ) && ( start_index < (*string).count ) ) );
   PRECONDITION( "end index ok", ( ( end_index >= 0 ) && ( end_index < (*string).count ) ) );
   LOCK( (*string).mutex );
   INVARIANT( string );

   char_t *cp = NULL;

   // move string contents after index forward
   cp = (*string).area;
   memmove( cp + start_index, cp + end_index + 1, (*string).count - end_index - 1 );

   // set count
   (*string).count = (*string).count - end_index + start_index - 1;
   cp[ (*string).count ] = 0;

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_keep_head
*/

void
string_keep_head( string_t *string, int32_t count )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );
   PRECONDITION( "count ok", (*string).count >= count );

   // set new end
   (*string).area[count] = 0;
   (*string).count = count;

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_remove_head
*/

void
string_remove_head( string_t *string, int32_t count )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   PRECONDITION( "count ok", (*string).count >= count );
   INVARIANT( string );

   char_t *cp = NULL;

   // move string contents after count forward
   cp = (*string).area;
   memmove( cp, cp + count, (*string).count - count );
   cp[(*string).count - count] = 0;
   (*string).count = (*string).count - count;

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_keep_tail
*/

void
string_keep_tail( string_t *string, int32_t count )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   PRECONDITION( "count ok", (*string).count >= count );
   INVARIANT( string );

   char_t *cp = NULL;

   // move string contents after (*string).count - count forward
   cp = (*string).area;
   memmove( cp, cp + (*string).count - count , count );
   cp[count] = 0;
   (*string).count = count;

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_remove_tail
*/

void
string_remove_tail( string_t *string, int32_t count )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   PRECONDITION( "count ok", (*string).count >= count );
   INVARIANT( string );

   // set new end
   (*string).area[ (*string).count - count] = 0;
   (*string).count = (*string).count - count;

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_wipe_out
*/

void
string_wipe_out( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   INVARIANT( string );

   // set to empty string
   (*string).area[0] = 0;
   (*string).count = 0;

   (*string).hash_code_valid = 0;

   INVARIANT( string );
   POSTCONDITION( "string empty", (*string).count == 0 );
   UNLOCK( (*string).mutex );

   return;
}

/**
   string_resize
*/

void
string_resize( string_t *string, int32_t new_capacity )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );
   LOCK( (*string).mutex );
   PRECONDITION( "capacity ok", new_capacity > (*string).count );
   INVARIANT( string );

   // don't reduce capacity below what is required to store the content
   if ( new_capacity > (*string).count )
   {
      // make new capacity at least 4 characters
      if ( new_capacity < STRING_MIN_SIZE )
      {
         new_capacity = STRING_MIN_SIZE;
      }
      
      // set new capacity
      (*string).area = ( char_t * ) realloc( (*string).area, new_capacity );
      (*string).capacity = new_capacity;
   }

   INVARIANT( string );
   POSTCONDITION( "capacity set", (*string).capacity == new_capacity );
   UNLOCK( (*string).mutex );

   return;
}

/**
   Extras - may be used as dispose, duplicate functions in other classes
*/

/**
   s_hash_code
*/

int32_t
s_hash_code( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );

   if ( (*string).hash_code_valid == 0 )
   {
      (*string).hash_code = get_hash( (*string).area, (*string).count );
      (*string).hash_code_valid = 1;
   }

   int32_t result = (*string).hash_code;

   return result;
}

/**
   s_is_equal
*/

int32_t
s_is_equal( string_t *s1, string_t *s2 )
{
   PRECONDITION( "s1 not null", s1 != NULL );
   PRECONDITION( "s1 type OK", (*s1).type == STRING_TYPE );
   PRECONDITION( "s2 not null", s2 != NULL );
   PRECONDITION( "s2 type OK", (*s2).type == STRING_TYPE );

   int32_t result = 0;
   result = strcmp( (*s1).area, (*s2).area );

   return ( result == 0 );
}

/**
   s_dispose_with_contents
*/

void
s_dispose_with_contents( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );

   // delete string items
   free( (*string).area );

   MULTITHREAD_MUTEX_DESTROY( (*string).mutex );

   // delete string struct
   free( string );

   return;
}

/**
   s_make_from
*/

string_t *
s_make_from( string_t *string )
{
   PRECONDITION( "string not null", string != NULL );
   PRECONDITION( "string type OK", (*string).type == STRING_TYPE );

   // allocate string struct
   string_t * result = ( string_t * ) calloc( 1, sizeof( string_t ) );

   // set type
   (*result).type = STRING_TYPE;
   
   // set area
   (*result).area = ( char * ) calloc( (*string).capacity, sizeof( char_t ) );
   strncpy( (*result).area, (*string).area, (*string).count );

   // set count
   (*result).count = (*string).count;

   // set capacity
   (*result).capacity = (*string).capacity;

   // set hash_code
   (*result).hash_code = (*string).hash_code;

   // set hash_code_valid
   (*result).hash_code_valid = (*string).hash_code_valid;

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   POSTCONDITION( "size set", (*result).count == (*string).count );
   POSTCONDITION( "area set", strcmp( (*result).area, (*string).area ) == 0 );

   return result;
}


#ifdef __cplusplus
}
#endif

/* End of file */

