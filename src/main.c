#include <stdio.h>
#include <smem/mem.h>


int main(int argc, char const *argv[])
{
    smpool* pool = smpool_new();

    int * ptr = (int*)smalloc(pool, sizeof(int) * 15);
    printf("address: %lu\n", (uintptr_t)ptr);

    for (int i = 0; i < 15; i++)
    {
        ptr[i] = i;
    }

    for (int i = 0; i < 15; i++)
    {
        printf("%d, ", ptr[i]);
    }
    
    for (int i = 0; i < pool->count; i++)
    {
        printf("addr: %lu\n", pool->addr[i]);
    }
    

    smfree(pool, ptr);
    
    smpool_destroy(pool);
    return 0;
}
