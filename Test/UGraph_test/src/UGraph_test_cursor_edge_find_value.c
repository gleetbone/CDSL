/**
 @file UGraph_test_cursor_edge_find_value.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for UGraph_make_Depth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for UGraph_cursor_make_depth.

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
   test_cursor_edge_find_value_1
*/

void test_cursor_edge_find_value_1( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_vertex_t *v1 = NULL;
   ii_ugraph_vertex_t *v2 = NULL;
   ii_ugraph_vertex_t *v3 = NULL;
   ii_ugraph_cursor_t *cursor = NULL;
   ii_ugraph_edge_t *edge = NULL;

   ugraph = ii_ugraph_make_depth();
   cursor = ii_ugraph_cursor_make_depth( ugraph );

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( cursor != NULL );

   v1 = ii_ugraph_vertex_make( 13 );
   ii_ugraph_put( ugraph, v1 );

   v2 = ii_ugraph_vertex_make( 14 );
   ii_ugraph_put( ugraph, v2 );

   v3 = ii_ugraph_vertex_make( 15 );
   ii_ugraph_put( ugraph, v3 );

   CU_ASSERT( v1 != NULL );
   CU_ASSERT( v2 != NULL );
   CU_ASSERT( v3 != NULL );

   ii_ugraph_edge_put( ugraph, 23, v1, v2 );
   ii_ugraph_edge_put( ugraph, 24, v2, v3 );

   edge = ii_ugraph_cursor_edge_find_value( cursor, 23 );
   CU_ASSERT( edge != NULL );

   edge = ii_ugraph_cursor_edge_find_value( cursor, 24 );
   CU_ASSERT( edge != NULL );

   edge = ii_ugraph_cursor_edge_find_value( cursor, 29 );
   CU_ASSERT( edge == NULL );

   ii_ugraph_dispose( ugraph );

   return;
}

int
add_test_cursor_edge_find_value( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_edge_find_value", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_edge_find_value_1
   add_test_to_suite( p_suite, test_cursor_edge_find_value_1, "test_cursor_edge_find_value_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

