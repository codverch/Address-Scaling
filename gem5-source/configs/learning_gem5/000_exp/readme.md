#### To use asmalloc library, we need to compile the library first.

```gcc asmalloc.c -o asmalloc.so -shared -fPIC-ldl```

#### To run a gem5 configuration script with asmalloc library

```SCALE_FACTOR=<value of scaling factor> LD_PRELOAD=/path/to/asmalloc.so ./build/X86/gem5.opt /path/to/config.py <command line arguments>```

``` python

For example, to run the config.py script with scaling factor 2, we can use the following command:

gcc configs/learning_gem5/000_exp/asmalloc.c -o configs/learning_gem5/000_exp/asmalloc.so -shared -fPIC -ldl
SCALE_FACTOR=2 LD_PRELOAD="configs/learning_gem5/000_exp/asmalloc.so" ./build/X86/gem5.opt configs/learning_gem5/000_exp/config.py -n 3000 -e "bo" -t 1


```