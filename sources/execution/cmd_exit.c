/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:06:23 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/24 15:47:36 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_only_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[0] == '-')
		i = 1;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

void	ft_ctrl_d_heredoc_msg(int line, char *limiter)
{
	ft_write_stdout(SHELL_NAME);
	ft_write_stdout("warning: here-document at line ");
	ft_putnbr_fd(line, 1);
	ft_write_stdout(" delimited by end-of-file (wanted `");
	ft_write_stdout(limiter);
	ft_write_stdout("')");
	write(1, "\n", 1);
}

void	ft_ctrl_d(t_minishell *shell)
{
	if (shell->env)
		ft_free_env(shell->env);
	rl_clear_history();
	ft_write_stdout("exit\n");
	exit(EXIT_SUCCESS);
}

int	ft_exit(t_minishell *shl, int index)
{
	int	status;

	status = shl->exit_status;
	if (shl->process == PARENT)
		write(1, "exit\n", 5);
	if (shl->cmd[index]->args[1])
	{
		shl->exit_status = ft_atoi(shl->cmd[index]->args[1]);
		if (!ft_only_numeric(shl->cmd[index]->args[1]))
		{
			ft_write_to_stderr(shl, "exit: ", shl->cmd[index]->args[1],
				": numeric argument required");
			status = 2;
		}
		else if (shl->cmd[index]->args[2])
		{
			ft_error_msg(shl, SHL_NAME_ERR, "exit", ": too many arguments");
			shl->exit_status = 1;
			return (1);
		}
		status = shl->exit_status;
	}
	ft_save_std_fileno(shl);
	ft_free_all(&shl);
	exit((unsigned char)status);
}
