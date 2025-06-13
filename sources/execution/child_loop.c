/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:19:59 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/13 21:11:42 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_child_loop(t_minishell *shell, int index, int pipe[2])
{
	int	i;

	i = 0;
	(void) shell;
		if (shell->cmd[index]->input[0] != '\0')
			ft_input_redir_simple_cmd(shell, index);
		if (shell->cmd[index]->pipe == 1)
			ft_redir_in_pipe(pipe);
		if (shell->cmd[index]->output[0] != '\0')
			ft_output_redir_simple_cmd(shell, index);
		ft_execute_one_cmd(shell, shell->cmd[index]->args[0], index);
		printf("child ^%d\n", index);
		exit(EXIT_SUCCESS);
}
