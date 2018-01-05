/**
 @file AList_test_p_diterable.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for AList P_DIterable"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AList_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_AList.h"
#include "Protocol_Base.h"
#include "i_DIterable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_diterable_1
*/

void test_p_diterable_1( void )
{
   int_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;
   
   list = int_alist_make();
   pb_list = ( protocol_base_t * ) list;
   
   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   CU_ASSERT( i_diterable_dispose_f( pb_list ) == int_alist_dispose );

   i_diterable_dispose( pb_list );
 
   return;
}

/**
   test_p_diterable_2
*/

void test_p_diterable_2( void )
{
   int_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   CU_ASSERT( i_diterable_dispose_with_contents_f( pb_list ) == int_alist_dispose_with_contents );

   i_diterable_dispose_with_contents( pb_list );

   return;
}

/**
   test_p_diterable_3
*/

void test_p_diterable_3( void )
{
   int_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_alist_put_last( list, 24 );

   CU_ASSERT( i_diterable_count_f( pb_list ) == int_alist_count );
   CU_ASSERT( i_diterable_count( pb_list ) == 1 );

   i_diterable_dispose( pb_list );

   return;
}

/**
   test_p_diterable_4
*/

void test_p_diterable_4( void )
{
   int_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_alist_put_last( list, 24 );
   int_alist_start( list );

   CU_ASSERT( i_diterable_item_f( pb_list ) == int_alist_item_at );
   CU_ASSERT( i_diterable_item( pb_list) == 24 );

   i_diterable_dispose( pb_list );

   return;
}

/**
   test_p_diterable_5
*/

void test_p_diterable_5( void )
{
   int_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_alist_put_last( list, 24 );

   CU_ASSERT( i_diterable_off_f( pb_list ) == int_alist_off );
   CU_ASSERT( i_diterable_off( pb_list ) == 1 );

   i_diterable_dispose( pb_list );

   return;
}

/**
   test_p_diterable_6
*/

void test_p_diterable_6( void )
{
   int_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   CU_ASSERT( i_diterable_is_empty_f( pb_list ) == int_alist_is_empty );
   CU_ASSERT( i_diterable_is_empty( pb_list ) == 1 );

   i_diterable_dispose( pb_list );

   return;
}

/**
   test_p_diterable_7
*/

void test_p_diterable_7( void )
{
   int_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_alist_put_last( list, 24 );
   i_diterable_start( pb_list );

   CU_ASSERT( i_diterable_item_f( pb_list ) == int_alist_item_at );
   CU_ASSERT( i_diterable_item( pb_list) == 24 );

   i_diterable_dispose( pb_list );

   return;
}

/**
   test_p_diterable_8
*/

void test_p_diterable_8( void )
{
   int_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_alist_put_last( list, 24 );
   int_alist_put_last( list, 13 );

   int_alist_start( list );
   i_diterable_forth( pb_list );

   CU_ASSERT( i_diterable_forth_f( pb_list ) == int_alist_forth );
   CU_ASSERT( i_diterable_item( pb_list) == 13 );

   i_diterable_dispose( pb_list );

   return;
}

/**
   test_p_diterable_9
*/

void test_p_diterable_9( void )
{
   int_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_alist_put_last( list, 24 );
   int_alist_put_last( list, 13 );
   i_diterable_finish( pb_list );

   CU_ASSERT( i_diterable_finish_f( pb_list ) == int_alist_finish );
   CU_ASSERT( i_diterable_item( pb_list) == 13 );

   i_diterable_dispose( pb_list );

   return;
}

/**
   test_p_diterable_10
*/

void test_p_diterable_10( void )
{
   int_alist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_alist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_alist_put_last( list, 24 );
   int_alist_put_last( list, 13 );

   int_alist_finish( list );
   i_diterable_back( pb_list );

   CU_ASSERT( i_diterable_back_f( pb_list ) == int_alist_back );
   CU_ASSERT( i_diterable_item( pb_list) == 24 );

   i_diterable_dispose( pb_list );

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

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

