/**
 @file DGraph_test_vertex_value_put.c
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
   test_vertex_value_put_1
*/

void test_vertex_value_put_1( void )
{
   ii_dgraph_t *dgraph = NULL;
   int32_t v = 0;

   dgraph = ii_dgraph_make();
   
   v = ii_dgraph_vertex_add( dgraph, 19 );
   
   CU_ASSERT( ii_dgraph_vertex_count( dgraph ) == 1 );
   
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v ) == 19 );
   
   ii_dgraph_vertex_value_put( dgraph, v, 29 );
   
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v ) == 29 );
   
   ii_dgraph_dispose( &dgraph );

   return;
}

/**
   test_vertex_value_put_2
*/

void test_vertex_value_put_2( void )
{
   ii_dgraph_t *dgraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t v5 = 0;

   dgraph = ii_dgraph_make();
   
   v1 = ii_dgraph_vertex_add( dgraph, 19 );
   v2 = ii_dgraph_vertex_add( dgraph, 23 );
   v3 = ii_dgraph_vertex_add( dgraph, 29 );
   v4 = ii_dgraph_vertex_add( dgraph, 31 );
   v5 = ii_dgraph_vertex_add( dgraph, 37 );
   
   CU_ASSERT( ii_dgraph_vertex_count( dgraph ) == 5 );
   
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v1 ) == 19 );
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v2 ) == 23 );
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v3 ) == 29 );
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v4 ) == 31 );
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v5 ) == 37 );
   
   ii_dgraph_vertex_value_put( dgraph, v1, 29 );
   ii_dgraph_vertex_value_put( dgraph, v2, 33 );
   ii_dgraph_vertex_value_put( dgraph, v3, 39 );
   ii_dgraph_vertex_value_put( dgraph, v4, 41 );
   ii_dgraph_vertex_value_put( dgraph, v5, 47 );
   
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v1 ) == 29 );
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v2 ) == 33 );
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v3 ) == 39 );
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v4 ) == 41 );
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v5 ) == 47 );
   
   ii_dgraph_dispose( &dgraph );

   return;
}

/**
   test_vertex_value_put_3
*/

void test_vertex_value_put_3( void )
{
   ii_dgraph_t *dgraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t v5 = 0;

   dgraph = ii_dgraph_make();
   
   v1 = ii_dgraph_vertex_add( dgraph, 19 );
   v2 = ii_dgraph_vertex_add( dgraph, 23 );
   v3 = ii_dgraph_vertex_add( dgraph, 29 );
   v4 = ii_dgraph_vertex_add( dgraph, 31 );
   
   ii_dgraph_vertex_remove( dgraph, v2 );
   
   v5 = ii_dgraph_vertex_add( dgraph, 37 );
   
   CU_ASSERT( ii_dgraph_vertex_count( dgraph ) == 4 );
   
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v1 ) == 19 );
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v3 ) == 29 );
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v4 ) == 31 );
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v5 ) == 37 );
   
   ii_dgraph_vertex_value_put( dgraph, v1, 39 );
   ii_dgraph_vertex_value_put( dgraph, v3, 43 );
   ii_dgraph_vertex_value_put( dgraph, v4, 49 );
   ii_dgraph_vertex_value_put( dgraph, v5, 51 );
   
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v1 ) == 39 );
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v3 ) == 43 );
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v4 ) == 49 );
   CU_ASSERT( ii_dgraph_vertex_value( dgraph, v5 ) == 51 );
   
   ii_dgraph_dispose( &dgraph );

   return;
}

int
add_test_vertex_value_put( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_vertex_value_put", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_vertex_value_put_1
   add_test_to_suite( p_suite, test_vertex_value_put_1, "test_vertex_value_put_1" );

   // test_vertex_value_put_2
   add_test_to_suite( p_suite, test_vertex_value_put_2, "test_vertex_value_put_2" );

   // test_vertex_value_put_3
   add_test_to_suite( p_suite, test_vertex_value_put_3, "test_vertex_value_put_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

