/**
 @file UGraph.h
 @author Greg Lee
 @version 1.0.0
 @brief: "Undirected Graphs with nodes and edges"
 
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

#define UGraph_vertex_struct( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_struct )

#define UGraph_edge_struct( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_struct )

#define UGraph_cursor_struct( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_struct )


#define UGraph_type( arg ) PRIMITIVE_CAT( arg, _ugraph_t )

#define UGraph_vertex_type( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_t )

#define UGraph_edge_type( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_t )

#define UGraph_cursor_type( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_t )

/** 
   Structure declarations
*/

struct UGraph_struct( Prefix );
struct UGraph_vertex_struct( Prefix );
struct UGraph_edge_struct( Prefix );
struct UGraph_cursor_struct( Prefix );

/**
   Structure typedefs
*/

typedef struct UGraph_struct( Prefix ) UGraph_type( Prefix );
typedef struct UGraph_vertex_struct( Prefix ) UGraph_vertex_type( Prefix );
typedef struct UGraph_edge_struct( Prefix ) UGraph_edge_type( Prefix );
typedef struct UGraph_cursor_struct( Prefix ) UGraph_cursor_type( Prefix );

/**
   Function names below are prepended with "Prefix_".
*/

/** 
   Initialization
*/

/**
   UGraph_make_depth
   
   Return a new UGraph_type( Prefix ) instance with a default number of buckets. Depth first
   search.
   
   @return UGraph_type( Prefix ) instance 
*/
#define UGraph_make_depth( arg ) PRIMITIVE_CAT( arg, _ugraph_make_depth )
UGraph_type( Prefix ) * UGraph_make_depth( Prefix )( void );

/**
   UGraph_make_breadth
   
   Return a new UGraph_type( Prefix ) instance with a default number of buckets. Breadth first
   search.
   
   @return UGraph_type( Prefix ) instance 
*/
#define UGraph_make_breadth( arg ) PRIMITIVE_CAT( arg, _ugraph_make_breadth )
UGraph_type( Prefix ) * UGraph_make_breadth( Prefix )( void );

