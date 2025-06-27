/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:25:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/27 14:27:18 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	}
	history[i] = '\0';
	return (history);
}

void	ft_handle_heredoc(t_minishell *shell, char *limiter, int idx)
{
	char	*line;

	line = NULL;
	pipe(shell->cmd[idx]->heredoc_pipe);
	flag = HEREDOC_IS_ON;
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			shell->history = ft_strjoin_heredoc(shell->history, line);
			shell->history = ft_strjoin_heredoc(shell->history, "\n");
		}
		if (flag == HEREDOC_IS_OFF)
		{
			shell->exit_status = 130;
			if (line)
				free(line);
			return ;
		}
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
				return ;
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
				return ;
			}
		}
	}
	flag = HEREDOC_IS_OFF;
}
