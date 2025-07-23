/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:04:38 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/23 22:15:50 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_struct_foreach_cmd(t_minishell *shell,
		t_cmd_struct ***cmd, int nb)
{
	int	i;

	i = 0;
	*cmd = (t_cmd_struct **)malloc(sizeof(t_cmd_struct *) * (nb + 1));
	if (!*cmd)
		ft_malloc_failed(shell, sizeof(t_cmd_struct *), "ft_malloc_struct_foreach_cmd");
	while (i < nb)
	{
		(*cmd)[i] = NULL;
		(*cmd)[i] = (t_cmd_struct *)malloc(sizeof(t_cmd_struct));
		if (!(*cmd)[i])
			ft_malloc_failed(shell, sizeof(t_cmd_struct), "ft_malloc_struct_foreach_cmd");
		i++;
	}
	(*cmd)[i] = NULL;
}

void	ft_start_value(t_minishell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < shell->nb_of_cmd)
	{
		shell->cmd[i]->args = NULL;
		shell->cmd[i]->args = (char **)ft_calloc(sizeof(char *),
				(shell->cmd[i]->nb_of_words + 1));
		if (!shell->cmd[i]->args)
		{
			ft_malloc_failed(shell,
					sizeof(shell->cmd[i]->nb_of_words + 1), "ft_start_value");
		}/*
		while (j < shell->cmd[i]->nb_of_words)
		{
			shell->cmd[i]->args[j] = NULL;
			j++;
		}*/
		shell->cmd[i]->input = NULL;
		shell->cmd[i]->output = NULL;
		shell->cmd[i]->append = 0;
		shell->cmd[i]->heredoc = 0;
		//shell->cmd[i]->heredoc_pipe[0] = 0;
		//shell->cmd[i]->heredoc_pipe[1] = 0;
		shell->cmd[i]->pipe_flag = 0;
		shell->cmd[i]->input_list = NULL;
		shell->cmd[i]->output_list = NULL;
		shell->cmd[i]->pipe[0] = 0;
		shell->cmd[i]->pipe[1] = 0;
		i++;
	}
}

int	ft_fill_cmd_struct(t_minishell *shell)
{
	int			i_struct;
	int			i_args;
	t_token		*temp;

	i_struct = 0;
	i_args = 0;
	temp = shell->token_lst;
	while (temp)
	{
		if (!temp->value)
			temp = temp->next;
		if (temp && ft_fill_redirection(shell, i_struct, temp) == CTRLC_ALERT)
			return (CTRLC_ALERT);
		if (temp && temp->type == WORD)
			i_args = ft_put_word_to_struct(shell, i_struct, i_args, temp);
		else if (temp && temp->type == PIPE)
		{
			shell->cmd[i_struct]->pipe_flag = 1;
			i_args = 0;
			i_struct++;
		}
		if (temp)
			temp = temp->next;
	}
	return (SUCCESS);
}

int	ft_init_struct_foreach_cmd(t_minishell *shell)
{
	int	i;

	i = 0;
	ft_get_nb_of_cmd(shell);
	ft_malloc_struct_foreach_cmd(shell, &shell->cmd, shell->nb_of_cmd);
	ft_get_nb_of_words(shell);
	ft_start_value(shell);
	if (ft_fill_cmd_struct(shell) == CTRLC_ALERT)
		return (CTRLC_ALERT);
	if (shell->token_lst)
		free_token_list(shell->token_lst);
	shell->token_lst = NULL;
	return (SUCCESS);
}
