/**
 @file HSet.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Hash Sets"

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

 Function declarations for the opaque HSet_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
   Version
*/

#define HSET_VERSION_MAJOR 2
#define HSET_VERSION_MINOR 0
#define HSET_VERSION_PATCH 0

#define HSET_MAKE_VERSION( major, minor, patch ) \
   ( (major)*10000 + (minor)*100 + (patch) )

#define HSET_VERSION \
   HSET_MAKE_VERSION( HSET_VERSION_MAJOR, \
                       HSET_VERSION_MINOR, \
                       HSET_VERSION_PATCH )

/**
   Includes
*/

#include "base.h"

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix - string used to name this container type
   Item   - the type of the item

   Macros that must be present (external to this file):

   HASH_FUNCTION           -  takes a item instance as an argument and returns an
                              integer hash code
   DEEP_EQUAL_FUNCTION     -  compares two item instances for equality
   DEEP_CLONE_FUNCTION     -  makes a deep clone of the item
   DEEP_DISPOSE_FUNCTION   -  frees a item instance

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define HSet_struct( arg ) PRIMITIVE_CAT( arg, _hset_struct )
#define HSet_type( arg ) PRIMITIVE_CAT( arg, _hset_t )
#define HSet_name( arg ) PRIMITIVE_CAT( arg, _hset )

#define HSet_cursor_struct( arg ) PRIMITIVE_CAT( arg, _hset_cursor_struct )
#define HSet_cursor_type( arg ) PRIMITIVE_CAT( arg, _hset_cursor_t )
#define HSet_cursor_name( arg ) PRIMITIVE_CAT( arg, _hset_cursor )

/**
   Structure declarations
*/

struct HSet_struct( Prefix );
struct HSet_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct HSet_struct( Prefix ) HSet_type( Prefix );
typedef struct HSet_cursor_struct( Prefix ) HSet_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/*
   Initialization
*/

/**
   HSet_make

   Return a new HSet_t instance with a default number of buckets.

   @return HSet_t instance
*/
#define HSet_make( arg ) PRIMITIVE_CAT( arg, _hset_make )
HSet_type( Prefix ) * HSet_make( Prefix )( void );

/**
   HSet_make_n

   Return a new HSet_t instance with bucket_count buckets.

   @param  bucket_count the number or buckets to initialize the hash set with
   @return HSet_t instance
*/
#define HSet_make_n( arg ) PRIMITIVE_CAT( arg, _hset_make_n )
HSet_type( Prefix ) * HSet_make_n( Prefix )( int32_t bucket_count );

/**
   HSet_make_from_array

   Return a new HSet_t instance that has the same content as array. The
   values in array are not copied.

   @param  array the array to copy from
   @param  count the number of items to copy
   @return HSet_t instance
*/
#define HSet_make_from_array( arg ) PRIMITIVE_CAT( arg, _hset_make_from_array )
HSet_type( Prefix ) * HSet_make_from_array( Prefix )( Item *array, int32_t count );

/**
   HSet_cursor_make

   Return a new HSet_t cursor instance.

   @param  the HSet_t instance the new cursor works on
   @return HSet_cursor_t instance
*/
#define HSet_cursor_make( arg ) PRIMITIVE_CAT( arg, _hset_cursor_make )
HSet_cursor_type( Prefix ) * HSet_cursor_make( Prefix )( HSet_type( Prefix ) *hset );


/*
   Basic
*/

/**
   HSet_clone

   Return a new HSet_t instance that has the same content as hset. The
   values in hset are copied.

   @param  currrent the HSet_t instance to copy from
   @return HSet_t instance
*/
#define HSet_clone( arg ) PRIMITIVE_CAT( arg, _hset_clone )
HSet_type( Prefix ) * HSet_clone( Prefix )( HSet_type( Prefix ) *currrent );

/**
   HSet_deep_clone

   Return a new HSet_t instance that has the same content as hset. The
   values in hset are not copied.

   @param  currrent the HSet_t instance to copy from
   @return HSet_t instance
*/
#define HSet_deep_clone( arg ) PRIMITIVE_CAT( arg, _hset_deep_clone )
HSet_type( Prefix ) * HSet_deep_clone( Prefix )( HSet_type( Prefix ) *currrent );

