/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:22:55 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/01 14:20:32 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_infile(char *input)
{
	int	fd;

	if (access(input, F_OK) == -1)
	{
		ft_error_msg(SHELL_NAME_ERROR, input, ": No such file or directory");
		return (ERROR);
	}
	fd = open(input, O_RDONLY);
	if (fd == -1)
	{
		ft_error_msg(SHELL_NAME_ERROR, input, ": Permission denied");
		return (ERROR);
	}
	return (fd);
}

int	ft_redir_input(t_minishell *shell, int index)
{
	int			fd;
	t_redirect	*temp;

	temp = shell->cmd[index]->input_list;
	while (temp)
	{
		if (temp->type == INPUT)
		{
			fd = ft_check_infile(temp->file_name);
			if (fd < 3)
				return (ERROR);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (temp->type == HEREDOC)
		{
			close(temp->heredoc_pipe[1]);
			dup2(temp->heredoc_pipe[0], STDIN_FILENO);
			close(temp->heredoc_pipe[0]);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

int	ft_redir_output(t_minishell *shell, int index)
{
	int			i;
	int			fd;
	t_redirect	*temp;

	temp = shell->cmd[index]->output_list;
	i = 0;
	while (temp)
	{
		if (temp->type == APPEND)
		{
			fd = open(temp->file_name, O_RDWR | O_CREAT | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
		else if (temp->type == OUTPUT)
		{
			fd = open(temp->file_name, O_RDWR | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
		if (fd == -1)
		{
			perror(SHELL_NAME_ERROR);
			return (ERROR);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
		i++;
		temp = temp->next;
	}
	return (SUCCESS);
}

int	ft_redirections(t_minishell *shell, int index)
{
	if (shell->cmd[index]->input_list)
	{
		if (ft_redir_input(shell, index) == ERROR)
			return (ERROR);
	}
	if (shell->cmd[index]->pipe_flag == 1)
		dup2(shell->cmd[index]->pipe[1], STDOUT_FILENO);
	if (shell->cmd[index]->output_list)
		if (ft_redir_output(shell, index) == ERROR)
			return (ERROR);
	return (SUCCESS);
}
