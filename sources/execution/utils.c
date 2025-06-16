/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:09:56 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/16 16:29:25 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_nb_of_cmd(t_minishell *shell)
{
	int	i;
	t_token	*temp;

	i = 0;
	temp = shell->token_lst;
	if (temp)
		i = 1;
	while (temp)
	{
		if (temp->type == PIPE)
			i++;;
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

void	ft_get_nb_of_words(t_minishell *shell)
{
	int	i_word;
	int	i_struct;
	bool	word_is_on;
	t_token	*temp;

	i_word = 0;
	i_struct = 0;
	word_is_on = false;
	temp = shell->token_lst;
	ft_init_nb_of_words(shell);
	while (temp)
	{
		while (temp && (temp->type == WORD || temp->type == HEREDOC)) 
		{
			if (temp && temp->type == HEREDOC)
				temp = temp->next;
			if (temp && temp->type == WORD)
			{
				word_is_on = true;
				i_word++;
				temp = temp->next;
			}
		}
		if (word_is_on)
		{
			shell->cmd[i_struct]->nb_of_words = i_word;
			word_is_on = false;
			i_word = 0;
			i_struct++;
		}
		if (temp)
			temp = temp->next;
	}
}

void    ft_save_STD_FILENO(t_minishell *shell)
{
	dup2(shell->save_stdin, STDIN_FILENO);
	dup2(shell->save_stdout, STDOUT_FILENO);
	close(shell->save_stdin);
	close(shell->save_stdout);
}
