/**
 @file Quaternion_test_set_from_array.c
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
   test_set_from_array_1
*/

void test_set_from_array_1( void )
{
   f_quaternion_t *fq = NULL;
   float32_t *array = NULL;

   array = ( float32_t * ) calloc( 4, sizeof( float32_t ) );
   array[0] = 1.0;
   array[1] = 2.0;
   array[2] = 3.0;
   array[3] = 4.0;
   fq = f_quaternion_make_default();
   f_quaternion_set_from_array( fq, array );

   CU_ASSERT( fq != NULL );
   CU_ASSERT( f_quaternion_q0( fq ) == 1.0 );
   CU_ASSERT( f_quaternion_q1( fq ) == 2.0 );
   CU_ASSERT( f_quaternion_q2( fq ) == 3.0 );
   CU_ASSERT( f_quaternion_q3( fq ) == 4.0 );

   f_quaternion_dispose( &fq );
   free( array );

   return;
}

/**
   test_set_from_array_2
*/
void test_set_from_array_2( void )
{
   d_quaternion_t *dq = NULL;
   float64_t *array = NULL;

   array = ( float64_t * ) calloc( 4, sizeof( float64_t ) );
   array[0] = 1.0;
   array[1] = 2.0;
   array[2] = 3.0;
   array[3] = 4.0;

   dq = d_quaternion_make_default();
    d_quaternion_set_from_array( dq, array );

   CU_ASSERT( dq != NULL );
   CU_ASSERT( d_quaternion_q0( dq ) == 1.0 );
   CU_ASSERT( d_quaternion_q1( dq ) == 2.0 );
   CU_ASSERT( d_quaternion_q2( dq ) == 3.0 );
   CU_ASSERT( d_quaternion_q3( dq ) == 4.0 );

   d_quaternion_dispose( &dq );
   free( array );

   return;
}


int
add_test_set_from_array( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_set_from_array", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_set_from_array_1
   add_test_to_suite( p_suite, test_set_from_array_1, "test_set_from_array_1" );

   // test_set_from_array_2
   add_test_to_suite( p_suite, test_set_from_array_2, "test_set_from_array_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

