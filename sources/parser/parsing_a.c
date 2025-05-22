/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_a.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:37:20 by lfournie          #+#    #+#             */
/*   Updated: 2025/05/22 15:04:22 by lfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*ft_if_simple_quotes(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	int		j;
	
	value_buf = malloc(100);
		if (!value_buf)
			exit(EXIT_FAILURE);
	j = 0;
	start++;
	while (input[start] != 39 && input[start])
	{
		value_buf[j] = input[start];
		start++;
		j++;
	}
	value_buf[j] = '\0';
	token = new_token_nd(value_buf, CMD, j + 2);
	if (!token)
	{
		free(value_buf);
		return (NULL);
	}
	free(value_buf);
	return (token);
}

t_token	*ft_if_double_quotes(char *input, int start)
{
	t_token	*token;
	char	*value_buf;
	int		j;
	
	value_buf = malloc(100);
		if (!value_buf)
			exit(EXIT_FAILURE);
	j = 0;
	start++;
	while (input[start] != 34 && input[start])
	{
		value_buf[j] = input[start];
		start++;
		j++;
	}
	value_buf[j] = '\0';
	token = new_token_nd(value_buf, CMD, j + 2);
	if (!token)
	{
		free(value_buf);
		return (NULL);
	}
	free(value_buf);
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
	{
		value_buf[j] = input[start];
		start++;
		j++;
	}
	value_buf[j] = '\0';
	token = new_token_nd(value_buf, CMD, j);
	if (!token)
	{
		free(value_buf);
		return (NULL);
	}
	free(value_buf);
	return (token);
}

t_token *ft_parser(char *input)
{
	t_token	*token_lst;
	t_token	*new_token;
	int		i;

	token_lst = NULL;
	i = 0;
	while (i < ft_strlen(input))
	{
		if (input[i] == 39)
		{
			new_token = ft_if_simple_quotes(input, i);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 34)
		{
			new_token = ft_if_double_quotes(input, i);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 124)
		{
			new_token = ft_if_pipe(input, i);
			i++;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 60 && input[i + 1] == 60)
		{
			new_token = ft_if_heredoc(input, i);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 60 && input[i + 1] != 60)
		{
			new_token = ft_if_input(input, i);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 62 && input[i + 1] == 62)
		{
			new_token = ft_if_append(input, i);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 62 && input[i + 1] != 62)
		{
			new_token = ft_if_output(input, i);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
		else if (input[i] == 32)
			i++;
		else
		{
			new_token = ft_if_command(input, i);
			i += new_token->incr;
			ft_lstadd_back_tok(&token_lst, new_token);
		}
	}
	return (token_lst);
}
