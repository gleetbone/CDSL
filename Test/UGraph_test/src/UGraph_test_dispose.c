/**
 @file UGraph_test_dispose.c
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
   test_dispose_1
*/

void test_dispose_1( void )
{
   ii_ugraph_t *ugraph = NULL;

   ugraph = ii_ugraph_make();
   ii_ugraph_dispose( &ugraph );

   return;
}

/**
   test_dispose_2
*/

void test_dispose_2( void )
{
   ii_ugraph_t *ugraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t e = 0;

   ugraph = ii_ugraph_make();
   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   e = ii_ugraph_edge_add( ugraph, v1, v2, 29 );
   
   ii_ugraph_dispose( &ugraph );

   return;
}

/**
   test_dispose_3
*/

void test_dispose_3( void )
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
   
   ss_ugraph_dispose( &ugraph );

   string_dispose( &v1s );
   string_dispose( &v2s );
   string_dispose( &es );
   
   return;
}

int
add_test_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_dispose_1
   add_test_to_suite( p_suite, test_dispose_1, "test_dispose_1" );

   // test_dispose_2
   add_test_to_suite( p_suite, test_dispose_2, "test_dispose_2" );

   // test_dispose_3
   add_test_to_suite( p_suite, test_dispose_3, "test_dispose_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

