/**
 @file Matvec_test_make_from.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Matvec_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Matvec_t

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

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_from_1
*/

void test_make_from_1( void )
{
   f_matvec_t *fm = NULL;
   f_matvec_t *fm1 = NULL;

   fm = f_matvec_make( 2, 2 );
   fm1 = f_matvec_make_from( fm );

   CU_ASSERT( fm1 != NULL );
   CU_ASSERT( f_matvec_item( fm1, 1, 1 ) == 0.0 );

   f_matvec_dispose( &fm );
   f_matvec_dispose( &fm1 );

   return;
}

/**
   test_make_from_2
*/
void test_make_from_2( void )
{
   d_matvec_t *dm = NULL;
   d_matvec_t *dm1 = NULL;

   dm = d_matvec_make( 2, 2 );
   dm1 = d_matvec_make_from( dm );

   CU_ASSERT( dm1 != NULL );
   CU_ASSERT( d_matvec_item( dm1, 1, 1 ) == 0.0 );

   d_matvec_dispose( &dm );
   d_matvec_dispose( &dm1 );

   return;
}


/**
   test_make_from_3
*/

void test_make_from_3( void )
{
   cf_matvec_t *cfm = NULL;
   cf_matvec_t *cfm1 = NULL;

   cfm = cf_matvec_make( 2, 2 );
   cfm1 = cf_matvec_make_from( cfm );

   CU_ASSERT( cfm1 != NULL );
   CU_ASSERT( cf_matvec_item( cfm1, 1, 1 ) == 0.0 );

   cf_matvec_dispose( &cfm );
   cf_matvec_dispose( &cfm1 );

   return;
}

/**
   test_make_from_4
*/

void test_make_from_4( void )
{
   cd_matvec_t *cdm = NULL;
   cd_matvec_t *cdm1 = NULL;

   cdm = cd_matvec_make( 2, 2 );
   cdm1 = cd_matvec_make_from( cdm );

   CU_ASSERT( cdm1 != NULL );
   CU_ASSERT( cd_matvec_item( cdm1, 1, 1 ) == 0.0 );

   cd_matvec_dispose( &cdm );
   cd_matvec_dispose( &cdm1 );

   return;
}

int
add_test_make_from( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_from", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_from_1
   add_test_to_suite( p_suite, test_make_from_1, "test_make_from_1" );

   // test_make_from_2
   add_test_to_suite( p_suite, test_make_from_2, "test_make_from_2" );

   // test_make_from_3
   add_test_to_suite( p_suite, test_make_from_3, "test_make_from_3" );

   // test_make_from_4
   add_test_to_suite( p_suite, test_make_from_4, "test_make_from_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

