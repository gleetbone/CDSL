/**
 @file AVLTree_test_occurrences.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AVLTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_AVLTree.h"
#include "s_AVLTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_occurrences_1
*/

void test_occurrences_1( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   result = i_avltree_occurrences( avltree, 1 );
   CU_ASSERT( result == 0 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_occurrences_2
*/

void test_occurrences_2( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 1 );
   
   result = i_avltree_occurrences( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_occurrences( avltree, 13 );
   CU_ASSERT( result == 0 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_occurrences_3
*/

void test_occurrences_3( void )
{
   i_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   avltree = i_avltree_make();
   
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 3 );
   i_avltree_put( avltree, 2 );
   i_avltree_put( avltree, 1 );
   
   result = i_avltree_occurrences( avltree, 1 );
   CU_ASSERT( result == 1 );
 
   result = i_avltree_occurrences( avltree, 2 );
   CU_ASSERT( result == 2 );
 
   result = i_avltree_occurrences( avltree, 3 );
   CU_ASSERT( result == 1 );
 
   i_avltree_dispose( &avltree );

   return;
}

/**
   test_occurrences_4
*/

void test_occurrences_4( void )
{
   s_avltree_t *avltree = NULL;
   int32_t result = 0;
   
   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   string_t *s2a = string_make_from_cstring( "2" );
   string_t *s3 = string_make_from_cstring( "3" );
   
   avltree = s_avltree_make();
   
   s_avltree_put( avltree, s2 );
   s_avltree_put( avltree, s3 );
   s_avltree_put( avltree, s2a );
   s_avltree_put( avltree, s1 );
   
   result = s_avltree_occurrences( avltree, s1 );
   CU_ASSERT( result == 1 );
 
   result = s_avltree_occurrences( avltree, s2 );
   CU_ASSERT( result == 2 );
 
   result = s_avltree_occurrences( avltree, s3 );
   CU_ASSERT( result == 1 );
 
   s_avltree_deep_dispose( &avltree );

   return;
}

int
add_test_occurrences( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_occurrences", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_occurrences_1
   add_test_to_suite( p_suite, test_occurrences_1, "test_occurrences_1" );

   // test_occurrences_2
   add_test_to_suite( p_suite, test_occurrences_2, "test_occurrences_2" );

   // test_occurrences_3
   add_test_to_suite( p_suite, test_occurrences_3, "test_occurrences_3" );

   // test_occurrences_4
   add_test_to_suite( p_suite, test_occurrences_4, "test_occurrences_4" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

