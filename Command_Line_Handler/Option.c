/**
 @file Option.c
 @author Greg Lee
 @version 2.0.0
 @brief: "Holds an optiion for the command_line_handler"

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

 Function definitions for the opaque option_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Option.h"
#include "s_AList.h"
#include "o_AList.h"

#define PROTOCOLS_ENABLED

#include "protocol.h"

#ifdef PROTOCOLS_ENABLED
#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_Basic.ph"
#include "P_CLH_Option.ph"
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
   option structure
*/

struct option_struct
{

   PROTOCOLS_DEFINITION;

   int32_t _type;

   string_t *short_name;
   string_t *long_name;
   string_t *documentation;
   int32_t num_required_arguments;
   s_alist_t *arguments;

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
members_ok( option_t *current )
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
         ( (*current).arguments != NULL );

   return result;
}


static
void invariant( option_t *current )
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
   option_dispose,
   option_deep_dispose,
   option_is_equal,
   option_is_deep_equal,
   option_copy,
   option_deep_copy,
   option_clone,
   option_deep_clone
};

static
void *
p_clh_option_table[P_CLH_OPTION_FUNCTION_COUNT]
=
{
   option_short_name,
   option_long_name,
   option_documentation,
   option_num_required_arguments,
   option_num_arguments,
   option_argument_item,
   option_add_argument,
   option_wipe_out
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

      case P_CLH_OPTION_TYPE:
      {
         if ( ( function_id >= 0 ) && ( function_id <= P_CLH_OPTION_FUNCTION_MAX ) )
         {
            result = p_clh_option_table[ function_id ];
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

      case P_CLH_OPTION_TYPE:
      {
         result = 1;
         break;
      }

   }

   return result;
}

#endif // PROTOCOLS_ENABLED

/**
   option_make
*/

option_t *
option_make
(
   string_t *short_name,
   string_t *long_name,
   string_t *documentation,
   int32_t num_required_arguments
)
{
   PRECONDITION( "short_name not null", short_name != NULL );
   PRECONDITION( "long_name not null", long_name != NULL );
   PRECONDITION( "documentation not null", documentation != NULL );

   // allocate option struct
   option_t * result = ( option_t * ) calloc( 1, sizeof( option_t ) );
   CHECK( "result allocated correctly", result != NULL );
   
   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // set type
   (*result)._type = OPTION_TYPE;

   // init values
   (*result).short_name = string_clone( short_name );
   (*result).long_name = string_clone( long_name );
   (*result).documentation = string_clone( documentation );
   (*result).num_required_arguments = num_required_arguments;

   (*result).arguments = s_alist_make();

   MULTITHREAD_MUTEX_INIT( (*result).mutex );

   INVARIANT( result );

   return result;
}

/**
   option_clone
*/

option_t *
option_clone( option_t *current )
{
   PRECONDITION( "option not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == OPTION_TYPE );

   // allocate option struct
   option_t * result = ( option_t * ) calloc( 1, sizeof( option_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // lock mutex
   LOCK( (*current).mutex );

   // set type
   (*result)._type = OPTION_TYPE;

   (*result).short_name = string_clone( (*current).short_name );
   (*result).long_name = string_clone( (*current).long_name );
   (*result).documentation = string_clone( (*current).documentation );
   (*result).num_required_arguments = (*current).num_required_arguments;

   (*result).arguments = s_alist_clone( (*current).arguments );

   // unlock mutex
   UNLOCK( (*current).mutex );

   INVARIANT( current );

   return result;
}

/**
   option_deep_clone
*/

option_t *
option_deep_clone( option_t *current )
{
   PRECONDITION( "option not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == OPTION_TYPE );

   // allocate option struct
   option_t * result = ( option_t * ) calloc( 1, sizeof( option_t ) );
   CHECK( "result allocated correctly", result != NULL );

   // initialize protocol functions if protocols enabled
   PROTOCOLS_INIT( result );

   // lock mutex
   LOCK( (*current).mutex );

   // set type
   (*result)._type = OPTION_TYPE;

   (*result).short_name = string_deep_clone( (*current).short_name );
   (*result).long_name = string_deep_clone( (*current).long_name );
   (*result).documentation = string_deep_clone( (*current).documentation );
   (*result).num_required_arguments = (*current).num_required_arguments;

   (*result).arguments = s_alist_deep_clone( (*current).arguments );

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
is_equal(  option_t *current, option_t *other )
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
      ( s_alist_is_equal( (*current).arguments, (*other).arguments ) == 1 );

   return result;
};

/**
   option_is_equal
*/

int32_t
option_is_equal( option_t *current, option_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == OPTION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == OPTION_TYPE );
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
is_deep_equal(  option_t *current, option_t *other )
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
      ( s_alist_is_deep_equal( (*current).arguments, (*other).arguments ) == 1 );

   return result;
};

/**
   option_is_deep_equal
*/

int32_t
option_is_deep_equal( option_t *current, option_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == OPTION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == OPTION_TYPE );
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
   option_copy
*/

void
option_copy( option_t *current, option_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == OPTION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == OPTION_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   string_copy( (*current).short_name, (*other).short_name );
   string_copy( (*current).long_name, (*other).long_name );
   string_copy( (*current).documentation, (*other).documentation );
   (*current).num_required_arguments = (*other).num_required_arguments;
   s_alist_copy( (*current).arguments, (*other).arguments );

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   option_deep_copy
*/

void
option_deep_copy( option_t *current, option_t *other )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == OPTION_TYPE );
   PRECONDITION( "other not null", other != NULL );
   PRECONDITION( "other type OK", (*other)._type == OPTION_TYPE );

   INVARIANT( current );
   INVARIANT( other );

   // lock mutex
   LOCK( (*current).mutex );
   LOCK( (*other).mutex );

   string_deep_copy( (*current).short_name, (*other).short_name );
   string_deep_copy( (*current).long_name, (*other).long_name );
   string_deep_copy( (*current).documentation, (*other).documentation );
   (*current).num_required_arguments = (*other).num_required_arguments;
   s_alist_deep_copy( (*current).arguments, (*other).arguments );

   INVARIANT( current );
   INVARIANT( other );

   // unlock mutex
   UNLOCK( (*other).mutex );
   UNLOCK( (*current).mutex );

   return;
}

/**
   option_dispose
*/

void
option_dispose( option_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == OPTION_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   string_dispose( &(**current).short_name );
   string_dispose( &(**current).long_name );
   string_dispose( &(**current).documentation );
   s_alist_dispose( &(**current).arguments );

   free(*current);

   // set to NULL
   *current = NULL;

   return;
}


/**
   option_deep_dispose
*/

void
option_deep_dispose( option_t **current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "*current not null", *current != NULL );
   PRECONDITION( "current type OK", (**current)._type == OPTION_TYPE );
   LOCK( (**current).mutex );
   INVARIANT(*current);

   MULTITHREAD_MUTEX_DESTROY( (**current).mutex );

   string_deep_dispose( &(**current).short_name );
   string_deep_dispose( &(**current).long_name );
   string_deep_dispose( &(**current).documentation );
   s_alist_deep_dispose( &(**current).arguments );

   free(*current);

   // set to NULL
   *current = NULL;

   return;
}


/**
   option_short_name
*/

string_t *
option_short_name( option_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == OPTION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_clone( (*current).short_name );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   option_long_name
*/

string_t *
option_long_name( option_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == OPTION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_clone( (*current).long_name );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   option_documentation
*/

string_t *
option_documentation( option_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == OPTION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = string_clone( (*current).documentation );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   option_num_required_arguments
*/

int32_t
option_num_required_arguments( option_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == OPTION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = (*current).num_required_arguments;

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   option_num_arguments
*/

int32_t
option_num_arguments( option_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == OPTION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   int32_t result = s_alist_count( (*current).arguments );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   option_argument_item
*/

string_t *
option_argument_item( option_t *current, int32_t index )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == OPTION_TYPE );
   PRECONDITION( "index ok", ( ( index >= 0 ) && ( index < s_alist_count( (*current).arguments ) ) ) );
   LOCK( (*current).mutex );
   INVARIANT( current );

   string_t *result = s_alist_item( (*current).arguments, index );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return result;
}

/**
   option_add_argument
*/

void
option_add_argument
(
   option_t *current,
   string_t *argument
)
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == OPTION_TYPE );
   PRECONDITION( "argument not null", argument != NULL );
   LOCK( (*current).mutex );
   INVARIANT( current );

   s_alist_put_last( (*current).arguments, argument );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

/**
   option_wipe_out
*/

void
option_wipe_out( option_t *current )
{
   PRECONDITION( "current not null", current != NULL );
   PRECONDITION( "current type OK", (*current)._type == OPTION_TYPE );
   LOCK( (*current).mutex );
   INVARIANT( current );

   s_alist_wipe_out( (*current).arguments );

   INVARIANT( current );
   UNLOCK( (*current).mutex );

   return;
}

#ifdef __cplusplus
}
#endif

/* End of file */

