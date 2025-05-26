/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:56:41 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/26 14:03:07 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *ft_parser(char *input)
{
	t_token	*token_lst;
	t_token	*new_token;
	int		i;

	token_lst = NULL;
	i = 0;
	while (i < ft_strlen(input))
	{
		if (input[i] == 39 || input[i] == 34)
		{
			new_token = ft_if_quotes(input, i);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 124)
		{
			new_token = ft_if_pipe(input, i);
			i++;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 60 && input[i + 1] == 60)
		{
			new_token = ft_if_heredoc(input, i + 2);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 60 && input[i + 1] != 60)
		{
			new_token = ft_if_input(input, i + 1);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 62 && input[i + 1] == 62)
		{
			new_token = ft_if_append(input, i + 2);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 62 && input[i + 1] != 62)
		{
			new_token = ft_if_output(input, i + 1);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 32)
			i++;
		else
		{
			new_token = ft_if_command(input, i);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
	}
	return (token_lst);
}
