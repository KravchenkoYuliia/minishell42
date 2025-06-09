/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:11:22 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/09 20:02:40 by yukravch         ###   ########.fr       */
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
	int	i;
	t_env	*head;
	t_env	*ex_head;
//	t_env	*previous;



	i = 1;
	head = shell->env;
	if (shell->cmd[index]->args[0] && !shell->cmd[index]->args[1])
		return (SUCCESS); //no arguments
	while (head && shell->cmd[index]->args && ft_unset_or_not_unset(head->line, shell->cmd[index]->args) == true)  //first arg need to be unset
	{
		ex_head = head;
		printf("Head needed to be deleted = %s\n", ex_head->line);
		if (head->next)
			shell->env = head->next;
		printf("New head = %s\n", head->line);
		free(ex_head);
	}
	
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
