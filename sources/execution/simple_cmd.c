/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:59:13 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/04 14:34:38 by yukravch         ###   ########.fr       */
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
		ft_error_msg(shell->cmd[index]->args[0], NULL, ": command not found");
		exit(127);
	}
	ft_copy_env_for_execve(shell);
	if (execve(cmd, shell->cmd[index]->args, shell->env_execve) != 0)
	{
		perror(SHELL_NAME_ERROR);
		shell->exit_status = 127;
		exit(127);
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
		ft_error_msg(SHELL_NAME, NULL, "fork failed in simple cmd");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		ft_execute_child(shell, index, cmd);
	ft_set_of_sig(shell, SIGIGN);
	ft_waiting_for_child(shell, 1, pid);
	ft_set_of_sig(shell, PARENT);
}
