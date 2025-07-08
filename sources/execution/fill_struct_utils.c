/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:44:10 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/08 15:19:39 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_put_word_to_struct(t_minishell *shell,
		int i_struct, int i_args, t_token *temp)
{
	shell->cmd[i_struct]->args[i_args] = ft_strdup(temp->value);
	i_args++;
	if (i_args == shell->cmd[i_struct]->nb_of_words)
		shell->cmd[i_struct]->args[i_args] = NULL;
	return (i_args);
}

void	ft_fill_heredoc_history(t_minishell *shell, int index)
{
	char		*line;

	//close(->heredoc_pipe[1]);
		line = get_next_line(shell->cmd[index]->heredoc_pipe[0]);
		if (!line || line[0] == '\0') 
			return ;
		shell->history = ft_strjoin_heredoc(shell->history, line);
}
