/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:22:55 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/13 19:23:57 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_infile(t_minishell *shell, int index)
{
	int	fd;
	
	if (access(shell->cmd[index]->input, F_OK) == -1)
	{
		ft_error_msg(SHELL_NAME_ERROR, shell->cmd[index]->input, ": No such file or directory");
		return (ERROR);
	}
	fd = open(shell->cmd[index]->input, O_RDONLY);
	if (fd == -1)
	{
		ft_error_msg(SHELL_NAME_ERROR, shell->cmd[index]->input, ": Permission denied");
		return (ERROR);
	}
	return (fd);
}

int	ft_input_redir_simple_cmd(t_minishell *shell, int index)
{
	int	fd;

	if (shell->cmd[index]->input[0] == '\0')
		return (SUCCESS);
	if (shell->cmd[index]->heredoc == 1)
		printf("heredoc\n");
	fd = ft_check_infile(shell, index);
	if (fd < 3)
		return (ERROR);
	dup2(fd, STDIN_FILENO);
	return (SUCCESS);
}

int	ft_output_redir_simple_cmd(t_minishell *shell, int index)
{
	int	fd;

	fd = open(shell->cmd[index]->output, O_RDWR | O_CREAT | O_TRUNC,
                        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		perror(SHELL_NAME_ERROR);
		return (ERROR);
	}
	dup2(fd, STDOUT_FILENO);
	return (SUCCESS);
}

int	ft_redirections_simple_cmd(t_minishell *shell, int index)
{
	if (ft_input_redir_simple_cmd(shell, index) == ERROR)
		return (ERROR);
	if (shell->cmd[index]->output[0] != '\0')
		if (ft_output_redir_simple_cmd(shell, index) == ERROR)
			return (ERROR);
	return (SUCCESS);
}
