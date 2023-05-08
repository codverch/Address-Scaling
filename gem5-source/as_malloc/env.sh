#!/bin/bash

# Set the environment variables
export LD_LIBRARY_PATH=/home/deepanjali/deepanjali/Address-Scaling/gem5-source/as_malloc:$LD_LIBRARY_PATH
export SCALING_FACTOR=3

./test -n 3000 -e "b0" -t 1