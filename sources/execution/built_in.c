/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:15:55 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/03 17:56:37 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_names(char *built_in_names[7])
{
	built_in_names[0] = "echo";
	built_in_names[1] = "cd";
	built_in_names[2] = "pwd";
	built_in_names[3] = "export";
	built_in_names[4] = "unset";
	built_in_names[5] = "env";
	built_in_names[6] = "exit";
}

void	ft_init_functions(int (*ft_built_in_functions[7])
		(t_minishell *, int))
{
	ft_built_in_functions[0] = &ft_echo;
	ft_built_in_functions[1] = &ft_cd;
	ft_built_in_functions[2] = &ft_pwd;
	ft_built_in_functions[3] = &ft_export;
	ft_built_in_functions[4] = &ft_unset;
	ft_built_in_functions[5] = &ft_env;
	ft_built_in_functions[6] = &ft_exit;
}

bool	ft_exec_built_in_cmd(t_minishell *shell, int index, char *cmd)
{
	char	*built_in_names[7];
	int		i;
	int		(*ft_built_in_functions[7])(t_minishell *, int);

	i = 0;
	ft_init_names(built_in_names);
	ft_init_functions(ft_built_in_functions);
	while (i < 7)
	{
		if ((cmd && ft_strncmp(cmd, built_in_names[i],
					(ft_strlen(cmd) + 1)) == 0))
		{
			ft_built_in_functions[i](shell, index);
			return (true);
		}
		i++;
	}
	return (false);
}
