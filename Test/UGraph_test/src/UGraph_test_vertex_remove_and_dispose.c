/**
 @file UGraph_test_vertex_remove_and_dispose.c
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
#include "ss_UGraph.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_vertex_remove_and_dispose_1
*/

void test_vertex_remove_and_dispose_1( void )
{
   ii_ugraph_t *ugraph = NULL;
   int32_t v = 0;

   ugraph = ii_ugraph_make();
   
   v = ii_ugraph_vertex_add( ugraph, 19 );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 1 );
   
   ii_ugraph_vertex_remove_and_dispose( ugraph, v );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 0 );
   
   ii_ugraph_dispose( &ugraph );

   return;
}

/**
   test_vertex_remove_and_dispose_2
*/

void test_vertex_remove_and_dispose_2( void )
{
   ii_ugraph_t *ugraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t v5 = 0;

   ugraph = ii_ugraph_make();
   
   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   v3 = ii_ugraph_vertex_add( ugraph, 29 );
   v4 = ii_ugraph_vertex_add( ugraph, 31 );
   v5 = ii_ugraph_vertex_add( ugraph, 37 );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 5 );
   
   ii_ugraph_vertex_remove_and_dispose( ugraph, v1 );
   ii_ugraph_vertex_remove_and_dispose( ugraph, v2 );
   ii_ugraph_vertex_remove_and_dispose( ugraph, v3 );
   ii_ugraph_vertex_remove_and_dispose( ugraph, v4 );
   ii_ugraph_vertex_remove_and_dispose( ugraph, v5 );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 0 );
   
   ii_ugraph_dispose( &ugraph );

   return;
}

/**
   test_vertex_remove_and_dispose_3
*/

void test_vertex_remove_and_dispose_3( void )
{
   ii_ugraph_t *ugraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t v5 = 0;

   ugraph = ii_ugraph_make();
   
   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   v3 = ii_ugraph_vertex_add( ugraph, 29 );
   v4 = ii_ugraph_vertex_add( ugraph, 31 );
   
   ii_ugraph_vertex_remove_and_dispose( ugraph, v2 );
   
   v5 = ii_ugraph_vertex_add( ugraph, 37 );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 4 );
   
   ii_ugraph_vertex_remove_and_dispose( ugraph, v1 );
   ii_ugraph_vertex_remove_and_dispose( ugraph, v3 );
   ii_ugraph_vertex_remove_and_dispose( ugraph, v4 );
   ii_ugraph_vertex_remove_and_dispose( ugraph, v5 );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 0 );
   
   ii_ugraph_dispose( &ugraph );

   return;
}

/**
   test_vertex_remove_and_dispose_4
*/

void test_vertex_remove_and_dispose_4( void )
{
   ss_ugraph_t *ugraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t e = 0;
   string_t *v1s = NULL;
   string_t *v2s = NULL;
   string_t *es = NULL;
   
   ugraph = ss_ugraph_make();
   
   v1s = string_make_from_cstring( "19" );
   v1 = ss_ugraph_vertex_add( ugraph, v1s );
   
   v2s = string_make_from_cstring( "23" );
   v2 = ss_ugraph_vertex_add( ugraph, v2s );
   
   CU_ASSERT( ss_ugraph_vertex_count( ugraph ) == 2 );
   
   es = string_make_from_cstring( "29" );
   e = ss_ugraph_edge_add( ugraph, v1, v2, es );
   
   ss_ugraph_vertex_remove_and_dispose( ugraph, v1 );
   
   CU_ASSERT( ss_ugraph_vertex_count( ugraph ) == 1 );
   
   ss_ugraph_dispose( &ugraph );

   string_dispose( &v2s );
   
   return;
}

int
add_test_vertex_remove_and_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_vertex_remove_and_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_vertex_remove_and_dispose_1
   add_test_to_suite( p_suite, test_vertex_remove_and_dispose_1, "test_vertex_remove_and_dispose_1" );

   // test_vertex_remove_and_dispose_2
   add_test_to_suite( p_suite, test_vertex_remove_and_dispose_2, "test_vertex_remove_and_dispose_2" );

   // test_vertex_remove_and_dispose_3
   add_test_to_suite( p_suite, test_vertex_remove_and_dispose_3, "test_vertex_remove_and_dispose_3" );

   // test_vertex_remove_and_dispose_4
   add_test_to_suite( p_suite, test_vertex_remove_and_dispose_4, "test_vertex_remove_and_dispose_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

