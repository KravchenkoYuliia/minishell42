/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:51:40 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/21 12:06:40 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_check_unclosed_quotes(char *input)
{
	int 	i;
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
		if ( db % 2 == 0)
			db = 0;
		i++;
	}
	if (sp % 2 != 0 || db % 2 != 0)
		return (false);
	return (true);
}

bool ft_check_pipes(char *input)
{
	
}



bool	ft_lexer(char *input)
{
	if (!input)
		return (false);
	if (!ft_check_unclosed_quotes(input))
		return (lexer_err_handler(1), false);
	if (!ft_check_pipes(input))
		return (lexer_err_handler(2), false);
	if (!ft_check_redir_heredoc(input))
		return (lexer_err_handler(3), false);
	if (!ft_check_redir_append(input))
		return (lexer_err_handler(4), false);
	if (!ft_check_redir_input(input))
		return (lexer_err_handler(5), false);
	if (!ft_check_redir_output(input))
		return (lexer_err_handler(6), false);
	return (true);
}
