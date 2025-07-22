/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:58:06 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/22 11:31:30 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_option(char *args)
{
	int	i;

	i = 1;
	if (args[0] != '-')
		return (false);
	if (!args[i])
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
		return (SUCCESS);
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
	return (SUCCESS);
}
