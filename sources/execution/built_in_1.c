/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:11:22 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/11 15:01:02 by yukravch         ###   ########.fr       */
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
                line = ft_strjoin_export("declare -x ", temp->line);
                new = ft_lstnew_env(line);
                ft_lstadd_back_env(&export, new);
                temp = temp->next;
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

int	ft_unset(t_minishell *shell, int index)
{
	t_env	*head;
	t_env	*current;
	t_env	*ex;
	t_env	*previous;

	head = shell->env;
	if (shell->cmd[index]->args[0] && !shell->cmd[index]->args[1])
		return (SUCCESS); //no arguments
	while (head && shell->cmd[index]->args && ft_unset_or_not_unset(head->line, shell->cmd[index]->args) == true)  //first arg need to be unset
	{
		ex = head;
		if (head->next)
		{
			shell->env = head->next;
			head = head->next;
		}
		printf("New head = %s\n", head->line);
		free(ex);
	}
	previous = shell->env;
	current = shell->env->next;
	while (current)
	{
		if (ft_unset_or_not_unset(current->line, shell->cmd[index]->args) == true)
		{
			printf("Need to be deleted %s, previous = %s\n", current->line, previous->line);
			ex = current;
			if (current->next)
			{
				previous->next = current->next;
				current = current->next;
			
				printf("Now previous %s points to %s, current = %s\n", previous->line, previous->next->line, current->line);
			}
			else
			{
				previous->next = NULL;
				current = NULL;
			}
			free(ex);
		}
		else
		{
			previous = previous->next;
			current = current->next;
		}
	}
	return (SUCCESS);
}
