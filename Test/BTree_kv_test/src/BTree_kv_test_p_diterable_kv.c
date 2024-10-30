/**
 @file AList_test_p_diterable_kv.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AList P_DIterable"
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
#include "Protocol_Base.h"
#include "ii_DIterable_kv.h"
#include "ss_DIterable_kv.h"
#include "p_Basic.h"

#include "ss_DIterable_kv.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_diterable_kv_1
*/

void test_p_diterable_kv_1( void )
{
   ii_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;
   
   btree = ii_btree_kv_make( 4 );
   pb_btree = ( protocol_base_t * ) btree;
   
   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   p_basic_dispose( &pb_btree );
 
   return;
}

/**
   test_p_diterable_kv_2
*/

void test_p_diterable_kv_2( void )
{
   ii_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;

   btree = ii_btree_kv_make( 4 );
   pb_btree = ( protocol_base_t * ) btree;

   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   p_basic_deep_dispose( &pb_btree );

   return;
}

/**
   test_p_diterable_kv_3
*/

void test_p_diterable_kv_3( void )
{
   ii_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;

   btree = ii_btree_kv_make( 4 );
   pb_btree = ( protocol_base_t * ) btree;

   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   ii_btree_kv_put( btree, 24, 24 );

   CU_ASSERT( ii_diterable_kv_count( pb_btree ) == 1 );

   p_basic_dispose( &pb_btree );

   return;
}

/**
   test_p_diterable_kv_4
*/

void test_p_diterable_kv_4( void )
{
   ii_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;

   btree = ii_btree_kv_make( 4 );
   pb_btree = ( protocol_base_t * ) btree;

   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   ii_btree_kv_put( btree, 24, 24 );
   ii_btree_kv_start( btree );

   CU_ASSERT( ii_diterable_kv_value( pb_btree) == 24 );

   p_basic_dispose( &pb_btree );

   return;
}

/**
   test_p_diterable_kv_5
*/

void test_p_diterable_kv_5( void )
{
   ii_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;

   btree = ii_btree_kv_make( 4 );
   pb_btree = ( protocol_base_t * ) btree;

   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   ii_btree_kv_put( btree, 24, 24 );

   CU_ASSERT( ii_diterable_kv_off( pb_btree ) == 1 );

   p_basic_dispose( &pb_btree );

   return;
}

/**
   test_p_diterable_kv_6
*/

void test_p_diterable_kv_6( void )
{
   ii_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;

   btree = ii_btree_kv_make( 4 );
   pb_btree = ( protocol_base_t * ) btree;

   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   CU_ASSERT( ii_diterable_kv_is_empty( pb_btree ) == 1 );

   p_basic_dispose( &pb_btree );

   return;
}

/**
   test_p_diterable_kv_7
*/

void test_p_diterable_kv_7( void )
{
   ii_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;

   btree = ii_btree_kv_make( 4 );
   pb_btree = ( protocol_base_t * ) btree;

   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   ii_btree_kv_put( btree, 24, 24 );
   ii_diterable_kv_start( pb_btree );

   CU_ASSERT( ii_diterable_kv_value( pb_btree ) == 24 );

   p_basic_dispose( &pb_btree );

   return;
}

/**
   test_p_diterable_kv_8
*/

void test_p_diterable_kv_8( void )
{
   ii_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;

   btree = ii_btree_kv_make( 4 );
   pb_btree = ( protocol_base_t * ) btree;

   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   ii_btree_kv_put( btree, 24, 24 );
   ii_btree_kv_put( btree, 13, 13 );

   ii_btree_kv_start( btree );
   ii_diterable_kv_forth( pb_btree );

   CU_ASSERT( ii_diterable_kv_value( pb_btree ) == 24 );

   p_basic_dispose( &pb_btree );

   return;
}

/**
   test_p_diterable_kv_9
*/

