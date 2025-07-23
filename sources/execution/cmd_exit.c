/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:06:23 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/23 19:43:27 by yukravch         ###   ########.fr       */
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
	//free (shell);
	rl_clear_history();
	ft_write_stdout("exit\n");
	//ft_free_all(&shell);
	exit(EXIT_SUCCESS);
}

int	ft_exit(t_minishell *shell, int index)
{
	int	status;

	status = shell->exit_status;
	if (shell->process == PARENT)
		write(1, "exit\n", 5);
	if (shell->cmd[index]->args[1])
	{
		shell->exit_status = ft_atoi(shell->cmd[index]->args[1]);
		if (!ft_only_numeric(shell->cmd[index]->args[1]))
		{
			ft_write_to_stderr(shell, "exit: ", shell->cmd[index]->args[1],
				": numeric argument required");
			status = 2;
		}
		else if (shell->cmd[index]->args[2])
		{
			ft_error_msg(shell, SHELL_NAME_ERROR, "exit",
				": too many arguments");
			shell->exit_status = 1;
			return (1);
		}
		status = shell->exit_status;
	}
	ft_save_std_fileno(shell);
	ft_free_all(&shell);
	exit((unsigned char)status);
}
