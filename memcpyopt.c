#include "malloc.h"

void *ft_memcpyopt(void *restrict dst, const void *restrict src, size_t n)
{
    uintptr_t *dst8 = (uintptr_t *)dst;
    const uintptr_t *src8 = (uintptr_t *)src;
    for (; n > 0; n -= 8)
        *dst8++ = *src8++;
    return dst;
}