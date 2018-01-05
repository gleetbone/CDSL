/**
 @file UGraph_test_forth.c
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
   test_forth_1
*/

void test_forth_1( void )
{
   ii_ugraph_t *ugraph = NULL;
   ii_ugraph_vertex_t *v1 = NULL;
   ii_ugraph_vertex_t *v2 = NULL;
   int32_t flag1 = 0;
   int32_t flag2 = 0;
   int32_t flag3 = 0;
   int32_t flag4 = 0;

   ugraph = ii_ugraph_make_depth();

   v1 = ii_ugraph_vertex_make( 1 );
   ii_ugraph_put( ugraph, v1 );
   v2 = ii_ugraph_vertex_make( 2 );
   ii_ugraph_put( ugraph, v2 );

   flag1 = ii_ugraph_off( ugraph );

   ii_ugraph_start( ugraph );
   flag2 = ii_ugraph_off( ugraph );

   ii_ugraph_forth( ugraph );
   flag3 = ii_ugraph_off( ugraph );

   ii_ugraph_forth( ugraph );
   flag4 = ii_ugraph_off( ugraph );

   CU_ASSERT( ugraph != NULL );
   CU_ASSERT( v1 != NULL );
   CU_ASSERT( v2 != NULL );
   CU_ASSERT( flag1 == 1 );
   CU_ASSERT( flag2 == 0 );
   CU_ASSERT( flag3 == 0 );
   CU_ASSERT( flag4 == 1 );

   ii_ugraph_dispose( ugraph );

   return;
}

int
add_test_forth( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_forth", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_forth_1
   add_test_to_suite( p_suite, test_forth_1, "test_forth_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

