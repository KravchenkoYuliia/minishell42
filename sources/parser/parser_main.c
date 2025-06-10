/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:56:41 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/27 15:15:31 by lfournie         ###   ########.fr       */
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

t_token *ft_parser(char *input)
{
	t_token	*token_lst;
	t_token	*new_token;
	int		i;

	token_lst = NULL;
	i = 0;
	while (i < ft_strlen(input))
	{
		if ((input[i] == 39 || input[i] == 34 || input [i] == 124) 
			|| ft_redirs_lim(input[i]))
		{
			new_token = ft_parsing_a(input, i);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 60 || input[i] == 62)
		{
			new_token = ft_parsing_b(input, i);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 32)
			i++;
	}
	return (token_lst);
}
