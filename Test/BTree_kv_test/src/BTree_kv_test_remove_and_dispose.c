/**
 @file BTree_test_remove_and_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_kv_remove_and_dispose"
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
   test_remove_and_dispose_1
*/

void test_remove_and_dispose_1( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );

   ii_btree_kv_remove_and_dispose( btree, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 0 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_2
*/

void test_remove_and_dispose_2( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_remove_and_dispose( btree, 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 2 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_2a
*/

void test_remove_and_dispose_2a( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_remove_and_dispose( btree, 3 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 2 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_2b
*/

void test_remove_and_dispose_2b( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_remove_and_dispose( btree, 2 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 2 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_3
*/

void test_remove_and_dispose_3( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   ii_btree_kv_remove_and_dispose( btree, 2 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 2 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_3a
*/

void test_remove_and_dispose_3a( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   ii_btree_kv_remove_and_dispose( btree, 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 2 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_3b
*/

void test_remove_and_dispose_3b( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   ii_btree_kv_remove_and_dispose( btree, 2 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 2 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_4
*/

void test_remove_and_dispose_4( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_remove_and_dispose( btree, 2 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 2 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_4a
*/

void test_remove_and_dispose_4a( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_remove_and_dispose( btree, 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 2 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_4b
*/

void test_remove_and_dispose_4b( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_remove_and_dispose( btree, 3 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 2 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_5
*/

void test_remove_and_dispose_5( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_remove_and_dispose( btree, 4 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_5a
*/

void test_remove_and_dispose_5a( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_remove_and_dispose( btree, 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_5b
*/

void test_remove_and_dispose_5b( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_remove_and_dispose( btree, 2 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_5c
*/

void test_remove_and_dispose_5c( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_remove_and_dispose( btree, 3 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_5d
*/

void test_remove_and_dispose_5d( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_remove_and_dispose( btree, 5 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 5 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_5e
*/

void test_remove_and_dispose_5e( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_remove_and_dispose( btree, 6 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_5f
*/

void test_remove_and_dispose_5f( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_remove_and_dispose( btree, 7 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 7 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_6
*/

void test_remove_and_dispose_6( void )
{
   ii_btree_kv_t *btree = NULL;
   ii_btree_kv_cursor_t *cursor = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );
   cursor = ii_btree_kv_cursor_make( btree );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );

   ii_btree_kv_cursor_start( cursor );
   ii_btree_kv_remove_and_dispose( btree, 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 0 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_6a
*/

void test_remove_and_dispose_6a( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );

   ii_btree_kv_remove_and_dispose( btree, 4 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 1 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_6b
*/

void test_remove_and_dispose_6b( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 80, 8 );
   ii_btree_kv_put( btree, 70, 7 );
   ii_btree_kv_put( btree, 60, 6 );

   ii_btree_kv_remove_and_dispose( btree, 8 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 8 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_6c
*/

void test_remove_and_dispose_6c( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );

   ii_btree_kv_remove_and_dispose( btree, 1 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 0 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_7
*/

void test_remove_and_dispose_7( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 70, 7 );
   ii_btree_kv_put( btree, 80, 8 );
   ii_btree_kv_put( btree, 90, 9 );

   ii_btree_kv_remove_and_dispose( btree, 9 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 8 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 9 );
   CU_ASSERT( result == 0 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 8 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_7a
*/

void test_remove_and_dispose_7a( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t result = 0;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 70, 7 );
   ii_btree_kv_put( btree, 80, 8 );
   ii_btree_kv_put( btree, 90, 9 );

   ii_btree_kv_remove_and_dispose( btree, 8 );

   result = ii_btree_kv_has( btree, 1 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 2 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 3 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 4 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 5 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 6 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 7 );
   CU_ASSERT( result == 1 );

   result = ii_btree_kv_has( btree, 8 );
   CU_ASSERT( result == 0 );

   result = ii_btree_kv_has( btree, 9 );
   CU_ASSERT( result == 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 8 );

   ii_btree_kv_dispose( &btree );

   return;
}

#define MAX_COUNT 100
#define MAX_VALUE 1000

/**
   test_remove_and_dispose_8
*/

void test_remove_and_dispose_8( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   btree = ii_btree_kv_make( 3 );

   srand( 101 );

   for( k=0; k<10000; k++ )
   {
      count = 0;

      while( count == 0 )
      {
         count = rand() % MAX_COUNT;
      }

      i = 0;
      while( i<count )
      {
         n = rand() % MAX_VALUE;
         if ( ii_btree_kv_has( btree, n ) == 0 )
         {
            ii_btree_kv_put( btree, n, n );
            values[i] = n;
            i = i + 1;
         }
      }


      j = 0;
      while ( j< count/2 )
      {
         i = rand() % count;
         if ( ii_btree_kv_has( btree, values[i] ) == 1 )
         {
            ii_btree_kv_remove_and_dispose( btree, values[i] );
            j = j + 1;
         }
      }

      ii_btree_kv_wipe_out( btree );
   }

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_8a
*/

void test_remove_and_dispose_8a( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   btree = ii_btree_kv_make( 4 );

   srand( 10143 );

   for( k=0; k<10000; k++ )
   {
      count = 0;

      while( count == 0 )
      {
         count = rand() % MAX_COUNT;
      }

      i = 0;
      while( i<count )
      {
         n = rand() % MAX_VALUE;
         if ( ii_btree_kv_has( btree, n ) == 0 )
         {
            ii_btree_kv_put( btree, n, n );
            values[i] = n;
            i = i + 1;
         }
      }


      j = 0;
      while ( j< count/2 )
      {
         i = rand() % count;
         if ( ii_btree_kv_has( btree, values[i] ) == 1 )
         {
            ii_btree_kv_remove_and_dispose( btree, values[i] );
            j = j + 1;
         }
      }

      ii_btree_kv_wipe_out( btree );
   }

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_8b
*/

void test_remove_and_dispose_8b( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   btree = ii_btree_kv_make( 5 );

   srand( 10147 );

   for( k=0; k<10000; k++ )
   {
      count = 0;

      while( count == 0 )
      {
         count = rand() % MAX_COUNT;
      }

      i = 0;
      while( i<count )
      {
         n = rand() % MAX_VALUE;
         if ( ii_btree_kv_has( btree, n ) == 0 )
         {
            ii_btree_kv_put( btree, n, n );
            values[i] = n;
            i = i + 1;
         }
      }


      j = 0;
      while ( j< count/2 )
      {
         i = rand() % count;
         if ( ii_btree_kv_has( btree, values[i] ) == 1 )
         {
            ii_btree_kv_remove_and_dispose( btree, values[i] );
            j = j + 1;
         }
      }

      ii_btree_kv_wipe_out( btree );
   }

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_8c
*/

void test_remove_and_dispose_8c( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   btree = ii_btree_kv_make( 2 );

   srand( 10149 );

   for( k=0; k<10000; k++ )
   {
      count = 0;

      while( count == 0 )
      {
         count = rand() % MAX_COUNT;
      }

      i = 0;
      while( i<count )
      {
         n = rand() % MAX_VALUE;
         if ( ii_btree_kv_has( btree, n ) == 0 )
         {
            ii_btree_kv_put( btree, n, n );
            values[i] = n;
            i = i + 1;
         }
      }


      j = 0;
      while ( j< count/2 )
      {
         i = rand() % count;
         if ( ii_btree_kv_has( btree, values[i] ) == 1 )
         {
            ii_btree_kv_remove_and_dispose( btree, values[i] );
            j = j + 1;
         }
      }

      ii_btree_kv_wipe_out( btree );
   }

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_9
*/

void test_remove_and_dispose_9( void )
{
   ss_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   string_t * keys[MAX_COUNT] = {NULL};
   string_t * values[MAX_COUNT] = {NULL};
   string_t *key = NULL;
   string_t *value = NULL;
   char str[8] = {0};

   btree = ss_btree_kv_make( 3 );

   srand( 10153 );

   for( k=0; k<1000; k++ )
   {
      count = 0;

      while( count == 0 )
      {
         count = rand() % MAX_COUNT;
      }

      i = 0;
      while( i<count )
      {
         n = rand() % MAX_VALUE;
         str[0] = 0;
         sprintf( str, "%03d", n );
         
         key = string_make_from_cstring(  str );
         value = string_make_from_cstring( str );
         
         if ( ss_btree_kv_has( btree, key ) == 0 )
         {
            ss_btree_kv_put( btree, value, key );
            keys[i] = key;
            values[i] = value;
            i = i + 1;
         }
         else
         {
            string_deep_dispose( &key );
            string_deep_dispose( &value );
         }
      }
      j = 0;
      while ( j < count )
      {
         i = rand() % count;
         if ( keys[i] != NULL )
         {
            if ( ss_btree_kv_has( btree, keys[i] ) == 1 )
            {
               ss_btree_kv_remove_and_dispose( btree, keys[i] );
               keys[i] = NULL;
               values[i] = NULL;
            }
         }
         j = j + 1;
      }

      j = 0;
      while ( j < count )
      {
         if ( keys[j] != NULL )
         {
            if ( ss_btree_kv_has( btree, keys[j] ) == 1 )
            {
               ss_btree_kv_remove_and_dispose( btree, keys[j] );
               keys[j] = NULL;
               values[j] = NULL;
            }
         }
         j = j + 1;
      }

      ss_btree_kv_wipe_out( btree );
      
   }

   ss_btree_kv_dispose( &btree );

   return;
}

/**
   test_remove_and_dispose_9a
*/

void test_remove_and_dispose_9a( void )
{
   ss_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   string_t * keys[MAX_COUNT] = {NULL};
   string_t * values[MAX_COUNT] = {NULL};
   string_t *key = NULL;
   string_t *value = NULL;
   char str[8] = {0};

   btree = ss_btree_kv_make( 5 );

   srand( 10153 );

   for( k=0; k<1000; k++ )
   {
      count = 0;

      while( count == 0 )
      {
         count = rand() % MAX_COUNT;
      }

      i = 0;
      while( i<count )
      {
         n = rand() % MAX_VALUE;
         str[0] = 0;
         sprintf( str, "%03d", n );
         
         key = string_make_from_cstring(  str );
         value = string_make_from_cstring( str );
         
         if ( ss_btree_kv_has( btree, key ) == 0 )
         {
            ss_btree_kv_put( btree, value, key );
            keys[i] = key;
            values[i] = value;
            i = i + 1;
         }
         else
         {
            string_deep_dispose( &key );
            string_deep_dispose( &value );
         }
      }
      j = 0;
      while ( j < count )
      {
         i = rand() % count;
         if ( keys[i] != NULL )
         {
            if ( ss_btree_kv_has( btree, keys[i] ) == 1 )
            {
               ss_btree_kv_remove_and_dispose( btree, keys[i] );
               keys[i] = NULL;
               values[i] = NULL;
            }
         }
         j = j + 1;
      }

      j = 0;
      while ( j < count )
      {
         if ( keys[j] != NULL )
         {
            if ( ss_btree_kv_has( btree, keys[j] ) == 1 )
            {
               ss_btree_kv_remove_and_dispose( btree, keys[j] );
               keys[j] = NULL;
               values[j] = NULL;
            }
         }
         j = j + 1;
      }

      ss_btree_kv_wipe_out( btree );
      
   }

   ss_btree_kv_dispose( &btree );

   return;
}

int
add_test_remove_and_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_remove_and_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_remove_and_dispose_1
   add_test_to_suite( p_suite, test_remove_and_dispose_1, "test_remove_and_dispose_1" );

   // test_remove_and_dispose_2
   add_test_to_suite( p_suite, test_remove_and_dispose_2, "test_remove_and_dispose_2" );
   add_test_to_suite( p_suite, test_remove_and_dispose_2a, "test_remove_and_dispose_2a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_2b, "test_remove_and_dispose_2b" );

   // test_remove_and_dispose_3
   add_test_to_suite( p_suite, test_remove_and_dispose_3, "test_remove_and_dispose_3" );
   add_test_to_suite( p_suite, test_remove_and_dispose_3a, "test_remove_and_dispose_3a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_3b, "test_remove_and_dispose_3b" );

   // test_remove_and_dispose_4
   add_test_to_suite( p_suite, test_remove_and_dispose_4, "test_remove_and_dispose_4" );
   add_test_to_suite( p_suite, test_remove_and_dispose_4a, "test_remove_and_dispose_4a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_4b, "test_remove_and_dispose_4b" );

   // test_remove_and_dispose_5
   add_test_to_suite( p_suite, test_remove_and_dispose_5, "test_remove_and_dispose_5" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5a, "test_remove_and_dispose_5a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5b, "test_remove_and_dispose_5b" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5c, "test_remove_and_dispose_5c" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5d, "test_remove_and_dispose_5d" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5e, "test_remove_and_dispose_5e" );
   add_test_to_suite( p_suite, test_remove_and_dispose_5f, "test_remove_and_dispose_5f" );

   // test_remove_and_dispose_6
   add_test_to_suite( p_suite, test_remove_and_dispose_6, "test_remove_and_dispose_6" );
   add_test_to_suite( p_suite, test_remove_and_dispose_6a, "test_remove_and_dispose_6a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_6b, "test_remove_and_dispose_6b" );
   add_test_to_suite( p_suite, test_remove_and_dispose_6c, "test_remove_and_dispose_6c" );

   // test_remove_and_dispose_7
   add_test_to_suite( p_suite, test_remove_and_dispose_7, "test_remove_and_dispose_7" );
   add_test_to_suite( p_suite, test_remove_and_dispose_7a, "test_remove_and_dispose_7a" );

   // test_remove_and_dispose_8
   add_test_to_suite( p_suite, test_remove_and_dispose_8, "test_remove_and_dispose_8" );
   add_test_to_suite( p_suite, test_remove_and_dispose_8a, "test_remove_and_dispose_8a" );
   add_test_to_suite( p_suite, test_remove_and_dispose_8b, "test_remove_and_dispose_8b" );
   add_test_to_suite( p_suite, test_remove_and_dispose_8c, "test_remove_and_dispose_8c" );

   // test_remove_and_dispose_9
   add_test_to_suite( p_suite, test_remove_and_dispose_9, "test_remove_and_dispose_9" );
   add_test_to_suite( p_suite, test_remove_and_dispose_9a, "test_remove_and_dispose_9a" );
   
   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

