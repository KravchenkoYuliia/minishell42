/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:04:38 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/27 14:30:27 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_struct_foreach_cmd(t_minishell *shl, t_cmd_struct ***cmd, int nb)
{
	int	i;

	i = 0;
	*cmd = (t_cmd_struct **)malloc(sizeof(t_cmd_struct *) * nb);
	if (!*cmd)
		ft_total_exit("Malloc failed in malloc_struct_foreach_cmd", shl, nb);
	while (i < nb)
	{
		(*cmd)[i] = NULL;
		(*cmd)[i] = (t_cmd_struct *)malloc(sizeof(t_cmd_struct));
		if (!(*cmd)[i])
		{
			ft_total_exit("Malloc failed for one of the struct foreach cmd",
				shl, i);
		}
		i++;
	}
}

void	ft_start_value(t_minishell *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_of_cmd)
	{
		shell->cmd[i]->args = NULL;
		shell->cmd[i]->args = (char **)malloc(sizeof(char *)
				* (shell->cmd[i]->nb_of_words + 1));
		shell->cmd[i]->args[0] = NULL;
		shell->cmd[i]->input = NULL;
		shell->cmd[i]->output = NULL;
		shell->cmd[i]->append = 0;
		shell->cmd[i]->heredoc = 0;
		shell->cmd[i]->pipe_flag = 0;
		shell->cmd[i]->input_list = NULL;
		shell->cmd[i]->output_list = NULL;
		i++;
	}
}

void	ft_fill_cmd_struct(t_minishell *shl)
{
	int			i_struct;
	int			i_args;
	bool		flag;
	t_token		*temp;
	t_redirect	*new;

	i_struct = 0;
	i_args = 0;
	flag = false;
	temp = shl->token_lst;
	while (temp)
	{
		if (temp->type == WORD)
		{
			shl->cmd[i_struct]->args[i_args] = ft_strdup(temp->value);
			i_args++;
			if (i_args == shl->cmd[i_struct]->nb_of_words)
				shl->cmd[i_struct]->args[i_args] = NULL;
		}
		else if (temp->type == INPUT)
		{
			shl->cmd[i_struct]->input = ft_strdup(temp->value);
			new = ft_lstnew_redirect(shl->cmd[i_struct]->input, INPUT);
			ft_lstadd_back_redirect(&shl->cmd[i_struct]->input_list, new);
		}
		else if (temp->type == OUTPUT)
		{
			shl->cmd[i_struct]->output = ft_strdup(temp->value);
			new = ft_lstnew_redirect(shl->cmd[i_struct]->output, OUTPUT);
			ft_lstadd_back_redirect(&shl->cmd[i_struct]->output_list, new);
		}
		else if (temp->type == APPEND)
		{
			shl->cmd[i_struct]->output = ft_strdup(temp->value);
			new = ft_lstnew_redirect(shl->cmd[i_struct]->output, APPEND);
			ft_lstadd_back_redirect(&shl->cmd[i_struct]->output_list, new);
		}
		else if (temp->type == HEREDOC)
		{
			if (flag == false)
			{
				shl->history = ft_strjoin_heredoc(shl->history, shl->input);
				shl->history = ft_strjoin_heredoc(shl->history, "\n");
				flag = true;
			}
			ft_handle_heredoc(shl, temp->value, i_struct);
			if (shl->exit_status == 130)
				return ;
			new = ft_lstnew_redirect(shl->cmd[i_struct]->heredoc_pipe, HEREDOC);
			ft_lstadd_back_redirect(&shl->cmd[i_struct]->input_list, new);
		}
		else if (temp->type == PIPE)
		{
			shl->cmd[i_struct]->pipe_flag = 1;
			i_args = 0;
			i_struct++;
		}
		temp = temp->next;
	}
}

void	ft_init_struct_foreach_cmd(t_minishell *shell)
{
	ft_get_nb_of_cmd(shell);
	ft_malloc_struct_foreach_cmd(shell, &shell->cmd, shell->nb_of_cmd);
	ft_get_nb_of_words(shell);
	ft_start_value(shell);
	ft_fill_cmd_struct(shell);
	free_token_list(shell->token_lst);
	shell->token_lst = NULL;
}
