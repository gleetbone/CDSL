/**
 @file ii_UGraph.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for directed graph with integer values and edges"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a dgraph into a ii_dgraph.

*/

#ifndef INT_INT_UGRAPH_H_
#define INT_INT_UGRAPH_H_

#ifdef __cplusplus
extern "C" {
#endif
 
#define PROTOCOLS_ENABLED

#include "base.h"
#include "protocol.h"

#define Prefix ii
#define Value int32_t
#define Edge int32_t

#include "UGraph.h"

#undef Prefix 
#undef Value 
#undef Edge 

#ifdef __cplusplus
}
#endif

#endif /* INT_INT_UGRAPH_H_ */

/* End of file */



