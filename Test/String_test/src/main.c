/*
   Tests for String
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
add_test_make_n( void );

int
add_test_make_from( void );

int
add_test_make_from_cstring( void );

int
add_test_dispose( void );

int
add_test_dispose_with_contents( void );

int
add_test_item( void );

int
add_test_as_cstring( void );

int
add_test_count( void );

int
add_test_capacity( void );

int
add_test_is_empty( void );

int
add_test_has( void );

int
add_test_is_int32( void );

int
add_test_is_float64( void );

int
add_test_hash_code( void );

int
add_test_is_equal( void );

int
add_test_is_equal_cstring( void );

int
add_test_is_less_than( void );

int
add_test_is_less_than_cstring( void );

int
add_test_is_greater_than( void );

int
add_test_is_greater_than_cstring( void );

int
add_test_has_substring( void );

int
add_test_has_substring_cstring( void );

int
add_test_starts_with( void );

int
add_test_starts_with_cstring( void );

int
add_test_ends_with( void );

int
add_test_ends_with_cstring( void );

int
add_test_substring_index_in_bounds( void );

int
add_test_substring_index_in_bounds_cstring( void );

int
add_test_substring_index( void );

int
add_test_substring_index_cstring( void );

int
add_test_split( void );

int
add_test_split_cstring( void );

int
add_test_as_lower( void );

int
add_test_as_upper( void );

int
add_test_as_int32( void );

int
add_test_as_float64( void );

int
add_test_put( void );

int
add_test_replace( void );

int
add_test_replace_cstring( void );

int
add_test_replace_all( void );

int
add_test_replace_all_cstring( void );

int
add_test_replace_all_cstring2( void );

int
add_test_append( void );

int
add_test_append_cstring( void );

int
add_test_prepend( void );

int
add_test_prepend_cstring( void );

int
add_test_insert( void );

int
add_test_insert_cstring( void );

int
add_test_append_character( void );

int
add_test_prepend_character( void );

int
add_test_insert_character( void );

int
add_test_insert_int32( void );

int
add_test_insert_float64( void );

int
add_test_to_lower( void );

int
add_test_to_upper( void );

int
add_test_substring( void );

int
add_test_copy( void );

int
add_test_remove( void );

int
add_test_remove_substring( void );

int
add_test_keep_head( void );

int
add_test_keep_tail( void );

int
add_test_remove_head( void );

int
add_test_remove_tail( void );

int
add_test_wipe_out( void );

int
add_test_valid_index( void );

int
add_test_resize( void );

int
add_test_from_file( void );

int
add_test_from_file_cstring( void );

int
add_test_to_file( void );

int
add_test_to_file_cstring( void );

int
add_test_cstring_to_file_cstring( void );

int
add_test_append_indent( void );

int
add_test_append_newline( void );

int
add_test_hex_to_uint8( void );

int
add_test_cstring_hex_to_uint8( void );

int
add_test_hex_from_uint8( void );

int
add_test_hex_from_int32( void );

int
add_test_cstring_hex_from_uint8( void );

int
add_test_cstring_hex_from_int32( void );

int
add_test_cstring_hex_from_int32( void );

int
add_test_current_time( void );

int
add_test_extras( void );


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
   add_test_make_n();
   add_test_make_from();
   add_test_make_from_cstring();
   add_test_dispose();
   add_test_dispose_with_contents();
   add_test_item();
   add_test_as_cstring();
   add_test_count();
   add_test_capacity();
   add_test_is_empty();
   add_test_has();
   add_test_is_int32();
   add_test_is_float64();
   add_test_hash_code();
   add_test_is_equal();
   add_test_is_equal_cstring();
   add_test_is_less_than();
   add_test_is_less_than_cstring();
   add_test_is_greater_than();
   add_test_is_greater_than_cstring();
   add_test_has_substring();
   add_test_has_substring_cstring();
   add_test_starts_with();
   add_test_starts_with_cstring();
   add_test_ends_with();
   add_test_ends_with_cstring();
   add_test_substring_index_in_bounds();
   add_test_substring_index_in_bounds_cstring();
   add_test_substring_index();
   add_test_substring_index_cstring();
   add_test_split();
   add_test_split_cstring();
   add_test_as_lower();
   add_test_as_upper();
   add_test_as_int32();
   add_test_as_float64();
   add_test_put();
   add_test_replace();
   add_test_replace_cstring();
   add_test_replace_all();
   add_test_replace_all_cstring();
   add_test_replace_all_cstring2();
   add_test_append();
   add_test_append_cstring();
   add_test_prepend();
   add_test_prepend_cstring();
   add_test_insert();
   add_test_insert_cstring();
   add_test_append_character();
   add_test_prepend_character();
   add_test_insert_character();
   add_test_insert_int32();
   add_test_insert_float64();
   add_test_to_lower();
   add_test_to_upper();
   add_test_substring();
   add_test_copy();
   add_test_remove();
   add_test_remove_substring();
   add_test_keep_head();
   add_test_keep_tail();
   add_test_remove_head();
   add_test_remove_tail();
   add_test_wipe_out();
   add_test_valid_index();
   add_test_resize();
   add_test_from_file();
   add_test_from_file_cstring();
   add_test_to_file();
   add_test_to_file_cstring();
   add_test_cstring_to_file_cstring();
   add_test_append_indent();
   add_test_append_newline();
   add_test_hex_to_uint8();
   add_test_cstring_hex_to_uint8();
   add_test_hex_from_uint8();
   add_test_cstring_hex_from_uint8();
   add_test_hex_from_int32();
   add_test_cstring_hex_from_int32();
   add_test_current_time();
   add_test_extras();


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

