#include "malloc.h"

t_zone *zones[3];
pthread_mutex_t mutexes[3] = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};

uint32_t getNbPage()
{
    uint32_t ret = 0;
    
    t_zone *curr = zones[TINY];
    while (curr)
    {
        ret += 3;
        curr = curr->next;
    }
    curr = zones[SMALL];
    while (curr)
    {
        ret += 129;
        curr = curr->next;
    }
    curr = zones[LARGE];
    while (curr)
    {
        ret += curr->bitmap[0] / PAGE_SIZE;
        curr = curr->next;
    }
    return ret;
}

/* créé une zone avec mmap */
INLINE void *create_zone(uint32_t size)
{
    char *page_max = getenv("MALLOC_PAGE_MAX_");
    if (page_max)
    {
        int nb_page = getNbPage();
        
        if (nb_page >= ft_atoi(page_max))
        {
            write(2, "malloc error: Maximum number of pages reached\n", 46);
            return NULL;
        }
    }

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

    pthread_mutex_lock(&mutexes[zoneSize]);
    if (zones[zoneSize] == NULL)
    {
        currZone = create_zone(nbPage * PAGE_SIZE);
        if (currZone == MAP_FAILED || currZone == NULL) {
            pthread_mutex_unlock(&mutexes[zoneSize]);
            return NULL;
        }
        zones[zoneSize] = currZone;
    }
    else
        currZone = getFreeZone(zones[zoneSize]);

    /* zone pleine, on rappelle mmap pour avoir une nouvelle zone */
    if (currZone->first_free_index == -1)
    {
        t_zone *newZone = create_zone(nbPage * PAGE_SIZE);
        if (newZone == MAP_FAILED || newZone == NULL) {
            pthread_mutex_unlock(&mutexes[zoneSize]);
            return NULL;
        }
        currZone->next = newZone;
        currZone = newZone;
    }

    /* on renvoit l'adresse du premier chunk libre */
    void *ret = (void *)currZone + sizeof(t_zone) + currZone->first_free_index * chunkSize;
    /* on met le bit à 1 (chunk utilisé) */
    setBit(currZone->bitmap, currZone->first_free_index);
    /* on choppe le prochain index */
    currZone->first_free_index = getNextIndex(currZone);
    char *perturb = getenv("MALLOC_PERTURB_");
    if (perturb)
        ft_memset(ret, ~(ft_atoi(perturb    ) & 0xff), chunkSize); // & 0xff sert à garder uniquement le byte de poids faible pour rester entr 0 et 255
    pthread_mutex_unlock(&mutexes[zoneSize]);
    return ret;
}

/* renvoie une adresse allouée par mmap spécifiquement pour cet appel malloc */
INLINE void *large(size_t size)
{
    size_t currSize = ((size + sizeof(t_zone) + PAGE_SIZE - 1) / PAGE_SIZE) * PAGE_SIZE; // arrondit au multiple de page supérieur

    pthread_mutex_lock(&mutexes[LARGE]);
    t_zone *currZone = create_zone(currSize);
    if (currZone == MAP_FAILED || currZone == NULL) {
        pthread_mutex_unlock(&mutexes[LARGE]);
        return NULL;
    }

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
    char *perturb = getenv("MALLOC_PERTURB_");
    if (perturb)
        ft_memset(ptr, ft_atoi(perturb) & 0xff, currSize);
    pthread_mutex_unlock(&mutexes[LARGE]);
    return ptr;
}
