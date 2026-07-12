/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 17:41:31 by igrousso          #+#    #+#             */
/*   Updated: 2024/11/18 06:55:33 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	intlen_base(unsigned long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 16;
		len++;
	}
	return (len);
}

void	if_zero(unsigned long nb, char *str)
{
	if (nb == 0)
	{
		str[0] = '0';
		str[1] = '\0';
	}
}

char	*rest(unsigned long nb, char *str)
{
	int				i;
	unsigned long	n;

	n = nb;
	i = intlen_base(nb) - 1;
	while (nb != 0)
	{
		str[i--] = "0123456789abcdef"[nb % 16];
		nb = nb / 16;
	}
	str[(intlen_base(n))] = '\0';
	return (str);
}

char	*ft_ul_itoa_base(unsigned long n)
{
	unsigned long	nb;
	char			*str;

	nb = n;
	str = malloc(sizeof(char) * intlen_base(nb) + 1);
	if (str == NULL)
		return (NULL);
	if_zero(nb, str);
	return (rest(nb, str));
}
