/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:51:40 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/24 10:16:54 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_check_unclosed_quotes(char *input)
{
	int		i;
	int		sp;
	int		db;

	i = 0;
	sp = 0;
	db = 0;
	while (input[i])
	{
		if (input[i] == 39 && db == 0)
			sp++;
		else if (input[i] == 34 && sp == 0)
			db++;
		if (sp % 2 == 0)
			sp = 0;
		if (db % 2 == 0)
			db = 0;
		i++;
	}
	if (sp % 2 != 0 || db % 2 != 0)
		return (false);
	return (true);
}

bool	ft_check_pipes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[0] == 124 || input[ft_strlen(input) - 1] == 124)
			return (false);
		if (input[i] == 124 && input[i + 1] == 124)
			return (false);
		if (input[i] == 124 && (input[i + 1] == 32 || input[i + 1] == 9))
		{
			i++;
			while (input[i] == 32 || input[i] == 9)
				i++;
			if (input[i] == 124)
				return (false);
		}
		i++;
	}
	return (true);
}

int	ft_check_redirs(char *input)
{
	size_t	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			if ((input[i] == '>' && input[i + 1] == '>')
				|| (input[i] == '<' && input[i + 1] == '<'))
				i += 2;
			else
				i++;
			while (input[i] && input[i] == ' ')
				i++;
			if (input[i] == '|' || input[i] == '\0'
				|| input[i] == '>' || input[i] == '<')
				return (i);
			i++;
		}
		else
			i++;
	}
	return (-1);
}

bool	ft_lexer(char *input)
{
	int	redir_check;

	if (!input)
		return (false);
	redir_check = ft_check_redirs(input);
	if (!ft_check_unclosed_quotes(input))
		return (lexer_err_handler(1, 'c'), false);
	if (!ft_check_pipes(input))
		return (lexer_err_handler(2, 'c'), false);
	if (redir_check != -1)
	{
		if (input[redir_check] == '\0'
			|| input[redir_check] == 34
			|| input[redir_check] == 39)
		{
			printf("%s: ", SHELL_NAME_ERROR);
			printf("syntax error near unexpected token 'new_line'\n");
			return (false);
		}	
		else
			return (lexer_err_handler(3, input[redir_check]), false);
	}
	return (true);
}
