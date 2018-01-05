/**
 @file DGraph_test_is_empty.c
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
   test_is_empty_1
*/

void test_is_empty_1( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_vertex_t *vertex = NULL;
   int32_t flag1 = 0;
   int32_t flag2 = 0;

   dgraph = ii_dgraph_make_depth();
   vertex = ii_dgraph_vertex_make( 13 );

   flag1 = ii_dgraph_is_empty( dgraph );

   ii_dgraph_put( dgraph, vertex );

   flag2 = ii_dgraph_is_empty( dgraph );

   CU_ASSERT( dgraph != NULL );
   CU_ASSERT( vertex != NULL );
   CU_ASSERT( flag1 == 1 );
   CU_ASSERT( flag2 == 0 );

   ii_dgraph_dispose( dgraph );

   return;
}

int
add_test_is_empty( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_empty", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_empty_1
   add_test_to_suite( p_suite, test_is_empty_1, "test_is_empty_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

