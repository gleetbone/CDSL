/**
 @file i_MSorter.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for sorter of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a msorter into a i_msorter.

*/

#ifndef I_MSORTER_H_
#define I_MSORTER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PROTOCOLS_ENABLED

#include "base.h"
#include "protocol.h"

#define Prefix i
#define Type int32_t

#include "MSorter.h"

#undef Prefix
#undef Type
 
#ifdef __cplusplus
}
#endif

#endif /* I_MSORTER_H_ */

/* End of file */



