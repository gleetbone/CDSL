/**
 @file DGraph_test_cursor_make_depth.c
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
   test_cursor_make_depth_1
*/

void test_cursor_make_depth_1( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_cursor_t *cursor = NULL;

   dgraph = ii_dgraph_make_depth();
   cursor = ii_dgraph_cursor_make_depth( dgraph );

   CU_ASSERT( dgraph != NULL );
   CU_ASSERT( cursor != NULL );
   CU_ASSERT( ii_dgraph_count( dgraph ) == 0 );
   CU_ASSERT( ii_dgraph_is_empty( dgraph ) == 1 );
   CU_ASSERT( ii_dgraph_cursor_off( cursor ) == 1 );

   ii_dgraph_dispose( dgraph );

   return;
}

/**
   test_cursor_make_depth_2
*/

void test_cursor_make_depth_2( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_cursor_t *cursor = NULL;
   ii_dgraph_cursor_t *cursor1 = NULL;

   dgraph = ii_dgraph_make_depth();
   cursor = ii_dgraph_cursor_make_depth( dgraph );
   cursor1 = ii_dgraph_cursor_make_depth( dgraph );

   CU_ASSERT( dgraph != NULL );
   CU_ASSERT( cursor != NULL );
   CU_ASSERT( cursor1 != NULL );
   CU_ASSERT( ii_dgraph_count( dgraph ) == 0 );
   CU_ASSERT( ii_dgraph_is_empty( dgraph ) == 1 );
   CU_ASSERT( ii_dgraph_cursor_off( cursor ) == 1 );

   ii_dgraph_dispose( dgraph );

   return;
}

int
add_test_cursor_make_depth( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_make_depth", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_make_depth_1
   add_test_to_suite( p_suite, test_cursor_make_depth_1, "test_cursor_make_depth_1" );

   // test_cursor_make_depth_2
   add_test_to_suite( p_suite, test_cursor_make_depth_2, "test_cursor_make_depth_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

