#include "malloc.h"

t_zone *zones[3];

/* créé une zone avec mmap */
INLINE void *create_zone(uint32_t size)
{
    return mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
}

/* renvoie la premiere zone qui a de la place */
INLINE t_zone *getFreeZone(t_zone *zone)
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
void *littleZone(bool zoneSize, size_t chunkSize, size_t nbPage)
{
    t_zone *currZone;

    if (zones[zoneSize] == NULL)
    {
        currZone = create_zone(nbPage * PAGE_SIZE);
        if (currZone == MAP_FAILED)
            return NULL;
        zones[zoneSize] = currZone;
    }
    else
        currZone = getFreeZone(zones[zoneSize]);

    /* zone pleine, on rappelle mmap pour avoir une nouvelle zone */
    if (currZone->first_free_index == -1)
    {
        t_zone *newZone = create_zone(nbPage * PAGE_SIZE);
        if (newZone == MAP_FAILED)
            return NULL;
        currZone->next = newZone;
        currZone = newZone;
    }

    /* on renvoit l'adresse du premier chunk libre */
    void *ret = (void *)currZone + sizeof(t_zone) + currZone->first_free_index * chunkSize;
    /* on met le bit à 1 (chunk utilisé) */
    setBit(currZone->bitmap, currZone->first_free_index);
    /* on choppe le prochain index */
    currZone->first_free_index = getNextIndex(currZone);
    return ret;
}

/* renvoie une adresse allouée par mmap spécifiquement pour cet appel malloc */
INLINE void *large(size_t size)
{
    size_t currSize = ((size + sizeof(t_zone) + PAGE_SIZE - 1) / PAGE_SIZE) * PAGE_SIZE; // arrondit au multiple de page supérieur
    t_zone *currZone = create_zone(currSize);
    if (currZone == MAP_FAILED)
        return NULL;

    /* stock la taille de l'allocation dans bitmap[0] puisqu'on n'utilise pas la bitmap pour les zones LARGE */
    currZone->bitmap[0] = currSize;
    if (zones[LARGE] == NULL)
        zones[LARGE] = currZone;
    else
    {
        t_zone *tmp = zones[LARGE];
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = currZone;
    }
    void *ptr = (void *)currZone + sizeof(t_zone);
    return ptr;
}