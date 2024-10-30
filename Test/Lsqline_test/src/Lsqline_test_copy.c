/**
 @file Lsqline_test_copy.c
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
   test_copy_1
*/

void test_copy_1( void )
{
   lsqline_t *lsqline = NULL;
   lsqline_t *lsqline1 = NULL;
   
   lsqline = lsqline_make( 4 );
   
   CU_ASSERT( lsqline != NULL );

   lsqline1 = lsqline_make( 4 );
   lsqline_copy( lsqline1, lsqline );
   
   CU_ASSERT( lsqline1 != NULL );
   CU_ASSERT( lsqline_capacity( lsqline1 ) == 4 );

   lsqline_dispose( &lsqline );
   lsqline_dispose( &lsqline1 );

   return;
}

/**
   test_copy_2
*/

void test_copy_2( void )
{
   lsqline_t *lsqline = NULL;
   lsqline_t *lsqline1 = NULL;
   
   lsqline = lsqline_make( 4 );
   
   lsqline_put( lsqline, 1.0, 1.0 );
   CU_ASSERT( lsqline != NULL );

   lsqline1 = lsqline_make( 4 );
   lsqline_copy( lsqline1, lsqline );
   
   CU_ASSERT( lsqline1 != NULL );
   CU_ASSERT( lsqline_capacity( lsqline1 ) == 4 );
   
   CU_ASSERT( lsqline_is_equal( lsqline, lsqline1 ) == 1 );

   lsqline_dispose( &lsqline );
   lsqline_dispose( &lsqline1 );

   return;
}

/**
   test_copy_3
*/

void test_copy_3( void )
{
   lsqline_t *lsqline = NULL;
   lsqline_t *lsqline1 = NULL;
   
   lsqline = lsqline_make( 4 );
   
   CU_ASSERT( lsqline != NULL );

   lsqline1 = lsqline_make( 5 );
   lsqline_copy( lsqline1, lsqline );
   
   CU_ASSERT( lsqline1 != NULL );
   CU_ASSERT( lsqline_capacity( lsqline1 ) == 4 );

   lsqline_deep_dispose( &lsqline );
   lsqline_deep_dispose( &lsqline1 );

   return;
}

/**
   test_copy_4
*/

void test_copy_4( void )
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

   lsqline1 = lsqline_make( 1 );
   lsqline_copy( lsqline1, lsqline );
   
   CU_ASSERT( lsqline1 != NULL );
   CU_ASSERT( lsqline_capacity( lsqline1 ) == 8 );
   
   CU_ASSERT( lsqline_is_equal( lsqline, lsqline1 ) == 1 );

   lsqline_dispose( &lsqline );
   lsqline_dispose( &lsqline1 );

   return;
}



int
add_test_copy( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_copy", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_copy_1
   add_test_to_suite( p_suite, test_copy_1, "test_copy_1" );

   // test_copy_2
   add_test_to_suite( p_suite, test_copy_2, "test_copy_2" );

   // test_copy_3
   add_test_to_suite( p_suite, test_copy_3, "test_copy_3" );

   // test_copy_4
   add_test_to_suite( p_suite, test_copy_4, "test_copy_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

