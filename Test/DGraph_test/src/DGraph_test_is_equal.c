/**
 @file DGraph_test_is_equal.c
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
   test_is_equal_1
*/

void test_is_equal_1( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_t *dgraph1 = NULL;

   dgraph = ii_dgraph_make();

   CU_ASSERT( dgraph != NULL );
   CU_ASSERT( ii_dgraph_vertex_count( dgraph ) == 0 );

   dgraph1 = ii_dgraph_clone( dgraph );
  
   CU_ASSERT( dgraph1 != NULL );
   CU_ASSERT( ii_dgraph_vertex_count( dgraph1 ) == 0 );

   CU_ASSERT( ii_dgraph_is_equal( dgraph, dgraph1 ) == 1 );
   
   ii_dgraph_dispose( &dgraph );
   ii_dgraph_dispose( &dgraph1 );

   return;
}

/**
   test_is_equal_2
*/

void test_is_equal_2( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_t *dgraph1 = NULL;
   ii_dgraph_t *dgraph2 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t e = 0;

   dgraph = ii_dgraph_make();
   dgraph2 = ii_dgraph_make();

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

   CU_ASSERT( ii_dgraph_is_equal( dgraph, dgraph1 ) == 1 );
   CU_ASSERT( ii_dgraph_is_equal( dgraph, dgraph2 ) == 0 );
   
   ii_dgraph_dispose( &dgraph );
   ii_dgraph_dispose( &dgraph1 );
   ii_dgraph_dispose( &dgraph2 );

   return;
}

/**
   test_is_equal_3
*/

void test_is_equal_3( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_t *dgraph1 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t e = 0;

   dgraph = ii_dgraph_make();

   v1 = ii_dgraph_vertex_add( dgraph, 19 );
   v2 = ii_dgraph_vertex_add( dgraph, 23 );
   v3 = ii_dgraph_vertex_add( dgraph, 29 );
   e = ii_dgraph_edge_add( dgraph, v1, v2, 29 );
   
   CU_ASSERT( dgraph != NULL );
   CU_ASSERT( ii_dgraph_vertex_count( dgraph ) == 3 );
   CU_ASSERT( ii_dgraph_edge_count( dgraph ) == 1 );

   dgraph1 = ii_dgraph_clone( dgraph );
  
   CU_ASSERT( dgraph1 != NULL );
   CU_ASSERT( ii_dgraph_vertex_count( dgraph1 ) == 3 );
   CU_ASSERT( ii_dgraph_edge_count( dgraph1 ) == 1 );

   ii_dgraph_vertex_remove( dgraph, v1 );
   ii_dgraph_vertex_remove( dgraph1, v2 );
   
   CU_ASSERT( ii_dgraph_is_equal( dgraph, dgraph1 ) == 0 );
   
   ii_dgraph_dispose( &dgraph );
   ii_dgraph_dispose( &dgraph1 );

   return;
}

/**
   test_is_equal_4
*/

void test_is_equal_4( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_t *dgraph1 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;

   dgraph = ii_dgraph_make();

   v1 = ii_dgraph_vertex_add( dgraph, 19 );
   v2 = ii_dgraph_vertex_add( dgraph, 23 );
   v3 = ii_dgraph_vertex_add( dgraph, 29 );
   v4 = ii_dgraph_vertex_add( dgraph, 31 );
   
   ii_dgraph_vertex_value_put( dgraph, v1, 5 );
   
   dgraph1 = ii_dgraph_clone( dgraph );
  
   e1 = ii_dgraph_edge_add( dgraph, v2, v1, 2 );
   e2 = ii_dgraph_edge_add( dgraph, v3, v1, 2 );
   
   e1 = ii_dgraph_edge_add( dgraph1, v2, v1, 3 );
   e2 = ii_dgraph_edge_add( dgraph1, v4, v1, 2 );
   
   CU_ASSERT( ii_dgraph_is_equal( dgraph, dgraph1 ) == 0 );
   CU_ASSERT( ii_dgraph_is_equal( dgraph1, dgraph ) == 0 );
   
   ii_dgraph_dispose( &dgraph );
   ii_dgraph_dispose( &dgraph1 );

   return;
}

/**
   test_is_equal_5
*/

void test_is_equal_5( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_t *dgraph1 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;

   dgraph = ii_dgraph_make();

   v1 = ii_dgraph_vertex_add( dgraph, 19 );
   v2 = ii_dgraph_vertex_add( dgraph, 23 );
   v3 = ii_dgraph_vertex_add( dgraph, 29 );
   v4 = ii_dgraph_vertex_add( dgraph, 31 );
   
   ii_dgraph_vertex_value_put( dgraph, v1, 5 );
   
   dgraph1 = ii_dgraph_clone( dgraph );
  
   e1 = ii_dgraph_edge_add( dgraph, v2, v1, 2 );
   e2 = ii_dgraph_edge_add( dgraph, v3, v1, 2 );
   
   e1 = ii_dgraph_edge_add( dgraph1, v2, v1, 3 );
   
   CU_ASSERT( ii_dgraph_is_equal( dgraph, dgraph1 ) == 0 );
   CU_ASSERT( ii_dgraph_is_equal( dgraph1, dgraph ) == 0 );
   
   ii_dgraph_dispose( &dgraph );
   ii_dgraph_dispose( &dgraph1 );

   return;
}

