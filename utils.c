// #include "malloc.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void *ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
    uint8_t *dst1 = (uint8_t *)dst;
    const uint8_t *src1 = (uint8_t *)src;

    while (n > 0 && (uintptr_t)dst1 & 7)  // & 7 pour vérifier l'alignement sur 8
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
        *dst1++ = *src1++;
    return dst;
}

void *ft_memset(void *s, int c, size_t n)
{
    uint8_t *src = (uint8_t *)s;
    
    while (n > 0 && (uintptr_t)src & 7)
    {
        *src++ = c;
        n--;
    }
    uintptr_t *src8 = (uintptr_t *)src;
    uintptr_t mask = (uint8_t)c;
    mask |= mask << 8;
    mask |= mask << 16;
    mask |= mask << 32;
    while (n >= 8)
    {
        *src8++ = mask;
        n -= 8;
    }
    src = (uint8_t *)src8;
    while (n--)
        *src++ = c;
    return s;
}

int ft_atoi(char *s)
{
    if (!s)
        return 0;
    int i = 0;
    while (s[i] >= 7 && s[i] <= 13)
        i++;
    int nb = 0;
    int neg = 1;
    if (s[i] == '-' || s[i] == '+')
        neg = (s[i++] == '-' ? -1 : 1);
    while (s[i] >= '0' && s[i] <= '9')
		nb = nb * 10 + (s[i++] - '0');
    return nb * neg;
}
