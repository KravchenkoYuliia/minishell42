/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:41:17 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/30 12:01:23 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execution(t_minishell *shell)
{
	ft_init_struct_foreach_cmd(shell);
	ft_parent_process(shell);
	return (SUCCESS);
}
