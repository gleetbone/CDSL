/**
 @file Input_File_Reader.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Simple text file parser"

 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018-2020 Greg Lee

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

 Function definitions for the opaque ifr_t type.
 Data structure and functions to parse a text file line by line into tokens

*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Input_File_Reader.h"
#include "String_utilities.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

struct input_file_reader_struct;

#include "dbc.h"

/**
   defines
*/

/**
   Input file reader structure
*/

struct input_file_reader_struct
{
   int32_t _type;

   string_t *file_name;
   FILE *fp;
   s_dlist_t *tokens;
   string_t *line;
   int32_t line_number;
   int32_t is_skip_comments;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

#if INVARIANT_CONDITIONAL != 0

static
int32_t
members_ok( ifr_t *p )
{
   int32_t result = 1;

   result
      =  ( (*p).fp != NULL )
         &&
         ( (*p).file_name != NULL )
         &&
         ( (*p).tokens != NULL )
         &&
         ( (*p).line != NULL )
         &&
         ( (*p).line_number >= 0 );

   return result;
}

static
void invariant( ifr_t *p )
{
   assert( ( ( void ) "members ok", members_ok( p ) ) );
   return;
}

#endif

/**
   get_string_tokens

   Parse a string into whitespace separated tokens. Double quotes may be used
   to delineate tokens containing whitespace - double quotes will not be returned
   as part of the token.

   @param line string_t instance to parse
   @param list list to receive parsed tokens
*/
static
void
get_string_tokens
(
   string_t *line,
   s_dlist_t *list
)
{
   PRECONDITION( "line not null", line != NULL );
   PRECONDITION( "list not null", list != NULL );

   int32_t i = 0;
   int32_t n = 0;
   string_t *t = NULL;
   char_t c = 0;
   int32_t token_flag = 0;
   int32_t quote_flag = 0;

   s_dlist_wipe_out_and_dispose( list );

   // look for tokens as whitespace separated strings
   n = string_count( line );
   token_flag = 0;
   quote_flag = 0;

   // loop through each character in line
   for( i = 0; i < n; i++ )
   {
      // get the character
      c = string_item( line, i );

      // if c is whitespace
      if ( ( c == ' ' ) || ( c == '\t' ) )
      {
         // and we're parsing a token
         if ( token_flag == 1 )
         {
            // and we're inside quotes
            if ( quote_flag == 1 )
            {
               // append the character to the token
               string_append_character( t, c );
            }
            // if we're not inside quotes
            else if ( quote_flag == 0 )
            {
               // whitespace terminates the token - put it in the list
               s_dlist_put_last( list, t );
               t = NULL;
               token_flag = 0;
            }
         }
         // if we're not parsing a token, skip the whitespace
         else if ( token_flag == 0 )
         {
         }

      }
      // if c is a new line
      else if ( ( c == '\n' ) || ( c == '\r' ) )
      {
         // and we're parsing a token
         if ( token_flag == 1 )
         {
            // whitespace terminates the token - put it in the list
            s_dlist_put_last( list, t );
            t = NULL;
            token_flag = 0;
            quote_flag = 0;
         }
      }
      // if c is double quotes
      else if ( c == '\"' )
      {
         // and we're inside a token
         if ( token_flag == 1 )
         {
            // and we're not inside quotes
            if ( quote_flag == 0 )
            {
               // append the double quote character to the token
               string_append_character( t, c );
            }
            // if we're inside quotes
            else if ( quote_flag == 1 )
            {
               // double quotes terminates the token - put it in the list
               s_dlist_put_last( list, t );
               t = NULL;
               token_flag = 0;

               // now outside quotes
               quote_flag = 0;
            }
         }
         // if we're not parsing a token
         else if ( token_flag == 0 )
         {
            // start a new token
            t = string_make_n( 12 );
            token_flag = 1;

            // and we're inside quotes
            quote_flag = 1;
         }
      }
      // for any other character
      else
      {
         // if we're not parsing a token
         if ( token_flag == 0 )
         {
            // start a new token
            t = string_make_n( 12 );

            // now parsing a token
            token_flag = 1;
         }
         // append c to the end of the token
         string_append_character( t, c );
      }

   }

   // at end of line and parsing a token
   if ( token_flag == 1 )
   {
      // finish the token, put the token in the list
      s_dlist_put_last( list, t );
      t = NULL;
   }

}

#define DEFAULT_LINE_SIZE 120

/**
   ifr_make
*/

ifr_t *
ifr_make( string_t *file_name )
{
   PRECONDITION( "file_name not null", file_name != NULL );
   PRECONDITION( "file exists", file_exists( file_name ) == 1 );

   // allocate list struct
   ifr_t * result = ( ifr_t * ) calloc( 1, sizeof( ifr_t ) );
   CHECK( "result allocated_correctly", result != NULL );

   // set type code
   (*result)._type = INPUT_FILE_READER_TYPE;

   // open the file
   (*result).fp = fopen( string_as_cstring( file_name ), "r" );

   (*result).file_name = string_deep_clone( file_name );
   (*result).tokens = s_dlist_make();
   (*result).line = string_make_n( DEFAULT_LINE_SIZE );
   (*result).line_number = 0;
   (*result).is_skip_comments = 0;
   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   if ( result != NULL )
   {
      INVARIANT( result );
   }

   return result;
}

/**
   ifr_make_cstring
*/

ifr_t *
ifr_make_cstring( char_t *file_name )
{
   PRECONDITION( "file_name not null", file_name != NULL );
   PRECONDITION( "file exists", file_exists_cstring( file_name ) == 1 );

   // allocate list struct
   ifr_t * result = ( ifr_t * ) calloc( 1, sizeof( ifr_t ) );
   CHECK( "result allocated_correctly", result != NULL );

   // set type code
   (*result)._type = INPUT_FILE_READER_TYPE;

   // open the file
   (*result).fp = fopen( file_name, "r" );

   (*result).file_name = string_make_from_cstring( file_name );
   (*result).tokens = s_dlist_make();
   (*result).line = string_make_n( DEFAULT_LINE_SIZE );
   (*result).line_number = 0;
   (*result).is_skip_comments = 0;
   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   if ( result != NULL )
   {
      INVARIANT( result );
   }

   return result;
}

/**
   ifr_clone
*/

ifr_t *
ifr_clone( ifr_t *current )
{
   PRECONDITION( "ifr not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == INPUT_FILE_READER_TYPE );

   // allocate ifr struct
   ifr_t * result = ( ifr_t * ) calloc( 1, sizeof( ifr_t ) );
   CHECK( "result allocated_correctly", result != NULL );

   // lock mutex
   LOCK( (*current).mutex );

   // set type
   (*result)._type = INPUT_FILE_READER_TYPE;

   (*result).file_name = string_clone( (*current).file_name );

   (*result).fp = fopen( string_as_cstring( (*result).file_name ), "r" );
   fseek( (*result).fp, ftell( (*current).fp ), SEEK_SET );

   (*result).tokens = s_dlist_clone( (*current).tokens );
   (*result).line = string_clone( (*current).line );
   (*result).line_number = (*current).line_number;
   (*result).is_skip_comments = (*current).is_skip_comments;

   // unlock mutex
   UNLOCK( (*current).mutex );

   INVARIANT( current );

   return result;
}

/**
   ifr_deep_clone
*/

ifr_t *
ifr_deep_clone( ifr_t *current )
{
   PRECONDITION( "ifr not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == INPUT_FILE_READER_TYPE );

   // allocate ifr struct
   ifr_t * result = ( ifr_t * ) calloc( 1, sizeof( ifr_t ) );
   CHECK( "result allocated_correctly", result != NULL );

   // lock mutex
   LOCK( (*current).mutex );

   // set type
   (*result)._type = INPUT_FILE_READER_TYPE;

   (*result).file_name = string_deep_clone( (*current).file_name );

   (*result).fp = fopen( string_as_cstring( (*result).file_name ), "r" );
   fseek( (*result).fp, ftell( (*current).fp ), SEEK_SET );

   (*result).tokens = s_dlist_deep_clone( (*current).tokens );
   (*result).line = string_deep_clone( (*current).line );
   (*result).line_number = (*current).line_number;
   (*result).is_skip_comments = (*current).is_skip_comments;

   // unlock mutex
   UNLOCK( (*current).mutex );

   INVARIANT( current );

   return result;
}

/**
  is_equal
*/

static
int32_t
is_equal(  ifr_t *current, ifr_t *other )
{
   int32_t result = 0;

   result =
      ( string_is_equal( (*current).file_name, (*other).file_name ) == 1 )
      &&
      ( s_dlist_is_equal( (*current).tokens, (*other).tokens ) == 1 )
      &&
      ( string_is_equal( (*current).line, (*other).line ) == 1 )
      &&
      ( (*current).line_number == (*other).line_number )
      &&
      ( (*current).is_skip_comments == (*other).is_skip_comments )
      &&
      ( ftell( (*current).fp ) == ftell( (*other).fp ) );

   return result;
};

/**
   ifr_is_equal
*/

int32_t
ifr_is_equal( ifr_t *current, ifr_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == INPUT_FILE_READER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == INPUT_FILE_READER_TYPE );
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

      result = is_equal( current, other );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
  is_deep_equal
*/

static
int32_t
is_deep_equal(  ifr_t *current, ifr_t *other )
{
   int32_t result = 0;

   result =
      ( string_is_deep_equal( (*current).file_name, (*other).file_name ) == 1 )
      &&
      ( s_dlist_is_deep_equal( (*current).tokens, (*other).tokens ) == 1 )
      &&
      ( string_is_deep_equal( (*current).line, (*other).line ) == 1 )
      &&
      ( (*current).line_number == (*other).line_number )
      &&
      ( (*current).is_skip_comments == (*other).is_skip_comments )
      &&
      ( ftell( (*current).fp ) == ftell( (*other).fp ) );

   return result;
};

/**
   ifr_is_deep_equal
*/

int32_t
ifr_is_deep_equal( ifr_t *current, ifr_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == INPUT_FILE_READER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == INPUT_FILE_READER_TYPE );
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

      result = is_deep_equal( current, other );

      // unlock other
      UNLOCK( (*other).mutex );
   }

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   ifr_copy
*/

void
ifr_copy( ifr_t *current, ifr_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == INPUT_FILE_READER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == INPUT_FILE_READER_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   string_copy( (*current).file_name, (*other).file_name );

   fseek( (*current).fp, ftell( (*other).fp ), SEEK_SET );

   s_dlist_copy( (*current).tokens, (*other).tokens );
   string_copy( (*current).line, (*other).line );
   (*current).line_number = (*other).line_number;
   (*current).is_skip_comments = (*other).is_skip_comments;

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   ifr_deep_copy
*/

void
ifr_deep_copy( ifr_t *current, ifr_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == INPUT_FILE_READER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == INPUT_FILE_READER_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   string_deep_copy( (*current).file_name, (*other).file_name );

   fseek( (*current).fp, ftell( (*other).fp ), SEEK_SET );

   s_dlist_deep_copy( (*current).tokens, (*other).tokens );
   string_deep_copy( (*current).line, (*other).line );
   (*current).line_number = (*other).line_number;
   (*current).is_skip_comments = (*other).is_skip_comments;

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   ifr_dispose
*/

void
ifr_dispose( ifr_t **ifr )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "*ifr not null", *ifr != NULL );
   PRECONDITION( "ifr type OK", (**ifr)._type == INPUT_FILE_READER_TYPE );
   LOCK( (**ifr).mutex );
   INVARIANT(*ifr);

   // delete structure items
   string_dispose( &(**ifr).file_name );
   s_dlist_dispose( &(**ifr).tokens );
   string_dispose( &(**ifr).line );

   // close the file
   fclose( (**ifr).fp );

   MULTITHREAD_MUTEX_DESTROY( (**ifr).mutex );

   // deallocate the structure
   free(*ifr);

   // set the pointer to null
   *ifr = NULL;

   return;
}

/**
   ifr_deep_dispose
*/

void
ifr_deep_dispose( ifr_t **ifr )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "*ifr not null", *ifr != NULL );
   PRECONDITION( "ifr type OK", (**ifr)._type == INPUT_FILE_READER_TYPE );
   LOCK( (**ifr).mutex );
   INVARIANT(*ifr);

