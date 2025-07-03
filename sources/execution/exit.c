/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:46:33 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/03 15:28:19 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_error_msg(char *shell_name, char *cmd, char *msg)
{
	if (shell_name)
		write(2, shell_name, ft_strlen(shell_name));
	if (cmd)
	{
		write(2, ": ", 2);
		write(2, cmd, ft_strlen(cmd));
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	ft_total_exit(t_minishell *shell)
{
	int	status;
	
	ft_save_std_fileno(shell);
	status = shell->exit_status;
	ft_free_all(&shell);
	/* if (shell->token_lst)
		free_token_list(shell->token_lst);
	if (shell->env)
		ft_free_env(shell->env);
	if (shell->cmd)
		ft_free_struct_foreach_cmd(shell->cmd, stop);
	free(shell); */
	exit((unsigned char)status);
}

/*typedef struct s_minishell
{
	int				prompt_count;
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
}	t_minishell; */
