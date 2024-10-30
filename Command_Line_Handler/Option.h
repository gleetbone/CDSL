/**
 @file Option.h
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

 Function declarations for the opaque option_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OPTION_T_H
#define OPTION_T_H


/**
   Version
*/

#define OPTION_VERSION_MAJOR 2
#define OPTION_VERSION_MINOR 0
#define OPTION_VERSION_PATCH 0

#define OPTION_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define OPTION_VERSION \
   OPTION_MAKE_VERSION( OPTION_VERSION_MAJOR, \
                       OPTION_VERSION_MINOR, \
                       OPTION_VERSION_PATCH )

/**
   Includes
*/

#include <stdio.h>
#include <stdlib.h>

#include "base.h"
#include "user_defined_types.h"
#include "String.h"
#include "Protocol_Base.h"

/**
   Structure declaration
*/

struct option_struct;

/**
   Structure typedef
*/

typedef struct option_struct option_t;


/**
   Defines
*/

/**
   Initialization
*/

/*
   option_make

   Create and initialize a option_t instance from input parameters.

   @param short_name short name of the option
   @param long_name long name of the option
   @param documentation documentation of the option
   @param num_required_arguments number of required arguments
   @return pointer to the new data structure
*/
option_t *
option_make
(
   string_t *short_name,
   string_t *long_name,
   string_t *documentation,
   int32_t num_required_arguments
);

/*
   Basic
*/

/**
   option_clone

   Create and initialize a clone of a option_t instance.

   @param current the option_t instance to initialize from
   @return pointer to the new data structure
*/
option_t *
option_clone( option_t *current );

/**
   option_deep_clone

   Create and initialize a deep clone of a option_t instance.

   @param current the option_t instance to initialize from
   @return pointer to the new data structure
*/
option_t *
option_deep_clone( option_t *current );

/**
   option_is_equal

   Returns 1 if the current contains the same values as other

   @param current the option_t instance
   @param other the other option_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t option_is_equal( option_t *current, option_t *other );

/**
   option_is_deep_equal

   Returns 1 if the current contains the same values as other

   @param current the option_t instance
   @param other the other option_t instance
   @return 1 if current is equal to other, 0 otherwise
*/
int32_t option_is_deep_equal( option_t *current, option_t *other );

/**
   option_copy

   Puts contents of other into current

   @param current the option_t instance to copy into
   @param other the option_t to copy from
*/
void option_copy( option_t *current, option_t *other );

/**
   option_deep_copy

   Puts contents of other into current

   @param current the option_t instance to copy into
   @param other the option_t to copy from
*/
void option_deep_copy( option_t *current, option_t *other );


/*
   Disposal
*/

/**
   option_dispose

   Deallocates a option_t instance.

   @param current pointer to the option instance to dispose
*/
void
option_dispose( option_t **current );

/**
   option_deep_dispose

   Deallocates a option_t instance.

   @param current pointer to the option instance to dispose
*/
void
option_deep_dispose( option_t **current );


/*
   Access
*/

/**
   option_short_name

   Returns the short name of the instance.

   @param current pointer to the option instance
   @return the short name
*/
string_t *
option_short_name( option_t *current );

/**
   option_long_name

   Returns the long name of the instance.

   @param current pointer to the option instance
   @return the long name
*/
string_t *
option_long_name( option_t *current );

/**
   option_documentation

   Returns the documentation of the instance.

   @param current pointer to the option instance
   @return the short name
*/
string_t *
option_documentation( option_t *current );

/**
   option_num_required_arguments

   Returns the number of required arguments of the instance.

   @param current pointer to the option instance
   @return the number of required arguments
*/
int32_t
option_num_required_arguments( option_t *current );

/**
   option_num_arguments

   Returns the number of required arguments of the instance.

   @param current pointer to the option instance
   @return the number of required arguments
*/
int32_t
option_num_arguments( option_t *current );

/**
   option_argument_item

   Returns the argument at index.

   @param current pointer to the option instance
   @param index which argument
   @return the argument at index
*/
string_t *
option_argument_item( option_t *current, int32_t index );

/**
   option_num_options

   Returns the number of required options of the instance.

   @param current pointer to the option instance
   @return the number of required options
*/
int32_t
option_num_options( option_t *current );

/**
   option_option_item

   Returns the option at index.

   @param current pointer to the option instance
   @param index which option
   @return the option at index
*/
protocol_base_t *
option_option_item( option_t *current, int32_t index );

/**
   Measurement
*/

/**
   Basic Operations
*/

/**
   Status Report
*/

/**
   Comparison
*/

/**
   Conversion
*/

/**
   Element Change
*/

/**
   option_add_argument

   Adds an argument.

   @param current pointer to the data structure
   @param argument the argument
*/
void
option_add_argument
(
   option_t *current,
   string_t *argument
);

/**
   option_add_option

   Adds an option.

   @param current pointer to the data structure
   @param p_clh_option the option
*/
void
option_add_option
(
   option_t *current,
   protocol_base_t *p_clh_option
);

/**
   Duplication
*/

/**
   Removal
*/

/**
   option_wipe_out

   Clears the arguments and options.

   @param current the option_t instance
*/
void option_wipe_out( option_t *current );

/**
   Resize
*/

#ifdef __cplusplus
}
#endif

#endif /* OPTION_T_H */

/* End of file */




