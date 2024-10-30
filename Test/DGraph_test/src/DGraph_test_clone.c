/**
 @file DGraph_test_clone.c
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
   test_clone_1
*/

void test_clone_1( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_t *dgraph1 = NULL;

   dgraph = ii_dgraph_make();

   CU_ASSERT( dgraph != NULL );
   CU_ASSERT( ii_dgraph_vertex_count( dgraph ) == 0 );

   dgraph1 = ii_dgraph_clone( dgraph );
  
   CU_ASSERT( dgraph1 != NULL );
   CU_ASSERT( ii_dgraph_vertex_count( dgraph1 ) == 0 );

   ii_dgraph_dispose( &dgraph );
   ii_dgraph_dispose( &dgraph1 );

   return;
}

/**
   test_clone_2
*/

void test_clone_2( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_t *dgraph1 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t e = 0;

   dgraph = ii_dgraph_make();

   v1 = ii_dgraph_vertex_add( dgraph, 19 );
   v2 = ii_dgraph_vertex_add( dgraph, 23 );
   e = ii_dgraph_edge_add( dgraph, v1, v2, 29 );
   
   CU_ASSERT( dgraph != NULL );
   CU_ASSERT( ii_dgraph_vertex_count( dgraph ) == 2 );
   CU_ASSERT( ii_dgraph_edge_count( dgraph ) == 1 );

   dgraph1 = ii_dgraph_clone( dgraph );
  
   CU_ASSERT( dgraph1 != NULL );
   CU_ASSERT( ii_dgraph_vertex_count( dgraph1 ) == 2 );
   CU_ASSERT( ii_dgraph_edge_count( dgraph1 ) == 1 );

   ii_dgraph_dispose( &dgraph );
   ii_dgraph_dispose( &dgraph1 );

   return;
}

int
add_test_clone( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_clone", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_clone_1
   add_test_to_suite( p_suite, test_clone_1, "test_clone_1" );

   // test_clone_2
   add_test_to_suite( p_suite, test_clone_2, "test_clone_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

