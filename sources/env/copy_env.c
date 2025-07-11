/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 18:10:01 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/11 11:07:13 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstlast_env(t_env *lst)
{
	t_env	*s_temp;

	s_temp = lst;
	while (s_temp && s_temp->next != NULL)
			s_temp = s_temp->next;
	return (s_temp);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*s_temp;

	s_temp = ft_lstlast_env(*lst);
	if (!s_temp)
		*lst = new;
	else
		s_temp->next = new;
}

t_env	*ft_lstnew_env(void *content)
{
	t_env	*lst;

	lst = (t_env *)malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->line = content;
	lst->next = NULL;
	return (lst);
}

void	ft_change_last_line(t_minishell *shell, t_env **env)
{
	t_env	*temp;
	char	*content;

	temp = *env;
	content = ft_strdup("_=/usr/bin/env");
	if (!content)
		ft_malloc_failed(shell, ft_strlen("_=/usr/bin/env"), "ft_change_last_line");
	while (temp)
	{
		if (temp->line[0] == '_')
		{
			free(temp->line);
			temp->line = content;
		}
		temp = temp->next;
	}
}

void	ft_fill_env(t_minishell *shell, t_env **env_list, char **env)
{
	int		i;
	char	*content;
	t_env	*new;

	i = 0;
	content = NULL;
	while (env[i])
	{
		content = ft_strdup(env[i]);
		if (!content)
			ft_malloc_failed(shell, ft_strlen(env[i]), "ft_fill_env");
		new = ft_lstnew_env(content);
		if (!new)
		{
			free(content);
			ft_malloc_failed(shell, sizeof(t_env), "ft_fill_env");
		}
		ft_lstadd_back_env(env_list, new);
		i++;
	}
	ft_change_last_line(shell, env_list);
	//ft_handle_shlvl_in_list(*env_list);
	if (!*env_list)
		ft_export_forempty_env(shell);
}
