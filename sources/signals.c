/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:52:18 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/27 12:20:31 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_c(int sign)
{
	if (sign == SIGINT)
	{
		if (flag == HEREDOC_IS_OFF)
		{	
			printf("\n");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else if (flag == HEREDOC_IS_ON)
		{
			flag = HEREDOC_IS_OFF;
			printf("\n");
		}
	}
	else
		perror(SHELL_NAME_ERROR);
}
