/*
   Tests for directed graphs
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
add_test_make_depth( void );

int
add_test_make_breadth( void );

int
add_test_cursor_make_depth( void );

int
add_test_cursor_make_breadth( void );

int
add_test_vertex_make( void );

int
add_test_dispose( void );

int
add_test_dispose_with_contents( void );

int
add_test_cursor_dispose( void );

int
add_test_vertex_dispose( void );

int
add_test_vertex_dispose_with_contents( void );

int
add_test_value( void );

int
add_test_edge_value_from_to( void );

int
add_test_edge_value( void );

int
add_test_edge_vertex_from( void );

int
add_test_edge_vertex_to( void );

int
add_test_cursor_value_at( void );

int
add_test_value_at( void );

int
add_test_cursor_at( void );

int
add_test_at( void );

int
add_test_as_array( void );

int
add_test_cursor_edge_value_at( void );

int
add_test_edge_value_at( void );

int
add_test_cursor_edge_at( void );

int
add_test_edge_at( void );

int
add_test_edge_from_to( void );

int
add_test_edges_as_array( void );

int
add_test_count( void );

int
add_test_edge_count( void );

int
add_test_are_adjacent( void );

int
add_test_off( void );

int
add_test_cursor_off( void );

int
add_test_is_empty( void );

int
add_test_edge_off( void );

int
add_test_cursor_edge_off( void );

int
add_test_edge_is_empty( void );

int
add_test_is_connected( void );

int
add_test_has( void );

int
add_test_edge_has( void );

int
add_test_has_value( void );

int
add_test_edge_has_value( void );

int
add_test_neighbors_from( void );

int
add_test_neighbors_to( void );

int
add_test_cursor_forth( void );

int
add_test_cursor_start( void );

int
add_test_forth( void );

int
add_test_start( void );

int
add_test_find_value( void );

int
add_test_find_next_value( void );

int
add_test_cursor_find_value( void );

int
add_test_cursor_find_next_value( void );

int
add_test_cursor_edge_forth( void );

int
add_test_cursor_edge_start( void );

int
add_test_edge_forth( void );

int
add_test_edge_start( void );

int
add_test_edge_find_value( void );

int
add_test_edge_find_next_value( void );

int
add_test_cursor_edge_find_value( void );

int
add_test_cursor_edge_find_next_value( void );

int
add_test_put( void );

int
add_test_edge_put( void );

int
add_test_set_value( void );

int
add_test_edge_set( void );

int
add_test_edge_set_value( void );

int
add_test_remove( void );

int
add_test_remove_and_dispose( void );

int
add_test_edge_remove_from_to( void );

int
add_test_edge_remove_and_dispose_from_to( void );

int
add_test_edge_remove( void );

int
add_test_edge_remove_and_dispose( void );

int
add_test_wipe_out( void );

int
add_test_wipe_out_and_dispose( void );

int
add_test_edge_wipe_out( void );

int
add_test_edge_wipe_out_and_dispose( void );

int
add_test_vertex_set_bucket_count( void );

int
add_test_edge_set_bucket_count( void );


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

   add_test_make_depth();
   add_test_make_breadth();
   add_test_cursor_make_depth();
   add_test_cursor_make_breadth();
   add_test_vertex_make();
   add_test_dispose();
   add_test_dispose_with_contents();
   add_test_cursor_dispose();
   add_test_vertex_dispose();
   add_test_vertex_dispose_with_contents();
   add_test_value();
   add_test_edge_value_from_to();
   add_test_edge_value();
   add_test_edge_vertex_from();
   add_test_edge_vertex_to();
   add_test_cursor_value_at();
   add_test_value_at();
   add_test_cursor_at();
   add_test_at();
   add_test_as_array();
   add_test_cursor_edge_value_at();
   add_test_edge_value_at();
   add_test_cursor_edge_at();
   add_test_edge_at();
   add_test_edge_from_to();
   add_test_edges_as_array();
   add_test_count();
   add_test_edge_count();
   add_test_are_adjacent();
   add_test_off();
   add_test_cursor_off();
   add_test_is_empty();
   add_test_edge_off();
   add_test_cursor_edge_off();
   add_test_edge_is_empty();
   add_test_is_connected();
   add_test_has();
   add_test_edge_has();
   add_test_has_value();
   add_test_edge_has_value();
   add_test_neighbors_from();
   add_test_neighbors_to();
   add_test_cursor_forth();
   add_test_cursor_start();
   add_test_forth();
   add_test_start();
   add_test_find_value();
   add_test_find_next_value();
   add_test_cursor_find_value();
   add_test_cursor_find_next_value();
   add_test_cursor_edge_forth();
   add_test_cursor_edge_start();
   add_test_edge_forth();
   add_test_edge_start();
   add_test_edge_find_value();
   add_test_edge_find_next_value();
   add_test_cursor_edge_find_value();
   add_test_cursor_edge_find_next_value();
   add_test_put();
   add_test_edge_put();
   add_test_set_value();
   add_test_edge_set();
   add_test_edge_set_value();
   add_test_remove();
   add_test_remove_and_dispose();
   add_test_edge_remove_from_to();
   add_test_edge_remove_and_dispose_from_to();
   add_test_edge_remove();
   add_test_edge_remove_and_dispose();
   add_test_wipe_out();
   add_test_wipe_out_and_dispose();
   add_test_edge_wipe_out();
   add_test_edge_wipe_out_and_dispose();
   add_test_vertex_set_bucket_count();
   add_test_edge_set_bucket_count();


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

