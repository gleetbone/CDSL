/**
 @file HSet_test_intersection.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for HSet_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for HSet_t

*/

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "i_HSet.h"
#include "s_HSet.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_intersection_1
*/

void test_intersection_1( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   result = i_hset_intersection( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 0 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result  );

   return;
}

/**
   test_intersection_2
*/

void test_intersection_2( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   
   result = i_hset_intersection( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 0 );
   CU_ASSERT( i_hset_has( result, 24 ) == 0 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result  );

   return;
}

/**
   test_intersection_3
*/

void test_intersection_3( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   i_hset_put( other, 24 );
   
   result = i_hset_intersection( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 1 );
   CU_ASSERT( i_hset_has( result, 24 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result  );

   return;
}

/**
   test_intersection_4
*/

void test_intersection_4( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( other, 24 );
   
   result = i_hset_intersection( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 0 );
   CU_ASSERT( i_hset_has( result, 24 ) == 0 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result  );

   return;
}

/**
   test_intersection_5
*/

void test_intersection_5( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );
   i_hset_put( other, 24 );
   
   result = i_hset_intersection( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 1 );
   CU_ASSERT( i_hset_has( result, 24 ) == 1 );
   CU_ASSERT( i_hset_has( result, 13 ) == 0 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result  );

   return;
}

/**
   test_intersection_6
*/

void test_intersection_6( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   i_hset_put( other, 24 );
   i_hset_put( other, 13 );
   
   result = i_hset_intersection( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 1 );
   CU_ASSERT( i_hset_has( result, 24 ) == 1 );
   CU_ASSERT( i_hset_has( result, 13 ) == 0 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result  );

   return;
}

/**
   test_intersection_7
*/

void test_intersection_7( void )
{
   i_hset_t *hset = i_hset_make();
   i_hset_t *other = i_hset_make();
   i_hset_t *result = NULL;
   
   i_hset_put( hset, 24 );
   i_hset_put( hset, 13 );
   i_hset_put( other, 24 );
   i_hset_put( other, 13 );
   
   result = i_hset_intersection( hset, other );
   
   CU_ASSERT( i_hset_count( result ) == 2 );
   CU_ASSERT( i_hset_has( result, 24 ) == 1 );
   CU_ASSERT( i_hset_has( result, 13 ) == 1 );
 
   i_hset_dispose( &hset );
   i_hset_dispose( &other );
   i_hset_dispose( &result );

   return;
}

/**
   test_intersection_8
*/

void test_intersection_8( void )
{
   s_hset_t *hset = s_hset_make();
   s_hset_t *other = s_hset_make();
   s_hset_t *result = NULL;
   
   string_t *s1 = string_make_from_cstring( "a" ); 
   string_t *s2 = string_make_from_cstring( "b" ); 
   string_t *s3 = string_make_from_cstring( "a" ); 
   string_t *s4 = string_make_from_cstring( "b" ); 
   
   s_hset_put( hset, s1 );
   s_hset_put( hset, s2 );
   s_hset_put( other, s3 );
   s_hset_put( other, s4 );
   
   result = s_hset_intersection( hset, other );
   
   CU_ASSERT( s_hset_count( result ) == 2 );
   CU_ASSERT( s_hset_has( result, s1 ) == 1 );
   CU_ASSERT( s_hset_has( result, s2 ) == 1 );
   CU_ASSERT( s_hset_has( result, s3 ) == 1 );
   CU_ASSERT( s_hset_has( result, s4 ) == 1 );
 
   s_hset_dispose( &result  );
   s_hset_deep_dispose( &hset );
   s_hset_deep_dispose( &other );

   return;
}

int
add_test_intersection( void )
{
   CU_pSuite p_suite = NULL;
   
   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_intersection", NULL, NULL);
   if (NULL == p_suite) 
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_intersection_1
   add_test_to_suite( p_suite, test_intersection_1, "test_intersection_1" );

   // test_intersection_2
   add_test_to_suite( p_suite, test_intersection_2, "test_intersection_2" );

   // test_intersection_3
   add_test_to_suite( p_suite, test_intersection_3, "test_intersection_3" );

   // test_intersection_4
   add_test_to_suite( p_suite, test_intersection_4, "test_intersection_4" );

   // test_intersection_5
   add_test_to_suite( p_suite, test_intersection_5, "test_intersection_5" );

   // test_intersection_6
   add_test_to_suite( p_suite, test_intersection_6, "test_intersection_6" );

   // test_intersection_7
   add_test_to_suite( p_suite, test_intersection_7, "test_intersection_7" );

   // test_intersection_8
   add_test_to_suite( p_suite, test_intersection_8, "test_intersection_8" );

   return CUE_SUCCESS;
   
}

#ifdef __cplusplus
}
#endif

/* End of file */