/**
   HSet_is_equal

   Returns 1 if current and other contain same items (items compare equal).

   @param  current HSet_t instance
   @param  other HSet_t instance
   @return 1 if true, otherwise 0
*/
#define HSet_is_equal( arg ) PRIMITIVE_CAT( arg, _hset_is_equal )
int32_t HSet_is_equal( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other );

/**
   HSet_is_deep_equal

   Returns 1 if current and other contain equal items (items compare equal).

   @param  current HSet_t instance
   @param  other HSet_t instance
   @return 1 if true, otherwise 0
*/
#define HSet_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _hset_is_deep_equal )
int32_t HSet_is_deep_equal( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other );

/**
   HSet_copy

   Copy (shallow) other into current.

   @param  current HSet_t instance
   @param  other HSet_t instance
*/
#define HSet_copy( arg ) PRIMITIVE_CAT( arg, _hset_copy )
void HSet_copy( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other );

/**
   HSet_deep_copy

   Copy (shallow) other into current.

   @param  current HSet_t instance
   @param  other HSet_t instance
*/
#define HSet_deep_copy( arg ) PRIMITIVE_CAT( arg, _hset_deep_copy )
void HSet_deep_copy( Prefix )( HSet_type( Prefix ) *current, HSet_type( Prefix ) *other );

/*
   Disposal
*/

/**
   HSet_dispose

   Frees a HSet_t instance without freeing its contained items.

   @param pointer to HSet_t instance
*/
#define HSet_dispose( arg ) PRIMITIVE_CAT( arg, _hset_dispose )
void HSet_dispose( Prefix )( HSet_type( Prefix ) **currrent );

/**
   HSet_deep_dispose

   Frees a HSet_t instance and its contained items.

   @param pointer to HSet_t instance
*/
#define HSet_deep_dispose( arg ) PRIMITIVE_CAT( arg, _hset_deep_dispose )
void HSet_deep_dispose( Prefix )( HSet_type( Prefix ) **currrent );

/**
   HSet_cursor_dispose

   Frees a HSet_cursor_t instance. Its hset is not disposed.

   @param HSet_cursor_t instance
*/
#define HSet_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _hset_cursor_dispose )
void HSet_cursor_dispose( Prefix )( HSet_cursor_type( Prefix ) **cursor );


/*
   Access
*/

/**
   HSet_cursor_item_at

   Returns the value of the item that the HSet_cursor_t instance is pointing to.

   @param  HSet_cursor_t instance
   @return a Item value
*/
#define HSet_cursor_item_at( arg ) PRIMITIVE_CAT( arg, _hset_cursor_item_at )
Item HSet_cursor_item_at( Prefix )( HSet_cursor_type( Prefix ) *cursor );

/**
   HSet_item_at

   Returns the value of the item that the HSet_t instance's internal
   cursor is pointing to.

   @param  currrent HSet_t instance
   @return a Item value
*/
#define HSet_item_at( arg ) PRIMITIVE_CAT( arg, _hset_item_at )
Item HSet_item_at( Prefix )( HSet_type( Prefix ) *currrent );

/**
   HSet_item

   Returns the value of the item in the HSet_t instance associated
   with item.

   @param  currrent HSet_t instance
   @return a Item value
*/
#define HSet_item( arg ) PRIMITIVE_CAT( arg, _hset_item )
Item HSet_item( Prefix )( HSet_type( Prefix ) *hset, Item currrent );

/**
   HSet_item_at_index

   Returns the value of the item pointed to by index. First index is 0.

   @param  currrent HSet_t instance
   @param  index desired index
   @return a Item value
*/
#define HSet_item_at_index( arg ) PRIMITIVE_CAT( arg, _hset_item_at_index )
Item HSet_item_at_index( Prefix )( HSet_type( Prefix ) *currrent, int32_t index );

/**
   HSet_as_array

   Returns the values of the items in the HSet_t instance as an array.

   @param  currrent HSet_t instance
   @return array of items
*/
#define HSet_as_array( arg ) PRIMITIVE_CAT( arg, _hset_as_array )
Item * HSet_as_array( Prefix )( HSet_type( Prefix ) *currrent, int32_t *count );


/*
   Measurement
*/

/**
   HSet_count

   Returns the number of items in the HSet_t instance.

   @param  currrent HSet_t instance
   @return number of items in HSet instance
*/
#define HSet_count( arg ) PRIMITIVE_CAT( arg, _hset_count )
int32_t HSet_count( Prefix )( HSet_type( Prefix ) *currrent );

