/**
 @file DGraph_test_edge_value_from_to.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for DGraph_make_Depth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for DGraph_vertex_make.

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
   test_edge_value_from_to_1
*/

void test_edge_value_from_to_1( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_vertex_t *v_from = NULL;
   ii_dgraph_vertex_t *v_to = NULL;
   int32_t value = 0;

   dgraph = ii_dgraph_make_depth();
   v_from = ii_dgraph_vertex_make( 13 );
   v_to = ii_dgraph_vertex_make( 14 );

   ii_dgraph_put( dgraph, v_from );
   ii_dgraph_put( dgraph, v_to );

   ii_dgraph_edge_put( dgraph, 23, v_from, v_to );

   value = ii_dgraph_edge_value_from_to( dgraph, v_from, v_to );

   CU_ASSERT( value == 23 );

   ii_dgraph_dispose( dgraph );

   return;
}

int
add_test_edge_value_from_to( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_edge_value_from_to", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_edge_value_from_to_1
   add_test_to_suite( p_suite, test_edge_value_from_to_1, "test_edge_value_from_to_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

