/**
 @file SList_test_occurrences.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for SList_forth"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for SList_t.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "int_SList.h"
#include "s_SList.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_occurrences_1
*/

void test_occurrences_1( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );

   CU_ASSERT( int_slist_occurrences( list, 24 ) == 1 );
   CU_ASSERT( int_slist_occurrences( list, 17 ) == 0 );

   int_slist_dispose( &list );

   return;
}

/**
   test_occurrences_2
*/

void test_occurrences_2( void )
{
   int_slist_t *list = NULL;

   list = int_slist_make();
   int_slist_put_last( list, 24 );
   int_slist_put_last( list, 13 );
   int_slist_put_last( list, 24 );

   CU_ASSERT( int_slist_occurrences( list, 24 ) == 2 );
   CU_ASSERT( int_slist_occurrences( list, 13 ) == 1 );
   CU_ASSERT( int_slist_occurrences( list, 7 ) == 0 );
   
   int_slist_dispose( &list );

   return;
}

/**
   test_occurrences_3
*/

void test_occurrences_3( void )
{
   s_slist_t *list = s_slist_make();
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "c" ); 
   string_t *s4 = string_make_from_cstring( "a" ); 
   
   s_slist_put_last( list, s1 );
   s_slist_put_last( list, s2 );
   s_slist_put_last( list, s3 );

   CU_ASSERT( s_slist_occurrences( list, s1 ) == 1 );
   CU_ASSERT( s_slist_occurrences( list, s4 ) == 0 );
   
   string_deep_dispose( &s4 );
   s_slist_deep_dispose( &list );

   return;
}

int
add_test_occurrences( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_occurrences", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_occurrences_1
   add_test_to_suite( p_suite, test_occurrences_1, "test_occurrences_1" );

   // test_occurrences_2
   add_test_to_suite( p_suite, test_occurrences_2, "test_occurrences_2" );

   // test_occurrences_3
   add_test_to_suite( p_suite, test_occurrences_3, "test_occurrences_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

