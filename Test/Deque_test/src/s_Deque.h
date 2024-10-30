/**
 @file s_Deque.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for deque of strings"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a deque into a s_deque.

*/

#ifndef S_DEQUE_H_
#define S_DEQUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include "String.h"

#define Prefix s
#define Type string_t *

#include "Deque.h"

#undef Prefix
#undef Type

#ifdef __cplusplus
}
#endif

#endif /* S_DEQUE_H_ */

/* End of file */



