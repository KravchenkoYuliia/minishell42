/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:48:16 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/22 14:56:58 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	free(value_buf);
	return(token);
}
t_token	*ft_if_heredoc(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	int		j;
	
	value_buf = malloc(100);
	if (!value_buf)
		exit(EXIT_FAILURE);
	value_buf[0] = 60;
	value_buf[1] = 60;
	start += 2;
	j = 2;
	while ((input[start] == 32 || ft_isalnum(input[start])) && input[start])
	{
		value_buf[j] = input[start];
		start++;
		j++;
	}
	value_buf[j] = '\0';
	token = new_token_nd(value_buf, HEREDOC, j);
	free(value_buf);
	return(token);
}
 t_token	*ft_if_input(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	int		j;
	
	value_buf = malloc(100);
	if (!value_buf)
		exit(EXIT_FAILURE);
	value_buf[0] = 60;
	start++;
	j = 1;
	while ((input[start] == 32 || ft_isalnum(input[start])) && input[start])
	{
		value_buf[j] = input[start];
		start++;
		j++;
	}
	value_buf[j] = '\0';
	token = new_token_nd(value_buf, INPUT, j);
	free(value_buf);
	return (token);
}
t_token	*ft_if_append(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	int		j;
	
	value_buf = malloc(100);
	if (!value_buf)
		exit(EXIT_FAILURE);
	value_buf[0] = 62;
	value_buf[1] = 62;
	start += 2;
	j = 2;
	while ((input[start] == 32 || ft_isalnum(input[start])) && input[start])
	{
		value_buf[j] = input[start];
		start++;
		j++;
	}
	value_buf[j] = '\0';
	token = new_token_nd(value_buf, APPEND, j);
	free(value_buf);
	return(token);
}
t_token	*ft_if_output(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	int		j;
	
	value_buf = malloc(100);
	if (!value_buf)
		exit(EXIT_FAILURE);
	value_buf[0] = 62;
	start++;
	j = 1;
	while ((input[start] == 32 || ft_isalnum(input[start])) && input[start])
	{
		value_buf[j] = input[start];
		start++;
		j++;
	}
	value_buf[j] = '\0';
	token = new_token_nd(value_buf, INPUT, j);
	free(value_buf);
	return (token);
}
