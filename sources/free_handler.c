/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:16:30 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/23 11:10:46 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_token_list(t_token *head)
{
	t_token *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
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
	while (i < stop)
	{
		ft_free_args(structs[i]->args);
		free(structs[i]);
		i++;
	}
	free(structs);
}