void test_p_diterable_kv_9( void )
{
   ii_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;

   btree = ii_btree_kv_make( 4 );
   pb_btree = ( protocol_base_t * ) btree;

   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   ii_btree_kv_put( btree, 24, 24 );
   ii_btree_kv_put( btree, 13, 13 );
   ii_diterable_kv_finish( pb_btree );

   CU_ASSERT( ii_diterable_kv_value( pb_btree ) == 24 );

   p_basic_dispose( &pb_btree );

   return;
}

/**
   test_p_diterable_kv_10
*/

void test_p_diterable_kv_10( void )
{
   ii_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;

   btree = ii_btree_kv_make( 4 );
   pb_btree = ( protocol_base_t * ) btree;

   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   ii_btree_kv_put( btree, 24, 24 );
   ii_btree_kv_put( btree, 13, 13 );

   ii_btree_kv_finish( btree );
   ii_diterable_kv_back( pb_btree );

   CU_ASSERT( ii_diterable_kv_value( pb_btree ) == 13 );

   p_basic_dispose( &pb_btree );

   return;
}

/**
   test_p_diterable_kv_11
*/

void test_p_diterable_kv_11( void )
{
   ss_btree_kv_t *btree = NULL;
   protocol_base_t *pb_btree = NULL;
   string_t *s1v = NULL;
   string_t *s1k = NULL;
   string_t *s2v = NULL;
   string_t *s2k = NULL;

   s1k = string_make_from_cstring( "4" );
   s1v = string_make_from_cstring( "40" );
   
   s2k = string_make_from_cstring( "2" );
   s2v = string_make_from_cstring( "20" );
   
   btree = ss_btree_kv_make( 4 );
   
   pb_btree = ( protocol_base_t * ) btree;

   CU_ASSERT( btree != NULL );
   CU_ASSERT( pb_btree != NULL );

   ss_btree_kv_put( btree, s1v, s1k );
   ss_btree_kv_put( btree, s2v, s2k );
   
   ss_btree_kv_finish( btree );
   ss_diterable_kv_back( pb_btree );

   CU_ASSERT( string_is_equal( ss_diterable_kv_value( pb_btree ), s2v ) == 1 );

   p_basic_deep_dispose( &pb_btree );

   return;
}

int
add_test_p_diterable_kv( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_p_diterable_kv", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_p_diterable_kv_1
   add_test_to_suite( p_suite, test_p_diterable_kv_1, "test_p_diterable_kv_1" );

   // test_p_diterable_kv_2
   add_test_to_suite( p_suite, test_p_diterable_kv_2, "test_p_diterable_kv_2" );

   // test_p_diterable_kv_3
   add_test_to_suite( p_suite, test_p_diterable_kv_3, "test_p_diterable_kv_3" );

   // test_p_diterable_kv_4
   add_test_to_suite( p_suite, test_p_diterable_kv_4, "test_p_diterable_kv_4" );

   // test_p_diterable_kv_5
   add_test_to_suite( p_suite, test_p_diterable_kv_5, "test_p_diterable_kv_5" );

   // test_p_diterable_kv_6
   add_test_to_suite( p_suite, test_p_diterable_kv_6, "test_p_diterable_kv_6" );

   // test_p_diterable_kv_7
   add_test_to_suite( p_suite, test_p_diterable_kv_7, "test_p_diterable_kv_7" );

   // test_p_diterable_kv_8
   add_test_to_suite( p_suite, test_p_diterable_kv_8, "test_p_diterable_kv_8" );

   // test_p_diterable_kv_9
   add_test_to_suite( p_suite, test_p_diterable_kv_9, "test_p_diterable_kv_9" );

   // test_p_diterable_kv_10
   add_test_to_suite( p_suite, test_p_diterable_kv_10, "test_p_diterable_kv_10" );

   // test_p_diterable_kv_11
   add_test_to_suite( p_suite, test_p_diterable_kv_11, "test_p_diterable_kv_11" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

