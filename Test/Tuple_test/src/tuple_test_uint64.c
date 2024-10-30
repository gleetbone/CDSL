/**
 @file tuple_test_uint64.c
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
   test_uint64_1
*/

void test_uint64_1( void )
{
   tuple_t *t = NULL;
   uint64_t i = 0;

   t = tuple_make( "tuple", 1, TUPLE_UINT64_TYPE, "uint64" );
   CU_ASSERT( t != NULL );
   
   tuple_put_uint64( t, 0, 13 );
   
   i = tuple_item_uint64( t, 0 );
   CU_ASSERT( i == 13 );
   
   tuple_dispose( &t );
   
   return;
}

/**
   test_uint64_2
*/

void test_uint64_2( void )
{
   tuple_t *t = NULL;
   uint64_t *auint64 = NULL;
   uint64_t *auint64a = NULL;
   int32_t count = 0;
   uint64_t i = 0;

   t = tuple_make( "tuple", 1, TUPLE_ARRAY_UINT64_TYPE, "uint64", 4 );
   CU_ASSERT( t != NULL );
   
   auint64 = ( uint64_t * ) calloc( 4, sizeof( uint64_t ) );
   
   tuple_put_auint64( t, 0, auint64, 4 );
   
   auint64a = tuple_item_auint64( t, 0 , &count);
   CU_ASSERT( auint64a != NULL );
   CU_ASSERT( count == 4 );

   tuple_put_element_auint64( t, 0, 1, 13 );
   
   i = tuple_item_element_auint64( t, 0, 1 );
   CU_ASSERT( i == 13 );
   
   free( auint64 );
   free( auint64a );
   tuple_dispose( &t );
   
   return;
}

int
add_test_uint64( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_uint64", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_uint64_1
   add_test_to_suite( p_suite, test_uint64_1, "test_uint64_1" );

   // test_uint64_2
   add_test_to_suite( p_suite, test_uint64_2, "test_uint64_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