   // delete structure items
   string_deep_dispose( &(**ifr).file_name );
   s_dlist_deep_dispose( &(**ifr).tokens );
   string_deep_dispose( &(**ifr).line );

   // close the file
   fclose( (**ifr).fp );

   MULTITHREAD_MUTEX_DESTROY( (**ifr).mutex );

   // deallocate the structure
   free(*ifr);

   // set the pointer to null
   *ifr = NULL;

   return;
}

/**
   ifr_tokens
*/

s_dlist_t *
ifr_tokens( ifr_t *ifr )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "ifr type OK", (*ifr)._type == INPUT_FILE_READER_TYPE );
   LOCK( (*ifr).mutex );
   INVARIANT( ifr );

   s_dlist_t *result = (*ifr).tokens;

   INVARIANT( ifr );
   UNLOCK( (*ifr).mutex );

   return( result );
}

/**
   ifr_line
*/

string_t *
ifr_line( ifr_t *ifr )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "ifr type OK", (*ifr)._type == INPUT_FILE_READER_TYPE );
   LOCK( (*ifr).mutex );
   INVARIANT( ifr );

   string_t *result = (*ifr).line;

   INVARIANT( ifr );
   UNLOCK( (*ifr).mutex );

   return( result );
}

/**
   ifr_line_number
*/

