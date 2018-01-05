/**
 @file Quaternion_test_interpolate.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for Quaternion_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Quaternion_make.

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
   test_interpolate_1
*/

void test_interpolate_1( void )
{
   f_quaternion_t *fq = NULL;
   f_quaternion_t *fq1 = NULL;
   f_quaternion_t *fq2 = NULL;

   fq = f_quaternion_make( 1.0, 2.0, 3.0, 4.0 );
   fq1 = f_quaternion_make( 5.0, 5.0, 5.0, 5.0 );
   fq2 = f_quaternion_make( 0.39562828403747219, 0.46156633137705089, 0.52750437871662958, 0.59344242605620834 );
   f_quaternion_interpolate( fq, fq1, 0.5, 0.5 );

   CU_ASSERT( fq != NULL );
   CU_ASSERT( f_quaternion_is_approximately_equal( fq, fq2, 0.0001 ) == 1.0 );

   f_quaternion_dispose( fq );
   f_quaternion_dispose( fq1 );
   f_quaternion_dispose( fq2 );

   return;
}

/**
   test_interpolate_2
*/
void test_interpolate_2( void )
{
   d_quaternion_t *dq = NULL;
   d_quaternion_t *dq1 = NULL;
   d_quaternion_t *dq2 = NULL;

   dq = d_quaternion_make( 1.0, 2.0, 3.0, 4.0 );
   dq1 = d_quaternion_make( 5.0, 5.0, 5.0, 5.0 );
   dq2 = d_quaternion_make( 0.39562828403747219, 0.46156633137705089, 0.52750437871662958, 0.59344242605620834 );
   d_quaternion_interpolate( dq, dq1, 0.5, 0.5 );

   CU_ASSERT( dq != NULL );
   CU_ASSERT( d_quaternion_is_approximately_equal( dq, dq2, 0.0001 ) == 1.0 );

   d_quaternion_dispose( dq );
   d_quaternion_dispose( dq1 );
   d_quaternion_dispose( dq2 );

   return;
}


int
add_test_interpolate( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_interpolate", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_interpolate_1
   add_test_to_suite( p_suite, test_interpolate_1, "test_interpolate_1" );

   // test_interpolate_2
   add_test_to_suite( p_suite, test_interpolate_2, "test_interpolate_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

