/**
 @file ifr_test_multiline.c
 @author Greg Lee
 @version 1.0.0
 @brief: "tests for ifr_make_from_cstring"
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
   test_multiline_1
*/

void test_multiline_1( void )
{
   ifr_t *ifr = NULL;
   string_t *filename = NULL;
   s_dlist_t *list = NULL;
   
   string_t *t1 = NULL;
   string_t *t2 = NULL;
   string_t *t3 = NULL;
   string_t *t4 = NULL;
   string_t *t5 = NULL;
   
   string_t *s1 = NULL;
   string_t *s2 = NULL;
   string_t *s3 = NULL;
   string_t *s4 = NULL;
   string_t *s5 = NULL;
   string_t *s6 = NULL;
   
   string_t *u1 = NULL;
   string_t *u2 = NULL;
   
   string_t *v1 = NULL;
   string_t *v2 = NULL;
   
   t1 = string_make_from_cstring( "one" );
   t2 = string_make_from_cstring( "two" );
   t3 = string_make_from_cstring( "three" );
   t4 = string_make_from_cstring( "//" );
   t5 = string_make_from_cstring( "comment" );
   
   s1 = string_make_from_cstring( "red" );
   s2 = string_make_from_cstring( "green" );
   s3 = string_make_from_cstring( "blue" );
   s4 = string_make_from_cstring( "yellow" );
   s5 = string_make_from_cstring( "--" );
   s6 = string_make_from_cstring( "colors" );
   
   u1 = string_make_from_cstring( "--" );
   u2 = string_make_from_cstring( "notice" );
   
   v1 = string_make_from_cstring( "--" );
   v2 = string_make_from_cstring( "end" );
   
   filename = string_make_from_cstring( "src/input_files/f_multiline.txt" );
   
   ifr = ifr_make( filename );

   // first line
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
 
   // second line skipped - blank
   
   // third line
   
   ifr_forth( ifr );
   
   list = ifr_tokens( ifr );
   
   CU_ASSERT( s_dlist_count( list ) == 2 );

   s_dlist_start( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), u1 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), u2 ) == 1 );
 
   // fourth line
   
   ifr_forth( ifr );
   
   list = ifr_tokens( ifr );
   
   CU_ASSERT( s_dlist_count( list ) == 6 );

   s_dlist_start( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), s1 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), s2 ) == 1 );

   // fourth line
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), s3 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), s4 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), s5 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), s6 ) == 1 );
 
   // fifth line skipped - blank
      
   // sixth line
   
   ifr_forth( ifr );
   
   list = ifr_tokens( ifr );
   
   CU_ASSERT( s_dlist_count( list ) == 2 );

   s_dlist_start( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), v1 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), v2 ) == 1 );

   // end of file
   
   ifr_forth( ifr );
   
   list = ifr_tokens( ifr );
   
   CU_ASSERT( s_dlist_count( list ) == 0 );

   CU_ASSERT( ifr_eof( ifr ) == 1 );

   ifr_dispose( ifr );
   string_dispose_with_contents( filename );
   string_dispose_with_contents( t1 );
   string_dispose_with_contents( t2 );
   string_dispose_with_contents( t3 );
   string_dispose_with_contents( t4 );
   string_dispose_with_contents( t5 );
   string_dispose_with_contents( s1 );
   string_dispose_with_contents( s2 );
   string_dispose_with_contents( s3 );
   string_dispose_with_contents( s4 );
   string_dispose_with_contents( s5 );
   string_dispose_with_contents( s6 );
   string_dispose_with_contents( u1 );
   string_dispose_with_contents( u2 );
   string_dispose_with_contents( v1 );
   string_dispose_with_contents( v2 );
   
   return;
}

int
add_test_multiline( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_multiline", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_multiline_1
   add_test_to_suite( p_suite, test_multiline_1, "test_multiline_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

