/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 15:02:27 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/04 15:28:09 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* int ft_check_redirs(char *input)
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
			while (input[i])
			{
				if ()
				if (input[i] == 34 && !sp_quote)
					db_quote = true;
				else if (input[i] == 39 && !db_quote)
					sp_quote = true;
				if ()
			}	
		}
		else
			i++;
	}	
	return (-1);
} */
