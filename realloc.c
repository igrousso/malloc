#include "malloc.h"

EXPORT void *realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
        return malloc(size);
    if (size == 0)
        return free(ptr), NULL;

    t_zone *currZone;
    int zone = findZone(&currZone, ptr);
    if (zone == -1)
        return NULL;
    void *ret;
    if (size <= 64)
    {
        if (zone == TINY)
            return ptr;
        ret = move_tiny(size, currZone, ptr, zone);
    }
    else if (size <= 4096)
    {
        if (zone == SMALL)
            return ptr;
        ret = move_small(size, currZone, ptr, zone);
    }
    else
        ret = move_large(size, currZone, ptr, zone);
    return ret;
}

void *move_tiny(size_t size, t_zone *currZone, void *ptr, int zone)
{
    void *dst = littleZone(TINY, TINY_CHUNK, 3);
    if (dst == NULL)
        return NULL;
    size_t size_cpy;
    if (zone == TINY)
        size_cpy = TINY_CHUNK;
    else if (zone == SMALL)
        size_cpy = SMALL_CHUNK;
    else
        size_cpy = currZone->bitmap[0] - sizeof(t_zone);
    if (size < size_cpy)
        size_cpy = size;
    ft_memcpy(dst, ptr, size_cpy);
    free(ptr);
    return dst;
}

void *move_small(size_t size, t_zone *currZone, void *ptr, int zone)
{
    void *dst = littleZone(SMALL, SMALL_CHUNK, 129);
    if (dst == NULL)
        return NULL;
    size_t size_cpy;
    if (zone == TINY)
        size_cpy = TINY_CHUNK;
    if (zone == SMALL)
        size_cpy = SMALL_CHUNK;
    else
        size_cpy = currZone->bitmap[0] - sizeof(t_zone);
    if (size < size_cpy)
        size_cpy = size;
    ft_memcpy(dst, ptr, size_cpy);
    free(ptr);
    return dst;
}

void *move_large(size_t size, t_zone *currZone, void *ptr, int zone)
{
    void *dst = large(size);
    if (dst == NULL)
        return NULL;
    size_t size_cpy;
    if (zone == TINY)
        size_cpy = TINY_CHUNK;
    if (zone == SMALL)
        size_cpy = SMALL_CHUNK;
    else
        size_cpy = currZone->bitmap[0] - sizeof(t_zone);
    if (size < size_cpy)
        size_cpy = size;
    ft_memcpy(dst, ptr, size_cpy);
    free(ptr);
    return dst;
}
