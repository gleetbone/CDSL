/**
 @file Trie_test_put.c
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
   test_put_1
*/

void test_put_1( void )
{
   si_trie_t *trie = NULL;
   int32_t result = 0;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );

   result = si_trie_item( trie, "a", 1 );
   CU_ASSERT( result == 24 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_put_2
*/

void test_put_2( void )
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

   si_trie_dispose( &trie );

   return;
}

/**
   test_put_3
*/

void test_put_3( void )
{
   si_trie_t *trie = NULL;
   int32_t result = 0;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 17, "ax", 2 );
   si_trie_put( trie, 17, "ay", 2 );

   result = si_trie_item( trie, "a", 1 );
   CU_ASSERT( result == 24 );

   result = si_trie_item( trie, "ax", 2 );
   CU_ASSERT( result == 17 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_put_4
*/

void test_put_4( void )
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

   si_trie_dispose( &trie );

   return;
}

/**
   test_put_5
*/

void test_put_5( void )
{
   si_trie_t *trie = NULL;
   int32_t result = 0;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 13, "c", 1 );
   si_trie_put( trie, 17, "ax", 2 );
   si_trie_put( trie, 19, "b", 1 );

   result = si_trie_item( trie, "a", 1 );
   CU_ASSERT( result == 24 );

   result = si_trie_item( trie, "b", 1 );
   CU_ASSERT( result == 19 );

   result = si_trie_item( trie, "c", 1 );
   CU_ASSERT( result == 13 );

   result = si_trie_item( trie, "ax", 2 );
   CU_ASSERT( result == 17 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_put_6
*/

void test_put_6( void )
{
   si_trie_t *trie = NULL;
   int32_t result = 0;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 13, "ab", 2 );
   si_trie_put( trie, 17, "ac", 2 );
   si_trie_put( trie, 19, "b", 1 );
   si_trie_put( trie, 23, "aa", 2 );
   si_trie_put( trie, 29, "ad", 2 );

   result = si_trie_item( trie, "a", 1 );
   CU_ASSERT( result == 24 );

   result = si_trie_item( trie, "aa", 2 );
   CU_ASSERT( result == 23 );

   result = si_trie_item( trie, "ab", 2 );
   CU_ASSERT( result == 13 );

   result = si_trie_item( trie, "ac", 2 );
   CU_ASSERT( result == 17 );

   result = si_trie_item( trie, "ad", 2 );
   CU_ASSERT( result == 29 );

   result = si_trie_item( trie, "b", 1 );
   CU_ASSERT( result == 19 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_put_7
*/

void test_put_7( void )
{
   si_trie_t *trie = NULL;
   int32_t result = 0;

   trie = si_trie_make();

   si_trie_put( trie, 24, "a", 1 );
   si_trie_put( trie, 13, "aa", 2 );
   si_trie_put( trie, 17, "ad", 2 );
   si_trie_put( trie, 19, "b", 1 );
   si_trie_put( trie, 23, "ab", 2 );
   si_trie_put( trie, 29, "ac", 2 );
   si_trie_put( trie, 31, "bc", 2 );
   si_trie_put( trie, 37, "bcx", 3 );

   result = si_trie_item( trie, "a", 1 );
   CU_ASSERT( result == 24 );

   result = si_trie_item( trie, "aa", 2 );
   CU_ASSERT( result == 13 );

   result = si_trie_item( trie, "ab", 2 );
   CU_ASSERT( result == 23 );

   result = si_trie_item( trie, "ac", 2 );
   CU_ASSERT( result == 29 );

   result = si_trie_item( trie, "ad", 2 );
   CU_ASSERT( result == 17 );

   result = si_trie_item( trie, "b", 1 );
   CU_ASSERT( result == 19 );

   result = si_trie_item( trie, "bc", 2 );
   CU_ASSERT( result == 31 );

   result = si_trie_item( trie, "bcx", 3 );
   CU_ASSERT( result == 37 );

   si_trie_put( trie, 39, "bcx", 3 );
   
   result = si_trie_item( trie, "bcx", 3 );
   CU_ASSERT( result == 39 );

   si_trie_dispose( &trie );

   return;
}

/**
   test_put_8
*/

void test_put_8( void )
{
   si_trie_t *trie = NULL;
   int32_t result = 0;

   trie = si_trie_make();

   si_trie_put( trie, 24, "b", 1 );
   si_trie_put( trie, 13, "ba", 2 );
   si_trie_put( trie, 17, "bd", 2 );
   si_trie_put( trie, 19, "a", 1 );
   si_trie_put( trie, 23, "ab", 2 );

   result = si_trie_item( trie, "a", 1 );
   CU_ASSERT( result == 19 );

   result = si_trie_item( trie, "ab", 2 );
   CU_ASSERT( result == 23 );

   result = si_trie_item( trie, "b", 1 );
   CU_ASSERT( result == 24 );

   result = si_trie_item( trie, "ba", 2 );
   CU_ASSERT( result == 13 );

   result = si_trie_item( trie, "bd", 2 );
   CU_ASSERT( result == 17 );

   si_trie_put( trie, 39, "ba", 2 );
   
   result = si_trie_item( trie, "ba", 2 );
   CU_ASSERT( result == 39 );

   si_trie_dispose( &trie );

   return;
}

int
add_test_put( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_1
   add_test_to_suite( p_suite, test_put_1, "test_put_1" );

   // test_put_2
   add_test_to_suite( p_suite, test_put_2, "test_put_2" );

   // test_put_3
   add_test_to_suite( p_suite, test_put_3, "test_put_3" );

   // test_put_4
   add_test_to_suite( p_suite, test_put_4, "test_put_4" );

   // test_put_5
   add_test_to_suite( p_suite, test_put_5, "test_put_5" );

   // test_put_6
   add_test_to_suite( p_suite, test_put_6, "test_put_6" );

   // test_put_7
   add_test_to_suite( p_suite, test_put_7, "test_put_7" );

   // test_put_8
   add_test_to_suite( p_suite, test_put_8, "test_put_8" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

