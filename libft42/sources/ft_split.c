/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                 unt = 0;
 23     while (str[i])
 24     {
 25         if (str[i] == c && str[i - 1] != c && i != 0)
 26             count++; 
 27         if ((str[i + 1] == '\0') && str[i] != c)
 28             count++;
 29         i++;
 30     }
 31     return (count);
               +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:22:25 by yukravch          #+#    #+#             */
/*   Updated: 2024/11/18 20:47:09 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	*ft_free_malloc(char **array, size_t word)
{
	size_t	i;

	i = 0;
	while (i < word)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static size_t	ft_count_words(char const *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c && str[i - 1] != c && i != 0)
			count++;
		if ((str[i + 1] == '\0') && str[i] != c)
			count++;
		i++;
	}
	return (count);
}

static char	*ft_print_words(const char *str, char c)
{
	size_t	size;
	char	*array;
	size_t	i;

	i = 0;
	size = 0;
	while (str[size] && str[size] != c)
		size++;
	array = (char *)malloc(sizeof(char) * size + 1);
	if (!array)
		return (NULL);
	while (i < size)
	{
		array[i] = str[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	word;
	char	**array;

	i = 0;
	word = 0;
	if (!s)
		return (NULL);
	array = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (s[i] && word < ft_count_words(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		array[word] = ft_print_words(s + i, c);
		if (!array)
			return (ft_free_malloc(array, word));
		i += ft_strlen(array[word]);
		word++;
	}
	array[word] = 0;
	return (array);
}
