/**
 @file P_Iterable.h
 @author Greg Lee
 @version 2.0.0
 @brief: "P_Iterable protocol"
 
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

 Function declarations for the P_Iterable protocol.

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
   p_iterable_count

   returns number of elements in the p_iterable

   @param p_iterable the pointer to the iterable struct
   @return the number of elemements in the p_iterable
*/
#define P_Iterable_count( arg ) PRIMITIVE_CAT( arg, _iterable_count )
int32_t
P_Iterable_count( Prefix )
(
   protocol_base_t *p_iterable
);

/**
   p_iterable_item

   returns current value in the p_iterable

   @param p_iterable the pointer to the protocol base struct
   @return the currentvalue in p_iterable
*/
#define P_Iterable_item( arg ) PRIMITIVE_CAT( arg, _iterable_item )
Type
P_Iterable_item( Prefix )
(
   protocol_base_t *p_iterable
);

/**
   p_iterable_off

   returns 1 if cursor in the p_iterable is off, 0 otherwise

   @param p_iterable the pointer to the iterable struct
   @return 1 if cursor in p_iterable is off, 0 otherwise
*/
#define P_Iterable_off( arg ) PRIMITIVE_CAT( arg, _iterable_off )
int32_t
P_Iterable_off( Prefix )
(
   protocol_base_t *p_iterable
);

/**
   p_iterable_is_empty

   returns 1 if p_iterable is empty, 0 otherwise

   @param p_iterable the pointer to the iterable struct
   @return 1 if p_iterable is empty, 0 otherwise
*/
#define P_Iterable_is_empty( arg ) PRIMITIVE_CAT( arg, _iterable_is_empty )
int32_t
P_Iterable_is_empty( Prefix )
(
   protocol_base_t *p_iterable
);

/**
   p_iterable_start

   puts cursor in p_iterable at first item

   @param p_iterable the pointer to the protocol base struct
*/
#define P_Iterable_start( arg ) PRIMITIVE_CAT( arg, _iterable_start )
void
P_Iterable_start( Prefix )
(
   protocol_base_t *p_iterable
);

/**
   p_iterable_forth

   puts cursor in p_iterable at next item, if any

   @param p_iterable the pointer to the protocol base struct
*/
#define P_Iterable_forth( arg ) PRIMITIVE_CAT( arg, _iterable_forth )
void
P_Iterable_forth( Prefix )
(
   protocol_base_t *p_iterable
);

/* End of file */




