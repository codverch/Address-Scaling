#### To use asmalloc library, we need to compile the library first.

``` sh
gcc asmalloc.c -o asmalloc.so -shared -fPIC-ldl
```

#### To run a gem5 configuration script with asmalloc library

``` sh
./build/X86/gem5.opt /path/to/config.py  -e /path/to/env.sh <command line arguments>```

``` python

For example, to run the config.py script with scaling factor 2, we can use the following command:

gcc configs/learning_gem5/000_exp/asmalloc.c -o configs/learning_gem5/000_exp/asmalloc.so -shared -fPIC -ldl
./build/X86/gem5.opt configs/learning_gem5/000_exp/config.py -e "configs/learning_gem5/000_exp/env.sh" -n 3000 -e "bo" -t 1


```