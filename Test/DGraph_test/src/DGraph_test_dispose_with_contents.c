/**
 @file DGraph_test_dispose_with_contents.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for DGraph_make_Depth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for DGraph_dispose_with_contents.

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
   test_dispose_with_contents_1
*/

void test_dispose_with_contents_1( void )
{
   ii_dgraph_t *dgraph = NULL;

   dgraph = ii_dgraph_make_depth();
   ii_dgraph_dispose_with_contents( dgraph );

   return;
}

/**
   test_dispose_with_contents_2
*/

void test_dispose_with_contents_2( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_vertex_t *v_from = NULL;
   ii_dgraph_vertex_t *v_to = NULL;

   dgraph = ii_dgraph_make_depth();
   v_from = ii_dgraph_vertex_make( 13 );
   ii_dgraph_put( dgraph, v_from );
   v_to = ii_dgraph_vertex_make( 14 );
   ii_dgraph_put( dgraph, v_to );
   ii_dgraph_edge_put( dgraph, 23, v_from, v_to );
   ii_dgraph_edge_put( dgraph, 31, v_to, v_from );

   ii_dgraph_dispose_with_contents( dgraph );

   return;
}

int
add_test_dispose_with_contents( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_dispose_with_contents", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_dispose_with_contents_1
   add_test_to_suite( p_suite, test_dispose_with_contents_1, "test_dispose_with_contents_1" );

   // test_dispose_with_contents_2
   add_test_to_suite( p_suite, test_dispose_with_contents_2, "test_dispose_with_contents_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

