/**
 @file DGraph_test_find_next_value.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for DGraph_make_Depth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for DGraph_cursor_make_depth.

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
   test_find_next_value_1
*/

void test_find_next_value_1( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_vertex_t *v1 = NULL;
   ii_dgraph_vertex_t *v2 = NULL;
   ii_dgraph_vertex_t *v3 = NULL;
   ii_dgraph_vertex_t *v = NULL;

   dgraph = ii_dgraph_make_depth();

   CU_ASSERT( dgraph != NULL );

   v1 = ii_dgraph_vertex_make( 13 );
   ii_dgraph_put( dgraph, v1 );

   v2 = ii_dgraph_vertex_make( 14 );
   ii_dgraph_put( dgraph, v2 );

   v3 = ii_dgraph_vertex_make( 13 );
   ii_dgraph_put( dgraph, v3 );

   CU_ASSERT( v1 != NULL );
   CU_ASSERT( v2 != NULL );
   CU_ASSERT( v3 != NULL );

   v = ii_dgraph_find_value( dgraph, 13 );
   CU_ASSERT( v != NULL );

   v = ii_dgraph_find_next_value( dgraph, 13 );
   CU_ASSERT( v != NULL );

   v = ii_dgraph_find_value( dgraph, 14 );
   CU_ASSERT( v != NULL );

   v = ii_dgraph_find_next_value( dgraph, 14 );
   CU_ASSERT( v == NULL );

   ii_dgraph_dispose( dgraph );

   return;
}

int
add_test_find_next_value( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_find_next_value", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_find_next_value_1
   add_test_to_suite( p_suite, test_find_next_value_1, "test_find_next_value_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

