/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa_printf.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:29:47 by yukravch          #+#    #+#             */
/*   Updated: 2025/02/17 11:51:51 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include "libft.h"

void	ft_convert_hexa_printf(unsigned long d, char *base)
{
	if (d > 15)
	{
		ft_convert_hexa_printf(d / 16, base);
		ft_convert_hexa_printf(d % 16, base);
	}
	else
		ft_putchar_printf(base[d % 16]);
}

int	ft_count_hexa_printf(unsigned long d)
{
	unsigned long	count;

	count = 0;
	while (d != 0)
	{
		d /= 16;
		count++;
	}
	return (count);
}

int	ft_convert_pointer_printf(void *p)
{
	unsigned long	adresse;

	if (!p)
	{
		ft_putstr_printf("(nil)");
		return (5);
	}
	adresse = (unsigned long)p;
	return (ft_print_hexa_printf(adresse, 'p'));
}

int	ft_print_hexa_printf(unsigned long d, int c)
{
	char			*hex_min;
	char			*hex_maj;
	size_t			count;

	hex_min = "0123456789abcdef";
	hex_maj = "0123456789ABCDEF";
	if (d == 0)
	{
		ft_putchar_printf('0');
		return (1);
	}
	count = ft_count_hexa_printf(d);
	if (c == 'x')
		ft_convert_hexa_printf(d, hex_min);
	else if (c == 'X')
		ft_convert_hexa_printf(d, hex_maj);
	else if (c == 'p')
	{
		ft_putstr_printf("0x");
		count += 2;
		ft_convert_hexa_printf(d, hex_min);
	}
	return (count);
}
