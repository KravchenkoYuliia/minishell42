/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:46:08 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/24 13:48:52 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_all(t_minishell **shell)
{
	if (!*shell)
		return ;
	if ((*shell)->input)
		free ((*shell)->input);
	if ((*shell)->token_lst)
		free_token_list((*shell)->token_lst);
	if ((*shell)->env)
		ft_free_env((*shell)->env);
	if ((*shell)->env_execve)
		ft_free_args((*shell)->env_execve);
	if ((*shell)->cmd)
		ft_free_struct_foreach_cmd((*shell)->cmd);
	shell = NULL;
	rl_clear_history();
}

void	ft_unlink_heredoc_files(t_minishell *shell)
{
	int			i;
	t_redirect	*temp;

	i = 0;
	while (i < shell->nb_of_cmd)
	{
		temp = shell->cmd[i]->input_list;
		while (temp)
		{
			if (temp->type == HEREDOC)
			{
				unlink(temp->file_name);
			}
			temp = temp->next;
		}
		i++;
	}
}

void	ft_clear_after_cmd_exec(t_minishell *shell)
{
	int	i;

	i = 0;
	ft_unlink_heredoc_files(shell);
	ft_free_struct_foreach_cmd(shell->cmd);
	free_token_list(shell->token_lst);
	ft_save_std_fileno(shell);
}
