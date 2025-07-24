/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 14:12:49 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/24 14:29:24 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_quoted(char const *s1, char const set, int index)
{
	int		i;
	bool	sp_quote;
	bool	db_quote;

	if (s1[index] != set)
		return (false);
	sp_quote = false;
	db_quote = false;
	i = 0;
	while (i < index)
	{
		if (s1[i] == '\'' && !db_quote)
			sp_quote = !sp_quote;
		else if (s1[i] == '\"' && !sp_quote)
			db_quote = !db_quote;
		i++;
	}
	if (!sp_quote && !db_quote)
			return (true);
	return (false);
}

static int	ft_count_word(char const *s1, char const set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s1[i])
	{
		if (!is_quoted(s1, set, i))
		{
			count++;
			while (s1[i] && !is_quoted(s1, set, i))
				i++;
		}
		else
			i++;
	}
	return (count);
}

static size_t	ft_word_len(char const *s1, char const set, size_t start)
{
	size_t	i;
	size_t	size;

	i = start;
	size = 0;
	while (s1[i] && !is_quoted(s1, set, i))
	{
		size++;
		i++;
	}
	return (size);
}

static void	fr_tb(char **tab, int j)
{
	if (tab)
		while (j >= 0)
			free(tab[j--]);
	free(tab);
}

char	**ft_split_exp(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		wlen;

	if (!s || !s[0])
		return (NULL);
	tab = ft_calloc (ft_count_word(s, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (j < ft_count_word(s, c))
	{
		while (s[i] == c)
			i++;
		wlen = ft_word_len(s, c, i);
		tab[j] = ft_calloc(wlen + 1, sizeof(char));
		if (!tab[j])
			return (fr_tb(tab, j), NULL);
		ft_memcpy(tab[j++], &s[i], wlen);
		i += wlen;
	}
	return (tab);
}
