/**
 @file AList_test_p_diterable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AList P_DIterable"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AList_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_AList.h"
#include "Protocol_Base.h"
#include "i_DIterable.h"

#include "s_AList.h"
#include "s_DIterable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_diterable_1
*/

void test_p_diterable_1( void )
{
   i_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;
   
   list = i_alist_make();
   pb_list = ( protocol_base_t * ) list;
   
   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_alist_dispose( &list );
 
   return;
}

/**
   test_p_diterable_2
*/

void test_p_diterable_2( void )
{
   i_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_alist_deep_dispose( &list );

   return;
}

/**
   test_p_diterable_3
*/

void test_p_diterable_3( void )
{
   i_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_alist_put_last( list, 24 );

   CU_ASSERT( i_diterable_count( pb_list ) == 1 );

   i_alist_dispose( &list );

   return;
}

/**
   test_p_diterable_4
*/

void test_p_diterable_4( void )
{
   i_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_alist_put_last( list, 24 );
   i_alist_start( list );

   CU_ASSERT( i_diterable_item( pb_list) == 24 );

   i_alist_dispose( &list );

   return;
}

/**
   test_p_diterable_5
*/

void test_p_diterable_5( void )
{
   i_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_alist_put_last( list, 24 );

   CU_ASSERT( i_diterable_off( pb_list ) == 1 );

   i_alist_dispose( &list );

   return;
}

/**
   test_p_diterable_6
*/

void test_p_diterable_6( void )
{
   i_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   CU_ASSERT( i_diterable_is_empty( pb_list ) == 1 );

   i_alist_dispose( &list );

   return;
}

/**
   test_p_diterable_7
*/

void test_p_diterable_7( void )
{
   i_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_alist_put_last( list, 24 );
   i_diterable_start( pb_list );

   CU_ASSERT( i_diterable_item( pb_list ) == 24 );

   i_alist_dispose( &list );

   return;
}

/**
   test_p_diterable_8
*/

void test_p_diterable_8( void )
{
   i_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );

   i_alist_start( list );
   i_diterable_forth( pb_list );

   CU_ASSERT( i_diterable_item( pb_list ) == 13 );

   i_alist_dispose( &list );

   return;
}

/**
   test_p_diterable_9
*/

void test_p_diterable_9( void )
{
   i_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );
   i_diterable_finish( pb_list );

   CU_ASSERT( i_diterable_item( pb_list ) == 13 );

   i_alist_dispose( &list );

   return;
}

/**
   test_p_diterable_10
*/

void test_p_diterable_10( void )
{
   i_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_alist_put_last( list, 24 );
   i_alist_put_last( list, 13 );

   i_alist_finish( list );
   i_diterable_back( pb_list );

   CU_ASSERT( i_diterable_item( pb_list ) == 24 );

   i_alist_dispose( &list );

   return;
}

/**
   test_p_diterable_11
*/

void test_p_diterable_11( void )
{
   s_alist_t *list = s_alist_make();
   protocol_base_t *pb_list = NULL;

   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   s_alist_put_last( list, s1 );
   s_alist_put_last( list, s2 );

   s_alist_finish( list );
   s_diterable_back( pb_list );

   CU_ASSERT( string_is_equal( s_diterable_item( pb_list ), s1 ) == 1 );

   s_alist_deep_dispose( &list );

   return;
}

int
add_test_p_diterable( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_p_diterable", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_p_diterable_1
   add_test_to_suite( p_suite, test_p_diterable_1, "test_p_diterable_1" );

   // test_p_diterable_2
   add_test_to_suite( p_suite, test_p_diterable_2, "test_p_diterable_2" );

   // test_p_diterable_3
   add_test_to_suite( p_suite, test_p_diterable_3, "test_p_diterable_3" );

   // test_p_diterable_4
   add_test_to_suite( p_suite, test_p_diterable_4, "test_p_diterable_4" );

   // test_p_diterable_5
   add_test_to_suite( p_suite, test_p_diterable_5, "test_p_diterable_5" );

   // test_p_diterable_6
   add_test_to_suite( p_suite, test_p_diterable_6, "test_p_diterable_6" );

   // test_p_diterable_7
   add_test_to_suite( p_suite, test_p_diterable_7, "test_p_diterable_7" );

   // test_p_diterable_8
   add_test_to_suite( p_suite, test_p_diterable_8, "test_p_diterable_8" );

   // test_p_diterable_9
   add_test_to_suite( p_suite, test_p_diterable_9, "test_p_diterable_9" );

   // test_p_diterable_10
   add_test_to_suite( p_suite, test_p_diterable_10, "test_p_diterable_10" );

   // test_p_diterable_11
   add_test_to_suite( p_suite, test_p_diterable_11, "test_p_diterable_11" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

