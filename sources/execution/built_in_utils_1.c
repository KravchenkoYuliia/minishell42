/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:17:14 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/13 15:45:17 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_charset(char *str, char c)
{
	int	i;

	i = 0 ;
	while (str[i])
	{
		if (str[i] == c)
			return (SUCCESS);
		i++;
	}
	return (ERROR);
}

void	ft_print_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		printf("%s\n", temp->line);
		temp = temp->next;
	}
}

char	*ft_copy_name_inenv(char *line)
{
	int	i;
	int	j;
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

bool	ft_name_exists_already(t_env *env, char	*name, char *line)
{
	int	i;
	int	j;
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
			if (ft_strncmp(temp->line, name, i) == 0)
			{
				free(temp->line);
				temp->line = line;
				return (true);
			}
		}
		else
		{
			if (ft_strncmp(temp->line, name, j) == 0)
			{
				free(temp->line);
				temp->line = line;
				return (true);
			}
		}
		temp = temp->next;
	}
	return (false);
}
/*
void	ft_change_valueof_name(t_env *env, char *line)
{
	int	i;
	t_env	*temp;

	temp = env;
	while (temp)
	{
		i = 0;
		while (temp->line[i] && temp->line[i] != '=')
			i++;
		if (ft_strncmp(temp->line, line, i) == 0)
		{
			free(temp->line);
			temp->line = line;
		}
		temp = temp->next;
	}
}
*/
char	*ft_strjoin_export(char *str1, char *str2)
{
	int	i;
	int	j;
	char	*line;
	int	len;

	i = 0;
	j = 0;
	len = ft_strlen(str1) + ft_strlen(str2) + 3;
	line = (char *)malloc(sizeof(char) * len);
	if (!line)
		return (NULL);
	while (str1[i])
	{
		line[i] = str1[i];
		i++;
	}
	while (str2[j])
	{
		if (j != 0  && str2[j - 1] == '=')
			break ;
		line[i] = str2[j];
		i++;
		j++;
	}
	line[i] = '\"';
	i++;
	while (str2[j])
	{
		line[i] = str2[j];
		i++;
		j++;
	}
	line[i] = '\"';
	i++;
	line[i] ='\0';
	return (line);
}

bool	ft_unset_or_not_unset(char *env_line, char **args)
{
	int	i;
	char	*name;

	i = 1;
	name = ft_copy_name_inenv(env_line);
	while (args[i])
	{
		if (!ft_strchr(args[i], '=') && ft_strncmp(name, args[i], (ft_strlen(name) + 1)) == 0)
		{
			free(name);
			return (true);
		}
		i++;
	}
	free(name);
	return (false);
}

