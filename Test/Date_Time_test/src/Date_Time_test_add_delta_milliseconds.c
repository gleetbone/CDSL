/**
 @file date_time_test_add_delta_milliseconds.c
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
   test_add_delta_milliseconds_1
*/

void test_add_delta_milliseconds_1( void )
{
   date_time_t *date_time = NULL;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   date_time_add_delta_milliseconds( date_time, 1 );
   
   CU_ASSERT( date_time != NULL );
   
   CU_ASSERT( date_time_millisecond( date_time ) == 5 );
 
   date_time_dispose( &date_time );
  
   return;
}

/**
   test_add_delta_milliseconds_2
*/

void test_add_delta_milliseconds_2( void )
{
   date_time_t *date_time = NULL;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   date_time_add_delta_milliseconds( date_time, -1 );
   
   CU_ASSERT( date_time != NULL );
   
   CU_ASSERT( date_time_millisecond( date_time ) == 3 );
 
   date_time_dispose( &date_time );
  
   return;
}

/**
   test_add_delta_milliseconds_3
*/

void test_add_delta_milliseconds_3( void )
{
   date_time_t *date_time = NULL;
   
   date_time = date_time_make( 2019, 12, 31, 23, 59, 59, 999 );
   date_time_add_delta_milliseconds( date_time, 2 );
   
   CU_ASSERT( date_time != NULL );
   
   CU_ASSERT( date_time_year( date_time ) == 2020 );
   CU_ASSERT( date_time_month( date_time ) == 1 );
   CU_ASSERT( date_time_day( date_time ) == 1 );
   CU_ASSERT( date_time_day_of_year( date_time ) == 1 );
   CU_ASSERT( date_time_hour_24( date_time ) == 0 );
   CU_ASSERT( date_time_minute( date_time ) == 0 );
   CU_ASSERT( date_time_second( date_time ) == 0 );
   CU_ASSERT( date_time_millisecond( date_time ) == 1 );
 
   date_time_dispose( &date_time );
  
   return;
}

/**
   test_add_delta_milliseconds_4
*/

void test_add_delta_milliseconds_4( void )
{
   date_time_t *date_time = NULL;
   
   date_time = date_time_make( -1, 12, 31, 23, 59, 59, 999 );
   date_time_add_delta_milliseconds( date_time, 2 );
   
   CU_ASSERT( date_time != NULL );
   
   CU_ASSERT( date_time_year( date_time ) == 1 );
   CU_ASSERT( date_time_month( date_time ) == 1 );
   CU_ASSERT( date_time_day( date_time ) == 1 );
   CU_ASSERT( date_time_day_of_year( date_time ) == 1 );
   CU_ASSERT( date_time_hour_24( date_time ) == 0 );
   CU_ASSERT( date_time_minute( date_time ) == 0 );
   CU_ASSERT( date_time_second( date_time ) == 0 );
   CU_ASSERT( date_time_millisecond( date_time ) == 1 );
 
   date_time_dispose( &date_time );
  
   return;
}

/**
   test_add_delta_milliseconds_5
*/

void test_add_delta_milliseconds_5( void )
{
   date_time_t *date_time = NULL;
   
   date_time = date_time_make( 1, 1, 1, 0, 0, 0, 1 );
   date_time_add_delta_milliseconds( date_time, -2 );
   
   CU_ASSERT( date_time != NULL );
   
   CU_ASSERT( date_time_year( date_time ) == -1 );
   CU_ASSERT( date_time_month( date_time ) == 12 );
   CU_ASSERT( date_time_day( date_time ) == 31 );
   CU_ASSERT( date_time_day_of_year( date_time ) == 366 );
   CU_ASSERT( date_time_hour_24( date_time ) == 23 );
   CU_ASSERT( date_time_minute( date_time ) == 59 );
   CU_ASSERT( date_time_second( date_time ) == 59 );
   CU_ASSERT( date_time_millisecond( date_time ) == 999 );
 
   date_time_dispose( &date_time );
  
   return;
}

/**
   test_add_delta_milliseconds_6
*/

void test_add_delta_milliseconds_6( void )
{
   date_time_t *date_time = NULL;
   
   date_time = date_time_make( 2000, 1, 1, 0, 0, 0, 1 );
   date_time_add_delta_milliseconds( date_time, -2 );
   
   CU_ASSERT( date_time != NULL );
   
   CU_ASSERT( date_time_year( date_time ) ==  1999 );
   CU_ASSERT( date_time_month( date_time ) == 12 );
   CU_ASSERT( date_time_day( date_time ) == 31 );
   CU_ASSERT( date_time_day_of_year( date_time ) == 365 );
   CU_ASSERT( date_time_hour_24( date_time ) == 23 );
   CU_ASSERT( date_time_minute( date_time ) == 59 );
   CU_ASSERT( date_time_second( date_time ) == 59 );
   CU_ASSERT( date_time_millisecond( date_time ) == 999 );
 
   date_time_dispose( &date_time );
  
   return;
}

/**
   test_add_delta_milliseconds_7
*/

void test_add_delta_milliseconds_7( void )
{
   date_time_t *date_time = NULL;
   
   date_time = date_time_make( 2000, 1, 1, 0, 0, 0, 1 );
   date_time_add_delta_milliseconds( date_time, 3600000 );
   
   CU_ASSERT( date_time != NULL );
   
   CU_ASSERT( date_time_year( date_time ) ==  2000 );
   CU_ASSERT( date_time_month( date_time ) == 1 );
   CU_ASSERT( date_time_day( date_time ) == 1 );
   CU_ASSERT( date_time_day_of_year( date_time ) == 1 );
   CU_ASSERT( date_time_hour_24( date_time ) == 1 );
   CU_ASSERT( date_time_minute( date_time ) == 0 );
   CU_ASSERT( date_time_second( date_time ) == 0 );
   CU_ASSERT( date_time_millisecond( date_time ) == 1 );
 
   date_time_dispose( &date_time );
  
   return;
}

int
add_test_add_delta_milliseconds( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_add_delta_milliseconds", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_add_delta_milliseconds_1
   add_test_to_suite( p_suite, test_add_delta_milliseconds_1, "test_add_delta_milliseconds_1" );

   // test_add_delta_milliseconds_2
   add_test_to_suite( p_suite, test_add_delta_milliseconds_2, "test_add_delta_milliseconds_2" );

   // test_add_delta_milliseconds_3
   add_test_to_suite( p_suite, test_add_delta_milliseconds_3, "test_add_delta_milliseconds_3" );

   // test_add_delta_milliseconds_4
   add_test_to_suite( p_suite, test_add_delta_milliseconds_4, "test_add_delta_milliseconds_4" );

   // test_add_delta_milliseconds_5
   add_test_to_suite( p_suite, test_add_delta_milliseconds_5, "test_add_delta_milliseconds_5" );

   // test_add_delta_milliseconds_6
   add_test_to_suite( p_suite, test_add_delta_milliseconds_6, "test_add_delta_milliseconds_6" );

   // test_add_delta_milliseconds_7
   add_test_to_suite( p_suite, test_add_delta_milliseconds_7, "test_add_delta_milliseconds_7" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

