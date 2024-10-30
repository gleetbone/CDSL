/**
 @file Lsqline_test_is_equal.c
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
   test_is_equal_1
*/

void test_is_equal_1( void )
{
   lsqline_t *lsqline = NULL;
   lsqline_t *lsqline1 = NULL;
   
   lsqline = lsqline_make( 4 );
   
   CU_ASSERT( lsqline != NULL );

   lsqline1 = lsqline_make( 4 );
   
   CU_ASSERT( lsqline_is_equal( lsqline, lsqline1 ) == 1 );

   lsqline_dispose( &lsqline );
   lsqline_dispose( &lsqline1 );

   return;
}

/**
   test_is_equal_2
*/

void test_is_equal_2( void )
{
   lsqline_t *lsqline = NULL;
   lsqline_t *lsqline1 = NULL;
   
   lsqline = lsqline_make( 4 );
   lsqline_put( lsqline, 1.0, 1.0 );

   lsqline1 = lsqline_make( 4 );
   lsqline_put( lsqline1, 1.0, 1.0 );
   
   CU_ASSERT( lsqline_is_equal( lsqline, lsqline1 ) == 1 );

   lsqline_dispose( &lsqline );
   lsqline_dispose( &lsqline1 );

   return;
}

/**
   test_is_equal_3
*/

void test_is_equal_3( void )
{
   lsqline_t *lsqline = NULL;
   lsqline_t *lsqline1 = NULL;
   
   lsqline = lsqline_make( 5 );
   
   CU_ASSERT( lsqline != NULL );

   lsqline1 = lsqline_make( 5 );
   
   CU_ASSERT( lsqline_is_equal( lsqline, lsqline1 ) == 1 );

   lsqline_deep_dispose( &lsqline );
   lsqline_deep_dispose( &lsqline1 );

   return;
}

/**
   test_is_equal_4
*/

void test_is_equal_4( void )
{
   lsqline_t *lsqline = NULL;
   lsqline_t *lsqline1 = NULL;
   
   lsqline = lsqline_make( 4 );
   
   lsqline_put( lsqline, 1.0, 1.0 );
   lsqline_put( lsqline, 2.0, 2.0 );
   lsqline_put( lsqline, 1.1, 1.1 );
   lsqline_put( lsqline, 1.2, 1.2 );
   lsqline_put( lsqline, 1.3, 1.3 );
   lsqline_put( lsqline, 1.4, 1.4 );
   lsqline_put( lsqline, 1.5, 1.5 );
   lsqline_put( lsqline, 1.6, 1.6 );
   
   CU_ASSERT( lsqline != NULL );

   lsqline1 = lsqline_make( 4 );
   
   lsqline_put( lsqline1, 1.0, 1.0 );
   lsqline_put( lsqline1, 2.0, 2.0 );
   lsqline_put( lsqline1, 1.1, 1.1 );
   lsqline_put( lsqline1, 1.2, 1.2 );
   lsqline_put( lsqline1, 1.3, 1.3 );
   lsqline_put( lsqline1, 1.4, 1.4 );
   lsqline_put( lsqline1, 1.5, 1.5 );
   lsqline_put( lsqline1, 1.6, 1.6 );
   
   CU_ASSERT( lsqline_is_equal( lsqline, lsqline1 ) == 1 );

   lsqline_dispose( &lsqline );
   lsqline_dispose( &lsqline1 );

   return;
}

/**
   test_is_equal_5
*/

void test_is_equal_5( void )
{
   lsqline_t *lsqline = NULL;
   lsqline_t *lsqline1 = NULL;
   
   lsqline = lsqline_make( 4 );
   
   lsqline1 = lsqline_make( 5 );
   
   CU_ASSERT( lsqline_is_equal( lsqline, lsqline1 ) == 0 );

   lsqline_dispose( &lsqline );
   lsqline_dispose( &lsqline1 );

   return;
}

/**
   test_is_equal_6
*/

void test_is_equal_6( void )
{
   lsqline_t *lsqline = NULL;
   lsqline_t *lsqline1 = NULL;
   
   lsqline = lsqline_make( 4 );
   lsqline_put( lsqline, 1.0, 1.0 );
   
   lsqline1 = lsqline_make( 4 );
   lsqline_put( lsqline, 2.0, 2.0 );
   
   CU_ASSERT( lsqline_is_equal( lsqline, lsqline1 ) == 0 );

   lsqline_dispose( &lsqline );
   lsqline_dispose( &lsqline1 );

   return;
}

/**
   test_is_equal_7
*/

void test_is_equal_7( void )
{
   lsqline_t *lsqline = NULL;
   lsqline_t *lsqline1 = NULL;
   
   lsqline = lsqline_make( 4 );
   lsqline_put( lsqline, 1.0, 1.0 );
   lsqline_put( lsqline, 2.0, 2.0 );
   lsqline_put( lsqline, 3.0, 3.0 );
   lsqline_put( lsqline, 4.0, 4.0 );
   lsqline_compute( lsqline );
      
   lsqline1 = lsqline_make( 4 );
   lsqline_put( lsqline1, 1.0, 1.0 );
   lsqline_put( lsqline1, 2.0, 2.0 );
   lsqline_put( lsqline1, 3.0, 3.0 );
   lsqline_put( lsqline1, 4.0, 4.0 );
   
   CU_ASSERT( lsqline_is_equal( lsqline, lsqline1 ) == 0 );

   lsqline_dispose( &lsqline );
   lsqline_dispose( &lsqline1 );

   return;
}

