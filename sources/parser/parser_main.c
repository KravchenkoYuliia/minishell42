/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:56:41 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/24 11:40:54 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_parsing_a(t_minishell *shell, int i)
{
	t_token	*token;

	token = NULL;
	if (shell->input[i] == 39 || shell->input[i] == 34)
		token = ft_if_quotes_a(shell, i);
	else if (shell->input[i] == 124)
		token = ft_if_pipe(shell, i);
	else
		token = ft_if_command(shell, i);
	return (token);
}

t_token	*ft_parsing_b(t_minishell *shell, int i)
{
	t_token	*token;

	token = NULL;
	if (shell->input[i] == 60)
	{
		if (shell->input[i + 1] == 60)
			token = ft_if_heredoc(shell, i + 2);
		else
			token = ft_if_input(shell, i + 1);
	}
	else if (shell->input[i] == 62)
	{
		if (shell->input[i + 1] == 62)
			token = ft_if_append(shell, i + 2);
		else
			token = ft_if_output(shell, i + 1);
	}
	return (token);
}

t_token	*ft_parser(t_minishell *shell, int i)
{
	t_token	*new_token;

	new_token = NULL;
	while (i < ft_strlen(shell->input))
	{
		if ((shell->input[i] == 39 || shell->input[i] == 34 
			|| shell->input[i] == 124)
			|| (rds_lim(shell->input[i]) && !ft_if_symbol(shell->input[i])))
			new_token = ft_parsing_a(shell, i);
		else if (shell->input[i] == 60 || shell->input[i] == 62)
			new_token = ft_parsing_b(shell, i);
		if (ft_if_symbol(shell->input[i]))
			i++;
		if (new_token && (shell->input[i] != 32 && shell->input[i] != 9))
		{
			i += new_token->incr;
			ft_lstadd_back_tok(&shell->token_lst, new_token);
		}
		else if (shell->input[i] == 32 || shell->input[i] == 9)
			i++;
		else if (shell->malloc_fail)
			return (NULL);
	}
	return (shell->token_lst);
}
