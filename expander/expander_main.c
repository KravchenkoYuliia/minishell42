/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:15:39 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/17 13:26:01 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* void	ft_unquote(char *value)
{
	
} */



/* void	ft_update_token(t_minishell **shell, char *var)
{
	static int		i;
	static char		*new_value;
	
	new_value = malloc(100000);
	if (!new_value)
		return ;
	while((*shell)->token_lst->value[i])
	{
		
	}
	if ((*shell)->token_lst->value[i] == '\0')
	{}
} */

void	ft_expand_a(t_minishell **shell, char *var, int i)
{
	int	j;
	
	j = 0;
	i++;
	while ((*shell)->token_lst->value[i] != 34 && (*shell)->token_lst->value[i] != 39)
	{	
		if ((*shell)->token_lst->value[i] == '$')
			i++;
		var[j++] = (*shell)->token_lst->value[i++];
	}
	var[j] = '\0';
	printf("%s\n", ft_get_env(var, (*shell)->env));
}

void	ft_expand_b(t_minishell **shell, char *var, int i)
{
	int	j;
	
	j = 0;
	i++;
	while ((*shell)->token_lst->value[i] != '$' && (*shell)->token_lst->value[i])
	{	
		if ((*shell)->token_lst->value[i] == '$')
			i++;
		var[j++] = (*shell)->token_lst->value[i++];
	}
	var[j] = '\0';
	printf("%s\n", ft_get_env(var, (*shell)->env));
}

void	ft_expand_var(t_minishell **shell)
{
	int		i;
	char	*value_buf;
	
	value_buf = malloc(100000);
	if (!value_buf)
		return ;
	i = -1;
	while ((*shell)->token_lst->value[++i])
	{
		if ((*shell)->token_lst->value[i] == 34 || (*shell)->token_lst->value[i] == 39)
		{
			if (ft_is_expandable((*shell)->token_lst->value, i))
			{
				ft_expand_a(shell, value_buf, i);
				i += ft_strlen(value_buf);
			}
			else
				break;
		}
		else if ((*shell)->token_lst->value[i] == '$')
		{
			ft_expand_b(shell, value_buf, i);
			i += ft_strlen(value_buf);
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
		else
		{
			//ft_unquote(shell->token_lst->value);
		}
		shell->token_lst = shell->token_lst->next;
	}
	shell->token_lst = head;
} 
