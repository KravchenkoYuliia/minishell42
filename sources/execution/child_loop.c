/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:19:59 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/22 11:53:47 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_simple_cmd_withpipe(t_minishell *shell, int index)
{
	char	*cmd;

	cmd = shell->cmd[index]->args[0];

	                if (cmd && ft_strchr(shell->cmd[index]->args[0], '/') && (access(shell->cmd[index]->args[0], X_OK) == -1))
                {
                        ft_error_msg(SHELL_NAME_ERROR, shell->cmd[index]->args[0], ": No such file or directory");
                        exit(127) ;
                }
                if (cmd && !ft_strchr(shell->cmd[index]->args[0], '/'))
                        cmd = ft_find_absolute_path(shell, index);
                if (cmd == NULL)
                {
                        ft_error_msg(shell->cmd[index]->args[0], NULL, ": command not found");
                        exit(127) ;
                }
		close(shell->save_stdin);
		close(shell->save_stdout);
                if (execve(cmd, shell->cmd[index]->args, NULL) != 0)
                {
                        perror(SHELL_NAME_ERROR);
			if (errno == ENOENT)
				exit(127);
			else
				exit(126);
                }

}

void    ft_execute_cmd_withpipe(t_minishell *shell, char *cmd, int index)
{
        int     i;
        char    *built_in_names[] = {"echo", "cd", "pwd",
                "export", "unset", "env", "exit"};

        int     (*ft_built_in_functions[])(t_minishell *, int) = {
                &ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env,
                &ft_exit
        };

        i = 0;
        while (i < 7)
        {
                if ((cmd && ft_strncmp(cmd, built_in_names[i], (ft_strlen(cmd) + 1)) == 0))
                {
                        ft_built_in_functions[i](shell, index);
			exit(EXIT_SUCCESS) ;
                }
                i++;
        }
        ft_simple_cmd_withpipe(shell, index);
}



void	ft_child_loop(t_minishell *shell, int index, int pipe[2])
{
	int	i;

	i = 0;
	if (shell->cmd[index]->input[0] != '\0')
		ft_input_redir_simple_cmd(shell, index);
	if (shell->cmd[index]->args[0] && shell->cmd[index]->pipe == 1)
		ft_redir_in_pipe(pipe);
	if (shell->cmd[index]->output[0] != '\0')
		ft_output_redir_simple_cmd(shell, index);
	close(pipe[0]);
	close(pipe[1]);
	if (shell->cmd[index]->args[0])
		ft_execute_cmd_withpipe(shell, shell->cmd[index]->args[0], index);
	else
		exit(EXIT_SUCCESS);
}
