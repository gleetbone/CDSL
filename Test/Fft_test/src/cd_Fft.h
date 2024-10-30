/**
 @file cd_Fft.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for fft of matrices of complex floats"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a Fft into a cd_fft.

*/

#ifndef COMPLEX_DOUBLE_FFT_H_
#define COMPLEX_DOUBLE_FFT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PROTOCOLS_ENABLED

#include "base.h"
#include "protocol.h"
#include "d_Matvec.h"
#include "cd_Matvec.h"
#include <complex.h>

#define Prefix cd
#define Matvec_prefix cd
#define Matvec_magnitude_prefix d
#define Type complex double
#define Magnitude_type double

#include "Fft.h"

#undef Prefix
#undef Matvec_prefix
#undef Matvec_magnitude_prefix
#undef Type
#undef Magnitude_type

#ifdef __cplusplus
}
#endif

#endif /* COMPLEX_DOUBLE_FFT_H_ */

/* End of file */