/**
   HSet_bucket_count

   Returns the number of buckets in the HSet_t instance.

   @param  currrent HSet_t instance
   @return number of buckets in HSet instance
*/
#define HSet_bucket_count( arg ) PRIMITIVE_CAT( arg, _hset_bucket_count )
int32_t HSet_bucket_count( Prefix )( HSet_type( Prefix ) *currrent );


/*
   Status report
*/

/**
   HSet_off

   Returns 1 if the HSet_t instance's internal cursor is off, otherwise 0.

   @param  currrent HSet_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define HSet_off( arg ) PRIMITIVE_CAT( arg, _hset_off )
int32_t HSet_off( Prefix )( HSet_type( Prefix ) *currrent );

/**
   HSet_cursor_off

   Returns 1 if the HSet_cursor_t instance is off, otherwise 0.

   @param  cursor HSet_cursor_t instance
   @return 1 if internal cursor is off, otherwise 0
*/
#define HSet_cursor_off( arg ) PRIMITIVE_CAT( arg, _hset_cursor_off )
int32_t HSet_cursor_off( Prefix )( HSet_cursor_type( Prefix ) *cursor );

/**
   HSet_is_empty

   Returns 1 if the HSet_t instance contains no items, otherwise 0.

   @param  currrent HSet_t instance
   @return 1 if empty, otherwise 0
*/
#define HSet_is_empty( arg ) PRIMITIVE_CAT( arg, _hset_is_empty )
int32_t HSet_is_empty( Prefix )( HSet_type( Prefix ) *currrent );

/**
   HSet_has

   Returns 1 if the HSet_t instance contains the item, otherwise 0.

   @param  currrent HSet_t instance
   @return 1 if hset has item, otherwise 0
*/
#define HSet_has( arg ) PRIMITIVE_CAT( arg, _hset_has )
int32_t HSet_has( Prefix )( HSet_type( Prefix ) *currrent, Item item );


/*
   Cursor movement
*/

/**
   HSet_cursor_forth

   Moves the HSet_cursor_t instance to the next item or off.

   @param  hset_cursor HSet_cursor_t instance
*/
#define HSet_cursor_forth( arg ) PRIMITIVE_CAT( arg, _hset_cursor_forth )
void HSet_cursor_forth( Prefix )( HSet_cursor_type( Prefix ) *cursor );

/**
   HSet_cursor_go

   Moves the HSet_t instance's internal cursor to the ith item in the hset.

   @param  hset_cursor HSet_cursor_t instance
   @param  index the index where the cursor will be moved to
*/
#define HSet_cursor_go( arg ) PRIMITIVE_CAT( arg, _hset_cursor_go )
void HSet_cursor_go( Prefix )( HSet_cursor_type( Prefix ) *cursor, int32_t index );

/**
   HSet_cursor_index

   Returns index of the cursor - if cursor is off, returns -1

   @param  list HSet_cursor_t instance
   @return index in list of cursor if not off, -1 otherwise
*/
#define HSet_cursor_index( arg ) PRIMITIVE_CAT( arg, _hset_cursor_index )
int32_t HSet_cursor_index( Prefix )( HSet_cursor_type( Prefix ) *cursor );

/**
   HSet_cursor_start

   Moves the HSet_cursor_t instance to the first item or off if the hset is empty.

   @param  hset_cursor HSet_cursor_t instance
*/
#define HSet_cursor_start( arg ) PRIMITIVE_CAT( arg, _hset_cursor_start )
void HSet_cursor_start( Prefix )( HSet_cursor_type( Prefix ) *cursor );

/**
   HSet_forth

   Moves the HSet_t instance internal cursor to the next item or off.

   @param  currrent HSet_t instance
*/
#define HSet_forth( arg ) PRIMITIVE_CAT( arg, _hset_forth )
void HSet_forth( Prefix )( HSet_type( Prefix ) *currrent );

/**
   HSet_go

   Moves the HSet_t instance's internal cursor to the ith item in the hset.

   @param  currrent HSet_t instance
   @param  index the index where the  will be moved to
*/
#define HSet_go( arg ) PRIMITIVE_CAT( arg, _hset_go )
void HSet_go( Prefix )( HSet_type( Prefix ) *currrent, int32_t index );

