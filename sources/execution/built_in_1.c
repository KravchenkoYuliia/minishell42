/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 17:11:22 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/11 11:11:53 by yukravch         ###   ########.fr       */
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
	int	i;
	t_env	*head;
	t_env	*ex_head;
//	t_env	*previous;



	i = 1;
	head = shell->env;
	if (shell->cmd[index]->args[0] && !shell->cmd[index]->args[1])
		return (SUCCESS); //no arguments
	while (head && shell->cmd[index]->args && ft_unset_or_not_unset(head->line, shell->cmd[index]->args) == true)  //first arg need to be unset
	{
		ex_head = head;
		printf("Head needed to be deleted = %s\n", ex_head->line);
		if (head->next)
			shell->env = head->next;
		printf("New head = %s\n", head->line);
		free(ex_head);
	}
	
	/*while (shell->cmd[index]->args[i])
	{
		temp = shell->env;
		while (temp)
		{
			if (ft_strncmp(shell->cmd[index]->args[i], temp->line, ft_strlen(temp->line)) == 0)
				
			temp = temp->next;
		}

		i++;
	}*/
	return (SUCCESS);
}
