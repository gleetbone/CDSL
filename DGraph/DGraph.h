/**
 @file DGraph.h
 @author Greg Lee
 @version 2.0.0
 @brief: "Directed graph with edges and nodes"

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

 Function declarations for the opaque DGraph_t type.

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

#define DGraph_struct( arg ) PRIMITIVE_CAT( arg, _dgraph_struct )
#define DGraph_cursor_struct( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_struct )

#define DGraph_type( arg ) PRIMITIVE_CAT( arg, _dgraph_t )
#define DGraph_cursor_type( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_t )

/**
   Structure declarations
*/

struct DGraph_struct( Prefix );
struct DGraph_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct DGraph_struct( Prefix ) DGraph_type( Prefix );
typedef struct DGraph_cursor_struct( Prefix ) DGraph_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/*
   Initialization
*/

/**
   DGraph_make

   Return a new DGraph_type( Prefix ) instance.

   @return DGraph_type( Prefix ) instance
*/
#define DGraph_make( arg ) PRIMITIVE_CAT( arg, _dgraph_make )
DGraph_type( Prefix ) * DGraph_make( Prefix )( void );

/**
   DGraph_make_cursor

   Return a new DGraph_cursor_type( Prefix ) instance.

   @param current the dgraph
   @return aDGraph_cursor_type( Prefix ) instance
*/
#define DGraph_make_cursor( arg ) PRIMITIVE_CAT( arg, _dgraph_make_cursor )
DGraph_cursor_type( Prefix ) * DGraph_make_cursor( Prefix )( DGraph_type( Prefix ) *current  );

/**
   DGraph_vertex_add

   Adds a new vertex to the DGraph_type( Prefix ) instance

   @param current DGraph_type( Prefix ) instance
   @param the new vertex's value
   @return the new vertex's id

*/
#define DGraph_vertex_add( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_add )
int32_t DGraph_vertex_add( Prefix )( DGraph_type( Prefix ) *current, Value value );

/**
   DGraph_edge_add

   Adds a new edge to the DGraph_type( Prefix ) instance

   @param current DGraph_type( Prefix ) instance
   @param vertex_from the id of the edge's starting vertex
   @param vertex_to the id of the edge's ending vertex
   @param the new edge's value
   @return the new edge's id

*/
#define DGraph_edge_add( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_add )
int32_t DGraph_edge_add( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t verves_from,
   int32_t vertex_to,
   Value value
);

/**
   DGraph_dispose

   Frees a DGraph_type( Prefix ) instance without freeing its contained vertex
   and edge values.

   @param current DGraph_type( Prefix ) instance
*/
#define DGraph_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_dispose )
void DGraph_dispose( Prefix )( DGraph_type( Prefix ) **current );

/*
   Disposal
*/

/**
   DGraph_dispose

   Frees a DGraph_type( Prefix ) instance without freeing its contained vertices
   and edges along with all cursors.

   @param current DGraph_type( Prefix ) instance
*/
#define DGraph_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_dispose )
void DGraph_dispose( Prefix )( DGraph_type( Prefix ) **current );

/**
   DGraph_deep_dispose

   Frees a DGraph_type( Prefix ) instance without freeing its contained vertices
   and edges, their values, and with all cursors.

   @param current DGraph_type( Prefix ) instance
*/
#define DGraph_deep_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_deep_dispose )
void DGraph_deep_dispose( Prefix )( DGraph_type( Prefix ) **current );

/**
   DGraph_cursor_dispose

   Frees a DGraph_cursor_type( Prefix ) instance.

   @param cursor DGraph_cursor_type( Prefix ) instance
*/
#define DGraph_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_dispose )
void DGraph_cursor_dispose( Prefix )( DGraph_cursor_type( Prefix ) **cursor );

/*
   Access
*/


/**
   DGraph_vertex_value

   Returns value of vertex

   @param current DGraph_type( Prefix ) instance
   @param id the vertex id
   @return the vertex value

*/
#define DGraph_vertex_value( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_value )
Value DGraph_vertex_value( Prefix )( DGraph_type( Prefix ) *current, int32_t id );

