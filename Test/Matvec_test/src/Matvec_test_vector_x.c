/**
 @file Matvec_test_vector_x.c
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
   test_vector_x_1
*/

void test_vector_x_1( void )
{
   f_matvec_t *fm = NULL;

   fm = f_matvec_make_from_args( 1, 3, 3, 1.0, 2.0, 3.0 );

   CU_ASSERT( fm != NULL );
   CU_ASSERT( f_matvec_is_row_vector( fm ) == 1 );
   CU_ASSERT( f_matvec_vector_x( fm ) == 1.0 );

   f_matvec_dispose( fm );

   fm = f_matvec_make_from_args( 3, 1, 3, 1.0, 2.0, 3.0 );

   CU_ASSERT( fm != NULL );
   CU_ASSERT( f_matvec_is_column_vector( fm ) == 1 );
   CU_ASSERT( f_matvec_vector_x( fm ) == 1.0 );

   f_matvec_dispose( fm );

   return;
}

/**
   test_vector_x_2
*/

void test_vector_x_2( void )
{
   d_matvec_t *dm = NULL;

   dm = d_matvec_make_from_args( 1, 3, 3, 1.0, 2.0, 3.0 );

   CU_ASSERT( dm != NULL );
   CU_ASSERT( d_matvec_is_row_vector( dm ) == 1 );
   CU_ASSERT( d_matvec_vector_x( dm ) == 1.0 );

   d_matvec_dispose( dm );

   dm = d_matvec_make_from_args( 3, 1, 3, 1.0, 2.0, 3.0 );

   CU_ASSERT( dm != NULL );
   CU_ASSERT( d_matvec_is_column_vector( dm ) == 1 );
   CU_ASSERT( d_matvec_vector_x( dm ) == 1.0 );

   d_matvec_dispose( dm );

   return;
}

/**
   test_vector_x_3
*/

void test_vector_x_3( void )
{
   cf_matvec_t *cfm = NULL;

   cfm = cf_matvec_make_from_args( 1, 3, 3, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I );

   CU_ASSERT( cfm != NULL );
   CU_ASSERT( cf_matvec_is_row_vector( cfm ) == 1 );
   CU_ASSERT( cf_matvec_vector_x( cfm ) == 1.0 + 1.0*I );

   cf_matvec_dispose( cfm );

   cfm = cf_matvec_make_from_args( 3, 1, 3, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I );

   CU_ASSERT( cfm != NULL );
   CU_ASSERT( cf_matvec_is_column_vector( cfm ) == 1 );
   CU_ASSERT( cf_matvec_vector_x( cfm ) == 1.0 + 1.0*I );

   cf_matvec_dispose( cfm );

   return;
}

/**
   test_vector_x_4
*/

void test_vector_x_4( void )
{
   cd_matvec_t *cdm = NULL;

   cdm = cd_matvec_make_from_args( 1, 3, 3, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I );

   CU_ASSERT( cdm != NULL );
   CU_ASSERT( cd_matvec_is_row_vector( cdm ) == 1 );
   CU_ASSERT( cd_matvec_vector_x( cdm ) == 1.0 + 1.0*I );

   cd_matvec_dispose( cdm );

   cdm = cd_matvec_make_from_args( 3, 1, 3, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I );

   CU_ASSERT( cdm != NULL );
   CU_ASSERT( cd_matvec_is_column_vector( cdm ) == 1 );

   CU_ASSERT( cd_matvec_vector_x( cdm ) == 1.0 + 1.0*I );

   cd_matvec_dispose( cdm );

   return;
}

int
add_test_vector_x( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_vector_x", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_vector_x_1
   add_test_to_suite( p_suite, test_vector_x_1, "test_vector_x_1" );

   // test_vector_x_2
   add_test_to_suite( p_suite, test_vector_x_2, "test_vector_x_2" );

   // test_vector_x_3
   add_test_to_suite( p_suite, test_vector_x_3, "test_vector_x_3" );

   // test_vector_x_4
   add_test_to_suite( p_suite, test_vector_x_4, "test_vector_x_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

