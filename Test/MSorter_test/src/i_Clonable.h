/**
 @file i_Clonable.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for Clonable of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make Clonable of ints.

*/

#ifndef I_CLONABLE_H
#define I_CLONABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

#define Prefix i
#define Type int32_t

#include "P_Clonable.h"

#undef Prefix
#undef Type
 
#ifdef __cplusplus
}
#endif

#endif /* I_CLONABLE_H */

/* End of file */



