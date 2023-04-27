# Scaled Malloc for Address Scaling 

Implementation of Scaled Malloc that allocates a scaled number of bytes to an application, taking the scaling factor as an environment variable

## Usage

1) Replace the use of malloc() with as_malloc(size_t size) in the application's code.

2) Compile the as_malloc library using the following command:

```sh
gcc -shared -fPIC -o as_malloc.so as_malloc.c

```

3) Export the library path using the following command:

```sh
export LD_LIBRARY_PATH=/path/to/as_malloc:$LD_LIBRARY_PATH
```
4) Compile the application 

```sh
gcc -o test test.c as_malloc.so

```

5) Run the application by setting the SCALING_FACTOR environment variable to "n" and executing the following command: 

```sh
SCALING_FACTOR = n ./test <args>

```