int32_t
ifr_line_number( ifr_t *ifr )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "ifr type OK", (*ifr)._type == INPUT_FILE_READER_TYPE );
   LOCK( (*ifr).mutex );
   INVARIANT( ifr );

   int32_t result = (*ifr).line_number;

   INVARIANT( ifr );
   UNLOCK( (*ifr).mutex );

   return( result );
}

/**
   ifr_file_name
*/

string_t *
ifr_file_name( ifr_t *ifr )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "ifr type OK", (*ifr)._type == INPUT_FILE_READER_TYPE );
   LOCK( (*ifr).mutex );
   INVARIANT( ifr );

   string_t *result = string_deep_clone( (*ifr).file_name );

   INVARIANT( ifr );
   UNLOCK( (*ifr).mutex );

   return( result );
}

/**
   ifr_eof
*/

int32_t
ifr_eof( ifr_t *ifr )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "ifr type OK", (*ifr)._type == INPUT_FILE_READER_TYPE );
   LOCK( (*ifr).mutex );
   INVARIANT( ifr );

   int32_t result = feof( (*ifr).fp );

   INVARIANT( ifr );
   UNLOCK( (*ifr).mutex );

   return( result );
}

/**
   ifr_is_skip_comments
*/

int32_t
ifr_is_skip_comments( ifr_t *ifr )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "ifr type OK", (*ifr)._type == INPUT_FILE_READER_TYPE );
   LOCK( (*ifr).mutex );
   INVARIANT( ifr );

   int32_t result = (*ifr).is_skip_comments;

   INVARIANT( ifr );
   UNLOCK( (*ifr).mutex );

   return( result );
}

