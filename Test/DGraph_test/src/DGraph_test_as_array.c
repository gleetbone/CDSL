/**
 @file DGraph_test_as_array.c
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
   test_as_array_1
*/

void test_as_array_1( void )
{
   ii_dgraph_t *dgraph = NULL;
   ii_dgraph_vertex_t *vertex = NULL;
   ii_dgraph_vertex_t **a = NULL;

   dgraph = ii_dgraph_make_depth();
   vertex = ii_dgraph_vertex_make( 13 );
   ii_dgraph_put( dgraph, vertex );

   a = ii_dgraph_as_array( dgraph );

   CU_ASSERT( dgraph != NULL );
   CU_ASSERT( vertex != NULL );
   CU_ASSERT( a != NULL );
   CU_ASSERT( a[0] == vertex );
   CU_ASSERT( a[1] == NULL );

   CU_ASSERT( ii_dgraph_count( dgraph ) == 1 );

   free( a );

   ii_dgraph_dispose( dgraph );

   return;
}

int
add_test_as_array( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_as_array", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_as_array_1
   add_test_to_suite( p_suite, test_as_array_1, "test_as_array_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

