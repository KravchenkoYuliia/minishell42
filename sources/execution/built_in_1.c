/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:11:22 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/07 18:42:44 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_minishell *shell, int index)
{
	if (!shell->cmd[index]->args[1])
	{
		if (ft_just_export(shell->env) != SUCCESS)
			return (ERROR);
	}
	else
	{
		if (ft_export_value(shell, index) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_unset(t_minishell *shell, int index)
{
/*	int	i;
	t_env	*temp;
	t_env	*previous;


	i = 1;*/
	if (shell->cmd[index]->args[0] && !shell->cmd[index]->args[1])
		return (SUCCESS);
	/*while (shell->cmd[index]->args[i])
	{
		temp = shell->env;
		while (temp)
		{
			if (ft_strncmp(shell->cmd[index]->args[i], temp->line, ft_strlen(temp->line)) == 0)
				
			temp = temp->next;
		}

		i++;
	}*/
	return (SUCCESS);
}
