/**
 @file ii_BTree_kv.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for hash table of ints to ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License

 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)

 @section Description

 Defines for int_DList type.

*/

#include "ii_BTree_kv.h"

#ifdef __cplusplus
extern "C" {
#endif

#define KEY_EQUAL_FUNCTION( arg1, arg2 ) ( arg1 == arg2 )

#define VALUE_EQUAL_FUNCTION( arg1, arg2 ) ( arg1 == arg2 )

#define KEY_DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( arg1 == arg2 )

#define VALUE_DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( arg1 == arg2 )

#define KEY_ORDER_FUNCTION( arg1, arg2 ) ( arg1 < arg2 )

#define KEY_DISPOSE_FUNCTION( arg )

#define VALUE_DISPOSE_FUNCTION( arg )

#define KEY_DEEP_DISPOSE_FUNCTION( arg )

#define VALUE_DEEP_DISPOSE_FUNCTION( arg )

#define KEY_DUPLICATE_FUNCTION( arg ) ( arg )

#define VALUE_DUPLICATE_FUNCTION( arg ) ( arg )

#define KEY_DEFAULT_VALUE 0

#define VALUE_DEFAULT_VALUE 0

#define Prefix ii
#define Type int32_t
#define Key int32_t
#define Key_Code int32_type_code
#define Type_Code int32_type_code

#define PROTOCOLS_ENABLED

#include <stdio.h>
#include <stdlib.h>

static int32_t print_flag = 0;

static void print_nodes( ii_btree_kv_t *btree );
static void print_tree( ii_btree_kv_t *btree );

#include "BTree_kv.c"

static void print_nodes( ii_btree_kv_t *btree )
{
if ( print_flag != 0 )
{
   ii_btree_kv_cursor_t *cursor = NULL;
   int32_t i = 0;

   cursor = cursor_make( btree );
   cursor_start( cursor );

   printf( "\n" );
   while( ii_btree_kv_cursor_off( cursor ) == 0 )
   {
      // index and n
      printf
      (
         "%d %d",
         (*cursor).indices[ (*cursor).i_indices ],
         (*(*cursor).item).n
      );

      printf( " |" );
 
      // keys 
      //for ( i=0; i<(*(*cursor).item).n; i++ )
      for ( i=0; i < (*btree).max_n_keys + 1; i++ )
      {
         printf( " %d", (*(*cursor).item).keys[i] );
      }

      printf( " |" );
 
      // values
      //for ( i=0; i<(*(*cursor).item).n; i++ )
      for ( i=0; i < (*btree).max_n_keys + 1; i++ )
      {
         printf( " %d", (*(*cursor).item).values[i] );
      }

      printf( " |" );
 
      printf( " |" );
 
      // children
      //for ( i=0; i<(*(*cursor).item).n + 1; i++ )
      for ( i=0; i < (*btree).max_n_keys + 1 + 1; i++ )
      {
         printf( " %p", (*(*cursor).item).children[i] );
      }

      printf( " |" );
 
      // self
      printf( " %p", (*cursor).item );

      printf( " |" );
 
      // parent
      printf( " %p", (*(*cursor).item).parent );

      printf( " |" );
 
      // i_indices
      printf( " %d", (*cursor).i_indices );

      printf( " |" );
 
      // indices
      for ( i=0; i<(*cursor).n_indices; i++ )
      {
         printf( " %d", (*cursor).indices[i] );
      }

      printf( "\n" );

      cursor_forth( cursor );
   }
   
   cursor_dispose( &cursor );
}
   return;
}

#define SEPARATOR_SPACES 4

static void print_tree_recurse( node_t *node, int32_t spaces )
{
   int32_t i = 0;

   if ( node != NULL )
   {
      for ( i=0; i<spaces; i++ )
      {
         printf( " " );
      }
      
      for ( i=0; i<(*node).n; i++ )
      {
         printf( "%d ", (*node).keys[i] );
      }
      printf( "\n" );
      
      for ( i=0; i<=(*node).n; i++ )
      {
         print_tree_recurse( (*node).children[i], spaces + SEPARATOR_SPACES ); 
      }

   }
   
   return;
}

static void print_tree( ii_btree_kv_t *btree )
{
   if ( print_flag != 0 )
   {
      print_tree_recurse( (*btree).root, 0 );
      printf( "\n" );
   }
   return;
}

#undef Prefix
#undef Type
#undef Key
#undef Key_Code
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */

