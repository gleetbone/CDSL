/**
 @file Quaternion_test_set_from.c
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
   test_set_from_1
*/

void test_set_from_1( void )
{
   f_quaternion_t *fq = NULL;
   f_quaternion_t *fq1 = NULL;

   fq1 = f_quaternion_make( 1.0, 2.0, 3.0, 4.0 );
   fq = f_quaternion_make_default();
   f_quaternion_set_from( fq, fq1 );

   CU_ASSERT( fq != NULL );
   CU_ASSERT( fq1 != NULL );
   CU_ASSERT( f_quaternion_q0( fq ) == 1.0 );
   CU_ASSERT( f_quaternion_q1( fq ) == 2.0 );
   CU_ASSERT( f_quaternion_q2( fq ) == 3.0 );
   CU_ASSERT( f_quaternion_q3( fq ) == 4.0 );

   f_quaternion_dispose( fq );
   f_quaternion_dispose( fq1 );

   return;
}

/**
   test_set_from_2
*/
void test_set_from_2( void )
{
   d_quaternion_t *dq = NULL;
   d_quaternion_t *dq1 = NULL;

   dq1 = d_quaternion_make( 1.0, 2.0, 3.0, 4.0 );
   dq = d_quaternion_make_default();
   d_quaternion_set_from( dq, dq1 );

   CU_ASSERT( dq != NULL );
   CU_ASSERT( dq1 != NULL );
   CU_ASSERT( d_quaternion_q0( dq ) == 1.0 );
   CU_ASSERT( d_quaternion_q1( dq ) == 2.0 );
   CU_ASSERT( d_quaternion_q2( dq ) == 3.0 );
   CU_ASSERT( d_quaternion_q3( dq ) == 4.0 );

   d_quaternion_dispose( dq );
   d_quaternion_dispose( dq1 );

   return;
}


int
add_test_set_from( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_set_from", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_set_from_1
   add_test_to_suite( p_suite, test_set_from_1, "test_set_from_1" );

   // test_set_from_2
   add_test_to_suite( p_suite, test_set_from_2, "test_set_from_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

