#include "malloc.h"

EXPORT void *malloc(size_t size)
{
    void *ptr_ret;

    if (size <= 64)
        ptr_ret = littleZone(size, TINY, TINY_CHUNK, 3);
    else if (size <= 4096)
        ptr_ret = littleZone(size, SMALL, SMALL_CHUNK, 129);
    else
        ptr_ret = large(size);
    return ptr_ret;
}