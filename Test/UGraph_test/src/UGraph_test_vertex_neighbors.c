/**
 @file UGraph_test_vertex_neighbors.c
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

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

static
int32_t
is_index_in_array
(
   int32_t *ip,
   int32_t count,
   int32_t index
)
{
   int32_t result = 0;
   int32_t i = 0;
   
   for( i=0; ( i<count ) && ( result == 0 ); i++ )
   {
      if ( ip[i] == index )
      {
         result = 1;
      }
   }
   
   return result;
}


/**
   test_vertex_neighbors_1
*/

void test_vertex_neighbors_1( void )
{
   ii_ugraph_t *ugraph = NULL;
   int32_t v1 = 0;
   int32_t v2 = 0;
   int32_t e = 0;
   int32_t count = 0;
   int32_t *ip = NULL;

   ugraph = ii_ugraph_make();
   
   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   
   e = ii_ugraph_edge_add( ugraph, v1, v2, 29 );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 2 );
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 1 );
   
   ip = ii_ugraph_vertex_neighbors( ugraph, v2, &count );
   
   CU_ASSERT( count == 1 );
   CU_ASSERT( is_index_in_array( ip, count, v1 ) == 1 );
   
   free( ip );
   
   ii_ugraph_dispose( &ugraph );

   return;
}

/**
   test_vertex_neighbors_2
*/

void test_vertex_neighbors_2( void )
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
   int32_t count = 0;
   int32_t *ip = NULL;

   ugraph = ii_ugraph_make();
   
   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   v3 = ii_ugraph_vertex_add( ugraph, 29 );
   v4 = ii_ugraph_vertex_add( ugraph, 31 );
   v5 = ii_ugraph_vertex_add( ugraph, 37 );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 5 );
   
   e1 = ii_ugraph_edge_add( ugraph, v1, v5, 2 );
   e2 = ii_ugraph_edge_add( ugraph, v2, v5, 3 );
   e3 = ii_ugraph_edge_add( ugraph, v3, v5, 5 );
   e4 = ii_ugraph_edge_add( ugraph, v4, v5, 7 );
   
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 4 );
  
   ip = ii_ugraph_vertex_neighbors( ugraph, v5, &count );
   
   CU_ASSERT( count == 4 );
   
   CU_ASSERT( is_index_in_array( ip, count, v1 ) == 1 );
   CU_ASSERT( is_index_in_array( ip, count, v2 ) == 1 );
   CU_ASSERT( is_index_in_array( ip, count, v3 ) == 1 );
   CU_ASSERT( is_index_in_array( ip, count, v4 ) == 1 );
   
   free( ip );
   
   ii_ugraph_dispose( &ugraph );

   return;
}

/**
   test_vertex_neighbors_3
*/

void test_vertex_neighbors_3( void )
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
   int32_t count = 0;
   int32_t *ip = NULL;

   ugraph = ii_ugraph_make();
   
   v1 = ii_ugraph_vertex_add( ugraph, 19 );
   v2 = ii_ugraph_vertex_add( ugraph, 23 );
   v3 = ii_ugraph_vertex_add( ugraph, 29 );
   v4 = ii_ugraph_vertex_add( ugraph, 31 );
   
   ii_ugraph_vertex_remove( ugraph, v2 );
   
   v5 = ii_ugraph_vertex_add( ugraph, 37 );
   
   CU_ASSERT( ii_ugraph_vertex_count( ugraph ) == 4 );
   
   e1 = ii_ugraph_edge_add( ugraph, v1, v5, 2 );
   e2 = ii_ugraph_edge_add( ugraph, v3, v5, 3 );
   e3 = ii_ugraph_edge_add( ugraph, v4, v5, 5 );
   
   CU_ASSERT( ii_ugraph_edge_count( ugraph ) == 3 );
   
   ip = ii_ugraph_vertex_neighbors( ugraph, v5, &count );
   
   CU_ASSERT( count == 3 );
   
   CU_ASSERT( is_index_in_array( ip, count, v1 ) == 1 );
   CU_ASSERT( is_index_in_array( ip, count, v3 ) == 1 );
   CU_ASSERT( is_index_in_array( ip, count, v4 ) == 1 );
   
   free( ip );
   
   ii_ugraph_dispose( &ugraph );

   return;
}

int
add_test_vertex_neighbors( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_vertex_neighbors", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_vertex_neighbors_1
   add_test_to_suite( p_suite, test_vertex_neighbors_1, "test_vertex_neighbors_1" );

   // test_vertex_neighbors_2
   add_test_to_suite( p_suite, test_vertex_neighbors_2, "test_vertex_neighbors_2" );

   // test_vertex_neighbors_3
   add_test_to_suite( p_suite, test_vertex_neighbors_3, "test_vertex_neighbors_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */
