/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_and_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:28:16 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/24 13:51:03 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_only_white_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] > 13 && input[i] != 32)
			return (false);
		i++;
	}
	return (true);
}

bool	ft_find_heredoc(t_token *token_lst)
{
	t_token	*temp;

	temp = token_lst;
	while (temp)
	{
		if (temp->type == HEREDOC)
			return (true);
		temp = temp->next;
	}
	return (false);
}

void	ft_init_minishell(t_minishell *shell, char **env)
{
	shell->prompt_count = 0;
	shell->token_lst = NULL;
	shell->input = NULL;
	shell->exit_status = 0;
	shell->env = NULL;
	shell->malloc_fail = false;
	ft_fill_env(shell, &shell->env, env);
	shell->env_execve = NULL;
	shell->cmd = NULL;
	shell->nb_of_cmd = 0;
	shell->process = PARENT;
	shell->quote_lim = false;
	shell->need_to_add_oldpwd = true;
	shell->malloc_fail_size = 0;
}

void	ft_checking_input(t_minishell *shell)
{
	if (!shell->input)
		ft_ctrl_d(shell);
	if (g_flag == CTRLC_ALERT)
	{
		g_flag = CTRLC_OFF;
		shell->exit_status = 130;
	}
	shell->prompt_count += 1;
}
