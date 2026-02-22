#pragma once

#include <stdint.h>

// it is needed to malloc the pool first
// we cannot use own malloc here
#include <malloc.h>

typedef struct smpool
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
} smpool;

// global pool for smpool
static smpool * smem_gpool = NULL;


// returns new smem_pool
// if flag is 1 then creates new smpool struct
// otherwise it will init global smem_pool
smpool *smpool_new(int flag)
{
    smpool *pool = (smpool *)malloc(sizeof(smpool));
    pool->length = 10;
    pool->addr = (uintptr_t *)calloc(pool->length, sizeof(uintptr_t));
    pool->count = 0;
    pool->allocated = 0;
    pool->freed = 0;
    if (flag == 1)
    {
        return pool;
    }
    smem_gpool = pool;
}

// it frees the pool
void smpool_destroy(smpool *pool)
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
void smpool_append(smpool *pool, void *ptr)
{
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

// it frees the pointer from the pool
void smpool_remove(smpool *pool, void *ptr)
{
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
