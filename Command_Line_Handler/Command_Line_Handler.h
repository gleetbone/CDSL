/**
 @file Command_Line_Handler.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Specifies a time on a date"

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

 Function declarations for the opaque command_line_handler_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef COMMAND_LINE_HANDLER_T_H
#define COMMAND_LINE_HANDLER_T_H


/**
   Version
*/

#define COMMAND_LINE_HANDLER_VERSION_MAJOR 2
#define COMMAND_LINE_HANDLER_VERSION_MINOR 0
#define COMMAND_LINE_HANDLER_VERSION_PATCH 0

#define COMMAND_LINE_HANDLER_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define COMMAND_LINE_HANDLER_VERSION \
   COMMAND_LINE_HANDLER_MAKE_VERSION( COMMAND_LINE_HANDLER_VERSION_MAJOR, \
                       COMMAND_LINE_HANDLER_VERSION_MINOR, \
                       COMMAND_LINE_HANDLER_VERSION_PATCH )

/**
   Includes
*/

#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "user_defined_types.h"
#include "Protocol_Base.h"
#include "String.h"
#include "s_HSet.h"
#include "p_CLH_Command.h"
#include "p_CLH_Option.h"

/**
   Structure declaration
*/

struct command_line_handler_struct;

/**
   Structure typedef
*/

typedef struct command_line_handler_struct command_line_handler_t;


/*
   Initialization
*/

/**
   command_line_handler_make

   Create and initialize a command_line_handler_t instance from input parameters.

   @param fp_in the input file or stdin
   @param fp_out the output file or stdout
   @param help_string the text of the help string
   @param usage_string the text of the usage string
   @param version_string the text of the version string
   @return pointer to the new data structure
*/
command_line_handler_t *
command_line_handler_make
(
   FILE *fp_in,
   FILE *fp_out,
   string_t *help_string,
   string_t *usage_string,
   string_t *version_string
);

/*
   Basic
*/

/**
   command_line_handler_clone

   Create and initialize a clone of a command_line_handler_t instance.

   @param current the command_line_handler_t instance to initialize from
   @return pointer to the new data structure
*/
command_line_handler_t *
command_line_handler_clone( command_line_handler_t *current );

/**
   command_line_handler_deep_clone

   Create and initialize a deep clone of a command_line_handler_t instance.

   @param current the command_line_handler_t instance to initialize from
   @return pointer to the new data structure
*/
command_line_handler_t *
command_line_handler_deep_clone( command_line_handler_t *current );

/**
   command_line_handler_is_equal

   Returns 1 if the current contains the same values as other

   @param current the command_line_handler_t instance
   @param other the other command_line_handler_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t command_line_handler_is_equal( command_line_handler_t *current, command_line_handler_t *other );

/**
   command_line_handler_is_deep_equal

   Returns 1 if the current contains the same values as other

   @param current the command_line_handler_t instance
   @param other the other command_line_handler_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t command_line_handler_is_deep_equal( command_line_handler_t *current, command_line_handler_t *other );

/**
   command_line_handler_copy

   Puts contents of other into current

   @param current the command_line_handler_t instance to copy into
   @param other the command_line_handler_t to copy from
*/
void command_line_handler_copy( command_line_handler_t *current, command_line_handler_t *other );

/**
   command_line_handler_deep_copy

   Puts contents of other into current

   @param current the command_line_handler_t instance to copy into
   @param other the command_line_handler_t to copy from
*/
void command_line_handler_deep_copy( command_line_handler_t *current, command_line_handler_t *other );


/*
   Disposal
*/

/**
   command_line_handler_dispose

   Deallocates a command_line_handler_t instance.

   @param current pointer to the command_line_handler instance to dispose
*/
void
command_line_handler_dispose( command_line_handler_t **current );

/**
   command_line_handler_deep_dispose

   Deallocates a command_line_handler_t instance.

   @param current pointer to the command_line_handler instance to dispose
*/
void
command_line_handler_deep_dispose( command_line_handler_t **current );


/*
   Access
*/

/**
   command_line_handler_help_string

   Returns the help_string of the instance.

   @param current pointer to the command_line_handler instance
   @return the help string
*/
string_t *
command_line_handler_help_string( command_line_handler_t *current );

/**
   command_line_handler_usage_string

   Returns the usage_string of the instance.

   @param current pointer to the command_line_handler instance
   @return the usage string
*/
string_t *
command_line_handler_usage_string( command_line_handler_t *current );

/**
   command_line_handler_version_string

   Returns the version_string of the instance.

   @param current pointer to the command_line_handler instance
   @return the version string
*/
string_t *
command_line_handler_version_string( command_line_handler_t *current );

/**
   command_line_handler_last_error

   Returns last error from a invalid command line

   @param command_line_handler the command_line_handler
   @return the last error string
*/
string_t *command_line_handler_last_error( command_line_handler_t *current );

/**
   command_line_handler_num_commands

   Returns number of commands

   @param command_line_handler the command_line_handler
   @return number of commands registered
*/
int32_t command_line_handler_num_commands( command_line_handler_t *current );

/**
   command_line_handler_command_item

   Returns command by index

   @param command_line_handler the command_line_handler
   @param index of command
   @return command at index
*/
protocol_base_t *command_line_handler_command_item( command_line_handler_t *current, int32_t index );

/**
   command_line_handler_num_options

   Returns number of options

   @param command_line_handler_string the command_line_handler
   @return number of options registered
*/
int32_t command_line_handler_num_options( command_line_handler_t *current );

/**
   command_line_handler_option_item

   Returns option by index

   @param command_line_handler_string the command_line_handler
   @param index of option
   @return option at index
*/
protocol_base_t *command_line_handler_option_item( command_line_handler_t *current, int32_t index );

/*
   Measurement
*/

/*
   Basic Operations
*/

/**
   command_line_handler_execute

   Returns 1 if the command_line_handler evaluates to true, 0 if false.

   @param current the command_line_handler_t instance
*/
void command_line_handler_execute( command_line_handler_t *current );

/*
   Status Report
*/

/*
   Comparison
*/

/*
   Conversion
*/

/*
   Element Change
*/

/**
   command_line_handler_add_command

   Add a command into the instance with parameter values.

   @param current pointer to the data structure
   @param command P_Command pointer to command structure
*/
void
command_line_handler_add_command
(
   command_line_handler_t *current,
   protocol_base_t *command
);

/**
   command_line_handler_add_option

   Add an option into the instance with parameter values.

   @param current pointer to the data structure
   @param command P_Option pointer to option structure
*/
void
command_line_handler_add_option
(
   command_line_handler_t *current,
   protocol_base_t *option
);

/*
   Duplication
*/

/*
   Removal
*/

/*
   Resize
*/

#ifdef __cplusplus
}
#endif

#endif /* COMMAND_LINE_HANDLER_T_H */

/* End of file */




