#pragma once

#include "smem/pool.h"
#include <stdlib.h>

/**
 * @brief Allocates memory and adds it to the global pool.
 *
 * This function wraps malloc to allocate memory and automatically tracks it in the shared memory pool.
 *
 * @param size Number of bytes to allocate.
 * @return Pointer to the allocated memory, or NULL if allocation fails.
 */
void *smalloc(size_t size);

/**
 * @brief Reallocates memory and updates the global pool.
 *
 * This function wraps realloc to resize memory and updates the pool tracking.
 *
 * @param ptr Pointer to the memory to reallocate.
 * @param size New size in bytes.
 * @return Pointer to the reallocated memory, or NULL if reallocation fails.
 */
void *smrealloc(void *ptr, size_t size);

/**
 * @brief Frees memory and removes it from the global pool.
 *
 * This function wraps free to deallocate memory and removes it from the pool tracking.
 *
 * @param ptr Pointer to the memory to free.
 */
void smfree(void *ptr);

/**
 * @brief Allocates and initializes memory to zero, adding it to the global pool.
 *
 * This function wraps calloc to allocate zero-initialized memory and tracks it in the pool.
 *
 * @param size Size of each element.
 * @param len Number of elements.
 * @return Pointer to the allocated memory, or NULL if allocation fails.
 */
void *smcalloc(size_t size, size_t len);