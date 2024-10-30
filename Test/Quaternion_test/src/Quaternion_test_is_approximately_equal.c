/**
 @file Quaternion_test_is_approximately_equal.c
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
   test_is_approximately_equal_1
*/

void test_is_approximately_equal_1( void )
{
   f_quaternion_t *fq = NULL;
   f_quaternion_t *fq1 = NULL;
   f_quaternion_t *fq2 = NULL;

   fq = f_quaternion_make( 1.0, 2.0, 3.0, 4.0 );
   fq1 = f_quaternion_make( 1.0000001, 2.0, 3.0, 4.0 );
   fq2 = f_quaternion_make( 1.0, 2.0, 3.001, 4.0 );

   CU_ASSERT( fq != NULL );
   CU_ASSERT( f_quaternion_is_approximately_equal( fq, fq1, 0.0001 ) == 1 );
   CU_ASSERT( f_quaternion_is_approximately_equal( fq, fq2, 0.0001 ) == 0 );

   f_quaternion_dispose( &fq );
   f_quaternion_dispose( &fq1 );
   f_quaternion_dispose( &fq2 );

   return;
}

/**
   test_is_approximately_equal_2
*/
void test_is_approximately_equal_2( void )
{
   d_quaternion_t *dq = NULL;
   d_quaternion_t *dq1 = NULL;
   d_quaternion_t *dq2 = NULL;

   dq = d_quaternion_make( 1.0, 2.0, 3.0, 4.0 );
   dq1 = d_quaternion_make( 1.0000001, 2.0, 3.0, 4.0 );
   dq2 = d_quaternion_make( 1.0, 2.0, 3.001, 4.0 );

   CU_ASSERT( dq != NULL );
   CU_ASSERT( d_quaternion_is_approximately_equal( dq, dq1, 0.0001 ) == 1 );
   CU_ASSERT( d_quaternion_is_approximately_equal( dq, dq2, 0.0001 ) == 0 );

   d_quaternion_dispose( &dq );
   d_quaternion_dispose( &dq1 );
   d_quaternion_dispose( &dq2 );

   return;
}


int
add_test_is_approximately_equal( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_approximately_equal", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_approximately_equal_1
   add_test_to_suite( p_suite, test_is_approximately_equal_1, "test_is_approximately_equal_1" );

   // test_is_approximately_equal_2
   add_test_to_suite( p_suite, test_is_approximately_equal_2, "test_is_approximately_equal_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

