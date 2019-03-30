// o que eu vou precisar fazer
#ifndef GRAPH_H
#define GRAPH_H

#include "error.h"
#include <stddef.h>

typedef struct Graph Graph;

Graph* graph_create(size_t nVertex, bool directed, Error* error);

void graph_destroy(Graph* g, Error* error);

/** Adds the edge u->v on the graph. */
void graph_addEdge(Graph* g, int u, int v, void* w, Error* error);

/** Removes the edge u->v from a graph. */
void graph_removeEdge(Graph* g, int u, int v, Error* error);

int graph_degreeOfVertex(Graph* g, int u, Error* error);

int graph_nextAdj(Graph* g, int u, int first, Error* error);

int graph_qttEdges(Graph* g, Error* error);

/** Returns the eulerian circuit if possible, and NULL otherwise. */
void graph_eulerianCircuit(Graph* g, int** circuit, int* circuitSize, Error* error);

#endif