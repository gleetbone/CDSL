/**
 @file ifr_test_one_line_comment.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for ifr_test_one_line_comment"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for ifr_make_from_cstring.

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
   test_one_line_comment_1
*/

void test_one_line_comment_1( void )
{
   ifr_t *ifr = NULL;
   string_t *filename = NULL;
   s_dlist_t *list = NULL;
   
   string_t *t1 = NULL;
   string_t *t2 = NULL;
   string_t *t3 = NULL;
   string_t *t4 = NULL;
   string_t *t5 = NULL;
   
   t1 = string_make_from_cstring( "one" );
   t2 = string_make_from_cstring( "two" );
   t3 = string_make_from_cstring( "three" );
   t4 = string_make_from_cstring( "--" );
   t5 = string_make_from_cstring( "four" );
   
   filename = string_make_from_cstring( "src/input_files/f_one_line_comment.txt" );
   
   ifr = ifr_make( filename );

   ifr_forth( ifr );
   
   list = ifr_tokens( ifr );
   
   CU_ASSERT( s_dlist_count( list ) == 5 );

   s_dlist_start( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t1 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t2 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t3 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t4 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t5 ) == 1 );
 
   ifr_dispose( ifr );
   string_dispose_with_contents( filename );
   string_dispose_with_contents( t1 );
   string_dispose_with_contents( t2 );
   string_dispose_with_contents( t3 );
   string_dispose_with_contents( t4 );
   string_dispose_with_contents( t5 );
   
   return;
}

/**
   test_one_line_comment_2
*/

void test_one_line_comment_2( void )
{
   ifr_t *ifr = NULL;
   string_t *filename = NULL;
   s_dlist_t *list = NULL;
   int32_t skip_comments = 0;
   
   string_t *t1 = NULL;
   string_t *t2 = NULL;
   string_t *t3 = NULL;
   
   t1 = string_make_from_cstring( "one" );
   t2 = string_make_from_cstring( "two" );
   t3 = string_make_from_cstring( "three" );
   
   filename = string_make_from_cstring( "src/input_files/f_one_line_comment.txt" );
   
   ifr = ifr_make( filename );
   ifr_set_skip_comments( ifr, 1 );

   skip_comments = ifr_skip_comments( ifr );

   CU_ASSERT( skip_comments == 1 );

   ifr_forth( ifr );
   
   list = ifr_tokens( ifr );
   
   CU_ASSERT( s_dlist_count( list ) == 3 );

   s_dlist_start( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t1 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t2 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t3 ) == 1 );
 
      
   ifr_dispose( ifr );
   string_dispose_with_contents( filename );
   string_dispose_with_contents( t1 );
   string_dispose_with_contents( t2 );
   string_dispose_with_contents( t3 );
   
   return;
}

int
add_test_one_line_comment( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_one_line_comment", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_one_line_comment_1
   add_test_to_suite( p_suite, test_one_line_comment_1, "test_one_line_comment_1" );

   // test_one_line_comment_2
   add_test_to_suite( p_suite, test_one_line_comment_2, "test_one_line_comment_2" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

