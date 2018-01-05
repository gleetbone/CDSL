/**
 @file ifr_test_two_line.c
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
   test_two_line_1
*/

void test_two_line_1( void )
{
   ifr_t *ifr = NULL;
   string_t *filename = NULL;
   s_dlist_t *list = NULL;
   
   string_t *t1 = NULL;
   string_t *t2 = NULL;
   string_t *t3 = NULL;
   
   string_t *s1 = NULL;
   string_t *s2 = NULL;
   string_t *s3 = NULL;
   string_t *s4 = NULL;
   
   t1 = string_make_from_cstring( "one" );
   t2 = string_make_from_cstring( "two" );
   t3 = string_make_from_cstring( "three" );
   
   s1 = string_make_from_cstring( "red" );
   s2 = string_make_from_cstring( "green" );
   s3 = string_make_from_cstring( "blue" );
   s4 = string_make_from_cstring( "yellow" );
   
   filename = string_make_from_cstring( "src/input_files/f_two_line.txt" );
   
   ifr = ifr_make( filename );

   // first line
   ifr_forth( ifr );
   
   list = ifr_tokens( ifr );
   
   CU_ASSERT( s_dlist_count( list ) == 3 );

   s_dlist_start( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t1 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t2 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), t3 ) == 1 );
 
   // second line
   ifr_forth( ifr );
   
   list = ifr_tokens( ifr );
   
   CU_ASSERT( s_dlist_count( list ) == 4 );

   s_dlist_start( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), s1 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), s2 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), s3 ) == 1 );
 
   s_dlist_forth( list );
   
   CU_ASSERT( string_is_equal( s_dlist_item_at( list ), s4 ) == 1 );
 
   ifr_dispose( ifr );
   string_dispose_with_contents( filename );
   string_dispose_with_contents( t1 );
   string_dispose_with_contents( t2 );
   string_dispose_with_contents( t3 );
   string_dispose_with_contents( s1 );
   string_dispose_with_contents( s2 );
   string_dispose_with_contents( s3 );
   string_dispose_with_contents( s4 );
   
   return;
}

int
add_test_two_line( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_two_line", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_two_line_1
   add_test_to_suite( p_suite, test_two_line_1, "test_two_line_1" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

