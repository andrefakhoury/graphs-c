#include "queue.h"
#include "graph.h"
#include "wavefront.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

/* Defining constants for the colors of the characters. */
#define RED "\x1B[1;31m"
#define YEL   "\x1B[01;33m"
#define RESET "\x1B[0m"

/* Function that implements the wavefront method using BFS. */
void graph_waveFront(Graph* g, int x, int y, Error* error) {
	Queue* q = create();
	push(q, x, y);

	while(!empty(q)) {
		int atX = q->x[q->begin];
		int atY = q->y[q->begin];
		pop(q);

		int cnt = *((int*)graph_edgeWeight(g, atX, atY, error)) + 1;

        /* The west values of wavefront are setted */
		if ((atX-1) >= 0 && *((int*)graph_edgeWeight(g, atX-1, atY, error)) == -1) {
			graph_addEdge(g, atX-1, atY, &cnt, error);
			push(q, atX-1, atY);
		}
        /* The lest values of wavefront are setted */
		if ((atX+1) < 5 && *((int*)graph_edgeWeight(g, atX+1, atY, error)) == -1) {
			graph_addEdge(g, atX+1, atY, &cnt, error);
			push(q, atX+1, atY);
		}
        /* The north values of wavefront are setted */
		if ((atY-1) >= 0 && *((int*)graph_edgeWeight(g, atX, atY-1, error)) == -1) {
			graph_addEdge(g, atX, atY-1, &cnt, error);
			push(q, atX, atY-1);
		}
        /* The south values of wavefront are setted */
		if ((atY+1) < 5 && *((int*)graph_edgeWeight(g, atX, atY+1, error)) == -1) {
			graph_addEdge(g, atX, atY+1, &cnt, error);
			push(q, atX, atY+1);
		}
	}
	
	free_queue(q);
}

/* Function responsible for the movement of the characters in the game. */
void graph_walk(Graph* g, int px, int py, int gx, int gy, Error* error) {    
    int flag, zero, min, nx, ny;

    /* Ensuring number's randomness */
    srand(time(NULL));
    
    while (px != gx || py != gy) { /* While Pac Man does not reach the ghost */
        int ghost = 1+rand()%4;

        graph_empty(g, error); /* Reinitializing values of the graph */
        flag = 0;

        /* The ghost goes to west */
        if (ghost == 1 && gx-1 >= 0 && px != gx && py != gy)
            gx--, flag = 1;
        /* The ghost goes to south */
        else if (ghost == 2 && gy+1 < 5 && px != gx && py != gy)
            gy++, flag = 1;
        /* The ghost goes to east */
        else if (ghost == 3 && gx+1 < 5 && px != gx && py != gy)
            gx++, flag = 1;
        /* The ghost goes to north */
        else if (ghost == 4 && gy-1 >= 0 && px != gx && py != gy)
            gy--, flag = 1;
    
        /* Inserting the position of the ghost in the graph */
        zero = 0;
        graph_addEdge(g, gx, gy, &zero, error);

        /* Generating the wavefront */
        graph_waveFront(g, gx, gy, error);

        /* Only if the ghost has changed position the map is reprinted */
        if(flag) print_screen(g, px, py, gx, gy, error); 

        /* Setting values */
        min = 1000;
        nx = 0;
        ny = 0;

        /* Pac Man goes to Lest */
        if (px+1 < 5 && *((int*)graph_edgeWeight(g, px+1, py, error)) < min) {
            min = *((int*)graph_edgeWeight(g, px+1, py, error));
            nx = px+1;
            ny = py;
        }
        /* Pac Man goes to West */
        if (px-1 >= 0 && *((int*)graph_edgeWeight(g, px-1, py, error)) < min) {
            min = *((int*)graph_edgeWeight(g, px-1, py, error));
            nx = px-1;
            ny = py;
        }
        /* Pac Man goes to South */
        if (py+1 < 5 && *((int*)graph_edgeWeight(g, px, py+1, error)) < min) {
            min = *((int*)graph_edgeWeight(g, px, py+1, error));
            nx = px;
            ny = py+1;
        }
        /* Pac Man goes to North */
        if (py-1 >= 0 && *((int*)graph_edgeWeight(g, px, py-1, error)) < min) {
            min = *((int*)graph_edgeWeight(g, px, py-1, error));
            nx = px;
            ny = py-1;
        }     
        
        px = nx;
        py = ny;
        
        /* Sending the moves to the screen */
        print_screen(g, px, py, gx, gy, error);
    }
}

/* Function that initializes the values of the graph with -1. */
void graph_empty(Graph* g, Error* error) {
    int empty = -1;
    for (int i = 0; i < 5; i++) 
        for(int j = 0; j < 5; j++) 
            graph_addEdge(g, i, j, &empty, error);

}

/* Function that prints the game board, overwriting the data with each new move. */
void print_screen(Graph* g, int px, int py, int gx, int gy, Error* error) {
    static int flag = 0;

    /* Overwriting the data */
    for(int i = 0; flag && i < 5; ++i)
        printf("\033[F");

    /* Printing the game */
    flag = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == px && j == py) 
                printf(YEL "P " RESET);
            else if (i == gx && j == gy) 
                printf(RED "G " RESET);
            else 
                printf(". ");
                // printf("%d ", *((int*)graph_edgeWeight(g, i, j, error)));
        }
        printf("\n");
    }
    
    // printf("\n");
    fflush(stdout);
    sleep(1); /* Generating a delay in printing */

    /* PS: if the commented lines of code are uncommented, one can see the wavefront algorithm acting. */
}

