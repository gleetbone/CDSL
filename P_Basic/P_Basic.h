/**
 @file P_Basic.h
 @author Greg Lee
 @version 2.0.0
 @brief: "P_Basic protocol"

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

 Function declarations for the P_Basic protocol.

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
   p_basic_dispose

   dispose of p_basic

   @param p_basic the pointer to the p_basic
*/
#define P_Basic_dispose( arg ) PRIMITIVE_CAT( arg, _basic_dispose )
void
P_Basic_dispose( Prefix )
(
   protocol_base_t **p_basic
);

/**
   p_basic_deep_dispose

   dispose of p_basic and its contained elements

   @param p_basic the pointer to the p_basic
*/
#define P_Basic_deep_dispose( arg ) PRIMITIVE_CAT( arg, _basic_deep_dispose )
void
P_Basic_deep_dispose( Prefix )
(
   protocol_base_t **p_basic
);

/**
   p_basic_is_equal

   returns whether p_basic is (shallow) equal to other

   @param p_basic the pointer to the basic struct
   @param other the pointer to the other basic struct
   @return 1 if is equal, 0 otherwise
*/
#define P_Basic_is_equal( arg ) PRIMITIVE_CAT( arg, _basic_is_equal )
int32_t
P_Basic_is_equal( Prefix )
(
   protocol_base_t *p_basic,
   protocol_base_t *other
);

/**
   p_basic_is_deep_equal

   returns whether p_basic is (deep) equal to other

   @param p_basic the pointer to the basic struct
   @param other the pointer to the other basic struct
   @return 1 if is equal, 0 otherwise
*/
#define P_Basic_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _basic_is_deep_equal )
int32_t
P_Basic_is_deep_equal( Prefix )
(
   protocol_base_t *p_basic,
   protocol_base_t *other
);

/**
   p_basic_copy

   copies (shallow) other into basic

   @param p_basic the pointer to the basic struct
   @param other the pointer to the other basic struct
*/
#define P_Basic_copy( arg ) PRIMITIVE_CAT( arg, _basic_copy )
void
P_Basic_copy( Prefix )
(
   protocol_base_t *p_basic,
   protocol_base_t *other
);

/**
   p_basic_deep_copy

   copies (deep) other into basic

   @param p_basic the pointer to the basic struct
   @param other the pointer to the other basic struct
*/
#define P_Basic_deep_copy( arg ) PRIMITIVE_CAT( arg, _basic_deep_copy )
void
P_Basic_deep_copy( Prefix )
(
   protocol_base_t *p_basic,
   protocol_base_t *other
);

/**
   p_basic_clone

   returns number of elements in the p_basic

   @param p_basic the pointer to the basic struct
   @return clone of p_basic
*/
#define P_Basic_clone( arg ) PRIMITIVE_CAT( arg, _basic_clone )
protocol_base_t *
P_Basic_clone( Prefix )
(
   protocol_base_t *p_basic
);

/**
   p_basic_deep_clone

   returns value at index in the p_basic

   @param p_basic the pointer to the protocol base struct
   @return deep clone of p_basic
*/
#define P_Basic_deep_clone( arg ) PRIMITIVE_CAT( arg, _basic_deep_clone )
protocol_base_t *
P_Basic_deep_clone( Prefix )
(
   protocol_base_t *p_basic
);

/* End of file */




