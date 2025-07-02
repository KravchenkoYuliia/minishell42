/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:48:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/02 16:22:38 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_one_cmd(t_minishell *shell, char *cmd, int index)
{
	int		i;
	char	*built_in_names[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};
	int		(*ft_built_in_functions[])(t_minishell *, int) = {
		&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env,
		&ft_exit
	};

	i = 0;
	ft_redirections(shell, index);
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
	int		status;
	int		index;
	pid_t	pid;
	struct sigaction	child_sig;

	index = 0;
	if (shell->heredoc_in_input == true)
	{
		add_history(shell->history);
		free(shell->history);
	}
	shell->save_stdin = dup(STDIN_FILENO);
	shell->save_stdout = dup(STDOUT_FILENO);
	if (shell->cmd[0]->pipe_flag == 0)
	{
		if (shell->cmd[0]->args[0])
			ft_execute_one_cmd(shell, shell->cmd[0]->args[0], 0);
	}
	else
	{
		shell->process = CHILD;
		while (index < shell->nb_of_cmd)
		{
			pipe(shell->cmd[index]->pipe);
			pid = fork();
			if (pid == -1)
				return ;
			if (pid == 0)
			{
				sigemptyset(&child_sig.sa_mask);
		                child_sig.sa_handler = ft_ctrl_c_child;
        	        	child_sig.sa_flags = 0;
	        	        sigaction(SIGINT, &child_sig, NULL);

				ft_child_loop(shell, index);
			}
			close(shell->cmd[index]->heredoc_pipe[0]);
			close(shell->cmd[index]->heredoc_pipe[1]);
			close(shell->cmd[index]->pipe[1]);
			dup2(shell->cmd[index]->pipe[0], STDIN_FILENO);
			close(shell->cmd[index]->pipe[0]);
			index++;
		}
		while (waitpid(-1, &status, 0) != -1)
		{
			sigemptyset(&shell->sig.sa_mask);
			shell->sig.sa_handler = SIG_IGN;
			shell->sig.sa_flags = 0;
			sigaction(SIGINT, &shell->sig, NULL);
			if (WIFSIGNALED(status))
			{
				status = WTERMSIG(status);
				status += 128;
				write(1, "\n", 1);
			}
			else if (WIFEXITED(status))
				status = WEXITSTATUS(status);
			shell->exit_status = status;
			continue ;
		}
		sigemptyset(&shell->sig.sa_mask);
		shell->sig.sa_handler = ft_ctrl_c;
		shell->sig.sa_flags = 0;
		sigaction(SIGINT, &shell->sig, NULL);
	}
	ft_save_std_fileno(shell);
}
