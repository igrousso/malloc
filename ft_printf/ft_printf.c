/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:40:32 by igrousso          #+#    #+#             */
/*   Updated: 2024/11/18 19:06:54 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_possibilities(const char *s, va_list params, int i)
{
	int	c;

	c = 0;
	if (s[i] == 'c')
		c += ft_print_c(params);
	else if (s[i] == 's')
		c += ft_print_s(params);
	else if (s[i] == 'p')
		c += ft_print_p(params);
	else if (s[i] == 'd')
		c += ft_print_d(params);
	else if (s[i] == 'i')
		c += ft_print_d(params);
	else if (s[i] == 'u')
		c += ft_print_u(params);
	else if (s[i] == '%')
	{
		write(1, "%", 1);
		c++;
	}
	return ((c - 2));
}

int	ft_printf(const char *s, ...)
{
	va_list	params;
	int		i;
	int		c;

	i = 0;
	c = 0;
	va_start(params, s);
	while (s[i] != '\0')
	{
		if (s[i] != '%')
			write(1, &s[i], 1);
		if (s[i] == '%')
		{
			i++;
			if (ft_intstrchr("cspdiux%", s[i]) == 1)
				c += check_possibilities(s, params, i);
		}
		i++;
	}
	va_end(params);
	return (c + i);
}

// #include <limits.h>

// int	main(void)
// {
// 	ft_printf("%d", ft_printf("%% %%"));
// 	printf("\n");
// 	ft_printf("%d", printf("%% %%"));
// 	return (0);
// }
