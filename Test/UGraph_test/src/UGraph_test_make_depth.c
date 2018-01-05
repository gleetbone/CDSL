/**
 @file UGraph_test_make_depth.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for UGraph_make_Depth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for UGraph_make_depth.

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
   test_make_depth_1
*/

void test_make_depth_1( void )
{
   ii_ugraph_t *ugraph = NULL;

   ugraph = ii_ugraph_make_depth();

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( ii_ugraph_count( ugraph ) == 0 );
   CU_ASSERT( ii_ugraph_is_empty( ugraph ) == 1 );

   ii_ugraph_dispose( ugraph );

   return;
}

int
add_test_make_depth( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_depth", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_depth_1
   add_test_to_suite( p_suite, test_make_depth_1, "test_make_depth_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

