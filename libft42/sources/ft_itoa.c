/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:23:48 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/25 11:24:14 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_strlen_n(int n)
{
	long int	len;
	long int	n_temp;

	len = 0;
	n_temp = n;
	if (n_temp < 0)
	{	
		len++;
		n_temp *= -1;
	}
	while (n_temp != 0)
	{
		n_temp /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*array;
	long int	i;
	long int	n_temp;

	n_temp = n;
	i = ft_strlen_n(n);
	if (n == 0)
		return (ft_strdup("0"));
	array = (char *)ft_calloc(ft_strlen_n(n) + 1, sizeof(char));
	if (!array)
		return (NULL);
	if (n_temp < 0)
		n_temp *= -1;
	while (i > 0)
	{
		array[i - 1] = n_temp % 10 + '0';
		n_temp /= 10;
		i--;
	}
	if (n < 0)
		array[i] = '-';
	return (array);
}
