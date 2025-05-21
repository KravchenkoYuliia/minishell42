/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_Y.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:47:36 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/21 14:41:04 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

const char	*ft_check_if_build_in_cmd(t_token *token)
{
	int			i;
	const char	*build_in_names[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(token->value, build_in_names[i],
				ft_strlen(token->value)) == 0)
			return (build_in_names[i]);
		i++;
	}
	return (NULL);
}

void	ft_execution(t_token *tokens)
{
	t_token		*token;
	const char	*cmd;

	token = tokens;
	while (token)
	{
		cmd = ft_check_if_build_in_cmd(token);
		if (cmd)
			printf("Execute build in cmd %s\n", cmd);
		else //cmd classic avec 'execve'
			printf("Execute cmd %s... \n", token->value);
			//ft_execve_cmd(token);
		token = token->next;
	}
}