/**
   ifr_put_is_skip_comments
*/

void
ifr_put_is_skip_comments( ifr_t *ifr, int32_t flag )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "ifr type OK", (*ifr)._type == INPUT_FILE_READER_TYPE );
   LOCK( (*ifr).mutex );
   INVARIANT( ifr );

   (*ifr).is_skip_comments = flag;

   INVARIANT( ifr );
   UNLOCK( (*ifr).mutex );

   return;
}

/**
   ifr_forth
*/

void
ifr_forth( ifr_t *ifr )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "ifr type OK", (*ifr)._type == INPUT_FILE_READER_TYPE );
   LOCK( (*ifr).mutex );
   INVARIANT( ifr );

   char_t *line = NULL;
   uint64_t len = 0;
   int32_t count = 0;
   int32_t token_count = 0;
   string_t *s = NULL;
   string_t *comment1 = string_make_from_cstring( "//" );
   string_t *comment2 = string_make_from_cstring( "--" );

   // clear out tokens and line
   s_dlist_wipe_out_and_dispose( (*ifr).tokens );
   string_wipe_out( (*ifr).line );

   if ( feof( (*ifr).fp ) == 0 )
   {
      // keep getting lines to skip blank and comment lines
      // return non empty tokens or at eof

      while ( feof( (*ifr).fp ) == 0 )
      {
         // exit if last pass put something into tokens
         if ( s_dlist_count( (*ifr).tokens ) != 0 )
         {
            break;
         }

         // clear out tokens and line
         s_dlist_wipe_out_and_dispose( (*ifr).tokens );
         string_wipe_out( (*ifr).line );

         // get the next line
         count = getline( &line, &len, (*ifr).fp );
         (*ifr).line_number = (*ifr).line_number + 1;

         // parse for tokens only if line is not the empty string
         if ( count > 0 )
         {
            // get the next line from the file
            s = string_make_from_cstring( line );
            string_append( (*ifr).line, s );
            string_deep_dispose( &s );

            // parse the line into tokens
            get_string_tokens
            (
               (*ifr).line,
               (*ifr).tokens
            );

            // eliminate tokens after the comment string if flag is set to do so
            if ( (*ifr).is_skip_comments == 1 )
            {
               token_count = 0;
               // walk through the tokens, looking for a token that starts
               // with a comment string
               for
               (
                  s_dlist_start( (*ifr).tokens );
                  s_dlist_off( (*ifr).tokens ) == 0;
                  s_dlist_forth( (*ifr).tokens )
               )
               {
                  if (
                     ( string_starts_with( s_dlist_item_at( (*ifr).tokens ), comment1 ) == 1 )
                     ||
                     ( string_starts_with( s_dlist_item_at( (*ifr).tokens ), comment2 ) == 1 )
                  )
                  {
                     // if comment string found, prune this and all following tokens
                     s_dlist_keep_first_and_dispose( (*ifr).tokens, token_count );
                     break;
                  }
                  else
                  {
                     // count the tokens examined
                     token_count = token_count + 1;
                  }
               }
            }

         }

      }
   }

   if ( line != NULL )
   {
      free( line );
   }

   string_deep_dispose( &comment1 );
   string_deep_dispose( &comment2 );

   INVARIANT( ifr );
   UNLOCK( (*ifr).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

