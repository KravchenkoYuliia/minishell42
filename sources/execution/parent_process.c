/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:48:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/17 17:45:33 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_one_cmd(t_minishell *shell, char *cmd, int index) 
{
	int	i;
	char	*built_in_names[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};

	int	(*ft_built_in_functions[])(t_minishell *, int) = {
		&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env,
		&ft_exit
	};

	i = 0;
	ft_redirections_simple_cmd(shell, index, 0);
	while (i < 7)
	{
		if ((ft_strncmp(cmd, built_in_names[i], (ft_strlen(cmd) + 1)) == 0))
		{
			ft_built_in_functions[i](shell, index);
				return ;
		}
		i++;
	}
	ft_simple_cmd(shell, index);
}

void	ft_parent_process(t_minishell *shell)
{
	int	status;
	int	index;
	int     pipe_init[2];
	pid_t   pid;

	index = 0;
	shell->save_stdin = dup(STDIN_FILENO);
	shell->save_stdout = dup(STDOUT_FILENO);
	if (shell->cmd[0]->heredoc == 1)
		ft_handle_heredoc(shell, index);
	if (shell->cmd[0]->pipe == 0 && shell->cmd[0]->args[0])
		ft_execute_one_cmd(shell, shell->cmd[0]->args[0], 0);
	else
	{
		while (index < shell->nb_of_cmd)
		{
			pipe(pipe_init);
			pid = fork();
			if (pid == 0)	
				ft_child_loop(shell, index, pipe_init);
			dup2(pipe_init[0], STDIN_FILENO);
			close(pipe_init[1]);
			index++;
		}
		while (waitpid(-1, &status, 0) != -1)
				continue ;
	}
	ft_save_STD_FILENO(shell);
}
