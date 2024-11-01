/**
 @file Protocol_Base.ph
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

 Structure definition for the opaque protocol_base_t type.

 */

#ifndef PROTOCOL_BASE_PH
#define PROTOCOL_BASE_PH

/**
   Defines
*/

#define PROTOCOL_MASK 0xFF000000
#define PROTOCOL_VALID_OBJECT 0xA5000000
#define PROTOCOL_VALID_PROTOCOL 0x5A000000


/**
   Includes
*/

#include "base.h"

struct protocol_base_struct
{
   void * (*get_function)( int32_t protocol_id, int32_t function_id );
   int32_t (*supports_protocol)( int32_t protocol_id );
   int32_t type;
};

#endif /* PROTOCOL_BASE_PH */

/* End of file */

