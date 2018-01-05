/**
 @file P_DIterable.ph
 @author Greg Lee
 @version 1.0.0
 @brief: "P_Clonable protocol defines"
 
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

 Defines for the P_Clonable protocol.

*/

#ifndef P_DITERABLE_PH
#define P_DITERABLE_PH

/**
   Defines
*/

#define P_DITERABLE 0x5A000302

#define P_DITERABLE_DISPOSE               0
#define P_DITERABLE_DISPOSE_WITH_CONTENTS 1
#define P_DITERABLE_COUNT                 2
#define P_DITERABLE_ITEM                  3
#define P_DITERABLE_OFF                   4
#define P_DITERABLE_IS_EMPTY              5
#define P_DITERABLE_START                 6
#define P_DITERABLE_FORTH                 7
#define P_DITERABLE_FINISH                8
#define P_DITERABLE_BACK                  9  

#define P_DITERABLE_FUNCTION_MAX     9
#define P_DITERABLE_FUNCTION_COUNT   10

#endif /* P_DITERABLE_PH */

/* End of file */




