/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:19:50 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/25 11:25:56 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char			src;
	unsigned char	*dest;
	size_t			i;

	src = (char)c;
	dest = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		dest[i] = src;
		i++;
	}
	return (dest);
}
