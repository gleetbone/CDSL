/**
 @file P_CLH_Option.h
 @author Greg Lee
 @version 2.0.0
 @brief: "P_CLH_Option protocol"
 
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

 Function declarations for the p_clh_option protocol.

*/

#include "base.h"
#include "Protocol_Base.h"
#include "user_defined_types.h"
#include "String.h"

/**
   Note that this include file does NOT have an include guard - it may 
   be included multiple times with different macro defintions.
   
   Defines that must be present (external to this file):
   
   P_CLH_Option_Prefix - string used to name this container type
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
   p_clh_option_short_name

   returns short name

   @param p_clh_option the pointer to the option
   @return the short name
*/
#define P_CLH_Option_short_name( arg ) PRIMITIVE_CAT( arg, _clh_option_short_name )
string_t *
P_CLH_Option_short_name( P_CLH_Option_Prefix )
(
   protocol_base_t *p_clh_option
);

/**
   p_clh_option_long_name

   returns long name

   @param p_clh_option the pointer to the option
   @return the long name
*/
#define P_CLH_Option_long_name( arg ) PRIMITIVE_CAT( arg, _clh_option_long_name )
string_t *
P_CLH_Option_long_name( P_CLH_Option_Prefix )
(
   protocol_base_t *p_clh_option
);

/**
   p_clh_option_documentation

   returns documentation string

   @param p_clh_option the pointer to the option
   @return the documentation string
*/
#define P_CLH_Option_documentation( arg ) PRIMITIVE_CAT( arg, _clh_option_documentation )
string_t *
P_CLH_Option_documentation( P_CLH_Option_Prefix )
(
   protocol_base_t *p_clh_option
);

/**
   p_clh_option_num_required_arguments

   returns the number of required arguments to the option

   @param p_clh_option the pointer to the option
   @return number of required arguments to the option
*/
#define P_CLH_Option_num_required_arguments( arg ) PRIMITIVE_CAT( arg, _clh_option_num_required_arguments )
int32_t
P_CLH_Option_num_required_arguments( P_CLH_Option_Prefix )
(
   protocol_base_t *p_clh_option
);

/**
   p_clh_option_num_arguments

   returns the number of required arguments to the option

   @param p_clh_option the pointer to the option
   @return number of required arguments to the option
*/
#define P_CLH_Option_num_arguments( arg ) PRIMITIVE_CAT( arg, _clh_option_num_arguments )
int32_t
P_CLH_Option_num_arguments( P_CLH_Option_Prefix )
(
   protocol_base_t *p_clh_option
);

/**
   p_clh_option_argument_item

   returns the number of required arguments to the option

   @param p_clh_option the pointer to the option
   @param index which argument
   @return argument at index
*/
#define P_CLH_Option_argument_item( arg ) PRIMITIVE_CAT( arg, _clh_option_argument_item )
string_t *
P_CLH_Option_argument_item( P_CLH_Option_Prefix )
(
   protocol_base_t *p_clh_option,
   int32_t index
);

/**
   p_clh_option_add_argument

   sets option arguments

   @param p_clh_option the pointer to the option
   @param argument the argument
*/
#define P_CLH_Option_add_argument( arg ) PRIMITIVE_CAT( arg, _clh_option_add_argument )
void
P_CLH_Option_add_argument( P_CLH_Option_Prefix )
(
   protocol_base_t *p_clh_option,
   string_t *argument
);

/**
   p_clh_option_wipe_out

   clears parameters and options

   @param p_clh_option the pointer to the option
*/
#define P_CLH_Option_wipe_out( arg ) PRIMITIVE_CAT( arg, _clh_option_wipe_out )
void
P_CLH_Option_wipe_out( P_CLH_Option_Prefix )
(
   protocol_base_t *p_clh_option
);

/* End of file */




