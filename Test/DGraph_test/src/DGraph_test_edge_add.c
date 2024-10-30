/**
 @file DGraph_test_edge_add.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for DGraph_make_Depth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for DGraph_t

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
   test_edge_add_1
*/

void test_edge_add_1( void )
{
   ii_dgraph_t *dgraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t e = 0;

   dgraph = ii_dgraph_make();
   
   v1 = ii_dgraph_vertex_add( dgraph, 19 );
   v2 = ii_dgraph_vertex_add( dgraph, 23 );
   
   e = ii_dgraph_edge_add( dgraph, v1, v2, 29 );
   
   CU_ASSERT( ii_dgraph_vertex_count( dgraph ) == 2 );
   CU_ASSERT( ii_dgraph_edge_count( dgraph ) == 1 );
   
   ii_dgraph_dispose( &dgraph );

   return;
}

/**
   test_edge_add_2
*/

void test_edge_add_2( void )
{
   ii_dgraph_t *dgraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t v5 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;
   int32_t e3 = 0;
   int32_t e4 = 0;

   dgraph = ii_dgraph_make();
   
   v1 = ii_dgraph_vertex_add( dgraph, 19 );
   v2 = ii_dgraph_vertex_add( dgraph, 23 );
   v3 = ii_dgraph_vertex_add( dgraph, 29 );
   v4 = ii_dgraph_vertex_add( dgraph, 31 );
   v5 = ii_dgraph_vertex_add( dgraph, 37 );
   
   CU_ASSERT( ii_dgraph_vertex_count( dgraph ) == 5 );
   
   e1 = ii_dgraph_edge_add( dgraph, v1, v2, 2 );
   e2 = ii_dgraph_edge_add( dgraph, v2, v3, 3 );
   e3 = ii_dgraph_edge_add( dgraph, v3, v4, 5 );
   e3 = ii_dgraph_edge_add( dgraph, v4, v5, 7 );
   
   CU_ASSERT( ii_dgraph_edge_count( dgraph ) == 4 );
   
   ii_dgraph_dispose( &dgraph );

   return;
}

/**
   test_edge_add_3
*/

void test_edge_add_3( void )
{
   ii_dgraph_t *dgraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t v5 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;
   int32_t e3 = 0;

   dgraph = ii_dgraph_make();
   
   v1 = ii_dgraph_vertex_add( dgraph, 19 );
   v2 = ii_dgraph_vertex_add( dgraph, 23 );
   v3 = ii_dgraph_vertex_add( dgraph, 29 );
   v4 = ii_dgraph_vertex_add( dgraph, 31 );
   
   ii_dgraph_vertex_remove( dgraph, v2 );
   
   v5 = ii_dgraph_vertex_add( dgraph, 37 );
   
   CU_ASSERT( ii_dgraph_vertex_count( dgraph ) == 4 );
   
   e1 = ii_dgraph_edge_add( dgraph, v1, v3, 2 );
   e2 = ii_dgraph_edge_add( dgraph, v3, v4, 3 );
   e3 = ii_dgraph_edge_add( dgraph, v4, v5, 5 );
   
   CU_ASSERT( ii_dgraph_edge_count( dgraph ) == 3 );
   
   ii_dgraph_dispose( &dgraph );

   return;
}

int
add_test_edge_add( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_edge_add", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_edge_add_1
   add_test_to_suite( p_suite, test_edge_add_1, "test_edge_add_1" );

   // test_edge_add_2
   add_test_to_suite( p_suite, test_edge_add_2, "test_edge_add_2" );

   // test_edge_add_3
   add_test_to_suite( p_suite, test_edge_add_3, "test_edge_add_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

