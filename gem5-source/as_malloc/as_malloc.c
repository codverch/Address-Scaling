/*
    * as_malloc.c
    * Allocates scaling_factor * size bytes using malloc
    * Created on: 26-04-2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "as_malloc.h"

int scaling_factor;

// Receives the scaling_factor via environment variable
void init_scaling_factor() {
    char *env_scaling_factor = getenv("SCALING_FACTOR");
    if (env_scaling_factor == NULL) {
        scaling_factor = 2;
    } else {
        scaling_factor = atoi(env_scaling_factor);
    }
}

// Allocates scaling_factor * size bytes using malloc
void *as_malloc(size_t size) {
    if (scaling_factor == 0) {
        init_scaling_factor();
    }

    // Print how much memory is being allocated
    printf("Allocating %d bytes\n", size * scaling_factor);

    return malloc(size * scaling_factor);
}

// Free the memory space pointed to by ptr, which must have been returned by a previous call to malloc().
void as_free(void *ptr) {
    free(ptr);
}








