/**
 @file UGraph.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Undirected graph with edges and nodes"

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

 Function declarations for the opaque UGraph_t type.

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
   Note that this include file does NOT have an include guard - it may
   be included multiple times with different macro defintions.

   Defines that must be present (external to this file):

   Prefix - string used to name this container type
   Value   - the type of the value
   Edge   - the type of the edge's "value"

   Macros that must be present (external to this file):

   EQUALITY_FUNCTION -  compares two vertex values for equality
   DISPOSE_FUNCTION  -  frees a vertex value instance
   EDGE_EQUALITY_FUNCTION -  compares two edge values for equality
   EDGE_DISPOSE_FUNCTION  -  frees a edge instance
   EDGE_DEFAULT_VALUE - the default value for an edge value (usually 0 or NULL)

*/

/**
   Macro definitions
*/

#define PRIMITIVE_CAT(arg, ...) arg ## __VA_ARGS__

#define UGraph_struct( arg ) PRIMITIVE_CAT( arg, _ugraph_struct )
#define UGraph_cursor_struct( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_struct )

#define UGraph_type( arg ) PRIMITIVE_CAT( arg, _ugraph_t )
#define UGraph_cursor_type( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_t )

/**
   Structure declarations
*/

struct UGraph_struct( Prefix );
struct UGraph_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct UGraph_struct( Prefix ) UGraph_type( Prefix );
typedef struct UGraph_cursor_struct( Prefix ) UGraph_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/*
   Initialization
*/

/**
   UGraph_make

   Return a new UGraph_type( Prefix ) instance.

   @return UGraph_type( Prefix ) instance
*/
#define UGraph_make( arg ) PRIMITIVE_CAT( arg, _ugraph_make )
UGraph_type( Prefix ) * UGraph_make( Prefix )( void );

/**
   UGraph_make_cursor

   Return a new UGraph_cursor_type( Prefix ) instance.

   @param current the ugraph
   @return aUGraph_cursor_type( Prefix ) instance
*/
#define UGraph_make_cursor( arg ) PRIMITIVE_CAT( arg, _ugraph_make_cursor )
UGraph_cursor_type( Prefix ) * UGraph_make_cursor( Prefix )( UGraph_type( Prefix ) *current  );

/**
   UGraph_vertex_add

   Adds a new vertex to the UGraph_type( Prefix ) instance

   @param current UGraph_type( Prefix ) instance
   @param the new vertex's value
   @return the new vertex's id

*/
#define UGraph_vertex_add( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_add )
int32_t UGraph_vertex_add( Prefix )( UGraph_type( Prefix ) *current, Value value );

/**
   UGraph_edge_add

   Adds a new edge to the UGraph_type( Prefix ) instance

   @param current UGraph_type( Prefix ) instance
   @param vertex_1 the id of the edge's "starting" vertex
   @param vertex_2 the id of the edge's "ending" vertex
   @param the new edge's value
   @return the new edge's id

*/
#define UGraph_edge_add( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_add )
int32_t UGraph_edge_add( Prefix )
(
   UGraph_type( Prefix ) *current,
   int32_t verves_1,
   int32_t vertex_2,
   Value value
);

/**
   UGraph_dispose

   Frees a UGraph_type( Prefix ) instance without freeing its contained vertex
   and edge values.

   @param current UGraph_type( Prefix ) instance
*/
#define UGraph_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_dispose )
void UGraph_dispose( Prefix )( UGraph_type( Prefix ) **current );

/*
   Disposal
*/

/**
   UGraph_dispose

   Frees a UGraph_type( Prefix ) instance without freeing its contained vertices
   and edges along with all cursors.

   @param current UGraph_type( Prefix ) instance
*/
#define UGraph_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_dispose )
void UGraph_dispose( Prefix )( UGraph_type( Prefix ) **current );

/**
   UGraph_deep_dispose

   Frees a UGraph_type( Prefix ) instance without freeing its contained vertices
   and edges, their values, and with all cursors.

   @param current UGraph_type( Prefix ) instance
*/
#define UGraph_deep_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_deep_dispose )
void UGraph_deep_dispose( Prefix )( UGraph_type( Prefix ) **current );

/**
   UGraph_cursor_dispose

   Frees a UGraph_cursor_type( Prefix ) instance.

   @param cursor UGraph_cursor_type( Prefix ) instance
*/
#define UGraph_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_dispose )
void UGraph_cursor_dispose( Prefix )( UGraph_cursor_type( Prefix ) **cursor );

/*
   Access
*/


/**
   UGraph_vertex_value

   Returns value of vertex

   @param current UGraph_type( Prefix ) instance
   @param id the vertex id
   @return the vertex value

*/
#define UGraph_vertex_value( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_value )
Value UGraph_vertex_value( Prefix )( UGraph_type( Prefix ) *current, int32_t id );

/**
   UGraph_edge_value

   Returns value of edge

   @param current UGraph_type( Prefix ) instance
   @param id the edge id
   @return the edge value

*/
#define UGraph_edge_value( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_value )
Edge UGraph_edge_value( Prefix )( UGraph_type( Prefix ) *current, int32_t id );

/**
   UGraph_edge_value_put

   Sets value of edge

   @param current UGraph_type( Prefix ) instance
   @param id the edge id
   @return the edge value

*/
#define UGraph_edge_value_put( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_value_put )
void UGraph_edge_value_put( Prefix )( UGraph_type( Prefix ) *current, int32_t id, Edge value );

/**
   UGraph_vertex_id_at

   Get id of current vertex pointed to by the internal cursor

   @param current UGraph_type( Prefix ) instance
   @return the vertex id pointed to by the internal cursor

*/
#define UGraph_vertex_id_at( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_id_at )
int32_t UGraph_vertex_id_at( Prefix )( UGraph_type( Prefix ) *current );

