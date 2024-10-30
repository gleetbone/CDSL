/**
 @file AList_test_clone.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AList_make_from"
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
   test_clone_1
*/

void test_clone_1( void )
{
   i_alist_t *list = NULL;
   
   list = i_alist_make();
   
   i_alist_t *list_1 = i_alist_clone( list );
   
   CU_ASSERT( list_1 != NULL );
   CU_ASSERT( i_alist_count( list_1 ) == 0 );
   CU_ASSERT( i_alist_is_empty( list_1 ) == 1 );
  
   i_alist_dispose( &list );
   i_alist_dispose( &list_1 );

   return;
}

/**
   test_clone_2
*/

void test_clone_2( void )
{
   i_alist_t *list = NULL;
   
   list = i_alist_make();
   i_alist_put_last( list, 24 );
   
   i_alist_t *list_1 = i_alist_clone( list );
   
   CU_ASSERT( list_1 != NULL );
   CU_ASSERT( i_alist_count( list_1 ) == 1 );
   CU_ASSERT( i_alist_is_empty( list_1 ) == 0 );
   CU_ASSERT( i_alist_first( list_1 ) == 24 );
 
   i_alist_dispose( &list );
   i_alist_dispose( &list_1 );

   return;
}

/**
   test_clone_3
*/

void test_clone_3( void )
{
   s_alist_t *list = s_alist_make();
   s_alist_t *list_1 = NULL;
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   
   s_alist_put_last( list, s1 );
   
   list_1 = s_alist_clone( list );
   
   CU_ASSERT( list_1 != NULL );
   CU_ASSERT( s_alist_count( list_1 ) == 1 );
   CU_ASSERT( s_alist_is_empty( list_1 ) == 0 );
   CU_ASSERT( string_is_equal( s_alist_first( list_1 ), s1 ) == 1 );
 
   s_alist_dispose( &list_1 );
   s_alist_deep_dispose( &list );

   return;
}

int
add_test_clone( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_clone", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_clone_1
   add_test_to_suite( p_suite, test_clone_1, "test_clone_1" );

   // test_clone_2
   add_test_to_suite( p_suite, test_clone_2, "test_clone_2" );

   // test_clone_3
   add_test_to_suite( p_suite, test_clone_3, "test_clone_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

