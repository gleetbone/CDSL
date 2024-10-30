/**
 @file ss_DGraph.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for directed graph with string values and edges"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a dgraph into a ss_dgraph.

*/

#ifndef STRING_STRING_DGRAPH_H_
#define STRING_STRING_DGRAPH_H_

#ifdef __cplusplus
extern "C" {
#endif
 
#define PROTOCOLS_ENABLED

#include "base.h"
#include "protocol.h"

#include "String.h"

#define Prefix ss
#define Value string_t *
#define Edge string_t *

#include "DGraph.h"

#undef Prefix 
#undef Value 
#undef Edge 

#ifdef __cplusplus
}
#endif

#endif /* STRING_STRING_DGRAPH_H_ */

/* End of file */



