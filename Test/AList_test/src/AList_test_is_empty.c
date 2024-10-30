/**
 @file AList_test_is_empty.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AList_last"
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
   test_is_empty_1
*/

void test_is_empty_1( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   
   CU_ASSERT( i_alist_is_empty( list ) == 1 );

   i_alist_dispose( &list );

   return;
}

/**
   test_is_empty_2
*/

void test_is_empty_2( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   
   CU_ASSERT( i_alist_is_empty( list ) == 1 );
   
   i_alist_put_last( list, 24 );
   
   CU_ASSERT( i_alist_is_empty( list ) == 0 );
      
   i_alist_dispose( &list );

   return;
}

/**
   test_is_empty_3
*/

void test_is_empty_3( void )
{
   s_alist_t *list = s_alist_make();
   
   CU_ASSERT( s_alist_is_empty( list ) == 1 );
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   s_alist_put_last( list, s1 );
   
   CU_ASSERT( s_alist_is_empty( list ) == 0 );
      
   s_alist_deep_dispose( &list );

   return;
}

int
add_test_is_empty( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_empty", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_empty_1
   add_test_to_suite( p_suite, test_is_empty_1, "test_is_empty_1" );

   // test_is_empty_2
   add_test_to_suite( p_suite, test_is_empty_2, "test_is_empty_2" );

   // test_is_empty_3
   add_test_to_suite( p_suite, test_is_empty_3, "test_is_empty_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

