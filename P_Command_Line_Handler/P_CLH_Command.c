/**
 @file P_CLH_Command.c
 @author Greg Lee
 @version 2.0.0
 @brief: "P_CLH_Command protocol"
 
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

 Function definitions for the p_clh_command protocol.

*/

#include "Protocol_Base.h"
#include "Protocol_Base.ph"
#include "P_CLH_Command.h"
#include "P_CLH_Command.ph"
#include "P_CLH_Option.ph"
#include "P_Indexable.ph"
   
#ifdef MULTITHREADED
#include MULTITHREAD_INCLUDE
#endif

#include "dbc.h"

/**
   Includes
*/

#include <stddef.h>

/**
   p_clh_command_short_name
*/
string_t *
P_CLH_Command_short_name( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
)
{
   PRECONDITION( "p_clh_command not null", p_clh_command != NULL );
   PRECONDITION( "p_clh_command is object", protocol_base_is_valid_object( p_clh_command ) == 1 );
   PRECONDITION( "p_clh_command supports protocol", protocol_base_supports_protocol( p_clh_command, P_CLH_COMMAND_TYPE) == 1 );

   string_t *result = NULL;
   
   string_t * (*short_name)( protocol_base_t * ) 
      = (*p_clh_command).get_function( P_CLH_COMMAND_TYPE, P_CLH_COMMAND_SHORT_NAME );

   CHECK( "P_CLH_COMMAND_SHORT_NAME function not null", short_name != NULL );

   result = short_name( p_clh_command );

   return result;
}

/**
   p_clh_command_long_name
*/
string_t *
P_CLH_Command_long_name( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
)
{
   PRECONDITION( "p_clh_command not null", p_clh_command != NULL );
   PRECONDITION( "p_clh_command is object", protocol_base_is_valid_object( p_clh_command ) == 1 );
   PRECONDITION( "p_clh_command supports protocol", protocol_base_supports_protocol( p_clh_command, P_CLH_COMMAND_TYPE ) == 1 );

   string_t * result = NULL;
   
   string_t * (*long_name)( protocol_base_t * ) 
      = (*p_clh_command).get_function( P_CLH_COMMAND_TYPE, P_CLH_COMMAND_LONG_NAME );

   CHECK( "P_CLH_COMMAND_LONG_NAME function not null", long_name != NULL );

   result = long_name( p_clh_command );

   return result;
}

/**
   p_clh_command_documentation
*/
string_t *
P_CLH_Command_documentation( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
)
{
   PRECONDITION( "p_clh_command not null", p_clh_command != NULL );
   PRECONDITION( "p_clh_command is object", protocol_base_is_valid_object( p_clh_command ) == 1 );
   PRECONDITION( "p_clh_command supports protocol", protocol_base_supports_protocol( p_clh_command, P_CLH_COMMAND_TYPE ) == 1 );

   string_t *result = NULL;
   
   string_t * (*documentation)( protocol_base_t * ) 
      = (*p_clh_command).get_function( P_CLH_COMMAND_TYPE, P_CLH_COMMAND_DOCUMENTATION );

   CHECK( "P_CLH_COMMAND_DOCUMENTATION function not null", documentation != NULL );

   result = documentation( p_clh_command );

   return result;
}

/**
   p_clh_command_num_required_arguments
*/
int32_t
P_CLH_Command_num_required_arguments( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
)
{
   PRECONDITION( "p_clh_command not null", p_clh_command != NULL );
   PRECONDITION( "p_clh_command is object", protocol_base_is_valid_object( p_clh_command ) == 1 );
   PRECONDITION( "p_clh_command supports protocol", protocol_base_supports_protocol( p_clh_command, P_CLH_COMMAND_TYPE ) == 1 );

   int32_t result = 0;
   
   int32_t (*num_required_arguments)( protocol_base_t * ) 
      = (*p_clh_command).get_function( P_CLH_COMMAND_TYPE, P_CLH_COMMAND_NUM_REQUIRED_ARGUMENTS );

   CHECK( "P_CLH_COMMAND_NUM_REQUIRED_ARGUMENTS function not null", num_required_arguments != NULL );

   result = num_required_arguments( p_clh_command );

   return result;
}

/**
   p_clh_command_num_arguments
*/
int32_t
P_CLH_Command_num_arguments( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
)
{
   PRECONDITION( "p_clh_command not null", p_clh_command != NULL );
   PRECONDITION( "p_clh_command is object", protocol_base_is_valid_object( p_clh_command ) == 1 );
   PRECONDITION( "p_clh_command supports protocol", protocol_base_supports_protocol( p_clh_command, P_CLH_COMMAND_TYPE ) == 1 );

   int32_t result = 0;
   
   int32_t (*num_arguments)( protocol_base_t * ) 
      = (*p_clh_command).get_function( P_CLH_COMMAND_TYPE, P_CLH_COMMAND_NUM_ARGUMENTS );

   CHECK( "P_CLH_COMMAND_NUM_ARGUMENTS function not null", num_arguments != NULL );

   result = num_arguments( p_clh_command );

   return result;
}

/**
   p_clh_command_argument_item
*/
string_t *
P_CLH_Command_argument_item( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command,
   int32_t index
)
{
   PRECONDITION( "p_clh_command not null", p_clh_command != NULL );
   PRECONDITION( "p_clh_command is object", protocol_base_is_valid_object( p_clh_command ) == 1 );
   PRECONDITION( "p_clh_command supports protocol", protocol_base_supports_protocol( p_clh_command, P_CLH_COMMAND_TYPE ) == 1 );

   string_t *result = NULL;
   
   string_t * (*argument_item)( protocol_base_t *, int32_t ) 
      = (*p_clh_command).get_function( P_CLH_COMMAND_TYPE, P_CLH_COMMAND_ARGUMENT_ITEM );

   CHECK( "P_CLH_COMMAND_ARGUMENT_ITEM function not null", argument_item != NULL );

   result = argument_item( p_clh_command, index );

   return result;
}

