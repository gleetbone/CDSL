/**
 @file s_Heap.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for binary search tree of strings"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Defines to make a heap into a s_heap

*/

#ifndef S_HEAP_H_
#define S_HEAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PROTOCOLS_ENABLED

#include "base.h"
#include "protocol.h"
#include "String.h"

#define Prefix s
#define Type string_t *

#include "Heap.h"

#undef Prefix
#undef Type

#ifdef __cplusplus
}
#endif

#endif /* S_HEAP_H_ */

/* End of file */



