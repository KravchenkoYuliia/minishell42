/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:59:13 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/22 16:18:21 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_child(t_minishell *shell, int index, char *cmd)
{
	ft_set_of_sig(shell, CHILD);
	if (close(shell->save_stdin) == -1 || close(shell->save_stdout) == -1)
	{
		ft_syscall_ft_failed(shell, "close");
		ft_free_all(&shell);
		exit (EXIT_FAILURE);
	}
	ft_cmd_checking(shell, index, cmd);
	if (!ft_strchr(shell->cmd[index]->args[0], '/'))
		cmd = ft_find_absolute_path(shell, index);
	if (cmd == NULL)
	{
		ft_error_msg(shell, shell->cmd[index]->args[0], NULL,
			": command not found");
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
	return (SUCCESS);
}

int	ft_simple_cmd(t_minishell *shell, int index)
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
		ft_syscall_ft_failed(shell, "fork");
		ft_clear_after_cmd_exec(shell);
		return (ERROR);
	}
	if (pid == 0)
	{
		shell->process = CHILD;
		ft_set_sig_quit(shell, index);
		if (ft_execute_child(shell, index, cmd) == ERROR)
			return (ERROR);
	}
	shell->process = PARENT;
	ft_set_of_sig(shell, SIGIGN);
	ft_waiting_for_child(shell, 0, 1, pid);
	ft_set_of_sig(shell, PARENT);
	return (SUCCESS);
}
