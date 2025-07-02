/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:01:09 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/02 16:15:14 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_get_home_path(t_env *env)
{
        t_env   *temp;

        temp = env;
        while (temp)
        {
                if (ft_strncmp(temp->line, "HOME=", 5) == 0)
                        return (temp->line + 5);
                temp = temp->next;
        }
        return (NULL);
}

void    ft_change_pwd(t_env *env, char *directory)
{
        bool    flag;
        t_env   *temp;
        char    oldpwd[PATH_MAX];
        char    newpwd[PATH_MAX];

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

int     ft_cd(t_minishell *shell, int index)
{
        char    directory[PATH_MAX];
        char    *home_path;

        if (!shell->cmd[index]->args[1])
        {
                home_path = ft_get_home_path(shell->env);
                if (!home_path)
                {
                        ft_error_msg(SHELL_NAME_ERROR, NULL, ": cd: HOME not set");
                        shell->exit_status = 1;
                        return (ERROR);
                }
                ft_strcpy(directory, home_path);
        }
        else if (shell->cmd[index]->args[1])
        {
                ft_strcpy(directory, shell->cmd[index]->args[1]);
                if (shell->cmd[index]->args[2])
                {
                        ft_error_msg(SHELL_NAME, NULL, "cd: too many arguments");
                        return (ERROR);
                }
        }
        if (chdir(directory) != 0)
        {
                ft_error_msg("toupetishell: cd",
                        directory, ": No such file or directory");
                return (ERROR);
        }
        ft_bzero(directory, PATH_MAX);
        getcwd(directory, PATH_MAX);
        ft_change_pwd(shell->env, directory);
        return (SUCCESS);
}
