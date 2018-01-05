/**
 @file int_Sequence.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for sequences of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a sequence into a int_sequence.

*/

#ifndef INT_SEQUENCE_H_
#define INT_SEQUENCE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

#define Prefix int
#define Type int32_t

#include "Sequence.h"

#undef Prefix
#undef Type

#ifdef __cplusplus
}
#endif

#endif /* INT_SEQUENCE_H_ */

/* End of file */



