/**
 @file HTable.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Hash Tables"

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

 Function declarations for the opaque HTable_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
   Version
*/

#define HTABLE_VERSION_MAJOR 2
#define HTABLE_VERSION_MINOR 0
#define HTABLE_VERSION_PATCH 0

#define HTABLE_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define HTABLE_VERSION \
   HTABLE_MAKE_VERSION( HTABLE_VERSION_MAJOR, \
                       HTABLE_VERSION_MINOR, \
                       HTABLE_VERSION_PATCH )

/**
   Includes
*/

#include "base.h"

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix - string used to name this container type
   Key    - the type of the key
   Type   - the type of the value

   Macros that must be present (external to this file):

   HASH_FUNCTION           -  takes a key instance as an argument and returns an
                              integer hash code
   EQUALITY_FUNCTION       -  compares two key instances for equality
   KEY_DISPOSE_FUNCTION    -  frees a key instance
   VALUE_DISPOSE_FUNCTION  -  frees a value instance

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define HTable_struct( arg ) PRIMITIVE_CAT( arg, _htable_struct )
#define HTable_type( arg ) PRIMITIVE_CAT( arg, _htable_t )
#define HTable_name( arg ) PRIMITIVE_CAT( arg, _htable )

#define HTable_cursor_struct( arg ) PRIMITIVE_CAT( arg, _htable_cursor_struct )
#define HTable_cursor_type( arg ) PRIMITIVE_CAT( arg, _htable_cursor_t )
#define HTable_cursor_name( arg ) PRIMITIVE_CAT( arg, _htable_cursor )

/**
   Structure declarations
*/

struct HTable_struct( Prefix );
struct HTable_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct HTable_struct( Prefix ) HTable_type( Prefix );
typedef struct HTable_cursor_struct( Prefix ) HTable_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/*
   Initialization
*/

/**
   HTable_make

   Return a new HTable_t instance with a default number of buckets.

   @return HTable_t instance
*/
#define HTable_make( arg ) PRIMITIVE_CAT( arg, _htable_make )
HTable_type( Prefix ) * HTable_make( Prefix )( void );

/**
   HTable_make_n

   Return a new HTable_t instance with bucket_count buckets.

   @param  bucket_count the number or buckets to initialize the hash table with
   @return HTable_t instance
*/
#define HTable_make_n( arg ) PRIMITIVE_CAT( arg, _htable_make_n )
HTable_type( Prefix ) * HTable_make_n( Prefix )( int32_t bucket_count );

/**
   HTable_make_from_array

   Return a new HTable_t instance that has the same content as array. The key
   and value items inarray are not copied.

   @param  array the array to copy from
   @param  count the number of items to copy
   @return HTable_t instance
*/
#define HTable_make_from_array( arg ) PRIMITIVE_CAT( arg, _htable_make_from_array )
HTable_type( Prefix ) * HTable_make_from_array( Prefix )( Key *key_array, Type *value_array, int32_t count );

/**
   HTable_cursor_make

   Return a new HTable_t cursor instance.

   @param  current the HTable_t instance the new cursor works on
   @return HTable_cursor_t instance
*/
#define HTable_cursor_make( arg ) PRIMITIVE_CAT( arg, _htable_cursor_make )
HTable_cursor_type( Prefix ) * HTable_cursor_make( Prefix )( HTable_type( Prefix ) *current );


/*
   Basic
*/

/**
   HTable_clone

   Return a new HTable_t instance that has the same content as htable. The key
   and value items in htable are not copied.

   @param  current the HTable_t instance to copy from
   @return HTable_t instance
*/
#define HTable_clone( arg ) PRIMITIVE_CAT( arg, _htable_clone )
HTable_type( Prefix ) * HTable_clone( Prefix )( HTable_type( Prefix ) *current );

/**
   HTable_deep_clone

   Return a new HTable_t instance that has the same content as htable. The key
   and value items in htable are not copied.

   @param  current the HTable_t instance to copy from
   @return HTable_t instance
*/
#define HTable_deep_clone( arg ) PRIMITIVE_CAT( arg, _htable_deep_clone )
HTable_type( Prefix ) * HTable_deep_clone( Prefix )( HTable_type( Prefix ) *current );

/**
   HTable_is_equal

   Return 1 if current has the same (shallow) content as other.

   @param  current the HTable_t instance to compare to
   @param  other the HTable_t instance to compare from
   @return 1 if true, 0 otherwise
*/
#define HTable_is_equal( arg ) PRIMITIVE_CAT( arg, _htable_is_equal )
int32_t HTable_is_equal( Prefix )( HTable_type( Prefix ) *current, HTable_type( Prefix ) *other );

