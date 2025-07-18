/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:09:17 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/10 20:31:48 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_shlvl_in_array(char **env)
{
	int		i;
	int		shlvl;
	char	*newline;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("SHLVL=", env[i], 6))
		{
			newline = ft_strdup("SHLVL=");
			shlvl = ft_atoi(env[i] + 6);
			shlvl++;
			newline = ft_strjoin(newline, ft_itoa(shlvl));
			free(env[i]);
			env[i] = newline;
		}
		i++;
	}
}

void	ft_handle_shlvl_in_list(t_env *env)
{
	int		shlvl;
	char	*newline;
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (!ft_strncmp("SHLVL=", temp->line, 6))
		{
			newline = ft_strdup("SHLVL=");
			shlvl = ft_atoi(temp->line + 6);
			shlvl++;
			newline = ft_strjoin(newline, ft_itoa(shlvl));
			free(temp->line);
			temp->line = newline;
		}
		temp = temp->next;
	}
}

int	ft_env(t_minishell *shell, int index)
{
	bool	first_line;
	t_env	*list;

	first_line = true;
	list = shell->env;
	if (shell->cmd[index]->args[1])
	{
		ft_error_msg(shell, NULL, NULL, "env with no options or arguments :)");
		return (ERROR);
	}
	while (list)
	{
		if (first_line == false)
			printf("\n");
		printf("%s", ((char *)(list->line)));
		first_line = false;
		list = list->next;
	}
	if (shell->env && shell->process == PARENT)
		printf("\n");
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
