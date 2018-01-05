/**
 @file i_SSorter.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for sorter of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a qsorter into a i_qsorter.

*/

#ifndef I_SSORTER_H_
#define I_SSORTER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

#define Prefix i
#define Type int32_t

#include "SSorter.h"

#undef Prefix
#undef Type
 
#ifdef __cplusplus
}
#endif

#endif /* I_SSORTER_H_ */

/* End of file */



