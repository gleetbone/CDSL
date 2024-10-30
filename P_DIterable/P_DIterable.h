/**
 @file P_DIterable.h
 @author Greg Lee
 @version 2.0.0
 @brief: "P_Clonable protocol"
 
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

 Function declarations for the P_Clonable protocol.

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
   p_diterable_count

   returns number of elements in the p_diterable

   @param p_diterable the pointer to the diterable struct
   @return the number of elemements in the p_diterable
*/
#define P_DIterable_count( arg ) PRIMITIVE_CAT( arg, _diterable_count )
int32_t
P_DIterable_count( Prefix )
(
   protocol_base_t *p_diterable
);

/**
   p_diterable_item

   returns current value in the p_diterable

   @param p_diterable the pointer to the protocol base struct
   @return the currentvalue in p_diterable
*/
#define P_DIterable_item( arg ) PRIMITIVE_CAT( arg, _diterable_item )
Type
P_DIterable_item( Prefix )
(
   protocol_base_t *p_diterable
);

/**
   p_diterable_off

   returns 1 if cursor in the p_diterable is off, 0 otherwise

   @param p_diterable the pointer to the diterable struct
   @return 1 if cursor in p_diterable is off, 0 otherwise
*/
#define P_DIterable_off( arg ) PRIMITIVE_CAT( arg, _diterable_off )
int32_t
P_DIterable_off( Prefix )
(
   protocol_base_t *p_diterable
);

/**
   p_diterable_is_empty

   returns 1 if p_diterable is empty, 0 otherwise

   @param p_diterable the pointer to the diterable struct
   @return 1 if p_diterable is empty, 0 otherwise
*/
#define P_DIterable_is_empty( arg ) PRIMITIVE_CAT( arg, _diterable_is_empty )
int32_t
P_DIterable_is_empty( Prefix )
(
   protocol_base_t *p_diterable
);

/**
   p_diterable_start

   puts cursor in p_diterable at first item

   @param p_diterable the pointer to the protocol base struct
*/
#define P_DIterable_start( arg ) PRIMITIVE_CAT( arg, _diterable_start )
void
P_DIterable_start( Prefix )
(
   protocol_base_t *p_diterable
);

/**
   p_diterable_forth

   puts cursor in p_diterable at next item, if any

   @param p_diterable the pointer to the protocol base struct
*/
#define P_DIterable_forth( arg ) PRIMITIVE_CAT( arg, _diterable_forth )
void
P_DIterable_forth( Prefix )
(
   protocol_base_t *p_diterable
);

/**
   p_diterable_finish

   puts cursor in p_diterable at first item

   @param p_diterable the pointer to the protocol base struct
*/
#define P_DIterable_finish( arg ) PRIMITIVE_CAT( arg, _diterable_finish )
void
P_DIterable_finish( Prefix )
(
   protocol_base_t *p_diterable
);

/**
   p_diterable_back

   puts cursor in p_diterable at next item, if any

   @param p_diterable the pointer to the protocol base struct
*/
#define P_DIterable_back( arg ) PRIMITIVE_CAT( arg, _diterable_back )
void
P_DIterable_back( Prefix )
(
   protocol_base_t *p_diterable
);

/* End of file */




