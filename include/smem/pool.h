#pragma once

#include <stdint.h>
#include <malloc.h>
#include <string.h>  // for memset

#define HASH_SIZE 1024

/**
 * @brief Simple hash set for storing uintptr_t keys with open addressing.
 */
typedef struct {
    uintptr_t *table; /**< Hash table array */
    int size;         /**< Size of the table */
    int count;        /**< Number of elements */
} hash_set;

/**
 * @brief Computes a simple hash for a uintptr_t key.
 */
static unsigned int hash_uintptr(uintptr_t key, int size) {
    return (unsigned int)(key >> 2) % size;
}

/**
 * @brief Inserts a key into the hash set.
 */
void hash_insert(hash_set *set, uintptr_t key) {
    unsigned int h = hash_uintptr(key, set->size);
    while (set->table[h] != 0 && set->table[h] != key) {
        h = (h + 1) % set->size;
    }
    if (set->table[h] == 0) {
        set->table[h] = key;
        set->count++;
    }
}

/**
 * @brief Removes a key from the hash set.
 */
int hash_remove(hash_set *set, uintptr_t key) {
    unsigned int h = hash_uintptr(key, set->size);
    while (set->table[h] != 0) {
        if (set->table[h] == key) {
            set->table[h] = 0;
            set->count--;
            return 1;
        }
        h = (h + 1) % set->size;
    }
    return 0;
}

/**
 * @brief Structure representing a shared memory pool.
 *
 * This structure manages a collection of memory addresses allocated by the library.
 * It uses a hash set for O(1) average-case operations.
 */
typedef struct smpool
{
    hash_set *set;    /**< Hash set for tracking pointers */
    int allocated;    /**< Total number of allocations */
    int freed;        /**< Total number of deallocations */
} smpool;

// global pool for smpool
static smpool * smem_gpool = NULL;

/**
 * @brief Initializes the global shared memory pool.
 *
 * Allocates and initializes a new smpool structure with a hash set and sets it as the global pool.
 */
void smpool_init()
{
    smpool *pool = (smpool *)malloc(sizeof(smpool));
    pool->set = (hash_set *)malloc(sizeof(hash_set));
    pool->set->size = HASH_SIZE;
    pool->set->table = (uintptr_t *)calloc(HASH_SIZE, sizeof(uintptr_t));
    pool->set->count = 0;
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
    for (int i = 0; i < pool->set->size; i++)
    {
        if (pool->set->table[i] != 0)
        {
            free((void *)pool->set->table[i]);
        }
    }
    free(pool->set->table);
    free(pool->set);
    free(pool);
}

/**
 * @brief Adds a memory pointer to the global pool.
 *
 * @param ptr Pointer to the allocated memory to add to the pool.
 */
void smpool_append(void *ptr)
{
    hash_insert(smem_gpool->set, (uintptr_t)ptr);
    smem_gpool->allocated++;
}

/**
 * @brief Removes a memory pointer from the global pool.
 *
 * @param ptr Pointer to the memory to remove from the pool.
 */
void smpool_remove(void *ptr)
{
    if (hash_remove(smem_gpool->set, (uintptr_t)ptr)) {
        smem_gpool->freed++;
    }
}
