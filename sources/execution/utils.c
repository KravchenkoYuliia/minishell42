/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:09:56 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/27 14:42:42 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_nb_of_cmd(t_minishell *shell)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = shell->token_lst;
	if (temp)
		i = 1;
	while (temp)
	{
		if (temp->type == PIPE)
			i++;
		temp = temp->next;
	}
	shell->nb_of_cmd = i;
}

void	ft_init_nb_of_words(t_minishell *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_of_cmd && shell->cmd[i])
	{
		shell->cmd[i]->nb_of_words = 0;
		i++;
	}
}

void	ft_get_nb_of_words_no_pipe(t_minishell *shell)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = shell->token_lst;
	while (temp)
	{
		if (temp->type == WORD)
			i++;
		temp = temp->next;
	}
	shell->cmd[0]->nb_of_words = i;
}

void	ft_get_nb_of_words(t_minishell *shell)
{
	int		i_word;
	int		i_bloc_cmd;
	t_token	*temp;

	i_word = 0;
	i_bloc_cmd = 0;
	temp = shell->token_lst;
	while (temp)
	{
		if (temp->type == WORD)
			i_word++;
		if (temp->type == PIPE)
		{
			shell->cmd[i_bloc_cmd]->nb_of_words = i_word;
			i_bloc_cmd++;
			i_word = 0;
		}
		temp = temp->next;
	}
	shell->cmd[i_bloc_cmd]->nb_of_words = i_word;
}

void	ft_save_std_fileno(t_minishell *shell)
{
	dup2(shell->save_stdin, STDIN_FILENO);
	dup2(shell->save_stdout, STDOUT_FILENO);
	close(shell->save_stdin);
	close(shell->save_stdout);
}
