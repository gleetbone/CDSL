/**
 @file Command.h
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

 Function declarations for the opaque command_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef COMMAND_T_H
#define COMMAND_T_H


/**
   Version
*/

#define COMMAND_VERSION_MAJOR 2
#define COMMAND_VERSION_MINOR 0
#define COMMAND_VERSION_PATCH 0

#define COMMAND_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define COMMAND_VERSION \
   COMMAND_MAKE_VERSION( COMMAND_VERSION_MAJOR, \
                       COMMAND_VERSION_MINOR, \
                       COMMAND_VERSION_PATCH )

/**
   Includes
*/

#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "user_defined_types.h"
#include "String.h"
#include "Protocol_Base.h"
#include "p_CLH_Option.h"

/**
   Structure declaration
*/

struct command_struct;

/**
   Structure typedef
*/

typedef struct command_struct command_t;


/**
   Defines
*/

/*
   Initialization
*/

/**
   command_make

   Create and initialize a command_t instance from input parameters.

   @param fp_out stream to print to
   @param short_name short name of the command
   @param long_name long name of the command
   @param documentation documentation of the command
   @param num_required_arguments number of required arguments
   @return pointer to the new data structure
*/
command_t *
command_make
(
   FILE *fp_out,
   string_t *short_name,
   string_t *long_name,
   string_t *documentation,
   int32_t num_required_arguments
);

/*
   Basic
*/

/**
   command_clone

   Create and initialize a clone of a command_t instance.

   @param current the command_t instance to initialize from
   @return pointer to the new data structure
*/
command_t *
command_clone( command_t *current );

/**
   command_deep_clone

   Create and initialize a deep clone of a command_t instance.

   @param current the command_t instance to initialize from
   @return pointer to the new data structure
*/
command_t *
command_deep_clone( command_t *current );

/**
   command_is_equal

   Returns 1 if the current contains the same values as other

   @param current the command_t instance
   @param other the other command_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t command_is_equal( command_t *current, command_t *other );

/**
   command_is_deep_equal

   Returns 1 if the current contains the same values as other

   @param current the command_t instance
   @param other the other command_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t command_is_deep_equal( command_t *current, command_t *other );

/**
   command_copy

   Puts contents of other into current

   @param current the command_t instance to copy into
   @param other the command_t to copy from
*/
void command_copy( command_t *current, command_t *other );

/**
   command_deep_copy

   Puts contents of other into current

   @param current the command_t instance to copy into
   @param other the command_t to copy from
*/
void command_deep_copy( command_t *current, command_t *other );


/*
   Disposal
*/

/**
   command_dispose

   Deallocates a command_t instance.

   @param current pointer to the command instance to dispose
*/
void
command_dispose( command_t **current );

/**
   command_deep_dispose

   Deallocates a command_t instance.

   @param current pointer to the command instance to dispose
*/
void
command_deep_dispose( command_t **current );


/*
   Access
*/

/**
   command_short_name

   Returns the short name of the instance.

   @param current pointer to the command instance
   @return the short name
*/
string_t *
command_short_name( command_t *current );

/**
   command_long_name

   Returns the long name of the instance.

   @param current pointer to the command instance
   @return the long name
*/
string_t *
command_long_name( command_t *current );

/**
   command_documentation

   Returns the documentation of the instance.

   @param current pointer to the command instance
   @return the short name
*/
string_t *
command_documentation( command_t *current );

/**
   command_num_required_arguments

   Returns the number of required arguments of the instance.

   @param current pointer to the command instance
   @return the number of required arguments
*/
int32_t
command_num_required_arguments( command_t *current );

/**
   command_num_arguments

   Returns the number of required arguments of the instance.

   @param current pointer to the command instance
   @return the number of required arguments
*/
int32_t
command_num_arguments( command_t *current );

/**
   command_argument_item

   Returns the argument at index.

   @param current pointer to the command instance
   @param index which argument
   @return the argument at index
*/
string_t *
command_argument_item( command_t *current, int32_t index );

/**
   command_num_options

   Returns the number of required options of the instance.

   @param current pointer to the command instance
   @return the number of required options
*/
int32_t
command_num_options( command_t *current );

/**
   command_option_item

   Returns the option at index.

   @param current pointer to the command instance
   @param index which option
   @return the option at index
*/
protocol_base_t *
command_option_item( command_t *current, int32_t index );

/*
   Measurement
*/

/*
   Basic Operations
*/

/**
   command_execute

   Executes the command.

   @param current the command_t instance
*/
void command_execute( command_t *current );

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
   command_add_argument

   Adds an argument.

   @param current pointer to the data structure
   @param argument the argument
*/
void
command_add_argument
(
   command_t *current,
   string_t *argument
);

/**
   command_add_option

   Adds an option.

   @param current pointer to the data structure
   @param p_clh_option the option
*/
void
command_add_option
(
   command_t *current,
   protocol_base_t *p_clh_option
);

/*
   Duplication
*/

/*
   Removal
*/

/**
   command_wipe_out

   Clears the arguments and options.

   @param current the command_t instance
*/
void command_wipe_out( command_t *current );

/*
   Resize
*/

#ifdef __cplusplus
}
#endif

#endif /* COMMAND_T_H */

/* End of file */




