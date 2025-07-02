/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:25:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/02 15:05:15 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_fork_heredoc(t_minishell *shell, char *limiter, int index)
{
	int		status;
	pid_t	pid;
	struct sigaction	child_sig;
	pipe(shell->cmd[index]->heredoc_pipe);
	pid = fork();
	if (pid == -1)
	{
		ft_error_msg(SHELL_NAME, NULL, "fork failed in simple cmd");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		sigemptyset(&child_sig.sa_mask);
                child_sig.sa_handler = ft_ctrl_c_child;
                child_sig.sa_flags = 0;
                sigaction(SIGINT, &child_sig, NULL);

		 ft_handle_heredoc(shell, limiter, index);
		 exit(EXIT_SUCCESS);
	}
		sigemptyset(&shell->sig.sa_mask);
	        shell->sig.sa_handler = SIG_IGN;
        	shell->sig.sa_flags = 0;
	        sigaction(SIGINT, &shell->sig, NULL);
		waitpid(pid, &status, 0);
		if (flag == CTRLC_ALERT)
		{
			shell->exit_status = 130;
			return (ERROR);
		}
		if (WIFSIGNALED(status))
		{
			printf("status == %d\nflag == %d\n", status,  flag);
			status = WTERMSIG(status);
			status += 128;
			flag = CTRLC_ALERT;
		}
		else if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
			if (status == CTRLC_ALERT)
			{
				flag = CTRLC_ALERT;
				shell->exit_status = 130;
				return (ERROR);
			}
		}
		shell->exit_status = status;
	
		sigemptyset(&shell->sig.sa_mask);
		shell->sig.sa_handler = ft_ctrl_c;
		shell->sig.sa_flags = 0;
		sigaction(SIGINT, &shell->sig, NULL);
	
	return (SUCCESS);
}

char	*ft_strjoin_heredoc(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*history;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	history = (char *)malloc(sizeof(char) * len);
	if (s1)
	{
		while (s1 && s1[i])
		{
			history[i] = s1[i];
			i++;
		}
		free(s1);
	}
	if (s2)
	{
		while (s2[j])
		{
			history[i] = s2[j];
			i++;
			j++;
		}
		//free(s2);
	}
	history[i] = '\0';
	return (history);
}

void	ft_handle_heredoc(t_minishell *shell, char *limiter, int idx)
{
	char	*line;
	bool	quote;

	line = NULL;
	close(shell->cmd[idx]->heredoc_pipe[0]);
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
			if (flag == CTRLC_ALERT)
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
				write(shell->cmd[idx]->heredoc_pipe[1], line, ft_strlen(line));
				write(shell->cmd[idx]->heredoc_pipe[1], "\n", 1);
				free(line);

			}
			else
			{
				free(line);
				free(limiter);
				exit(EXIT_SUCCESS);
			}
		}
		else
		{
			if (ft_strncmp(limiter, line, ft_strlen(limiter)) != '\n'
				&& ft_strncmp(limiter, line, ft_strlen(limiter)) != 0)
			{
				write(shell->cmd[idx]->heredoc_pipe[1], line, ft_strlen(line));
				write(shell->cmd[idx]->heredoc_pipe[1], "\n", 1);
				free(line);
			}
			else
			{
				free(line);
				free(limiter);
				exit(EXIT_SUCCESS);
			}
		}
	}
}
