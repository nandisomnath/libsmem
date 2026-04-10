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
void smpool_init()
{
    smpool *pool = (smpool *)malloc(sizeof(smpool));
    pool->length = 10;
    pool->addr = (uintptr_t *)calloc(pool->length, sizeof(uintptr_t));
    pool->count = 0;
    pool->allocated = 0;
    pool->freed = 0;
    smem_gpool = pool;
}

/**
 * @brief Destroys the global shared memory pool.
 *
 * Frees all memory addresses stored in the pool and then frees the pool structure itself.
 * After calling this, the global pool is no longer valid.
 */
void smpool_destroy()
{
    smpool* pool = smem_gpool;
    for (int i = 0; i < pool->count; i++)
    {
        if (pool->addr[i] != 0x0)
        {
            free((void *)pool->addr[i]);
            pool->addr[i] = 0;
        }
    }
    free(pool->addr);
    free(pool);
}

/**
 * @brief Adds a memory pointer to the global pool.
 *
 * @param ptr Pointer to the allocated memory to add to the pool.
 * If the pool is full, its capacity is increased by 10.
 */
void smpool_append(void *ptr)
{
    smpool *pool = smem_gpool;
    if (pool->count >= pool->length)
    {
        pool->length += 10;
        pool->addr = (uintptr_t *)realloc(pool->addr, pool->length * sizeof(uintptr_t));
        for (int i = pool->length - 10; i < pool->length; i++)
        {
            pool->addr[i] = 0;
        }
    }
    pool->addr[pool->count] = (uintptr_t)ptr;
    pool->count++;
    pool->allocated++;
}

/**
 * @brief Removes a memory pointer from the global pool.
 *
 * @param ptr Pointer to the memory to remove from the pool.
 * The pointer is found and removed, with the last element moved to its position if not at the end.
 */
void smpool_remove(void *ptr)
{
    smpool *pool = smem_gpool;
    for (int i = 0; i < pool->count; i++)
    {
        if (pool->addr[i] == (uintptr_t)ptr)
        {
            pool->addr[i] = 0;
            if (i != pool->count-1)
            {
                pool->addr[i] = pool->addr[pool->count - 1];
                pool->addr[pool->count - 1] = 0;
            }
            pool->count--;
        }
    }
    pool->freed++;
}
