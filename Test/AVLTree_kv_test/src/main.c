/*
   Tests for AVLTree_kv
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
add_test_make_from_array( void );

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
add_test_dispose( void );

int
add_test_deep_dispose( void );

int
add_test_put( void );

int
add_test_count( void );

int
add_test_is_empty( void );

int
add_test_off( void );

int
add_test_is_first( void );

int
add_test_is_last( void );

int
add_test_has( void );

int
add_test_has_eq_fn( void );

int
add_test_has_value( void );

int
add_test_has_value_eq_fn( void );

int
add_test_remove( void );

int
add_test_remove_and_dispose( void );

int
add_test_remove_at( void );

int
add_test_remove_at_and_dispose( void );

int
add_test_remove_by_index( void );

int
add_test_remove_by_index_and_dispose( void );

int
add_test_remove_first( void );

int
add_test_remove_first_and_dispose( void );

int
add_test_remove_last( void );

int
add_test_remove_last_and_dispose( void );

int
add_test_remove_value( void );

int
add_test_remove_value_and_dispose( void );

int
add_test_height( void );

int
add_test_start( void );

int
add_test_finish( void );

int
add_test_forth( void );

int
add_test_back( void );

int
add_test_item_at( void );

int
add_test_key_at( void );

int
add_test_first( void );

int
add_test_last( void );

int
add_test_key_first( void );

int
add_test_key_last( void );

int
add_test_key_search_back( void );

int
add_test_key_search_back_eq_fn( void );

int
add_test_key_search_forth( void );

int
add_test_key_search_forth_eq_fn( void );

int
add_test_search_back( void );

int
add_test_search_back_eq_fn( void );

int
add_test_search_forth( void );

int
add_test_search_forth_eq_fn( void );

int
add_test_occurrences( void );

int
add_test_occurrences_eq_fn( void );

int
add_test_occurrences_value( void );

int
add_test_occurrences_value_eq_fn( void );

int
add_test_item( void );

int
add_test_key( void );

int
add_test_cursor_make( void );

int
add_test_cursor_dispose( void );

int
add_test_cursor_start( void );

int
add_test_cursor_finish( void );

int
add_test_cursor_forth( void );

int
add_test_cursor_back( void );

int
add_test_cursor_item_at( void );

int
add_test_cursor_key_at( void );

int
add_test_cursor_remove_at( void );

int
add_test_cursor_remove_at_and_dispose( void );

int
add_test_cursor_off( void );

int
add_test_cursor_is_first( void );

int
add_test_cursor_is_last( void );

int
add_test_go( void );

int
add_test_go_to_key( void );

int
add_test_index( void );

int
add_test_cursor_go( void );

int
add_test_cursor_go_to_key( void );

int
add_test_cursor_index( void );

int
add_test_cursor_search_back( void );

int
add_test_cursor_search_back_eq_fn( void );

int
add_test_cursor_search_forth( void );

int
add_test_cursor_search_forth_eq_fn( void );

int
add_test_cursor_key_search_back( void );

int
add_test_cursor_key_search_back_eq_fn( void );

int
add_test_cursor_key_search_forth( void );

int
add_test_cursor_key_search_forth_eq_fn( void );

int
add_test_wipe_out( void );

int
add_test_wipe_out_and_dispose( void );

int
add_test_values_as_array( void );

int
add_test_keys_as_array( void );

int
add_test_p_basic( void );

int
add_test_p_iterable_kv( void );

int
add_test_p_diterable_kv( void );


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
   add_test_make_from_array();
   add_test_clone();
   add_test_deep_clone();
   add_test_copy();
   add_test_deep_copy();
   add_test_is_equal();
   add_test_is_deep_equal();
   add_test_dispose();
   add_test_deep_dispose();
   add_test_put();
   add_test_count();
   add_test_is_empty();
   add_test_off();
   add_test_is_first();
   add_test_is_last();
   add_test_has();
   add_test_has_eq_fn();
   add_test_has_value();
   add_test_has_value_eq_fn();
   add_test_remove();
   add_test_remove_and_dispose();
   add_test_remove_at();
   add_test_remove_at_and_dispose();
   add_test_remove_by_index();
   add_test_remove_by_index_and_dispose();
   add_test_remove_first();
   add_test_remove_first_and_dispose();
   add_test_remove_last();
   add_test_remove_last_and_dispose();
   add_test_remove_value();
   add_test_remove_value_and_dispose();
   add_test_height();
   add_test_start();
   add_test_finish();
   add_test_forth();
   add_test_back();
   add_test_item_at();
   add_test_key_at();
   add_test_first();
   add_test_last();
   add_test_key_first();
   add_test_key_last();
   add_test_key_search_forth();
   add_test_key_search_forth_eq_fn();
   add_test_key_search_back();
   add_test_key_search_back_eq_fn();
   add_test_search_forth();
   add_test_search_forth_eq_fn();
   add_test_search_back();
   add_test_search_back_eq_fn();
   add_test_occurrences();
   add_test_occurrences_eq_fn();
   add_test_occurrences_value();
   add_test_occurrences_value_eq_fn();
   add_test_item();
   add_test_key();
   add_test_cursor_make();
   add_test_cursor_dispose();
   add_test_cursor_start();
   add_test_cursor_finish();
   add_test_cursor_forth();
   add_test_cursor_back();
   add_test_cursor_item_at();
   add_test_cursor_key_at();
   add_test_cursor_remove_at();
   add_test_cursor_remove_at_and_dispose();
   add_test_cursor_off();
   add_test_cursor_is_first();
   add_test_cursor_is_last();
   add_test_go();
   add_test_go_to_key();
   add_test_index();
   add_test_cursor_go();
   add_test_cursor_go_to_key();
   add_test_cursor_index();
   add_test_cursor_search_back();
   add_test_cursor_search_back_eq_fn();
   add_test_cursor_search_forth();
   add_test_cursor_search_forth_eq_fn();
   add_test_cursor_key_search_back();
   add_test_cursor_key_search_back_eq_fn();
   add_test_cursor_key_search_forth();
   add_test_cursor_key_search_forth_eq_fn();
   add_test_wipe_out();
   add_test_wipe_out_and_dispose();
   add_test_values_as_array();
   add_test_keys_as_array();

   add_test_p_basic();
   add_test_p_iterable_kv();
   add_test_p_diterable_kv();

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

