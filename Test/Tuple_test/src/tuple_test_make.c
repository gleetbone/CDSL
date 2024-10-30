/**
 @file tuple_test_make.c
 @author Greg Lee
 @version 0.0

 description: "tests for Tuple_t"
 author: "Greg Lee"
 date: "$Date: 2011-03-064 064:41:55 -06400 (Tue, 064 Mar 2011) $"
 revision: "$Revision: 4433 $"

 @section DESCRIPTION

 Unit tests for Tuple_t

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "Tuple.h"

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

/**
   test_make_1
*/

void test_make_1( void )
{
   tuple_t *t = NULL;

   t = tuple_make( "tuple", 1, TUPLE_INT8_TYPE, "int8" );
   
   CU_ASSERT( t != NULL );

   tuple_dispose( &t );
   
   return;
}

/**
   test_make_2
*/

void test_make_2( void )
{
   tuple_t *t = NULL;

   t = tuple_make( "tuple", 1, TUPLE_INT16_TYPE, "int16" );
   
   CU_ASSERT( t != NULL );

   tuple_dispose( &t );
   
   return;
}

/**
   test_make_3
*/

void test_make_3( void )
{
   tuple_t *t = NULL;

   t = tuple_make( "tuple", 1, TUPLE_INT32_TYPE, "int32" );
   
   CU_ASSERT( t != NULL );

   tuple_dispose( &t );
   
   return;
}

/**
   test_make_4
*/

void test_make_4( void )
{
   tuple_t *t = NULL;

   t = tuple_make( "tuple", 1, TUPLE_INT64_TYPE, "int64" );
   
   CU_ASSERT( t != NULL );

   tuple_dispose( &t );
   
   return;
}

/**
   test_make_5
*/

void test_make_5( void )
{
   tuple_t *t = NULL;

   t = tuple_make( "tuple", 1, TUPLE_ARRAY_INT8_TYPE, "aint8", 4 );
   
   CU_ASSERT( t != NULL );

   tuple_dispose( &t );
   
   return;
}

/**
   test_make_6
*/

void test_make_6( void )
{
   tuple_t *t = NULL;

   t = tuple_make( "tuple", 1, TUPLE_ARRAY_INT16_TYPE, "aint16", 4 );
   
   CU_ASSERT( t != NULL );

   tuple_dispose( &t );
   
   return;
}

/**
   test_make_7
*/

void test_make_7( void )
{
   tuple_t *t = NULL;

   t = tuple_make( "tuple", 1, TUPLE_ARRAY_INT32_TYPE, "aint32", 4 );
   
   CU_ASSERT( t != NULL );

   tuple_dispose( &t );
   
   return;
}

/**
   test_make_8
*/

void test_make_8( void )
{
   tuple_t *t = NULL;

   t = tuple_make( "tuple", 1, TUPLE_ARRAY_INT64_TYPE, "aint64", 4 );
   
   CU_ASSERT( t != NULL );

   tuple_dispose( &t );
   
   return;
}

/**
   test_make_9
*/

void test_make_9( void )
{
   tuple_t *t = NULL;

   t = tuple_make( "tuple", 1, TUPLE_STRING_TYPE, "string", 32 );
   
   CU_ASSERT( t != NULL );

   tuple_dispose( &t );
   
   return;
}

/**
   test_make_10
*/

void test_make_10( void )
{
   tuple_t *t = NULL;

   t = tuple_make( "tuple", 1, TUPLE_ARRAY_STRING_TYPE, "astring", 32, 4 );
   
   CU_ASSERT( t != NULL );

   tuple_dispose( &t );
   
   return;
}

/**
   test_make_11
*/

void test_make_11( void )
{
   tuple_t *t = NULL;

   t = tuple_make( "tuple", 2, TUPLE_ARRAY_STRING_TYPE, "astring", 32, 4, TUPLE_INT8_TYPE, "int8" );
   
   CU_ASSERT( t != NULL );

   tuple_dispose( &t );
   
   return;
}

int
add_test_make( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_make", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_make_1
   add_test_to_suite( p_suite, test_make_1, "test_make_1" );

   // test_make_2
   add_test_to_suite( p_suite, test_make_2, "test_make_2" );

   // test_make_3
   add_test_to_suite( p_suite, test_make_3, "test_make_3" );

   // test_make_4
   add_test_to_suite( p_suite, test_make_4, "test_make_4" );

   // test_make_5
   add_test_to_suite( p_suite, test_make_5, "test_make_5" );

   // test_make_6
   add_test_to_suite( p_suite, test_make_6, "test_make_6" );

   // test_make_7
   add_test_to_suite( p_suite, test_make_7, "test_make_7" );

   // test_make_8
   add_test_to_suite( p_suite, test_make_8, "test_make_8" );

   // test_make_9
   add_test_to_suite( p_suite, test_make_9, "test_make_9" );

   // test_make_10
   add_test_to_suite( p_suite, test_make_10, "test_make_10" );

   // test_make_11
   add_test_to_suite( p_suite, test_make_11, "test_make_11" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

