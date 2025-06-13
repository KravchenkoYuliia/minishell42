/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 13:58:59 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/13 15:54:45 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_just_export(t_env *env)
{
        t_env   *temp;
        t_env   *export;
        t_env   *new;
        char    *line;

        temp = env;
        export = NULL;
        while (temp)
        {
		if (ft_strncmp(temp->line, "_=/usr/bin/env", ft_strlen("_=/usr/bin/env")) == 0)
			temp = temp->next;
		if (temp)
		{
			line = ft_strjoin_export("declare -x ", temp->line);
	                new = ft_lstnew_env(line);
        	        ft_lstadd_back_env(&export, new);
                	temp = temp->next;
		}
        }
        ft_print_env(export);
        ft_free_env(export);
        return (SUCCESS);
}

int     ft_export_value(t_minishell *shell, int index)
{
        int     i;
        char    *line;
        t_env*  new;
	char	*buffer;

        i = 1;
        while (shell->cmd[index]->args[i])
        {
		if (shell->cmd[index]->args[i][0] == '_' && shell->cmd[index]->args[i][1] == '=')
		{
			if (!shell->cmd[index]->args[i+1])
				break ;
			i++;
		}
		if (shell->cmd[index]->args[i][0] == '-')
		{
			printf("%s: export: %s: invalid option\n", SHELL_NAME_ERROR, shell->cmd[index]->args[i]);
			shell->exit_status = 2;
			return (ERROR);
		}
                if (!ft_isalpha(shell->cmd[index]->args[i][0]) && shell->cmd[index]->args[i][0] != '_')
                        printf("%s: export: `%s': not a valid identifier\n", SHELL_NAME_ERROR, shell->cmd[index]->args[i]);
                if (ft_charset(shell->cmd[index]->args[i], '=') == SUCCESS)
                {
                        line = ft_strdup(shell->cmd[index]->args[i]);
			buffer = ft_copy_name_inenv(line);
			if (ft_name_exists_already(shell->env, buffer, line) == false)
			{
				new = ft_lstnew_env(line);
				ft_lstadd_back_env(&shell->env, new);
			}
			free(buffer);
                }
                i++;
        }
        return (SUCCESS);
}

int	ft_export(t_minishell *shell, int index)
{
	if (!shell->cmd[index]->args[1])
	{
		if (ft_just_export(shell->env) != SUCCESS)
			return (ERROR);
	}
	else
	{
		if (ft_export_value(shell, index) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

int	ft_export_forempty_env(t_minishell *shell)
{
	char	buffer[PATH_MAX];
	char	*pwd;
	char	*shlvl;
	char	*env_path;
	t_env	*new;

	if (getcwd(buffer, PATH_MAX) == NULL)
	{
		shell->exit_status = 1;
		return (ERROR);
	}
	pwd = ft_strjoin("PWD=", buffer);
	shlvl = ft_strdup("SHLVL=1");
	env_path = ft_strdup("_=/usr/bin/env");
	new = ft_lstnew_env(pwd);
	ft_lstadd_back_env(&shell->env, new);
	new = ft_lstnew_env(shlvl);
	ft_lstadd_back_env(&shell->env, new);
	new = ft_lstnew_env(env_path);
	ft_lstadd_back_env(&shell->env, new);
	return (SUCCESS);
}
