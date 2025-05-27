/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:48:16 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/27 09:24:18 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_buf_redirs(char *input, int start, char *value_buf, int buf_start)
{
	bool	in_quote;
	
	in_quote = false;
	while (input[start] == 32 && input[start])
		value_buf[buf_start++] = input[start++];
	if ((input[start] == 34 || input[start] == 39) && in_quote == false)
		{
			in_quote = true;
			value_buf[buf_start++] = input[start++];
		}
	while (ft_redirs_lim(input[start]) && input[start])
		{
			value_buf[buf_start++] = input[start++];
			if ((input[start] == 34 || input[start] == 39) && in_quote == true)
			{
				value_buf[buf_start++] = input[start++];
				in_quote = false;
			}
			if ((!ft_redirs_lim(input[start])) && in_quote == true)
				value_buf[buf_start++] = input[start++];
		}
	value_buf[buf_start] = '\0';
}

t_token	*ft_if_heredoc(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	
	value_buf = malloc(100);
	if (!value_buf)
		exit(EXIT_FAILURE);
	value_buf[0] = 60;
	value_buf[1] = 60;
	set_buf_redirs(input, start, value_buf, 2);
	token = new_token_nd(value_buf, HEREDOC, ft_strlen(value_buf));
	return(token);
}
 t_token	*ft_if_input(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	
	value_buf = malloc(100);
	if (!value_buf)
		exit(EXIT_FAILURE);
	value_buf[0] = 60;
	set_buf_redirs(input, start, value_buf, 1);
	token = new_token_nd(value_buf, INPUT, ft_strlen(value_buf));
	return (token);
}
t_token	*ft_if_append(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	
	value_buf = malloc(100);
	if (!value_buf)
		exit(EXIT_FAILURE);
	value_buf[0] = 62;
	value_buf[1] = 62;
	set_buf_redirs(input, start, value_buf, 2);
	token = new_token_nd(value_buf, APPEND, ft_strlen(value_buf));
	return(token);
}
t_token	*ft_if_output(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	
	value_buf = malloc(100);
	if (!value_buf)
		exit(EXIT_FAILURE);
	value_buf[0] = 62;
	set_buf_redirs(input, start, value_buf, 1);
	token = new_token_nd(value_buf, OUTPUT, ft_strlen(value_buf));
	return (token);
}
