#include "malloc.h"

void print_x(unsigned char c)
{
    char buf[2] = {'0', '0'};
    int i = 1;
    while (c)
    {
        buf[i--] = "0123456789abcdef"[c % 16];
        c /= 16;
    }
    write(1, buf, 2);
}

void display_ex(void *ptr, int mode)
{
    for (int i = 0; i < mode;)
    {
        ft_printf(1, "%p  ", ptr + i);
        char buf[8] = {'.', '.', '.', '.', '.', '.', '.', '.'};
        int k = 0;
        for (int j = 0 ;i < mode && j < 8; i++, j++)
        {
            char c = *(char *)(ptr + i);
            if (c < 127 && c > 31)
                buf[j] = c;
            print_x(c);
            ft_printf(1, " ");
            k = j + 1;
        }
        for (int j = 0; j < k; j++)
            ft_printf(1, " %c", buf[j]);
        ft_printf(1, "\n");
    }
}

void display_ex_tiny()
{
    t_zone *curr = zones[TINY];
    bool entry = 0;

    ft_printf(1, "TINY : %p\n\n", (void *)curr);
    int n = 1;
    while (curr)
    {
        ft_printf(1, "zone %d: %p\n", n, curr);
        for (int i = 0; i < 128; i++)
        {
            if (checkBit(curr->bitmap, i) == 0)
            {
                if (entry == 1) {
                    entry = 0;
                    ft_printf(1, "\n");
                }
                continue;
            }
            entry = 1;
            void *addr = (void *)((void *)curr + sizeof(t_zone) + (i * TINY_CHUNK));
            display_ex(addr, TINY_CHUNK);
        }
        if (entry == 1) {
            entry = 0;
            ft_printf(1, "\n");
        }
        n++;
        curr = curr->next;
    }
}

void display_ex_small()
{
    t_zone *curr = zones[SMALL];
    bool entry = 0;

    ft_printf(1, "SMALL : %p\n\n", (void *)curr);
    int n = 1;
    while (curr)
    {
        ft_printf(1, "zone %d: %p\n", n, curr);
        for (int i = 0; i < 128; i++)
        {
            if (checkBit(curr->bitmap, i) == 0)
            {
                if (entry == 1) {
                    entry = 0;
                    ft_printf(1, "\n");
                }
                continue;
            }
            entry = 1;
            void *addr = (void *)((void *)curr + sizeof(t_zone) + (i * SMALL_CHUNK));
            display_ex(addr, SMALL_CHUNK);
        }
        if (entry == 1) {
            entry = 0;
            ft_printf(1, "\n");
        }
        n++;
        curr = curr->next;
    }
}

void display_ex_large()
{
    t_zone *curr = zones[LARGE];

    ft_printf(1, "LARGE : %p\n", (void *)curr);
    int n = 1;
    while (curr)
    {
        ft_printf(1, "zone %d: %p\n", n, curr);
        void *addr = (void *)((void *)curr + sizeof(t_zone));
        display_ex(addr, curr->bitmap[0] - sizeof(t_zone));
        ft_printf(1, "\n");
        n++;
        curr = curr->next;
    }
    ft_printf(1, "\n");
}

void show_alloc_mem_ex()
{
    pthread_mutex_lock(&mutexes[TINY]);
    display_ex_tiny();
    pthread_mutex_unlock(&mutexes[TINY]);
    pthread_mutex_lock(&mutexes[SMALL]);
    display_ex_small();
    pthread_mutex_unlock(&mutexes[SMALL]);
    pthread_mutex_lock(&mutexes[LARGE]);
    display_ex_large();
    pthread_mutex_unlock(&mutexes[LARGE]);
}