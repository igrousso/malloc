#include "malloc.h"

EXPORT void *malloc(size_t size)
{
    void *ptr_ret;

    if (size <= TINY_CHUNK)
        ptr_ret = littleZone(TINY, TINY_CHUNK, 3);
    else if (size <= SMALL_CHUNK)
        ptr_ret = littleZone(SMALL, SMALL_CHUNK, 129);
    else
        ptr_ret = large(size);
    return ptr_ret;
}