/**
 @file date_time_duration_test_make_dhms.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for date_time_duration_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for date_time_duration_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include "CUnit/Basic.h"

#include "Date_Time_Duration.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_dhms_1
*/

void test_make_dhms_1( void )
{
   date_time_duration_t *date_time_duration = NULL;
   
   date_time_duration = date_time_duration_make_dhms( 0, 1, 0, 0, 0 );
   
   CU_ASSERT( date_time_duration != NULL );
   
   CU_ASSERT( date_time_duration_duration_milliseconds( date_time_duration ) == 3600000L );
   CU_ASSERT( date_time_duration_is_definite( date_time_duration ) == 0 );
 
   date_time_duration_dispose( &date_time_duration );

   return;
}

int
add_test_make_dhms( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_dhms", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_dhms_1
   add_test_to_suite( p_suite, test_make_dhms_1, "test_make_dhms_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

