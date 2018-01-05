/**
 @file RBTree_test_print_utility.h
 @author Greg Lee
 @version 0.0
 @brief: "tests for BSTree_make"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Unit tests for BSTree_make.

*/
#ifndef TEST_PRINT_UTILITY_H
#define TEST_PRINT_UTILITY_H

#ifdef __cplusplus
extern "C" {
#endif
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "CUnit/Basic.h"

#include "base.h"

/**
   test_print_utility_make_array
*/

char_t ** test_print_utility_make_array( int32_t height, int32_t width );

/**
   test_print_utility_dispose_array
*/

void test_print_utility_dispose_array( char_t **array );

/**
   test_print_utility_clear_array
*/

void test_print_utility_clear_array( char_t **array, int32_t height, int32_t width );

/**
   test_print_utility_print_array
*/

void test_print_utility_print_array( char_t **array );

#ifdef __cplusplus
}
#endif

#endif /* TEST_PRINT_UTILITY_H */

/* End of file */