/**
   HTable_is_deep_equal

   Return 1 if current has the same (deep) content as other.

   @param  current the HTable_t instance to compare to
   @param  other the HTable_t instance to compare from
   @return 1 if true, 0 otherwise
*/
#define HTable_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _htable_is_deep_equal )
int32_t HTable_is_deep_equal( Prefix )( HTable_type( Prefix ) *current, HTable_type( Prefix ) *other );

/**
   HTable_copy

   Copy (shallow) other into current.

   @param  current the HTable_t instance to compare to
   @param  other the HTable_t instance to compare from
   @return 1 if true, 0 otherwise
*/
#define HTable_copy( arg ) PRIMITIVE_CAT( arg, _htable_copy )
void HTable_copy( Prefix )( HTable_type( Prefix ) *current, HTable_type( Prefix ) *other );

/**
   HTable_deep_copy

   Copy (deep) other into current.

   @param  current the HTable_t instance to compare to
   @param  other the HTable_t instance to compare from
   @return 1 if true, 0 otherwise
*/
#define HTable_deep_copy( arg ) PRIMITIVE_CAT( arg, _htable_deep_copy )
void HTable_deep_copy( Prefix )( HTable_type( Prefix ) *current, HTable_type( Prefix ) *other );

/*
   Disposal
*/

/**
   HTable_dispose

   Frees a HTable_t instance without freeing its contained keys and values.

   @param current pointer to HTable_t instance
*/
#define HTable_dispose( arg ) PRIMITIVE_CAT( arg, _htable_dispose )
void HTable_dispose( Prefix )( HTable_type( Prefix ) **current );

/**
   HTable_deep_dispose

   Frees a HTable_t instance and its contained keys and values.

   @param current pointer to HTable_t instance
*/
#define HTable_deep_dispose( arg ) PRIMITIVE_CAT( arg, _htable_deep_dispose )
void HTable_deep_dispose( Prefix )( HTable_type( Prefix ) **current );

/**
   HTable_cursor_dispose

   Frees a HTable_cursor_t instance. Its htable is not disposed.

   @param pointer to HTable_cursor_t instance
*/
#define HTable_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _htable_cursor_dispose )
void HTable_cursor_dispose( Prefix )( HTable_cursor_type( Prefix ) **cursor );


/**
   HTable_keys_as_array

   Returns the keys as an array.

   @param  current HTable_t instance
   @return array of Key values
*/
#define HTable_keys_as_array( arg ) PRIMITIVE_CAT( arg, _htable_keys_as_array )
Key *HTable_keys_as_array( Prefix )( HTable_type( Prefix ) *current );

/**
   HTable_values_as_array

   Returns the values as an array.

   @param  current HTable_t instance
   @return array of Type values
*/
#define HTable_values_as_array( arg ) PRIMITIVE_CAT( arg, _htable_values_as_array )
Type *HTable_values_as_array( Prefix )( HTable_type( Prefix ) *current );

/*
   Access
*/

/**
   HTable_cursor_item_at

   Returns the value of the item that the HTable_cursor_t instance is pointing to.

   @param  cursor HTable_cursor_t instance
   @return a Type value
*/
#define HTable_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _htable_cursor_item_at )
Type HTable_cursor_item_at( Prefix )( HTable_cursor_type( Prefix ) *cursor );

/**
   HTable_cursor_key_at

   Returns the key of the item that the HTable_cursor_t instance is pointing to.

   @param  cursor HTable_cursor_t instance
   @return a Key value
*/
#define HTable_cursor_key_at( arg ) PRIMITIVE_CAT( arg, _htable_cursor_key_at )
Key HTable_cursor_key_at( Prefix )( HTable_cursor_type( Prefix ) *cursor );

/**
   HTable_item_at

   Returns the value of the item that the HTable_t instance's internal
   cursor is pointing to.

   @param  current HTable_t instance
   @return a Type value
*/
#define HTable_item_at( arg ) PRIMITIVE_CAT( arg, _htable_item_at )
Type HTable_item_at( Prefix )( HTable_type( Prefix ) *current );

/**
   HTable_key_at

   Returns the key of the item that the HTable_t instance's internal
   cursor is pointing to.

   @param  current HTable_t instance
   @return a Type value
*/
#define HTable_key_at( arg ) PRIMITIVE_CAT( arg, _htable_key_at )
Key HTable_key_at( Prefix )( HTable_type( Prefix ) *current );

