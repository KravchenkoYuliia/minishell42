/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 20:20:09 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/06 15:55:18 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_minishell *shell, int index)
{
	t_env	*list;

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
