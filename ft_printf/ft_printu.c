/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:03:21 by igrousso          #+#    #+#             */
/*   Updated: 2024/11/18 06:14:08 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void    ft_putnbr(int fd, unsigned int nb)
{
    if (nb >= 10)
    {
        ft_putnbr(fd, nb / 10);
        ft_putnbr(fd, nb % 10);
    }
    else
	{
		char c = nb + '0';
		write(fd, &c, 1);
	}
}

static size_t intlen(unsigned int nb)
{
	if (nb == 0)
		return 1;
	int count = 0;
	while (nb)
	{
		nb /= 10;
		count++;
	}
	return count;
}

int	ft_print_u(int fd, va_list params)
{
	unsigned int	c;

	c = va_arg(params, unsigned int);
	ft_putnbr(fd, c);
	return (intlen(c));
}
