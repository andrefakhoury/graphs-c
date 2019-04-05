#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
	int begin, end; 
	int x[1000], y[1000];
} Queue;

/* Function that creates a queue. */
Queue* create (void);

/* Auxiliary function that performs an increment in a given number.*/
int incr (int i); 

/* Function that pushes elements in the stack. */
void push (Queue* q, int x, int y);

/* Function that pops elements in the stack. */
void pop (Queue* q);

/* Function that checks if the stack is empty. */
int empty (Queue* q); 

/* Funtion that frees the allocated memory for the stack. */
void free_queue (Queue* q);

#endif
