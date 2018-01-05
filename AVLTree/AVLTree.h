/**
 @file AVLTree.h
 @author Greg Lee
 @version 0.0
 @brief: "AVL Binary Search Trees"

 @date: "$Mon Jan 01 15:26:01 PST 2018 @18 /Internet Time/$"

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

 Function declarations for the opaque AVLTree_t type.
 
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
   DUPLICATE_FUNCTION  -  make a duplicate of a value instance  
   
*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define AVLTree_struct( arg ) PRIMITIVE_CAT( arg, _avltree_struct )
#define AVLTree_type( arg ) PRIMITIVE_CAT( arg, _avltree_t )
#define AVLTree_name( arg ) PRIMITIVE_CAT( arg, _avltree )

#define AVLTree_cursor_struct( arg ) PRIMITIVE_CAT( arg, _avltree_cursor_struct )
#define AVLTree_cursor_type( arg ) PRIMITIVE_CAT( arg, _avltree_cursor_t )
#define AVLTree_cursor_name( arg ) PRIMITIVE_CAT( arg, _avltree_cursor )

/** 
   Structure declarations
*/

struct AVLTree_struct( Prefix );
struct AVLTree_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct AVLTree_struct( Prefix ) AVLTree_type( Prefix );
typedef struct AVLTree_cursor_struct( Prefix ) AVLTree_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/** 
   Initialization
*/

/**
   AVLTree_make
   
   Return a new AVLTree_t instance with a default number of buckets.
   
   @return AVLTree_t instance 
*/
#define AVLTree_make( arg ) PRIMITIVE_CAT( arg, _avltree_make )
AVLTree_type( Prefix ) * AVLTree_make( Prefix )( void );

/**
   AVLTree_make_duplicate_from
   
   Return a new AVLTree_t instance with a duplicate items from avltree
   
   @return AVLTree_t instance 
*/

#define AVLTree_make_duplicate_from( arg ) PRIMITIVE_CAT( arg, _avltree_make_duplicate_from )
AVLTree_type( Prefix ) *
AVLTree_make_duplicate_from( Prefix )( AVLTree_type( Prefix ) *avltree );

/**
   AVLTree_make_from
   
   Return a new AVLTree_t instance that has the same content as avltree. The 
   value items in avltree are not copied.
   
   @param  avltree the AVLTree_t instance to copy from 
   @return AVLTree_t instance 
*/
#define AVLTree_make_from( arg ) PRIMITIVE_CAT( arg, _avltree_make_from )
AVLTree_type( Prefix ) * AVLTree_make_from( Prefix )( AVLTree_type( Prefix ) *avltree );

/**
   AVLTree_cursor_make
   
   Return a new AVLTree_t cursor instance.
   
   @param  the AVLTree_t instance the new cursor works on 
   @return AVLTree_cursor_t instance 
*/
#define AVLTree_cursor_make( arg ) PRIMITIVE_CAT( arg, _avltree_cursor_make )
AVLTree_cursor_type( Prefix ) * AVLTree_cursor_make( Prefix )( AVLTree_type( Prefix ) *avltree );

/**
   AVLTree_make_from_array
   
   Return a new AVLTree_t instance that has the same content as array. The 
   value items in array are not copied.
   
   @param  array the array to copy from
   @param  count the number of items to copy 
   @return AVLTree_t instance 
*/
#define AVLTree_make_from_array( arg ) PRIMITIVE_CAT( arg, _avltree_make_from_array )
AVLTree_type( Prefix ) * AVLTree_make_from_array( Prefix )( Type *array, int32_t count );


/** 
   Disposal
*/

/**
   AVLTree_dispose
   
   Frees a AVLTree_t instance without freeing its contained keys and values.
   
   @param AVLTree_t instance 
*/
#define AVLTree_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_dispose )
void AVLTree_dispose( Prefix )( AVLTree_type( Prefix ) *avltree );

