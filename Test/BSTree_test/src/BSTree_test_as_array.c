/**
 @file BSTree_test_as_array.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree_forth"
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
   test_as_array_1
*/

void test_as_array_1( void )
{
   i_bstree_t *bstree = NULL;
   int32_t *array = NULL;
   int32_t count = 0;

   bstree = i_bstree_make();
   
   i_bstree_put( bstree, 24 );
   i_bstree_put( bstree, 13 );

   array = i_bstree_as_array( bstree, &count );

   CU_ASSERT( count == 2 );
   CU_ASSERT( array[0] == 13 );
   CU_ASSERT( array[1] == 24 );

   free( array );
   i_bstree_dispose( &bstree );

   return;
}

/**
   test_as_array_2
*/

void test_as_array_2( void )
{
   s_bstree_t *bstree = NULL;
   string_t **array = NULL;
   int32_t count = 0;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   
   bstree = s_bstree_make();
   
   s_bstree_put( bstree, s1 );
   s_bstree_put( bstree, s2 );

   array = s_bstree_as_array( bstree, &count );

   CU_ASSERT( count == 2 );
   CU_ASSERT( array[0] == s1 );
   CU_ASSERT( array[1] == s2 );

   free( array );
   s_bstree_deep_dispose( &bstree );

   return;
}

int
add_test_as_array( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_as_array", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_as_array_1
   add_test_to_suite( p_suite, test_as_array_1, "test_as_array_1" );

   // test_as_array_2
   add_test_to_suite( p_suite, test_as_array_2, "test_as_array_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

