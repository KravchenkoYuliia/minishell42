/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:16:30 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/05 17:45:28 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_token_list(t_token *head)
{
	t_token *tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

void ft_free_env(t_env *head)
{
	t_env *temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->line);
		free(temp);
	}
}

void	ft_free_args(char **array) //free **array
{
	int	i;

	i = 0;
	while(array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_struct_foreach_cmd(t_cmd_struct **structs, int stop)
{
	int i;

	i = 0;
	while (i < stop && structs[i])
	{
		ft_free_args(structs[i]->args);
		free(structs[i]);
		i++;
	}
	free(structs);
}
