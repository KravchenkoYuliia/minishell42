/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:18:58 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/28 10:17:12 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int     ft_child_process(t_exec *exec, int i)//, int save_stdin, int save_stdout)
{
/*      close(save_stdin);
        close(save_stdout);
*/      dup2(exec->pipe[1], STDOUT_FILENO);
        close(exec->pipe[0]);
        close(exec->pipe[1]);
        if ((execve(exec->cmd[i]->args[0], exec->cmd[i]->args, NULL)) == -1)
        {
                perror("babyshell");
                return (ERROR);
        }
        return (SUCCESS);
}

int     ft_child_for_last_cmd(t_exec *exec, int i)//, int save_stdin, int save_stdout)
{/*
        close(save_stdin);
        close(save_stdout);
*/

        close(exec->pipe[1]);
        close(exec->pipe[0]);
        if ((execve(exec->cmd[i]->args[0], exec->cmd[i]->args, NULL)) == -1)
        {
                perror("babyshell");
                exit(EXIT_FAILURE);
                //return (ERROR);
        }
        return (SUCCESS);

}

