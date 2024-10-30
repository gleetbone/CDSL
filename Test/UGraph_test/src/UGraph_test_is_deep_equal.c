/**
 @file UGraph_test_is_deep_equal.c
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
   test_is_deep_equal_1
*/

void test_is_deep_equal_1( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_t *ugraph1 = NULL;

   ugraph = ii_ugraph_make();

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 0 );

   ugraph1 = ii_ugraph_deep_clone( ugraph );
  
   CU_ASSERT( ugraph1 != NULL );
   CU_ASSERT( ii_ugraph_vertex_count( ugraph1 ) == 0 );

   CU_ASSERT( ii_ugraph_is_deep_equal( ugraph, ugraph1 ) == 1 );
   
   ii_ugraph_dispose( &ugraph );
   ii_ugraph_dispose( &ugraph1 );

   return;
}

/**
   test_is_deep_equal_2
*/

void test_is_deep_equal_2( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_t *ugraph1 = NULL;
   ii_ugraph_t *ugraph2 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t e = 0;

   ugraph = ii_ugraph_make();
   ugraph2 = ii_ugraph_make();

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

   CU_ASSERT( ii_ugraph_is_deep_equal( ugraph, ugraph1 ) == 1 );
   CU_ASSERT( ii_ugraph_is_deep_equal( ugraph, ugraph2 ) == 0 );
   
   ii_ugraph_dispose( &ugraph );
   ii_ugraph_dispose( &ugraph1 );
   ii_ugraph_dispose( &ugraph2 );

   return;
}

/**
   test_is_deep_equal_3
*/

void test_is_deep_equal_3( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_t *ugraph1 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t e = 0;

   ugraph = ii_ugraph_make();

   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   v3 = ii_ugraph_vertex_add( ugraph, 29 );
   e = ii_ugraph_edge_add( ugraph, v1, v2, 29 );
   
   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 3 );
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 1 );

   ugraph1 = ii_ugraph_clone( ugraph );
  
   CU_ASSERT( ugraph1 != NULL );
   CU_ASSERT( ii_ugraph_vertex_count( ugraph1 ) == 3 );
   CU_ASSERT( ii_ugraph_edge_count( ugraph1 ) == 1 );

   ii_ugraph_vertex_remove( ugraph, v1 );
   ii_ugraph_vertex_remove( ugraph1, v2 );
   
   CU_ASSERT( ii_ugraph_is_deep_equal( ugraph, ugraph1 ) == 0 );
   
   ii_ugraph_dispose( &ugraph );
   ii_ugraph_dispose( &ugraph1 );

   return;
}

/**
   test_is_deep_equal_4
*/

void test_is_deep_equal_4( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_t *ugraph1 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;

   ugraph = ii_ugraph_make();

   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   v3 = ii_ugraph_vertex_add( ugraph, 29 );
   v4 = ii_ugraph_vertex_add( ugraph, 31 );
   
   ii_ugraph_vertex_value_put( ugraph, v1, 5 );
   
   ugraph1 = ii_ugraph_clone( ugraph );
  
   e1 = ii_ugraph_edge_add( ugraph, v2, v1, 2 );
   e2 = ii_ugraph_edge_add( ugraph, v3, v1, 2 );
   
   e1 = ii_ugraph_edge_add( ugraph1, v2, v1, 3 );
   e2 = ii_ugraph_edge_add( ugraph1, v4, v1, 2 );
   
   CU_ASSERT( ii_ugraph_is_deep_equal( ugraph, ugraph1 ) == 0 );
   CU_ASSERT( ii_ugraph_is_deep_equal( ugraph1, ugraph ) == 0 );
   
   ii_ugraph_dispose( &ugraph );
   ii_ugraph_dispose( &ugraph1 );

   return;
}

/**
   test_is_deep_equal_5
*/

void test_is_deep_equal_5( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_t *ugraph1 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;

   ugraph = ii_ugraph_make();

   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   v3 = ii_ugraph_vertex_add( ugraph, 29 );
   v4 = ii_ugraph_vertex_add( ugraph, 31 );
   
   ii_ugraph_vertex_value_put( ugraph, v1, 5 );
   
   ugraph1 = ii_ugraph_clone( ugraph );
  
   e1 = ii_ugraph_edge_add( ugraph, v2, v1, 2 );
   e2 = ii_ugraph_edge_add( ugraph, v3, v1, 2 );
   
   e1 = ii_ugraph_edge_add( ugraph1, v2, v1, 3 );
   
   CU_ASSERT( ii_ugraph_is_deep_equal( ugraph, ugraph1 ) == 0 );
   CU_ASSERT( ii_ugraph_is_deep_equal( ugraph1, ugraph ) == 0 );
   
   ii_ugraph_dispose( &ugraph );
   ii_ugraph_dispose( &ugraph1 );

   return;
}

