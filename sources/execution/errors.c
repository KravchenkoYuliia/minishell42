/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:27:48 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/07 15:40:04 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
-bash: fork: Resource temporarily unavailable
-bash: pipe: Resource temporarily unavailable
-bash: dup2: Resource temporarily unavailable

minishell: malloc: cannot allocate %zu bytes
*/

void	ft_malloc_failed(t_minishell *shell, int nb, char *name)
{
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	write(STDERR_FILENO, "malloc: cannot allocate ", 24);
	ft_putnbr_fd(nb, STDERR_FILENO);
	write(STDERR_FILENO, " bytes in ", 10);
	write(STDERR_FILENO, name, ft_strlen(name));
	write(STDERR_FILENO, "\n", 1);
	ft_free_all(shell);
	exit(EXIT_FAILURE);
}

void	ft_error_msg(char *shell_name, char *cmd, char *msg)
{
	if (shell_name)
		write(STDERR_FILENO, shell_name, ft_strlen(shell_name));
	if (cmd)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
	}
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}
