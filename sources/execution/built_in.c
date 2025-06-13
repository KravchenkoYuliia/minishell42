/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:04:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/13 14:48:04 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_minishell *shell, int index)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (!shell->cmd[index]->args[1])
	{
		printf("\n");
		return (0);
	}
	while (shell->cmd[index]->args[i] && ft_is_option(shell->cmd[index]->args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (shell->cmd[index]->args[i] != NULL)
	{
		printf("%s", shell->cmd[index]->args[i]);
		if (shell->cmd[index]->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}

int	ft_cd(t_minishell *shell, int index)
{
	char	directory[PATH_MAX];
	char	*home_path;


	if (!shell->cmd[index]->args[1])
	{
		home_path = ft_get_home_path(shell->env);
		if (!home_path)
		{	
			ft_error_msg(SHELL_NAME_ERROR, ": cd: HOME not set");
			shell->exit_status = 1;
			return (ERROR);
		}
		ft_strcpy(directory, home_path);
	}
	else if (shell->cmd[index]->args[1])
	{
		ft_strcpy(directory, shell->cmd[index]->args[1]);
		if (shell->cmd[index]->args[2])
		{
			ft_error_msg(SHELL_NAME, "cd: too many arguments");
			return (1);
		}
	}
	if (chdir(directory) != 0)
	{
		perror(SHELL_NAME_ERROR);
		return (1);
	}
	ft_bzero(directory, PATH_MAX);
	getcwd(directory, PATH_MAX);
	printf("PWD after cd = %s\n", directory);
	ft_change_pwd(shell->env, directory);
	return (0);
}

int	ft_pwd(t_minishell *shell, int	index)
{
	(void) shell;
	(void) index;
	char	buffer[PATH_MAX];
	
	ft_bzero(buffer, PATH_MAX);
	if (getcwd(buffer, PATH_MAX) == NULL)
		return (1);
	printf("%s\n", buffer);
	return (0);
}

int     ft_env(t_minishell *shell, int index)
{
        t_env   *list;

        if (shell->cmd[index]->args[1])
        {
                ft_error_msg(NULL, "env with no options or arguments :)");
                return (1);
        }
        list = shell->env;
	if (!list)
		ft_export_forempty_env(shell);
        list = shell->env;
        while (list)
        {
                printf("%s", ((char *)(list->line)));
                printf("\n");
                list = list->next;
        }
        return (0);
}
