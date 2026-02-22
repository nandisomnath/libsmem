#pragma once

#include "smem/pool.h"
#include <stdlib.h>
// signatures



void *smalloc(size_t size)
{
    void *mem = malloc(size);
    smpool_append(mem);
    return mem;
}

void *smrealloc(void *ptr, size_t size)
{
    void *mem = realloc(ptr, size);
    smpool_append(mem);
    smpool_remove(ptr);
    return mem;
}
void smfree(void *ptr)
{
    free(ptr);
    smpool_remove(ptr);
}
void *smcalloc(size_t size, size_t len)
{
    void *mem = calloc(size, len);
    smpool_append(mem);
    return mem;
}