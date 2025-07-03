/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 19:42:23 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/03 13:07:42 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_option_check(t_minishell *shell, int index, int i)
{
	if (shell->cmd[index]->args[i][0] == '-')
	{
		printf("%s: export: %s: invalid option\n",
			SHELL_NAME_ERROR, shell->cmd[index]->args[i]);
		shell->exit_status = 2;
		return (ERROR);
	}
	return (SUCCESS);
}

bool	ft_line_bigger_than_name(t_env *temp, char *line, char *name, int i)
{
	if (ft_strncmp(temp->line, name, i) == 0)
	{
		free(temp->line);
		temp->line = line;
		return (true);
	}
	return (false);
}

bool	ft_line_smaller_than_name(t_env *temp, char *line, char *name, int j)
{
	if (ft_strncmp(temp->line, name, j) == 0)
	{
		free(temp->line);
		temp->line = line;
		return (true);
	}
	return (false);
}

bool	ft_name_exists_already(t_env *env, char *name, char *line)
{
	int		i;
	int		j;
	t_env	*temp;

	j = ft_strlen(name);
	temp = env;
	while (temp)
	{
		i = 0;
		while (temp->line[i] && temp->line[i] != '=')
			i++;
		if (i >= j)
		{
			if (ft_line_bigger_than_name(temp, line, name, i) == true)
				return (true);
		}
		else
		{
			if (ft_line_smaller_than_name(temp, line, name, j) == true)
				return (true);
		}
		temp = temp->next;
	}
	return (false);
}

char	*ft_copy_name_inenv(char *line)
{
	int		i;
	int		j;
	char	*buffer;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '=')
		i++;
	buffer = (char *)malloc(sizeof(char) * i + 1);
	if (!buffer)
		return (NULL);
	while (j < i)
	{
		buffer[j] = line[j];
		j++;
	}
	buffer[j] = '\0';
	return (buffer);
}
