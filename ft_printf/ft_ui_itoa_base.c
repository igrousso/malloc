/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ui_itoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 06:56:47 by igrousso          #+#    #+#             */
/*   Updated: 2024/11/18 07:08:21 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	len_base(unsigned int n)
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

void	zero(unsigned int nb, char *str)
{
	if (nb == 0)
	{
		str[0] = '0';
		str[1] = '\0';
	}
}

char	*restint(unsigned int nb, char *str)
{
	int				i;
	unsigned int	n;

	n = nb;
	i = len_base(nb) - 1;
	while (nb != 0)
	{
		str[i--] = "0123456789abcdef"[nb % 16];
		nb = nb / 16;
	}
	str[(len_base(n))] = '\0';
	return (str);
}

char	*ft_ui_itoa_base(unsigned int n)
{
	unsigned int	nb;
	char			*str;

	nb = n;
	str = malloc(sizeof(char) * len_base(nb) + 1);
	if (str == NULL)
		return (NULL);
	zero(nb, str);
	return (restint(nb, str));
}
