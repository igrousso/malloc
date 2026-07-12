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

int		ft_printf(const char *s, ...);
int		ft_print_c(va_list params);
int		ft_print_s(va_list params);
int		ft_print_p(va_list params);
int		ft_print_d(va_list params);
int		ft_print_u(va_list params);
int		ft_print_xlow(va_list params);
int		ft_print_xup(va_list params);
char	*ft_ul_itoa_base(unsigned long n);
int		ft_intstrchr(const char *s, int c);
char	*ft_toupper_string(char *x);
int		longlen(long nb);
char	*ft_longitoa(long nb);
char	*ft_ui_itoa_base(unsigned int n);
char	*restint(unsigned int nb, char *str);
void	zero(unsigned int nb, char *str);
int		len_base(unsigned int n);
size_t ft_strlen(char *str);
char ft_toupper(char c);

#endif