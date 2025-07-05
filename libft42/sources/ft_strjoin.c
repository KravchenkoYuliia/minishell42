/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 09:42:03 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/05 17:51:15 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	unsigned int	len;
	char			*array;
	int				i;
	int				j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	array = malloc(sizeof(char) * len + 1);
	if (!array)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	while (s1 && s1[i])
	{
		array[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2 && s2[j])
	{
		array[i + j] = s2[j];
		j++;
	}
	free(s2);
	array[i + j] = '\0';
	return (array);
}
