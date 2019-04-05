#ifndef WAVEFRONT_H
#define WAVEFRONT_H

/* Function that implements the wavefront method using BFS. */
void graph_waveFront(Graph* g, int x, int y, Error* error);

/* Function responsible for the movement of the characters in the game. */
void graph_walk(Graph* g, int px, int py, int gx, int gy, Error* error);

/* Function that initializes the values of the graph with -1. */
void graph_empty(Graph* g, Error* error);

/* Function that prints the game board, overwriting the data with each new move. */
void print_screen(Graph* g, int px, int py, int gx, int gy, Error* error);

#endif
