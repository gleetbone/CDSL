/**
 @file i_Basic.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for Basic of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make Basic of ints.

*/

#ifndef I_BASIC_H
#define I_BASIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

#define Prefix int
#define Type int32_t

#include "P_Basic.h"

#undef Prefix
#undef Type
 
#ifdef __cplusplus
}
#endif

#endif /* I_BASIC_H */

/* End of file */



