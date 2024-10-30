/**
 @file Quaternion_test_as_vector.c
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
   test_as_vector_1
*/

void test_as_vector_1( void )
{
   f_quaternion_t *fq = NULL;
   f_matvec_t *vector = NULL;

   fq = f_quaternion_make( 1.0, 2.0, 3.0, 4.0 );
   vector = f_quaternion_as_vector( fq );

   CU_ASSERT( fq != NULL );
   CU_ASSERT( vector != NULL );
   CU_ASSERT( f_matvec_vector_item( vector, 0 ) == 1.0 );
   CU_ASSERT( f_matvec_vector_item( vector, 1 ) == 2.0 );
   CU_ASSERT( f_matvec_vector_item( vector, 2 ) == 3.0 );
   CU_ASSERT( f_matvec_vector_item( vector, 3 ) == 4.0 );

   f_quaternion_dispose( &fq );
   f_matvec_dispose( &vector );

   return;
}

/**
   test_as_vector_2
*/
void test_as_vector_2( void )
{
   d_quaternion_t *dq = NULL;
   d_matvec_t *vector = NULL;

   dq = d_quaternion_make( 1.0, 2.0, 3.0, 4.0 );
   vector = d_quaternion_as_vector( dq );

   CU_ASSERT( dq != NULL );
   CU_ASSERT( vector != NULL );
   CU_ASSERT( d_matvec_vector_item( vector, 0 ) == 1.0 );
   CU_ASSERT( d_matvec_vector_item( vector, 1 ) == 2.0 );
   CU_ASSERT( d_matvec_vector_item( vector, 2 ) == 3.0 );
   CU_ASSERT( d_matvec_vector_item( vector, 3 ) == 4.0 );

   d_quaternion_dispose( &dq );
   d_matvec_dispose( &vector );

   return;
}


int
add_test_as_vector( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_as_vector", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_as_vector_1
   add_test_to_suite( p_suite, test_as_vector_1, "test_as_vector_1" );

   // test_as_vector_2
   add_test_to_suite( p_suite, test_as_vector_2, "test_as_vector_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

