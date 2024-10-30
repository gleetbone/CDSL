/**
 @file ss_UGraph.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for undirected graph with string values and edges"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for ss_ugraph type.

*/

#include "ss_UGraph.h"

#ifdef __cplusplus
extern "C" {
#endif

#define Prefix ss
#define Value string_t *
#define Value_Code STRING_TYPE
#define Edge string_t *
#define Edge_Code STRING_TYPE

#define EDGE_VALUE_EQUALITY_FUNCTION( arg1, arg2 ) ( arg1 == arg2 )
#define EDGE_VALUE_DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( string_is_equal( arg1, arg2 ) )
#define EDGE_VALUE_DEEP_CLONE_FUNCTION( arg ) ( string_deep_clone( arg ) ) 
#define EDGE_VALUE_DEEP_DISPOSE_FUNCTION( arg ) ( string_deep_dispose( &arg ) )

#define VERTEX_VALUE_EQUALITY_FUNCTION( arg1, arg2 ) ( arg1 == arg2 )
#define VERTEX_VALUE_DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( string_is_equal( arg1, arg2 ) )
#define VERTEX_VALUE_DEEP_CLONE_FUNCTION( arg ) ( string_deep_clone( arg ) )
#define VERTEX_VALUE_DEEP_DISPOSE_FUNCTION( arg ) ( string_deep_dispose( &arg ) )
 
#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#include "UGraph.c"

#ifdef __cplusplus
}
#endif

/* End of file */

