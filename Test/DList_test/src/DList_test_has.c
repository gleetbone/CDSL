/**
 @file DList_test_has.c
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

/**
   test_has_1
*/

void test_has_1( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   
   i_dlist_put_last( list, 24 );
   i_dlist_put_last( list, 13 );

   CU_ASSERT( i_dlist_has( list, 17 ) == 0 );
   CU_ASSERT( i_dlist_has( list, 24 ) == 1 );
   CU_ASSERT( i_dlist_has( list, 13 ) == 1 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_has_2
*/

void test_has_2( void )
{
   i_dlist_t *list = NULL;

   list = i_dlist_make();
   i_dlist_put_last( list, 24 );
   i_dlist_put_last( list, 13 );
   i_dlist_put_last( list, 7 );

   CU_ASSERT( i_dlist_has( list, 17 ) == 0 );
   CU_ASSERT( i_dlist_has( list, 24 ) == 1 );
   CU_ASSERT( i_dlist_has( list, 13 ) == 1 );
   CU_ASSERT( i_dlist_has( list, 7 ) == 1 );
   
   i_dlist_dispose( &list );

   return;
}

/**
   test_has_3
*/

void test_has_3( void )
{
   s_dlist_t *list = s_dlist_make();
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "c" ); 
   string_t *s4 = string_make_from_cstring( "a" ); 
   
   s_dlist_put_last( list, s1 );
   s_dlist_put_last( list, s2 );
   s_dlist_put_last( list, s3 );

   CU_ASSERT( s_dlist_has( list, s1 ) == 1 );
   CU_ASSERT( s_dlist_has( list, s2 ) == 1 );
   CU_ASSERT( s_dlist_has( list, s3 ) == 1 );
   CU_ASSERT( s_dlist_has( list, s4 ) == 0 );
   
   string_deep_dispose( &s4 );
   s_dlist_deep_dispose( &list );

   return;
}

int
add_test_has( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_has", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_has_1
   add_test_to_suite( p_suite, test_has_1, "test_has_1" );

   // test_has_2
   add_test_to_suite( p_suite, test_has_2, "test_has_2" );

   // test_has_3
   add_test_to_suite( p_suite, test_has_3, "test_has_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

