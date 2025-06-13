/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:59:13 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/13 18:02:39 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	ft_simple_cmd(t_minishell *shell, int index)
{
	char	*cmd;
	pid_t	pid;
	
	cmd = shell->cmd[index]->args[0];
	pid = fork();
	if (pid == -1)
		ft_error_msg(SHELL_NAME, "fork failed in simple cmd");
	if (pid == 0)
	{
		if (!ft_strchr(shell->cmd[index]->args[0], '/'))
			cmd = ft_find_absolute_path(shell, index);
		if (execve(cmd, shell->cmd[index]->args, NULL) != 0)
		{
			perror(SHELL_NAME_ERROR);
		}
	}
	waitpid(pid, NULL, 0);
}
