/**
 @file date_time_duration_test_overlap.c
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
   test_overlap_1
*/

void test_overlap_1( void )
{
   date_time_t *start_dt = NULL;
   date_time_t *end_dt = NULL;
   date_time_duration_t *date_time_duration = NULL;
   date_time_duration_t *date_time_duration_1 = NULL;
   date_time_duration_t *dtd = NULL;
   
   date_time_duration = date_time_duration_make_dhms(  1, 0, 0, 0, 0 );
   
   start_dt = date_time_make( 2020, 2, 1, 0, 0, 0, 0 );
   end_dt = date_time_make( 2020, 2, 2, 0, 0, 0, 0 );
   date_time_duration_1 = date_time_duration_make_start_end( start_dt, end_dt );
   date_time_dispose( &start_dt );
   date_time_dispose( &end_dt );
   
   dtd = date_time_duration_overlap( date_time_duration, date_time_duration_1 );   
   CU_ASSERT( dtd == NULL );
   
   if ( dtd != NULL )
   {
      date_time_duration_dispose( &dtd );
   }
   
   date_time_duration_dispose( &date_time_duration );
   date_time_duration_dispose( &date_time_duration_1 );

   return;
}

/**
   test_overlap_2
*/

void test_overlap_2( void )
{
   date_time_t *start_dt = NULL;
   date_time_t *end_dt = NULL;
   date_time_duration_t *date_time_duration = NULL;
   date_time_duration_t *date_time_duration_1 = NULL;
   date_time_duration_t *dtd = NULL;
   
   start_dt = date_time_make( 2020, 1, 1, 0, 0, 0, 0 );
   end_dt = date_time_make( 2020, 1, 2, 0, 0, 0, 0 );
   date_time_duration = date_time_duration_make_start_end( start_dt, end_dt );
   date_time_deep_dispose( &start_dt );
   date_time_deep_dispose( &end_dt );
   
   start_dt = date_time_make( 2020, 2, 1, 0, 0, 0, 0 );
   end_dt = date_time_make( 2020, 2, 2, 0, 0, 0, 0 );
   date_time_duration_1 = date_time_duration_make_start_end( start_dt, end_dt );
   date_time_dispose( &start_dt );
   date_time_dispose( &end_dt );
   
   dtd = date_time_duration_overlap( date_time_duration, date_time_duration_1 );   
   CU_ASSERT( dtd == NULL );
   
   if ( dtd != NULL )
   {
      date_time_duration_dispose( &dtd );
   }
   
   date_time_duration_dispose( &date_time_duration );
   date_time_duration_dispose( &date_time_duration_1 );

   return;
}

/**
   test_overlap_3
*/

void test_overlap_3( void )
{
   date_time_t *start_dt = NULL;
   date_time_t *end_dt = NULL;
   date_time_duration_t *date_time_duration = NULL;
   date_time_duration_t *date_time_duration_1 = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt = NULL;
   
   start_dt = date_time_make( 2020, 1, 1, 0, 0, 0, 0 );
   end_dt = date_time_make( 2020, 1, 4, 0, 0, 0, 0 );
   date_time_duration = date_time_duration_make_start_end( start_dt, end_dt );
   date_time_deep_dispose( &start_dt );
   date_time_deep_dispose( &end_dt );
   
   start_dt = date_time_make( 2020, 1, 2, 0, 0, 0, 0 );
   end_dt = date_time_make( 2020, 1, 3, 0, 0, 0, 0 );
   date_time_duration_1 = date_time_duration_make_start_end( start_dt, end_dt );
   date_time_dispose( &start_dt );
   date_time_dispose( &end_dt );
   
   dtd = date_time_duration_overlap( date_time_duration, date_time_duration_1 );   
   CU_ASSERT( dtd != NULL );
   
   dt = date_time_duration_start( dtd );
   CU_ASSERT( date_time_day( dt ) == 2 );
   date_time_deep_dispose( &dt );
   
   dt = date_time_duration_end( dtd );
   CU_ASSERT( date_time_day( dt ) == 3 );
   date_time_deep_dispose( &dt );
   
   if ( dtd != NULL )
   {
      date_time_duration_dispose( &dtd );
   }
   
   date_time_duration_dispose( &date_time_duration );
   date_time_duration_dispose( &date_time_duration_1 );

   return;
}

/**
   test_overlap_4
*/

void test_overlap_4( void )
{
   date_time_t *start_dt = NULL;
   date_time_t *end_dt = NULL;
   date_time_duration_t *date_time_duration = NULL;
   date_time_duration_t *date_time_duration_1 = NULL;
   date_time_duration_t *dtd = NULL;
   date_time_t *dt = NULL;
   
   start_dt = date_time_make( 2020, 1, 2, 0, 0, 0, 0 );
   end_dt = date_time_make( 2020, 1, 3, 0, 0, 0, 0 );
   date_time_duration = date_time_duration_make_start_end( start_dt, end_dt );
   date_time_deep_dispose( &start_dt );
   date_time_deep_dispose( &end_dt );
   
   start_dt = date_time_make( 2020, 1, 1, 0, 0, 0, 0 );
   end_dt = date_time_make( 2020, 1, 4, 0, 0, 0, 0 );
   date_time_duration_1 = date_time_duration_make_start_end( start_dt, end_dt );
   date_time_dispose( &start_dt );
   date_time_dispose( &end_dt );
   
   dtd = date_time_duration_overlap( date_time_duration, date_time_duration_1 );   
   CU_ASSERT( dtd != NULL );
   
   dt = date_time_duration_start( dtd );
   CU_ASSERT( date_time_day( dt ) == 2 );
   date_time_deep_dispose( &dt );
   
   dt = date_time_duration_end( dtd );
   CU_ASSERT( date_time_day( dt ) == 3 );
   date_time_deep_dispose( &dt );
   
   if ( dtd != NULL )
   {
      date_time_duration_dispose( &dtd );
   }
   
   date_time_duration_dispose( &date_time_duration );
   date_time_duration_dispose( &date_time_duration_1 );

   return;
}

int
add_test_overlap( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_overlap", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_overlap_1
   add_test_to_suite( p_suite, test_overlap_1, "test_overlap_1" );

   // test_overlap_2
   add_test_to_suite( p_suite, test_overlap_2, "test_overlap_2" );

   // test_overlap_3
   add_test_to_suite( p_suite, test_overlap_3, "test_overlap_3" );

   // test_overlap_4
   add_test_to_suite( p_suite, test_overlap_4, "test_overlap_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

