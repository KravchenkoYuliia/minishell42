/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:55:18 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/18 17:47:02 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_minishell *shell, int index)
{
	t_env	*head;
	t_env	*current;
	t_env	*ex;
	t_env	*previous;

	head = shell->env;
	if (shell->cmd[index]->args[0] && !shell->cmd[index]->args[1])
		return (SUCCESS); //no arguments
	while (head && shell->cmd[index]->args && ft_unset_or_not_unset(head->line, shell->cmd[index]->args) == true)  //first arg need to be unset
	{
		ex = head;
		if (head->next)
		{
			shell->env = head->next;
			head = head->next;
		}
		free(ex);
	}
	previous = shell->env;
	current = shell->env->next;
	while (current)
	{
		if (ft_unset_or_not_unset(current->line, shell->cmd[index]->args) == true)
		{
			ex = current;
			if (current->next)
			{
				previous->next = current->next;
				current = current->next;

			}
			else
			{
				previous->next = NULL;
				current = NULL;
			}
			free(ex);
		}
		else
		{
			previous = previous->next;
			current = current->next;
		}
}
return (SUCCESS);
}
