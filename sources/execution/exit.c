/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:46:33 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/06 17:25:16 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_msg(char *shell_name, char *msg)
{
	if (shell_name)
		write(2, shell_name, ft_strlen(shell_name));
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	ft_exit_free(char *msg, t_minishell *shell, int stop)
{
	int	status;

	status = shell->exit_status;
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	if (shell->token_lst)
		free_token_list(shell->token_lst);
	if (shell->env)
		ft_free_env(shell->env);
	if (shell->cmd)
		ft_free_struct_foreach_cmd(shell->cmd, stop);
	free(shell);
	exit(status);
}
