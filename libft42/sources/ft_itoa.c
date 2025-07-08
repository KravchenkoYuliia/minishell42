/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:19:44 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/08 14:11:10 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(int n)
{
	int	size;

	if (n == -2147483648)
		n += 1;
	size = 0;
	if (n == 0)
		size++;
	if (n < 0)
	{
		n *= -1;
		size++;
	}
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*dest;
	int		size;
	long	n_temp;

	size = ft_size(n);
	n_temp = n;
	if (n_temp < 0)
		n_temp *= -1;
	dest = ft_calloc(size + 1, sizeof(char));
	if (!dest)
		return (0);
	i = size;
	while (i > 0)
	{
		dest[i - 1] = n_temp % 10 + 48;
		n_temp /= 10;
		i--;
	}
	if (n < 0)
		dest[i] = '-';
	return (dest);
}
