/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:48:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/22 14:10:34 by yukravch         ###   ########.fr       */
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
	printf("bool = %d\n", shell->heredoc_in_input);
	if (shell->heredoc_in_input == true)
	{
		add_history(shell->history);
		printf("history =%s\n\n", shell->history);
	}
	shell->save_stdin = dup(STDIN_FILENO);
	shell->save_stdout = dup(STDOUT_FILENO);
	if (shell->cmd[0]->pipe == 0)
	{
		if (shell->cmd[0]->args[0])
			ft_execute_one_cmd(shell, shell->cmd[0]->args[0], 0);
	}
	else
	{
		while (index < shell->nb_of_cmd)
		{
			pipe(pipe_init);
			pid = fork();
			if (pid == 0)	
			{
				printf("nb_of_words in bloc[%d] = %d\n", index, shell->cmd[index]->nb_of_words);
				ft_child_loop(shell, index, pipe_init);
			}
			close(pipe_init[1]);
			dup2(pipe_init[0], STDIN_FILENO);
			close(pipe_init[0]);
			index++;
		}
		while (waitpid(pid, &status, 0) != -1)
		{
			if (WIFEXITED(status))
			{
				status = WEXITSTATUS(status);
				shell->exit_status = status;
			}
			continue ;
		}
	}
	ft_save_STD_FILENO(shell);
}
