/**
 @file LRUCache_test_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for LRUCache_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Unit tests for LRUCache_make.

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
   test_dispose_1
*/

void test_dispose_1( void )
{
   si_trie_t *Trie = NULL;

   Trie = si_trie_make();

   si_trie_put( Trie, 1, "a", 1 );

   CU_ASSERT( Trie != NULL );

   si_trie_dispose( &Trie );

   return;
}

/**
   test_dispose_2
*/

void test_dispose_2( void )
{
   si_trie_t *Trie = NULL;

   Trie = si_trie_make();

   si_trie_put( Trie, 1, "a", 1 );
   si_trie_put( Trie, 2, "aa", 2 );
   si_trie_put( Trie, 3, "ab", 2 );
   si_trie_put( Trie, 4, "ac", 2 );
   si_trie_put( Trie, 5, "b", 1 );
   si_trie_put( Trie, 6, "bbc", 3 );
   si_trie_put( Trie, 7, "cabd", 4 );

   CU_ASSERT( Trie != NULL );

   si_trie_dispose( &Trie );

   return;
}

/**
   test_dispose_3
*/

void test_dispose_3( void )
{
   si_trie_t *Trie = NULL;

   Trie = si_trie_make();

   CU_ASSERT( Trie != NULL );

   si_trie_dispose( &Trie );

   return;
}

int
add_test_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_dispose_1
   add_test_to_suite( p_suite, test_dispose_1, "test_dispose_1" );

   // test_dispose_2
   add_test_to_suite( p_suite, test_dispose_2, "test_dispose_2" );

   // test_dispose_3
   add_test_to_suite( p_suite, test_dispose_3, "test_dispose_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */
