/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:46:08 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/07 15:39:54 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_all(t_minishell *shell)
{
	if (shell->token_lst)
		free_token_list(shell->token_lst);
	if (shell->env)
		ft_free_env(shell->env);
	if (shell->env_execve)
		ft_free_args(shell->env_execve);
	if (shell->cmd)
		ft_free_struct_foreach_cmd(shell->cmd, 0);
	if (shell->history)
		free (shell->history);
	ft_save_std_fileno(shell);
	free (shell);
	rl_clear_history();
}

/*typedef struct s_minishell
{
	int					prompt_count;
	char				*input;
	t_token				*token_lst;
	int					exit_status;
	t_env				*env;
	char				**env_execve;
	t_cmd_struct		**cmd;
	int					nb_of_cmd;
	int					pipe[2];
	int					save_stdin;
	int					save_stdout;
	char				*history;
	bool				heredoc_in_input;
	struct sigaction	sig;
}	t_minishell;*/
