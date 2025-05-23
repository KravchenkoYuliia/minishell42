/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:26:59 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/23 12:15:32 by yukravch         ###   ########.fr       */
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
			/*while(token_lst)
			{
				printf("value: %s, type: %d\n", token_lst->value, token_lst->type);
				token_lst = token_lst->next;
			}*/
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
