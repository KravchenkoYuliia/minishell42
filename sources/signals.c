/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:52:18 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/01 17:10:22 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_c(int sign)
{
	if (sign == SIGINT)
	{
		flag = CTRLC_ALERT;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		perror(SHELL_NAME_ERROR);
}

void	ft_ctrl_c_child(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		flag = CTRLC_ALERT;
		exit(130);
	}
}
