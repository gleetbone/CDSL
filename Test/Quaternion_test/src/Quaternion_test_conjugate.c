/**
 @file Quaternion_test_conjugate.c
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
   test_conjugate_1
*/

void test_conjugate_1( void )
{
   f_quaternion_t *fq = NULL;

   fq = f_quaternion_make( 1.0, 2.0, 3.0, 4.0 );
   f_quaternion_conjugate( fq );

   CU_ASSERT( fq != NULL );
   CU_ASSERT( f_quaternion_q0( fq ) == 1.0 );
   CU_ASSERT( f_quaternion_q1( fq ) == -2.0 );
   CU_ASSERT( f_quaternion_q2( fq ) == -3.0 );
   CU_ASSERT( f_quaternion_q3( fq ) == -4.0 );

   f_quaternion_dispose( fq );

   return;
}

/**
   test_conjugate_2
*/
void test_conjugate_2( void )
{
   d_quaternion_t *dq = NULL;

   dq = d_quaternion_make( 1.0, 2.0, 3.0, 4.0 );
   d_quaternion_conjugate( dq );

   CU_ASSERT( dq != NULL );
   CU_ASSERT( d_quaternion_q0( dq ) == 1.0 );
   CU_ASSERT( d_quaternion_q1( dq ) == -2.0 );
   CU_ASSERT( d_quaternion_q2( dq ) == -3.0 );
   CU_ASSERT( d_quaternion_q3( dq ) == -4.0 );

   d_quaternion_dispose( dq );

   return;
}


int
add_test_conjugate( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_conjugate", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_conjugate_1
   add_test_to_suite( p_suite, test_conjugate_1, "test_conjugate_1" );

   // test_conjugate_2
   add_test_to_suite( p_suite, test_conjugate_2, "test_conjugate_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

