/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:25:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/22 14:02:34 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_strjoin_heredoc(char *s1, char *s2)
{
	int	i;
	int	j;
	int	len;
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


void	ft_handle_heredoc(t_minishell *shell, char *limiter, int index)
{
	char	*line;

	line = NULL;
	pipe(shell->cmd[index]->heredoc_pipe);
	while (1)
	{
		write(1, "> ", 2);
		line = readline(STDIN_FILENO);
		if (line)
			shell->history = ft_strjoin_heredoc(shell->history, line);
		if (ft_strlen(line) >= ft_strlen(limiter))
		{	
			if (ft_strncmp(line, limiter, ft_strlen(line)) != '\n' &&
				ft_strncmp(line, limiter, ft_strlen(line)) != 0)
					write(shell->cmd[index]->heredoc_pipe[1], line, ft_strlen(line));
			else
			{
				free(line);
				break ;
			}
		}
		else
		{
			if (ft_strncmp(limiter, line, ft_strlen(limiter)) != '\n' &&
				ft_strncmp(limiter, line, ft_strlen(limiter)) != 0)
					write(shell->cmd[index]->heredoc_pipe[1], line, ft_strlen(line));
			else
			{
				free(line);
				break ;
			}
		}
	}
}
