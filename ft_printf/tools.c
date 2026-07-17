/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:33:44 by igrousso          #+#    #+#             */
/*   Updated: 2024/11/18 01:48:43 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_intstrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return (1);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return (1);
	return (0);
}

char	*ft_toupper_string(char *x)
{
	size_t	i;

	i = 0;
	while (x[i] != '\0')
	{
		x[i] = ft_toupper(x[i]);
		i++;
	}
	return (x);
}

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

