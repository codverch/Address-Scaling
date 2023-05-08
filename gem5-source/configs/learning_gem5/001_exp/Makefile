# -*- MakeFile -*-

# Path to the as_malloc directory
AS_MALLOC_DIR = /home/deepanjali/deepanjali/Address-Scaling/gem5-source/as_malloc

all: $(AS_MALLOC_DIR)/as_malloc.so test

# Build the shared library 
$(AS_MALLOC_DIR)/as_malloc.so: $(AS_MALLOC_DIR)/as_malloc.c 
	gcc -shared -fPIC -o $(AS_MALLOC_DIR)/as_malloc.so $(AS_MALLOC_DIR)/as_malloc.c 

# Build the test program
test: memory-padded.c $(AS_MALLOC_DIR)/as_malloc.so
	gcc -o test memory-padded.c $(AS_MALLOC_DIR)/as_malloc.so

clean:
	rm -f *.o *.so test
