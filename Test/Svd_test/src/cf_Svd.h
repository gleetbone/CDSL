/**
 @file cf_Svd.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for svd of matrices of complex floats"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a Svd into a cf_svd.

*/

#ifndef COMPLEX_FLOAT_SVD_H_
#define COMPLEX_FLOAT_SVD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include <complex.h>

#define Prefix cf
#define Matvec_prefix cf
#define Type complex float
#define Magnitude_type float

#include "Svd.h"

#undef Prefix
#undef Matvec_prefix
#undef Type
#undef Magnitude_type

#ifdef __cplusplus
}
#endif

#endif /* COMPLEX_FLOAT_SVD_H_ */

/* End of file */



