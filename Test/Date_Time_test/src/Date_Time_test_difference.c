/**
 @file date_time_test_difference.c
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
   test_difference_1
*/

void test_difference_1( void )
{
   date_time_t *date_time = NULL;
   date_time_t *date_time_1 = NULL;
   int64_t diff = 0;
   
   date_time = date_time_make( 2020, 1, 1, 1, 2, 3, 4 );
   date_time_1 = date_time_make( 2020, 1, 1, 1, 2, 3, 5 );
   
   diff = date_time_difference( date_time, date_time_1 );
   
   CU_ASSERT( diff == 1L );
 
   date_time_dispose( &date_time );
   date_time_dispose( &date_time_1 );

   return;
}

/**
   test_difference_2
*/

void test_difference_2( void )
{
   date_time_t *date_time = NULL;
   date_time_t *date_time_1 = NULL;
   int64_t diff = 0;
   
   date_time = date_time_make( 2020, 1, 1, 1, 1, 1, 1 );
   date_time_1 = date_time_make( 2021, 1, 1, 1, 1, 1, 1 );
   
   diff = date_time_difference( date_time, date_time_1 );
   
   CU_ASSERT( diff == 31622400000L );
 
   date_time_dispose( &date_time );
   date_time_dispose( &date_time_1 );

   return;
}

/**
   test_difference_3
*/

void test_difference_3( void )
{
   date_time_t *date_time = NULL;
   date_time_t *date_time_1 = NULL;
   int64_t diff = 0;
   
   date_time = date_time_make( -1, 1, 1, 1, 1, 1, 1 );
   date_time_1 = date_time_make( 1, 1, 1, 1, 1, 1, 1 );
   
   diff = date_time_difference( date_time, date_time_1 );
   
   CU_ASSERT( diff == 31622400000L );
 
   date_time_dispose( &date_time );
   date_time_dispose( &date_time_1 );

   return;
}

/**
   test_difference_4
*/

void test_difference_4( void )
{
   date_time_t *date_time = NULL;
   date_time_t *date_time_1 = NULL;
   int64_t diff = 0;
   
   date_time = date_time_make( 2000, 1, 1, 1, 1, 1, 1 );
   date_time_1 = date_time_make( 1999, 1, 1, 1, 1, 1, 1 );
   
   diff = date_time_difference( date_time, date_time_1 );
   
   CU_ASSERT( diff == -31536000000L );
 
   date_time_dispose( &date_time );
   date_time_dispose( &date_time_1 );

   return;
}

int
add_test_difference( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_difference", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_difference_1
   add_test_to_suite( p_suite, test_difference_1, "test_difference_1" );

   // test_difference_2
   add_test_to_suite( p_suite, test_difference_2, "test_difference_2" );

   // test_difference_3
   add_test_to_suite( p_suite, test_difference_3, "test_difference_3" );

   // test_difference_4
   add_test_to_suite( p_suite, test_difference_4, "test_difference_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

