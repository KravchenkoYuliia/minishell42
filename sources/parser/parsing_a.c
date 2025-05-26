/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:37:20 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/26 14:10:59 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_if_quotes(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	int		j;
	
	value_buf = malloc(100);
		if (!value_buf)
			exit(EXIT_FAILURE);
	value_buf[0] = input[start];
	j = 1;
	start++;
	while ((input[start] != 39 && input[start] != 34) && input[start])
	{	
		value_buf[j++] = input[start++];
		if (input[start + 2] == 39 || input[start + 2] == 34)
		{
			value_buf[j++] = input[start++];
			value_buf[j++] = input[start++];
		}
	}
	value_buf[j] = input[start];
	value_buf[j + 1] = '\0';
	token = new_token_nd(value_buf, CMD, j + 2);
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
			&& input[start] != 60 && input[start] != 62)
			&& input[start])
		value_buf[j++] = input[start++];
	value_buf[j] = '\0';
	token = new_token_nd(value_buf, CMD, j);
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
