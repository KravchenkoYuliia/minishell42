/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:16:30 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/23 09:59:09 by yukravch         ###   ########.fr       */
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


void	ft_free_struct_foreach_cmd(t_cmd_struct **structs, int stop)
{
	int i;

	i = 0;
	while (i < stop)
	{
		free(structs[i]);
		i++;
	}
	free(structs);
}
