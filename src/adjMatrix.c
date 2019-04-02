#include "graph.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/** Macro for an empty element of the matrix */
#define EMPTY NULL

/** Struct of a graph with adjacency Matrix */
struct Graph {
	void*** mat;

	size_t nVertex, elemSize;
	bool directed;
};

/** Create and return a graph with nVertex vertex. */
Graph* graph_create(size_t nVertex, size_t elemSize, bool directed, Error* error) {
	Graph* g = malloc(sizeof(Graph));
	if (g == NULL) {
		error->occurred = true;
		strcpy(error->msg, "No space for allocation.");
		return NULL;
	}

	g->nVertex = nVertex;
	g->directed = directed;
	g->elemSize = elemSize;

	g->mat = malloc(nVertex * sizeof(void**));
	if (g->mat == NULL) {
		error->occurred = true;
		strcpy(error->msg, "No space for allocation.");
		return NULL;
	}

	for (int i = 0; i < nVertex; i++) {
		g->mat[i] = malloc(nVertex * sizeof(void*));
		if (g->mat[i] == NULL) {
			error->occurred = true;
			strcpy(error->msg, "No space for allocation.");
			return NULL;
		}

		for (int j = 0; j < nVertex; j++) {
			g->mat[i][j] = EMPTY;
		}
	}

	error->occurred = false;
	return g;
}

/** Free the memory usage of the graph */
void graph_destroy(Graph* g, Error* error) {
	if (g != NULL) {
		if (g->mat != NULL) {
			for (int i = 0; i < g->nVertex; i++) {
				if (g->mat[i] != NULL) {
					for (int j = 0; j < g->nVertex; j++) {
						if (g->mat[i][j] != EMPTY)
							free(g->mat[i][j]);
					}
				}
				free(g->mat[i]);
			}
			free(g->mat);
		}
		free(g);
	}
}

/** Returns a copy of the graph g */
Graph* graph_copy(Graph* g, Error* error) {
	if (g == NULL) {
		error->occurred = true;
		strcpy(error->msg, "The original graph is null.");
		return NULL;
	}

	Graph* r = graph_create(g->nVertex, g->elemSize, g->directed, error);
	if (error->occurred) {
		return NULL;
	}

	r->elemSize = g->elemSize;
	r->nVertex = g->nVertex;
	r->directed = g->directed;

	for (int u = 0; u < g->nVertex; u++) {
		for (int v = 0; v < g->nVertex; v++) {
			if (g->mat[u][v] != NULL) {
				r->mat[u][v] = malloc(r->elemSize);
				memcpy(r->mat[u][v], g->mat[u][v], r->elemSize);
			}
		}
	}

	return r;
}

/** Adds the edge u->v on the graph. */
void graph_addEdge(Graph* g, int u, int v, void* w, Error* error) {
	if (u >= g->nVertex || v >= g->nVertex) {
		error->occurred = true;
		strcpy(error->msg, "Invalid vertex number.");
		return;
	}

	error->occurred = false;

	if (g->mat[u][v] != EMPTY) {
		graph_removeEdge(g, u, v, error);
	}

	g->mat[u][v] = malloc(g->elemSize);
	memcpy(g->mat[u][v], w, g->elemSize);

	if (!g->directed) {
		g->mat[v][u] = malloc(g->elemSize);
		memcpy(g->mat[v][u], w, g->elemSize);
	}
}

/** Removes the edge u->v from a graph. */
void graph_removeEdge(Graph* g, int u, int v, Error* error) {
	if (u >= g->nVertex || v >= g->nVertex) {
		error->occurred = true;
		strcpy(error->msg, "Invalid vertex number.");
		return;
	}

	error->occurred = false;

	if (g->mat[u][v] != EMPTY) {
		free(g->mat[u][v]);
		g->mat[u][v] = EMPTY;
	}

	if (!g->directed && g->mat[v][u] != EMPTY) {
		free(g->mat[v][u]);
		g->mat[v][u] = EMPTY;
	}	
}

/** Returns the degree of a vertex */
int graph_degreeOfVertex(Graph* g, int u, Error* error) {
	if (u >= g->nVertex) {
		error->occurred = true;
		strcpy(error->msg, "Invalid vertex number.");
		return 0;
	}

	error->occurred = false;

	int degree = 0;
	for (int v = 0; v < g->nVertex; v++) {
		if (g->mat[u][v] != EMPTY)
			degree++;
	}

	return degree;
}

/** Returns the next vertex adjacent to u, in range [first, nVertex) */
int graph_nextAdj(Graph* g, int u, int first, Error* error) {
	if (u >= g->nVertex || first >= g->nVertex) {
		error->occurred = true;
		strcpy(error->msg, "Invalid vertex number.");
		return -1;
	}

	error->occurred = false;
	for (int i = first; i < g->nVertex; i++) {
		if (g->mat[u][i] != EMPTY) {
			return i;
		}
	}

	return 0;
}

