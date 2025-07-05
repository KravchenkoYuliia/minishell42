/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:04:38 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/05 16:16:36 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_malloc_struct_foreach_cmd(t_minishell *shell,
		t_cmd_struct ***cmd, int nb)
{
	int	i;

	i = 0;
	*cmd = NULL;
	*cmd = (t_cmd_struct **)malloc(sizeof(t_cmd_struct *) * (nb + 1));
	if (!*cmd)
	{
		cmd[0] = NULL;
		ft_malloc_failed(shell, sizeof(t_cmd_struct) * nb, "ft_malloc_struct_foreach_cmd");
	}
	while (i < nb)
	{
		(*cmd)[i] = NULL;
		(*cmd)[i] = (t_cmd_struct *)malloc(sizeof(t_cmd_struct));
		if (!(*cmd)[i])
		{
			(*cmd)[i] = NULL;
			ft_malloc_failed(shell, sizeof(t_cmd_struct), "ft_malloc_struct_foreach_cmd");
		}
		i++;
	}
	(*cmd)[i] = NULL;
}

void	ft_start_value(t_minishell *shell)
{
	int	i;

	i = 0;
	while (i < shell->nb_of_cmd)
	{
		shell->cmd[i]->input_list = NULL;
		shell->cmd[i]->output_list = NULL;
		shell->cmd[i]->args = NULL;
		if (shell->cmd[i]->nb_of_words > 0)
		{
			shell->cmd[i]->args = (char **)malloc(sizeof(char *)
				* (shell->cmd[i]->nb_of_words + 1));
			if (!shell->cmd[i]->args)
			{
				shell->cmd[i]->args[0] = NULL;
				ft_malloc_failed(shell, sizeof(char *)
                                	* (shell->cmd[i]->nb_of_words + 1),
					"ft_start_value");
			}
			shell->cmd[i]->args[0] = NULL;
		}
		shell->cmd[i]->input = NULL;
		shell->cmd[i]->output = NULL;
		shell->cmd[i]->append = 0;
		shell->cmd[i]->heredoc = 0;
		shell->cmd[i]->pipe_flag = 0;
		shell->cmd[i]->heredoc_pipe[0] = 0;
		shell->cmd[i]->heredoc_pipe[1] = 0;
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
		if (ft_fill_redirection(shell, i_struct, temp) == CTRLC_ALERT)
			return (CTRLC_ALERT);
		if (temp->type == WORD)
			i_args = ft_put_word_to_struct(shell, i_struct, i_args, temp);
		else if (temp->type == PIPE)
		{
			shell->cmd[i_struct]->pipe_flag = 1;
			i_args = 0;
			i_struct++;
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

int	ft_init_struct_foreach_cmd(t_minishell *shell)
{
	ft_get_nb_of_cmd(shell);
	ft_malloc_struct_foreach_cmd(shell, &shell->cmd, shell->nb_of_cmd);
	ft_get_nb_of_words(shell);
	ft_start_value(shell);
	if (ft_fill_cmd_struct(shell) == ERROR)
		return (ERROR);
	free_token_list(shell->token_lst);
	shell->token_lst = NULL;
	return (SUCCESS);
}
