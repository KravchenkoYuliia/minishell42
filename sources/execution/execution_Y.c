/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_Y.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:47:36 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/28 10:24:52 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void	ft_create_child_loop(t_exec *exec)
{
	int	i;
	pid_t	pid;
	int	pipe_init[2];


	i = 0;
	while (i < exec->nb_of_cmd)
	{
		pipe(pipe_init);
		exec->pipe[0] = pipe_init[0];
		exec->pipe[1] = pipe_init[1];
		ft_check_if_build_in_cmd(exec, i);
		pid = fork();
		if (pid == 0)
		{
			if (i == exec->nb_of_cmd - 1)
				ft_child_for_last_cmd(exec, i);//, save_stdin, save_stdout);
			else 
				ft_child_process(exec, i); //, save_stdin, save_stdout == ERROR))
		}
		dup2(pipe_init[0], STDIN_FILENO);
		close(pipe_init[0]);
		close(pipe_init[1]);
		i++;
	}

}

void	ft_parent_process(t_exec *exec)
{
	int	status;
	
	status = 0;
	exec->save_stdin = dup(STDIN_FILENO); 
	exec->save_stdout = dup(STDOUT_FILENO);
	ft_create_child_loop(exec);
	while (waitpid(-1, &status, 0) != -1)
		continue ;
	ft_save_STD_FILENO(exec);
}

void	ft_execution(t_token *tokens)
{
	int		nb_of_cmd; //in line
	t_exec		*exec;
	t_cmd_struct	**struct_for_cmd;

	exec = NULL;
	nb_of_cmd = ft_count_cmds(tokens);
	ft_malloc_struct_foreach_cmd(&struct_for_cmd, nb_of_cmd);
	ft_initialize_struct_foreach_cmd(struct_for_cmd, nb_of_cmd);
	ft_fill_struct_foreach_cmd(tokens, struct_for_cmd, nb_of_cmd);
	free_token_list(tokens);
	ft_init_exec(&exec, struct_for_cmd, nb_of_cmd);
	ft_parent_process(exec);
	ft_free_struct_foreach_cmd(struct_for_cmd, nb_of_cmd);
	free(exec);
}
























/*	PRINT THE CONTENT OF CMD STRUCTURES

	int i = 0;
	while (i < nb_of_cmd)
	{
		ft_printf_content(struct_for_cmds[i]->args);
		printf("{input file: %s | output file: %s | append: %d | heredoc: %d | pipe: %d\n", struct_for_cmds[i]->input, struct_for_cmds[i]->output, struct_for_cmds[i]->append, struct_for_cmds[i]->heredoc, struct_for_cmds[i]->pipe);
		i++;
	}*/
