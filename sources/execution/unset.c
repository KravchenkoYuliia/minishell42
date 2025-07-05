/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:55:18 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/05 17:30:30 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset_or_not_unset(char *env_line, char **args)
{
	int		i;
	char	*name;

	i = 1;
	name = ft_copy_name_inenv(env_line);
	if (!name)
		return (MALLOC_FAIL);
	while (args[i])
	{
		if (!ft_strchr(args[i], '=')
			&& ft_strncmp(name, args[i], (ft_strlen(name) + 1)) == 0)
		{
			free(name);
			return (SUCCESS);
		}
		i++;
	}
	free(name);
	return (ERROR);
}

int	ft_unset_head(t_minishell *shell, int index)
{
	int		status;
	t_env	*head;
	t_env	*ex;

	status = 0;
	head = shell->env;
	status = ft_unset_or_not_unset(head->line,
                        shell->cmd[index]->args);
	if (status == MALLOC_FAIL)
		return (MALLOC_FAIL);
	while (head && shell->cmd[index]->args
		&& status == SUCCESS)
	{
		ex = head;
		if (head->next)
		{
			shell->env = head->next;
			head = head->next;
		}
		free(ex);
	}
	return (SUCCESS);
}

int	ft_unset_body(char **args, t_env *current,
		t_env *previous, t_env *ex)
{
	int	status;

	while (current)
	{
		status = ft_unset_or_not_unset(current->line, args);
		if (status == MALLOC_FAIL)
			return (MALLOC_FAIL);
		if (status == SUCCESS)
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
			free(ex);
		}
		else
		{
			previous = previous->next;
			current = current->next;
		}
	}
	return (SUCCESS);
}

int	ft_unset(t_minishell *shell, int index)
{
	t_env	*current;
	t_env	*previous;
	t_env	*ex;

	if (shell->cmd[index]->args[0] && !shell->cmd[index]->args[1])
		return (SUCCESS);
	if (ft_unset_head(shell, index) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	ex = NULL;
	previous = shell->env;
	current = shell->env->next;
	if (ft_unset_body(shell->cmd[index]->args, current, previous, ex) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}
