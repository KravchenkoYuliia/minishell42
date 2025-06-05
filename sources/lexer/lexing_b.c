/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:02:27 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/05 13:55:48 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_check_redirs(char *input)
{
	size_t	i;
	bool	sp_quote;
	bool	db_quote;

	i = 0;
	sp_quote = false;
	db_quote = false;
	while (input[i])
	{
		if (input[i] == 60 || input[i] == 62)
		{
			if ((input[i] == 60 && input[i + 1] == 60)
				|| (input[i] == 62 && input[i + 1] == 62))
				i += 2;
			else
				i++;
			while (input[i] == 32)
				i++;
			while (input[i])
			{
				if (input[i] == 34 && !sp_quote)
					db_quote = true;
				else if (input[i] == 39 && !db_quote)
					sp_quote = true;
				if (input[i] == '\n')
					return (i);
				if ((!(ft_isalnum(input[i]) || input[i] == '.' || input[i] == '/')) && (!db_quote && !sp_quote))
					return (i);
				if ((input[i] == 34 && db_quote) || (input[i] == 39 && sp_quote))
				{
					sp_quote = false;
					db_quote = false;
				}
				i++;
			}	
		}
		else
			i++;
	}	
	return (-1);
}
