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
	char	*str;
	size_t	len;

	ptr = va_arg(params, void *);
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	str = ft_ul_itoa_base((unsigned long)ptr);
	len = ft_strlen(str);
	write(1, "0x", 2);
	write(1, str, len);
	free(str);
	return ((len + 2));
}
