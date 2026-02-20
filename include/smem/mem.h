#pragma once

#include "pool.h"
#include <stdlib.h>
// signatures

// This is for global use one per library instance
const smem_pool *smem_pool_global = smem_pool_new();

void *smem_alloc(size_t size)
{
    void *mem = malloc(size);
    smem_pool_append(smem_pool_global, mem);
    return mem;
}

void *smem_realloc(void *ptr, size_t size)
{
    void *mem = realloc(ptr, size);
    smem_pool_append(smem_pool_global, mem);
    return mem;
}
void smem_free(void *ptr)
{
    free(ptr);
    smem_pool_remove(smem_pool_global, ptr);
}
void *smem_calloc(size_t size, size_t len)
{
    void *mem = calloc(size, len);
    smem_pool_append(smem_pool_global, mem);
    return mem;
}