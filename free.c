#include "malloc.h"

EXPORT void free(void *ptr)
{
    t_zone *currZone;
    int zone = findZone(&currZone, ptr);
    if (zone == -1) {
        if (getenv("MALLOC_CHECK_"))
            write(2, "malloc error: Invalid free\n", 27);
        return;
    }
    uintptr_t offset = ptr - ((void *)currZone + sizeof(t_zone));
    int size = (zone == 0 ? TINY_CHUNK : (zone == 1 ? SMALL_CHUNK : 0));
    if ((size && (offset % size != 0)) || \
        (!size && offset))
    {
        if (getenv("MALLOC_CHECK_"))
            write(2, "malloc error: Invalid pointer (misaligned)\n", 43);
        pthread_mutex_unlock(&mutexes[zone]);
        return;
    }
    if (freeChunk(currZone, ptr, zone) == -1) {
        pthread_mutex_unlock(&mutexes[zone]);
        if (getenv("MALLOC_CHECK_"))
            write(2, "malloc error: Double free\n", 26);
        return;
    }
    if (zone != LARGE && \
        currZone->bitmap[0] == 0 && \
        currZone->bitmap[1] == 0 && \
        currZone != zones[zone])
    {
        t_zone *prevZone = getPrevZone(currZone, zone);
        prevZone->next = currZone->next;
        size_t size;
        if (zone == TINY)
            size = TINY_ZONE_SIZE;
        else
            size = SMALL_ZONE_SIZE;
        munmap(currZone, size);
    }
    pthread_mutex_unlock(&mutexes[zone]);
    if (getenv("MALLOC_VERBOSE_")) {
        pthread_mutex_lock(&mutexes[PRINT]);
        ft_printf(2, "free(%p)\n", ptr);
        pthread_mutex_unlock(&mutexes[PRINT]);
    }
}

/* libère le chunk OU la zone entiere si le ptr vient d'une zone LARGE */
int freeChunk(t_zone *currZone, void *ptr, int zone)
{
    if (zone == LARGE)
    {
        if (currZone == zones[LARGE])
            zones[LARGE] = currZone->next;
        else
        {
            t_zone *prevZone = getPrevZone(currZone, zone);
            prevZone->next = currZone->next;
        }
        munmap(currZone, currZone->bitmap[0]);
        return 0;
    }
    size_t sizeChunk = TINY_CHUNK + (zone * (SMALL_CHUNK - TINY_CHUNK));
    char index = (ptr - ((void *)currZone + sizeof(t_zone))) / sizeChunk;
    if (checkBit(currZone->bitmap, index) == 0)
        return -1;
    clearBit(currZone->bitmap, index);
    if (currZone->first_free_index == -1 || index < currZone->first_free_index)
        currZone->first_free_index = index;
    char *perturb = getenv("MALLOC_PERTURB_");
    if (perturb)
        ft_memset(ptr, ft_atoi(perturb) & 0xff, sizeChunk);
    return 0;
}

/* trouve la bonne zone en fonction du pointeur */
int findZone(t_zone **currZone, void *ptr)
{
    pthread_mutex_lock(&mutexes[TINY]);
    *currZone = zones[TINY];
    while (*currZone)
    {
        void *begin = (void *)(*currZone) + sizeof(t_zone);
        if (ptr >= begin && ptr < (void *)(*currZone) + TINY_ZONE_SIZE)
            return TINY;
        *currZone = (*currZone)->next;
    }
    pthread_mutex_unlock(&mutexes[TINY]);
    pthread_mutex_lock(&mutexes[SMALL]);
    *currZone = zones[SMALL];
    while (*currZone)
    {
        void *begin = (void *)(*currZone) + sizeof(t_zone);
        if (ptr >= begin && ptr < (void *)(*currZone) + SMALL_ZONE_SIZE)
            return SMALL;
        *currZone = (*currZone)->next;
    }
    pthread_mutex_unlock(&mutexes[SMALL]);
    pthread_mutex_lock(&mutexes[LARGE]);
    *currZone = zones[LARGE];
    while (*currZone)
    {
        if (ptr == (void *)(*currZone) + sizeof(t_zone))
            return LARGE;
        *currZone = (*currZone)->next;
    }
    pthread_mutex_unlock(&mutexes[LARGE]);
    return -1;
}

/* cherche le noeud prev dans la list t_zone */
t_zone *getPrevZone(t_zone *currZone, int zone)
{
    t_zone *tmp = zones[zone];
    while (tmp->next && tmp->next != currZone)
        tmp = tmp->next;
    return tmp;
}
