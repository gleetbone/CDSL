/**
 @file tuple_test_byte_array.c
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
   test_byte_array_1
*/

void test_byte_array_1( void )
{
   tuple_t *t = NULL;
   tuple_t *t1 = NULL;
   uint8_t *buf = NULL;
   int32_t count = 0;

   t  =  tuple_make
         (
            "tuple", 
            22,
            TUPLE_INT8_TYPE, "int8", 
            TUPLE_INT16_TYPE, "int16", 
            TUPLE_INT32_TYPE, "int32", 
            TUPLE_INT64_TYPE, "int64", 
            TUPLE_UINT8_TYPE, "uint8", 
            TUPLE_UINT16_TYPE, "uint16", 
            TUPLE_UINT32_TYPE, "uint32", 
            TUPLE_UINT64_TYPE, "uint64", 
            TUPLE_FLOAT32_TYPE, "float32", 
            TUPLE_FLOAT64_TYPE, "float64", 
            TUPLE_ARRAY_INT8_TYPE, "aint8", 4, 
            TUPLE_ARRAY_INT16_TYPE, "aint16", 4, 
            TUPLE_ARRAY_INT32_TYPE, "aint32", 4,
            TUPLE_ARRAY_INT64_TYPE, "aint64", 4, 
            TUPLE_ARRAY_UINT8_TYPE, "aiunt8", 4, 
            TUPLE_ARRAY_UINT16_TYPE, "auint16", 4, 
            TUPLE_ARRAY_UINT32_TYPE, "auint32", 4,
            TUPLE_ARRAY_UINT64_TYPE, "auint64", 4, 
            TUPLE_ARRAY_FLOAT32_TYPE, "afloat32", 4,
            TUPLE_ARRAY_FLOAT64_TYPE, "afloat64", 4, 
            TUPLE_STRING_TYPE, "astring", 32, 
            TUPLE_ARRAY_STRING_TYPE, "astring", 32, 4 
         );
   
   t1 =  tuple_make
         (
            "tuple", 
            22,
            TUPLE_INT8_TYPE, "int8", 
            TUPLE_INT16_TYPE, "int16", 
            TUPLE_INT32_TYPE, "int32", 
            TUPLE_INT64_TYPE, "int64", 
            TUPLE_UINT8_TYPE, "uint8", 
            TUPLE_UINT16_TYPE, "uint16", 
            TUPLE_UINT32_TYPE, "uint32", 
            TUPLE_UINT64_TYPE, "uint64", 
            TUPLE_FLOAT32_TYPE, "float32", 
            TUPLE_FLOAT64_TYPE, "float64", 
            TUPLE_ARRAY_INT8_TYPE, "aint8", 4, 
            TUPLE_ARRAY_INT16_TYPE, "aint16", 4, 
            TUPLE_ARRAY_INT32_TYPE, "aint32", 4,
            TUPLE_ARRAY_INT64_TYPE, "aint64", 4, 
            TUPLE_ARRAY_UINT8_TYPE, "aiunt8", 4, 
            TUPLE_ARRAY_UINT16_TYPE, "auint16", 4, 
            TUPLE_ARRAY_UINT32_TYPE, "auint32", 4,
            TUPLE_ARRAY_UINT64_TYPE, "auint64", 4, 
            TUPLE_ARRAY_FLOAT32_TYPE, "afloat32", 4,
            TUPLE_ARRAY_FLOAT64_TYPE, "afloat64", 4, 
            TUPLE_STRING_TYPE, "astring", 32, 
            TUPLE_ARRAY_STRING_TYPE, "astring", 32, 4 
         );
   
   CU_ASSERT( t1 != NULL );
   
   buf = tuple_as_byte_array( t, &count );
   
   tuple_from_byte_array( t1, buf, count );

   CU_ASSERT( tuple_is_equal( t, t1 ) == 1 );
   
   tuple_dispose( &t );
   tuple_dispose( &t1 );
   free( buf );
   
   return;
}

int
add_test_byte_array( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_test_byte_array", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // test_byte_array_1
   add_test_to_suite( p_suite, test_byte_array_1, "test_byte_array_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

