/**
 @file i_dgraph_vertex_HSet.c
 @author Greg Lee
 @version 1.0.0
 @brief: "implementation file for hash set of dgraph vertices"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for i_dgraph_vertex_HSet type.

*/
#include "i_dgraph_vertex_HSet.h"
#include "ii_DGraph.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t
address_to_hash( void *p );

#define Dgraph_prefix ii
#define DGraph_dispose_of_vertex( arg ) PRIMITIVE_CAT( arg, _dgraph_dispose_of_vertex )
#define DGraph_address_to_hash( arg ) PRIMITIVE_CAT( arg, _dgraph_address_to_hash )

void
DGraph_dispose_of_vertex( Dgraph_prefix )( DGraph_vertex_type( Dgraph_prefix ) *vertex );

int32_t
DGraph_address_to_hash( Dgraph_prefix )( DGraph_vertex_type( Dgraph_prefix ) *vertex );

#define HASH_FUNCTION( arg ) ( DGraph_address_to_hash( Dgraph_prefix )( arg ) )

#define EQUALITY_FUNCTION( arg1, arg2 ) ( arg1 == arg2 )

#define DISPOSE_FUNCTION( arg ) ( DGraph_dispose_of_vertex( Dgraph_prefix )( arg ) )
#define DUPLICATE_FUNCTION( arg ) ( arg )

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix i_dgraph_vertex
#define Item DGraph_vertex_type( Dgraph_prefix ) *
#define Type_Code 0xA5000602

#include "HSet.c"

#undef Prefix
#undef Item
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */

