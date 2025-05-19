/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:35:19 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/25 11:26:55 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>

int		ft_putchar_printf(int c);
size_t	ft_putstr_printf(char *str);
size_t	ft_putnbr_printf(long nb);
int		ft_print_hexa_printf(unsigned long d, int c);
int		ft_count_hexa_printf(unsigned long d);
int		ft_charset_printf(char mand_arg, char *charset);
int		ft_format_printf(char mand_arg, va_list arg);
int		ft_printf(const char *mand_arg, ...);
void	ft_convert_hexa_printf(unsigned long d, char *base);
int		ft_convert_pointer_printf(void *p);
size_t	ft_put_u_nbr_printf(unsigned int nb);

#endif
