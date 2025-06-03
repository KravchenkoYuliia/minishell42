/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:38:19 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/03 14:04:46 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_init_exec(t_exec **exec, t_cmd_struct **struct_for_cmd, int nb_of_cmd, char **env)
{
	*exec = malloc(sizeof(t_exec));
	if (!*exec)
	{
		ft_free_struct_foreach_cmd(struct_for_cmd, nb_of_cmd);
		exit(EXIT_FAILURE);
	}
	(*exec)->nb_of_cmd = nb_of_cmd;
	(*exec)->cmd = struct_for_cmd;
	(*exec)->env = env;
}

void    ft_malloc_struct_foreach_cmd(t_cmd_struct ***struct_for_cmds, int nb_of_cmd)
{
        int     i;

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

void    ft_initialize_struct_foreach_cmd(t_cmd_struct **cmds, int nb)
{
        int     i;

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
void	ft_choose_type(t_token *temp, t_cmd_struct **cmds, int i)
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
}
void    ft_fill_struct_foreach_cmd(t_token *tokens, t_cmd_struct **cmds, int nb)
{
        int     i;
        t_token *temp;

        i = 0;
        temp = tokens;
        while (temp && i < nb)
        {
		ft_choose_type(temp, cmds, i);
                temp = temp->next;
        }
}

