/**
 @file P_Iterable_kv.h
 @author Greg Lee
 @version 2.0.0
 @brief: "P_Iterable_kv protocol"

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

 Function declarations for the P_Iterable_kv protocol.

*/

#include "base.h"
#include "Protocol_Base.h"

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix - string used to name this container type
   Key    - the type of the key
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
   p_iterable_kv_count

   returns number of elements in the p_iterable_kv

   @param p_iterable_kv the pointer to the iterable_kv struct
   @return the number of elemements in the p_iterable_kv
*/
#define P_Iterable_kv_count( arg ) PRIMITIVE_CAT( arg, _iterable_kv_count )
int32_t
P_Iterable_kv_count( Prefix )
(
   protocol_base_t *p_iterable_kv
);

/**
   p_iterable_kv_key

   returns current key in the p_iterable_kv

   @param p_iterable_kv the pointer to the protocol base struct
   @return the currentkey in p_iterable_kv
*/
#define P_Iterable_kv_key( arg ) PRIMITIVE_CAT( arg, _iterable_kv_key )
Key
P_Iterable_kv_key( Prefix )
(
   protocol_base_t *p_iterable_kv
);

/**
   p_iterable_kv_value

   returns current value in the p_iterable_kv

   @param p_iterable_kv the pointer to the protocol base struct
   @return the currentvalue in p_iterable_kv
*/
#define P_Iterable_kv_value( arg ) PRIMITIVE_CAT( arg, _iterable_kv_value )
Type
P_Iterable_kv_value( Prefix )
(
   protocol_base_t *p_iterable_kv
);

/**
   p_iterable_kv_off

   returns 1 if cursor in the p_iterable_kv is off, 0 otherwise

   @param p_iterable_kv the pointer to the iterable_kv struct
   @return 1 if cursor in p_iterable_kv is off, 0 otherwise
*/
#define P_Iterable_kv_off( arg ) PRIMITIVE_CAT( arg, _iterable_kv_off )
int32_t
P_Iterable_kv_off( Prefix )
(
   protocol_base_t *p_iterable_kv
);

/**
   p_iterable_kv_is_empty

   returns 1 if p_iterable_kv is empty, 0 otherwise

   @param p_iterable_kv the pointer to the iterable_kv struct
   @return 1 if p_iterable_kv is empty, 0 otherwise
*/
#define P_Iterable_kv_is_empty( arg ) PRIMITIVE_CAT( arg, _iterable_kv_is_empty )
int32_t
P_Iterable_kv_is_empty( Prefix )
(
   protocol_base_t *p_iterable_kv
);

/**
   p_iterable_kv_start

   puts cursor in p_iterable_kv at first item

   @param p_iterable_kv the pointer to the protocol base struct
*/
#define P_Iterable_kv_start( arg ) PRIMITIVE_CAT( arg, _iterable_kv_start )
void
P_Iterable_kv_start( Prefix )
(
   protocol_base_t *p_iterable_kv
);

/**
   p_iterable_kv_forth

   puts cursor in p_iterable_kv at next item, if any

   @param p_iterable_kv the pointer to the protocol base struct
*/
#define P_Iterable_kv_forth( arg ) PRIMITIVE_CAT( arg, _iterable_kv_forth )
void
P_Iterable_kv_forth( Prefix )
(
   protocol_base_t *p_iterable_kv
);

/* End of file */




