#include "graph.h"
#include "error.h"
#include "wavefront.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	int posXPM, posYPM; //Pac man's positions
	int zero = 0;
	Error error;
	Graph* g = graph_create(5, sizeof(int), true , &error);

	// Initializing the graph
	graph_empty(g, &error);

	//Ensuring number's randomness
	srand(time(NULL));

	//Creating ghost's position
	int posXG = rand()%5;
	int posYG = rand()%5;

	//Creating pac man's position
	do {
		posXPM = rand()%5;
	} while (posXPM == posXG || posXPM == posXG+1 || posXPM == posXG-1);
	
	do {
		posYPM = rand()%5;
	} while (posYPM == posYG || posYPM == posYG+1 || posYPM == posYG-1);
	
	//Generating game flow
	graph_addEdge(g, posXG, posYG, &zero, &error);
	graph_waveFront(g, posXG, posYG, &error);
	graph_walk(g, posXPM, posYPM, posXG, posYG, &error);
	graph_destroy(g, &error);

	return 0;
}