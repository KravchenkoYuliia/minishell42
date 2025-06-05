/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:09:56 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/05 16:30:14 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_nb_of_cmd(t_minishell *shell)
{
	int	i;
	bool	cmd_is_on;
	t_token	*temp;

	i = 0;
	cmd_is_on = false;
	temp = shell->token_lst;
	while (temp)
	{
		if (temp->type == PIPE)
			cmd_is_on = false;
		if (temp->type == WORD && cmd_is_on == false)
		{
			i++;
			cmd_is_on = true;
		}
		temp = temp->next;
	}
	shell->nb_of_cmd = i;
	printf("nb of cmd = %d\n", i);
}
