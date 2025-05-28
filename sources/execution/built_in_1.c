/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:11:41 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/28 10:58:37 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

void    ft_check_if_build_in_cmd(t_exec *exec, int str_index)
{
        int                     i;
        char    *built_in_names[] = {"echo", "cd", "pwd",
                "export", "unset", "env", "exit"};
        void    (*built_in_functions[])(t_exec *, int) = {
                NULL, NULL, NULL, NULL, NULL, NULL,
                &ft_exit
        };

        i = 0;
        while (i < 7)
        {
                if (ft_strncmp(exec->cmd[str_index]->args[0], built_in_names[i],
                                ft_strlen(built_in_names[i]) + 1) == 0)
                {
                        if (built_in_functions[i] != NULL)
                                built_in_functions[i](exec, str_index);
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
}

void    ft_exit(t_exec *exec, int str_index)
{
        int     i;
        unsigned char exit_status;

        i = 0;
        exit_status = 0;
        if ((ft_strncmp(exec->cmd[str_index]->args[0], "exit", 5) == 0))
        {
                if (exec->cmd[str_index]->args[1])
                {
			if (!ft_isdigit(exec->cmd[str_index]->args[1]))
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
}
