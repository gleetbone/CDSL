/**
 @file UGraph_test_edge_v1_v2.c
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
   test_edge_v1_v2_1
*/

void test_edge_v1_v2_1( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_vertex_t *v_from = NULL;
   ii_ugraph_vertex_t *v_to = NULL;
   ii_ugraph_edge_t *edge = NULL;

   ugraph = ii_ugraph_make_depth();
   v_from = ii_ugraph_vertex_make( 13 );
   ii_ugraph_put( ugraph, v_from );
   v_to = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_to );

   ii_ugraph_edge_put( ugraph, 23, v_from, v_to );
   edge = ii_ugraph_edge_v1_v2( ugraph, v_from, v_to );

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( v_from != NULL );
   CU_ASSERT( v_to != NULL );
   CU_ASSERT( edge != NULL );
   CU_ASSERT( ii_ugraph_count( ugraph ) == 2 );
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 1 );
   CU_ASSERT( ii_ugraph_edge_is_empty( ugraph ) == 0 );

   ii_ugraph_dispose( ugraph );

   return;
}

/**
   test_edge_v1_v2_2
*/

void test_edge_v1_v2_2( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_vertex_t *v_from = NULL;
   ii_ugraph_vertex_t *v_to = NULL;
   ii_ugraph_vertex_t *v_1 = NULL;
   ii_ugraph_vertex_t *v_2 = NULL;
   ii_ugraph_vertex_t *v_3 = NULL;
   ii_ugraph_vertex_t *v_4 = NULL;
   ii_ugraph_vertex_t *v_5 = NULL;
   ii_ugraph_vertex_t *v_6 = NULL;
   ii_ugraph_vertex_t *v_7 = NULL;
   ii_ugraph_vertex_t *v_8 = NULL;
   ii_ugraph_vertex_t *v_9 = NULL;
   ii_ugraph_vertex_t *v_10 = NULL;
   ii_ugraph_vertex_t *v_11 = NULL;
   ii_ugraph_vertex_t *v_12 = NULL;
   ii_ugraph_vertex_t *v_13 = NULL;
   ii_ugraph_edge_t *edge = NULL;

   ugraph = ii_ugraph_make_depth();
   v_from = ii_ugraph_vertex_make( 13 );
   ii_ugraph_put( ugraph, v_from );
   v_to = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_to );
   v_1 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_1 );
   v_2 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_2 );
   v_3 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_3 );
   v_4 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_4 );
   v_5 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_5 );
   v_6 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_6 );
   v_7 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_7 );
   v_8 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_8 );
   v_9 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_9 );
   v_10 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_10 );
   v_11 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_11 );
   v_12 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_12 );
   v_13 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_13 );

   ii_ugraph_edge_put( ugraph, 23, v_from, v_to );

   ii_ugraph_edge_put( ugraph, 23, v_from, v_1 );
   ii_ugraph_edge_put( ugraph, 23, v_from, v_2 );
   ii_ugraph_edge_put( ugraph, 23, v_from, v_3 );
   ii_ugraph_edge_put( ugraph, 23, v_from, v_4 );
   ii_ugraph_edge_put( ugraph, 23, v_from, v_5 );
   ii_ugraph_edge_put( ugraph, 23, v_from, v_6 );
   ii_ugraph_edge_put( ugraph, 23, v_from, v_7 );
   ii_ugraph_edge_put( ugraph, 23, v_from, v_8 );
   ii_ugraph_edge_put( ugraph, 23, v_from, v_9 );
   ii_ugraph_edge_put( ugraph, 23, v_from, v_10 );
   ii_ugraph_edge_put( ugraph, 23, v_from, v_11 );
   ii_ugraph_edge_put( ugraph, 23, v_from, v_12 );
   ii_ugraph_edge_put( ugraph, 23, v_from, v_13 );

   edge = ii_ugraph_edge_v1_v2( ugraph, v_from, v_to );

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( v_from != NULL );
   CU_ASSERT( v_to != NULL );
   CU_ASSERT( edge != NULL );
   CU_ASSERT( ii_ugraph_edge_is_empty( ugraph ) == 0 );

   ii_ugraph_dispose( ugraph );

   return;
}

