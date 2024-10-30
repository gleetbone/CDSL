/**
 @file ifr_test_quotes.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for ifr_t"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for ifr_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "Input_File_Reader.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_quotes_1
*/

void test_quotes_1( void )
{
   ifr_t *ifr = NULL;
   string_t *file_name = NULL;
   s_dlist_t *list = NULL;
   
   string_t *t1 = NULL;
   string_t *t2 = NULL;
   string_t *t3 = NULL;
   string_t *t4 = NULL;
   
   t1 = string_make_from_cstring( "one" );
   t2 = string_make_from_cstring( "two" );
   t3 = string_make_from_cstring( "three four" );
   t4 = string_make_from_cstring( "split\"token" );
   
   file_name = string_make_from_cstring( "src/input_files/f_quotes.txt" );
   
   ifr = ifr_make( file_name );

   ifr_forth( ifr );
   
   list = ifr_tokens( ifr );
   
   CU_ASSERT( s_dlist_count( list ) == 4 );

   s_dlist_start( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t1 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t2 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t3 ) == 1 );
 
   s_dlist_forth( list );

   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t4 ) == 1 );

   ifr_deep_dispose( &ifr );
   string_deep_dispose( &file_name );
   string_deep_dispose( &t1 );
   string_deep_dispose( &t2 );
   string_deep_dispose( &t3 );
   string_deep_dispose( &t4 );
   
   return;
}

int
add_test_quotes( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_quotes", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_quotes_1
   add_test_to_suite( p_suite, test_quotes_1, "test_quotes_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

