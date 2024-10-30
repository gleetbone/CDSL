/**
 @file s_HSet.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for hash set of Strings"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a dlist into a int_dlist.

*/

#ifndef STRING_HSET_H_
#define STRING_HSET_H_

#ifdef __cplusplus
extern "C" {
#endif
 
#define PROTOCOLS_ENABLED

#include "String.h"

#define Prefix s
#define Item string_t *

#include "HSet.h"

#undef Prefix
#undef Item

#ifdef __cplusplus
}
#endif

#endif /* STRING_HSET_H_ */

/* End of file */



