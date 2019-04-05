#ifndef GRAPH_H
#define GRAPH_H

#include "error.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct Graph Graph;

/** Create and return a graph with nVertex vertex. */
Graph* graph_create(size_t nVertex, size_t elemSize, bool directed, Error* error);

/** Free the memory usage of the graph */
void graph_destroy(Graph* g, Error* error);

/** Returns a copy of the graph g */
Graph* graph_copy(Graph* g, Error* error);

/** Adds the edge u->v on the graph. */
void graph_addEdge(Graph* g, int u, int v, void* w, Error* error);

/** Removes the edge u->v from a graph. */
void graph_removeEdge(Graph* g, int u, int v, Error* error);

/** Returns the degree of a vertex */
int graph_degreeOfVertex(Graph* g, int u, Error* error);

/** Returns the next vertex adjacent to u, in range [first, nVertex) */
int graph_nextAdj(Graph* g, int u, int first, Error* error);

/** Returns whether an edge u-v is a bridge. */
bool graph_isBridge(Graph* g, int u, int v, Error* error);

/** Returns the number of edges on a graph */
int graph_qttEdges(Graph* g, Error* error);

/** Checks and fill the eulerian circuit if possible. */
void graph_eulerianCircuit(Graph* g, int** circuit, int* circuitSize, Error* error);

/** Returns a pointer to the weight of the edge u->v. */
void* graph_edgeWeight(Graph* g, int u, int v, Error* error);

/** Returns whether the vertex is connected to another one */
bool graph_vertexIsUsed(Graph* g, int u, Error* error);

/** Returns whether the edge u->v exists in the graph */
bool graph_edgeIsSet(Graph* g, int u, int v, Error* error);

#endif
