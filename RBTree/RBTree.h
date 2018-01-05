/**
 @file RBTree.h
 @author Greg Lee
 @version 1.0.0
 @brief: "Red Black Binary Search Trees"
 
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

 Function declarations for the opaque RBTree_t type.
 
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
   
   EQUALITY_FUNCTION -  compares two instances for equality
   ORDER_FUNCTION    -  returns 1 if first argument is "before" second argument
   DISPOSE_FUNCTION  -  frees a value instance  
   
*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define RBTree_struct( arg ) PRIMITIVE_CAT( arg, _rbtree_struct )
#define RBTree_type( arg ) PRIMITIVE_CAT( arg, _rbtree_t )
#define RBTree_name( arg ) PRIMITIVE_CAT( arg, _rbtree )

#define RBTree_cursor_struct( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_struct )
#define RBTree_cursor_type( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_t )
#define RBTree_cursor_name( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor )

/** 
   Structure declarations
*/

struct RBTree_struct( Prefix );
struct RBTree_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct RBTree_struct( Prefix ) RBTree_type( Prefix );
typedef struct RBTree_cursor_struct( Prefix ) RBTree_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/** 
   Initialization
*/

/**
   RBTree_make
   
   Return a new RBTree_t instance with a default number of buckets.
   
   @return RBTree_t instance 
*/
#define RBTree_make( arg ) PRIMITIVE_CAT( arg, _rbtree_make )
RBTree_type( Prefix ) * RBTree_make( Prefix )( void );

/**
   RBTree_make_duplicate_from
   
   Return a new RBTree_t instance with a duplicate items from rbtree
   
   @return RBTree_t instance 
*/

