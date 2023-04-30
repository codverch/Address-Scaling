# -*- MakeFile -*-

#target: dependencies
#	action

# Build the shared library and the test program
all: as_malloc.so test


# Build the shared library
as_malloc.so: as_malloc.c
	gcc -shared -fPIC -o as_malloc.so as_malloc.c

# Build the test program
test: memory-padded.c as_malloc.so
	gcc -o test memory-padded.c as_malloc.so
	

# Clean up the directory
clean:
	rm -f *.o *.so test

