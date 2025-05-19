/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:25:52 by yukravch          #+#    #+#             */
/*   Updated: 2025/02/17 11:51:07 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

size_t	ft_putstr_printf(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
	{
		ft_putstr_printf("(null)");
		return (6);
	}
	while (str[i])
	{
		ft_putchar_printf(str[i]);
		i++;
	}
	return (i);
}
