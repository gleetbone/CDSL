/**
 @file ss_Iterable_kv.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for Iterable_kv of strings"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make Iterable of strings.

*/

#ifndef SS_ITERABLE_KV_H
#define SS_ITERABLE_KV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include "String.h"

#define Prefix ss
#define Key string_t *
#define Type string_t *

#include "P_Iterable_kv.h"

#undef Prefix
#undef Key
#undef Type
 
#ifdef __cplusplus
}
#endif

#endif /* SS_ITERABLE_KV_H */

/* End of file */



