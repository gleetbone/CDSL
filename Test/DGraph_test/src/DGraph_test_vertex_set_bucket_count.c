/**
 @file DGraph_test_vertex_set_bucket_count.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for DGraph_make_Depth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for DGraph_make_depth.

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
   test_vertex_set_bucket_count_1
*/

void test_vertex_set_bucket_count_1( void )
{
   ii_dgraph_t *dgraph = NULL;

   dgraph = ii_dgraph_make_depth();
   ii_dgraph_vertex_set_bucket_count( dgraph, 29 );

   CU_ASSERT( dgraph != NULL );
   CU_ASSERT( ii_dgraph_count( dgraph ) == 0 );
   CU_ASSERT( ii_dgraph_is_empty( dgraph ) == 1 );

   ii_dgraph_dispose( dgraph );

   return;
}

/**
   test_vertex_set_bucket_count_2
*/

void test_vertex_set_bucket_count_2( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_vertex_t *v = NULL;

   dgraph = ii_dgraph_make_depth();
   v = ii_dgraph_vertex_make( 31 );
   ii_dgraph_put( dgraph, v );

   ii_dgraph_vertex_set_bucket_count( dgraph, 29 );

   CU_ASSERT( dgraph != NULL );
   CU_ASSERT( ii_dgraph_count( dgraph ) == 1 );
   CU_ASSERT( ii_dgraph_is_empty( dgraph ) == 0 );

   ii_dgraph_dispose( dgraph );

   return;
}

int
add_test_vertex_set_bucket_count( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_vertex_set_bucket_count", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_vertex_set_bucket_count_1
   add_test_to_suite( p_suite, test_vertex_set_bucket_count_1, "test_vertex_set_bucket_count_1" );

   // test_vertex_set_bucket_count_2
   add_test_to_suite( p_suite, test_vertex_set_bucket_count_2, "test_vertex_set_bucket_count_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

