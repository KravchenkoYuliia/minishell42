/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:25:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/17 18:21:40 by yukravch         ###   ########.fr       */
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


void	ft_handle_heredoc(t_minishell *shell, int index)
{
	char	*line;
	int	pipe_init[2];

	line = NULL;
	pipe(pipe_init);
	shell->heredoc_history = ft_strjoin_heredoc(shell->heredoc_history, shell->input);
	shell->heredoc_history = ft_strjoin_heredoc(shell->heredoc_history, "\n");
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line)
			shell->heredoc_history = ft_strjoin_heredoc(shell->heredoc_history, line);
		if (ft_strlen(line) >= ft_strlen(shell->cmd[index]->input))
		{	
			if (ft_strncmp(line, shell->cmd[index]->input, ft_strlen(line)) != '\n' &&
				ft_strncmp(line, shell->cmd[index]->input, ft_strlen(line)) != 0)
					write(pipe_init[1], line, ft_strlen(line));
			else
			{
				free(line);
				break ;
			}
		}
		else
		{
			if (ft_strncmp(shell->cmd[index]->input, line, ft_strlen(shell->cmd[index]->input)) != '\n' &&
				ft_strncmp(shell->cmd[index]->input, line, ft_strlen(shell->cmd[index]->input)) != 0)
					write(pipe_init[1], line, ft_strlen(line));
			else
			{
				free(line);
				break ;
			}
		}
	}
	add_history(shell->heredoc_history);
	ft_input_redir_simple_cmd(shell, index, pipe_init);
}
