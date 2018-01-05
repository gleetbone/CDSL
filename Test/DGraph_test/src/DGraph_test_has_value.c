/**
 @file DGraph_test_has_value.c
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
   test_has_value_1
*/

void test_has_value_1( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_vertex_t *v_from = NULL;
   ii_dgraph_vertex_t *v_to = NULL;
   int32_t flag1 = 0;
   int32_t flag2 = 0;
   int32_t flag3 = 0;

   dgraph = ii_dgraph_make_depth();
   v_from = ii_dgraph_vertex_make( 13 );
   ii_dgraph_put( dgraph, v_from );
   v_to = ii_dgraph_vertex_make( 14 );
   ii_dgraph_put( dgraph, v_to );

   flag1 = ii_dgraph_has_value( dgraph, 13 );
   flag2 = ii_dgraph_has_value( dgraph, 14 );
   flag3 = ii_dgraph_has_value( dgraph, 23 );

   CU_ASSERT( dgraph != NULL );
   CU_ASSERT( v_from != NULL );
   CU_ASSERT( v_to != NULL );
   CU_ASSERT( flag1 == 1 );
   CU_ASSERT( flag2 == 1 );
   CU_ASSERT( flag3 == 0 );

   ii_dgraph_dispose( dgraph );

   return;
}

int
add_test_has_value( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_has_value", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_has_value_1
   add_test_to_suite( p_suite, test_has_value_1, "test_has_value_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

