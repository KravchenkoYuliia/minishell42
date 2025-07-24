/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:04:24 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/24 11:03:41 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_quote_or_not_quote(char *limiter)
{
	int	i;

	i = 0;
	while (limiter[i])
	{
		if (limiter[i] == SINGLE_QUOTE || limiter[i] == DOUBLE_QUOTE)
			return (true);
		i++;
	}
	return (false);
}

char	*ft_unquote_limiter(char *unquote_me)
{
	char	*limiter;

	limiter = ft_calloc(sizeof(char), ft_strlen(unquote_me));
	if (!limiter)
		return (NULL);
	limiter = ft_quotes(unquote_me, limiter);
	return (limiter);
}

char	*ft_quotes(char *has_quotes, char *result)
{
	int		i;
	int		j;
	bool	single_quote;
	bool	double_quote;

	i = 0;
	j = 0;
	single_quote = false;
	double_quote = false;
	while (has_quotes[i])
	{
		if (has_quotes[i] == SINGLE_QUOTE && !double_quote)
			single_quote = !single_quote;
		else if (has_quotes[i] == DOUBLE_QUOTE && !single_quote)
			double_quote = !double_quote;
		if (((has_quotes[i] == SINGLE_QUOTE && double_quote)
				|| (has_quotes[i] == DOUBLE_QUOTE && single_quote))
			|| (has_quotes[i] != SINGLE_QUOTE
				&& has_quotes[i] != DOUBLE_QUOTE))
			result[j++] = has_quotes[i++];
		else
			i++;
	}
	return (result);
}
