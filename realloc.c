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
    pthread_mutex_unlock(&mutexes[zone]);

    uintptr_t offset = ptr - ((void *)currZone + sizeof(t_zone));
    int sizeChunk = (zone == 0 ? TINY_CHUNK : (zone == 1 ? SMALL_CHUNK : 0));
    if ((sizeChunk && (offset % sizeChunk != 0)) || \
        (!sizeChunk && offset))
    {
        if (getenv("MALLOC_CHECK_"))
            write(2, "malloc error: Invalid pointer (misaligned)\n", 43);
        return NULL;
    }

    void *ret;
    int retptr = 0;
    if (size <= 64)
    {
        if (zone == TINY)
            retptr = 1;
        else
            ret = move_tiny(size, currZone, ptr, zone);
    }
    else if (size <= 4096)
    {
        if (zone == SMALL)
            retptr = 1;
        else
            ret = move_small(size, currZone, ptr, zone);
    }
    else
        ret = move_large(size, currZone, ptr, zone);
    if (retptr == 1)
    {
        if (getenv("MALLOC_VERBOSE_")) {
            pthread_mutex_lock(&mutexes[PRINT]);
            ft_printf(2, "realloc(%p, %u) = %p\n", ptr, size, ptr);
            pthread_mutex_unlock(&mutexes[PRINT]);
        }
        return ptr;
    }
    if (getenv("MALLOC_VERBOSE_")) {
        pthread_mutex_lock(&mutexes[PRINT]);
        ft_printf(2, "realloc(%p, %u) = %p\n", ptr, size, ret);
        pthread_mutex_unlock(&mutexes[PRINT]);
    }
    free(ptr);
    return ret;
}

/* déplace la data dans une zone tiny */
void *move_tiny(size_t size, t_zone *currZone, void *ptr, int zone)
{
    void *dst = littleZone(TINY, TINY_CHUNK, 3);
    if (dst == NULL)
        return NULL;
    size_t size_cpy;
    if (zone == SMALL)
        size_cpy = SMALL_CHUNK;
    else {
        pthread_mutex_lock(&mutexes[LARGE]); 
        size_cpy = currZone->bitmap[0] - sizeof(t_zone);
        pthread_mutex_unlock(&mutexes[LARGE]); 
    }
    if (size < size_cpy)
        size_cpy = size;
    ft_memcpy(dst, ptr, size_cpy);
    return dst;
}

/* déplace la data dans une zone small */
void *move_small(size_t size, t_zone *currZone, void *ptr, int zone)
{
    void *dst = littleZone(SMALL, SMALL_CHUNK, 129);
    if (dst == NULL)
        return NULL;
    size_t size_cpy;
    if (zone == TINY)
        size_cpy = TINY_CHUNK;
    else {
        pthread_mutex_lock(&mutexes[LARGE]); 
        size_cpy = currZone->bitmap[0] - sizeof(t_zone);
        pthread_mutex_unlock(&mutexes[LARGE]);
    }
    if (size < size_cpy)
        size_cpy = size;
    ft_memcpy(dst, ptr, size_cpy);
    return dst;
}

/* déplace la data dans une zone large */
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
    else {
        pthread_mutex_lock(&mutexes[LARGE]);
        size_cpy = currZone->bitmap[0] - sizeof(t_zone);
        pthread_mutex_unlock(&mutexes[LARGE]); 
    }
    if (size < size_cpy)
        size_cpy = size;
    ft_memcpy(dst, ptr, size_cpy);
    return dst;
}
