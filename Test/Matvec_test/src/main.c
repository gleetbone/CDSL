/*
   Tests for matvec
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
add_test_make_row_vector( void );

int
add_test_make_column_vector( void );

int
add_test_make_from( void );

int
add_test_make_from_args( void );

int
add_test_dispose( void );

int
add_test_deep_dispose( void );

int
add_test_rows( void );

int
add_test_columns( void );

int
add_test_vector_length( void );

int
add_test_is_column_vector( void );

int
add_test_is_row_vector( void );

int
add_test_item( void );

int
add_test_vector_item( void );

int
add_test_vector_x( void );

int
add_test_vector_y( void );

int
add_test_vector_z( void );

int
add_test_vector_magnitude( void );

int
add_test_vector_squared_magnitude( void );

int
add_test_max_item_magnitude( void );

int
add_test_is_symmetric( void );

int
add_test_is_hermitian_symmetric( void );

int
add_test_is_approximately_symmetric( void );

int
add_test_is_approximately_hermitian_symmetric( void );

int
add_test_is_equal( void );

int
add_test_is_approximately_equal( void );

int
add_test_put( void );

int
add_test_put_and_dispose( void );

int
add_test_vector_put( void );

int
add_test_vector_put_and_dispose( void );

int
add_test_vector_put_x( void );

int
add_test_vector_put_x_and_dispose( void );

int
add_test_vector_put_y( void );

int
add_test_vector_put_y_and_dispose( void );

int
add_test_vector_put_z( void );

int
add_test_vector_put_z_and_dispose( void );

int
add_test_set_from( void );

int
add_test_set_from_and_dispose( void );

int
add_test_do_and_set_all( void );

int
add_test_do_and_set_all_and_dispose( void );

int
add_test_do_and_set_if( void );

int
add_test_do_and_set_if_and_dispose( void );

int
add_test_one( void );

int
add_test_zero( void );

int
add_test_set_to_one( void );

int
add_test_set_to_one_and_dispose( void );

int
add_test_set_to_zero( void );

int
add_test_set_to_zero_and_dispose( void );

int
add_test_copied( void );

int
add_test_subcopied( void );

int
add_test_subcopy( void );

int
add_test_subcopy_and_dispose( void );

int
add_test_as_array( void );

int
add_test_copy_as_array( void );

int
add_test_vector_from_row( void );

int
add_test_vector_from_column( void );

int
add_test_row_vector_dot( void );

int
add_test_row_vector_squared_magnitude( void );

int
add_test_row_vector_scale( void );

int
add_test_column_vector_dot( void );

int
add_test_column_vector_squared_magnitude( void );

int
add_test_trace( void );

int
add_test_column_vector_scale( void );

int
add_test_add( void );

int
add_test_added( void );

int
add_test_subtract( void );

int
add_test_subtracted( void );

int
add_test_multiply( void );

int
add_test_multiplied( void );

int
add_test_vector_normalize( void );

int
add_test_vector_normalized( void );

int
add_test_vector_dot( void );

int
add_test_vector_cross( void );

int
add_test_vector_crossed( void );

int
add_test_item_by_item_multiply( void );

int
add_test_item_by_item_multiplied( void );

int
add_test_scale( void );

int
add_test_scaled( void );

int
add_test_negate( void );

int
add_test_negated( void );

int
add_test_transpose( void );

int
add_test_transposed( void );

int
add_test_hermitian_transpose( void );

int
add_test_hermitian_transposed( void );

int
add_test_hermitian_transposed( void );

int
add_test_conjugate( void );

int
add_test_conjugated( void );

int
add_test_invert( void );

int
add_test_inverse( void );

int
add_test_determinant( void );

int
add_test_trace( void );



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
   add_test_make_row_vector();
   add_test_make_column_vector();
   add_test_make_from();
   add_test_make_from_args();
   add_test_dispose();
   add_test_deep_dispose();
   add_test_rows();
   add_test_columns();
   add_test_vector_length();
   add_test_is_column_vector();
   add_test_is_row_vector();
   add_test_item();
   add_test_vector_item();
   add_test_vector_x();
   add_test_vector_y();
   add_test_vector_z();
   add_test_vector_magnitude();
   add_test_vector_squared_magnitude();
   add_test_max_item_magnitude();
   add_test_is_symmetric();
   add_test_is_hermitian_symmetric();
   add_test_is_approximately_symmetric();
   add_test_is_approximately_hermitian_symmetric();
   add_test_is_equal();
   add_test_is_approximately_equal();
   add_test_put();
   add_test_put_and_dispose();
   add_test_vector_put();
   add_test_vector_put_and_dispose();
   add_test_vector_put_x();
   add_test_vector_put_x_and_dispose();
   add_test_vector_put_y();
   add_test_vector_put_y_and_dispose();
   add_test_vector_put_z();
   add_test_vector_put_z_and_dispose();
   add_test_set_from();
   add_test_set_from_and_dispose();
   add_test_do_and_set_all();
   add_test_do_and_set_all_and_dispose();
   add_test_do_and_set_if();
   add_test_do_and_set_if_and_dispose();
   add_test_one();
   add_test_zero();
   add_test_set_to_one();
   add_test_set_to_one_and_dispose();
   add_test_set_to_zero();
   add_test_set_to_zero_and_dispose();
   add_test_copied();
   add_test_subcopied();
   add_test_subcopy();
   add_test_subcopy_and_dispose();
   add_test_as_array();
   add_test_copy_as_array();
   add_test_vector_from_row();
   add_test_vector_from_column();
   add_test_row_vector_dot();
   add_test_row_vector_squared_magnitude();
   add_test_row_vector_scale();
   add_test_column_vector_dot();
   add_test_column_vector_squared_magnitude();
   add_test_column_vector_scale();
   add_test_add();
   add_test_added();
   add_test_subtract();
   add_test_subtracted();
   add_test_multiply();
   add_test_multiplied();
   add_test_vector_normalize();
   add_test_vector_normalized();
   add_test_vector_dot();
   add_test_vector_cross();
   add_test_vector_crossed();
   add_test_item_by_item_multiply();
   add_test_item_by_item_multiplied();
   add_test_scale();
   add_test_scaled();
   add_test_negate();
   add_test_negated();
   add_test_transpose();
   add_test_transposed();
   add_test_hermitian_transpose();
   add_test_hermitian_transposed();
   add_test_conjugate();
   add_test_conjugated();
   add_test_invert();
   add_test_inverse();
   add_test_determinant();
   add_test_trace();

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

