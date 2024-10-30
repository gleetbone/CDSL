/**
 @file SelSorter_test_is_equal.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for SelSorter_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for SelSorter_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_SelSorter.h"
#include "i_Sorter.h"
#include "i_Sorter.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_equal_1
*/

void test_is_equal_1( void )
{
   i_selsorter_t *sorter = NULL;
   i_selsorter_t *sorter1 = NULL;
   int32_t result = 0;

   sorter = i_selsorter_make();
   CU_ASSERT( sorter != NULL );
   
   sorter1 = i_selsorter_make();
   CU_ASSERT( sorter1 != NULL );
   
   result = i_selsorter_is_equal( sorter, sorter1 );
   CU_ASSERT( result == 1 );
   
   i_selsorter_dispose( &sorter );
   i_selsorter_dispose( &sorter1 );
   CU_ASSERT( sorter == NULL );
   CU_ASSERT( sorter1 == NULL );
   
   return;
}

/**
   test_is_equal_1a
*/

void test_is_equal_1a( void )
{
   i_selsorter_t *sorter = NULL;
   int32_t result = 0;

   sorter = i_selsorter_make();
   CU_ASSERT( sorter != NULL );
   
   result = i_selsorter_is_equal( sorter, sorter );
   CU_ASSERT( result == 1 );
   
   i_selsorter_dispose( &sorter );
   CU_ASSERT( sorter == NULL );
   
   return;
}

/**
   test_is_equal_2
*/

void test_is_equal_2( void )
{
   i_selsorter_t *sorter = NULL;
   i_selsorter_t *sorter1 = NULL;
   int32_t result = 0;

   sorter = i_selsorter_make();
   CU_ASSERT( sorter != NULL );
   
   sorter1 = i_selsorter_make();
   CU_ASSERT( sorter != NULL );
   
   result = i_selsorter_is_deep_equal( sorter, sorter1 );
   CU_ASSERT( result == 1 );
   
   
   i_selsorter_deep_dispose( &sorter );
   i_selsorter_deep_dispose( &sorter1 );
   CU_ASSERT( sorter == NULL );
   CU_ASSERT( sorter1 == NULL );
   
   return;
}

/**
   test_is_equal_2a
*/

void test_is_equal_2a( void )
{
   i_selsorter_t *sorter = NULL;
   int32_t result = 0;

   sorter = i_selsorter_make();
   CU_ASSERT( sorter != NULL );
   
   result = i_selsorter_is_deep_equal( sorter, sorter );
   CU_ASSERT( result == 1 );
   
   
   i_selsorter_deep_dispose( &sorter );
   CU_ASSERT( sorter == NULL );
   
   return;
}

int
add_test_is_equal( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_is_equal", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_is_equal_1
   add_test_to_suite( p_suite, test_is_equal_1, "test_is_equal_1" );

   // test_is_equal_1a
   add_test_to_suite( p_suite, test_is_equal_1a, "test_is_equal_1a" );

   // test_is_equal_2
   add_test_to_suite( p_suite, test_is_equal_2, "test_is_equal_2" );

   // test_is_equal_2a
   add_test_to_suite( p_suite, test_is_equal_2a, "test_is_equal_2a" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