/**
   test_is_equal_8
*/

void test_is_equal_8( void )
{
   lsqline_t *lsqline = NULL;
   lsqline_t *lsqline1 = NULL;
   
   lsqline = lsqline_make( 4 );
   lsqline_put( lsqline, 1.0, 1.0 );
   lsqline_put( lsqline, 2.0, 2.0 );
      
   lsqline1 = lsqline_make( 4 );
   lsqline_put( lsqline1, 1.0, 1.0 );
   lsqline_put( lsqline1, 2.0, 2.0 );
   lsqline_put( lsqline1, 3.0, 3.0 );
   lsqline_put( lsqline1, 4.0, 4.0 );
   lsqline_put( lsqline1, 5.0, 5.0 );
   lsqline_put( lsqline1, 6.0, 6.0 );
   
   CU_ASSERT( lsqline_is_equal( lsqline, lsqline1 ) == 0 );

   lsqline_dispose( &lsqline );
   lsqline_dispose( &lsqline1 );

   return;
}

/**
   test_is_equal_9
*/

void test_is_equal_9( void )
{
   lsqline_t *lsqline = NULL;
   lsqline_t *lsqline1 = NULL;
   
   lsqline = lsqline_make( 4 );
   lsqline_put( lsqline, 1.0, 1.0 );
   lsqline_put( lsqline, 2.0, 2.0 );
      
   lsqline1 = lsqline_make( 4 );
   lsqline_put( lsqline1, 1.0, 1.0 );
   lsqline_put( lsqline1, 2.0, 2.1 );
   
   CU_ASSERT( lsqline_is_equal( lsqline, lsqline1 ) == 0 );

   lsqline_dispose( &lsqline );
   lsqline_dispose( &lsqline1 );

   return;
}

/**
   test_is_equal_9a
*/

void test_is_equal_9a( void )
{
   lsqline_t *lsqline = NULL;
   lsqline_t *lsqline1 = NULL;
   
   lsqline = lsqline_make( 4 );
   lsqline_put( lsqline, 1.0, 1.0 );
   lsqline_put( lsqline, 2.0, 2.0 );
   lsqline_put( lsqline, 3.0, 3.0 );
   lsqline_put( lsqline, 4.0, 4.0 );
   lsqline_compute( lsqline );
      
   lsqline1 = lsqline_make( 4 );
   lsqline_put( lsqline1, 1.0, 1.0 );
   lsqline_put( lsqline1, 2.0, 2.0 );
   lsqline_put( lsqline1, 3.0, 3.0 );
   lsqline_put( lsqline1, 4.0, 4.0 );
   
   CU_ASSERT( lsqline_is_equal( lsqline, lsqline1 ) == 0 );

   lsqline_dispose( &lsqline );
   lsqline_dispose( &lsqline1 );

   return;
}

/**
   test_is_equal_10
*/

void test_is_equal_10( void )
{
   lsqline_t *lsqline = NULL;
   lsqline_t *lsqline1 = NULL;
   
   lsqline = lsqline_make( 4 );
   lsqline_put( lsqline, 1.0, 1.0 );
   lsqline_put( lsqline, 2.0, 2.0 );
   lsqline_put( lsqline, 3.0, 3.0 );
   lsqline_put( lsqline, 4.0, 4.0 );
   lsqline_compute( lsqline );
   lsqline_put( lsqline, 1.0, 1.0 );
      
   lsqline1 = lsqline_make( 4 );
   lsqline_put( lsqline1, 1.0, 1.0 );
   lsqline_put( lsqline1, 2.0, 2.0 );
   lsqline_put( lsqline1, 3.0, 3.0 );
   lsqline_put( lsqline1, 4.0, 4.0 );
   lsqline_compute( lsqline1 );
   lsqline_put( lsqline1, 1.0, 1.0 );
   
   CU_ASSERT( lsqline_is_equal( lsqline, lsqline1 ) == 1 );

   lsqline_dispose( &lsqline );
   lsqline_dispose( &lsqline1 );

   return;
}


int
add_test_is_equal( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_equal", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_equal_1
   add_test_to_suite( p_suite, test_is_equal_1, "test_is_equal_1" );

   // test_is_equal_2
   add_test_to_suite( p_suite, test_is_equal_2, "test_is_equal_2" );

   // test_is_equal_3
   add_test_to_suite( p_suite, test_is_equal_3, "test_is_equal_3" );

   // test_is_equal_4
   add_test_to_suite( p_suite, test_is_equal_4, "test_is_equal_4" );

   // test_is_equal_5
   add_test_to_suite( p_suite, test_is_equal_5, "test_is_equal_5" );

   // test_is_equal_6
   add_test_to_suite( p_suite, test_is_equal_6, "test_is_equal_6" );

   // test_is_equal_7
   add_test_to_suite( p_suite, test_is_equal_7, "test_is_equal_7" );

   // test_is_equal_8
   add_test_to_suite( p_suite, test_is_equal_8, "test_is_equal_8" );

   // test_is_equal_9
   add_test_to_suite( p_suite, test_is_equal_9, "test_is_equal_9" );

   // test_is_equal_9a
   add_test_to_suite( p_suite, test_is_equal_9a, "test_is_equal_9a" );

   // test_is_equal_10
   add_test_to_suite( p_suite, test_is_equal_10, "test_is_equal_10" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

