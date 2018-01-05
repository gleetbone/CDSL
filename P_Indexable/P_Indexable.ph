/**
 @file P_Indexable.ph
 @author Greg Lee
 @version 1.0.0
 @brief: "P_Indexable protocol defines"
 
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

 Defines for the P_Indexable protocol.

*/

#ifndef P_INDEXABLE_PH
#define P_INDEXABLE_PH

/**
   Defines
*/

#define P_INDEXABLE 0x5A000200

#define P_INDEXABLE_DISPOSE               0
#define P_INDEXABLE_DISPOSE_WITH_CONTENTS 1
#define P_INDEXABLE_COUNT                 2
#define P_INDEXABLE_ITEM                  3
#define P_INDEXABLE_PUT                   4
#define P_INDEXABLE_PUT_AND_DISPOSE       5

#define P_INDEXABLE_FUNCTION_MAX          5
#define P_INDEXABLE_FUNCTION_COUNT        6

#endif /* P_INDEXABLE_PH */

/* End of file */




