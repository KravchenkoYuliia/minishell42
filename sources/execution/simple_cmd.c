/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:59:13 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/24 15:47:09 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_minishell *shell, int index, char *cmd)
{
	if (execve(cmd, shell->cmd[index]->args, shell->env_execve) != 0)
	{
		free(cmd);
		ft_free_all(&shell);
		perror(SHL_NAME_ERR);
		if (errno == ENOENT)
			exit(127);
		else
			exit(126);
	}
}

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
	if (!ft_strncmp(cmd, "./minishell", 11))
		ft_handle_shlvl_in_array(shell, shell->env_execve);
	ft_execve(shell, index, cmd);
	return (SUCCESS);
}

int	ft_child(t_minishell *shell, pid_t pid, int index, char *cmd)
{
	if (pid == 0)
	{
		shell->process = CHILD;
		ft_set_sig_quit(shell, index);
		if (ft_execute_child(shell, index, cmd) == ERROR)
			return (ERROR);
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
	if (ft_child(shell, pid, index, cmd) == ERROR)
		return (ERROR);
	shell->process = PARENT;
	ft_set_of_sig(shell, SIGIGN);
	ft_waiting_for_child(shell, 0, 1, pid);
	ft_set_of_sig(shell, PARENT);
	return (SUCCESS);
}
