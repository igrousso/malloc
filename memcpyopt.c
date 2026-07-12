// #include "malloc.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void *ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
    uint8_t *dst1 = (uint8_t *)dst;
    const uint8_t *src1 = (uint8_t *)src;

    while (n > 0 && (uintptr_t)dst1 & 7)
    {
        *dst1++ = *src1++;
        n--;
    }
    uintptr_t *dst8 = (uintptr_t *)dst1;
    const uintptr_t *src8 = (const uintptr_t *)src1;
    while (n >= 8)
    {
        *dst8++ = *src8++;
        n -= 8;
    }
    dst1 = (uint8_t *)dst8;
    src1 = (uint8_t *)src8;
    while (n--)
    {
        *dst1++ = *src1++;
    }
    return dst;
}