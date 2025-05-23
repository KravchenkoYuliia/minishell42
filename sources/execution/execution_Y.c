/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_Y.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:47:36 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/23 12:26:53 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

const char	*ft_check_if_build_in_cmd(t_token *token)
{
	int			i;
	const char	*build_in_names[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(token->value, build_in_names[i],
				ft_strlen(token->value)) == 0)
			return (build_in_names[i]);
		i++;
	}
	return (NULL);
}

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


void	ft_execute_simple_cmd(t_cmd_struct **cmd_str)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(cmd_str[0]->args[0], cmd_str[0]->args, NULL);
	}
	waitpid(pid, NULL, 0);
	printf("child has finished\n");
}

void	ft_execution(t_token *tokens)
{
	int		nb_of_cmd; //in line
	t_cmd_struct	**struct_for_cmds;

	nb_of_cmd = ft_count_cmds(tokens);
	ft_malloc_struct_foreach_cmd(&struct_for_cmds, nb_of_cmd);
	ft_initialize_struct_foreach_cmd(struct_for_cmds, nb_of_cmd);
	ft_fill_struct_foreach_cmd(tokens, struct_for_cmds, nb_of_cmd);
	ft_execute_simple_cmd(struct_for_cmds);
/*	
	int i = 0;
	while (i < nb_of_cmd)
	{
		ft_printf_content(struct_for_cmds[i]->args);
		printf("{input file: %s | output file: %s | append: %d | heredoc: %d | pipe: %d\n", struct_for_cmds[i]->input, struct_for_cmds[i]->output, struct_for_cmds[i]->append, struct_for_cmds[i]->heredoc, struct_for_cmds[i]->pipe);
		i++;
	}*/
	ft_free_struct_foreach_cmd(struct_for_cmds, nb_of_cmd);
}
	/*
	t_token		*token;
	const char	*cmd;
	token = tokens;
	while (token)
	{
		cmd = ft_check_if_build_in_cmd(token);
		if (cmd)
			printf("Execute build in cmd %s\n", cmd);
		else //cmd classic avec 'execve'
			printf("Execute cmd %s... \n", token->value);
			//ft_execve_cmd(token);
		token = token->next;
	}
}*/
