/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 14:25:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/23 16:14:07 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_name_the_heredoc_file(t_minishell *shell, int index)
{
	int	i;
	char	*name;
	char	*path;

	i = 0;
	(void)index;
	(void)shell;
	while (i < INT_MAX)
	{
		name = ft_itoa(i);
		path = ft_strjoin("../temp/", name);
		if (access(path, F_OK) == -1)
		{
			free(name);
			return (path);
		}
		free(path);
		free(name);
		i++;
	}
	return (NULL);
}

int	ft_fork_heredoc(t_minishell *shell, char *limiter, int index)
{
	char *fd_name;

	pid_t	pid;
	//fd_name = ft_itoa(index);

	pid = fork();
	//if (pid == -1)
		//smth;
	if (pid == 0)
	{
		fd_name = ft_name_the_heredoc_file(shell, index);
		shell->heredoc_fd[index] = open(fd_name,
			O_RDWR | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		ft_set_of_sig(shell, CHILD);
		ft_handle_heredoc(shell, limiter, index);
		ft_free_all(&shell);
		exit(EXIT_SUCCESS);
	}
	ft_put_heredoc_to_struct(shell, index);
	ft_set_of_sig(shell, SIGIGN);
	if (ft_wait_heredoc_child(shell, pid) == CTRLC_ALERT)
		return (CTRLC_ALERT);
	ft_set_of_sig(shell, PARENT);
	return (SUCCESS);
}

char	*ft_handle_line(t_minishell *shell, char *line)
{
	if (line)
	{
		if (g_flag == CTRLC_ALERT)
			shell->exit_status = 130;
	}
	if (!shell->quote_lim)
		line = ft_expand_line_heredoc(shell, line);
	return (line);
}

int	ft_line_is_not_limiter(char *line, char *limiter)
{
	//limiter = ft_strjoin_char(limiter, '\n');
	if (ft_strlen(line) >= ft_strlen(limiter))
	{	
		if (ft_strncmp(line, limiter, ft_strlen(line)) != 0)
			return (true);
		else
			return (false);
	}
	else
	{
		if (ft_strncmp(limiter, line, ft_strlen(limiter)) != 0)
			return (true);
		else
			return (false);
	}
}

int	ft_write_till_limiter(t_minishell *shell, char *line, char *limiter, int index)
{

	if (line && ft_line_is_not_limiter(line, limiter) == true)
	{
		write(shell->heredoc_fd[index], line, ft_strlen(line));
		write(shell->heredoc_fd[index], "\n", 1);
		free(line);
	}
	else
	{
		free(line);
		close(shell->heredoc_fd[index]);
		//free(limiter);
		//close(shell->cmd[index]->heredoc_pipe[1]);
		//ft_free_struct_foreach_cmd(shell->cmd, 0);
		return (EXIT_FLAG);
	}
	return (ERROR);
}

void	ft_handle_heredoc(t_minishell *shell, char *limiter, int index)
{
	char	*line;
	char	*lim_tmp;

	(void) index;
	line = NULL;
	lim_tmp = ft_unquote_lim_heredoc(shell, limiter);
	while (1)
	{
		line = readline("> ");
		if (g_flag == CTRLC_ALERT)
		{
			ft_free_all(&shell);
			exit(CTRLC_ALERT);
		}
		if (!line)
		{
			ft_ctrl_d_heredoc_msg(shell->prompt_count, lim_tmp);
			ft_free_all(&shell);
			exit(EXIT_SUCCESS);
		}
		line = ft_handle_line(shell, line);
		if (!line)
		{
			write(shell->heredoc_fd[index], "\n", 1);
			continue ;
		}
		if (ft_write_till_limiter(shell, line, lim_tmp, index) == EXIT_FLAG)
		{
			ft_free_all(&shell);
			exit(EXIT_SUCCESS);
		}
	}
}
