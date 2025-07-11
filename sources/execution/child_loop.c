/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:19:59 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/11 14:11:14 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_checking(t_minishell *shell, int index, char *cmd)
{
	if (cmd && ft_strchr(shell->cmd[index]->args[0], '/')
		&& (access(shell->cmd[index]->args[0], X_OK) == -1))
	{
		ft_error_msg(shell, SHELL_NAME_ERROR, shell->cmd[index]->args[0],
			": No such file or directory");
		ft_free_all(&shell);
		exit(127);
	}
	if (!ft_strncmp(cmd, "./minishell", 11))
	{
		ft_error_msg(shell, SHELL_NAME, NULL, "NOT asked in the subjet\nHave some mercy for heaven's sake!");
		ft_free_all(&shell);
		exit(EXIT_SUCCESS);	
	}
	if (shell->cmd[index]->args[0][0] == 46)
	{
		if (shell->cmd[index]->args[0][1] == 47 && shell->cmd[index]->args[0][2] == '\0')
		{
			ft_error_msg(shell, SHELL_NAME, NULL, "./: Is a directory");
			ft_free_all(&shell);
			exit(126);
		}
		else if (shell->cmd[index]->args[0][1] == '\0')
		{
			ft_error_msg(shell, SHELL_NAME, NULL, ".: filename argument required\n.: usage: . filename [arguments]");
			ft_free_all(&shell);
			exit(2);
		}
	}
}

void	ft_simple_cmd_withpipe(t_minishell *shell, int index)
{
	char	*cmd;

	cmd = shell->cmd[index]->args[0];
	ft_cmd_checking(shell, index, cmd);
	if (cmd && !ft_strchr(shell->cmd[index]->args[0], '/'))
		cmd = ft_find_absolute_path(shell, index);
	if (cmd == NULL)
	{
		ft_error_msg(shell, shell->cmd[index]->args[0], NULL, ": command not found");
		close_it_please(shell->cmd[index]);
		ft_free_all(&shell);
		exit(127);
	}
	ft_copy_env_for_execve(shell);
	if (execve(cmd, shell->cmd[index]->args, shell->env_execve) != 0)
	{
		write(2, "HERE\n\n", 6);
		close_it_please(shell->cmd[index]);
		free(cmd);
		ft_free_all(&shell);
		perror(SHELL_NAME_ERROR);
		if (errno == ENOENT)
			exit(127);
		else
			exit(126);
	}
}

void	ft_child_loop(t_minishell *shell, int index)
{
	t_redirect	*temp;

	temp = shell->cmd[index]->input_list;
	close(shell->save_stdin);
	close(shell->save_stdout);
	ft_redirections(shell, index);
	if (shell->cmd[index]->args[0])
	{
		if (ft_exec_built_in_cmd(shell,
				index, shell->cmd[index]->args[0]) == true)
		{
			if (shell->process == CHILD)
			{
				ft_free_all(&shell);
				/*close(shell->cmd[index]->heredoc_pipe[0]);
				close(shell->cmd[index]->heredoc_pipe[1]);*/
				while (temp)
				{
					if (temp->type == HEREDOC)
					{
						if (temp->heredoc_pipe > 0)
							close(temp->heredoc_pipe[0]);
					}
					temp = temp->next;
				}
				exit(EXIT_SUCCESS);
			}
			else
			{
				ft_free_all(&shell);
/*				close(shell->cmd[index]->heredoc_pipe[0]);
				close(shell->cmd[index]->heredoc_pipe[1]);*/
				return ;
			}
		}
		ft_simple_cmd_withpipe(shell, index);
	}
	else
	{
		ft_free_all(&shell);
		exit(EXIT_SUCCESS);
	}
}
