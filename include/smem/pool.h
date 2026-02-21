#pragma once

#include <stdint.h>

// it is needed to malloc the pool first
// we cannot use own malloc here
#include <malloc.h>

struct smem_pool
{
    // stores an array of memory address.
    // These are added like an array lifo order.
    // last element will the last memory allocated
    uintptr_t *addr;

    // how many address are stored.
    int count;

    // how many address can be stored
    int length;

    // how many address allocated
    int allocated;

    // how many address get freed
    int freed;
};

// returns new smem_pool
smem_pool *smem_pool_new()
{
    smem_pool *pool = (smem_pool *)malloc(sizeof(smem_pool));
    pool->length = 10;
    pool->addr = (uintptr_t *)calloc(sizeof(uintptr_t), pool->length);
    pool->count = 0;
    pool->allocated = 0;
    pool->freed = 0;
}

// it frees the pool
void smeme_pool_destroy(smem_pool *pool)
{
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

// it adds new pointer to mem_pool
void smem_pool_append(smem_pool *pool, void *ptr)
{
    if (pool->count >= pool->length)
    {
        pool->length += 10;
        pool->addr = (uintptr_t *)realloc(pool->addr, pool->length);
        for (int i = pool->length - 10; i < pool->length; i++)
        {
            pool->addr[i] = 0;
        }
    }
    pool->addr[pool->count] = (uintptr_t)ptr;
    pool->count++;
    pool->allocated++;
}

// it frees the pointer from the pool
void smem_pool_remove(smem_pool *pool, void *ptr)
{
    for (int i = 0; i < pool->count; i++)
    {
        if (pool->addr[i] == (uintptr_t)ptr)
        {
            pool->addr[i] = 0;
            pool->addr[i] = pool->addr[pool->count - 1];
            pool->addr[pool->count - 1] = 0;
            pool->count--;
        }
    }
    pool->freed++;
}
