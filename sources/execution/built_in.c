/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:15:55 by yukravch          #+#    #+#             */
/*   Updated: 2025/07/03 14:26:25 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_exec_built_in_cmd(t_minishell *shell, int index, char *cmd)
{
	int	i;
	char	*built_in_names[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};
	int		(*ft_built_in_functions[])(t_minishell *, int) = {
		&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env,
		&ft_exit};

	i = 0;
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
