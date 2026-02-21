#pragma once

#include "smem/pool.h"
#include <stdlib.h>
// signatures

void *smalloc(smpool* pool, size_t size)
{
    void *mem = malloc(size);
    smpool_append(pool, mem);
    return mem;
}

void *smrealloc(smpool* pool, void *ptr, size_t size)
{
    void *mem = realloc(ptr, size);
    smpool_append(pool, mem);
    smpool_remove(pool, ptr);
    return mem;
}
void smfree(smpool* pool, void *ptr)
{
    free(ptr);
    smpool_remove(pool, ptr);
}
void *smcalloc(smpool* pool, size_t size, size_t len)
{
    void *mem = calloc(size, len);
    smpool_append(pool, mem);
    return mem;
}