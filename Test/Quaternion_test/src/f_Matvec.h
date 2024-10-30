/**
 @file f_Matvec.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for matrices of floats"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a Matvec into a f_matvec.

*/

#ifndef FLOAT_MATVEC_H_
#define FLOAT_MATVEC_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PROTOCOLS_ENABLED

#include "base.h"
#include "protocol.h"

#define Prefix f
#define Type float
#define Magnitude_type float

#include "Matvec.h"

#undef Prefix
#undef Type
#undef Magnitude_type

#ifdef __cplusplus
}
#endif

#endif /* FLOAT_MATVEC_H_ */

/* End of file */



