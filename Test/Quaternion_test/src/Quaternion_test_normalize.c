/**
 @file Quaternion_test_normalize.c
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
   test_normalize_1
*/

void test_normalize_1( void )
{
   f_quaternion_t *fq = NULL;
   f_quaternion_t *fq1 = NULL;

   fq = f_quaternion_make( 1.0, 2.0, 3.0, 4.0 );
   fq1 = f_quaternion_make( 0.18257418583505536, 0.36514837167011072, 0.54772255750516607, 0.73029674334022143 );
   f_quaternion_normalize( fq );

   CU_ASSERT( fq != NULL );
   CU_ASSERT( fq1 != NULL );
   CU_ASSERT( f_quaternion_is_approximately_equal( fq, fq1, 0.00001 ) == 1.0 );

   f_quaternion_dispose( fq );
   f_quaternion_dispose( fq1 );

   return;
}

/**
   test_normalize_2
*/
void test_normalize_2( void )
{
   d_quaternion_t *dq = NULL;
   d_quaternion_t *dq1 = NULL;

   dq = d_quaternion_make( 1.0, 2.0, 3.0, 4.0 );
   dq1 = d_quaternion_make( 0.18257418583505536, 0.36514837167011072, 0.54772255750516607, 0.73029674334022143 );
   d_quaternion_normalize( dq );

   CU_ASSERT( dq != NULL );
   CU_ASSERT( dq1 != NULL );
   CU_ASSERT( d_quaternion_is_approximately_equal( dq, dq1, 0.00001 ) == 1.0 );

   d_quaternion_dispose( dq );
   d_quaternion_dispose( dq1 );

   return;
}


int
add_test_normalize( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_normalize", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_normalize_1
   add_test_to_suite( p_suite, test_normalize_1, "test_normalize_1" );

   // test_normalize_2
   add_test_to_suite( p_suite, test_normalize_2, "test_normalize_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */
