/**
 @file RBTree_kv.h
 @author Greg Lee
 @version 1.0.0
 @brief: "Red Black Binary Search Trees of keys with values"
 
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

 Function declarations for the opaque RBTree_kv_t type.
 
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
   
   KEY_EQUALITY_FUNCTION   -  compares two key instances for equality
   KEY_ORDER_FUNCTION      -  returns 1 if first key argument is "before" second argument
   KEY_DISPOSE_FUNCTION    -  frees a key instance  
   VALUE_DISPOSE_FUNCTION  -  frees a value instance  
   
*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define RBTree_kv_struct( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_struct )
#define RBTree_kv_type( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_t )
#define RBTree_kv_name( arg ) PRIMITIVE_CAT( arg, _rbtree_kv )

#define RBTree_kv_cursor_struct( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_struct )
#define RBTree_kv_cursor_type( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_t )
#define RBTree_kv_cursor_name( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor )

/** 
   Structure declarations
*/

struct RBTree_kv_struct( Prefix );
struct RBTree_kv_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct RBTree_kv_struct( Prefix ) RBTree_kv_type( Prefix );
typedef struct RBTree_kv_cursor_struct( Prefix ) RBTree_kv_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/** 
   Initialization
*/

/**
   RBTree_kv_make
   
   Return a new RBTree_kv_t instance with a default number of buckets.
   
   @return RBTree_kv_t instance 
*/
#define RBTree_kv_make( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_make )
RBTree_kv_type( Prefix ) * RBTree_kv_make( Prefix )( void );

/**
   RBTree_kv_make_duplicate_from
   
   Return a new RBTree_kv_t instance with a duplicate items from rbtree
   
   @return RBTree_kv_t instance 
*/

#define RBTree_kv_make_duplicate_from( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_make_duplicate_from )
RBTree_kv_type( Prefix ) *
RBTree_kv_make_duplicate_from( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_make_from
   
   Return a new RBTree_kv_t instance that has the same content as rbtree. The key
   and value items in rbtree are not copied.
   
   @param  rbtree the RBTree_kv_t instance to copy from 
   @return RBTree_kv_t instance 
*/
#define RBTree_kv_make_from( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_make_from )
RBTree_kv_type( Prefix ) * RBTree_kv_make_from( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_make_from_array
   
   Return a new RBTree_kv_t instance that has the same content as array. The key
   and value items in array are not copied.
   
   @param  key_array key array to copy from 
   @param  value_array value array to copy from
   @param  count the number of items to copy
   @return RBTree_kv_t instance 
*/
#define RBTree_kv_make_from_array( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_make_from_array )
RBTree_kv_type( Prefix ) * RBTree_kv_make_from_array( Prefix )( Key *key_array, Type *value_array, int32_t count );

/**
   RBTree_kv_cursor_make
   
   Return a new RBTree_kv_t cursor instance.
   
   @param  the RBTree_kv_t instance the new cursor works on 
   @return RBTree_kv_cursor_t instance 
*/
#define RBTree_kv_cursor_make( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_make )
RBTree_kv_cursor_type( Prefix ) * RBTree_kv_cursor_make( Prefix )( RBTree_kv_type( Prefix ) *rbtree );


/** 
   Disposal
*/

/**
   RBTree_kv_dispose
   
   Frees a RBTree_kv_t instance without freeing its contained keys and values.
   
   @param RBTree_kv_t instance 
*/
#define RBTree_kv_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_dispose )
void RBTree_kv_dispose( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_dispose_with_contents
   
   Frees a RBTree_kv_t instance and its contained keys and values.
   
   @param RBTree_kv_t instance 
*/
#define RBTree_kv_dispose_with_contents( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_dispose_with_contents )
void RBTree_kv_dispose_with_contents( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_cursor_dispose
   
   Frees a RBTree_kv_cursor_t instance. Its rbtree is not disposed.
   
   @param RBTree_kv_cursor_t instance 
*/
#define RBTree_kv_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_dispose )
void RBTree_kv_cursor_dispose( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );


/**
   RBTree_kv_keys_as_array
   
   Returns the values as an array.
   
   @param  RBTree_kv_t instance 
   @return array of Key values
*/
#define RBTree_kv_keys_as_array( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_keys_as_array )
Key *RBTree_kv_keys_as_array( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_values_as_array
   
   Returns the values as an array.
   
   @param  RBTree_kv_t instance 
   @return array of Type values
*/
#define RBTree_kv_values_as_array( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_values_as_array )
Type *RBTree_kv_values_as_array( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/** 
   Access
*/

/**
   RBTree_kv_cursor_key_at
   
   Returns the key of the item that the RBTree_kv_cursor_t instance is pointing to.
   
   @param  RBTree_kv_cursor_t instance 
   @return a Key value
*/
#define RBTree_kv_cursor_key_at( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_key_at )
Key RBTree_kv_cursor_key_at( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_item_at
   
   Returns the value of the item that the RBTree_kv_cursor_t instance is pointing to.
   
   @param  RBTree_kv_cursor_t instance 
   @return a Type value
*/
#define RBTree_kv_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_item_at )
Type RBTree_kv_cursor_item_at( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_key_at
   
   Returns the key of the item that the RBTree_kv_t instance's internal
   cursor is pointing to.
   
   @param  rbtree RBTree_kv_t instance 
   @return a Key value
*/
#define RBTree_kv_key_at( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_key_at )
Key RBTree_kv_key_at( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_item_at
   
   Returns the value of the item that the RBTree_kv_t instance's internal
   cursor is pointing to.
   
   @param  rbtree RBTree_kv_t instance 
   @return a Type value
*/
#define RBTree_kv_item_at( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_item_at )
Type RBTree_kv_item_at( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_key_at_index
   
   Returns the key of the item pointed to by index. First index is 0.
   
   @param  rbtree RBTree_kv_t instance 
   @param  index desired index 
   @return a Key value
*/
#define RBTree_kv_key_at_index( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_key_at_index )
Key RBTree_kv_key_at_index( Prefix )( RBTree_kv_type( Prefix ) *rbtree, int32_t index );

/**
   RBTree_kv_item_at_index
   
   Returns the value of the item pointed to by index. First index is 0.
   
   @param  rbtree RBTree_kv_t instance 
   @param  index desired index 
   @return a Type value
*/
#define RBTree_kv_item_at_index( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_item_at_index )
Type RBTree_kv_item_at_index( Prefix )( RBTree_kv_type( Prefix ) *rbtree, int32_t index );


/** 
   Measurement
*/

/**
   RBTree_kv_count
   
   Returns the number of items in the RBTree_kv_t instance.
   
   @param  rbtree RBTree_kv_t instance 
   @return number of items in RBTree instance
*/
#define RBTree_kv_count( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_count )
int32_t RBTree_kv_count( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_height
   
   Returns the (max) height of the RBTree_kv_t instance.
   
   @param  rbtree RBTree_kv_t instance 
   @return (max) height of the RBTree instance
*/
#define RBTree_kv_height( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_height )
int32_t RBTree_kv_height( Prefix )( RBTree_kv_type( Prefix ) *rbtree );


/** 
   Status report
*/

/**
   RBTree_kv_off
   
   Returns 1 if the RBTree_kv_t instance's internal cursor is off, otherwise 0.
   
   @param  rbtree RBTree_kv_t instance 
   @return 1 if internal cursor is off, otherwise 0
*/
#define RBTree_kv_off( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_off )
int32_t RBTree_kv_off( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_cursor_off
   
   Returns 1 if the RBTree_kv_cursor_t instance is off, otherwise 0.
   
   @param  cursor RBTree_kv_cursor_t instance 
   @return 1 if internal cursor is off, otherwise 0
*/
#define RBTree_kv_cursor_off( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_off )
int32_t RBTree_kv_cursor_off( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_is_empty
   
   Returns 1 if the RBTree_kv_t instance contains no items, otherwise 0.
   
   @param  rbtree RBTree_kv_t instance 
   @return 1 if empty, otherwise 0
*/
#define RBTree_kv_is_empty( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_is_empty )
int32_t RBTree_kv_is_empty( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_has
   
   Returns 1 if the RBTree_kv_t instance contains the key, otherwise 0.
   
   @param  rbtree RBTree_kv_t instance 
   @param  key the value to search for 
   @return 1 if rbtree has key, otherwise 0
*/
#define RBTree_kv_has( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_has )
int32_t RBTree_kv_has( Prefix )( RBTree_kv_type( Prefix ) *rbtree, Key key );


/** 
   Cursor movement
*/

/**
   RBTree_kv_cursor_forth
   
   Moves the RBTree_kv_cursor_t instance to the next item or off.
   
   @param  rbtree_kv_cursor RBTree_kv_cursor_t instance 
*/
#define RBTree_kv_cursor_forth( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_forth )
void RBTree_kv_cursor_forth( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_back
   
   Moves the RBTree_kv_cursor_t instance to the previous item or off.
   
   @param  rbtree_kv_cursor RBTree_kv_cursor_t instance 
*/
#define RBTree_kv_cursor_back( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_back )
void RBTree_kv_cursor_back( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_go
   
   Moves the RBTree_kv_t instance's internal cursor to the ith item in the rbtree.
   
   @param  rbtree_kv_cursor RBTree_kv_cursor_t instance 
   @param  index the index where the cursor will be moved to 
*/
#define RBTree_kv_cursor_go( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_go )
void RBTree_kv_cursor_go( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor, int32_t index );

/**
   RBTree_kv_cursor_start
   
   Moves the RBTree_kv_cursor_t instance to the first item or off if the rbtree is empty.
   
   @param  rbtree_kv_cursor RBTree_kv_cursor_t instance 
*/
#define RBTree_kv_cursor_start( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_start )
void RBTree_kv_cursor_start( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_finish
   
   Moves the RBTree_kv_cursor_t instance to the last item or off if the rbtree is empty.
   
   @param  rbtree_kv_cursor RBTree_kv_cursor_t instance 
*/
#define RBTree_kv_cursor_finish( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_finish )
void RBTree_kv_cursor_finish( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_cursor_index
   
   Returns index of the cursor - if cursor is off, returns -1
   
   @param  list RBTree_kv_cursor_t instance 
   @return index in list of cursor if not off, -1 otherwise
*/
#define RBTree_kv_cursor_index( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_cursor_index )
int32_t RBTree_kv_cursor_index( Prefix )( RBTree_kv_cursor_type( Prefix ) *cursor );

/**
   RBTree_kv_forth
   
   Moves the RBTree_kv_t instance internal cursor to the next item or off.
   
   @param  rbtree RBTree_kv_t instance 
*/
#define RBTree_kv_forth( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_forth )
void RBTree_kv_forth( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_back
   
   Moves the RBTree_kv_t instance internal cursor to the previous item or off.
   
   @param  rbtree RBTree_kv_t instance 
*/
#define RBTree_kv_back( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_back )
void RBTree_kv_back( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_go
   
   Moves the RBTree_kv_t instance's internal cursor to the ith item in the rbtree.
   
   @param  rbtree RBTree_kv_t instance 
   @param  index the index where the  will be moved to 
*/
#define RBTree_kv_go( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_go )
void RBTree_kv_go( Prefix )( RBTree_kv_type( Prefix ) *rbtree, int32_t index );

/**
   RBTree_kv_start
   
   Moves the RBTree_kv_t instance's internal cursor to the first item or off if the rbtree is empty.
   
   @param  rbtree RBTree_kv_t instance 
*/
#define RBTree_kv_start( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_start )
void RBTree_kv_start( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_finish
   
   Moves the RBTree_kv_t instance's internal cursor to the first item or off if the rbtree is empty.
   
   @param  rbtree RBTree_kv_t instance 
*/
#define RBTree_kv_finish( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_finish )
void RBTree_kv_finish( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_index
   
   Returns index of the internal cursor - if internal cursor is off, returns -1
   
   @param  list RBTree_kv_t instance 
   @return index in list of internal cursor if not off, -1 otherwise
*/
#define RBTree_kv_index( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_index )
int32_t RBTree_kv_index( Prefix )( RBTree_kv_type( Prefix ) *list );



/** 
   Element change
*/

/**
   RBTree_kv_put
   
   Put the key-value pair into the RBTree_kv_t instance. Replace any existing item
   that has the same key.
   
   @param  rbtree RBTree_kv_t instance 
   @param  value the value to insert 
*/
#define RBTree_kv_put( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_put )
void RBTree_kv_put( Prefix )( RBTree_kv_type( Prefix ) *rbtree, Type value, Key key );


/** 
   Removal
*/

/**
   RBTree_kv_remove
   
   Remove the item in the RBTree_kv_t instance that has the key.
   
   @param  rbtree RBTree_kv_t instance 
   @param  key the key for the value 
*/
#define RBTree_kv_remove( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_remove )
void RBTree_kv_remove( Prefix )( RBTree_kv_type( Prefix ) *rbtree, Key key );

/**
   RBTree_kv_remove_and_dispose
   
   Remove the item in the RBTree_kv_t instance that has the key and dispose
   of the key and the value.
   
   @param  rbtree RBTree_kv_t instance 
   @param  key the key for the value 
*/
#define RBTree_kv_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_remove_and_dispose )
void RBTree_kv_remove_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *rbtree, Key key );

/**
   RBTree_kv_wipe_out
   
   Remove all items in the RBTree_kv_t instance.
   
   @param  rbtree RBTree_kv_t instance 
*/
#define RBTree_kv_wipe_out( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_wipe_out )
void RBTree_kv_wipe_out( Prefix )( RBTree_kv_type( Prefix ) *rbtree );

/**
   RBTree_kv_wipe_out_and_dispose
   
   Remove all items in the RBTree_kv_t instance. Dispose of all keys and values.
   
   @param  rbtree RBTree_kv_t instance 
*/
#define RBTree_kv_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_wipe_out_and_dispose )
void RBTree_kv_wipe_out_and_dispose( Prefix )( RBTree_kv_type( Prefix ) *rbtree );


/** 
   Miscellaneous
*/

/**
   RBTree_as_string
   
   Put a representation of the tree into an array of strings
   
   @param  rbtree RBTree_kv_t instance
   @param astr array of strings to put the representation into
   @param width the number of characters to place a node's data into
   @param func a function to put node's data into a character string
*/
#define RBTree_kv_as_string( arg ) PRIMITIVE_CAT( arg, _rbtree_kv_as_string )
void RBTree_kv_as_string( Prefix )
( 
   RBTree_kv_type( Prefix ) *rbtree, 
   char_t **astr,
   int32_t width,
   void (func)( char_t *, Key key, Type value )
);


#ifdef __cplusplus
}
#endif

/* End of file */



