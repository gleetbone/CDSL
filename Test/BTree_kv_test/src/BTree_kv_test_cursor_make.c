/**
 @file BTree_test_cursor_make.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_cursor_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Unit tests for BTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_BTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_cursor_make_1
*/

void test_cursor_make_1( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_cursor_t *cursor = NULL;

   btree = ii_btree_kv_make( 3 );
   cursor = ii_btree_kv_cursor_make( btree );

   CU_ASSERT( cursor != NULL );

   ii_btree_kv_cursor_dispose( &cursor );
   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_cursor_make_2
*/

void test_cursor_make_2( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_cursor_t *cursor1 = NULL;
   ii_btree_kv_cursor_t *cursor2 = NULL;

   btree = ii_btree_kv_make( 3 );
   cursor1 = ii_btree_kv_cursor_make( btree );
   cursor2 = ii_btree_kv_cursor_make( btree );

   CU_ASSERT( cursor1 != NULL );
   CU_ASSERT( cursor2 != NULL );

   ii_btree_kv_cursor_dispose( &cursor2 );
   ii_btree_kv_cursor_dispose( &cursor1 );
   ii_btree_kv_dispose( &btree );

   return;
}


int
add_test_cursor_make( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_make", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_make_1
   add_test_to_suite( p_suite, test_cursor_make_1, "test_cursor_make_1" );

   // test_cursor_make_2
   add_test_to_suite( p_suite, test_cursor_make_2, "test_cursor_make_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