/**
   HSet_index

   Returns index of the internal cursor - if internal cursor is off, returns -1

   @param  currrent HSet_t instance
   @return index in list of internal cursor if not off, -1 otherwise
*/
#define HSet_index( arg ) PRIMITIVE_CAT( arg, _hset_index )
int32_t HSet_index( Prefix )( HSet_type( Prefix ) *currrent );

/**
   HSet_start

   Moves the HSet_t instance's internal cursor to the first item or off if the hset is empty.

   @param  currrent HSet_t instance
*/
#define HSet_start( arg ) PRIMITIVE_CAT( arg, _hset_start )
void HSet_start( Prefix )( HSet_type( Prefix ) *currrent );



/*
   Element change
*/

/**
   HSet_put

   Put the item into the HSet_t instance. Replace any existing item
   that compares equal.

   @param  currrent HSet_t instance
   @param  item the item to insert
*/
#define HSet_put( arg ) PRIMITIVE_CAT( arg, _hset_put )
void HSet_put( Prefix )( HSet_type( Prefix ) *currrent, Item item );

/**
   HSet_replace

   Replace the value in the HSet_t instance that compares equal to the same item.

   @param  currrent HSet_t instance
   @param  item the item to replace with
*/
#define HSet_replace( arg ) PRIMITIVE_CAT( arg, _hset_replace )
void HSet_replace( Prefix )( HSet_type( Prefix ) *currrent, Item item );

/**
   HSet_replace_and_dispose

   Replace the value in the HSet_t instance that compares equal to the same item.
   Dispose of the original item.

   @param  currrent HSet_t instance
   @param  item the item to replace with
*/
#define HSet_replace_and_dispose( arg ) PRIMITIVE_CAT( arg, _hset_replace_and_dispose )
void HSet_replace_and_dispose( Prefix )( HSet_type( Prefix ) *currrent, Item item );


/*
   Removal
*/

/**
   HSet_remove

   Remove the item in the HSet_t instance that compares equal.

   @param  currrent HSet_t instance
   @param  item the item
*/
#define HSet_remove( arg ) PRIMITIVE_CAT( arg, _hset_remove )
void HSet_remove( Prefix )( HSet_type( Prefix ) *currrent, Item item );

/**
   HSet_remove_and_dispose

   Remove the item in the HSet_t instance that compares equal and dispose
   of the item.

   @param  currrent HSet_t instance
   @param  item the item
*/
#define HSet_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _hset_remove_and_dispose )
void HSet_remove_and_dispose( Prefix )( HSet_type( Prefix ) *currrent, Item item );

/**
   HSet_wipe_out

   Remove all items in the HSet_t instance.

   @param  currrent HSet_t instance
*/
#define HSet_wipe_out( arg ) PRIMITIVE_CAT( arg, _hset_wipe_out )
void HSet_wipe_out( Prefix )( HSet_type( Prefix ) *currrent );

/**
   HSet_wipe_out_and_dispose

   Remove all items in the HSet_t instance. Dispose of all items.

   @param  currrent HSet_t instance
*/
#define HSet_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _hset_wipe_out_and_dispose )
void HSet_wipe_out_and_dispose( Prefix )( HSet_type( Prefix ) *currrent );


/*
   Resize
*/

/**
   HSet_set_bucket_count

   Adjust the number of buckets in the hset.

   @param  currrent HSet_t instance
*/
#define HSet_set_bucket_count( arg ) PRIMITIVE_CAT( arg, _hset_set_bucket_count )
void HSet_set_bucket_count( Prefix )( HSet_type( Prefix ) *currrent, int32_t new_bucket_count );

/*
   Set operations
*/

/**
   HSet_intersect

   Remove all items in hset that are not also in other.

   @param  currrent HSet_t instance
   @param  other HSet_t instance
*/
#define HSet_intersect( arg ) PRIMITIVE_CAT( arg, _hset_intersect )
void HSet_intersect( Prefix )( HSet_type( Prefix ) *currrent, HSet_type( Prefix ) *other );

/**
   HSet_intersection

   Return a new HSet_t instance that has the items in hset that are also in other.
   The items in hset are not copied.

   @param  currrent HSet_t instance
   @param  other HSet_t instance
   @return HSet_t instance
*/
#define HSet_intersection( arg ) PRIMITIVE_CAT( arg, _hset_intersection )
HSet_type( Prefix ) *
HSet_intersection( Prefix )( HSet_type( Prefix ) *currrent, HSet_type( Prefix ) *other );

