/**
 @file SList_test_clone.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for SList_clone"
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
   test_clone_1
*/

void test_clone_1( void )
{
   int_slist_t *list = NULL;
   
   list = int_slist_make();
   
   int_slist_t *list_1 = int_slist_clone( list );
   
   CU_ASSERT( list_1 != NULL );
   CU_ASSERT( int_slist_count( list_1 ) == 0 );
   CU_ASSERT( int_slist_is_empty( list_1 ) == 1 );
  
   int_slist_dispose( &list );
   int_slist_dispose( &list_1 );

   return;
}

/**
   test_clone_2
*/

void test_clone_2( void )
{
   int_slist_t *list = NULL;
   
   list = int_slist_make();
   int_slist_put_last( list, 24 );
   
   int_slist_t *list_1 = int_slist_clone( list );
   
   CU_ASSERT( list_1 != NULL );
   CU_ASSERT( int_slist_count( list_1 ) == 1 );
   CU_ASSERT( int_slist_is_empty( list_1 ) == 0 );
   CU_ASSERT( int_slist_first( list_1 ) == 24 );
 
   int_slist_dispose( &list );
   int_slist_dispose( &list_1 );

   return;
}

/**
   test_clone_3
*/

void test_clone_3( void )
{
   s_slist_t *list = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   
   list = s_slist_make();
   
   s_slist_put_last( list, s1 );
   
   s_slist_t *list_1 = s_slist_clone( list );
   
   CU_ASSERT( list_1 != NULL );
   CU_ASSERT( s_slist_count( list_1 ) == 1 );
   CU_ASSERT( s_slist_is_empty( list_1 ) == 0 );
   CU_ASSERT( s_slist_first( list_1 ) == s1 );
 
   s_slist_dispose( &list );
   s_slist_deep_dispose( &list_1 );

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

