/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:25:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/04 17:00:01 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_fork_heredoc(t_minishell *shell, char *limiter, int index)
{
	int		status;
	pid_t	pid;
	pipe(shell->cmd[index]->heredoc_pipe);
	pid = fork();
	if (pid == -1)
	{
		ft_error_msg(SHELL_NAME, NULL, "fork failed in simple cmd");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		ft_set_of_sig(shell, CHILD);
		ft_handle_heredoc(shell, limiter, index);
		exit(EXIT_SUCCESS);
	}
	ft_set_of_sig(shell, SIGIGN);
		waitpid(pid, &status, 0);
		if (g_flag == CTRLC_ALERT)
		{
			shell->exit_status = 130;
			return (ERROR);
		}
		else if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
			if (status == CTRLC_ALERT)
			{
				g_flag = CTRLC_ALERT;
				shell->exit_status = 130;
				return (ERROR);
			}
		}
		shell->exit_status = status;
	ft_set_of_sig(shell, PARENT);
	return (SUCCESS);
}

void	ft_handle_heredoc(t_minishell *shell, char *limiter, int index)
{
	char	*line;
	bool	quote;

	line = NULL;
	close(shell->cmd[index]->heredoc_pipe[0]);
	quote = ft_quote_or_not_quote(limiter);
	if (quote == true)
		limiter = ft_unquote_limiter(limiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_ctrl_d_heredoc_msg(shell->prompt_count, limiter);
			free(line);
			return ;
		}
		if (line)
		{
			if (g_flag == CTRLC_ALERT)
				shell->exit_status = 130;
			shell->history = ft_strjoin_heredoc(shell->history, line);
			shell->history = ft_strjoin_heredoc(shell->history, "\n");
		}
		if (!quote)
			line = ft_expand_line_heredoc(line);
		if (ft_strlen(line) >= ft_strlen(limiter))
		{	
			if (ft_strncmp(line, limiter, ft_strlen(line)) != '\n'
				&& ft_strncmp(line, limiter, ft_strlen(line)) != 0)
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
				ft_free_struct_foreach_cmd(shell->cmd, 0);
				exit(EXIT_SUCCESS);
			}
		}
		else
		{
			if (ft_strncmp(limiter, line, ft_strlen(limiter)) != '\n'
				&& ft_strncmp(limiter, line, ft_strlen(limiter)) != 0)
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
				ft_free_struct_foreach_cmd(shell->cmd, 0);
				exit(EXIT_SUCCESS);
			}
		}
	}
}
