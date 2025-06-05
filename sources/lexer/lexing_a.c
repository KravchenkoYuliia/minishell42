/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_a.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:51:40 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/05 14:57:08 by lfournie         ###   ########.fr       */
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
	int	i;
	
	i = 0;
	while (input[i])
	{
		if (input[0] == 124 || input[ft_strlen(input) - 1] == 124)
			return (false);
		if (input[i] == 124 && input[i + 1] == 124)
			return (false);
		i++;
	}
	return (true);
}
	
bool	ft_lexer(char *input)
{
	if (!input)
		return (false);
	if (!ft_check_unclosed_quotes(input))
		return (lexer_err_handler(1, 'c'), false);
	if (!ft_check_pipes(input))
		return (lexer_err_handler(2, '|'), false);
	if (ft_check_redirs(input) != -1)
			return (lexer_err_handler(2, input[ft_check_redirs(input)]), false);
	return (true);
}
