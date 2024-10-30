/**
 @file tuple_test_int64.c
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
   test_int64_1
*/

void test_int64_1( void )
{
   tuple_t *t = NULL;
   int64_t i = 0;

   t = tuple_make( "tuple", 1, TUPLE_INT64_TYPE, "int64" );
   CU_ASSERT( t != NULL );
   
   tuple_put_int64( t, 0, 13 );
   
   i = tuple_item_int64( t, 0 );
   CU_ASSERT( i == 13 );
   
   tuple_dispose( &t );
   
   return;
}

/**
   test_int64_2
*/

void test_int64_2( void )
{
   tuple_t *t = NULL;
   int64_t *aint64 = NULL;
   int64_t *aint64a = NULL;
   int32_t count = 0;
   int64_t i = 0;

   t = tuple_make( "tuple", 1, TUPLE_ARRAY_INT64_TYPE, "int64", 4 );
   CU_ASSERT( t != NULL );
   
   aint64 = ( int64_t * ) calloc( 4, sizeof( int64_t ) );
   
   tuple_put_aint64( t, 0, aint64, 4 );
   
   aint64a = tuple_item_aint64( t, 0 , &count);
   CU_ASSERT( aint64a != NULL );
   CU_ASSERT( count == 4 );

   tuple_put_element_aint64( t, 0, 1, 13 );
   
   i = tuple_item_element_aint64( t, 0, 1 );
   CU_ASSERT( i == 13 );
   
   free( aint64 );
   free( aint64a );
   tuple_dispose( &t );
   
   return;
}

int
add_test_int64( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_int64", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_int64_1
   add_test_to_suite( p_suite, test_int64_1, "test_int64_1" );

   // test_int64_2
   add_test_to_suite( p_suite, test_int64_2, "test_int64_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

