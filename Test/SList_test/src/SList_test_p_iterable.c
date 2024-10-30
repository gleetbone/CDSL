/**
 @file SList_test_p_iterable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for SList P_Iterable"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for SList_t.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_SList.h"
#include "s_SList.h"
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
   int_slist_t *list = NULL;
   protocol_base_t *pb_list = NULL;
   
   list = int_slist_make();
   pb_list = ( protocol_base_t * ) list;
   
   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_slist_dispose( &list );
 
   return;
}

/**
   test_p_iterable_2
*/

void test_p_iterable_2( void )
{
   int_slist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_slist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_slist_deep_dispose( &list );

   return;
}

/**
   test_p_iterable_3
*/

void test_p_iterable_3( void )
{
   int_slist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_slist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_slist_put_last( list, 24 );

   CU_ASSERT( i_iterable_count( pb_list ) == 1 );

   int_slist_dispose( &list );

   return;
}

/**
   test_p_iterable_4
*/

void test_p_iterable_4( void )
{
   int_slist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_slist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_slist_put_last( list, 24 );
   int_slist_start( list );

   CU_ASSERT( i_iterable_item( pb_list) == 24 );

   int_slist_dispose( &list );

   return;
}

/**
   test_p_iterable_5
*/

void test_p_iterable_5( void )
{
   int_slist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_slist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_slist_put_last( list, 24 );

   CU_ASSERT( i_iterable_off( pb_list ) == 1 );

   int_slist_dispose( &list );

   return;
}

/**
   test_p_iterable_6
*/

void test_p_iterable_6( void )
{
   int_slist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_slist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   CU_ASSERT( i_iterable_is_empty( pb_list ) == 1 );

   int_slist_dispose( &list );

   return;
}

/**
   test_p_iterable_7
*/

void test_p_iterable_7( void )
{
   int_slist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_slist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_slist_put_last( list, 24 );
   i_iterable_start( pb_list );

   CU_ASSERT( i_iterable_item( pb_list) == 24 );

   int_slist_dispose( &list );

   return;
}

/**
   test_p_iterable_8
*/

void test_p_iterable_8( void )
{
   int_slist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_slist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   int_slist_start( list );
   i_iterable_forth( pb_list );

   CU_ASSERT( i_iterable_item( pb_list) == 13 );

   int_slist_dispose( &list );

   return;
}

/**
   test_p_iterable_9
*/

void test_p_iterable_9( void )
{
   s_slist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   
   list = s_slist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   s_slist_put_last( list, s1 );
   s_slist_put_last( list, s2 );

   s_slist_start( list );
   s_iterable_forth( pb_list );

   CU_ASSERT( s_iterable_item( pb_list) == s2 );

   s_slist_deep_dispose( &list );

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

