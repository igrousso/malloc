#ifndef MALLOC_H
#define MALLOC_H

#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "ft_printf/ft_printf.h"

/* pour que, dans le .so, il y ait uniquement les fonctions avec le tag EXPORT*/
#define EXPORT __attribute__((visibility("default")))

/* force le inline */
#define INLINE __attribute__((always_inline)) inline

#define PAGE_SIZE sysconf(_SC_PAGESIZE)


#define TINY 0
#define SMALL 1
#define LARGE 2
#define TINY_CHUNK 64
#define SMALL_CHUNK 4096
#define TINY_ZONE_SIZE (3 * PAGE_SIZE)
#define SMALL_ZONE_SIZE (129 * PAGE_SIZE)

/* structure representant le header de chaque zone de memoire */
typedef struct s_zone
{
    void        *next;
    uint64_t    bitmap[2];
    char        first_free_index;
}               t_zone;

extern t_zone *zones[3];
extern pthread_mutex_t mutexes[3];

/* bitmap.c */

void setBit(unsigned long *bitmap, size_t bitPos);
void clearBit(unsigned long *bitmap, size_t bitPos);
bool checkBit(unsigned long *bitmap, size_t bitPos);
char getNextIndex(t_zone *zone);

/* malloc.c */

void *malloc(size_t size);

/* free.c */

void free(void *ptr);
int freeChunk(t_zone *currZone, void *ptr, int zone);
int findZone(t_zone **currZone, void *ptr);
t_zone *getPrevZone(t_zone *currZone, int zone);

/* realloc.c */

void *realloc(void *ptr, size_t size);
void *move_tiny(size_t size, t_zone *currZone, void *ptr, int zone);
void *move_small(size_t size, t_zone *currZone, void *ptr, int zone);
void *move_large(size_t size, t_zone *currZone, void *ptr, int zone);

/* zone.c */

void *create_zone(uint32_t size);
t_zone *getFreeZone(t_zone *zone);
void *littleZone(bool zoneSize, size_t chunkSize, size_t nbPage);
void *large(size_t size);

/* memcpyopt.c */

void *ft_memcpy(void *restrict dst, const void *restrict src, size_t n);

/* show_alloc_mem.c */

void show_alloc_mem();

/* show_alloc_meme_ex.c */

void show_alloc_mem_ex();

#endif