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

int	longlen(long nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_longitoa(long nb)
{
	long	n;
	int		sign;
	int		len;
	char	*str;

	n = nb;
	sign = 0;
	if (nb < 0)
	{
		sign = 1;
		n = -n;
	}
	len = longlen(nb) + sign;
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (sign == 1)
		str[0] = '-';
	while (len > sign)
	{
		str[--len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
