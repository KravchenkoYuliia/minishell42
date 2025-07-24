/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:41:17 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/24 11:41:14 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execution(t_minishell *shell)
{
	if (ft_init_struct_foreach_cmd(shell) == CTRLC_ALERT)
	{
		ft_unlink_heredoc_files(shell);
		ft_free_struct_foreach_cmd(shell->cmd);
		free_token_list(shell->token_lst);
		return (CTRLC_ALERT);
	}
	if (g_flag == CTRLC_ALERT)
		return (CTRLC_ALERT);
	if (ft_parent_process(shell) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
