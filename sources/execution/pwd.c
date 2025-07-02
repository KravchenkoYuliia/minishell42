/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:03:56 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/02 18:58:01 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_minishell *shell, int index)
{
	char	buffer[PATH_MAX];

	(void) shell;
	(void) index;
	ft_bzero(buffer, PATH_MAX);
	if (getcwd(buffer, PATH_MAX) == NULL)
		return (ERROR);
	ft_write_stdout(buffer);
	ft_write_stdout("\n");
	return (SUCCESS);
}

void	ft_change_oldpwd(t_env *env)
{
	bool	flag;
	t_env	*temp;
	char	oldpwd[PATH_MAX];

	temp = env;
	flag = false;
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
}

void	ft_change_pwd(t_env *env, char *directory)
{
	t_env	*temp;
	char	newpwd[PATH_MAX];

	ft_change_oldpwd(env);
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
