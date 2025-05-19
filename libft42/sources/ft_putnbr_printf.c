/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:13:20 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/25 11:29:37 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

size_t	ft_putnbr_printf(long nb)
{
	size_t	arg_len;

	arg_len = 0;
	if (nb < 0)
	{
		ft_putchar_printf('-');
		nb *= -1;
		arg_len++;
	}
	if (nb >= 0 && nb <= 9)
	{
		ft_putchar_printf('0' + nb);
		arg_len++;
	}
	if (nb >= 10)
	{
		arg_len += ft_putnbr_printf(nb / 10);
		arg_len += ft_putnbr_printf(nb % 10);
	}
	return (arg_len);
}

size_t	ft_put_u_nbr_printf(unsigned int nb)
{
	size_t	arg_len;

	arg_len = 0;
	if (nb <= 9)
	{
		ft_putchar_printf('0' + nb);
		arg_len++;
	}
	if (nb >= 10)
	{
		arg_len += ft_putnbr_printf(nb / 10);
		arg_len += ft_putnbr_printf(nb % 10);
	}
	return (arg_len);
}
