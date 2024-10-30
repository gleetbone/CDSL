/**
 @file Trie_test_wipe_out.c
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
   test_wipe_out_1
*/

void test_wipe_out_1( void )
{
   si_trie_t *trie = NULL;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   CU_ASSERT( si_trie_has( trie, "a", 1 ) == 1 );

   si_trie_wipe_out( trie );
   CU_ASSERT( si_trie_has( trie, "a", 1 ) == 0 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_wipe_out_2
*/

void test_wipe_out_2( void )
{
   si_trie_t *trie = NULL;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 13, "b", 1 );

   si_trie_wipe_out( trie );

   CU_ASSERT( si_trie_has( trie, "a", 1 ) == 0 );

   CU_ASSERT( si_trie_has( trie, "b", 1 ) == 0 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_wipe_out_3
*/

void test_wipe_out_3( void )
{
   si_trie_t *trie = NULL;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 17, "ax", 2 );

   si_trie_wipe_out( trie );

   CU_ASSERT( si_trie_has( trie, "a", 1 ) == 0 );

   CU_ASSERT( si_trie_has( trie, "ax", 2 ) == 0 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_wipe_out_4
*/

void test_wipe_out_4( void )
{
   si_trie_t *trie = NULL;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 13, "b", 1 );
   si_trie_put( trie, 17, "ax", 2 );

   si_trie_wipe_out( trie );

   CU_ASSERT( si_trie_has( trie, "a", 1 ) == 0 );

   CU_ASSERT( si_trie_has( trie, "b", 1 ) == 0 );

   CU_ASSERT( si_trie_has( trie, "ax", 2 ) == 0 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_wipe_out_5
*/

void test_wipe_out_5( void )
{
   si_trie_t *trie = NULL;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 13, "b", 1 );
   si_trie_put( trie, 17, "ax", 2 );

   si_trie_wipe_out( trie );

   CU_ASSERT( si_trie_has( trie, "a", 1 ) == 0 );

   CU_ASSERT( si_trie_has( trie, "b", 1 ) == 0 );

   CU_ASSERT( si_trie_has( trie, "ax", 2 ) == 0 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_wipe_out_6
*/

void test_wipe_out_6( void )
{
   si_trie_t *trie = NULL;

   trie = si_trie_make();

   si_trie_wipe_out( trie );

   si_trie_dispose( &trie );

   return;
}

int
add_test_wipe_out( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_wipe_out", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_wipe_out_1
   add_test_to_suite( p_suite, test_wipe_out_1, "test_wipe_out_1" );

   // test_wipe_out_2
   add_test_to_suite( p_suite, test_wipe_out_2, "test_wipe_out_2" );

   // test_wipe_out_3
   add_test_to_suite( p_suite, test_wipe_out_3, "test_wipe_out_3" );

   // test_wipe_out_4
   add_test_to_suite( p_suite, test_wipe_out_4, "test_wipe_out_4" );

   // test_wipe_out_5
   add_test_to_suite( p_suite, test_wipe_out_5, "test_wipe_out_5" );

   // test_wipe_out_6
   add_test_to_suite( p_suite, test_wipe_out_6, "test_wipe_out_6" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

