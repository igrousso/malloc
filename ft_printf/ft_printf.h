/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igrousso <igrousso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:40:58 by igrousso          #+#    #+#             */
/*   Updated: 2024/11/18 07:08:52 by igrousso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// # include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		ft_printf(int fd, const char *s, ...);
int		ft_print_c(int fd, va_list params);
int		ft_print_s(int fd, va_list params);
int		ft_print_p(int fd, va_list params);
int		ft_print_d(int fd, va_list params);
int		ft_print_u(int fd, va_list params);
int		ft_intstrchr(const char *s, int c);
char	*ft_toupper_string(char *x);
size_t ft_strlen(char *str);
char ft_toupper(char c);

#endif