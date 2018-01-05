/**
 @file Matvec_test_vector_normalize.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for Matvec_make"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue64 Mar 2011) $"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Matvec_make.

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
   test_vector_normalize_1
*/

void test_vector_normalize_1( void )
{
   f_matvec_t *fm = NULL;
   f_matvec_t *fm1 = NULL;

   fm = f_matvec_make_from_args( 1, 3, 3, 1.0, 2.0, 2.0 );
   fm1 = f_matvec_make_from_args( 1, 3, 3, 0.333333, 0.666666, 0.666666 );
   f_matvec_vector_normalize( fm );

   CU_ASSERT( fm != NULL );
   CU_ASSERT( f_matvec_is_row_vector( fm ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( fm, fm1, 0.001 ) == 1 );

   f_matvec_dispose( fm );
   f_matvec_dispose( fm1 );

   fm = f_matvec_make_from_args( 3, 1, 3, 1.0, 2.0, 2.0 );
   fm1 = f_matvec_make_from_args( 3, 1, 3, 0.333333, 0.666666, 0.666666 );
   f_matvec_vector_normalize( fm );

   CU_ASSERT( fm != NULL );
   CU_ASSERT( f_matvec_is_column_vector( fm ) == 1 );
   CU_ASSERT( f_matvec_is_approximately_equal( fm, fm1, 0.001 ) == 1 );

   f_matvec_dispose( fm );
   f_matvec_dispose( fm1 );

   return;
}

/**
   test_vector_normalize_2
*/

void test_vector_normalize_2( void )
{
   d_matvec_t *dm = NULL;
   d_matvec_t *dm1 = NULL;

   dm = d_matvec_make_from_args( 1, 3, 3, 1.0, 2.0, 2.0 );
   dm1 = d_matvec_make_from_args( 1, 3, 3, 0.333333, 0.666666, 0.666666 );
   d_matvec_vector_normalize( dm );

   CU_ASSERT( dm != NULL );
   CU_ASSERT( d_matvec_is_row_vector( dm ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( dm, dm1, 0.001 ) == 1 );

   d_matvec_dispose( dm );
   d_matvec_dispose( dm1 );

   dm = d_matvec_make_from_args( 3, 1, 3, 1.0, 2.0, 2.0 );
   dm1 = d_matvec_make_from_args( 3, 1, 3, 0.333333, 0.666666, 0.666666 );
   d_matvec_vector_normalize( dm );

   CU_ASSERT( dm != NULL );
   CU_ASSERT( d_matvec_is_column_vector( dm ) == 1 );
   CU_ASSERT( d_matvec_is_approximately_equal( dm, dm1, 0.001 ) == 1 );

   d_matvec_dispose( dm );
   d_matvec_dispose( dm1 );

   return;
}

/**
   test_vector_normalize_3
*/

void test_vector_normalize_3( void )
{
   cf_matvec_t *cfm = NULL;
   cf_matvec_t *cfm1 = NULL;

   cfm = cf_matvec_make_from_args( 1, 3, 3, 0.0 + 1.0*I, 0.0 + 2.0*I, 0.0 + 2.0*I );
   cfm1 = cf_matvec_make_from_args( 1, 3, 3, 0.0 + 0.333333*I, 0.0 + 0.666666*I, 0.0 + 0.666666*I );
   cf_matvec_vector_normalize( cfm );

   CU_ASSERT( cfm != NULL );
   CU_ASSERT( cf_matvec_is_row_vector( cfm ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( cfm, cfm1, 0.001 ) == 1 );

   cf_matvec_dispose( cfm );
   cf_matvec_dispose( cfm1 );

   cfm = cf_matvec_make_from_args( 3, 1, 3, 0.0 + 1.0*I, 0.0 + 2.0*I, 0.0 + 2.0*I );
   cfm1 = cf_matvec_make_from_args( 3, 1, 3, 0.0 + 0.333333*I, 0.0 + 0.666666*I, 0.0 + 0.666666*I );
   cf_matvec_vector_normalize( cfm );

   CU_ASSERT( cfm != NULL );
   CU_ASSERT( cf_matvec_is_column_vector( cfm ) == 1 );
   CU_ASSERT( cf_matvec_is_approximately_equal( cfm, cfm1, 0.001 ) == 1 );

   cf_matvec_dispose( cfm );
   cf_matvec_dispose( cfm1 );

   return;
}

/**
   test_vector_normalize_4
*/

void test_vector_normalize_4( void )
{
   cd_matvec_t *cdm = NULL;
   cd_matvec_t *cdm1 = NULL;

   cdm = cd_matvec_make_from_args( 1, 3, 3, 0.0 + 1.0*I, 0.0 + 2.0*I, 0.0 + 2.0*I );
   cdm1 = cd_matvec_make_from_args( 1, 3, 3, 0.0 + 0.333333*I, 0.0 + 0.666666*I, 0.0 + 0.666666*I );
   cd_matvec_vector_normalize( cdm );

   CU_ASSERT( cdm != NULL );
   CU_ASSERT( cdm1 != NULL );
   CU_ASSERT( cd_matvec_is_row_vector( cdm ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( cdm, cdm1, 0.001 ) == 1 );

   cd_matvec_dispose( cdm );
   cd_matvec_dispose( cdm1 );

   cdm = cd_matvec_make_from_args( 3, 1, 3, 0.0 + 1.0*I, 0.0 + 2.0*I, 0.0 + 2.0*I );
   cdm1 = cd_matvec_make_from_args( 3, 1, 3, 0.0 + 0.333333*I, 0.0 + 0.666666*I, 0.0 + 0.666666*I );
   cd_matvec_vector_normalize( cdm );

   CU_ASSERT( cdm != NULL );
   CU_ASSERT( cd_matvec_is_column_vector( cdm ) == 1 );
   CU_ASSERT( cd_matvec_is_approximately_equal( cdm, cdm1, 0.001 ) == 1 );

   cd_matvec_dispose( cdm );
   cd_matvec_dispose( cdm1 );

   return;
}

int
add_test_vector_normalize( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_vector_normalize", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_vector_normalize_1
   add_test_to_suite( p_suite, test_vector_normalize_1, "test_vector_normalize_1" );

   // test_vector_normalize_2
   add_test_to_suite( p_suite, test_vector_normalize_2, "test_vector_normalize_2" );

   // test_vector_normalize_3
   add_test_to_suite( p_suite, test_vector_normalize_3, "test_vector_normalize_3" );

   // test_vector_normalize_4
   add_test_to_suite( p_suite, test_vector_normalize_4, "test_vector_normalize_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