/**
   HTable_item_at_index

   Returns the value of the item pointed to by index. First index is 0.

   @param  current HTable_t instance
   @param  index desired index
   @return a Type value
*/
#define HTable_item_at_index( arg ) PRIMITIVE_CAT( arg, _htable_item_at_index )
Type HTable_item_at_index( Prefix )( HTable_type( Prefix ) *current, int32_t index );

/**
   HTable_key_at_index

   Returns the key of the item pointed to by index. First index is 0.

   @param  current HTable_t instance
   @param  index desired index
   @return a Type value
*/
#define HTable_key_at_index( arg ) PRIMITIVE_CAT( arg, _htable_key_at_index )
Key HTable_key_at_index( Prefix )( HTable_type( Prefix ) *current, int32_t index );

/**
   HTable_item

   Returns the value of the item in the HTable_t instance associated
   with key.

   @param  current HTable_t instance
   @return a Type value
*/
#define HTable_item( arg ) PRIMITIVE_CAT( arg, _htable_item )
Type HTable_item( Prefix )( HTable_type( Prefix ) *current, Key key );


/*
   Measurement
*/

/**
   HTable_count

   Returns the number of items in the HTable_t instance.

   @param  current HTable_t instance
   @return number of items in HTable instance
*/
#define HTable_count( arg ) PRIMITIVE_CAT( arg, _htable_count )
int32_t HTable_count( Prefix )( HTable_type( Prefix ) *current );

/**
   HTable_bucket_count

   Returns the number of buckets in the HTable_t instance.

   @param  current HTable_t instance
   @return number of buckets in HTable instance
*/
#define HTable_bucket_count( arg ) PRIMITIVE_CAT( arg, _htable_bucket_count )
int32_t HTable_bucket_count( Prefix )( HTable_type( Prefix ) *current );


/*
   Status report
*/

/**
   HTable_off

   Returns 1 if the HTable_t instance's internal cursor is off, otherwise 0.

   @param  current HTable_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define HTable_off( arg ) PRIMITIVE_CAT( arg, _htable_off )
int32_t HTable_off( Prefix )( HTable_type( Prefix ) *current );

/**
   HTable_cursor_off

   Returns 1 if the HTable_cursor_t instance is off, otherwise 0.

   @param  cursor HTable_cursor_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define HTable_cursor_off( arg ) PRIMITIVE_CAT( arg, _htable_cursor_off )
int32_t HTable_cursor_off( Prefix )( HTable_cursor_type( Prefix ) *cursor );

/**
   HTable_is_empty

   Returns 1 if the HTable_t instance contains no items, otherwise 0.

   @param  current HTable_t instance
   @return 1 if empty, otherwise 0
*/
#define HTable_is_empty( arg ) PRIMITIVE_CAT( arg, _htable_is_empty )
int32_t HTable_is_empty( Prefix )( HTable_type( Prefix ) *current );

/**
   HTable_has

   Returns 1 if the HTable_t instance contains the key, otherwise 0.

   @param  current HTable_t instance
   @return 1 if htable has key, otherwise 0
*/
#define HTable_has( arg ) PRIMITIVE_CAT( arg, _htable_has )
int32_t HTable_has( Prefix )( HTable_type( Prefix ) *current, Key key );


/*
   Cursor movement
*/

/**
   HTable_cursor_forth

   Moves the HTable_cursor_t instance to the next item or off.

   @param  htable_cursor HTable_cursor_t instance
*/
#define HTable_cursor_forth( arg ) PRIMITIVE_CAT( arg, _htable_cursor_forth )
void HTable_cursor_forth( Prefix )( HTable_cursor_type( Prefix ) *cursor );

/**
   HTable_cursor_go

   Moves the HTable_t instance's internal cursor to the ith item in the htable.

   @param  htable_cursor HTable_cursor_t instance
   @param  index the index where the cursor will be moved to
*/
#define HTable_cursor_go( arg ) PRIMITIVE_CAT( arg, _htable_cursor_go )
void HTable_cursor_go( Prefix )( HTable_cursor_type( Prefix ) *cursor, int32_t index );

/**
   HTable_cursor_index

   Returns index of the cursor - if cursor is off, returns -1

   @param  list HTable_cursor_t instance
   @return index in list of cursor if not off, -1 otherwise
*/
#define HTable_cursor_index( arg ) PRIMITIVE_CAT( arg, _htable_cursor_index )
int32_t HTable_cursor_index( Prefix )( HTable_cursor_type( Prefix ) *cursor );

