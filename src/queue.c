#include "queue.h"

/* Function that creates a queue. */
Queue* create(void) {
	Queue* q = (Queue*) malloc(sizeof(Queue));
	q->begin = q->end = 0;
	return q;
} 

/* Auxiliary function that performs an increment in a given number.*/
int incr(int i) {
	return (i+1)%1000;
}

/* Function that pushes elements in the stack. */
void push(Queue* q, int x, int y) {
	if (incr(q->end) == q->begin) exit (1); // capacidade esgotada
	
	q->x[q->end] = x;
	q->y[q->end] = y;
	
	q->end = incr(q->end); 
}

/* Function that pops elements in the stack. */
void pop(Queue* q) {
	q->begin = incr(q->begin);
}

/* Function that checks if the stack is empty. */
int empty(Queue* q) {
	return (q->begin == q->end);
}

/* Funtion that frees the allocated memory for the stack. */
void free_queue(Queue* q) {
	free(q);
}
