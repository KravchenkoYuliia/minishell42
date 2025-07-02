/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:09:56 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/02 17:00:46 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_save_std_fileno(t_minishell *shell)
{
	dup2(shell->save_stdin, STDIN_FILENO);
	dup2(shell->save_stdout, STDOUT_FILENO);
	close(shell->save_stdin);
	close(shell->save_stdout);
}

void	ft_write_stdout(char *msg)
{
	write(1, msg, ft_strlen(msg));
}

int     ft_charset(char *str, char c)
{
        int     i;

        i = 0 ;
        while (str[i])
        {
                if (str[i] == c)
                        return (SUCCESS);
                i++;
        }
        return (ERROR);
}
