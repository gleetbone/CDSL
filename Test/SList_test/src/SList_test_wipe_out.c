/**
 @file SList_test_wipe_out.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for SList_put"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for SList_t.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_SList.h"
#include "s_SList.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_wipe_out_1
*/

void test_wipe_out_1( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_wipe_out( list);

   CU_ASSERT( int_slist_count( list ) == 0 );

   int_slist_dispose( &list );

   return;
}

/**
   test_wipe_out_2
*/

void test_wipe_out_2( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );

   int_slist_wipe_out( list);

   CU_ASSERT( int_slist_count( list ) == 0 );

   int_slist_dispose( &list );

   return;
}

/**
   test_wipe_out_3
*/

void test_wipe_out_3( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   int_slist_wipe_out( list );

   CU_ASSERT( int_slist_count( list ) == 0 );

   int_slist_dispose( &list );

   return;
}

/**
   test_wipe_out_4
*/

void test_wipe_out_4( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 7 );

   int_slist_wipe_out( list );
   
   CU_ASSERT( int_slist_count( list ) == 0 );

   int_slist_dispose( &list );

   return;
}

/**
   test_wipe_out_5
*/

void test_wipe_out_5( void )
{
   s_slist_t *list = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   
   list = s_slist_make();
   
   s_slist_put_last( list, s1 );
   s_slist_put_last( list, s2 );
   s_slist_put_last( list, s3 );

   s_slist_wipe_out( list );
   
   CU_ASSERT( s_slist_count( list ) == 0 );

   s_slist_dispose( &list );
   string_deep_dispose( &s1 );
   string_deep_dispose( &s2 );
   string_deep_dispose( &s3 );

   return;
}

int
add_test_wipe_out( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_wipe_out", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_wipe_out_1
   add_test_to_suite( p_suite, test_wipe_out_1, "test_wipe_out_1" );

   // test_wipe_out_2
   add_test_to_suite( p_suite, test_wipe_out_2, "test_wipe_out_2" );

   // test_wipe_out_3
   add_test_to_suite( p_suite, test_wipe_out_3, "test_wipe_out_3" );

   // test_wipe_out_4
   add_test_to_suite( p_suite, test_wipe_out_4, "test_wipe_out_4" );

   // test_wipe_out_5
   add_test_to_suite( p_suite, test_wipe_out_5, "test_wipe_out_5" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

