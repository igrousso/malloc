#include "malloc.h"

t_zone *zones[2];

/* créé une zone avec mmap */
INLINE
inline void *create_zone(uint32_t size)
{
    return mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

/* renvoie la premiere zone qui a de la place */
t_zone *getZone(t_zone *zone)
{
    while (zone->next)
    {
        if (zone->first_free_index != -1)
            break;
        zone = zone->next;
    }
    return zone;
}

/* renvoie l'adresse d'un chunk vide pour une zone tiny ou small */
void *littleZone(size_t size, bool zoneSize, size_t chunkSize, size_t nbPage)
{
    t_zone *currZone;

    if (zones[zoneSize] == NULL)
        currZone = zones[zoneSize] = create_zone(nbPage * PAGE_SIZE);
    else
        currZone = getZone(zones[zoneSize]);

    if (currZone->first_free_index == -1)
    {
        t_zone *newZone = create_zone(nbPage * PAGE_SIZE);
        currZone->next = newZone;
        currZone = newZone;
    }

    void *ret = (void *)currZone + sizeof(t_zone) + currZone->first_free_index * chunkSize;
    setBit(currZone->bitmap, currZone->first_free_index);
    currZone->first_free_index = getNextIndex(currZone);
    return ret;
}

/* renvoie une adresse allouée par mmap spécifiquement pour cet appel malloc */
INLINE
inline void *large(size_t size)
{
    void *ptr = create_zone(((size + PAGE_SIZE - 1) / PAGE_SIZE) * PAGE_SIZE);  // arrondit au multiple de page supérieur
    return ptr;
}