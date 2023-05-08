/*
    Custom malloc header file for Address Scaling.

*/

#ifndef AS_MALLOC_H
#define AS_MALLOC_H

#include <stdlib.h>
// Header for m5op
#include "/home/deepanjali/deepanjali/Address-Scaling/gem5-source/include/gem5/m5ops.h"



// Initialize the scaling factor
void init_scaling_factor();

// Allocate scaled memory
void *as_malloc(size_t size);

// Free scaled memory
void as_free(void *ptr);

#endif