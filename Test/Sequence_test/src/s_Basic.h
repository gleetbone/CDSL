/**
 @file s_Basic.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for Basic of strings"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make Basic of strings.

*/

#ifndef S_BASIC_H
#define S_BASIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

#define Prefix s
#define Type string_t 8

#include "P_Basic.h"

#undef Prefix
#undef Type
 
#ifdef __cplusplus
}
#endif

#endif /* S_BASIC_H */

/* End of file */



