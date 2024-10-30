/**
 @file Svd_test_make.c
 @author Greg Lee
 @version 2.0.0
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
   test_make_1
*/

void test_make_1( void )
{
   f_svd_t *fsvd = NULL;

   fsvd = f_svd_make();

   CU_ASSERT( fsvd != NULL );

   f_svd_deep_dispose( &fsvd );

   return;
}

/**
   test_make_2
*/
void test_make_2( void )
{
   d_svd_t *dsvd = NULL;

   dsvd = d_svd_make();

   CU_ASSERT( dsvd != NULL );

   d_svd_deep_dispose( &dsvd );

   return;
}


/**
   test_make_3
*/

void test_make_3( void )
{
   cf_svd_t *cfsvd = NULL;

   cfsvd = cf_svd_make();

   CU_ASSERT( cfsvd != NULL );

   cf_svd_deep_dispose( &cfsvd );

   return;
}

/**
   test_make_4
*/

void test_make_4( void )
{
   cd_svd_t *cdsvd = NULL;

   cdsvd = cd_svd_make();

   CU_ASSERT( cdsvd != NULL );

   cd_svd_deep_dispose( &cdsvd );

   return;
}

int
add_test_make( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_1
   add_test_to_suite( p_suite, test_make_1, "test_make_1" );

   // test_make_2
   add_test_to_suite( p_suite, test_make_2, "test_make_2" );

   // test_make_3
   add_test_to_suite( p_suite, test_make_3, "test_make_3" );

   // test_make_4
   add_test_to_suite( p_suite, test_make_4, "test_make_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

