/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:44:15 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/09 19:05:07 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "ft_printf.h"

void	ft_print_bits(int i)
{
	int	count;

	count = 7;
	while (count >= 0)
	{
		if (1 & (i >> count))
			ft_printf("1");
		else
			ft_printf("0");
		count--;
	}
}
