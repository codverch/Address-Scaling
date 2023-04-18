### To compile and use the as_malloc library
```
gcc as_malloc.c -o as_malloc.so -fPIC -shared -ldl
LD_PRELOAD="./as_malloc.so" ./application <args>

```

