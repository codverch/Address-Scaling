### To compile the address scaled malloc library
```
gcc as_malloc.c -o as_malloc.so -fPIC -shared -ldl

```

### To run the test application
```
gcc test.c -o test

SCALE_FACTOR = 2 LD_PRELOAD="./as_malloc.so" ./test <command line arguments>
```


