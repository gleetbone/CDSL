/**
 @file string_test_keep_tail.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for string_make_from_cstring"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for string_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "String.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_keep_tail_1
*/

void test_keep_tail_1( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_keep_tail( string, 0 );
   
   string_t *stringt = string_make_from_cstring( "" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_keep_tail_2
*/

void test_keep_tail_2( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_keep_tail( string, 1 );
   
   string_t *stringt = string_make_from_cstring( "D" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_keep_tail_3
*/

void test_keep_tail_3( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_keep_tail( string, 2 );
   
   string_t *stringt = string_make_from_cstring( "CD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_keep_tail_4
*/

void test_keep_tail_4( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_keep_tail( string, 3 );
   
   string_t *stringt = string_make_from_cstring( "BCD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_keep_tail_5
*/

void test_keep_tail_5( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_keep_tail( string, 4);
   
   string_t *stringt = string_make_from_cstring( "ABCD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &stringt );

   return;
}

int
add_test_keep_tail( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_keep_tail", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_keep_tail_1
   add_test_to_suite( p_suite, test_keep_tail_1, "test_keep_tail_1" );

   // test_keep_tail_2
   add_test_to_suite( p_suite, test_keep_tail_2, "test_keep_tail_2" );

   // test_keep_tail_3
   add_test_to_suite( p_suite, test_keep_tail_3, "test_keep_tail_3" );

   // test_keep_tail_4
   add_test_to_suite( p_suite, test_keep_tail_4, "test_keep_tail_4" );

   // test_keep_tail_5
   add_test_to_suite( p_suite, test_keep_tail_5, "test_keep_tail_5" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