/**
   HTable_cursor_start

   Moves the HTable_cursor_t instance to the first item or off if the htable is empty.

   @param  htable_cursor HTable_cursor_t instance
*/
#define HTable_cursor_start( arg ) PRIMITIVE_CAT( arg, _htable_cursor_start )
void HTable_cursor_start( Prefix )( HTable_cursor_type( Prefix ) *cursor );

/**
   HTable_forth

   Moves the HTable_t instance internal cursor to the next item or off.

   @param  current HTable_t instance
*/
#define HTable_forth( arg ) PRIMITIVE_CAT( arg, _htable_forth )
void HTable_forth( Prefix )( HTable_type( Prefix ) *current );

/**
   HTable_go

   Moves the HTable_t instance's internal cursor to the ith item in the htable.

   @param  current HTable_t instance
   @param  index the index where the  will be moved to
*/
#define HTable_go( arg ) PRIMITIVE_CAT( arg, _htable_go )
void HTable_go( Prefix )( HTable_type( Prefix ) *current, int32_t index );

/**
   HTable_index

   Returns index of the internal cursor - if internal cursor is off, returns -1

   @param  current HTable_t instance
   @return index in list of internal cursor if not off, -1 otherwise
*/
#define HTable_index( arg ) PRIMITIVE_CAT( arg, _htable_index )
int32_t HTable_index( Prefix )( HTable_type( Prefix ) *current );

/**
   HTable_start

   Moves the HTable_t instance's internal cursor to the first item or off if the htable is empty.

   @param  current HTable_t instance
*/
#define HTable_start( arg ) PRIMITIVE_CAT( arg, _htable_start )
void HTable_start( Prefix )( HTable_type( Prefix ) *current );



/*
   Element change
*/

/**
   HTable_put

   Put the key-value pair into the HTable_t instance. Replace any existing item
   that has the same key.

   @param  current HTable_t instance
   @param  value the value to insert
   @param  key the key for the value
*/
#define HTable_put( arg ) PRIMITIVE_CAT( arg, _htable_put )
void HTable_put( Prefix )( HTable_type( Prefix ) *current, Type value, Key key );

/**
   HTable_replace

   Replace the value in the HTable_t instance that has the same key.

   @param  current HTable_t instance
   @param  value the value to replace with
   @param  key the key for the value
*/
#define HTable_replace( arg ) PRIMITIVE_CAT( arg, _htable_replace )
void HTable_replace( Prefix )( HTable_type( Prefix ) *current, Type value, Key key );

/**
   HTable_replace_and_dispose

   Replace the value in the HTable_t instance that has the same key. Dispose of
   the original value. Leave the key unchanged.

   @param  current HTable_t instance
   @param  value the value to replace with
   @param  key the key for the value
*/
#define HTable_replace_and_dispose( arg ) PRIMITIVE_CAT( arg, _htable_replace_and_dispose )
void HTable_replace_and_dispose( Prefix )( HTable_type( Prefix ) *current, Type value, Key key );


/*
   Removal
*/

/**
   HTable_remove

   Remove the item in the HTable_t instance that has the key.

   @param  current HTable_t instance
   @param  key the key for the value
*/
#define HTable_remove( arg ) PRIMITIVE_CAT( arg, _htable_remove )
void HTable_remove( Prefix )( HTable_type( Prefix ) *current, Key key );

/**
   HTable_remove_and_dispose

   Remove the item in the HTable_t instance that has the key and dispose
   of the key and the value.

   @param  current HTable_t instance
   @param  key the key for the value
*/
#define HTable_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _htable_remove_and_dispose )
void HTable_remove_and_dispose( Prefix )( HTable_type( Prefix ) *current, Key key );

/**
   HTable_wipe_out

   Remove all items in the HTable_t instance.

   @param  current HTable_t instance
*/
#define HTable_wipe_out( arg ) PRIMITIVE_CAT( arg, _htable_wipe_out )
void HTable_wipe_out( Prefix )( HTable_type( Prefix ) *current );

/**
   HTable_wipe_out_and_dispose

   Remove all items in the HTable_t instance. Dispose of all keys and values.

   @param  current HTable_t instance
*/
#define HTable_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _htable_wipe_out_and_dispose )
void HTable_wipe_out_and_dispose( Prefix )( HTable_type( Prefix ) *current );


/*
   Resize
*/

/**
   HTable_set_bucket_count

   Adjust the number of buckets in the htable.

   @param  current HTable_t instance
*/
#define HTable_set_bucket_count( arg ) PRIMITIVE_CAT( arg, _htable_set_bucket_count )
void HTable_set_bucket_count( Prefix )( HTable_type( Prefix ) *current, int32_t new_bucket_count );


#ifdef __cplusplus
}
#endif

/* End of file */



