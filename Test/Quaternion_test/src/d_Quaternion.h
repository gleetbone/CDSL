/**
 @file d_Quaternion.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for quaternions of doubles"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a Quaternion into a d_quaternion.

*/

#ifndef DOUBLE_QUATERNION_H_
#define DOUBLE_QUATERNION_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PROTOCOLS_ENABLED

#include "base.h"
#include "protocol.h"

#include "d_Matvec.h"

#define Prefix d
#define Mv_Prefix d
#define Type double

#include "Quaternion.h"

#undef Prefix
#undef Mv_Prefix
#undef Type

#ifdef __cplusplus
}
#endif

#endif /* DOUBLE_QUATERNION_H_ */

/* End of file */



