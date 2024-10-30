/**
 @file UGraph_test_edge_remove.c
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
   test_edge_remove_1
*/

void test_edge_remove_1( void )
{
   ii_ugraph_t *ugraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t e = 0;

   ugraph = ii_ugraph_make();
   
   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   
   e = ii_ugraph_edge_add( ugraph, v1, v2, 29 );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 2 );
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 1 );
   
   ii_ugraph_edge_remove( ugraph, e );
   
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 0 );
   
   ii_ugraph_dispose( &ugraph );

   return;
}

/**
   test_edge_remove_2
*/

void test_edge_remove_2( void )
{
   ii_ugraph_t *ugraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t v5 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;
   int32_t e3 = 0;
   int32_t e4 = 0;

   ugraph = ii_ugraph_make();
   
   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   v3 = ii_ugraph_vertex_add( ugraph, 29 );
   v4 = ii_ugraph_vertex_add( ugraph, 31 );
   v5 = ii_ugraph_vertex_add( ugraph, 37 );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 5 );
   
   e1 = ii_ugraph_edge_add( ugraph, v1, v2, 2 );
   e2 = ii_ugraph_edge_add( ugraph, v2, v3, 3 );
   e3 = ii_ugraph_edge_add( ugraph, v3, v4, 5 );
   e4 = ii_ugraph_edge_add( ugraph, v4, v5, 7 );
   
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 4 );
   
   ii_ugraph_edge_remove( ugraph, e1 );
   ii_ugraph_edge_remove( ugraph, e2 );
   ii_ugraph_edge_remove( ugraph, e3 );
   ii_ugraph_edge_remove( ugraph, e4 );
   
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 0 );
   
   ii_ugraph_dispose( &ugraph );

   return;
}

/**
   test_edge_remove_3
*/

void test_edge_remove_3( void )
{
   ii_ugraph_t *ugraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t v3 = 0;
   int32_t v4 = 0;
   int32_t v5 = 0;
   int32_t e1 = 0;
   int32_t e2 = 0;
   int32_t e3 = 0;

   ugraph = ii_ugraph_make();
   
   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   v3 = ii_ugraph_vertex_add( ugraph, 29 );
   v4 = ii_ugraph_vertex_add( ugraph, 31 );
   
   ii_ugraph_vertex_remove( ugraph, v2 );
   
   v5 = ii_ugraph_vertex_add( ugraph, 37 );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 4 );
   
   e1 = ii_ugraph_edge_add( ugraph, v1, v3, 2 );
   e2 = ii_ugraph_edge_add( ugraph, v3, v4, 3 );
   e3 = ii_ugraph_edge_add( ugraph, v4, v5, 5 );
   
   ii_ugraph_edge_remove( ugraph, e2 );
   ii_ugraph_edge_remove( ugraph, e1 );
   ii_ugraph_edge_remove( ugraph, e3 );
   
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 0 );
   
   ii_ugraph_dispose( &ugraph );

   return;
}

/**
   test_edge_remove_4
*/

void test_edge_remove_4( void )
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
   
   es = string_make_from_cstring( "29" );
   e = ss_ugraph_edge_add( ugraph, v1, v2, es );
   
   CU_ASSERT( ss_ugraph_vertex_count( ugraph ) == 2 );
   CU_ASSERT( ss_ugraph_edge_count( ugraph ) == 1 );
   
   ss_ugraph_edge_remove( ugraph, e );
   
   CU_ASSERT( ss_ugraph_edge_count( ugraph ) == 0 );
   
   ss_ugraph_dispose( &ugraph );

   string_dispose( &v1s );
   string_dispose( &v2s );
   string_dispose( &es );
   
   return;
}

int
add_test_edge_remove( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_edge_remove", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_edge_remove_1
   add_test_to_suite( p_suite, test_edge_remove_1, "test_edge_remove_1" );

   // test_edge_remove_2
   add_test_to_suite( p_suite, test_edge_remove_2, "test_edge_remove_2" );

   // test_edge_remove_3
   add_test_to_suite( p_suite, test_edge_remove_3, "test_edge_remove_3" );

   // test_edge_remove_4
   add_test_to_suite( p_suite, test_edge_remove_4, "test_edge_remove_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

