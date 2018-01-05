/**
 @file BSTree.h
 @author Greg Lee
 @version 1.0.0
 @brief: "Binary Search Trees"
 
 @date: "$Mon Jan 01 15:18:30 PST 2018 @12 /Internet Time/$"

 @section License
 
 Copyright 2018 Greg Lee

 Licensed under the Eiffel Forum License, Version 2 (EFL-2.0):
 
 1. Permission is hereby granted to use, copy, modify and/or
    distribute this package, provided that:
       * copyright notices are retained unchanged,
       * any distribution of this package, whether modified or not,
         includes this license text.
 2. Permission is hereby also granted to distribute binary programs
    which depend on this package. If the binary program depends on a
    modified version of this package, you are encouraged to publicly
    release the modified version of this package. 

 THIS PACKAGE IS PROVIDED "AS IS" AND WITHOUT WARRANTY. ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE AUTHORS BE LIABLE TO ANY PARTY FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES ARISING IN ANY WAY OUT OF THE USE OF THIS PACKAGE.
 
 @section Description

 Function declarations for the opaque BSTree_t type.
 
*/

#ifdef __cplusplus
extern "C" {
#endif
 
/**
   Note that this include file does NOT have an include guard - it may 
   be included multiple times with different macro defintions.
   
   Defines that must be present (external to this file):
   
   Prefix - string used to name this container type
   Type   - the type of the value
   
   Macros that must be present (external to this file):
   
   EQUALITY_FUNCTION       -  compares two key instances for equality
   ORDER_FUNCTION    -  returns 1 if first argument is "before" second argument
   DISPOSE_FUNCTION  -  frees a value instance  
   
*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define BSTree_struct( arg ) PRIMITIVE_CAT( arg, _bstree_struct )
#define BSTree_type( arg ) PRIMITIVE_CAT( arg, _bstree_t )
#define BSTree_name( arg ) PRIMITIVE_CAT( arg, _bstree )

#define BSTree_cursor_struct( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_struct )
#define BSTree_cursor_type( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_t )
#define BSTree_cursor_name( arg ) PRIMITIVE_CAT( arg, _bstree_cursor )

/** 
   Structure declarations
*/

struct BSTree_struct( Prefix );
struct BSTree_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct BSTree_struct( Prefix ) BSTree_type( Prefix );
typedef struct BSTree_cursor_struct( Prefix ) BSTree_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/** 
   Initialization
*/

/**
   BSTree_make
   
   Return a new BSTree_t instance with a default number of buckets.
   
   @return BSTree_t instance 
*/
#define BSTree_make( arg ) PRIMITIVE_CAT( arg, _bstree_make )
BSTree_type( Prefix ) * BSTree_make( Prefix )( void );

/**
   BSTree_make_from
   
   Return a new BSTree_t instance that has the same content as bstree. The
   items in bstree are not copied.
   
   @param  bstree the BSTree_t instance to copy from 
   @return BSTree_t instance 
*/
#define BSTree_make_from( arg ) PRIMITIVE_CAT( arg, _bstree_make_from )
BSTree_type( Prefix ) * BSTree_make_from( Prefix )( BSTree_type( Prefix ) *bstree );

/**
   BSTree_make_duplicate_from
   
   Return a new BSTree_t instance with a duplicate items from bstree
   
   @return BSTree_t instance 
*/

#define BSTree_make_duplicate_from( arg ) PRIMITIVE_CAT( arg, _bstree_make_duplicate_from )
BSTree_type( Prefix ) *
BSTree_make_duplicate_from( Prefix )( BSTree_type( Prefix ) *bstree );

/**
   BSTree_make_from_array
   
   Return a new BSTree_t instance that has the same content as array. The
   items in array are not copied.
   
   @param  bstree the BSTree_t instance to copy from 
   @return BSTree_t instance 
*/
#define BSTree_make_from_array( arg ) PRIMITIVE_CAT( arg, _bstree_make_from_array )
BSTree_type( Prefix ) * BSTree_make_from_array( Prefix )( Type *array, int32_t count );

/**
   BSTree_cursor_make
   
   Return a new BSTree_t cursor instance.
   
   @param  the BSTree_t instance the new cursor works on 
   @return BSTree_cursor_t instance 
*/
#define BSTree_cursor_make( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_make )
BSTree_cursor_type( Prefix ) * BSTree_cursor_make( Prefix )( BSTree_type( Prefix ) *bstree );


/** 
   Disposal
*/

/**
   BSTree_dispose
   
   Frees a BSTree_t instance without freeing its contained keys and values.
   
   @param BSTree_t instance 
*/
#define BSTree_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_dispose )
void BSTree_dispose( Prefix )( BSTree_type( Prefix ) *bstree );

/**
   BSTree_dispose_with_contents
   
   Frees a BSTree_t instance and its contained keys and values.
   
   @param BSTree_t instance 
*/
#define BSTree_dispose_with_contents( arg ) PRIMITIVE_CAT( arg, _bstree_dispose_with_contents )
void BSTree_dispose_with_contents( Prefix )( BSTree_type( Prefix ) *bstree );

/**
   BSTree_cursor_dispose
   
   Frees a BSTree_cursor_t instance. Its bstree is not disposed.
   
   @param BSTree_cursor_t instance 
*/
#define BSTree_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_dispose )
void BSTree_cursor_dispose( Prefix )( BSTree_cursor_type( Prefix ) *cursor );


/** 
   Access
*/

/**
   BSTree_cursor_item_at
   
   Returns the value of the item that the BSTree_cursor_t instance is pointing to.
   
   @param  BSTree_cursor_t instance 
   @return a Type value
*/
#define BSTree_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_item_at )
Type BSTree_cursor_item_at( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_item_at
   
   Returns the value of the item that the BSTree_t instance's internal
   cursor is pointing to.
   
   @param  bstree BSTree_t instance 
   @return a Type value
*/
#define BSTree_item_at( arg ) PRIMITIVE_CAT( arg, _bstree_item_at )
Type BSTree_item_at( Prefix )( BSTree_type( Prefix ) *bstree );

/**
   BSTree_item_at_index
   
   Returns the value of the item pointed to by index. First index is 0.
   
   @param  bstree BSTree_t instance 
   @param  index desired index 
   @return a Type value
*/
#define BSTree_item_at_index( arg ) PRIMITIVE_CAT( arg, _bstree_item_at_index )
Type BSTree_item_at_index( Prefix )( BSTree_type( Prefix ) *bstree, int32_t index );

/**
   BSTree_as_array
   
   Returns the values of the items in the BSTree_t instance as an array.
   
   @param  bstree BSTree_t instance 
   @param  count pointer to the returned count 
   @return array of values
*/
#define BSTree_as_array( arg ) PRIMITIVE_CAT( arg, _bstree_as_array )
Type * BSTree_as_array( Prefix )( BSTree_type( Prefix ) *bstree, int32_t *count );


/** 
   Measurement
*/

/**
   BSTree_count
   
   Returns the number of items in the BSTree_t instance.
   
   @param  bstree BSTree_t instance 
   @return number of items in BSTree instance
*/
#define BSTree_count( arg ) PRIMITIVE_CAT( arg, _bstree_count )
int32_t BSTree_count( Prefix )( BSTree_type( Prefix ) *bstree );

/**
   BSTree_height
   
   Returns the (max) height of the BSTree_t instance.
   
   @param  bstree BSTree_t instance 
   @return (max) height of the BSTree instance
*/
#define BSTree_height( arg ) PRIMITIVE_CAT( arg, _bstree_height )
int32_t BSTree_height( Prefix )( BSTree_type( Prefix ) *bstree );


/** 
   Status report
*/

/**
   BSTree_off
   
   Returns 1 if the BSTree_t instance's internal cursor is off, otherwise 0.
   
   @param  bstree BSTree_t instance 
   @return 1 if internal cursor is off, otherwise 0
*/
#define BSTree_off( arg ) PRIMITIVE_CAT( arg, _bstree_off )
int32_t BSTree_off( Prefix )( BSTree_type( Prefix ) *bstree );

/**
   BSTree_cursor_off
   
   Returns 1 if the BSTree_cursor_t instance is off, otherwise 0.
   
   @param  cursor BSTree_cursor_t instance 
   @return 1 if internal cursor is off, otherwise 0
*/
#define BSTree_cursor_off( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_off )
int32_t BSTree_cursor_off( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_is_empty
   
   Returns 1 if the BSTree_t instance contains no items, otherwise 0.
   
   @param  bstree BSTree_t instance 
   @return 1 if empty, otherwise 0
*/
#define BSTree_is_empty( arg ) PRIMITIVE_CAT( arg, _bstree_is_empty )
int32_t BSTree_is_empty( Prefix )( BSTree_type( Prefix ) *bstree );

/**
   BSTree_has
   
   Returns 1 if the BSTree_t instance contains the key, otherwise 0.
   
   @param  bstree BSTree_t instance 
   @param  value the value to search for 
   @return 1 if bstree has key, otherwise 0
*/
#define BSTree_has( arg ) PRIMITIVE_CAT( arg, _bstree_has )
int32_t BSTree_has( Prefix )( BSTree_type( Prefix ) *bstree, Type value );


/** 
   Cursor movement
*/

/**
   BSTree_cursor_back
   
   Moves the BSTree_cursor_t instance to the previous item or off.
   
   @param  bstree_cursor BSTree_cursor_t instance 
*/
#define BSTree_cursor_back( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_back )
void BSTree_cursor_back( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_cursor_forth
   
   Moves the BSTree_cursor_t instance to the next item or off.
   
   @param  bstree_cursor BSTree_cursor_t instance 
*/
#define BSTree_cursor_forth( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_forth )
void BSTree_cursor_forth( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_cursor_go
   
   Moves the BSTree_t instance's internal cursor to the ith item in the bstree.
   
   @param  bstree_cursor BSTree_cursor_t instance 
   @param  index the index where the cursor will be moved to 
*/
#define BSTree_cursor_go( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_go )
void BSTree_cursor_go( Prefix )( BSTree_cursor_type( Prefix ) *cursor, int32_t index );

/**
   BSTree_cursor_start
   
   Moves the BSTree_cursor_t instance to the first item or off if the bstree is empty.
   
   @param  bstree_cursor BSTree_cursor_t instance 
*/
#define BSTree_cursor_start( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_start )
void BSTree_cursor_start( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_cursor_finish
   
   Moves the BSTree_cursor_t instance to the last item or off if the bstree is empty.
   
   @param  bstree_cursor BSTree_cursor_t instance 
*/
#define BSTree_cursor_finish( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_finish )
void BSTree_cursor_finish( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_cursor_index
   
   Returns index of the cursor - if cursor is off, returns -1
   
   @param  list BSTree_cursor_t instance 
   @return index in list of cursor if not off, -1 otherwise
*/
#define BSTree_cursor_index( arg ) PRIMITIVE_CAT( arg, _bstree_cursor_index )
int32_t BSTree_cursor_index( Prefix )( BSTree_cursor_type( Prefix ) *cursor );

/**
   BSTree_back
   
   Moves the BSTree_t instance internal cursor to the previous item or off.
   
   @param  bstree BSTree_t instance 
*/
#define BSTree_back( arg ) PRIMITIVE_CAT( arg, _bstree_back )
void BSTree_back( Prefix )( BSTree_type( Prefix ) *bstree );

/**
   BSTree_forth
   
   Moves the BSTree_t instance internal cursor to the next item or off.
   
   @param  bstree BSTree_t instance 
*/
#define BSTree_forth( arg ) PRIMITIVE_CAT( arg, _bstree_forth )
void BSTree_forth( Prefix )( BSTree_type( Prefix ) *bstree );

/**
   BSTree_go
   
   Moves the BSTree_t instance's internal cursor to the ith item in the bstree.
   
   @param  bstree BSTree_t instance 
   @param  index the index where the  will be moved to 
*/
#define BSTree_go( arg ) PRIMITIVE_CAT( arg, _bstree_go )
void BSTree_go( Prefix )( BSTree_type( Prefix ) *bstree, int32_t index );

/**
   BSTree_start
   
   Moves the BSTree_t instance's internal cursor to the first item or off if the bstree is empty.
   
   @param  bstree BSTree_t instance 
*/
#define BSTree_start( arg ) PRIMITIVE_CAT( arg, _bstree_start )
void BSTree_start( Prefix )( BSTree_type( Prefix ) *bstree );

/**
   BSTree_finish
   
   Moves the BSTree_t instance's internal cursor to the last item or off if the bstree is empty.
   
   @param  bstree BSTree_t instance 
*/
#define BSTree_finish( arg ) PRIMITIVE_CAT( arg, _bstree_finish )
void BSTree_finish( Prefix )( BSTree_type( Prefix ) *bstree );

/**
   BSTree_index
   
   Returns index of the internal cursor - if internal cursor is off, returns -1
   
   @param  list BSTree_t instance 
   @return index in list of internal cursor if not off, -1 otherwise
*/
#define BSTree_index( arg ) PRIMITIVE_CAT( arg, _bstree_index )
int32_t BSTree_index( Prefix )( BSTree_type( Prefix ) *list );



/** 
   Element change
*/

/**
   BSTree_put
   
   Put the key-value pair into the BSTree_t instance. Replace any existing item
   that has the same key.
   
   @param  bstree BSTree_t instance 
   @param  value the value to insert 
*/
#define BSTree_put( arg ) PRIMITIVE_CAT( arg, _bstree_put )
void BSTree_put( Prefix )( BSTree_type( Prefix ) *bstree, Type value );


/** 
   Removal
*/

/**
   BSTree_remove
   
   Remove the item in the BSTree_t instance that has the key.
   
   @param  bstree BSTree_t instance 
   @param  key the key for the value 
*/
#define BSTree_remove( arg ) PRIMITIVE_CAT( arg, _bstree_remove )
void BSTree_remove( Prefix )( BSTree_type( Prefix ) *bstree, Type value );

/**
   BSTree_remove_and_dispose
   
   Remove the item in the BSTree_t instance that has the key and dispose
   of the key and the value.
   
   @param  bstree BSTree_t instance 
   @param  key the key for the value 
*/
#define BSTree_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_remove_and_dispose )
void BSTree_remove_and_dispose( Prefix )( BSTree_type( Prefix ) *bstree, Type value );

/**
   BSTree_wipe_out
   
   Remove all items in the BSTree_t instance.
   
   @param  bstree BSTree_t instance 
*/
#define BSTree_wipe_out( arg ) PRIMITIVE_CAT( arg, _bstree_wipe_out )
void BSTree_wipe_out( Prefix )( BSTree_type( Prefix ) *bstree );

/**
   BSTree_wipe_out_and_dispose
   
   Remove all items in the BSTree_t instance. Dispose of all keys and values.
   
   @param  bstree BSTree_t instance 
*/
#define BSTree_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _bstree_wipe_out_and_dispose )
void BSTree_wipe_out_and_dispose( Prefix )( BSTree_type( Prefix ) *bstree );


/** 
   Resize
*/

/**
   BSTree_balance
   
   Balance the tree  
   
   @param  bstree BSTree_t instance 
*/
#define BSTree_balance( arg ) PRIMITIVE_CAT( arg, _bstree_balance )
void BSTree_balance( Prefix )( BSTree_type( Prefix ) *bstree );


#ifdef __cplusplus
}
#endif

/* End of file */



