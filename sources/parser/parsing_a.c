/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:37:20 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/30 12:03:43 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_if_quotes_b(char *input, int start, char *value_buf, int buf_start)
{
	bool	db_quote;
	bool	sp_quote;

	db_quote = false;
	sp_quote = false;
	while (input[start])
	{	
		if (input[start] == '\'' && !db_quote)
			sp_quote = !sp_quote;
		else if (input[start] == '\"' && !sp_quote)
			db_quote = !db_quote;
		if ((input[start] == '<' || input[start] == '>' 
			|| input[start] == '|') && (!db_quote && !sp_quote))
			break ;
		value_buf[buf_start++] = input[start++];
	}
	value_buf[buf_start] = '\0';
}

t_token	*ft_if_quotes_a(char *input, int start)
{
	t_token	*token;
	char	*value_buf;

	value_buf = ft_calloc(ft_strlen(input), 1);
	if (!value_buf)
		return (NULL);
	ft_if_quotes_b(input, start, value_buf, 0);
	token = new_token_nd(value_buf, WORD, ft_strlen(value_buf));
	return (token);
}

t_token	*ft_if_command(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	int		j;

	value_buf = ft_calloc(ft_strlen(input), 1);
	if (!value_buf)
		return (NULL);
	j = 0;
	while ((input[start] != 39 && input[start] != 34 && input[start] != 124
			&& input[start] != 60 && input[start] != 62 && input[start] != 32)
		&& input[start])
		value_buf[j++] = input[start++];
	if (input[start] == 39 || input[start] == 34)
		ft_if_quotes_b(input, start, value_buf, j);
	else
		value_buf[j] = '\0';
	token = new_token_nd(value_buf, WORD, ft_strlen(value_buf));
	return (token);
}

t_token	*ft_if_pipe(char *input, int start)
{
	t_token	*token;
	char	*value_buf;

	(void)input;
	(void)start;
	value_buf = ft_calloc(ft_strlen(input), 1);
	if (!value_buf)
		return (NULL);
	value_buf[0] = 124;
	value_buf[1] = '\0';
	token = new_token_nd(value_buf, PIPE, 1);
	return (token);
}
