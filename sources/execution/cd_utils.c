/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:03:29 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/24 17:11:02 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_liberate_the_child(t_minishell *shell)
{
	if (shell->process == CHILD)
	{
		ft_free_all(&shell);
		exit(ERROR);
	}
}

void	ft_handle_err_msg(t_minishell *shell, int err_code)
{
	shell->exit_status = 1;
	if (err_code == 1)
		ft_error_msg(shell, SHELL_NAME, NULL, "cd: too many arguments");
	else if (err_code == 2)
	{
		ft_error_msg(shell, "toupetishell: cd",
			shell->directory, ": No such file or directory");
	}
}
