/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printX.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:04:25 by igrousso          #+#    #+#             */
/*   Updated: 2024/11/18 07:07:19 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_xup(va_list params)
{
	char	*str;
	int		x;
	size_t	len;

	x = va_arg(params, int);
	str = ft_ui_itoa_base(x);
	str = ft_toupper_string(str);
	len = ft_strlen(str);
	write(1, str, len);
	free(str);
	return (len);
}
