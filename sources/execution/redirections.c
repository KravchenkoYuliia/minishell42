/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:22:55 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/24 15:49:43 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_infile(t_minishell *shell, char *input)
{
	int	fd;

	if (access(input, F_OK) == -1)
	{
		ft_error_msg(shell, SHL_NAME_ERR,
			input, ": No such file or directory");
		if (shell->process == PARENT)
			return (ERROR);
		else
		{
			ft_free_all(&shell);
			exit(127);
		}
	}
	fd = open(input, O_RDONLY);
	if (fd == -1)
	{
		ft_error_msg(shell, SHL_NAME_ERR, input, ": Permission denied");
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
			fd = ft_check_infile(shell, temp->file_name);
			if (fd < 3 || dup2(fd, STDIN_FILENO) == -1 || close(fd) == -1)
				return (ERROR);
		}
		else if (temp->type == HEREDOC)
		{
			fd = open(temp->file_name, O_RDONLY);
			if (dup2(fd, STDIN_FILENO) == -1)
				return (ERROR);
			if (close(fd) == -1)
				return (ERROR);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

int	ft_open_fd(t_redirect *temp)
{
	int	fd;

	fd = 0;
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
	return (fd);
}

int	ft_redir_output(t_minishell *shell, int index)
{
	int			i;
	int			fd;
	t_redirect	*temp;

	temp = shell->cmd[index]->output_list;
	i = 0;
	fd = 0;
	while (temp)
	{
		fd = ft_open_fd(temp);
		if (fd == -1)
		{
			shell->exit_status = 1;
			perror(SHL_NAME_ERR);
			return (ERROR);
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (ERROR);
		if (close(fd) == -1)
			return (ERROR);
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
	{
		if (dup2(shell->cmd[index]->pipe[1], STDOUT_FILENO) == -1)
			return (ERROR);
		if (close(shell->cmd[index]->pipe[1]) == -1)
			return (ERROR);
	}
	if (shell->cmd[index]->pipe_flag == 0 && shell->cmd[index]->pipe[1] > 2)
		if (close(shell->cmd[index]->pipe[1]) == -1)
			return (ERROR);
	if (shell->cmd[index]->output_list)
		if (ft_redir_output(shell, index) == ERROR)
			return (ERROR);
	return (SUCCESS);
}