/**
   HSet_subtract

   Remove all items in hset that are also in other.

   @param  currrent HSet_t instance
   @param  other HSet_t instance
*/
#define HSet_subtract( arg ) PRIMITIVE_CAT( arg, _hset_subtract )
void HSet_subtract( Prefix )( HSet_type( Prefix ) *currrent, HSet_type( Prefix ) *other );

/**
   HSet_subtraction

   Return a new HSet_t instance that has the items in hset that are not
   also in other. The items in hset are not copied.

   @param  currrent HSet_t instance
   @param  other HSet_t instance
   @return HSet_t instance
*/
#define HSet_subtraction( arg ) PRIMITIVE_CAT( arg, _hset_subtraction )
HSet_type( Prefix ) *
HSet_subtraction( Prefix )( HSet_type( Prefix ) *currrent, HSet_type( Prefix ) *other );

/**
   HSet_symdif

   Alter contents of hset so that items in other that are not in hset are added
   to hset, and items in hset that are also in other are removed from hset.

   @param  currrent HSet_t instance
   @param  other HSet_t instance
*/
#define HSet_symdif( arg ) PRIMITIVE_CAT( arg, _hset_symdif )
void HSet_symdif( Prefix )( HSet_type( Prefix ) *currrent, HSet_type( Prefix ) *other );

/**
   HSet_symdifference

   Return a new HSet_t instance such that items in hset that are not in other
   are in the result, and items in hset that are also in other are not in the
   result. The items in hset are not copied.

   @param  currrent HSet_t instance
   @param  other HSet_t instance
   @return HSet_t instance
*/
#define HSet_symdifference( arg ) PRIMITIVE_CAT( arg, _hset_symdifference )
HSet_type( Prefix ) *
HSet_symdifference( Prefix )( HSet_type( Prefix ) *currrent, HSet_type( Prefix ) *other );

/**
   HSet_merge

   Add items in other to hset.

   @param  currrent HSet_t instance
   @param  other HSet_t instance
*/
#define HSet_merge( arg ) PRIMITIVE_CAT( arg, _hset_merge )
void HSet_merge( Prefix )( HSet_type( Prefix ) *currrent, HSet_type( Prefix ) *other );

/**
   HSet_union

   Return a new HSet_t instance containins all items in hset and other. The
   items in hset and other are not copied.

   @param  currrent HSet_t instance
   @param  other HSet_t instance
   @return HSet_t instance
*/
#define HSet_union( arg ) PRIMITIVE_CAT( arg, _hset_union )
HSet_type( Prefix ) *
HSet_union( Prefix )( HSet_type( Prefix ) *currrent, HSet_type( Prefix ) *other );

/**
   HSet_is_disjoint

   Returns 1 if no item in hset is also in other.

   @param  currrent HSet_t instance
   @param  other HSet_t instance
   @return 1 if true, otherwise 0
*/
#define HSet_is_disjoint( arg ) PRIMITIVE_CAT( arg, _hset_is_disjoint )
int32_t HSet_is_disjoint( Prefix )( HSet_type( Prefix ) *currrent, HSet_type( Prefix ) *other );

/**
   HSet_is_subset

   Returns 1 if all items in hset are also in other.

   @param  currrent HSet_t instance
   @param  other HSet_t instance
   @return 1 if true, otherwise 0
*/
#define HSet_is_subset( arg ) PRIMITIVE_CAT( arg, _hset_is_subset )
int32_t HSet_is_subset( Prefix )( HSet_type( Prefix ) *currrent, HSet_type( Prefix ) *other );

/**
   HSet_is_superset

   Returns 1 if all items in other are also in hset.

   @param  currrent HSet_t instance
   @param  other HSet_t instance
   @return 1 if true, otherwise 0
*/
#define HSet_is_superset( arg ) PRIMITIVE_CAT( arg, _hset_is_superset )
int32_t HSet_is_superset( Prefix )( HSet_type( Prefix ) *currrent, HSet_type( Prefix ) *other );

/**
   HSet_equal_items

   Returns 1 if item and other compare equal.

   @param  item Item instance
   @param  other Item instance
   @return 1 if true, otherwise 0
*/
#define HSet_equal_items( arg ) PRIMITIVE_CAT( arg, _hset_equal_items )
int32_t HSet_equal_items( Prefix )( Item item, Item other );


#ifdef __cplusplus
}
#endif

/* End of file */



