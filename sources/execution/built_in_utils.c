/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:50:25 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/27 13:57:43 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_option(char	*args)
{
	int	i;

	i = 1;
	if (args[0] != '-')
		return (false);
	if (!args[i])
		return (false);
	while (args[i])
	{
		if (args[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

char	*ft_get_home_path(t_env *env)
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
	bool	flag;
	t_env	*temp;
	char	oldpwd[PATH_MAX];
	char	newpwd[PATH_MAX];

	flag = false;
	temp = env;
	ft_bzero(oldpwd, PATH_MAX);
	while (temp)
	{
		if (ft_strncmp(temp->line, "PWD=", 4) == 0 && flag == false)
		{
			flag = true;
			ft_strcpy(oldpwd, "OLDPWD=");
			ft_strcpy(oldpwd + 7, temp->line + 4);
		}
		if (oldpwd[0] != '\0' && ft_strncmp(temp->line, "OLDPWD=", 7) == 0)
		{
			free(temp->line);
			temp->line = ft_strdup(oldpwd);
		}
		temp = temp->next;
	}
	temp = env;
	while (temp)
	{
		if (ft_strncmp(temp->line, "PWD=", 4) == 0)
		{
			ft_strcpy(newpwd, "PWD=");
			ft_strcpy(newpwd + 4, directory);
			free(temp->line);
			temp->line = ft_strdup(newpwd);
		}
		temp = temp->next;
	}
}
