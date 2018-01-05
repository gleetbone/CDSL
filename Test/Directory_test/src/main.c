/*
   Tests for Directory
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#ifdef __cplusplus
extern "C" {
#endif

// declarations

int
add_test_make( void );

int
add_test_make_cstring( void );

int
add_test_dispose( void );

int
add_test_name( void );

int
add_test_name_cstring( void );

int
add_test_last_entry( void );

int
add_test_last_entry_cstring( void );

int
add_test_filenames( void );

int
add_test_filenames_cstring( void );

int
add_test_filenames_count( void );

int
add_test_directories( void );

int
add_test_directories_cstring( void );

int
add_test_directories_count( void );

int
add_test_links( void );

int
add_test_links_cstring( void );

int
add_test_links_count( void );

int
add_test_is_closed( void );

int
add_test_is_open_read( void );

int
add_test_close( void );

int
add_test_end_of_input( void );

int
add_test_exists( void );

int
add_test_is_readable( void );

int
add_test_is_empty( void );

int
add_test_create( void );

int
add_test_create_mode( void );

int
add_test_recursive_create( void );

int
add_test_recursive_delete( void );

int
add_test_delete( void );

int
add_test_delete_files( void );

int
add_test_open_read( void );

int
add_test_read_next_entry( void );

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

int main(int argc, char *argv[] )
{
   CU_ErrorCode result;

   // initialize the CUnit test registry
   result = CU_initialize_registry();
   if ( result != CUE_SUCCESS )
   {
      return CU_get_error();
   }

   // add tests

   add_test_make();
   add_test_make_cstring();
   add_test_dispose();
   add_test_name();
   add_test_name_cstring();
   add_test_last_entry();
   add_test_last_entry_cstring();
   add_test_filenames();
   add_test_filenames_cstring();
   add_test_filenames_count();
   add_test_directories();
   add_test_directories_cstring();
   add_test_directories_count();
   add_test_links();
   add_test_links_cstring();
   add_test_links_count();
   add_test_is_closed();
   add_test_end_of_input();
   add_test_is_open_read();
   add_test_close();
   add_test_exists();
   add_test_is_readable();
   add_test_is_empty();
   add_test_create();
   add_test_create_mode();
   add_test_recursive_create();
   add_test_recursive_delete();
   add_test_delete();
   add_test_delete_files();
   add_test_open_read();
   add_test_read_next_entry();

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

