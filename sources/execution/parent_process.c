/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:48:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/24 11:43:12 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_one_cmd(t_minishell *shell, char *cmd, int index)
{
	if (ft_redirections(shell, index) == ERROR)
		return (ERROR);
	if (ft_exec_built_in_cmd(shell, index, cmd) == true)
		return (SUCCESS);
	if (ft_simple_cmd(shell, index) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	ft_creating_child(t_minishell *shell, int index, pid_t pid)
{
	while (index < shell->nb_of_cmd)
	{
		if (pipe(shell->cmd[index]->pipe) == -1)
		{
			ft_syscall_ft_failed(shell, "pipe");
			ft_clear_after_cmd_exec(shell);
			return (ERROR);
		}
		pid = fork();
		if (pid == -1)
		{
			ft_syscall_ft_failed(shell, "fork");
			ft_clear_after_cmd_exec(shell);
			return (ERROR);
		}
		if (pid == 0)
		{
			if (close(shell->cmd[index]->pipe[0]) == -1)
			{
				close(shell->save_stdin);
				close(shell->save_stdout);
				ft_syscall_ft_failed(shell, "close");
				ft_free_all(&shell);
				exit(EXIT_FAILURE);
			}
			shell->process = CHILD;
			ft_set_sig_quit(shell, index);
			ft_set_of_sig(shell, CHILD);
			ft_child_loop(shell, index);
		}
		shell->process = PARENT;
		if (close(shell->cmd[index]->pipe[1]) == -1)
		{
			ft_syscall_ft_failed(shell, "close");
			ft_free_all(&shell);
			exit(EXIT_FAILURE);
		}
		if (dup2(shell->cmd[index]->pipe[0], STDIN_FILENO) == -1)
		{
			close(shell->cmd[index]->pipe[0]);
			ft_syscall_ft_failed(shell, "dup2");
			ft_free_all(&shell);
			exit(EXIT_FAILURE);
		}
		if (close(shell->cmd[index]->pipe[0]) == -1)
		{
			ft_syscall_ft_failed(shell, "close");
			ft_free_all(&shell);
			exit(EXIT_FAILURE);
		}
		index++;
	}
	ft_set_of_sig(shell, SIGIGN);
	ft_waiting_for_child(shell, index - 1, 10, 0);
	ft_set_of_sig(shell, PARENT);
	return (SUCCESS);
}

int	ft_parent_process(t_minishell *shell)
{
	int		index;
	pid_t	pid;

	index = 0;
	pid = 0;
	shell->process = PARENT;
	shell->save_stdin = dup(STDIN_FILENO);
	if (shell->save_stdin == -1)
	{
		ft_syscall_ft_failed(shell, "dup");
		return (ERROR);
	}
	shell->save_stdout = dup(STDOUT_FILENO);
	if (shell->save_stdout == -1)
	{
		ft_syscall_ft_failed(shell, "dup");
		return (ERROR);
	}
	if (shell->cmd[0]->pipe_flag == 0 && !shell->cmd[0]->args[0])
		ft_redirections(shell, 0);
	if (shell->cmd[0]->pipe_flag == 0)
	{
		if (shell->cmd[0]->args[0])
		{

			if (ft_execute_one_cmd(shell, shell->cmd[0]->args[0], 0) == ERROR)
			{
				ft_clear_after_cmd_exec(shell);
				return (ERROR);
			}
		}
	}
	else
	{
		shell->process = CHILD;
		if (ft_creating_child(shell, index, pid) == ERROR)
		{
			ft_clear_after_cmd_exec(shell);
			return (ERROR);
		}
	}
	ft_clear_after_cmd_exec(shell);
	return (SUCCESS);
}
