/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:03:35 by igrousso          #+#    #+#             */
/*   Updated: 2024/11/18 07:07:14 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_xlow(va_list params)
{
	int		x;
	char	*str;
	size_t	len;

	x = va_arg(params, int);
	str = ft_ui_itoa_base(x);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
