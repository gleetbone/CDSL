/**
 @file i_HSet.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for hash set of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a dlist into a int_dlist.

*/

#ifndef INT_HSET_H_
#define INT_HSET_H_

#ifdef __cplusplus
extern "C" {
#endif
 
#define PROTOCOLS_ENABLED

#define Prefix i
#define Item int32_t

#include "HSet.h"

#undef Prefix
#undef Item

#ifdef __cplusplus
}
#endif

#endif /* INT_HSET_H_ */

/* End of file */