/**
   p_clh_command_num_options
*/
int32_t
P_CLH_Command_num_options( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
)
{
   PRECONDITION( "p_clh_command not null", p_clh_command != NULL );
   PRECONDITION( "p_clh_command is object", protocol_base_is_valid_object( p_clh_command ) == 1 );
   PRECONDITION( "p_clh_command supports protocol", protocol_base_supports_protocol( p_clh_command, P_CLH_COMMAND_TYPE ) == 1 );

   int32_t result = 0;
   
   int32_t (*num_options)( protocol_base_t * ) 
      = (*p_clh_command).get_function( P_CLH_COMMAND_TYPE, P_CLH_COMMAND_NUM_OPTIONS );

   CHECK( "P_CLH_COMMAND_NUM_OPTIONS function not null", num_options != NULL );

   result = num_options( p_clh_command );

   return result;
}

/**
   p_clh_command_option_item
*/
protocol_base_t *
P_CLH_Command_option_item( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command,
   int32_t index
)
{
   PRECONDITION( "p_clh_command not null", p_clh_command != NULL );
   PRECONDITION( "p_clh_command is object", protocol_base_is_valid_object( p_clh_command ) == 1 );
   PRECONDITION( "p_clh_command supports protocol", protocol_base_supports_protocol( p_clh_command, P_CLH_COMMAND_TYPE ) == 1 );

   protocol_base_t *result = NULL;
   
   protocol_base_t * (*option_item)( protocol_base_t *, int32_t ) 
      = (*p_clh_command).get_function( P_CLH_COMMAND_TYPE, P_CLH_COMMAND_OPTION_ITEM );

   CHECK( "P_CLH_COMMAND_OPTION_ITEM function not null", option_item != NULL );

   result = option_item( p_clh_command, index );

   return result;
}

/**
   p_clh_command_execute
*/
void
P_CLH_Command_execute( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
)
{
   PRECONDITION( "p_clh_command not null", p_clh_command != NULL );
   PRECONDITION( "p_clh_command is object", protocol_base_is_valid_object( p_clh_command ) == 1 );
   PRECONDITION( "p_clh_command supports protocol", protocol_base_supports_protocol( p_clh_command, P_CLH_COMMAND_TYPE ) == 1 );

   void (*execute)( protocol_base_t * ) 
      = (*p_clh_command).get_function( P_CLH_COMMAND_TYPE, P_CLH_COMMAND_EXECUTE );

   CHECK( "P_CLH_COMMAND_EXECUTE function not null", execute != NULL );

   execute( p_clh_command );

   return;
}

/**
   p_clh_command_add_argument
*/
void
P_CLH_Command_add_argument( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command,
   string_t *argument
)
{
   PRECONDITION( "p_clh_command not null", p_clh_command != NULL );
   PRECONDITION( "p_clh_command is object", protocol_base_is_valid_object( p_clh_command ) == 1 );
   PRECONDITION( "p_clh_command supports protocol", protocol_base_supports_protocol( p_clh_command, P_CLH_COMMAND_TYPE ) == 1 );
   PRECONDITION( "argument not null", argument != NULL );

   void (*add_argument)( protocol_base_t *, string_t * ) 
      = (*p_clh_command).get_function( P_CLH_COMMAND_TYPE, P_CLH_COMMAND_ADD_ARGUMENT );

   CHECK( "P_CLH_COMMAND_ADD_ARGUMENT function not null", add_argument != NULL );

   add_argument( p_clh_command, argument );

   return;
}

/**
   p_clh_command_add_option
*/
void
P_CLH_Command_add_option( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command,
   protocol_base_t *p_clh_option
)
{
   PRECONDITION( "p_clh_command not null", p_clh_command != NULL );
   PRECONDITION( "p_clh_command is object", protocol_base_is_valid_object( p_clh_command ) == 1 );
   PRECONDITION( "p_clh_command supports protocol", protocol_base_supports_protocol( p_clh_command, P_CLH_COMMAND_TYPE ) == 1 );
   PRECONDITION( "p_clh_option not null", p_clh_option != NULL );
   PRECONDITION( "p_clh_option is object", protocol_base_is_valid_object( p_clh_option ) == 1 );
   PRECONDITION( "p_clh_option supports protocol", protocol_base_supports_protocol( p_clh_option, P_CLH_OPTION_TYPE ) == 1 );

   void (*add_option)( protocol_base_t *, protocol_base_t * ) 
      = (*p_clh_command).get_function( P_CLH_COMMAND_TYPE, P_CLH_COMMAND_ADD_OPTION );

   CHECK( "P_CLH_COMMAND_ADD_OPTION function not null", add_option != NULL );

   add_option( p_clh_command, p_clh_option );

   return;
}

/**
   p_clh_command_wipe_out
*/
void
P_CLH_Command_wipe_out( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
)
{
   PRECONDITION( "p_clh_command not null", p_clh_command != NULL );
   PRECONDITION( "p_clh_command is object", protocol_base_is_valid_object( p_clh_command ) == 1 );
   PRECONDITION( "p_clh_command supports protocol", protocol_base_supports_protocol( p_clh_command, P_CLH_COMMAND_TYPE ) == 1 );

   void (*wipe_out)( protocol_base_t * ) 
      = (*p_clh_command).get_function( P_CLH_COMMAND_TYPE, P_CLH_COMMAND_WIPE_OUT );

   CHECK( "P_CLH_COMMAND_WIPE_OUT function not null", wipe_out != NULL );

   wipe_out( p_clh_command );

   return;
}

/* End of file */




