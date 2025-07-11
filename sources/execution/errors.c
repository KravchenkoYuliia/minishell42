/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 13:27:48 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/11 20:26:26 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
-bash: fork: Resource temporarily unavailable
-bash: pipe: Resource temporarily unavailable
-bash: dup2: Resource temporarily unavailable

minishell: malloc: cannot allocate %zu bytes
*/

void	ft_syscall_ft_failed(t_minishell *shell, char *cmd)
{
	ft_putstr_fd("-", STDERR_FILENO);
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": Resource temporarily unavailable\n", STDERR_FILENO);
	if (shell)
		ft_clear_after_cmd_exec(shell);
}

void	ft_malloc_failed(t_minishell *shell, int nb, char *name)
{
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	write(STDERR_FILENO, "malloc: cannot allocate ", 24);
	ft_putnbr_fd(nb, STDERR_FILENO);
	write(STDERR_FILENO, " bytes in ", 10);
	write(STDERR_FILENO, name, ft_strlen(name));
	write(STDERR_FILENO, "\n", 1);
	ft_free_all(&shell);
	exit(EXIT_FAILURE);
}

void	ft_write_to_stderr(t_minishell *shell, char *msg1, char *arg, char *msg2)
{
	write(STDERR_FILENO, SHELL_NAME, ft_strlen(SHELL_NAME));
	write(STDERR_FILENO, msg1, ft_strlen(msg1));
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, msg2, ft_strlen(msg2));
	write(STDERR_FILENO, "\n", 1);
	(void) shell;
}

void	ft_error_msg(t_minishell *shell, char *shell_name, char *cmd, char *msg)
{
	if (shell_name)
		write(STDERR_FILENO, shell_name, ft_strlen(shell_name));
	if (cmd)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
	}
	write(STDERR_FILENO, msg, ft_strlen(msg));
	(void) shell;
	//if (shell && ((shell->process == PARENT) || shell->cmd[0]->pipe_flag == 0))
		write(STDERR_FILENO, "\n", 1);
}