/**
   UGraph_cursor_vertex_id_at

   Get id of current vertex pointed to by the cursor

   @param cursor UGraph_cursor_type( Prefix ) instance
   @return the vertex id pointed to by the cursor

*/
#define UGraph_cursor_vertex_id_at( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_vertex_id_at )
int32_t UGraph_cursor_vertex_id_at( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_edge_id_at

   Get id of curren edge pointed to by the internal cursor

   @param current UGraph_type( Prefix ) instance
   @return the edge id pointed to by the internal cursor

*/
#define UGraph_edge_id_at( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_id_at )
int32_t UGraph_edge_id_at( Prefix )( UGraph_type( Prefix ) *current );

/**
   UGraph_cursor_edge_id_at

   Get id of current edge pointed to by the cursor

   @param cursor UGraph_cursor_type( Prefix ) instance
   @return the edge id pointed to by the cursor

*/
#define UGraph_cursor_edge_id_at( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_edge_id_at )
int32_t UGraph_cursor_edge_id_at( Prefix )( UGraph_cursor_type( Prefix ) *cursor );


/*
   Measurement
*/

/**
   UGraph_vertex_count

   Returns number of vertices in ugraph

   @param current UGraph_type( Prefix ) instance
   @return the number of vertexs

*/
#define UGraph_vertex_count( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_count )
int32_t UGraph_vertex_count( Prefix )( UGraph_type( Prefix ) *current );

/**
   UGraph_vertex_neighbors

   Returns array of vertex ids in neighbors_from. the vertices in the array
   are in no particular order.

   @param current UGraph_type( Prefix ) instance
   @param id the vertex id
   @param count pointer to the returned number of neighbor ids
   @return array of vertex ids - caller is responsible for disposing this array

*/
#define UGraph_vertex_neighbors( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_neighbors )
int32_t *
UGraph_vertex_neighbors( Prefix )
(
   UGraph_type( Prefix ) *current,
   int32_t id,
   int32_t *count
);

/**
   UGraph_edge_count

   Returns number of edges in ugraph

   @param current UGraph_type( Prefix ) instance
   @return the number of edges

*/
#define UGraph_edge_count( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_count )
int32_t UGraph_edge_count( Prefix )( UGraph_type( Prefix ) *current );

/**
   UGraph_edge_vertex_1

   Returns vertex id of edge "start"

   @param current UGraph_type( Prefix ) instance
   @param id the edge id
   @return vertex id of edge "start"

*/
#define UGraph_edge_vertex_1( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_vertex_1 )
int32_t
UGraph_edge_vertex_1( Prefix )
(
   UGraph_type( Prefix ) *current,
   int32_t id
);

/**
   UGraph_edge_vertex_2

   Returns vertex id of edge "end"

   @param current UGraph_type( Prefix ) instance
   @param id edge id
   @return vertex id of edge "end"

*/
#define UGraph_edge_vertex_2( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_vertex_2 )
int32_t
UGraph_edge_vertex_2( Prefix )
(
   UGraph_type( Prefix ) *current,
   int32_t id
);

/**
   UGraph_edge_for_vertices

   Returns id of edge connecting two vertices if it exists

   @param current UGraph_type( Prefix ) instance
   @param v_1 id of a vertex
   @param v_2 id of the other vertex
   @return id of the found edge or -1 if no edge found

*/
#define UGraph_edge_for_vertices( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_for_vertices )
int32_t
UGraph_edge_for_vertices( Prefix )
(
   UGraph_type( Prefix ) *current,
   int32_t v_1,
   int32_t v_2
);

/*
   Status report
*/

/**
   UGraph_is_equal

   Returns number of edges in ugraph

   @param current UGraph_type( Prefix ) instance
   @param other UGraph_type( Prefix ) instance to compare
   @return 1 if equal, 0 otherwise

*/
#define UGraph_is_equal( arg ) PRIMITIVE_CAT( arg, _ugraph_is_equal )
int32_t
UGraph_is_equal( Prefix )
(
   UGraph_type( Prefix ) *current,
   UGraph_type( Prefix ) *other
);

/**
   UGraph_is_deep_equal

   Returns number of edges in ugraph

   @param current UGraph_type( Prefix ) instance
   @param other UGraph_type( Prefix ) instance to compare
   @return 1 if equal, 0 otherwise

*/
#define UGraph_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _ugraph_is_deep_equal )
int32_t
UGraph_is_deep_equal( Prefix )
(
   UGraph_type( Prefix ) *current,
   UGraph_type( Prefix ) *other
);

/**
   UGraph_connected_vertices_breadth_first

   Returns array of connected vertex ids

   @param current UGraph_type( Prefix ) instance
   @param vertex_id the vertex to start searching from - will be
      included in result
   @param count pointer that returns the number of items in the result array
   @return array of vertex indices

*/

#define UGraph_connected_vertices_breadth_first( arg ) \
PRIMITIVE_CAT( arg, _ugraph_connected_vertices_breadth_first )
int32_t *
UGraph_connected_vertices_breadth_first( Prefix )
(
   UGraph_type( Prefix ) *current,
   int32_t vertex_id,
   int32_t *count
);

/**
   UGraph_connected_vertices_depth_first

   Returns array of connected vertex ids

   @param current UGraph_type( Prefix ) instance
   @param vertex_id the vertex to start searching from - will be
      included in result
   @param count pointer that returns the number of items in the result array
   @return array of vertex indices

*/

#define UGraph_connected_vertices_depth_first( arg ) \
PRIMITIVE_CAT( arg, _ugraph_connected_vertices_depth_first )
int32_t *
UGraph_connected_vertices_depth_first( Prefix )
(
   UGraph_type( Prefix ) *current,
   int32_t vertex_id,
   int32_t *count
);


/*
   Cursor movement
*/

/**
   UGraph_vertex_start

   Sets internal cursor to first vertex

   @param current UGraph_type( Prefix ) instance

*/
#define UGraph_vertex_start( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_start )
void UGraph_vertex_start( Prefix )( UGraph_type( Prefix ) *current );

/**
   UGraph_vertex_forth

   Sets internal cursor to first vertex

   @param current UGraph_type( Prefix ) instance

*/
#define UGraph_vertex_forth( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_forth )
void UGraph_vertex_forth( Prefix )( UGraph_type( Prefix ) *current );

/**
   UGraph_vertex_off

   Returns 1 if internal vertex cursor is off

   @param current UGraph_type( Prefix ) instance
   @return 1 if off, - otherwise 0

*/
#define UGraph_vertex_off( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_off )
int32_t  UGraph_vertex_off( Prefix )( UGraph_type( Prefix ) *current );

/**
   UGraph_cursor_vertex_start

   Sets cursor to first vertex

   @param current UGraph_cursor_type( Prefix ) instance

*/
#define UGraph_cursor_vertex_start( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_vertex_start )
void UGraph_cursor_vertex_start( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_cursor_vertex_forth

   Sets cursor to first vertex

   @param cursor UGraph_cursor_type( Prefix ) instance

*/
#define UGraph_cursor_vertex_forth( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_vertex_forth )
void UGraph_cursor_vertex_forth( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_cursor_vertex_off

   Returns 1 if vertex cursor is off

   @param cursor UGraph_cursor_type( Prefix ) instance
   @return 1 if off, - otherwise 0

*/
#define UGraph_cursor_vertex_off( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_vertex_off )
int32_t  UGraph_cursor_vertex_off( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_edge_start

   Sets internal cursor to first edge

   @param current UGraph_type( Prefix ) instance

*/
#define UGraph_edge_start( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_start )
void UGraph_edge_start( Prefix )( UGraph_type( Prefix ) *current );

/**
   UGraph_edge_forth

   Sets internal cursor to first edge

   @param current UGraph_type( Prefix ) instance

*/
#define UGraph_edge_forth( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_forth )
void UGraph_edge_forth( Prefix )( UGraph_type( Prefix ) *current );

/**
   UGraph_edge_off

   Returns 1 if internal edge cursor is off

   @param current UGraph_type( Prefix ) instance
   @return 1 if off, - otherwise0

*/
#define UGraph_edge_off( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_off )
int32_t  UGraph_edge_off( Prefix )( UGraph_type( Prefix ) *current );

/**
   UGraph_cursor_edge_start

   Sets cursor to first edge

   @param current UGraph_cursor_type( Prefix ) instance

*/
#define UGraph_cursor_edge_start( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_edge_start )
void UGraph_cursor_edge_start( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_cursor_edge_forth

   Sets cursor to first edge

   @param cursor UGraph_cursor_type( Prefix ) instance

*/
#define UGraph_cursor_edge_forth( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_edge_forth )
void UGraph_cursor_edge_forth( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_cursor_edge_off

   Returns 1 if edge cursor is off

   @param cursor UGraph_cursor_type( Prefix ) instance
   @return 1 if off, - otherwise 0

*/
#define UGraph_cursor_edge_off( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_edge_off )
int32_t  UGraph_cursor_edge_off( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/*
   Miscellaneous
*/

/**
   UGraph_copy

   Copies other into current

   @param current UGraph_type( Prefix ) instance to copy into
   @param other UGraph_type( Prefix ) instance to copy from

*/
#define UGraph_copy( arg ) PRIMITIVE_CAT( arg, _ugraph_copy )
void
UGraph_copy( Prefix )
(
   UGraph_type( Prefix ) *current,
   UGraph_type( Prefix ) *other
);

/**
   UGraph_deep_copy

   Deep copies other into current

   @param current UGraph_type( Prefix ) instance to copy into
   @param other UGraph_type( Prefix ) instance to copy from

*/
#define UGraph_deep_copy( arg ) PRIMITIVE_CAT( arg, _ugraph_deep_copy )
void
UGraph_deep_copy( Prefix )
(
   UGraph_type( Prefix ) *current,
   UGraph_type( Prefix ) *other
);

/**
   UGraph_clone

   Makes a clone of  current

   @param current UGraph_type( Prefix ) instance to clone
   @return UGraph_type( Prefix ) cloned instance

*/
#define UGraph_clone( arg ) PRIMITIVE_CAT( arg, _ugraph_clone )
UGraph_type( Prefix ) *
UGraph_clone( Prefix )
(
   UGraph_type( Prefix ) *current
);

/**
   UGraph_deep_clone

   Makes a deep_clone of  current

   @param current UGraph_type( Prefix ) instance to deep_clone
   @return UGraph_type( Prefix ) deep_cloned instance

*/
#define UGraph_deep_clone( arg ) PRIMITIVE_CAT( arg, _ugraph_deep_clone )
UGraph_type( Prefix ) *
UGraph_deep_clone( Prefix )
(
   UGraph_type( Prefix ) *current
);


/*
   Element change
*/

/**
   UGraph_vertex_value_put

   Sets value of vertex

   @param current UGraph_type( Prefix ) instance
   @param id the vertex id
   @param the new value

*/
#define UGraph_vertex_value_put( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_value_put )
void UGraph_vertex_value_put( Prefix )( UGraph_type( Prefix ) *current, int32_t id, Value value );

/**
   UGraph_edge_value_put

   Sets value of edge

   @param current UGraph_type( Prefix ) instance
   @param id the edge id
   @return the edge value

*/
#define UGraph_edge_value_put( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_value_put )
void UGraph_edge_value_put( Prefix )( UGraph_type( Prefix ) *current, int32_t id, Edge value );


/*
   Removal
*/

/**
   UGraph_vertex_remove

   Remove a vertex in the UGraph_type( Prefix ) instance. will also remove all
   edges that have this vertex as a start or end vertex. does not dispose of
   values.

   @param current UGraph_type( Prefix ) instance
   @param the vertex's id

*/
#define UGraph_vertex_remove( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_remove )
void UGraph_vertex_remove( Prefix )( UGraph_type( Prefix ) *current, int32_t id );

/**
   UGraph_vertex_remove_and_dispose

   Remove a vertex in the UGraph_type( Prefix ) instance. will also remove all
   edges that have this vertex as a start or end vertex. disposes of
   values.

   @param current UGraph_type( Prefix ) instance
   @param the vertex's id

*/
#define UGraph_vertex_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_remove_and_dispose )
void UGraph_vertex_remove_and_dispose( Prefix )( UGraph_type( Prefix ) *current, int32_t id );

/**
   UGraph_wipe_out

   Remove all vertices and edges in the UGraph_type( Prefix ) instance. does
   not dispose of values.

   @param current UGraph_type( Prefix ) instance

*/
#define UGraph_wipe_out( arg ) PRIMITIVE_CAT( arg, _ugraph_wipe_out )
void UGraph_wipe_out( Prefix )( UGraph_type( Prefix ) *current );

/**
   UGraph_wipe_out_and_dispose

   Remove all vertices and edges in the UGraph_type( Prefix ) instance.
   disposes of values.

   @param current UGraph_type( Prefix ) instance

*/
#define UGraph_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_wipe_out_and_dispose )
void UGraph_wipe_out_and_dispose( Prefix )( UGraph_type( Prefix ) *current );

/**
   UGraph_edge_remove

   Remove an edge in the UGraph_type( Prefix ) instance. does not dispose of
   values.

   @param current UGraph_type( Prefix ) instance
   @param the edge's id

*/
#define UGraph_edge_remove( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_remove )
void UGraph_edge_remove( Prefix )( UGraph_type( Prefix ) *current, int32_t id );

/**
   UGraph_edge_remove_and_dispose

   Remove an edge in the UGraph_type( Prefix ) instance. disposes of
   values.

   @param current UGraph_type( Prefix ) instance
   @param the edge's id

*/
#define UGraph_edge_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_remove_and_dispose )
void UGraph_edge_remove_and_dispose( Prefix )( UGraph_type( Prefix ) *current, int32_t id );

/**
   UGraph_wipe_out_edges

   Remove all edges in the UGraph_type( Prefix ) instance. does not dispose of
   values.

   @param current UGraph_type( Prefix ) instance

*/
#define UGraph_wipe_out_edges( arg ) PRIMITIVE_CAT( arg, _ugraph_wipe_out_edges )
void UGraph_wipe_out_edges( Prefix )( UGraph_type( Prefix ) *current );


/**
   UGraph_wipe_out_edges_and_dispose

   Remove all edges in the UGraph_type( Prefix ) instance. disposes of
   values.

   @param current UGraph_type( Prefix ) instance

*/
#define UGraph_wipe_out_edges_and_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_wipe_out_edges_and_dispose )
void UGraph_wipe_out_edges_and_dispose( Prefix )( UGraph_type( Prefix ) *current );


#ifdef __cplusplus
}
#endif

/* End of file */



