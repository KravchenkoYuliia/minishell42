/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_Y.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:47:36 by yukravch          #+#    #+#             */
/*   Updated: 2025/05/21 13:53:24 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_check_if_build_in_cmd(t_token *token)
{
	if (ft_strncmp(token->value, "echo", ft_strlen(token->value)) == 0)
		return ("echo");
		//call ft to execute build in command
	if (ft_strncmp(token->value, "cd", ft_strlen(token->value)) == 0)
		return ("cd");
	if (ft_strncmp(token->value, "pwd", ft_strlen(token->value)) == 0)
		return ("pwd");
	if (ft_strncmp(token->value, "export", ft_strlen(token->value)) == 0)
		return ("export");
	if (ft_strncmp(token->value, "unset", ft_strlen(token->value)) == 0)
		return ("unset");
	if (ft_strncmp(token->value, "env", ft_strlen(token->value)) == 0)
		return ("env");
	if (ft_strncmp(token->value, "exit", ft_strlen(token->value)) == 0)
		return ("exit");
	return (0);
}

void	ft_execution(t_token *tokens)
{
	t_token	*token;
	char	*cmd;

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
