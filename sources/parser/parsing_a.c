/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:37:20 by lfournie          #+#    #+#             */
/*   Updated: 2025/06/10 08:30:23 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_if_quotes_b(char *input, int start, char *value_buf, int buf_start)
{
	int		sp;
	int		db;
	bool	in_quote;
	
	sp = 0;
	db = 0;
	in_quote = false;
	while (input[start] && (((input[start] != 124
			&& input[start] != 60 && input[start] != 62) && !in_quote) || in_quote))
	{	
		if (input[start] == 39 && db % 2 == 0)
			sp++;
		else if (input[start] == 34 && sp % 2 == 0)
			db++;
		value_buf[buf_start++] = input[start++];
		if ((sp % 2 != 0 || db % 2 != 0) || (input[start] == 39 || input[start] == 34) || ft_isalnum(input[start]))
				in_quote = true;
		else
			break;
	}
	value_buf[buf_start] = '\0';
}


t_token	*ft_if_quotes_a(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	
	value_buf = malloc(100);
	if (!value_buf)
		exit(EXIT_FAILURE);
	ft_if_quotes_b(input, start, value_buf, 0);
	token = new_token_nd(value_buf, WORD, ft_strlen(value_buf));
	return (token);
}

t_token	*ft_if_command(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	int		j;
	
	value_buf = malloc(100);
	if (!value_buf)
		exit(EXIT_FAILURE);
	j = 0;
	while ((input[start] != 39 && input[start] != 34 && input[start] != 124 
			&& input[start] != 60 && input[start] != 62 && input[start] != 32)
			&& input[start])
		value_buf[j++] = input[start++];
	if (input[start] == 39 || input[start] == 34)
		ft_if_quotes_b(input, start, value_buf, j);
	else
		value_buf[j] = '\0';
	token = new_token_nd(value_buf, WORD, ft_strlen(value_buf));
	return (token);
}

t_token	*ft_if_pipe(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	
	(void)input;
	(void)start;
	value_buf = malloc(100);
	if (!value_buf)
		exit(EXIT_FAILURE);
	value_buf[0] = 124;
	value_buf[1] = '\0';
	token = new_token_nd(value_buf, PIPE, 1);
	return(token);
}
