/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:26:59 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/05 16:33:09 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_minishell(t_minishell **shell, char **env)
{
	*shell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!*shell)
		exit(EXIT_FAILURE);
	(*shell)->exit_status = 0;
	ft_fill_env(&(*shell)->env, env);
	//ft_print_list_env((*shell)->env);
}

int main(int ac, char **av, char **env)
{
	t_minishell	*shell;
	(void)av;
	
	shell = NULL;
	ft_init_minishell(&shell, env);
	if (ac != 1)
	{	
		return(0);
	}
	//printf("%s\n", getenv("PATH"));
	t_token *cursor;
	while (1)
	{
		shell->input = readline(SHELL_NAME);
		if (shell->input)
			add_history(shell->input);
		if (ft_lexer(shell->input))
		{
			shell->token_lst = ft_parser(shell->input);
			if (!shell->token_lst)
				printf("input empty\n");
			cursor = shell->token_lst;
			while(cursor)
			{
				printf("value: %s, type: %d\n", cursor->value, cursor->type);
				cursor = cursor->next;
			}
			ft_execution(shell);
			//free_token_list(shell->token_lst);
		}
		free(shell->input);
	}
	return (0);
}
