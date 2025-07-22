/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_for_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:57:11 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/22 09:24:58 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_malloc_env_for_execve(char ***env, int nb)
{
	int	i;

	i = 0;
	(*env) = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!(*env))
		return (ERROR);
	return (SUCCESS);
}

int	ft_copy_env_for_execve(t_minishell *shell)
{
	int		i;
	int		nb_of_variables;
	t_env	*temp;

	i = 0;
	temp = shell->env;
	nb_of_variables = ft_count_var_in_env(shell->env);
	if (ft_malloc_env_for_execve(&shell->env_execve, nb_of_variables) == ERROR)
		return (ERROR);
	while (temp)
	{
		shell->env_execve[i] = ft_strdup(temp->line);
		if (!shell->env_execve[i])
			return (ERROR);
		temp = temp->next;
		i++;
	}
	shell->env_execve[i] = NULL;
	return (SUCCESS);
}

int	ft_count_var_in_env(t_env *env)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = env;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
