/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:55:18 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/10 20:56:22 by yukravch         ###   ########.fr       */
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
		//if (ft_strncmp(args[i], "_", 2) == 0)
		//	return (false);
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
		else
			shell->env = NULL;
		free(ex->line);
		free(ex);

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
			free(ex->line);
			free(ex);
		}
		else
		{
			if (!current->next)
				current = NULL;
			if (previous->next && current && current->next)
			{
				previous = previous->next;
				current = current->next;
			}
		}
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
