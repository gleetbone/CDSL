/**
 @file BTree_test_put_and_dispose.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_kv_put_and_dispose"
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
   test_put_and_dispose_1
*/

void test_put_and_dispose_1( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 1 );
   CU_ASSERT( ii_btree_kv_is_empty( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_2
*/

void test_put_and_dispose_2( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 2 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_2a
*/

void test_put_and_dispose_2a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 2 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_3
*/

void test_put_and_dispose_3( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_3a
*/

void test_put_and_dispose_3a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_3b
*/

void test_put_and_dispose_3b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_3c
*/

void test_put_and_dispose_3c( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_3d
*/

void test_put_and_dispose_3d( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_3e
*/

void test_put_and_dispose_3e( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4
*/

void test_put_and_dispose_4( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4a
*/

void test_put_and_dispose_4a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4b
*/

void test_put_and_dispose_4b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4c
*/

void test_put_and_dispose_4c( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4d
*/

void test_put_and_dispose_4d( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4e
*/

void test_put_and_dispose_4e( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4f
*/

void test_put_and_dispose_4f( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4g
*/

void test_put_and_dispose_4g( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4h
*/

void test_put_and_dispose_4h( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4i
*/

void test_put_and_dispose_4i( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4j
*/

void test_put_and_dispose_4j( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4k
*/

void test_put_and_dispose_4k( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4l
*/

void test_put_and_dispose_4l( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4m
*/

void test_put_and_dispose_4m( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4n
*/

void test_put_and_dispose_4n( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4o
*/

void test_put_and_dispose_4o( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4p
*/

void test_put_and_dispose_4p( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4q
*/

void test_put_and_dispose_4q( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4r
*/

void test_put_and_dispose_4r( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4s
*/

void test_put_and_dispose_4s( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4t
*/

void test_put_and_dispose_4t( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4u
*/

void test_put_and_dispose_4u( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4v
*/

void test_put_and_dispose_4v( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_4w
*/

void test_put_and_dispose_4w( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_5
*/

void test_put_and_dispose_5( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 5 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_5a
*/

void test_put_and_dispose_5a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 5 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_5b
*/

void test_put_and_dispose_5b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 5 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_5c
*/

void test_put_and_dispose_5c( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 5 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_5d
*/

void test_put_and_dispose_5d( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 5 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_6
*/

void test_put_and_dispose_6( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_6a
*/

void test_put_and_dispose_6a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_6b
*/

void test_put_and_dispose_6b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_6c
*/

void test_put_and_dispose_6c( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_6d
*/

void test_put_and_dispose_6d( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_6e
*/

void test_put_and_dispose_6e( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 60, 6 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_7
*/

void test_put_and_dispose_7( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );
   ii_btree_kv_put_and_dispose( btree, 70, 7 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_7a
*/

void test_put_and_dispose_7a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 70, 7 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_7b
*/

void test_put_and_dispose_7b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 70, 7 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_7c
*/

void test_put_and_dispose_7c( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 70, 7 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_7d
*/

void test_put_and_dispose_7d( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 70, 7 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_7e
*/

void test_put_and_dispose_7e( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 70, 7 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_7f
*/

void test_put_and_dispose_7f( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 70, 7 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_8
*/

void test_put_and_dispose_8( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );
   ii_btree_kv_put_and_dispose( btree, 70, 7 );
   ii_btree_kv_put_and_dispose( btree, 80, 8 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 8 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_8a
*/

void test_put_and_dispose_8a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 80, 8 );
   ii_btree_kv_put_and_dispose( btree, 70, 7 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 8 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_9
*/

void test_put_and_dispose_9( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 10, 1 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );
   ii_btree_kv_put_and_dispose( btree, 70, 7 );
   ii_btree_kv_put_and_dispose( btree, 80, 8 );
   ii_btree_kv_put_and_dispose( btree, 90, 9 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 9 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_9a
*/

void test_put_and_dispose_9a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 90, 9 );
   ii_btree_kv_put_and_dispose( btree, 80, 8 );
   ii_btree_kv_put_and_dispose( btree, 70, 7 );
   ii_btree_kv_put_and_dispose( btree, 60, 6 );
   ii_btree_kv_put_and_dispose( btree, 50, 5 );
   ii_btree_kv_put_and_dispose( btree, 40, 4 );
   ii_btree_kv_put_and_dispose( btree, 30, 3 );
   ii_btree_kv_put_and_dispose( btree, 20, 2 );
   ii_btree_kv_put_and_dispose( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 9 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_10
*/

void test_put_and_dispose_10( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree,  10,  1 );
   ii_btree_kv_put_and_dispose( btree,  20,  2 );
   ii_btree_kv_put_and_dispose( btree,  30,  3 );
   ii_btree_kv_put_and_dispose( btree,  40,  4 );
   ii_btree_kv_put_and_dispose( btree,  50,  5 );
   ii_btree_kv_put_and_dispose( btree,  60,  6 );
   ii_btree_kv_put_and_dispose( btree,  70,  7 );
   ii_btree_kv_put_and_dispose( btree,  80,  8 );
   ii_btree_kv_put_and_dispose( btree,  90,  9 );
   ii_btree_kv_put_and_dispose( btree, 100, 10 );
   ii_btree_kv_put_and_dispose( btree, 110, 11 );
   ii_btree_kv_put_and_dispose( btree, 120, 12 );
   ii_btree_kv_put_and_dispose( btree, 130, 13 );
   ii_btree_kv_put_and_dispose( btree, 140, 14 );
   ii_btree_kv_put_and_dispose( btree, 150, 15 );
   ii_btree_kv_put_and_dispose( btree, 160, 16 );
   ii_btree_kv_put_and_dispose( btree, 170, 17 );
   ii_btree_kv_put_and_dispose( btree, 180, 18 );
   ii_btree_kv_put_and_dispose( btree, 190, 19 );
   ii_btree_kv_put_and_dispose( btree, 200, 20 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 20 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_10a
*/

void test_put_and_dispose_10a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree, 200, 20 );
   ii_btree_kv_put_and_dispose( btree, 190, 19 );
   ii_btree_kv_put_and_dispose( btree, 180, 18 );
   ii_btree_kv_put_and_dispose( btree, 170, 17 );
   ii_btree_kv_put_and_dispose( btree, 160, 16 );
   ii_btree_kv_put_and_dispose( btree, 150, 15 );
   ii_btree_kv_put_and_dispose( btree, 140, 14 );
   ii_btree_kv_put_and_dispose( btree, 130, 13 );
   ii_btree_kv_put_and_dispose( btree, 120, 12 );
   ii_btree_kv_put_and_dispose( btree, 110, 11 );
   ii_btree_kv_put_and_dispose( btree, 100, 10 );
   ii_btree_kv_put_and_dispose( btree,  90,  9 );
   ii_btree_kv_put_and_dispose( btree,  80,  8 );
   ii_btree_kv_put_and_dispose( btree,  70,  7 );
   ii_btree_kv_put_and_dispose( btree,  60,  6 );
   ii_btree_kv_put_and_dispose( btree,  50,  5 );
   ii_btree_kv_put_and_dispose( btree,  40,  4 );
   ii_btree_kv_put_and_dispose( btree,  30,  3 );
   ii_btree_kv_put_and_dispose( btree,  20,  2 );
   ii_btree_kv_put_and_dispose( btree,  10,  1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 20 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_10b
*/

void test_put_and_dispose_10b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree,  10,  1 );
   ii_btree_kv_put_and_dispose( btree,  20,  2 );
   ii_btree_kv_put_and_dispose( btree,  30,  3 );
   ii_btree_kv_put_and_dispose( btree,  40,  4 );
   ii_btree_kv_put_and_dispose( btree,  50,  5 );
   ii_btree_kv_put_and_dispose( btree,  60,  6 );
   ii_btree_kv_put_and_dispose( btree,  70,  7 );
   ii_btree_kv_put_and_dispose( btree,  80,  8 );
   ii_btree_kv_put_and_dispose( btree,  90,  9 );
   ii_btree_kv_put_and_dispose( btree, 100, 10 );
   ii_btree_kv_put_and_dispose( btree, 200, 20 );
   ii_btree_kv_put_and_dispose( btree, 190, 19 );
   ii_btree_kv_put_and_dispose( btree, 180, 18 );
   ii_btree_kv_put_and_dispose( btree, 170, 17 );
   ii_btree_kv_put_and_dispose( btree, 160, 16 );
   ii_btree_kv_put_and_dispose( btree, 150, 15 );
   ii_btree_kv_put_and_dispose( btree, 140, 14 );
   ii_btree_kv_put_and_dispose( btree, 130, 13 );
   ii_btree_kv_put_and_dispose( btree, 120, 12 );
   ii_btree_kv_put_and_dispose( btree, 110, 11 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 20 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_10c
*/

void test_put_and_dispose_10c( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree,  962,  962 );
   ii_btree_kv_put_and_dispose( btree,  775,  775 );
   ii_btree_kv_put_and_dispose( btree,  307,  307 );
   ii_btree_kv_put_and_dispose( btree,  766,  766 );
   ii_btree_kv_put_and_dispose( btree,  243,  243 );
   ii_btree_kv_put_and_dispose( btree,  349,  349 );
   ii_btree_kv_put_and_dispose( btree,  340,  340 );
   ii_btree_kv_put_and_dispose( btree,  654,  654 );
   ii_btree_kv_put_and_dispose( btree,   37,   37 );
   ii_btree_kv_put_and_dispose( btree,  359,  359 );
   ii_btree_kv_put_and_dispose( btree,  630,  630 );
   ii_btree_kv_put_and_dispose( btree,  141,  141 );
   ii_btree_kv_put_and_dispose( btree,  332,  332 );
   ii_btree_kv_put_and_dispose( btree,   18,   18 );
   ii_btree_kv_put_and_dispose( btree,   48,   48 );
   ii_btree_kv_put_and_dispose( btree,  275,  275 );
   ii_btree_kv_put_and_dispose( btree,  666,  666 );
   ii_btree_kv_put_and_dispose( btree,  832,  832 );
   ii_btree_kv_put_and_dispose( btree,  263,  263 );
   ii_btree_kv_put_and_dispose( btree,  462,  462 );
   ii_btree_kv_put_and_dispose( btree,  793,  793 );
   ii_btree_kv_put_and_dispose( btree,  129,  129 );
   ii_btree_kv_put_and_dispose( btree,  347,  347 );
   ii_btree_kv_put_and_dispose( btree,  787,  787 );
   ii_btree_kv_put_and_dispose( btree,  494,  494 );
   ii_btree_kv_put_and_dispose( btree,  521,  521 );
   ii_btree_kv_put_and_dispose( btree,  790,  790 );
   ii_btree_kv_put_and_dispose( btree,  693,  693 );
   ii_btree_kv_put_and_dispose( btree,   61,   61 );
   ii_btree_kv_put_and_dispose( btree,  629,  629 );
   ii_btree_kv_put_and_dispose( btree,  848,  848 );
   ii_btree_kv_put_and_dispose( btree,  563,  563 );
   ii_btree_kv_put_and_dispose( btree,  756,  756 );
   ii_btree_kv_put_and_dispose( btree,  507,  507 );
   ii_btree_kv_put_and_dispose( btree,  329,  329 );
   ii_btree_kv_put_and_dispose( btree,  654,  654 );
   ii_btree_kv_put_and_dispose( btree,  351,  351 );
   ii_btree_kv_put_and_dispose( btree,  208, 208 );
   ii_btree_kv_put_and_dispose( btree,   21,  21 );
   ii_btree_kv_put_and_dispose( btree,    5,   5 );
   ii_btree_kv_put_and_dispose( btree,  246,  246 );
   ii_btree_kv_put_and_dispose( btree,  380,  380 );
   ii_btree_kv_put_and_dispose( btree,  635,  635 );
   ii_btree_kv_put_and_dispose( btree,  739,  739 );
   ii_btree_kv_put_and_dispose( btree,  712,  712 );
   ii_btree_kv_put_and_dispose( btree,    6,    6 );
   ii_btree_kv_put_and_dispose( btree,  788,  788 );
   ii_btree_kv_put_and_dispose( btree,  339,  339 );
   ii_btree_kv_put_and_dispose( btree,  672,  672 );
   ii_btree_kv_put_and_dispose( btree,  620,  620 );
   ii_btree_kv_put_and_dispose( btree,  955,  955 );
   
//   ii_btree_kv_remove( btree, 666 );
   //ii_btree_kv_remove( btree,  21 );
   //ii_btree_kv_remove( btree, 351 );
   //ii_btree_kv_remove( btree, 766 );
   //ii_btree_kv_remove( btree, 563 );
   
   ii_btree_kv_remove( btree, 37 );

   //CU_ASSERT( ii_btree_kv_count( btree ) == 20 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_10d
*/

void test_put_and_dispose_10d( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put_and_dispose( btree,  353,  353 );
   ii_btree_kv_put_and_dispose( btree,  638,  638 );
   ii_btree_kv_put_and_dispose( btree,  460,  460 );
   ii_btree_kv_put_and_dispose( btree,  678,  678 );
   ii_btree_kv_put_and_dispose( btree,  651,  651 );
   ii_btree_kv_put_and_dispose( btree,  243,  243 );
   ii_btree_kv_put_and_dispose( btree,  922,  922 );
   ii_btree_kv_put_and_dispose( btree,  684,  684 );
   ii_btree_kv_put_and_dispose( btree,  383,  383 );
   ii_btree_kv_put_and_dispose( btree,  764,  764 );
   ii_btree_kv_put_and_dispose( btree,  450,  450 );
   ii_btree_kv_put_and_dispose( btree,  158,  158 );
   ii_btree_kv_put_and_dispose( btree,  993,  993 );
   ii_btree_kv_put_and_dispose( btree,  280,  280 );
   ii_btree_kv_put_and_dispose( btree,  292,  292 );
   ii_btree_kv_put_and_dispose( btree,  715,  715 );
   ii_btree_kv_put_and_dispose( btree,  449,  449 );
   ii_btree_kv_put_and_dispose( btree,   98,   98 );
   ii_btree_kv_put_and_dispose( btree,   56,   56 );
   ii_btree_kv_put_and_dispose( btree,  574,  574 );
   ii_btree_kv_put_and_dispose( btree,  743,  743 );
   ii_btree_kv_put_and_dispose( btree,  515,  515 );
   ii_btree_kv_put_and_dispose( btree,  134,  134 );
   ii_btree_kv_put_and_dispose( btree,  222,  222 );
   ii_btree_kv_put_and_dispose( btree,  526,  526 );
   ii_btree_kv_put_and_dispose( btree,  977,  977 );
   ii_btree_kv_put_and_dispose( btree,  408,  408 );
   ii_btree_kv_put_and_dispose( btree,  879,  879 );
   ii_btree_kv_put_and_dispose( btree,  796,  796 );
   ii_btree_kv_put_and_dispose( btree,  363,  363 );
   ii_btree_kv_put_and_dispose( btree,  908,  908 );
   ii_btree_kv_put_and_dispose( btree,  790,  790 );
   ii_btree_kv_put_and_dispose( btree,  354,  354 );
   ii_btree_kv_put_and_dispose( btree,  721,  721 );
   ii_btree_kv_put_and_dispose( btree,  820,  820 );
   ii_btree_kv_put_and_dispose( btree,    5,    5 );
   ii_btree_kv_put_and_dispose( btree,  964,  964 );
   ii_btree_kv_put_and_dispose( btree,  742,  742 );
   ii_btree_kv_put_and_dispose( btree,  689,  689 );
   ii_btree_kv_put_and_dispose( btree,  347,  347 );
   ii_btree_kv_put_and_dispose( btree,  506,  506 );
   ii_btree_kv_put_and_dispose( btree,  491,  491 );
   ii_btree_kv_put_and_dispose( btree,  857,  857 );
   ii_btree_kv_put_and_dispose( btree,  852,  852 );
   ii_btree_kv_put_and_dispose( btree,  771,  771 );
   ii_btree_kv_put_and_dispose( btree,  501,  501 );
   ii_btree_kv_put_and_dispose( btree,  919,  919 );
   ii_btree_kv_put_and_dispose( btree,  221,  221 );
   ii_btree_kv_put_and_dispose( btree,  951,  951 );
   ii_btree_kv_put_and_dispose( btree,  975,  975 );
   ii_btree_kv_put_and_dispose( btree,  795,  795 );
   ii_btree_kv_put_and_dispose( btree,  694,  694 );
   ii_btree_kv_put_and_dispose( btree,  490,  490 );
   ii_btree_kv_put_and_dispose( btree,  281,  281 );
   ii_btree_kv_put_and_dispose( btree,  916,  916 );
   ii_btree_kv_put_and_dispose( btree,   16,   16 );
   ii_btree_kv_put_and_dispose( btree,  259,  259 );
   ii_btree_kv_put_and_dispose( btree,  325,  325 );
   ii_btree_kv_put_and_dispose( btree,  248,  248 );
   ii_btree_kv_put_and_dispose( btree,   55,   55 );
   ii_btree_kv_put_and_dispose( btree,   40,   40 );
   ii_btree_kv_put_and_dispose( btree,  508,  508 );
   ii_btree_kv_put_and_dispose( btree,  197,  197 );
   ii_btree_kv_put_and_dispose( btree,  394,  394 );
   ii_btree_kv_put_and_dispose( btree,  229,  229 );
   ii_btree_kv_put_and_dispose( btree,   18,   18 );
   ii_btree_kv_put_and_dispose( btree,  399,  399 );
   ii_btree_kv_put_and_dispose( btree,  193,  193 );
   ii_btree_kv_put_and_dispose( btree,  112,  112 );
   ii_btree_kv_put_and_dispose( btree,  441,  441 );
   ii_btree_kv_put_and_dispose( btree,  892,  892 );
   ii_btree_kv_put_and_dispose( btree,  971,  971 );
   ii_btree_kv_put_and_dispose( btree,  284,  284 );
   ii_btree_kv_put_and_dispose( btree,  750,  750 );
   ii_btree_kv_put_and_dispose( btree,  175,  175 );
   ii_btree_kv_put_and_dispose( btree,   56,   56 );
   ii_btree_kv_put_and_dispose( btree,  251,  251 );
   ii_btree_kv_put_and_dispose( btree,   94,   94 );
   ii_btree_kv_put_and_dispose( btree,  629,  629 );
   ii_btree_kv_put_and_dispose( btree,  203,  203 );
   ii_btree_kv_put_and_dispose( btree,   69,   69 );
   ii_btree_kv_put_and_dispose( btree,  776,  776 );
   ii_btree_kv_put_and_dispose( btree,  897,  897 );
   ii_btree_kv_put_and_dispose( btree,  912,  912 );
   ii_btree_kv_put_and_dispose( btree,   57,   57 );
   ii_btree_kv_put_and_dispose( btree,  166,  166 );
   ii_btree_kv_put_and_dispose( btree,  280,  280 );
   ii_btree_kv_put_and_dispose( btree,  316,  316 );
   ii_btree_kv_put_and_dispose( btree,  843,  843 );
   ii_btree_kv_put_and_dispose( btree,  880,  880 );
   ii_btree_kv_put_and_dispose( btree,  723,  723 );
   ii_btree_kv_put_and_dispose( btree,  883,  883 );
   ii_btree_kv_put_and_dispose( btree,  389,  389 );
   ii_btree_kv_put_and_dispose( btree,  921,  921 );
   ii_btree_kv_put_and_dispose( btree,  630,  630 );
   ii_btree_kv_put_and_dispose( btree,  618,  618 );
   
   ii_btree_kv_remove( btree, 449 );
   ii_btree_kv_remove( btree, 501 );
   ii_btree_kv_remove( btree, 912 );
   ii_btree_kv_remove( btree, 618 );
   

   //CU_ASSERT( ii_btree_kv_count( btree ) == 20 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_10e
*/

void test_put_and_dispose_10e( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );
   ii_btree_kv_put_and_dispose( btree,  10,  10 );
   ii_btree_kv_put_and_dispose( btree,  20,  20 );
   ii_btree_kv_put_and_dispose( btree,  30,  30 );
   ii_btree_kv_put_and_dispose( btree,  40,  40 );
   ii_btree_kv_put_and_dispose( btree,  50,  50 );
   ii_btree_kv_put_and_dispose( btree,  60,  60 );
   ii_btree_kv_put_and_dispose( btree,  70,  70 );

   ii_btree_kv_remove( btree, 60 );
   
   ii_btree_kv_dispose( &btree );

   return;
}

#define MAX_COUNT 100
#define MAX_VALUE 1000

/**
   test_put_and_dispose_11
*/

void test_put_and_dispose_11( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   btree = ii_btree_kv_make( 3 );

   srand( 103 );

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
         if ( ii_btree_kv_has( btree, n ) == 0 )
         {
            ii_btree_kv_put_and_dispose( btree, n, n );
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
            ii_btree_kv_remove( btree, values[i] );
        	   j = j + 1;
         }
      }

      ii_btree_kv_wipe_out( btree );
   }

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_11a
*/

void test_put_and_dispose_11a( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   btree = ii_btree_kv_make( 44 );

   srand( 10355 );

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
         if ( ii_btree_kv_has( btree, n ) == 0 )
         {
            ii_btree_kv_put_and_dispose( btree, n, n );
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
            ii_btree_kv_remove( btree, values[i] );
        	   j = j + 1;
         }
      }

      ii_btree_kv_wipe_out( btree );
   }

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_11b
*/

void test_put_and_dispose_11b( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   btree = ii_btree_kv_make( 5 );

   srand( 10357 );

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
         if ( ii_btree_kv_has( btree, n ) == 0 )
         {
            ii_btree_kv_put_and_dispose( btree, n, n );
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
            ii_btree_kv_remove( btree, values[i] );
        	   j = j + 1;
         }
      }

      ii_btree_kv_wipe_out( btree );
   }

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_11c
*/

void test_put_and_dispose_11c( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   btree = ii_btree_kv_make( 2 );

   srand( 10359 );

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
         if ( ii_btree_kv_has( btree, n ) == 0 )
         {
            ii_btree_kv_put_and_dispose( btree, n, n );
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
            ii_btree_kv_remove( btree, values[i] );
        	   j = j + 1;
         }
      }

      ii_btree_kv_wipe_out( btree );
   }

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_12
*/

void test_put_and_dispose_12( void )
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

   srand( 104 );

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
         sprintf( str, "%d", n );
         
         key = string_make_from_cstring(  str );
         value = string_make_from_cstring( str );
         
         if ( ss_btree_kv_has( btree, key ) == 0 )
         {
            ss_btree_kv_put_and_dispose( btree, value, key );
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
      while ( j< count )
      {
         i = rand() % count;
         if ( ss_btree_kv_has( btree, values[i] ) == 1 )
         {
            ss_btree_kv_remove( btree, values[i] );
         }
         j = j + 1;
      }

      j = 0;
      while ( j< count )
      {
         if ( ss_btree_kv_has( btree, values[j] ) == 1 )
         {
            ss_btree_kv_remove( btree, values[j] );
         }
         j = j + 1;
      }

      ss_btree_kv_wipe_out( btree );
      
      for ( i=0; i<count; i++ )
      {
         string_deep_dispose( &keys[i] );
         string_deep_dispose( &values[i] );
      }
      
   }

   ss_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_and_dispose_12a
*/

void test_put_and_dispose_12a( void )
{
   ss_btree_kv_t *btree = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;
   string_t *s1va = NULL;
   string_t *s1ka = NULL;
   string_t *s2v = NULL;
   string_t *s2k = NULL;
   string_t *s3v = NULL;
   string_t *s3k = NULL;
   string_t *s4v = NULL;
   string_t *s4k = NULL;

   s1k = string_make_from_cstring( "4" );
   s1v = string_make_from_cstring( "40" );
   
   s1ka = string_make_from_cstring( "4" );
   s1va = string_make_from_cstring( "40" );
   
   s2k = string_make_from_cstring( "2" );
   s2v = string_make_from_cstring( "20" );
   
   s3k = string_make_from_cstring( "6" );
   s3v = string_make_from_cstring( "60" );
   
   s4k = string_make_from_cstring( "4" );
   s4v = string_make_from_cstring( "40" );
      
   btree = ss_btree_kv_make( 3 );
   
   ss_btree_kv_put_and_dispose( btree, s1v, s1k );
   ss_btree_kv_put_and_dispose( btree, s1va, s1ka );
   ss_btree_kv_put_and_dispose( btree, s2v, s2k );
   ss_btree_kv_put_and_dispose( btree, s3v, s3k );
   ss_btree_kv_put_and_dispose( btree, s4v, s4k );

   CU_ASSERT( ss_btree_kv_count( btree ) == 3 );
   
   ss_btree_kv_deep_dispose( &btree );

   return;
}


int
add_test_put_and_dispose( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put_and_dispose", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_and_dispose_1
   add_test_to_suite( p_suite, test_put_and_dispose_1, "test_put_and_dispose_1" );

   // test_put_and_dispose_2
   add_test_to_suite( p_suite, test_put_and_dispose_2, "test_put_and_dispose_2" );

   // test_put_and_dispose_2a
   add_test_to_suite( p_suite, test_put_and_dispose_2a, "test_put_and_dispose_2a" );

   // test_put_and_dispose_3
   add_test_to_suite( p_suite, test_put_and_dispose_3, "test_put_and_dispose_3" );

   // test_put_and_dispose_3a
   add_test_to_suite( p_suite, test_put_and_dispose_3a, "test_put_and_dispose_3a" );

   // test_put_and_dispose_3b
   add_test_to_suite( p_suite, test_put_and_dispose_3b, "test_put_and_dispose_3b" );

   // test_put_and_dispose_3c
   add_test_to_suite( p_suite, test_put_and_dispose_3c, "test_put_and_dispose_3c" );

   // test_put_and_dispose_3d
   add_test_to_suite( p_suite, test_put_and_dispose_3d, "test_put_and_dispose_3d" );

   // test_put_and_dispose_3e
   add_test_to_suite( p_suite, test_put_and_dispose_3e, "test_put_and_dispose_3e" );

   // test_put_and_dispose_4
   add_test_to_suite( p_suite, test_put_and_dispose_4, "test_put_and_dispose_4" );

   // test_put_and_dispose_4a
   add_test_to_suite( p_suite, test_put_and_dispose_4a, "test_put_and_dispose_4a" );

   // test_put_and_dispose_4b
   add_test_to_suite( p_suite, test_put_and_dispose_4b, "test_put_and_dispose_4b" );

   // test_put_and_dispose_4c
   add_test_to_suite( p_suite, test_put_and_dispose_4c, "test_put_and_dispose_4c" );

   // test_put_and_dispose_4d
   add_test_to_suite( p_suite, test_put_and_dispose_4d, "test_put_and_dispose_4d" );

   // test_put_and_dispose_4e
   add_test_to_suite( p_suite, test_put_and_dispose_4e, "test_put_and_dispose_4e" );

   // test_put_and_dispose_4f
   add_test_to_suite( p_suite, test_put_and_dispose_4f, "test_put_and_dispose_4f" );

   // test_put_and_dispose_4g
   add_test_to_suite( p_suite, test_put_and_dispose_4g, "test_put_and_dispose_4g" );

   // test_put_and_dispose_4h
   add_test_to_suite( p_suite, test_put_and_dispose_4h, "test_put_and_dispose_4h" );

   // test_put_and_dispose_4i
   add_test_to_suite( p_suite, test_put_and_dispose_4i, "test_put_and_dispose_4i" );

   // test_put_and_dispose_4j
   add_test_to_suite( p_suite, test_put_and_dispose_4j, "test_put_and_dispose_4j" );

   // test_put_and_dispose_4k
   add_test_to_suite( p_suite, test_put_and_dispose_4k, "test_put_and_dispose_4k" );

   // test_put_and_dispose_4l
   add_test_to_suite( p_suite, test_put_and_dispose_4l, "test_put_and_dispose_4l" );

   // test_put_and_dispose_4m
   add_test_to_suite( p_suite, test_put_and_dispose_4m, "test_put_and_dispose_4m" );

   // test_put_and_dispose_4n
   add_test_to_suite( p_suite, test_put_and_dispose_4n, "test_put_and_dispose_4n" );

   // test_put_and_dispose_4o
   add_test_to_suite( p_suite, test_put_and_dispose_4o, "test_put_and_dispose_4o" );

   // test_put_and_dispose_4p
   add_test_to_suite( p_suite, test_put_and_dispose_4p, "test_put_and_dispose_4p" );

   // test_put_and_dispose_4q
   add_test_to_suite( p_suite, test_put_and_dispose_4q, "test_put_and_dispose_4q" );

   // test_put_and_dispose_4r
   add_test_to_suite( p_suite, test_put_and_dispose_4r, "test_put_and_dispose_4r" );

   // test_put_and_dispose_4s
   add_test_to_suite( p_suite, test_put_and_dispose_4s, "test_put_and_dispose_4s" );

   // test_put_and_dispose_4t
   add_test_to_suite( p_suite, test_put_and_dispose_4t, "test_put_and_dispose_4t" );

   // test_put_and_dispose_4u
   add_test_to_suite( p_suite, test_put_and_dispose_4u, "test_put_and_dispose_4u" );

   // test_put_and_dispose_4v
   add_test_to_suite( p_suite, test_put_and_dispose_4v, "test_put_and_dispose_4v" );

   // test_put_and_dispose_4w
   add_test_to_suite( p_suite, test_put_and_dispose_4w, "test_put_and_dispose_4w" );

   // test_put_and_dispose_5
   add_test_to_suite( p_suite, test_put_and_dispose_5, "test_put_and_dispose_5" );

   // test_put_and_dispose_5a
   add_test_to_suite( p_suite, test_put_and_dispose_5a, "test_put_and_dispose_5a" );

   // test_put_and_dispose_5b
   add_test_to_suite( p_suite, test_put_and_dispose_5b, "test_put_and_dispose_5b" );

   // test_put_and_dispose_5c
   add_test_to_suite( p_suite, test_put_and_dispose_5c, "test_put_and_dispose_5c" );

   // test_put_and_dispose_5d
   add_test_to_suite( p_suite, test_put_and_dispose_5d, "test_put_and_dispose_5d" );

   // test_put_and_dispose_6
   add_test_to_suite( p_suite, test_put_and_dispose_6, "test_put_and_dispose_6" );

   // test_put_and_dispose_6a
   add_test_to_suite( p_suite, test_put_and_dispose_6a, "test_put_and_dispose_6a" );

   // test_put_and_dispose_6b
   add_test_to_suite( p_suite, test_put_and_dispose_6b, "test_put_and_dispose_6b" );

   // test_put_and_dispose_6c
   add_test_to_suite( p_suite, test_put_and_dispose_6c, "test_put_and_dispose_6c" );

   // test_put_and_dispose_6d
   add_test_to_suite( p_suite, test_put_and_dispose_6d, "test_put_and_dispose_6d" );

   // test_put_and_dispose_6e
   add_test_to_suite( p_suite, test_put_and_dispose_6e, "test_put_and_dispose_6e" );

   // test_put_and_dispose_7
   add_test_to_suite( p_suite, test_put_and_dispose_7, "test_put_and_dispose_7" );

   // test_put_and_dispose_7a
   add_test_to_suite( p_suite, test_put_and_dispose_7a, "test_put_and_dispose_7a" );

   // test_put_and_dispose_7b
   add_test_to_suite( p_suite, test_put_and_dispose_7b, "test_put_and_dispose_7b" );

   // test_put_and_dispose_7c
   add_test_to_suite( p_suite, test_put_and_dispose_7c, "test_put_and_dispose_7c" );

   // test_put_and_dispose_7d
   add_test_to_suite( p_suite, test_put_and_dispose_7d, "test_put_and_dispose_7d" );

   // test_put_and_dispose_7e
   add_test_to_suite( p_suite, test_put_and_dispose_7e, "test_put_and_dispose_7e" );

   // test_put_and_dispose_7f
   add_test_to_suite( p_suite, test_put_and_dispose_7f, "test_put_and_dispose_7f" );

   // test_put_and_dispose_8
   add_test_to_suite( p_suite, test_put_and_dispose_8, "test_put_and_dispose_8" );

   // test_put_and_dispose_8a
   add_test_to_suite( p_suite, test_put_and_dispose_8a, "test_put_and_dispose_8a" );

   // test_put_and_dispose_9
   add_test_to_suite( p_suite, test_put_and_dispose_9, "test_put_and_dispose_9" );

   // test_put_and_dispose_9a
   add_test_to_suite( p_suite, test_put_and_dispose_9a, "test_put_and_dispose_9a" );

   // test_put_and_dispose_10
   add_test_to_suite( p_suite, test_put_and_dispose_10, "test_put_and_dispose_10" );

   // test_put_and_dispose_10a
   add_test_to_suite( p_suite, test_put_and_dispose_10a, "test_put_and_dispose_10a" );

   // test_put_and_dispose_10b
   add_test_to_suite( p_suite, test_put_and_dispose_10b, "test_put_and_dispose_10b" );

   // test_put_and_dispose_10c
   add_test_to_suite( p_suite, test_put_and_dispose_10c, "test_put_and_dispose_10c" );

   // test_put_and_dispose_10d
   add_test_to_suite( p_suite, test_put_and_dispose_10d, "test_put_and_dispose_10d" );

   // test_put_and_dispose_10e
   add_test_to_suite( p_suite, test_put_and_dispose_10e, "test_put_and_dispose_10e" );

   // test_put_and_dispose_11
   add_test_to_suite( p_suite, test_put_and_dispose_11, "test_put_and_dispose_11" );
   add_test_to_suite( p_suite, test_put_and_dispose_11a, "test_put_and_dispose_11a" );
   add_test_to_suite( p_suite, test_put_and_dispose_11b, "test_put_and_dispose_11b" );
   add_test_to_suite( p_suite, test_put_and_dispose_11c, "test_put_and_dispose_11c" );

   // test_put_and_dispose_12
   add_test_to_suite( p_suite, test_put_and_dispose_12, "test_put_and_dispose_12" );
   add_test_to_suite( p_suite, test_put_and_dispose_12a, "test_put_and_dispose_12a" );
   
   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

