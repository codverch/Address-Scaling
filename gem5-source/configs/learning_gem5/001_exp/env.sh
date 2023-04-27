#!/bin/bash

# export LD_LIBRARY_PATH=/home/deepanjali/deepanjali/Address-Scaling/gem5-source/as_malloc:$LD_LIBRARY_PATH
# gcc -o configs/learning_gem5/001_exp/test configs/learning_gem5/001_exp/memory-padded.c as_malloc/as_malloc.so
export SCALING_FACTOR=7

SCALING_FACTOR=${SCALING_FACTOR} gcc -shared -fPIC -o as_malloc/as_malloc.so as_malloc/as_malloc.c -ldl
# ./build/X86/gem5.opt -e SCALING_FACTOR=${SCALING_FACTOR} configs/learning_gem5/001_exp/config.py -n 3000 -e bo -t 1
./build/X86/gem5.opt  configs/learning_gem5/001_exp/config.py -n 3000 -e bo -t 1