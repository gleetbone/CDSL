/**
 @file ii_RBTree_kv.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for red-black tree of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a dlist into a int_dlist.

*/

#ifndef INT_INT_RBTREE_KV_H_
#define INT_INT_RBTREE_KV_H_

#ifdef __cplusplus
extern "C" {
#endif
 
#include "base.h"

#define Prefix ii
#define Key int32_t
#define Type int32_t

#include "RBTree_kv.h"

#undef Prefix
#undef Key
#undef Value

#ifdef __cplusplus
}
#endif

#endif /* INT_INT_RBTREE_KV_H_ */

/* End of file */