/**
   test_is_deep_equal_6
*/

void test_is_deep_equal_6( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_t *ugraph1 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;

   ugraph = ii_ugraph_make();

   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   v3 = ii_ugraph_vertex_add( ugraph, 29 );
   v4 = ii_ugraph_vertex_add( ugraph, 31 );
   
   ugraph1 = ii_ugraph_clone( ugraph );
  
   ii_ugraph_vertex_value_put( ugraph, v1, 5 );
   
   e1 = ii_ugraph_edge_add( ugraph, v1, v2, 2 );
   e2 = ii_ugraph_edge_add( ugraph, v1, v3, 2 );
   
   e1 = ii_ugraph_edge_add( ugraph1, v1, v2, 3 );
   e2 = ii_ugraph_edge_add( ugraph1, v1, v4, 2 );
   
   CU_ASSERT( ii_ugraph_is_deep_equal( ugraph, ugraph1 ) == 0 );
   CU_ASSERT( ii_ugraph_is_deep_equal( ugraph1, ugraph ) == 0 );
   
   ii_ugraph_dispose( &ugraph );
   ii_ugraph_dispose( &ugraph1 );

   return;
}

/**
   test_is_deep_equal_7
*/

void test_is_deep_equal_7( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_t *ugraph1 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;

   ugraph = ii_ugraph_make();

   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   v3 = ii_ugraph_vertex_add( ugraph, 29 );
   v4 = ii_ugraph_vertex_add( ugraph, 31 );
   
   ugraph1 = ii_ugraph_clone( ugraph );
  
   ii_ugraph_vertex_value_put( ugraph, v1, 5 );
   
   e1 = ii_ugraph_edge_add( ugraph, v1, v2, 2 );
   e2 = ii_ugraph_edge_add( ugraph, v1, v3, 2 );
   
   e1 = ii_ugraph_edge_add( ugraph1, v1, v2, 3 );
   e2 = ii_ugraph_edge_add( ugraph1, v1, v4, 2 );
   
   ii_ugraph_edge_remove( ugraph1, e1 );
   
   CU_ASSERT( ii_ugraph_is_deep_equal( ugraph, ugraph1 ) == 0 );
   CU_ASSERT( ii_ugraph_is_deep_equal( ugraph1, ugraph ) == 0 );
   
   ii_ugraph_dispose( &ugraph );
   ii_ugraph_dispose( &ugraph1 );

   return;
}

/**
   test_is_deep_equal_8
*/

void test_is_deep_equal_8( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_t *ugraph1 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;

   ugraph = ii_ugraph_make();

   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   v3 = ii_ugraph_vertex_add( ugraph, 29 );
   v4 = ii_ugraph_vertex_add( ugraph, 31 );
   
   ugraph1 = ii_ugraph_clone( ugraph );
  
   ii_ugraph_vertex_value_put( ugraph, v1, 5 );
   
   e1 = ii_ugraph_edge_add( ugraph, v1, v2, 2 );
   e2 = ii_ugraph_edge_add( ugraph, v1, v3, 2 );
   
   e1 = ii_ugraph_edge_add( ugraph1, v1, v2, 3 );
   e2 = ii_ugraph_edge_add( ugraph1, v1, v4, 2 );
   
   ii_ugraph_edge_value_put( ugraph1, e1, 123 );
   
   CU_ASSERT( ii_ugraph_is_deep_equal( ugraph, ugraph1 ) == 0 );
   CU_ASSERT( ii_ugraph_is_deep_equal( ugraph1, ugraph ) == 0 );
   
   ii_ugraph_dispose( &ugraph );
   ii_ugraph_dispose( &ugraph1 );

   return;
}

int
add_test_is_deep_equal( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_deep_equal", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_deep_equal_1
   add_test_to_suite( p_suite, test_is_deep_equal_1, "test_is_deep_equal_1" );

   // test_is_deep_equal_2
   add_test_to_suite( p_suite, test_is_deep_equal_2, "test_is_deep_equal_2" );

   // test_is_deep_equal_3
   add_test_to_suite( p_suite, test_is_deep_equal_3, "test_is_deep_equal_3" );

   // test_is_deep_equal_4
   add_test_to_suite( p_suite, test_is_deep_equal_4, "test_is_deep_equal_4" );

   // test_is_deep_equal_5
   add_test_to_suite( p_suite, test_is_deep_equal_5, "test_is_deep_equal_5" );

   // test_is_deep_equal_6
   add_test_to_suite( p_suite, test_is_deep_equal_6, "test_is_deep_equal_6" );

   // test_is_deep_equal_7
   add_test_to_suite( p_suite, test_is_deep_equal_7, "test_is_deep_equal_7" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