#define RBTree_make_duplicate_from( arg ) PRIMITIVE_CAT( arg, _rbtree_make_duplicate_from )
RBTree_type( Prefix ) *
RBTree_make_duplicate_from( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_make_from
   
   Return a new RBTree_t instance that has the same content as rbtree. The key
   and value items in rbtree are not copied.
   
   @param  rbtree the RBTree_t instance to copy from 
   @return RBTree_t instance 
*/
#define RBTree_make_from( arg ) PRIMITIVE_CAT( arg, _rbtree_make_from )
RBTree_type( Prefix ) * RBTree_make_from( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_make_from_array
   
   Return a new RBTree_t instance that has the same content as array. The key
   and value items in rbtree are not copied.
   
   @param  rbtree the RBTree_t instance to copy from 
   @return RBTree_t instance 
*/
#define RBTree_make_from_array( arg ) PRIMITIVE_CAT( arg, _rbtree_make_from_array )
RBTree_type( Prefix ) * RBTree_make_from_array( Prefix )( Type *array, int32_t count );

/**
   RBTree_cursor_make
   
   Return a new RBTree_t cursor instance.
   
   @param  the RBTree_t instance the new cursor works on 
   @return RBTree_cursor_t instance 
*/
#define RBTree_cursor_make( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_make )
RBTree_cursor_type( Prefix ) * RBTree_cursor_make( Prefix )( RBTree_type( Prefix ) *rbtree );


/** 
   Disposal
*/

/**
   RBTree_dispose
   
   Frees a RBTree_t instance without freeing its contained keys and values.
   
   @param RBTree_t instance 
*/
#define RBTree_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_dispose )
void RBTree_dispose( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_dispose_with_contents
   
   Frees a RBTree_t instance and its contained keys and values.
   
   @param RBTree_t instance 
*/
#define RBTree_dispose_with_contents( arg ) PRIMITIVE_CAT( arg, _rbtree_dispose_with_contents )
void RBTree_dispose_with_contents( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_cursor_dispose
   
   Frees a RBTree_cursor_t instance. Its rbtree is not disposed.
   
   @param RBTree_cursor_t instance 
*/
#define RBTree_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_dispose )
void RBTree_cursor_dispose( Prefix )( RBTree_cursor_type( Prefix ) *cursor );


/**
   RBTree_as_array
   
   Returns the values as an array.
   
   @param  RBTree_t instance 
   @return array of Type values
*/
#define RBTree_as_array( arg ) PRIMITIVE_CAT( arg, _rbtree_as_array )
Type *RBTree_as_array( Prefix )( RBTree_type( Prefix ) *rbtree );

/** 
   Access
*/

/**
   RBTree_cursor_item_at
   
   Returns the value of the item that the RBTree_cursor_t instance is pointing to.
   
   @param  RBTree_cursor_t instance 
   @return a Type value
*/
#define RBTree_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_item_at )
Type RBTree_cursor_item_at( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_item_at
   
   Returns the value of the item that the RBTree_t instance's internal
   cursor is pointing to.
   
   @param  rbtree RBTree_t instance 
   @return a Type value
*/
#define RBTree_item_at( arg ) PRIMITIVE_CAT( arg, _rbtree_item_at )
Type RBTree_item_at( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_item_at_index
   
   Returns the value of the item pointed to by index. First index is 0.
   
   @param  rbtree RBTree_t instance 
   @param  index desired index 
   @return a Type value
*/
#define RBTree_item_at_index( arg ) PRIMITIVE_CAT( arg, _rbtree_item_at_index )
Type RBTree_item_at_index( Prefix )( RBTree_type( Prefix ) *rbtree, int32_t index );


/** 
   Measurement
*/

/**
   RBTree_count
   
   Returns the number of items in the RBTree_t instance.
   
   @param  rbtree RBTree_t instance 
   @return number of items in RBTree instance
*/
#define RBTree_count( arg ) PRIMITIVE_CAT( arg, _rbtree_count )
int32_t RBTree_count( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_height
   
   Returns the (max) height of the RBTree_t instance.
   
   @param  rbtree RBTree_t instance 
   @return (max) height of the RBTree instance
*/
#define RBTree_height( arg ) PRIMITIVE_CAT( arg, _rbtree_height )
int32_t RBTree_height( Prefix )( RBTree_type( Prefix ) *rbtree );


/** 
   Status report
*/

/**
   RBTree_off
   
   Returns 1 if the RBTree_t instance's internal cursor is off, otherwise 0.
   
   @param  rbtree RBTree_t instance 
   @return 1 if internal cursor is off, otherwise 0
*/
#define RBTree_off( arg ) PRIMITIVE_CAT( arg, _rbtree_off )
int32_t RBTree_off( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_cursor_off
   
   Returns 1 if the RBTree_cursor_t instance is off, otherwise 0.
   
   @param  cursor RBTree_cursor_t instance 
   @return 1 if internal cursor is off, otherwise 0
*/
#define RBTree_cursor_off( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_off )
int32_t RBTree_cursor_off( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_is_empty
   
   Returns 1 if the RBTree_t instance contains no items, otherwise 0.
   
   @param  rbtree RBTree_t instance 
   @return 1 if empty, otherwise 0
*/
#define RBTree_is_empty( arg ) PRIMITIVE_CAT( arg, _rbtree_is_empty )
int32_t RBTree_is_empty( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_has
   
   Returns 1 if the RBTree_t instance contains the key, otherwise 0.
   
   @param  rbtree RBTree_t instance 
   @param  value the value to search for 
   @return 1 if rbtree has key, otherwise 0
*/
#define RBTree_has( arg ) PRIMITIVE_CAT( arg, _rbtree_has )
int32_t RBTree_has( Prefix )( RBTree_type( Prefix ) *rbtree, Type value );


/** 
   Cursor movement
*/

/**
   RBTree_cursor_forth
   
   Moves the RBTree_cursor_t instance to the next item or off.
   
   @param  rbtree_cursor RBTree_cursor_t instance 
*/
#define RBTree_cursor_forth( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_forth )
void RBTree_cursor_forth( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_cursor_back
   
   Moves the RBTree_cursor_t instance to the previous item or off.
   
   @param  rbtree_cursor RBTree_cursor_t instance 
*/
#define RBTree_cursor_back( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_back )
void RBTree_cursor_back( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_cursor_go
   
   Moves the RBTree_t instance's internal cursor to the ith item in the rbtree.
   
   @param  rbtree_cursor RBTree_cursor_t instance 
   @param  index the index where the cursor will be moved to 
*/
#define RBTree_cursor_go( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_go )
void RBTree_cursor_go( Prefix )( RBTree_cursor_type( Prefix ) *cursor, int32_t index );

/**
   RBTree_cursor_start
   
   Moves the RBTree_cursor_t instance to the first item or off if the rbtree is empty.
   
   @param  rbtree_cursor RBTree_cursor_t instance 
*/
#define RBTree_cursor_start( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_start )
void RBTree_cursor_start( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_cursor_finish
   
   Moves the RBTree_cursor_t instance to the last item or off if the rbtree is empty.
   
   @param  rbtree_cursor RBTree_cursor_t instance 
*/
#define RBTree_cursor_finish( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_finish )
void RBTree_cursor_finish( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_cursor_index
   
   Returns index of the cursor - if cursor is off, returns -1
   
   @param  list RBTree_cursor_t instance 
   @return index in list of cursor if not off, -1 otherwise
*/
#define RBTree_cursor_index( arg ) PRIMITIVE_CAT( arg, _rbtree_cursor_index )
int32_t RBTree_cursor_index( Prefix )( RBTree_cursor_type( Prefix ) *cursor );

/**
   RBTree_forth
   
   Moves the RBTree_t instance internal cursor to the next item or off.
   
   @param  rbtree RBTree_t instance 
*/
#define RBTree_forth( arg ) PRIMITIVE_CAT( arg, _rbtree_forth )
void RBTree_forth( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_back
   
   Moves the RBTree_t instance internal cursor to the previous item or off.
   
   @param  rbtree RBTree_t instance 
*/
#define RBTree_back( arg ) PRIMITIVE_CAT( arg, _rbtree_back )
void RBTree_back( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_go
   
   Moves the RBTree_t instance's internal cursor to the ith item in the rbtree.
   
   @param  rbtree RBTree_t instance 
   @param  index the index where the  will be moved to 
*/
#define RBTree_go( arg ) PRIMITIVE_CAT( arg, _rbtree_go )
void RBTree_go( Prefix )( RBTree_type( Prefix ) *rbtree, int32_t index );

/**
   RBTree_start
   
   Moves the RBTree_t instance's internal cursor to the first item or off if the rbtree is empty.
   
   @param  rbtree RBTree_t instance 
*/
#define RBTree_start( arg ) PRIMITIVE_CAT( arg, _rbtree_start )
void RBTree_start( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_finish
   
   Moves the RBTree_t instance's internal cursor to the last item or off if the rbtree is empty.
   
   @param  rbtree RBTree_t instance 
*/
#define RBTree_finish( arg ) PRIMITIVE_CAT( arg, _rbtree_finish )
void RBTree_finish( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_index
   
   Returns index of the internal cursor - if internal cursor is off, returns -1
   
   @param  list RBTree_t instance 
   @return index in list of internal cursor if not off, -1 otherwise
*/
#define RBTree_index( arg ) PRIMITIVE_CAT( arg, _rbtree_index )
int32_t RBTree_index( Prefix )( RBTree_type( Prefix ) *list );



/** 
   Element change
*/

/**
   RBTree_put
   
   Put the key-value pair into the RBTree_t instance. Replace any existing item
   that has the same key.
   
   @param  rbtree RBTree_t instance 
   @param  value the value to insert 
*/
#define RBTree_put( arg ) PRIMITIVE_CAT( arg, _rbtree_put )
void RBTree_put( Prefix )( RBTree_type( Prefix ) *rbtree, Type value );


/** 
   Removal
*/

/**
   RBTree_remove
   
   Remove the item in the RBTree_t instance that has the key.
   
   @param  rbtree RBTree_t instance 
   @param  key the key for the value 
*/
#define RBTree_remove( arg ) PRIMITIVE_CAT( arg, _rbtree_remove )
void RBTree_remove( Prefix )( RBTree_type( Prefix ) *rbtree, Type value );

/**
   RBTree_remove_and_dispose
   
   Remove the item in the RBTree_t instance that has the key and dispose
   of the key and the value.
   
   @param  rbtree RBTree_t instance 
   @param  key the key for the value 
*/
#define RBTree_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_remove_and_dispose )
void RBTree_remove_and_dispose( Prefix )( RBTree_type( Prefix ) *rbtree, Type value );

/**
   RBTree_wipe_out
   
   Remove all items in the RBTree_t instance.
   
   @param  rbtree RBTree_t instance 
*/
#define RBTree_wipe_out( arg ) PRIMITIVE_CAT( arg, _rbtree_wipe_out )
void RBTree_wipe_out( Prefix )( RBTree_type( Prefix ) *rbtree );

/**
   RBTree_wipe_out_and_dispose
   
   Remove all items in the RBTree_t instance. Dispose of all keys and values.
   
   @param  rbtree RBTree_t instance 
*/
#define RBTree_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _rbtree_wipe_out_and_dispose )
void RBTree_wipe_out_and_dispose( Prefix )( RBTree_type( Prefix ) *rbtree );


/** 
   Resize
*/

/**
   RBTree_as_string
   
   Convert the tree to a string representation  
   
   @param  rbtree RBTree_t instance 
   @param  astr array of strings 
   @param  width number of characters for each value as a string 
   @param  func function to put string representation of value into string 
*/

#define RBTree_as_string( arg ) PRIMITIVE_CAT( arg, _rbtree_as_string )
void RBTree_as_string( Prefix )
(
   RBTree_type( Prefix ) *rbtree,
   char_t **astr,
   int32_t width,
   void (func)( char_t *, Type value )
);


#ifdef __cplusplus
}
#endif

/* End of file */



