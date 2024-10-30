/**
 @file tuple_test_field_info.c
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
   test_field_info_1
*/

void test_field_info_1( void )
{
   tuple_t *t = NULL;
   char_t *name = NULL;
   int32_t i = 0;

   t = tuple_make( "tuple", 1, TUPLE_INT32_TYPE, "int32" );
   CU_ASSERT( t != NULL );
   
   name = tuple_name( t );
   CU_ASSERT( strcmp( name, "tuple" ) == 0 )
   free( name );
   
   i = tuple_field_count( t );
   CU_ASSERT( i == 1 );
   
   i = tuple_field_type( t, 0 );
   CU_ASSERT( i == TUPLE_INT32_TYPE );
   
   name = tuple_field_name( t, 0 );
   CU_ASSERT( strcmp( name, "int32" ) == 0 )
   free( name );
   
   i = tuple_field_array_count( t, 0 );
   CU_ASSERT( i == 1 );
   
   i = tuple_field_string_length( t, 0 );
   CU_ASSERT( i == 0 );
   
   i = tuple_field_is_array( t, 0 );
   CU_ASSERT( i == 0 );
   
   i = tuple_field_is_string( t, 0 );
   CU_ASSERT( i == 0 );
   
   tuple_dispose( &t );
   
   return;
}

/**
   test_field_info_2
*/

void test_field_info_2( void )
{
   tuple_t *t = NULL;
   char_t *name = NULL;
   int32_t i = 0;

   t = tuple_make( "tuple", 1, TUPLE_STRING_TYPE, "astring", 32 );
   CU_ASSERT( t != NULL );
   
   name = tuple_name( t );
   CU_ASSERT( strcmp( name, "tuple" ) == 0 )
   free( name );
   
   i = tuple_field_count( t );
   CU_ASSERT( i == 1 );
   
   i = tuple_field_type( t, 0 );
   CU_ASSERT( i == TUPLE_STRING_TYPE );
   
   name = tuple_field_name( t, 0 );
   CU_ASSERT( strcmp( name, "astring" ) == 0 )
   free( name );
   
   i = tuple_field_array_count( t, 0 );
   CU_ASSERT( i == 32 );
   
   i = tuple_field_string_length( t, 0 );
   CU_ASSERT( i == 32 );
   
   i = tuple_field_is_array( t, 0 );
   CU_ASSERT( i == 0 );
   
   i = tuple_field_is_string( t, 0 );
   CU_ASSERT( i == 1 );
   
   tuple_dispose( &t );
   
   return;
}

/**
   test_field_info_3
*/

void test_field_info_3( void )
{
   tuple_t *t = NULL;
   char_t *name = NULL;
   int32_t i = 0;

   t = tuple_make( "tuple", 1, TUPLE_ARRAY_STRING_TYPE, "astring", 32, 4 );
   CU_ASSERT( t != NULL );
   
   name = tuple_name( t );
   CU_ASSERT( strcmp( name, "tuple" ) == 0 )
   free( name );
   
   i = tuple_field_count( t );
   CU_ASSERT( i == 1 );
   
   i = tuple_field_type( t, 0 );
   CU_ASSERT( i == TUPLE_ARRAY_STRING_TYPE );
   
   name = tuple_field_name( t, 0 );
   CU_ASSERT( strcmp( name, "astring" ) == 0 )
   free( name );
   
   i = tuple_field_array_count( t, 0 );
   CU_ASSERT( i == 4 );
   
   i = tuple_field_string_length( t, 0 );
   CU_ASSERT( i == 32 );
   
   i = tuple_field_is_array( t, 0 );
   CU_ASSERT( i == 1 );
   
   i = tuple_field_is_string( t, 0 );
   CU_ASSERT( i == 1 );
   
   tuple_dispose( &t );
   
   return;
}

int
add_test_field_info( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_field_info", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_field_info_1
   add_test_to_suite( p_suite, test_field_info_1, "test_field_info_1" );

   // test_field_info_2
   add_test_to_suite( p_suite, test_field_info_2, "test_field_info_2" );

   // test_field_info_3
   add_test_to_suite( p_suite, test_field_info_3, "test_field_info_3" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

