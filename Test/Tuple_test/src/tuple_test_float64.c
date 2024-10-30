/**
 @file tuple_test_float64.c
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
   test_float64_1
*/

void test_float64_1( void )
{
   tuple_t *t = NULL;
   float64_t f = 0;

   t = tuple_make( "tuple", 1, TUPLE_FLOAT64_TYPE, "float64" );
   CU_ASSERT( t != NULL );
   
   tuple_put_float64( t, 0, 13.0 );
   
   f = tuple_item_float64( t, 0 );
   CU_ASSERT( f == 13.0 );
   
   tuple_dispose( &t );
   
   return;
}

/**
   test_float64_2
*/

void test_float64_2( void )
{
   tuple_t *t = NULL;
   float64_t *afloat64 = NULL;
   float64_t *afloat64a = NULL;
   int32_t count = 0;
   float64_t f = 0;

   t = tuple_make( "tuple", 1, TUPLE_ARRAY_FLOAT64_TYPE, "float64", 4 );
   CU_ASSERT( t != NULL );
   
   afloat64 = ( float64_t * ) calloc( 4, sizeof( float64_t ) );
   
   tuple_put_afloat64( t, 0, afloat64, 4 );
   
   afloat64a = tuple_item_afloat64( t, 0 , &count);
   CU_ASSERT( afloat64a != NULL );
   CU_ASSERT( count == 4 );

   tuple_put_element_afloat64( t, 0, 1, 13.0 );
   
   f = tuple_item_element_afloat64( t, 0, 1 );
   CU_ASSERT( f == 13.0 );
   
   free( afloat64 );
   free( afloat64a );
   tuple_dispose( &t );
   
   return;
}

int
add_test_float64( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_float64", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_float64_1
   add_test_to_suite( p_suite, test_float64_1, "test_float64_1" );

   // test_float64_2
   add_test_to_suite( p_suite, test_float64_2, "test_float64_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

