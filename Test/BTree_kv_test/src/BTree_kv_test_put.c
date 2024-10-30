/**
 @file BTree_test_put.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BTree_kv_put"
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
   test_put_1
*/

void test_put_1( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 1 );
   CU_ASSERT( ii_btree_kv_is_empty( btree ) == 0 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_2
*/

void test_put_2( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 2 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_2a
*/

void test_put_2a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 2 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_3
*/

void test_put_3( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_3a
*/

void test_put_3a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_3b
*/

void test_put_3b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_3c
*/

void test_put_3c( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_3d
*/

void test_put_3d( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_3e
*/

void test_put_3e( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 3 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4
*/

void test_put_4( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4a
*/

void test_put_4a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4b
*/

void test_put_4b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4c
*/

void test_put_4c( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4d
*/

void test_put_4d( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4e
*/

void test_put_4e( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4f
*/

void test_put_4f( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4g
*/

void test_put_4g( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4h
*/

void test_put_4h( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4i
*/

void test_put_4i( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4j
*/

void test_put_4j( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4k
*/

void test_put_4k( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4l
*/

void test_put_4l( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4m
*/

void test_put_4m( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4n
*/

void test_put_4n( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4o
*/

void test_put_4o( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4p
*/

void test_put_4p( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4q
*/

void test_put_4q( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4r
*/

void test_put_4r( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4s
*/

void test_put_4s( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4t
*/

void test_put_4t( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 30, 3 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4u
*/

void test_put_4u( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4v
*/

void test_put_4v( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_4w
*/

void test_put_4w( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 4 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_5
*/

void test_put_5( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 5 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_5a
*/

void test_put_5a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 5 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_5b
*/

void test_put_5b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 5 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_5c
*/

void test_put_5c( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 5 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_5d
*/

void test_put_5d( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 5 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_6
*/

void test_put_6( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 60, 6 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_6a
*/

void test_put_6a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 50, 5 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_6b
*/

void test_put_6b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_6c
*/

void test_put_6c( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_6d
*/

void test_put_6d( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_6e
*/

void test_put_6e( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 6 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_7
*/

void test_put_7( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 70, 7 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_7a
*/

void test_put_7a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 70, 7 );
   ii_btree_kv_put( btree, 60, 6 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_7b
*/

void test_put_7b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 70, 7 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 60, 6 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_7c
*/

void test_put_7c( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 70, 7 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 60, 6 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_7d
*/

void test_put_7d( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 70, 7 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 60, 6 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_7e
*/

void test_put_7e( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 70, 7 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 60, 6 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_7f
*/

void test_put_7f( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 70, 7 );
   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 60, 6 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 7 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_8
*/

void test_put_8( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 10, 1 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 70, 7 );
   ii_btree_kv_put( btree, 80, 8 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 8 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_8a
*/

void test_put_8a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 80, 8 );
   ii_btree_kv_put( btree, 70, 7 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 8 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_9
*/

void test_put_9( void )
{
   ii_btree_kv_t *btree = NULL;

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

   CU_ASSERT( ii_btree_kv_count( btree ) == 9 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_9a
*/

void test_put_9a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 90, 9 );
   ii_btree_kv_put( btree, 80, 8 );
   ii_btree_kv_put( btree, 70, 7 );
   ii_btree_kv_put( btree, 60, 6 );
   ii_btree_kv_put( btree, 50, 5 );
   ii_btree_kv_put( btree, 40, 4 );
   ii_btree_kv_put( btree, 30, 3 );
   ii_btree_kv_put( btree, 20, 2 );
   ii_btree_kv_put( btree, 10, 1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 9 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_10
*/

void test_put_10( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree,  10,  1 );
   ii_btree_kv_put( btree,  20,  2 );
   ii_btree_kv_put( btree,  30,  3 );
   ii_btree_kv_put( btree,  40,  4 );
   ii_btree_kv_put( btree,  50,  5 );
   ii_btree_kv_put( btree,  60,  6 );
   ii_btree_kv_put( btree,  70,  7 );
   ii_btree_kv_put( btree,  80,  8 );
   ii_btree_kv_put( btree,  90,  9 );
   ii_btree_kv_put( btree, 100, 10 );
   ii_btree_kv_put( btree, 110, 11 );
   ii_btree_kv_put( btree, 120, 12 );
   ii_btree_kv_put( btree, 130, 13 );
   ii_btree_kv_put( btree, 140, 14 );
   ii_btree_kv_put( btree, 150, 15 );
   ii_btree_kv_put( btree, 160, 16 );
   ii_btree_kv_put( btree, 170, 17 );
   ii_btree_kv_put( btree, 180, 18 );
   ii_btree_kv_put( btree, 190, 19 );
   ii_btree_kv_put( btree, 200, 20 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 20 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_10a
*/

void test_put_10a( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree, 200, 20 );
   ii_btree_kv_put( btree, 190, 19 );
   ii_btree_kv_put( btree, 180, 18 );
   ii_btree_kv_put( btree, 170, 17 );
   ii_btree_kv_put( btree, 160, 16 );
   ii_btree_kv_put( btree, 150, 15 );
   ii_btree_kv_put( btree, 140, 14 );
   ii_btree_kv_put( btree, 130, 13 );
   ii_btree_kv_put( btree, 120, 12 );
   ii_btree_kv_put( btree, 110, 11 );
   ii_btree_kv_put( btree, 100, 10 );
   ii_btree_kv_put( btree,  90,  9 );
   ii_btree_kv_put( btree,  80,  8 );
   ii_btree_kv_put( btree,  70,  7 );
   ii_btree_kv_put( btree,  60,  6 );
   ii_btree_kv_put( btree,  50,  5 );
   ii_btree_kv_put( btree,  40,  4 );
   ii_btree_kv_put( btree,  30,  3 );
   ii_btree_kv_put( btree,  20,  2 );
   ii_btree_kv_put( btree,  10,  1 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 20 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_10b
*/

void test_put_10b( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );
   ii_btree_kv_put( btree,  10,  1 );
   ii_btree_kv_put( btree,  20,  2 );
   ii_btree_kv_put( btree,  30,  3 );
   ii_btree_kv_put( btree,  40,  4 );
   ii_btree_kv_put( btree,  50,  5 );
   ii_btree_kv_put( btree,  60,  6 );
   ii_btree_kv_put( btree,  70,  7 );
   ii_btree_kv_put( btree,  80,  8 );
   ii_btree_kv_put( btree,  90,  9 );
   ii_btree_kv_put( btree, 100, 10 );
   ii_btree_kv_put( btree, 200, 20 );
   ii_btree_kv_put( btree, 190, 19 );
   ii_btree_kv_put( btree, 180, 18 );
   ii_btree_kv_put( btree, 170, 17 );
   ii_btree_kv_put( btree, 160, 16 );
   ii_btree_kv_put( btree, 150, 15 );
   ii_btree_kv_put( btree, 140, 14 );
   ii_btree_kv_put( btree, 130, 13 );
   ii_btree_kv_put( btree, 120, 12 );
   ii_btree_kv_put( btree, 110, 11 );

   CU_ASSERT( ii_btree_kv_count( btree ) == 20 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_10c
*/

void test_put_10c( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree,  962,  962 );
   ii_btree_kv_put( btree,  775,  775 );
   ii_btree_kv_put( btree,  307,  307 );
   ii_btree_kv_put( btree,  766,  766 );
   ii_btree_kv_put( btree,  243,  243 );
   ii_btree_kv_put( btree,  349,  349 );
   ii_btree_kv_put( btree,  340,  340 );
   ii_btree_kv_put( btree,  654,  654 );
   ii_btree_kv_put( btree,   37,   37 );
   ii_btree_kv_put( btree,  359,  359 );
   ii_btree_kv_put( btree,  630,  630 );
   ii_btree_kv_put( btree,  141,  141 );
   ii_btree_kv_put( btree,  332,  332 );
   ii_btree_kv_put( btree,   18,   18 );
   ii_btree_kv_put( btree,   48,   48 );
   ii_btree_kv_put( btree,  275,  275 );
   ii_btree_kv_put( btree,  666,  666 );
   ii_btree_kv_put( btree,  832,  832 );
   ii_btree_kv_put( btree,  263,  263 );
   ii_btree_kv_put( btree,  462,  462 );
   ii_btree_kv_put( btree,  793,  793 );
   ii_btree_kv_put( btree,  129,  129 );
   ii_btree_kv_put( btree,  347,  347 );
   ii_btree_kv_put( btree,  787,  787 );
   ii_btree_kv_put( btree,  494,  494 );
   ii_btree_kv_put( btree,  521,  521 );
   ii_btree_kv_put( btree,  790,  790 );
   ii_btree_kv_put( btree,  693,  693 );
   ii_btree_kv_put( btree,   61,   61 );
   ii_btree_kv_put( btree,  629,  629 );
   ii_btree_kv_put( btree,  848,  848 );
   ii_btree_kv_put( btree,  563,  563 );
   ii_btree_kv_put( btree,  756,  756 );
   ii_btree_kv_put( btree,  507,  507 );
   ii_btree_kv_put( btree,  329,  329 );
   ii_btree_kv_put( btree,  654,  654 );
   ii_btree_kv_put( btree,  351,  351 );
   ii_btree_kv_put( btree,  208, 208 );
   ii_btree_kv_put( btree,   21,  21 );
   ii_btree_kv_put( btree,    5,   5 );
   ii_btree_kv_put( btree,  246,  246 );
   ii_btree_kv_put( btree,  380,  380 );
   ii_btree_kv_put( btree,  635,  635 );
   ii_btree_kv_put( btree,  739,  739 );
   ii_btree_kv_put( btree,  712,  712 );
   ii_btree_kv_put( btree,    6,    6 );
   ii_btree_kv_put( btree,  788,  788 );
   ii_btree_kv_put( btree,  339,  339 );
   ii_btree_kv_put( btree,  672,  672 );
   ii_btree_kv_put( btree,  620,  620 );
   ii_btree_kv_put( btree,  955,  955 );
   
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
   test_put_10d
*/

void test_put_10d( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );

   ii_btree_kv_put( btree,  353,  353 );
   ii_btree_kv_put( btree,  638,  638 );
   ii_btree_kv_put( btree,  460,  460 );
   ii_btree_kv_put( btree,  678,  678 );
   ii_btree_kv_put( btree,  651,  651 );
   ii_btree_kv_put( btree,  243,  243 );
   ii_btree_kv_put( btree,  922,  922 );
   ii_btree_kv_put( btree,  684,  684 );
   ii_btree_kv_put( btree,  383,  383 );
   ii_btree_kv_put( btree,  764,  764 );
   ii_btree_kv_put( btree,  450,  450 );
   ii_btree_kv_put( btree,  158,  158 );
   ii_btree_kv_put( btree,  993,  993 );
   ii_btree_kv_put( btree,  280,  280 );
   ii_btree_kv_put( btree,  292,  292 );
   ii_btree_kv_put( btree,  715,  715 );
   ii_btree_kv_put( btree,  449,  449 );
   ii_btree_kv_put( btree,   98,   98 );
   ii_btree_kv_put( btree,   56,   56 );
   ii_btree_kv_put( btree,  574,  574 );
   ii_btree_kv_put( btree,  743,  743 );
   ii_btree_kv_put( btree,  515,  515 );
   ii_btree_kv_put( btree,  134,  134 );
   ii_btree_kv_put( btree,  222,  222 );
   ii_btree_kv_put( btree,  526,  526 );
   ii_btree_kv_put( btree,  977,  977 );
   ii_btree_kv_put( btree,  408,  408 );
   ii_btree_kv_put( btree,  879,  879 );
   ii_btree_kv_put( btree,  796,  796 );
   ii_btree_kv_put( btree,  363,  363 );
   ii_btree_kv_put( btree,  908,  908 );
   ii_btree_kv_put( btree,  790,  790 );
   ii_btree_kv_put( btree,  354,  354 );
   ii_btree_kv_put( btree,  721,  721 );
   ii_btree_kv_put( btree,  820,  820 );
   ii_btree_kv_put( btree,    5,    5 );
   ii_btree_kv_put( btree,  964,  964 );
   ii_btree_kv_put( btree,  742,  742 );
   ii_btree_kv_put( btree,  689,  689 );
   ii_btree_kv_put( btree,  347,  347 );
   ii_btree_kv_put( btree,  506,  506 );
   ii_btree_kv_put( btree,  491,  491 );
   ii_btree_kv_put( btree,  857,  857 );
   ii_btree_kv_put( btree,  852,  852 );
   ii_btree_kv_put( btree,  771,  771 );
   ii_btree_kv_put( btree,  501,  501 );
   ii_btree_kv_put( btree,  919,  919 );
   ii_btree_kv_put( btree,  221,  221 );
   ii_btree_kv_put( btree,  951,  951 );
   ii_btree_kv_put( btree,  975,  975 );
   ii_btree_kv_put( btree,  795,  795 );
   ii_btree_kv_put( btree,  694,  694 );
   ii_btree_kv_put( btree,  490,  490 );
   ii_btree_kv_put( btree,  281,  281 );
   ii_btree_kv_put( btree,  916,  916 );
   ii_btree_kv_put( btree,   16,   16 );
   ii_btree_kv_put( btree,  259,  259 );
   ii_btree_kv_put( btree,  325,  325 );
   ii_btree_kv_put( btree,  248,  248 );
   ii_btree_kv_put( btree,   55,   55 );
   ii_btree_kv_put( btree,   40,   40 );
   ii_btree_kv_put( btree,  508,  508 );
   ii_btree_kv_put( btree,  197,  197 );
   ii_btree_kv_put( btree,  394,  394 );
   ii_btree_kv_put( btree,  229,  229 );
   ii_btree_kv_put( btree,   18,   18 );
   ii_btree_kv_put( btree,  399,  399 );
   ii_btree_kv_put( btree,  193,  193 );
   ii_btree_kv_put( btree,  112,  112 );
   ii_btree_kv_put( btree,  441,  441 );
   ii_btree_kv_put( btree,  892,  892 );
   ii_btree_kv_put( btree,  971,  971 );
   ii_btree_kv_put( btree,  284,  284 );
   ii_btree_kv_put( btree,  750,  750 );
   ii_btree_kv_put( btree,  175,  175 );
   ii_btree_kv_put( btree,   56,   56 );
   ii_btree_kv_put( btree,  251,  251 );
   ii_btree_kv_put( btree,   94,   94 );
   ii_btree_kv_put( btree,  629,  629 );
   ii_btree_kv_put( btree,  203,  203 );
   ii_btree_kv_put( btree,   69,   69 );
   ii_btree_kv_put( btree,  776,  776 );
   ii_btree_kv_put( btree,  897,  897 );
   ii_btree_kv_put( btree,  912,  912 );
   ii_btree_kv_put( btree,   57,   57 );
   ii_btree_kv_put( btree,  166,  166 );
   ii_btree_kv_put( btree,  280,  280 );
   ii_btree_kv_put( btree,  316,  316 );
   ii_btree_kv_put( btree,  843,  843 );
   ii_btree_kv_put( btree,  880,  880 );
   ii_btree_kv_put( btree,  723,  723 );
   ii_btree_kv_put( btree,  883,  883 );
   ii_btree_kv_put( btree,  389,  389 );
   ii_btree_kv_put( btree,  921,  921 );
   ii_btree_kv_put( btree,  630,  630 );
   ii_btree_kv_put( btree,  618,  618 );
   
   ii_btree_kv_remove( btree, 449 );
   ii_btree_kv_remove( btree, 501 );
   ii_btree_kv_remove( btree, 912 );
   ii_btree_kv_remove( btree, 618 );
   

   //CU_ASSERT( ii_btree_kv_count( btree ) == 20 );

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_10e
*/

void test_put_10e( void )
{
   ii_btree_kv_t *btree = NULL;

   btree = ii_btree_kv_make( 3 );
   ii_btree_kv_put( btree,  10,  10 );
   ii_btree_kv_put( btree,  20,  20 );
   ii_btree_kv_put( btree,  30,  30 );
   ii_btree_kv_put( btree,  40,  40 );
   ii_btree_kv_put( btree,  50,  50 );
   ii_btree_kv_put( btree,  60,  60 );
   ii_btree_kv_put( btree,  70,  70 );

   ii_btree_kv_remove( btree, 60 );
   
   ii_btree_kv_dispose( &btree );

   return;
}

#define MAX_COUNT 100
#define MAX_VALUE 1000

/**
   test_put_11
*/

void test_put_11( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   btree = ii_btree_kv_make( 3 );

   srand( 102 );

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
   test_put_11a
*/

void test_put_11a( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   btree = ii_btree_kv_make( 4 );

   srand( 1021 );

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
   test_put_11b
*/

void test_put_11b( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   btree = ii_btree_kv_make( 5 );

   srand( 1023 );

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
   test_put_11c
*/

void test_put_11c( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   btree = ii_btree_kv_make( 2 );

   srand( 1023 );

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
   test_put_11d
*/

void test_put_11d( void )
{
   ii_btree_kv_t *btree = NULL;
   int32_t count = 0;
   int32_t i = 0;
   int32_t j = 0;
   int32_t k = 0;
   int32_t n = 0;
   int32_t values[MAX_COUNT] = {0};

   btree = ii_btree_kv_make( 3 );

   srand( 102 );

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
            ii_btree_kv_put( btree, n, n );
            values[i] = n;
            i = i + 1;
         }
      }

      j = 0;
      while ( j< count )
      {
         i = rand() % count;
         if ( ii_btree_kv_has( btree, values[i] ) == 1 )
         {
            ii_btree_kv_remove( btree, values[i] );
         }
         j = j + 1;
      }

      j = 0;
      while ( j< count )
      {
         if ( ii_btree_kv_has( btree, values[j] ) == 1 )
         {
            ii_btree_kv_remove( btree, values[j] );
         }
         j = j + 1;
      }

      ii_btree_kv_wipe_out( btree );
   }

   ii_btree_kv_dispose( &btree );

   return;
}

/**
   test_put_12
*/

void test_put_12( void )
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
         str[0] = 0;
         sprintf( str, "%d", n );
         
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


int
add_test_put( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_put", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_put_1
   add_test_to_suite( p_suite, test_put_1, "test_put_1" );

   // test_put_2
   add_test_to_suite( p_suite, test_put_2, "test_put_2" );

   // test_put_2a
   add_test_to_suite( p_suite, test_put_2a, "test_put_2a" );

   // test_put_3
   add_test_to_suite( p_suite, test_put_3, "test_put_3" );

   // test_put_3a
   add_test_to_suite( p_suite, test_put_3a, "test_put_3a" );

   // test_put_3b
   add_test_to_suite( p_suite, test_put_3b, "test_put_3b" );

   // test_put_3c
   add_test_to_suite( p_suite, test_put_3c, "test_put_3c" );

   // test_put_3d
   add_test_to_suite( p_suite, test_put_3d, "test_put_3d" );

   // test_put_3e
   add_test_to_suite( p_suite, test_put_3e, "test_put_3e" );

   // test_put_4
   add_test_to_suite( p_suite, test_put_4, "test_put_4" );

   // test_put_4a
   add_test_to_suite( p_suite, test_put_4a, "test_put_4a" );

   // test_put_4b
   add_test_to_suite( p_suite, test_put_4b, "test_put_4b" );

   // test_put_4c
   add_test_to_suite( p_suite, test_put_4c, "test_put_4c" );

   // test_put_4d
   add_test_to_suite( p_suite, test_put_4d, "test_put_4d" );

   // test_put_4e
   add_test_to_suite( p_suite, test_put_4e, "test_put_4e" );

   // test_put_4f
   add_test_to_suite( p_suite, test_put_4f, "test_put_4f" );

   // test_put_4g
   add_test_to_suite( p_suite, test_put_4g, "test_put_4g" );

   // test_put_4h
   add_test_to_suite( p_suite, test_put_4h, "test_put_4h" );

   // test_put_4i
   add_test_to_suite( p_suite, test_put_4i, "test_put_4i" );

   // test_put_4j
   add_test_to_suite( p_suite, test_put_4j, "test_put_4j" );

   // test_put_4k
   add_test_to_suite( p_suite, test_put_4k, "test_put_4k" );

   // test_put_4l
   add_test_to_suite( p_suite, test_put_4l, "test_put_4l" );

   // test_put_4m
   add_test_to_suite( p_suite, test_put_4m, "test_put_4m" );

   // test_put_4n
   add_test_to_suite( p_suite, test_put_4n, "test_put_4n" );

   // test_put_4o
   add_test_to_suite( p_suite, test_put_4o, "test_put_4o" );

   // test_put_4p
   add_test_to_suite( p_suite, test_put_4p, "test_put_4p" );

   // test_put_4q
   add_test_to_suite( p_suite, test_put_4q, "test_put_4q" );

   // test_put_4r
   add_test_to_suite( p_suite, test_put_4r, "test_put_4r" );

   // test_put_4s
   add_test_to_suite( p_suite, test_put_4s, "test_put_4s" );

   // test_put_4t
   add_test_to_suite( p_suite, test_put_4t, "test_put_4t" );

   // test_put_4u
   add_test_to_suite( p_suite, test_put_4u, "test_put_4u" );

   // test_put_4v
   add_test_to_suite( p_suite, test_put_4v, "test_put_4v" );

   // test_put_4w
   add_test_to_suite( p_suite, test_put_4w, "test_put_4w" );

   // test_put_5
   add_test_to_suite( p_suite, test_put_5, "test_put_5" );

   // test_put_5a
   add_test_to_suite( p_suite, test_put_5a, "test_put_5a" );

   // test_put_5b
   add_test_to_suite( p_suite, test_put_5b, "test_put_5b" );

   // test_put_5c
   add_test_to_suite( p_suite, test_put_5c, "test_put_5c" );

   // test_put_5d
   add_test_to_suite( p_suite, test_put_5d, "test_put_5d" );

   // test_put_6
   add_test_to_suite( p_suite, test_put_6, "test_put_6" );

   // test_put_6a
   add_test_to_suite( p_suite, test_put_6a, "test_put_6a" );

   // test_put_6b
   add_test_to_suite( p_suite, test_put_6b, "test_put_6b" );

   // test_put_6c
   add_test_to_suite( p_suite, test_put_6c, "test_put_6c" );

   // test_put_6d
   add_test_to_suite( p_suite, test_put_6d, "test_put_6d" );

   // test_put_6e
   add_test_to_suite( p_suite, test_put_6e, "test_put_6e" );

   // test_put_7
   add_test_to_suite( p_suite, test_put_7, "test_put_7" );

   // test_put_7a
   add_test_to_suite( p_suite, test_put_7a, "test_put_7a" );

   // test_put_7b
   add_test_to_suite( p_suite, test_put_7b, "test_put_7b" );

   // test_put_7c
   add_test_to_suite( p_suite, test_put_7c, "test_put_7c" );

   // test_put_7d
   add_test_to_suite( p_suite, test_put_7d, "test_put_7d" );

   // test_put_7e
   add_test_to_suite( p_suite, test_put_7e, "test_put_7e" );

   // test_put_7f
   add_test_to_suite( p_suite, test_put_7f, "test_put_7f" );

   // test_put_8
   add_test_to_suite( p_suite, test_put_8, "test_put_8" );

   // test_put_8a
   add_test_to_suite( p_suite, test_put_8a, "test_put_8a" );

   // test_put_9
   add_test_to_suite( p_suite, test_put_9, "test_put_9" );

   // test_put_9a
   add_test_to_suite( p_suite, test_put_9a, "test_put_9a" );

   // test_put_10
   add_test_to_suite( p_suite, test_put_10, "test_put_10" );

   // test_put_10a
   add_test_to_suite( p_suite, test_put_10a, "test_put_10a" );

   // test_put_10b
   add_test_to_suite( p_suite, test_put_10b, "test_put_10b" );

   // test_put_10c
   add_test_to_suite( p_suite, test_put_10c, "test_put_10c" );

   // test_put_10d
   add_test_to_suite( p_suite, test_put_10d, "test_put_10d" );

   // test_put_10e
   add_test_to_suite( p_suite, test_put_10e, "test_put_10e" );

   // test_put_11
   add_test_to_suite( p_suite, test_put_11, "test_put_11" );

   // test_put_11a
   add_test_to_suite( p_suite, test_put_11a, "test_put_11a" );

   // test_put_11b
   add_test_to_suite( p_suite, test_put_11b, "test_put_11b" );

   // test_put_11c
   add_test_to_suite( p_suite, test_put_11c, "test_put_11c" );

   // test_put_11d
   add_test_to_suite( p_suite, test_put_11d, "test_put_11d" );

   // test_put_12
   add_test_to_suite( p_suite, test_put_12, "test_put_12" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

