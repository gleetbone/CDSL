/**
 @file Input_File_Reader.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Simple text file parser"
 
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

 Function definitions for the opaque ifr_t type.
 Data structure and functions to parse a text file line by line into tokens

*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Input_File_Reader.h"

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

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

#define INPUT_FILE_READER_TYPE 0xA5000703

/**
   Input file reader structure
*/

struct input_file_reader_struct
{
   int32_t type;
   
   string_t *filename;
   FILE *fp;
   s_dlist_t *tokens;
   string_t *line;
   int32_t skip_comments;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

#if INVARIANT_CONDITIONAL != 0

static
int32_t
members_not_null( ifr_t *p )
{
   int32_t result = 1;
  
   result 
      =  ( (*p).fp != NULL ) 
         && 
         ( (*p).filename != NULL ) 
         && 
         ( (*p).tokens != NULL )
         && 
         ( (*p).line != NULL );
   
   return result;
}

static
void invariant( ifr_t *p )
{
   assert(((void) "members not null", members_not_null( p ) ));
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
         // and we're paring a token
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
               // double quotes terminates the token - put it in the list
               s_dlist_put_last( list, t );
               t = NULL;
               token_flag = 0;

               // set inside quotes flag
               quote_flag = 1;
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

   return;
}

#define DEFAULT_LINE_SIZE 120

/**
   ifr_make
*/

ifr_t *
ifr_make( string_t *filename )
{
   PRECONDITION( "filename not null", filename != NULL );

   // allocate list struct
   ifr_t * ifr = ( ifr_t * ) calloc( 1, sizeof( ifr_t ) );

   // set type code
   (*ifr).type = INPUT_FILE_READER_TYPE;
   
   // attempt to open the file
   (*ifr).fp = fopen( string_as_cstring( filename ), "r" );

   // if file pointer null, print error message and return NULL
   if ( (*ifr).fp == NULL )
   {
      printf( "Error - Input_File_Reader - file %s does not exist.", string_as_cstring( filename ) );
      free( ifr );
      ifr = NULL;
   }
   // if file pointer ok, allocate tokens list and line
   else
   {
      (*ifr).filename = string_make_from( filename );
      (*ifr).tokens = s_dlist_make();
      (*ifr).line = string_make_n( DEFAULT_LINE_SIZE );
      MULTITHREAD_MUTEX_INIT( (*ifr).mutex );
   }

   if ( ifr != NULL )
   {
      INVARIANT( ifr );
   }

   return ifr;
}

/**
   ifr_make_cstring
*/

ifr_t *
ifr_make_cstring( char_t *filename )
{
   PRECONDITION( "filename not null", filename != NULL );

   // allocate list struct
   ifr_t * ifr = ( ifr_t * ) calloc( 1, sizeof( ifr_t ) );

   // set type code
   (*ifr).type = INPUT_FILE_READER_TYPE;
   
   // attempt to open the file
   (*ifr).fp = fopen( filename, "r" );

   // if file pointer null, print error message and return NULL
   if ( (*ifr).fp == NULL )
   {
      printf( "Error - Input_File_Reader - file %s does not exist.", filename );
      free( ifr );
      ifr = NULL;
   }
   // if file pointer ok, allocate tokens list and line
   else
   {
      (*ifr).filename = string_make_from_cstring( filename );
      (*ifr).tokens = s_dlist_make();
      (*ifr).line = string_make_n( DEFAULT_LINE_SIZE );
      MULTITHREAD_MUTEX_INIT( (*ifr).mutex );
   }

   if ( ifr != NULL )
   {
      INVARIANT( ifr );
   }

   return ifr;
}

/**
   ifr_dispose
*/

void
ifr_dispose( ifr_t *ifr )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "ifr type OK", (*ifr).type == INPUT_FILE_READER_TYPE );
   LOCK( (*ifr).mutex );
   INVARIANT( ifr );

   // delete structure items
   string_dispose_with_contents( (*ifr).filename );
   s_dlist_dispose_with_contents( (*ifr).tokens );
   string_dispose_with_contents( (*ifr).line );

   // close the file
   fclose( (*ifr).fp );

   MULTITHREAD_MUTEX_DESTROY( (*ifr).mutex );

   // deallocate the structure
   free( ifr );

   return;
}

/**
   ifr_tokens
*/

s_dlist_t *
ifr_tokens( ifr_t *ifr )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "ifr type OK", (*ifr).type == INPUT_FILE_READER_TYPE );
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
   PRECONDITION( "ifr type OK", (*ifr).type == INPUT_FILE_READER_TYPE );
   LOCK( (*ifr).mutex );
   INVARIANT( ifr );

   string_t *result = (*ifr).line;
   
   INVARIANT( ifr );
   UNLOCK( (*ifr).mutex );
   
   return( result );
}

/**
   ifr_filename
*/

string_t *
ifr_filename( ifr_t *ifr )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "ifr type OK", (*ifr).type == INPUT_FILE_READER_TYPE );
   LOCK( (*ifr).mutex );
   INVARIANT( ifr );

   string_t *result = (*ifr).filename;
   
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
   PRECONDITION( "ifr type OK", (*ifr).type == INPUT_FILE_READER_TYPE );
   LOCK( (*ifr).mutex );
   INVARIANT( ifr );

   int32_t result = feof( (*ifr).fp );
   
   INVARIANT( ifr );
   UNLOCK( (*ifr).mutex );
   
   return( result );
}

/**
   ifr_skip_comments
*/

int32_t
ifr_skip_comments( ifr_t *ifr )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "ifr type OK", (*ifr).type == INPUT_FILE_READER_TYPE );
   LOCK( (*ifr).mutex );
   INVARIANT( ifr );

   int32_t result = (*ifr).skip_comments;
   
   INVARIANT( ifr );
   UNLOCK( (*ifr).mutex );
   
   return( result );
}

/**
   ifr_set_skip_comments
*/

void
ifr_set_skip_comments( ifr_t *ifr, int32_t flag )
{
   PRECONDITION( "ifr not null", ifr != NULL );
   PRECONDITION( "ifr type OK", (*ifr).type == INPUT_FILE_READER_TYPE );
   LOCK( (*ifr).mutex );
   INVARIANT( ifr );

   (*ifr).skip_comments = flag;
   
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
   PRECONDITION( "ifr type OK", (*ifr).type == INPUT_FILE_READER_TYPE );
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
         // exit if last past put something into tokens
         if ( s_dlist_count( (*ifr).tokens ) != 0 )
         {
            break;
         }

         // clear out tokens and line
         s_dlist_wipe_out_and_dispose( (*ifr).tokens );
         string_wipe_out( (*ifr).line );

         // get the next line
         count = getline( &line, &len, (*ifr).fp );

         // parse for tokens only if line is not the empty string
         if ( count > 0 )
         {
            // get the next line from the file
            s = string_make_from_cstring( line );
            string_append( (*ifr).line, s );
            string_dispose_with_contents( s );

            // parse the line into tokens
            get_string_tokens
            (
               (*ifr).line,
               (*ifr).tokens
            );

            // eliminate tokens after the comment string if flag is set to do so
            if ( (*ifr).skip_comments == 1 )
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
   
   string_dispose_with_contents( comment1 );
   string_dispose_with_contents( comment2 );
   
   INVARIANT( ifr );
   UNLOCK( (*ifr).mutex );
   
   return;
}

/* End of file */

