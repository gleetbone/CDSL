/**
 @file f_Svd.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for svd of matrices of floats"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a Svd into a f_svd.

*/

#ifndef FLOAT_SVD_H_
#define FLOAT_SVD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

#define Prefix f
#define Matvec_prefix f
#define Type float
#define Magnitude_type float

#include "Svd.h"

#undef Prefix
#undef Matvec_prefix
#undef Type
#undef Magnitude_type

#ifdef __cplusplus
}
#endif

#endif /* FLOAT_SVD_H_ */

/* End of file */



