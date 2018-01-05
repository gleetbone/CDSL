/**
 @file UGraph_test_neighbors.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for UGraph_make_Depth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for UGraph_cursor_make_depth.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_UGraph.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_neighbors_1
*/

void test_neighbors_1( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_vertex_t *v1 = NULL;
   ii_ugraph_vertex_t *v2 = NULL;
   ii_ugraph_vertex_t *v3 = NULL;
   ii_ugraph_vertex_t **a = NULL;

   ugraph = ii_ugraph_make_depth();

   v1 = ii_ugraph_vertex_make( 1 );
   ii_ugraph_put( ugraph, v1 );

   v2 = ii_ugraph_vertex_make( 2 );
   ii_ugraph_put( ugraph, v2 );

   v3 = ii_ugraph_vertex_make( 3 );
   ii_ugraph_put( ugraph, v3 );

   ii_ugraph_edge_put( ugraph, 12, v1, v2);
   ii_ugraph_edge_put( ugraph, 23, v2, v3);

   a = ii_ugraph_neighbors( ugraph, v2 );

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( v1 != NULL );
   CU_ASSERT( v2 != NULL );
   CU_ASSERT( v3 != NULL );
   CU_ASSERT( a != NULL );
   CU_ASSERT( a[0] == v1 );
   CU_ASSERT( a[1] == v3 );
   CU_ASSERT( a[2] == NULL );

   free( a );

   ii_ugraph_dispose( ugraph );

   return;
}

int
add_test_neighbors( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_neighbors", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_neighbors_1
   add_test_to_suite( p_suite, test_neighbors_1, "test_neighbors_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

