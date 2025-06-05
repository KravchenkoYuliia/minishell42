/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:11:41 by yukravch          #+#    #+#             */
/*   Updated: 2025/06/05 08:44:50 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

int	ft_check_if_build_in_cmd(t_exec *exec, int str_index)
{
        int                     i;
        char    *built_in_names[] = {"echo", "cd", "pwd",
                "export", "unset", "env", "exit"};
        int    (*built_in_functions[])(t_exec *, int) = {
                NULL, &ft_cd, NULL, NULL, NULL, NULL,
                &ft_exit
        };

        i = 0;
        while (i < 7)
        {
                if (ft_strncmp(exec->cmd[str_index]->args[0], built_in_names[i],
                                ft_strlen(built_in_names[i]) + 1) == 0)
                {
                        if (built_in_functions[i] != NULL)
			{
				if (built_in_functions[i](exec, str_index) != SUCCESS)
					return (ERROR);
			}
                        else {
                                char    msg[30] = {0};
                                ft_strcpy(msg, built_in_names[i]);
                                ft_strcpy(msg + ft_strlen(msg),
                                        " is not implemented\n");
                                write(2, msg, ft_strlen(msg));
                        }
                        break ;
                }
                i++;
        }
	return SUCCESS;
}
/*
int	ft_pwd(t_exec *exec, int str_index)
{
		
}*/


char*   ft_get_home_path(char** env)
{
        int     i = 0;

        while (env[i])
        {
                if (ft_strncmp(env[i], "HOME=", 5) == 0)
                        return (env[i] + 5);
                i++;
        }
        return (NULL);
}


int     ft_cd(t_exec *exec, int str_index)
{
	/*
	args[0] == cd
	args[1] == directory OR rien
	args[2] == NULL OR error message*/
	int	i;
	char	*directory = exec->cmd[str_index]->args[1];
	char	*next_arg = exec->cmd[str_index]->args[2];

	i = 0;
	if (next_arg != NULL)
	{
		printf("toupetishell🤏: cd: too many arguments\n");
		return (ERROR);
	}
	if (directory == NULL)
	{
		directory = ft_get_home_path(exec->env);
	}
	if (chdir(directory) != SUCCESS)
		return (ERROR);
        return (0);
}

int    ft_exit(t_exec *exec, int str_index)
{
        int     i;
        unsigned char exit_status;

        i = 0;
        exit_status = 0;
        if ((ft_strncmp(exec->cmd[str_index]->args[0], "exit", 5) == 0))
        {
                if (exec->cmd[str_index]->args[1])
                {
			if (!ft_isdigit_str(exec->cmd[str_index]->args[1]))
			{
        	        	printf("exit\n");
				printf("toupetishell🤏​: exit: %s: numeric argument required\n", exec->cmd[str_index]->args[1]);
                		ft_free_struct_foreach_cmd(exec->cmd, exec->nb_of_cmd);
				close(exec->save_stdin);
				close(exec->save_stdout);
				close(exec->pipe[0]);
				close(exec->pipe[1]);
				free(exec);
	        	        exit(2);
			}
                        i = ft_atoi(exec->cmd[str_index]->args[1]);
                        exit_status = (unsigned char) i;
                }
                ft_free_struct_foreach_cmd(exec->cmd, exec->nb_of_cmd);
		close(exec->save_stdin);
		close(exec->save_stdout);
		close(exec->pipe[0]);
		close(exec->pipe[1]);
		free(exec);
                printf("exit\n");
                exit(exit_status);
        }
	return (SUCCESS);
}
