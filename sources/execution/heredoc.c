/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:25:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/11 19:45:10 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fork_heredoc(t_minishell *shell, char *limiter, int index)
{
	pid_t	pid;
	int	pipe_create[2];
	pipe(pipe_create);
	pid = fork();
	//if (pid == -1)
		//smth;
	if (pid == 0)
	{
		if (shell->previous_heredoc_pipe[0] > 0)
		{
			close(shell->previous_heredoc_pipe[0]);
			shell->previous_heredoc_pipe[0] = 0;
		}
		ft_set_of_sig(shell, CHILD);
		ft_handle_heredoc(shell, limiter, index, pipe_create);
		ft_free_all(&shell);
		exit(EXIT_SUCCESS);
	}
	close(pipe_create[1]);
	pipe_create[1] = 0;
	ft_put_heredoc_to_struct(shell, index, pipe_create);
	ft_set_of_sig(shell, SIGIGN);
	if (ft_wait_heredoc_child(shell, pid) == CTRLC_ALERT)
		return (CTRLC_ALERT);
	ft_set_of_sig(shell, PARENT);
	return (SUCCESS);
}

char	*ft_handle_line(t_minishell *shell, char *line)
{
	if (line)
	{
		if (g_flag == CTRLC_ALERT)
			shell->exit_status = 130;
	}
	if (!shell->quote_lim)
		line = ft_expand_line_heredoc(shell, line);
	return (line);
}

int	ft_line_is_not_limiter(char *line, char *limiter)
{
	if (ft_strlen(line) >= ft_strlen(limiter))
	{	
		if (ft_strncmp(line, limiter, ft_strlen(line)) != '\n'
			&& ft_strncmp(line, limiter, ft_strlen(line)) != 0)
			return (true);
		else
			return (false);
	}
	else
	{
		if (ft_strncmp(limiter, line, ft_strlen(limiter)) != '\n'
			&& ft_strncmp(limiter, line, ft_strlen(limiter)) != 0)
			return (true);
		else
			return (false);
	}
}

int	ft_write_till_limiter(char *line, char *limiter, int heredoc_pipe[2])
{
	if (ft_line_is_not_limiter(line, limiter) == true)
	{
		write(heredoc_pipe[1], line, ft_strlen(line));
		write(heredoc_pipe[1], "\n", 1);
		free(line);
	}
	else
	{
		free(line);
		//free(limiter);
		//close(shell->cmd[index]->heredoc_pipe[1]);
		//ft_free_struct_foreach_cmd(shell->cmd, 0);
		return (EXIT_FLAG);
	}
	return (ERROR);
}

void	ft_handle_heredoc(t_minishell *shell, char *limiter, int index, int heredoc_pipe[2])
{
	char	*line;

	(void) index;
	line = NULL;
	limiter = ft_unquote_lim_heredoc(shell, limiter);
	close(heredoc_pipe[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_ctrl_d_heredoc_msg(shell->prompt_count, limiter);
			close(heredoc_pipe[1]);

			ft_free_all(&shell);
			exit(EXIT_SUCCESS);
		}
		if (line[0] < 14 || line[0] == 32)
		{
			free(line);
			continue ;
		}
		line = ft_handle_line(shell, line);
		if (ft_write_till_limiter(line, limiter, heredoc_pipe) == EXIT_FLAG)
		{
			close_it_please(shell->cmd[index]);
			close(heredoc_pipe[1]);
			ft_free_all(&shell);
			exit(EXIT_SUCCESS);
		}
	}
}
