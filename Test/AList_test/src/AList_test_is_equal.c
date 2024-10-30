/**
 @file AList_test_is_equal.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AList_put_last"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AList_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_AList.h"
#include "s_AList.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_equal_1
*/

void test_is_equal_1( void )
{
   i_alist_t *list = NULL;
   i_alist_t *list1 = NULL;

   list = i_alist_make();
   list1 = i_alist_make();
   
   i_alist_put_last( list, 24 );
   i_alist_put_last( list1, 24 );

   CU_ASSERT( i_alist_is_equal( list, list1 ) == 1 );

   i_alist_dispose( &list );
   i_alist_dispose( &list1 );

   return;
}

/**
   test_is_equal_1a
*/

void test_is_equal_1a( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   
   i_alist_put_last( list, 24 );

   CU_ASSERT( i_alist_is_equal( list, list ) == 1 );

   i_alist_dispose( &list );

   return;
}

/**
   test_is_equal_2
*/

void test_is_equal_2( void )
{
   i_alist_t *list = NULL;
   i_alist_t *list1 = NULL;

   list = i_alist_make();
   list1 = i_alist_make();
   
   i_alist_put_last( list, 24 );
   i_alist_put_last( list1, 24 );

   CU_ASSERT( i_alist_is_deep_equal( list, list1 ) == 1 );

   i_alist_dispose( &list );
   i_alist_dispose( &list1 );

   return;
}

/**
   test_is_equal_3
*/

void test_is_equal_3( void )
{
   i_alist_t *list = NULL;
   i_alist_t *list1 = NULL;

   list = i_alist_make();
   list1 = i_alist_make();
   
   i_alist_put_last( list1, 24 );

   CU_ASSERT( i_alist_is_equal( list, list1 ) == 0 );

   i_alist_put_last( list, 23 );
   
   CU_ASSERT( i_alist_is_equal( list, list1 ) == 0 );

   i_alist_dispose( &list );
   i_alist_dispose( &list1 );

   return;
}

/**
   test_is_equal_4
*/

void test_is_equal_4( void )
{
   i_alist_t *list = NULL;
   i_alist_t *list1 = NULL;

   list = i_alist_make();
   list1 = i_alist_make();
   
   i_alist_put_last( list1, 24 );

   CU_ASSERT( i_alist_is_deep_equal( list, list1 ) == 0 );

   i_alist_put_last( list, 23 );
   
   CU_ASSERT( i_alist_is_deep_equal( list, list1 ) == 0 );

   i_alist_dispose( &list );
   i_alist_dispose( &list1 );

   return;
}

/**
   test_is_equal_4a
*/

void test_is_equal_4a( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   
   i_alist_put_last( list, 24 );

   CU_ASSERT( i_alist_is_deep_equal( list, list ) == 1 );

   i_alist_put_last( list, 23 );
   
   CU_ASSERT( i_alist_is_deep_equal( list, list ) == 1 );

   i_alist_dispose( &list );

   return;
}

/**
   test_is_equal_5
*/

void test_is_equal_5( void )
{
   s_alist_t *list = NULL;
   s_alist_t *list1 = NULL;
   s_alist_t *list2 = NULL;

   list = s_alist_make();
   list1 = s_alist_make();
   list2 = s_alist_make();
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "a" );
   
   s_alist_put_last( list, s1 );
   s_alist_put_last( list1, s1 );
   s_alist_put_last( list2, s2 );

   CU_ASSERT( s_alist_is_equal( list, list1 ) == 1 );
   CU_ASSERT( s_alist_is_equal( list, list2 ) == 0 );

   CU_ASSERT( s_alist_is_deep_equal( list, list1 ) == 1 );
   CU_ASSERT( s_alist_is_deep_equal( list, list2 ) == 1 );

   s_alist_deep_dispose( &list );
   s_alist_dispose( &list1 );
   s_alist_deep_dispose( &list2 );

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

   // test_is_equal_1a
   add_test_to_suite( p_suite, test_is_equal_1a, "test_is_equal_1a" );

   // test_is_equal_2
   add_test_to_suite( p_suite, test_is_equal_2, "test_is_equal_2" );

   // test_is_equal_3
   add_test_to_suite( p_suite, test_is_equal_3, "test_is_equal_3" );

   // test_is_equal_4
   add_test_to_suite( p_suite, test_is_equal_4, "test_is_equal_4" );

   // test_is_equal_4a
   add_test_to_suite( p_suite, test_is_equal_4a, "test_is_equal_4a" );

   // test_is_equal_5
   add_test_to_suite( p_suite, test_is_equal_5, "test_is_equal_5" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

