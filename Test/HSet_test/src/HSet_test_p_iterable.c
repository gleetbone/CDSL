/**
 @file HSet_test_p_iterable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for HSet P_Iterable"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HSet_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_HSet.h"
#include "s_HSet.h"
#include "Protocol_Base.h"
#include "i_Iterable.h"
#include "s_Iterable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_iterable_1
*/

void test_p_iterable_1( void )
{
   i_hset_t *hset = NULL;
   protocol_base_t *pb_hset = NULL;
   
   hset = i_hset_make();
   pb_hset = ( protocol_base_t * ) hset;
   
   CU_ASSERT( hset != NULL );
   CU_ASSERT( pb_hset != NULL );

   i_hset_dispose( &hset );
 
   return;
}

/**
   test_p_iterable_2
*/

void test_p_iterable_2( void )
{
   i_hset_t *hset = NULL;
   protocol_base_t *pb_hset = NULL;

   hset = i_hset_make();
   pb_hset = ( protocol_base_t * ) hset;

   CU_ASSERT( hset != NULL );
   CU_ASSERT( pb_hset != NULL );

   i_hset_deep_dispose( &hset );

   return;
}

/**
   test_p_iterable_3
*/

void test_p_iterable_3( void )
{
   i_hset_t *hset = NULL;
   protocol_base_t *pb_hset = NULL;

   hset = i_hset_make();
   pb_hset = ( protocol_base_t * ) hset;

   CU_ASSERT( hset != NULL );
   CU_ASSERT( pb_hset != NULL );

   i_hset_put( hset, 24 );

   CU_ASSERT( i_iterable_count( pb_hset ) == 1 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_p_iterable_4
*/

void test_p_iterable_4( void )
{
   i_hset_t *hset = NULL;
   protocol_base_t *pb_hset = NULL;

   hset = i_hset_make();
   pb_hset = ( protocol_base_t * ) hset;

   CU_ASSERT( hset != NULL );
   CU_ASSERT( pb_hset != NULL );

   i_hset_put( hset, 24 );
   i_hset_start( hset );

   CU_ASSERT( i_iterable_item( pb_hset) == 24 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_p_iterable_5
*/

void test_p_iterable_5( void )
{
   i_hset_t *hset = NULL;
   protocol_base_t *pb_hset = NULL;

   hset = i_hset_make();
   pb_hset = ( protocol_base_t * ) hset;

   CU_ASSERT( hset != NULL );
   CU_ASSERT( pb_hset != NULL );

   i_hset_put( hset, 24 );

   CU_ASSERT( i_iterable_off( pb_hset ) == 1 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_p_iterable_6
*/

void test_p_iterable_6( void )
{
   i_hset_t *hset = NULL;
   protocol_base_t *pb_hset = NULL;

   hset = i_hset_make();
   pb_hset = ( protocol_base_t * ) hset;

   CU_ASSERT( hset != NULL );
   CU_ASSERT( pb_hset != NULL );

   CU_ASSERT( i_iterable_is_empty( pb_hset ) == 1 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_p_iterable_7
*/

void test_p_iterable_7( void )
{
   i_hset_t *hset = NULL;
   protocol_base_t *pb_hset = NULL;

   hset = i_hset_make();
   pb_hset = ( protocol_base_t * ) hset;

   CU_ASSERT( hset != NULL );
   CU_ASSERT( pb_hset != NULL );

   i_hset_put( hset, 24 );
   i_iterable_start( pb_hset );

   CU_ASSERT( i_iterable_item( pb_hset) == 24 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_p_iterable_8
*/

void test_p_iterable_8( void )
{
   i_hset_t *hset = NULL;
   protocol_base_t *pb_hset = NULL;

   hset = i_hset_make();
   pb_hset = ( protocol_base_t * ) hset;

   CU_ASSERT( hset != NULL );
   CU_ASSERT( pb_hset != NULL );

   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );

   i_hset_start( hset );
   i_iterable_forth( pb_hset );

   CU_ASSERT( i_iterable_item( pb_hset) == 13 );

   i_hset_dispose( &hset );

   return;
}

/**
   test_p_iterable_9
*/

void test_p_iterable_9( void )
{
   s_hset_t *hset = NULL;
   protocol_base_t *pb_hset = NULL;

   hset = s_hset_make();
   pb_hset = ( protocol_base_t * ) hset;

   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   
   CU_ASSERT( hset != NULL );
   CU_ASSERT( pb_hset != NULL );

   s_hset_put( hset, s1 );
   s_hset_put( hset, s2 );

   s_hset_start( hset );
   s_iterable_forth( pb_hset );

   CU_ASSERT( s_iterable_item( pb_hset) == s2 );

   s_hset_deep_dispose( &hset );

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

