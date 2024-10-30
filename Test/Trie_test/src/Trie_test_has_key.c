/**
 @file Trie_test_has_key.c
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
   test_has_key_1
*/

void test_has_key_1( void )
{
   si_trie_t *trie = NULL;

   trie = si_trie_make();

   CU_ASSERT( si_trie_has_key( trie, "a", 1 ) == 0 );

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 13, "boy", 3 );

   CU_ASSERT( si_trie_has_key( trie, "a", 1 ) == 1 );
   CU_ASSERT( si_trie_has_key( trie, "bo", 2 ) == 1 );
   CU_ASSERT( si_trie_has_key( trie, "boy", 3 ) == 1 );

   si_trie_dispose( &trie );

   return;
}

int
add_test_has_key( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_has_key", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_has_key_1
   add_test_to_suite( p_suite, test_has_key_1, "test_has_key_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

