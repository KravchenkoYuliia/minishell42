/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:55:18 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/24 16:54:34 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_unset_or_not_unset(char *env_line, char **args)
{
	int		i;
	char	*name;

	i = 1;
	name = ft_copy_name_inenv(env_line);
	while (args[i])
	{
		if (ft_strncmp(args[i], "_", 2) == 0)
			return (false);
		if (!ft_strchr(args[i], '=')
			&& ft_strncmp(name, args[i], (ft_strlen(name) + 1)) == 0)
		{
			free(name);
			return (true);
		}
		i++;
	}
	free(name);
	return (false);
}

void	ft_unset_head(t_minishell *shell, int index)
{
	t_env	*head;
	t_env	*ex;

	head = shell->env;
	while (head && shell->cmd[index]->args
		&& ft_unset_or_not_unset(head->line,
			shell->cmd[index]->args) == true)
	{
		ex = head;
		if (head->next)
		{
			shell->env = head->next;
			head = head->next;
		}
		if (ft_strncmp(ex->line, "_=/usr/bin/env",
				ft_strlen("_=/usr/bin/env")) == 0)
			break ;
		free(ex->line);
		free(ex);
	}
}

void	ft_else(t_env **current, t_env **previous)	
{
	if (!(*current)->next)
			(*current) = NULL;
	if ((*previous)->next && (*current) && (*current)->next)
	{
		(*previous) = (*previous)->next;
		(*current) = (*current)->next;
	}
}

void	ft_unset_body(char **args, t_env *current,
		t_env *previous, t_env *ex)
{
	while (current)
	{
		if (ft_unset_or_not_unset(current->line, args) == true)
		{
			ex = current;
			if (current->next)
			{
				previous->next = current->next;
				current = current->next;
			}
			else
			{
				previous->next = NULL;
				current = NULL;
			}
			if (ft_strncmp(ex->line, "_=/usr/bin/env",
					ft_strlen("_=/usr/bin/env")) == 0)
				return ;
			free(ex->line);
			free(ex);
		}
		else
			ft_else(&current, &previous);
	}
}

int	ft_unset(t_minishell *shell, int index)
{
	t_env	*current;
	t_env	*previous;
	t_env	*ex;

	if (shell->cmd[index]->args[0]
		&& (!shell->cmd[index]->args[1]))
		return (SUCCESS);
	if (!ft_strncmp("OLDPWD", shell->cmd[index]->args[1], 7))
		shell->need_to_add_oldpwd = false;
	ft_unset_head(shell, index);
	ex = NULL;
	if (shell->env)
	{
		previous = shell->env;
		current = shell->env->next;
		ft_unset_body(shell->cmd[index]->args, current, previous, ex);
	}
	return (SUCCESS);
}
