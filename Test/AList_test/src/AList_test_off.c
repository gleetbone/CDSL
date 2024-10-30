/**
 @file AList_test_off.c
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
   test_off_1
*/

void test_off_1( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   CU_ASSERT( i_alist_off( list ) == 1 );
   
   i_alist_dispose( &list );

   return;
}

/**
   test_off_2
*/

void test_off_2( void )
{
   i_alist_t *list = NULL;

   list = i_alist_make();
   
   CU_ASSERT( i_alist_off( list ) == 1 );
   
   i_alist_start( list );
   
   CU_ASSERT( i_alist_off( list ) == 1 );
   
   i_alist_put_last( list, 24 );
   
   CU_ASSERT( i_alist_off( list ) == 1 );
      
   i_alist_start( list );
   
   CU_ASSERT( i_alist_off( list ) == 0 );
   
   i_alist_dispose( &list );

   return;
}

/**
   test_off_3
*/

void test_off_3( void )
{
   s_alist_t *list = s_alist_make();
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   
   CU_ASSERT( s_alist_off( list ) == 1 );
   
   s_alist_start( list );
   
   CU_ASSERT( s_alist_off( list ) == 1 );
   
   s_alist_put_last( list, s1 );
   
   CU_ASSERT( s_alist_off( list ) == 1 );
      
   s_alist_start( list );
   
   CU_ASSERT( s_alist_off( list ) == 0 );
   
   s_alist_deep_dispose( &list );

   return;
}

int
add_test_off( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_off", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_off_1
   add_test_to_suite( p_suite, test_off_1, "test_off_1" );

   // test_off_2
   add_test_to_suite( p_suite, test_off_2, "test_off_2" );

   // test_off_3
   add_test_to_suite( p_suite, test_off_3, "test_off_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

