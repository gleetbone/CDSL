/**
 @file ii_DIterable_kv.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for DIterable_kv of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make DIterable of ints.

*/

#ifndef II_DITERABLE_KV_H
#define II_DITERABLE_KV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

#define Prefix ii
#define Key int32_t
#define Type int32_t

#include "P_DIterable_kv.h"

#undef Prefix
#undef Key
#undef Type
 
#ifdef __cplusplus
}
#endif

#endif /* II_DITERABLE_KV_H */

/* End of file */



