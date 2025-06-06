/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:04:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/06 16:19:56 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_option(char *args)
{
	int	i;

	i = 1;
	if (args[0] != '-')
		return (false);
	while (args[i])
	{
		if (args[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(t_minishell *shell, int index)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (!shell->cmd[index]->args[1])
	{
		printf("\n");
		return (0);
	}
	while (shell->cmd[index]->args[i] && ft_is_option(shell->cmd[index]->args[i]))
	{
		n_flag = 1;
		i++;
	}
	while (shell->cmd[index]->args[i] != NULL)
	{
		printf("%s", shell->cmd[index]->args[i]);
		if (shell->cmd[index]->args[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}

int     ft_env(t_minishell *shell, int index)
{
        t_env   *list;

        if (shell->cmd[index]->args[1])
        {
                ft_error_msg("env with no options or arguments :)");
                return (1);
        }
        list = shell->env;
        while (list)
        {
                printf("%s", ((char *)(list->line)));
                printf("\n");
                list = list->next;
        }
        return (0);
}
