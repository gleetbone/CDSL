/**
 @file BSTree_test_make_from_array.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_kv_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_BSTree_kv.h"
#include "ss_BSTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_from_array_1
*/

void test_make_from_array_1( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t key_array[3] = { 13, 0, 0 };
   int32_t value_array[3] = { 130, 0, 0 };

   bstree = ii_bstree_kv_make_from_array( key_array, value_array, 1 );

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 1 );
   CU_ASSERT( ii_bstree_kv_has( bstree, 13 ) == 1 );

   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_make_from_array_2
*/

void test_make_from_array_2( void )
{
   ii_bstree_kv_t *bstree = NULL;
   int32_t key_array[8] = { 2, 3, 7, 11, 13, 17, 19, 23 };
   int32_t value_array[8] = { 20, 30, 70, 110, 130, 170, 190, 230 };

   bstree = ii_bstree_kv_make_from_array( key_array, value_array, 8 );

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( ii_bstree_kv_count( bstree ) == 8 );
   CU_ASSERT( ii_bstree_kv_has( bstree, 13 ) == 1 );

   ii_bstree_kv_dispose( &bstree );

   return;
}

/**
   test_make_from_array_3
*/

void test_make_from_array_3( void )
{
   ss_bstree_kv_t *bstree = NULL;
   
   string_t *s2 = NULL;
   string_t *s20 = NULL;
   string_t *s4 = NULL;
   string_t *s40 = NULL;
   string_t *s6 = NULL;
   string_t *s60 = NULL;
   string_t *s7 = NULL;
   string_t *s70 = NULL;
   
   s2 = string_make_from_cstring( "2" );
   s20 = string_make_from_cstring( "20" );
   s4 = string_make_from_cstring( "4" );
   s40 = string_make_from_cstring( "40" );
   s6 = string_make_from_cstring( "6" );
   s60 = string_make_from_cstring( "60" );
   s7 = string_make_from_cstring( "7" );
   s70 = string_make_from_cstring( "70" );
   
   string_t *key_array[8] = { s2, s4, s6, s7 };
   string_t *value_array[8] = { s20, s40, s60, s70 };

   bstree = ss_bstree_kv_make_from_array( key_array, value_array, 4 );

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( ss_bstree_kv_count( bstree ) == 4 );
   CU_ASSERT( ss_bstree_kv_has( bstree, s2 ) == 1 );

   ss_bstree_kv_deep_dispose( &bstree );

   return;
}

int
add_test_make_from_array( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make_from_array", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_from_array_1
   add_test_to_suite( p_suite, test_make_from_array_1, "test_make_from_array_1" );

   // test_make_from_array_2
   add_test_to_suite( p_suite, test_make_from_array_2, "test_make_from_array_2" );

   // test_make_from_array_3
   add_test_to_suite( p_suite, test_make_from_array_3, "test_make_from_array_3" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */
