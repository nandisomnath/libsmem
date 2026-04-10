#pragma once

#include <stdint.h>

// it is needed to malloc the pool first
// we cannot use own malloc here
#include <malloc.h>

/**
 * @brief Structure representing a shared memory pool.
 *
 * This structure manages a collection of memory addresses allocated by the library.
 * It uses a dynamic array to store pointers in LIFO order.
 */
typedef struct smpool
{
    // stores an array of memory address.
    // These are added like an array lifo order.
    // last element will the last memory allocated
    uintptr_t *addr; /**< Array of memory addresses */

    // how many address are stored.
    int count; /**< Current number of addresses stored */

    // how many address can be stored
    int length; /**< Capacity of the address array */

    // how many address allocated
    int allocated; /**< Total number of allocations */

    // how many address get freed
    int freed; /**< Total number of deallocations */
} smpool;

// global pool for smpool
static smpool * smem_gpool = NULL;

/**
 * @brief Initializes the global shared memory pool.
 *
 * Allocates and initializes a new smpool structure and sets it as the global pool.
 * The pool starts with a capacity of 10 addresses.
 */
void smpool_init();

/**
 * @brief Destroys the global shared memory pool.
 *
 * Frees all memory addresses stored in the pool and then frees the pool structure itself.
 * After calling this, the global pool is no longer valid.
 */
void smpool_destroy();

/**
 * @brief Adds a memory pointer to the global pool.
 *
 * @param ptr Pointer to the allocated memory to add to the pool.
 * If the pool is full, its capacity is increased by 10.
 */
void smpool_append(void *ptr);

/**
 * @brief Removes a memory pointer from the global pool.
 *
 * @param ptr Pointer to the memory to remove from the pool.
 * The pointer is found and removed, with the last element moved to its position if not at the end.
 */
void smpool_remove(void *ptr);
