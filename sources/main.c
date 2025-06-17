/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:26:59 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/17 18:00:00 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_minishell(t_minishell **shell, char **env)
{
	*shell = (t_minishell *)malloc(sizeof(t_minishell));
	if (!*shell)
		exit(EXIT_FAILURE);
	(*shell)->token_lst = NULL;
	(*shell)->exit_status = 0;
	(*shell)->env = NULL;
	ft_fill_env(*shell, &(*shell)->env, env);
}

bool	ft_find_heredoc(t_token *token_lst)
{
	t_token	*temp;
	
	temp = token_lst;
	while (temp)
	{
		if (temp->type == HEREDOC)
			return (true);
		temp = temp->next;
	}
	return (false);
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
	//t_token *cursor;
	while (1)
	{
		shell->input = readline(SHELL_NAME);
		if (ft_lexer(shell->input))
		{
			shell->token_lst = ft_parser(shell->input);
			if (shell->input && *shell->input && !ft_find_heredoc(shell->token_lst))
				add_history(shell->input);
			//ft_expander(shell);
			/*cursor = shell->token_lst;
			while(cursor)
			{
				printf("value: %s, type: %d\n", cursor->value, cursor->type);
				cursor = cursor->next;
			}*/
			if (shell->token_lst)
				ft_execution(shell);
			free(shell->input);
		}
		else
			shell->exit_status = 2;
	}
	return (0);
}
