/**
 @file Matvec_test_trace.c
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
   test_trace_1
*/

void test_trace_1( void )
{
   f_matvec_t *fm = NULL;
   float32_t x = 0.0;

   fm = f_matvec_make_from_args( 2, 2, 4, 1.0, 2.0, 3.0, 4.0 );
   x = f_matvec_trace( fm );

   CU_ASSERT( fm != NULL );
   CU_ASSERT( x == 5.0 );

   f_matvec_dispose( &fm );

   fm = f_matvec_make_from_args( 2, 2, 4, 0.0, 2.0, 3.0, 4.0 );
   x = f_matvec_trace( fm );

   CU_ASSERT( fm != NULL );
   CU_ASSERT( x == 4.0 );

   f_matvec_dispose( &fm );

   return;
}

/**
   test_trace_2
*/
void test_trace_2( void )
{
   d_matvec_t *dm = NULL;
   float64_t x = 0.0;

   dm = d_matvec_make_from_args( 2, 2, 4, 1.0, 2.0, 3.0, 4.0 );;
   x = d_matvec_trace( dm );

   CU_ASSERT( dm != NULL );
   CU_ASSERT( x == 5.0 );

   d_matvec_dispose( &dm );

   return;
}


/**
   test_trace_3
*/

void test_trace_3( void )
{
   cf_matvec_t *cfm = NULL;
   complex64_t x = 0.0 + 0.0*I;

   cfm = cf_matvec_make_from_args( 2, 2, 4, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I, 4.0 + 4.0*I );
   x = cf_matvec_trace( cfm );

   CU_ASSERT( cfm != NULL );
   CU_ASSERT( x == 5.0 + 5.0*I );

   cf_matvec_dispose( &cfm );

   return;
}

/**
   test_trace_4
*/

void test_trace_4( void )
{
   cd_matvec_t *cdm = NULL;
   complex128_t x = 0.0 + 0.0*I;

   cdm = cd_matvec_make_from_args( 2, 2, 4, 1.0 + 1.0*I, 2.0 + 2.0*I, 3.0 + 3.0*I, 4.0 + 4.0*I );
   x = cd_matvec_trace( cdm );

   CU_ASSERT( cdm != NULL );
   CU_ASSERT( x == 5.0 + 5.0*I );

   cd_matvec_dispose( &cdm );

   return;
}

int
add_test_trace( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_trace", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_trace_1
   add_test_to_suite( p_suite, test_trace_1, "test_trace_1" );

   // test_trace_2
   add_test_to_suite( p_suite, test_trace_2, "test_trace_2" );

   // test_trace_3
   add_test_to_suite( p_suite, test_trace_3, "test_trace_3" );

   // test_trace_4
   add_test_to_suite( p_suite, test_trace_4, "test_trace_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

