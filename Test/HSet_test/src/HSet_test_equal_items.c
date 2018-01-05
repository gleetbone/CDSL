/**
 @file HSet_test_equal_items.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for HSet_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HSet_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_HSet.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_equal_items_1
*/

void test_equal_items_1( void )
{
   int flag = i_hset_equal_items( 0, 0 );
   
   CU_ASSERT( flag == 1 );
 
   return;
}

/**
   test_equal_items_2
*/

void test_equal_items_2( void )
{
   int flag = i_hset_equal_items( 24, 13 );
   
   CU_ASSERT( flag == 0 );
 
   return;
}

/**
   test_equal_items_3
*/

void test_equal_items_3( void )
{
   int flag = i_hset_equal_items( 13, 24 );
   
   CU_ASSERT( flag == 0 );
 
   return;
}

/**
   test_equal_items_4
*/

void test_equal_items_4( void )
{
   int flag = i_hset_equal_items( 24, 24 );
   
   CU_ASSERT( flag == 1 );
 
   return;
}

/**
   test_equal_items_5
*/

void test_equal_items_5( void )
{
   int flag = i_hset_equal_items( 13, 13 );
   
   CU_ASSERT( flag == 1 );
 
   return;
}

int
add_test_equal_items( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_equal_items", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_equal_items_1
   add_test_to_suite( p_suite, test_equal_items_1, "test_equal_items_1" );

   // test_equal_items_2
   add_test_to_suite( p_suite, test_equal_items_2, "test_equal_items_2" );

   // test_equal_items_3
   add_test_to_suite( p_suite, test_equal_items_3, "test_equal_items_3" );

   // test_equal_items_4
   add_test_to_suite( p_suite, test_equal_items_4, "test_equal_items_4" );

   // test_equal_items_5
   add_test_to_suite( p_suite, test_equal_items_5, "test_equal_items_5" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

