/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:48:16 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/16 14:03:03 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_buf_redirs(char *ipt, int srt, char *value_buf, int buf_start)
{
	bool	in_quote;
	int		start_bf;

	start_bf = srt;
	in_quote = false;
	while (ipt[srt] == 32 && ipt[srt])
		srt++;
	if ((ipt[srt] == 34 || ipt[srt] == 39) && !in_quote)
	{
		in_quote = true;
		value_buf[buf_start++] = ipt[srt++];
	}
	while (ipt[srt] && (rds_lim(ipt[srt]) || (!rds_lim(ipt[srt]) && in_quote)))
	{
		value_buf[buf_start++] = ipt[srt++];
		if ((ipt[srt] == 34 || ipt[srt] == 39) && in_quote
			&& (ipt[srt + 1] != 34 && ipt[srt + 1] != 39))
		{
			value_buf[buf_start++] = ipt[srt++];
			in_quote = false;
		}
		if ((!rds_lim(ipt[srt])) && in_quote)
			value_buf[buf_start++] = ipt[srt++];
	}
	return (srt - start_bf);
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
	free (value_buf);
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
	free (value_buf);
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
	free (value_buf);
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
	free (value_buf);
	return (token);
}
