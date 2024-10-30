/**
 @file AList_test_item.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AList_item"
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
   test_item_1
*/

void test_item_1( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   i_alist_put_last( list, 24 );

   CU_ASSERT( i_alist_item( list, 0 ) == 24 );

   i_alist_dispose( &list );

   return;
}

/**
   test_item_2
*/

void test_item_2( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );
   i_alist_put_last( list, 7 );

   CU_ASSERT( i_alist_item( list, 0 ) == 24 );
   CU_ASSERT( i_alist_item( list, 1 ) == 13 );
   CU_ASSERT( i_alist_item( list, 2 ) == 7 );

   i_alist_dispose( &list );

   return;
}

/**
   test_item_3
*/

void test_item_3( void )
{
   s_alist_t *list = s_alist_make();
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "c" ); 
   
   s_alist_put_last( list, s1 );
   s_alist_put_last( list, s2 );
   s_alist_put_last( list, s3 );

   CU_ASSERT( string_is_equal( s_alist_item( list, 0 ), s1 ) == 1 );
   CU_ASSERT( string_is_equal( s_alist_item( list, 1 ), s2 ) == 1 );
   CU_ASSERT( string_is_equal( s_alist_item( list, 2 ), s3 ) == 1 );
   
   s_alist_deep_dispose( &list );

   return;
}

int
add_test_item( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_item", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_item_1
   add_test_to_suite( p_suite, test_item_1, "test_item_1" );

   // test_item_2
   add_test_to_suite( p_suite, test_item_2, "test_item_2" );

   // test_item_3
   add_test_to_suite( p_suite, test_item_3, "test_item_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

