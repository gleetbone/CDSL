/**
 @file i_ugraph_vertex_HSet.h
 @author Greg Lee
 @version 0.0
 @brief: "include file for hash set of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines to make a dlist into a int_dlist.

*/

#ifndef INT_DGRAPH_VERTEX_HSET_H_
#define INT_DGRAPH_VERTEX_HSET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "base.h"

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define UGraph_vertex_struct( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_struct )
#define UGraph_vertex_type( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_t )

#define Prefix i_ugraph_vertex
#define Ugraph_prefix ii

struct UGraph_vertex_struct( Ugraph_prefix );
typedef struct UGraph_vertex_struct( Ugraph_prefix ) UGraph_vertex_type( Ugraph_prefix );

#define Item UGraph_vertex_type( Ugraph_prefix ) *

#include "HSet.h"

#undef Prefix
#undef Ugraph_prefix
#undef Item

#ifdef __cplusplus
}
#endif

#endif /* INT_DGRAPH_VERTEX_HSET_H_ */

/* End of file */



