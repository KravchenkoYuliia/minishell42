/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:34:04 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/25 11:27:08 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "libft.h"

int	ft_charset_printf(char mand_arg, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (mand_arg == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_format_printf(char mand_arg, va_list arg)
{
	size_t	arg_len;

	arg_len = 0;
	if (mand_arg == 'd' || mand_arg == 'i')
		arg_len = ft_putnbr_printf(va_arg(arg, int));
	else if (mand_arg == 'u')
		arg_len = ft_put_u_nbr_printf(va_arg(arg, unsigned int));
	else if (mand_arg == 'c')
		arg_len = ft_putchar_printf(va_arg(arg, int));
	else if (mand_arg == 's')
		arg_len = ft_putstr_printf(va_arg(arg, char *));
	else if (mand_arg == 'x')
		arg_len = ft_print_hexa_printf(va_arg(arg, unsigned int), 'x');
	else if (mand_arg == 'X')
		arg_len = ft_print_hexa_printf(va_arg(arg, unsigned int), 'X');
	else if (mand_arg == 'p')
		arg_len = ft_convert_pointer_printf(va_arg(arg, void *));
	else if (mand_arg == '%')
		arg_len = ft_putchar_printf('%');
	return (arg_len);
}

int	ft_printf(const char *mand_arg, ...)
{
	va_list	arg;
	size_t	i;
	size_t	arg_len;

	i = 0;
	arg_len = 0;
	if (mand_arg == (NULL))
		return (-1);
	va_start(arg, mand_arg);
	while (mand_arg[i])
	{
		if (mand_arg[i] != '%')
			arg_len += ft_putchar_printf((char)mand_arg[i]);
		else if (mand_arg[i] == '%'
			&& ft_charset_printf(mand_arg[i + 1], "cspdiuxX%"))
		{
			arg_len += ft_format_printf(mand_arg[i + 1], arg);
			i++;
		}
		i++;
	}
	va_end(arg);
	return (arg_len);
}
