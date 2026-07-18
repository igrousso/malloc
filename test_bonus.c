#include "malloc.h"

int main()
{
    void *ptr = malloc(10);
    show_alloc_mem_ex();
    ptr = realloc(ptr, 80);

    free((void *)(ptr + 1)); // misaligned
    free(ptr - 1000000); // invalid free
    free(ptr);
    free(ptr); // double free
}