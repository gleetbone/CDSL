/**
 @file Matvec_test_subtract.c
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
   test_subtract_1
*/

void test_subtract_1( void )
{
   f_matvec_t *fm = NULL;
   f_matvec_t *fm1 = NULL;

   fm = f_matvec_make_from_args( 3, 3, 9, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 );
   fm1 = f_matvec_make_from_args( 3, 3, 9, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 );
   f_matvec_subtract( fm, fm1 );

   CU_ASSERT( fm != NULL );
   CU_ASSERT( fm1 != NULL );
   CU_ASSERT( f_matvec_item( fm, 0, 0 ) == 1.0 );
   CU_ASSERT( f_matvec_item( fm, 0, 1 ) == 1.0 );
   CU_ASSERT( f_matvec_item( fm, 0, 2 ) == 1.0 );
   CU_ASSERT( f_matvec_item( fm, 1, 0 ) == 1.0 );
   CU_ASSERT( f_matvec_item( fm, 1, 1 ) == 1.0 );
   CU_ASSERT( f_matvec_item( fm, 1, 2 ) == 1.0 );
   CU_ASSERT( f_matvec_item( fm, 2, 0 ) == 1.0 );
   CU_ASSERT( f_matvec_item( fm, 2, 1 ) == 1.0 );
   CU_ASSERT( f_matvec_item( fm, 2, 2 ) == 1.0 );

   f_matvec_dispose( &fm );
   f_matvec_dispose( &fm1 );

   return;
}

/**
   test_subtract_2
*/
void test_subtract_2( void )
{
   d_matvec_t *dm = NULL;
   d_matvec_t *dm1 = NULL;

   dm = d_matvec_make_from_args( 3, 3, 9, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 );
   dm1 = d_matvec_make_from_args( 3, 3, 9, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 );
   d_matvec_subtract( dm, dm1 );

   CU_ASSERT( dm != NULL );
   CU_ASSERT( dm1 != NULL );
   CU_ASSERT( d_matvec_item( dm, 0, 0 ) == 1.0 );
   CU_ASSERT( d_matvec_item( dm, 0, 1 ) == 1.0 );
   CU_ASSERT( d_matvec_item( dm, 0, 2 ) == 1.0 );
   CU_ASSERT( d_matvec_item( dm, 1, 0 ) == 1.0 );
   CU_ASSERT( d_matvec_item( dm, 1, 1 ) == 1.0 );
   CU_ASSERT( d_matvec_item( dm, 1, 2 ) == 1.0 );
   CU_ASSERT( d_matvec_item( dm, 2, 0 ) == 1.0 );
   CU_ASSERT( d_matvec_item( dm, 2, 1 ) == 1.0 );
   CU_ASSERT( d_matvec_item( dm, 2, 2 ) == 1.0 );

   d_matvec_dispose( &dm );
   d_matvec_dispose( &dm1 );

   return;
}


/**
   test_subtract_3
*/

void test_subtract_3( void )
{
   cf_matvec_t *cfm = NULL;
   cf_matvec_t *cfm1 = NULL;

   cfm = cf_matvec_make_from_args( 3, 3, 9, 2.0 + 2.0*I, 3.0 + 3.0*I, 4.0 + 4.0*I, 5.0 + 5.0*I, 6.0 + 6.0*I, 7.0 + 7.0*I, 8.0 + 8.0*I, 9.0 + 9.0*I, 10.0 + 10.0*I );
   cfm1 = cf_matvec_make_from_args( 3, 3, 9, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I, 4.0 + 4.0*I, 5.0 + 5.0*I, 6.0 + 6.0*I, 7.0 + 7.0*I, 8.0 + 8.0*I, 9.0 + 9.0*I );
   cf_matvec_subtract( cfm, cfm1 );

   CU_ASSERT( cfm != NULL );
   CU_ASSERT( cf_matvec_item( cfm, 0, 0 ) == 1.0 + 1.0*I );
   CU_ASSERT( cf_matvec_item( cfm, 0, 1 ) == 1.0 + 1.0*I );
   CU_ASSERT( cf_matvec_item( cfm, 0, 2 ) == 1.0 + 1.0*I );
   CU_ASSERT( cf_matvec_item( cfm, 1, 0 ) == 1.0 + 1.0*I );
   CU_ASSERT( cf_matvec_item( cfm, 1, 1 ) == 1.0 + 1.0*I );
   CU_ASSERT( cf_matvec_item( cfm, 1, 2 ) == 1.0 + 1.0*I );
   CU_ASSERT( cf_matvec_item( cfm, 2, 0 ) == 1.0 + 1.0*I );
   CU_ASSERT( cf_matvec_item( cfm, 2, 1 ) == 1.0 + 1.0*I );
   CU_ASSERT( cf_matvec_item( cfm, 2, 2 ) == 1.0 + 1.0*I );

   cf_matvec_dispose( &cfm );
   cf_matvec_dispose( &cfm1 );

   return;
}

/**
   test_subtract_4
*/

void test_subtract_4( void )
{
   cd_matvec_t *cdm = NULL;
   cd_matvec_t *cdm1 = NULL;

   cdm = cd_matvec_make_from_args( 3, 3, 9, 2.0 + 2.0*I, 3.0 + 3.0*I, 4.0 + 4.0*I, 5.0 + 5.0*I, 6.0 + 6.0*I, 7.0 + 7.0*I, 8.0 + 8.0*I, 9.0 + 9.0*I, 10.0 + 10.0*I );
   cdm1 = cd_matvec_make_from_args( 3, 3, 9, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I, 4.0 + 4.0*I, 5.0 + 5.0*I, 6.0 + 6.0*I, 7.0 + 7.0*I, 8.0 + 8.0*I, 9.0 + 9.0*I );
   cd_matvec_subtract( cdm, cdm1 );

   CU_ASSERT( cdm != NULL );
   CU_ASSERT( cd_matvec_item( cdm, 0, 0 ) == 1.0 + 1.0*I );
   CU_ASSERT( cd_matvec_item( cdm, 0, 1 ) == 1.0 + 1.0*I );
   CU_ASSERT( cd_matvec_item( cdm, 0, 2 ) == 1.0 + 1.0*I );
   CU_ASSERT( cd_matvec_item( cdm, 1, 0 ) == 1.0 + 1.0*I );
   CU_ASSERT( cd_matvec_item( cdm, 1, 1 ) == 1.0 + 1.0*I );
   CU_ASSERT( cd_matvec_item( cdm, 1, 2 ) == 1.0 + 1.0*I );
   CU_ASSERT( cd_matvec_item( cdm, 2, 0 ) == 1.0 + 1.0*I );
   CU_ASSERT( cd_matvec_item( cdm, 2, 1 ) == 1.0 + 1.0*I );
   CU_ASSERT( cd_matvec_item( cdm, 2, 2 ) == 1.0 + 1.0*I );

   cd_matvec_dispose( &cdm );
   cd_matvec_dispose( &cdm1 );

   return;
}

int
add_test_subtract( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_subtract", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_subtract_1
   add_test_to_suite( p_suite, test_subtract_1, "test_subtract_1" );

   // test_subtract_2
   add_test_to_suite( p_suite, test_subtract_2, "test_subtract_2" );

   // test_subtract_3
   add_test_to_suite( p_suite, test_subtract_3, "test_subtract_3" );

   // test_subtract_4
   add_test_to_suite( p_suite, test_subtract_4, "test_subtract_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

