/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:19:59 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/28 15:25:18 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_simple_cmd_withpipe(t_minishell *shell, int index)
{
	char	*cmd;

	cmd = shell->cmd[index]->args[0];
	if (cmd && ft_strchr(shell->cmd[index]->args[0], '/')
		&& (access(shell->cmd[index]->args[0], X_OK) == -1))
	{
		ft_error_msg(SHELL_NAME_ERROR, shell->cmd[index]->args[0],
			": No such file or directory");
		shell->exit_status = 127;
		exit(127);
	}
	if (cmd && !ft_strchr(shell->cmd[index]->args[0], '/'))
		cmd = ft_find_absolute_path(shell, index);
	if (cmd == NULL)
	{
		ft_error_msg(shell->cmd[index]->args[0], NULL, ": command not found");
		exit(127);
	}
	close(shell->save_stdin);
	close(shell->save_stdout);
	ft_copy_env_for_execve(shell);
	if (!ft_strncmp(cmd, "./minishell", 11))
		ft_handle_shlvl(shell->env_execve);
	if (execve(cmd, shell->cmd[index]->args, shell->env_execve) != 0)
	{
		perror(SHELL_NAME_ERROR);
		if (errno == ENOENT)
			exit(127);
		else
			exit(126);
	}
}

void	ft_child_loop(t_minishell *shell, int index)
{
	int		i;
	char	*cmd;
	char	*built_in_names[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};
	int		(*ft_built_in_functions[])(t_minishell *, int) = {
		&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env,
		&ft_exit};

	i = 0;
	cmd = NULL;
	ft_redirections(shell, index);
	close(shell->cmd[index]->pipe[0]);
	close(shell->cmd[index]->pipe[1]);
	if (shell->cmd[index]->args[0])
	{
		cmd = shell->cmd[index]->args[0];
		while (i < 7)
		{
			if ((cmd && ft_strncmp(cmd, built_in_names[i],
						(ft_strlen(cmd) + 1)) == 0))
			{
				ft_built_in_functions[i](shell, index);
				exit(EXIT_SUCCESS);
			}
			i++;
		}
		ft_simple_cmd_withpipe(shell, index);
	}
	else
		exit(EXIT_SUCCESS);
}
