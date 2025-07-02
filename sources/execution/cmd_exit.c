/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:06:23 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/02 15:49:30 by yukravch         ###   ########.fr       */
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
	int status;
	
	status = shell->exit_status;
	shell->exit_status = 0;
	ft_free_env(shell->env);
	free(shell);
	ft_write_stdout("exit\n");
	exit(status);
}

int	ft_exit(t_minishell *shell, int index)
{
	//if (shell->process == PARENT_CMD)
		//write(1, "exit\n", 5);
	if (shell->cmd[index]->args[1])
	{
		shell->exit_status = ft_atoi(shell->cmd[index]->args[1]);
		if (!ft_only_numeric(shell->cmd[index]->args[1]))
		{
			//printf("%s: exit: %s: numeric argument required\n",
			//	SHELL_NAME_ERROR, shell->cmd[index]->args[1]);
			shell->exit_status = 2;
		}
		else if (shell->cmd[index]->args[2])
		{
			//printf("%s: exit: too many arguments\n", SHELL_NAME_ERROR);
			shell->exit_status = 1;
			return (ERROR);
		}
	}
	//return SUCCESS;
	//return (ft_total_exit(shell), SUCCESS);
	ft_save_std_fileno(shell);
	exit((unsigned char)shell->exit_status);
}
