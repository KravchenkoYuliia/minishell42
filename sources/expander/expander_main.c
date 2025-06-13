/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:15:39 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/13 13:33:37 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* void	ft_unquote(char *value)
{
	
} */

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

/* char	*ft_update_token(char *value, char *var)
{
} */

char	*ft_get_env(char *var, t_env *env)
{
	int		i;
	t_env	*cursor;
	
	i = 0;
	cursor = env;
	while (cursor)
	{
		if (ft_strstr(cursor->line, var) != NULL)
		{
			while (cursor->line[i] != '=')
				i++;
			return(ft_strdup(cursor->line + i + 1));
		}
		cursor = cursor->next;
	}
	return (NULL);
}

void	ft_expand_var(t_minishell **shell)
{
	int		i;
	int		j;
	char	value_buf[500];
	
	i = -1;
	while ((*shell)->token_lst->value[++i])
	{
		if ((*shell)->token_lst->value[i] == 34 || (*shell)->token_lst->value[i] == 39)
		{
			if (ft_is_expandable((*shell)->token_lst->value, i))
			{
				while ((*shell)->token_lst->value[i])
				{
					j = 0;
					if ((*shell)->token_lst->value[i] == '$')
					{
						while ((*shell)->token_lst->value[i] != 34 && (*shell)->token_lst->value[i] != 39)
						{	
							if ((*shell)->token_lst->value[i] == '$')
								i++;
							value_buf[j] = (*shell)->token_lst->value[i];
							j++;
							i++;
						}
						value_buf[j] = '\0';
						/* (*shell)->token_lst->value = */ 
						printf("%s\n", ft_get_env(value_buf, (*shell)->env));
					}
					i++;
				}
			}
			else
				break;
		}
		else if ((*shell)->token_lst->value[i] == '$')
		{
			j = 0;
			i++;
			while ((*shell)->token_lst->value[i] != '$' && (*shell)->token_lst->value[i])
			{	
				if ((*shell)->token_lst->value[i] == '$')
					i++;
				value_buf[j] = (*shell)->token_lst->value[i];
				j++;
				i++;
			}
			value_buf[j] = '\0';
			/* (*shell)->token_lst->value = */ 
			printf("%s\n", ft_get_env(value_buf, (*shell)->env));
		}		
	}
	
}

void	ft_expander(t_minishell *shell)
{
	//int		i;
	t_token 	*head;
	
	head = shell->token_lst;
	while (shell->token_lst)
	{
		if (ft_strchr(shell->token_lst->value, '$') != 0)
		{
			ft_expand_var(&shell);
			//ft_unquote(shell->token_lst->value);
		}
		shell->token_lst = shell->token_lst->next;
	}
	shell->token_lst = head;
} 
