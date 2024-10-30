/**
 @file f_Quaternion.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for quaternions of floats"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a Quaternion into a f_quaternion.

*/

#ifndef FLOAT_QUATERNION_H_
#define FLOAT_QUATERNION_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PROTOCOLS_ENABLED

#include "base.h"
#include "protocol.h"

#include "f_Matvec.h"

#define Prefix f
#define Mv_Prefix f
#define Type float

#include "Quaternion.h"

#undef Prefix
#undef Mv_Prefix
#undef Type

#ifdef __cplusplus
}
#endif

#endif /* FLOAT_QUATERNION_H_ */

/* End of file */



