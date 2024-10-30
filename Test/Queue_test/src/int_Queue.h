/**
 @file int_Queue.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for stack of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a stack into a int_stack.

*/

#ifndef INT_STACK_H_
#define INT_STACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PROTOCOLS_ENABLED

#include "base.h"
#include "protocol.h"

#define Prefix int
#define Type int32_t

#include "Queue.h"

#undef Prefix
#undef Type

#ifdef __cplusplus
}
#endif

#endif /* INT_STACK_H_ */

/* End of file */



