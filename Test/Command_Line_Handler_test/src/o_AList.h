/**
 @file o_AList.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for arrayed lists of P_CLH_Option"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a AList into a c_AList.

*/

#ifndef P_CLH_OPTION_ALIST_H_
#define P_CLH_OPTION_ALIST_H_

#ifdef __cplusplus
extern "C" {
#endif

#define PROTOCOLS_ENABLED

#include "P_CLH_Option.h"

#define Prefix o
#define Type protocol_base_t *

#include "AList.h"

#undef Prefix
#undef Type

#ifdef __cplusplus
}
#endif

#endif /* P_CLH_OPTION_ALIST_H_ */

/* End of file */



