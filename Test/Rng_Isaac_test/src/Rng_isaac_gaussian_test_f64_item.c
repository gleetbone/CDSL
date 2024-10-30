/**
 @file Rng_isaac_gaussian_test_f64_item.c
 @author Greg Lee
 @version 2.0.0
 @brief: "tests for Rng_isaac_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for Rng_isaac_make.

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "CUnit/Basic.h"

#include "Rng_Isaac_gaussian.h"

#define UNION_CAST(x, destType) \
 (((union {__typeof__(x) a; destType b;})x).b)

int
add_test_to_suite( CU_pSuite p_suite, CU_TestFunc test, char *name );

static int32_t count = 0;
static float64_t sum = 0.0;
static float64_t sum_squares = 0.0;

static
float64_t
mean( void )
{
   float64_t result = sum/count;
   return result;
}

static
float64_t
std( void )
{
   float64_t result = sqrt( ( sum_squares - sum*sum/count )/( count - 1 ) );
   return result;
}

/**
   gaussian_test_f64_item_1
*/

void gaussian_test_f64_item_1( void )
{
   rng_isaac_gaussian_t *rng = NULL;
   int32_t i = 0;
   float64_t f = 0;

   rng = rng_isaac_gaussian_make();

   CU_ASSERT( rng != NULL );

   for ( i=0; i<1000000; i++ )
   {
      f = rng_isaac_gaussian_f64_item( rng );
      rng_isaac_gaussian_forth( rng );

      count = count + 1;
      sum = sum + f;
      sum_squares = sum_squares + f*f;

   }

   f = mean();
   CU_ASSERT( f < 0.001 );
   f = std() - 1.0;
   f = fabs( f );
   CU_ASSERT( f < 0.0005 );

   rng_isaac_gaussian_dispose( &rng );

   return;
}

int
add_gaussian_test_f64_item( void )
{
   CU_pSuite p_suite = NULL;

   // add a suite for these tests to the registry
   p_suite = CU_add_suite("suite_gaussian_test_f64_item", NULL, NULL);
   if (NULL == p_suite)
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   // add the tests to the suite

   // gaussian_test_f64_item_1
   add_test_to_suite( p_suite, gaussian_test_f64_item_1, "gaussian_test_f64_item_1" );

   return CUE_SUCCESS;

}

#ifdef __cplusplus
}
#endif

/* End of file */

