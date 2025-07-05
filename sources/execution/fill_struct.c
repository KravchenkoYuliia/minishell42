/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:08:29 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/05 16:10:23 by yukravch         ###   ########.fr       */
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
		if (flag_input_in_history == false)
		{
			shell->history = ft_strjoin_heredoc(shell->history, shell->input);
			shell->history = ft_strjoin_heredoc(shell->history, "\n");
			flag_input_in_history = true;
		}
		if (ft_fork_heredoc(shell, temp->value, i_struct) == CTRLC_ALERT)
			return (CTRLC_ALERT);
		ft_put_heredoc_to_struct(shell, i_struct);
	}
	return (SUCCESS);
}

void	ft_put_input_to_struct(t_minishell *shell, int i_struct, t_token *temp)
{
	t_redirect	*new;

	shell->cmd[i_struct]->input = ft_strdup(temp->value);
	if (!shell->cmd[i_struct]->input)
		ft_malloc_failed(shell, ft_strlen(temp->value), "ft_put_input_to_struct");
	new = ft_lstnew_redirect(shell->cmd[i_struct]->input, INPUT);
	if (!new)
	{
		free(shell->cmd[i_struct]->input);
		ft_malloc_failed(shell, sizeof(t_redirect), "ft_put_input_to_struct");
	}
	ft_lstadd_back_redirect(&shell->cmd[i_struct]->input_list, new);
}

void	ft_put_output_to_struct(t_minishell *shell, int i_struct, t_token *temp)
{
	t_redirect	*new;

	shell->cmd[i_struct]->output = ft_strdup(temp->value);
	if (!shell->cmd[i_struct]->output)
	{
		free(shell->cmd[i_struct]->output);
		ft_malloc_failed(shell, ft_strlen(temp->value), "ft_put_output_to_struct");
	}
	new = ft_lstnew_redirect(shell->cmd[i_struct]->output, OUTPUT);
	if (!new)
	{
		free(shell->cmd[i_struct]->output);
		ft_malloc_failed(shell, sizeof(t_redirect), "ft_put_output_to_struct");
	}
	ft_lstadd_back_redirect(&shell->cmd[i_struct]->output_list, new);
}

void	ft_put_append_to_struct(t_minishell *shell, int i_struct, t_token *temp)
{
	t_redirect	*new;

	shell->cmd[i_struct]->output = ft_strdup(temp->value);
	if (!shell->cmd[i_struct]->output)
		ft_malloc_failed(shell, ft_strlen(temp->value), "ft_put_output_to_struct");
	new = ft_lstnew_redirect(shell->cmd[i_struct]->output, APPEND);
	if (!new)
	{
		free(shell->cmd[i_struct]->output);
		ft_malloc_failed(shell, sizeof(t_redirect), "ft_put_output_to_struct");
	}
	ft_lstadd_back_redirect(&shell->cmd[i_struct]->output_list, new);
}

void	ft_put_heredoc_to_struct(t_minishell *shell, int i_struct)
{
	t_redirect	*new;

	new = ft_lstnew_redirect(shell->cmd[i_struct]->heredoc_pipe, HEREDOC);
	if (!new)
	{
		free(new);
		ft_malloc_failed(shell, sizeof(t_redirect), "ft_put_input_to_struct");
	}
	ft_lstadd_back_redirect(&shell->cmd[i_struct]->input_list, new);
}
