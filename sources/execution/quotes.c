/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 16:04:24 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/30 18:13:57 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
