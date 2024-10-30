/**
 @file ii_DGraph.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for directed graph with integer values and edges"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for ii_dgraph type.

*/

#include "ii_DGraph.h"

#ifdef __cplusplus
extern "C" {
#endif

#define Prefix ii
#define Value int32_t
#define Value_Code int32_type_code
#define Edge int32_t
#define Edge_Code int32_type_code

#define EDGE_VALUE_DEFAULT_VALUE ( 0 )
#define EDGE_VALUE_EQUALITY_FUNCTION( arg1, arg2 ) ( arg1 == arg2 )
#define EDGE_VALUE_DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( arg1 == arg2 ) 
#define EDGE_VALUE_DEEP_CLONE_FUNCTION( arg ) ( arg ) 
#define EDGE_VALUE_DISPOSE_FUNCTION( arg )
#define EDGE_VALUE_DEEP_DISPOSE_FUNCTION( arg ) 

#define VERTEX_VALUE_DEFAULT_VALUE ( 0 )
#define VERTEX_VALUE_EQUALITY_FUNCTION( arg1, arg2 ) ( arg1 == arg2 )
#define VERTEX_VALUE_DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( arg1 == arg2 )
#define VERTEX_VALUE_DEEP_COPY_FUNCTION( arg1, arg2 ) ( arg1 == arg2 )
#define VERTEX_VALUE_DEEP_CLONE_FUNCTION( arg ) ( arg )
#define VERTEX_VALUE_DEEP_DISPOSE_FUNCTION( arg1 )
 
#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#include "DGraph.c"

#ifdef __cplusplus
}
#endif

/* End of file */

