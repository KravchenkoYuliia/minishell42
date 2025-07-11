/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:48:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/11 20:31:25 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_one_cmd(t_minishell *shell, char *cmd, int index)
{
	ft_redirections(shell, index);
	if (ft_exec_built_in_cmd(shell, index, cmd) == true)
		return (SUCCESS);
	if (ft_simple_cmd(shell, index) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	ft_creating_child(t_minishell *shell, int index, pid_t pid)
{
	while (index < shell->nb_of_cmd)
	{
		if (pipe(shell->cmd[index]->pipe) == -1)
			return ;
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			close(shell->cmd[index]->pipe[0]);
			shell->process = CHILD;
			ft_set_sig_quit(shell, index);
			ft_set_of_sig(shell, CHILD);
			ft_child_loop(shell, index);
		}
		shell->process = PARENT;
		close(shell->cmd[index]->pipe[1]);
		dup2(shell->cmd[index]->pipe[0], STDIN_FILENO);
		close(shell->cmd[index]->pipe[0]);
		index++;
	}
	ft_set_of_sig(shell, SIGIGN);
	ft_waiting_for_child(shell, index - 1, 10, 0);
	ft_set_of_sig(shell, PARENT);
}

int	ft_parent_process(t_minishell *shell)
{
	int		index;
	pid_t	pid;

	index = 0;
	pid = 0;
	shell->process = PARENT;
	/*if (shell->heredoc_in_input == true && shell->history)
	{
		add_history(shell->history);
		free(shell->history);
	}*/
	shell->save_stdin = dup(STDIN_FILENO);
	shell->save_stdout = dup(STDOUT_FILENO);
	if (shell->cmd[0]->pipe_flag == 0 && !shell->cmd[0]->args[0])
		ft_redirections(shell, 0);
	
	if (shell->cmd[0]->pipe_flag == 0)
	{
		if (shell->cmd[0]->args[0])
		{
			if (ft_execute_one_cmd(shell, shell->cmd[0]->args[0], 0) == ERROR)
				return (ERROR);
		}
	}
	else
	{
		shell->process = CHILD;
		ft_creating_child(shell, index, pid);
		close_them_please(shell->cmd);
	}
	ft_clear_after_cmd_exec(shell);
	return (SUCCESS);
}
