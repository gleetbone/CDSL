/**
 @file DList_test_has_eq_fn.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for DList_forth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for DList_t.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_DList.h"
#include "s_DList.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

static int32_t is_equal_int( int32_t i1, int32_t i2 )
{
   return ( i1 == i2 );
}

static int32_t is_equal_string( string_t *s1, string_t *s2 )
{
   return ( string_is_equal( s1, s2 ) );
}

/**
   test_has_eq_fn_1
*/

void test_has_eq_fn_1( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   
   i_dlist_put_last( list, 24 );
   i_dlist_put_last( list, 13 );

   CU_ASSERT( i_dlist_has_eq_fn( list, 17, is_equal_int ) == 0 );
   CU_ASSERT( i_dlist_has_eq_fn( list, 24, is_equal_int ) == 1 );
   CU_ASSERT( i_dlist_has_eq_fn( list, 13, is_equal_int ) == 1 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_has_eq_fn_2
*/

void test_has_eq_fn_2( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   i_dlist_put_last( list, 24 );
   i_dlist_put_last( list, 13 );
   i_dlist_put_last( list, 7 );

   CU_ASSERT( i_dlist_has_eq_fn( list, 17, is_equal_int ) == 0 );
   CU_ASSERT( i_dlist_has_eq_fn( list, 24, is_equal_int ) == 1 );
   CU_ASSERT( i_dlist_has_eq_fn( list, 13, is_equal_int ) == 1 );
   CU_ASSERT( i_dlist_has_eq_fn( list, 7, is_equal_int ) == 1 );
   
   i_dlist_dispose( &list );

   return;
}

/**
   test_has_eq_fn_3
*/

void test_has_eq_fn_3( void )
{
   s_dlist_t *list = s_dlist_make();
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "c" ); 
   string_t *s4 = string_make_from_cstring( "a" ); 
   
   s_dlist_put_last( list, s1 );
   s_dlist_put_last( list, s2 );
   s_dlist_put_last( list, s3 );

   CU_ASSERT( s_dlist_has_eq_fn( list, s1, is_equal_string ) == 1 );
   CU_ASSERT( s_dlist_has_eq_fn( list, s2, is_equal_string ) == 1 );
   CU_ASSERT( s_dlist_has_eq_fn( list, s3, is_equal_string ) == 1 );
   CU_ASSERT( s_dlist_has_eq_fn( list, s4, is_equal_string ) == 1 );
   
   string_deep_dispose( &s4 );
   s_dlist_deep_dispose( &list );

   return;
}

int
add_test_has_eq_fn( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_has_eq_fn", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_has_eq_fn_1
   add_test_to_suite( p_suite, test_has_eq_fn_1, "test_has_eq_fn_1" );

   // test_has_eq_fn_2
   add_test_to_suite( p_suite, test_has_eq_fn_2, "test_has_eq_fn_2" );

   // test_has_eq_fn_3
   add_test_to_suite( p_suite, test_has_eq_fn_3, "test_has_eq_fn_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

