/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:22:07 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/08 17:10:20 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wait_heredoc_child(t_minishell *shell, pid_t pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		status = WEXITSTATUS(status);
		if (status == CTRLC_ALERT)
		{
			g_flag = CTRLC_ALERT;
			shell->exit_status = 130;
			return (CTRLC_ALERT);
		}
	}
	shell->exit_status = status;
	return (SUCCESS);
}

void	ft_exit_status(t_minishell *shell, int status)
{
	if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status);
		if (status == 2)
		{
			status += 128;
			write(1, "\n", 1);
		}
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	shell->exit_status = status;
}

void	ft_waiting_for_child(t_minishell *shell, int nb_of_child, pid_t pid)
{
	int	status;

	status = 0;
	if (nb_of_child == 1)
	{
		waitpid(pid, &status, 0);
		ft_exit_status(shell, status);
	}
	else
	{
		while (waitpid(-1, &status, 0) != -1)
		{
			ft_exit_status(shell, status);
			continue ;
		}
	}
}
