/**
 @file AList_test_make_from.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for AList_make_from"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AList_make_from.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_AList.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_from_1
*/

void test_make_from_1( void )
{
   int_alist_t *list = NULL;
   
   list = int_alist_make();
   
   int_alist_t *list_1 = int_alist_make_from( list );
   
   CU_ASSERT( list_1 != NULL );
   CU_ASSERT( int_alist_count( list_1 ) == 0 );
   CU_ASSERT( int_alist_is_empty( list_1 ) == 1 );
  
   int_alist_dispose( list );
   int_alist_dispose( list_1 );

   return;
}

void test_make_from_2( void )
{
   int_alist_t *list = NULL;
   
   list = int_alist_make();
   int_alist_put_last( list, 24 );
   
   int_alist_t *list_1 = int_alist_make_from( list );
   
   CU_ASSERT( list_1 != NULL );
   CU_ASSERT( int_alist_count( list_1 ) == 1 );
   CU_ASSERT( int_alist_is_empty( list_1 ) == 0 );
   CU_ASSERT( int_alist_first( list_1 ) == 24 );
 
   int_alist_dispose( list );
   int_alist_dispose( list_1 );

   return;
}

int
add_test_make_from( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_from", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_from_1
   add_test_to_suite( p_suite, test_make_from_1, "test_make_from_1" );

   // test_make_from_2
   add_test_to_suite( p_suite, test_make_from_2, "test_make_from_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

