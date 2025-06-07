/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:50:25 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/06 17:59:22 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char*   ft_get_home_path(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->line, "HOME=", 5) == 0)
			return (temp->line + 5);
		temp = temp->next;
	}
	return (NULL);
}

void	ft_change_pwd(t_env *env, char *directory)
{
	t_env	*temp;
	char	oldpwd[PATH_MAX];

	temp = env;
	ft_bzero(oldpwd, PATH_MAX);
	while (temp)
	{
		if (ft_strncmp(temp->line, "PWD=", 5) == 0)
			ft_strcpy(oldpwd, temp->line);
		if (oldpwd[0] != '\0' && ft_strncmp(temp->line, "OLDPWD=", 8) == 0)
		{
			free(temp->line);
			temp->line = ft_strdup(oldpwd);
		}
		temp = temp->next;
	}
	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->line, "PWD=", 5) == 0)
		{
			free(temp->line);
			temp->line = ft_strdup(directory);
		}
		temp = temp->next;
	}
}
