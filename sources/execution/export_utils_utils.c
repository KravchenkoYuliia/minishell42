/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 14:53:30 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/24 14:46:12 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_find_oldpwd_in_env(t_minishell *shell)
{
	t_env	*temp;

	temp = shell->env;
	while (temp)
	{
		if (!ft_strncmp(temp->line, "OLDPWD", 6))
			return (true);
		temp = temp->next;
	}
	return (false);
}

void	ft_export_oldpwd(t_minishell *shell)
{
	t_env	*new;
	char	*line;

	line = ft_strdup("OLDPWD=");
	if (!line)
		ft_malloc_failed(shell, ft_strlen("OLDPWD="), "ft_export_oldpwd");
	new = ft_lstnew_env(line);
	ft_lstadd_back_env(&shell->env, new);
}

bool	ft_check_var_name(char *name)
{
	int	i;

	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	i = 1;
	while (name[i] && name[i] != '=')
	{
		if (ft_isalnum(name[i]) || name[i] == '_')
			i++;
		else
			return (false);
	}
	return (true);
}

void	ft_export_path_forempty_env(t_minishell *shell, char *pwd)
{
	char	*env_path;
	t_env	*new;

	env_path = ft_strdup("_=/usr/bin/env");
	if (!env_path)
	{
		free(pwd);
		ft_malloc_failed(shell,
			ft_strlen("_=/usr/bin/env"), "ft_export_forempty_env");
	}
	new = ft_lstnew_env(env_path);
	if (!new)
	{
		free(env_path);
		ft_malloc_failed(shell, sizeof(t_env), "ft_export_forempty_env");
	}
	ft_lstadd_back_env(&shell->env, new);
}

void	ft_export_shlvl_forempty_env(t_minishell *shell, char *pwd)
{
	char	*shlvl;
	t_env	*new;

	shlvl = ft_strdup("SHLVL=1");
	if (!shlvl)
	{
		free(pwd);
		ft_malloc_failed(shell, ft_strlen("SHLVL=1"), "ft_export_forempty_env");
	}
	new = ft_lstnew_env(shlvl);
	if (!new)
	{
		free(shlvl);
		ft_malloc_failed(shell, sizeof(t_env), "ft_export_forempty_env");
	}
	ft_lstadd_back_env(&shell->env, new);
}
