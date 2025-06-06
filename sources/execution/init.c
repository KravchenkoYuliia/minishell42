/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:04:38 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/06 15:50:45 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_struct_foreach_cmd(t_minishell *shell, t_cmd_struct ***cmd, int nb)
{
	int	i;

	i = 0;
	

	*cmd = (t_cmd_struct **)malloc(sizeof(t_cmd_struct *) * nb);
	if (!*cmd)
		ft_exit_free("Malloc failed in malloc_struct_foreach_cmd", shell, nb);
	while (i < nb)
	{
		(*cmd)[i] = NULL;
		(*cmd)[i] = (t_cmd_struct *)malloc(sizeof(t_cmd_struct));
		if (!(*cmd)[i])
		{
			ft_exit_free("Malloc failed for one of the struct foreach cmd",
					shell, i);
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
		ft_get_nb_of_words(shell);
		shell->cmd[i]->args = (char **)malloc(sizeof(char *) * (shell->cmd[i]->nb_of_words + 1));
		ft_bzero(shell->cmd[i]->input, PATH_MAX);
		ft_bzero(shell->cmd[i]->output, PATH_MAX);
		shell->cmd[i]->append = 0;
		shell->cmd[i]->heredoc = 0;
		shell->cmd[i]->pipe = 0;
		i++;
	}
}

void	ft_fill_cmd_struct(t_minishell *shell)
{
	int	i_struct;
	int	i_args;
	t_token	*temp;

	i_struct = 0;
	i_args = 0;
	temp = shell->token_lst;
	while (temp)
	{
		if (temp->type == WORD)
		{
			shell->cmd[i_struct]->args[i_args] = ft_strdup(temp->value);
			i_args++;
			if (i_args == shell->cmd[i_struct]->nb_of_words)
				shell->cmd[i_struct]->args[i_args] = NULL;
		}
		else if (temp->type == INPUT)
			ft_strcpy(shell->cmd[i_struct]->input,
					temp->value);
		else if (temp->type == OUTPUT)
			ft_strcpy(shell->cmd[i_struct]->output,
					temp->value);
		else if (temp->type == APPEND)
			shell->cmd[i_struct]->append = 1;
		else if (temp->type == HEREDOC)
			shell->cmd[i_struct]->heredoc = 1;
		else if (temp->type == PIPE)
		{
			shell->cmd[i_struct]->pipe = 1;
			i_args = 0;
			i_struct++;
		}
		temp = temp->next;
	}
}

void	ft_init_struct_foreach_cmd(t_minishell *shell)
{
	shell->cmd = NULL;
	ft_get_nb_of_cmd(shell);
	ft_malloc_struct_foreach_cmd(shell, &shell->cmd, shell->nb_of_cmd);
	ft_start_value(shell);
	ft_fill_cmd_struct(shell);
	free_token_list(shell->token_lst);
	shell->token_lst = NULL;
}
