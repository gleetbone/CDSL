/**
 @file P_Sorter.h
 @author Greg Lee
 @version 1.0.0
 @brief: "P_Sorter protocol"
 
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

 Function declarations for the p_sorter protocol.

*/

#include "base.h"
#include "Protocol_Base.h"

/**
   Note that this include file does NOT have an include guard - it may 
   be included multiple times with different macro defintions.
   
   Defines that must be present (external to this file):
   
   Prefix - string used to name this container type
   Type   - the type of the value
   
*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

/**
   Includes
*/

/**
   p_sorter_dispose

   dispose of p_sorter

   @param p_sorter the pointer to the p_sorter
*/
#define P_Sorter_dispose( arg ) PRIMITIVE_CAT( arg, _sorter_dispose )
void 
P_Sorter_dispose( Prefix )
(
   protocol_base_t *p_sorter
);

/**
   p_sorter_dispose_f

   returns function to dispose of p_sorter

   @param p_sorter the pointer to the p_sorter
   @return the function
*/
typedef void (*sorter_dispose_f)( protocol_base_t *p_sorter );
#define P_Sorter_dispose_f( arg ) PRIMITIVE_CAT( arg, _sorter_dispose_f )
sorter_dispose_f
P_Sorter_dispose_f( Prefix )
(
   protocol_base_t *p_sorter
);

/**
   p_sorter_sort

   sorts p_indexable

   @param p_sorter the pointer to the sorter
   @param p_indexable the pointer to the indexable
*/
#define P_Sorter_sort( arg ) PRIMITIVE_CAT( arg, _sorter_sort )
void
P_Sorter_sort( Prefix )
(
   protocol_base_t *p_sorter,
   protocol_base_t *p_indexable
);

/**
   p_sorter_sort_f

   returns function to sort p_indexable

   @param p_sorter the pointer to the semaphore struct
   @return the function
*/
typedef void (*sorter_sort_f)( protocol_base_t *p_sorter, protocol_base_t *p_indexable );
#define P_Sorter_sort_f( arg ) PRIMITIVE_CAT( arg, _sorter_sort_f )
sorter_sort_f
P_Sorter_sort_f( Prefix )
(
   protocol_base_t *p_sorter
);

/* End of file */




