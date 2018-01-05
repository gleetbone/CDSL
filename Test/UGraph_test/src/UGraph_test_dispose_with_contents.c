/**
 @file UGraph_test_dispose_with_contents.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for UGraph_make_Depth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for UGraph_dispose_with_contents.

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
   test_dispose_with_contents_1
*/

void test_dispose_with_contents_1( void )
{
   ii_ugraph_t *ugraph = NULL;

   ugraph = ii_ugraph_make_depth();
   ii_ugraph_dispose_with_contents( ugraph );

   return;
}

/**
   test_dispose_with_contents_2
*/

void test_dispose_with_contents_2( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_vertex_t *v1 = NULL;
   ii_ugraph_vertex_t *v2 = NULL;

   ugraph = ii_ugraph_make_depth();
   
   v1 = ii_ugraph_vertex_make( 0 );
   ii_ugraph_put( ugraph, v1 );
   
   v2 = ii_ugraph_vertex_make( 1 );
   ii_ugraph_put( ugraph, v2 );
   
   ii_ugraph_edge_put( ugraph, 1, v1, v2 );
   
   ii_ugraph_dispose_with_contents( ugraph );

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

