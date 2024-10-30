/**
 @file Command_Line_Handler.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Command Line Handler class"

 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2020 Greg Lee

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

 Function definitions for the opaque command_line_handler_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Command_Line_Handler.h"

#include "Protocol_Base.ph"

#include "p_CLH_Command.h"
#include "p_CLH_Option.h"

#include "s_AList.h"
#include "c_AList.h"
#include "o_AList.h"

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#include <Command_Line_Handler.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

/**
   command_line_handler structure
*/

struct command_line_handler_struct
{
   int32_t _type;

   FILE *fp_in;
   FILE *fp_out;
   string_t *help_string;
   string_t *usage_string;
   string_t *version_string;
   c_alist_t *commands;
   o_alist_t *options;
   string_t *last_error;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Local Functions and  Prototypes
*/

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
   char_t *line,
   s_alist_t *list
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

   s_alist_wipe_out_and_dispose( list );

   // look for tokens as whitespace separated strings
   n = strlen( line );
   token_flag = 0;
   quote_flag = 0;

   // loop through each character in line
   for( i = 0; i < n; i++ )
   {
      // get the character
      c = line[i];

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
               s_alist_put_last( list, t );
               t = NULL;
               token_flag = 0;
            }
         }
         // if we're not parsing a token, skip the whitespace
         else if ( token_flag == 0 )
         {
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
               s_alist_put_last( list, t );
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
      s_alist_put_last( list, t );
      t = NULL;
   }

   return;
}

/**
   File variables
*/

static int32_t quit_flag = 0;

#if INVARIANT_CONDITIONAL != 0

static
int32_t
help_string_valid( command_line_handler_t *current )
{
   int32_t result = 0;

   result = ( (*current).help_string != NULL );

   return result;
}

static
int32_t
usage_string_valid( command_line_handler_t *current )
{
   int32_t result = 0;

   result = ( (*current).usage_string != NULL );

   return result;
}

static
int32_t
version_string_valid( command_line_handler_t *current )
{
   int32_t result = 0;

   result = ( (*current).version_string != NULL );

   return result;
}

static
int32_t
commands_valid( command_line_handler_t *current )
{
   int32_t result = 0;

   result = ( (*current).commands != NULL );

   return result;
}

static
int32_t
options_valid( command_line_handler_t *current )
{
   int32_t result = 0;

   result = ( (*current).options != NULL );

   return result;
}

static
int32_t
last_error_valid( command_line_handler_t *current )
{
   int32_t result = 0;

   result = ( (*current).last_error != NULL );

   return result;
}

static
void invariant( command_line_handler_t *current )
{
   assert( ( ( void ) "help_string_valid", help_string_valid( current ) ) );
   assert( ( ( void ) "usage_string_valid", usage_string_valid( current ) ) );
   assert( ( ( void ) "version_string_valid", version_string_valid( current ) ) );
   assert( ( ( void ) "commands_valid", commands_valid( current ) ) );
   assert( ( ( void ) "options_valid", options_valid( current ) ) );
   assert( ( ( void ) "last_error_valid", last_error_valid( current ) ) );
   return;
}

#endif

/**
   command_line_handler_make
*/

