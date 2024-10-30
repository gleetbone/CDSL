/**
 @file DList_test_p_indexable.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for DList P_Indexable"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for DList_t.

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_DList.h"
#include "s_DList.h"
#include "Protocol_Base.h"
#include "i_Indexable.h"
#include "s_Indexable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_indexable_1
*/

void test_p_indexable_1( void )
{
   i_dlist_t *list = NULL;
   protocol_base_t *pb_list = NULL;
   
   list = i_dlist_make();
   pb_list = ( protocol_base_t * ) list;
   
   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_dlist_dispose( &list );
 
   return;
}

/**
   test_p_indexable_2
*/

void test_p_indexable_2( void )
{
   i_dlist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_dlist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_dlist_deep_dispose( &list );

   return;
}

/**
   test_p_indexable_3
*/

void test_p_indexable_3( void )
{
   i_dlist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_dlist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_dlist_put_last( list, 24 );

   CU_ASSERT( i_indexable_count( pb_list ) == 1 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_p_indexable_4
*/

void test_p_indexable_4( void )
{
   i_dlist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_dlist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_dlist_put_last( list, 24 );

   CU_ASSERT( i_indexable_item( pb_list, 0 ) == 24 );


   i_dlist_dispose( &list );

   return;
}

/**
   test_p_indexable_5
*/

void test_p_indexable_5( void )
{
   i_dlist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_dlist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_dlist_put_last( list, 24 );

   CU_ASSERT( i_indexable_item( pb_list, 0 ) == 24 );

   i_indexable_put( pb_list, 23, 0 );

   CU_ASSERT( i_indexable_item( pb_list, 0 ) == 23 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_p_indexable_6
*/

void test_p_indexable_6( void )
{
   i_dlist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   list = i_dlist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   i_dlist_put_last( list, 24 );

   CU_ASSERT( i_indexable_item( pb_list, 0 ) == 24 );

   i_indexable_put_and_dispose( pb_list, 23, 0 );

   CU_ASSERT( i_indexable_item( pb_list, 0 ) == 23 );

   i_dlist_dispose( &list );

   return;
}

/**
   test_p_indexable_7
*/

void test_p_indexable_7( void )
{
   s_dlist_t *list = NULL;
   protocol_base_t *pb_list = NULL;

   string_t *s1 = string_make_from_cstring( "1" );
   string_t *s2 = string_make_from_cstring( "2" );
   
   list = s_dlist_make();
   pb_list = ( protocol_base_t * ) list;

   CU_ASSERT( list != NULL );
   CU_ASSERT( pb_list != NULL );

   s_dlist_put_last( list, s1 );

   CU_ASSERT( s_indexable_item( pb_list, 0 ) == s1 );

   s_indexable_put_and_dispose( pb_list, s2, 0 );

   CU_ASSERT( s_indexable_item( pb_list, 0 ) == s2 );

   s_dlist_deep_dispose( &list );

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

   // test_p_indexable_7
   add_test_to_suite( p_suite, test_p_indexable_7, "test_p_indexable_7" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

