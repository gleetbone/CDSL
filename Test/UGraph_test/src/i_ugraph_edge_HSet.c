/**
 @file i_ugraph_edge_HSet.c
 @author Greg Lee
 @version 1.0.0
 @brief: "implementation file for hash set of ugraph edges"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for i_ugraph_edge_HSet type.

*/
#include "i_ugraph_edge_HSet.h"
#include "ii_UGraph.h"

#ifdef __cplusplus
extern "C" {
#endif

#define Dgraph_prefix ii
#define UGraph_edge_address_to_hash( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_address_to_hash )
#define UGraph_dispose_of_edge( arg ) PRIMITIVE_CAT( arg, _ugraph_dispose_of_edge )
#define UGraph_edge_equal( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_equal )

void
UGraph_dispose_of_edge( Dgraph_prefix )( UGraph_edge_type( Dgraph_prefix ) *edge );

int32_t
UGraph_edge_address_to_hash( Dgraph_prefix )( UGraph_edge_type( Dgraph_prefix ) *edge );

int32_t
UGraph_edge_equal( Dgraph_prefix )( UGraph_edge_type( Dgraph_prefix ) *edge1, UGraph_edge_type( Dgraph_prefix ) *edge2 );

#define HASH_FUNCTION( arg ) ( UGraph_edge_address_to_hash( Dgraph_prefix )( arg ) )

#define EQUALITY_FUNCTION( arg1, arg2 ) ( UGraph_edge_equal( Dgraph_prefix )( arg1, arg2 ) )

#define DISPOSE_FUNCTION( arg ) ( UGraph_dispose_of_edge( Dgraph_prefix )( arg ) )
#define DUPLICATE_FUNCTION( arg ) ( arg )

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix i_ugraph_edge
#define Item UGraph_edge_type( Dgraph_prefix ) *
#define Type_Code 0xA5000611

#include "HSet.c"

#ifdef __cplusplus
}
#endif

/* End of file */