/**
   DGraph_edge_value

   Returns value of edge

   @param current DGraph_type( Prefix ) instance
   @param id the edge id
   @return the edge value

*/
#define DGraph_edge_value( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_value )
Edge DGraph_edge_value( Prefix )( DGraph_type( Prefix ) *current, int32_t id );

/**
   DGraph_edge_value_put

   Sets value of edge

   @param current DGraph_type( Prefix ) instance
   @param id the edge id
   @return the edge value

*/
#define DGraph_edge_value_put( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_value_put )
void DGraph_edge_value_put( Prefix )( DGraph_type( Prefix ) *current, int32_t id, Edge value );

/**
   DGraph_vertex_id_at

   Get id of current vertex pointed to by the internal cursor

   @param current DGraph_type( Prefix ) instance
   @return the vertex id pointed to by the internal cursor

*/
#define DGraph_vertex_id_at( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_id_at )
int32_t DGraph_vertex_id_at( Prefix )( DGraph_type( Prefix ) *current );

/**
   DGraph_cursor_vertex_id_at

   Get id of current vertex pointed to by the cursor

   @param cursor DGraph_cursor_type( Prefix ) instance
   @return the vertex id pointed to by the cursor

*/
#define DGraph_cursor_vertex_id_at( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_vertex_id_at )
int32_t DGraph_cursor_vertex_id_at( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_edge_id_at

   Get id of curren edge pointed to by the internal cursor

   @param current DGraph_type( Prefix ) instance
   @return the edge id pointed to by the internal cursor

*/
#define DGraph_edge_id_at( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_id_at )
int32_t DGraph_edge_id_at( Prefix )( DGraph_type( Prefix ) *current );

/**
   DGraph_cursor_edge_id_at

   Get id of current edge pointed to by the cursor

   @param cursor DGraph_cursor_type( Prefix ) instance
   @return the edge id pointed to by the cursor

*/
#define DGraph_cursor_edge_id_at( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_edge_id_at )
int32_t DGraph_cursor_edge_id_at( Prefix )( DGraph_cursor_type( Prefix ) *cursor );


/*
   Measurement
*/

/**
   DGraph_vertex_count

   Returns number of vertices in dgraph

   @param current DGraph_type( Prefix ) instance
   @return the number of vertexs

*/
#define DGraph_vertex_count( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_count )
int32_t DGraph_vertex_count( Prefix )( DGraph_type( Prefix ) *current );

/**
   DGraph_vertex_neighbors_from

   Returns array of vertex ids in neighbors_from. the vertices in the array
   are in no particular order.

   @param current DGraph_type( Prefix ) instance
   @param id the vertex id
   @param count pointer to the returned number of neighbor_from ids
   @return array of vertex ids - caller is responsible for disposing this array

*/
#define DGraph_vertex_neighbors_from( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_neighbors_from )
int32_t *
DGraph_vertex_neighbors_from( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t id,
   int32_t *count
);

/**
   DGraph_vertex_neighbors_to

   Returns array of vertex ids in neighbors_to the vertices in the array
   are in no particular order.

   @param current DGraph_type( Prefix ) instance
   @param id the vertex id
   @param count pointer to the returned number of neighbor_to ids
   @return array of vertex ids - caller is responsible for disposing this array

*/
#define DGraph_vertex_neighbors_to( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_neighbors_to )
int32_t *
DGraph_vertex_neighbors_to( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t id,
   int32_t *count
);

/**
   DGraph_edge_count

   Returns number of edges in dgraph

   @param current DGraph_type( Prefix ) instance
   @return the number of edges

*/
#define DGraph_edge_count( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_count )
int32_t DGraph_edge_count( Prefix )( DGraph_type( Prefix ) *current );

/**
   DGraph_edge_vertex_from

   Returns vertex id of edge start

   @param current DGraph_type( Prefix ) instance
   @param id the edge id
   @return vertex id of edge start

*/
#define DGraph_edge_vertex_from( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_vertex_from )
int32_t
DGraph_edge_vertex_from( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t id
);

/**
   DGraph_edge_vertex_to

   Returns vertex id of edge end

   @param current DGraph_type( Prefix ) instance
   @param id edge id
   @return vertex id of edge end

*/
#define DGraph_edge_vertex_to( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_vertex_to )
int32_t
DGraph_edge_vertex_to( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t id
);

/**
   DGraph_edge_for_from_to

   Returns id of edge connecting two vertices if it exists

   @param current DGraph_type( Prefix ) instance
   @param v_from id of the start vertex
   @param v_to id of the end vertex
   @return id of the found edge or -1 if no edge found

*/
#define DGraph_edge_for_from_to( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_for_from_to )
int32_t
DGraph_edge_for_from_to( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t v_from,
   int32_t v_to
);

/*
   Status report
*/

/**
   DGraph_is_equal

   Returns number of edges in dgraph

   @param current DGraph_type( Prefix ) instance
   @param other DGraph_type( Prefix ) instance to compare
   @return 1 if equal, 0 otherwise

*/
#define DGraph_is_equal( arg ) PRIMITIVE_CAT( arg, _dgraph_is_equal )
int32_t
DGraph_is_equal( Prefix )
(
   DGraph_type( Prefix ) *current,
   DGraph_type( Prefix ) *other
);

/**
   DGraph_is_deep_equal

   Returns number of edges in dgraph

   @param current DGraph_type( Prefix ) instance
   @param other DGraph_type( Prefix ) instance to compare
   @return 1 if equal, 0 otherwise

*/
#define DGraph_is_deep_equal( arg ) PRIMITIVE_CAT( arg, _dgraph_is_deep_equal )
int32_t
DGraph_is_deep_equal( Prefix )
(
   DGraph_type( Prefix ) *current,
   DGraph_type( Prefix ) *other
);

/**
   DGraph_connected_vertices_breadth_first

   Returns array of connected vertex ids

   @param current DGraph_type( Prefix ) instance
   @param vertex_id the vertex to start searching from - will be
      included in result
   @param count pointer that returns the number of items in the result array
   @return array of vertex indices

*/

#define DGraph_connected_vertices_breadth_first( arg ) \
PRIMITIVE_CAT( arg, _dgraph_connected_vertices_breadth_first )
int32_t *
DGraph_connected_vertices_breadth_first( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t vertex_id,
   int32_t *count
);

/**
   DGraph_connected_vertices_depth_first

   Returns array of connected vertex ids

   @param current DGraph_type( Prefix ) instance
   @param vertex_id the vertex to start searching from - will be
      included in result
   @param count pointer that returns the number of items in the result array
   @return array of vertex indices

*/

#define DGraph_connected_vertices_depth_first( arg ) \
PRIMITIVE_CAT( arg, _dgraph_connected_vertices_depth_first )
int32_t *
DGraph_connected_vertices_depth_first( Prefix )
(
   DGraph_type( Prefix ) *current,
   int32_t vertex_id,
   int32_t *count
);


/*
   Cursor movement
*/

/**
   DGraph_vertex_start

   Sets internal cursor to first vertex

   @param current DGraph_type( Prefix ) instance

*/
#define DGraph_vertex_start( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_start )
void DGraph_vertex_start( Prefix )( DGraph_type( Prefix ) *current );

/**
   DGraph_vertex_forth

   Sets internal cursor to first vertex

   @param current DGraph_type( Prefix ) instance

*/
#define DGraph_vertex_forth( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_forth )
void DGraph_vertex_forth( Prefix )( DGraph_type( Prefix ) *current );

/**
   DGraph_vertex_off

   Returns 1 if internal vertex cursor is off

   @param current DGraph_type( Prefix ) instance
   @return 1 if off, - otherwise 0

*/
#define DGraph_vertex_off( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_off )
int32_t  DGraph_vertex_off( Prefix )( DGraph_type( Prefix ) *current );

/**
   DGraph_cursor_vertex_start

   Sets cursor to first vertex

   @param current DGraph_cursor_type( Prefix ) instance

*/
#define DGraph_cursor_vertex_start( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_vertex_start )
void DGraph_cursor_vertex_start( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_cursor_vertex_forth

   Sets cursor to first vertex

   @param cursor DGraph_cursor_type( Prefix ) instance

*/
#define DGraph_cursor_vertex_forth( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_vertex_forth )
void DGraph_cursor_vertex_forth( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_cursor_vertex_off

   Returns 1 if vertex cursor is off

   @param cursor DGraph_cursor_type( Prefix ) instance
   @return 1 if off, - otherwise 0

*/
#define DGraph_cursor_vertex_off( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_vertex_off )
int32_t  DGraph_cursor_vertex_off( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_edge_start

   Sets internal cursor to first edge

   @param current DGraph_type( Prefix ) instance

*/
#define DGraph_edge_start( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_start )
void DGraph_edge_start( Prefix )( DGraph_type( Prefix ) *current );

/**
   DGraph_edge_forth

   Sets internal cursor to first edge

   @param current DGraph_type( Prefix ) instance

*/
#define DGraph_edge_forth( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_forth )
void DGraph_edge_forth( Prefix )( DGraph_type( Prefix ) *current );

/**
   DGraph_edge_off

   Returns 1 if internal edge cursor is off

   @param current DGraph_type( Prefix ) instance
   @return 1 if off, - otherwise0

*/
#define DGraph_edge_off( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_off )
int32_t  DGraph_edge_off( Prefix )( DGraph_type( Prefix ) *current );

/**
   DGraph_cursor_edge_start

   Sets cursor to first edge

   @param current DGraph_cursor_type( Prefix ) instance

*/
#define DGraph_cursor_edge_start( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_edge_start )
void DGraph_cursor_edge_start( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_cursor_edge_forth

   Sets cursor to first edge

   @param cursor DGraph_cursor_type( Prefix ) instance

*/
#define DGraph_cursor_edge_forth( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_edge_forth )
void DGraph_cursor_edge_forth( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_cursor_edge_off

   Returns 1 if edge cursor is off

   @param cursor DGraph_cursor_type( Prefix ) instance
   @return 1 if off, - otherwise 0

*/
#define DGraph_cursor_edge_off( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_edge_off )
int32_t  DGraph_cursor_edge_off( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/*
   Miscellaneous
*/

/**
   DGraph_copy

   Copies other into current

   @param current DGraph_type( Prefix ) instance to copy into
   @param other DGraph_type( Prefix ) instance to copy from

*/
#define DGraph_copy( arg ) PRIMITIVE_CAT( arg, _dgraph_copy )
void
DGraph_copy( Prefix )
(
   DGraph_type( Prefix ) *current,
   DGraph_type( Prefix ) *other
);

/**
   DGraph_deep_copy

   Deep copies other into current

   @param current DGraph_type( Prefix ) instance to copy into
   @param other DGraph_type( Prefix ) instance to copy from

*/
#define DGraph_deep_copy( arg ) PRIMITIVE_CAT( arg, _dgraph_deep_copy )
void
DGraph_deep_copy( Prefix )
(
   DGraph_type( Prefix ) *current,
   DGraph_type( Prefix ) *other
);

/**
   DGraph_clone

   Makes a clone of  current

   @param current DGraph_type( Prefix ) instance to clone
   @return DGraph_type( Prefix ) cloned instance

*/
#define DGraph_clone( arg ) PRIMITIVE_CAT( arg, _dgraph_clone )
DGraph_type( Prefix ) *
DGraph_clone( Prefix )
(
   DGraph_type( Prefix ) *current
);

/**
   DGraph_deep_clone

   Makes a deep_clone of  current

   @param current DGraph_type( Prefix ) instance to deep_clone
   @return DGraph_type( Prefix ) deep_cloned instance

*/
#define DGraph_deep_clone( arg ) PRIMITIVE_CAT( arg, _dgraph_deep_clone )
DGraph_type( Prefix ) *
DGraph_deep_clone( Prefix )
(
   DGraph_type( Prefix ) *current
);


/*
   Element change
*/

/**
   DGraph_vertex_value_put

   Sets value of vertex

   @param current DGraph_type( Prefix ) instance
   @param id the vertex id
   @param the new value

*/
#define DGraph_vertex_value_put( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_value_put )
void DGraph_vertex_value_put( Prefix )( DGraph_type( Prefix ) *current, int32_t id, Value value );

/**
   DGraph_edge_value_put

   Sets value of edge

   @param current DGraph_type( Prefix ) instance
   @param id the edge id
   @return the edge value

*/
#define DGraph_edge_value_put( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_value_put )
void DGraph_edge_value_put( Prefix )( DGraph_type( Prefix ) *current, int32_t id, Edge value );


/*
   Removal
*/

/**
   DGraph_vertex_remove

   Remove a vertex in the DGraph_type( Prefix ) instance. will also remove all
   edges that have this vertex as a start or end vertex. does not dispose of
   values.

   @param current DGraph_type( Prefix ) instance
   @param the vertex's id

*/
#define DGraph_vertex_remove( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_remove )
void DGraph_vertex_remove( Prefix )( DGraph_type( Prefix ) *current, int32_t id );

/**
   DGraph_vertex_remove_and_dispose

   Remove a vertex in the DGraph_type( Prefix ) instance. will also remove all
   edges that have this vertex as a start or end vertex. disposes of
   values.

   @param current DGraph_type( Prefix ) instance
   @param the vertex's id

*/
#define DGraph_vertex_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_remove_and_dispose )
void DGraph_vertex_remove_and_dispose( Prefix )( DGraph_type( Prefix ) *current, int32_t id );

/**
   DGraph_wipe_out

   Remove all vertices and edges in the DGraph_type( Prefix ) instance. does
   not dispose of values.

   @param current DGraph_type( Prefix ) instance

*/
#define DGraph_wipe_out( arg ) PRIMITIVE_CAT( arg, _dgraph_wipe_out )
void DGraph_wipe_out( Prefix )( DGraph_type( Prefix ) *current );

/**
   DGraph_wipe_out_and_dispose

   Remove all vertices and edges in the DGraph_type( Prefix ) instance.
   disposes of values.

   @param current DGraph_type( Prefix ) instance

*/
#define DGraph_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_wipe_out_and_dispose )
void DGraph_wipe_out_and_dispose( Prefix )( DGraph_type( Prefix ) *current );

/**
   DGraph_edge_remove

   Remove an edge in the DGraph_type( Prefix ) instance. does not dispose of
   values.

   @param current DGraph_type( Prefix ) instance
   @param the edge's id

*/
#define DGraph_edge_remove( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_remove )
void DGraph_edge_remove( Prefix )( DGraph_type( Prefix ) *current, int32_t id );

/**
   DGraph_edge_remove_and_dispose

   Remove an edge in the DGraph_type( Prefix ) instance. disposes of
   values.

   @param current DGraph_type( Prefix ) instance
   @param the edge's id

*/
#define DGraph_edge_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_remove_and_dispose )
void DGraph_edge_remove_and_dispose( Prefix )( DGraph_type( Prefix ) *current, int32_t id );

/**
   DGraph_wipe_out_edges

   Remove all edges in the DGraph_type( Prefix ) instance. does not dispose of
   values.

   @param current DGraph_type( Prefix ) instance

*/
#define DGraph_wipe_out_edges( arg ) PRIMITIVE_CAT( arg, _dgraph_wipe_out_edges )
void DGraph_wipe_out_edges( Prefix )( DGraph_type( Prefix ) *current );


/**
   DGraph_wipe_out_edges_and_dispose

   Remove all edges in the DGraph_type( Prefix ) instance. disposes of
   values.

   @param current DGraph_type( Prefix ) instance

*/
#define DGraph_wipe_out_edges_and_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_wipe_out_edges_and_dispose )
void DGraph_wipe_out_edges_and_dispose( Prefix )( DGraph_type( Prefix ) *current );


#ifdef __cplusplus
}
#endif

/* End of file */



