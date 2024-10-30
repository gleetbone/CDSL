/**
 @file RBTree_test_as_array.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for RBTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for RBTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_RBTree.h"
#include "s_RBTree.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_as_array_1
*/

void test_as_array_1( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t *array = NULL;
   int32_t count = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   
   array = i_rbtree_as_array( rbtree, &count );
   
   CU_ASSERT( count == 1 );
   CU_ASSERT( array[0] == 1 );

   free( array );
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_as_array_2
*/

void test_as_array_2( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t *array = NULL;
   int32_t count = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 3 );
   
   array = i_rbtree_as_array( rbtree, &count );
   
   CU_ASSERT( count == 3 );
   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 3 );
 
   free( array );
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_as_array_3
*/

void test_as_array_3( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t *array = NULL;
   int32_t count = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 3 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 1 );
   
   array = i_rbtree_as_array( rbtree, &count );
   
   CU_ASSERT( count == 3 );
   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 3 );
 
   free( array );
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_as_array_4
*/

void test_as_array_4( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t *array = NULL;
   int32_t count = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 1 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 3 );
   
   array = i_rbtree_as_array( rbtree, &count );
   
   CU_ASSERT( count == 3 );
   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 3 );
 
   free( array );
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_as_array_5
   
            4
         2      6
       1  
*/

void test_as_array_5( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t *array = NULL;
   int32_t count = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 1 );
   
   array = i_rbtree_as_array( rbtree, &count );
   
   CU_ASSERT( count == 4 );
   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 4 );
   CU_ASSERT( array[3] == 6 );
  
   free( array );
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_as_array_6
   
            4
         2      6
            3       
*/

void test_as_array_6( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t *array = NULL;
   int32_t count = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 3 );
   
   array = i_rbtree_as_array( rbtree, &count );
   
   CU_ASSERT( count == 4 );
   CU_ASSERT( array[0] == 2 );
   CU_ASSERT( array[1] == 3 );
   CU_ASSERT( array[2] == 4 );
   CU_ASSERT( array[3] == 6 );
 
   free( array );
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_as_array_7
   
            4
         2      6
              5 
*/

void test_as_array_7( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t *array = NULL;
   int32_t count = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 5 );
   
   array = i_rbtree_as_array( rbtree, &count );
   
   CU_ASSERT( count == 4 );
   CU_ASSERT( array[0] == 2 );
   CU_ASSERT( array[1] == 4 );
   CU_ASSERT( array[2] == 5 );
   CU_ASSERT( array[3] == 6 );
 
   free( array );
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_as_array_8
   
            4
         2      6
                  7   
*/

void test_as_array_8( void )
{
   i_rbtree_t *rbtree = NULL;
   int32_t *array = NULL;
   int32_t count = 0;
   
   rbtree = i_rbtree_make();
   
   i_rbtree_put( rbtree, 4 );
   i_rbtree_put( rbtree, 2 );
   i_rbtree_put( rbtree, 6 );
   i_rbtree_put( rbtree, 7 );
   
   array = i_rbtree_as_array( rbtree, &count );
   
   CU_ASSERT( count == 4 );
   CU_ASSERT( array[0] == 2 );
   CU_ASSERT( array[1] == 4 );
   CU_ASSERT( array[2] == 6 );
   CU_ASSERT( array[3] == 7 );
 
   free( array );
   i_rbtree_dispose( &rbtree );
   
   return;
}

/**
   test_as_array_9
*/

void test_as_array_9( void )
{
   s_rbtree_t *rbtree = NULL;
   string_t **array = NULL;
   int32_t count = 0;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   
   rbtree = s_rbtree_make();
   
   s_rbtree_put( rbtree, s1 );
   s_rbtree_put( rbtree, s2 );

   array = s_rbtree_as_array( rbtree, &count );

   CU_ASSERT( count == 2 );
   CU_ASSERT( array[0] == s1 );
   CU_ASSERT( array[1] == s2 );

   free( array );
   s_rbtree_deep_dispose( &rbtree );

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

   // test_as_array_3
   add_test_to_suite( p_suite, test_as_array_3, "test_as_array_3" );

   // test_as_array_4
   add_test_to_suite( p_suite, test_as_array_4, "test_as_array_4" );

   // test_as_array_5
   add_test_to_suite( p_suite, test_as_array_5, "test_as_array_5" );

   // test_as_array_6
   add_test_to_suite( p_suite, test_as_array_6, "test_as_array_6" );

   // test_as_array_7
   add_test_to_suite( p_suite, test_as_array_7, "test_as_array_7" );

   // test_as_array_8
   add_test_to_suite( p_suite, test_as_array_8, "test_as_array_8" );

   // test_as_array_9
   add_test_to_suite( p_suite, test_as_array_9, "test_as_array_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

