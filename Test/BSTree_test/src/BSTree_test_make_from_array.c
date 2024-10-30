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

 Unit tests for BSTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_BSTree.h"
#include "s_BSTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_from_array_1
*/

void test_make_from_array_1( void )
{
   i_bstree_t *bstree = NULL;
   int32_t array[3] = {13, 0, 0 };

   bstree = i_bstree_make_from_array( array, 1 );

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( i_bstree_count( bstree ) == 1 );
   CU_ASSERT( i_bstree_has( bstree, 13 ) == 1 );

   i_bstree_dispose( &bstree );

   return;
}

/**
   test_make_from_array_2
*/

void test_make_from_array_2( void )
{
   i_bstree_t *bstree = NULL;
   int32_t array[3] = { 13, 24, 7 };

   bstree = i_bstree_make_from_array( array, 2 );

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( i_bstree_count( bstree ) == 2 );
   CU_ASSERT( i_bstree_has( bstree, 13 ) == 1 );
   CU_ASSERT( i_bstree_has( bstree, 24 ) == 1 );
   CU_ASSERT( i_bstree_has( bstree, 7 ) == 0 );

   i_bstree_dispose( &bstree );

   return;
}

/**
   test_make_from_array_3
*/

void test_make_from_array_3( void )
{
   s_bstree_t *bstree = NULL;
   
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   
   string_t *array[3] = { s1, s2, s3 };

   bstree = s_bstree_make_from_array( array, 2 );

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( s_bstree_count( bstree ) == 2 );
   CU_ASSERT( s_bstree_has( bstree, s1 ) == 1 );
   CU_ASSERT( s_bstree_has( bstree, s2 ) == 1 );
   CU_ASSERT( s_bstree_has( bstree, s3 ) == 0 );

   string_deep_dispose( &s3 );
   s_bstree_deep_dispose( &bstree );

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

