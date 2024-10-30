/**
 @file Command.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Holds a command for the command_line_handler"

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

 Function definitions for the opaque command_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Command.h"
#include "s_AList.h"
#include "o_AList.h"

#define PROTOCOLS_ENABLED

#include "protocol.h"

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_CLH_Command.ph"
#include "P_CLH_Option.ph"
#endif // PROTOCOLS_ENABLED   

// take care of undefined prototypes

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   defines
*/

/**
   command structure
*/

struct command_struct
{

   PROTOCOLS_DEFINITION;

   int32_t _type;

   FILE *fp_out;
   string_t *short_name;
   string_t *long_name;
   string_t *documentation;
   int32_t num_required_arguments;
   s_alist_t *arguments;
   o_alist_t *options;

   MULTITHREAD_MUTEX_DEFINITION( mutex );
};

/**
   Local Functions and  Prototypes
*/


/**
   File variables
*/

#if INVARIANT_CONDITIONAL != 0

static
int32_t
members_ok( command_t *current )
{
   int32_t result = 1;

   result
      =  ( (*current).short_name != NULL )
         &&
         ( (*current).long_name != NULL )
         &&
         ( (*current).documentation != NULL )
         &&
         ( (*current).num_required_arguments >= 0 )
         &&
         ( (*current).arguments != NULL )
         &&
         ( (*current).options != NULL );

   return result;
}


static
void invariant( command_t *current )
{
   assert( ( ( void ) "members ok", members_ok( current ) ) );
   return;
}

#endif

/**
   Protocol stuff
*/

#ifdef PROTOCOLS_ENABLED

/**
   math_operation protocol function array
*/

/**
   basic protocol function array
*/

static
void *
p_basic_table[P_BASIC_FUNCTION_COUNT]
=
{
   command_dispose,
   command_deep_dispose,
   command_is_equal,
   command_is_deep_equal,
   command_copy,
   command_deep_copy,
   command_clone,
   command_deep_clone
};

static
void *
p_clh_command_table[P_CLH_COMMAND_FUNCTION_COUNT]
=
{
   command_short_name,
   command_long_name,
   command_documentation,
   command_num_required_arguments,
   command_num_arguments,
   command_argument_item,
   command_num_options,
   command_option_item,
   command_execute,
   command_add_argument,
   command_add_option,
   command_wipe_out
};

/**
   protocol get_function
*/

static
void *
get_function
(
   int32_t protocol_id,
   int32_t function_id
)
{
   PRECONDITION( "protocol id is ok", protocol_base_is_valid_protocol( protocol_id ) == 1 );

   void *result = NULL;

   switch ( protocol_id )
   {
      case P_BASIC_TYPE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_BASIC_FUNCTION_MAX ) )
         {
            result = p_basic_table[ function_id ];
         }
         break;
      }

      case P_CLH_COMMAND_TYPE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_CLH_COMMAND_FUNCTION_MAX ) )
         {
            result = p_clh_command_table[ function_id ];
         }
         break;
      }

   }

   return result;
}

/**
   protocol supports_protocol
*/

static
int32_t
supports_protocol
(
   int32_t protocol_id
)
{
   PRECONDITION( "protocol id is ok", protocol_base_is_valid_protocol( protocol_id ) == 1 );

   int32_t result = 0;

   switch ( protocol_id )
   {
      case P_BASIC_TYPE:
      {
         result = 1;
         break;
      }

      case P_CLH_COMMAND_TYPE:
      {
         result = 1;
         break;
      }

   }

   return result;
}

#endif // PROTOCOLS_ENABLED

/**
   command_make
*/

command_t *
command_make
(
   FILE *fp_out,
   string_t *short_name,
   string_t *long_name,
   string_t *documentation,
   int32_t num_required_arguments
)
{
   PRECONDITION( "fp_out not null", fp_out != NULL );
   PRECONDITION( "short_name not null", short_name != NULL );
   PRECONDITION( "long_name not null", long_name != NULL );
   PRECONDITION( "documentation not null", documentation != NULL );

   // allocate command struct
   command_t * result = ( command_t * ) calloc( 1, sizeof( command_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type
   (*result)._type = COMMAND_TYPE;

   // init values
   (*result).fp_out = fp_out;
   (*result).short_name = string_clone( short_name );
   (*result).long_name = string_clone( long_name );
   (*result).documentation = string_clone( documentation );
   (*result).num_required_arguments = num_required_arguments;

   (*result).arguments = s_alist_make();
   (*result).options = o_alist_make();

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   command_clone
*/

command_t *
command_clone( command_t *current )
{
   PRECONDITION( "command not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );

   // allocate command struct
   command_t * result = ( command_t * ) calloc( 1, sizeof( command_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // lock mutex
   LOCK( (*current).mutex );

   // set type
   (*result)._type = COMMAND_TYPE;

   (*result).fp_out = (*current).fp_out;
   (*result).short_name = string_clone( (*current).short_name );
   (*result).long_name = string_clone( (*current).long_name );
   (*result).documentation = string_clone( (*current).documentation );
   (*result).num_required_arguments = (*current).num_required_arguments;

   (*result).arguments = s_alist_clone( (*current).arguments );
   (*result).options = o_alist_clone( (*current).options );

   // unlock mutex
   UNLOCK( (*current).mutex );

   INVARIANT( current );

   return result;
}

/**
   command_deep_clone
*/

command_t *
command_deep_clone( command_t *current )
{
   PRECONDITION( "command not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );

   // allocate command struct
   command_t * result = ( command_t * ) calloc( 1, sizeof( command_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // lock mutex
   LOCK( (*current).mutex );

   // set type
   (*result)._type = COMMAND_TYPE;

   (*result).fp_out = (*current).fp_out;
   (*result).short_name = string_deep_clone( (*current).short_name );
   (*result).long_name = string_deep_clone( (*current).long_name );
   (*result).documentation = string_deep_clone( (*current).documentation );
   (*result).num_required_arguments = (*current).num_required_arguments;

   (*result).arguments = s_alist_deep_clone( (*current).arguments );
   (*result).options = o_alist_deep_clone( (*current).options );

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
is_equal(  command_t *current, command_t *other )
{
   int32_t result = 0;

   result =
      ( string_is_equal( (*current).short_name, (*other).short_name ) == 1 )
      &&
      ( string_is_equal( (*current).long_name, (*other).long_name ) == 1 )
      &&
      ( string_is_equal( (*current).documentation, (*other).documentation ) == 1 )
      &&
      ( (*current).num_required_arguments == (*other).num_required_arguments  )
      &&
      ( s_alist_is_equal( (*current).arguments, (*other).arguments ) == 1 )
      &&
      ( o_alist_is_equal( (*current).options, (*other).options ) == 1 );

   return result;
};

/**
   command_is_equal
*/

int32_t
command_is_equal( command_t *current, command_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == COMMAND_TYPE );
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
is_deep_equal(  command_t *current, command_t *other )
{
   int32_t result = 0;

   result =
      ( string_is_deep_equal( (*current).short_name, (*other).short_name ) == 1 )
      &&
      ( string_is_deep_equal( (*current).long_name, (*other).long_name ) == 1 )
      &&
      ( string_is_deep_equal( (*current).documentation, (*other).documentation ) == 1 )
      &&
      ( (*current).num_required_arguments == (*other).num_required_arguments  )
      &&
      ( s_alist_is_deep_equal( (*current).arguments, (*other).arguments ) == 1 )
      &&
      ( o_alist_is_deep_equal( (*current).options, (*other).options ) == 1 );

   return result;
};

/**
   command_is_deep_equal
*/

int32_t
command_is_deep_equal( command_t *current, command_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == COMMAND_TYPE );
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
   command_copy
*/

void
command_copy( command_t *current, command_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == COMMAND_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   (*current).fp_out = (*other).fp_out;
   string_copy( (*current).short_name, (*other).short_name );
   string_copy( (*current).long_name, (*other).long_name );
   string_copy( (*current).documentation, (*other).documentation );
   (*current).num_required_arguments = (*other).num_required_arguments;
   s_alist_copy( (*current).arguments, (*other).arguments );
   o_alist_copy( (*current).options, (*other).options );

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   command_deep_copy
*/

void
command_deep_copy( command_t *current, command_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == COMMAND_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   (*current).fp_out = (*other).fp_out;
   string_deep_copy( (*current).short_name, (*other).short_name );
   string_deep_copy( (*current).long_name, (*other).long_name );
   string_deep_copy( (*current).documentation, (*other).documentation );
   (*current).num_required_arguments = (*other).num_required_arguments;
   s_alist_deep_copy( (*current).arguments, (*other).arguments );
   o_alist_deep_copy( (*current).options, (*other).options );

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   command_dispose
*/

void
command_dispose( command_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == COMMAND_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   string_dispose( &(**current).short_name );
   string_dispose( &(**current).long_name );
   string_dispose( &(**current).documentation );
   s_alist_dispose( &(**current).arguments );
   o_alist_dispose( &(**current).options );

   free(*current);

   // set to NULL
   *current = NULL;

   return;
}


/**
   command_deep_dispose
*/

void
command_deep_dispose( command_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == COMMAND_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   string_deep_dispose( &(**current).short_name );
   string_deep_dispose( &(**current).long_name );
   string_deep_dispose( &(**current).documentation );
   s_alist_deep_dispose( &(**current).arguments );
   o_alist_deep_dispose( &(**current).options );

   free(*current);

   // set to NULL
   *current = NULL;

   return;
}


/**
   command_short_name
*/

string_t *
command_short_name( command_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_clone( (*current).short_name );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_long_name
*/

string_t *
command_long_name( command_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_clone( (*current).long_name );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_documentation
*/

string_t *
command_documentation( command_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_clone( (*current).documentation );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_num_required_arguments
*/

int32_t
command_num_required_arguments( command_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).num_required_arguments;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_num_arguments
*/

int32_t
command_num_arguments( command_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = s_alist_count( (*current).arguments );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_argument_item
*/

string_t *
command_argument_item( command_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < s_alist_count( (*current).arguments ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = s_alist_item( (*current).arguments, index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_num_options
*/

int32_t
command_num_options( command_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = o_alist_count( (*current).options );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_option_item
*/

protocol_base_t *
command_option_item( command_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < o_alist_count( (*current).options ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   protocol_base_t *result = o_alist_item( (*current).options, index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   command_execute
*/

void
command_execute( command_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   s_alist_t *arguments = NULL;
   protocol_base_t *option = NULL;
   int32_t i = 0;
   int32_t n_arguments = 0;
   string_t *s = NULL;

   fprintf( (*current).fp_out, "%s ", string_as_cstring( (*current).short_name ) );

   arguments = (*current).arguments;
   s_alist_start( arguments );
   while ( s_alist_off( arguments ) == 0 )
   {
      fprintf( (*current).fp_out, "%s ", string_as_cstring( s_alist_item_at( arguments ) ) );
      s_alist_forth( arguments );
   }

   o_alist_start( (*current).options );
   while ( o_alist_off( (*current).options ) == 0 )
   {
      option = o_alist_item_at( (*current).options );

      s = p_clh_option_short_name( option );
      fprintf( (*current).fp_out, "%s ", string_as_cstring( s ) );
      string_dispose( &s );

      n_arguments = p_clh_option_num_arguments( option );

      for ( i = 0; i < n_arguments; i++ )
      {
         fprintf( (*current).fp_out, "%s ", string_as_cstring( p_clh_option_argument_item( option, i ) ) );
      }

      o_alist_forth( (*current).options );
   }

   fprintf( (*current).fp_out, "\n" );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   command_add_argument
*/

void
command_add_argument
(
   command_t *current,
   string_t *argument
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   PRECONDITION( "argument not null", argument != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   s_alist_put_last( (*current).arguments, argument );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   command_add_option
*/

void
command_add_option
(
   command_t *current,
   protocol_base_t *option
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   PRECONDITION( "option not null", option != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   o_alist_put_last( (*current).options, option );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   command_wipe_out
*/

void
command_wipe_out( command_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == COMMAND_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   s_alist_wipe_out( (*current).arguments );
   o_alist_wipe_out( (*current).options );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

