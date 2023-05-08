
#!/bin/bash

# Set the environment variables
export LD_LIBRARY_PATH=/home/deepanjali/deepanjali/Address-Scaling/gem5-source/as_malloc:$LD_LIBRARY_PATH
export SCALING_FACTOR=5
echo "SCALING_FACTOR = $SCALING_FACTOR"
./build/X86/gem5.opt  configs/learning_gem5/001_exp/config.py -n 10000 -e "bo" -t 1
