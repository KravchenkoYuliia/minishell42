/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:15:06 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/25 11:31:44 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	s_len;
	size_t	d_len;

	i = 0;
	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	if (d_len < siz)
	{
		while (src[i] && d_len + i < siz - 1)
		{
			dst[d_len + i] = src[i];
			i++;
		}
		dst[d_len + i] = '\0';
		return (d_len + s_len);
	}
	return (siz + s_len);
}
