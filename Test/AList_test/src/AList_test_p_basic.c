/**
 @file AList_test_p_basic.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AList P_Clonable"
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
#include "i_Basic.h"

#include "s_AList.h"
#include "s_Basic.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_basic_1
*/

void test_p_basic_1( void )
{
   i_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;
   
   list = i_alist_make();
   pb_list = ( protocol_base_t * ) list;
   
   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_basic_dispose( &pb_list );
 
   return;
}

/**
   test_p_basic_2
*/

void test_p_basic_2( void )
{
   i_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_basic_deep_dispose( &pb_list );

   return;
}

/**
   test_p_basic_3
*/

void test_p_basic_3( void )
{
   i_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;
   protocol_base_t *pb_list1 = NULL;

   list = i_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   pb_list1 = i_basic_clone( pb_list );
   CU_ASSERT( pb_list1 != NULL );

   i_basic_dispose( &pb_list );
   i_basic_dispose( &pb_list1 );

   return;
}

/**
   test_p_basic_4
*/

void test_p_basic_4( void )
{
   i_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;
   protocol_base_t *pb_list1 = NULL;

   list = i_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   pb_list1 = i_basic_deep_clone( pb_list );
   CU_ASSERT( pb_list1 != NULL );

   i_basic_dispose( &pb_list );
   i_basic_dispose( &pb_list1 );

   return;
}

/**
   test_p_basic_5
*/

void test_p_basic_5( void )
{
   i_alist_t *list = i_alist_make();
   i_alist_t *list1 = i_alist_make();
   protocol_base_t *pb_list = NULL;
   protocol_base_t *pb_list1 = NULL;

   pb_list = ( protocol_base_t * ) list;
   pb_list1 = ( protocol_base_t * ) list1;

   CU_ASSERT( pb_list != NULL );
   CU_ASSERT( pb_list1 != NULL );

   CU_ASSERT( i_basic_is_equal( pb_list, pb_list1 ) == 1 );
   CU_ASSERT( i_basic_is_deep_equal( pb_list, pb_list1 ) == 1 );

   i_alist_put_last( list, 24 );
   i_basic_copy( pb_list1, pb_list );
   
   CU_ASSERT( i_basic_is_equal( pb_list, pb_list1 ) == 1 );
   CU_ASSERT( i_basic_is_deep_equal( pb_list, pb_list1 ) == 1 );

   i_alist_put_last( list, 13 );
   i_basic_deep_copy( pb_list1, pb_list );
   
   CU_ASSERT( i_basic_is_equal( pb_list, pb_list1 ) == 1 );
   CU_ASSERT( i_basic_is_deep_equal( pb_list, pb_list1 ) == 1 );

   i_basic_dispose( &pb_list );
   i_basic_dispose( &pb_list1 );

   return;
}

/**
   test_p_basic_6
*/

void test_p_basic_6( void )
{
   s_alist_t *list = s_alist_make();
   s_alist_t *list1 = NULL;
   protocol_base_t *pb_list = NULL;
   protocol_base_t *pb_list1 = NULL;

   string_t *s1 = string_make_from_cstring( "a" ); 
   s_alist_put_last( list, s1 );
   
   pb_list = ( protocol_base_t * ) list;
   pb_list1 = s_basic_clone( pb_list );
   
   CU_ASSERT( pb_list != NULL );
   CU_ASSERT( pb_list1 != NULL );
   
   CU_ASSERT( s_basic_is_equal( pb_list, pb_list1 ) == 1 );
   CU_ASSERT( s_basic_is_deep_equal( pb_list, pb_list1 ) == 1 );

   s_basic_dispose( &pb_list1 );
   pb_list1 = s_basic_deep_clone( pb_list );

   CU_ASSERT( s_basic_is_equal( pb_list, pb_list1 ) == 0 );
   CU_ASSERT( s_basic_is_deep_equal( pb_list, pb_list1 ) == 1 );

   s_basic_copy( pb_list1, pb_list );
   
   CU_ASSERT( s_basic_is_equal( pb_list, pb_list1 ) == 1 );
   CU_ASSERT( s_basic_is_deep_equal( pb_list, pb_list1 ) == 1 );

   list1 = ( s_alist_t * ) pb_list1;
   s_alist_wipe_out( list1 );
   s_basic_deep_copy( pb_list1, pb_list );
   
   CU_ASSERT( s_basic_is_equal( pb_list, pb_list1 ) == 0 );
   CU_ASSERT( s_basic_is_deep_equal( pb_list, pb_list1 ) == 1 );

   s_basic_deep_dispose( &pb_list );
   s_basic_deep_dispose( &pb_list1 );

   return;
}

int
add_test_p_basic( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_p_basic", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_p_basic_1
   add_test_to_suite( p_suite, test_p_basic_1, "test_p_basic_1" );

   // test_p_basic_2
   add_test_to_suite( p_suite, test_p_basic_2, "test_p_basic_2" );

   // test_p_basic_3
   add_test_to_suite( p_suite, test_p_basic_3, "test_p_basic_3" );

   // test_p_basic_4
   add_test_to_suite( p_suite, test_p_basic_4, "test_p_basic_4" );

   // test_p_basic_5
   add_test_to_suite( p_suite, test_p_basic_5, "test_p_basic_5" );

   // test_p_basic_6
   add_test_to_suite( p_suite, test_p_basic_6, "test_p_basic_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

