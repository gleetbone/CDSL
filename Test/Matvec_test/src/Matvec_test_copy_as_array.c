/**
 @file Matvec_test_copy_as_array.c
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
   test_copy_as_array_1
*/

void test_copy_as_array_1( void )
{
   f_matvec_t *fm = NULL;
   float32_t *array = NULL;

   fm = f_matvec_make_from_args( 1, 3, 3, 1.0, 2.0, 3.0 );
   array = f_matvec_copy_as_array( fm );

   CU_ASSERT( fm != NULL );
   CU_ASSERT( f_matvec_is_row_vector( fm ) == 1 );
   CU_ASSERT( array[0] == 1.0 );
   CU_ASSERT( array[1] == 2.0 );
   CU_ASSERT( array[2] == 3.0 );

   f_matvec_dispose( &fm );
   free( array );

   fm = f_matvec_make_from_args( 3, 1, 3, 1.0, 2.0, 3.0 );
   array = f_matvec_copy_as_array( fm );

   CU_ASSERT( fm != NULL );
   CU_ASSERT( f_matvec_is_column_vector( fm ) == 1 );
   CU_ASSERT( array[0] == 1.0 );
   CU_ASSERT( array[1] == 2.0 );
   CU_ASSERT( array[2] == 3.0 );

   f_matvec_dispose( &fm );
   free( array );

   fm = f_matvec_make_from_args( 2, 2, 4, 1.0, 2.0, 3.0, 4.0 );
   array = f_matvec_copy_as_array( fm );

   CU_ASSERT( fm != NULL );
   CU_ASSERT( array[0] == 1.0 );
   CU_ASSERT( array[1] == 2.0 );
   CU_ASSERT( array[2] == 3.0 );
   CU_ASSERT( array[3] == 4.0 );

   f_matvec_dispose( &fm );
   free( array );

   return;
}

/**
   test_copy_as_array_2
*/

void test_copy_as_array_2( void )
{
   d_matvec_t *dm = NULL;
   float64_t *array = NULL;

   dm = d_matvec_make_from_args( 1, 3, 3, 1.0, 2.0, 3.0 );
   array = d_matvec_copy_as_array( dm );

   CU_ASSERT( dm != NULL );
   CU_ASSERT( d_matvec_is_row_vector( dm ) == 1 );
   CU_ASSERT( array[0] == 1.0 );
   CU_ASSERT( array[1] == 2.0 );
   CU_ASSERT( array[2] == 3.0 );

   d_matvec_dispose( &dm );
   free( array );

   dm = d_matvec_make_from_args( 3, 1, 3, 1.0, 2.0, 3.0 );
   array = d_matvec_copy_as_array( dm );

   CU_ASSERT( dm != NULL );
   CU_ASSERT( d_matvec_is_column_vector( dm ) == 1 );
   CU_ASSERT( array[0] == 1.0 );
   CU_ASSERT( array[1] == 2.0 );
   CU_ASSERT( array[2] == 3.0 );

   d_matvec_dispose( &dm );
   free( array );

   dm = d_matvec_make_from_args( 2, 2, 4, 1.0, 2.0, 3.0, 4.0 );
   array = d_matvec_copy_as_array( dm );

   CU_ASSERT( dm != NULL );
   CU_ASSERT( array[0] == 1.0 );
   CU_ASSERT( array[1] == 2.0 );
   CU_ASSERT( array[2] == 3.0 );
   CU_ASSERT( array[3] == 4.0 );

   d_matvec_dispose( &dm );
   free( array );

   return;
}

/**
   test_copy_as_array_3
*/

