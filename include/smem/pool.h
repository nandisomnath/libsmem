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
    uintptr_t *adrr;

    // how many address are stored.
    int length;

    // how many address allocated
    int allocated;

    // how many address get freed
    int freed;
};

// returns new smem_pool
smem_pool *smem_pool_new() {
    smem_pool* pool = (smem_pool*) malloc(sizeof(smem_pool));
    pool->adrr = ()
}

// it frees the pool
void smeme_pool_free(smem_pool *pool);

// it adds new pointer to mem_pool
void smem_pool_append(const smem_pool *pool, void *ptr);

// it frees the pointer from the pool
void smem_pool_remove(const smem_pool *pool, void *ptr);
