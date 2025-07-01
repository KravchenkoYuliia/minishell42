/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:59:13 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/01 12:20:39 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_simple_cmd(t_minishell *shell, int index)
{
	int		status;
	char	*cmd;
	pid_t	pid;
	struct sigaction	child_sig;
	status = 0;
	cmd = shell->cmd[index]->args[0];
	pid = fork();
	if (pid == -1)
	{
		ft_error_msg(SHELL_NAME, NULL, "fork failed in simple cmd");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		sigemptyset(&child_sig.sa_mask);
		child_sig.sa_handler = ft_ctrl_c_child;
		child_sig.sa_flags = 0;
		sigaction(SIGINT, &child_sig, NULL);
		if (ft_strchr(shell->cmd[index]->args[0], '/')
			&& (access(shell->cmd[index]->args[0], X_OK) == -1))
		{
			ft_error_msg(SHELL_NAME_ERROR, shell->cmd[index]->args[0],
				": No such file or directory");
			shell->exit_status = 127;
			exit(127);
		}
		if (!ft_strchr(shell->cmd[index]->args[0], '/'))
			cmd = ft_find_absolute_path(shell, index);
		if (cmd == NULL)
		{
			ft_error_msg(shell->cmd[index]->args[0],
				NULL, ": command not found");
			shell->exit_status = 127;
			exit(127);
		}
		close(shell->save_stdin);
		close(shell->save_stdout);
		ft_copy_env_for_execve(shell);
		if (!ft_strncmp(cmd, "./minishell", 11))
                        ft_handle_shlvl(shell->env_execve);
		if (execve(cmd, shell->cmd[index]->args, shell->env_execve) != 0)
		{
			perror(SHELL_NAME_ERROR);
			shell->exit_status = 127;
			exit(127);
		}
	}


	sigemptyset(&shell->sig.sa_mask);
	shell->sig.sa_handler = SIG_IGN;
	shell->sig.sa_flags = 0;
	sigaction(SIGINT, &shell->sig, NULL);
	
	waitpid(pid, &status, 0);
	
	sigemptyset(&shell->sig.sa_mask);
	shell->sig.sa_handler = ft_ctrl_c;
	shell->sig.sa_flags = 0;
	sigaction(SIGINT, &shell->sig, NULL);
	if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status);
		status += 128;
		write(1, "\n", 1);
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	shell->exit_status = status;

}
