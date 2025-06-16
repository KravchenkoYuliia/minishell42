/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:25:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/16 16:00:39 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_heredoc(t_minishell *shell, int index)
{
	char	*line;
	int	pipe_init[2];

	line = NULL;
	pipe(pipe_init);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
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
	ft_input_redir_simple_cmd(shell, index, pipe_init);
}
