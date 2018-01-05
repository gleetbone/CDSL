/**
 @file RBTree_test_as_string.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for RBTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_RBTree.h"
#include "RBTree_test_print_utility.h"

void convert_func( char_t *cstr, int32_t value )
{
   int32_t i = 0;
   char_t a[256] = {0};
   sprintf( a, "%d", value );

   for( i=0; a[i] != 0; i++ )
   {
      cstr[i] = a[i];
   }

   return;
}

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_as_string_1
*/

void test_as_string_1( void )
{
   i_rbtree_t *rbtree = NULL;
   char_t **astr = NULL;

   rbtree = i_rbtree_make();

   i_rbtree_put( rbtree, 1 );

   astr = test_print_utility_make_array( i_rbtree_height( rbtree ), 2 );

   CU_ASSERT( astr != NULL );

   i_rbtree_as_string( rbtree, astr, 2, convert_func );

   test_print_utility_print_array( astr );

   test_print_utility_dispose_array( astr );

   i_rbtree_dispose( rbtree );
   
   return;
}

/**
   test_as_string_2
*/

void test_as_string_2( void )
{
   i_rbtree_t *rbtree = NULL;
   char_t **astr = NULL;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   astr = test_print_utility_make_array( i_rbtree_height( rbtree ), 2 );

   CU_ASSERT( astr != NULL );

   i_rbtree_as_string( rbtree, astr, 2, convert_func );

   test_print_utility_print_array( astr );

   test_print_utility_dispose_array( astr );
 
   i_rbtree_dispose( rbtree );
   
   return;
}

int
add_test_as_string( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_as_string", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_as_string_1
   add_test_to_suite( p_suite, test_as_string_1, "test_as_string_1" );

   // test_as_string_2
   add_test_to_suite( p_suite, test_as_string_2, "test_as_string_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

