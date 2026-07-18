#include "malloc.h"

static void show_tiny(size_t * count)
{
    t_zone *curr = zones[TINY];

    ft_printf(1, "TINY : %p\n", (void *)curr);
    while (curr)
    {
        for (int i = 0; i < 128; i++)
        {
            if (checkBit(curr->bitmap, i) == 0)
                continue;
            void *beginAddr = (void *)((void *)curr + sizeof(t_zone) + (i * TINY_CHUNK));
            ft_printf(1, "%p - %p : %d bytes\n", beginAddr, (void *)(beginAddr + TINY_CHUNK - 1), TINY_CHUNK);
            *count += TINY_CHUNK;
        }
        curr = curr->next;
    }
}

static void show_small(size_t *count)
{
    t_zone *curr = zones[SMALL];

    ft_printf(1, "SMALL : %p\n", (void *)curr);
    while (curr)
    {
        for (int i = 0; i < 128; i++)
        {
            if (checkBit(curr->bitmap, i) == 0)
                continue;
            void *beginAddr = (void *)((void *)curr + sizeof(t_zone) + (i * SMALL_CHUNK));
            ft_printf(1, "%p - %p : %d bytes\n", beginAddr, (void *)(beginAddr + SMALL_CHUNK - 1), SMALL_CHUNK);
            *count += SMALL_CHUNK;
        }
        curr = curr->next;
    }
}

static void show_large(size_t *count)
{
    t_zone *curr = zones[LARGE];

    ft_printf(1, "LARGE : %p\n", (void *)curr);
    while (curr)
    {
        void *beginAddr = (void *)((void *)curr + sizeof(t_zone));
        ft_printf(1, "%p - %p : %d bytes\n", beginAddr, (void *)(beginAddr + curr->bitmap[0] - 1), curr->bitmap[0]);
        *count += curr->bitmap[0];
        curr = curr->next;
    }
}

EXPORT void show_alloc_mem()
{
    size_t count = 0;
    pthread_mutex_lock(&mutexes[TINY]);
    show_tiny(&count);
    pthread_mutex_unlock(&mutexes[TINY]);
    pthread_mutex_lock(&mutexes[SMALL]);
    show_small(&count);
    pthread_mutex_unlock(&mutexes[SMALL]);
    pthread_mutex_lock(&mutexes[LARGE]);
    show_large(&count);
    pthread_mutex_lock(&mutexes[LARGE]);
    ft_printf(1, "Total : %u bytes\n", count);
}
