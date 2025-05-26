/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_Y.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:47:36 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/26 14:51:10 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


int	ft_count_cmds(t_token *tokens)
{
	int	i;
	t_token	*temp;

	i = 0;
	temp = tokens;
	while (temp)
	{
		if (temp->type == CMD)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	ft_malloc_struct_foreach_cmd(t_cmd_struct ***struct_for_cmds, int nb_of_cmd)
{
	int	i;

	i = 0;
	(*struct_for_cmds) = (t_cmd_struct **)malloc(sizeof(t_cmd_struct *) * nb_of_cmd);
	if (!*struct_for_cmds)
		ft_exit_msg("Malloc failed for struct for cmds");
	while (i < nb_of_cmd)
	{
		(*struct_for_cmds)[i] = (t_cmd_struct *)malloc(sizeof(t_cmd_struct));
		if (!(*struct_for_cmds)[i])
		{
			ft_free_struct_foreach_cmd(*struct_for_cmds, i);
			ft_exit_msg("Malloc failed for struct_for_cmds[i]");
		}
		i++;
	}
}

void	ft_printf_content(char **args)
{
	int	word = 0;

	while (args[word])
	{
		printf("%s\n", args[word]);
		word++;
	}
}

void	ft_fill_struct_foreach_cmd(t_token *tokens, t_cmd_struct **cmds, int nb)
{
	int	i;
	t_token	*temp;

	i = 0;
	temp = tokens;
	while (temp && i < nb)
	{
		if (temp->type == HEREDOC)
			cmds[i]->heredoc = 1;
		if (temp->type == INPUT)
			cmds[i]->input = temp->value;
		if (temp->type == CMD)
			cmds[i]->args = ft_split(temp->value, ' ');
		if (temp->type == APPEND || temp->type == OUTPUT)
		{
			cmds[i]->output = temp->value;
			cmds[i]->append = APPEND;
		}
		if (temp->type == PIPE)
		{
			cmds[i]->pipe = 1;
			
			i++;
		}
		temp = temp->next;
	}
}

void	ft_initialize_struct_foreach_cmd(t_cmd_struct **cmds, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		cmds[i]->input = NULL;
		cmds[i]->output = NULL;
		cmds[i]->append = 0;
		cmds[i]->heredoc = 0;
		cmds[i]->pipe = 0;
		i++;
	}
}

int	ft_child_process(t_cmd_struct *cmd_str, int pipe[2])//, int save_stdin, int save_stdout)
{
/*	close(save_stdin);
	close(save_stdout);
*/	dup2(pipe[1], STDOUT_FILENO);
	close(pipe[0]);
	close(pipe[1]);
	if ((execve(cmd_str->args[0], cmd_str->args, NULL)) == -1)
	{
		perror("babyshell");
		return (ERROR);
	}
	return (SUCCESS);
}

int	ft_child_for_last_cmd(t_cmd_struct *cmd_str, int pipe[2])//, int save_stdin, int save_stdout)
{/*
	close(save_stdin);
	close(save_stdout);
*/	
	
	close(pipe[1]);
	close(pipe[0]);
	if ((execve(cmd_str->args[0], cmd_str->args, NULL)) == -1)
	{
		perror("babyshell");
		exit(EXIT_FAILURE);
		//return (ERROR);
	}
	return (SUCCESS);

}

void	ft_exit(t_cmd_struct *cmd_str, int pipe[2])
{
	(void) pipe;
	int	i;
	unsigned char exit_status;

	i = 0;
	exit_status = 0;
	if ((ft_strncmp(cmd_str->args[0], "exit", 5) == 0))
	{
		if (cmd_str->args[1])
		{
			i = atoi(cmd_str->args[1]);
			exit_status = (unsigned char) i;
		}
		printf("exit\n");
		exit(exit_status);
	}
}


void	ft_check_if_build_in_cmd(t_cmd_struct *cmd, int pipe[2])
{
	int			i;
	char	*built_in_names[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};
	void	(*built_in_functions[])(t_cmd_struct*, int*) = {
		NULL, NULL, NULL, NULL, NULL, NULL,
		&ft_exit
	};

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(cmd->args[0], built_in_names[i],
				ft_strlen(built_in_names[i]) + 1) == 0)
		{
			if (built_in_functions[i] != NULL)
				built_in_functions[i](cmd, pipe);
			else {
				char	msg[30] = {0};
				ft_strcpy(msg, built_in_names[i]);
				ft_strcpy(msg + ft_strlen(msg),
					" is not implemented\n");
				write(2, msg, ft_strlen(msg));
			}
			break ;
		}
		i++;
	}
}
//void	ft_making_child_process_loop(t_cmd_struct **cmd_str)

void	ft_parent_process(t_token *tokens, t_cmd_struct **cmd_str, int nb)
{
	int	status;
	int	save_stdin;
	int	save_stdout;

	int	i;
	pid_t	pid;
	int	pipe_init[2];

	
	status = 0;
	save_stdin = dup(STDIN_FILENO); 
	save_stdout = dup(STDOUT_FILENO); 
	i = 0;
	while (i < nb)
	{
		pipe(pipe_init);
		ft_check_if_build_in_cmd(cmd_str[i], pipe_init);
		pid = fork();
		if (pid == 0)
		{
			if (i == nb - 1)
				ft_child_for_last_cmd(cmd_str[nb - 1], pipe_init);//, save_stdin, save_stdout);
			else if (ft_child_process(cmd_str[i], pipe_init))//, save_stdin, save_stdout == ERROR))
			{
				ft_free_struct_foreach_cmd(cmd_str, nb);
				free_token_list(tokens);
				exit(EXIT_FAILURE);
			}
		}
		dup2(pipe_init[0], STDIN_FILENO);
		close(pipe_init[0]);
		close(pipe_init[1]);
		i++;
	}
	while (waitpid(-1, &status, 0) != -1)
		continue ;
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdin);
	close(save_stdout);
}

void	ft_execution(t_token *tokens)
{
	int		nb_of_cmd; //in line
	t_cmd_struct	**struct_for_cmds;

	nb_of_cmd = ft_count_cmds(tokens);
	ft_malloc_struct_foreach_cmd(&struct_for_cmds, nb_of_cmd);
	ft_initialize_struct_foreach_cmd(struct_for_cmds, nb_of_cmd);
	ft_fill_struct_foreach_cmd(tokens, struct_for_cmds, nb_of_cmd);
	free_token_list(tokens);
	ft_parent_process(tokens, struct_for_cmds, nb_of_cmd);
	ft_free_struct_foreach_cmd(struct_for_cmds, nb_of_cmd);
}



/*	PRINT THE CONTENT OF CMD STRUCTURES

	int i = 0;
	while (i < nb_of_cmd)
	{
		ft_printf_content(struct_for_cmds[i]->args);
		printf("{input file: %s | output file: %s | append: %d | heredoc: %d | pipe: %d\n", struct_for_cmds[i]->input, struct_for_cmds[i]->output, struct_for_cmds[i]->append, struct_for_cmds[i]->heredoc, struct_for_cmds[i]->pipe);
		i++;
	}*/