command_line_handler_t *
command_line_handler_make
(
   FILE *fp_in,
   FILE *fp_out,
   string_t *help_string,
   string_t *usage_string,
   string_t *version_string
)
{
   PRECONDITION( "fp_in not null", fp_in != NULL );
   PRECONDITION( "fp_out not null", fp_out != NULL );
   PRECONDITION( "help_string not null", help_string != NULL );
   PRECONDITION( "usage_string not null", usage_string != NULL );
   PRECONDITION( "version_string not null", version_string != NULL );

   // allocate command_line_handler struct
   command_line_handler_t * result = ( command_line_handler_t * ) calloc( 1, sizeof( command_line_handler_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // set type
   (*result)._type = COMMAND_LINE_HANDLER_TYPE;

   // set fp_in
   (*result).fp_in = fp_in;

   // set fp_in
   (*result).fp_out = fp_out;

   // set help_string
   (*result).help_string = string_deep_clone( help_string );

   // set usage_string
   (*result).usage_string = string_deep_clone( usage_string );

   // set version_string
   (*result).version_string = string_deep_clone( version_string );

   // set commands
   (*result).commands = c_alist_make();

   // set options
   (*result).options = o_alist_make();

   // last error
   (*result).last_error = string_make();

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   command_line_handler_clone
*/

command_line_handler_t *
command_line_handler_clone( command_line_handler_t *current )
{
   PRECONDITION( "command_line_handler not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );

   // allocate command_line_handler struct
   command_line_handler_t * result = ( command_line_handler_t * ) calloc( 1, sizeof( command_line_handler_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // lock mutex
   LOCK( (*current).mutex );

   // set type
   (*result)._type = COMMAND_LINE_HANDLER_TYPE;

   (*result).fp_in = (*current).fp_in;
   (*result).fp_out = (*current).fp_out;

   (*result).help_string = string_clone( (*current).help_string );
   (*result).usage_string = string_clone( (*current).usage_string );
   (*result).version_string = string_clone( (*current).version_string );

   (*result).commands = c_alist_clone( (*current).commands );
   (*result).options = o_alist_clone( (*current).options );

   (*result).last_error = string_clone( (*current).last_error );

   // unlock mutex
   UNLOCK( (*current).mutex );

   INVARIANT( current );

   return result;
}

/**
   command_line_handler_deep_clone
*/

command_line_handler_t *
command_line_handler_deep_clone( command_line_handler_t *current )
{
   PRECONDITION( "command_line_handler not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );

   // allocate command_line_handler struct
   command_line_handler_t * result = ( command_line_handler_t * ) calloc( 1, sizeof( command_line_handler_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // lock mutex
   LOCK( (*current).mutex );

   // set type
   (*result)._type = COMMAND_LINE_HANDLER_TYPE;

   (*result).fp_in = (*current).fp_in;
   (*result).fp_out = (*current).fp_out;

   (*result).help_string = string_deep_clone( (*current).help_string );
   (*result).usage_string = string_deep_clone( (*current).usage_string );
   (*result).version_string = string_deep_clone( (*current).version_string );

   (*result).commands = c_alist_deep_clone( (*current).commands );
   (*result).options = o_alist_deep_clone( (*current).options );

   (*result).last_error = string_deep_clone( (*current).last_error );

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
is_equal(  command_line_handler_t *current, command_line_handler_t *other )
{
   int32_t result = 0;

   result =
      ( string_is_equal( (*current).help_string, (*other).help_string ) == 1 )
      &&
      ( string_is_equal( (*current).usage_string, (*other).usage_string ) == 1 )
      &&
      ( string_is_equal( (*current).version_string, (*other).version_string ) == 1 )
      &&
      ( c_alist_is_equal( (*current).commands, (*other).commands ) == 1 )
      &&
      ( o_alist_is_equal( (*current).options, (*other).options ) == 1 )
      &&
      ( string_is_equal( (*current).last_error, (*other).last_error ) == 1 );

   return result;
};

/**
   command_line_handler_is_equal
*/

int32_t
command_line_handler_is_equal( command_line_handler_t *current, command_line_handler_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == COMMAND_LINE_HANDLER_TYPE );
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
is_deep_equal(  command_line_handler_t *current, command_line_handler_t *other )
{
   int32_t result = 0;

   result =
      ( string_is_deep_equal( (*current).help_string, (*other).help_string ) == 1 )
      &&
      ( string_is_deep_equal( (*current).usage_string, (*other).usage_string ) == 1 )
      &&
      ( string_is_deep_equal( (*current).version_string, (*other).version_string ) == 1 )
      &&
      ( c_alist_is_deep_equal( (*current).commands, (*other).commands ) == 1 )
      &&
      ( o_alist_is_deep_equal( (*current).options, (*other).options ) == 1 )
      &&
      ( string_is_deep_equal( (*current).last_error, (*other).last_error ) == 1 );

   return result;
};

/**
   command_line_handler_is_deep_equal
*/

int32_t
command_line_handler_is_deep_equal( command_line_handler_t *current, command_line_handler_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == COMMAND_LINE_HANDLER_TYPE );
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
   command_line_handler_copy
*/

void
command_line_handler_copy( command_line_handler_t *current, command_line_handler_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == COMMAND_LINE_HANDLER_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   (*current).fp_in = (*other).fp_in;
   (*current).fp_out = (*other).fp_out;

   string_copy( (*current).help_string, (*other).help_string );
   string_copy( (*current).usage_string, (*other).usage_string );
   string_copy( (*current).version_string, (*other).version_string );
   c_alist_copy( (*current).commands, (*other).commands );
   o_alist_copy( (*current).options, (*other).options );
   string_copy( (*current).last_error, (*other).last_error );

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   command_line_handler_deep_copy
*/

void
command_line_handler_deep_copy( command_line_handler_t *current, command_line_handler_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == COMMAND_LINE_HANDLER_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   (*current).fp_in = (*other).fp_in;
   (*current).fp_out = (*other).fp_out;

   string_deep_copy( (*current).help_string, (*other).help_string );
   string_deep_copy( (*current).usage_string, (*other).usage_string );
   string_deep_copy( (*current).version_string, (*other).version_string );
   c_alist_deep_copy( (*current).commands, (*other).commands );
   o_alist_deep_copy( (*current).options, (*other).options );
   string_deep_copy( (*current).last_error, (*other).last_error );

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   command_line_handler_dispose
*/

void
command_line_handler_dispose( command_line_handler_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == COMMAND_LINE_HANDLER_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   string_dispose( &(**current).help_string );
   string_dispose( &(**current).usage_string );
   string_dispose( &(**current).version_string );
   c_alist_dispose( &(**current).commands );
   o_alist_dispose( &(**current).options );
   string_dispose( &(**current).last_error );

   free(*current);

   // set to NULL
   *current = NULL;

   return;
}


/**
   command_line_handler_deep_dispose
*/

void
command_line_handler_deep_dispose( command_line_handler_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == COMMAND_LINE_HANDLER_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   string_deep_dispose( &(**current).help_string );
   string_deep_dispose( &(**current).usage_string );
   string_deep_dispose( &(**current).version_string );
   c_alist_deep_dispose( &(**current).commands );
   o_alist_deep_dispose( &(**current).options );
   string_deep_dispose( &(**current).last_error );

   free(*current);

   // set to NULL
   *current = NULL;

   return;
}


/**
   command_line_handler_help_string
*/

string_t *
command_line_handler_help_string( command_line_handler_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_deep_clone( (*current).help_string );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_line_handler_usage_string
*/

string_t *
command_line_handler_usage_string( command_line_handler_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_deep_clone( (*current).usage_string );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_line_handler_version_string
*/

string_t *
command_line_handler_version_string( command_line_handler_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_deep_clone( (*current).version_string );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_line_handler_last_error
*/

string_t *
command_line_handler_last_error( command_line_handler_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_deep_clone( (*current).last_error );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_line_handler_num_commands
*/

int32_t
command_line_handler_num_commands( command_line_handler_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = c_alist_count( (*current).commands );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_line_handler_command_item
*/

protocol_base_t *
command_line_handler_command_item( command_line_handler_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   PRECONDITION( "index OK", ( ( index >= 0 ) && ( index < c_alist_count( (*current).commands ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   protocol_base_t *result = c_alist_item( (*current).commands, index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_line_handler_num_options
*/

int32_t
command_line_handler_num_options( command_line_handler_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = o_alist_count( (*current).options );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_line_handler_command_item
*/

protocol_base_t *
command_line_handler_option_item( command_line_handler_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   PRECONDITION( "index OK", ( ( index >= 0 ) && ( index < o_alist_count( (*current).options ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   protocol_base_t *result = o_alist_item( (*current).options, index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
*/
static
s_alist_t *
get_arguments( s_alist_t *tokens )
{
   s_alist_t *result = NULL;
   string_t *token = NULL;

   result = s_alist_make();

   // parameters are tokens from current tokens location to first item in tokens
   // that begins with '-'
   if ( s_alist_off( tokens ) == 0 )
   {
      token = s_alist_item_at( tokens );

      while ( ( string_item( token, 0 ) != '-' ) && ( s_alist_off( tokens ) == 0 ) )
      {
         s_alist_put_last( result, token );
         s_alist_forth( tokens );
         if ( s_alist_off( tokens ) == 0 )
         {
            token = s_alist_item_at( tokens );
         }
      }
   }

   return result;
}

/**
   interpret_tokens
*/
static
void
interpret_tokens
(
   command_line_handler_t *current,
   s_alist_t *tokens,
   c_alist_t *commands,
   o_alist_t *options
)
{
   string_t *token = NULL;
   c_alist_t *registered_commands = NULL;
   o_alist_t *registered_options = NULL;
   protocol_base_t *c = NULL;
   protocol_base_t *o = NULL;
   s_alist_t * arguments = NULL;
   int32_t i = 0;
   string_t *s = NULL;

   registered_commands = (*current).commands;
   registered_options = (*current).options;

   // first token must be a command
   s_alist_start( tokens );
   token = s_alist_item_at( tokens );
   s_alist_forth( tokens );

   // match token to command
   c_alist_start( registered_commands );
   while ( c_alist_off( registered_commands ) == 0 )
   {
      c = c_alist_item_at( registered_commands );
      s = p_clh_command_short_name( c );
      if ( string_is_equal( token, s ) == 1 )
      {
         string_dispose( &s );
         arguments = get_arguments( tokens );
         for ( i = 0; i < s_alist_count( arguments ); i++ )
         {
            p_clh_command_add_argument( c, s_alist_item( arguments, i ) );
         }
         s_alist_dispose( &arguments );
         break;
      }
      else
      {
         string_dispose( &s );
      }

      s = p_clh_command_long_name( c );
      if ( string_is_equal( token, s ) == 1 )
      {
         string_dispose( &s );
         arguments = get_arguments( tokens );
         for ( i = 0; i < s_alist_count( arguments ); i++ )
         {
            p_clh_command_add_argument( c, s_alist_item( arguments, i ) );
         }
         s_alist_dispose( &arguments );
         break;
      }
      else
      {
         string_dispose( &s );
      }

      c_alist_forth( registered_commands );
      c = NULL;
      o = NULL;
   }

   if ( c != NULL )
   {
      c_alist_put_last( commands, c );
   }
   else
   {
      fprintf( (*current).fp_out, "Error - non-command token %s found in command line.\n", string_as_cstring( token ) );
   }

   // rest of tokens, if any, are options
   // the current location in tokens is advanced in get_arguments
   if ( c != NULL )
   {
      while ( s_alist_off( tokens ) == 0 )
      {
         token = s_alist_item_at( tokens );
         s_alist_forth( tokens );
         o_alist_start( registered_options );
         while ( o_alist_off( registered_options ) == 0 )
         {
            o = o_alist_item_at( registered_options );
            s = p_clh_option_short_name( o );
            if ( string_is_equal( token, s ) == 1 )
            {
               string_dispose( &s );
               arguments = get_arguments( tokens );
               for ( i = 0; i < s_alist_count( arguments ); i++ )
               {
                  p_clh_option_add_argument( o, s_alist_item( arguments, i ) );
               }
               s_alist_dispose( &arguments );
               break;
            }
            else
            {
               string_dispose( &s );
            }

            s = p_clh_option_long_name( o );
            if ( string_is_equal( token, s ) == 1 )
            {
               string_dispose( &s );
               arguments = get_arguments( tokens );
               for ( i = 0; i < s_alist_count( arguments ); i++ )
               {
                  p_clh_option_add_argument( o, s_alist_item( arguments, i ) );
               }
               s_alist_dispose( &arguments );
               break;
            }
            else
            {
               string_dispose( &s );
            }

            o_alist_forth( registered_options );
            o = NULL;
         }

         if ( o != NULL )
         {
            o_alist_put_last( options, o );
         }
         else
         {
            fprintf( (*current).fp_out, "Error - extra token %s found in command line.\n", string_as_cstring( token ) );
         }

      }
   }

   return;
}

/**
   execute
*/
static
void
execute( command_line_handler_t *current )
{
   char_t *line = NULL;
   size_t size = 0;
   s_alist_t *tokens = NULL;
   c_alist_t *commands = NULL;
   o_alist_t *options = NULL;
   protocol_base_t *command = NULL;

   tokens = s_alist_make();
   commands = c_alist_make();
   options = o_alist_make();

   // loop to get input from keyboard, parse command line, handle commands
   while ( quit_flag == 0 )
   {
      // get input line
      if ( getline( &line, &size, (*current).fp_in ) == -1 )
      {
         fprintf( (*current).fp_out, "Error reading command line.\n" );
         break;
      }

      // remove newline at end of line, if present
      if ( line[ strlen( line ) - 1 ] == '\n' )
      {
         line[ strlen( line ) - 1 ] = 0;
      }

      // parse line into tokens
      get_string_tokens( line, tokens );

      if ( s_alist_count( tokens ) == 0 )
      {
         continue;
      }

      // check for quit, help, usage, or version command
      else if  (
         ( string_is_equal_cstring( s_alist_first( tokens ), "q" ) )
         ||
         ( string_is_equal_cstring( s_alist_first( tokens ), "quit" ) )
      )
      {
         fprintf( (*current).fp_out, "Exiting program.\n" );
         quit_flag = 1;
         break;

      }
      else if  (
         ( string_is_equal_cstring( s_alist_first( tokens ), "?" ) )
         ||
         ( string_is_equal_cstring( s_alist_first( tokens ), "h" ) )
         ||
         ( string_is_equal_cstring( s_alist_first( tokens ), "help" ) )
      )
      {
         fprintf( (*current).fp_out, "%s\n", string_as_cstring( (*current).help_string ) );
         continue;
      }
      else if  (
         ( string_is_equal_cstring( s_alist_first( tokens ), "u" ) )
         ||
         ( string_is_equal_cstring( s_alist_first( tokens ), "usage" ) )
      )
      {
         fprintf( (*current).fp_out, "%s\n", string_as_cstring( (*current).usage_string ) );
         continue;
      }
      else if  (
         ( string_is_equal_cstring( s_alist_first( tokens ), "v" ) )
         ||
         ( string_is_equal_cstring( s_alist_first( tokens ), "version" ) )
      )
      {
         fprintf( (*current).fp_out, "%s\n", string_as_cstring( (*current).version_string ) );
         continue;
      }

      // interpret tokens into command and options
      c_alist_wipe_out( commands );
      o_alist_wipe_out( options );
      interpret_tokens( current, tokens, commands, options );

      // execute command
      if ( c_alist_count( commands ) == 0 )
      {
         fprintf( (*current).fp_out, "Error - no command found.\n" );
      }
      else // if ( c_alist_count( commands ) == 1 )
      {
         // get the command
         command = c_alist_first( commands );

         // add options
         o_alist_start( options );
         while ( o_alist_off( options ) == 0 )
         {
            p_clh_command_add_option( command, o_alist_item_at( options ) );
            o_alist_forth( options );
         }

         // execute the command
         p_clh_command_execute( command );

         // clear the command and options
         p_clh_command_wipe_out( command );

         o_alist_start( options );
         while( o_alist_off( options ) == 0 )
         {
            p_clh_option_wipe_out( o_alist_item_at( options ) );
            o_alist_forth( options );
         }

         // wipe out commands and options
         c_alist_wipe_out( commands );
         o_alist_wipe_out( options );

      }

   }

   free( line );
   s_alist_deep_dispose( &tokens );
   c_alist_dispose( &commands );
   o_alist_dispose( &options );

   // reset quit_flag
   quit_flag = 0;

   return;
}

/**
   command_line_handler_execute
*/

void
command_line_handler_execute( command_line_handler_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   execute( current );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   command_line_handler_add_command
*/

void
command_line_handler_add_command
(
   command_line_handler_t *current,
   protocol_base_t *command
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   PRECONDITION( "command not null", command != NULL );
   PRECONDITION( "command ok", protocol_arg_ok( P_CLH_COMMAND_TYPE, command ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   c_alist_put_last( (*current).commands, command );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   command_line_handler_add_option
*/

void
command_line_handler_add_option
(
   command_line_handler_t *current,
   protocol_base_t *option
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_LINE_HANDLER_TYPE );
   PRECONDITION( "option not null", option != NULL );
   PRECONDITION( "option ok", protocol_arg_ok( P_CLH_OPTION_TYPE, option ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   o_alist_put_last( (*current).options, option );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

