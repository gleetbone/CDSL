/**
 @file s_BSTree.c
 @author Greg Lee
 @version 2.0.0
 @brief: "implementation file for binary search tree of Strings"
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee
 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0)
 
 @section Description

 Defines for s_BSTree type.

*/

#include "s_BSTree.h"

#ifdef __cplusplus
extern "C" {
#endif
 
#define VALUE_DEEP_DISPOSE_FUNCTION( arg ) string_deep_dispose( &arg )
#define VALUE_DEEP_CLONE_FUNCTION( arg ) string_deep_clone( arg )
#define VALUE_DEEP_EQUAL_FUNCTION( arg1, arg2 ) string_is_deep_equal( (arg1), (arg2) )
#define VALUE_DEFAULT NULL

#define ORDER_FUNCTION( arg1, arg2 ) ( ( string_is_less_than( arg1, arg2 ) == 1  ) || ( string_is_equal( arg1, arg2 ) == 1 ) )

#define PRE_FILE DBC_YES
#define POST_FILE DBC_YES
#define INVARIANT_FILE DBC_YES

#define Prefix s
#define Type string_t *
#define Type_Code STRING_TYPE

#include <stdio.h>
#include <stdlib.h>


static int32_t print_flag = 0;

static void print_nodes( s_bstree_t *btree );
static void print_tree( s_bstree_t *btree );

#include "BSTree.c"

static void print_nodes( s_bstree_t *bstree )
{
   s_bstree_cursor_t *cursor = NULL;

   if ( print_flag != 0 )
   {
      cursor = cursor_make( bstree );
      cursor_start( cursor );
   
      printf( "\n" );
      while( cursor_off( cursor ) == 0 )
      {
         // value
         printf( " %s", string_as_cstring( (*(*cursor).item).value ) );
   
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
      
      printf( "%s ", string_as_cstring( (*node).value ) );
      
      printf( "\n" );
      
      print_tree_recurse( (*node).left, spaces + SEPARATOR_SPACES ); 
      print_tree_recurse( (*node).right, spaces + SEPARATOR_SPACES ); 
         
   }
   
   return;
}

static void print_tree( s_bstree_t *bstree )
{
   if ( print_flag != 0 )
   {
      printf( "\n%d\n", (*bstree).count );
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

