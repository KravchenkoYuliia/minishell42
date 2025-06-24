/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:15:39 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/24 16:11:12 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_unquote(t_minishell **shl, char *value, int i, int j)
{
	bool	sp_quote;
	bool	db_quote;
	
	ft_bzero(value, 100000);
	sp_quote = false;
	db_quote = false;
	while ((*shl)->token_lst->value[i])
	{
		if ((*shl)->token_lst->value[i] == '\'' && !db_quote)
		{
			sp_quote = !sp_quote;
			i++;
		}
		else if ((*shl)->token_lst->value[i] == '\"' && !sp_quote)
		{	
			db_quote = !db_quote;
			i++;
		}
		if (((*shl)->token_lst->value[i] == '\'' && !sp_quote) 
			|| ((*shl)->token_lst->value[i] == '\"' && !db_quote))
			continue;
		value[j++] = (*shl)->token_lst->value[i++];
	}
	return(value);
}

char	*ft_update_token(char *value, char *var_value, int var_len, int index)
{
	int		i;
	int		j;
	int		l;
	char	*new_value;
	
	if (!var_value)
		var_value = NULL;
	new_value = ft_calloc(100000, 1);
	if (!new_value)
		return (NULL);
	i = 0;
	j = 0;
	l = 0;
	while(i < index)
		new_value[j++] = value[i++];
	while (var_value && var_value[l])
		new_value[j++] = var_value[l++];
	i += var_len + 1;
	while(value[i])
		new_value[j++] = value[i++];
	free(value);
	return (new_value);
}

void	ft_expand_b(t_minishell **shell, char *var, int index)
{
	(*shell)->token_lst->value = ft_strdup(
	ft_update_token((*shell)->token_lst->value , 
	ft_get_env(var, (*shell)->env, (*shell)->exit_status), 
	ft_strlen(var), index));
}

void	ft_expand_a(t_minishell *shell, char *var, int index)
{
	int i;
	int	j;
	
	ft_bzero(var, 100000);
	i = index + 1;
	while (shell->token_lst->value[i])
	{
		if (ft_isdigit(shell->token_lst->value[i]) 
		|| shell->token_lst->value[i] == '?')
		{
			var[0] = shell->token_lst->value[i];
			break;
		}
		else
		{
			j = 0;
			while (ft_redirs_lim(shell->token_lst->value[i]) 
			&& shell->token_lst->value[i] != '$')
			var[j++] = shell->token_lst->value[i++];
			break;
		}
	}
	ft_expand_b(&shell, var, index);
}

void	ft_expander(t_minishell *shl)
{
	int		index;
	t_token *head;
	char	*vl_bf;
	
	vl_bf = ft_calloc(100000, 1);
	if (!vl_bf)
		return ;
	head = shl->token_lst;
	while (shl->token_lst)
	{
		if (ft_strchr(shl->token_lst->value, '$') != 0 
			&& shl->token_lst->type != 2)
		{
			while (ft_is_expandable(shl->token_lst->value) != -2)
			{	
				index = ft_is_expandable(shl->token_lst->value);
				ft_expand_a(shl, vl_bf, index);
			}
		}
		if (ft_is_unquotable(shl->token_lst->type, shl->token_lst->value))
			shl->token_lst->value = ft_strdup(ft_unquote(&shl, vl_bf, 0, 0));
		shl->token_lst = shl->token_lst->next;
	}
	free(vl_bf);
	shl->token_lst = head;
}
	
/* i++;
			j = 0;
			while (ft_isdigit((*shell)->token_lst->value[i]) 
				|| (*shell)->token_lst->value[i] == '?')
					var[j++] = (*shell)->token_lst->value[i++];
			if (var)
				ft_expand_b(shell, var, index);
			while (ft_isalpha((*shell)->token_lst->value[i])
				|| (*shell)->token_lst->value[i] == '_')
				var[j++] = (*shell)->token_lst->value[i++];
			break; */