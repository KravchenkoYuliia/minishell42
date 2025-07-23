/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:22:55 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/23 18:46:31 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_infile(t_minishell *shell, char *input)
{
	int	fd;

	if (access(input, F_OK) == -1)
	{
		ft_error_msg(shell, SHELL_NAME_ERROR, input, ": No such file or directory");
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
		ft_error_msg(shell, SHELL_NAME_ERROR, input, ": Permission denied");
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
			if (fd < 3)
				return (ERROR);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (temp->type == HEREDOC)
		{
			int fd = open(temp->file_name, O_RDONLY);
			dup2(fd, STDIN_FILENO);
			close(fd);
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
/*
void	close_them_please(t_cmd_struct **cmds)
{
	for (size_t i = 0; cmds[i] != NULL; ++i)
	{
		close_it_please(cmds[i]);
	}
}*/
/*
void	close_it_please(t_cmd_struct *cmds)
{
	for (t_redirect *input = cmds->input_list; input; input = input->next)
	{
		if (input->heredoc_pipe[0] > 2)
			close(input->heredoc_pipe[0]);
		if (input->heredoc_pipe[1] > 2)
			close(input->heredoc_pipe[1]);
	}
}
*/

int	ft_redirections(t_minishell *shell, int index)
{
	if (shell->cmd[index]->input_list)
	{
		if (ft_redir_input(shell, index) == ERROR)
			return (ERROR);
	}
	if (shell->cmd[index]->pipe_flag == 1)
	{
		dup2(shell->cmd[index]->pipe[1], STDOUT_FILENO);
		close(shell->cmd[index]->pipe[1]);
	}
	if (shell->cmd[index]->pipe_flag == 0 && shell->cmd[index]->pipe[1] > 2)
		close(shell->cmd[index]->pipe[1]);
	if (shell->cmd[index]->output_list)
		if (ft_redir_output(shell, index) == ERROR)
			return (ERROR);
	//close_them_please(shell->cmd);
	return (SUCCESS);
}
