/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_Y.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:47:36 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/04 18:33:36 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

int	ft_create_child_loop(t_exec *exec)
{
	int	i;
	//pid_t	pid;
	//int	pipe_init[2];
	//int	status_built_in;

	i = 0;
	(void) exec;
	ft_check_if_build_in_cmd(exec, i);

	/*while (i < exec->nb_of_cmd)
	{
		pipe(pipe_init);
		exec->pipe[0] = pipe_init[0];
		exec->pipe[1] = pipe_init[1];
		status_built_in = ft_check_if_build_in_cmd(exec, i);
		if (status_built_in == SUCCESS)
			i++;
		else
			return (ERROR);
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
	}*/
	return (SUCCESS);
}



int	ft_parent_process(t_exec *exec)
{
	int	status;
	
	status = 0;
	exec->save_stdin = dup(STDIN_FILENO); 
	exec->save_stdout = dup(STDOUT_FILENO);
	if (ft_create_child_loop(exec) != SUCCESS)
		return (ERROR);
	while (waitpid(-1, &status, 0) != -1)
		continue ;
	ft_save_STD_FILENO(exec);
	return (SUCCESS);
}

int	ft_env(t_minishell *all)
{
	t_env	*temp;

	temp = all->env;
        while (temp)
        {
                printf("%s", ((char *)(temp->line)));
                printf("\n");
                temp = temp->next;
        }
	return (SUCCESS);
}


int	ft_execution(t_minishell *all, t_token *tokens)
{
	(void) tokens;
	ft_env(all);

	/*
	int		nb_of_cmd; //in line
	t_exec		*exec;
	t_cmd_struct	**struct_for_cmd;

	exec = NULL;
//	nb_of_cmd = ft_count_cmds(tokens);
	ft_malloc_struct_foreach_cmd(&struct_for_cmd, nb_of_cmd);
	ft_initialize_struct_foreach_cmd(struct_for_cmd, nb_of_cmd);
	ft_fill_struct_foreach_cmd(tokens, struct_for_cmd, nb_of_cmd);
	free_token_list(tokens);
	ft_init_exec(&exec, struct_for_cmd, nb_of_cmd, all);
	if (ft_parent_process(exec) != SUCCESS)
		return (ERROR);
	ft_free_struct_foreach_cmd(struct_for_cmd, nb_of_cmd);
	free(exec);*/
	return SUCCESS;
}
























/*	PRINT THE CONTENT OF CMD STRUCTURES

	int i = 0;
	while (i < nb_of_cmd)
	{
		ft_printf_content(struct_for_cmds[i]->args);
		printf("{input file: %s | output file: %s | append: %d | heredoc: %d | pipe: %d\n", struct_for_cmds[i]->input, struct_for_cmds[i]->output, struct_for_cmds[i]->append, struct_for_cmds[i]->heredoc, struct_for_cmds[i]->pipe);
		i++;
	}*/
