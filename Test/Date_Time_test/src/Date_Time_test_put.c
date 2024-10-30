/**
 @file date_time_test_put.c
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
   test_put_1
*/

void test_put_1( void )
{
   date_time_t *date_time = NULL;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   date_time_put( date_time, 2021, 1, 2, 2, 3, 4, 5 );
   
   CU_ASSERT( date_time != NULL );
   
   CU_ASSERT( date_time_year( date_time ) == 2021 );
   CU_ASSERT( date_time_month( date_time ) == 1 );
   CU_ASSERT( date_time_day( date_time ) == 2 );
   CU_ASSERT( date_time_day_of_year( date_time ) == 2 );
   CU_ASSERT( date_time_hour_24( date_time ) == 2 );
   CU_ASSERT( date_time_minute( date_time ) == 3 );
   CU_ASSERT( date_time_second( date_time ) == 4 );
   CU_ASSERT( date_time_millisecond( date_time ) == 5 );
 
   date_time_dispose( &date_time );
  
   return;
}

/**
   test_put_2
*/

void test_put_2( void )
{
   date_time_t *date_time = NULL;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   date_time_put( date_time, 2021, 12, 13, 0, 0, 0, 0 );
   
   CU_ASSERT( date_time != NULL );
   
   CU_ASSERT( date_time_year( date_time ) == 2021 );
   CU_ASSERT( date_time_month( date_time ) == 12 );
   CU_ASSERT( date_time_day( date_time ) == 13 );
   CU_ASSERT( date_time_day_of_year( date_time ) == 347 );
   CU_ASSERT( date_time_hour_24( date_time ) == 0 );
   CU_ASSERT( date_time_minute( date_time ) == 0 );
   CU_ASSERT( date_time_second( date_time ) == 0 );
   CU_ASSERT( date_time_millisecond( date_time ) == 0 );
 
   date_time_dispose( &date_time );
  
   return;
}

/**
   test_put_3
*/

void test_put_3( void )
{
   date_time_t *date_time = NULL;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   date_time_put( date_time, 2024, 12, 13, 0, 0, 0, 0 );
   
   CU_ASSERT( date_time != NULL );
   
   CU_ASSERT( date_time_year( date_time ) == 2024 );
   CU_ASSERT( date_time_month( date_time ) == 12 );
   CU_ASSERT( date_time_day( date_time ) == 13 );
   CU_ASSERT( date_time_day_of_year( date_time ) == 348 );
   CU_ASSERT( date_time_hour_24( date_time ) == 0 );
   CU_ASSERT( date_time_minute( date_time ) == 0 );
   CU_ASSERT( date_time_second( date_time ) == 0 );
   CU_ASSERT( date_time_millisecond( date_time ) == 0 );
 
   date_time_dispose( &date_time );
  
   return;
}

int
add_test_put( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_1
   add_test_to_suite( p_suite, test_put_1, "test_put_1" );

   // test_put_2
   add_test_to_suite( p_suite, test_put_2, "test_put_2" );

   // test_put_3
   add_test_to_suite( p_suite, test_put_3, "test_put_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

