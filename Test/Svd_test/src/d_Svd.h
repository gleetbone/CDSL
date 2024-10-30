/**
 @file d_Svd.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for svd of matrices of doubles"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a Svd into a d_svd.

*/

#ifndef DOUBLE_SVD_H_
#define DOUBLE_SVD_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PROTOCOLS_ENABLED

#include "base.h"
#include "protocol.h"

#define Prefix d
#define Matvec_prefix d
#define Type double
#define Magnitude_type double

#include "Svd.h"

#undef Prefix
#undef Matvec_prefix
#undef Type
#undef Magnitude_type

#ifdef __cplusplus
}
#endif

#endif /* DOUBLE_SVD_H_ */

/* End of file */



