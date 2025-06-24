/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 08:45:34 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/24 14:48:55 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* bool	ft_expand_split()
{} */

char	*ft_get_env(char *var, t_env *env, int exit_status)
{
	int		i;
	t_env	*cursor;
	
	i = 0;
	cursor = env;
	if (var[i] == '?')
		return (ft_itoa(exit_status));
	else
		while (cursor)
		{
			if (ft_strstr(cursor->line, var) != NULL 
				&& cursor->line[ft_strlen(var)] == '=')
			{
				while (cursor->line[i] != '=')
					i++;
				return(ft_strdup(cursor->line + i + 1));
			}
			cursor = cursor->next;
		}
	return (NULL);
}

int	ft_is_expandable(char *value)
{
	int		i;
	bool	sp_quote;
	bool	db_quote;

	sp_quote = false;
	db_quote = false;
	i = -1;
	while (value[++i])
	{
		if (value[i] == '\'' && !db_quote)
			sp_quote = !sp_quote;
		else if (value[i] == '\"' && !sp_quote)
			db_quote = !db_quote;
		if (value[i] == '$' && !(value[i + 1] == '\'' 
			|| value[i + 1] == '\"' || value[i + 1] == ' ') && !sp_quote)
			return (i);
	}
	return (-2);
}

bool	ft_is_unquotable(int type, char *value)
{
	if (type == 2)
		return (false);
	if (ft_strchr(value, '\'') == 0	&& ft_strchr(value, '\"') == 0)
		return (false);
	return (true);
}
