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

## CMake Integration

To include libsmem as a dependency in your CMake project using FetchContent:

```cmake
include(FetchContent)

FetchContent_Declare(
    libsmem
    GIT_REPOSITORY <repository-url>
    GIT_TAG <tag>  # e.g., v0.0.1 or main
)

FetchContent_MakeAvailable(libsmem)

# Link to your target
target_link_libraries(your_target libsmem)
```

This will make the libsmem headers available to your project.

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

See [LICENSE](LICENSE) for details.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for contribution guidelines.