/**
   test_edge_v1_v2_3
*/

void test_edge_v1_v2_3( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_vertex_t *v_from = NULL;
   ii_ugraph_vertex_t *v_to = NULL;
   ii_ugraph_vertex_t *v_1 = NULL;
   ii_ugraph_vertex_t *v_2 = NULL;
   ii_ugraph_vertex_t *v_3 = NULL;
   ii_ugraph_vertex_t *v_4 = NULL;
   ii_ugraph_vertex_t *v_5 = NULL;
   ii_ugraph_vertex_t *v_6 = NULL;
   ii_ugraph_vertex_t *v_7 = NULL;
   ii_ugraph_vertex_t *v_8 = NULL;
   ii_ugraph_vertex_t *v_9 = NULL;
   ii_ugraph_vertex_t *v_10 = NULL;
   ii_ugraph_vertex_t *v_11 = NULL;
   ii_ugraph_vertex_t *v_12 = NULL;
   ii_ugraph_vertex_t *v_13 = NULL;
   ii_ugraph_edge_t *edge = NULL;

   ugraph = ii_ugraph_make_depth();
   v_from = ii_ugraph_vertex_make( 13 );
   ii_ugraph_put( ugraph, v_from );
   v_to = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_to );
   v_1 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_1 );
   v_2 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_2 );
   v_3 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_3 );
   v_4 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_4 );
   v_5 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_5 );
   v_6 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_6 );
   v_7 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_7 );
   v_8 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_8 );
   v_9 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_9 );
   v_10 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_10 );
   v_11 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_11 );
   v_12 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_12 );
   v_13 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_13 );

   ii_ugraph_edge_put( ugraph, 23, v_to, v_from );

   ii_ugraph_edge_put( ugraph, 23, v_1, v_from );
   ii_ugraph_edge_put( ugraph, 23, v_2, v_from );
   ii_ugraph_edge_put( ugraph, 23, v_3, v_from );
   ii_ugraph_edge_put( ugraph, 23, v_4, v_from );
   ii_ugraph_edge_put( ugraph, 23, v_5, v_from );
   ii_ugraph_edge_put( ugraph, 23, v_6, v_from );
   ii_ugraph_edge_put( ugraph, 23, v_7, v_from );
   ii_ugraph_edge_put( ugraph, 23, v_8, v_from );
   ii_ugraph_edge_put( ugraph, 23, v_9, v_from );
   ii_ugraph_edge_put( ugraph, 23, v_10, v_from );
   ii_ugraph_edge_put( ugraph, 23, v_11, v_from );
   ii_ugraph_edge_put( ugraph, 23, v_12, v_from );
   ii_ugraph_edge_put( ugraph, 23, v_13, v_from );

   edge = ii_ugraph_edge_v1_v2( ugraph, v_to, v_from );

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( v_from != NULL );
   CU_ASSERT( v_to != NULL );
   CU_ASSERT( edge != NULL );
   CU_ASSERT( ii_ugraph_edge_is_empty( ugraph ) == 0 );

   ii_ugraph_dispose( ugraph );

   return;
}

int
add_test_edge_v1_v2( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_edge_v1_v2", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_edge_v1_v2_1
   add_test_to_suite( p_suite, test_edge_v1_v2_1, "test_edge_v1_v2_1" );

   // test_edge_v1_v2_2
   add_test_to_suite( p_suite, test_edge_v1_v2_2, "test_edge_v1_v2_2" );

   // test_edge_v1_v2_3
   add_test_to_suite( p_suite, test_edge_v1_v2_3, "test_edge_v1_v2_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