/**
   AVLTree_dispose_with_contents
   
   Frees a AVLTree_t instance and its contained keys and values.
   
   @param AVLTree_t instance 
*/
#define AVLTree_dispose_with_contents( arg ) PRIMITIVE_CAT( arg, _avltree_dispose_with_contents )
void AVLTree_dispose_with_contents( Prefix )( AVLTree_type( Prefix ) *avltree );

/**
   AVLTree_cursor_dispose
   
   Frees a AVLTree_cursor_t instance. Its avltree is not disposed.
   
   @param AVLTree_cursor_t instance 
*/
#define AVLTree_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_cursor_dispose )
void AVLTree_cursor_dispose( Prefix )( AVLTree_cursor_type( Prefix ) *cursor );


/**
   AVLTree_as_array
   
   Returns the values as an array.
   
   @param  AVLTree_t instance 
   @return array of Type values
*/
#define AVLTree_as_array( arg ) PRIMITIVE_CAT( arg, _avltree_as_array )
Type *AVLTree_as_array( Prefix )( AVLTree_type( Prefix ) *avltree );

/** 
   Access
*/

/**
   AVLTree_cursor_item_at
   
   Returns the value of the item that the AVLTree_cursor_t instance is pointing to.
   
   @param  AVLTree_cursor_t instance 
   @return a Type value
*/
#define AVLTree_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _avltree_cursor_item_at )
Type AVLTree_cursor_item_at( Prefix )( AVLTree_cursor_type( Prefix ) *cursor );

/**
   AVLTree_item_at
   
   Returns the value of the item that the AVLTree_t instance's internal
   cursor is pointing to.
   
   @param  avltree AVLTree_t instance 
   @return a Type value
*/
#define AVLTree_item_at( arg ) PRIMITIVE_CAT( arg, _avltree_item_at )
Type AVLTree_item_at( Prefix )( AVLTree_type( Prefix ) *avltree );

/**
   AVLTree_item_at_index
   
   Returns the value of the item pointed to by index. First index is 0.
   
   @param  avltree AVLTree_t instance 
   @param  index desired index 
   @return a Type value
*/
#define AVLTree_item_at_index( arg ) PRIMITIVE_CAT( arg, _avltree_item_at_index )
Type AVLTree_item_at_index( Prefix )( AVLTree_type( Prefix ) *avltree, int32_t index );


/** 
   Measurement
*/

/**
   AVLTree_count
   
   Returns the number of items in the AVLTree_t instance.
   
   @param  avltree AVLTree_t instance 
   @return number of items in AVLTree instance
*/
#define AVLTree_count( arg ) PRIMITIVE_CAT( arg, _avltree_count )
int32_t AVLTree_count( Prefix )( AVLTree_type( Prefix ) *avltree );

/**
   AVLTree_height
   
   Returns the (max) height of the AVLTree_t instance.
   
   @param  avltree AVLTree_t instance 
   @return (max) height of the AVLTree instance
*/
#define AVLTree_height( arg ) PRIMITIVE_CAT( arg, _avltree_height )
int32_t AVLTree_height( Prefix )( AVLTree_type( Prefix ) *avltree );


/** 
   Status report
*/

/**
   AVLTree_off
   
   Returns 1 if the AVLTree_t instance's internal cursor is off, otherwise 0.
   
   @param  avltree AVLTree_t instance 
   @return 1 if internal cursor is off, otherwise 0
*/
#define AVLTree_off( arg ) PRIMITIVE_CAT( arg, _avltree_off )
int32_t AVLTree_off( Prefix )( AVLTree_type( Prefix ) *avltree );

/**
   AVLTree_cursor_off
   
   Returns 1 if the AVLTree_cursor_t instance is off, otherwise 0.
   
   @param  cursor AVLTree_cursor_t instance 
   @return 1 if internal cursor is off, otherwise 0
*/
#define AVLTree_cursor_off( arg ) PRIMITIVE_CAT( arg, _avltree_cursor_off )
int32_t AVLTree_cursor_off( Prefix )( AVLTree_cursor_type( Prefix ) *cursor );

