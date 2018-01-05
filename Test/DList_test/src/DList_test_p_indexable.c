/**
 @file DList_test_p_indexable.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for DList P_Indexable"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for DList_make.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_DList.h"
#include "Protocol_Base.h"
#include "i_Indexable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_indexable_1
*/

void test_p_indexable_1( void )
{
   int_dlist_t *list = NULL;
   protocol_base_t *pb_list = NULL;
   
   list = int_dlist_make();
   pb_list = ( protocol_base_t * ) list;
   
   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   CU_ASSERT( i_indexable_dispose_f( pb_list ) == int_dlist_dispose );

   i_indexable_dispose( pb_list );
 
   return;
}

/**
   test_p_indexable_2
*/

void test_p_indexable_2( void )
{
   int_dlist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_dlist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   CU_ASSERT( i_indexable_dispose_with_contents_f( pb_list ) == int_dlist_dispose_with_contents );

   i_indexable_dispose_with_contents( pb_list );

   return;
}

/**
   test_p_indexable_3
*/

void test_p_indexable_3( void )
{
   int_dlist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_dlist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_dlist_put_last( list, 24 );

   CU_ASSERT( i_indexable_count_f( pb_list ) == int_dlist_count );
   CU_ASSERT( i_indexable_count( pb_list ) == 1 );

   i_indexable_dispose( pb_list );

   return;
}

/**
   test_p_indexable_4
*/

void test_p_indexable_4( void )
{
   int_dlist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_dlist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_dlist_put_last( list, 24 );

   CU_ASSERT( i_indexable_item_f( pb_list ) == int_dlist_item );
   CU_ASSERT( i_indexable_item( pb_list, 0 ) == 24 );


   i_indexable_dispose( pb_list );

   return;
}

/**
   test_p_indexable_5
*/

void test_p_indexable_5( void )
{
   int_dlist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_dlist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_dlist_put_last( list, 24 );

   CU_ASSERT( i_indexable_item_f( pb_list ) == int_dlist_item );
   CU_ASSERT( i_indexable_item( pb_list, 0 ) == 24 );

   i_indexable_put( pb_list, 23, 0 );

   CU_ASSERT( i_indexable_item( pb_list, 0 ) == 23 );

   i_indexable_dispose( pb_list );

   return;
}

/**
   test_p_indexable_6
*/

void test_p_indexable_6( void )
{
   int_dlist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = int_dlist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   int_dlist_put_last( list, 24 );

   CU_ASSERT( i_indexable_item_f( pb_list ) == int_dlist_item );
   CU_ASSERT( i_indexable_item( pb_list, 0 ) == 24 );

   i_indexable_put_and_dispose( pb_list, 23, 0 );

   CU_ASSERT( i_indexable_item( pb_list, 0 ) == 23 );

   i_indexable_dispose( pb_list );

   return;
}

int
add_test_p_indexable( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_p_indexable", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_p_indexable_1
   add_test_to_suite( p_suite, test_p_indexable_1, "test_p_indexable_1" );

   // test_p_indexable_2
   add_test_to_suite( p_suite, test_p_indexable_2, "test_p_indexable_2" );

   // test_p_indexable_3
   add_test_to_suite( p_suite, test_p_indexable_3, "test_p_indexable_3" );

   // test_p_indexable_4
   add_test_to_suite( p_suite, test_p_indexable_4, "test_p_indexable_4" );

   // test_p_indexable_5
   add_test_to_suite( p_suite, test_p_indexable_5, "test_p_indexable_5" );

   // test_p_indexable_6
   add_test_to_suite( p_suite, test_p_indexable_6, "test_p_indexable_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

