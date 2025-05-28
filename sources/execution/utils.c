/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:14:31 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/28 13:09:31 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

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
