/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:48:16 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/03 11:45:37 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_buf_redirs(char *input, int start, char *value_buf, int buf_start)
{
	bool	in_quote;
	int		start_bf;

	start_bf = start;
	in_quote = false;
	while (input[start] == 32 && input[start])
		start++;
	if ((input[start] == 34 || input[start] == 39) && !in_quote)
	{
		in_quote = true;
		value_buf[buf_start++] = input[start++];
	}
	while (input[start] && (ft_redirs_lim(input[start])
			|| (!ft_redirs_lim(input[start]) && in_quote)))
	{
		value_buf[buf_start++] = input[start++];
		if ((input[start] == 34 || input[start] == 39) && in_quote
			&& (input[start + 1] != 34 && input[start + 1] != 39))
		{
			value_buf[buf_start++] = input[start++];
			in_quote = false;
		}
		if ((!ft_redirs_lim(input[start])) && in_quote)
			value_buf[buf_start++] = input[start++];
	}
	return (start - start_bf);
}

t_token	*ft_if_heredoc(char *input, int start)
{
	int		incr;
	t_token	*token;
	char	*value_buf;

	value_buf = ft_calloc(ft_strlen(input) + 1, 1);
	if (!value_buf)
		return (NULL);
	incr = set_buf_redirs(input, start, value_buf, 0);
	token = new_token_nd(value_buf, HEREDOC, incr + 2);
	return (token);
}

t_token	*ft_if_input(char *input, int start)
{
	int		incr;
	t_token	*token;
	char	*value_buf;

	value_buf = ft_calloc(ft_strlen(input) + 1, 1);
	if (!value_buf)
		return (NULL);
	incr = set_buf_redirs(input, start, value_buf, 0);
	token = new_token_nd(value_buf, INPUT, incr + 1);
	return (token);
}

t_token	*ft_if_append(char *input, int start)
{
	int		incr;
	t_token	*token;
	char	*value_buf;

	value_buf = ft_calloc(ft_strlen(input) + 1, 1);
	if (!value_buf)
		return (NULL);
	incr = set_buf_redirs(input, start, value_buf, 0);
	token = new_token_nd(value_buf, APPEND, incr + 2);
	return (token);
}

t_token	*ft_if_output(char *input, int start)
{
	int		incr;
	t_token	*token;
	char	*value_buf;

	value_buf = ft_calloc(ft_strlen(input) + 1, 1);
	if (!value_buf)
		return (NULL);
	incr = set_buf_redirs(input, start, value_buf, 0);
	token = new_token_nd(value_buf, OUTPUT, incr + 1);
	return (token);
}
