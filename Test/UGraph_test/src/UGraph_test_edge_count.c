/**
 @file UGraph_test_edge_count.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for UGraph_make_Depth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for UGraph_t

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
   test_edge_count_1
*/

void test_edge_count_1( void )
{
   ii_ugraph_t *ugraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t e = 0;

   ugraph = ii_ugraph_make();
   
   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   
   e = ii_ugraph_edge_add( ugraph, v1, v2, 29 );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 2 );
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 1 );
   
   ii_ugraph_dispose( &ugraph );

   return;
}

/**
   test_edge_count_2
*/

void test_edge_count_2( void )
{
   ii_ugraph_t *ugraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t v5 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;
   int32_t e3 = 0;
   int32_t e4 = 0;

   ugraph = ii_ugraph_make();
   
   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   v3 = ii_ugraph_vertex_add( ugraph, 29 );
   v4 = ii_ugraph_vertex_add( ugraph, 31 );
   v5 = ii_ugraph_vertex_add( ugraph, 37 );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 5 );
   
   e1 = ii_ugraph_edge_add( ugraph, v1, v2, 2 );
   e2 = ii_ugraph_edge_add( ugraph, v2, v3, 3 );
   e3 = ii_ugraph_edge_add( ugraph, v3, v4, 5 );
   e4 = ii_ugraph_edge_add( ugraph, v4, v5, 7 );
   
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 4 );
   
   ii_ugraph_dispose( &ugraph );

   return;
}

/**
   test_edge_count_3
*/

void test_edge_count_3( void )
{
   ii_ugraph_t *ugraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t v5 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;
   int32_t e3 = 0;

   ugraph = ii_ugraph_make();
   
   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   v3 = ii_ugraph_vertex_add( ugraph, 29 );
   v4 = ii_ugraph_vertex_add( ugraph, 31 );
   
   ii_ugraph_vertex_remove( ugraph, v2 );
   
   v5 = ii_ugraph_vertex_add( ugraph, 37 );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 4 );
   
   e1 = ii_ugraph_edge_add( ugraph, v1, v3, 2 );
   e2 = ii_ugraph_edge_add( ugraph, v3, v4, 3 );
   e3 = ii_ugraph_edge_add( ugraph, v4, v5, 5 );
   
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 3 );
   
   ii_ugraph_dispose( &ugraph );

   return;
}

int
add_test_edge_count( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_edge_count", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_edge_count_1
   add_test_to_suite( p_suite, test_edge_count_1, "test_edge_count_1" );

   // test_edge_count_2
   add_test_to_suite( p_suite, test_edge_count_2, "test_edge_count_2" );

   // test_edge_count_3
   add_test_to_suite( p_suite, test_edge_count_3, "test_edge_count_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

