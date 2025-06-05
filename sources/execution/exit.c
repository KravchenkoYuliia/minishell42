/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:46:33 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/05 17:04:41 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char *msg, t_minishell *shell)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	if (shell->token_lst)
		free_token_list(shell->token_lst);
	if (shell->env)
		ft_free_env(shell->env);
	if (shell->cmd)
		ft_free_struct_foreach_cmd(shell->cmd, shell->nb_of_cmd);
	exit(shell->exit_status);
}
