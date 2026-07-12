/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:01:43 by igrousso          #+#    #+#             */
/*   Updated: 2024/11/18 06:24:50 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_s(va_list params)
{
	size_t	len;
	char	*str;

	str = va_arg(params, char *);
	if (str == NULL)
		return (write(1, "(null)", 6));
	len = ft_strlen(str);
	write(1, str, len);
	return (len);
}
