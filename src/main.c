#include <stdio.h>
#include <smem/mem.h>

/**
 * @brief Main function demonstrating the usage of libsmem.
 *
 * This program initializes a shared memory pool, allocates memory using smalloc,
 * fills it with data, prints the data, lists the pool addresses, frees the memory,
 * and destroys the pool.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Exit status.
 */
int main(int argc, char const *argv[])
{
    // Initialize the global shared memory pool
    smpool_init();

    // Allocate memory for 15 integers using smalloc
    int *ptr = (int *)smalloc(sizeof(int) * 15);
    printf("address: %lu\n", (uintptr_t)ptr);

    // Fill the allocated memory with values 0 to 14
    for (int i = 0; i < 15; i++)
    {
        ptr[i] = i;
    }

    // Print the values
    for (int i = 0; i < 15; i++)
    {
        printf("%d, ", ptr[i]);
    }
    printf("\n");

    // Print all addresses in the pool
    printf("Pool count: %d\n", smem_gpool->set->count);
    for (int i = 0; i < smem_gpool->set->size; i++)
    {
        if (smem_gpool->set->table[i] != 0)
        {
            printf("addr: %lu\n", smem_gpool->set->table[i]);
        }
    }

    // Free the allocated memory
    smfree(ptr);

    // Destroy the pool
    smpool_destroy();
    return 0;
}
