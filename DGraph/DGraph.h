/**
 @file DGraph.h
 @author Greg Lee
 @version 1.0.0
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

#define DGraph_vertex_struct( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_struct )

#define DGraph_edge_struct( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_struct )

#define DGraph_cursor_struct( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_struct )


#define DGraph_type( arg ) PRIMITIVE_CAT( arg, _dgraph_t )

#define DGraph_vertex_type( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_t )

#define DGraph_edge_type( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_t )

#define DGraph_cursor_type( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_t )

/** 
   Structure declarations
*/

struct DGraph_struct( Prefix );
struct DGraph_vertex_struct( Prefix );
struct DGraph_edge_struct( Prefix );
struct DGraph_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct DGraph_struct( Prefix ) DGraph_type( Prefix );
typedef struct DGraph_vertex_struct( Prefix ) DGraph_vertex_type( Prefix );
typedef struct DGraph_edge_struct( Prefix ) DGraph_edge_type( Prefix );
typedef struct DGraph_cursor_struct( Prefix ) DGraph_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/** 
   Initialization
*/

/**
   DGraph_make_depth
   
   Return a new DGraph_type( Prefix ) instance with a default number of buckets. Depth first
   search.
   
   @return DGraph_type( Prefix ) instance 
*/
#define DGraph_make_depth( arg ) PRIMITIVE_CAT( arg, _dgraph_make_depth )
DGraph_type( Prefix ) * DGraph_make_depth( Prefix )( void );

/**
   DGraph_make_breadth
   
   Return a new DGraph_type( Prefix ) instance with a default number of buckets. Breadth first
   search.
   
   @return DGraph_type( Prefix ) instance 
*/
#define DGraph_make_breadth( arg ) PRIMITIVE_CAT( arg, _dgraph_make_breadth )
DGraph_type( Prefix ) * DGraph_make_breadth( Prefix )( void );

