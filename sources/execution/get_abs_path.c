/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_abs_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 17:27:00 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/27 14:24:52 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_path_for_cmd(char **paths, t_minishell *shell, int index)
{
	int		i;
	char	*add_slash;
	char	*cmd_path;

	i = 0;
	while (paths[i])
	{
		add_slash = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(add_slash, shell->cmd[index]->args[0]);
		free(add_slash);
		if (access(cmd_path, X_OK) == 0)
		{
			ft_free_args(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_free_args(paths);
	return (NULL);
}

char	*ft_find_absolute_path(t_minishell *shell, int index)
{
	t_env	*temp;
	char	*env_line_with_paths;
	char	**array_with_paths;
	char	*cmd_path;

	temp = shell->env;
	while (ft_strncmp(temp->line, "PATH=", 5) != 0)
		temp = temp->next;
	env_line_with_paths = temp->line + 5;
	array_with_paths = ft_split(env_line_with_paths, ':');
	if (!array_with_paths)
		return (NULL);
	cmd_path = ft_get_path_for_cmd(array_with_paths, shell, index);
	return (cmd_path);
}
