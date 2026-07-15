#include "malloc.h"

void show_tiny(size_t * count)
{
    pthread_mutex_lock(&mutexes[TINY]);
    t_zone *curr = zones[TINY];
    pthread_mutex_unlock(&mutexes[TINY]);

    ft_printf("TINY : %p\n", (void *)curr);
    pthread_mutex_lock(&mutexes[TINY]);
    while (curr)
    {
        for (int i = 0; i < 128; i++)
        {
            if (checkBit(curr->bitmap, i) == 0)
                continue;
            void *beginAddr = (void *)((void *)curr + sizeof(t_zone) + (i * TINY_CHUNK));
            pthread_mutex_unlock(&mutexes[TINY]);
            ft_printf("%p - %p : %d bytes\n", beginAddr, (void *)(beginAddr + TINY_CHUNK - 1), TINY_CHUNK);
            pthread_mutex_lock(&mutexes[TINY]);
            *count += TINY_CHUNK;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&mutexes[TINY]);
}

void show_small(size_t *count)
{
    pthread_mutex_lock(&mutexes[SMALL]);
    t_zone *curr = zones[SMALL];
    pthread_mutex_unlock(&mutexes[SMALL]);

    ft_printf("SMALL : %p\n", (void *)curr);
    pthread_mutex_lock(&mutexes[SMALL]);
    while (curr)
    {
        for (int i = 0; i < 128; i++)
        {
            if (checkBit(curr->bitmap, i) == 0)
                continue;
            void *beginAddr = (void *)((void *)curr + sizeof(t_zone) + (i * SMALL_CHUNK));
            pthread_mutex_unlock(&mutexes[SMALL]);
            ft_printf("%p - %p : %d bytes\n", beginAddr, (void *)(beginAddr + SMALL_CHUNK - 1), SMALL_CHUNK);
            pthread_mutex_lock(&mutexes[SMALL]);
            *count += SMALL_CHUNK;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&mutexes[SMALL]);
}

void show_large(size_t *count)
{
    pthread_mutex_lock(&mutexes[LARGE]);
    t_zone *curr = zones[LARGE];
    pthread_mutex_unlock(&mutexes[LARGE]);

    ft_printf("LARGE : %p\n", (void *)curr);
    pthread_mutex_lock(&mutexes[LARGE]);
    while (curr)
    {
        void *beginAddr = (void *)((void *)curr + sizeof(t_zone));
        pthread_mutex_unlock(&mutexes[LARGE]);
        ft_printf("%p - %p : %d bytes\n", beginAddr, (void *)(beginAddr + curr->bitmap[0] - 1), curr->bitmap[0]);
        pthread_mutex_lock(&mutexes[LARGE]);
        *count += curr->bitmap[0];
        curr = curr->next;
    }
    pthread_mutex_unlock(&mutexes[LARGE]);
}

EXPORT void show_alloc_mem()
{
    size_t count = 0;
    show_tiny(&count);
    show_small(&count);
    show_large(&count);
    ft_printf("Total : %u bytes\n", count);
}
