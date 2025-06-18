/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:59:13 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/18 15:57:02 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	ft_simple_cmd(t_minishell *shell, int index)
{
	int	status;
	char	*cmd;
	pid_t	pid;
	
	status = 0;
	cmd = shell->cmd[index]->args[0];
	pid = fork();
	if (pid == -1)
		ft_error_msg(SHELL_NAME, NULL, "fork failed in simple cmd");
	if (pid == 0)
	{
		if (ft_strchr(shell->cmd[index]->args[0], '/') && (access(shell->cmd[index]->args[0], X_OK) == -1))
		{
			ft_error_msg(SHELL_NAME_ERROR, shell->cmd[index]->args[0], ": No such file or directory");
			return ;
		}
		if (!ft_strchr(shell->cmd[index]->args[0], '/'))
			cmd = ft_find_absolute_path(shell, index);
		if (cmd == NULL)
		{
			ft_error_msg(shell->cmd[index]->args[0], NULL, ": command not found");
			shell->exit_status = 127;
			exit(127);
		}
		if (execve(cmd, shell->cmd[index]->args, NULL) != 0)
		{
			perror(SHELL_NAME_ERROR);
		}
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	shell->exit_status = status;
}
