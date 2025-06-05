/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:04:38 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/05 17:53:32 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_struct_foreach_cmd(t_minishell *shell, t_cmd_struct ***cmd, int nb)
{
	int	i;

	i = 0;
	*cmd = (t_cmd_struct **)malloc(sizeof(t_cmd_struct *) * nb);
	if (!*cmd)
		ft_exit_free("Malloc failed in malloc_struct_foreach_cmd", shell, nb);
	while (i < nb)
	{
		(*cmd)[i] = NULL;
		(*cmd)[i] = (t_cmd_struct *)malloc(sizeof(t_cmd_struct));
		if (!(*cmd)[i])
		{
			ft_exit_free("Malloc failed for one of the struct foreach cmd",
					shell, i);
		}
		i++;
	}
}


void	ft_init_struct_foreach_cmd(t_minishell *shell)
{
	shell->cmd = NULL;
	ft_get_nb_of_cmd(shell);
	ft_malloc_struct_foreach_cmd(shell, &shell->cmd, shell->nb_of_cmd);
}
