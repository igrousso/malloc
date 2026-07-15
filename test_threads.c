#include "malloc.h"

void *routine(void *p)
{
    int* i = (int *)p;
    for (int j = 0; j < 1000; j++)
    {
        void * ptr = malloc(10 + ((*i % 3) * 3000));
        void *ptr2 = realloc(ptr, 54 + ((*i % 3) * 3000));
        free(ptr2);
    }
    free(p);
    return NULL;
}

int main()
{
    pthread_t ths[50];
    for (size_t i = 0; i < 50; i++)
    {
        size_t *arg = malloc(sizeof(size_t));
        *arg = i;
        pthread_create(&ths[i], NULL, &routine, arg);
    }
    
    for (size_t i = 0; i < 50; i++)
    {
        pthread_join(ths[i], NULL);
    }
}