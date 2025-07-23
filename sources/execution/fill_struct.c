/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:08:29 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/23 18:03:25 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fill_redirection(t_minishell *shell, int i_struct, t_token *temp)
{
	bool	flag_input_in_history;

	flag_input_in_history = false;
	if (temp->type == INPUT)
		ft_put_input_to_struct(shell, i_struct, temp);
	else if (temp->type == OUTPUT)
		ft_put_output_to_struct(shell, i_struct, temp);
	else if (temp->type == APPEND)
		ft_put_append_to_struct(shell, i_struct, temp);
	else if (temp->type == HEREDOC)
	{
		if (ft_fork_heredoc(shell, temp->value, i_struct) == CTRLC_ALERT)
			return (CTRLC_ALERT);
	//	ft_put_heredoc_to_struct(shell, i_struct);
	//	ft_fill_heredoc_history(shell, i_struct);
	}
	return (SUCCESS);
}

void	ft_put_input_to_struct(t_minishell *shell, int i_struct, t_token *temp)
{
	t_redirect	*new;

	shell->cmd[i_struct]->input = ft_strdup(temp->value);
	new = ft_lstnew_redirect(shell->cmd[i_struct]->input, INPUT);
	ft_lstadd_back_redirect(&shell->cmd[i_struct]->input_list, new);
}

void	ft_put_output_to_struct(t_minishell *shell, int i_struct, t_token *temp)
{
	t_redirect	*new;

	shell->cmd[i_struct]->output = ft_strdup(temp->value);
	new = ft_lstnew_redirect(shell->cmd[i_struct]->output, OUTPUT);
	ft_lstadd_back_redirect(&shell->cmd[i_struct]->output_list, new);
}

void	ft_put_append_to_struct(t_minishell *shell, int i_struct, t_token *temp)
{
	t_redirect	*new;

	shell->cmd[i_struct]->output = ft_strdup(temp->value);
	new = ft_lstnew_redirect(shell->cmd[i_struct]->output, APPEND);
	ft_lstadd_back_redirect(&shell->cmd[i_struct]->output_list, new);
}

void	ft_put_heredoc_to_struct(t_minishell *shell, int index, char *heredoc_file_name)
{
	t_redirect	*new;

	new = ft_lstnew_redirect_heredoc(shell, index, heredoc_file_name);
	ft_lstadd_back_redirect(&shell->cmd[index]->input_list, new);
}