/**
   test_is_equal_6
*/

void test_is_equal_6( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_t *dgraph1 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;

   dgraph = ii_dgraph_make();

   v1 = ii_dgraph_vertex_add( dgraph, 19 );
   v2 = ii_dgraph_vertex_add( dgraph, 23 );
   v3 = ii_dgraph_vertex_add( dgraph, 29 );
   v4 = ii_dgraph_vertex_add( dgraph, 31 );
   
   dgraph1 = ii_dgraph_clone( dgraph );
  
   ii_dgraph_vertex_value_put( dgraph, v1, 5 );
   
   e1 = ii_dgraph_edge_add( dgraph, v1, v2, 2 );
   e2 = ii_dgraph_edge_add( dgraph, v1, v3, 2 );
   
   e1 = ii_dgraph_edge_add( dgraph1, v1, v2, 3 );
   e2 = ii_dgraph_edge_add( dgraph1, v1, v4, 2 );
   
   CU_ASSERT( ii_dgraph_is_equal( dgraph, dgraph1 ) == 0 );
   CU_ASSERT( ii_dgraph_is_equal( dgraph1, dgraph ) == 0 );
   
   ii_dgraph_dispose( &dgraph );
   ii_dgraph_dispose( &dgraph1 );

   return;
}

/**
   test_is_equal_7
*/

void test_is_equal_7( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_t *dgraph1 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;

   dgraph = ii_dgraph_make();

   v1 = ii_dgraph_vertex_add( dgraph, 19 );
   v2 = ii_dgraph_vertex_add( dgraph, 23 );
   v3 = ii_dgraph_vertex_add( dgraph, 29 );
   v4 = ii_dgraph_vertex_add( dgraph, 31 );
   
   dgraph1 = ii_dgraph_clone( dgraph );
  
   ii_dgraph_vertex_value_put( dgraph, v1, 5 );
   
   e1 = ii_dgraph_edge_add( dgraph, v1, v2, 2 );
   e2 = ii_dgraph_edge_add( dgraph, v1, v3, 2 );
   
   e1 = ii_dgraph_edge_add( dgraph1, v1, v2, 3 );
   e2 = ii_dgraph_edge_add( dgraph1, v1, v4, 2 );
   
   ii_dgraph_edge_remove( dgraph1, e1 );
   
   CU_ASSERT( ii_dgraph_is_equal( dgraph, dgraph1 ) == 0 );
   CU_ASSERT( ii_dgraph_is_equal( dgraph1, dgraph ) == 0 );
   
   ii_dgraph_dispose( &dgraph );
   ii_dgraph_dispose( &dgraph1 );

   return;
}

/**
   test_is_equal_8
*/

void test_is_equal_8( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_t *dgraph1 = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;

   dgraph = ii_dgraph_make();

   v1 = ii_dgraph_vertex_add( dgraph, 19 );
   v2 = ii_dgraph_vertex_add( dgraph, 23 );
   v3 = ii_dgraph_vertex_add( dgraph, 29 );
   v4 = ii_dgraph_vertex_add( dgraph, 31 );
   
   dgraph1 = ii_dgraph_clone( dgraph );
  
   ii_dgraph_vertex_value_put( dgraph, v1, 5 );
   
   e1 = ii_dgraph_edge_add( dgraph, v1, v2, 2 );
   e2 = ii_dgraph_edge_add( dgraph, v1, v3, 2 );
   
   e1 = ii_dgraph_edge_add( dgraph1, v1, v2, 3 );
   e2 = ii_dgraph_edge_add( dgraph1, v1, v4, 2 );
   
   ii_dgraph_edge_value_put( dgraph1, e1, 123 );
   
   CU_ASSERT( ii_dgraph_is_equal( dgraph, dgraph1 ) == 0 );
   CU_ASSERT( ii_dgraph_is_equal( dgraph1, dgraph ) == 0 );
   
   ii_dgraph_dispose( &dgraph );
   ii_dgraph_dispose( &dgraph1 );

   return;
}

int
add_test_is_equal( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_equal", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_equal_1
   add_test_to_suite( p_suite, test_is_equal_1, "test_is_equal_1" );

   // test_is_equal_2
   add_test_to_suite( p_suite, test_is_equal_2, "test_is_equal_2" );

   // test_is_equal_3
   add_test_to_suite( p_suite, test_is_equal_3, "test_is_equal_3" );

   // test_is_equal_4
   add_test_to_suite( p_suite, test_is_equal_4, "test_is_equal_4" );

   // test_is_equal_5
   add_test_to_suite( p_suite, test_is_equal_5, "test_is_equal_5" );

   // test_is_equal_6
   add_test_to_suite( p_suite, test_is_equal_6, "test_is_equal_6" );

   // test_is_equal_7
   add_test_to_suite( p_suite, test_is_equal_7, "test_is_equal_7" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

