/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:58:06 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/02 16:14:12 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    ft_is_option(char       *args)
{
        int     i;

        i = 1;
        if (args[0] != '-')
                return (false);
        if (!args[i])
                return (false);
        while (args[i])
        {
                if (args[i] != 'n')
                        return (false);
                i++;
        }
        return (true);
}

int     ft_echo(t_minishell *shell, int idx)
{
        int     i;
        int     n_flag;

        i = 1;
        n_flag = 0;
        if (!shell->cmd[idx]->args[1])
        {
                printf("\n");
                return (SUCCESS);
        }
        while (shell->cmd[idx]->args[i] && ft_is_option(shell->cmd[idx]->args[i]))
        {
                n_flag = 1;
                i++;
        }
        while (shell->cmd[idx]->args[i] != NULL)
        {
                printf("%s", shell->cmd[idx]->args[i]);
                if (shell->cmd[idx]->args[i + 1] != NULL)
                        printf(" ");
                i++;
        }
        if (n_flag == 0)
                printf("\n");
        return (SUCCESS);
}
