/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 08:45:34 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/30 18:07:52 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_word_split(t_minishell **shell)
{
	int		i;
	char	**tab;
	t_token	*splited;
	t_token	*head;

	i = 1;
	tab = ft_split((*shell)->token_lst->value, ' ');
	(*shell)->token_lst->value = ft_strdup(tab[0]);
	free (tab[0]);
	head = (*shell)->token_lst;
	while (tab[i])
	{
		splited = new_token_nd(tab[i], WORD, 0);
		splited->next = (*shell)->token_lst->next;
		(*shell)->token_lst->next = splited;
		i++;
	}
	free (tab);
}

char	*ft_get_env(char *var, t_env *env, int exit_status)
{
	int		i;
	t_env	*cursor;

	i = 0;
	cursor = env;
	if (var[i] == '?')
		return (ft_itoa(exit_status));
	while (cursor)
	{
		if (ft_strstr(cursor->line, var) != NULL
			&& cursor->line[ft_strlen(var)] == '=')
		{
			while (cursor->line[i] != '=')
				i++;
			return (ft_strdup(cursor->line + i + 1));
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
	if (ft_strchr(value, '$') == NULL)
		return (-2);
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
	if (type == HEREDOC)
		return (false);
	if (ft_strchr(value, '\'') == 0 && ft_strchr(value, '\"') == 0)
		return (false);
	return (true);
}

bool	ft_is_splitable(char *value)
{
	int		i;
	bool	sp_quote;
	bool	db_quote;

	if (ft_strchr(value, ' ') == NULL || ft_strchr(value, '|') != NULL)
		return (false);
	sp_quote = false;
	db_quote = false;
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' && !db_quote)
			sp_quote = !sp_quote;
		else if (value[i] == '\"' && !sp_quote)
			db_quote = !db_quote;
		if (value[i] == ' ' && (!sp_quote && !db_quote))
			return (true);
		i++;
	}
	return (false);
}
