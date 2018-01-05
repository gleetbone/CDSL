/**
 @file Svd_test_input.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for Svd_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Svd_make.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "f_Matvec.h"
#include "d_Matvec.h"
#include "cf_Matvec.h"
#include "cd_Matvec.h"

#include "f_Svd.h"
#include "d_Svd.h"
#include "cf_Svd.h"
#include "cd_Svd.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_input_1
*/

void test_input_1( void )
{
   f_svd_t *fsvd = NULL;
   f_matvec_t *m = NULL;
   f_matvec_t *m1 = NULL;

   fsvd = f_svd_make();
   m = f_matvec_make_from_args( 2, 2, 4, 1.0, 2.0, 3.0, 4.0 );
   f_svd_set_input( fsvd, m );
   m1 = f_svd_input( fsvd );

   CU_ASSERT( fsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m == m1 );

   f_svd_dispose_with_contents( fsvd );

   return;
}

/**
   test_input_2
*/
void test_input_2( void )
{
   d_svd_t *dsvd = NULL;
   d_matvec_t *m = NULL;
   d_matvec_t *m1 = NULL;

   dsvd = d_svd_make();
   m = d_matvec_make_from_args( 2, 2, 4, 1.0, 2.0, 3.0, 4.0 );
   d_svd_set_input( dsvd, m );
   m1 = d_svd_input( dsvd );

   CU_ASSERT( dsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m == m1 );

   d_svd_dispose_with_contents( dsvd );

   return;
}


/**
   test_input_3
*/

void test_input_3( void )
{
   cf_svd_t *cfsvd = NULL;
   cf_matvec_t *m = NULL;
   cf_matvec_t *m1 = NULL;

   cfsvd = cf_svd_make();
   m = cf_matvec_make_from_args( 2, 2, 4, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I, 4.0 + 4.0*I );
   cf_svd_set_input( cfsvd, m );
   m1 = cf_svd_input( cfsvd );

   CU_ASSERT( cfsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m == m1 );

   cf_svd_dispose_with_contents( cfsvd );

   return;
}

/**
   test_input_4
*/

void test_input_4( void )
{
   cd_svd_t *cdsvd = NULL;
   cd_matvec_t *m = NULL;
   cd_matvec_t *m1 = NULL;

   cdsvd = cd_svd_make();
   m = cd_matvec_make_from_args( 2, 2, 4, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I, 4.0 + 4.0*I );
   cd_svd_set_input( cdsvd, m );
   m1 = cd_svd_input( cdsvd );

   CU_ASSERT( cdsvd != NULL );
   CU_ASSERT( m != NULL );
   CU_ASSERT( m == m1 );

   cd_svd_dispose_with_contents( cdsvd );

   return;
}

int
add_test_input( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_input", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_input_1
   add_test_to_suite( p_suite, test_input_1, "test_input_1" );

   // test_input_2
   add_test_to_suite( p_suite, test_input_2, "test_input_2" );

   // test_input_3
   add_test_to_suite( p_suite, test_input_3, "test_input_3" );

   // test_input_4
   add_test_to_suite( p_suite, test_input_4, "test_input_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

