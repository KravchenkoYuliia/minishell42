/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:06:23 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/11 15:37:04 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_only_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

int	ft_exit(t_minishell *shell, int index)
{
	int	i;
	
	i = 0;
	if (shell->cmd[index]->args[1])
	{
		printf("exit\n");
		if (!ft_only_numeric(shell->cmd[index]->args[1]))
		{
			printf("%s: exit: %s: numeric argument required\n", SHELL_NAME_ERROR, shell->cmd[index]->args[1]);
			shell->exit_status = 2;
		}
		else if (shell->cmd[index]->args[2])
		{
			printf("%s: exit: too many arguments\n", SHELL_NAME_ERROR);
			shell->exit_status = 1;
			return (ERROR);
		}
		shell->exit_status = ft_atoi(shell->cmd[index]->args[1]);
	}
	exit((unsigned char)shell->exit_status);
}