/**
   AVLTree_is_empty
   
   Returns 1 if the AVLTree_t instance contains no items, otherwise 0.
   
   @param  avltree AVLTree_t instance 
   @return 1 if empty, otherwise 0
*/
#define AVLTree_is_empty( arg ) PRIMITIVE_CAT( arg, _avltree_is_empty )
int32_t AVLTree_is_empty( Prefix )( AVLTree_type( Prefix ) *avltree );

/**
   AVLTree_has
   
   Returns 1 if the AVLTree_t instance contains the key, otherwise 0.
   
   @param  avltree AVLTree_t instance 
   @param  value the value to search for 
   @return 1 if avltree has key, otherwise 0
*/
#define AVLTree_has( arg ) PRIMITIVE_CAT( arg, _avltree_has )
int32_t AVLTree_has( Prefix )( AVLTree_type( Prefix ) *avltree, Type value );


/** 
   Cursor movement
*/

/**
   AVLTree_cursor_forth
   
   Moves the AVLTree_cursor_t instance to the next item or off.
   
   @param  avltree_cursor AVLTree_cursor_t instance 
*/
#define AVLTree_cursor_forth( arg ) PRIMITIVE_CAT( arg, _avltree_cursor_forth )
void AVLTree_cursor_forth( Prefix )( AVLTree_cursor_type( Prefix ) *cursor );

/**
   AVLTree_cursor_back
   
   Moves the AVLTree_cursor_t instance to the previous item or off.
   
   @param  avltree_cursor AVLTree_cursor_t instance 
*/
#define AVLTree_cursor_back( arg ) PRIMITIVE_CAT( arg, _avltree_cursor_back )
void AVLTree_cursor_back( Prefix )( AVLTree_cursor_type( Prefix ) *cursor );

/**
   AVLTree_cursor_go
   
   Moves the AVLTree_t instance's internal cursor to the ith item in the avltree.
   
   @param  avltree_cursor AVLTree_cursor_t instance 
   @param  index the index where the cursor will be moved to 
*/
#define AVLTree_cursor_go( arg ) PRIMITIVE_CAT( arg, _avltree_cursor_go )
void AVLTree_cursor_go( Prefix )( AVLTree_cursor_type( Prefix ) *cursor, int32_t index );

/**
   AVLTree_cursor_start
   
   Moves the AVLTree_cursor_t instance to the first item or off if the avltree is empty.
   
   @param  avltree_cursor AVLTree_cursor_t instance 
*/
#define AVLTree_cursor_start( arg ) PRIMITIVE_CAT( arg, _avltree_cursor_start )
void AVLTree_cursor_start( Prefix )( AVLTree_cursor_type( Prefix ) *cursor );

/**
   AVLTree_cursor_finish
   
   Moves the AVLTree_cursor_t instance to the last item or off if the avltree is empty.
   
   @param  avltree_cursor AVLTree_cursor_t instance 
*/
#define AVLTree_cursor_finish( arg ) PRIMITIVE_CAT( arg, _avltree_cursor_finish )
void AVLTree_cursor_finish( Prefix )( AVLTree_cursor_type( Prefix ) *cursor );

/**
   AVLTree_cursor_index
   
   Returns index of the cursor - if cursor is off, returns -1
   
   @param  list AVLTree_cursor_t instance 
   @return index in list of cursor if not off, -1 otherwise
*/
#define AVLTree_cursor_index( arg ) PRIMITIVE_CAT( arg, _avltree_cursor_index )
int32_t AVLTree_cursor_index( Prefix )( AVLTree_cursor_type( Prefix ) *cursor );

/**
   AVLTree_forth
   
   Moves the AVLTree_t instance internal cursor to the next item or off.
   
   @param  avltree AVLTree_t instance 
*/
#define AVLTree_forth( arg ) PRIMITIVE_CAT( arg, _avltree_forth )
void AVLTree_forth( Prefix )( AVLTree_type( Prefix ) *avltree );

