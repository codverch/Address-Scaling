#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

static void *(*real_malloc)(size_t) = NULL;

// Data structure to track the segments allocated by malloc
typedef struct segment{
    // Original size requested by the application
    size_t orig_size;
    // Scaled size allocated by malloc
    size_t scaled_size;
    // Starting address of the segment
    void *start_addr;
    // Ending address of the segment
    void *end_addr;
}segment_tracker;

// Create a pointer to the structure
static segment_tracker *seg_tracker = NULL;
// Keep track of the number of segments
static int num_segments = 0;

// Initialize the malloc interceptor
static void mtrace_init(void) {
    real_malloc = dlsym(RTLD_NEXT, "malloc");
    if (NULL == real_malloc) {
        fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
        exit(EXIT_FAILURE);
    }
}

// Intercept malloc and track segments
void *malloc(size_t size) {
    if (real_malloc == NULL) {
        mtrace_init();
    }

    // Get environment variable
    char *scale = getenv("SCALE_FACTOR");
    int scale_factor = atoi(scale);

    // Allocate memory with scaled size
    size_t scaled_size = size * scale_factor;
    void *p = real_malloc(scaled_size);

    // Create new segment and store in data structure
    segment_tracker new_seg;
    new_seg.orig_size = size;
    new_seg.scaled_size = scaled_size;
    new_seg.start_addr = p;
    new_seg.end_addr = p + scaled_size;
    seg_tracker = realloc(seg_tracker, (num_segments + 1) * sizeof(segment_tracker));
    seg_tracker[num_segments++] = new_seg;

    return p;
}