/**
   DGraph_cursor_make_depth
   
   Return a new DGraph_type( Prefix ) cursor instance that makes depth first searches.
   
   @param  the DGraph_type( Prefix ) instance the new cursor works on 
   @return DGraph_cursor_t instance 
*/
#define DGraph_cursor_make_depth( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_make_depth )
DGraph_cursor_type( Prefix ) * DGraph_cursor_make_depth( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_cursor_make_breadth
   
   Return a new DGraph_type( Prefix ) cursor instance that makes breadth first searches.
   
   @param  the DGraph_type( Prefix ) instance the new cursor works on 
   @return DGraph_cursor_t instance 
*/
#define DGraph_cursor_make_breadth( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_make_breadth )
DGraph_cursor_type( Prefix ) * DGraph_cursor_make_breadth( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_vertex_make
   
   Return a new DGraph_vertex_type( Prefix ) instanc.
   
   @param  the value for the vertex 
   @return DGraph_vertex_type( Prefix ) instance 
*/
#define DGraph_vertex_make( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_make )
DGraph_vertex_type( Prefix ) * DGraph_vertex_make( Prefix )( Value value );


/** 
   Disposal
*/

/**
   DGraph_dispose
   
   Frees a DGraph_type( Prefix ) instance without freeing its contained values and edges.
   
   @param DGraph_type( Prefix ) instance 
*/
#define DGraph_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_dispose )
void DGraph_dispose( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_dispose_with_contents
   
   Frees a DGraph_type( Prefix ) instance and its contained values and edges.
   
   @param DGraph_type( Prefix ) instance 
*/
#define DGraph_dispose_with_contents( arg ) PRIMITIVE_CAT( arg, _dgraph_dispose_with_contents )
void DGraph_dispose_with_contents( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_cursor_dispose
   
   Frees a DGraph_cursor_t instance. Its DGraph is not disposed.
   
   @param DGraph_cursor_t instance 
*/
#define DGraph_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_dispose )
void DGraph_cursor_dispose( Prefix )( DGraph_cursor_type( Prefix ) *cursor );


/**
   DGraph_vertex_dispose
   
   Frees a DGraph_vertex_type( Prefix ) instance. Its value is not disposed. All edges of vertex
   and their "values" are disposed.
   
   @param  DGraph_vertex_type( Prefix ) instance 
*/
#define DGraph_vertex_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_dispose )
void DGraph_vertex_dispose( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex );

/**
   DGraph_vertex_dispose_with_contents
   
   Frees a DGraph_vertex_type( Prefix ) instance. Its value is disposed. All edges of vertex
   and their "values" are disposed.
   
   @param  DGraph_vertex_type( Prefix ) instance 
*/
#define DGraph_vertex_dispose_with_contents( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_dispose_with_contents )
void DGraph_vertex_dispose_with_contents( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex );

/** 
   Access
*/

/**
   DGraph_value
   
   Returns the value of the vertex.
   
   @param  DGraph DGraph_type( Prefix ) instance
   @param  vertex the vertex
   @return  value the new vertex Value
*/
#define DGraph_value( arg ) PRIMITIVE_CAT( arg, _dgraph_value )
Value DGraph_value( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex );

/**
   DGraph_edge_value_from_to
   
   Get the value of the edge defined by the from and to vertices.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  v_from the from vertex of the edge 
   @param  v_to the to vertex of the edge
   @return the value of the edge
*/
#define DGraph_edge_value_from_to( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_value_from_to )
Edge DGraph_edge_value_from_to( Prefix )
( 
   DGraph_type( Prefix ) *DGraph, 
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to
);

/**
   DGraph_edge_value
   
   Get the value of the edge.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  edge the edge 
   @return the edge value
*/
#define DGraph_edge_value( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_value )
Edge DGraph_edge_value( Prefix )
( 
   DGraph_type( Prefix ) *DGraph, 
   DGraph_edge_type( Prefix ) *edge 
);

/**
   DGraph_edge_vertex_from
   
   Get the value of the edge's vertex_from.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  edge the edge 
   @return the edge's vertex_from
*/
#define DGraph_edge_vertex_from( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_vertex_from )
DGraph_vertex_type( Prefix ) *DGraph_edge_vertex_from( Prefix )
( 
   DGraph_type( Prefix ) *DGraph, 
   DGraph_edge_type( Prefix ) *edge 
);

/**
   DGraph_edge_vertex_to
   
   Get the value of the edge's vertex_to.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  edge the edge 
   @return the edge's vertex_to
*/
#define DGraph_edge_vertex_to( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_vertex_to )
DGraph_vertex_type( Prefix ) *DGraph_edge_vertex_to( Prefix )
( 
   DGraph_type( Prefix ) *DGraph, 
   DGraph_edge_type( Prefix ) *edge 
);

/**
   DGraph_cursor_value_at
   
   Returns the value of the vertex that the DGraph_cursor_t instance is pointing to.
   
   @param  DGraph_cursor_t instance 
   @return a Value value
*/
#define DGraph_cursor_value_at( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_value_at )
Value DGraph_cursor_value_at( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_value_at
   
   Returns the value of the vertex that the DGraph_type( Prefix ) instance's internal
   cursor is pointing to.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return a Value value
*/
#define DGraph_value_at( arg ) PRIMITIVE_CAT( arg, _dgraph_value_at )
Value DGraph_value_at( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_cursor_at
   
   Returns the vertex that the DGraph_cursor_t instance is pointing to.
   
   @param  DGraph_cursor_t instance 
   @return a DGraph_vertex_type( Prefix ) vertex
*/
#define DGraph_cursor_at( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_at )
DGraph_vertex_type( Prefix ) *DGraph_cursor_at( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_at
   
   Returns the vertex of the vertex that the DGraph_type( Prefix ) instance's internal
   cursor is pointing to.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return a Value vertex
*/
#define DGraph_at( arg ) PRIMITIVE_CAT( arg, _dgraph_at )
DGraph_vertex_type( Prefix ) *DGraph_at( Prefix )( DGraph_type( Prefix ) *dgraph );


/**
   DGraph_as_array
   
   Returns array of vertices in the DGraph_type( Prefix ) instance. The vertices are not copied.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return array of vertices in DGraph instance
*/
#define DGraph_as_array( arg ) PRIMITIVE_CAT( arg, _dgraph_as_array )
DGraph_vertex_type( Prefix ) ** DGraph_as_array( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_cursor_edge_value_at
   
   Returns the edge value of the edge that the DGraph_cursor_t instance is pointing to.
   
   @param  DGraph_cursor_t instance 
   @return a Edge value
*/
#define DGraph_cursor_edge_value_at( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_edge_value_at )
Edge DGraph_cursor_edge_value_at( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_edge_value_at
   
   Returns the value of the edge that the DGraph_type( Prefix ) instance's internal
   cursor is pointing to.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return a Edge value
*/
#define DGraph_edge_value_at( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_value_at )
Edge DGraph_edge_value_at( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_cursor_edge_at
   
   Returns the edge that the DGraph_cursor_t instance is pointing to.
   
   @param  DGraph_cursor_t instance 
   @return a DGraph_edge_type( Prefix ) edge
*/
#define DGraph_cursor_edge_at( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_edge_at )
DGraph_edge_type( Prefix ) *DGraph_cursor_edge_at( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_edge_at
   
   Returns the edge that the DGraph_type( Prefix ) instance's internal
   cursor is pointing to.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return a edge
*/
#define DGraph_edge_at( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_at )
DGraph_edge_type( Prefix ) *DGraph_edge_at( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_edge_from_to
   
   Returns the edge that the DGraph_type( Prefix ) instance's internal
   cursor is pointing to.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return a edge
*/
#define DGraph_edge_from_to( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_from_to )
DGraph_edge_type( Prefix ) *DGraph_edge_from_to( Prefix )
( 
   DGraph_type( Prefix ) *dgraph, 
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to
);

/**
   DGraph_edges_as_array
   
   Returns array of edges in the DGraph_type( Prefix ) instance. The edges are not copied.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return array of edges in DGraph instance
*/
#define DGraph_edges_as_array( arg ) PRIMITIVE_CAT( arg, _dgraph_edges_as_array )
DGraph_edge_type( Prefix ) ** DGraph_edges_as_array( Prefix )( DGraph_type( Prefix ) *dgraph );

/** 
   Measurement
*/

/**
   DGraph_count
   
   Returns the number of vertices in the DGraph_type( Prefix ) instance.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return number of vertices in DGraph instance
*/
#define DGraph_count( arg ) PRIMITIVE_CAT( arg, _dgraph_count )
int32_t DGraph_count( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_edge_count
   
   Returns the number of edges in the DGraph_type( Prefix ) instance.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return number of edges in DGraph instance
*/
#define DGraph_edge_count( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_count )
int32_t DGraph_edge_count( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_are_adjacent
   
   Returns 1 if vertices v1 and v2 are connected with edge from v1 to v2, 
   otherwise 0.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return 1 if vertices are adjacent, otherwise 0
*/
#define DGraph_are_adjacent( arg ) PRIMITIVE_CAT( arg, _dgraph_are_adjacent )
int32_t DGraph_are_adjacent( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *v1, DGraph_vertex_type( Prefix ) *v2 );


/** 
   Status report
*/

/**
   DGraph_off
   
   Returns 1 if the DGraph_type( Prefix ) instance's internal cursor is off, otherwise 0.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return 1 if internal cursor is off, otherwise 0
*/
#define DGraph_off( arg ) PRIMITIVE_CAT( arg, _dgraph_off )
int32_t DGraph_off( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_cursor_off
   
   Returns 1 if the DGraph_cursor_t instance is off, otherwise 0.
   
   @param  cursor DGraph_cursor_t instance 
   @return 1 if internal cursor is off, otherwise 0
*/
#define DGraph_cursor_off( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_off )
int32_t DGraph_cursor_off( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_is_empty
   
   Returns true if no vertices are in the DGraph_type( Prefix ) instance.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return is the the DGraph instance empty?
   
*/
#define DGraph_is_empty( arg ) PRIMITIVE_CAT( arg, _dgraph_is_empty )
int32_t DGraph_is_empty( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_edge_off
   
   Returns 1 if the DGraph_type( Prefix ) instance's internal edge cursor is 
   off, otherwise 0.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return 1 if internal edge cursor is off, otherwise 0
*/
#define DGraph_edge_off( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_off )
int32_t DGraph_edge_off( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_cursor_edge_off
   
   Returns 1 if the DGraph_cursor_t edge instance is off, otherwise 0.
   
   @param  cursor DGraph_cursor_t instance 
   @return 1 if internal cursor is off, otherwise 0
*/
#define DGraph_cursor_edge_off( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_edge_off )
int32_t DGraph_cursor_edge_off( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_edge_is_empty
   
   Returns true if no edges are in the DGraph_type( Prefix ) instance.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return is the the DGraph instance empty?
   
*/
#define DGraph_edge_is_empty( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_is_empty )
int32_t DGraph_edge_is_empty( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_is_connected
   
   Returns true if there is a path between all vertices in the DGraph_type( Prefix ) instance.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @return are all vertices in the the DGraph instance connected?
   
*/
#define DGraph_is_connected( arg ) PRIMITIVE_CAT( arg, _dgraph_is_connected )
int32_t DGraph_is_connected( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_has
   
   Returns 1 if the DGraph_type( Prefix ) instance contains the vertex, otherwise 0.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  vertex the vertex to search for 
   @return 1 if DGraph has value, otherwise 0
*/
#define DGraph_has( arg ) PRIMITIVE_CAT( arg, _dgraph_has )
int32_t DGraph_has( Prefix )( DGraph_type( Prefix ) *DGraph, DGraph_vertex_type( Prefix ) *vertex );

/**
   DGraph_edge_has
   
   Returns 1 if the DGraph_type( Prefix ) instance contains the edge, otherwise 0.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  edge the edge to search for 
   @return 1 if DGraph has value, otherwise 0
*/
#define DGraph_edge_has( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_has )
int32_t DGraph_edge_has( Prefix )( DGraph_type( Prefix ) *DGraph, DGraph_edge_type( Prefix ) *edge );

/**
   DGraph_has_value
   
   Returns 1 if the DGraph_type( Prefix ) instance contains a vertex with the value, otherwise 0.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  value the value to search for 
   @return 1 if DGraph has value, otherwise 0
*/
#define DGraph_has_value( arg ) PRIMITIVE_CAT( arg, _dgraph_has_value )
int32_t DGraph_has_value( Prefix )( DGraph_type( Prefix ) *DGraph, Value value );

/**
   DGraph_edge_has_value
   
   Returns 1 if the DGraph_type( Prefix ) instance contains an edge with the edge value, otherwise 0.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  edge the edge value to search for 
   @return 1 if DGraph has edge value, otherwise 0
*/
#define DGraph_edge_has_value( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_has_value )
int32_t DGraph_edge_has_value( Prefix )( DGraph_type( Prefix ) *DGraph, Edge edge );

/**
   DGraph_neighbors_from
   
   Returns array of vertices that the vertex is connected to by a directed edge.
   
   @param  DGraph DGraph_type( Prefix ) instance
   @param  vertex the vertex to look at
   @return array of vertices
*/
#define DGraph_neighbors_from( arg ) PRIMITIVE_CAT( arg, _dgraph_neighbors_from )
DGraph_vertex_type( Prefix ) ** DGraph_neighbors_from( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex );

/**
   DGraph_neighbors_to
   
   Returns array of vertices that the vertex is connected to by a directed edge.
   
   @param  DGraph DGraph_type( Prefix ) instance
   @param  vertex the vertex to look at
   @return array of vertices
*/
#define DGraph_neighbors_to( arg ) PRIMITIVE_CAT( arg, _dgraph_neighbors_to )
DGraph_vertex_type( Prefix ) ** DGraph_neighbors_to( Prefix )( DGraph_type( Prefix ) *dgraph, DGraph_vertex_type( Prefix ) *vertex );


/** 
   Cursor movement
*/

/**
   DGraph_cursor_forth
   
   Moves the DGraph_cursor_t instance to the next item or off.
   
   @param  DGraph_cursor DGraph_cursor_t instance 
*/
#define DGraph_cursor_forth( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_forth )
void DGraph_cursor_forth( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_cursor_start
   
   Moves the DGraph_cursor_t instance to the first item or off if the DGraph is empty.
   
   @param  DGraph_cursor DGraph_cursor_t instance 
*/
#define DGraph_cursor_start( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_start )
void DGraph_cursor_start( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_forth
   
   Moves the DGraph_type( Prefix ) instance internal cursor to the next item or off.
   
   @param  DGraph DGraph_type( Prefix ) instance 
*/
#define DGraph_forth( arg ) PRIMITIVE_CAT( arg, _dgraph_forth )
void DGraph_forth( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_start
   
   Moves the DGraph_type( Prefix ) instance's internal cursor to the first item or off if the DGraph is empty.
   
   @param  DGraph DGraph_type( Prefix ) instance 
*/
#define DGraph_start( arg ) PRIMITIVE_CAT( arg, _dgraph_start )
void DGraph_start( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_find_value
   
   Returns vertex if search finds a vertex with value in the DGraph_type( Prefix ) instance, 
   otherwise null. Starts at "start". If found, internal cursor points to vertex,
   search paused at that point.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  value the value to search for 
   @return vertex if search found vertex with value in DGraph, otherwise null
*/
#define DGraph_find_value( arg ) PRIMITIVE_CAT( arg, _dgraph_find_value )
DGraph_vertex_type( Prefix ) *DGraph_find_value( Prefix )( DGraph_type( Prefix ) *DGraph, Value value );

/**
   DGraph_find_next_value
   
   Returns vertex if search finds a vertex with value in the DGraph_type( Prefix ) instance 
   starting where the last search ended, otherwise null. Starts at internal cursor 
   current position. If found internal cursor points to vertex, search paused at
   that point.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  value the value to search for 
   @return vertex if search found vertex with value in DGraph, otherwise null
*/
#define DGraph_find_next_value( arg ) PRIMITIVE_CAT( arg, _dgraph_find_next_value )
DGraph_vertex_type( Prefix ) *DGraph_find_next_value( Prefix )( DGraph_type( Prefix ) *DGraph, Value value );

/**
   DGraph_cursor_find_value
   
   Returns vertex if search finds a vertex with value in the DGraph_type( Prefix ) instance, 
   otherwise null. Starts at "start". If found, internal cursor points to vertex,
   search paused at that point.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  value the value to search for 
   @return vertex if search found vertex with value in DGraph, otherwise null
*/
#define DGraph_cursor_find_value( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_find_value )
DGraph_vertex_type( Prefix ) *DGraph_cursor_find_value( Prefix )( DGraph_cursor_type( Prefix ) *DGraph, Value value );

/**
   DGraph_cursor_find_next_value
   
   Returns vertex if search finds a vertex with value in the DGraph_type( Prefix ) instance 
   starting where the last search ended, otherwise null. Starts at internal cursor 
   current position. If found internal cursor points to vertex, search paused at
   that point.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  value the value to search for 
   @return vertex if search found vertex with value in DGraph, otherwise null
*/
#define DGraph_cursor_find_next_value( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_find_next_value )
DGraph_vertex_type( Prefix ) *DGraph_cursor_find_next_value( Prefix )( DGraph_cursor_type( Prefix ) *DGraph, Value value );


/**
   DGraph_cursor_edge_forth
   
   Moves the DGraph_cursor_t instance to the next edge item or off.
   
   @param  DGraph_cursor DGraph_cursor_t instance 
*/
#define DGraph_cursor_edge_forth( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_edge_forth )
void DGraph_cursor_edge_forth( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_cursor_edge_start
   
   Moves the DGraph_cursor_t instance to the first edge or off if the DGraph is empty.
   
   @param  DGraph_cursor DGraph_cursor_t instance 
*/
#define DGraph_cursor_edge_start( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_edge_start )
void DGraph_cursor_edge_start( Prefix )( DGraph_cursor_type( Prefix ) *cursor );

/**
   DGraph_edge_forth
   
   Moves the DGraph_type( Prefix ) instance internal cursor to the next edge or off.
   
   @param  DGraph DGraph_type( Prefix ) instance 
*/
#define DGraph_edge_forth( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_forth )
void DGraph_edge_forth( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_edge_start
   
   Moves the DGraph_type( Prefix ) instance's internal cursor to the first edge 
   or off if the DGraph is empty.
   
   @param  DGraph DGraph_type( Prefix ) instance 
*/
#define DGraph_edge_start( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_start )
void DGraph_edge_start( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_edge_find_value
   
   Returns edge if search finds an edge with value in the DGraph_type( Prefix ) instance, 
   otherwise null. Starts at "start". If found, internal cursor points to edge,
   search paused at that point.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  value the edge value to search for 
   @return edge if search found edge with value in DGraph, otherwise null
*/
#define DGraph_edge_find_value( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_find_value )
DGraph_edge_type( Prefix ) *DGraph_edge_find_value( Prefix )( DGraph_type( Prefix ) *DGraph, Edge value );

/**
   DGraph_edge_find_next_value
   
   Returns edge if search finds an edge with value in the DGraph_type( Prefix ) instance 
   starting where the last search ended, otherwise null. Starts at internal cursor 
   current position. If found internal cursor points to edge, search paused at
   that point.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  value the edge value to search for 
   @return edge if search found edge with value in DGraph, otherwise null
*/
#define DGraph_edge_find_next_value( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_find_next_value )
DGraph_edge_type( Prefix ) *DGraph_edge_find_next_value( Prefix )( DGraph_type( Prefix ) *DGraph, Edge value );

/**
   DGraph_cursor_edge_find_value
   
   Returns edge if search finds an edge with value in the DGraph_type( Prefix ) instance, 
   otherwise null. Starts at "start". If found, internal cursor points to edge,
   search paused at that point.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  value the edge value to search for 
   @return vertex if search found vertex with value in DGraph, otherwise null
*/
#define DGraph_cursor_edge_find_value( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_edge_find_value )
DGraph_edge_type( Prefix ) *DGraph_cursor_edge_find_value( Prefix )( DGraph_cursor_type( Prefix ) *DGraph, Edge value );

/**
   DGraph_cursor_edge_find_next_value
   
   Returns edge if search finds an edge with value in the DGraph_type( Prefix ) instance 
   starting where the last search ended, otherwise null. Starts at internal cursor 
   current position. If found internal cursor points to edge, search paused at
   that point.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  value the edge value to search for 
   @return edge if search found edge with value in DGraph, otherwise null
*/
#define DGraph_cursor_edge_find_next_value( arg ) PRIMITIVE_CAT( arg, _dgraph_cursor_edge_find_next_value )
DGraph_edge_type( Prefix ) *DGraph_cursor_edge_find_next_value( Prefix )( DGraph_cursor_type( Prefix ) *DGraph, Edge value );

/**
   Miscellaneous
*/

/**
   DGraph_vertex_set_bucket_count
   
   Sets bucket count of internal hash sets of vertices. 
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  bucket_count number of hash buckets to set to (should be prime number) 
*/
#define DGraph_vertex_set_bucket_count( arg ) PRIMITIVE_CAT( arg, _dgraph_vertex_set_bucket_count )
void DGraph_vertex_set_bucket_count( Prefix )( DGraph_type( Prefix ) *DGraph, int32_t bucket_count );

/**
   DGraph_edge_set_bucket_count
   
   Sets bucket count of internal hash sets of edges. 
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  bucket_count number of hash buckets to set to (should be prime number) 
*/
#define DGraph_edge_set_bucket_count( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_set_bucket_count )
void DGraph_edge_set_bucket_count( Prefix )( DGraph_type( Prefix ) *DGraph, int32_t bucket_count );



/** 
   Element change
*/

/**
   DGraph_put
   
   Put the vertex into the DGraph_type( Prefix ) instance. Does not alter or add edges.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  vertex the vertex to insert 
*/
#define DGraph_put( arg ) PRIMITIVE_CAT( arg, _dgraph_put )
void DGraph_put( Prefix )( DGraph_type( Prefix ) *DGraph, DGraph_vertex_type( Prefix ) *vertex );

/**
   DGraph_edge_put
   
   Put the edge into the DGraph_type( Prefix ) instance.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  edge the edge to insert 
   @param  v_from the "from" vertex for the edge 
   @param  v_to "to" vertex for the edge 
*/
#define DGraph_edge_put( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_put )
void DGraph_edge_put( Prefix )
( 
   DGraph_type( Prefix ) *DGraph, 
   Edge edge,
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to 
);

/**
   DGraph_set_value
   
   Set the vertex' value.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  vertex the vertex to insert 
   @param  value the new value for the 
*/
#define DGraph_set_value( arg ) PRIMITIVE_CAT( arg, _dgraph_set_value )
void DGraph_set_value( Prefix )
(
   DGraph_type( Prefix ) *DGraph, 
   DGraph_vertex_type( Prefix ) *vertex,
   Value value
);

/**
   DGraph_edge_set
   
   Set the value of the edge.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  v_from the from vertex of the edge 
   @param  v_to the to vertex of the edge
   @param  edge the new value for the edge
*/
#define DGraph_edge_set( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_set )
void DGraph_edge_set( Prefix )
( 
   DGraph_type( Prefix ) *DGraph, 
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to,
   Edge edge
);

/**
   DGraph_edge_set_value
   
   Set the value of the edge.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  edge the edge 
   @param  edge the new value for the edge
*/
#define DGraph_edge_set_value( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_set_value )
void DGraph_edge_set_value( Prefix )
( 
   DGraph_type( Prefix ) *DGraph, 
   DGraph_edge_type( Prefix ) *edge, 
   Edge edge_value
);


/** 
   Removal
*/

/**
   DGraph_remove
   
   Remove the vertex from the DGraph_type( Prefix ) instance. All edges that connect to vertex 
   are disposed. Their edge values are not disposed of. The vertex is not disposed.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  vertex the vertex to dispose 
*/
#define DGraph_remove( arg ) PRIMITIVE_CAT( arg, _dgraph_remove )
void DGraph_remove( Prefix )( DGraph_type( Prefix ) *DGraph, DGraph_vertex_type( Prefix ) *vertex );

/**
   DGraph_remove_and_dispose
   
   Remove the vertex from the DGraph_type( Prefix ) instance All edges that connect to vertex 
   and their edge values are disposed of. The vertex and its value is disposed.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  vertex the vertex to dispose 
*/
#define DGraph_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_remove_and_dispose )
void DGraph_remove_and_dispose( Prefix )( DGraph_type( Prefix ) *DGraph, DGraph_vertex_type( Prefix ) *vertex );

/**
   DGraph_edge_remove_from_to
   
   Remove and dispose the edge from the DGraph_type( Prefix ) instance. The edge value is 
   not disposed.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  v_from the from vertex of the edge 
   @param  v_to the to vertex of the edge 
*/
#define DGraph_edge_remove_from_to( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_remove_from_to )
void DGraph_edge_remove_from_to( Prefix )
( 
   DGraph_type( Prefix ) *DGraph, 
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to
);

/**
   DGraph_edge_remove_and_dispose_from_to
   
   Remove and dispose the edge from the DGraph_type( Prefix ) instance.The edge value is 
   disposed.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  v_from the from vertex of the edge 
   @param  v_to the to vertex of the edge 
*/
#define DGraph_edge_remove_and_dispose_from_to( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_remove_and_dispose_from_to )
void DGraph_edge_remove_and_dispose_from_to( Prefix )
( 
   DGraph_type( Prefix ) *DGraph, 
   DGraph_vertex_type( Prefix ) *v_from, 
   DGraph_vertex_type( Prefix ) *v_to
);

/**
   DGraph_edge_remove
   
   Remove and dispose the edge from the DGraph_type( Prefix ) instance. The edge value is 
   not disposed.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  edge the edge to remove 
*/
#define DGraph_edge_remove( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_remove )
void DGraph_edge_remove( Prefix )
( 
   DGraph_type( Prefix ) *DGraph, 
   DGraph_edge_type( Prefix ) *edge 
);

/**
   DGraph_edge_remove_and_dispose
   
   Remove and dispose the edge from the DGraph_type( Prefix ) instance.The edge value is 
   disposed.
   
   @param  DGraph DGraph_type( Prefix ) instance 
   @param  edge the edge to remove
*/
#define DGraph_edge_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_remove_and_dispose )
void DGraph_edge_remove_and_dispose( Prefix )
( 
   DGraph_type( Prefix ) *DGraph, 
   DGraph_edge_type( Prefix ) *edge
);

/**
   DGraph_wipe_out
   
   Remove all vertices and edges in the DGraph_type( Prefix ) instance. The edge and vertex
   structures are not disposed.
   
   @param  DGraph DGraph_type( Prefix ) instance 
*/
#define DGraph_wipe_out( arg ) PRIMITIVE_CAT( arg, _dgraph_wipe_out )
void DGraph_wipe_out( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_wipe_out_and_dispose
   
   Remove all vertices and edges in the DGraph_type( Prefix ) instance. Dispose of all 
   vertices and edges and their values.
   
   @param  DGraph DGraph_type( Prefix ) instance 
*/
#define DGraph_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_wipe_out_and_dispose )
void DGraph_wipe_out_and_dispose( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_edge_wipe_out
   
   Remove all edges in the DGraph_type( Prefix ) instance. The edge
   structures are not disposed.
   
   @param  DGraph DGraph_type( Prefix ) instance 
*/
#define DGraph_edge_wipe_out( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_wipe_out )
void DGraph_edge_wipe_out( Prefix )( DGraph_type( Prefix ) *dgraph );

/**
   DGraph_edge_wipe_out_and_dispose
   
   Remove all edges in the DGraph_type( Prefix ) instance. Dispose of all 
   edges and their values.
   
   @param  DGraph DGraph_type( Prefix ) instance 
*/
#define DGraph_edge_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _dgraph_edge_wipe_out_and_dispose )
void DGraph_edge_wipe_out_and_dispose( Prefix )( DGraph_type( Prefix ) *dgraph );

#ifdef __cplusplus
}
#endif

/* End of file */



