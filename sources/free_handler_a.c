/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:16:30 by lfournie          #+#    #+#             */
/*   Updated: 2025/07/07 15:42:28 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->value);
		free(tmp);
	}
}

void	ft_free_env(t_env *head)
{
	t_env	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->line);
		free(temp);
	}
}

void	free_redir_list(t_redirect *head)
{
	t_redirect	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->file_name);
		free(tmp);
	}
}

void	ft_free_args(char **array) //free **array
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_struct_foreach_cmd(t_cmd_struct **structs)
{
	int	i;

	i = 0;
	while (structs && structs[i])
	{
		if (structs[i]->args)
			ft_free_args(structs[i]->args);
		if (structs[i]->input_list)
			free_redir_list(structs[i]->input_list);
		if (structs[i]->output_list)
			free_redir_list(structs[i]->output_list);
		free(structs[i]);
		i++;
	}
	free(structs);
}

/*typedef struct s_cmd_struct
{
	int					nb_of_words;
	char				**args;
	struct s_redirect	*input_list;
	struct s_redirect	*output_list;
	char				*input;
	char				*output;
	int					heredoc_pipe[2];
	int					append;
	int					heredoc;
	int					pipe_flag;
	int					pipe[2];
}	t_cmd_struct;*/
