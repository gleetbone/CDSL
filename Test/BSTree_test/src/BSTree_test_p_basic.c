/**
 @file BSTree_test_p_basic.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for BSTree P_Basic"
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

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_p_basic_1
*/

void test_p_basic_1( void )
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
   test_p_basic_2
*/

void test_p_basic_2( void )
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
   test_p_basic_3
*/

void test_p_basic_3( void )
{
   i_bstree_t *bstree = NULL;
   protocol_base_t *pb_bstree = NULL;
   protocol_base_t *pb_bstree1 = NULL;

   bstree = i_bstree_make();
   pb_bstree = ( protocol_base_t * ) bstree;

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( pb_bstree != NULL );

   pb_bstree1 = p_basic_clone( pb_bstree );
   CU_ASSERT( pb_bstree1 != NULL );

   p_basic_dispose( &pb_bstree );
   p_basic_dispose( &pb_bstree1 );

   return;
}

/**
   test_p_basic_4
*/

void test_p_basic_4( void )
{
   i_bstree_t *bstree = NULL;
   protocol_base_t *pb_bstree = NULL;
   protocol_base_t *pb_bstree1 = NULL;

   bstree = i_bstree_make();
   pb_bstree = ( protocol_base_t * ) bstree;

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( pb_bstree != NULL );

   pb_bstree1 = p_basic_deep_clone( pb_bstree );
   CU_ASSERT( pb_bstree1 != NULL );

   p_basic_dispose( &pb_bstree );
   p_basic_dispose( &pb_bstree1 );

   return;
}

/**
   test_p_basic_5
*/

void test_p_basic_5( void )
{
   s_bstree_t *bstree = NULL;
   protocol_base_t *pb_bstree = NULL;
   protocol_base_t *pb_bstree1 = NULL;

   bstree = s_bstree_make();
   pb_bstree = ( protocol_base_t * ) bstree;

   CU_ASSERT( bstree != NULL );
   CU_ASSERT( pb_bstree != NULL );

   pb_bstree1 = p_basic_deep_clone( pb_bstree );
   CU_ASSERT( pb_bstree1 != NULL );

   p_basic_dispose( &pb_bstree );
   p_basic_dispose( &pb_bstree1 );

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

