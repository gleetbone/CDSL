/**
 @file int_SList.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for singly linked lists of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a slist into a int_slist.

*/

#ifndef INT_SLIST_H_
#define INT_SLIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

#define Prefix int
#define Type int32_t

#include "SList.h"

#undef Prefix
#undef Type

#ifdef __cplusplus
}
#endif

#endif /* INT_SLIST_H_ */

/* End of file */



