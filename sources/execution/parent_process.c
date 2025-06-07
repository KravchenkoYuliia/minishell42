/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:48:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/07 15:28:03 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_one_cmd(t_minishell *shell, char *cmd)
{
	int	i;
	char	*built_in_names[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};

	int	(*ft_built_in_functions[])(t_minishell *, int) = {
		&ft_echo, &ft_cd, &ft_pwd, NULL, NULL, &ft_env,
		NULL
	};

	i = 0;
	while (i < 7)
	{
		if ((ft_strncmp(cmd, built_in_names[i], (ft_strlen(cmd) + 1)) == 0))
		{
			ft_built_in_functions[i](shell, 0);
			return ;
		}
		i++;
	}
//	ft_simple_cmd(shell);
}

void	ft_parent_process(t_minishell *shell)
{
	//int	status;
	
	shell->save_stdin = dup(STDIN_FILENO);
	shell->save_stdout = dup(STDOUT_FILENO);
	if (shell->cmd[0]->pipe == 0 && shell->cmd[0]->args[0])
		ft_execute_one_cmd(shell, shell->cmd[0]->args[0]);
	/*else
	{
		ft_child_loop(shell);
		while (waitpid(-1, &status, 0) != -1)
			continue ;
	}*/
	ft_save_STD_FILENO(shell);
}
