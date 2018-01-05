/**
 @file i_ugraph_vertex_HSet.c
 @author Greg Lee
 @version 1.0.0
 @brief: "implementation file for hash set of ugraph vertices"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for i_ugraph_vertex_HSet type.

*/
#include "i_ugraph_vertex_HSet.h"
#include "ii_UGraph.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t
address_to_hash( void *p );

#define Dgraph_prefix ii
#define UGraph_dispose_of_vertex( arg ) PRIMITIVE_CAT( arg, _ugraph_dispose_of_vertex )
#define UGraph_address_to_hash( arg ) PRIMITIVE_CAT( arg, _ugraph_address_to_hash )

void
UGraph_dispose_of_vertex( Dgraph_prefix )( UGraph_vertex_type( Dgraph_prefix ) *vertex );

int32_t
UGraph_address_to_hash( Dgraph_prefix )( UGraph_vertex_type( Dgraph_prefix ) *vertex );

#define HASH_FUNCTION( arg ) ( UGraph_address_to_hash( Dgraph_prefix )( arg ) )

#define EQUALITY_FUNCTION( arg1, arg2 ) ( arg1 == arg2 )

#define DISPOSE_FUNCTION( arg ) ( UGraph_dispose_of_vertex( Dgraph_prefix )( arg ) )
#define DUPLICATE_FUNCTION( arg ) ( arg )

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix i_ugraph_vertex
#define Item UGraph_vertex_type( Dgraph_prefix ) *
#define Type_Code 0xA5000612

#include "HSet.c"

#ifdef __cplusplus
}
#endif

/* End of file */

