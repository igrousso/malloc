/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:04:58 by igrousso          #+#    #+#             */
/*   Updated: 2024/11/18 07:02:08 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_p(va_list params)
{
	void	*ptr;

	ptr = va_arg(params, void *);
	if (ptr == NULL)
		return (write(1, "(nil)", 5));

	char buf[19];
	unsigned long n = (unsigned long)ptr;
	int i = 18;

	buf[i--] = 0;
	if (n == 0)
		buf[i--] = '0';
	while (n)
	{
		buf[i--] = "0123456789abcdef"[n % 16];
		n /= 16;
	}
	buf[i--] = 'x';
	buf[i] = '0';
	write(1, buf + i, 18 - i);
	return (18 - i);
}
