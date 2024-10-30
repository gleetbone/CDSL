/**
 @file s_DIterable.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for DIterable of strings"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make DIterable of strings.

*/

#ifndef S_DITERABLE_H
#define S_DITERABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include "String.h"

#define Prefix s
#define Type string_t *

#include "P_DIterable.h"

#undef Prefix
#undef Type
 
#ifdef __cplusplus
}
#endif

#endif /* S_DITERABLE_H */

/* End of file */



