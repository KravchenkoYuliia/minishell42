/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_and_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:28:16 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/23 18:25:53 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	/* *shell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!*shell)
		ft_malloc_failed(NULL, sizeof(t_minishell), "ft_init_minishell"); */
	shell->prompt_count = 0;
	shell->token_lst = NULL;
	shell->input = NULL;
	shell->exit_status = 0;
	shell->env = NULL;
	shell->malloc_fail = false;
	ft_fill_env(shell, &shell->env, env);
	shell->env_execve = NULL;
	shell->cmd = NULL;
	shell->history = NULL;
	shell->nb_of_cmd = 0;
	shell->heredoc_in_input = true;
	shell->process = PARENT;
	shell->quote_lim = false;
	shell->need_to_add_oldpwd = true;
	shell->malloc_fail_size = 0;
}

char	*ft_cut_input(char *cut_me)
{
	int		i;
	char	*new_input;
	char	**lines;

	i = 0;
	new_input = NULL;
	lines = ft_split(cut_me, '\n');
	if (!lines)
		return (NULL);
	while (lines[i] && lines[i][0] > 13 && lines[i][0] != 32)
		i++;
	if (i <= 1)
	{
		ft_free_args(lines);
		return (cut_me);
	}
	new_input = ft_strdup(lines[i - 1]);
	if (i > 1 && ft_strstr(lines[0], new_input))
	{
		free(new_input);
		free(cut_me);
		ft_free_args(lines);
		return (NULL);
	}
	free(cut_me);
	ft_free_args(lines);
	return (new_input);
}

void	ft_init_for_every_prompt(t_minishell *shell)
{
	shell->heredoc_in_input = true;
	shell->history = NULL;
	shell->process = PARENT;
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
