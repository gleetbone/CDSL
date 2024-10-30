/**
 @file BTree_test_keys_as_array.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_kv_keys_as_array"
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
#include "ss_BTree_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_keys_as_array_1
*/

void test_keys_as_array_1( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t *array = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );

   array = ii_btree_kv_keys_as_array( btree );

   CU_ASSERT( array[0] == 1 );

   free( array );
   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_keys_as_array_2
*/

void test_keys_as_array_2( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t *array = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );

   array = ii_btree_kv_keys_as_array( btree );

   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 3 );

   free( array );
   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_keys_as_array_3
*/

void test_keys_as_array_3( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t *array = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   array = ii_btree_kv_keys_as_array( btree );

   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 3 );

   free( array );
   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_keys_as_array_4
*/

void test_keys_as_array_4( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t *array = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );

   array = ii_btree_kv_keys_as_array( btree );

   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 3 );

   free( array );
   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_keys_as_array_5

            4
         2      6
       1
*/

void test_keys_as_array_5( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t *array = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );

   array = ii_btree_kv_keys_as_array( btree );

   CU_ASSERT( array[0] == 1 );
   CU_ASSERT( array[1] == 2 );
   CU_ASSERT( array[2] == 4 );
   CU_ASSERT( array[3] == 6 );

   free( array );
   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_keys_as_array_6

            4
         2      6
            3
*/

void test_keys_as_array_6( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t *array = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 30, 3 );

   array = ii_btree_kv_keys_as_array( btree );

   CU_ASSERT( array[0] == 2 );
   CU_ASSERT( array[1] == 3 );
   CU_ASSERT( array[2] == 4 );
   CU_ASSERT( array[3] == 6 );

   free( array );
   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_keys_as_array_7

            4
         2      6
              5
*/

void test_keys_as_array_7( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t *array = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 50, 5 );

   array = ii_btree_kv_keys_as_array( btree );

   CU_ASSERT( array[0] == 2 );
   CU_ASSERT( array[1] == 4 );
   CU_ASSERT( array[2] == 5 );
   CU_ASSERT( array[3] == 6 );

   free( array );
   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_keys_as_array_8

            4
         2      6
                  7
*/

void test_keys_as_array_8( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t *array = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 70, 7 );

   array = ii_btree_kv_keys_as_array( btree );

   CU_ASSERT( array[0] == 2 );
   CU_ASSERT( array[1] == 4 );
   CU_ASSERT( array[2] == 6 );
   CU_ASSERT( array[3] == 7 );

   free( array );
   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_keys_as_array_9
*/

void test_keys_as_array_9( void )
{
   ss_btree_kv_t *btree = NULL;
   string_t **array = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;
   string_t *s2v = NULL;
   string_t *s2k = NULL;
   string_t *s3v = NULL;
   string_t *s3k = NULL;
   string_t *s4v = NULL;
   string_t *s4k = NULL;
   
   s1k = string_make_from_cstring( "4" );
   s1v = string_make_from_cstring( "40" );
   
   s2k = string_make_from_cstring( "2" );
   s2v = string_make_from_cstring( "20" );
   
   s3k = string_make_from_cstring( "6" );
   s3v = string_make_from_cstring( "60" );
   
   s4k = string_make_from_cstring( "7" );
   s4v = string_make_from_cstring( "70" );
      
   btree = ss_btree_kv_make( 3 );

   ss_btree_kv_put( btree, s1v, s1k );
   ss_btree_kv_put( btree, s2v, s2k );
   ss_btree_kv_put( btree, s3v, s3k );
   ss_btree_kv_put( btree, s4v, s4k );

   array = ss_btree_kv_keys_as_array( btree );

   CU_ASSERT( string_is_equal( array[0], s2k ) );
   CU_ASSERT( string_is_equal( array[1], s1k ) );
   CU_ASSERT( string_is_equal( array[2], s3k ) );
   CU_ASSERT( string_is_equal( array[3], s4k ) );

   free( array );
   ss_btree_kv_deep_dispose( &btree );

   return;
}

int
add_test_keys_as_array( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_keys_as_array", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_keys_as_array_1
   add_test_to_suite( p_suite, test_keys_as_array_1, "test_keys_as_array_1" );

   // test_keys_as_array_2
   add_test_to_suite( p_suite, test_keys_as_array_2, "test_keys_as_array_2" );

   // test_keys_as_array_3
   add_test_to_suite( p_suite, test_keys_as_array_3, "test_keys_as_array_3" );

   // test_keys_as_array_4
   add_test_to_suite( p_suite, test_keys_as_array_4, "test_keys_as_array_4" );

   // test_keys_as_array_5
   add_test_to_suite( p_suite, test_keys_as_array_5, "test_keys_as_array_5" );

   // test_keys_as_array_6
   add_test_to_suite( p_suite, test_keys_as_array_6, "test_keys_as_array_6" );

   // test_keys_as_array_7
   add_test_to_suite( p_suite, test_keys_as_array_7, "test_keys_as_array_7" );

   // test_keys_as_array_8
   add_test_to_suite( p_suite, test_keys_as_array_8, "test_keys_as_array_8" );

   // test_keys_as_array_9
   add_test_to_suite( p_suite, test_keys_as_array_9, "test_keys_as_array_9" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

