/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:59:13 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/08 13:17:44 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_child(t_minishell *shell, int index, char *cmd)
{
	ft_set_of_sig(shell, CHILD);
	close(shell->save_stdin);
	close(shell->save_stdout);
	ft_cmd_checking(shell, index, cmd);
	if (!ft_strchr(shell->cmd[index]->args[0], '/'))
		cmd = ft_find_absolute_path(shell, index);
	if (cmd == NULL)
	{
		ft_error_msg(shell, shell->cmd[index]->args[0], NULL, ": command not found");
		ft_free_all(&shell);
		exit(127);
	}
	ft_copy_env_for_execve(shell);
	if (execve(cmd, shell->cmd[index]->args, shell->env_execve) != 0)
	{
		free(cmd);
		ft_free_all(&shell);
		perror(SHELL_NAME_ERROR);
		if (errno == ENOENT)
                        exit(127);
                else
                        exit(126);
	}
}

void	ft_simple_cmd(t_minishell *shell, int index)
{
	int		status;
	char	*cmd;
	pid_t	pid;

	status = 0;
	cmd = shell->cmd[index]->args[0];
	shell->process = CHILD;
	pid = fork();
	if (pid == -1)
	{
		ft_error_msg(shell, SHELL_NAME, NULL, "fork failed in simple cmd");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		shell->process = CHILD;
		ft_execute_child(shell, index, cmd);
	}
	shell->process = PARENT;
	ft_set_of_sig(shell, SIGIGN);
	ft_waiting_for_child(shell, 1, pid);
	ft_set_of_sig(shell, PARENT);
}
