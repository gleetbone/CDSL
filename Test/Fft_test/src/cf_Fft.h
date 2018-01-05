/**
 @file cf_Fft.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for fft of matrices of complex floats"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a Fft into a cf_fft.

*/

#ifndef COMPLEX_FLOAT_FFT_H_
#define COMPLEX_FLOAT_FFT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"
#include "f_Matvec.h"
#include "cf_Matvec.h"
#include <complex.h>

#define Prefix cf
#define Matvec_prefix cf
#define Matvec_magnitude_prefix f
#define Type complex float
#define Magnitude_type float

#include "Fft.h"

#undef Prefix
#undef Matvec_prefix
#undef Matvec_magnitude_prefix
#undef Type
#undef Magnitude_type

#ifdef __cplusplus
}
#endif

#endif /* COMPLEX_FLOAT_FFT_H_ */

/* End of file */



