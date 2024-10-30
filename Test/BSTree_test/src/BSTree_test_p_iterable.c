/**
 @file BSTree_test_p_iterable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree P_Iterable"
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
#include "Protocol_Base.h"
#include "P_Basic.h"
#include "p_Basic.h"
#include "i_Iterable.h"
#include "s_Iterable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_iterable_1
*/

void test_p_iterable_1( void )
{
   i_bstree_t *bstree = NULL;
   protocol_base_t *pb_bstree = NULL;
   
   bstree = i_bstree_make();
   pb_bstree = ( protocol_base_t * ) bstree;
   
   CU_ASSERT( bstree != NULL );
   CU_ASSERT( pb_bstree != NULL );

   p_basic_dispose( &pb_bstree );
 
   return;
}

/**
   test_p_iterable_2
*/

void test_p_iterable_2( void )
{
   i_bstree_t *bstree = NULL;
   protocol_base_t *pb_bstree = NULL;

   bstree = i_bstree_make();
   pb_bstree = ( protocol_base_t * ) bstree;

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( pb_bstree != NULL );

   p_basic_deep_dispose( &pb_bstree );

   return;
}

/**
   test_p_iterable_3
*/

void test_p_iterable_3( void )
{
   i_bstree_t *bstree = NULL;
   protocol_base_t *pb_bstree = NULL;

   bstree = i_bstree_make();
   pb_bstree = ( protocol_base_t * ) bstree;

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( pb_bstree != NULL );

   i_bstree_put( bstree, 24 );

   CU_ASSERT( i_iterable_count( pb_bstree ) == 1 );

   p_basic_dispose( &pb_bstree );

   return;
}

/**
   test_p_iterable_4
*/

void test_p_iterable_4( void )
{
   i_bstree_t *bstree = NULL;
   protocol_base_t *pb_bstree = NULL;

   bstree = i_bstree_make();
   pb_bstree = ( protocol_base_t * ) bstree;

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( pb_bstree != NULL );

   i_bstree_put( bstree, 24 );
   i_bstree_start( bstree );

   CU_ASSERT( i_iterable_item( pb_bstree) == 24 );

   p_basic_dispose( &pb_bstree );

   return;
}

/**
   test_p_iterable_5
*/

void test_p_iterable_5( void )
{
   i_bstree_t *bstree = NULL;
   protocol_base_t *pb_bstree = NULL;

   bstree = i_bstree_make();
   pb_bstree = ( protocol_base_t * ) bstree;

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( pb_bstree != NULL );

   i_bstree_put( bstree, 24 );

   CU_ASSERT( i_iterable_off( pb_bstree ) == 1 );

   p_basic_dispose( &pb_bstree );

   return;
}

/**
   test_p_iterable_6
*/

void test_p_iterable_6( void )
{
   i_bstree_t *bstree = NULL;
   protocol_base_t *pb_bstree = NULL;

   bstree = i_bstree_make();
   pb_bstree = ( protocol_base_t * ) bstree;

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( pb_bstree != NULL );

   CU_ASSERT( i_iterable_is_empty( pb_bstree ) == 1 );

   p_basic_dispose( &pb_bstree );

   return;
}

/**
   test_p_iterable_7
*/

void test_p_iterable_7( void )
{
   i_bstree_t *bstree = NULL;
   protocol_base_t *pb_bstree = NULL;

   bstree = i_bstree_make();
   pb_bstree = ( protocol_base_t * ) bstree;

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( pb_bstree != NULL );

   i_bstree_put( bstree, 24 );
   i_iterable_start( pb_bstree );

   CU_ASSERT( i_iterable_item( pb_bstree) == 24 );

   p_basic_dispose( &pb_bstree );

   return;
}

/**
   test_p_iterable_8
*/

void test_p_iterable_8( void )
{
   i_bstree_t *bstree = NULL;
   protocol_base_t *pb_bstree = NULL;

   bstree = i_bstree_make();
   pb_bstree = ( protocol_base_t * ) bstree;

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( pb_bstree != NULL );

   i_bstree_put( bstree, 24 );
   i_bstree_put( bstree, 13 );

   i_bstree_start( bstree );
   i_iterable_forth( pb_bstree );

   CU_ASSERT( i_iterable_item( pb_bstree) == 24 );

   p_basic_dispose( &pb_bstree );

   return;
}

/**
   test_p_iterable_9
*/

void test_p_iterable_9( void )
{
   s_bstree_t *bstree = NULL;
   protocol_base_t *pb_bstree = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   
   bstree = s_bstree_make();
   pb_bstree = ( protocol_base_t * ) bstree;

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( pb_bstree != NULL );

   s_bstree_put( bstree, s2 );
   s_bstree_put( bstree, s1 );

   s_bstree_start( bstree );
   s_iterable_forth( pb_bstree );

   CU_ASSERT( s_iterable_item( pb_bstree) == s2 );

   p_basic_deep_dispose( &pb_bstree );

   return;
}

int
add_test_p_iterable( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_p_iterable", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_p_iterable_1
   add_test_to_suite( p_suite, test_p_iterable_1, "test_p_iterable_1" );

   // test_p_iterable_2
   add_test_to_suite( p_suite, test_p_iterable_2, "test_p_iterable_2" );

   // test_p_iterable_3
   add_test_to_suite( p_suite, test_p_iterable_3, "test_p_iterable_3" );

   // test_p_iterable_4
   add_test_to_suite( p_suite, test_p_iterable_4, "test_p_iterable_4" );

   // test_p_iterable_5
   add_test_to_suite( p_suite, test_p_iterable_5, "test_p_iterable_5" );

   // test_p_iterable_6
   add_test_to_suite( p_suite, test_p_iterable_6, "test_p_iterable_6" );

   // test_p_iterable_7
   add_test_to_suite( p_suite, test_p_iterable_7, "test_p_iterable_7" );

   // test_p_iterable_8
   add_test_to_suite( p_suite, test_p_iterable_8, "test_p_iterable_8" );

   // test_p_iterable_9
   add_test_to_suite( p_suite, test_p_iterable_9, "test_p_iterable_9" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

