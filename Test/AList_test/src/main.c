/*
   Tests for doubly linked list
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
add_test_make_from( void );

int
add_test_make_duplicate_from( void );

int
add_test_make_from_array( void );

int
add_test_cursor_make( void );

int
add_test_dispose( void );

int
add_test_dispose_with_contents( void );

int
add_test_cursor_dispose( void );

int
add_test_cursor_item_at( void );

int
add_test_item_at( void );

int
add_test_cursor_item_next( void );

int
add_test_item_next( void );

int
add_test_cursor_item_prev( void );

int
add_test_item_prev( void );

int
add_test_item( void );

int
add_test_first( void );

int
add_test_last( void );

int
add_test_as_array( void );

int
add_test_count( void );

int
add_test_off( void );

int
add_test_cursor_off( void );

int
add_test_is_empty( void );

int
add_test_is_first( void );

int
add_test_is_last( void );

int
add_test_index( void );

int
add_test_forth( void );

int
add_test_cursor_forth( void );

int
add_test_back( void );

int
add_test_cursor_back( void );

int
add_test_go( void );

int
add_test_cursor_go( void );

int
add_test_cursor_is_first( void );

int
add_test_cursor_is_last( void );

int
add_test_cursor_index( void );

int
add_test_start( void );

int
add_test_cursor_start( void );

int
add_test_finish( void );

int
add_test_cursor_finish( void );

int
add_test_put( void );

int
add_test_put_right( void );

int
add_test_cursor_put_right( void );

int
add_test_put_left( void );

int
add_test_cursor_put_left( void );

int
add_test_put_first( void );

int
add_test_put_last( void );

int
add_test_replace( void );

int
add_test_replace_and_dispose( void );

int
add_test_replace_at( void );

int
add_test_cursor_replace_at( void );

int
add_test_replace_at_and_dispose( void );

int
add_test_cursor_replace_at_and_dispose( void );

int
add_test_append( void );

int
add_test_append_right( void );

int
add_test_cursor_append_right( void );

int
add_test_append_left( void );

int
add_test_cursor_append_left( void );

int
add_test_append_first( void );

int
add_test_append_last( void );

int
add_test_remove( void );

int
add_test_remove_and_dispose( void );

int
add_test_remove_at( void );

int
add_test_remove_at_and_dispose( void );

int
add_test_cursor_remove_at( void );

int
add_test_cursor_remove_at_and_dispose( void );

int
add_test_remove_first( void );

int
add_test_remove_first_and_dispose( void );

int
add_test_remove_last( void );

int
add_test_remove_last_and_dispose( void );

int
add_test_prune( void );

int
add_test_prune_and_dispose( void );

int
add_test_prune_first( void );

int
add_test_prune_first_and_dispose( void );

int
add_test_prune_last( void );

int
add_test_prune_last_and_dispose( void );

int
add_test_keep_first( void );

int
add_test_keep_first_and_dispose( void );

int
add_test_keep_last( void );

int
add_test_keep_last_and_dispose( void );

int
add_test_wipe_out( void );

int
add_test_wipe_out_and_dispose( void );

int
add_test_sort( void );

int
add_test_p_clonable( void );

int
add_test_p_indexable( void );

int
add_test_p_iterable( void );

int
add_test_p_diterable( void );


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

   // add tests for AList_make

   add_test_make();
   add_test_make_from();
   add_test_make_duplicate_from();
   add_test_make_from_array();
   add_test_cursor_make();
   add_test_dispose();
   add_test_dispose_with_contents();
   add_test_cursor_dispose();
   add_test_cursor_item_at();
   add_test_item_at();
   add_test_cursor_item_next();
   add_test_item_next();
   add_test_cursor_item_prev();
   add_test_item_prev();
   add_test_item();
   add_test_first();
   add_test_last();
   add_test_as_array();
   add_test_count();
   add_test_off();
   add_test_cursor_off();
   add_test_is_empty();
   add_test_is_first();
   add_test_is_last();
   add_test_index();
   add_test_forth();
   add_test_cursor_forth();
   add_test_back();
   add_test_cursor_back();
   add_test_go();
   add_test_cursor_go();
   add_test_cursor_is_first();
   add_test_cursor_is_last();
   add_test_cursor_index();
   add_test_start();
   add_test_cursor_start();
   add_test_finish();
   add_test_cursor_finish();
   add_test_put();
   add_test_put_right();
   add_test_cursor_put_right();
   add_test_put_left();
   add_test_cursor_put_left();
   add_test_put_first();
   add_test_put_last();
   add_test_replace();
   add_test_replace_and_dispose();
   add_test_replace_at();
   add_test_cursor_replace_at();
   add_test_replace_at_and_dispose();
   add_test_cursor_replace_at_and_dispose();
   add_test_append();
   add_test_append_right();
   add_test_cursor_append_right();
   add_test_append_left();
   add_test_cursor_append_left();
   add_test_append_first();
   add_test_append_last();
   add_test_remove();
   add_test_remove_and_dispose();
   add_test_remove_at();
   add_test_remove_at_and_dispose();
   add_test_cursor_remove_at();
   add_test_cursor_remove_at_and_dispose();
   add_test_remove_first();
   add_test_remove_first_and_dispose();
   add_test_remove_last();
   add_test_remove_last_and_dispose();
   add_test_prune();
   add_test_prune_and_dispose();
   add_test_prune_first();
   add_test_prune_first_and_dispose();
   add_test_prune_last();
   add_test_prune_last_and_dispose();
   add_test_keep_first();
   add_test_keep_first_and_dispose();
   add_test_keep_last();
   add_test_keep_last_and_dispose();
   add_test_wipe_out();
   add_test_wipe_out_and_dispose();
   
   add_test_sort();
   add_test_p_clonable();
   add_test_p_indexable();
   add_test_p_iterable();
   add_test_p_diterable();


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

