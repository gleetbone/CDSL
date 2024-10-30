/**
 @file date_time_test_is_less_than_or_equal.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for date_time_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for date_time_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include "CUnit/Basic.h"

#include "Date_Time.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_less_than_or_equal_1
*/

void test_is_less_than_or_equal_1( void )
{
   date_time_t *date_time = NULL;
   date_time_t *date_time_1 = NULL;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   date_time_1 = date_time_make( 2020, 1, 1, 1, 2, 3, 5 );
   
   CU_ASSERT( date_time_is_less_than_or_equal( date_time, date_time_1 ) == 1 );
 
   date_time_dispose( &date_time );
   date_time_dispose( &date_time_1 );

   return;
}

/**
   test_is_less_than_or_equal_2
*/

void test_is_less_than_or_equal_2( void )
{
   date_time_t *date_time = NULL;
   date_time_t *date_time_1 = NULL;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   date_time_1 = date_time_make( 2020, 1, 1, 1, 2, 4, 4 );
   
   CU_ASSERT( date_time_is_less_than_or_equal( date_time, date_time_1 ) == 1 );
 
   date_time_dispose( &date_time );
   date_time_dispose( &date_time_1 );

   return;
}

/**
   test_is_less_than_or_equal_3
*/

void test_is_less_than_or_equal_3( void )
{
   date_time_t *date_time = NULL;
   date_time_t *date_time_1 = NULL;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   date_time_1 = date_time_make( 2020, 1, 1, 1, 3, 3, 4 );
   
   CU_ASSERT( date_time_is_less_than_or_equal( date_time, date_time_1 ) == 1 );
 
   date_time_dispose( &date_time );
   date_time_dispose( &date_time_1 );

   return;
}

/**
   test_is_less_than_or_equal_4
*/

void test_is_less_than_or_equal_4( void )
{
   date_time_t *date_time = NULL;
   date_time_t *date_time_1 = NULL;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   date_time_1 = date_time_make( 2020, 1, 1, 2, 2, 3, 4 );
   
   CU_ASSERT( date_time_is_less_than_or_equal( date_time, date_time_1 ) == 1 );
 
   date_time_dispose( &date_time );
   date_time_dispose( &date_time_1 );

   return;
}

/**
   test_is_less_than_or_equal_5
*/

void test_is_less_than_or_equal_5( void )
{
   date_time_t *date_time = NULL;
   date_time_t *date_time_1 = NULL;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   date_time_1 = date_time_make( 2020, 1, 2, 1, 2, 3, 4 );
   
   CU_ASSERT( date_time_is_less_than_or_equal( date_time, date_time_1 ) == 1 );
 
   date_time_dispose( &date_time );
   date_time_dispose( &date_time_1 );

   return;
}

/**
   test_is_less_than_or_equal_6
*/

void test_is_less_than_or_equal_6( void )
{
   date_time_t *date_time = NULL;
   date_time_t *date_time_1 = NULL;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   date_time_1 = date_time_make( 2020, 2, 1, 1, 2, 3, 4 );
   
   CU_ASSERT( date_time_is_less_than_or_equal( date_time, date_time_1 ) == 1 );
 
   date_time_dispose( &date_time );
   date_time_dispose( &date_time_1 );

   return;
}

/**
   test_is_less_than_or_equal_7
*/

void test_is_less_than_or_equal_7( void )
{
   date_time_t *date_time = NULL;
   date_time_t *date_time_1 = NULL;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   date_time_1 = date_time_make( 2021, 1, 1, 1, 2, 3, 4 );
   
   CU_ASSERT( date_time_is_less_than_or_equal( date_time, date_time_1 ) == 1 );
 
   date_time_dispose( &date_time );
   date_time_dispose( &date_time_1 );

   return;
}

/**
   test_is_less_than_or_equal_8
*/

void test_is_less_than_or_equal_8( void )
{
   date_time_t *date_time = NULL;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   
   CU_ASSERT( date_time_is_less_than_or_equal( date_time, date_time ) == 1 );
 
   date_time_dispose( &date_time );

   return;
}

int
add_test_is_less_than_or_equal( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_less_than_or_equal", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_less_than_or_equal_1
   add_test_to_suite( p_suite, test_is_less_than_or_equal_1, "test_is_less_than_or_equal_1" );

   // test_is_less_than_or_equal_2
   add_test_to_suite( p_suite, test_is_less_than_or_equal_2, "test_is_less_than_or_equal_2" );

   // test_is_less_than_or_equal_3
   add_test_to_suite( p_suite, test_is_less_than_or_equal_3, "test_is_less_than_or_equal_3" );

   // test_is_less_than_or_equal_4
   add_test_to_suite( p_suite, test_is_less_than_or_equal_4, "test_is_less_than_or_equal_4" );

   // test_is_less_than_or_equal_5
   add_test_to_suite( p_suite, test_is_less_than_or_equal_5, "test_is_less_than_or_equal_5" );

   // test_is_less_than_or_equal_6
   add_test_to_suite( p_suite, test_is_less_than_or_equal_6, "test_is_less_than_or_equal_6" );

   // test_is_less_than_or_equal_7
   add_test_to_suite( p_suite, test_is_less_than_or_equal_7, "test_is_less_than_or_equal_7" );

   // test_is_less_than_or_equal_8
   add_test_to_suite( p_suite, test_is_less_than_or_equal_8, "test_is_less_than_or_equal_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

