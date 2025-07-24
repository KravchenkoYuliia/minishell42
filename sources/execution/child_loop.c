/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:19:59 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/24 17:09:10 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_if_child(shell, index, pid);
		shell->process = PARENT;
		ft_check_close_dup(shell, index);
		index++;
	}
	ft_set_of_sig(shell, SIGIGN);
	ft_waiting_for_child(shell, index - 1, 10, 0);
	ft_set_of_sig(shell, PARENT);
	return (SUCCESS);
}

void	ft_handle_a_dot(t_minishell *shell, int index)
{
	if (shell->cmd[index]->args[0][1] == 47
		&& shell->cmd[index]->args[0][2] == '\0')
	{
		ft_error_msg(shell, SHELL_NAME, NULL, "./: Is a directory");
		ft_free_all(&shell);
		exit(126);
	}
	else if (shell->cmd[index]->args[0][1] == '\0')
	{
		ft_error_msg(shell, SHELL_NAME, NULL,
			".: filename argument required\n");
		ft_error_msg(NULL, NULL, NULL,
			".: usage: . filename [arguments]");
		ft_free_all(&shell);
		exit(2);
	}
}

void	ft_simple_cmd_withpipe(t_minishell *shell, int index)
{
	char	*cmd;

	cmd = shell->cmd[index]->args[0];
	if (!ft_strncmp(cmd, "./minishell", 11))
	{
		ft_error_msg(shell, SHELL_NAME, NULL,
			"NOT asked in the subjet\nHave some mercy for heaven's sake!");
		ft_free_all(&shell);
		exit(EXIT_SUCCESS);
	}
	ft_cmd_checking(shell, index, cmd);
	if (cmd && !ft_strchr(shell->cmd[index]->args[0], '/'))
		cmd = ft_find_absolute_path(shell, index);
	if (cmd == NULL)
	{
		ft_error_msg(shell, shell->cmd[index]->args[0], NULL,
			": command not found");
		ft_free_all(&shell);
		exit(127);
	}
	ft_copy_env_for_execve(shell);
	ft_execve(shell, index, cmd);
}

void	ft_close_for_chloop(t_minishell *shell)
{
	if (close(shell->save_stdin) == -1 || close(shell->save_stdout) == -1)
	{
		ft_syscall_ft_failed(shell, "close");
		ft_free_all(&shell);
		exit (EXIT_FAILURE);
	}
}

void	ft_child_loop(t_minishell *shell, int index)
{
	ft_close_for_chloop(shell);
	ft_redirections(shell, index);
	if (shell->cmd[index]->args[0])
	{
		if (ft_exec_built_in_cmd(shell,
				index, shell->cmd[index]->args[0]) == true)
		{
			if (shell->process == CHILD)
			{
				ft_free_all(&shell);
				exit(EXIT_SUCCESS);
			}
			else
			{
				ft_free_all(&shell);
				return ;
			}
		}
		ft_simple_cmd_withpipe(shell, index);
	}
	else
	{
		ft_free_all(&shell);
		exit(EXIT_SUCCESS);
	}
}
