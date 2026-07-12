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

int	ft_print_d(va_list params)
{
	int		c;
	char	*str;
	size_t	len;

	c = va_arg(params, int);
	str = ft_longitoa(c);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
