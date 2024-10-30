/**
 @file user_defined_types.h
 @author Greg Lee
 @version 2.0.0
 @brief: "include file for data structure type codes"

 @date: "Tue Sep 24 16:44:11 PDT 2019 @30 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee

 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0):

 1. Permission is hereby granted to use, copy, modify and/or
    distribute this package, provided that:
    #define  copyright notices are retained unchanged,
    #define  any distribution of this package, whether modified or not,
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

 Defines for basic types.

*/

#ifndef USER_DEFINED_TYPES_H
#define USER_DEFINED_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/**
   C Data Structure Type Codes
*/

// Protocols


#define P_CLH_COMMAND_TYPE 0x5A010500
#define P_CLH_OPTION_TYPE  0x5A010501


// Classes

#define COMMAND_TYPE 0xA5010000
#define OPTION_TYPE 0xA5010001

#ifdef __cplusplus
}
#endif

#endif /* USER_DEFINED_TYPES_H */

/* End of file */
