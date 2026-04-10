# libsmem

A C library for shared memory management.

## Description

libsmem provides utilities for managing shared memory pools and memory allocation in C applications.

## Features

- Shared memory pool management
- Memory allocation and deallocation
- Thread-safe operations

## Installation

Clone the repository and build using CMake:

```bash
git clone <repository-url>
cd libsmem
mkdir build
cd build
cmake ..
make
make install
```

## Usage

Include the headers in your C code:

```c
#include <smem/mem.h>
#include <smem/pool.h>
```

Example usage:

```c
// Initialize a memory pool
smem_pool_t *pool = smem_pool_create(1024 * 1024); // 1MB pool

// Allocate memory
void *ptr = smem_alloc(pool, 100);

// Use memory...

// Free memory
smem_free(pool, ptr);

// Destroy pool
smem_pool_destroy(pool);
```

## Building

To build the project:

```bash
mkdir build
cd build
cmake ..
make
```

To run tests:

```bash
make test
```

## License

[Specify license here]

## Contributing

[Add contribution guidelines]