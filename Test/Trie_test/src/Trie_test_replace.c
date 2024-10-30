/**
 @file Trie_test_replace.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Trie_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Unit tests for Trie_make.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "si_Trie.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_replace_1
*/

void test_replace_1( void )
{
   si_trie_t *trie = NULL;
   int32_t result = 0;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );

   result = si_trie_item( trie, "a", 1 );
   CU_ASSERT( result == 24 );

   si_trie_replace( trie, 13, "a", 1 );

   result = si_trie_item( trie, "a", 1 );
   CU_ASSERT( result == 13 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_replace_2
*/

void test_replace_2( void )
{
   si_trie_t *trie = NULL;
   int32_t result = 0;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 13, "b", 1 );

   result = si_trie_item( trie, "a", 1 );
   CU_ASSERT( result == 24 );

   result = si_trie_item( trie, "b", 1 );
   CU_ASSERT( result == 13 );

   si_trie_replace( trie, 25, "a", 1 );
   si_trie_replace( trie, 14, "b", 1 );

   result = si_trie_item( trie, "a", 1 );
   CU_ASSERT( result == 25 );

   result = si_trie_item( trie, "b", 1 );
   CU_ASSERT( result == 14 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_replace_3
*/

void test_replace_3( void )
{
   si_trie_t *trie = NULL;
   int32_t result = 0;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 17, "ax", 2 );

   result = si_trie_item( trie, "a", 1 );
   CU_ASSERT( result == 24 );

   result = si_trie_item( trie, "ax", 2 );
   CU_ASSERT( result == 17 );

   si_trie_replace( trie, 25, "a", 1 );
   si_trie_replace( trie, 18, "ax", 2 );

   result = si_trie_item( trie, "a", 1 );
   CU_ASSERT( result == 25 );

   result = si_trie_item( trie, "ax", 2 );
   CU_ASSERT( result == 18 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_replace_4
*/

void test_replace_4( void )
{
   si_trie_t *trie = NULL;
   int32_t result = 0;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 13, "b", 1 );
   si_trie_put( trie, 17, "ax", 2 );

   result = si_trie_item( trie, "a", 1 );
   CU_ASSERT( result == 24 );

   result = si_trie_item( trie, "b", 1 );
   CU_ASSERT( result == 13 );

   result = si_trie_item( trie, "ax", 2 );
   CU_ASSERT( result == 17 );

   si_trie_put( trie, 25, "a", 1 );
   si_trie_put( trie, 14, "b", 1 );
   si_trie_put( trie, 18, "ax", 2 );

   result = si_trie_item( trie, "a", 1 );
   CU_ASSERT( result == 25 );

   result = si_trie_item( trie, "b", 1 );
   CU_ASSERT( result == 14 );

   result = si_trie_item( trie, "ax", 2 );
   CU_ASSERT( result == 18 );

   si_trie_dispose( &trie );

   return;
}

int
add_test_replace( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_replace", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_replace_1
   add_test_to_suite( p_suite, test_replace_1, "test_replace_1" );

   // test_replace_2
   add_test_to_suite( p_suite, test_replace_2, "test_replace_2" );

   // test_replace_3
   add_test_to_suite( p_suite, test_replace_3, "test_replace_3" );

   // test_replace_4
   add_test_to_suite( p_suite, test_replace_4, "test_replace_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

