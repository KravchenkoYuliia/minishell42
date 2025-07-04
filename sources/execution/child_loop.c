/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:19:59 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/04 18:22:45 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_checking(t_minishell *shell, int index, char *cmd)
{
	if (cmd && ft_strchr(shell->cmd[index]->args[0], '/')
		&& (access(shell->cmd[index]->args[0], X_OK) == -1))
	{
		ft_error_msg(SHELL_NAME_ERROR, shell->cmd[index]->args[0],
			": No such file or directory");
		shell->exit_status = 127;
		exit(127);
	}
	if (!ft_strncmp(cmd, "./minishell", 11))
		ft_handle_shlvl_in_array(shell->env_execve);
}

void	ft_simple_cmd_withpipe(t_minishell *shell, int index)
{
	char	*cmd;

	cmd = shell->cmd[index]->args[0];
	ft_cmd_checking(shell, index, cmd);
	if (cmd && !ft_strchr(shell->cmd[index]->args[0], '/'))
		cmd = ft_find_absolute_path(shell, index);
	if (cmd == NULL)
	{
		ft_error_msg(shell->cmd[index]->args[0], NULL, ": command not found");
		exit(127);
	}
	ft_copy_env_for_execve(shell);
	if (execve(cmd, shell->cmd[index]->args, shell->env_execve) != 0)
	{
		perror(SHELL_NAME_ERROR);
		if (errno == ENOENT)
			exit(127);
		else
			exit(126);
	}
}

void	ft_child_loop(t_minishell *shell, int index)
{
	close(shell->save_stdin);
	close(shell->save_stdout);
	ft_redirections(shell, index);
	close(shell->cmd[index]->pipe[0]);
	close(shell->cmd[index]->pipe[1]);
	if (shell->cmd[index]->args[0])
	{
		if (ft_exec_built_in_cmd(shell,
				index, shell->cmd[index]->args[0]) == true)
		{
			if (shell->process == CHILD)
				exit(EXIT_SUCCESS);
			else
				return ;
		}
		ft_simple_cmd_withpipe(shell, index);
	}
	else
		exit(EXIT_SUCCESS);
}
