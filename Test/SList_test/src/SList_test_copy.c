/**
 @file SList_test_copy.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for SList_put_last"
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
   test_copy_1
*/

void test_copy_1( void )
{
   int_slist_t *list = NULL;
   int_slist_t *list1 = NULL;

   list = int_slist_make();
   list1 = int_slist_make();
   
   int_slist_put_last( list, 24 );

   int_slist_copy( list, list1 );
   CU_ASSERT( int_slist_is_equal( list, list1 ) == 1 );

   int_slist_dispose( &list );
   int_slist_dispose( &list1 );

   return;
}

/**
   test_copy_1a
*/

void test_copy_1a( void )
{
   int_slist_t *list = NULL;
   int_slist_t *list1 = NULL;

   list = int_slist_make();
   list1 = int_slist_make();
   
   int_slist_put_last( list1, 24 );

   int_slist_copy( list, list1 );
   CU_ASSERT( int_slist_is_equal( list, list1 ) == 1 );

   int_slist_dispose( &list );
   int_slist_dispose( &list1 );

   return;
}

/**
   test_copy_2
*/

void test_copy_2( void )
{
   int_slist_t *list = NULL;
   int_slist_t *list1 = NULL;

   list = int_slist_make();
   list1 = int_slist_make();
   
   int_slist_put_last( list1, 24 );

   int_slist_deep_copy( list, list1 );
   CU_ASSERT( int_slist_is_deep_equal( list, list1 ) == 1 );

   int_slist_dispose( &list );
   int_slist_dispose( &list1 );

   return;
}

/**
   test_copy_2a
*/

void test_copy_2a( void )
{
   int_slist_t *list = NULL;
   int_slist_t *list1 = NULL;

   list = int_slist_make();
   list1 = int_slist_make();
   
   int_slist_put_last( list, 24 );

   int_slist_deep_copy( list, list1 );
   CU_ASSERT( int_slist_is_deep_equal( list, list1 ) == 1 );

   int_slist_dispose( &list );
   int_slist_dispose( &list1 );

   return;
}

/**
   test_copy_3
*/

void test_copy_3( void )
{
   s_slist_t *list = s_slist_make();
   s_slist_t *list1 = s_slist_make();

   string_t *s1 = string_make_from_cstring( "a" ); 
   
   s_slist_put_last( list1, s1 );

   s_slist_copy( list, list1 );
   CU_ASSERT( s_slist_is_equal( list, list1 ) == 1 );
   CU_ASSERT( s_slist_is_deep_equal( list, list1 ) == 1 );

   s_slist_wipe_out( list );
   
   s_slist_deep_copy( list, list1 );
   CU_ASSERT( s_slist_is_equal( list, list1 ) == 0 );
   CU_ASSERT( s_slist_is_deep_equal( list, list1 ) == 1 );

   s_slist_deep_dispose( &list );
   s_slist_deep_dispose( &list1 );

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

   // test_copy_1a
   add_test_to_suite( p_suite, test_copy_1a, "test_copy_1a" );

   // test_copy_2
   add_test_to_suite( p_suite, test_copy_2, "test_copy_2" );

   // test_copy_2a
   add_test_to_suite( p_suite, test_copy_2a, "test_copy_2a" );

   // test_copy_3
   add_test_to_suite( p_suite, test_copy_3, "test_copy_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

