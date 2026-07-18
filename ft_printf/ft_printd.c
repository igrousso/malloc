/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:03:03 by igrousso          #+#    #+#             */
/*   Updated: 2024/11/18 06:13:04 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void    ft_putnbr(int fd, int nb)
{
    if (nb < 0)
    {
        if (nb == -2147483648)
        {
            write(fd, "-2147483648", 11);
            return ;
        }
        write(1, "-", 1);
        nb = -nb;
    }
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

static size_t intlen(int nb)
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

int	ft_print_d(int fd, va_list params)
{
	int		c;

	c = va_arg(params, int);
	ft_putnbr(fd, c);
	return (intlen(c) + (c < 0 ? 1 : 0));
}
