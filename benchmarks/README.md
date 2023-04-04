## STREAM

http://www.cs.virginia.edu/stream/ref.html
http://www.cs.virginia.edu/stream/FTP/Code/

### Install Requirements

### Setup

```sh
mkdir stream
cd stream
wget http://www.cs.virginia.edu/stream/FTP/Code/stream.c
echo -e "all: stream
stream: stream.c
\t\$(CC) -o stream stream.c -static -O3
clean:
\trm -fv stream
" > Makefile
make
```

### Compile-Time modifications to the benchmark

```sh
# -DSTREAM_ARRAY_SIZE - size of the array to use
# -DNTIMES - number of times to run the benchmark
gcc -O -DNTIMES=100 -DSTREAM_ARRAY_SIZE=100000000 stream.c -o stream

```