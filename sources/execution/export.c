/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:58:59 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/24 11:18:00 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_just_export(t_env *env)
{
	t_env	*temp;
	t_env	*export;
	t_env	*new;
	char	*line;

	temp = env;
	export = NULL;
	while (temp)
	{
		if (ft_strncmp(temp->line, "_=/usr/bin/env",
				ft_strlen("_=/usr/bin/env")) == 0)
			temp = temp->next;
		if (temp)
		{
			line = ft_strjoin_export("declare -x ", temp->line);
			new = ft_lstnew_env(line);
			ft_lstadd_back_env(&export, new);
			temp = temp->next;
		}
	}
	ft_print_env(export);
	ft_free_env(export);
	return (SUCCESS);
}

void	ft_execution_of_export(t_minishell *shell, int index, int i)
{
	char	*line;
	char	*buffer;
	t_env	*new;

	if (ft_charset(shell->cmd[index]->args[i], '=') == SUCCESS)
	{
		line = ft_strdup(shell->cmd[index]->args[i]);
		buffer = ft_copy_name_inenv(line);
		if (ft_name_exists_already(shell->env, buffer, line) == false)
		{
			new = ft_lstnew_env(line);
			ft_lstadd_back_env(&shell->env, new);
		}
		free(buffer);
	}
}

int	ft_export_value(t_minishell *shell, int index)
{
	int		i;

	i = 1;
	while (shell->cmd[index]->args[i])
	{
		if (shell->cmd[index]->args[i][0] == '_'
			&& shell->cmd[index]->args[i][1] == '=')
		{
			if (!shell->cmd[index]->args[i + 1])
				break ;
			i++;
		}
		if (ft_option_check(shell, index, i) == ERROR)
			return (ERROR);
		if (!ft_check_var_name(shell->cmd[index]->args[i]))
		{
			printf("%s: export: `%s': not a valid identifier\n",
				SHELL_NAME_ERROR, shell->cmd[index]->args[i]);
			i++;
			continue ;
		}
		ft_execution_of_export(shell, index, i);
		i++;
	}
	return (SUCCESS);
}

int	ft_export(t_minishell *shell, int index)
{
	if (!shell->cmd[index]->args[1])
	{
		if (ft_just_export(shell->env) != SUCCESS)
			return (ERROR);
	}
	else
	{
		if (ft_export_value(shell, index) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_export_forempty_env(t_minishell *shell)
{
	char	buffer[PATH_MAX];
	char	*pwd;
	char	*shlvl;
	char	*env_path;
	t_env	*new;

	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		shell->exit_status = 1;
		return (ERROR);
	}
	pwd = ft_strjoin("PWD=", buffer);
	if (!pwd)
		ft_malloc_failed(shell, ft_strlen(buffer), "ft_export_forempty_env");
	shlvl = ft_strdup("SHLVL=1");
	if (!shlvl)
	{
		free(pwd);
		ft_malloc_failed(shell, ft_strlen("SHLVL=1"), "ft_export_forempty_env");
	}
	env_path = ft_strdup("_=/usr/bin/env");
	if (!env_path)
	{
		free(shlvl);
		free(pwd);
		ft_malloc_failed(shell,
			ft_strlen("_=/usr/bin/env"), "ft_export_forempty_env");
	}
	new = ft_lstnew_env(pwd);
	if (!new)
	{
		free(pwd);
		free(shlvl);
		free(env_path);
		ft_malloc_failed(shell, sizeof(t_env), "ft_export_forempty_env");
	}
	ft_lstadd_back_env(&shell->env, new);
	new = ft_lstnew_env(shlvl);
	if (!new)
	{
		free(shlvl);
		free(env_path);
		ft_malloc_failed(shell, sizeof(t_env), "ft_export_forempty_env");
	}
	ft_lstadd_back_env(&shell->env, new);
	new = ft_lstnew_env(env_path);
	if (!new)
	{
		free(env_path);
		ft_malloc_failed(shell, sizeof(t_env), "ft_export_forempty_env");
	}
	ft_lstadd_back_env(&shell->env, new);
	return (SUCCESS);
}
