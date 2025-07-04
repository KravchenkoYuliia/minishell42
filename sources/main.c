/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:26:59 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/04 18:36:08 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_new_prompt(t_minishell *shell)
{
	int	i;

	i = 0;
	if (!shell->input)
		return (true);
	if (ft_only_white_space(shell->input) == true)
	{
		shell->exit_status = 0;
		return (true);
	}
	return (false);
}

void	ft_add_history_and_expand(t_minishell *shell)
{
	if (shell->input && *shell->input
		&& !ft_find_heredoc(shell->token_lst))
	{
		add_history(shell->input);
		free(shell->input);
		shell->heredoc_in_input = false;
	}
	ft_expander(shell);
}

bool	ft_parsing_check_error(t_minishell *shell)
{
	shell->token_lst = ft_parser(shell->input, 0);
	if (!shell->token_lst)
	{
		ft_error_msg(SHELL_NAME, NULL, "Failed to create tokens");
		free(shell->input);
		return (true);
	}
	return (false);
}

bool	ft_execution_check_error(t_minishell *shell)
{
	int	check;

	check = ft_execution(shell);
	if (g_flag == CTRLC_ALERT && shell->history)
	{
		g_flag = CTRLC_OFF;
		add_history(shell->history);
		free(shell->history);
		ft_set_of_sig(shell, PARENT);
		return (true);
	}
	else if (check == NEW_PROMPT)
		return (true);
	return (false);
}

void	ft_minishell(t_minishell *shell)
{
	while (1)
	{
		ft_init_for_every_prompt(shell);
		shell->input = readline(SHELL_NAME);
		ft_checking_input(shell);
		shell->input = ft_cut_input(shell->input);
		if (ft_new_prompt(shell) == true)
			continue ;
		if (shell->input && ft_lexer(shell->input))
		{
			if (ft_parsing_check_error(shell) == true)
				continue ;
			ft_add_history_and_expand(shell);
			if (shell->token_lst && shell->token_lst->value[0])
			{
				if (ft_execution_check_error(shell) == true)
					continue ;
			}
		}
		else
			shell->exit_status = 2;
	}
}

volatile sig_atomic_t	g_flag = CTRLC_OFF;

int	main(int ac, char **av, char **env)
{
	t_minishell		*shell;

	(void)av;
	shell = NULL;
	signal(SIGQUIT, SIG_IGN);
	ft_init_minishell(&shell, env);
	if (shell->malloc_error)
	{
		ft_free_all(&shell);
		return (0);
	}
	if (ac != 1)
		return (0);
	sigemptyset(&shell->sig.sa_mask);
	shell->sig.sa_handler = ft_ctrl_c;
	shell->sig.sa_flags = 0;
	sigaction(SIGINT, &shell->sig, NULL);
	ft_minishell(shell);
	return (0);
}
