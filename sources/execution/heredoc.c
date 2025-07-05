/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:25:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/05 16:10:44 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fork_heredoc(t_minishell *shell, char *limiter, int index)
{
	int		status;
	pid_t	pid;

	pipe(shell->cmd[index]->heredoc_pipe);
	pid = fork();
	//if (pid == -1)
		//smth;
	if (pid == 0)
	{
		ft_set_of_sig(shell, CHILD);
		ft_handle_heredoc(shell, limiter, index);
		exit(EXIT_SUCCESS);
	}
	ft_set_of_sig(shell, SIGIGN);
	status = ft_wait_heredoc_child(shell, pid);
	if (status == CTRLC_ALERT)
		return (CTRLC_ALERT);
	else if (status == MALLOC_FAIL)
	{
		close(shell->cmd[index]->heredoc_pipe[1]);
		ft_malloc_failed(shell, 0, "CHILD");
	}
	ft_set_of_sig(shell, PARENT);
	close(shell->cmd[index]->heredoc_pipe[1]);
	return (SUCCESS);
}

char	*ft_handle_line(t_minishell *shell, char *line)
{
	if (line)
	{
		if (g_flag == CTRLC_ALERT)
			shell->exit_status = 130;
		shell->history = ft_strjoin_heredoc(shell->history, line);
		shell->history = ft_strjoin_heredoc(shell->history, "\n");
	}
	if (!shell->quote_lim)
	{
		line = ft_expand_line_heredoc(shell, line);
		if (!line)
			return (NULL);
	}
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

int	ft_write_till_limiter(t_minishell *shell,
		int index, char *line, char *limiter)
{
	if (ft_line_is_not_limiter(line, limiter) == true)
	{
		write(shell->cmd[index]->heredoc_pipe[1], line, ft_strlen(line));
		write(shell->cmd[index]->heredoc_pipe[1], "\n", 1);
		free(line);
	}
	else
	{
		free(line);
		free(limiter);
		close(shell->cmd[index]->heredoc_pipe[1]);
		return (EXIT_FLAG);
	}
	return (SUCCESS);
}

void	ft_handle_heredoc(t_minishell *shell, char *limiter, int index)
{
	char	*line;

	line = NULL;
	close(shell->cmd[index]->heredoc_pipe[0]);
	limiter = ft_unquote_lim_heredoc(shell, limiter);
	if (!limiter)
	{
		ft_free_all(shell);
		exit(MALLOC_FAIL);
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_ctrl_d_heredoc_msg(shell->prompt_count, limiter);
			close(shell->cmd[index]->heredoc_pipe[0]);
			close(shell->cmd[index]->heredoc_pipe[1]);
			free(limiter);
			return ;
		}
		if (line[0] < 14 || line[0] == 32)
		{
			free(line);
			continue ;
		}
		line = ft_handle_line(shell, line);
		if (!line)
		{
			ft_free_all(shell);
			exit(MALLOC_FAIL);
		}
		if (ft_write_till_limiter(shell, index, line, limiter) == EXIT_FLAG)
			exit(EXIT_SUCCESS);
	}
}
