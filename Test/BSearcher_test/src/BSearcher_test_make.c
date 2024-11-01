/**
 @file BSearcher_test_make.c
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

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_1
*/

void test_make_1( void )
{
   i_bsearcher_t *searcher = NULL;

   searcher = i_bsearcher_make();
   CU_ASSERT( searcher != NULL );
   
   i_bsearcher_dispose( &searcher );
   CU_ASSERT( searcher == NULL );
   
   return;
}

/**
   test_make_2
*/

void test_make_2( void )
{
   i_bsearcher_t *searcher = NULL;

   searcher = i_bsearcher_make();
   CU_ASSERT( searcher != NULL );
   
   i_bsearcher_deep_dispose( &searcher );
   CU_ASSERT( searcher == NULL );
   
   return;
}

int
add_test_make( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_1
   add_test_to_suite( p_suite, test_make_1, "test_make_1" );

   // test_make_2
   add_test_to_suite( p_suite, test_make_2, "test_make_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

