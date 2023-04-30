# -*- MakeFile -*-

#target: dependencies
#	action

all: as_malloc.so test

as_malloc.so: as_malloc.c
	gcc -shared -fPIC -o as_malloc.so as_malloc.c

test: memory-padded.c as_malloc.so
	gcc -o test memory-padded.c as_malloc.so

clean:
	rm -f *.o *.so test