/** Depth-First search on the graph. */
void graph_dfs(Graph* g, int u, bool* vis) {
	vis[u] = true;

	for (int v = 0; v < g->nVertex; v++) {
		if (g->mat[u][v] != EMPTY && vis[v] == false) {
			graph_dfs(g, v, vis);
		}
	}
}

/** Returns whether an edge u-v is a bridge. */
bool graph_isBridge(Graph* g, int u, int v, Error* error) {
	void* old = malloc(g->elemSize);
	memcpy(old, g->mat[u][v], g->elemSize);

	graph_removeEdge(g, u, v, error);
	if (!g->directed) {
		graph_removeEdge(g, v, u, error);
	}

	bool ans = false;

	bool* vis = calloc(g->nVertex, sizeof(bool));

	int start = 0;
	for (; start < g->nVertex; start++) {
		if (graph_degreeOfVertex(g, start, error) != 0)
			break;
	}

	graph_dfs(g, start, vis);

	for (int i = 0; i < g->nVertex; i++) {
		if (graph_degreeOfVertex(g, i, error) != 0 && !vis[i]) {
			ans = true;
		}
	}

	free(vis);

	graph_addEdge(g, u, v, old, error);
	graph_addEdge(g, v, u, old, error);

	free(old);

	return ans;
}

/** Returns the number of edges on a graph */
int graph_qttEdges(Graph* g, Error* error) {
	if (g == NULL) {
		error->occurred = true;
		strcpy(error->msg, "The graph is null.");
		return 0;
	}

	error->occurred = false;

	int ans = 0;
	for (int u = 0; u < g->nVertex; u++) {
		for (int v = 0; v < g->nVertex; v++) {
			if (g->mat[u][v] != EMPTY) {
				ans++;
			}
		}
	}

	return ans;
}

/** Executes the fleury algorithm to find the Eulerian Circuit of a graph. */
void graph_fleury(Graph* g, int u, int** circuit, int* circuitSize, Error* error) {

	int v = -1;

	if (graph_degreeOfVertex(g, u, error) == 1) {
		v = graph_nextAdj(g, u, 0, error);
	} else {
		v = 0;
		do {
			v = graph_nextAdj(g, u, v+1, error);
		} while (graph_isBridge(g, u, v, error));

	}

	graph_removeEdge(g, u, v, error);

	if (!g->directed) {
		graph_removeEdge(g, v, u, error);
	}

	(*circuitSize)++;
	*circuit = realloc(*circuit, (*circuitSize) * sizeof(int));
	((*circuit)[(*circuitSize)-1]) = v;


	if (graph_qttEdges(g, error) > 0)
		graph_fleury(g, v, circuit, circuitSize, error);
}

/** Checks and fill the eulerian circuit if possible. */
void graph_eulerianCircuit(Graph* g, int** circuit, int* circuitSize, Error* error) {
	if (g->directed) {
		error->occurred = true;
		strcpy(error->msg, "The fleury algorithm only works with bidirected graphs.");
		return;
	}

	error->occurred = false;

	/* Creates a copy of g */
	Graph* g2 = graph_copy(g, error);
	if (error->occurred) {
		graph_destroy(g2, error);

		error->occurred = true;
		strcpy(error->msg, "Error on creating a copy of the graph");

		*circuit = NULL;
		*circuitSize = 0;
		return;
	}

	/* Check the existence conditions. */
	int v1 = -1;
	for (int u = 0; u < g2->nVertex; u++) {
		int deg = graph_degreeOfVertex(g2, u, error);
		if (deg%2 != 0) {
			*circuitSize = 0;
			return;
		}

		if (deg != 0 && v1 == -1) {
			v1 = u;
		}
	}

	(*circuitSize)++;
	*circuit = realloc(*circuit, (*circuitSize) * sizeof(int));
	((*circuit)[(*circuitSize)-1]) = v1;

	graph_fleury(g2, v1, circuit, circuitSize, error);

	graph_destroy(g2, error);
}

/** Returns a pointer to the weight of the edge u->v. */
void* graph_edgeWeight(Graph* g, int u, int v, Error* error) {
	if (g == NULL) {
		error->occurred = true;
		strcpy(error->msg, "Given graph is null.");
		return NULL;
	}

	if (u >= g->nVertex || v >= g->nVertex) {
		error->occurred = true;
		strcpy(error->msg, "Invalid vertex number.");
		return NULL;
	}

	return g->mat[u][v];
}

bool graph_vertexIsUsed(Graph* g, int u, Error* error) {
	//TODO: erro

	int count = 0;
	for (int i = 0; i < g->nVertex; i++) {
		count += g->mat[u][i] != EMPTY;
		count += g->mat[i][u] != EMPTY;
	}

	return count > 0;
}

bool graph_edgeIsSet(Graph* g, int u, int v, Error* error) {
	//TODO: erro

	bool ret = g->mat[u][v] != EMPTY;
	if (g->directed)
		ret |= g->mat[v][u] != EMPTY;

	return ret;
}