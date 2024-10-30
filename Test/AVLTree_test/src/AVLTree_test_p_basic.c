/**
 @file AVLTree_test_p_basic.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for AVLTree P_Basic"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for AVLTree_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_AVLTree.h"
#include "s_AVLTree.h"
#include "Protocol_Base.h"
#include "i_Basic.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_basic_1
*/

void test_p_basic_1( void )
{
   i_avltree_t *avltree = NULL;
   protocol_base_t *pb_avltree = NULL;
   
   avltree = i_avltree_make();
   pb_avltree = ( protocol_base_t * ) avltree;
   
   CU_ASSERT( avltree != NULL );
   CU_ASSERT( pb_avltree != NULL );

   i_basic_dispose( &pb_avltree );
 
   return;
}

/**
   test_p_basic_2
*/

void test_p_basic_2( void )
{
   i_avltree_t *avltree = NULL;
   protocol_base_t *pb_avltree = NULL;

   avltree = i_avltree_make();
   pb_avltree = ( protocol_base_t * ) avltree;

   CU_ASSERT( avltree != NULL );
   CU_ASSERT( pb_avltree != NULL );

   i_basic_deep_dispose( &pb_avltree );

   return;
}

/**
   test_p_basic_3
*/

void test_p_basic_3( void )
{
   i_avltree_t *avltree = NULL;
   protocol_base_t *pb_avltree = NULL;
   protocol_base_t *pb_avltree1 = NULL;

   avltree = i_avltree_make();
   pb_avltree = ( protocol_base_t * ) avltree;

   CU_ASSERT( avltree != NULL );
   CU_ASSERT( pb_avltree != NULL );

   pb_avltree1 = i_basic_clone( pb_avltree );
   CU_ASSERT( pb_avltree1 != NULL );

   i_basic_dispose( &pb_avltree );
   i_basic_dispose( &pb_avltree1 );

   return;
}

/**
   test_p_basic_4
*/

void test_p_basic_4( void )
{
   i_avltree_t *avltree = NULL;
   protocol_base_t *pb_avltree = NULL;
   protocol_base_t *pb_avltree1 = NULL;

   avltree = i_avltree_make();
   pb_avltree = ( protocol_base_t * ) avltree;

   CU_ASSERT( avltree != NULL );
   CU_ASSERT( pb_avltree != NULL );

   pb_avltree1 = i_basic_deep_clone( pb_avltree );
   CU_ASSERT( pb_avltree1 != NULL );

   i_basic_dispose( &pb_avltree );
   i_basic_dispose( &pb_avltree1 );

   return;
}

/**
   test_p_basic_5
*/

void test_p_basic_5( void )
{
   s_avltree_t *avltree = NULL;
   protocol_base_t *pb_avltree = NULL;
   protocol_base_t *pb_avltree1 = NULL;

   avltree = s_avltree_make();
   pb_avltree = ( protocol_base_t * ) avltree;

   CU_ASSERT( avltree != NULL );
   CU_ASSERT( pb_avltree != NULL );

   pb_avltree1 = i_basic_deep_clone( pb_avltree );
   CU_ASSERT( pb_avltree1 != NULL );

   i_basic_dispose( &pb_avltree );
   i_basic_dispose( &pb_avltree1 );

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

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

