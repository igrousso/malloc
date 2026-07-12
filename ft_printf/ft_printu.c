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

int	ft_print_u(va_list params)
{
	unsigned int	c;
	size_t			len;
	char			*str;

	c = va_arg(params, unsigned int);
	str = ft_longitoa(c);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
