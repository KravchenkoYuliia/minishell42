/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:26:59 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/04 17:04:59 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
	t_token	*token_lst;
	char	*input;
	(void)av;

	if (ac != 1)
	{	
		return(0);
	}
	//printf("%s\n", getenv("PATH"));
	t_token *cursor;
	while (1)
	{
		input = readline(SHELL_NAME);
		if (input && *input)
			add_history(input);
		if (ft_lexer(input))
		{
			token_lst = ft_parser(input);
			if (!token_lst)
				printf("input empty\n");
			cursor = token_lst;
			while(cursor)
			{
				printf("value: %s, type: %d\n", cursor->value, cursor->type);
				cursor = cursor->next;
			}
			ft_execution(token_lst, env);	
			//free_token_list(token_lst);
		}
		free(input);
	}
	return (0);
}
