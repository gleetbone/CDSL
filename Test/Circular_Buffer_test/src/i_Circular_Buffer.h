/**
 @file i_Circular_buffer.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for circular_buffer of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a circular_buffer into a i_circular_buffer.

*/

#ifndef I_CIRCULAR_BUFFER_H_
#define I_CIRCULAR_BUFFER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PROTOCOLS_ENABLED

#include "base.h"
#include "protocol.h"

#define Prefix i
#define Type int32_t

#include "Circular_Buffer.h"

#undef Prefix
#undef Type

#ifdef __cplusplus
}
#endif

#endif /* I_CIRCULAR_BUFFER_H_ */

/* End of file */



