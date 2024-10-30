/*
   Tests for Input_File_Reader
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
add_test_clone( void );

int
add_test_deep_clone( void );

int
add_test_is_equal( void );

int
add_test_is_deep_equal( void );

int
add_test_copy( void );

int
add_test_deep_copy( void );

int
add_test_make_cstring( void );

int
add_test_dispose( void );

int
add_test_deep_dispose( void );

int
add_test_empty( void );

int
add_test_tokens( void );

int
add_test_line( void );

int
add_test_line_number( void );

int
add_test_file_name( void );

int
add_test_eof( void );

int
add_test_is_skip_comments( void );

int
add_test_put_is_skip_comments( void );

int
add_test_forth( void );

int
add_test_one_line( void );

int
add_test_one_line_comment( void );

int
add_test_two_line( void );

int
add_test_three_line( void );

int
add_test_multiline( void );

int
add_test_quotes( void );


int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name )
{
   // add the test to the suite
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

   // add tests for Input_File_Reader

   add_test_make();
   add_test_make_cstring();
   add_test_clone();
   add_test_deep_clone();
   add_test_is_equal();
   add_test_is_deep_equal();
   add_test_copy();
   add_test_deep_copy();
   add_test_dispose();
   add_test_deep_dispose();
   add_test_tokens();
   add_test_line();
   add_test_line_number();
   add_test_file_name();
   add_test_eof();
   add_test_is_skip_comments();
   add_test_put_is_skip_comments();
   add_test_forth();
   add_test_empty();
   add_test_one_line();
   add_test_one_line_comment();
   add_test_two_line();
   add_test_three_line();
   add_test_multiline();
   add_test_quotes();

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

