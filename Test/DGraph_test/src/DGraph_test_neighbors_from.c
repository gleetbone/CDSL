/**
 @file DGraph_test_neighbors_from.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for DGraph_make_Depth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for DGraph_cursor_make_depth.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_DGraph.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_neighbors_from_1
*/

void test_neighbors_from_1( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_vertex_t *v1 = NULL;
   ii_dgraph_vertex_t *v2 = NULL;
   ii_dgraph_vertex_t *v3 = NULL;
   ii_dgraph_vertex_t **a = NULL;

   dgraph = ii_dgraph_make_depth();

   v1 = ii_dgraph_vertex_make( 1 );
   ii_dgraph_put( dgraph, v1 );

   v2 = ii_dgraph_vertex_make( 2 );
   ii_dgraph_put( dgraph, v2 );

   v3 = ii_dgraph_vertex_make( 3 );
   ii_dgraph_put( dgraph, v3 );

   ii_dgraph_edge_put( dgraph, 12, v1, v2);
   ii_dgraph_edge_put( dgraph, 23, v2, v3);

   a = ii_dgraph_neighbors_from( dgraph, v2 );

   CU_ASSERT( dgraph != NULL );
   CU_ASSERT( v1 != NULL );
   CU_ASSERT( v2 != NULL );
   CU_ASSERT( v3 != NULL );
   CU_ASSERT( a != NULL );
   CU_ASSERT( a[0] == v1 );
   CU_ASSERT( a[1] == NULL );

   free( a );

   ii_dgraph_dispose( dgraph );

   return;
}

int
add_test_neighbors_from( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_neighbors_from", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_neighbors_from_1
   add_test_to_suite( p_suite, test_neighbors_from_1, "test_neighbors_from_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

