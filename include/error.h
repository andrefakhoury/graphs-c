#ifndef ERROR_H
#define ERROR_H

#include <stdbool.h>

/** Tells if an error has occurred and its cause. */
typedef struct {
    bool occurred;
    char msg[2048];
} Error;

#endif