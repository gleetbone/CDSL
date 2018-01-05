/**
 @file Protocol_Base.c
 @author Greg Lee
 @version 1.0.0
 @brief: "Protocol Base"
 
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

 Function definitions for the opaque protocol_base_t type.

*/

/**
   Includes
*/

#include "Protocol_Base.h"
#include "Protocol_Base.ph"

#define PROTOCOL_MASK 0xFF000000
#define PROTOCOL_VALID_OBJECT 0xA5000000
#define PROTOCOL_VALID_PROTOCOL 0x5A000000

int32_t
protocol_base_is_valid_object( protocol_base_t *object )
{
   return ( ( (*object).type & PROTOCOL_MASK ) == PROTOCOL_VALID_OBJECT );
}

int32_t
protocol_base_is_valid_protocol( int32_t protocol_id )
{
   return ( ( protocol_id & PROTOCOL_MASK ) == PROTOCOL_VALID_PROTOCOL );
}

int32_t
protocol_base_supports_protocol( protocol_base_t *object, int32_t protocol_id )
{
   return (*object).supports_protocol( protocol_id );
}

/* End of file */

