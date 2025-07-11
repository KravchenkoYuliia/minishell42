/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:52:18 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/11 17:08:13 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ctrl_c(int sign)
{
	if (sign == SIGINT)
	{
		g_flag = CTRLC_ALERT;
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
		g_flag = CTRLC_ALERT;
		exit(CTRLC_ALERT);
	}
}

void	ft_set_of_sig(t_minishell *shell, int type)
{
	struct sigaction	child_sig;

	if (type == CHILD)
	{
		sigemptyset(&child_sig.sa_mask);
		child_sig.sa_handler = ft_ctrl_c_child;
		child_sig.sa_flags = 0;
		sigaction(SIGINT, &child_sig, NULL);
	}
	else if (type == SIGIGN)
	{
		sigemptyset(&shell->sig.sa_mask);
		shell->sig.sa_handler = SIG_IGN;
		shell->sig.sa_flags = 0;
		sigaction(SIGINT, &shell->sig, NULL);
	}
	else if (type == PARENT)
	{
		sigemptyset(&shell->sig.sa_mask);
		shell->sig.sa_handler = ft_ctrl_c;
		shell->sig.sa_flags = 0;
		sigaction(SIGINT, &shell->sig, NULL);
	}
}

void	ft_sig_quit_no_p(int sign)
{
	if (sign == SIGQUIT)
		g_flag = SIG_QUIT;
}

void	ft_set_sig_quit(t_minishell *shell, int index)
{
	struct sigaction	sig_quit;

	if (shell->cmd[index]->pipe_flag == 1)
	{
		sigemptyset(&sig_quit.sa_mask);
		sig_quit.sa_handler = SIG_DFL;
		sig_quit.sa_flags = 0;
		sigaction(SIGQUIT, &sig_quit, NULL);
	}
	else if (shell->cmd[index]->pipe_flag == 0)
	{
		sigemptyset(&sig_quit.sa_mask);
		sig_quit.sa_handler = ft_sig_quit_no_p;
		sig_quit.sa_flags = 0;
		sigaction(SIGQUIT, &sig_quit, NULL);
	}
}
