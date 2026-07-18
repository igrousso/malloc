#include "malloc.h"

EXPORT void *malloc(size_t size)
{
    void *ptr_ret;

    if (size == 0)
        return NULL;
    if (size <= TINY_CHUNK)
        ptr_ret = littleZone(TINY, TINY_CHUNK, 3);
    else if (size <= SMALL_CHUNK)
        ptr_ret = littleZone(SMALL, SMALL_CHUNK, 129);
    else
        ptr_ret = large(size);
    if (getenv("MALLOC_VERBOSE_")) {
        pthread_mutex_lock(&mutexes[PRINT]);
        ft_printf(2, "malloc(%u) = %p\n", size, ptr_ret);
        pthread_mutex_unlock(&mutexes[PRINT]);
    }
    return ptr_ret;
}