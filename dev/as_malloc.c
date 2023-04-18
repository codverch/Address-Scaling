// Address Scaled malloc() using LD_PRELOAD
// Author: Deepanjali Mishra, Microsoft Research India
// Date: 18/04/2023

#define _GNU_SOURCE
#include <stdio.h>
// Declares functions for dynamically loading and using shared libraries
#include <dlfcn.h>

static void *(*real_malloc)(size_t) = NULL;
static int scale_factor = 2;

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
    size_t scaled_size = size * scale_factor;
    fprintf(stderr, "\nmalloc (%d) = ", scaled_size);
    p = real_malloc(scaled_size);
    fprintf(stderr, "%p\\n", p);
    // Print the original size and scaled size
    fprintf(stderr, "\nOriginal size: %d, Scaled size: %d\n", size, scaled_size);
    return p;
}