/**
 @file tuple_test_pointer.c
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
   test_pointer_1
*/

void test_pointer_1( void )
{
   tuple_t *t = NULL;
   void *p = NULL;

   t = tuple_make( "tuple", 1, TUPLE_POINTER_TYPE, "pointer" );
   CU_ASSERT( t != NULL );
   
   tuple_put_pointer( t, 0, ( void * ) 0x12345678 );
   
   p = tuple_item_pointer( t, 0 );
   CU_ASSERT( p == (void * )  0x12345678 );
   
   tuple_dispose( &t );
   
   return;
}

/**
   test_pointer_2
*/

void test_pointer_2( void )
{
   tuple_t *t = NULL;
   void **apointer = NULL;
   void **apointera = NULL;
   int32_t count = 0;
   void *p = NULL;

   t = tuple_make( "tuple", 1, TUPLE_ARRAY_POINTER_TYPE, "pointer", 4 );
   CU_ASSERT( t != NULL );
   
   apointer = ( void ** ) calloc( 4, sizeof( void * ) );
   
   tuple_put_apointer( t, 0, apointer, 4 );
   
   apointera = tuple_item_apointer( t, 0 , &count);
   CU_ASSERT( apointera != NULL );
   CU_ASSERT( count == 4 );

   tuple_put_element_apointer( t, 0, 1, ( void * ) 0x12345678 );
   
   p = tuple_item_element_apointer( t, 0, 1 );
   CU_ASSERT( p == ( void * ) 0x12345678 );
   
   free( apointer );
   free( apointera );
   tuple_dispose( &t );
   
   return;
}

int
add_test_pointer( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_pointer", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_pointer_1
   add_test_to_suite( p_suite, test_pointer_1, "test_pointer_1" );

   // test_pointer_2
   add_test_to_suite( p_suite, test_pointer_2, "test_pointer_2" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

