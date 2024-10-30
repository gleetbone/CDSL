/**
 @file HTable_test_cursor_forth.c
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
   test_cursor_forth_1
*/

void test_cursor_forth_1( void )
{
   ii_htable_t *htable = NULL;
   
   htable = ii_htable_make();
   
   ii_htable_put( htable, 24, 1000 );
   
   ii_htable_cursor_t *cursor = NULL;
   
   cursor = ii_htable_cursor_make( htable );
   
   ii_htable_cursor_start( cursor );
   
   CU_ASSERT( ii_htable_cursor_off( cursor ) == 0 );
 
   ii_htable_cursor_forth( cursor );
   
   CU_ASSERT( ii_htable_cursor_off( cursor ) == 1 );
   
   ii_htable_dispose( &htable );

   return;
}

/**
   test_cursor_forth_2
*/

void test_cursor_forth_2( void )
{
   ss_htable_t *htable = NULL;
   
   htable = ss_htable_make();
   
   string_t *k1 = string_make_from_cstring( "k1" );
   string_t *v1 = string_make_from_cstring( "v1" );
   
   ss_htable_put( htable, v1, k1 );
   
   ss_htable_cursor_t *cursor = NULL;
   
   cursor = ss_htable_cursor_make( htable );
   
   ss_htable_cursor_start( cursor );
   
   CU_ASSERT( ss_htable_cursor_off( cursor ) == 0 );
 
   ss_htable_cursor_forth( cursor );
   
   CU_ASSERT( ss_htable_cursor_off( cursor ) == 1 );
   
   ss_htable_deep_dispose( &htable );

   return;
}

int
add_test_cursor_forth( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_cursor_forth", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_cursor_forth_1
   add_test_to_suite( p_suite, test_cursor_forth_1, "test_cursor_forth_1" );

   // test_cursor_forth_2
   add_test_to_suite( p_suite, test_cursor_forth_2, "test_cursor_forth_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

