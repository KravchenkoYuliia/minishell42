/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:56:41 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/03 11:46:03 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_parsing_a(char *input, int i)
{
	t_token	*token;

	token = NULL;
	if (input[i] == 39 || input[i] == 34)
		token = ft_if_quotes_a(input, i);
	else if (input[i] == 124)
		token = ft_if_pipe(input, i);
	else
		token = ft_if_command(input, i);
	return (token);
}

t_token	*ft_parsing_b(char *input, int i)
{
	t_token	*token;

	token = NULL;
	if (input[i] == 60)
	{
		if (input[i + 1] == 60)
			token = ft_if_heredoc(input, i + 2);
		else
			token = ft_if_input(input, i + 1);
	}
	else if (input[i] == 62)
	{
		if (input[i + 1] == 62)
			token = ft_if_append(input, i + 2);
		else
			token = ft_if_output(input, i + 1);
	}
	return (token);
}

t_token	*ft_parser(char *input, int i)
{
	t_token	*token_lst;
	t_token	*new_token;

	token_lst = NULL;
	new_token = NULL;
	while (i < ft_strlen(input))
	{
		if ((input[i] == 39 || input[i] == 34 || input[i] == 124)
			|| ft_redirs_lim(input[i]))
			new_token = ft_parsing_a(input, i);
		else if (input[i] == 60 || input[i] == 62)
			new_token = ft_parsing_b(input, i);
		if (new_token && (input[i] != 32 && input[i] != 9))
		{
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 32 || input[i] == 9)
			i++;
		else
			return (parser_err_handler(token_lst, 1), token_lst);
	}
	return (token_lst);
}