/**
   UGraph_cursor_make_depth
   
   Return a new UGraph_type( Prefix ) cursor instance that makes depth first searches.
   
   @param  the UGraph_type( Prefix ) instance the new cursor works on 
   @return UGraph_cursor_t instance 
*/
#define UGraph_cursor_make_depth( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_make_depth )
UGraph_cursor_type( Prefix ) * UGraph_cursor_make_depth( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_cursor_make_breadth
   
   Return a new UGraph_type( Prefix ) cursor instance that makes breadth first searches.
   
   @param  the UGraph_type( Prefix ) instance the new cursor works on 
   @return UGraph_cursor_t instance 
*/
#define UGraph_cursor_make_breadth( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_make_breadth )
UGraph_cursor_type( Prefix ) * UGraph_cursor_make_breadth( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_vertex_make
   
   Return a new UGraph_vertex_type( Prefix ) instanc.
   
   @param  the value for the vertex 
   @return UGraph_vertex_type( Prefix ) instance 
*/
#define UGraph_vertex_make( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_make )
UGraph_vertex_type( Prefix ) * UGraph_vertex_make( Prefix )( Value value );


/** 
   Disposal
*/

/**
   UGraph_dispose
   
   Frees a UGraph_type( Prefix ) instance without freeing its contained values and edges.
   
   @param UGraph_type( Prefix ) instance 
*/
#define UGraph_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_dispose )
void UGraph_dispose( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_dispose_with_contents
   
   Frees a UGraph_type( Prefix ) instance and its contained values and edges.
   
   @param UGraph_type( Prefix ) instance 
*/
#define UGraph_dispose_with_contents( arg ) PRIMITIVE_CAT( arg, _ugraph_dispose_with_contents )
void UGraph_dispose_with_contents( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_cursor_dispose
   
   Frees a UGraph_cursor_t instance. Its UGraph is not disposed.
   
   @param UGraph_cursor_t instance 
*/
#define UGraph_cursor_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_dispose )
void UGraph_cursor_dispose( Prefix )( UGraph_cursor_type( Prefix ) *cursor );


/**
   UGraph_vertex_dispose
   
   Frees a UGraph_vertex_type( Prefix ) instance. Its value is not disposed. All edges of vertex
   and their "values" are disposed.
   
   @param  UGraph_vertex_type( Prefix ) instance 
*/
#define UGraph_vertex_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_dispose )
void UGraph_vertex_dispose( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_vertex_type( Prefix ) *vertex );

/**
   UGraph_vertex_dispose_with_contents
   
   Frees a UGraph_vertex_type( Prefix ) instance. Its value is disposed. All edges of vertex
   and their "values" are disposed.
   
   @param  UGraph_vertex_type( Prefix ) instance 
*/
#define UGraph_vertex_dispose_with_contents( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_dispose_with_contents )
void UGraph_vertex_dispose_with_contents( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_vertex_type( Prefix ) *vertex );

/** 
   Access
*/

/**
   UGraph_value
   
   Returns the value of the vertex.
   
   @param  UGraph UGraph_type( Prefix ) instance
   @param  vertex the vertex
   @return  value the new vertex Value
*/
#define UGraph_value( arg ) PRIMITIVE_CAT( arg, _ugraph_value )
Value UGraph_value( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_vertex_type( Prefix ) *vertex );

/**
   UGraph_edge_value_v1_v2
   
   Get the value of the edge defined by the from and to vertices.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  v1 the from vertex of the edge 
   @param   the to vertex of the edge
   @return the value of the edge
*/
#define UGraph_edge_value_v1_v2( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_value_v1_v2 )
Edge UGraph_edge_value_v1_v2( Prefix )
( 
   UGraph_type( Prefix ) *UGraph, 
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) *v2
);

/**
   UGraph_edge_value
   
   Get the value of the edge.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  edge the edge 
   @return the edge value
*/
#define UGraph_edge_value( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_value )
Edge UGraph_edge_value( Prefix )
( 
   UGraph_type( Prefix ) *UGraph, 
   UGraph_edge_type( Prefix ) *edge 
);

/**
   UGraph_edge_v1
   
   Get the value of the edge's vertex_from.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  edge the edge 
   @return the edge's vertex_from
*/
#define UGraph_edge_v1( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_v1 )
UGraph_vertex_type( Prefix ) *UGraph_edge_v1( Prefix )
( 
   UGraph_type( Prefix ) *UGraph, 
   UGraph_edge_type( Prefix ) *edge 
);

/**
   UGraph_edge_v2
   
   Get the value of the edge's vertex_to.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  edge the edge 
   @return the edge's vertex_to
*/
#define UGraph_edge_v2( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_v2 )
UGraph_vertex_type( Prefix ) *UGraph_edge_v2( Prefix )
( 
   UGraph_type( Prefix ) *UGraph, 
   UGraph_edge_type( Prefix ) *edge 
);

/**
   UGraph_cursor_value_at
   
   Returns the value of the vertex that the UGraph_cursor_t instance is pointing to.
   
   @param  UGraph_cursor_t instance 
   @return a Value value
*/
#define UGraph_cursor_value_at( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_value_at )
Value UGraph_cursor_value_at( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_value_at
   
   Returns the value of the vertex that the UGraph_type( Prefix ) instance's internal
   cursor is pointing to.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return a Value value
*/
#define UGraph_value_at( arg ) PRIMITIVE_CAT( arg, _ugraph_value_at )
Value UGraph_value_at( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_cursor_at
   
   Returns the vertex that the UGraph_cursor_t instance is pointing to.
   
   @param  UGraph_cursor_t instance 
   @return a UGraph_vertex_type( Prefix ) vertex
*/
#define UGraph_cursor_at( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_at )
UGraph_vertex_type( Prefix ) *UGraph_cursor_at( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_at
   
   Returns the vertex of the vertex that the UGraph_type( Prefix ) instance's internal
   cursor is pointing to.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return a Value vertex
*/
#define UGraph_at( arg ) PRIMITIVE_CAT( arg, _ugraph_at )
UGraph_vertex_type( Prefix ) *UGraph_at( Prefix )( UGraph_type( Prefix ) *ugraph );


/**
   UGraph_as_array
   
   Returns array of vertices in the UGraph_type( Prefix ) instance. The vertices are not copied.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return array of vertices in UGraph instance
*/
#define UGraph_as_array( arg ) PRIMITIVE_CAT( arg, _ugraph_as_array )
UGraph_vertex_type( Prefix ) ** UGraph_as_array( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_cursor_edge_value_at
   
   Returns the edge value of the edge that the UGraph_cursor_t instance is pointing to.
   
   @param  UGraph_cursor_t instance 
   @return a Edge value
*/
#define UGraph_cursor_edge_value_at( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_edge_value_at )
Edge UGraph_cursor_edge_value_at( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_edge_value_at
   
   Returns the value of the edge that the UGraph_type( Prefix ) instance's internal
   cursor is pointing to.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return a Edge value
*/
#define UGraph_edge_value_at( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_value_at )
Edge UGraph_edge_value_at( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_cursor_edge_at
   
   Returns the edge that the UGraph_cursor_t instance is pointing to.
   
   @param  UGraph_cursor_t instance 
   @return a UGraph_edge_type( Prefix ) edge
*/
#define UGraph_cursor_edge_at( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_edge_at )
UGraph_edge_type( Prefix ) *UGraph_cursor_edge_at( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_edge_at
   
   Returns the edge that the UGraph_type( Prefix ) instance's internal
   cursor is pointing to.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return a edge
*/
#define UGraph_edge_at( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_at )
UGraph_edge_type( Prefix ) *UGraph_edge_at( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_edge_v1_v2
   
   Returns the edge that the UGraph_type( Prefix ) instance's internal
   cursor is pointing to.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return a edge
*/
#define UGraph_edge_v1_v2( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_v1_v2 )
UGraph_edge_type( Prefix ) *UGraph_edge_v1_v2( Prefix )
( 
   UGraph_type( Prefix ) *ugraph, 
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) *
);

/**
   UGraph_edges_as_array
   
   Returns array of edges in the UGraph_type( Prefix ) instance. The edges are not copied.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return array of edges in UGraph instance
*/
#define UGraph_edges_as_array( arg ) PRIMITIVE_CAT( arg, _ugraph_edges_as_array )
UGraph_edge_type( Prefix ) ** UGraph_edges_as_array( Prefix )( UGraph_type( Prefix ) *ugraph );

/** 
   Measurement
*/

/**
   UGraph_count
   
   Returns the number of vertices in the UGraph_type( Prefix ) instance.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return number of vertices in UGraph instance
*/
#define UGraph_count( arg ) PRIMITIVE_CAT( arg, _ugraph_count )
int32_t UGraph_count( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_edge_count
   
   Returns the number of edges in the UGraph_type( Prefix ) instance.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return number of edges in UGraph instance
*/
#define UGraph_edge_count( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_count )
int32_t UGraph_edge_count( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_are_adjacent
   
   Returns 1 if vertices v1 and v2 are connected with edge from v1 to v2, 
   otherwise 0.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return 1 if vertices are adjacent, otherwise 0
*/
#define UGraph_are_adjacent( arg ) PRIMITIVE_CAT( arg, _ugraph_are_adjacent )
int32_t UGraph_are_adjacent( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_vertex_type( Prefix ) *v1, UGraph_vertex_type( Prefix ) *v2 );


/** 
   Status report
*/

/**
   UGraph_off
   
   Returns 1 if the UGraph_type( Prefix ) instance's internal cursor is off, otherwise 0.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return 1 if internal cursor is off, otherwise 0
*/
#define UGraph_off( arg ) PRIMITIVE_CAT( arg, _ugraph_off )
int32_t UGraph_off( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_cursor_off
   
   Returns 1 if the UGraph_cursor_t instance is off, otherwise 0.
   
   @param  cursor UGraph_cursor_t instance 
   @return 1 if internal cursor is off, otherwise 0
*/
#define UGraph_cursor_off( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_off )
int32_t UGraph_cursor_off( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_is_empty
   
   Returns true if no vertices are in the UGraph_type( Prefix ) instance.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return is the the UGraph instance empty?
   
*/
#define UGraph_is_empty( arg ) PRIMITIVE_CAT( arg, _ugraph_is_empty )
int32_t UGraph_is_empty( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_edge_off
   
   Returns 1 if the UGraph_type( Prefix ) instance's internal edge cursor is 
   off, otherwise 0.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return 1 if internal edge cursor is off, otherwise 0
*/
#define UGraph_edge_off( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_off )
int32_t UGraph_edge_off( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_cursor_edge_off
   
   Returns 1 if the UGraph_cursor_t edge instance is off, otherwise 0.
   
   @param  cursor UGraph_cursor_t instance 
   @return 1 if internal cursor is off, otherwise 0
*/
#define UGraph_cursor_edge_off( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_edge_off )
int32_t UGraph_cursor_edge_off( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_edge_is_empty
   
   Returns true if no edges are in the UGraph_type( Prefix ) instance.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return is the the UGraph instance empty?
   
*/
#define UGraph_edge_is_empty( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_is_empty )
int32_t UGraph_edge_is_empty( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_is_connected
   
   Returns true if there is a path between all vertices in the UGraph_type( Prefix ) instance.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @return are all vertices in the the UGraph instance connected?
   
*/
#define UGraph_is_connected( arg ) PRIMITIVE_CAT( arg, _ugraph_is_connected )
int32_t UGraph_is_connected( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_has
   
   Returns 1 if the UGraph_type( Prefix ) instance contains the vertex, otherwise 0.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  vertex the vertex to search for 
   @return 1 if UGraph has value, otherwise 0
*/
#define UGraph_has( arg ) PRIMITIVE_CAT( arg, _ugraph_has )
int32_t UGraph_has( Prefix )( UGraph_type( Prefix ) *UGraph, UGraph_vertex_type( Prefix ) *vertex );

/**
   UGraph_edge_has
   
   Returns 1 if the UGraph_type( Prefix ) instance contains the edge, otherwise 0.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  edge the edge to search for 
   @return 1 if UGraph has value, otherwise 0
*/
#define UGraph_edge_has( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_has )
int32_t UGraph_edge_has( Prefix )( UGraph_type( Prefix ) *UGraph, UGraph_edge_type( Prefix ) *edge );

/**
   UGraph_has_value
   
   Returns 1 if the UGraph_type( Prefix ) instance contains a vertex with the value, otherwise 0.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  value the value to search for 
   @return 1 if UGraph has value, otherwise 0
*/
#define UGraph_has_value( arg ) PRIMITIVE_CAT( arg, _ugraph_has_value )
int32_t UGraph_has_value( Prefix )( UGraph_type( Prefix ) *UGraph, Value value );

/**
   UGraph_edge_has_value
   
   Returns 1 if the UGraph_type( Prefix ) instance contains an edge with the edge value, otherwise 0.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  edge the edge value to search for 
   @return 1 if UGraph has edge value, otherwise 0
*/
#define UGraph_edge_has_value( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_has_value )
int32_t UGraph_edge_has_value( Prefix )( UGraph_type( Prefix ) *UGraph, Edge edge );

/**
   UGraph_neighbors
   
   Returns array of vertices that the vertex is connected to by an edge.
   
   @param  UGraph UGraph_type( Prefix ) instance
   @param  vertex the vertex to look at
   @return array of vertices
*/
#define UGraph_neighbors( arg ) PRIMITIVE_CAT( arg, _ugraph_neighbors )
UGraph_vertex_type( Prefix ) ** UGraph_neighbors( Prefix )( UGraph_type( Prefix ) *ugraph, UGraph_vertex_type( Prefix ) *vertex );

/** 
   Cursor movement
*/

/**
   UGraph_cursor_forth
   
   Moves the UGraph_cursor_t instance to the next item or off.
   
   @param  UGraph_cursor UGraph_cursor_t instance 
*/
#define UGraph_cursor_forth( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_forth )
void UGraph_cursor_forth( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_cursor_start
   
   Moves the UGraph_cursor_t instance to the first item or off if the UGraph is empty.
   
   @param  UGraph_cursor UGraph_cursor_t instance 
*/
#define UGraph_cursor_start( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_start )
void UGraph_cursor_start( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_forth
   
   Moves the UGraph_type( Prefix ) instance internal cursor to the next item or off.
   
   @param  UGraph UGraph_type( Prefix ) instance 
*/
#define UGraph_forth( arg ) PRIMITIVE_CAT( arg, _ugraph_forth )
void UGraph_forth( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_start
   
   Moves the UGraph_type( Prefix ) instance's internal cursor to the first item or off if the UGraph is empty.
   
   @param  UGraph UGraph_type( Prefix ) instance 
*/
#define UGraph_start( arg ) PRIMITIVE_CAT( arg, _ugraph_start )
void UGraph_start( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_find_value
   
   Returns vertex if search finds a vertex with value in the UGraph_type( Prefix ) instance, 
   otherwise null. Starts at "start". If found, internal cursor points to vertex,
   search paused at that point.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  value the value to search for 
   @return vertex if search found vertex with value in UGraph, otherwise null
*/
#define UGraph_find_value( arg ) PRIMITIVE_CAT( arg, _ugraph_find_value )
UGraph_vertex_type( Prefix ) *UGraph_find_value( Prefix )( UGraph_type( Prefix ) *UGraph, Value value );

/**
   UGraph_find_next_value
   
   Returns vertex if search finds a vertex with value in the UGraph_type( Prefix ) instance 
   starting where the last search ended, otherwise null. Starts at internal cursor 
   current position. If found internal cursor points to vertex, search paused at
   that point.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  value the value to search for 
   @return vertex if search found vertex with value in UGraph, otherwise null
*/
#define UGraph_find_next_value( arg ) PRIMITIVE_CAT( arg, _ugraph_find_next_value )
UGraph_vertex_type( Prefix ) *UGraph_find_next_value( Prefix )( UGraph_type( Prefix ) *UGraph, Value value );

/**
   UGraph_cursor_find_value
   
   Returns vertex if search finds a vertex with value in the UGraph_type( Prefix ) instance, 
   otherwise null. Starts at "start". If found, internal cursor points to vertex,
   search paused at that point.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  value the value to search for 
   @return vertex if search found vertex with value in UGraph, otherwise null
*/
#define UGraph_cursor_find_value( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_find_value )
UGraph_vertex_type( Prefix ) *UGraph_cursor_find_value( Prefix )( UGraph_cursor_type( Prefix ) *UGraph, Value value );

/**
   UGraph_cursor_find_next_value
   
   Returns vertex if search finds a vertex with value in the UGraph_type( Prefix ) instance 
   starting where the last search ended, otherwise null. Starts at internal cursor 
   current position. If found internal cursor points to vertex, search paused at
   that point.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  value the value to search for 
   @return vertex if search found vertex with value in UGraph, otherwise null
*/
#define UGraph_cursor_find_next_value( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_find_next_value )
UGraph_vertex_type( Prefix ) *UGraph_cursor_find_next_value( Prefix )( UGraph_cursor_type( Prefix ) *UGraph, Value value );


/**
   UGraph_cursor_edge_forth
   
   Moves the UGraph_cursor_t instance to the next edge item or off.
   
   @param  UGraph_cursor UGraph_cursor_t instance 
*/
#define UGraph_cursor_edge_forth( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_edge_forth )
void UGraph_cursor_edge_forth( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_cursor_edge_start
   
   Moves the UGraph_cursor_t instance to the first edge or off if the UGraph is empty.
   
   @param  UGraph_cursor UGraph_cursor_t instance 
*/
#define UGraph_cursor_edge_start( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_edge_start )
void UGraph_cursor_edge_start( Prefix )( UGraph_cursor_type( Prefix ) *cursor );

/**
   UGraph_edge_forth
   
   Moves the UGraph_type( Prefix ) instance internal cursor to the next edge or off.
   
   @param  UGraph UGraph_type( Prefix ) instance 
*/
#define UGraph_edge_forth( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_forth )
void UGraph_edge_forth( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_edge_start
   
   Moves the UGraph_type( Prefix ) instance's internal cursor to the first edge 
   or off if the UGraph is empty.
   
   @param  UGraph UGraph_type( Prefix ) instance 
*/
#define UGraph_edge_start( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_start )
void UGraph_edge_start( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_edge_find_value
   
   Returns edge if search finds an edge with value in the UGraph_type( Prefix ) instance, 
   otherwise null. Starts at "start". If found, internal cursor points to edge,
   search paused at that point.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  value the edge value to search for 
   @return edge if search found edge with value in UGraph, otherwise null
*/
#define UGraph_edge_find_value( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_find_value )
UGraph_edge_type( Prefix ) *UGraph_edge_find_value( Prefix )( UGraph_type( Prefix ) *UGraph, Edge value );

/**
   UGraph_edge_find_next_value
   
   Returns edge if search finds an edge with value in the UGraph_type( Prefix ) instance 
   starting where the last search ended, otherwise null. Starts at internal cursor 
   current position. If found internal cursor points to edge, search paused at
   that point.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  value the edge value to search for 
   @return edge if search found edge with value in UGraph, otherwise null
*/
#define UGraph_edge_find_next_value( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_find_next_value )
UGraph_edge_type( Prefix ) *UGraph_edge_find_next_value( Prefix )( UGraph_type( Prefix ) *UGraph, Edge value );

/**
   UGraph_cursor_edge_find_value
   
   Returns edge if search finds an edge with value in the UGraph_type( Prefix ) instance, 
   otherwise null. Starts at "start". If found, internal cursor points to edge,
   search paused at that point.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  value the edge value to search for 
   @return vertex if search found vertex with value in UGraph, otherwise null
*/
#define UGraph_cursor_edge_find_value( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_edge_find_value )
UGraph_edge_type( Prefix ) *UGraph_cursor_edge_find_value( Prefix )( UGraph_cursor_type( Prefix ) *UGraph, Edge value );

/**
   UGraph_cursor_edge_find_next_value
   
   Returns edge if search finds an edge with value in the UGraph_type( Prefix ) instance 
   starting where the last search ended, otherwise null. Starts at internal cursor 
   current position. If found internal cursor points to edge, search paused at
   that point.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  value the edge value to search for 
   @return edge if search found edge with value in UGraph, otherwise null
*/
#define UGraph_cursor_edge_find_next_value( arg ) PRIMITIVE_CAT( arg, _ugraph_cursor_edge_find_next_value )
UGraph_edge_type( Prefix ) *UGraph_cursor_edge_find_next_value( Prefix )( UGraph_cursor_type( Prefix ) *UGraph, Edge value );

/**
   Miscellaneous
*/

/**
   UGraph_vertex_set_bucket_count
   
   Sets bucket count of internal hash sets of vertices. 
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  bucket_count number of hash buckets to set to (should be prime number) 
*/
#define UGraph_vertex_set_bucket_count( arg ) PRIMITIVE_CAT( arg, _ugraph_vertex_set_bucket_count )
void UGraph_vertex_set_bucket_count( Prefix )( UGraph_type( Prefix ) *UGraph, int32_t bucket_count );

/**
   UGraph_edge_set_bucket_count
   
   Sets bucket count of internal hash sets of edges. 
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  bucket_count number of hash buckets to set to (should be prime number) 
*/
#define UGraph_edge_set_bucket_count( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_set_bucket_count )
void UGraph_edge_set_bucket_count( Prefix )( UGraph_type( Prefix ) *UGraph, int32_t bucket_count );


/** 
   Element change
*/

/**
   UGraph_put
   
   Put the vertex into the UGraph_type( Prefix ) instance. Does not alter or add edges.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  vertex the vertex to insert 
*/
#define UGraph_put( arg ) PRIMITIVE_CAT( arg, _ugraph_put )
void UGraph_put( Prefix )( UGraph_type( Prefix ) *UGraph, UGraph_vertex_type( Prefix ) *vertex );

/**
   UGraph_edge_put
   
   Put the edge into the UGraph_type( Prefix ) instance.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  edge the edge to insert 
   @param  v1 the "from" vertex for the edge 
   @param   "to" vertex for the edge 
*/
#define UGraph_edge_put( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_put )
void UGraph_edge_put( Prefix )
( 
   UGraph_type( Prefix ) *UGraph, 
   Edge edge,
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) * 
);

/**
   UGraph_set_value
   
   Set the vertex' value.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  vertex the vertex to insert 
   @param  value the new value for the 
*/
#define UGraph_set_value( arg ) PRIMITIVE_CAT( arg, _ugraph_set_value )
void UGraph_set_value( Prefix )
(
   UGraph_type( Prefix ) *UGraph, 
   UGraph_vertex_type( Prefix ) *vertex,
   Value value
);

/**
   UGraph_edge_set
   
   Set the value of the edge.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  v1 the from vertex of the edge 
   @param   the to vertex of the edge
   @param  edge the new value for the edge
*/
#define UGraph_edge_set( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_set )
void UGraph_edge_set( Prefix )
( 
   UGraph_type( Prefix ) *UGraph, 
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) *,
   Edge edge
);

/**
   UGraph_edge_set_value
   
   Set the value of the edge.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  edge the edge 
   @param  edge the new value for the edge
*/
#define UGraph_edge_set_value( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_set_value )
void UGraph_edge_set_value( Prefix )
( 
   UGraph_type( Prefix ) *UGraph, 
   UGraph_edge_type( Prefix ) *edge, 
   Edge edge_value
);


/** 
   Removal
*/

/**
   UGraph_remove
   
   Remove the vertex from the UGraph_type( Prefix ) instance. All edges that connect to vertex 
   are disposed. Their edge values are not disposed of. The vertex is not disposed.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  vertex the vertex to dispose 
*/
#define UGraph_remove( arg ) PRIMITIVE_CAT( arg, _ugraph_remove )
void UGraph_remove( Prefix )( UGraph_type( Prefix ) *UGraph, UGraph_vertex_type( Prefix ) *vertex );

/**
   UGraph_remove_and_dispose
   
   Remove the vertex from the UGraph_type( Prefix ) instance All edges that connect to vertex 
   and their edge values are disposed of. The vertex and its value is disposed.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  vertex the vertex to dispose 
*/
#define UGraph_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_remove_and_dispose )
void UGraph_remove_and_dispose( Prefix )( UGraph_type( Prefix ) *UGraph, UGraph_vertex_type( Prefix ) *vertex );

/**
   UGraph_edge_remove_v1_v2
   
   Remove and dispose the edge from the UGraph_type( Prefix ) instance. The edge value is 
   not disposed.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  v1 the from vertex of the edge 
   @param   the to vertex of the edge 
*/
#define UGraph_edge_remove_v1_v2( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_remove_v1_v2 )
void UGraph_edge_remove_v1_v2( Prefix )
( 
   UGraph_type( Prefix ) *UGraph, 
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) *
);

/**
   UGraph_edge_remove_and_dispose_
   
   Remove and dispose the edge from the UGraph_type( Prefix ) instance.The edge value is 
   disposed.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  v1 the from vertex of the edge 
   @param   the to vertex of the edge 
*/
#define UGraph_edge_remove_and_dispose_v1_v2( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_remove_and_dispose_v1_v2 )
void UGraph_edge_remove_and_dispose_v1_v2( Prefix )
( 
   UGraph_type( Prefix ) *UGraph, 
   UGraph_vertex_type( Prefix ) *v1, 
   UGraph_vertex_type( Prefix ) *
);

/**
   UGraph_edge_remove
   
   Remove and dispose the edge from the UGraph_type( Prefix ) instance. The edge value is 
   not disposed.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  edge the edge to remove 
*/
#define UGraph_edge_remove( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_remove )
void UGraph_edge_remove( Prefix )
( 
   UGraph_type( Prefix ) *UGraph, 
   UGraph_edge_type( Prefix ) *edge 
);

/**
   UGraph_edge_remove_and_dispose
   
   Remove and dispose the edge from the UGraph_type( Prefix ) instance.The edge value is 
   disposed.
   
   @param  UGraph UGraph_type( Prefix ) instance 
   @param  edge the edge to remove
*/
#define UGraph_edge_remove_and_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_remove_and_dispose )
void UGraph_edge_remove_and_dispose( Prefix )
( 
   UGraph_type( Prefix ) *UGraph, 
   UGraph_edge_type( Prefix ) *edge
);

/**
   UGraph_wipe_out
   
   Remove all vertices and edges in the UGraph_type( Prefix ) instance. The edge and vertex
   structures are not disposed.
   
   @param  UGraph UGraph_type( Prefix ) instance 
*/
#define UGraph_wipe_out( arg ) PRIMITIVE_CAT( arg, _ugraph_wipe_out )
void UGraph_wipe_out( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_wipe_out_and_dispose
   
   Remove all vertices and edges in the UGraph_type( Prefix ) instance. Dispose of all 
   vertices and edges and their values.
   
   @param  UGraph UGraph_type( Prefix ) instance 
*/
#define UGraph_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_wipe_out_and_dispose )
void UGraph_wipe_out_and_dispose( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_edge_wipe_out
   
   Remove all edges in the UGraph_type( Prefix ) instance. The edge
   structures are not disposed.
   
   @param  UGraph UGraph_type( Prefix ) instance 
*/
#define UGraph_edge_wipe_out( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_wipe_out )
void UGraph_edge_wipe_out( Prefix )( UGraph_type( Prefix ) *ugraph );

/**
   UGraph_edge_wipe_out_and_dispose
   
   Remove all edges in the UGraph_type( Prefix ) instance. Dispose of all 
   edges and their values.
   
   @param  UGraph UGraph_type( Prefix ) instance 
*/
#define UGraph_edge_wipe_out_and_dispose( arg ) PRIMITIVE_CAT( arg, _ugraph_edge_wipe_out_and_dispose )
void UGraph_edge_wipe_out_and_dispose( Prefix )( UGraph_type( Prefix ) *ugraph );

#ifdef __cplusplus
}
#endif

/* End of file */



