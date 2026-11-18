# Parallel Merge Sort with pthreads

An Operating Systems course exercise: sorting an array using multiple POSIX threads.

## How it works

The program sorts a fixed array of 10 integers using three threads:

1. **Thread 1** insertion-sorts the first half of the array.
2. **Thread 2** insertion-sorts the second half.
3. After both halves are sorted (`pthread_join`), **Thread 3** merges them into the final sorted array.

The sorted result is printed to stdout.

## Build & Run

With GCC directly:

```bash
gcc main.c -pthread -o thread
./thread
```

Or with CMake:

```bash
cmake -B build
cmake --build build
./build/thread
```

Expected output:

```
2 3 4 6 7 8 12 15 18 19
```