/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:14:31 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/28 10:30:20 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_count_cmds(t_token *tokens)
{
        int     i;
        t_token *temp;

        i = 0;
        temp = tokens;
        while (temp)
        {
                if (temp->type == CMD)
                        i++;
                temp = temp->next;
        }
        return (i);
}

void	ft_save_STD_FILENO(t_exec *exec)
{
	dup2(exec->save_stdin, STDIN_FILENO);
        dup2(exec->save_stdout, STDOUT_FILENO);
        close(exec->save_stdin);
        close(exec->save_stdout);
}
