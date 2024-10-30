/**
 @file P_CLH_Command.ph
 @author Greg Lee
 @version 1.0.0
 @brief: "P_Command protocol defines"
 
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

 Defines for the p_command protocol.

*/

#ifndef P_CLH_COMMAND_PH
#define P_CLH_COMMAND_PH

/**
   Defines
*/

#define P_CLH_COMMAND   0x5A010500

#define P_CLH_COMMAND_SHORT_NAME             0
#define P_CLH_COMMAND_LONG_NAME              1
#define P_CLH_COMMAND_DOCUMENTATION          2
#define P_CLH_COMMAND_NUM_REQUIRED_ARGUMENTS 3
#define P_CLH_COMMAND_NUM_ARGUMENTS          4
#define P_CLH_COMMAND_ARGUMENT_ITEM          5
#define P_CLH_COMMAND_NUM_OPTIONS            6
#define P_CLH_COMMAND_OPTION_ITEM            7
#define P_CLH_COMMAND_EXECUTE                8
#define P_CLH_COMMAND_ADD_ARGUMENT           9
#define P_CLH_COMMAND_ADD_OPTION            10
#define P_CLH_COMMAND_WIPE_OUT              11

#define P_CLH_COMMAND_FUNCTION_MAX          11
#define P_CLH_COMMAND_FUNCTION_COUNT        12

#endif /* P_CLH_COMMAND_PH */

/* End of file */




