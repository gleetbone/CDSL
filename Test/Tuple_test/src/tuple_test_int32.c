/**
 @file tuple_test_int32.c
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
   test_int32_1
*/

void test_int32_1( void )
{
   tuple_t *t = NULL;
   int32_t i = 0;

   t = tuple_make( "tuple", 1, TUPLE_INT32_TYPE, "int32" );
   CU_ASSERT( t != NULL );
   
   tuple_put_int32( t, 0, 13 );
   
   i = tuple_item_int32( t, 0 );
   CU_ASSERT( i == 13 );
   
   tuple_dispose( &t );
   
   return;
}

/**
   test_int32_2
*/

void test_int32_2( void )
{
   tuple_t *t = NULL;
   int32_t *aint32 = NULL;
   int32_t *aint32a = NULL;
   int32_t count = 0;
   int32_t i = 0;

   t = tuple_make( "tuple", 1, TUPLE_ARRAY_INT32_TYPE, "int32", 4 );
   CU_ASSERT( t != NULL );
   
   aint32 = ( int32_t * ) calloc( 4, sizeof( int32_t ) );
   
   tuple_put_aint32( t, 0, aint32, 4 );
   
   aint32a = tuple_item_aint32( t, 0 , &count);
   CU_ASSERT( aint32a != NULL );
   CU_ASSERT( count == 4 );

   tuple_put_element_aint32( t, 0, 1, 13 );
   
   i = tuple_item_element_aint32( t, 0, 1 );
   CU_ASSERT( i == 13 );
   
   free( aint32 );
   free( aint32a );
   tuple_dispose( &t );
   
   return;
}

int
add_test_int32( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_int32", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_int32_1
   add_test_to_suite( p_suite, test_int32_1, "test_int32_1" );

   // test_int32_2
   add_test_to_suite( p_suite, test_int32_2, "test_int32_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

