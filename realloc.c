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
    // TODO : faire un memcpy opti, faire 3 fonctions en fonction de la zone
}