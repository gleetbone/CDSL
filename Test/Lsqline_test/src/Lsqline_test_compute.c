/**
 @file Lsqline_test_compute.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for raw_buffer_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for raw_buffer_t.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "Lsqline.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );


/**
   test_compute_1
*/

void test_compute_1( void )
{
   lsqline_t *lsqline = NULL;
   
   lsqline = lsqline_make( 4 );
   
   lsqline_put( lsqline, 1.0, 1.0 );
   lsqline_put( lsqline, 2.0, 2.0 );
   lsqline_put( lsqline, 3.0, 3.0 );
   lsqline_put( lsqline, 4.0, 4.0 );

   lsqline_compute( lsqline );
   
   CU_ASSERT( lsqline_is_output_valid( lsqline ) == 1 );
   
   CU_ASSERT_DOUBLE_EQUAL( lsqline_slope( lsqline ), 1.0, 0.000001 );
   CU_ASSERT_DOUBLE_EQUAL( lsqline_y_intercept( lsqline ), 0.0, 0.000001 );
   CU_ASSERT_DOUBLE_EQUAL( lsqline_fit( lsqline ), 0.0, 0.000001 );
   
   lsqline_dispose( &lsqline );

   return;
}

/**
   test_compute_2
*/

void test_compute_2( void )
{
   lsqline_t *lsqline = NULL;
   
   lsqline = lsqline_make( 4 );
   
   lsqline_put( lsqline, 1.0, 1.0 );
   lsqline_put( lsqline, 2.0, 2.0 );
   lsqline_put( lsqline, 3.0, 3.0 );
   lsqline_put( lsqline, 4.0, 4.1 );

   lsqline_compute( lsqline );
   
   CU_ASSERT( lsqline_is_output_valid( lsqline ) == 1 );
   
   CU_ASSERT_DOUBLE_EQUAL( lsqline_slope( lsqline ), 1.03, 0.000001 );
   CU_ASSERT_DOUBLE_EQUAL( lsqline_y_intercept( lsqline ), -0.05, 0.000001 );
   CU_ASSERT_DOUBLE_EQUAL( lsqline_fit( lsqline ), 0.002997, 0.000001 );
   
   lsqline_dispose( &lsqline );

   return;
}

/**
   test_compute_3
*/

void test_compute_3( void )
{
   lsqline_t *lsqline = NULL;
   
   lsqline = lsqline_make( 4 );
   
   lsqline_put( lsqline, 1.0, 1.1 );
   
   lsqline_compute( lsqline );
   CU_ASSERT( lsqline_is_output_valid( lsqline ) == 0 );
   
   lsqline_put( lsqline, 2.0, 2.0 );
   lsqline_put( lsqline, 3.0, 3.0 );
   lsqline_put( lsqline, 4.0, 4.0 );
   lsqline_put( lsqline, 5.0, 5.0 );

   lsqline_compute( lsqline );
   
   CU_ASSERT( lsqline_is_output_valid( lsqline ) == 1 );
   
   CU_ASSERT_DOUBLE_EQUAL( lsqline_slope( lsqline ), 1.0, 0.000001 );
   CU_ASSERT_DOUBLE_EQUAL( lsqline_y_intercept( lsqline ), 0.0, 0.000001 );
   CU_ASSERT_DOUBLE_EQUAL( lsqline_fit( lsqline ), 0.0, 0.000001 );
   
   lsqline_dispose( &lsqline );

   return;
}

/**
   test_compute_4
*/

void test_compute_4( void )
{
   lsqline_t *lsqline = NULL;
   
   lsqline = lsqline_make( 4 );
   
   lsqline_put( lsqline, 1.0, 1.0 );
   lsqline_put( lsqline, 2.0, 2.0 );
   lsqline_put( lsqline, 3.0, 3.0 );
   lsqline_put( lsqline, 4.0, 4.0 );
   lsqline_put( lsqline, 5.0, 5.0 );
                                       
   lsqline_put( lsqline, 9.0, 9.0 );
   lsqline_put( lsqline, 6.0, 6.0 );
   lsqline_put( lsqline, 7.0, 7.0 );
   lsqline_put( lsqline, 8.0, 8.0 );

   lsqline_compute( lsqline );
   
   CU_ASSERT( lsqline_is_output_valid( lsqline ) == 1 );
   
   CU_ASSERT_DOUBLE_EQUAL( lsqline_slope( lsqline ), 1.0, 0.000001 );
   CU_ASSERT_DOUBLE_EQUAL( lsqline_y_intercept( lsqline ), 0.0, 0.000001 );
   CU_ASSERT_DOUBLE_EQUAL( lsqline_fit( lsqline ), 0.0, 0.000001 );
   
   lsqline_dispose( &lsqline );

   return;
}

/**
   test_compute_5
*/

void test_compute_5( void )
{
   lsqline_t *lsqline = NULL;
   
   lsqline = lsqline_make( 4 );
   
   lsqline_put( lsqline, 1.0, 1.0 );

   lsqline_compute( lsqline );
   
   CU_ASSERT( lsqline_is_output_valid( lsqline ) == 0 );
      
   lsqline_dispose( &lsqline );

   return;
}



int
add_test_compute( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_compute", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_compute_1
   //add_test_to_suite( p_suite, test_compute_1, "test_compute_1" );
   
   // test_compute_2
   //add_test_to_suite( p_suite, test_compute_2, "test_compute_2" );

   // test_compute_3
   //add_test_to_suite( p_suite, test_compute_3, "test_compute_3" );

   // test_compute_4
   add_test_to_suite( p_suite, test_compute_4, "test_compute_4" );

   // test_compute_5
   add_test_to_suite( p_suite, test_compute_5, "test_compute_5" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

