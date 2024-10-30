/**
 @file tuple_test_float32.c
 @author Greg Lee
 @version 0.0

 description: "tests for Tuple_t"
 author: "Greg Lee"
 date: "$Date: 2011-03-032 032:41:55 -03200 (Tue, 032 Mar 2011) $"
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
   test_float32_1
*/

void test_float32_1( void )
{
   tuple_t *t = NULL;
   float32_t f = 0;

   t = tuple_make( "tuple", 1, TUPLE_FLOAT32_TYPE, "float32" );
   CU_ASSERT( t != NULL );
   
   tuple_put_float32( t, 0, 13.0 );
   
   f = tuple_item_float32( t, 0 );
   CU_ASSERT( f == 13.0 );
   
   tuple_dispose( &t );
   
   return;
}

/**
   test_float32_2
*/

void test_float32_2( void )
{
   tuple_t *t = NULL;
   float32_t *afloat32 = NULL;
   float32_t *afloat32a = NULL;
   int32_t count = 0;
   float32_t f = 0;

   t = tuple_make( "tuple", 1, TUPLE_ARRAY_FLOAT32_TYPE, "float32", 4 );
   CU_ASSERT( t != NULL );
   
   afloat32 = ( float32_t * ) calloc( 4, sizeof( float32_t ) );
   
   tuple_put_afloat32( t, 0, afloat32, 4 );
   
   afloat32a = tuple_item_afloat32( t, 0 , &count);
   CU_ASSERT( afloat32a != NULL );
   CU_ASSERT( count == 4 );

   tuple_put_element_afloat32( t, 0, 1, 13.0 );
   
   f = tuple_item_element_afloat32( t, 0, 1 );
   CU_ASSERT( f == 13.0 );
   
   free( afloat32 );
   free( afloat32a );
   tuple_dispose( &t );
   
   return;
}

int
add_test_float32( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_float32", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_float32_1
   add_test_to_suite( p_suite, test_float32_1, "test_float32_1" );

   // test_float32_2
   add_test_to_suite( p_suite, test_float32_2, "test_float32_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

