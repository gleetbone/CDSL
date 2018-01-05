/**
 @file i_dgraph_edge_HSet.c
 @author Greg Lee
 @version 1.0.0
 @brief: "implementation file for hash set of dgraph edges"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for i_dgraph_edge_HSet type.

*/
#include "i_dgraph_edge_HSet.h"
#include "ii_DGraph.h"

#ifdef __cplusplus
extern "C" {
#endif

#define Dgraph_prefix ii
#define DGraph_edge_address_to_hash( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_address_to_hash )
#define DGraph_dispose_of_edge( arg ) PRIMITIVE_CAT( arg, _dgraph_dispose_of_edge )
#define DGraph_edge_equal( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_equal )

void
DGraph_dispose_of_edge( Dgraph_prefix )( DGraph_edge_type( Dgraph_prefix ) *edge );

int32_t
DGraph_edge_address_to_hash( Dgraph_prefix )( DGraph_edge_type( Dgraph_prefix ) *edge );

int32_t
DGraph_edge_equal( Dgraph_prefix )( DGraph_edge_type( Dgraph_prefix ) *edge1, DGraph_edge_type( Dgraph_prefix ) *edge2 );

#define HASH_FUNCTION( arg ) ( DGraph_edge_address_to_hash( Dgraph_prefix )( arg ) )

#define EQUALITY_FUNCTION( arg1, arg2 ) ( DGraph_edge_equal( Dgraph_prefix )( arg1, arg2 ) )

#define DISPOSE_FUNCTION( arg ) ( DGraph_dispose_of_edge( Dgraph_prefix )( arg ) )
#define DUPLICATE_FUNCTION( arg ) ( arg )

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix i_dgraph_edge
#define Item DGraph_edge_type( Dgraph_prefix ) *
#define Type_Code 0xA5000601

#include "HSet.c"

#undef Prefix
#undef Item
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */

