/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:37:20 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/24 11:45:04 by lfournie         ###   ########.fr       */
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

t_token	*ft_if_quotes_a(t_minishell *shell, int start)
{
	t_token	*token;
	char	*value_buf;

	value_buf = ft_calloc(ft_strlen(shell->input) + 1, 1);
	if (!value_buf)
		return (NULL);
	ft_if_quotes_b(shell->input, start, value_buf, 0);
	token = new_token_nd(value_buf, WORD, ft_strlen(value_buf));
	free (value_buf);
	return (token);
}

t_token	*ft_if_command(t_minishell *shell, int start)
{
	t_token	*token;
	char	*value_buf;
	int		j;

	value_buf = ft_calloc(ft_strlen(shell->input) + 1, 1);
	if (!value_buf)
		return (NULL);
	j = 0;
	while ((shell->input[start] != 39 && shell->input[start] != 34 && shell->input[start] != 124
			&& shell->input[start] != 60 && shell->input[start] != 62 && shell->input[start] != 32)
		&& shell->input[start])
		value_buf[j++] = shell->input[start++];
	if (shell->input[start] == 39 || shell->input[start] == 34)
		ft_if_quotes_b(shell->input, start, value_buf, j);
	token = new_token_nd(value_buf, WORD, ft_strlen(value_buf));
	if (!token)
	{
		shell->malloc_fail = true;
		shell->malloc_fail_size = ft_strlen(value_buf);
	}
	free (value_buf);
	return (token);
}

t_token	*ft_if_pipe(t_minishell *shell, int start)
{
	t_token	*token;
	char	*value_buf;

	(void)start;
	value_buf = ft_calloc(ft_strlen(shell->input) + 1, 1);
	if (!value_buf)
		return (NULL);
	value_buf[0] = 124;
	value_buf[1] = '\0';
	token = new_token_nd(value_buf, PIPE, 1);
	free (value_buf);
	return (token);
}
