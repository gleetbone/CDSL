/**
 @file P_CLH_Command.h
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

 Function declarations for the p_clh_command protocol.

*/

#include "base.h"
#include "Protocol_Base.h"
#include "user_defined_types.h"
#include "String.h"

/**
   Note that this include file does NOT have an include guard - it may 
   be included multiple times with different macro defintions.
   
   Defines that must be present (external to this file):
   
   P_CLH_Command_Prefix - string used to name this container type
   Type   - the type of the value
   
*/

/**
   Defines
*/


/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

/**
   Includes
*/

/**
   p_clh_command_short_name

   returns short name

   @param p_clh_command the pointer to the command
   @return the short name
*/
#define P_CLH_Command_short_name( arg ) PRIMITIVE_CAT( arg, _clh_command_short_name )
string_t *
P_CLH_Command_short_name( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
);

/**
   p_clh_command_long_name

   returns long name

   @param p_clh_command the pointer to the command
   @return the long name
*/
#define P_CLH_Command_long_name( arg ) PRIMITIVE_CAT( arg, _clh_command_long_name )
string_t *
P_CLH_Command_long_name( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
);

/**
   p_clh_command_documentation

   returns documentation string

   @param p_clh_command the pointer to the command
   @return the documentation string
*/
#define P_CLH_Command_documentation( arg ) PRIMITIVE_CAT( arg, _clh_command_documentation )
string_t *
P_CLH_Command_documentation( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
);

/**
   p_clh_command_num_required_arguments

   returns the number of required arguments to the command

   @param p_clh_command the pointer to the command
   @return number of required arguments to the command
*/
#define P_CLH_Command_num_required_arguments( arg ) PRIMITIVE_CAT( arg, _clh_command_num_required_arguments )
int32_t
P_CLH_Command_num_required_arguments( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
);

/**
   p_clh_command_num_arguments

   returns the number of arguments for the command

   @param p_clh_command the pointer to the command
   @return number of arguments for the command
*/
#define P_CLH_Command_num_arguments( arg ) PRIMITIVE_CAT( arg, _clh_command_num_arguments )
int32_t
P_CLH_Command_num_arguments( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
);

/**
   p_clh_command_argument_item

   returns the argument at index

   @param p_clh_command the pointer to the command
   @param index which argument
   @return argument at index
*/
#define P_CLH_Command_argument_item( arg ) PRIMITIVE_CAT( arg, _clh_command_argument_item )
string_t *
P_CLH_Command_argument_item( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command,
   int32_t index
);

/**
   p_clh_command_num_options

   returns the number of options for the command

   @param p_clh_command the pointer to the command
   @return number of options for the command
*/
#define P_CLH_Command_num_options( arg ) PRIMITIVE_CAT( arg, _clh_command_num_options )
int32_t
P_CLH_Command_num_options( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
);

/**
   p_clh_command_option_item

   returns the option at index

   @param p_clh_command the pointer to the command
   @param index which option
   @return option at index
*/
#define P_CLH_Command_option_item( arg ) PRIMITIVE_CAT( arg, _clh_command_option_item )
protocol_base_t *
P_CLH_Command_option_item( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command,
   int32_t index
);

/**
   p_clh_command_execute

   executes command

   @param p_clh_command the pointer to the command
*/
#define P_CLH_Command_execute( arg ) PRIMITIVE_CAT( arg, _clh_command_execute )
void
P_CLH_Command_execute( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
);

/**
   p_clh_command_add_argument

   adds a command argument

   @param p_clh_command the pointer to the command
   @param argument arguments to add
*/
#define P_CLH_Command_add_argument( arg ) PRIMITIVE_CAT( arg, _clh_command_add_argument )
void
P_CLH_Command_add_argument( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command,
   string_t *argument
);

/**
   p_clh_command_add_option

   adds an option

   @param p_clh_command the pointer to the command
   @param option the option to add
   @param parameters list of parameters of option to add
*/
#define P_CLH_Command_add_option( arg ) PRIMITIVE_CAT( arg, _clh_command_add_option )
void
P_CLH_Command_add_option( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command,
   protocol_base_t *p_clh_option
);

/**
   p_clh_command_wipe_out

   clears arguments and options

   @param p_clh_command the pointer to the command
*/
#define P_CLH_Command_wipe_out( arg ) PRIMITIVE_CAT( arg, _clh_command_wipe_out )
void
P_CLH_Command_wipe_out( P_CLH_Command_Prefix )
(
   protocol_base_t *p_clh_command
);

/* End of file */




