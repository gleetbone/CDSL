/**
 @file i_BSTree.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for binary search tree of ints"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for int_DList type.

*/

#include "i_BSTree.h"

#ifdef __cplusplus
extern "C" {
#endif
 
#define VALUE_DEEP_DISPOSE_FUNCTION( arg )
#define VALUE_DEEP_CLONE_FUNCTION( arg ) ( arg )
#define VALUE_DEEP_EQUAL_FUNCTION( arg1, arg2 ) ( (arg1) == (arg2) )
#define VALUE_DEFAULT 0

#define ORDER_FUNCTION( arg1, arg2 ) ( ( arg1 <= arg2  ) )

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix i
#define Type int32_t
#define Type_Code int32_type_code

#include <stdio.h>
#include <stdlib.h>


 int32_t print_flag = 0;

static void print_nodes( i_bstree_t *btree );
static void print_tree( i_bstree_t *btree );

#include "BSTree.c"

static void print_nodes( i_bstree_t *bstree )
{
   i_bstree_cursor_t *cursor = NULL;
   int32_t i = 0;

   if ( print_flag != 0 )
   {
      cursor = cursor_make( bstree );
      cursor_start( cursor );
   
      printf( "\n" );
      while( cursor_off( cursor ) == 0 )
      {
         // value
         printf( " %d", (*(*cursor).item).value );
   
         printf( " |" );
    
         // self and parent
         printf( " %p", (*cursor).item );
         printf( " %p", (*(*cursor).item).parent );
         
         printf( " |" );
    
         // children
         printf( " %p", (*(*cursor).item).left );
         printf( " %p", (*(*cursor).item).right );
         
         printf( " |" );
         
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
      
      printf( "%d ", (*node).value );
      
      printf( "\n" );
      
      print_tree_recurse( (*node).left, spaces + SEPARATOR_SPACES ); 
      print_tree_recurse( (*node).right, spaces + SEPARATOR_SPACES ); 
         
   }
   
   return;
}

static void print_tree( i_bstree_t *bstree )
{
   if ( print_flag != 0 )
   {
      print_tree_recurse( (*bstree).root, 0 );
      printf( "\n" );
   }
   return;
}

#undef Prefix
#undef Type
#undef Type_Code

#ifdef __cplusplus
}
#endif

/* End of file */

