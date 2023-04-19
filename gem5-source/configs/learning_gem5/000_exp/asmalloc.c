// Address Scaled malloc() using LD_PRELOAD
// Author: Deepanjali Mishra, Microsoft Research India
// Date: 18/04/2023

#define _GNU_SOURCE
#include <stdio.h>
// Declares functions for dynamically loading and using shared libraries
#include <dlfcn.h>
// For environment variables
#include <stdlib.h>

static void *(*real_malloc)(size_t) = NULL;

static void mtrace_init(void)
{
    real_malloc = dlsym(RTLD_NEXT, "malloc");
    if (NULL == real_malloc)
    {
        fprintf(stderr, "Error in `dlsym`: %s\\n", dlerror());
    }
}

void *malloc(size_t size)
{
    if (real_malloc == NULL)
    {
        mtrace_init();
    }

    void *p = NULL;
    // Get environment variable
    char *scale = getenv("SCALE_FACTOR");
    // Set the environment variable received from the user
    int scale_factor = atoi(scale);
    size_t scaled_size = size * scale_factor;
    fprintf(stderr, "\nmalloc (%d) = ", scaled_size);
    p = real_malloc(scaled_size);
    fprintf(stderr, "%p\\n", p);
    // Print the original size and scaled size
    fprintf(stderr, "\nOriginal size: %d, Scaled size: %d\n", size, scaled_size);
    return p;
}