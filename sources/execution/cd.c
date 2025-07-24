/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:01:09 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/24 16:43:17 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_home_path(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->line, "HOME=", 5) == 0)
			return (temp->line + 5);
		temp = temp->next;
	}
	return (NULL);
}

int	ft_cd_home(t_minishell *shell, char directory[PATH_MAX], char *home_path)
{
	home_path = ft_get_home_path(shell->env);
	if (!home_path)
	{
		ft_error_msg(shell, SHL_NAME_ERR, NULL, ": cd: HOME not set");
		shell->exit_status = 1;
		return (ERROR);
	}
	ft_strcpy(directory, home_path);
	return (SUCCESS);
}

int	ft_cd_somewhere_else(t_minishell *shell,
		int index, char directory[PATH_MAX])
{
	ft_strcpy(directory, shell->cmd[index]->args[1]);
	if (shell->cmd[index]->args[2])
	{
		ft_error_msg(shell, SHELL_NAME, NULL, "cd: too many arguments");
		return (ERROR);
	}
	return (SUCCESS);
}

static int	ft_cd_b(t_minishell *shell, t_cmd_struct *arg, int index)
{
	char	*home_path;

	home_path = NULL;
	if (!arg->args[1] || (arg->args[1][0] == '~' && !arg->args[1][1]))
	{
		if (ft_cd_home(shell, shell->directory, home_path) == ERROR)
		{
			shell->exit_status = 1;
			ft_liberate_the_child(shell);
			return (ERROR);
		}
	}
	else if (arg->args[1])
	{
		if (ft_cd_somewhere_else(shell, index, shell->directory) == ERROR)
		{
			ft_liberate_the_child(shell);
			shell->exit_status = 1;
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	ft_cd(t_minishell *shell, int index)
{
	t_cmd_struct	*arg;

	arg = shell->cmd[index];
	if (arg->args[0] && arg->args[1] && arg->args[2])
	{
		ft_handle_err_msg(shell, 1);
		ft_liberate_the_child(shell);
		return (ERROR);
	}
	if (ft_cd_b(shell, arg, index) == ERROR)
		return (ERROR);
	if (chdir(shell->directory) != 0)
	{
		ft_handle_err_msg(shell, 2);
		return (ERROR);
	}
	ft_bzero(shell->directory, PATH_MAX);
	if (getcwd(shell->directory, PATH_MAX) == NULL)
	{
		ft_syscall_ft_failed(shell, "getcwd");
		shell->exit_status = 1;
		return (ERROR);
	}
	ft_change_pwd(shell, shell->env, shell->directory);
	return (SUCCESS);
}
