/**
 @file Quaternion_test_rotate_vector.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Quaternion_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Quaternion_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "f_Quaternion.h"
#include "d_Quaternion.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_rotate_vector_1
*/

void test_rotate_vector_1( void )
{
   f_quaternion_t *fq = NULL;
   f_matvec_t *vector = NULL;
   f_matvec_t *v1 = NULL;

   vector = f_matvec_make_from_args( 3, 1, 3, 1.0, 0.0, 0.0 );
   v1 = f_matvec_make_from_args( 3, 1, 3, 1.0, 0.0, 0.0 );

   fq = f_quaternion_make_from_roll_pitch_yaw( 0.0, 0.0, 0.0 );
   f_quaternion_rotate_vector( fq, vector );

   CU_ASSERT( fq != NULL );
   CU_ASSERT( vector != NULL );
   CU_ASSERT( v1 != NULL );
   CU_ASSERT( f_matvec_is_approximately_equal( vector, v1, 0.0001 ) == 1.0 );

   f_matvec_dispose( &vector );
   f_matvec_dispose( &v1 );
   f_quaternion_dispose( &fq );

   vector = f_matvec_make_from_args( 3, 1, 3, 1.0, 0.0, 0.0 );
   v1 = f_matvec_make_from_args( 3, 1, 3, 0.0, 0.0, -1.0 );

   fq = f_quaternion_make_from_roll_pitch_yaw( 0.0, M_PI/2.0, 0.0);
   f_quaternion_rotate_vector( fq, vector );

   CU_ASSERT( fq != NULL );
   CU_ASSERT( vector != NULL );
   CU_ASSERT( v1 != NULL );
   CU_ASSERT( f_matvec_is_approximately_equal( vector, v1, 0.0001 ) == 1.0 );

   f_matvec_dispose( &vector );
   f_matvec_dispose( &v1 );
   f_quaternion_dispose( &fq );

   return;
}

/**
   test_rotate_vector_2
*/
void test_rotate_vector_2( void )
{
   d_quaternion_t *dq = NULL;
   d_matvec_t *vector = NULL;
   d_matvec_t *v1 = NULL;

   vector = d_matvec_make_from_args( 3, 1, 3, 1.0, 0.0, 0.0 );
   v1 = d_matvec_make_from_args( 3, 1, 3, 1.0, 0.0, 0.0 );

   dq = d_quaternion_make_from_roll_pitch_yaw( 0.0, 0.0, 0.0 );
   d_quaternion_rotate_vector( dq, vector );

   CU_ASSERT( dq != NULL );
   CU_ASSERT( vector != NULL );
   CU_ASSERT( v1 != NULL );
   CU_ASSERT( d_matvec_is_approximately_equal( vector, v1, 0.0001 ) == 1.0 );

   d_matvec_dispose( &vector );
   d_matvec_dispose( &v1 );
   d_quaternion_dispose( &dq );

   vector = d_matvec_make_from_args( 3, 1, 3, 1.0, 0.0, 0.0 );
   v1 = d_matvec_make_from_args( 3, 1, 3, 0.0, 0.0, -1.0 );

   dq = d_quaternion_make_from_roll_pitch_yaw( 0.0, M_PI/2.0, 0.0);
   d_quaternion_rotate_vector( dq, vector );

   CU_ASSERT( dq != NULL );
   CU_ASSERT( vector != NULL );
   CU_ASSERT( v1 != NULL );
   CU_ASSERT( d_matvec_is_approximately_equal( vector, v1, 0.0001 ) == 1.0 );

   d_matvec_dispose( &vector );
   d_matvec_dispose( &v1 );
   d_quaternion_dispose( &dq );

   return;
}


int
add_test_rotate_vector( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_rotate_vector", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_rotate_vector_1
   add_test_to_suite( p_suite, test_rotate_vector_1, "test_rotate_vector_1" );

   // test_rotate_vector_2
   add_test_to_suite( p_suite, test_rotate_vector_2, "test_rotate_vector_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

