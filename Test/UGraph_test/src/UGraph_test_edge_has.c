/**
 @file UGraph_test_edge_has.c
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
   test_edge_has_1
*/

void test_edge_has_1( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_vertex_t *v_from = NULL;
   ii_ugraph_vertex_t *v_to = NULL;
   ii_ugraph_edge_t *edge = NULL;
   int32_t flag = 0;

   ugraph = ii_ugraph_make_depth();
   v_from = ii_ugraph_vertex_make( 13 );
   ii_ugraph_put( ugraph, v_from );
   v_to = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_to );

   ii_ugraph_edge_put( ugraph, 23, v_from, v_to );
   ii_ugraph_edge_start( ugraph );
   edge = ii_ugraph_edge_at( ugraph );
   flag = ii_ugraph_edge_has( ugraph, edge );

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( v_from != NULL );
   CU_ASSERT( v_to != NULL );
   CU_ASSERT( edge != NULL );
   CU_ASSERT( flag == 1 );
   CU_ASSERT( ii_ugraph_count( ugraph ) == 2 );
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 1 );
   CU_ASSERT( ii_ugraph_edge_is_empty( ugraph ) == 0 );
   CU_ASSERT( ii_ugraph_edge_off( ugraph ) == 0 );

   ii_ugraph_dispose( ugraph );

   return;
}

/**
   test_edge_has_2
*/

void test_edge_has_2( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_vertex_t *v_from = NULL;
   ii_ugraph_vertex_t *v_to = NULL;
   ii_ugraph_vertex_t *v_1 = NULL;
   ii_ugraph_edge_t *edge = NULL;
   int32_t flag = 0;

   ugraph = ii_ugraph_make_depth();
   v_from = ii_ugraph_vertex_make( 13 );
   ii_ugraph_put( ugraph, v_from );
   v_to = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_to );
   v_1 = ii_ugraph_vertex_make( 15 );
   ii_ugraph_put( ugraph, v_1 );

   ii_ugraph_edge_put( ugraph, 23, v_from, v_1 );
   ii_ugraph_edge_put( ugraph, 23, v_from, v_to );
   ii_ugraph_edge_start( ugraph );
   edge = ii_ugraph_edge_at( ugraph );
   flag = ii_ugraph_edge_has( ugraph, edge );

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( v_from != NULL );
   CU_ASSERT( v_to != NULL );
   CU_ASSERT( v_1 != NULL );
   CU_ASSERT( edge != NULL );
   CU_ASSERT( flag == 1 );
   CU_ASSERT( ii_ugraph_count( ugraph ) == 3 );
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 2 );
   CU_ASSERT( ii_ugraph_edge_is_empty( ugraph ) == 0 );
   CU_ASSERT( ii_ugraph_edge_off( ugraph ) == 0 );

   ii_ugraph_dispose( ugraph );

   return;
}

int
add_test_edge_has( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_edge_has", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_edge_has_1
   add_test_to_suite( p_suite, test_edge_has_1, "test_edge_has_1" );

   // test_edge_has_2
   add_test_to_suite( p_suite, test_edge_has_2, "test_edge_has_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

