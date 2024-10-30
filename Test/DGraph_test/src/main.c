/*
   Tests for DGraph
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#ifdef __cplusplus
extern "C" {
#endif

// test suite declarations

int
add_test_make( void );

int
add_test_dispose( void );

int
add_test_deep_dispose( void );

int
add_test_vertex_add( void );

int
add_test_vertex_remove( void );

int
add_test_vertex_remove_and_dispose( void );

int
add_test_edge_add( void );

int
add_test_edge_remove( void );

int
add_test_edge_remove_and_dispose( void );

int
add_test_wipe_out( void );

int
add_test_wipe_out_and_dispose( void );

int
add_test_wipe_out_edges( void );

int
add_test_wipe_out_edges_and_dispose( void );

int
add_test_vertex_value( void );

int
add_test_vertex_value_put( void );

int
add_test_edge_value( void );

int
add_test_edge_value_put( void );

int
add_test_vertex_neighbors_from( void );

int
add_test_vertex_neighbors_to( void );

int
add_test_edge_vertex_from( void );

int
add_test_edge_for_from_to( void );

int
add_test_vertex_count( void );

int
add_test_edge_count( void );

int
add_test_clone( void );

int
add_test_deep_clone( void );

int
add_test_copy( void );

int
add_test_deep_copy( void );

int
add_test_is_equal( void );

int
add_test_is_deep_equal( void );

int
add_test_vertex_start( void );

int
add_test_vertex_forth( void );

int
add_test_vertex_off( void );

int
add_test_vertex_id_at( void );

int
add_test_edge_start( void );

int
add_test_edge_forth( void );

int
add_test_edge_off( void );

int
add_test_edge_id_at( void );

int
add_test_edge_vertex_to( void );

int
add_test_edge_vertex_from( void );

int
add_test_make_cursor( void );

int
add_test_cursor_dispose( void );

int
add_test_cursor_vertex_start( void );

int
add_test_cursor_vertex_forth( void );

int
add_test_cursor_vertex_off( void );

int
add_test_cursor_vertex_id_at( void );

int
add_test_cursor_edge_start( void );

int
add_test_cursor_edge_forth( void );

int
add_test_cursor_edge_off( void );

int
add_test_cursor_edge_id_at( void );

int
add_test_connected_vertices_breadth_first( void );

int
add_test_connected_vertices_depth_first( void );

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name )
{
   // add the test to the suite

   // test_make_1
   CU_pTest p_test = CU_add_test( p_suite, name, test );

   if ( p_test == NULL )
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   return CUE_SUCCESS;
}

/**
   main() function for setting up and running the tests.

   Returns a CUE_SUCCESS on successful running, another
   CUnit error code on failure.

*/

int main()
{
   CU_ErrorCode result;

   // initialize the CUnit test registry
   result = CU_initialize_registry();
   if ( result != CUE_SUCCESS )
   {
      return CU_get_error();
   }

   // add tests for DList_make

   add_test_make();
   add_test_dispose();
   add_test_deep_dispose();
   add_test_vertex_add();
   add_test_vertex_remove();
   add_test_vertex_remove_and_dispose();
   add_test_edge_add();
   add_test_edge_remove();
   add_test_edge_remove_and_dispose();
   add_test_wipe_out();
   add_test_wipe_out_and_dispose();
   add_test_wipe_out_edges();
   add_test_wipe_out_edges_and_dispose();
   add_test_vertex_value();
   add_test_vertex_value_put();
   add_test_edge_value();
   add_test_edge_value_put();
   add_test_vertex_neighbors_from();
   add_test_vertex_neighbors_to();
   add_test_edge_vertex_from();
   add_test_edge_for_from_to();
   add_test_vertex_count();
   add_test_edge_count();
   add_test_clone();
   add_test_deep_clone();
   add_test_copy();
   add_test_deep_copy();
   add_test_is_equal();
   add_test_is_deep_equal();
   add_test_vertex_start();
   add_test_vertex_forth();
   add_test_vertex_off();
   add_test_vertex_id_at();
   add_test_edge_start();
   add_test_edge_forth();
   add_test_edge_off();
   add_test_edge_id_at();
   add_test_edge_vertex_to();
   add_test_edge_vertex_from();
   add_test_make_cursor();
   add_test_cursor_dispose();
   add_test_cursor_vertex_start();
   add_test_cursor_vertex_forth();
   add_test_cursor_vertex_off();
   add_test_cursor_vertex_id_at();
   add_test_cursor_edge_start();
   add_test_cursor_edge_forth();
   add_test_cursor_edge_off();
   add_test_cursor_edge_id_at();
   add_test_connected_vertices_breadth_first();
   add_test_connected_vertices_depth_first();

   // Run all tests using the CUnit Basic interface

   // set the test mode to verbose
   CU_basic_set_mode(CU_BRM_VERBOSE);

   // run the tests
   CU_basic_run_tests();

   // do any cleanup
   CU_cleanup_registry();

   // exit with error code
   return CU_get_error();
}

#ifdef __cplusplus
}
#endif

/* End of file */

