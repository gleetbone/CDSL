/**
 @file BSearcher_test_is_equal.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSearcher_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSearcher_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_BSearcher.h"
#include "i_Searcher.h"
#include "i_Searcher.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_is_equal_1
*/

void test_is_equal_1( void )
{
   i_bsearcher_t *searcher = NULL;
   i_bsearcher_t *searcher1 = NULL;
   int32_t result = 0;

   searcher = i_bsearcher_make();
   CU_ASSERT( searcher != NULL );
   
   searcher1 = i_bsearcher_make();
   CU_ASSERT( searcher1 != NULL );
   
   result = i_bsearcher_is_equal( searcher, searcher1 );
   CU_ASSERT( result == 1 );
   
   i_bsearcher_dispose( &searcher );
   i_bsearcher_dispose( &searcher1 );
   CU_ASSERT( searcher == NULL );
   CU_ASSERT( searcher1 == NULL );
   
   return;
}

/**
   test_is_equal_1a
*/

void test_is_equal_1a( void )
{
   i_bsearcher_t *searcher = NULL;
   int32_t result = 0;

   searcher = i_bsearcher_make();
   CU_ASSERT( searcher != NULL );
   
   result = i_bsearcher_is_equal( searcher, searcher );
   CU_ASSERT( result == 1 );
   
   i_bsearcher_dispose( &searcher );
   CU_ASSERT( searcher == NULL );
   
   return;
}

/**
   test_is_equal_2
*/

void test_is_equal_2( void )
{
   i_bsearcher_t *searcher = NULL;
   i_bsearcher_t *searcher1 = NULL;
   int32_t result = 0;

   searcher = i_bsearcher_make();
   CU_ASSERT( searcher != NULL );
   
   searcher1 = i_bsearcher_make();
   CU_ASSERT( searcher != NULL );
   
   result = i_bsearcher_is_deep_equal( searcher, searcher1 );
   CU_ASSERT( result == 1 );
   
   
   i_bsearcher_deep_dispose( &searcher );
   i_bsearcher_deep_dispose( &searcher1 );
   CU_ASSERT( searcher == NULL );
   CU_ASSERT( searcher1 == NULL );
   
   return;
}

/**
   test_is_equal_2a
*/

void test_is_equal_2a( void )
{
   i_bsearcher_t *searcher = NULL;
   int32_t result = 0;

   searcher = i_bsearcher_make();
   CU_ASSERT( searcher != NULL );
   
   result = i_bsearcher_is_deep_equal( searcher, searcher );
   CU_ASSERT( result == 1 );
   
   
   i_bsearcher_deep_dispose( &searcher );
   CU_ASSERT( searcher == NULL );
   
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

