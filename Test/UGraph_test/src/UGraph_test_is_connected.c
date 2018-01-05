/**
 @file UGraph_test_is_connected.c
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
   test_is_connected_1
*/

void test_is_connected_1( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_vertex_t *v_from = NULL;
   ii_ugraph_vertex_t *v_to = NULL;
   int32_t flag1 = 0;
   int32_t flag2 = 0;

   ugraph = ii_ugraph_make_depth();
   v_from = ii_ugraph_vertex_make( 13 );
   ii_ugraph_put( ugraph, v_from );
   v_to = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v_to );

   flag1 = ii_ugraph_is_connected( ugraph );

   ii_ugraph_edge_put( ugraph, 23, v_from, v_to );

   flag2 = ii_ugraph_is_connected( ugraph );

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( v_from != NULL );
   CU_ASSERT( v_to != NULL );
   CU_ASSERT( flag1 == 0 );
   CU_ASSERT( flag2 == 1 );

   ii_ugraph_dispose( ugraph );

   return;
}

/**
   test_is_connected_2
*/

void test_is_connected_2( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_vertex_t *v11 = NULL;
   ii_ugraph_vertex_t *v21 = NULL;
   ii_ugraph_vertex_t *v22 = NULL;
   ii_ugraph_vertex_t *v31 = NULL;
   int32_t flag1 = 0;
   int32_t flag2 = 0;
   int32_t flag3 = 0;

   ugraph = ii_ugraph_make_depth();

   v11 = ii_ugraph_vertex_make( 11 );
   ii_ugraph_put( ugraph, v11 );

   v21 = ii_ugraph_vertex_make( 21 );
   ii_ugraph_put( ugraph, v21 );

   v22 = ii_ugraph_vertex_make( 22 );
   ii_ugraph_put( ugraph, v22 );

   v31 = ii_ugraph_vertex_make( 31 );
   ii_ugraph_put( ugraph, v31 );

   flag1 = ii_ugraph_is_connected( ugraph );

   ii_ugraph_edge_put( ugraph, 1121, v11, v21);
   ii_ugraph_edge_put( ugraph, 2131, v21, v31);

   flag2 = ii_ugraph_is_connected( ugraph );

   ii_ugraph_edge_put( ugraph, 1122, v11, v22);

   flag3 = ii_ugraph_is_connected( ugraph );

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( v11 != NULL );
   CU_ASSERT( v21 != NULL );
   CU_ASSERT( v22 != NULL );
   CU_ASSERT( v31 != NULL );
   CU_ASSERT( flag1 == 0 );
   CU_ASSERT( flag2 == 0 );
   CU_ASSERT( flag3 == 1 );

   ii_ugraph_dispose( ugraph );

   return;
}

/**
   test_is_connected_3
*/

void test_is_connected_3( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_vertex_t *v11 = NULL;
   ii_ugraph_vertex_t *v21 = NULL;
   ii_ugraph_vertex_t *v22 = NULL;
   ii_ugraph_vertex_t *v31 = NULL;
   int32_t flag1 = 0;
   int32_t flag2 = 0;
   int32_t flag3 = 0;

   ugraph = ii_ugraph_make_breadth();

   v11 = ii_ugraph_vertex_make( 11 );
   ii_ugraph_put( ugraph, v11 );

   v21 = ii_ugraph_vertex_make( 21 );
   ii_ugraph_put( ugraph, v21 );

   v22 = ii_ugraph_vertex_make( 22 );
   ii_ugraph_put( ugraph, v22 );

   v31 = ii_ugraph_vertex_make( 31 );
   ii_ugraph_put( ugraph, v31 );

   flag1 = ii_ugraph_is_connected( ugraph );

   ii_ugraph_edge_put( ugraph, 1121, v11, v21);
   ii_ugraph_edge_put( ugraph, 2131, v21, v31);

   flag2 = ii_ugraph_is_connected( ugraph );

   ii_ugraph_edge_put( ugraph, 1122, v11, v22);

   flag3 = ii_ugraph_is_connected( ugraph );

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( v11 != NULL );
   CU_ASSERT( v21 != NULL );
   CU_ASSERT( v22 != NULL );
   CU_ASSERT( v31 != NULL );
   CU_ASSERT( flag1 == 0 );
   CU_ASSERT( flag2 == 0 );
   CU_ASSERT( flag3 == 1 );

   ii_ugraph_dispose( ugraph );

   return;
}

/**
   test_is_connected_4
*/

void test_is_connected_4( void )
{
   ii_ugraph_t *ugraph = NULL;
   int32_t flag = 0;

   ugraph = ii_ugraph_make_depth();

   flag = ii_ugraph_is_connected( ugraph );

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( flag == 1 );

   ii_ugraph_dispose( ugraph );

   return;
}

int
add_test_is_connected( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_connected", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_connected_1
   add_test_to_suite( p_suite, test_is_connected_1, "test_is_connected_1" );

   // test_is_connected_2
   add_test_to_suite( p_suite, test_is_connected_2, "test_is_connected_2" );

   // test_is_connected_3
   add_test_to_suite( p_suite, test_is_connected_3, "test_is_connected_3" );

   // test_is_connected_4
   add_test_to_suite( p_suite, test_is_connected_4, "test_is_connected_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

