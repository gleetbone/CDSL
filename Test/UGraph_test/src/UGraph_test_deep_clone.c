/**
 @file UGraph_test_deep_clone.c
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
   test_deep_clone_1
*/

void test_deep_clone_1( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_t *ugraph1 = NULL;

   ugraph = ii_ugraph_make();

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 0 );

   ugraph1 = ii_ugraph_deep_clone( ugraph );
  
   CU_ASSERT( ugraph1 != NULL );
   CU_ASSERT( ii_ugraph_vertex_count( ugraph1 ) == 0 );

   ii_ugraph_dispose( &ugraph );
   ii_ugraph_dispose( &ugraph1 );

   return;
}

/**
   test_deep_clone_2
*/

void test_deep_clone_2( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_t *ugraph1 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t e = 0;

   ugraph = ii_ugraph_make();

   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   e = ii_ugraph_edge_add( ugraph, v1, v2, 29 );
   
   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 2 );
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 1 );

   ugraph1 = ii_ugraph_deep_clone( ugraph );
  
   CU_ASSERT( ugraph1 != NULL );
   CU_ASSERT( ii_ugraph_vertex_count( ugraph1 ) == 2 );
   CU_ASSERT( ii_ugraph_edge_count( ugraph1 ) == 1 );

   ii_ugraph_dispose( &ugraph );
   ii_ugraph_dispose( &ugraph1 );

   return;
}

int
add_test_deep_clone( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_deep_clone", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_deep_clone_1
   add_test_to_suite( p_suite, test_deep_clone_1, "test_deep_clone_1" );

   // test_deep_clone_2
   add_test_to_suite( p_suite, test_deep_clone_2, "test_deep_clone_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

