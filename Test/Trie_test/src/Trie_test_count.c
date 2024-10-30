/**
 @file Trie_test_count.c
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
   test_count_1
*/

void test_count_1( void )
{
   si_trie_t *trie = NULL;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );

   CU_ASSERT( si_trie_count( trie ) == 1 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_count_2
*/

void test_count_2( void )
{
   si_trie_t *trie = NULL;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 13, "b", 1 );

   CU_ASSERT( si_trie_count( trie ) == 2 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_count_3
*/

void test_count_3( void )
{
   si_trie_t *trie = NULL;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 17, "ax", 2 );

   CU_ASSERT( si_trie_count( trie ) == 2 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_count_4
*/

void test_count_4( void )
{
   si_trie_t *trie = NULL;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 13, "b", 1 );
   si_trie_put( trie, 17, "ax", 2 );

   CU_ASSERT( si_trie_count( trie ) == 3 );

   si_trie_dispose( &trie );

   return;
}

int
add_test_count( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_count", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_count_1
   add_test_to_suite( p_suite, test_count_1, "test_count_1" );

   // test_count_2
   add_test_to_suite( p_suite, test_count_2, "test_count_2" );

   // test_count_3
   add_test_to_suite( p_suite, test_count_3, "test_count_3" );

   // test_count_4
   add_test_to_suite( p_suite, test_count_4, "test_count_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

