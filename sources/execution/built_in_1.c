/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:11:22 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/13 14:03:15 by yukravch         ###   ########.fr       */
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
		printf("New head = %s\n", head->line);
		free(ex);
	}
	previous = shell->env;
	current = shell->env->next;
	while (current)
	{
		if (ft_unset_or_not_unset(current->line, shell->cmd[index]->args) == true)
		{
			printf("Need to be deleted %s, previous = %s\n", current->line, previous->line);
			ex = current;
			if (current->next)
			{
				previous->next = current->next;
				current = current->next;
			
				printf("Now previous %s points to %s, current = %s\n", previous->line, previous->next->line, current->line);
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
