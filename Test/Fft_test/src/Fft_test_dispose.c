/**
 @file Fft_test_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Fft_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Fft_t

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

#include "cf_Fft.h"
#include "cd_Fft.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_dispose_1
*/

void test_dispose_1( void )
{
   cf_fft_t *cffft = NULL;
   cf_matvec_t *input = NULL;
   cf_matvec_t *output = NULL;
   f_matvec_t *psd = NULL;
   f_matvec_t *log_psd = NULL;
   f_matvec_t *phase = NULL;
   f_matvec_t *phase_degrees = NULL;

   cffft = cf_fft_make( 16 );

   CU_ASSERT( cffft != NULL );

   input = cf_fft_input( cffft );
   output = cf_fft_output( cffft );
   psd = cf_fft_psd( cffft );
   log_psd = cf_fft_log_psd( cffft );
   phase = cf_fft_phase( cffft );
   phase_degrees = cf_fft_phase_degrees( cffft );

   cf_fft_dispose( &cffft );

   cf_matvec_dispose( &input );
   cf_matvec_dispose( &output );
   f_matvec_dispose( &psd );
   f_matvec_dispose( &log_psd );
   f_matvec_dispose( &phase );
   f_matvec_dispose( &phase_degrees );

   return;
}

/**
   test_dispose_2
*/

void test_dispose_2( void )
{
   cd_fft_t *cdfft = NULL;
   cd_matvec_t *input = NULL;
   cd_matvec_t *output = NULL;
   d_matvec_t *psd = NULL;
   d_matvec_t *log_psd = NULL;
   d_matvec_t *phase = NULL;
   d_matvec_t *phase_degrees = NULL;

   cdfft = cd_fft_make( 16 );

   CU_ASSERT( cdfft != NULL );

   input = cd_fft_input( cdfft );
   output = cd_fft_output( cdfft );
   psd = cd_fft_psd( cdfft );
   log_psd = cd_fft_log_psd( cdfft );
   phase = cd_fft_phase( cdfft );
   phase_degrees = cd_fft_phase_degrees( cdfft );

   cd_fft_dispose( &cdfft );

   cd_matvec_dispose( &input );
   cd_matvec_dispose( &output );
   d_matvec_dispose( &psd );
   d_matvec_dispose( &log_psd );
   d_matvec_dispose( &phase );
   d_matvec_dispose( &phase_degrees );

   return;
}

int
add_test_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_dispose_1
   add_test_to_suite( p_suite, test_dispose_1, "test_dispose_1" );

   // test_dispose_2
   add_test_to_suite( p_suite, test_dispose_2, "test_dispose_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

