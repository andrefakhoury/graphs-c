#include "graph.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct EdgeNode {
	
} EdgeNode;

/** Struct of a graph with adjacency List */
struct Graph {
	void*** mat;
	size_t nVertex, elemSize;
	bool directed;
};
