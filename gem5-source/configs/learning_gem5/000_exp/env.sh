#!/bin/bash

SCALE_FACTOR=7
export LD_PRELOAD="$PWD/configs/learning_gem5/000_exp/asmalloc.so"

# Run only the config.py inside Gem5 using LD_PRELOAD
# ./build/X86/gem5.opt -e "LD_PRELOAD=$LD_PRELOAD" configs/learning_gem5/000_exp/config.py -n 3000 -e "bo" -t 1
./build/X86/gem5.opt  configs/learning_gem5/000_exp/config.py -n 3000 -e "bo" -t 1