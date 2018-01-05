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
add_test_make_default( void );

int
add_test_make_from( void );

int
add_test_make_from_array( void );

int
add_test_make_from_vector( void );

int
add_test_make_from_rotation_about_vector( void );

int
add_test_make_from_rotation_degrees_about_vector( void );

int
add_test_make_from_rotation_about_xyz( void );

int
add_test_make_from_rotation_degrees_about_xyz( void );

int
add_test_make_from_roll_pitch_yaw( void );

int
add_test_make_from_roll_pitch_yaw_degrees( void );

int
add_test_make_from_roll( void );

int
add_test_make_from_roll_degrees( void );

int
add_test_make_from_pitch( void );

int
add_test_make_from_pitch_degrees( void );

int
add_test_make_from_yaw( void );

int
add_test_make_from_yaw_degrees( void );

int
add_test_dispose( void );

int
add_test_as_array( void );

int
add_test_as_vector( void );

int
add_test_qn( void );

int
add_test_magnitude( void );

int
add_test_squared_magnitude( void );

int
add_test_is_equal( void );

int
add_test_is_approximately_equal( void );

int
add_test_set( void );

int
add_test_set_qn( void );

int
add_test_set_from( void );

int
add_test_set_from_array( void );

int
add_test_set_from_vector( void );

int
add_test_set_from_rotation_about_vector( void );

int
add_test_set_from_rotation_degrees_about_vector( void );

int
add_test_set_from_rotation_about_xyz( void );

int
add_test_set_from_rotation_degrees_about_xyz( void );

int
add_test_set_from_roll_pitch_yaw( void );

int
add_test_set_from_roll_pitch_yaw_degrees( void );

int
add_test_set_from_roll( void );

int
add_test_set_from_roll_degrees( void );

int
add_test_set_from_pitch( void );

int
add_test_set_from_pitch_degrees( void );

int
add_test_set_from_yaw( void );

int
add_test_set_from_yaw_degrees( void );

int
add_test_interpolate( void );

int
add_test_interpolated( void );

int
add_test_get_roll_pitch_yaw( void );

int
add_test_get_roll_pitch_yaw_degrees( void );

int
add_test_get_roll( void );

int
add_test_get_roll_degrees( void );

int
add_test_get_pitch( void );

int
add_test_get_pitch_degrees( void );

int
add_test_get_yaw( void );

int
add_test_get_yaw_degrees( void );

int
add_test_rotate_vector( void );

int
add_test_rotated_vector( void );

int
add_test_rotate_xyz( void );

int
add_test_scale( void );

int
add_test_scaled( void );

int
add_test_conjugate( void );

int
add_test_conjugated( void );

int
add_test_invert( void );

int
add_test_inverse( void );

int
add_test_normalize( void );

int
add_test_normalized( void );

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

   // add tests

   add_test_make();
   add_test_make_default();
   add_test_make_from();
   add_test_make_from_array();
   add_test_make_from_vector();
   add_test_make_from_rotation_about_vector();
   add_test_make_from_rotation_degrees_about_vector();
   add_test_make_from_rotation_about_xyz();
   add_test_make_from_rotation_degrees_about_xyz();
   add_test_make_from_roll_pitch_yaw();
   add_test_make_from_roll_pitch_yaw_degrees();
   add_test_make_from_roll();
   add_test_make_from_roll_degrees();
   add_test_make_from_pitch();
   add_test_make_from_pitch_degrees();
   add_test_make_from_yaw();
   add_test_make_from_yaw_degrees();
   add_test_dispose();
   add_test_as_array();
   add_test_as_vector();
   add_test_qn();
   add_test_magnitude();
   add_test_squared_magnitude();
   add_test_is_equal();
   add_test_is_approximately_equal();
   add_test_set();
   add_test_set_qn();
   add_test_set_from();
   add_test_set_from_array();
   add_test_set_from_vector();
   add_test_set_from_rotation_about_vector();
   add_test_set_from_rotation_degrees_about_vector();
   add_test_set_from_rotation_about_xyz();
   add_test_set_from_rotation_degrees_about_xyz();
   add_test_set_from_roll_pitch_yaw();
   add_test_set_from_roll_pitch_yaw_degrees();
   add_test_set_from_roll();
   add_test_set_from_roll_degrees();
   add_test_set_from_pitch();
   add_test_set_from_pitch_degrees();
   add_test_set_from_yaw();
   add_test_set_from_yaw_degrees();
   add_test_interpolate();
   add_test_interpolated();
   add_test_get_roll_pitch_yaw();
   add_test_get_roll_pitch_yaw_degrees();
   add_test_get_roll();
   add_test_get_roll_degrees();
   add_test_get_pitch();
   add_test_get_pitch_degrees();
   add_test_get_yaw();
   add_test_get_yaw_degrees();
   add_test_rotate_vector();
   add_test_rotated_vector();
   add_test_rotate_xyz();
   add_test_scale();
   add_test_scaled();
   add_test_conjugate();
   add_test_conjugated();
   add_test_invert();
   add_test_inverse();
   add_test_normalize();
   add_test_normalized();
   add_test_add();
   add_test_added();
   add_test_subtract();
   add_test_subtracted();
   add_test_multiply();
   add_test_multiplied();

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

