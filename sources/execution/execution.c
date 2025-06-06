/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:41:17 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/06 14:21:08 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execution(t_minishell *shell)
{
	
	ft_init_struct_foreach_cmd(shell);
	if ((shell->cmd[0]->nb_of_words > 0) && shell->cmd[0]->args[0] && ft_strncmp("env", shell->cmd[0]->args[0], 4) == 0)
		ft_print_env(shell->env);

	return (SUCCESS);
}
