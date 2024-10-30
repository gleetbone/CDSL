/**
 @file HTable_test_wipe_out.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for HTable_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HTable_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "ii_HTable.h"
#include "ss_HTable.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_wipe_out_1
*/

void test_wipe_out_1( void )
{
   ii_htable_t *htable = NULL;

   htable = ii_htable_make();

   ii_htable_put( htable, 24, 1000 );

   CU_ASSERT( ii_htable_count( htable ) == 1 );
   
   ii_htable_wipe_out( htable );

   CU_ASSERT( ii_htable_count( htable ) == 0 );
   
   ii_htable_dispose( &htable );

   return;
}

/**
   test_wipe_out_2
*/

void test_wipe_out_2( void )
{
   ii_htable_t *htable = NULL;

   htable = ii_htable_make();

   ii_htable_put( htable, 24, 1000 );
   ii_htable_put( htable, 13, 2000 );

   CU_ASSERT( ii_htable_count( htable ) == 2 );

   ii_htable_wipe_out( htable );
   
   CU_ASSERT( ii_htable_count( htable ) == 0 );

   ii_htable_dispose( &htable );

   return;
}

/**
   test_wipe_out_3
*/

void test_wipe_out_3( void )
{
   ii_htable_t *htable = NULL;
   ii_htable_cursor_t *cursor1 = NULL;
   ii_htable_cursor_t *cursor2 = NULL;
   ii_htable_cursor_t *cursor3 = NULL;

   htable = ii_htable_make();
   cursor1 = ii_htable_cursor_make( htable );
   cursor2 = ii_htable_cursor_make( htable );
   cursor3 = ii_htable_cursor_make( htable );

   ii_htable_put( htable, 24, 1000 );
   ii_htable_put( htable, 13, 2000 );

   CU_ASSERT( ii_htable_count( htable ) == 2 );

   ii_htable_wipe_out( htable );

   CU_ASSERT( ii_htable_count( htable ) == 0 );

   ii_htable_dispose( &htable );

   return;
}

/**
   test_wipe_out_4
*/

void test_wipe_out_4( void )
{
   ss_htable_t *htable = NULL;
   ss_htable_cursor_t *cursor1 = NULL;
   ss_htable_cursor_t *cursor2 = NULL;
   ss_htable_cursor_t *cursor3 = NULL;

   htable = ss_htable_make();
   
   string_t *k1 = string_make_from_cstring( "k1" );
   string_t *v1 = string_make_from_cstring( "v1" );
   
   string_t *k2 = string_make_from_cstring( "k2" );
   string_t *v2 = string_make_from_cstring( "v2" );
   
   cursor1 = ss_htable_cursor_make( htable );
   cursor2 = ss_htable_cursor_make( htable );
   cursor3 = ss_htable_cursor_make( htable );

   ss_htable_put( htable, v1, k1 );
   ss_htable_put( htable, v2, k2 );

   CU_ASSERT( ss_htable_count( htable ) == 2 );

   ss_htable_wipe_out( htable );

   CU_ASSERT( ss_htable_count( htable ) == 0 );

   string_deep_dispose( &k1 );
   string_deep_dispose( &v1 );
   string_deep_dispose( &k2 );
   string_deep_dispose( &v2 );
   
   ss_htable_dispose( &htable );

   return;
}

int
add_test_wipe_out( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_wipe_out", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_wipe_out_1
   add_test_to_suite( p_suite, test_wipe_out_1, "test_wipe_out_1" );

   // test_wipe_out_2
   add_test_to_suite( p_suite, test_wipe_out_2, "test_wipe_out_2" );

   // test_wipe_out_3
   add_test_to_suite( p_suite, test_wipe_out_3, "test_wipe_out_3" );

   // test_wipe_out_4
   add_test_to_suite( p_suite, test_wipe_out_4, "test_wipe_out_4" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

