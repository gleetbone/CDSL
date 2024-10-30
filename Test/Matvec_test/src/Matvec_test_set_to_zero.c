/**
 @file Matvec_test_set_to_zero.c
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
   test_set_to_zero_1
*/

void test_set_to_zero_1( void )
{
   f_matvec_t *fm = NULL;

   fm = f_matvec_make_from_args( 2, 2, 4, 1.0, 2.0, 3.0, 4.0 );
   f_matvec_set_to_zero( fm );

   CU_ASSERT( fm != NULL );
   CU_ASSERT( f_matvec_item( fm, 0, 0 ) == 0.0 );
   CU_ASSERT( f_matvec_item( fm, 0, 1 ) == 0.0 );
   CU_ASSERT( f_matvec_item( fm, 1, 0 ) == 0.0 );
   CU_ASSERT( f_matvec_item( fm, 1, 1 ) == 0.0 );

   f_matvec_dispose( &fm );

   return;
}

/**
   test_set_to_zero_2
*/
void test_set_to_zero_2( void )
{
   d_matvec_t *dm = NULL;

   dm = d_matvec_make_from_args( 2, 2, 4, 1.0, 2.0, 3.0, 4.0 );;
   d_matvec_set_to_zero( dm );

   CU_ASSERT( dm != NULL );
   CU_ASSERT( d_matvec_item( dm, 0, 0 ) == 0.0 );
   CU_ASSERT( d_matvec_item( dm, 0, 1 ) == 0.0 );
   CU_ASSERT( d_matvec_item( dm, 1, 0 ) == 0.0 );
   CU_ASSERT( d_matvec_item( dm, 1, 1 ) == 0.0 );

   d_matvec_dispose( &dm );

   return;
}


/**
   test_set_to_zero_3
*/

void test_set_to_zero_3( void )
{
   cf_matvec_t *cfm = NULL;

   cfm = cf_matvec_make_from_args( 2, 2, 4, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I, 4.0 + 4.0*I );
   cf_matvec_set_to_zero( cfm );

   CU_ASSERT( cfm != NULL );
   CU_ASSERT( cf_matvec_item( cfm, 0, 0 ) == 0.0 + 0.0*I );
   CU_ASSERT( cf_matvec_item( cfm, 0, 1 ) == 0.0 + 0.0*I );
   CU_ASSERT( cf_matvec_item( cfm, 1, 0 ) == 0.0 + 0.0*I );
   CU_ASSERT( cf_matvec_item( cfm, 1, 1 ) == 0.0 + 0.0*I );

   cf_matvec_dispose( &cfm );

   return;
}

/**
   test_set_to_zero_4
*/

void test_set_to_zero_4( void )
{
   cd_matvec_t *cdm = NULL;

   cdm = cd_matvec_make_from_args( 2, 2, 4, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I, 4.0 + 4.0*I );
   cd_matvec_set_to_zero( cdm );

   CU_ASSERT( cdm != NULL );
   CU_ASSERT( cd_matvec_item( cdm, 0, 0 ) == 0.0 + 0.0*I );
   CU_ASSERT( cd_matvec_item( cdm, 0, 1 ) == 0.0 + 0.0*I );
   CU_ASSERT( cd_matvec_item( cdm, 1, 0 ) == 0.0 + 0.0*I );
   CU_ASSERT( cd_matvec_item( cdm, 1, 1 ) == 0.0 + 0.0*I );

   cd_matvec_dispose( &cdm );

   return;
}

int
add_test_set_to_zero( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_set_to_zero", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_set_to_zero_1
   add_test_to_suite( p_suite, test_set_to_zero_1, "test_set_to_zero_1" );

   // test_set_to_zero_2
   add_test_to_suite( p_suite, test_set_to_zero_2, "test_set_to_zero_2" );

   // test_set_to_zero_3
   add_test_to_suite( p_suite, test_set_to_zero_3, "test_set_to_zero_3" );

   // test_set_to_zero_4
   add_test_to_suite( p_suite, test_set_to_zero_4, "test_set_to_zero_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