/**
   AVLTree_back
   
   Moves the AVLTree_t instance internal cursor to the previous item or off.
   
   @param  avltree AVLTree_t instance 
*/
#define AVLTree_back( arg ) PRIMITIVE_CAT( arg, _avltree_back )
void AVLTree_back( Prefix )( AVLTree_type( Prefix ) *avltree );

/**
   AVLTree_go
   
   Moves the AVLTree_t instance's internal cursor to the ith item in the avltree.
   
   @param  avltree AVLTree_t instance 
   @param  index the index where the  will be moved to 
*/
#define AVLTree_go( arg ) PRIMITIVE_CAT( arg, _avltree_go )
void AVLTree_go( Prefix )( AVLTree_type( Prefix ) *avltree, int32_t index );

/**
   AVLTree_start
   
   Moves the AVLTree_t instance's internal cursor to the first item or off if the avltree is empty.
   
   @param  avltree AVLTree_t instance 
*/
#define AVLTree_start( arg ) PRIMITIVE_CAT( arg, _avltree_start )
void AVLTree_start( Prefix )( AVLTree_type( Prefix ) *avltree );

/**
   AVLTree_finish
   
   Moves the AVLTree_t instance's internal cursor to the last item or off if the avltree is empty.
   
   @param  avltree AVLTree_t instance 
*/
#define AVLTree_finish( arg ) PRIMITIVE_CAT( arg, _avltree_finish )
void AVLTree_finish( Prefix )( AVLTree_type( Prefix ) *avltree );

/**
   AVLTree_index
   
   Returns index of the internal cursor - if internal cursor is off, returns -1
   
   @param  list AVLTree_t instance 
   @return index in list of internal cursor if not off, -1 otherwise
*/
#define AVLTree_index( arg ) PRIMITIVE_CAT( arg, _avltree_index )
int32_t AVLTree_index( Prefix )( AVLTree_type( Prefix ) *list );



/** 
   Element change
*/

/**
   AVLTree_put
   
   Put the key-value pair into the AVLTree_t instance. Replace any existing item
   that has the same key.
   
   @param  avltree AVLTree_t instance 
   @param  value the value to insert 
*/
#define AVLTree_put( arg ) PRIMITIVE_CAT( arg, _avltree_put )
void AVLTree_put( Prefix )( AVLTree_type( Prefix ) *avltree, Type value );


/** 
   Removal
*/

/**
   AVLTree_remove
   
   Remove the item in the AVLTree_t instance that has the key.
   
   @param  avltree AVLTree_t instance 
   @param  key the key for the value 
*/
#define AVLTree_remove( arg ) PRIMITIVE_CAT( arg, _avltree_remove )
void AVLTree_remove( Prefix )( AVLTree_type( Prefix ) *avltree, Type value );

/**
   AVLTree_remove_and_dispose
   
   Remove the item in the AVLTree_t instance that has the key and dispose
   of the key and the value.
   
   @param  avltree AVLTree_t instance 
   @param  key the key for the value 
*/
#define AVLTree_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_remove_and_dispose )
void AVLTree_remove_and_dispose( Prefix )( AVLTree_type( Prefix ) *avltree, Type value );

/**
   AVLTree_wipe_out
   
   Remove all items in the AVLTree_t instance.
   
   @param  avltree AVLTree_t instance 
*/
#define AVLTree_wipe_out( arg ) PRIMITIVE_CAT( arg, _avltree_wipe_out )
void AVLTree_wipe_out( Prefix )( AVLTree_type( Prefix ) *avltree );

/**
   AVLTree_wipe_out_and_dispose
   
   Remove all items in the AVLTree_t instance. Dispose of all keys and values.
   
   @param  avltree AVLTree_t instance 
*/
#define AVLTree_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _avltree_wipe_out_and_dispose )
void AVLTree_wipe_out_and_dispose( Prefix )( AVLTree_type( Prefix ) *avltree );


#ifdef __cplusplus
}
#endif

/* End of file */



