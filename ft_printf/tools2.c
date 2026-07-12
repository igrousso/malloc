#include "ft_printf.h"

size_t ft_strlen(char *str)
{
    int i = 0;

    while (str[i++]);
    return i;
}

char ft_toupper(char c)
{
    if (c >= 'z' && c <= 'a')
        return c - 32;
    return c;
}