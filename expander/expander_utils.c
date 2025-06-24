/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 08:45:34 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/17 11:17:15 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_env(char *var, t_env *env)
{
	int		i;
	t_env	*cursor;
	
	i = 0;
	cursor = env;
	while (cursor)
	{
		if (ft_strstr(cursor->line, var) != NULL && cursor->line[ft_strlen(var)] == '=')
		{
			while (cursor->line[i] != '=')
				i++;
			return(ft_strdup(cursor->line + i + 1));
		}
		cursor = cursor->next;
	}
	return (NULL);
}

bool	ft_is_expandable(char *value, int i)
{
	bool	sp_quote;
	bool	db_quote;

	sp_quote = false;
	db_quote = false;
	while (value[i])
	{
		if (value[i] == 39 && !db_quote)
			sp_quote = true;
		else if (value[i] == 34 && !sp_quote)
			db_quote = true;
		if (value[i] == '$' && !(value[i + 1] == 39 
			|| value[i + 1] == 34 || value[i + 1] == 32) && !sp_quote)
			return (true);
		i++;
		if (value[i] && ((value[i] == 39 && sp_quote) 
			|| (value[i] == 34 && db_quote)))
			break;
	}
	return (false);
}
