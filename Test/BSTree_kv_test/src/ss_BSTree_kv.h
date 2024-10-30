/**
 @file ss_BSTree_kv.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for binary search tree of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a dlist into a int_dlist.

*/

#ifndef SS_BSTREE_KV_H_
#define SS_BSTREE_KV_H_

#ifdef __cplusplus
extern "C" {
#endif
 
#define PROTOCOLS_ENABLED

#include "base.h"
#include "protocol.h"
#include "String.h"

#define Prefix ss
#define Key string_t *
#define Type string_t *

#include "BSTree_kv.h"

#undef Prefix
#undef Key
#undef Type

#ifdef __cplusplus
}
#endif

#endif /* SS_BSTREE_KV_H_ */

/* End of file */



