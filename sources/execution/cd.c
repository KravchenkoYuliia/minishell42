/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:01:09 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/23 21:40:24 by yukravch         ###   ########.fr       */
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
		ft_error_msg(shell, SHELL_NAME_ERROR, NULL, ": cd: HOME not set");
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

int	ft_cd(t_minishell *shell, int index)
{
	char	directory[PATH_MAX];
	char	*home_path;

	home_path = NULL;
	if (shell->cmd[index]->args[0] && shell->cmd[index]->args[1] && shell->cmd[index]->args[2])
        {
                ft_error_msg(shell, SHELL_NAME, NULL, "cd: too many arguments");
		shell->exit_status = 1;
			if (shell->process == CHILD)
			{
				ft_free_all(&shell);
				exit(ERROR);
			}
                return (ERROR);
        }
	if (!shell->cmd[index]->args[1] || (shell->cmd[index]->args[1][0] == '~'
				&& !shell->cmd[index]->args[1][1]))
	{
		if (ft_cd_home(shell, directory, home_path) == ERROR)
		{
			shell->exit_status = 1;
			if (shell->process == CHILD)
			{
				ft_free_all(&shell);
				exit(ERROR);
			}
			return (ERROR);
		}
	}
	else if (shell->cmd[index]->args[1])
	{
		if (ft_cd_somewhere_else(shell, index, directory) == ERROR)
		{
			if (shell->process == CHILD)
			{
				ft_free_all(&shell);
				exit(ERROR);
			}
			shell->exit_status = 1;
			return (ERROR);
		}
	}
	if (chdir(directory) != 0)
	{
		ft_error_msg(shell, "toupetishell: cd",
			directory, ": No such file or directory");
		shell->exit_status = 1;
		return (ERROR);
	}
	ft_bzero(directory, PATH_MAX);
	if (getcwd(directory, PATH_MAX) == NULL)
	{
		ft_syscall_ft_failed(shell, "getcwd");
		shell->exit_status = 1;
		return (ERROR);
	}
	ft_change_pwd(shell, shell->env, directory);
	return (SUCCESS);
}