void test_copy_as_array_3( void )
{
   cf_matvec_t *cfm = NULL;
   complex64_t *array = NULL;

   cfm = cf_matvec_make_from_args( 1, 3, 3, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I );
   array = cf_matvec_copy_as_array( cfm );

   CU_ASSERT( cfm != NULL );
   CU_ASSERT( cf_matvec_is_row_vector( cfm ) == 1 );
   CU_ASSERT( array[0] == 1.0 + 1.0*I );
   CU_ASSERT( array[1] == 2.0 + 2.0*I );
   CU_ASSERT( array[2] == 3.0 + 3.0*I );

   cf_matvec_dispose( &cfm );
   free( array );

   cfm = cf_matvec_make_from_args( 3, 1, 3, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I );
   array = cf_matvec_copy_as_array( cfm );

   CU_ASSERT( cfm != NULL );
   CU_ASSERT( cf_matvec_is_column_vector( cfm ) == 1 );
   CU_ASSERT( array[0] == 1.0 + 1.0*I );
   CU_ASSERT( array[1] == 2.0 + 2.0*I );
   CU_ASSERT( array[2] == 3.0 + 3.0*I );

   cf_matvec_dispose( &cfm );
   free( array );

   cfm = cf_matvec_make_from_args( 2, 2, 4, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I, 4.0 + 4.0*I );
   array = cf_matvec_copy_as_array( cfm );

   CU_ASSERT( cfm != NULL );
   CU_ASSERT( array[0] == 1.0 + 1.0*I );
   CU_ASSERT( array[1] == 2.0 + 2.0*I );
   CU_ASSERT( array[2] == 3.0 + 3.0*I );
   CU_ASSERT( array[3] == 4.0 + 4.0*I );

   cf_matvec_dispose( &cfm );
   free( array );

   return;
}

/**
   test_copy_as_array_4
*/

void test_copy_as_array_4( void )
{
   cd_matvec_t *cdm = NULL;
   complex128_t *array = NULL;

   cdm = cd_matvec_make_from_args( 1, 3, 3, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I );
   array = cd_matvec_copy_as_array( cdm );

   CU_ASSERT( cdm != NULL );
   CU_ASSERT( cd_matvec_is_row_vector( cdm ) == 1 );
   CU_ASSERT( array[0] == 1.0 + 1.0*I );
   CU_ASSERT( array[1] == 2.0 + 2.0*I );
   CU_ASSERT( array[2] == 3.0 + 3.0*I );

   cd_matvec_dispose( &cdm );
   free( array );

   cdm = cd_matvec_make_from_args( 3, 1, 3, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I );
   array = cd_matvec_copy_as_array( cdm );

   CU_ASSERT( cdm != NULL );
   CU_ASSERT( cd_matvec_is_column_vector( cdm ) == 1 );
   CU_ASSERT( array[0] == 1.0 + 1.0*I );
   CU_ASSERT( array[1] == 2.0 + 2.0*I );
   CU_ASSERT( array[2] == 3.0 + 3.0*I );

   cd_matvec_dispose( &cdm );
   free( array );

   cdm = cd_matvec_make_from_args( 2, 2, 4, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I, 4.0 + 4.0*I );
   array = cd_matvec_copy_as_array( cdm );

   CU_ASSERT( cdm != NULL );
   CU_ASSERT( array[0] == 1.0 + 1.0*I );
   CU_ASSERT( array[1] == 2.0 + 2.0*I );
   CU_ASSERT( array[2] == 3.0 + 3.0*I );
   CU_ASSERT( array[3] == 4.0 + 4.0*I );

   cd_matvec_dispose( &cdm );
   free( array );

   return;
}

int
add_test_copy_as_array( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_copy_as_array", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_copy_as_array_1
   add_test_to_suite( p_suite, test_copy_as_array_1, "test_copy_as_array_1" );

   // test_copy_as_array_2
   add_test_to_suite( p_suite, test_copy_as_array_2, "test_copy_as_array_2" );

   // test_copy_as_array_3
   add_test_to_suite( p_suite, test_copy_as_array_3, "test_copy_as_array_3" );

   // test_copy_as_array_4
   add_test_to_suite( p_suite, test_copy_as_array_4, "test_copy_as_array_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

