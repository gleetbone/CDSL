/**
 @file Quaternion_test_get_pitch.c
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
   test_get_pitch_1
*/

void test_get_pitch_1( void )
{
   f_quaternion_t *fq = NULL;
   float32_t x = 0.0;

   fq = f_quaternion_make_default();
   x = f_quaternion_get_pitch( fq );

   CU_ASSERT( fq != NULL );
   CU_ASSERT( x == 0.0 );

   f_quaternion_dispose( &fq );

   fq = f_quaternion_make_from_pitch( M_PI/3.0);
   x = f_quaternion_get_pitch( fq );

   CU_ASSERT( fq != NULL );
   CU_ASSERT( fabs( x - M_PI/3.0 ) < 0.0001 );

   f_quaternion_dispose( &fq );

   return;
}

/**
   test_get_pitch_2
*/
void test_get_pitch_2( void )
{
   d_quaternion_t *dq = NULL;
   float64_t x = 0.0;

   dq = d_quaternion_make_default();
   x = d_quaternion_get_pitch( dq );

   CU_ASSERT( dq != NULL );
   CU_ASSERT( x == 0.0 );

   d_quaternion_dispose( &dq );

   dq = d_quaternion_make_from_pitch( M_PI/3.0 );
   x = d_quaternion_get_pitch( dq );

   CU_ASSERT( dq != NULL );
   CU_ASSERT( fabs( x - M_PI/3.0 ) < 0.0001 );

   d_quaternion_dispose( &dq );

   return;
}


int
add_test_get_pitch( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_get_pitch", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_get_pitch_1
   add_test_to_suite( p_suite, test_get_pitch_1, "test_get_pitch_1" );

   // test_get_pitch_2
   add_test_to_suite( p_suite, test_get_pitch_2, "test_get_pitch_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

