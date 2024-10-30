/**
 @file string_test_replace_all_cstring2.c
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
   test_replace_all_cstring2_1
*/

void test_replace_all_cstring2_1( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_replace_all_cstring2( string, "B", "Q" );
   
   string_t *stringt = string_make_from_cstring( "AQCD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_replace_all_cstring2_2
*/

void test_replace_all_cstring2_2( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_replace_all_cstring2( string, "B", "QR" );
   
   string_t *stringt = string_make_from_cstring( "AQRCD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_replace_all_cstring2_3
*/

void test_replace_all_cstring2_3( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_replace_all_cstring2( string, "AB", "X" );
   
   string_t *stringt = string_make_from_cstring( "XCD" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_replace_all_cstring2_4
*/

void test_replace_all_cstring2_4( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_replace_all_cstring2( string, "CD", "XYZ" );
   
   string_t *stringt = string_make_from_cstring( "ABXYZ" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_replace_all_cstring2_5
*/

void test_replace_all_cstring2_5( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCD" );
   
   string_replace_all_cstring2( string, "BCD", "Q" );
   
   string_t *stringt = string_make_from_cstring( "AQ" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &stringt );

   return;
}

/**
   test_replace_all_cstring2_6
*/

void test_replace_all_cstring2_6( void )
{
   string_t *string = NULL;
   
   string = string_make_from_cstring( "ABCDE" );
   
   string_replace_all_cstring2( string, "BC", "QRWXYZ" );
   
   string_t *stringt = string_make_from_cstring( "AQRWXYZDE" );
   
   CU_ASSERT( string_is_equal( string, stringt ) == 1 );
 
   string_deep_dispose( &string );
   string_deep_dispose( &stringt );

   return;
}

int
add_test_replace_all_cstring2( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_replace_all_cstring2", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_replace_all_cstring2_1
   add_test_to_suite( p_suite, test_replace_all_cstring2_1, "test_replace_all_cstring2_1" );

   // test_replace_all_cstring2_2
   add_test_to_suite( p_suite, test_replace_all_cstring2_2, "test_replace_all_cstring2_2" );

   // test_replace_all_cstring2_3
   add_test_to_suite( p_suite, test_replace_all_cstring2_3, "test_replace_all_cstring2_4" );

   // test_replace_all_cstring2_4
   add_test_to_suite( p_suite, test_replace_all_cstring2_4, "test_replace_all_cstring2_4" );

   // test_replace_all_cstring2_5
   add_test_to_suite( p_suite, test_replace_all_cstring2_5, "test_replace_all_cstring2_5" );

   // test_replace_all_cstring2_6
   add_test_to_suite( p_suite, test_replace_all_cstring2_6, "test_replace_all_cstring2_6" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

