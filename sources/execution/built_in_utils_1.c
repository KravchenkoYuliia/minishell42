/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:17:14 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/09 19:58:31 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_just_export(t_env *env)
{
	t_env	*temp;
	t_env	*export;
	t_env	*new;
	char	*line;
       
	temp = env;
	export = NULL;
	while (temp)
	{
		line = ft_strjoin("declare -x ", temp->line);
		new = ft_lstnew_env(line);
		ft_lstadd_back_env(&export, new);
		temp = temp->next;
	}
	ft_print_env(export);
	ft_free_env(export);
	return (SUCCESS);
}

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

int	ft_export_value(t_minishell *shell, int index)
{
	int	i;
	char	*line;
	t_env*	new;

	i = 1;
	while (shell->cmd[index]->args[i])
	{
		if (!ft_isalpha(shell->cmd[index]->args[i][0]))
			printf("%s: export: `%s': not a valid identifier\n", SHELL_NAME_ERROR, shell->cmd[index]->args[i]);
		if (ft_charset(shell->cmd[index]->args[i], '=') == SUCCESS)
		{
			line = ft_strdup(shell->cmd[index]->args[i]);
			//if line "name=" == temp->line -> unset temp->line
			new = ft_lstnew_env(line);
			ft_lstadd_back_env(&shell->env, new);
		}
		i++;
	}
	return (SUCCESS);
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

bool	ft_unset_or_not_unset(char *env_line, char **args)
{
	int	i;
	char	*name;

	i = 1;
	name = ft_copy_name_inenv(env_line);
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
			i++;
		if (ft_strncmp(name, args[i], (ft_strlen(name) + 1)) == 0)
		{
			free(name);
			return (true);
		}
		i++;
	}
	free(name);
	return (false);
}

