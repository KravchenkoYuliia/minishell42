/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:26:59 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/22 13:41:42 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av)
{
	t_token	*token_lst;
	char	*input;
	(void)av;

	if (ac != 1)
	{	
		return(0);
	}
	//printf("%s\n", getenv("PATH"));
	while (1)
	{
		input = readline("babyshell: ");
		if (ft_lexer(input))
		{
			token_lst = NULL;
			token_lst = ft_parser(input);
			if (!token_lst)
				printf("OUPS");
			ft_execution(token_lst);
			free_token_list(token_lst);
		}
		if (input[0] == 'C')
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		free(input);
	}
	return (0);
}
