/**
 @file P_Clonable.h
 @author Greg Lee
 @version 1.0.0
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
   p_clonable_dispose

   dispose of p_clonable

   @param p_clonable the pointer to the p_clonable
*/
#define P_Clonable_dispose( arg ) PRIMITIVE_CAT( arg, _clonable_dispose )
void 
P_Clonable_dispose( Prefix )
(
   protocol_base_t *p_clonable
);

/**
   p_clonable_dispose_f

   returns function to dispose of p_clonable

   @param p_clonable the pointer to the p_clonable
   @return the function
*/
typedef void (*clonable_dispose_f)( protocol_base_t *p_clonable );
#define P_Clonable_dispose_f( arg ) PRIMITIVE_CAT( arg, _clonable_dispose_f )
clonable_dispose_f
P_Clonable_dispose_f( Prefix )
(
   protocol_base_t *p_clonable
);

/**
   p_clonable_dispose_with_contents

   dispose of p_clonable and its contained elements

   @param p_clonable the pointer to the p_clonable
*/
#define P_Clonable_dispose_with_contents( arg ) PRIMITIVE_CAT( arg, _clonable_dispose_with_contents )
void
P_Clonable_dispose_with_contents( Prefix )
(
   protocol_base_t *p_clonable
);

/**
   p_clonable_dispose_with_contents_f

   returns function to dispose of p_clonable and its contained elements

   @param p_clonable the pointer to the p_clonable
   @return the function
*/
typedef void (*clonable_dispose_with_contents_f)( protocol_base_t *p_clonable );
#define P_Clonable_dispose_with_contents_f( arg ) PRIMITIVE_CAT( arg, _clonable_dispose_with_contents_f )
clonable_dispose_with_contents_f
P_Clonable_dispose_with_contents_f( Prefix )
(
   protocol_base_t *p_clonable
);

/**
   p_clonable_clone

   returns number of elements in the p_clonable

   @param p_clonable the pointer to the clonable struct
   @return the number of elemements in the p_clonable
*/
#define P_Clonable_clone( arg ) PRIMITIVE_CAT( arg, _clonable_clone )
protocol_base_t *
P_Clonable_clone( Prefix )
(
   protocol_base_t *p_clonable
);

/**
   p_clonable_clone_f

   returns function to return number of elements in the p_clonable

   @param p_clonable the pointer to the clonable struct
   @return the function
*/
typedef protocol_base_t * (*clonable_clone_f)( protocol_base_t *p_clonable );
#define P_Clonable_clone_f( arg ) PRIMITIVE_CAT( arg, _clonable_clone_f )
clonable_clone_f
P_Clonable_clone_f( Prefix )
(
   protocol_base_t *p_clonable
);

/**
   p_clonable_deep_clone

   returns value at index in the p_clonable

   @param p_clonable the pointer to the protocol base struct
   @return the value at index in p_clonable
*/
#define P_Clonable_deep_clone( arg ) PRIMITIVE_CAT( arg, _clonable_deep_clone )
protocol_base_t *
P_Clonable_deep_clone( Prefix )
(
   protocol_base_t *p_clonable
);

/**
   p_clonable_deep_clone_f

   returns function to return value at index in the p_clonable

   @param p_clonable the pointer to the protocol base struct
   @return the function
*/
typedef protocol_base_t * (*clonable_deep_clone_f)( protocol_base_t *p_clonable );
#define P_Clonable_deep_clone_f( arg ) PRIMITIVE_CAT( arg, _clonable_deep_clone_f )
clonable_deep_clone_f
P_Clonable_deep_clone_f( Prefix )
(
   protocol_base_t *p_clonable
);

/* End of file */




