/**
 @file tuple_test_uint8.c
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
   test_uint8_1
*/

void test_uint8_1( void )
{
   tuple_t *t = NULL;
   uint8_t i = 0;

   t = tuple_make( "tuple", 1, TUPLE_UINT8_TYPE, "uint8" );
   CU_ASSERT( t != NULL );
   
   tuple_put_uint8( t, 0, 13 );
   
   i = tuple_item_uint8( t, 0 );
   CU_ASSERT( i == 13 );
   
   tuple_dispose( &t );
   
   return;
}

/**
   test_uint8_2
*/

void test_uint8_2( void )
{
   tuple_t *t = NULL;
   uint8_t *auint8 = NULL;
   uint8_t *auint8a = NULL;
   int32_t count = 0;
   uint8_t i = 0;

   t = tuple_make( "tuple", 1, TUPLE_ARRAY_UINT8_TYPE, "uint8", 4 );
   CU_ASSERT( t != NULL );
   
   auint8 = ( uint8_t * ) calloc( 4, sizeof( uint8_t ) );
   
   tuple_put_auint8( t, 0, auint8, 4 );
   
   auint8a = tuple_item_auint8( t, 0 , &count);
   CU_ASSERT( auint8a != NULL );
   CU_ASSERT( count == 4 );

   tuple_put_element_auint8( t, 0, 1, 13 );
   
   i = tuple_item_element_auint8( t, 0, 1 );
   CU_ASSERT( i == 13 );
   
   free( auint8 );
   free( auint8a );
   tuple_dispose( &t );
   
   return;
}

int
add_test_uint8( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_uint8", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_uint8_1
   add_test_to_suite( p_suite, test_uint8_1, "test_uint8_1" );

   // test_uint8_2
   add_test_to_suite( p_suite, test_uint8_2, "test_uint8_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

