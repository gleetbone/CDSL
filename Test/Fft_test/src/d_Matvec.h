/**
 @file d_Matvec.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for matrices of doubles"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a Matvec into a d_matvec.

*/

#ifndef DOUBLE_MATVEC_H_
#define DOUBLE_MATVEC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

#define Prefix d
#define Type double
#define Magnitude_type double

#include "Matvec.h"

#undef Prefix
#undef Type
#undef Magnitude_type

#ifdef __cplusplus
}
#endif

#endif /* DOUBLE_MATVEC_H_ */

/* End of file */



