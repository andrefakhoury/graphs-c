#include "graph.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
	Error error;
	Graph* g = graph_create(5, sizeof(int), false, &error);

	int w = 1;

	/* Graph 1 */
	graph_addEdge(g, 1, 0, &w, &error);
	graph_addEdge(g, 0, 3, &w, &error);
	graph_addEdge(g, 3, 4, &w, &error);
	graph_addEdge(g, 4, 0, &w, &error);
	graph_addEdge(g, 0, 2, &w, &error);
	graph_addEdge(g, 2, 1, &w, &error);

	/* Graph 2 */
	// graph_addEdge(g, 1, 2, &w, &error);
	// graph_addEdge(g, 1, 4, &w, &error);
	// graph_addEdge(g, 1, 3, &w, &error);
	// graph_addEdge(g, 1, 5, &w, &error);
	// graph_addEdge(g, 2, 4, &w, &error);
	// graph_addEdge(g, 3, 4, &w, &error);
	// graph_addEdge(g, 3, 5, &w, &error);
	// graph_addEdge(g, 3, 6, &w, &error);
	// graph_addEdge(g, 4, 6, &w, &error);

	/* Graph 3 */
	// graph_addEdge(g, 0, 1, &w, &error);
	// graph_addEdge(g, 0, 2, &w, &error);
	// graph_addEdge(g, 1, 2, &w, &error);
	// graph_addEdge(g, 1, 3, &w, &error);
	// graph_addEdge(g, 1, 4, &w, &error);
	// graph_addEdge(g, 3, 4, &w, &error);

	int* circuit = calloc(1, sizeof(int));
	int circuitSize = 0;
	graph_eulerianCircuit(g, &circuit, &circuitSize, &error);

	if (error.occurred) {
		printf("%s\n", error.msg);
		return 1;
	}

	for (int i = 0; i < circuitSize; i++)
		printf("%d ", circuit[i]);
	printf("\n");

	graph_destroy(g, &error);
	free(circuit);
}